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
#include <cssdk/common/model.h>
#include <cssdk/common/trace.h>
#include <cssdk/common/user_cmd.h>
#include <cssdk/common/vector.h>
#include <cssdk/pm_shared/pm_move_vars.h>
#include <cssdk/pm_shared/pm_trace.h>

//-V::591,730

namespace cssdk
{
    /**
     * @brief N/D
    */
    constexpr auto MAX_PHYS_ENTS = 600;

    /**
     * @brief N/D
    */
    constexpr auto MAX_MOVE_ENTS = 64;

    /**
     * @brief N/D
    */
    constexpr auto MAX_CLIP_PLANES = 5;

    /**
     * @brief N/D
    */
    constexpr auto PM_NORMAL = 0x00000000;

    /**
     * @brief N/D
    */
    constexpr auto PM_STUDIO_IGNORE = 0x00000001;

    /**
     * @brief N/D
    */
    constexpr auto PM_STUDIO_BOX = 0x00000002;

    /**
     * @brief N/D
    */
    constexpr auto PM_GLASS_IGNORE = 0x00000004;

    /**
     * @brief N/D
    */
    constexpr auto PM_WORLD_ONLY = 0x00000008;

    /**
     * @brief N/D
    */
    constexpr auto PM_TRACE_LINE_PHYS_ENTS_ONLY = 0;

    /**
     * @brief N/D
    */
    constexpr auto PM_TRACE_LINE_ANY_VISIBLE = 1;

    struct PhysEntity
    {
        /**
         * @brief Name of model, or "player" or "world".
        */
        char name[32]{};

        /**
         * @brief N/D
        */
        int player{};

        /**
         * @brief Model's origin in world coordinates.
        */
        Vector origin{};

        /**
         * @brief Only for bsp models.
        */
        Model* bsp_model{};

        /**
         * @brief \c SolidType::BoundingBox, but studio clip intersections.
        */
        Model* studio_model{};

        /**
         * @brief Only for non-bsp models.
        */
        Vector min_size{};

        /**
         * @brief Only for non-bsp models.
        */
        Vector max_size{};

        /**
         * @brief For client or server to use to identify (index into edicts or cl_entities).
        */
        int info{};

        /**
         * @brief Rotated entities need this info for hull testing to work.
        */
        Vector angles{};

        /**
         * @brief Triggers and func_door type WATER brushes are \c SolidType::NotSolid.
        */
        SolidType solid{};

        /**
         * @brief BSP Contents for such things like fun_door water brushes.
        */
        int skin{};

        /**
         * @brief So we can ignore glass.
        */
        Rendering render_mode{};

        /**
         * @brief N/D
        */
        float frame{};

        /**
         * @brief N/D
        */
        int sequence{};

        /**
         * @brief N/D
        */
        byte controller[4]{};

        /**
         * @brief N/D
        */
        byte blending[2]{};

        /**
         * @brief N/D
        */
        MoveTypeEntity move_type{};

        /**
         * @brief N/D
        */
        int take_damage{};

        /**
         * @brief N/D
        */
        int blood_decal{};

        /**
         * @brief N/D
        */
        int team{};

        /**
         * @brief N/D
        */
        int class_number{};

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

    struct PlayerMove
    {
        /**
         * @brief N/D
        */
        int player_index{};

        /**
         * @brief N/D
        */
        qboolean server{};

        /**
         * @brief N/D
        */
        qboolean multiplayer{};

        /**
         * @brief N/D
        */
        float time{};

        /**
         * @brief N/D
        */
        float frame_time{};

        /**
         * @brief N/D
        */
        Vector forward{};

        /**
         * @brief N/D
        */
        Vector right{};

        /**
         * @brief N/D
        */
        Vector up{};

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
        Vector old_angles{};

        /**
         * @brief N/D
        */
        Vector velocity{};

        /**
         * @brief N/D
        */
        Vector move_direction{};

        /**
         * @brief N/D
        */
        Vector base_velocity{};

        /**
         * @brief N/D
        */
        Vector view_ofs{};

        /**
         * @brief N/D
        */
        float duck_time{};

        /**
         * @brief N/D
        */
        qboolean in_duck{};

        /**
         * @brief N/D
        */
        int time_step_sound{};

        /**
         * @brief N/D
        */
        int step_left{};

        /**
         * @brief N/D
        */
        float fall_velocity{};

        /**
         * @brief N/D
        */
        Vector punch_angle{};

        /**
         * @brief N/D
        */
        float swim_time{};

        /**
         * @brief N/D
        */
        float next_primary_attack{};

        /**
         * @brief N/D
        */
        int effects{};

        /**
         * @brief N/D
        */
        int flags{};

        /**
         * @brief N/D
        */
        int use_hull{};

        /**
         * @brief N/D
        */
        float gravity{};

        /**
         * @brief N/D
        */
        float friction{};

        /**
         * @brief N/D
        */
        int old_buttons{};

        /**
         * @brief N/D
        */
        float water_jump_time{};

        /**
         * @brief N/D
        */
        qboolean dead{};

        /**
         * @brief N/D
        */
        DeathState dead_flag{};

        /**
         * @brief N/D
        */
        int spectator{};

        /**
         * @brief N/D
        */
        MoveTypeEntity move_type{};

        /**
         * @brief N/D
        */
        int on_ground{};

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
        int old_water_level{};

        /**
         * @brief N/D
        */
        char texture_name[256]{};

        /**
         * @brief N/D
        */
        char texture_type{};

        /**
         * @brief N/D
        */
        float max_speed{};

        /**
         * @brief N/D
        */
        float client_max_speed{};

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

        /**
         * @brief N/D
        */
        int num_phys_ent{};

        /**
         * @brief N/D
        */
        PhysEntity phys_ents[MAX_PHYS_ENTS]{};

        /**
         * @brief N/D
        */
        int num_move_ent{};

        /**
         * @brief N/D
        */
        PhysEntity move_ents[MAX_MOVE_ENTS]{};

        /**
         * @brief N/D
        */
        int num_vis_ent{};

        /**
         * @brief N/D
        */
        PhysEntity vis_ents[MAX_PHYS_ENTS]{};

        /**
         * @brief N/D
        */
        UserCmd cmd{};

        /**
         * @brief N/D
        */
        int num_touch{};

        /**
         * @brief N/D
        */
        PmTrace touch_index[MAX_PHYS_ENTS]{};

        /**
         * @brief N/D
        */
        char phys_info[MAX_PHYS_INFO_STRING]{};

        /**
         * @brief N/D
        */
        MoveVars* move_vars{};

        /**
         * @brief N/D
        */
        Vector player_min_size[MAX_MAP_HULLS]{};

        /**
         * @brief N/D
        */
        Vector player_max_size[MAX_MAP_HULLS]{};

        //
        // Common functions.
        //

        /**
         * @brief N/D
        */
        const char* (*pm_info_value_for_key)(const char* s, const char* key){};

        /**
         * @brief N/D
        */
        void (*pm_particle)(Vector& origin, int color, float life, int z_pos, int z_velocity){};

        /**
         * @brief N/D
        */
        int (*pm_test_player_position)(Vector& pos, PmTrace* trace){};

        /**
         * @brief N/D
        */
        void (*con_notify_print)(int pos, const char* format, ...){};

        /**
         * @brief N/D
        */
        void (*con_dev_print)(const char* format, ...){};

        /**
         * @brief N/D
        */
        void (*con_print)(const char* format, ...){};

        /**
         * @brief N/D
        */
        double (*sys_float_time)(){};

        /**
         * @brief N/D
        */
        void (*pm_stuck_touch)(int hit_ent, PmTrace* trace_result){};

        /**
         * @brief N/D
        */
        int (*pm_point_contents)(Vector& pos, int* true_contents){};

        /**
         * @brief N/D
        */
        int (*pm_true_point_contents)(Vector& pos){};

        /**
         * @brief N/D
        */
        int (*pm_hull_point_contents)(Hull* hull, int num, Vector& pos){};

        /**
         * @brief N/D
        */
        PmTrace (*pm_player_trace)(Vector& start, Vector& end, int trace_flags, int ignore_pe){};

        /**
         * @brief N/D
        */
        PmTrace* (*pm_trace_line)(Vector& start, Vector& end, int flags, int use_hull, int ignore_pe){};

        /**
         * @brief N/D
        */
        int32 (*random_long)(int32 low, int32 high){};

        /**
         * @brief N/D
        */
        float (*random_float)(float low, float high){};

        /**
         * @brief N/D
        */
        int (*pm_get_model_type)(Model* mdl){};

        /**
         * @brief N/D
        */
        void (*pm_get_model_bounds)(Model* mdl, Vector& min_size, Vector& max_size){};

        /**
         * @brief N/D
        */
        void (*pm_hull_for_bsp)(PhysEntity* phys_ent, float* offset){};

        /**
         * @brief N/D
        */
        float (*pm_trace_model)(PhysEntity* phys_ent, Vector& start, Vector& end, Trace* trace){};

        /**
         * @brief N/D
        */
        int (*com_file_size)(const char* file_name){};

        /**
         * @brief N/D
        */
        byte* (*com_load_file)(const char* path, int use_hunk, int* length){};

        /**
         * @brief N/D
        */
        void (*com_free_file)(void* buffer){};

        /**
         * @brief N/D
        */
        char* (*mem_file_gets)(byte* mem_file, int file_size, int* file_pos, char* buffer, int buffer_size){};

        //
        // Functions.
        //

        /**
         * @brief Run functions for this frame?
        */
        qboolean run_functions{};

        /**
         * @brief N/D
        */
        void (*pm_play_sound)(int channel, const char* sample, float volume, float attenuation, int flags, int pitch){};

        /**
         * @brief N/D
        */
        const char* (*pm_trace_texture)(int ground, Vector& start, Vector& end){};

        /**
         * @brief N/D
        */
        void (*pm_playback_event_full)(int flags, int client_index, unsigned short event_index, float delay, Vector& origin,
                                       Vector& angles, float f_param1, float f_param2, int i_param1, int i_param2,
                                       qboolean b_param1, qboolean b_param2){};

        /**
         * @brief N/D
        */
        PmTrace (*pm_player_trace_ex)(Vector& start, Vector& end, int trace_flags, int (*ignore)(PhysEntity* phys_ent)){};

        /**
         * @brief N/D
        */
        int (*pm_test_player_position_ex)(Vector& pos, PmTrace* trace, int (*ignore)(PhysEntity* phys_ent)){};

        /**
         * @brief N/D
        */
        PmTrace* (*pm_trace_line_ex)(Vector& start, Vector& end, int flags, int use_hull,
                                     int (*ignore)(PhysEntity* phys_ent)){};
    };
}
