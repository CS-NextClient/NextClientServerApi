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

#include <cssdk/common/const.h>

namespace cssdk
{
    //
    // Dot products for view cone checking.
    //

    /**
     * @brief +-180 degrees.
    */
    constexpr auto VIEW_FIELD_FULL = -1.0;

    /**
     * @brief +-135 degrees 0.1 // +-85 degrees, used for full FOV checks.
    */
    constexpr auto VIEW_FIELD_WIDE = -0.7;

    /**
     * @brief +-45 degrees, more narrow check used to set up ranged attacks.
    */
    constexpr auto VIEW_FIELD_NARROW = 0.7;

    /**
     * @brief +-25 degrees, more narrow check used to set up ranged attacks.
    */
    constexpr auto VIEW_FIELD_ULTRA_NARROW = 0.9;

    //
    //
    //

    /**
     * @brief Duplicated in protocol.h stop sound.
    */
    constexpr auto SND_STOP = 1 << 5;

    /**
     * @brief Duplicated in protocol.h change sound vol.
    */
    constexpr auto SND_CHANGE_VOL = 1 << 6;

    /**
     * @brief Duplicated in protocol.h change sound pitch.
    */
    constexpr auto SND_CHANGE_PITCH = 1 << 7;

    /**
     * @brief Duplicated in protocol.h we're spawning, used in some cases for ambients.
    */
    constexpr auto SND_SPAWNING = 1 << 8;

    //
    // All monsters need this data.
    //

    /**
     * @brief N/D
    */
    constexpr auto DONT_BLEED = -1;

    /**
     * @brief N/D
    */
    constexpr byte BLOOD_COLOR_DARK_RED = 223;

    /**
     * @brief N/D
    */
    constexpr byte BLOOD_COLOR_RED = 247;

    /**
     * @brief N/D
    */
    constexpr byte BLOOD_COLOR_YELLOW = 195;

    /**
     * @brief N/D
    */
    constexpr byte BLOOD_COLOR_GREEN = BLOOD_COLOR_YELLOW;

    //
    //
    //

    /**
     * @brief N/D
    */
    constexpr auto GERMAN_GIB_COUNT = 4;

    /**
     * @brief N/D
    */
    constexpr auto HUMAN_GIB_COUNT = 6;

    /**
     * @brief N/D
    */
    constexpr auto ALIEN_GIB_COUNT = 4;

    //
    //
    //

    /**
     * @brief N/D
    */
    constexpr auto LANGUAGE_ENGLISH = 0;

    /**
     * @brief N/D
    */
    constexpr auto LANGUAGE_GERMAN = 1;

    /**
     * @brief N/D
    */
    constexpr auto LANGUAGE_FRENCH = 2;

    /**
     * @brief N/D
    */
    constexpr auto LANGUAGE_BRITISH = 3;

    /**
     * @brief Set this bit on guns and stuff that should never respawn.
    */
    constexpr auto SF_NO_RESPAWN = 1 << 30;

    //
    // These are caps bits to indicate what an object's capabilities (currently used for save/restore and level transitions).
    //

    /**
     * @brief N/D
    */
    constexpr auto FCAP_CUSTOM_SAVE = 0x00000001;

    /**
     * @brief Should transfer between transitions.
    */
    constexpr auto FCAP_ACROSS_TRANSITION = 0x00000002;

    /**
     * @brief Spawn after restore.
    */
    constexpr auto FCAP_MUST_SPAWN = 0x00000004;

    /**
     * @brief Don't save this.
    */
    constexpr auto FCAP_DONT_SAVE = 0x80000000;

    /**
     * @brief Can be used by the player.
    */
    constexpr auto FCAP_IMPULSE_USE = 0x00000008;

    /**
     * @brief Can be used by the player.
    */
    constexpr auto FCAP_CONTINUOUS_USE = 0x00000010;

    /**
     * @brief Can be used by the player.
    */
    constexpr auto FCAP_ON_OFF_USE = 0x00000020;

    /**
     * @brief Player sends +/- 1 when using (currently only track trains).
    */
    constexpr auto FCAP_DIRECTIONAL_USE = 0x00000040;

    /**
     * @brief Can be used to "master" other entities (like multi source).
    */
    constexpr auto FCAP_MASTER = 0x00000080;

    /**
     * @brief Should reset on the new round.
    */
    constexpr auto FCAP_MUST_RESET = 0x00000100;

    /**
     * @brief Should release on the new round.
    */
    constexpr auto FCAP_MUST_RELEASE = 0x00000200;

    //
    // UNDONE: This will ignore transition volumes (trigger_transition), but not the PVS!!!
    //

    /**
     * @brief ALWAYS goes across transitions.
    */
    constexpr auto FCAP_FORCE_TRANSITION = 0x00000080;

    //
    //
    //

    /**
     * @brief Generic damage was done.
    */
    constexpr auto DMG_GENERIC = 0;

    /**
     * @brief Crushed by falling or moving object.
    */
    constexpr auto DMG_CRUSH = 1 << 0;

    /**
     * @brief Shot.
    */
    constexpr auto DMG_BULLET = 1 << 1;

    /**
     * @brief Cut, clawed, stabbed.
    */
    constexpr auto DMG_SLASH = 1 << 2;

    /**
     * @brief Heat burned.
    */
    constexpr auto DMG_BURN = 1 << 3;

    /**
     * @brief Frozen.
    */
    constexpr auto DMG_FREEZE = 1 << 4;

    /**
     * @brief Fell too far.
    */
    constexpr auto DMG_FALL = 1 << 5;

    /**
     * @brief Explosive blast damage.
    */
    constexpr auto DMG_BLAST = 1 << 6;

    /**
     * @brief Crowbar, punch, headbutt.
    */
    constexpr auto DMG_CLUB = 1 << 7;

    /**
     * @brief Electric shock.
    */
    constexpr auto DMG_SHOCK = 1 << 8;

    /**
     * @brief Sound pulse shockwave.
    */
    constexpr auto DMG_SONIC = 1 << 9;

    /**
     * @brief Laser or other high energy beam.
    */
    constexpr auto DMG_ENERGY_BEAM = 1 << 10;

    /**
     * @brief With this bit OR'd in, no damage type will be able to gib victims upon death.
    */
    constexpr auto DMG_NEVER_GIB = 1 << 12;

    /**
     * @brief With this bit OR'd in, any damage type can be made to gib victims upon death.
    */
    constexpr auto DMG_ALWAYS_GIB = 1 << 13;

    /**
     * @brief Drowning.
    */
    constexpr auto DMG_DROWN = 1 << 14;

    //
    // Time-based damage.
    //

    /**
     * @brief Mask for time-based damage.
    */
    constexpr auto DMG_TIME_BASED = ~0x3FFF;

    /**
     * @brief Slows affected creature down.
    */
    constexpr auto DMG_PARALYZE = 1 << 15;

    /**
     * @brief Nerve toxins, very bad.
    */
    constexpr auto DMG_NERVE_GAS = 1 << 16;

    /**
     * @brief Blood poisoning.
    */
    constexpr auto DMG_POISON = 1 << 17;

    /**
     * @brief Radiation exposure.
    */
    constexpr auto DMG_RADIATION = 1 << 18;

    /**
     * @brief Drowning recovery.
    */
    constexpr auto DMG_DROWN_RECOVER = 1 << 19;

    /**
     * @brief Toxic chemicals or acid burns.
    */
    constexpr auto DMG_ACID = 1 << 20;

    /**
     * @brief In an oven.
    */
    constexpr auto DMG_SLOW_BURN = 1 << 21;

    /**
     * @brief In a subzero freezer.
    */
    constexpr auto DMG_SLOW_FREEZE = 1 << 22;

    /**
     * @brief Hit by air raid (done to distinguish grenade from mortar).
    */
    constexpr auto DMG_MORTAR = 1 << 23;

    /**
     * @brief N/D
    */
    constexpr auto DMG_EXPLOSION = 1 << 24;

    /**
     * @brief These are the damage types that are allowed to gib corpses.
    */
    constexpr auto DMG_GIB_CORPSE = DMG_CRUSH | DMG_FALL | DMG_BLAST | DMG_SONIC | DMG_CLUB;

    /**
     * @brief These are the damage types that have client hud art.
    */
    constexpr auto DMG_SHOWN_HUD = DMG_POISON | DMG_ACID | DMG_FREEZE | DMG_SLOW_FREEZE | DMG_DROWN | DMG_BURN | DMG_SLOW_BURN |
        DMG_NERVE_GAS | DMG_RADIATION | DMG_SHOCK;

    //
    // When calling KILLED(), a value that governs gib behavior is expected to be one of these three values.
    //

    /**
     * @brief Gib if entity was overkilled.
    */
    constexpr auto GIB_NORMAL = 0;

    /**
     * @brief Never gib, no matter how much death damage is done (freezing, etc).
    */
    constexpr auto GIB_NEVER = 1;

    /**
     * @brief Always gib (Houndeye Shock, Barnacle Bite).
    */
    constexpr auto GIB_ALWAYS = 2;

    /**
     * @brief N/D
    */
    constexpr auto GIB_HEALTH_VALUE = -30;

    enum class Classify
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        Machine,

        /**
         * @brief N/D
        */
        Player,

        /**
         * @brief N/D
        */
        HumanPassive,

        /**
         * @brief N/D
        */
        HumanMilitary,

        /**
         * @brief N/D
        */
        AlienMilitary,

        /**
         * @brief N/D
        */
        AlienPassive,

        /**
         * @brief N/D
        */
        AlienMonster,

        /**
         * @brief N/D
        */
        AlienPrey,

        /**
         * @brief N/D
        */
        AlienPredator,

        /**
         * @brief N/D
        */
        Insect,

        /**
         * @brief N/D
        */
        PlayerAlly,

        /**
         * @brief Hornets and snarks. Launched by players.
        */
        PlayerBioWeapon,

        /**
         * @brief Hornets and snarks. Launched by the alien menace.
        */
        AlienBioWeapon,

        /**
         * @brief N/D
        */
        Vehicle,

        /**
         * @brief Special because no one pays attention to it, and it eats a wide cross-section of creatures.
        */
        Barnacle = 99
    };
}
