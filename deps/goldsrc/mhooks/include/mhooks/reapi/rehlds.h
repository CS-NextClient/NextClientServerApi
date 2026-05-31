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

#if defined(HAS_CSSDK_LIB) && defined(HAS_CORE_LIB)
#include <core/delegate.h>
#include <core/rehlds_api.h>
#include <mhooks/common/mhook.h>
#include <mhooks/reapi/reapi_mhookchain.h>

// GetEntityInit
using ReHldsGetEntityInitMChain = mhooks::ReApiMHookChain<cssdk::ReHookGetEntityInit, cssdk::EntityInitFunction(const char*)>;
using ReHldsGetEntityInitMCallback = core::Delegate<cssdk::EntityInitFunction(const ReHldsGetEntityInitMChain& chain, const char* classname)>;

// ClientConnected
using ReHldsClientConnectedMChain = mhooks::ReApiMHookChain<cssdk::ReHookClientConnected, void(cssdk::IGameClient*)>;
using ReHldsClientConnectedMCallback = core::Delegate<void(const ReHldsClientConnectedMChain& chain, cssdk::IGameClient* client)>;

// SV_ActivateServer
using ReHldsActivateServerMChain = mhooks::ReApiMHookChain<cssdk::ReHookSvActivateServer, void(cssdk::qboolean)>;
using ReHldsActivateServerMCallback = core::Delegate<void(const ReHldsActivateServerMChain& chain, cssdk::qboolean run_physics)>;

// SV_ConnectClient
using ReHldsConnectClientMChain = mhooks::ReApiMHookChain<cssdk::ReHookSvConnectClient, void()>;
using ReHldsConnectClientMCallback = core::Delegate<void(const ReHldsConnectClientMChain& chain)>;

// SV_DropClient
using ReHldsDropClientMChain = mhooks::ReApiMHookChain<cssdk::ReHookSvDropClient, void(cssdk::IGameClient*, bool, const char*)>;
using ReHldsDropClientMCallback = core::Delegate<void(const ReHldsDropClientMChain& chain, cssdk::IGameClient* client, bool crash, const char* reason)>;

// SV_Frame
using ReHldsFrameMChain = mhooks::ReApiMHookChain<cssdk::ReHookSvFrame, void()>;
using ReHldsFrameMCallback = core::Delegate<void(const ReHldsFrameMChain& chain)>;

// SV_StartSound
using ReHldsStartSoundMChain = mhooks::ReApiMHookChain<cssdk::ReHookSvStartSound, void(int, cssdk::Edict*, int, const char*, int, float, int, int)>;
using ReHldsStartSoundMCallback = core::Delegate<void(const ReHldsStartSoundMChain& chain, int recipients, cssdk::Edict* entity, int channel, const char* sample, int volume, float attenuation, int flags, int pitch)>;

// SV_EmitSound2
using ReHldsEmitSound2MChain = mhooks::ReApiMHookChain<cssdk::ReHookSvEmitSound2, bool(cssdk::Edict*, cssdk::IGameClient*, int, const char*, float, float, int, int, int, const float*)>;
using ReHldsEmitSound2MCallback = core::Delegate<bool(const ReHldsEmitSound2MChain& chain, cssdk::Edict* entity, cssdk::IGameClient* receiver, int channel, const char* sample, float volume, float attenuation, int flags, int pitch, int emit_flags, const float* origin)>;

// SV_WriteFullClientUpdate
using ReHldsWriteFullClientUpdateMChain = mhooks::ReApiMHookChain<cssdk::ReHookSvWriteFullClientUpdate, void(cssdk::IGameClient*, char*, std::size_t, cssdk::SizeBuf*, cssdk::IGameClient*)>;
using ReHldsWriteFullClientUpdateMCallback = core::Delegate<void(const ReHldsWriteFullClientUpdateMChain& chain, cssdk::IGameClient* client, char* info, std::size_t max_len, cssdk::SizeBuf* info_buffer, cssdk::IGameClient* receiver)>;

// SV_Spawn_f
using ReHldsSpawnMChain = mhooks::ReApiMHookChain<cssdk::ReHookSvSpawnF, void()>;
using ReHldsSpawnMCallback = core::Delegate<void(const ReHldsSpawnMChain& chain)>;

// SV_CreatePacketEntities
using ReHldsCreatePacketEntitiesMChain = mhooks::ReApiMHookChain<cssdk::ReHookSvCreatePacketEntities, int(cssdk::SvDelta, cssdk::IGameClient*, cssdk::PacketEntities*, cssdk::SizeBuf*)>;
using ReHldsCreatePacketEntitiesMCallback = core::Delegate<int(const ReHldsCreatePacketEntitiesMChain& chain, cssdk::SvDelta type, cssdk::IGameClient* client, cssdk::PacketEntities* to, cssdk::SizeBuf* message)>;

// Steam_NotifyClientConnect
using ReHldsSteamNotifyClientConnectMChain = mhooks::ReApiMHookChain<cssdk::ReHookSteamNotifyClientConnect, cssdk::qboolean(cssdk::IGameClient*, const void*, unsigned int)>;
using ReHldsSteamNotifyClientConnectMCallback = core::Delegate<cssdk::qboolean(const ReHldsSteamNotifyClientConnectMChain& chain, cssdk::IGameClient* client, const void* auth_blob, unsigned int blob_size)>;

// Steam_NotifyBotConnect
using ReHldsSteamNotifyBotConnectMChain = mhooks::ReApiMHookChain<cssdk::ReHookSteamNotifyBotConnect, cssdk::qboolean(cssdk::IGameClient*)>;
using ReHldsSteamNotifyBotConnectMCallback = core::Delegate<cssdk::qboolean(const ReHldsSteamNotifyBotConnectMChain& chain, cssdk::IGameClient* client)>;

// Steam_NotifyClientDisconnect
using ReHldsSteamNotifyClientDisconnectMChain = mhooks::ReApiMHookChain<cssdk::ReHookSteamNotifyClientDisconnect, void(cssdk::IGameClient*)>;
using ReHldsSteamNotifyClientDisconnectMCallback = core::Delegate<void(const ReHldsSteamNotifyClientDisconnectMChain& chain, cssdk::IGameClient* client)>;

// Mod_LoadBrushModel
using ReHldsLoadBrushModelMChain = mhooks::ReApiMHookChain<cssdk::ReHookModLoadBrushModel, void(cssdk::Model*, void*)>;
using ReHldsLoadBrushModelMCallback = core::Delegate<void(const ReHldsLoadBrushModelMChain& chain, cssdk::Model* model, void* buffer)>;

// Mod_LoadStudioModel
using ReHldsLoadStudioModelMChain = mhooks::ReApiMHookChain<cssdk::ReHookModLoadStudioModel, void(cssdk::Model*, void*)>;
using ReHldsLoadStudioModelMCallback = core::Delegate<void(const ReHldsLoadStudioModelMChain& chain, cssdk::Model* model, void* buffer)>;

// PF_BuildSoundMsg_I
using ReHldsBuildSoundMsgMChain = mhooks::ReApiMHookChain<cssdk::ReHookPfBuildSoundMsgI, void(cssdk::Edict*, int, const char*, float, float, int, int, int, int, const float*, cssdk::Edict*)>;
using ReHldsBuildSoundMsgMCallback = core::Delegate<void(const ReHldsBuildSoundMsgMChain& chain, cssdk::Edict* entity, int channel, const char* sample, float volume, float attenuation, int flags, int pitch, int msg_dest, int msg_type, const float* origin, cssdk::Edict* client)>;

// Cvar_DirectSet
using ReHldsCvarDirectSetMChain = mhooks::ReApiMHookChain<cssdk::ReHookCvarDirectSet, void(cssdk::CVar*, const char*)>;
using ReHldsCvarDirectSetMCallback = core::Delegate<void(const ReHldsCvarDirectSetMChain& chain, cssdk::CVar* cvar, const char* value)>;

namespace mhooks
{
    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsGetEntityInit(
        ReHldsGetEntityInitMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsClientConnected(
        ReHldsClientConnectedMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsActivateServer(
        ReHldsActivateServerMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsConnectClient(
        ReHldsConnectClientMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsDropClient(
        ReHldsDropClientMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsFrame(
        ReHldsFrameMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsStartSound(
        ReHldsStartSoundMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsEmitSound2(
        ReHldsEmitSound2MCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsWriteFullClientUpdate(
        ReHldsWriteFullClientUpdateMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsSpawn(
        ReHldsSpawnMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsCreatePacketEntities(
        ReHldsCreatePacketEntitiesMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsSteamNotifyClientConnect(
        ReHldsSteamNotifyClientConnectMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsSteamNotifyBotConnect(
        ReHldsSteamNotifyBotConnectMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsSteamNotifyClientDisconnect(
        ReHldsSteamNotifyClientDisconnectMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsLoadBrushModel(
        ReHldsLoadBrushModelMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsLoadStudioModel(
        ReHldsLoadStudioModelMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsBuildSoundMsg(
        ReHldsBuildSoundMsgMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookReHldsCvarDirectSet(
        ReHldsCvarDirectSetMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
}
#endif
