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
#include <cssdk/common/vector.h>

namespace cssdk
{
    /**
     * @brief N/D
    */
    constexpr auto ENTITY_NORMAL = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto ENTITY_BEAM = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto ENTITY_UNINITIALIZED = 1 << 30;

    /**
     * @brief Entity state is used for the baseline and for delta compression
     * of a packet of entities that is sent to a client.
    */
    struct EntityState
    {
        /**
         * @brief Fields which are filled in by routines outside of delta compression.
        */
        int entity_type{};

        /**
         * @brief Index into cl_entities array for this entity.
        */
        int number{};

        /**
         * @brief N/D
        */
        float msg_time{};

        /**
         * @brief Message number last time the player/entity state was updated.
        */
        int message_num{};

        /**
         * @brief N/D
        */
        Vector origin{};

        /**
         * @brief N/D
        */
        Vector angles{};

        /**
         * @brief N/D
        */
        int model_index{};

        /**
         * @brief N/D
        */
        int sequence{};

        /**
         * @brief N/D
        */
        float frame{};

        /**
         * @brief N/D
        */
        int color_map{};

        /**
         * @brief N/D
        */
        short skin{};

        /**
         * @brief N/D
        */
        short solid{};

        /**
         * @brief N/D
        */
        int effects{};

        /**
         * @brief N/D
        */
        float scale{};

        /**
         * @brief N/D
        */
        byte entity_flags{};

        /**
         * @brief N/D
        */
        Rendering render_mode{};

        /**
         * @brief N/D
        */
        int render_amount{};

        /**
         * @brief N/D
        */
        Color24 render_color{};

        /**
         * @brief N/D
        */
        RenderingFx render_fx{};

        /**
         * @brief N/D
        */
        MoveTypeEntity move_type{};

        /**
         * @brief N/D
        */
        float anim_time{};

        /**
         * @brief N/D
        */
        float frame_rate{};

        /**
         * @brief N/D
        */
        int body{};

        /**
         * @brief N/D
        */
        byte controller[4]{};

        /**
         * @brief N/D
        */
        byte blending[4]{};

        /**
         * @brief N/D
        */
        Vector velocity{};

        /**
         * @brief N/D
        */
        Vector min_size{};

        /**
         * @brief N/D
        */
        Vector max_size{};

        /**
         * @brief N/D
        */
        int aim_entity{};

        /**
         * @brief If owned by a player, the index of that player (for projectiles).
        */
        int owner{};

        /**
         * @brief Friction, for prediction.
        */
        float friction{};

        /**
         * @brief Gravity multiplier.
        */
        float gravity{};

        /**
         * @brief N/D
        */
        int team{};

        /**
         * @brief N/D
        */
        int player_class{};

        /**
         * @brief N/D
        */
        int health{};

        /**
         * @brief N/D
        */
        qboolean spectator{};

        /**
         * @brief N/D
        */
        int weapon_model{};

        /**
         * @brief N/D
        */
        int gait_sequence{};

        /**
         * @brief If standing on conveyor, e.g.
        */
        Vector base_velocity{};

        /**
         * @brief Use the crouched hull, or the regular player hull.
        */
        int use_hull{};

        /**
         * @brief Latched buttons last time state updated.
        */
        int old_buttons{};

        /**
         * @brief -1 = in air, else move entity number.
        */
        int on_ground{};

        /**
         * @brief N/D
        */
        int step_left{};

        /**
         * @brief How fast we are falling.
        */
        float fall_velocity{};

        /**
         * @brief N/D
        */
        float fov{};

        /**
         * @brief N/D
        */
        int weapon_anim{};

        /**
         * @brief N/D
        */
        Vector start_pos{};

        /**
         * @brief N/D
        */
        Vector end_pos{};

        /**
         * @brief N/D
        */
        float impact_time{};

        /**
         * @brief N/D
        */
        float start_time{};

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

        /**
         * @brief N/D
        */
        Vector v_user1{};

        /**
         * @brief N/D
        */
        Vector v_user2{};

        /**
         * @brief N/D
        */
        Vector v_user3{};

        /**
         * @brief N/D
        */
        Vector v_user4{};
    };

    struct ClientData
    {
        /**
         * @brief N/D
        */
        Vector origin{};

        /**
         * @brief N/D
        */
        Vector velocity{};

        /**
         * @brief N/D
        */
        int view_model{};

        /**
         * @brief N/D
        */
        Vector punch_angle{};

        /**
         * @brief N/D
        */
        int flags{};

        /**
         * @brief N/D
        */
        int water_level{};

        /**
         * @brief N/D
        */
        int water_type{};

        /**
         * @brief N/D
        */
        Vector view_ofs{};

        /**
         * @brief N/D
        */
        float health{};

        /**
         * @brief N/D
        */
        qboolean in_duck{};

        /**
         * @brief N/D
        */
        int weapons{};

        /**
         * @brief N/D
        */
        int time_step_sound{};

        /**
         * @brief N/D
        */
        int duck_time{};

        /**
         * @brief N/D
        */
        int swim_time{};

        /**
         * @brief N/D
        */
        int water_jump_time{};

        /**
         * @brief N/D
        */
        float max_speed{};

        /**
         * @brief N/D
        */
        float field_of_view{};

        /**
         * @brief N/D
        */
        int weapon_anim{};

        /**
         * @brief N/D
        */
        int id{};

        /**
         * @brief N/D
        */
        int ammo_shells{};

        /**
         * @brief N/D
        */
        int ammo_nails{};

        /**
         * @brief N/D
        */
        int ammo_cells{};

        /**
         * @brief N/D
        */
        int ammo_rockets{};

        /**
         * @brief N/D
        */
        float next_attack{};

        /**
         * @brief N/D
        */
        int tf_state{};

        /**
         * @brief N/D
        */
        int push_msec{};

        /**
         * @brief N/D
        */
        DeathState dead_flag{};

        /**
         * @brief N/D
        */
        char phys_info[MAX_PHYS_INFO_STRING]{};

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

        /**
         * @brief N/D
        */
        Vector v_user1{};

        /**
         * @brief N/D
        */
        Vector v_user2{};

        /**
         * @brief N/D
        */
        Vector v_user3{};

        /**
         * @brief N/D
        */
        Vector v_user4{};
    };
}
