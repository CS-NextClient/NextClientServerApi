/*
 *  Half Life 1 SDK Copyright(c) Valve Corp.
 *
 *  THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE CORPORATION ("Valve").
 *  PLEASE READ IT BEFORE DOWNLOADING OR USING THE HALF LIFE 1 SDK ("SDK"). BY
 *  DOWNLOADING AND/OR USING THE HALF LIFE 1 SDK YOU ACCEPT THIS LICENSE. IF YOU DO
 *  NOT AGREE TO THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.
 *
 *  You may, free of charge, download and use the SDK to develop a modified Valve
 *  game running on the Half-Life 1 engine. You may distribute your modified Valve
 *  game in source and object code form, but only for free. Terms of use for Valve
 *  games are found in the Steam Subscriber Agreement located here:
 *  http://store.steampowered.com/subscriber_agreement/
 *
 *  You may copy, modify, and distribute the SDK and any modifications you make to
 *  the SDK in source and object code form, but only for free. Any distribution of
 *  this SDK must include this LICENSE file.
 *
 *  Any distribution of the SDK or a substantial portion of the SDK must include
 *  the above copyright notice and the following:
 *
 *    DISCLAIMER OF WARRANTIES. THE HALF LIFE 1 SDK AND ANY OTHER MATERIAL
 *    DOWNLOADED BY LICENSEE IS PROVIDED "AS IS". VALVE AND ITS SUPPLIERS
 *    DISCLAIM ALL WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS OR IMPLIED,
 *    INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY,
 *    NON-INFRINGEMENT, TITLE AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    LIMITATION OF LIABILITY. IN NO EVENT SHALL VALVE OR ITS SUPPLIERS BE LIABLE
 *    FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 *    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
 *    LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THE ENGINE AND/OR THE
 *    SDK, EVEN IF VALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *  If you would like to use the SDK for a commercial purpose, please contact Valve
 *  at sourceengine@valvesoftware.com.
 */

#pragma once

#include <cssdk/common/hook_chains.h>
#include <cssdk/dll/game_rules.h>
#include <cssdk/dll/gib.h>
#include <cssdk/game_shared/game_event.h>

namespace cssdk
{
    constexpr auto REGAMEDLL_API_VERSION_MAJOR = 5;
    constexpr auto REGAMEDLL_API_VERSION_MINOR = 26;
    constexpr auto VREGAMEDLL_API_VERSION = "VRE_GAMEDLL_API_VERSION001";

    // PlayerBase::Spawn hook
    using ReHookPlayerSpawn = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerSpawn = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::Precache hook
    using ReHookPlayerPrecache = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerPrecache = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::ObjectCaps hook
    using ReHookPlayerObjectCaps = IHookChainClass<int, PlayerBase>;
    using ReHookRegistryPlayerObjectCaps = IHookChainClassRegistry<int, PlayerBase>;

    // PlayerBase::Classify hook
    using ReHookPlayerClassify = IHookChainClass<int, PlayerBase>;
    using ReHookRegistryPlayerClassify = IHookChainClassRegistry<int, PlayerBase>;

    // PlayerBase::TraceAttack hook
    using ReHookPlayerTraceAttack = IHookChainClass<void, PlayerBase, EntityVars*, float, Vector&, TraceResult*, int>;
    using ReHookRegistryPlayerTraceAttack =
        IHookChainClassRegistry<void, PlayerBase, EntityVars*, float, Vector&, TraceResult*, int>;

    // PlayerBase::TakeDamage hook
    using ReHookPlayerTakeDamage = IHookChainClass<qboolean, PlayerBase, EntityVars*, EntityVars*, float&, int>;
    using ReHookRegistryPlayerTakeDamage = IHookChainClassRegistry<qboolean, PlayerBase, EntityVars*, EntityVars*, float&, int>;

    // PlayerBase::TakeHealth hook
    using ReHookPlayerTakeHealth = IHookChainClass<qboolean, PlayerBase, float, int>;
    using ReHookRegistryPlayerTakeHealth = IHookChainClassRegistry<qboolean, PlayerBase, float, int>;

    // PlayerBase::Killed hook
    using ReHookPlayerKilled = IHookChainClass<void, PlayerBase, EntityVars*, int>;
    using ReHookRegistryPlayerKilled = IHookChainClassRegistry<void, PlayerBase, EntityVars*, int>;

    // PlayerBase::AddPoints hook
    using ReHookPlayerAddPoints = IHookChainClass<void, PlayerBase, int, qboolean>;
    using ReHookRegistryPlayerAddPoints = IHookChainClassRegistry<void, PlayerBase, int, qboolean>;

    // PlayerBase::AddPointsToTeam hook
    using ReHookPlayerAddPointsToTeam = IHookChainClass<void, PlayerBase, int, qboolean>;
    using ReHookRegistryPlayerAddPointsToTeam = IHookChainClassRegistry<void, PlayerBase, int, qboolean>;

    // PlayerBase::AddPlayerItem hook
    using ReHookPlayerAddPlayerItem = IHookChainClass<qboolean, PlayerBase, PlayerItemBase*>;
    using ReHookRegistryPlayerAddPlayerItem = IHookChainClassRegistry<qboolean, PlayerBase, PlayerItemBase*>;

    // PlayerBase::RemovePlayerItem hook
    using ReHookPlayerRemovePlayerItem = IHookChainClass<qboolean, PlayerBase, PlayerItemBase*>;
    using ReHookRegistryPlayerRemovePlayerItem = IHookChainClassRegistry<qboolean, PlayerBase, PlayerItemBase*>;

    // PlayerBase::GiveAmmo hook
    using ReHookPlayerGiveAmmo = IHookChainClass<int, PlayerBase, int, const char*, int>;
    using ReHookRegistryPlayerGiveAmmo = IHookChainClassRegistry<int, PlayerBase, int, const char*, int>;

    // PlayerBase::ResetMaxSpeed hook
    using ReHookPlayerResetMaxSpeed = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerResetMaxSpeed = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::Jump hook
    using ReHookPlayerJump = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerJump = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::Duck hook
    using ReHookPlayerDuck = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerDuck = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::PreThink hook
    using ReHookPlayerPreThink = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerPreThink = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::PostThink hook
    using ReHookPlayerPostThink = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerPostThink = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::UpdateClientData hook
    using ReHookPlayerUpdateClientData = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerUpdateClientData = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::ImpulseCommands hook
    using ReHookPlayerImpulseCommands = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerImpulseCommands = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::RoundRespawn hook
    using ReHookPlayerRoundRespawn = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerRoundRespawn = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::Blind hook
    using ReHookPlayerBaseBlind = IHookChainClass<void, PlayerBase, float, float, float, int>;
    using ReHookRegistryPlayerBaseBlind = IHookChainClassRegistry<void, PlayerBase, float, float, float, int>;

    // PlayerBase::Observer_IsValidTarget hook
    using ReHookPlayerObserverIsValidTarget = IHookChainClass<PlayerBase*, PlayerBase, int, bool>;
    using ReHookRegistryPlayerObserverIsValidTarget = IHookChainClassRegistry<PlayerBase*, PlayerBase, int, bool>;

    // PlayerBase::SetAnimation hook
    using ReHookPlayerSetAnimation = IHookChainClass<void, PlayerBase, PlayerAnim>;
    using ReHookRegistryPlayerSetAnimation = IHookChainClassRegistry<void, PlayerBase, PlayerAnim>;

    // PlayerBase::GiveDefaultItems hook
    using ReHookPlayerGiveDefaultItems = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerGiveDefaultItems = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::GiveNamedItem hook
    using ReHookPlayerGiveNamedItem = IHookChainClass<EntityBase*, PlayerBase, const char*>;
    using ReHookRegistryPlayerGiveNamedItem = IHookChainClassRegistry<EntityBase*, PlayerBase, const char*>;

    // PlayerBase::AddAccount hook
    using ReHookPlayerAddAccount = IHookChainClass<void, PlayerBase, int, RewardType, bool>;
    using ReHookRegistryPlayerAddAccount = IHookChainClassRegistry<void, PlayerBase, int, RewardType, bool>;

    // PlayerBase::GiveShield hook
    using ReHookPlayerGiveShield = IHookChainClass<void, PlayerBase, bool>;
    using ReHookRegistryPlayerGiveShield = IHookChainClassRegistry<void, PlayerBase, bool>;

    // PlayerBase:SetClientUserInfoModel hook
    using ReHookPlayerSetClientUserInfoModel = IHookChainClass<void, PlayerBase, char*, char*>;
    using ReHookRegistryPlayerSetClientUserInfoModel = IHookChainClassRegistry<void, PlayerBase, char*, char*>;

    // PlayerBase:SetClientUserInfoName hook
    using ReHookPlayerSetClientUserInfoName = IHookChainClass<bool, PlayerBase, char*, char*>;
    using ReHookRegistryPlayerSetClientUserInfoName = IHookChainClassRegistry<bool, PlayerBase, char*, char*>;

    // PlayerBase::HasRestrictItem hook
    using ReHookPlayerHasRestrictItem = IHookChainClass<bool, PlayerBase, ItemId, ItemRestType>;
    using ReHookRegistryPlayerHasRestrictItem = IHookChainClassRegistry<bool, PlayerBase, ItemId, ItemRestType>;

    // PlayerBase::DropPlayerItem hook
    using ReHookPlayerDropPlayerItem = IHookChainClass<EntityBase*, PlayerBase, const char*>;
    using ReHookRegistryPlayerDropPlayerItem = IHookChainClassRegistry<EntityBase*, PlayerBase, const char*>;

    // PlayerBase::DropShield hook
    using ReHookPlayerDropShield = IHookChainClass<EntityBase*, PlayerBase, bool>;
    using ReHookRegistryPlayerDropShield = IHookChainClassRegistry<EntityBase*, PlayerBase, bool>;

    // PlayerBase::OnSpawnEquip hook
    using ReHookPlayerOnSpawnEquip = IHookChainClass<void, PlayerBase, bool, bool>;
    using ReHookRegistryPlayerOnSpawnEquip = IHookChainClassRegistry<void, PlayerBase, bool, bool>;

    // PlayerBase::Radio hook
    using ReHookPlayerRadio = IHookChainClass<void, PlayerBase, const char*, const char*, short, bool>;
    using ReHookRegistryPlayerRadio = IHookChainClassRegistry<void, PlayerBase, const char*, const char*, short, bool>;

    // PlayerBase::Disappear hook
    using ReHookPlayerDisappear = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerDisappear = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::MakeVIP hook
    using ReHookPlayerMakeVip = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerMakeVip = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::MakeBomber hook
    using ReHookPlayerMakeBomber = IHookChainClass<bool, PlayerBase>;
    using ReHookRegistryPlayerMakeBomber = IHookChainClassRegistry<bool, PlayerBase>;

    // PlayerBase::StartObserver hook
    using ReHookPlayerStartObserver = IHookChainClass<void, PlayerBase, Vector&, Vector&>;
    using ReHookRegistryPlayerStartObserver = IHookChainClassRegistry<void, PlayerBase, Vector&, Vector&>;

    // PlayerBase::GetIntoGame hook
    using ReHookPlayerGetIntoGame = IHookChainClass<bool, PlayerBase>;
    using ReHookRegistryPlayerGetIntoGame = IHookChainClassRegistry<bool, PlayerBase>;

    // AnimatingBase::ResetSequenceInfo hook
    using ReHookAnimatingResetSequenceInfo = IHookChainClass<void, AnimatingBase>;
    using ReHookRegistryAnimatingResetSequenceInfo = IHookChainClassRegistry<void, AnimatingBase>;

    // GetForceCamera hook
    using ReHookGetForceCamera = IHookChain<int, PlayerBase*>;
    using ReHookRegistryGetForceCamera = IHookChainRegistry<int, PlayerBase*>;

    // PlayerBlind hook
    using ReHookPlayerBlind = IHookChain<void, PlayerBase*, EntityVars*, EntityVars*, float, float, int, Vector&>;
    using ReHookRegistryPlayerBlind =
        IHookChainRegistry<void, PlayerBase*, EntityVars*, EntityVars*, float, float, int, Vector&>;

    // RadiusFlash_TraceLine hook
    using ReHookRadiusFlashTraceLine = IHookChain<void, PlayerBase*, EntityVars*, EntityVars*, Vector&, Vector&, TraceResult*>;
    using ReHookRegistryRadiusFlashTraceLine =
        IHookChainRegistry<void, PlayerBase*, EntityVars*, EntityVars*, Vector&, Vector&, TraceResult*>;

    // RoundEnd hook
    using ReHookRoundEnd = IHookChain<bool, int, ScenarioEventEndRound, float>;
    using ReHookRegistryRoundEnd = IHookChainRegistry<bool, int, ScenarioEventEndRound, float>;

    // InstallGameRules hook
    using ReHookInstallGameRules = IHookChain<GameRulesBase*>;
    using ReHookRegistryInstallGameRules = IHookChainRegistry<GameRulesBase*>;

    // PM_Init hook
    using ReHookPmInit = IHookChain<void, PlayerMove*>;
    using ReHookRegistryPmInit = IHookChainRegistry<void, PlayerMove*>;

    // PM_Move hook
    using ReHookPmMove = IHookChain<void, PlayerMove*, int>;
    using ReHookRegistryPmMove = IHookChainRegistry<void, PlayerMove*, int>;

    // PM_AirMove hook
    using ReHookPmAirMove = IHookChain<void, int>;
    using ReHookRegistryPmAirMove = IHookChainRegistry<void, int>;

    // HandleMenu_ChooseAppearance hook
    using ReHookHandleMenuChooseAppearance = IHookChain<void, PlayerBase*, int>;
    using ReHookRegistryHandleMenuChooseAppearance = IHookChainRegistry<void, PlayerBase*, int>;

    // HandleMenu_ChooseTeam hook
    using ReHookHandleMenuChooseTeam = IHookChain<qboolean, PlayerBase*, ChooseTeamMenuSlot>;
    using ReHookRegistryHandleMenuChooseTeam = IHookChainRegistry<qboolean, PlayerBase*, ChooseTeamMenuSlot>;

    // ShowMenu hook
    using ReHookShowMenu = IHookChain<void, PlayerBase*, int, int, qboolean, char*>;
    using ReHookRegistryShowMenu = IHookChainRegistry<void, PlayerBase*, int, int, qboolean, char*>;

    // ShowVGUIMenu hook
    using ReHookShowVguiMenu = IHookChain<void, PlayerBase*, VguiMenu, int, char*>;
    using ReHookRegistryShowVguiMenu = IHookChainRegistry<void, PlayerBase*, VguiMenu, int, char*>;

    // BuyGunAmmo hook
    using ReHookBuyGunAmmo = IHookChain<bool, PlayerBase*, PlayerItemBase*, bool>;
    using ReHookRegistryBuyGunAmmo = IHookChainRegistry<bool, PlayerBase*, PlayerItemBase*, bool>;

    // BuyWeaponByWeaponID hook
    using ReHookBuyWeaponByWeaponId = IHookChain<EntityBase*, PlayerBase*, WeaponId>;
    using ReHookRegistryBuyWeaponByWeaponId = IHookChainRegistry<EntityBase*, PlayerBase*, WeaponId>;

    // InternalCommand hook
    using ReHookInternalCommand = IHookChain<void, Edict*, const char*, const char*>;
    using ReHookRegistryInternalCommand = IHookChainRegistry<void, Edict*, const char*, const char*>;

    // CHalfLifeMultiplay::FShouldSwitchWeapon hook
    using ReHookGameRulesShouldSwitchWeapon = IHookChain<qboolean, PlayerBase*, PlayerItemBase*>;
    using ReHookRegistryGameRulesShouldSwitchWeapon = IHookChainRegistry<qboolean, PlayerBase*, PlayerItemBase*>;

    // CHalfLifeMultiplay::GetNextBestWeapon hook
    using ReHookGameRulesGetNextBestWeapon = IHookChain<qboolean, PlayerBase*, PlayerItemBase*>;
    using ReHookRegistryGameRulesGetNextBestWeapon = IHookChainRegistry<qboolean, PlayerBase*, PlayerItemBase*>;

    // CHalfLifeMultiplay::FlPlayerFallDamage hook
    using ReHookGameRulesPlayerFallDamage = IHookChain<float, PlayerBase*>;
    using ReHookRegistryGameRulesPlayerFallDamage = IHookChainRegistry<float, PlayerBase*>;

    // CHalfLifeMultiplay::FPlayerCanTakeDamage hook
    using ReHookGameRulesPlayerCanTakeDamage = IHookChain<qboolean, PlayerBase*, EntityBase*>;
    using ReHookRegistryGameRulesPlayerCanTakeDamage = IHookChainRegistry<qboolean, PlayerBase*, EntityBase*>;

    // CHalfLifeMultiplay::PlayerSpawn hook
    using ReHookGameRulesPlayerSpawn = IHookChain<void, PlayerBase*>;
    using ReHookRegistryGameRulesPlayerSpawn = IHookChainRegistry<void, PlayerBase*>;

    // CHalfLifeMultiplay::FPlayerCanRespawn hook
    using ReHookGameRulesPlayerCanRespawn = IHookChain<qboolean, PlayerBase*>;
    using ReHookRegistryGameRulesPlayerCanRespawn = IHookChainRegistry<qboolean, PlayerBase*>;

    // CHalfLifeMultiplay::GetPlayerSpawnSpot hook
    using ReHookGameRulesGetPlayerSpawnSpot = IHookChain<Edict*, PlayerBase*>;
    using ReHookRegistryGameRulesGetPlayerSpawnSpot = IHookChainRegistry<Edict*, PlayerBase*>;

    // CHalfLifeMultiplay::ClientUserInfoChanged hook
    using ReHookGameRulesClientUserInfoChanged = IHookChain<void, PlayerBase*, char*>;
    using ReHookRegistryGameRulesClientUserInfoChanged = IHookChainRegistry<void, PlayerBase*, char*>;

    // CHalfLifeMultiplay::PlayerKilled hook
    using ReHookGameRulesPlayerKilled = IHookChain<void, PlayerBase*, EntityVars*, EntityVars*>;
    using ReHookRegistryGameRulesPlayerKilled = IHookChainRegistry<void, PlayerBase*, EntityVars*, EntityVars*>;

    // CHalfLifeMultiplay::DeathNotice hook
    using ReHookGameRulesDeathNotice = IHookChain<void, PlayerBase*, EntityVars*, EntityVars*>;
    using ReHookRegistryGameRulesDeathNotice = IHookChainRegistry<void, PlayerBase*, EntityVars*, EntityVars*>;

    // CHalfLifeMultiplay::CanHavePlayerItem hook
    using ReHookGameRulesCanHavePlayerItem = IHookChain<qboolean, PlayerBase*, PlayerItemBase*>;
    using ReHookRegistryGameRulesCanHavePlayerItem = IHookChainRegistry<qboolean, PlayerBase*, PlayerItemBase*>;

    // CHalfLifeMultiplay::DeadPlayerWeapons hook
    using ReHookGameRulesDeadPlayerWeapons = IHookChain<int, PlayerBase*>;
    using ReHookRegistryGameRulesDeadPlayerWeapons = IHookChainRegistry<int, PlayerBase*>;

    // CHalfLifeMultiplay::ServerDeactivate hook
    using ReHookGameRulesServerDeactivate = IHookChain<void>;
    using ReHookRegistryGameRulesServerDeactivate = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::CheckMapConditions hook
    using ReHookGameRulesCheckMapConditions = IHookChain<void>;
    using ReHookRegistryGameRulesCheckMapConditions = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::CleanUpMap hook
    using ReHookGameRulesCleanUpMap = IHookChain<void>;
    using ReHookRegistryGameRulesCleanUpMap = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::RestartRound hook
    using ReHookGameRulesRestartRound = IHookChain<void>;
    using ReHookRegistryGameRulesRestartRound = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::CheckWinConditions hook
    using ReHookGameRulesCheckWinConditions = IHookChain<void>;
    using ReHookRegistryGameRulesCheckWinConditions = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::RemoveGuns hook
    using ReHookGameRulesRemoveGuns = IHookChain<void>;
    using ReHookRegistryGameRulesRemoveGuns = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::GiveC4 hook
    using ReHookGameRulesGiveC4 = IHookChain<void>;
    using ReHookRegistryGameRulesGiveC4 = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::ChangeLevel hook
    using ReHookGameRulesChangeLevel = IHookChain<void>;
    using ReHookRegistryGameRulesChangeLevel = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::GoToIntermission hook
    using ReHookGameRulesGoToIntermission = IHookChain<void>;
    using ReHookRegistryGameRulesGoToIntermission = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::BalanceTeams hook
    using ReHookGameRulesBalanceTeams = IHookChain<void>;
    using ReHookRegistryGameRulesBalanceTeams = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::OnRoundFreezeEnd hook
    using ReHookGameRulesOnRoundFreezeEnd = IHookChain<void>;
    using ReHookRegistryGameRulesOnRoundFreezeEnd = IHookChainRegistry<void>;

    // GameRules::CanPlayerHearPlayer hook
    using ReHookGameRulesCanPlayerHearPlayer = IHookChain<bool, PlayerBase*, PlayerBase*>;
    using ReHookRegistryGameRulesCanPlayerHearPlayer = IHookChainRegistry<bool, PlayerBase*, PlayerBase*>;

    // PM_UpdateStepSound hook
    using ReHookPmUpdateStepSound = IHookChain<void>;
    using ReHookRegistryPmUpdateStepSound = IHookChainRegistry<void>;

    // PlayerBase::StartDeathCam hook
    using ReHookPlayerStartDeathCam = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerStartDeathCam = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::SwitchTeam hook
    using ReHookPlayerSwitchTeam = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerSwitchTeam = IHookChainClassRegistry<void, PlayerBase>;

    // PlayerBase::CanSwitchTeam hook
    using ReHookPlayerCanSwitchTeam = IHookChainClass<bool, PlayerBase, TeamName>;
    using ReHookRegistryPlayerCanSwitchTeam = IHookChainClassRegistry<bool, PlayerBase, TeamName>;

    // PlayerBase::ThrowGrenade hook
    using ReHookPlayerThrowGrenade =
        IHookChainClass<Grenade*, PlayerBase, PlayerWeaponBase*, Vector&, Vector&, float, unsigned short>;
    using ReHookRegistryPlayerThrowGrenade =
        IHookChainClassRegistry<Grenade*, PlayerBase, PlayerWeaponBase*, Vector&, Vector&, float, unsigned short>;

    // WeaponBox::SetModel hook
    using ReHookWeaponBoxSetModel = IHookChainClass<void, WeaponBox, const char*>;
    using ReHookRegistryWeaponBoxSetModel = IHookChainClassRegistry<void, WeaponBox, const char*>;

    // Grenade::DefuseBombStart hook
    using ReHookGrenadeDefuseBombStart = IHookChainClass<void, Grenade, PlayerBase*>;
    using ReHookRegistryGrenadeDefuseBombStart = IHookChainClassRegistry<void, Grenade, PlayerBase*>;

    // Grenade::DefuseBombEnd hook
    using ReHookGrenadeDefuseBombEnd = IHookChainClass<void, Grenade, PlayerBase*, bool>;
    using ReHookRegistryGrenadeDefuseBombEnd = IHookChainClassRegistry<void, Grenade, PlayerBase*, bool>;

    // Grenade::ExplodeHeGrenade hook
    using ReHookGrenadeExplodeHeGrenade = IHookChainClass<void, Grenade, TraceResult*, int>;
    using ReHookRegistryGrenadeExplodeHeGrenade = IHookChainClassRegistry<void, Grenade, TraceResult*, int>;

    // Grenade::ExplodeFlashbang hook
    using ReHookGrenadeExplodeFlashBang = IHookChainClass<void, Grenade, TraceResult*, int>;
    using ReHookRegistryGrenadeExplodeFlashBang = IHookChainClassRegistry<void, Grenade, TraceResult*, int>;

    // Grenade::ExplodeSmokeGrenade hook
    using ReHookGrenadeExplodeSmokeGrenade = IHookChainClass<void, Grenade>;
    using ReHookRegistryGrenadeExplodeSmokeGrenade = IHookChainClassRegistry<void, Grenade>;

    // Grenade::ExplodeBomb hook
    using ReHookGrenadeExplodeBomb = IHookChainClass<void, Grenade, TraceResult*, int>;
    using ReHookRegistryGrenadeExplodeBomb = IHookChainClassRegistry<void, Grenade, TraceResult*, int>;

    // ThrowHeGrenade hook
    using ReHookThrowHeGrenade = IHookChain<Grenade*, EntityVars*, Vector&, Vector&, float, int, unsigned short>;
    using ReHookRegistryThrowHeGrenade =
        IHookChainRegistry<Grenade*, EntityVars*, Vector&, Vector&, float, int, unsigned short>;

    // ThrowFlashbang hook
    using ReHookThrowFlashBang = IHookChain<Grenade*, EntityVars*, Vector&, Vector&, float>;
    using ReHookRegistryThrowFlashBang = IHookChainRegistry<Grenade*, EntityVars*, Vector&, Vector&, float>;

    // ThrowSmokeGrenade hook
    using ReHookThrowSmokeGrenade = IHookChain<Grenade*, EntityVars*, Vector&, Vector&, float, unsigned short>;
    using ReHookRegistryThrowSmokeGrenade = IHookChainRegistry<Grenade*, EntityVars*, Vector&, Vector&, float, unsigned short>;

    // PlantBomb hook
    using ReHookPlantBomb = IHookChain<Grenade*, EntityVars*, Vector&, Vector&>;
    using ReHookRegistryPlantBomb = IHookChainRegistry<Grenade*, EntityVars*, Vector&, Vector&>;

    // PlayerBase::SetSpawnProtection hook
    using ReHookPlayerSetSpawnProtection = IHookChainClass<void, PlayerBase, float>;
    using ReHookRegistryPlayerSetSpawnProtection = IHookChainClassRegistry<void, PlayerBase, float>;

    // PlayerBase::RemoveSpawnProtection hook
    using ReHookPlayerRemoveSpawnProtection = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerRemoveSpawnProtection = IHookChainClassRegistry<void, PlayerBase>;

    // IsPenetrableEntity hook
    using ReHookIsPenetrableEntity = IHookChain<bool, Vector&, Vector&, EntityVars*, Edict*>;
    using ReHookRegistryIsPenetrableEntity = IHookChainRegistry<bool, Vector&, Vector&, EntityVars*, Edict*>;

    // PlayerBase::HintMessageEx hook
    using ReHookPlayerHintMessageEx = IHookChainClass<bool, PlayerBase, const char*, float, bool, bool>;
    using ReHookRegistryPlayerHintMessageEx = IHookChainClassRegistry<bool, PlayerBase, const char*, float, bool, bool>;

    // PlayerBase::UseEmpty hook
    using ReHookPlayerUseEmpty = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerUseEmpty = IHookChainClassRegistry<void, PlayerBase>;

    // player_baseWeapon::CanDeploy hook
    using ReHookPlayerWeaponCanDeploy = IHookChainClass<qboolean, PlayerWeaponBase>;
    using ReHookRegistryPlayerWeaponCanDeploy = IHookChainClassRegistry<qboolean, PlayerWeaponBase>;

    // player_baseWeapon::DefaultDeploy hook
    using ReHookPlayerWeaponDefaultDeploy = IHookChainClass<qboolean, PlayerWeaponBase, char*, char*, int, char*, int>;
    using ReHookRegistryPlayerWeaponDefaultDeploy =
        IHookChainClassRegistry<qboolean, PlayerWeaponBase, char*, char*, int, char*, int>;

    // player_baseWeapon::DefaultReload hook
    using ReHookPlayerWeaponDefaultReload = IHookChainClass<int, PlayerWeaponBase, int, int, float>;
    using ReHookRegistryPlayerWeaponDefaultReload = IHookChainClassRegistry<int, PlayerWeaponBase, int, int, float>;

    // player_baseWeapon::DefaultShotgunReload hook
    using ReHookPlayerWeaponDefaultShotgunReload =
        IHookChainClass<bool, PlayerWeaponBase, int, int, float, float, const char*, const char*>;
    using ReHookRegistryPlayerWeaponDefaultShotgunReload =
        IHookChainClassRegistry<bool, PlayerWeaponBase, int, int, float, float, const char*, const char*>;

    // PlayerBase::DropIdlePlayer hook
    using ReHookPlayerDropIdlePlayer = IHookChainClass<void, PlayerBase, const char*>;
    using ReHookRegistryPlayerDropIdlePlayer = IHookChainClassRegistry<void, PlayerBase, const char*>;

    // CreateWeaponBox hook
    using ReHookCreateWeaponBox =
        IHookChain<WeaponBox*, PlayerItemBase*, PlayerBase*, const char*, Vector&, Vector&, Vector&, float, bool>;
    using ReHookRegistryCreateWeaponBox =
        IHookChainRegistry<WeaponBox*, PlayerItemBase*, PlayerBase*, const char*, Vector&, Vector&, Vector&, float, bool>;

    // SpawnHeadGib hook
    using ReHookSpawnHeadGib = IHookChain<Gib, EntityVars*>;
    using ReHookRegistrySpawnHeadGib = IHookChainRegistry<Gib, EntityVars*>;

    // SpawnRandomGibs hook
    using ReHookSpawnRandomGibs = IHookChain<void, EntityVars*, int, int>;
    using ReHookRegistrySpawnRandomGibs = IHookChainRegistry<void, EntityVars*, int, int>;

    // Gib::Spawn hook
    using ReHookGibSpawn = IHookChainClass<void, Gib, const char*>;
    using ReHookRegistryGibSpawn = IHookChainClassRegistry<void, Gib, const char*>;

    // Gib::BounceGibTouch hook
    using ReHookGibBounceGibTouch = IHookChainClass<void, Gib, EntityBase*>;
    using ReHookRegistryGibBounceGibTouch = IHookChainClassRegistry<void, Gib, EntityBase*>;

    // Gib::WaitTillLand hook
    using ReHookGibWaitTillLand = IHookChainClass<void, Gib>;
    using ReHookRegistryGibWaitTillLand = IHookChainClassRegistry<void, Gib>;

    // CBaseEntity::FireBullets hook
    using ReHookEntityBaseFireBullets =
        IHookChainClass<void, EntityBase, unsigned long, Vector&, Vector&, Vector&, float, int, int, int, EntityVars*>;
    using ReHookRegistryEntityBaseFireBullets =
        IHookChainClassRegistry<void, EntityBase, unsigned long, Vector&, Vector&, Vector&, float, int, int, int, EntityVars*>;

    // CBaseEntity::FireBuckshots hook
    using ReHookEntityBaseFireBuckshots =
        IHookChainClass<void, EntityBase, unsigned long, Vector&, Vector&, Vector&, float, int, int, EntityVars*>;
    using ReHookRegistryEntityBaseFireBuckshots =
        IHookChainClassRegistry<void, EntityBase, unsigned long, Vector&, Vector&, Vector&, float, int, int, EntityVars*>;

    // CBaseEntity::FireBullets3 hook
    using ReHookEntityBaseFireBullets3 =
        IHookChainClass<Vector&, EntityBase, Vector&, Vector&, float, float, int, int, int, float, EntityVars*, bool, int>;
    using ReHookRegistryEntityBaseFireBullets3 = IHookChainClassRegistry<Vector&, EntityBase, Vector&, Vector&, float, float,
        int, int, int, float, EntityVars*, bool, int>;

    // CBasePlayer::Observer_SetMode hook
    using ReHookPlayerObserverSetMode = IHookChainClass<void, PlayerBase, int>;
    using ReHookRegistryPlayerObserverSetMode = IHookChainClassRegistry<void, PlayerBase, int>;

    // CBasePlayer::Observer_FindNextPlayer hook
    using ReHookPlayerObserverFindNextPlayer = IHookChainClass<void, PlayerBase, bool, const char*>;
    using ReHookRegistryPlayerObserverFindNextPlayer = IHookChainClassRegistry<void, PlayerBase, bool, const char*>;

    // CBasePlayer::Pain hook
    using ReHookPlayerPain = IHookChainClass<void, PlayerBase, HitBoxGroup, bool>;
    using ReHookRegistryPlayerPain = IHookChainClassRegistry<void, PlayerBase, HitBoxGroup, bool>;

    // CBasePlayer::DeathSound hook
    using ReHookPlayerDeathSound = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerDeathSound = IHookChainClassRegistry<void, PlayerBase>;

    // CBasePlayer::JoiningThink hook
    using ReHookPlayerJoiningThink = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerJoiningThink = IHookChainClassRegistry<void, PlayerBase>;

    // FreeGameRules hook
    using ReHookFreeGameRules = IHookChain<void, GameRulesBase**>;
    using ReHookRegistryFreeGameRules = IHookChainRegistry<void, GameRulesBase**>;

    // PM_LadderMove hook
    using ReHookPmLadderMove = IHookChain<void, PhysEntity*>;
    using ReHookRegistryPmLadderMove = IHookChainRegistry<void, PhysEntity*>;

    // PM_WaterJump hook
    using ReHookPmWaterJump = IHookChain<void>;
    using ReHookRegistryPmWaterJump = IHookChainRegistry<void>;

    // PM_CheckWaterJump hook
    using ReHookPmCheckWaterJump = IHookChain<void>;
    using ReHookRegistryPmCheckWaterJump = IHookChainRegistry<void>;

    // PM_Jump hook
    using ReHookPmJump = IHookChain<void>;
    using ReHookRegistryPmJump = IHookChainRegistry<void>;

    // PM_Duck hook
    using ReHookPmDuck = IHookChain<void>;
    using ReHookRegistryPmDuck = IHookChainRegistry<void>;

    // PM_UnDuck hook
    using ReHookPmUnDuck = IHookChain<void>;
    using ReHookRegistryPmUnDuck = IHookChainRegistry<void>;

    // PM_PlayStepSound hook
    using ReHookPmPlayStepSound = IHookChain<void, int, float>;
    using ReHookRegistryPmPlayStepSound = IHookChainRegistry<void, int, float>;

    // PM_AirAccelerate hook
    using ReHookPmAirAccelerate = IHookChain<void, Vector*, float, float>;
    using ReHookRegistryPmAirAccelerate = IHookChainRegistry<void, Vector*, float, float>;

    // ClearMultiDamage hook
    using ReHookClearMultiDamage = IHookChain<void>;
    using ReHookRegistryClearMultiDamage = IHookChainRegistry<void>;

    // AddMultiDamage hook
    using ReHookAddMultiDamage = IHookChain<void, EntityVars*, EntityBase*, float, int>;
    using ReHookRegistryAddMultiDamage = IHookChainRegistry<void, EntityVars*, EntityBase*, float, int>;

    // ApplyMultiDamage hook
    using ReHookApplyMultiDamage = IHookChain<void, EntityVars*, EntityVars*>;
    using ReHookRegistryApplyMultiDamage = IHookChainRegistry<void, EntityVars*, EntityVars*>;

    // BuyItem hook
    using ReHookBuyItem = IHookChain<void, PlayerBase*, int>;
    using ReHookRegistryBuyItem = IHookChainRegistry<void, PlayerBase*, int>;

    // CHalfLifeMultiplay::Think hook
    using ReHookGameRulesThink = IHookChain<void>;
    using ReHookRegistryGameRulesThink = IHookChainRegistry<void>;

    // CHalfLifeMultiplay::TeamFull hook
    using ReHookGameRulesTeamFull = IHookChain<qboolean, int>;
    using ReHookRegistryGameRulesTeamFull = IHookChainRegistry<qboolean, int>;

    // CHalfLifeMultiplay::TeamStacked hook
    using ReHookGameRulesTeamStacked = IHookChain<qboolean, int, int>;
    using ReHookRegistryGameRulesTeamStacked = IHookChainRegistry<qboolean, int, int>;

    // CHalfLifeMultiplay::PlayerGotWeapon hook
    using ReHookGameRulesPlayerGotWeapon = IHookChain<void, PlayerBase*, PlayerItemBase*>;
    using ReHookRegistryGameRulesPlayerGotWeapon = IHookChainRegistry<void, PlayerBase*, PlayerItemBase*>;

    // CHalfLifeMultiplay::SendDeathMessage hook
    using ReHookGameRulesSendDeathMessage = IHookChain<void, EntityBase*, PlayerBase*, PlayerBase*, EntityVars*, const char*, int, int>;
    using ReHookRegistryGameRulesSendDeathMessage = IHookChainRegistry<void, EntityBase*, PlayerBase*, PlayerBase*, EntityVars*, const char*, int, int>;

    // CBotManager::OnEvent hook
    using ReHookBotManagerOnEvent = IHookChain<void, GameEventType, EntityBase*, EntityBase*>;
    using ReHookRegistryBotManagerOnEvent = IHookChainRegistry<void, GameEventType, EntityBase*, EntityBase*>;

    // CBasePlayer::CheckTimeBasedDamage hook
    using ReHookPlayerCheckTimeBasedDamage = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerCheckTimeBasedDamage = IHookChainClassRegistry<void, PlayerBase>;

    // CBasePlayer::EntSelectSpawnPoint hook
    using ReHookPlayerEntSelectSpawnPoint = IHookChainClass<Edict*, PlayerBase>;
    using ReHookRegistryPlayerEntSelectSpawnPoint = IHookChainClassRegistry<Edict*, PlayerBase>;

    // CBasePlayerWeapon::ItemPostFrame hook
    using ReHookPlayerWeaponItemPostFrame = IHookChainClass<void, PlayerWeaponBase>;
    using ReHookRegistryPlayerWeaponItemPostFrame = IHookChainClassRegistry<void, PlayerWeaponBase>;

    // CBasePlayerWeapon::KickBack hook
    using ReHookPlayerWeaponKickBack = IHookChainClass<void, PlayerWeaponBase, float, float, float, float, float, float, int>;
    using ReHookRegistryPlayerWeaponKickBack = IHookChainClassRegistry<void, PlayerWeaponBase, float, float, float, float, float, float, int>;

    // CBasePlayerWeapon::SendWeaponAnim hook
    using ReHookPlayerWeaponSendWeaponAnim = IHookChainClass<void, PlayerWeaponBase, int, int>;
    using ReHookRegistryPlayerWeaponSendWeaponAnim = IHookChainClassRegistry<void, PlayerWeaponBase, int, int>;

    // CBasePlayer::PlayerDeathThink hook
    using ReHookPlayerDeathThink = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerDeathThink = IHookChainClassRegistry<void, PlayerBase>;

    // CBasePlayer::Observer_Think hook
    using ReHookPlayerObserverThink = IHookChainClass<void, PlayerBase>;
    using ReHookRegistryPlayerObserverThink = IHookChainClassRegistry<void, PlayerBase>;

    class IReGameDllHookChains // NOLINT(cppcoreguidelines-special-member-functions)
    {
      public:
        virtual ~IReGameDllHookChains() = default;

        virtual ReHookRegistryPlayerSpawn* PlayerSpawn() = 0;
        virtual ReHookRegistryPlayerPrecache* PlayerPrecache() = 0;
        virtual ReHookRegistryPlayerObjectCaps* PlayerObjectCaps() = 0;
        virtual ReHookRegistryPlayerClassify* PlayerClassify() = 0;
        virtual ReHookRegistryPlayerTraceAttack* PlayerTraceAttack() = 0;
        virtual ReHookRegistryPlayerTakeDamage* PlayerTakeDamage() = 0;
        virtual ReHookRegistryPlayerTakeHealth* PlayerTakeHealth() = 0;
        virtual ReHookRegistryPlayerKilled* PlayerKilled() = 0;
        virtual ReHookRegistryPlayerAddPoints* PlayerAddPoints() = 0;
        virtual ReHookRegistryPlayerAddPointsToTeam* PlayerAddPointsToTeam() = 0;
        virtual ReHookRegistryPlayerAddPlayerItem* PlayerAddPlayerItem() = 0;
        virtual ReHookRegistryPlayerRemovePlayerItem* PlayerRemovePlayerItem() = 0;
        virtual ReHookRegistryPlayerGiveAmmo* PlayerGiveAmmo() = 0;
        virtual ReHookRegistryPlayerResetMaxSpeed* PlayerResetMaxSpeed() = 0;
        virtual ReHookRegistryPlayerJump* PlayerJump() = 0;
        virtual ReHookRegistryPlayerDuck* PlayerDuck() = 0;
        virtual ReHookRegistryPlayerPreThink* PlayerPreThink() = 0;
        virtual ReHookRegistryPlayerPostThink* PlayerPostThink() = 0;
        virtual ReHookRegistryPlayerUpdateClientData* PlayerUpdateClientData() = 0;
        virtual ReHookRegistryPlayerImpulseCommands* PlayerImpulseCommands() = 0;
        virtual ReHookRegistryPlayerRoundRespawn* PlayerRoundRespawn() = 0;
        virtual ReHookRegistryPlayerBaseBlind* PlayerBaseBlind() = 0;
        virtual ReHookRegistryPlayerObserverIsValidTarget* PlayerObserverIsValidTarget() = 0;
        virtual ReHookRegistryPlayerSetAnimation* PlayerSetAnimation() = 0;
        virtual ReHookRegistryPlayerGiveDefaultItems* PlayerGiveDefaultItems() = 0;
        virtual ReHookRegistryPlayerGiveNamedItem* PlayerGiveNamedItem() = 0;
        virtual ReHookRegistryPlayerAddAccount* PlayerAddAccount() = 0;
        virtual ReHookRegistryPlayerGiveShield* PlayerGiveShield() = 0;
        virtual ReHookRegistryPlayerSetClientUserInfoModel* PlayerSetClientUserInfoModel() = 0;
        virtual ReHookRegistryPlayerSetClientUserInfoName* PlayerSetClientUserInfoName() = 0;
        virtual ReHookRegistryPlayerHasRestrictItem* PlayerHasRestrictItem() = 0;
        virtual ReHookRegistryPlayerDropPlayerItem* PlayerDropPlayerItem() = 0;
        virtual ReHookRegistryPlayerDropShield* PlayerDropShield() = 0;
        virtual ReHookRegistryPlayerOnSpawnEquip* PlayerOnSpawnEquip() = 0;
        virtual ReHookRegistryPlayerRadio* PlayerRadio() = 0;
        virtual ReHookRegistryPlayerDisappear* PlayerDisappear() = 0;
        virtual ReHookRegistryPlayerMakeVip* PlayerMakeVip() = 0;
        virtual ReHookRegistryPlayerMakeBomber* PlayerMakeBomber() = 0;
        virtual ReHookRegistryPlayerStartObserver* PlayerStartObserver() = 0;
        virtual ReHookRegistryPlayerGetIntoGame* PlayerGetIntoGame() = 0;
        virtual ReHookRegistryAnimatingResetSequenceInfo* AnimatingResetSequenceInfo() = 0;
        virtual ReHookRegistryGetForceCamera* GetForceCamera() = 0;
        virtual ReHookRegistryPlayerBlind* PlayerBlind() = 0;
        virtual ReHookRegistryRadiusFlashTraceLine* RadiusFlashTraceLine() = 0;
        virtual ReHookRegistryRoundEnd* RoundEnd() = 0;
        virtual ReHookRegistryInstallGameRules* InstallGameRules() = 0;
        virtual ReHookRegistryPmInit* PmInit() = 0;
        virtual ReHookRegistryPmMove* PmMove() = 0;
        virtual ReHookRegistryPmAirMove* PmAirMove() = 0;
        virtual ReHookRegistryHandleMenuChooseAppearance* HandleMenuChooseAppearance() = 0;
        virtual ReHookRegistryHandleMenuChooseTeam* HandleMenuChooseTeam() = 0;
        virtual ReHookRegistryShowMenu* ShowMenu() = 0;
        virtual ReHookRegistryShowVguiMenu* ShowVguiMenu() = 0;
        virtual ReHookRegistryBuyGunAmmo* BuyGunAmmo() = 0;
        virtual ReHookRegistryBuyWeaponByWeaponId* BuyWeaponByWeaponId() = 0;
        virtual ReHookRegistryInternalCommand* InternalCommand() = 0;
        virtual ReHookRegistryGameRulesShouldSwitchWeapon* GameRulesShouldSwitchWeapon() = 0;
        virtual ReHookRegistryGameRulesGetNextBestWeapon* GameRulesGetNextBestWeapon() = 0;
        virtual ReHookRegistryGameRulesPlayerFallDamage* GameRulesPlayerFallDamage() = 0;
        virtual ReHookRegistryGameRulesPlayerCanTakeDamage* GameRulesPlayerCanTakeDamage() = 0;
        virtual ReHookRegistryGameRulesPlayerSpawn* GameRulesPlayerSpawn() = 0;
        virtual ReHookRegistryGameRulesPlayerCanRespawn* GameRulesPlayerCanRespawn() = 0;
        virtual ReHookRegistryGameRulesGetPlayerSpawnSpot* GameRulesGetPlayerSpawnSpot() = 0;
        virtual ReHookRegistryGameRulesClientUserInfoChanged* GameRulesClientUserInfoChanged() = 0;
        virtual ReHookRegistryGameRulesPlayerKilled* GameRulesPlayerKilled() = 0;
        virtual ReHookRegistryGameRulesDeathNotice* GameRulesDeathNotice() = 0;
        virtual ReHookRegistryGameRulesCanHavePlayerItem* GameRulesCanHavePlayerItem() = 0;
        virtual ReHookRegistryGameRulesDeadPlayerWeapons* GameRulesDeadPlayerWeapons() = 0;
        virtual ReHookRegistryGameRulesServerDeactivate* GameRulesServerDeactivate() = 0;
        virtual ReHookRegistryGameRulesCheckMapConditions* GameRulesCheckMapConditions() = 0;
        virtual ReHookRegistryGameRulesCleanUpMap* GameRulesCleanUpMap() = 0;
        virtual ReHookRegistryGameRulesRestartRound* GameRulesRestartRound() = 0;
        virtual ReHookRegistryGameRulesCheckWinConditions* GameRulesCheckWinConditions() = 0;
        virtual ReHookRegistryGameRulesRemoveGuns* GameRulesRemoveGuns() = 0;
        virtual ReHookRegistryGameRulesGiveC4* GameRulesGiveC4() = 0;
        virtual ReHookRegistryGameRulesChangeLevel* GameRulesChangeLevel() = 0;
        virtual ReHookRegistryGameRulesGoToIntermission* GameRulesGoToIntermission() = 0;
        virtual ReHookRegistryGameRulesBalanceTeams* GameRulesBalanceTeams() = 0;
        virtual ReHookRegistryGameRulesOnRoundFreezeEnd* GameRulesOnRoundFreezeEnd() = 0;
        virtual ReHookRegistryPmUpdateStepSound* PmUpdateStepSound() = 0;
        virtual ReHookRegistryPlayerStartDeathCam* PlayerStartDeathCam() = 0;
        virtual ReHookRegistryPlayerSwitchTeam* PlayerSwitchTeam() = 0;
        virtual ReHookRegistryPlayerCanSwitchTeam* PlayerCanSwitchTeam() = 0;
        virtual ReHookRegistryPlayerThrowGrenade* PlayerThrowGrenade() = 0;
        virtual ReHookRegistryGameRulesCanPlayerHearPlayer* GameRulesCanPlayerHearPlayer() = 0;
        virtual ReHookRegistryWeaponBoxSetModel* WeaponBoxSetModel() = 0;
        virtual ReHookRegistryGrenadeDefuseBombStart* GrenadeDefuseBombStart() = 0;
        virtual ReHookRegistryGrenadeDefuseBombEnd* GrenadeDefuseBombEnd() = 0;
        virtual ReHookRegistryGrenadeExplodeHeGrenade* GrenadeExplodeHeGrenade() = 0;
        virtual ReHookRegistryGrenadeExplodeFlashBang* GrenadeExplodeFlashBang() = 0;
        virtual ReHookRegistryGrenadeExplodeSmokeGrenade* GrenadeExplodeSmokeGrenade() = 0;
        virtual ReHookRegistryGrenadeExplodeBomb* GrenadeExplodeBomb() = 0;
        virtual ReHookRegistryThrowHeGrenade* ThrowHeGrenade() = 0;
        virtual ReHookRegistryThrowFlashBang* ThrowFlashBang() = 0;
        virtual ReHookRegistryThrowSmokeGrenade* ThrowSmokeGrenade() = 0;
        virtual ReHookRegistryPlantBomb* PlantBomb() = 0;
        virtual ReHookRegistryPlayerRemoveSpawnProtection* PlayerRemoveSpawnProtection() = 0;
        virtual ReHookRegistryPlayerSetSpawnProtection* PlayerSetSpawnProtection() = 0;
        virtual ReHookRegistryIsPenetrableEntity* IsPenetrableEntity() = 0;
        virtual ReHookRegistryPlayerHintMessageEx* PlayerHintMessageEx() = 0;
        virtual ReHookRegistryPlayerUseEmpty* PlayerUseEmpty() = 0;
        virtual ReHookRegistryPlayerWeaponCanDeploy* PlayerBaseWeaponCanDeploy() = 0;
        virtual ReHookRegistryPlayerWeaponDefaultDeploy* PlayerBaseWeaponDefaultDeploy() = 0;
        virtual ReHookRegistryPlayerWeaponDefaultReload* PlayerBaseWeaponDefaultReload() = 0;
        virtual ReHookRegistryPlayerWeaponDefaultShotgunReload* PlayerBaseWeaponDefaultShotgunReload() = 0;
        virtual ReHookRegistryPlayerDropIdlePlayer* PlayerDropIdlePlayer() = 0;
        virtual ReHookRegistryCreateWeaponBox* CreateWeaponBox() = 0;
        virtual ReHookRegistrySpawnHeadGib* SpawnHeadGib() = 0;
        virtual ReHookRegistrySpawnRandomGibs* SpawnRandomGibs() = 0;
        virtual ReHookRegistryGibSpawn* GibSpawn() = 0;
        virtual ReHookRegistryGibBounceGibTouch* GibBounceGibTouch() = 0;
        virtual ReHookRegistryGibWaitTillLand* GibWaitTillLand() = 0;
        virtual ReHookRegistryEntityBaseFireBullets* EntityBaseFireBullets() = 0;
        virtual ReHookRegistryEntityBaseFireBuckshots* EntityBaseFireBuckshots() = 0;
        virtual ReHookRegistryEntityBaseFireBullets3* EntityBaseFireBullets3() = 0;
        virtual ReHookRegistryPlayerObserverSetMode* PlayerObserverSetMode() = 0;
        virtual ReHookRegistryPlayerObserverFindNextPlayer* PlayerObserverFindNextPlayer() = 0;
        virtual ReHookRegistryPlayerPain* PlayerPain() = 0;
        virtual ReHookRegistryPlayerDeathSound* PlayerDeathSound() = 0;
        virtual ReHookRegistryPlayerJoiningThink* PlayerJoiningThink() = 0;
        virtual ReHookRegistryFreeGameRules* FreeGameRules() = 0;
        virtual ReHookRegistryPmLadderMove* PmLadderMove() = 0;
        virtual ReHookRegistryPmWaterJump* PmWaterJump() = 0;
        virtual ReHookRegistryPmCheckWaterJump* PmCheckWaterJump() = 0;
        virtual ReHookRegistryPmJump* PmJump() = 0;
        virtual ReHookRegistryPmDuck* PmDuck() = 0;
        virtual ReHookRegistryPmUnDuck* PmUnDuck() = 0;
        virtual ReHookRegistryPmPlayStepSound* PmPlayStepSound() = 0;
        virtual ReHookRegistryPmAirAccelerate* PmAirAccelerate() = 0;
        virtual ReHookRegistryClearMultiDamage* ClearMultiDamage() = 0;
        virtual ReHookRegistryAddMultiDamage* AddMultiDamage() = 0;
        virtual ReHookRegistryApplyMultiDamage* ApplyMultiDamage() = 0;
        virtual ReHookRegistryBuyItem* BuyItem() = 0;
        virtual ReHookRegistryGameRulesThink* GameRulesThink() = 0;
        virtual ReHookRegistryGameRulesTeamFull* GameRulesTeamFull() = 0;
        virtual ReHookRegistryGameRulesTeamStacked* GameRulesTeamStacked() = 0;
        virtual ReHookRegistryGameRulesPlayerGotWeapon* GameRulesPlayerGotWeapon() = 0;
        virtual ReHookRegistryBotManagerOnEvent* BotManagerOnEvent() = 0;
        virtual ReHookRegistryPlayerCheckTimeBasedDamage* PlayerCheckTimeBasedDamage() = 0;
        virtual ReHookRegistryPlayerEntSelectSpawnPoint* PlayerEntSelectSpawnPoint() = 0;
        virtual ReHookRegistryPlayerWeaponItemPostFrame* PlayerWeaponItemPostFrame() = 0;
        virtual ReHookRegistryPlayerWeaponKickBack* PlayerWeaponKickBack() = 0;
        virtual ReHookRegistryPlayerWeaponSendWeaponAnim* PlayerWeaponSendWeaponAnim() = 0;
        virtual ReHookRegistryGameRulesSendDeathMessage* GameRulesSendDeathMessage() = 0;
        virtual ReHookRegistryPlayerDeathThink* PlayerDeathThink() = 0;
        virtual ReHookRegistryPlayerObserverThink* PlayerObserverThink() = 0;
    };

    struct RegamedllFuncs {
        Edict* (* create_named_entity2)(Strind class_name){};
        void (* change_string)(char*& dest, const char* source){};
        void (* radius_damage)(
            Vector src,
            EntityVars* inflictor,
            EntityVars* attacker,
            float damage,
            float radius,
            int classIgnore,
            int damageType
        ){};
        void (* clear_multi_damage)(){};
        void (* apply_multi_damage)(EntityVars* inflictor, EntityVars* attacker){};
        void (* add_multi_damage)(EntityVars* inflictor, EntityBase* entity, float damage, int damage_type){};
        EntityBase* (* find_entity_by_string)(EntityBase* start_entity, const char* keyword, const char* value){};
        void (* add_entity_hash_value)(EntityVars* ent_vars, const char* value, HashType field_type){};
        void (* remove_entity_hash_value)(EntityVars* ent_vars, const char* value, HashType field_type){};
        int (* cmd_argc)(){};
        const char* (* cmd_argv)(int i){};
        Grenade* (* plant_bomb)(EntityVars* owner, Vector& start, Vector& velocity){};
        Gib* (* spawn_head_gib)(EntityVars* victim){};
        void (* spawn_random_gibs)(EntityVars* victim, int gibs, int human){};
        void (* util_restart_other)(const char* classname){};
        void (* util_reset_entities)(){};
        void (* util_remove_other)(const char* classname, int count){};
        void (* util_decal_trace)(TraceResult* trace, int decalNumber){};
        void (* util_remove)(EntityBase* entity){};
        int (* add_ammo_name_to_ammo_registry)(const char* ammoName){};
        void (* texture_type_play_sound)(TraceResult* trace, Vector src, Vector end, int bulletType){};
        WeaponBox* (* create_weapon_box)(
            PlayerItemBase* item,
            PlayerBase* owner,
            const char* modelName,
            Vector& origin,
            Vector& angles,
            Vector& velocity,
            float lifeTime,
            bool packAmmo
        ){};
        Grenade* (* spawn_grenade)(
            WeaponId weaponId,
            EntityVars* owner,
            Vector& src,
            Vector& direction,
            float time,
            int team,
            unsigned short usEvent
        ){};
    };

    class IReGameDllApi // NOLINT(cppcoreguidelines-special-member-functions)
    {
      public:
        virtual ~IReGameDllApi() = default;
        virtual int GetMajorVersion() = 0;
        virtual int GetMinorVersion() = 0;
        virtual const RegamedllFuncs* GetFuncs() = 0;
        virtual IReGameDllHookChains* GetHookChains() = 0;
        virtual GameRulesBase* GetGameRules() = 0;
        virtual WeaponInfoStruct* GetWeaponInfo(WeaponId weapon) = 0;
        virtual WeaponInfoStruct* GetWeaponInfo(const char* weapon) = 0;
        virtual PlayerMove* GetPlayerMove() = 0;
        virtual WeaponSlotInfo* GetWeaponSlot(WeaponId weapon) = 0;
        virtual WeaponSlotInfo* GetWeaponSlot(const char* weapon) = 0;
        virtual ItemInfo* GetItemInfo(WeaponId weapon) = 0;
        virtual AmmoInfo* GetAmmoInfo(AmmoType ammo) = 0;
        virtual AmmoInfoStruct* GetAmmoInfoEx(AmmoType ammo) = 0;
        virtual AmmoInfoStruct* GetAmmoInfoEx(const char* ammo) = 0;
        virtual bool CheckCsEntityVersion(const char* version) const = 0;
        virtual bool CheckGameRulesVersion(const char* version) const = 0;
    };
}
