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

#if defined(HAS_CSSDK_LIB) && defined(HAS_CORE_LIB)
#include "createhook.h"
#include <mhooks/reapi/rehlds.h>
#include <cassert>

using namespace core;
using namespace cssdk;
using namespace rehlds_api;
using namespace mhooks::detail;

namespace mhooks
{
    MHook* MHookReHldsGetEntityInit(const ReHldsGetEntityInitMCallback callback,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsGetEntityInit;
        return CreateHook<ReHldsGetEntityInit>(HookChains()->GetEntityInit(), callback, priority, enable);
    }

    MHook* MHookReHldsClientConnected(const ReHldsClientConnectedMCallback callback,
                                      const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsClientConnected;
        return CreateHook<ReHldsClientConnected>(HookChains()->ClientConnected(), callback, priority, enable);
    }

    MHook* MHookReHldsActivateServer(const ReHldsActivateServerMCallback callback,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsActivateServer;
        return CreateHook<ReHldsActivateServer>(HookChains()->SvActivateServer(), callback, priority, enable);
    }

    MHook* MHookReHldsConnectClient(const ReHldsConnectClientMCallback callback,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsConnectClient;
        return CreateHook<ReHldsConnectClient>(HookChains()->SvConnectClient(), callback, priority, enable);
    }

    MHook* MHookReHldsDropClient(const ReHldsDropClientMCallback callback,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsDropClient;
        return CreateHook<ReHldsDropClient>(HookChains()->SvDropClient(), callback, priority, enable);
    }

    MHook* MHookReHldsFrame(const ReHldsFrameMCallback callback,
                            const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsFrame;
        return CreateHook<ReHldsFrame>(HookChains()->SvFrame(), callback, priority, enable);
    }

    MHook* MHookReHldsStartSound(const ReHldsStartSoundMCallback callback,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsStartSound;
        return CreateHook<ReHldsStartSound>(HookChains()->SvStartSound(), callback, priority, enable);
    }

    MHook* MHookReHldsEmitSound2(const ReHldsEmitSound2MCallback callback,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsEmitSound2;
        return CreateHook<ReHldsEmitSound2>(HookChains()->SvEmitSound2(), callback, priority, enable);
    }

    MHook* MHookReHldsWriteFullClientUpdate(const ReHldsWriteFullClientUpdateMCallback callback,
                                            const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsWriteFullClientUpdate;
        return CreateHook<ReHldsWriteFullClientUpdate>(HookChains()->SvWriteFullClientUpdate(),
                                                       callback, priority, enable);
    }

    MHook* MHookReHldsSpawn(const ReHldsSpawnMCallback callback, const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsSpawn;
        return CreateHook<ReHldsSpawn>(HookChains()->SvSpawnF(), callback, priority, enable);
    }

    MHook* MHookReHldsCreatePacketEntities(const ReHldsCreatePacketEntitiesMCallback callback,
                                           const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsCreatePacketEntities;
        return CreateHook<ReHldsCreatePacketEntities>(HookChains()->SvCreatePacketEntities(), callback, priority, enable);
    }

    MHook* MHookReHldsSteamNotifyClientConnect(const ReHldsSteamNotifyClientConnectMCallback callback,
                                               const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsSteamNotifyClientConnect;
        return CreateHook<ReHldsSteamNotifyClientConnect>(HookChains()->SteamNotifyClientConnect(),
                                                          callback, priority, enable);
    }

    MHook* MHookReHldsSteamNotifyBotConnect(const ReHldsSteamNotifyBotConnectMCallback callback,
                                            const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsSteamNotifyBotConnect;
        return CreateHook<ReHldsSteamNotifyBotConnect>(HookChains()->SteamNotifyBotConnect(),
                                                       callback, priority, enable);
    }

    MHook* MHookReHldsSteamNotifyClientDisconnect(const ReHldsSteamNotifyClientDisconnectMCallback callback,
                                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsSteamNotifyClientDisconnect;
        return CreateHook<ReHldsSteamNotifyClientDisconnect>(HookChains()->SteamNotifyClientDisconnect(),
                                                             callback, priority, enable);
    }

    MHook* MHookReHldsLoadBrushModel(const ReHldsLoadBrushModelMCallback callback,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsLoadBrushModel;
        return CreateHook<ReHldsLoadBrushModel>(HookChains()->ModLoadBrushModel(), callback, priority, enable);
    }

    MHook* MHookReHldsLoadStudioModel(const ReHldsLoadStudioModelMCallback callback,
                                      const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsLoadStudioModel;
        return CreateHook<ReHldsLoadStudioModel>(HookChains()->ModLoadStudioModel(), callback, priority, enable);
    }

    MHook* MHookReHldsBuildSoundMsg(const ReHldsBuildSoundMsgMCallback callback,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsBuildSoundMsg;
        return CreateHook<ReHldsBuildSoundMsg>(HookChains()->PfBuildSoundMsgI(), callback, priority, enable);
    }

    MHook* MHookReHldsCvarDirectSet(const ReHldsCvarDirectSetMCallback callback,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReHldsCvarDirectSet;
        return CreateHook<ReHldsCvarDirectSet>(HookChains()->CvarDirectSet(), callback, priority, enable);
    }
}
#endif
