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
    /**
     * @brief N/D
    */
    constexpr auto DHF_ROUND_STARTED = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto DHF_HOSTAGE_SEEN_FAR = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto DHF_HOSTAGE_SEEN_NEAR = 1 << 3;

    /**
     * @brief N/D
    */
    constexpr auto DHF_HOSTAGE_USED = 1 << 4;

    /**
     * @brief N/D
    */
    constexpr auto DHF_HOSTAGE_INJURED = 1 << 5;

    /**
     * @brief N/D
    */
    constexpr auto DHF_HOSTAGE_KILLED = 1 << 6;

    /**
     * @brief N/D
    */
    constexpr auto DHF_FRIEND_SEEN = 1 << 7;

    /**
     * @brief N/D
    */
    constexpr auto DHF_ENEMY_SEEN = 1 << 8;

    /**
     * @brief N/D
    */
    constexpr auto DHF_FRIEND_INJURED = 1 << 9;

    /**
     * @brief N/D
    */
    constexpr auto DHF_FRIEND_KILLED = 1 << 10;

    /**
     * @brief N/D
    */
    constexpr auto DHF_ENEMY_KILLED = 1 << 11;

    /**
     * @brief N/D
    */
    constexpr auto DHF_BOMB_RETRIEVED = 1 << 12;

    /**
     * @brief N/D
    */
    constexpr auto DHF_AMMO_EXHAUSTED = 1 << 15;

    /**
     * @brief N/D
    */
    constexpr auto DHF_IN_TARGET_ZONE = 1 << 16;

    /**
     * @brief N/D
    */
    constexpr auto DHF_IN_RESCUE_ZONE = 1 << 17;

    /**
     * @brief N/D
    */
    constexpr auto DHF_IN_ESCAPE_ZONE = 1 << 18;

    /**
     * @brief N/D
    */
    constexpr auto DHF_IN_VIP_SAFETY_ZONE = 1 << 19;

    /**
     * @brief N/D
    */
    constexpr auto DHF_NIGHT_VISION = 1 << 20;

    /**
     * @brief N/D
    */
    constexpr auto DHF_HOSTAGE_CT_MOVE = 1 << 21;

    /**
     * @brief N/D
    */
    constexpr auto DHF_SPEC_DUCK = 1 << 22;

    /**
     * @brief N/D
    */
    constexpr auto DHM_ROUND_CLEAR = DHF_ROUND_STARTED | DHF_HOSTAGE_KILLED | DHF_FRIEND_KILLED | DHF_BOMB_RETRIEVED;

    /**
     * @brief N/D
    */
    constexpr auto DHM_CONNECT_CLEAR = DHF_HOSTAGE_SEEN_FAR | DHF_HOSTAGE_SEEN_NEAR | DHF_HOSTAGE_USED | DHF_HOSTAGE_INJURED |
        DHF_FRIEND_SEEN | DHF_ENEMY_SEEN | DHF_FRIEND_INJURED | DHF_ENEMY_KILLED | DHF_AMMO_EXHAUSTED | DHF_IN_TARGET_ZONE |
        DHF_IN_RESCUE_ZONE | DHF_IN_ESCAPE_ZONE | DHF_IN_VIP_SAFETY_ZONE | DHF_HOSTAGE_CT_MOVE | DHF_SPEC_DUCK;

    /**
     * @brief Dummy. DON'T USE THIS!
    */
    using HintMessageQueue = uint8[24];
}
