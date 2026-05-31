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

#ifdef HAS_METAMOD_LIB
#include "createhook.h"
#include <mhooks/metamod/gamedll.h>

using namespace cssdk;
using namespace metamod::gamedll;
using namespace mhooks::detail;

namespace mhooks
{
    MHook* MHookGameDllInit(const GameDllInitMCallback callback, const bool post,
                            const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllGameInit;
        return CreateHook<GameDllGameInit>(HookGameInit, callback, priority, post, enable);
    }

    MHook* MHookGameDllDispatchSpawn(const GameDllDispatchSpawnMCallback callback, const bool post,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllDispatchSpawn;
        return CreateHook<GameDllDispatchSpawn>(HookSpawn, callback, priority, post, enable);
    }

    MHook* MHookGameDllServerActivate(const GameDllServerActivateMCallback callback, const bool post,
                                      const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllServerActivate;
        return CreateHook<GameDllServerActivate>(HookServerActivate, callback, priority, post, enable);
    }

    MHook* MHookGameDllServerDeactivate(const GameDllServerDeactivateMCallback callback, const bool post,
                                        const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllServerDeactivate;
        return CreateHook<GameDllServerDeactivate>(HookServerDeactivate, callback, priority, post, enable);
    }

    MHook* MHookGameDllClientConnect(const GameDllClientConnectMCallback callback, const bool post,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllClientConnect;
        return CreateHook<GameDllClientConnect>(HookClientConnect, callback, priority, post, enable);
    }

    MHook* MHookGameDllClientKill(const GameDllClientKillMCallback callback, const bool post,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllClientKill;
        return CreateHook<GameDllClientKill>(HookClientKill, callback, priority, post, enable);
    }

    MHook* MHookGameDllClientUserInfoChanged(const GameDllClientUserInfoChangedMCallback callback, const bool post,
                                             const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllClientUserInfoChanged;
        return CreateHook<GameDllClientUserInfoChanged>(HookClientUserInfoChanged, callback, priority, post, enable);
    }

    MHook* MHookGameDllClientCommand(const GameDllClientCommandMCallback callback, const bool post,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllClientCommand;
        return CreateHook<GameDllClientCommand>(HookClientCommand, callback, priority, post, enable);
    }

    MHook* MHookGameDllStartFrame(const GameDllStartFrameMCallback callback, const bool post,
                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllStartFrame;
        return CreateHook<GameDllStartFrame>(HookStartFrame, callback, priority, post, enable);
    }

    MHook* MHookGameDllCmdStart(const GameDllCmdStartMCallback callback, const bool post,
                                const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllCmdStart;
        return CreateHook<GameDllCmdStart>(HookCmdStart, callback, priority, post, enable);
    }

    MHook* MHookGameDllCmdEnd(const GameDllCmdEndMCallback callback, const bool post,
                              const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllCmdEnd;
        return CreateHook<GameDllCmdEnd>(HookCmdEnd, callback, priority, post, enable);
    }

    MHook* MHookGameDllPlayerPreThink(const GameDllPlayerPreThinkMCallback callback, const bool post,
                                      const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllPlayerPreThink;
        return CreateHook<GameDllPlayerPreThink>(HookPlayerPreThink, callback, priority, post, enable);
    }

    MHook* MHookGameDllPlayerPostThink(const GameDllPlayerPostThinkMCallback callback, const bool post,
                                       const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllPlayerPostThink;
        return CreateHook<GameDllPlayerPostThink>(HookPlayerPostThink, callback, priority, post, enable);
    }

    MHook* MHookGameDllAddToFullPack(const GameDllAddToFullPackMCallback callback, const bool post,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllAddToFullPack;
        return CreateHook<GameDllAddToFullPack>(HookAddToFullPack, callback, priority, post, enable);
    }

    MHook* MHookGameDllClientPutInServer(const GameDllClientPutInServerMCallback callback, const bool post,
                                         const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllClientPutInServer;
        return CreateHook<GameDllClientPutInServer>(HookClientPutInServer, callback, priority, post, enable);
    }

    MHook* MHookGameDllUpdateClientData(const GameDllUpdateClientDataMCallback callback, const bool post,
                                        const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllUpdateClientData;
        return CreateHook<GameDllUpdateClientData>(HookUpdateClientData, callback, priority, post, enable);
    }

    MHook* MHookGameDllGetWeaponData(const GameDllGetWeaponDataMCallback callback, const bool post,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct GameDllGetWeaponData;
        return CreateHook<GameDllGetWeaponData>(HookGetWeaponData, callback, priority, post, enable);
    }
}
#endif
