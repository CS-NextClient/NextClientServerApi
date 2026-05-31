/*
 *  Half Life 1 SDK Copyright(c) Valve Corp.
 *
 *  THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE CORPORATION ("Valve").
 *  PLEASE READ IT BEFORE DOWNLOADING OR USING THE HALF LIFE 1 SDK ("SDK"). BY
 *  DOWNLOADING AND/OR USING THE HALF LIFE 1 SDK YOU ACCEPT THIS LICENSE. IF YOU DO
 *  NOT AGREE TO THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.
 *
 *  You may, free of charge, download and use the SDK to develop a modified Valve
 *  game running on the Half-Life 1 engine. You may distribute your modified Valve
 *  game in source and object code form, but only for free. Terms of use for Valve
 *  games are found in the Steam Subscriber Agreement located here:
 *  http://store.steampowered.com/subscriber_agreement/
 *
 *  You may copy, modify, and distribute the SDK and any modifications you make to
 *  the SDK in source and object code form, but only for free. Any distribution of
 *  this SDK must include this LICENSE file.
 *
 *  Any distribution of the SDK or a substantial portion of the SDK must include
 *  the above copyright notice and the following:
 *
 *    DISCLAIMER OF WARRANTIES. THE HALF LIFE 1 SDK AND ANY OTHER MATERIAL
 *    DOWNLOADED BY LICENSEE IS PROVIDED "AS IS". VALVE AND ITS SUPPLIERS
 *    DISCLAIM ALL WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS OR IMPLIED,
 *    INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY,
 *    NON-INFRINGEMENT, TITLE AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    LIMITATION OF LIABILITY. IN NO EVENT SHALL VALVE OR ITS SUPPLIERS BE LIABLE
 *    FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 *    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
 *    LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THE ENGINE AND/OR THE
 *    SDK, EVEN IF VALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *  If you would like to use the SDK for a commercial purpose, please contact Valve
 *  at sourceengine@valvesoftware.com.
 */

#include <cssdk/public/interface.h>
#include <cstdio>
#include <cstring>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN // NOLINT(clang-diagnostic-unused-macros)
#include <Windows.h>
#else
#include <climits>
#include <cstring>
#include <dlfcn.h>
#include <unistd.h>
#endif

namespace cssdk
{
    SysModule* SysLoadModule(const char* module_name, [[maybe_unused]] const unsigned long load_flags) // NOLINT(google-runtime-int)
    {
        if (module_name == nullptr) {
            return nullptr;
        }

#if defined(_WIN32)
        auto* const module_handle = LoadLibraryEx(module_name, nullptr, load_flags);
#else
        void* module_handle = nullptr;

        if (module_name[0] != '/') {
            char working_dir[PATH_MAX];
            char module_name_absolute[PATH_MAX];

            if (!getcwd(working_dir, sizeof(working_dir))) {
                return nullptr;
            }

            if (working_dir[std::strlen(working_dir) - 1] == '/') {
                working_dir[std::strlen(working_dir) - 1] = 0;
            }

            if (std::snprintf(module_name_absolute, sizeof(module_name_absolute), "%s/%s", working_dir, module_name) <= 0) {
                return nullptr;
            }

            module_handle = dlopen(module_name_absolute, RTLD_NOW);
        }
        else {
            module_handle = dlopen(module_name, RTLD_NOW);
        }
#endif

        return reinterpret_cast<SysModule*>(module_handle);
    }

    bool SysUnloadModule(SysModule*& module_handle)
    {
        if (module_handle == nullptr) {
            return true;
        }

#if defined(_WIN32)
        if (FreeLibrary(reinterpret_cast<HMODULE>(module_handle))) {
            module_handle = nullptr;
        }
#else
        if (!dlclose(module_handle)) {
            module_handle = nullptr;
        }
#endif

        return module_handle == nullptr;
    }

    EXPORT_FUNCTION SysInterfaceBase* CreateInterface(const char* name, CreateInterfaceStatus* return_code)
    {
        for (auto* cur = SysInterfaceReg::interface_regs; cur; cur = cur->next) {
            if (std::strcmp(cur->name, name) == 0) {
                if (return_code) {
                    *return_code = CreateInterfaceStatus::Ok;
                }

                return cur->create_fn();
            }
        }

        if (return_code) {
            *return_code = CreateInterfaceStatus::Failed;
        }

        return nullptr;
    }

    void* InitializeInterface(const char* interface_name, const CreateInterfaceFn* factory_list,
                              const std::size_t num_factories)
    {
        for (std::size_t i = 0; i < num_factories; i++) {
            const auto factory = factory_list[i];

            if (!factory) {
                continue;
            }

            if (void* ret_val = factory(interface_name, nullptr); ret_val) {
                return ret_val;
            }
        }

        return nullptr;
    }

    CreateInterfaceFn SysGetFactoryThis()
    {
        return CreateInterface;
    }

    CreateInterfaceFn SysGetFactory(SysModule* module_handle)
    {
        if (module_handle == nullptr) {
            return nullptr;
        }

#if defined(_WIN32)
        return reinterpret_cast<CreateInterfaceFn>(
            GetProcAddress(reinterpret_cast<HMODULE>(module_handle), CREATE_INTERFACE_PROC_NAME));
#else
        return reinterpret_cast<CreateInterfaceFn>(dlsym(module_handle, CREATE_INTERFACE_PROC_NAME));
#endif
    }
}
