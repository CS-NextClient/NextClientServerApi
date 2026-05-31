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
#include <mhooks/reapi/regamedll.h>
#include <cassert>

using namespace core;
using namespace cssdk;
using namespace regamedll_api;
using namespace mhooks::detail;

namespace mhooks
{
    MHook* MHookReGameShowMenu(const ReGameShowMenuMCallback callback,
                               const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameShowMenu;
        return CreateHook<ReGameShowMenu>(HookChains()->ShowMenu(), callback, priority, enable);
    }

    MHook* MHookReGameShowVguiMenu(const ReGameShowVguiMenuMCallback callback,
                                   const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameShowVguiMenu;
        return CreateHook<ReGameShowVguiMenu>(HookChains()->ShowVguiMenu(), callback, priority, enable);
    }

    MHook* MHookReGameHandleMenuChooseTeam(const ReGameHandleMenuChooseTeamMCallback callback,
                                           const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameHandleMenuChooseTeam;
        return CreateHook<ReGameHandleMenuChooseTeam>(HookChains()->HandleMenuChooseTeam(), callback, priority, enable);
    }

    MHook* MHookReGameHandleMenuChooseAppearance(const ReGameHandleMenuChooseAppearanceMCallback callback,
                                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameHandleMenuChooseAppearance;
        return CreateHook<ReGameHandleMenuChooseAppearance>(HookChains()->HandleMenuChooseAppearance(),
                                                            callback, priority, enable);
    }

    MHook* MHookReGameGetForceCamera(const ReGameGetForceCameraMCallback callback,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameGetForceCamera;
        return CreateHook<ReGameGetForceCamera>(HookChains()->GetForceCamera(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerBlind(const ReGamePlayerBlindMCallback callback,
                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerBlind;
        return CreateHook<ReGamePlayerBlind>(HookChains()->PlayerBlind(), callback, priority, enable);
    }

    MHook* MHookReGameRadiusFlashTraceLine(const ReGameRadiusFlashTraceLineMCallback callback,
                                           const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameRadiusFlashTraceLine;
        return CreateHook<ReGameRadiusFlashTraceLine>(HookChains()->RadiusFlashTraceLine(), callback, priority, enable);
    }

    MHook* MHookReGameInternalCommand(const ReGameInternalCommandMCallback callback,
                                      const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameInternalCommand;
        return CreateHook<ReGameInternalCommand>(HookChains()->InternalCommand(), callback, priority, enable);
    }

    MHook* MHookReGameRulesInstallGameRules(const ReGameRulesInstallGameRulesMCallback callback,
                                            const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameRulesInstallGameRules;
        return CreateHook<ReGameRulesInstallGameRules>(HookChains()->InstallGameRules(), callback, priority, enable);
    }

    MHook* MHookReGameRulesFreeGameRules(const ReGameRulesFreeGameRulesMCallback callback,
                                         const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameRulesFreeGameRules;
        return CreateHook<ReGameRulesFreeGameRules>(HookChains()->FreeGameRules(), callback, priority, enable);
    }

    MHook* MHookReGameRulesRoundFreezeEnd(const ReGameRulesRoundFreezeEndMCallback callback,
                                          const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameRulesRoundFreezeEnd;
        return CreateHook<ReGameRulesRoundFreezeEnd>(HookChains()->GameRulesOnRoundFreezeEnd(), callback, priority, enable);
    }

    MHook* MHookReGameRulesRoundEnd(const ReGameRulesRoundEndMCallback callback,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameRulesRoundEnd;
        return CreateHook<ReGameRulesRoundEnd>(HookChains()->RoundEnd(), callback, priority, enable);
    }

    MHook* MHookReGameMultiplayRestartRound(const ReGameMultiplayRestartRoundMCallback callback,
                                            const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameMultiplayRestartRound;
        return CreateHook<ReGameMultiplayRestartRound>(HookChains()->GameRulesRestartRound(), callback, priority, enable);
    }

    MHook* MHookReGameMultiplayBalanceTeams(const ReGameMultiplayBalanceTeamsMCallback callback,
                                            const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameMultiplayBalanceTeams;
        return CreateHook<ReGameMultiplayBalanceTeams>(HookChains()->GameRulesBalanceTeams(), callback, priority, enable);
    }

    MHook* MHookReGameMgrHelpCanPlayerHearPlayer(const ReGameMgrHelpCanPlayerHearPlayerMCallback callback,
                                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameMgrHelpCanPlayerHearPlayer;
        return CreateHook<ReGameMgrHelpCanPlayerHearPlayer>(HookChains()->GameRulesCanPlayerHearPlayer(), callback, priority, enable);
    }

    MHook* MHookReGameWeaponDefaultDeploy(const ReGameWeaponDefaultDeployMCallback callback,
                                          const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameWeaponDefaultDeploy;
        return CreateHook<ReGameWeaponDefaultDeploy>(HookChains()->PlayerBaseWeaponDefaultDeploy(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerSpawn(const ReGamePlayerSpawnMCallback callback,
                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerSpawn;
        return CreateHook<ReGamePlayerSpawn>(HookChains()->PlayerSpawn(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerPreThink(const ReGamePlayerPreThinkMCallback callback,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerPreThink;
        return CreateHook<ReGamePlayerPreThink>(HookChains()->PlayerPreThink(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerPostThink(const ReGamePlayerPostThinkMCallback callback,
                                      const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerPostThink;
        return CreateHook<ReGamePlayerPostThink>(HookChains()->PlayerPostThink(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerUpdateClientData(const ReGamePlayerUpdateClientDataMCallback callback,
                                             const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerUpdateClientData;
        return CreateHook<ReGamePlayerUpdateClientData>(HookChains()->PlayerUpdateClientData(),
                                                        callback, priority, enable);
    }

    MHook* MHookReGamePlayerTakeDamage(const ReGamePlayerTakeDamageMCallback callback,
                                       const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerTakeDamage;
        return CreateHook<ReGamePlayerTakeDamage>(HookChains()->PlayerTakeDamage(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerKilled(const ReGamePlayerKilledMCallback callback,
                                   const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerKilled;
        return CreateHook<ReGamePlayerKilled>(HookChains()->PlayerKilled(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerAddPlayerItem(const ReGamePlayerAddPlayerItemMCallback callback,
                                          const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerAddPlayerItem;
        return CreateHook<ReGamePlayerAddPlayerItem>(HookChains()->PlayerAddPlayerItem(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerDropPlayerItem(const ReGamePlayerDropPlayerItemMCallback callback,
                                          const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerDropPlayerItem;
        return CreateHook<ReGamePlayerDropPlayerItem>(HookChains()->PlayerDropPlayerItem(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerRemovePlayerItem(const ReGamePlayerRemovePlayerItemMCallback callback,
                                             const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerRemovePlayerItem;
        return CreateHook<ReGamePlayerRemovePlayerItem>(HookChains()->PlayerRemovePlayerItem(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerObserverIsValidTarget(const ReGamePlayerObserverIsValidTargetMCallback callback,
                                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerObserverIsValidTarget;
        return CreateHook<ReGamePlayerObserverIsValidTarget>(HookChains()->PlayerObserverIsValidTarget(),
                                                             callback, priority, enable);
    }

    MHook* MHookReGamePlayerStartObserver(const ReGamePlayerStartObserverMCallback callback,
                                          const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerStartObserver;
        return CreateHook<ReGamePlayerStartObserver>(HookChains()->PlayerStartObserver(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerGetIntoGame(const ReGamePlayerGetIntoGameMCallback callback,
                                        const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerGetIntoGame;
        return CreateHook<ReGamePlayerGetIntoGame>(HookChains()->PlayerGetIntoGame(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerMakeBomber(const ReGamePlayerMakeBomberMCallback callback,
                                       const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerMakeBomber;
        return CreateHook<ReGamePlayerMakeBomber>(HookChains()->PlayerMakeBomber(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerJump(const ReGamePlayerJumpMCallback callback,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerJump;
        return CreateHook<ReGamePlayerJump>(HookChains()->PlayerJump(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerResetMaxSpeed(const ReGamePlayerResetMaxSpeedMCallback callback,
                                          const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerResetMaxSpeed;
        return CreateHook<ReGamePlayerResetMaxSpeed>(HookChains()->PlayerResetMaxSpeed(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerSpawnEquip(const ReGamePlayerSpawnEquipMCallback callback,
                                       const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerSpawnEquip;
        return CreateHook<ReGamePlayerSpawnEquip>(HookChains()->PlayerOnSpawnEquip(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerGiveDefaultItems(const ReGamePlayerGiveDefaultItemsMCallback callback,
                                             const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerGiveDefaultItems;
        return CreateHook<ReGamePlayerGiveDefaultItems>(HookChains()->PlayerGiveDefaultItems(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerSetClientUserInfoName(const ReGamePlayerSetClientUserInfoNameMCallback callback,
                                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerSetClientUserInfoName;
        return CreateHook<ReGamePlayerSetClientUserInfoName>(HookChains()->PlayerSetClientUserInfoName(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerSetClientUserInfoModel(const ReGamePlayerSetClientUserInfoModelMCallback callback,
                                                   const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerSetClientUserInfoModel;
        return CreateHook<ReGamePlayerSetClientUserInfoModel>(HookChains()->PlayerSetClientUserInfoModel(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerThrowGrenade(const ReGamePlayerThrowGrenadeMCallback callback,
                                         const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerThrowGrenade;
        return CreateHook<ReGamePlayerThrowGrenade>(HookChains()->PlayerThrowGrenade(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerPain(const ReGamePlayerPainMCallback callback,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerPain;
        return CreateHook<ReGamePlayerPain>(HookChains()->PlayerPain(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerDeathSound(const ReGamePlayerDeathSoundMCallback callback,
                                       const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerDeathSound;
        return CreateHook<ReGamePlayerDeathSound>(HookChains()->PlayerDeathSound(), callback, priority, enable);
    }

    MHook* MHookReGamePlayerJoiningThink(const ReGamePlayerJoiningThinkMCallback callback,
                                         const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGamePlayerJoiningThink;
        return CreateHook<ReGamePlayerJoiningThink>(HookChains()->PlayerJoiningThink(), callback, priority, enable);
    }

    MHook* MHookReGameWeaponBoxSetModel(const ReGameWeaponBoxSetModelMCallback callback,
                                        const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct ReGameWeaponBoxSetModel;
        return CreateHook<ReGameWeaponBoxSetModel>(HookChains()->WeaponBoxSetModel(), callback, priority, enable);
    }
}
#endif
