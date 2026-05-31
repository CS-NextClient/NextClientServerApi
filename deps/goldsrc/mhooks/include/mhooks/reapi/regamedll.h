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
#include <core/regamedll_api.h>
#include <mhooks/common/mhook.h>
#include <mhooks/reapi/reapi_mhookchain.h>

// ShowMenu
using ReGameShowMenuMChain = mhooks::ReApiMHookChain<cssdk::ReHookShowMenu, void(cssdk::PlayerBase*, int, int, cssdk::qboolean, char*)>;
using ReGameShowMenuMCallback = core::Delegate<void(const ReGameShowMenuMChain& chain, cssdk::PlayerBase* player, int slots, int display_time, cssdk::qboolean need_more, char* text)>;

// ShowVGUIMenu
using ReGameShowVguiMenuMChain = mhooks::ReApiMHookChain<cssdk::ReHookShowVguiMenu, void(cssdk::PlayerBase*, cssdk::VguiMenu, int, char*)>;
using ReGameShowVguiMenuMCallback = core::Delegate<void(const ReGameShowVguiMenuMChain& chain, cssdk::PlayerBase* player, cssdk::VguiMenu menu, int mask, char* old_menu)>;

// HandleMenu_ChooseTeam
using ReGameHandleMenuChooseTeamMChain = mhooks::ReApiMHookChain<cssdk::ReHookHandleMenuChooseTeam, cssdk::qboolean(cssdk::PlayerBase*, cssdk::ChooseTeamMenuSlot)>;
using ReGameHandleMenuChooseTeamMCallback = core::Delegate<cssdk::qboolean(const ReGameHandleMenuChooseTeamMChain& chain, cssdk::PlayerBase* player, cssdk::ChooseTeamMenuSlot slot)>;

// HandleMenu_ChooseAppearance
using ReGameHandleMenuChooseAppearanceMChain = mhooks::ReApiMHookChain<cssdk::ReHookHandleMenuChooseAppearance, void(cssdk::PlayerBase*, int)>;
using ReGameHandleMenuChooseAppearanceMCallback = core::Delegate<void(const ReGameHandleMenuChooseAppearanceMChain& chain, cssdk::PlayerBase* player, int slot)>;

// GetForceCamera
using ReGameGetForceCameraMChain = mhooks::ReApiMHookChain<cssdk::ReHookGetForceCamera, int(cssdk::PlayerBase*)>;
using ReGameGetForceCameraMCallback = core::Delegate<int(const ReGameGetForceCameraMChain& chain, cssdk::PlayerBase* observer)>;

// PlayerBlind
using ReGamePlayerBlindMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerBlind, void(cssdk::PlayerBase*, cssdk::EntityVars*, cssdk::EntityVars*, float, float, int, cssdk::Vector&)>;
using ReGamePlayerBlindMCallback = core::Delegate<void(const ReGamePlayerBlindMChain& chain, cssdk::PlayerBase* victim, cssdk::EntityVars* inflictor, cssdk::EntityVars* attacker, float fade_time, float fade_hold, int alpha, cssdk::Vector& color)>;

// RadiusFlash_TraceLine
using ReGameRadiusFlashTraceLineMChain = mhooks::ReApiMHookChain<cssdk::ReHookRadiusFlashTraceLine, void(cssdk::PlayerBase*, cssdk::EntityVars*, cssdk::EntityVars*, cssdk::Vector&, cssdk::Vector&, cssdk::TraceResult*)>;
using ReGameRadiusFlashTraceLineMCallback = core::Delegate<void(const ReGameRadiusFlashTraceLineMChain& chain, cssdk::PlayerBase* player, cssdk::EntityVars* inflictor, cssdk::EntityVars* attacker, cssdk::Vector& origin, cssdk::Vector& spot, cssdk::TraceResult* trace_result)>;

// InternalCommand
using ReGameInternalCommandMChain = mhooks::ReApiMHookChain<cssdk::ReHookInternalCommand, void(cssdk::Edict*, const char*, const char*)>;
using ReGameInternalCommandMCallback = core::Delegate<void(const ReGameInternalCommandMChain& chain, cssdk::Edict* client, const char* command, const char* arg1)>;

// CGameRules::InstallGameRules
using ReGameRulesInstallGameRulesMChain = mhooks::ReApiMHookChain<cssdk::ReHookInstallGameRules, cssdk::GameRulesBase*()>;
using ReGameRulesInstallGameRulesMCallback = core::Delegate<cssdk::GameRulesBase*(const ReGameRulesInstallGameRulesMChain& chain)>;

// CGameRules::FreeGameRules
using ReGameRulesFreeGameRulesMChain = mhooks::ReApiMHookChain<cssdk::ReHookFreeGameRules, void(cssdk::GameRulesBase**)>;
using ReGameRulesFreeGameRulesMCallback = core::Delegate<void(const ReGameRulesFreeGameRulesMChain& chain, cssdk::GameRulesBase**)>;

// CGameRules::OnRoundFreezeEnd
using ReGameRulesRoundFreezeEndMChain = mhooks::ReApiMHookChain<cssdk::ReHookGameRulesOnRoundFreezeEnd, void()>;
using ReGameRulesRoundFreezeEndMCallback = core::Delegate<void(const ReGameRulesRoundFreezeEndMChain& chain)>;

// CGameRules::OnRoundEnd
using ReGameRulesRoundEndMChain = mhooks::ReApiMHookChain<cssdk::ReHookRoundEnd, bool(int, cssdk::ScenarioEventEndRound, float)>;
using ReGameRulesRoundEndMCallback = core::Delegate<bool(const ReGameRulesRoundEndMChain& chain, int win_status, cssdk::ScenarioEventEndRound event, float delay)>;

// CHalfLifeMultiplay::RestartRound
using ReGameMultiplayRestartRoundMChain = mhooks::ReApiMHookChain<cssdk::ReHookGameRulesRestartRound, void()>;
using ReGameMultiplayRestartRoundMCallback = core::Delegate<void(const ReGameMultiplayRestartRoundMChain& chain)>;

// CHalfLifeMultiplay::BalanceTeams
using ReGameMultiplayBalanceTeamsMChain = mhooks::ReApiMHookChain<cssdk::ReHookGameRulesBalanceTeams, void()>;
using ReGameMultiplayBalanceTeamsMCallback = core::Delegate<void(const ReGameMultiplayBalanceTeamsMChain& chain)>;

// CCStrikeGameMgrHelper::CanPlayerHearPlayer
using ReGameMgrHelpCanPlayerHearPlayerMChain = mhooks::ReApiMHookChain<cssdk::ReHookGameRulesCanPlayerHearPlayer, bool(cssdk::PlayerBase*, cssdk::PlayerBase*)>;
using ReGameMgrHelpCanPlayerHearPlayerMCallback = core::Delegate<bool(const ReGameMgrHelpCanPlayerHearPlayerMChain& chain, cssdk::PlayerBase* listener, cssdk::PlayerBase* talker)>;

// CBasePlayerWeapon::DefaultDeploy
using ReGameWeaponDefaultDeployMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerWeaponDefaultDeploy, cssdk::qboolean(cssdk::PlayerWeaponBase*, char*, char*, int, char*, cssdk::qboolean)>;
using ReGameWeaponDefaultDeployMCallback = core::Delegate<cssdk::qboolean(const ReGameWeaponDefaultDeployMChain& chain, cssdk::PlayerWeaponBase* weapon, char* view_model, char* weapon_model, int anim, char* anim_ext, cssdk::qboolean skip_local)>;

// CBasePlayer::Spawn
using ReGamePlayerSpawnMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerSpawn, void(cssdk::PlayerBase*)>;
using ReGamePlayerSpawnMCallback = core::Delegate<void(const ReGamePlayerSpawnMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::PreThink
using ReGamePlayerPreThinkMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerPreThink, void(cssdk::PlayerBase*)>;
using ReGamePlayerPreThinkMCallback = core::Delegate<void(const ReGamePlayerPreThinkMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::PostThink
using ReGamePlayerPostThinkMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerPostThink, void(cssdk::PlayerBase*)>;
using ReGamePlayerPostThinkMCallback = core::Delegate<void(const ReGamePlayerPostThinkMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::UpdateClientData
using ReGamePlayerUpdateClientDataMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerUpdateClientData, void(cssdk::PlayerBase*)>;
using ReGamePlayerUpdateClientDataMCallback = core::Delegate<void(const ReGamePlayerUpdateClientDataMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::TakeDamage
using ReGamePlayerTakeDamageMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerTakeDamage, cssdk::qboolean(cssdk::PlayerBase*, cssdk::EntityVars*, cssdk::EntityVars*, float&, int)>;
using ReGamePlayerTakeDamageMCallback = core::Delegate<cssdk::qboolean(const ReGamePlayerTakeDamageMChain& chain, cssdk::PlayerBase* victim, cssdk::EntityVars* inflictor, cssdk::EntityVars* attacker, float& damage, int damage_type)>;

// CBasePlayer::Killed
using ReGamePlayerKilledMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerKilled, void(cssdk::PlayerBase*, cssdk::EntityVars*, int)>;
using ReGamePlayerKilledMCallback = core::Delegate<void(const ReGamePlayerKilledMChain& chain, cssdk::PlayerBase* victim, cssdk::EntityVars* attacker, int gib)>;

// CBasePlayer::AddPlayerItem
using ReGamePlayerAddPlayerItemMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerAddPlayerItem, cssdk::qboolean(cssdk::PlayerBase*, cssdk::PlayerItemBase*)>;
using ReGamePlayerAddPlayerItemMCallback = core::Delegate<cssdk::qboolean(const ReGamePlayerAddPlayerItemMChain& chain, cssdk::PlayerBase* player, cssdk::PlayerItemBase* item)>;

// CBasePlayer::RemovePlayerItem
using ReGamePlayerRemovePlayerItemMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerRemovePlayerItem, cssdk::qboolean(cssdk::PlayerBase*, cssdk::PlayerItemBase*)>;
using ReGamePlayerRemovePlayerItemMCallback = core::Delegate<cssdk::qboolean(const ReGamePlayerRemovePlayerItemMChain& chain, cssdk::PlayerBase* player, cssdk::PlayerItemBase* item)>;

// CBasePlayer::DropPlayerItem
using ReGamePlayerDropPlayerItemMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerDropPlayerItem, cssdk::EntityBase*(cssdk::PlayerBase*, const char*)>;
using ReGamePlayerDropPlayerItemMCallback = core::Delegate<cssdk::EntityBase*(const ReGamePlayerDropPlayerItemMChain& chain, cssdk::PlayerBase* player, const char* itemName)>;

// CBasePlayer::Observer_IsValidTarget
using ReGamePlayerObserverIsValidTargetMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerObserverIsValidTarget, cssdk::PlayerBase*(cssdk::PlayerBase*, int, bool)>;
using ReGamePlayerObserverIsValidTargetMCallback = core::Delegate<cssdk::PlayerBase*(const ReGamePlayerObserverIsValidTargetMChain& chain, cssdk::PlayerBase* observer, int player_index, bool same_team)>;

// CBasePlayer::StartObserver
using ReGamePlayerStartObserverMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerStartObserver, void(cssdk::PlayerBase*, cssdk::Vector&, cssdk::Vector&)>;
using ReGamePlayerStartObserverMCallback = core::Delegate<void(const ReGamePlayerStartObserverMChain& chain, cssdk::PlayerBase* player, cssdk::Vector& position, cssdk::Vector& view_angle)>;

// CBasePlayer::GetIntoGame
using ReGamePlayerGetIntoGameMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerGetIntoGame, bool(cssdk::PlayerBase*)>;
using ReGamePlayerGetIntoGameMCallback = core::Delegate<bool(const ReGamePlayerGetIntoGameMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::MakeBomber
using ReGamePlayerMakeBomberMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerMakeBomber, bool(cssdk::PlayerBase*)>;
using ReGamePlayerMakeBomberMCallback = core::Delegate<bool(const ReGamePlayerMakeBomberMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::Jump
using ReGamePlayerJumpMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerJump, void(cssdk::PlayerBase*)>;
using ReGamePlayerJumpMCallback = core::Delegate<void(const ReGamePlayerJumpMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::ResetMaxSpeed
using ReGamePlayerResetMaxSpeedMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerResetMaxSpeed, void(cssdk::PlayerBase*)>;
using ReGamePlayerResetMaxSpeedMCallback = core::Delegate<void(const ReGamePlayerResetMaxSpeedMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::OnSpawnEquip
using ReGamePlayerSpawnEquipMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerOnSpawnEquip, void(cssdk::PlayerBase*, bool, bool)>;
using ReGamePlayerSpawnEquipMCallback = core::Delegate<void(const ReGamePlayerSpawnEquipMChain& chain, cssdk::PlayerBase* player, bool add_default, bool equip_game)>;

// CBasePlayer::GiveDefaultItems
using ReGamePlayerGiveDefaultItemsMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerGiveDefaultItems, void(cssdk::PlayerBase*)>;
using ReGamePlayerGiveDefaultItemsMCallback = core::Delegate<void(const ReGamePlayerGiveDefaultItemsMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::SetClientUserInfoName
using ReGamePlayerSetClientUserInfoNameMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerSetClientUserInfoName, bool(cssdk::PlayerBase*, char*, char*)>;
using ReGamePlayerSetClientUserInfoNameMCallback = core::Delegate<bool(const ReGamePlayerSetClientUserInfoNameMChain& chain, cssdk::PlayerBase* player, char* info, char* name)>;

// CBasePlayer::SetClientUserInfoModel
using ReGamePlayerSetClientUserInfoModelMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerSetClientUserInfoModel, void(cssdk::PlayerBase*, char*, char*)>;
using ReGamePlayerSetClientUserInfoModelMCallback = core::Delegate<void(const ReGamePlayerSetClientUserInfoModelMChain& chain, cssdk::PlayerBase* player, char* info, char* model)>;

// CBasePlayer::ThrowGrenade
using ReGamePlayerThrowGrenadeMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerThrowGrenade, cssdk::Grenade*(cssdk::PlayerBase*, cssdk::PlayerWeaponBase*, cssdk::Vector&, cssdk::Vector&, float, unsigned short)>;
using ReGamePlayerThrowGrenadeMCallback = core::Delegate<cssdk::Grenade*(const ReGamePlayerThrowGrenadeMChain& chain, cssdk::PlayerBase* player, cssdk::PlayerWeaponBase* weapon, cssdk::Vector& origin, cssdk::Vector& velocity, float time, unsigned short event_id)>;

// CBasePlayer::Pain
using ReGamePlayerPainMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerPain, void(cssdk::PlayerBase*, cssdk::HitBoxGroup, bool)>;
using ReGamePlayerPainMCallback = core::Delegate<void(const ReGamePlayerPainMChain& chain, cssdk::PlayerBase* player, cssdk::HitBoxGroup lastHitGroup, bool hasArmour)>;

// CBasePlayer::DeathSound
using ReGamePlayerDeathSoundMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerDeathSound, void(cssdk::PlayerBase*)>;
using ReGamePlayerDeathSoundMCallback = core::Delegate<void(const ReGamePlayerDeathSoundMChain& chain, cssdk::PlayerBase* player)>;

// CBasePlayer::JoiningThink
using ReGamePlayerJoiningThinkMChain = mhooks::ReApiMHookChain<cssdk::ReHookPlayerJoiningThink, void(cssdk::PlayerBase*)>;
using ReGamePlayerJoiningThinkMCallback = core::Delegate<void(const ReGamePlayerJoiningThinkMChain& chain, cssdk::PlayerBase* player)>;

// CWeaponBox::SetModel
using ReGameWeaponBoxSetModelMChain = mhooks::ReApiMHookChain<cssdk::ReHookWeaponBoxSetModel, void(cssdk::WeaponBox*, const char*)>;
using ReGameWeaponBoxSetModelMCallback = core::Delegate<void(const ReGameWeaponBoxSetModelMChain& chain, cssdk::WeaponBox* weaponBox, const char* modelName)>;

namespace mhooks
{
    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameShowMenu(
        ReGameShowMenuMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameShowVguiMenu(
        ReGameShowVguiMenuMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameHandleMenuChooseTeam(
        ReGameHandleMenuChooseTeamMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameHandleMenuChooseAppearance(
        ReGameHandleMenuChooseAppearanceMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameGetForceCamera(
        ReGameGetForceCameraMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerBlind(
        ReGamePlayerBlindMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameRadiusFlashTraceLine(
        ReGameRadiusFlashTraceLineMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameInternalCommand(
        ReGameInternalCommandMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameRulesInstallGameRules(
        ReGameRulesInstallGameRulesMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameRulesFreeGameRules(
        ReGameRulesFreeGameRulesMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameRulesRoundFreezeEnd(
        ReGameRulesRoundFreezeEndMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameRulesRoundEnd(
        ReGameRulesRoundEndMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameMultiplayRestartRound(
        ReGameMultiplayRestartRoundMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameMultiplayBalanceTeams(
        ReGameMultiplayBalanceTeamsMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameMgrHelpCanPlayerHearPlayer(
        ReGameMgrHelpCanPlayerHearPlayerMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameWeaponDefaultDeploy(
        ReGameWeaponDefaultDeployMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerSpawn(
        ReGamePlayerSpawnMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerPreThink(
        ReGamePlayerPreThinkMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerPostThink(
        ReGamePlayerPostThinkMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerUpdateClientData(
        ReGamePlayerUpdateClientDataMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerTakeDamage(
        ReGamePlayerTakeDamageMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerKilled(
        ReGamePlayerKilledMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerAddPlayerItem(
        ReGamePlayerAddPlayerItemMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerRemovePlayerItem(
        ReGamePlayerRemovePlayerItemMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerDropPlayerItem(
        ReGamePlayerDropPlayerItemMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerObserverIsValidTarget(
        ReGamePlayerObserverIsValidTargetMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerStartObserver(
        ReGamePlayerStartObserverMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerGetIntoGame(
        ReGamePlayerGetIntoGameMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerMakeBomber(
        ReGamePlayerMakeBomberMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerJump(
        ReGamePlayerJumpMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerResetMaxSpeed(
        ReGamePlayerResetMaxSpeedMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerSpawnEquip(
        ReGamePlayerSpawnEquipMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerGiveDefaultItems(
        ReGamePlayerGiveDefaultItemsMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerSetClientUserInfoName(
        ReGamePlayerSetClientUserInfoNameMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerSetClientUserInfoModel(
        ReGamePlayerSetClientUserInfoModelMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerThrowGrenade(
        ReGamePlayerThrowGrenadeMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerPain(
        ReGamePlayerPainMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerDeathSound(
        ReGamePlayerDeathSoundMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGamePlayerJoiningThink(
        ReGamePlayerJoiningThinkMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);

    /**
     * @brief N/D
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     */
    ATTR_MINSIZE MHook* MHookReGameWeaponBoxSetModel(
        ReGameWeaponBoxSetModelMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
}
#endif
