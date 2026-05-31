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

#pragma once

#include <cssdk/public/os_defs.h>
#include <cstddef>

namespace cssdk
{
    /**
     * @brief N/D
    */
    constexpr auto CREATE_INTERFACE_PROC_NAME = "CreateInterface";

    /**
     * @brief N/D
    */
    enum class CreateInterfaceStatus
    {
        /**
         * @brief N/D
        */
        Ok = 0,

        /**
         * @brief N/D
        */
        Failed
    };

    /**
     * @brief All interfaces derive from this.
    */
    // ReSharper disable once CppClassCanBeFinal
    class SysInterfaceBase // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        virtual ~SysInterfaceBase() = default;
    };

    /**
     * @brief N/D
    */
    using CreateInterfaceFn = SysInterfaceBase* (*)(const char* name, CreateInterfaceStatus* return_code);

    /**
     * @brief N/D
    */
    using InstantiateInterfaceFn = SysInterfaceBase* (*)();

    /**
     * @brief Used internally to register classes.
    */
    class SysInterfaceReg
    {
    public:
        SysInterfaceReg(const InstantiateInterfaceFn fn, const char* interface_name)
            : create_fn(fn), name(interface_name), next(interface_regs)
        {
            interface_regs = this;
        }

        /**
         * @brief N/D
        */
        InstantiateInterfaceFn create_fn{};

        /**
         * @brief N/D
        */
        const char* name{};

        /**
         * @brief For the global list.
        */
        SysInterfaceReg* next{};

        /**
         * @brief N/D
        */
        static inline SysInterfaceReg* interface_regs{};
    };

    // Use this to expose an interface that can have multiple instances.
    // e.g.:
    // EXPOSE_INTERFACE(CInterfaceImp, IInterface, "MyInterface001")
    // This will expose a class called CInterfaceImp that implements IInterface (a pure class)
    // clients can receive a pointer to this class by calling CreateInterface("MyInterface001")
    //
    // In practice, the shared header file defines the interface (IInterface) and version name ("MyInterface001")
    // so that each component can use these names/vtables to communicate
    //
    // A single class can support multiple interfaces through multiple inheritance
    //
    // Use this if you want to write the factory function.
#define EXPOSE_INTERFACE_FN(functionName, interfaceName, versionName) \
    static SysInterfaceReg __g_Create##interfaceName##_reg(functionName, versionName);

#define EXPOSE_INTERFACE(className, interfaceName, versionName) \
    static SysInterfaceBase* __Create##className##_interface()  \
    {                                                           \
        return (interfaceName*)new (className);                 \
    }                                                           \
    static SysInterfaceReg __g_Create##className##_reg(__Create##className##_interface, versionName);

    // Use this to expose a singleton interface with a global variable you've created.
#define EXPOSE_SINGLE_INTERFACE_GLOBALVAR(className, interfaceName, versionName, globalVarName)                       \
    static SysInterfaceBase* __Create##className##interfaceName##_interface()                                         \
    {                                                                                                                 \
        return (SysInterfaceBase*)&(globalVarName);                                                                   \
    }                                                                                                                 \
    static SysInterfaceReg __g_Create##className##interfaceName##_reg(__Create##className##interfaceName##_interface, \
                                                                      versionName);

    // Use this to expose a singleton interface. This creates the global variable for you automatically.
#define EXPOSE_SINGLE_INTERFACE(className, interfaceName, versionName) \
    static className __g_##className##_singleton;                      \
    EXPOSE_SINGLE_INTERFACE_GLOBALVAR(className, interfaceName, versionName, __g_##className##_singleton)

#if defined(_WIN32)
#define EXPORT_FUNCTION __declspec(dllexport) FORCE_STACK_ALIGN
#else
#define EXPORT_FUNCTION __attribute__((visibility("default"))) FORCE_STACK_ALIGN
#endif

    /**
     * @brief Load/unload components.
    */
    class SysModule;

    extern "C"
    {
        /**
 * @brief N/D
*/
        EXPORT_FUNCTION SysInterfaceBase* CreateInterface(const char* name, CreateInterfaceStatus* return_code);
    }

    /**
     * @brief N/D
    */
    void* InitializeInterface(const char* interface_name, const CreateInterfaceFn* factory_list,
                              std::size_t num_factories);

    /**
     * @brief N/D
    */
    CreateInterfaceFn SysGetFactoryThis();

    /**
     * @brief Loads a DLL/component from disk and returns a handle to it.
     *
     * @param module_name Filename of the component.
     * @param load_flags The action to be taken when loading the module.
     *
     * @return Opaque handle to the module (hides system dependency).
    */
    SysModule* SysLoadModule(const char* module_name, unsigned long load_flags = 0);

    /**
     * @brief Unloads a DLL/component from.
     *
     * @param module_handle Opaque handle to the module (hides system dependency).
    */
    bool SysUnloadModule(SysModule*& module_handle);

    /**
     * @brief Returns a pointer to a function, given a module.
     *
     * @param module_handle Opaque handle to the module (hides system dependency).
     *
     * @return Factory for this module.
    */
    CreateInterfaceFn SysGetFactory(SysModule* module_handle);
}
