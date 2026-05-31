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
#include <core/rehlds_api.h>
#include <core/console.h>
#include <core/strings/consts.h>
#include <cssdk/engine/engine_hlds_api.h>
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

namespace core::rehlds_api
{
    bool Init(const bool silent)
    {
        using namespace detail;

        if (Initialized()) {
            return true;
        }

        //
        // Load engine module.
        //

        auto* const engine_module = SysLoadModule(ENGINE_LIB);

        if (engine_module == nullptr) {
            Error(silent, "Failed to locate engine module.\n");
            return false;
        }

        //
        // Get the engine interface factory.
        //

        const auto interface_factory = SysGetFactory(engine_module);

        if (interface_factory == nullptr) {
            Error(silent, "Failed to locate interface factory in engine module.\n");
            return false;
        }

        //
        // Get the ReHLDS API interface.
        //

        auto ret_code = CreateInterfaceStatus::Failed;
        auto* const interface_base = interface_factory(VREHLDS_HLDS_API_VERSION, &ret_code);

        if (ret_code != CreateInterfaceStatus::Ok || interface_base == nullptr) {
            Error(silent, "Failed to retrieve \"%s\" interface from engine module; return code %d.\n",
                  VREHLDS_HLDS_API_VERSION, static_cast<int>(ret_code));

            return false;
        }

        rehlds_api = reinterpret_cast<IReHldsApi*>(interface_base);

        //
        // Check the ReHLDS version.
        //

        const auto major_version = MajorVersion();
        const auto minor_version = MinorVersion();

        if (major_version != REHLDS_API_VERSION_MAJOR) {
            Error(silent, "ReHLDS API major version mismatch; expected %d, real %d.",
                  REHLDS_API_VERSION_MAJOR, major_version);

            if (major_version < REHLDS_API_VERSION_MAJOR) {
                Message(silent, "Please update the ReHLDS up to a major version API >= %d.\n",
                        REHLDS_API_VERSION_MAJOR);
            }
            else {
                Message(silent, "Please update the %s up to a major version API >= %d.\n",
                        MODULE_NAME, REHLDS_API_VERSION_MAJOR);
            }

            return false;
        }

        if (minor_version < REHLDS_API_VERSION_MINOR) {
            Error(silent, "ReHLDS API minor version mismatch; expected %d, real %d.",
                  REHLDS_API_VERSION_MINOR, minor_version);

            Message(silent, "Please update the ReHLDS up to a minor version API >= %d.\n",
                    REHLDS_API_VERSION_MINOR);

            return false;
        }

        //
        // RehldsApi assignment.
        //

        rehlds_funcs = rehlds_api->GetFuncs();
        assert(rehlds_funcs != nullptr);

        rehlds_hook_chains = rehlds_api->GetHookChains();
        assert(rehlds_hook_chains != nullptr);

        rehlds_server_static = rehlds_api->GetServerStatic();
        assert(rehlds_server_static != nullptr);

        rehlds_server_data = rehlds_api->GetServerData();
        assert(rehlds_server_data != nullptr);

        rehlds_flight_recorder = rehlds_api->GetFlightRecorder();
        assert(rehlds_flight_recorder != nullptr);

        return Initialized();
    }
}
#endif
