/*
 *  Copyright (C) 2020 the_hunter
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifdef HAS_CSSDK_LIB
#include <core/regamedll_api.h>
#include <core/console.h>
#include <core/strings/consts.h>
#include <core/strings/path.h>
#include <cssdk/public/interface.h>

#ifdef HAS_AMXX_LIB
#include <amxx/config.h>
#else
#include <metamod/config.h>
#endif

using namespace core;
using namespace cssdk;

namespace
{
#ifdef HAS_AMXX_LIB
    constexpr auto MODULE_NAME = amxx::MODULE_NAME;
#else
    constexpr auto MODULE_NAME = metamod::PLUGIN_NAME;
#endif

    template <typename... Args>
    void Error(const bool silent, const std::string& format, Args&&... args)
    {
        if (!silent) {
            console::Message<false>(str::EMPTY); // Line feed
            console::Error(format, std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void Message(const bool silent, const std::string& format, Args&&... args)
    {
        if (!silent) {
            console::Message<false>(format, std::forward<Args>(args)...);
        }
    }
}

namespace core::regamedll_api
{
    bool Init(const bool silent)
    {
        using namespace detail;

        if (Initialized()) {
            return true;
        }

        //
        // Load game module.
        //

#ifdef _WIN32
        const auto game_module_path = str::BuildPathName("dlls/mp.dll");
#else
        const auto game_module_path = str::BuildPathName("dlls/cs.so");
#endif
        auto* const game_module = SysLoadModule(game_module_path.c_str());

        if (game_module == nullptr) {
            Error(silent, "Failed to locate game module.\n");
            return false;
        }

        //
        // Get the game interface factory.
        //

        const auto interface_factory = SysGetFactory(game_module);

        if (interface_factory == nullptr) {
            Error(silent, "Failed to locate interface factory in game module.\n");
            return false;
        }

        //
        // Get the ReGameDll API interface.
        //

        auto ret_code = CreateInterfaceStatus::Failed;
        auto* const interface_base = interface_factory(VREGAMEDLL_API_VERSION, &ret_code);

        if (ret_code != CreateInterfaceStatus::Ok || interface_base == nullptr) {
            Error(silent, "Failed to retrieve \"%s\" interface from game module; return code %d.\n",
                  VREGAMEDLL_API_VERSION, static_cast<int>(ret_code));

            return false;
        }

        regamedll_api = reinterpret_cast<IReGameDllApi*>(interface_base);

        //
        // Check the ReGameDll version.
        //

        const auto major_version = MajorVersion();
        const auto minor_version = MinorVersion();

        if (major_version != REGAMEDLL_API_VERSION_MAJOR) {
            Error(silent, "ReGameDll API major version mismatch; expected %d, real %d.",
                  REGAMEDLL_API_VERSION_MAJOR, major_version);

            if (major_version < REGAMEDLL_API_VERSION_MAJOR) {
                Message(silent, "Please update the ReGameDll up to a major version API >= %d.\n",
                        REGAMEDLL_API_VERSION_MAJOR);
            }
            else {
                Message(silent, "Please update the %s up to a major version API >= %d.\n",
                        MODULE_NAME, REGAMEDLL_API_VERSION_MAJOR);
            }

            return false;
        }

        if (minor_version < REGAMEDLL_API_VERSION_MINOR) {
            Error(silent, "ReGameDll API minor version mismatch; expected %d, real %d.",
                  REGAMEDLL_API_VERSION_MINOR, minor_version);

            Message(silent, "Please update the ReGameDll up to a minor version API >= %d.\n",
                    REGAMEDLL_API_VERSION_MINOR);

            return false;
        }

        //
        // Safe check cs_entity API interface version.
        //

        if (!regamedll_api->CheckCsEntityVersion(CS_ENTITY_API_INTERFACE_VERSION)) {
            Error(silent, "Interface CCSEntity API version '%s' not found.\n", CS_ENTITY_API_INTERFACE_VERSION);
            return false;
        }

        //
        // Safe check game_rules API interface version.
        //

        if (!regamedll_api->CheckGameRulesVersion(GAME_RULES_API_INTERFACE_VERSION)) {
            Error(silent, "Interface CGameRules API version '%s' not found.\n", GAME_RULES_API_INTERFACE_VERSION);
            return false;
        }

        //
        // ReGameDllApi assignment.
        //

        regamedll_funcs = regamedll_api->GetFuncs();
        assert(regamedll_funcs != nullptr);

        regamedll_hook_chains = regamedll_api->GetHookChains();
        assert(regamedll_hook_chains != nullptr);

        return Initialized();
    }
}
#endif
