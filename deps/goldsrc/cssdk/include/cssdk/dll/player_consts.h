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

namespace cssdk
{
    /**
     * @brief N/D
    */
    constexpr auto SOUND_FLASHLIGHT_ON = "items/flashlight1.wav";

    /**
     * @brief N/D
    */
    constexpr auto SOUND_FLASHLIGHT_OFF = "items/flashlight1.wav";

#ifdef REGAMEDLL_FIXES
    /**
     * @brief N/D
    */
    constexpr auto MIN_BUY_TIME = 0;
#else
    /**
     * @brief The minimum threshold values for cvar mp_buytime 15 sec's.
    */
    constexpr auto MIN_BUY_TIME = 15;
#endif

    /**
     * @brief N/D
    */
    constexpr auto MAX_PLAYER_NAME_LENGTH = 32;

    /**
     * @brief N/D
    */
    constexpr auto MAX_AUTO_BUY_LENGTH = 256;

    /**
     * @brief N/D
    */
    constexpr auto MAX_REBUY_LENGTH = 256;

    /**
     * @brief N/D
    */
    constexpr auto MAX_RECENT_PATH = 20;

    /**
     * @brief The maximum number of icons of the hostages in the HUD.
    */
    constexpr auto MAX_HOSTAGE_ICON = 4;

    /**
     * @brief N/D
    */
    constexpr auto MAX_SUIT_NO_REPEAT = 32;

    /**
     * @brief Max of 4 suit sentences queued up at any time.
    */
    constexpr auto MAX_SUIT_PLAYLIST = 4;

    /**
     * @brief N/D
    */
    constexpr auto MAX_BUFFER_MENU = 175;

    /**
     * @brief N/D
    */
    constexpr auto MAX_BUFFER_MENU_BRIEFING = 50;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_UPDATE_TIME = 3.5F;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_FIRST_UPDATE_TIME = 0.1F;

    /**
     * @brief N/D
    */
    constexpr auto MAX_PLAYER_FATAL_FALL_SPEED = 1100.F;

    /**
     * @brief N/D
    */
    constexpr auto MAX_PLAYER_SAFE_FALL_SPEED = 500.F;

    /**
     * @brief N/D
    */
    constexpr auto MAX_PLAYER_USE_RADIUS = 64.F;

    /**
     * @brief Armor Takes 50% of the damage.
    */
    constexpr auto ARMOR_RATIO = 0.5F;

    /**
     * @brief Each Point of Armor is work 1/x points of health.
    */
    constexpr auto ARMOR_BONUS = 0.5F;

    /**
     * @brief 100 units / 3 minutes.
    */
    constexpr auto FLASH_DRAIN_TIME = 1.2F;

    /**
     * @brief 100 units / 20 seconds (seconds per unit).
    */
    constexpr auto FLASH_CHARGE_TIME = 0.2F;

    /**
     * @brief Damage per unit per second.
    */
    constexpr auto DAMAGE_FOR_FALL_SPEED = 100.F / (MAX_PLAYER_FATAL_FALL_SPEED - MAX_PLAYER_SAFE_FALL_SPEED);

    /**
     * @brief N/D
    */
    constexpr auto PLAYER_MIN_BOUNCE_SPEED = 350.F;

    /**
     * @brief Won't punch player's screen/make scrape noise unless player falling at least this fast.
    */
    constexpr auto PLAYER_FALL_PUNCH_THRESHOLD = 250.F;

    /**
     * @brief Money blinks few of times on the freeze period.
     *
     * @note It works for CZ.
    */
    constexpr auto MONEY_BLINK_AMOUNT = 30;

    //
    // Player time based damage.
    //

    /**
     * @brief Lung full of air lasts this many seconds.
    */
    constexpr auto AIRTIME = 12;

    /**
     * @brief Number of 2 second intervals to take damage.
    */
    constexpr auto PARALYZE_DURATION = 2;

    /**
     * @brief Damage to take each 2 second interval.
    */
    constexpr auto PARALYZE_DAMAGE = 1.F;

    /**
     * @brief N/D
    */
    constexpr auto NERVE_GAS_DURATION = 2;

    /**
     * @brief N/D
    */
    constexpr auto NERVE_GAS_DAMAGE = 5.F;

    /**
     * @brief N/D
    */
    constexpr auto POISON_DURATION = 5;

    /**
     * @brief N/D
    */
    constexpr auto POISON_DAMAGE = 2.F;

    /**
     * @brief N/D
    */
    constexpr auto RADIATION_DURATION = 2;

    /**
     * @brief N/D
    */
    constexpr auto RADIATION_DAMAGE = 1.F;

    /**
     * @brief N/D
    */
    constexpr auto ACID_DURATION = 2;

    /**
     * @brief N/D
    */
    constexpr auto ACID_DAMAGE = 5.F;

    /**
     * @brief N/D
    */
    constexpr auto SLOW_BURN_DURATION = 2;

    /**
     * @brief N/D
    */
    constexpr auto SLOW_BURN_DAMAGE = 1.F;

    /**
     * @brief N/D
    */
    constexpr auto SLOW_FREEZE_DURATION = 2;

    /**
     * @brief N/D
    */
    constexpr auto SLOW_FREEZE_DAMAGE = 1.F;

    //
    // Player physics flags bits.
    // base_player::physics_flags
    //

    /**
     * @brief N/D
    */
    constexpr auto PFLAG_ON_LADDER = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto PFLAG_ON_SWING = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto PFLAG_ON_TRAIN = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto PFLAG_ON_BARNACLE = 1 << 2;

    /**
     * @brief In the process of ducking, but not totally squatted yet.
    */
    constexpr auto PFLAG_DUCKING = 1 << 3;

    /**
     * @brief Using a continuous entity.
    */
    constexpr auto PFLAG_USING = 1 << 4;

    /**
     * @brief Player is locked in stationary cam mode. Spectators can move, observers can't.
    */
    constexpr auto PFLAG_OBSERVER = 1 << 5;

    //
    // Player game state flags.
    //

    /**
     * @brief N/D
    */
    constexpr auto HIT_GROUP_SHIELD_ENABLED = 0;

    /**
     * @brief N/D
    */
    constexpr auto HIT_GROUP_SHIELD_DISABLED = 1;

    /**
     * @brief N/D
    */
    constexpr auto TRAIN_OFF = 0x00;

    /**
     * @brief N/D
    */
    constexpr auto TRAIN_NEUTRAL = 0x01;

    /**
     * @brief N/D
    */
    constexpr auto TRAIN_SLOW = 0x02;

    /**
     * @brief N/D
    */
    constexpr auto TRAIN_MEDIUM = 0x03;

    /**
     * @brief N/D
    */
    constexpr auto TRAIN_FAST = 0x04;

    /**
     * @brief N/D
    */
    constexpr auto TRAIN_BACK = 0x05;

    /**
     * @brief N/D
    */
    constexpr auto TRAIN_ACTIVE = 0x80;

    /**
     * @brief N/D
    */
    constexpr auto TRAIN_NEW = 0xc0;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_GROUP = true;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_SENTENCE = false;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_REPEAT_OK = 0;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_NEXT_IN_30_SEC = 30;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_NEXT_IN_1_MIN = 60;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_NEXT_IN_5_MIN = 300;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_NEXT_IN_10_MIN = 600;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_NEXT_IN_30_MIN = 1800;

    /**
     * @brief N/D
    */
    constexpr auto SUIT_NEXT_IN_1_HOUR = 3600;

    /**
     * @brief N/D
    */
    constexpr auto MAX_TEAM_NAME_LENGTH = 16;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_AIM_2DEGREES = 0.0348994967025;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_AIM_5DEGREES = 0.08715574274766;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_AIM_8DEGREES = 0.1391731009601;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_AIM_10DEGREES = 0.1736481776669;

    /**
     * @brief N/D
    */
    constexpr auto MAX_ID_RANGE = 2048.F;

    /**
     * @brief N/D
    */
    constexpr auto MAX_SPEC_ID_RANGE = 8192.F;

    /**
     * @brief N/D
    */
    constexpr auto MAX_SBAR_STRING = 128;

    /**
     * @brief N/D
    */
    constexpr auto SBAR_TARGET_TYPE_TEAMMATE = 1;

    /**
     * @brief N/D
    */
    constexpr auto SBAR_TARGET_TYPE_ENEMY = 2;

    /**
     * @brief N/D
    */
    constexpr auto SBAR_TARGET_TYPE_HOSTAGE = 3;

    /**
     * @brief N/D
    */
    constexpr auto MAX_LOCATION_LEN = 32;

    enum class RewardType
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        RoundBonus,

        /**
         * @brief N/D
        */
        PlayerReset,

        /**
         * @brief N/D
        */
        PlayerJoin,

        /**
         * @brief N/D
        */
        PlayerSpecJoin,

        /**
         * @brief N/D
        */
        PlayerBoughtSomething,

        /**
         * @brief N/D
        */
        HostageTook,

        /**
         * @brief N/D
        */
        HostageRescued,

        /**
         * @brief N/D
        */
        HostageDamaged,

        /**
         * @brief N/D
        */
        HostageKilled,

        /**
         * @brief N/D
        */
        TeammatesKilled,

        /**
         * @brief N/D
        */
        EnemyKilled,

        /**
         * @brief N/D
        */
        IntoGame,

        /**
         * @brief N/D
        */
        VipKilled,

        /**
         * @brief N/D
        */
        VipRescuedMyself
    };

    enum class PlayerAnim
    {
        /**
         * @brief N/D
        */
        Idle = 0,

        /**
         * @brief N/D
        */
        Walk,

        /**
         * @brief N/D
        */
        Jump,

        /**
         * @brief N/D
        */
        SuperJump,

        /**
         * @brief N/D
        */
        Die,

        /**
         * @brief N/D
        */
        Attack1,

        /**
         * @brief N/D
        */
        Attack2,

        /**
         * @brief N/D
        */
        Flinch,

        /**
         * @brief N/D
        */
        LargeFlinch,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        HoldBomb
    };

    enum class MenuName
    {
        /**
         * @brief N/D
        */
        Off = 0,

        /**
         * @brief N/D
        */
        ChooseTeam,

        /**
         * @brief N/D
        */
        IgChooseTeam,

        /**
         * @brief N/D
        */
        ChooseAppearance,

        /**
         * @brief N/D
        */
        Buy,

        /**
         * @brief N/D
        */
        BuyPistol,

        /**
         * @brief N/D
        */
        BuyRifle,

        /**
         * @brief N/D
        */
        BuyMachineGun,

        /**
         * @brief N/D
        */
        BuyShotgun,

        /**
         * @brief N/D
        */
        BuySubmachineGun,

        /**
         * @brief N/D
        */
        BuyItem,

        /**
         * @brief N/D
        */
        Radio1,

        /**
         * @brief N/D
        */
        Radio2,

        /**
         * @brief N/D
        */
        Radio3,

        /**
         * @brief N/D
        */
        ClientBuy
    };

    enum class TeamName
    {
        /**
         * @brief N/D
        */
        Unassigned = 0,

        /**
         * @brief N/D
        */
        Terrorist,

        /**
         * @brief N/D
        */
        Ct,

        /**
         * @brief N/D
        */
        Spectator
    };

    enum class ModelName
    {
        /**
         * @brief N/D
        */
        Unassigned = 0,

        /**
         * @brief N/D
        */
        Urban,

        /**
         * @brief N/D
        */
        Terror,

        /**
         * @brief N/D
        */
        Leet,

        /**
         * @brief N/D
        */
        Arctic,

        /**
         * @brief N/D
        */
        Gsg9,

        /**
         * @brief N/D
        */
        Gign,

        /**
         * @brief N/D
        */
        Sas,

        /**
         * @brief N/D
        */
        Guerilla,

        /**
         * @brief N/D
        */
        Vip,

        /**
         * @brief N/D
        */
        Militia,

        /**
         * @brief N/D
        */
        Spetsnaz,

        /**
         * @brief N/D
        */
        Auto
    };

    enum class JoinState
    {
        /**
         * @brief N/D
        */
        Joined = 0,

        /**
         * @brief N/D
        */
        ShowText,

        /**
         * @brief N/D
        */
        ReadingText,

        /**
         * @brief N/D
        */
        ShowTeamSelect,

        /**
         * @brief N/D
        */
        PickingTeam,

        /**
         * @brief N/D
        */
        GetIntoGame
    };

    enum class TrackCommands
    {
        /**
         * @brief N/D
        */
        Say = 0,

        /**
         * @brief N/D
        */
        SayTeam,

        /**
         * @brief N/D
        */
        FullUpdate,

        /**
         * @brief N/D
        */
        Vote,

        /**
         * @brief N/D
        */
        VoteMap,

        /**
         * @brief N/D
        */
        ListMaps,

        /**
         * @brief N/D
        */
        ListPlayers,

        /**
         * @brief N/D
        */
        NightVision,

        /**
         * @brief N/D
        */
        CommandsToTrack
    };

    enum class IgnoreChatMsg : int
    {
        /**
         * @brief Nothing to do.
        */
        None = 0,

        /**
         * @brief To ignore any chat messages from the enemy.
        */
        Enemy,

        /**
         * @brief Same as \c enemy but ignore teammates.
        */
        Team
    };

    enum class ThrowDirection
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        Forward,

        /**
         * @brief N/D
        */
        Backward,

        /**
         * @brief N/D
        */
        HitVel,

        /**
         * @brief N/D
        */
        Bomb,

        /**
         * @brief N/D
        */
        Grenade,

        /**
         * @brief N/D
        */
        HitVelMinusAirVel
    };

    enum class SBarData
    {
        /**
         * @brief N/D
        */
        IdTargetType = 1,

        /**
         * @brief N/D
        */
        IdTargetName,

        /**
         * @brief N/D
        */
        IdTargetHealth,

        /**
         * @brief N/D
        */
        End
    };

    enum class MusicState
    {
        /**
         * @brief N/D
        */
        Silent = 0,

        /**
         * @brief N/D
        */
        Calm,

        /**
         * @brief N/D
        */
        Intense
    };
}
