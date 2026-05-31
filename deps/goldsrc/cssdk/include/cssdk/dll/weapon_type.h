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

#include <cssdk/dll/player_consts.h>

namespace cssdk
{
    //
    // Auto buy class.
    //

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_NONE = 0;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_PRIMARY = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_SECONDARY = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_AMMO = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_ARMOR = 1 << 3;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_DEFUSER = 1 << 4;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_PISTOL = 1 << 5;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_SMG = 1 << 6;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_RIFLE = 1 << 7;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_SNIPER_RIFLE = 1 << 8;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_SHOTGUN = 1 << 9;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_MACHINE_GUN = 1 << 10;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_GRENADE = 1 << 11;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_NIGHT_VISION = 1 << 12;

    /**
     * @brief N/D
    */
    constexpr auto AUTO_BUY_CLASS_SHIELD = 1 << 13;

    //
    // Item cost.
    //

    /**
     * @brief N/D
    */
    constexpr auto ASSAULT_SUIT_PRICE = 1000;

    /**
     * @brief N/D
    */
    constexpr auto FLASH_BANG_PRICE = 200;

    /**
     * @brief N/D
    */
    constexpr auto HE_GRENADE_PRICE = 300;

    /**
     * @brief N/D
    */
    constexpr auto SMOKE_GRENADE_PRICE = 300;

    /**
     * @brief N/D
    */
    constexpr auto KEVLAR_PRICE = 650;

    /**
     * @brief N/D
    */
    constexpr auto HELMET_PRICE = 350;

    /**
     * @brief N/D
    */
    constexpr auto NVG_PRICE = 1250;

    /**
     * @brief N/D
    */
    constexpr auto DEFUSE_KIT_PRICE = 200;

    //
    // Ammo cost.
    //

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_338MAG_PRICE = 125;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_357SIG_PRICE = 50;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_45ACP_PRICE = 25;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_50AE_PRICE = 40;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_556MM_PRICE = 60;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_57MM_PRICE = 50;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_762MM_PRICE = 80;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_9MM_PRICE = 20;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_BUCKSHOT_PRICE = 65;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_FLASH_BANG_PRICE = FLASH_BANG_PRICE;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_HE_GRENADE_PRICE = HE_GRENADE_PRICE;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_SMOKE_GRENADE_PRICE = SMOKE_GRENADE_PRICE;

    //
    // Weapon cost.
    //

    /**
     * @brief N/D
    */
    constexpr auto AK47_PRICE = 2500;

    /**
     * @brief N/D
    */
    constexpr auto AWP_PRICE = 4750;

    /**
     * @brief N/D
    */
    constexpr auto DEAGLE_PRICE = 650;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_PRICE = 5000;

    /**
     * @brief N/D
    */
    constexpr auto SG550_PRICE = 4200;

    /**
     * @brief N/D
    */
    constexpr auto GLOCK18_PRICE = 400;

    /**
     * @brief N/D
    */
    constexpr auto M249_PRICE = 5750;

    /**
     * @brief N/D
    */
    constexpr auto M3_PRICE = 1700;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_PRICE = 3100;

    /**
     * @brief N/D
    */
    constexpr auto AUG_PRICE = 3500;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MP5NAVY_PRICE = 1500;

    /**
     * @brief N/D
    */
    constexpr auto P228_PRICE = 600;

    /**
     * @brief N/D
    */
    constexpr auto P90_PRICE = 2350;

    /**
     * @brief N/D
    */
    constexpr auto UMP45_PRICE = 1700;

    /**
     * @brief N/D
    */
    constexpr auto MAC10_PRICE = 1400;

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_PRICE = 2750;

    /**
     * @brief N/D
    */
    constexpr auto SG552_PRICE = 3500;

    /**
     * @brief N/D
    */
    constexpr auto TMP_PRICE = 1250;

    /**
     * @brief N/D
    */
    constexpr auto USP_PRICE = 500;

    /**
     * @brief N/D
    */
    constexpr auto ELITE_PRICE = 800;

    /**
     * @brief N/D
    */
    constexpr auto FIVESEVEN_PRICE = 750;

    /**
     * @brief N/D
    */
    constexpr auto XM1014_PRICE = 3000;

    /**
     * @brief N/D
    */
    constexpr auto GALIL_PRICE = 2000;

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_PRICE = 2250;

    /**
     * @brief N/D
    */
    constexpr auto SHIELD_GUN_PRICE = 2200;

    //
    // Weapon state.
    //

    /**
     * @brief N/D
    */
    constexpr auto WPN_STATE_USP_SILENCED = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto WPN_STATE_GLOCK18_BURST_MODE = 1 << 1;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto WPN_STATE_M4A1_SILENCED = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto WPN_STATE_ELITE_LEFT = 1 << 3;

    /**
     * @brief N/D
    */
    constexpr auto WPN_STATE_FAMAS_BURST_MODE = 1 << 4;

    /**
     * @brief N/D
    */
    constexpr auto WPN_STATE_SHIELD_DRAWN = 1 << 5;

    //
    // Default amount of ammo that comes with each gun when it spawns.
    //

    /**
     * @brief N/D
    */
    constexpr auto P228_DEFAULT_GIVE = 13;

    /**
     * @brief N/D
    */
    constexpr auto GLOCK18_DEFAULT_GIVE = 20;

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_DEFAULT_GIVE = 10;

    /**
     * @brief N/D
    */
    constexpr auto HE_GRENADE_DEFAULT_GIVE = 1;

    /**
     * @brief N/D
    */
    constexpr auto XM1014_DEFAULT_GIVE = 7;

    /**
     * @brief N/D
    */
    constexpr auto C4_DEFAULT_GIVE = 1;

    /**
     * @brief N/D
    */
    constexpr auto MAC10_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    constexpr auto AUG_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    constexpr auto SMOKE_GRENADE_DEFAULT_GIVE = 1;

    /**
     * @brief N/D
    */
    constexpr auto ELITE_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    constexpr auto FIVESEVEN_DEFAULT_GIVE = 20;

    /**
     * @brief N/D
    */
    constexpr auto UMP45_DEFAULT_GIVE = 25;

    /**
     * @brief N/D
    */
    constexpr auto SG550_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    constexpr auto GALIL_DEFAULT_GIVE = 35;

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_DEFAULT_GIVE = 25;

    /**
     * @brief N/D
    */
    constexpr auto USP_DEFAULT_GIVE = 12;

    /**
     * @brief N/D
    */
    constexpr auto AWP_DEFAULT_GIVE = 10;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MP5NAVY_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    constexpr auto M249_DEFAULT_GIVE = 100;

    /**
     * @brief N/D
    */
    constexpr auto M3_DEFAULT_GIVE = 8;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    constexpr auto TMP_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_DEFAULT_GIVE = 20;

    /**
     * @brief N/D
    */
    constexpr auto FLASH_BANG_DEFAULT_GIVE = 1;

    /**
     * @brief N/D
    */
    constexpr auto DEAGLE_DEFAULT_GIVE = 7;

    /**
     * @brief N/D
    */
    constexpr auto SG552_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    constexpr auto AK47_DEFAULT_GIVE = 30;

    /**
     * @brief N/D
    */
    constexpr auto P90_DEFAULT_GIVE = 50;

    //
    // Weapon clip size.
    //

    /**
     * @brief N/D
    */
    constexpr auto P228_MAX_CLIP = 13;

    /**
     * @brief N/D
    */
    constexpr auto GLOCK18_MAX_CLIP = 20;

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_MAX_CLIP = 10;

    /**
     * @brief N/D
    */
    constexpr auto XM1014_MAX_CLIP = 7;

    /**
     * @brief N/D
    */
    constexpr auto MAC10_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    constexpr auto AUG_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    constexpr auto ELITE_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    constexpr auto FIVESEVEN_MAX_CLIP = 20;

    /**
     * @brief N/D
    */
    constexpr auto UMP45_MAX_CLIP = 25;

    /**
     * @brief N/D
    */
    constexpr auto SG550_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    constexpr auto GALIL_MAX_CLIP = 35;

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_MAX_CLIP = 25;

    /**
     * @brief N/D
    */
    constexpr auto USP_MAX_CLIP = 12;

    /**
     * @brief N/D
    */
    constexpr auto AWP_MAX_CLIP = 10;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MP5N_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    constexpr auto M249_MAX_CLIP = 100;

    /**
     * @brief N/D
    */
    constexpr auto M3_MAX_CLIP = 8;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    constexpr auto TMP_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_MAX_CLIP = 20;

    /**
     * @brief N/D
    */
    constexpr auto DEAGLE_MAX_CLIP = 7;

    /**
     * @brief N/D
    */
    constexpr auto SG552_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    constexpr auto AK47_MAX_CLIP = 30;

    /**
     * @brief N/D
    */
    constexpr auto P90_MAX_CLIP = 50;

    //
    // Weapon clip weight.
    //

    /**
     * @brief N/D
    */
    constexpr auto P228_WEIGHT = 5;

    /**
     * @brief N/D
    */
    constexpr auto GLOCK18_WEIGHT = 5;

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_WEIGHT = 30;

    /**
     * @brief N/D
    */
    constexpr auto HE_GRENADE_WEIGHT = 2;

    /**
     * @brief N/D
    */
    constexpr auto XM1014_WEIGHT = 20;

    /**
     * @brief N/D
    */
    constexpr auto C4_WEIGHT = 3;

    /**
     * @brief N/D
    */
    constexpr auto MAC10_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto AUG_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto SMOKE_GRENADE_WEIGHT = 1;

    /**
     * @brief N/D
    */
    constexpr auto ELITE_WEIGHT = 5;

    /**
     * @brief N/D
    */
    constexpr auto FIVESEVEN_WEIGHT = 5;

    /**
     * @brief N/D
    */
    constexpr auto UMP45_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto SG550_WEIGHT = 20;

    /**
     * @brief N/D
    */
    constexpr auto GALIL_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_WEIGHT = 75;

    /**
     * @brief N/D
    */
    constexpr auto USP_WEIGHT = 5;

    /**
     * @brief N/D
    */
    constexpr auto AWP_WEIGHT = 30;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MP5NAVY_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto M249_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto M3_WEIGHT = 20;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto TMP_WEIGHT = 25;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_WEIGHT = 20;

    /**
     * @brief N/D
    */
    constexpr auto FLASH_BANG_WEIGHT = 1;

    /**
     * @brief N/D
    */
    constexpr auto DEAGLE_WEIGHT = 7;

    /**
     * @brief N/D
    */
    constexpr auto SG552_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto AK47_WEIGHT = 25;

    /**
     * @brief N/D
    */
    constexpr auto P90_WEIGHT = 26;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_WEIGHT = 0;

    //
    // Weapon max ammo.
    //

    /**
     * @brief N/D
    */
    constexpr auto MAX_AMMO_BUCKSHOT = 32;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_9MM = 120;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_556NATO = 90;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_556NATOBOX = 200;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_762NATO = 90;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_45ACP = 100;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_50AE = 35;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_338MAGNUM = 30;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_57MM = 100;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MAX_AMMO_357SIG = 52;

    /**
     * @brief N/D
    */
    constexpr auto MAX_AMMO_SMOKE_GRENADE = 1;

    /**
     * @brief N/D
    */
    constexpr auto MAX_AMMO_HE_GRENADE = 1;

    /**
     * @brief N/D
    */
    constexpr auto MAX_AMMO_FLASH_BANG = 2;

    /**
     * @brief N/D
    */
    constexpr auto MAX_AMMO_C4 = 1;

    //
    // Ammo buy amount.
    //

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_338MAG_BUY = 10;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_357SIG_BUY = 13;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_45ACP_BUY = 12;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_50AE_BUY = 7;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_556NATO_BUY = 30;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_556NATOBOX_BUY = 30;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_57MM_BUY = 50;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_762NATO_BUY = 30;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto AMMO_9MM_BUY = 30;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_BUCKSHOT_BUY = 8;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_FLASH_BANG_BUY = 1;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_HE_GRENADE_BUY = 1;

    /**
     * @brief N/D
    */
    constexpr auto AMMO_SMOKE_GRENADE_BUY = 1;

    enum class WeaponId
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        P228,

        /**
         * @brief N/D
        */
        Glock,

        /**
         * @brief N/D
        */
        Scout,

        /**
         * @brief N/D
        */
        HeGrenade,

        /**
         * @brief N/D
        */
        Xm1014,

        /**
         * @brief N/D
        */
        C4,

        /**
         * @brief N/D
        */
        Mac10,

        /**
         * @brief N/D
        */
        Aug,

        /**
         * @brief N/D
        */
        SmokeGrenade,

        /**
         * @brief N/D
        */
        Elite,

        /**
         * @brief N/D
        */
        Fiveseven,

        /**
         * @brief N/D
        */
        Ump45,

        /**
         * @brief N/D
        */
        Sg550,

        /**
         * @brief N/D
        */
        Galil,

        /**
         * @brief N/D
        */
        Famas,

        /**
         * @brief N/D
        */
        Usp,

        /**
         * @brief N/D
        */
        Glock18,

        /**
         * @brief N/D
        */
        Awp,

        /**
         * @brief N/D
        */
        Mp5Navy,

        /**
         * @brief N/D
        */
        M249,

        /**
         * @brief N/D
        */
        M3,

        /**
         * @brief N/D
        */
        M4A1,

        /**
         * @brief N/D
        */
        Tmp,

        /**
         * @brief N/D
        */
        G3Sg1,

        /**
         * @brief N/D
        */
        FlashBang,

        /**
         * @brief N/D
        */
        Deagle,

        /**
         * @brief N/D
        */
        Sg552,

        /**
         * @brief N/D
        */
        Ak47,

        /**
         * @brief N/D
        */
        Knife,

        /**
         * @brief N/D
        */
        P90,

        /**
         * @brief N/D
        */
        ShieldGun = 99
    };

    enum class AmmoType
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        Ammo338Magnum,

        /**
         * @brief N/D
        */
        Ammo762Nato,

        /**
         * @brief N/D
        */
        Ammo556Natobox,

        /**
         * @brief N/D
        */
        Ammo556Nato,

        /**
         * @brief N/D
        */
        AmmoBuckshot,

        /**
         * @brief N/D
        */
        Ammo45Acp,

        /**
         * @brief N/D
        */
        Ammo57Mm,

        /**
         * @brief N/D
        */
        Ammo50Ae,

        /**
         * @brief N/D
        */
        Ammo357Sig,

        /**
         * @brief N/D
        */
        Ammo9Mm,

        /**
         * @brief N/D
        */
        AmmoFlashBang,

        /**
         * @brief N/D
        */
        AmmoHeGrenade,

        /**
         * @brief N/D
        */
        AmmoSmokeGrenade,

        /**
         * @brief N/D
        */
        AmmoC4,

        /**
         * @brief N/D
        */
        AmmoMaxTypes
    };

    enum class WeaponClass
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        Knife,

        /**
         * @brief N/D
        */
        Pistol,

        /**
         * @brief N/D
        */
        Grenade,

        /**
         * @brief N/D
        */
        SubmachineGun,

        /**
         * @brief N/D
        */
        Shotgun,

        /**
         * @brief N/D
        */
        MachineGun,

        /**
         * @brief N/D
        */
        Rifle,

        /**
         * @brief N/D
        */
        SniperRifle,

        /**
         * @brief N/D
        */
        Max
    };

    enum class ShieldGun
    {
        /**
         * @brief N/D
        */
        Idle = 0,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        DrawnIdle,

        /**
         * @brief N/D
        */
        Up,

        /**
         * @brief N/D
        */
        Down
    };

    enum class ShieldGrenade
    {
        /**
         * @brief N/D
        */
        Idle = 4,

        /**
         * @brief N/D
        */
        Up,

        /**
         * @brief N/D
        */
        Down
    };

    enum class InventorySlot
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        Primary,

        /**
         * @brief N/D
        */
        Pistol,

        /**
         * @brief N/D
        */
        Knife,

        /**
         * @brief N/D
        */
        Grenade,

        /**
         * @brief N/D
        */
        C4
    };

    enum class BulletType
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        Player9Mm,

        /**
         * @brief N/D
        */
        PlayerMp5,

        /**
         * @brief N/D
        */
        Player357,

        /**
         * @brief N/D
        */
        PlayerBuckshot,

        /**
         * @brief N/D
        */
        PlayerCrowbar,

        /**
         * @brief N/D
        */
        Monster9Mm,

        /**
         * @brief N/D
        */
        MonsterMp5,

        /**
         * @brief N/D
        */
        Monster12Mm,

        /**
         * @brief N/D
        */
        Player45Acp,

        /**
         * @brief N/D
        */
        Player338Mag,

        /**
         * @brief N/D
        */
        Player762Mm,

        /**
         * @brief N/D
        */
        Player556Mm,

        /**
         * @brief N/D
        */
        Player50Ae,

        /**
         * @brief N/D
        */
        Player57Mm,

        /**
         * @brief N/D
        */
        Player357Sig
    };

    struct WeaponStruct
    {
        /**
         * @brief N/D
        */
        WeaponId id{};

        /**
         * @brief N/D
        */
        int price{};

        /**
         * @brief N/D
        */
        TeamName side{};

        /**
         * @brief N/D
        */
        InventorySlot slot{};

        /**
         * @brief N/D
        */
        int ammo_price{};
    };

    struct AutoBuyInfoStruct
    {
        /**
         * @brief N/D
        */
        int auto_buy_class{};

        /**
         * @brief N/D
        */
        char* command{};

        /**
         * @brief N/D
        */
        char* class_name{};
    };

    struct WeaponAliasInfo
    {
        /**
         * @brief N/D
        */
        char* alias{};

        /**
         * @brief N/D
        */
        WeaponId id{};
    };

    struct WeaponBuyAliasInfo
    {
        /**
         * @brief N/D
        */
        char* alias{};

        /**
         * @brief N/D
        */
        WeaponId id{};

        /**
         * @brief N/D
        */
        char* fail_name{};
    };

    struct WeaponClassAliasInfo
    {
        /**
         * @brief N/D
        */
        char* alias{};

        /**
         * @brief N/D
        */
        WeaponClass id{};
    };

    struct WeaponInfoStruct
    {
        /**
         * @brief N/D
        */
        WeaponId id{};

        /**
         * @brief N/D
        */
        int cost{};

        /**
         * @brief N/D
        */
        int clip_cost{};

        /**
         * @brief N/D
        */
        int buy_clip_size{};

        /**
         * @brief N/D
        */
        int gun_clip_size{};

        /**
         * @brief N/D
        */
        int max_rounds{};

        /**
         * @brief N/D
        */
        AmmoType ammo_type{};

        /**
         * @brief N/D
        */
        char* entity_name{};

        /**
         * @brief N/D
        */
        const char* ammo_name1{};

        /**
         * @brief N/D
        */
        const char* ammo_name2{};
    };

    struct AmmoInfoStruct
    {
        /**
         * @brief N/D
        */
        AmmoType ammo_type{};

        /**
         * @brief N/D
        */
        int clip_cost{};

        /**
         * @brief N/D
        */
        int buy_clip_size{};

        /**
         * @brief N/D
        */
        int max_rounds{};

        /**
         * @brief N/D
        */
        const char* ammo_name1{};

        /**
         * @brief N/D
        */
        const char* ammo_name2{};
    };

    struct WeaponSlotInfo
    {
        /**
         * @brief N/D
        */
        WeaponId id{};

        /**
         * @brief N/D
        */
        InventorySlot slot{};

        /**
         * @brief N/D
        */
        const char* weapon_name{};
    };
}
