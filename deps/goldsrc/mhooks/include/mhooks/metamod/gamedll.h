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

#ifdef HAS_METAMOD_LIB
#include <core/delegate.h>
#include <metamod/gamedll_hooks.h>
#include <mhooks/common/mhook.h>
#include <mhooks/metamod/metamod_mhookchain.h>

// GameInit
using GameDllInitMChain = mhooks::MetamodMHookChain<void()>;
using GameDllInitMCallback = core::Delegate<void(const GameDllInitMChain& chain)>;

// DispatchSpawn
using GameDllDispatchSpawnMChain = mhooks::MetamodMHookChain<int(cssdk::Edict*)>;
using GameDllDispatchSpawnMCallback = core::Delegate<int(const GameDllDispatchSpawnMChain& chain, cssdk::Edict* entity)>;

// ServerActivate
using GameDllServerActivateMChain = mhooks::MetamodMHookChain<void(cssdk::Edict*, int, int)>;
using GameDllServerActivateMCallback = core::Delegate<void(const GameDllServerActivateMChain& chain, cssdk::Edict* edict_list, int edict_count, int client_max)>;

// ServerDeactivate
using GameDllServerDeactivateMChain = mhooks::MetamodMHookChain<void()>;
using GameDllServerDeactivateMCallback = core::Delegate<void(const GameDllServerDeactivateMChain& chain)>;

// ClientConnect
using GameDllClientConnectMChain = mhooks::MetamodMHookChain<cssdk::qboolean(cssdk::Edict*, const char*, const char*, char*)>;
using GameDllClientConnectMCallback = core::Delegate<cssdk::qboolean(const GameDllClientConnectMChain& chain, cssdk::Edict* client, const char* name, const char* address, char* reject_reason)>;

// ClientKill
using GameDllClientKillMChain = mhooks::MetamodMHookChain<void(cssdk::Edict*)>;
using GameDllClientKillMCallback = core::Delegate<void(const GameDllClientKillMChain& chain, cssdk::Edict* client)>;

// ClientUserInfoChanged
using GameDllClientUserInfoChangedMChain = mhooks::MetamodMHookChain<void(cssdk::Edict*, char*)>;
using GameDllClientUserInfoChangedMCallback = core::Delegate<void(const GameDllClientUserInfoChangedMChain& chain, cssdk::Edict* client, char* info_buffer)>;

// ClientCommand
using GameDllClientCommandMChain = mhooks::MetamodMHookChain<void(cssdk::Edict*)>;
using GameDllClientCommandMCallback = core::Delegate<void(const GameDllClientCommandMChain& chain, cssdk::Edict* client)>;

// StartFrame
using GameDllStartFrameMChain = mhooks::MetamodMHookChain<void()>;
using GameDllStartFrameMCallback = core::Delegate<void(const GameDllStartFrameMChain& chain)>;

// CmdStart
using GameDllCmdStartMChain = mhooks::MetamodMHookChain<void(const cssdk::Edict*, const cssdk::UserCmd*, unsigned int)>;
using GameDllCmdStartMCallback = core::Delegate<void(const GameDllCmdStartMChain& chain, const cssdk::Edict* client, const cssdk::UserCmd* cmd, unsigned int random_seed)>;

// CmdEnd
using GameDllCmdEndMChain = mhooks::MetamodMHookChain<void(const cssdk::Edict*)>;
using GameDllCmdEndMCallback = core::Delegate<void(const GameDllCmdEndMChain& chain, const cssdk::Edict* client)>;

// PlayerPreThink
using GameDllPlayerPreThinkMChain = mhooks::MetamodMHookChain<void(cssdk::Edict*)>;
using GameDllPlayerPreThinkMCallback = core::Delegate<void(const GameDllPlayerPreThinkMChain& chain, cssdk::Edict* client)>;

// PlayerPostThink
using GameDllPlayerPostThinkMChain = mhooks::MetamodMHookChain<void(cssdk::Edict*)>;
using GameDllPlayerPostThinkMCallback = core::Delegate<void(const GameDllPlayerPostThinkMChain& chain, cssdk::Edict* client)>;

// AddToFullPack
using GameDllAddToFullPackMChain = mhooks::MetamodMHookChain<cssdk::qboolean(cssdk::EntityState*, int, cssdk::Edict*, cssdk::Edict*, int, cssdk::qboolean, unsigned char*)>;
using GameDllAddToFullPackMCallback = core::Delegate<cssdk::qboolean(const GameDllAddToFullPackMChain& chain, cssdk::EntityState* state, int entity_index, cssdk::Edict* entity, cssdk::Edict* host, int host_flags, cssdk::qboolean player, unsigned char* set)>;

// ClientPutInServer
using GameDllClientPutInServerMChain = mhooks::MetamodMHookChain<void(cssdk::Edict*)>;
using GameDllClientPutInServerMCallback = core::Delegate<void(const GameDllClientPutInServerMChain& chain, cssdk::Edict* client)>;

// UpdateClientData
using GameDllUpdateClientDataMChain = mhooks::MetamodMHookChain<void(const cssdk::Edict*, cssdk::qboolean, cssdk::ClientData*)>;
using GameDllUpdateClientDataMCallback = core::Delegate<void(const GameDllUpdateClientDataMChain& chain, const cssdk::Edict* client, cssdk::qboolean send_weapons, cssdk::ClientData* data)>;

// GetWeaponData
using GameDllGetWeaponDataMChain = mhooks::MetamodMHookChain<cssdk::qboolean(cssdk::Edict*, cssdk::WeaponData*)>;
using GameDllGetWeaponDataMCallback = core::Delegate<cssdk::qboolean(const GameDllGetWeaponDataMChain& chain, cssdk::Edict* client, cssdk::WeaponData* data)>;

namespace mhooks
{
    /**
     * @brief Called when the game loads this DLL.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllInit(
        GameDllInitMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine to spawn an entity.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllDispatchSpawn(
        GameDllDispatchSpawnMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called when the engine has finished spawning the map.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllServerActivate(
        GameDllServerActivateMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called when the map has ended. This happens before the entities are destroyed.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllServerDeactivate(
        GameDllServerDeactivateMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine when a client connects. Returning \c false rejects the client's connection.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllClientConnect(
        GameDllClientConnectMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * TODO: @brief
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllClientKill(
        GameDllClientKillMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine whenever the client's user info string changes.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllClientUserInfoChanged(
        GameDllClientUserInfoChangedMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine when it has received a command from the given client.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllClientCommand(
        GameDllClientCommandMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called at the start of a server game frame.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllStartFrame(
        GameDllStartFrameMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine when a user command has been received and is about to begin processing.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllCmdStart(
        GameDllCmdStartMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine when a user command has finished processing.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllCmdEnd(
        GameDllCmdEndMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine before it runs physics.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllPlayerPreThink(
        GameDllPlayerPreThinkMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine after it runs physics.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllPlayerPostThink(
        GameDllPlayerPostThinkMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine to determine whether the given entity should be added to the given
     * client's list of visible entities.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllAddToFullPack(
        GameDllAddToFullPackMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Called by the engine when the client has finished connecting.
     * This is where the player should be spawned and put into the world, or given a spectator position to view from.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllClientPutInServer(
        GameDllClientPutInServerMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief Updates the given client's data.
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllUpdateClientData(
        GameDllUpdateClientDataMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * TODO: @brief
     *
     * @param callback Hook callback function.
     * @param post Is this a post hook?
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookGameDllGetWeaponData(
        GameDllGetWeaponDataMCallback callback, bool post,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
}
#endif
