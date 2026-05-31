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

#include <cssdk/dll/ammo.h>
#include <cssdk/dll/items.h>
#include <cssdk/game_shared/voice_manager.h>

namespace cssdk
{
    class HalfLifeMultiplay;

    /**
     * @brief N/D
    */
    constexpr auto GAME_RULES_API_INTERFACE_VERSION = "GAMERULES_API_INTERFACE_VERSION001";

    /**
     * @brief N/D
    */
    constexpr auto MAX_RULE_BUFFER = 1024;

    /**
     * @brief N/D
    */
    constexpr auto MAX_VOTE_MAPS = 100;

    /**
     * @brief N/D
    */
    constexpr auto MAX_VIP_QUEUES = 5;

    /**
     * @brief Allowable money limit in the game that can be drawn on the HUD.
    */
    constexpr auto MAX_MONEY_THRESHOLD = 999999;

    /**
     * @brief N/D
    */
    constexpr auto MAX_MOTD_CHUNK = 60;

    /**
     * @brief (MAX_MOTD_CHUNK * 4)
    */
    constexpr auto MAX_MOTD_LENGTH = 1536;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_RESPAWN_TIME = 30.0f;

    /**
     * @brief N/D
    */
    constexpr auto WEAPON_RESPAWN_TIME = 20.0f;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_RESPAWN_TIME = 20.0f;

    /**
     * @brief N/D
    */
    constexpr auto ROUND_RESPAWN_TIME = 20.0f;

    /**
     * @brief Delay before beginning new round.
    */
    constexpr auto ROUND_BEGIN_DELAY = 5.0f;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_KILL_DELAY = 300.0f;

    /**
     * @brief N/D
    */
    constexpr auto RADIO_TIMEOUT = 1.5f;

    /**
     * @brief Longest the intermission can last, in seconds.
    */
    constexpr auto MAX_INTERMISSION_TIME = 120;

    /**
     * @brief When we are within this close to running out of entities,
     * items marked with the ITEM_FLAG_LIMIT_IN_WORLD will delay their respawn.
    */
    constexpr auto ENTITY_INTOLERANCE = 100;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_TARGET_BOMB = 3500;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_VIP_ESCAPED = 3500;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_VIP_ASSASSINATED = 3250;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_TERRORISTS_ESCAPED = 3150;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_CTS_PREVENT_ESCAPE = 3500;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_ESCAPING_TERRORISTS_NEUTRALIZED = 3250;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_BOMB_DEFUSED = 3250;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_BOMB_PLANTED = 800;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_BOMB_EXPLODED = 3250;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_CTS_WIN = 3000;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_TERRORISTS_WIN = 3000;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_ALL_HOSTAGES_RESCUED = 2500;

    /**
     * @brief The end round was by the expiration time.
    */
    constexpr auto REWARD_TARGET_BOMB_SAVED = 3250;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_HOSTAGE_NOT_RESCUED = 3250;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_VIP_NOT_ESCAPED = 3250;

    /**
     * @brief Loser bonus.
    */
    constexpr auto REWARD_LOSER_BONUS_DEFAULT = 1400;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_LOSER_BONUS_MIN = 1500;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_LOSER_BONUS_MAX = 3000;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_LOSER_BONUS_ADD = 500;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_RESCUED_HOSTAGE = 750;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_KILLED_ENEMY = 300;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_KILLED_VIP = 2500;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_VIP_HAVE_SELF_RESCUED = 2500;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_TAKEN_HOSTAGE = 1000;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_TOOK_HOSTAGE_ACC = 100;

    /**
     * @brief N/D
    */
    constexpr auto REWARD_TOOK_HOSTAGE = 150;

    /**
     * @brief N/D
    */
    constexpr auto PAYBACK_FOR_KILLED_TEAMMATES = -3300;

    /**
     * @brief Flag "a".
    */
    constexpr auto SCENARIO_BLOCK_TIME_EXPIRED = 1 << 0;

    /**
     * @brief Flag "b".
    */
    constexpr auto SCENARIO_BLOCK_NEED_PLAYERS = 1 << 1;

    /**
     * @brief Flag "c".
    */
    constexpr auto SCENARIO_BLOCK_VIP_ESCAPE = 1 << 2;

    /**
     * @brief Flag "d".
    */
    constexpr auto SCENARIO_BLOCK_PRISON_ESCAPE = 1 << 3;

    /**
     * @brief Flag "e".
    */
    constexpr auto SCENARIO_BLOCK_BOMB = 1 << 4;

    /**
     * @brief Flag "f".
    */
    constexpr auto SCENARIO_BLOCK_TEAM_EXTERMINATION = 1 << 5;

    /**
     * @brief Flag "g".
    */
    constexpr auto SCENARIO_BLOCK_HOSTAGE_RESCUE = 1 << 6;

    /**
     * @brief Flag "h".
    */
    constexpr auto SCENARIO_BLOCK_VIP_ESCAPE_TIME = 1 << 7;

    /**
     * @brief Flag "i".
    */
    constexpr auto SCENARIO_BLOCK_PRISON_ESCAPE_TIME = 1 << 8;

    /**
     * @brief Flag "j".
    */
    constexpr auto SCENARIO_BLOCK_BOMB_TIME = 1 << 9;

    /**
     * @brief Flag "k".
    */
    constexpr auto SCENARIO_BLOCK_HOSTAGE_RESCUE_TIME = 1 << 10;

    enum class WinStatus
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        Cts,

        /**
         * @brief N/D
        */
        Terrorists,

        /**
         * @brief N/D
        */
        Draw
    };

    /**
     * @brief Used for \c end_round_message() logged messages.
    */
    enum class ScenarioEventEndRound
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        TargetBomb,

        /**
         * @brief N/D
        */
        VipEscaped,

        /**
         * @brief N/D
        */
        VipAssassinated,

        /**
         * @brief N/D
        */
        TerroristsEscaped,

        /**
         * @brief N/D
        */
        CtsPreventEscape,

        /**
         * @brief N/D
        */
        EscapingTerroristsNeutralized,

        /**
         * @brief N/D
        */
        BombDefused,

        /**
         * @brief N/D
        */
        CtsWin,

        /**
         * @brief N/D
        */
        TerroristsWin,

        /**
         * @brief N/D
        */
        EndDraw,

        /**
         * @brief N/D
        */
        AllHostagesRescued,

        /**
         * @brief N/D
        */
        TargetSaved,

        /**
         * @brief N/D
        */
        HostageNotRescued,

        /**
         * @brief N/D
        */
        TerroristsNotEscaped,

        /**
         * @brief N/D
        */
        VipNotEscaped,

        /**
         * @brief N/D
        */
        GameCommence,

        /**
         * @brief N/D
        */
        GameRestart,

        /**
         * @brief N/D
        */
        GameOver
    };

    enum class RewardRules
    {
        /**
         * @brief N/D
        */
        CtsWin = 0,

        /**
         * @brief N/D
        */
        TerroristsWin,

        /**
         * @brief N/D
        */
        TargetBomb,

        /**
         * @brief N/D
        */
        VipEscaped,

        /**
         * @brief N/D
        */
        VipAssassinated,

        /**
         * @brief N/D
        */
        TerroristsEscaped,

        /**
         * @brief N/D
        */
        CtsPreventEscape,

        /**
         * @brief N/D
        */
        EscapingTerroristsNeutralized,

        /**
         * @brief N/D
        */
        BombDefused,

        /**
         * @brief N/D
        */
        BombPlanted,

        /**
         * @brief N/D
        */
        BombExploded,

        /**
         * @brief N/D
        */
        AllHostagesRescued,

        /**
         * @brief N/D
        */
        TargetBombSaved,

        /**
         * @brief N/D
        */
        HostageNotRescued,

        /**
         * @brief N/D
        */
        VipNotEscaped,

        /**
         * @brief N/D
        */
        LoserBonusDefault,

        /**
         * @brief N/D
        */
        LoserBonusMin,

        /**
         * @brief N/D
        */
        LoserBonusMax,

        /**
         * @brief N/D
        */
        LoserBonusAdd,

        /**
         * @brief N/D
        */
        RescuedHostage,

        /**
         * @brief N/D
        */
        TookHostageAcc,

        /**
         * @brief N/D
        */
        TookHostage,

        /**
         * @brief N/D
        */
        End
    };

    enum InfoMapBuyParam
    {
        /**
         * @brief N/D
        */
        Everyone = 0,

        /**
         * @brief N/D
        */
        OnlyCts,

        /**
         * @brief N/D
        */
        OnlyTerrorists,

        /**
         * @brief N/D
        */
        NoOne
    };

    /**
     * @brief Weapon respawning return codes.
    */
    enum class WeaponRespawnCode
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        WeaponRespawnYes,

        /**
         * @brief N/D
        */
        WeaponRespawnNo,

        /**
         * @brief N/D
        */
        AmmoRespawnYes,

        /**
         * @brief N/D
        */
        AmmoRespawnNo,

        /**
         * @brief N/D
        */
        ItemRespawnYes,

        /**
         * @brief N/D
        */
        ItemRespawnNo,

        /**
         * @brief N/D
        */
        PlrDropGunAll,

        /**
         * @brief N/D
        */
        PlrDropGunActive,

        /**
         * @brief N/D
        */
        PlrDropGunNo,

        /**
         * @brief N/D
        */
        PlrDropAmmoAll,

        /**
         * @brief N/D
        */
        PlrDropAmmoActive,

        /**
         * @brief N/D
        */
        PlrDropAmmoNo
    };

    /**
     * @brief Player relationship return codes.
    */
    enum class PlayerRelationship
    {
        /**
         * @brief N/D
        */
        NotTeammate = 0,

        /**
         * @brief N/D
        */
        Teammate,

        /**
         * @brief N/D
        */
        Enemy,

        /**
         * @brief N/D
        */
        Ally,

        /**
         * @brief N/D
        */
        Neutral
    };

    class GameRulesBase // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        virtual ~GameRulesBase() = default;

        /**
         * @brief Fill skill data struct with proper values.
        */
        virtual void RefreshSkillData() = 0;

        /**
         * @brief Runs every server frame, should handle any timer tasks, periodic events, etc.
        */
        virtual void Think() = 0;

        /**
         * @brief Can this item spawn (eg monsters don't spawn in deathmatch).
        */
        virtual qboolean IsAllowedToSpawn(EntityBase* entity) = 0;

        /**
         * @brief Are players allowed to switch on their flashlight?
        */
        virtual qboolean AllowFlashlight() = 0;

        /**
         * @brief Should the player switch to this weapon?
        */
        virtual qboolean ShouldSwitchWeapon(PlayerBase* player, PlayerItemBase* weapon) = 0;

        /**
         * @brief I can't use this weapon anymore, get me the next best one.
        */
        virtual qboolean GetNextBestWeapon(PlayerBase* player, PlayerItemBase* current_weapon) = 0;

        //
        // Functions to verify the single/multiplayer status of a game.
        //

        /**
         * @brief Is this a multiplayer game (either coop or deathmatch)?
        */
        virtual qboolean IsMultiplayer() = 0;

        /**
         * @brief Is this a deathmatch game?
        */
        virtual qboolean IsDeathmatch() = 0;

        /**
         * @brief Is this deathmatch game being played with team rules?
        */
        virtual qboolean IsTeamplay() = 0;

        /**
         * @brief Is this a coop game?
        */
        virtual qboolean IsCoop() = 0;

        /**
         * @brief This is the game name that gets seen in the server browser.
        */
        virtual const char* GetGameDescription() = 0;

        //
        // Client connection/disconnection.
        //

        /**
         * @brief A client just connected to the server (player hasn't spawned yet).
        */
        virtual qboolean ClientConnected(Edict* entity, const char* name, const char* address, char* reject_reason) = 0;

        /**
         * @brief The client dll is ready for updating.
        */
        virtual void InitHud(PlayerBase* player) = 0;

        /**
         * @brief A client just disconnected from the server.
        */
        virtual void ClientDisconnected(Edict* client) = 0;

        /**
         * @brief The client needs to be informed of the current game mode.
        */
        virtual void UpdateGameMode(PlayerBase* player) = 0;

        //
        // Client damage rules.
        //

        /**
         * @brief N/D
        */
        virtual float PlayerFallDamage(PlayerBase* player) = 0;

        /**
         * @brief Can this player take damage from this attacker?
        */
        virtual qboolean PlayerCanTakeDamage(PlayerBase* player, EntityBase* attacker) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean ShouldAutoAim(PlayerBase* player, Edict* target) = 0;

        //
        // Client spawn/respawn control.
        //

        /**
         * @brief Called by \c PlayerBase::spawn just before releasing player into the game.
        */
        virtual void PlayerSpawn(PlayerBase* player) = 0;

        /**
         * @brief Called by \c PlayerBase::pre_think every frame, before physics are run and after keys are accepted.
        */
        virtual void PlayerThink(PlayerBase* player) = 0;

        /**
         * @brief Is this player allowed to respawn now?
        */
        virtual qboolean PlayerCanRespawn(PlayerBase* player) = 0;

        /**
         * @brief When in the future will this player be able to spawn?
        */
        virtual float PlayerSpawnTime(PlayerBase* player) = 0;

        /**
         * @brief Place this player on their spawn spot and face them the proper direction.
        */
        virtual Edict* GetPlayerSpawnSpot(PlayerBase* player) = 0;

        //
        //
        //

        /**
         * @brief N/D
        */
        virtual qboolean AllowAutoTargetCrosshair() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean ClientCommandDeadOrAlive(PlayerBase* player, const char* cmd) = 0;

        /**
         * @brief Handles the user commands; returns TRUE if command handled properly.
        */
        virtual qboolean ClientCommand(PlayerBase* player, const char* cmd) = 0;

        /**
         * @brief The player has changed user info; can change it now.
        */
        virtual void ClientUserInfoChanged(PlayerBase* player, char* info_buffer) = 0;

        //
        // Client kills/scoring.
        //

        /**
         * @brief How many points do I award whoever kills this player?
        */
        virtual int PointsForKill(PlayerBase* attacker, PlayerBase* killed) = 0;

        /**
         * @brief Called each time a player dies.
        */
        virtual void PlayerKilled(PlayerBase* victim, EntityVars* killer, EntityVars* inflictor) = 0;

        /**
         * @brief Call this from within a GameRules class to report an obituary.
        */
        virtual void DeathNotice(PlayerBase* victim, EntityVars* killer, EntityVars* inflictor) = 0;

        //
        // Weapon retrieval.
        //

        /**
         * @brief The player is touching an PlayerItemBase, do I give it to him?
        */
        virtual qboolean CanHavePlayerItem(PlayerBase* player, PlayerItemBase* item) = 0;

        /**
         * @brief Called each time a player picks up a weapon from the ground.
        */
        virtual void PlayerGotWeapon(PlayerBase* player, PlayerItemBase* weapon) = 0;

        //
        // Weapon spawn/respawn control.
        //

        /**
         * @brief Should this weapon respawn?.
        */
        virtual WeaponRespawnCode WeaponShouldRespawn(PlayerItemBase* weapon) = 0;

        /**
         * @brief When may this weapon respawn?
        */
        virtual float WeaponRespawnTime(PlayerItemBase* weapon) = 0;

        /**
         * @brief Can i respawn now, and if not, when should I try again?
        */
        virtual float WeaponTryRespawn(PlayerItemBase* weapon) = 0;

        /**
         * @brief Where in the world should this weapon respawn?
        */
        virtual Vector WeaponRespawnSpot(PlayerItemBase* weapon) = 0;

        //
        // Item retrieval.
        //

        /**
         * @brief Is this player allowed to take this item?
        */
        virtual qboolean CanHaveItem(PlayerBase* player, Item* item) = 0;

        /**
         * @brief Call each time a player picks up an item (battery, health kit, long jump).
        */
        virtual void PlayerGotItem(PlayerBase* player, Item* item) = 0;

        //
        // Item spawn/respawn control.
        //

        /**
         * @brief Should this item respawn?
        */
        virtual WeaponRespawnCode ItemShouldRespawn(Item* item) = 0;

        /**
         * @brief When may this item respawn?
        */
        virtual float ItemRespawnTime(Item* item) = 0;

        /**
         * @brief Where in the world should this item respawn?
        */
        virtual Vector ItemRespawnSpot(Item* item) = 0;

        //
        // Ammo retrieval.
        //

        /**
         * @brief Can this player take more of this ammo?
        */
        virtual qboolean CanHaveAmmo(PlayerBase* player, const char* ammo_name, int max_carry) = 0;

        /**
         * @brief Called each time a player picks up some ammo in the world.
        */
        virtual void PlayerGotAmmo(PlayerBase* player, char* name, int count) = 0;

        //
        // Ammo spawn/respawn control.
        //

        /**
         * @brief Should this ammo item respawn?
        */
        virtual WeaponRespawnCode AmmoShouldRespawn(PlayerAmmoBase* ammo) = 0;

        /**
         * @brief When should this ammo item respawn?
        */
        virtual float AmmoRespawnTime(PlayerAmmoBase* ammo) = 0;

        /**
         * @brief Where in the world should this ammo item respawn?
        */
        virtual Vector AmmoRespawnSpot(PlayerAmmoBase* ammo) = 0;

        //
        // Health charger respawn control.
        //

        /**
         * @brief How long until a depleted HealthCharger recharges itself?
        */
        virtual float HealthChargerRechargeTime() = 0;

        /**
         * @brief How long until a depleted health_charger recharges itself?
        */
        virtual float HevChargerRechargeTime() = 0;

        //
        // What happens to a dead player's weapons.
        //

        /**
         * @brief What do I do with a player's weapons when he's killed?
        */
        virtual WeaponRespawnCode DeadPlayerWeapons(PlayerBase* player) = 0;

        //
        // What happens to a dead player's ammo.
        //

        /**
         * @brief Do I drop ammo when the player dies? How much?
        */
        virtual WeaponRespawnCode DeadPlayerAmmo(PlayerBase* player) = 0;

        //
        // Teamplay stuff.
        //

        /**
         * @brief What team is this entity on?
        */
        virtual const char* GetTeamId(EntityBase* entity) = 0;

        /**
         * @brief What is the player's relationship with this entity?
        */
        virtual PlayerRelationship GetPlayerRelationship(PlayerBase* player, EntityBase* target) = 0;

        /**
         * @brief N/D
        */
        virtual int GetTeamIndex(const char* team_name) = 0;

        /**
         * @brief N/D
        */
        virtual const char* GetIndexedTeamName(int team_index) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsValidTeam(const char* team_name) = 0;

        /**
         * @brief N/D
        */
        virtual void ChangePlayerTeam(PlayerBase* player, const char* team_name, qboolean kill, qboolean gib) = 0;

        /**
         * @brief N/D
        */
        virtual const char* SetDefaultPlayerTeam(PlayerBase* player) = 0;

        //
        // Sounds.
        //

        /**
         * @brief N/D
        */
        virtual qboolean PlayTextureSounds() = 0;

        //
        // Monsters.
        //

        /**
         * @brief Are monsters allowed.
        */
        virtual qboolean AllowMonsters() = 0;

        /**
         * @brief Immediately end a multiplayer game.
        */
        virtual void EndMultiplayerGame() = 0;

        //
        // Stuff that is shared between client and server.
        //

        /**
         * @brief N/D
        */
        virtual qboolean IsFreezePeriod() = 0;

        /**
         * @brief N/D
        */
        virtual void ServerDeactivate() = 0;

        /**
         * @brief N/D
        */
        virtual void CheckMapConditions() = 0;

        //
        //
        //

        /**
         * @brief N/D
        */
        [[nodiscard]] inline HalfLifeMultiplay* CsGameRules();

        /**
         * @brief N/D
        */
        [[nodiscard]] inline const HalfLifeMultiplay* CsGameRules() const;

        /**
         * @brief TRUE at beginning of round, set to FALSE when the period expires.
        */
        qboolean freeze_period{};

        /**
         * @brief N/D
        */
        qboolean bomb_dropped{};

        /**
         * @brief N/D
        */
        char* game_desc{};

        /**
         * @brief Intermission or finale.
        */
        bool is_game_over{};
    };

    class HalfLifeRules : public GameRulesBase // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        ~HalfLifeRules() override = 0;

        /**
         * @brief N/D
        */
        void Think() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsAllowedToSpawn(EntityBase* entity) override = 0;

        /**
         * @brief N/D
        */
        qboolean AllowFlashlight() override = 0;

        /**
         * @brief N/D
        */
        qboolean ShouldSwitchWeapon(PlayerBase* player, PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        qboolean GetNextBestWeapon(PlayerBase* player, PlayerItemBase* current_weapon) override = 0;

        //
        // Functions to verify the single/multiplayer status of a game.
        //

        /**
         * @brief N/D
        */
        qboolean IsMultiplayer() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsDeathmatch() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsCoop() override = 0;

        //
        // Client connection/disconnection.
        //

        /**
         * @brief N/D
        */
        qboolean ClientConnected(Edict* entity, const char* name, const char* address, char reject_reason[128]) override = 0;

        /**
         * @brief The client dll is ready for updating.
        */
        void InitHud(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        void ClientDisconnected(Edict* client) override = 0;

        //
        // Client damage rules.
        //

        /**
         * @brief N/D
        */
        float PlayerFallDamage(PlayerBase* player) override = 0;

        //
        // Client spawn/respawn control.
        //

        /**
         * @brief N/D
        */
        void PlayerSpawn(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        void PlayerThink(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        qboolean PlayerCanRespawn(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        float PlayerSpawnTime(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        Edict* GetPlayerSpawnSpot(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        qboolean AllowAutoTargetCrosshair() override = 0;

        //
        // Client kills/scoring.
        //

        /**
         * @brief N/D
        */
        int PointsForKill(PlayerBase* attacker, PlayerBase* killed) override = 0;

        /**
         * @brief N/D
        */
        void PlayerKilled(PlayerBase* victim, EntityVars* killer, EntityVars* inflictor) override = 0;

        /**
         * @brief N/D
        */
        void DeathNotice(PlayerBase* victim, EntityVars* killer, EntityVars* inflictor) override = 0;

        //
        // Weapon retrieval.
        //

        /**
         * @brief N/D
        */
        void PlayerGotWeapon(PlayerBase* player, PlayerItemBase* weapon) override = 0;

        //
        // Weapon spawn/respawn control.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode WeaponShouldRespawn(PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        float WeaponRespawnTime(PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        float WeaponTryRespawn(PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        Vector WeaponRespawnSpot(PlayerItemBase* weapon) override = 0;

        //
        // Item retrieval.
        //

        /**
         * @brief N/D
        */
        qboolean CanHaveItem(PlayerBase* player, Item* item) override = 0;

        /**
         * @brief N/D
        */
        void PlayerGotItem(PlayerBase* player, Item* item) override = 0;

        //
        // Item spawn/respawn control.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode ItemShouldRespawn(Item* item) override = 0;

        /**
         * @brief N/D
        */
        float ItemRespawnTime(Item* item) override = 0;

        /**
         * @brief N/D
        */
        Vector ItemRespawnSpot(Item* item) override = 0;

        //
        // Ammo retrieval.
        //

        /**
         * @brief N/D
        */
        void PlayerGotAmmo(PlayerBase* player, char* name, int count) override = 0;

        //
        // Ammo spawn/respawn control.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode AmmoShouldRespawn(PlayerAmmoBase* ammo) override = 0;

        /**
         * @brief N/D
        */
        float AmmoRespawnTime(PlayerAmmoBase* ammo) override = 0;

        /**
         * @brief N/D
        */
        Vector AmmoRespawnSpot(PlayerAmmoBase* ammo) override = 0;

        //
        // Health charger respawn control.
        //

        /**
         * @brief N/D
        */
        float HealthChargerRechargeTime() override = 0;

        //
        // What happens to a dead player's weapons.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode DeadPlayerWeapons(PlayerBase* player) override = 0;

        //
        // What happens to a dead player's ammo.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode DeadPlayerAmmo(PlayerBase* player) override = 0;

        //
        // Teamplay stuff.
        //

        /**
         * @brief N/D
        */
        const char* GetTeamId(EntityBase* entity) override = 0;

        /**
         * @brief N/D
        */
        PlayerRelationship GetPlayerRelationship(PlayerBase* player, EntityBase* target) override = 0;

        //
        // Monsters.
        //

        /**
         * @brief N/D
        */
        qboolean AllowMonsters() override = 0;
    };

#ifdef __INTEL_COMPILER
#pragma warning(push)
#pragma warning(disable : 2021)
#endif

    // ReSharper disable once CppImplicitDefaultConstructorNotAvailable
    class HalfLifeMultiplay : public GameRulesBase // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        ~HalfLifeMultiplay() override = default;

        /**
         * @brief N/D
        */
        void RefreshSkillData() override = 0;

        /**
         * @brief N/D
        */
        void Think() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsAllowedToSpawn(EntityBase* entity) override = 0;

        /**
         * @brief N/D
        */
        qboolean AllowFlashlight() override = 0;

        /**
         * @brief N/D
        */
        qboolean ShouldSwitchWeapon(PlayerBase* player, PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        qboolean GetNextBestWeapon(PlayerBase* player, PlayerItemBase* current_weapon) override = 0;

        /**
         * @brief N/D
        */
        qboolean IsMultiplayer() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsDeathmatch() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsCoop() override = 0;

        //
        // Client connection/disconnection.
        //

        /**
         * @brief If \c client_connected returns \c FALSE, the connection is rejected and the user is provided the
         * reason specified in \c reject_reason.
         * Only the client's name and remote address are provided to the dll for verification.
        */
        qboolean ClientConnected(Edict* entity, const char* name, const char* address, char reject_reason[128]) override = 0;

        /**
         * @brief The client dll is ready for updating.
        */
        void InitHud(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        void ClientDisconnected(Edict* client) override = 0;

        /**
         * @brief The client needs to be informed of the current game mode.
        */
        void UpdateGameMode(PlayerBase* player) override = 0;

        //
        // Client damage rules.
        //

        /**
         * @brief N/D
        */
        float PlayerFallDamage(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        qboolean PlayerCanTakeDamage(PlayerBase* player, EntityBase* attacker) override = 0;

        //
        // Client spawn/respawn control.
        //

        /**
         * @brief N/D
        */
        void PlayerSpawn(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        void PlayerThink(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        qboolean PlayerCanRespawn(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        float PlayerSpawnTime(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        Edict* GetPlayerSpawnSpot(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        qboolean AllowAutoTargetCrosshair() override = 0;

        /**
         * @brief N/D
        */
        qboolean ClientCommandDeadOrAlive(PlayerBase* player, const char* cmd) override = 0;

        /**
         * @brief N/D
        */
        qboolean ClientCommand(PlayerBase* player, const char* cmd) override = 0;

        /**
         * @brief N/D
        */
        void ClientUserInfoChanged(PlayerBase* player, char* info_buffer) override = 0;

        //
        // Client kills/scoring.
        //

        /**
         * @brief N/D
        */
        int PointsForKill(PlayerBase* attacker, PlayerBase* killed) override = 0;

        /**
         * @brief N/D
        */
        void PlayerKilled(PlayerBase* victim, EntityVars* killer, EntityVars* inflictor) override = 0;

        /**
         * @brief N/D
        */
        void DeathNotice(PlayerBase* victim, EntityVars* killer, EntityVars* inflictor) override = 0;

        //
        // Weapon retrieval.
        //

        /**
         * @brief The player is touching an PlayerItemBase, do I give it to him?
        */
        qboolean CanHavePlayerItem(PlayerBase* player, PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        void PlayerGotWeapon(PlayerBase* player, PlayerItemBase* weapon) override = 0;

        //
        // Weapon spawn/respawn control.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode WeaponShouldRespawn(PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        float WeaponRespawnTime(PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        float WeaponTryRespawn(PlayerItemBase* weapon) override = 0;

        /**
         * @brief N/D
        */
        Vector WeaponRespawnSpot(PlayerItemBase* weapon) override = 0;

        //
        // Item retrieval.
        //

        /**
         * @brief N/D
        */
        qboolean CanHaveItem(PlayerBase* player, Item* item) override = 0;

        /**
         * @brief N/D
        */
        void PlayerGotItem(PlayerBase* player, Item* item) override = 0;

        //
        // Item spawn/respawn control.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode ItemShouldRespawn(Item* item) override = 0;

        /**
         * @brief N/D
        */
        float ItemRespawnTime(Item* item) override = 0;

        /**
         * @brief N/D
        */
        Vector ItemRespawnSpot(Item* item) override = 0;

        //
        // Ammo retrieval.
        //

        /**
         * @brief N/D
        */
        void PlayerGotAmmo(PlayerBase* player, char* name, int count) override = 0;

        //
        // Ammo spawn/respawn control.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode AmmoShouldRespawn(PlayerAmmoBase* ammo) override = 0;

        /**
         * @brief N/D
        */
        float AmmoRespawnTime(PlayerAmmoBase* ammo) override = 0;

        /**
         * @brief N/D
        */
        Vector AmmoRespawnSpot(PlayerAmmoBase* ammo) override = 0;

        //
        // Health charger respawn control.
        //

        /**
         * @brief N/D
        */
        float HealthChargerRechargeTime() override = 0;

        /**
         * @brief N/D
        */
        float HevChargerRechargeTime() override = 0;

        //
        // What happens to a dead player's weapons.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode DeadPlayerWeapons(PlayerBase* player) override = 0;

        //
        // What happens to a dead player's ammo.
        //

        /**
         * @brief N/D
        */
        WeaponRespawnCode DeadPlayerAmmo(PlayerBase* player) override = 0;

        //
        // Teamplay stuff.
        //

        /**
         * @brief N/D
        */
        const char* GetTeamId(EntityBase* entity) override = 0;

        /**
         * @brief N/D
        */
        PlayerRelationship GetPlayerRelationship(PlayerBase* player, EntityBase* target) override = 0;

        /**
         * @brief N/D
        */
        void ChangePlayerTeam(PlayerBase* player, const char* team_name, qboolean kill, qboolean gib) override = 0;

        /**
         * @brief N/D
        */
        qboolean PlayTextureSounds() override = 0;

        //
        // Monsters.
        //

        /**
         * @brief N/D
        */
        qboolean AllowMonsters() override = 0;

        //
        // Immediately end a multiplayer game.
        //

        /**
         * @brief N/D
        */
        void EndMultiplayerGame() override = 0;

        /**
         * @brief N/D
        */
        void ServerDeactivate() override = 0;

        /**
         * @brief N/D
        */
        void CheckMapConditions() override = 0;

        //
        // Recreate all the map entities from the map data (preserving their indices), then remove everything else except the
        // players. Also get rid of all world decals.
        //

        /**
         * @brief N/D
        */
        virtual void CleanUpMap() = 0;

        /**
         * @brief N/D
        */
        virtual void RestartRound() = 0;

        //
        // Check if the scenario has been won/lost.
        //

        /**
         * @brief N/D
        */
        virtual void CheckWinConditions() = 0;

        /**
         * @brief N/D
        */
        virtual void RemoveGuns() = 0;

        /**
         * @brief N/D
        */
        virtual void GiveC4() = 0;

        /**
         * @brief N/D
        */
        virtual void ChangeLevel() = 0;

        /**
         * @brief N/D
        */
        virtual void GoToIntermission() = 0;

#ifdef REGAMEDLL_ADD
        /**
         * @brief N/D
        */
        virtual void InitializePlayerCounts(int& num_alive_terrorist, int& num_alive_ct, int& num_dead_terrorist,
                                            int& num_dead_ct) = 0;

        /**
         * @brief N/D
        */
        virtual void BalanceTeams() = 0;

        /**
         * @brief N/D
        */
        virtual void SwapAllPlayers() = 0;

        /**
         * @brief N/D
        */
        virtual void UpdateTeamScores() = 0;

        /**
         * @brief N/D
        */
        virtual void EndRoundMessage(const char* sentence, ScenarioEventEndRound event) = 0;

        /**
         * @brief N/D
        */
        virtual void SetAccountRules(RewardRules rules, int amount) = 0;

        /**
         * @brief N/D
        */
        [[nodiscard]] virtual int GetAccountRules(RewardRules rules) const = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsThereABomber() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsThereABomb() = 0;

        /**
         * @brief N/D
        */
        virtual TeamName SelectDefaultTeam() = 0;

        /**
         * @brief N/D
        */
        virtual bool HasRoundTimeExpired() = 0;

        /**
         * @brief N/D
        */
        virtual bool IsBombPlanted() = 0;
#endif

        /**
         * @brief N/D
        */
        VoiceGameMgr voice_manager;

        /**
         * @brief The global time when the round is supposed to end, if this is not 0 (deprecated name \c team_count).
        */
        float restart_round_time;

        /**
         * @brief N/D
        */
        float win_conditions;

        /**
         * @brief Time round has started (deprecated name \c round_count).
        */
        float round_start_time;

        /**
         * @brief (From mp_roundtime) - How many seconds long this round is.
        */
        int round_time;

        /**
         * @brief N/D
        */
        int round_time_secs;

        /**
         * @brief (From mp_freezetime) - How many seconds long the intro round (when players are frozen) is.
        */
        int intro_round_time;

        /**
         * @brief The global time when the intro round ends and the real one starts
         * wrote the original "RoundTime" comment for this variable).
        */
        float round_start_time_real;

        /**
         * @brief N/D
        */
        int account_terrorist;

        /**
         * @brief N/D
        */
        int account_ct;

        /**
         * @brief The number of terrorists on the team (this is generated at the end of a round).
        */
        int num_terrorist;

        /**
         * @brief The number of CTs on the team (this is generated at the end of a round).
        */
        int num_ct;

        /**
         * @brief N/D
        */
        int num_spawnable_terrorist;

        /**
         * @brief N/D
        */
        int num_spawnable_ct;

        /**
         * @brief Number of Terrorist spawn points.
        */
        int spawn_point_count_terrorist;

        /**
         * @brief Number of CT spawn points.
        */
        int spawn_point_count_ct;

        /**
         * @brief N/D
        */
        int hostages_rescued;

        /**
         * @brief N/D
        */
        int hostages_touched;

        /**
         * @brief N/D
        */
        WinStatus round_win_status;

        /**
         * @brief N/D
        */
        short num_ct_wins;

        /**
         * @brief N/D
        */
        short num_terrorist_wins;

        /**
         * @brief Whether or not the bomb has been bombed.
        */
        bool target_bombed;

        /**
         * @brief Whether or not the bomb has been defused.
        */
        bool bomb_defused;

        /**
         * @brief N/D
        */
        bool map_has_bomb_target;

        /**
         * @brief N/D
        */
        bool map_has_bomb_zone;

        /**
         * @brief N/D
        */
        bool map_has_buy_zone;

        /**
         * @brief N/D
        */
        bool map_has_rescue_zone;

        /**
         * @brief N/D
        */
        bool map_has_escape_zone;

        /**
         * @brief \c TRUE = has VIP safety zone, \c FALSE = does not have VIP safety zone.
        */
        qboolean map_has_vip_safety_zone;

        /**
         * @brief N/D
        */
        qboolean map_has_cameras;

        /**
         * @brief N/D
        */
        int c4_timer;

        /**
         * @brief The current Terrorist who has the C4.
        */
        int c4_guy;

        /**
         * @brief The amount of money the losing team gets. This scales up as they lose more rounds in a row.
        */
        int loser_bonus;

        /**
         * @brief The number of rounds the CTs have lost in a row.
        */
        int num_consecutive_ct_loses;

        /**
         * @brief The number of rounds the Terrorists have lost in a row.
        */
        int num_consecutive_terrorist_loses;

        /**
         * @brief For the idle kick functionality.
         * This is tha max amount of time that the player has to be idle before being kicked.
        */
        float max_idle_period;

        /**
         * @brief N/D
        */
        int limit_teams;

        /**
         * @brief N/D
        */
        bool level_initialized;

        /**
         * @brief N/D
        */
        bool round_terminating;

        /**
         * @brief Set to TRUE to have the scores reset next time round restarts.
        */
        bool complete_reset;

        /**
         * @brief N/D
        */
        float required_escape_ratio;

        /**
         * @brief N/D
        */
        int num_escapers;

        /**
         * @brief N/D
        */
        int have_escaped;

        /**
         * @brief N/D
        */
        bool ct_cant_buy;

        /**
         * @brief N/D
        */
        bool t_cant_buy;

        /**
         * @brief N/D
        */
        float bomb_radius;

        /**
         * @brief N/D
        */
        int consecutive_vip;

        /**
         * @brief N/D
        */
        int total_gun_count;

        /**
         * @brief N/D
        */
        int total_grenade_count;

        /**
         * @brief N/D
        */
        int total_armour_count;

        /**
         * @brief Keeps track of the # of consecutive rounds that have gone by where
         * one team outnumbers the other team by more than 2.
        */
        int unbalanced_rounds;

        /**
         * @brief Keeps track of the # of consecutive rounds of escape played. Teams will be swapped after 8 rounds
        */
        int num_escape_rounds;

        /**
         * @brief N/D
        */
        int map_votes[MAX_VOTE_MAPS];

        /**
         * @brief N/D
        */
        int last_pick;

        /**
         * @brief N/D
        */
        int max_map_time;

        /**
         * @brief N/D
        */
        int max_rounds;

        /**
         * @brief N/D
        */
        int total_rounds_played;

        /**
         * @brief N/D
        */
        int max_rounds_won;

        /**
         * @brief N/D
        */
        int stored_spect_value;

        /**
         * @brief N/D
        */
        float force_camera_value;

        /**
         * @brief N/D
        */
        float force_chase_cam_value;

        /**
         * @brief N/D
        */
        float fade_to_black_value;

        /**
         * @brief N/D
        */
        PlayerBase* vip;

        /**
         * @brief N/D
        */
        PlayerBase* vip_queue[MAX_VIP_QUEUES];

        // protected:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float intermission_end_time_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float intermission_start_time_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        qboolean end_intermission_button_hit_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float next_periodic_think_;

        /**
         * @brief \c TRUE = the game commencing when there is at least one CT and T,
         * \c FALSE = scoring will not start until both teams have players (deprecated name \c first_connected).
        */
        // ReSharper disable once CppInconsistentNaming
        bool game_started_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        bool in_career_game_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float career_round_menu_time_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int career_match_wins_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int round_win_difference_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float career_match_menu_time_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        bool skip_spawn_;

        //
        // Custom.
        //

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        bool skip_show_menu_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        bool needed_players_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float escape_ratio_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float time_limit_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float game_start_time_;

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        bool team_balanced_;
    };

    inline HalfLifeMultiplay* GameRulesBase::CsGameRules()
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
        return static_cast<HalfLifeMultiplay*>(this);
    }

    inline const HalfLifeMultiplay* GameRulesBase::CsGameRules() const
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
        return static_cast<const HalfLifeMultiplay*>(this);
    }

#ifdef __INTEL_COMPILER
#pragma warning(pop)
#endif
}
