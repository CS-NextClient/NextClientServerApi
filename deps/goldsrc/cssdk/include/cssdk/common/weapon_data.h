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
     * @brief Info about weapons player might have in his/her possession.
    */
    struct WeaponData
    {
        /**
         * @brief N/D
        */
        int id{};

        /**
         * @brief N/D
        */
        int clip{};

        /**
         * @brief N/D
        */
        float next_primary_attack{};

        /**
         * @brief N/D
        */
        float next_secondary_attack{};

        /**
         * @brief N/D
        */
        float time_weapon_idle{};

        /**
         * @brief N/D
        */
        qboolean in_reload{};

        /**
         * @brief N/D
        */
        qboolean in_special_reload{};

        /**
         * @brief N/D
        */
        float next_reload{};

        /**
         * @brief N/D
        */
        float pump_time{};

        /**
         * @brief N/D
        */
        float reload_time{};

        /**
         * @brief N/D
        */
        float aimed_damage{};

        /**
         * @brief N/D
        */
        float next_aim_bonus{};

        /**
         * @brief N/D
        */
        qboolean in_zoom{};

        /**
         * @brief N/D
        */
        int weapon_state{};

        /**
         * @brief N/D
        */
        int i_user1{};

        /**
         * @brief N/D
        */
        int i_user2{};

        /**
         * @brief N/D
        */
        int i_user3{};

        /**
         * @brief N/D
        */
        int i_user4{};

        /**
         * @brief N/D
        */
        float f_user1{};

        /**
         * @brief N/D
        */
        float f_user2{};

        /**
         * @brief N/D
        */
        float f_user3{};

        /**
         * @brief N/D
        */
        float f_user4{};
    };
}
