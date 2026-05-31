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
#include <cssdk/public/regamedll.h>
#include <cassert>

namespace core::regamedll_api
{
    namespace detail
    {
        inline const cssdk::RegamedllFuncs* regamedll_funcs{};
        inline cssdk::IReGameDllHookChains* regamedll_hook_chains{};
        inline cssdk::IReGameDllApi* regamedll_api{};
    }

    /**
     * @brief Initializes the ReGameDLL API. Returns true on success or false on failure.
    */
    bool Init(bool silent = false);

    /**
     * @brief Returns \c true if the ReGameDll API was successfully initialized, otherwise \c false.
    */
    [[nodiscard]] inline bool Initialized()
    {
        return detail::regamedll_funcs && detail::regamedll_hook_chains && detail::regamedll_api;
    }

    /**
     * @brief Returns the major version number of ReGameDLL API.
    */
    [[nodiscard]] inline int MajorVersion()
    {
        assert(detail::regamedll_api != nullptr);
        return detail::regamedll_api->GetMajorVersion();
    }

    /**
     * @brief Returns the minor version number of ReGameDLL API.
    */
    [[nodiscard]] inline int MinorVersion()
    {
        assert(detail::regamedll_api != nullptr);
        return detail::regamedll_api->GetMinorVersion();
    }

    /**
     * @brief Returns a pointer to a \c RegamedllFuncs structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline const cssdk::RegamedllFuncs* Funcs()
    {
        assert(detail::regamedll_funcs != nullptr);
        return detail::regamedll_funcs;
    }

    /**
     * @brief Returns a pointer to a \c RegamedllHookChains class provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::IReGameDllHookChains* HookChains()
    {
        assert(detail::regamedll_hook_chains != nullptr);
        return detail::regamedll_hook_chains;
    }

    /**
     * @brief Returns a pointer to a \c GameRules* class provided by the ReGameDLL API.
    */
    [[nodiscard]] inline auto* GameRules()
    {
        assert(detail::regamedll_api != nullptr);
        return detail::regamedll_api->GetGameRules();
    }

    /**
     * @brief Returns a pointer to a \c WeaponInfoStruct structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::WeaponInfoStruct* GetWeaponInfo(const cssdk::WeaponId weapon)
    {
        assert(detail::regamedll_api != nullptr);

        auto* const weapon_info = detail::regamedll_api->GetWeaponInfo(weapon);
        assert(weapon_info != nullptr);

        return weapon_info;
    }

    /**
     * @brief Returns a pointer to a \c WeaponInfoStruct structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::WeaponInfoStruct* GetWeaponInfo(const char* const weapon)
    {
        assert(detail::regamedll_api != nullptr);

        auto* const weapon_info = detail::regamedll_api->GetWeaponInfo(weapon);
        assert(weapon_info != nullptr);

        return weapon_info;
    }

    /**
     * @brief Returns a pointer to a \c PlayerMove structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::PlayerMove* GetPlayerMove()
    {
        assert(detail::regamedll_api != nullptr);

        auto* const player_move = detail::regamedll_api->GetPlayerMove();
        assert(player_move != nullptr);

        return player_move;
    }

    /**
     * @brief Returns a pointer to a \c WeaponSlotInfo structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::WeaponSlotInfo* GetWeaponSlot(const cssdk::WeaponId weapon)
    {
        assert(detail::regamedll_api != nullptr);

        auto* const weapon_slot = detail::regamedll_api->GetWeaponSlot(weapon);
        assert(weapon_slot != nullptr);

        return weapon_slot;
    }

    /**
     * @brief Returns a pointer to a \c WeaponSlotInfo structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::WeaponSlotInfo* GetWeaponSlot(const char* const weapon)
    {
        assert(detail::regamedll_api != nullptr);

        auto* const weapon_slot = detail::regamedll_api->GetWeaponSlot(weapon);
        assert(weapon_slot != nullptr);

        return weapon_slot;
    }

    /**
     * @brief Returns a pointer to a \c ItemInfo structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::ItemInfo* GetItemInfo(const cssdk::WeaponId weapon)
    {
        assert(detail::regamedll_api != nullptr);

        auto* const item_info = detail::regamedll_api->GetItemInfo(weapon);
        assert(item_info != nullptr);

        return item_info;
    }

    /**
     * @brief Returns a pointer to a \c AmmoInfo structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::AmmoInfo* GetAmmoInfo(const cssdk::AmmoType ammo)
    {
        assert(detail::regamedll_api != nullptr);

        auto* const ammo_info = detail::regamedll_api->GetAmmoInfo(ammo);
        assert(ammo_info != nullptr);

        return ammo_info;
    }

    /**
     * @brief Returns a pointer to a \c AmmoInfoStruct structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::AmmoInfoStruct* GetAmmoInfoEx(const cssdk::AmmoType ammo)
    {
        assert(detail::regamedll_api != nullptr);

        auto* const ammo_info = detail::regamedll_api->GetAmmoInfoEx(ammo);
        assert(ammo_info != nullptr);

        return ammo_info;
    }

    /**
     * @brief Returns a pointer to a \c AmmoInfoStruct structure provided by the ReGameDLL API.
    */
    [[nodiscard]] inline cssdk::AmmoInfoStruct* GetAmmoInfoEx(const char* const ammo)
    {
        assert(detail::regamedll_api != nullptr);

        auto* const ammo_info = detail::regamedll_api->GetAmmoInfoEx(ammo);
        assert(ammo_info != nullptr);

        return ammo_info;
    }
}
#endif
