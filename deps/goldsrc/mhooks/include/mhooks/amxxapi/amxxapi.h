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

#ifdef HAS_AMXX_LIB
#include <amxx/api.h>
#include <amxx/config.h>
#include <core/delegate.h>
#include <mhooks/common/mhook.h>
#include <mhooks/amxxapi/amxxapi_mhookchain.h>

#if !defined(USE_METAMOD) && !defined(AMXX_DETACH)
#error AMXX_DETACH function required. Please check your CMakeLists.txt
#endif

// AMXX_CheckGame
using AmxxCheckGameMChain = mhooks::AmxxApiMHookChain<AmxxGameStatus(const char*)>;
using AmxxCheckGameMCallback = core::Delegate<AmxxGameStatus(const AmxxCheckGameMChain& chain, const char* game)>;

// AMXX_Attach
using AmxxAttachMChain = mhooks::AmxxApiMHookChain<AmxxStatus()>;
using AmxxAttachMCallback = core::Delegate<AmxxStatus(const AmxxAttachMChain& chain)>;

// AMXX_PluginsLoaded
using AmxxPluginsLoadedMChain = mhooks::AmxxApiMHookChain<void()>;
using AmxxPluginsLoadedMCallback = core::Delegate<void(const AmxxPluginsLoadedMChain& chain)>;

// AMXX_PluginsUnloading
using AmxxPluginsUnloadingMChain = mhooks::AmxxApiMHookChain<void()>;
using AmxxPluginsUnloadingMCallback = core::Delegate<void(const AmxxPluginsUnloadingMChain& chain)>;

// AMXX_PluginsUnloaded
using AmxxPluginsUnloadedMChain = mhooks::AmxxApiMHookChain<void()>;
using AmxxPluginsUnloadedMCallback = core::Delegate<void(const AmxxPluginsUnloadedMChain& chain)>;

// AMXX_Detach
using AmxxDetachMChain = mhooks::AmxxApiMHookChain<void()>;
using AmxxDetachMCallback = core::Delegate<void(const AmxxDetachMChain& chain)>;

// ClientAuthorized
using AmxxClientAuthorizedMChain = mhooks::AmxxApiMHookChain<void(int, const char*)>;
using AmxxClientAuthorizedMCallback = core::Delegate<void(const AmxxClientAuthorizedMChain& chain, int index, const char* auth)>;

namespace mhooks
{
#ifdef AMXX_CHECK_GAME
    /**
     * @brief Hooks the \c AMXX_CheckGame function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookAmxxCheckGame(
        AmxxCheckGameMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif

#ifdef AMXX_ATTACH
    /**
     * @brief Hooks the \c AMXX_Attach function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookAmxxAttach(
        AmxxAttachMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif

#ifdef AMXX_PLUGINS_LOADED
    /**
     * @brief Hooks the \c AMXX_PluginsLoaded function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookAmxxPluginsLoaded(
        AmxxPluginsLoadedMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif

#ifdef AMXX_PLUGINS_UNLOADING
    /**
     * @brief Hooks the \c AMXX_PluginsUnloading function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookAmxxPluginsUnloading(
        AmxxPluginsUnloadingMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif

#ifdef AMXX_PLUGINS_UNLOADED
    /**
     * @brief Hooks the \c AMXX_PluginsUnloaded function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookAmxxPluginsUnloaded(
        AmxxPluginsUnloadedMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif

#ifdef AMXX_DETACH
    /**
     * @brief Hooks the \c AMXX_Detach function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookAmxxDetach(
        AmxxDetachMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif

    /**
     * @brief Called when the client gets a valid SteamID.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookAmxxClientAuthorized(
        AmxxClientAuthorizedMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
}
#endif
