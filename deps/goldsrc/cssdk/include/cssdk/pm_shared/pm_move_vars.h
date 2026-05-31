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
     * @brief Physics variables.
    */
    struct MoveVars
    {
        /**
         * @brief Gravity for map.
        */
        float gravity{};

        /**
         * @brief Deceleration when not moving.
        */
        float stop_speed{};

        /**
         * @brief Max allowed speed.
        */
        float max_speed{};

        /**
         * @brief N/D
        */
        float spectator_max_speed{};

        /**
         * @brief Acceleration factor.
        */
        float accelerate{};

        /**
         * @brief Acceleration factor when in open air.
        */
        float air_accelerate{};

        /**
         * @brief Acceleration factor when in water.
        */
        float water_accelerate{};

        /**
         * @brief N/D
        */
        float friction{};

        /**
         * @brief Extra friction near dropofs.
        */
        float edge_friction{};

        /**
         * @brief Less in water.
        */
        float water_friction{};

        /**
         * @brief 1.0.
        */
        float entity_gravity{};

        /**
         * @brief Wall bounce value. 1.0.
        */
        float bounce{};

        /**
         * @brief sv_stepsize.
        */
        float step_size{};

        /**
         * @brief Maximum server velocity.
        */
        float max_velocity{};

        /**
         * @brief Max z-buffer range (for GL).
        */
        float z_max{};

        /**
         * @brief Water wave height (for GL).
        */
        float wave_height{};

        /**
         * @brief Play footstep sounds.
        */
        qboolean footsteps{};

        /**
         * @brief Name of the sky map.
        */
        char sky_name[32]{};

        /**
         * @brief N/D
        */
        float roll_angle{};

        /**
         * @brief N/D
        */
        float roll_speed{};

        /**
         * @brief N/D
        */
        float sky_color_r{};

        /**
         * @brief N/D
        */
        float sky_color_g{};

        /**
         * @brief N/D
        */
        float sky_color_b{};

        /**
         * @brief N/D
        */
        float sky_vec_x{};

        /**
         * @brief N/D
        */
        float sky_vec_y{};

        /**
         * @brief N/D
        */
        float sky_vec_z{};
    };
}
