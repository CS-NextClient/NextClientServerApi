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

#pragma once

#ifdef HAS_CSSDK_LIB
#include <cssdk/public/rehlds.h>
#include <cassert>

namespace core::rehlds_api
{
    namespace detail
    {
        inline const cssdk::ReHldsFuncs* rehlds_funcs{};
        inline cssdk::IReHldsHookChains* rehlds_hook_chains{};
        inline cssdk::IReHldsServerData* rehlds_server_data{};
        inline cssdk::IReHldsServerStatic* rehlds_server_static{};
        inline cssdk::IReHldsFlightRecorder* rehlds_flight_recorder{};
        inline cssdk::IReHldsApi* rehlds_api{};
    }

    /**
     * @brief Initializes the ReHLDS API. Returns true on success or false on failure.
    */
    bool Init(bool silent = false);

    /**
     * @brief Returns \c true if the ReHLDS API was successfully initialized, otherwise \c false.
    */
    [[nodiscard]] inline bool Initialized()
    {
        return detail::rehlds_funcs && detail::rehlds_hook_chains && detail::rehlds_server_data &&
            detail::rehlds_server_static && detail::rehlds_flight_recorder && detail::rehlds_api;
    }

    /**
     * @brief Returns the major version number of ReHLDS API.
    */
    [[nodiscard]] inline int MajorVersion()
    {
        assert(detail::rehlds_api != nullptr);
        return detail::rehlds_api->GetMajorVersion();
    }

    /**
     * @brief Returns the minor version number of ReHLDS API.
    */
    [[nodiscard]] inline int MinorVersion()
    {
        assert(detail::rehlds_api != nullptr);
        return detail::rehlds_api->GetMinorVersion();
    }

    /**
     * @brief Returns a pointer to a \c ReHldsFuncs structure provided by the ReHLDS API.
    */
    [[nodiscard]] inline const cssdk::ReHldsFuncs* Funcs()
    {
        assert(detail::rehlds_funcs != nullptr);
        return detail::rehlds_funcs;
    }

    /**
     * @brief Returns a pointer to a \c RehldsHookChains class provided by the ReHLDS API.
    */
    [[nodiscard]] inline cssdk::IReHldsHookChains* HookChains()
    {
        assert(detail::rehlds_hook_chains != nullptr);
        return detail::rehlds_hook_chains;
    }

    /**
     * @brief Returns a pointer to a \c RehldsServerStatic class provided by the ReHLDS API.
    */
    [[nodiscard]] inline cssdk::IReHldsServerStatic* ServerStatic()
    {
        assert(detail::rehlds_server_static != nullptr);
        return detail::rehlds_server_static;
    }

    /**
     * @brief Returns a pointer to a \c RehldsServerData</c> class provided by the ReHLDS API.
    */
    [[nodiscard]] inline cssdk::IReHldsServerData* ServerData()
    {
        assert(detail::rehlds_server_data != nullptr);
        return detail::rehlds_server_data;
    }

    /**
     * @brief Returns a pointer to a \c RehldsFlightRecorder class provided by the ReHLDS API.
    */
    [[nodiscard]] inline cssdk::IReHldsFlightRecorder* FlightRecorder()
    {
        assert(detail::rehlds_flight_recorder != nullptr);
        return detail::rehlds_flight_recorder;
    }
}
#endif
