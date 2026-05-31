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

#include <climits>

namespace cssdk
{
    /**
     * @brief Hud item selection slots.
    */
    constexpr auto MAX_WEAPON_SLOTS = 5;

    /**
     * @brief Hud item selection slots.
    */
    constexpr auto MAX_ITEM_TYPES = 6;

    /**
     * @brief Not really slots.
    */
    constexpr auto MAX_AMMO_SLOTS = 32;

    /**
     * @brief Hard coded item types.
    */
    constexpr auto MAX_ITEMS = 4;

    /**
     * @brief Default field of view.
    */
    constexpr auto DEFAULT_FOV = 90;

    /**
     * @brief N/D
    */
    constexpr auto HIDE_HUD_WEAPONS = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto HIDE_HUD_FLASHLIGHT = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto HIDE_HUD_ALL = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto HIDE_HUD_HEALTH = 1 << 3;

    /**
     * @brief N/D
    */
    constexpr auto HIDE_HUD_TIMER = 1 << 4;

    /**
     * @brief N/D
    */
    constexpr auto HIDE_HUD_MONEY = 1 << 5;

    /**
     * @brief N/D
    */
    constexpr auto HIDE_HUD_CROSSHAIR = 1 << 6;

    /**
     * @brief N/D
    */
    constexpr auto HIDE_HUD_OBSERVER_CROSSHAIR = 1 << 7;

    /**
     * @brief N/D
    */
    constexpr auto STATUS_ICON_HIDE = 0;

    /**
     * @brief N/D
    */
    constexpr auto STATUS_ICON_SHOW = 1;

    /**
     * @brief N/D
    */
    constexpr auto STATUS_ICON_FLASH = 2;

    /**
     * @brief N/D
    */
    constexpr auto STATUS_NIGHT_VISION_ON = 1;

    /**
     * @brief N/D
    */
    constexpr auto STATUS_NIGHT_VISION_OFF = 0;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_STATUS_NIGHT_VISION = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_STATUS_DEFUSER = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto SCORE_STATUS_DEAD = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto SCORE_STATUS_BOMB = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto SCORE_STATUS_VIP = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto SCORE_STATUS_DEF_KIT = 1 << 3;

    //
    // Player data i_user3.
    //

    /**
     * @brief N/D
    */
    constexpr auto PLAYER_CAN_SHOOT = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto PLAYER_FREEZE_TIME_OVER = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto PLAYER_IN_BOMB_ZONE = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto PLAYER_HOLDING_SHIELD = 1 << 3;

    /**
     * @brief N/D
    */
    constexpr auto PLAYER_PREVENT_DUCK = 1 << 4;

    /**
     * @brief The player can't climb ladder.
    */
    constexpr auto PLAYER_PREVENT_CLIMB = 1 << 5;

    /**
     * @brief N/D
    */
    constexpr auto PLAYER_PREVENT_JUMP = 1 << 6;

    //
    //
    //

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_1 = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_2 = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_3 = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_4 = 1 << 3;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_5 = 1 << 4;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_6 = 1 << 5;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_7 = 1 << 6;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_8 = 1 << 7;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_9 = 1 << 8;

    /**
     * @brief N/D
    */
    constexpr auto MENU_KEY_0 = 1 << 9;

    /**
     * @brief N/D
    */
    constexpr auto WEAPON_SUIT = 31;

    /**
     * @brief N/D
    */
    constexpr auto WEAPON_ALL_WEAPONS = INT_MAX;

    enum class HudPrint
    {
        /**
         * @brief N/D
        */
        Notify = 1,

        /**
         * @brief N/D
        */
        Console,

        /**
         * @brief N/D
        */
        Talk,

        /**
         * @brief N/D
        */
        Center,

        /**
         * @brief N/D
        */
        Radio
    };

    enum class VguiMenu
    {
        /**
         * @brief N/D
        */
        Team = 2,

        /**
         * @brief N/D
        */
        MapBriefing = 4,

        /**
         * @brief N/D
        */
        ClassT = 26,

        /**
         * @brief N/D
        */
        ClassCt,

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
        BuyShotGun,

        /**
         * @brief N/D
        */
        BuyRifle,

        /**
         * @brief N/D
        */
        BuySubMachineGun,

        /**
         * @brief N/D
        */
        BuyMachineGun,

        /**
         * @brief N/D
        */
        BuyItem
    };

    enum class VguiMenuSlot
    {
        /**
         * @brief N/D
        */
        BuyPistol = 1,

        /**
         * @brief N/D
        */
        BuyShotGun,

        /**
         * @brief N/D
        */
        BuySubMachineGun,

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
        BuyPrimAmmo,

        /**
         * @brief N/D
        */
        BuySecAmmo,

        /**
         * @brief N/D
        */
        BuyItem
    };

    enum class BuyItemMenuSlot
    {
        /**
         * @brief N/D
        */
        Vest = 1,

        /**
         * @brief N/D
        */
        VestHelm,

        /**
         * @brief N/D
        */
        FlashGrenade,

        /**
         * @brief N/D
        */
        HeGrenade,

        /**
         * @brief N/D
        */
        SmokeGrenade,

        /**
         * @brief N/D
        */
        NightVision,

        /**
         * @brief N/D
        */
        DefuseKit,

        /**
         * @brief N/D
        */
        Shield
    };

    enum class ChooseTeamMenuSlot
    {
        /**
         * @brief N/D
        */
        Undefined = -1,

        /**
         * @brief N/D
        */
        Terrorist = 1,

        /**
         * @brief N/D
        */
        Ct,

        /**
         * @brief N/D
        */
        Vip,

        /**
         * @brief N/D
        */
        Random = 5,

        /**
         * @brief N/D
        */
        Spectator
    };
}
