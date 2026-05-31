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

#include <cssdk/common/vector.h>

namespace cssdk
{
    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_TRIANGLES = 20000;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_VERTS = 2048;

    /**
     * @brief Total animation sequences -- KSH incremented.
    */
    constexpr auto MAX_STUDIO_SEQUENCES = 2048;

    /**
     * @brief Total textures.
    */
    constexpr auto MAX_STUDIO_SKINS = 100;

    /**
     * @brief Bones allowed at source movement.
    */
    constexpr auto MAX_STUDIO_SRC_BONES = 512;

    /**
     * @brief Total bones actually used.
    */
    constexpr auto MAX_STUDIO_BONES = 128;

    /**
     * @brief Sub-models per model.
    */
    constexpr auto MAX_STUDIO_MODELS = 32;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_BODY_PARTS = 32;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_GROUPS = 16;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_ANIMATIONS = 2048;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_MESHES = 256;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_EVENTS = 1024;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_PIVOTS = 256;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STUDIO_CONTROLLERS = 8;

    //
    // Lighting options.
    //

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_NF_FLAT_SHADE = 0x0001;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_NF_CHROME = 0x0002;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_NF_FULL_BRIGHT = 0x0004;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_NF_NO_MIPS = 0x0008;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_NF_ALPHA = 0x0010;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_NF_ADDITIVE = 0x0020;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_NF_MASKED = 0x0040;

    //
    // Motion flags.
    //

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_X = 0x0001;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_Y = 0x0002;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_Z = 0x0004;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_XR = 0x0008;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_YR = 0x0010;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_ZR = 0x0020;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_LX = 0x0040;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_LY = 0x0080;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_LZ = 0x0100;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_AX = 0x0200;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_AY = 0x0400;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_AZ = 0x0800;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_AXR = 0x1000;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_AYR = 0x2000;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_AZR = 0x4000;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_TYPES = 0x7FFF;

    /**
     * @brief Controller that wraps shortest distance.
    */
    constexpr auto STUDIO_RLOOP = 0x8000;

    //
    // Sequence flags.
    //

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_LOOPING = 0x0001;

    //
    // Bone flags.
    //

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_HAS_NORMALS = 0x0001;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_HAS_VERTICES = 0x0002;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_HAS_BBOX = 0x0004;

    /**
     * @brief If any of the textures have chrome on them.
    */
    constexpr auto STUDIO_HAS_CHROME = 0x0008;

    struct StudioHdr
    {
        /**
         * @brief N/D
        */
        int id{};

        /**
         * @brief N/D
        */
        int version{};

        /**
         * @brief N/D
        */
        char name[64]{};

        /**
         * @brief N/D
        */
        int length{};

        /**
         * @brief Ideal eye position.
        */
        Vector eye_position{};

        /**
         * @brief Ideal movement hull size.
        */
        Vector min{};

        /**
         * @brief N/D
        */
        Vector max{};

        /**
         * @brief Clipping bounding box.
        */
        Vector bb_min{};

        /**
         * @brief N/D
        */
        Vector bb_max{};

        /**
         * @brief N/D
        */
        int flags{};

        /**
         * @brief N/D
        */
        int num_bones{};

        /**
         * @brief N/D
        */
        int bone_index{};

        /**
         * @brief N/D
        */
        int num_bone_controllers{};

        /**
         * @brief N/D
        */
        int bone_controller_index{};

        /**
         * @brief Complex bounding boxes.
        */
        int num_hitboxes{};

        /**
         * @brief N/D
        */
        int hitbox_index{};

        /**
         * @brief Animation sequences.
        */
        int num_seq{};

        /**
         * @brief N/D
        */
        int seq_index{};

        /**
         * @brief Demand loaded sequences.
        */
        int num_seq_groups{};

        /**
         * @brief N/D
        */
        int seq_group_index{};

        /**
         * @brief Raw textures.
        */
        int num_textures{};

        /**
         * @brief N/D
        */
        int texture_index{};

        /**
         * @brief N/D
        */
        int texture_data_index{};

        /**
         * @brief Replaceable textures.
        */
        int num_skin_ref{};

        /**
         * @brief N/D
        */
        int num_skin_families{};

        /**
         * @brief N/D
        */
        int skin_index{};

        /**
         * @brief N/D
        */
        int num_bodyparts{};

        /**
         * @brief N/D
        */
        int bodypart_index{};

        /**
         * @brief Queryable attachable points.
        */
        int num_attachments{};

        /**
         * @brief N/D
        */
        int attachment_index{};

        /**
         * @brief N/D
        */
        int sound_table{};

        /**
         * @brief N/D
        */
        int sound_index{};

        /**
         * @brief N/D
        */
        int sound_groups{};

        /**
         * @brief N/D
        */
        int sound_group_index{};

        /**
         * @brief Animation node to animation node transition graph.
        */
        int num_transitions{};

        /**
         * @brief N/D
        */
        int transition_index{};
    };

    struct StudioSeqDesc
    {
        /**
         * @brief Sequence label.
        */
        char label[32]{};

        /**
         * @brief Frames per second.
        */
        float fps{};

        /**
         * @brief Looping/non-looping flags.
        */
        int flags{};

        /**
         * @brief N/D
        */
        int activity{};

        /**
         * @brief N/D
        */
        int act_weight{};

        /**
         * @brief N/D
        */
        int num_events{};

        /**
         * @brief N/D
        */
        int event_index{};

        /**
         * @brief Number of frames per sequence.
        */
        int num_frames{};

        /**
         * @brief Number of foot pivots.
        */
        int num_pivots{};

        /**
         * @brief N/D
        */
        int pivot_index{};

        /**
         * @brief N/D
        */
        int motion_type{};

        /**
         * @brief N/D
        */
        int motion_bone{};

        /**
         * @brief N/D
        */
        Vector linear_movement{};

        /**
         * @brief N/D
        */
        int auto_move_pos_index{};

        /**
         * @brief N/D
        */
        int auto_move_angle_index{};

        /**
         * @brief Per sequence bounding box.
        */
        Vector bb_min{};

        /**
         * @brief N/D
        */
        Vector bb_max{};

        /**
         * @brief N/D
        */
        int num_blends{};

        /**
         * @brief \c StudioAnim pointer relative to start of sequence group data [blend][bone][X, Y, Z, XR, YR, ZR].
        */
        int anim_index{};

        /**
         * @brief X, Y, Z, XR, YR, ZR.
        */
        int blend_type[2]{};

        /**
         * @brief Starting value.
        */
        float blend_start[2]{};

        /**
         * @brief Ending value.
        */
        float blend_end[2]{};

        /**
         * @brief N/D
        */
        int blend_parent{};

        /**
         * @brief Sequence group for demand loading.
        */
        int seq_group{};

        /**
         * @brief Transition node at entry.
        */
        int entry_node{};

        /**
         * @brief Transition node at exit.
        */
        int exit_node{};

        /**
         * @brief Transition rules.
        */
        int node_flags{};

        /**
         * @brief Auto advancing sequences.
        */
        int next_seq{};
    };

    struct StudioEvent
    {
        /**
         * @brief N/D
        */
        int frame{};

        /**
         * @brief N/D
        */
        int event{};

        /**
         * @brief N/D
        */
        int type{};

        /**
         * @brief N/D
        */
        char options[64]{};
    };
}
