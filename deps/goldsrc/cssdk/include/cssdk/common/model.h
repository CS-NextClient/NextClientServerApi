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
    constexpr auto SURF_PLANE_BACK = 2;

    /**
     * @brief N/D
    */
    constexpr auto SURF_DRAW_SKY = 4;

    /**
     * @brief N/D
    */
    constexpr auto SURF_DRAW_SPRITE = 8;

    /**
     * @brief N/D
    */
    constexpr auto SURF_DRAW_TURB = 0x10;

    /**
     * @brief N/D
    */
    constexpr auto SURF_DRAW_TILED = 0x20;

    /**
     * @brief N/D
    */
    constexpr auto SURF_DRAW_BACKGROUND = 0x40;

    /**
     * @brief N/D
    */
    constexpr auto MAX_MODEL_NAME = 64;

    /**
     * @brief N/D
    */
    constexpr auto TEX_SPECIAL = 1;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_RENDER = 1;

    /**
     * @brief N/D
    */
    constexpr auto STUDIO_EVENTS = 2;

    /**
     * @brief N/D
    */
    constexpr auto PLANE_ANY_Z = 5;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_Z_CLIP_PLANE = 5;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_LEFT_CLIP = 0x0001;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_TOP_CLIP = 0x0002;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_RIGHT_CLIP = 0x0004;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_MODEL_VERSION = 0x006;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_BOTTOM_CLIP = 0x0008;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_Z_CLIP = 0x0010;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_ON_SEAM = 0x0020;

    /**
     * @brief N/D
    */
    constexpr auto ALIAS_XY_CLIP_MASK = 0x000F;

    /**
     * @brief N/D
    */
    constexpr float ZI_SCALE = 0x8000;

    /**
     * @brief Used to align key data structures.
    */
    constexpr auto CACHE_SIZE = 32;

    /**
     * @brief N/D
    */
    constexpr auto MAX_INFO_STRING = 256;

    /**
     * @brief N/D
    */
    constexpr auto MAX_SCOREBOARD_NAME = 32;

    enum class ModelType
    {
        /**
         * @brief N/D
        */
        Bad = -1,

        /**
         * @brief N/D
        */
        Brush,

        /**
         * @brief N/D
        */
        Sprite,

        /**
         * @brief N/D
        */
        Alias,

        /**
         * @brief N/D
        */
        Studio
    };

    enum class SyncType
    {
        /**
         * @brief N/D
        */
        Sync,

        /**
         * @brief N/D
        */
        Rand
    };

    struct MVertex
    {
        /**
         * @brief N/D
        */
        Vector position{};
    };

    struct Hull
    {
        /**
         * @brief N/D
        */
        struct DClipNode* clip_nodes{};

        /**
         * @brief N/D
        */
        struct MPlane* planes{};

        /**
         * @brief N/D
        */
        int first_clip_node{};

        /**
         * @brief N/D
        */
        int last_clip_node{};

        /**
         * @brief N/D
        */
        Vector clip_min_size{};

        /**
         * @brief N/D
        */
        Vector clip_max_size{};
    };

    struct CacheUser
    {
        /**
         * @brief N/D
        */
        void* data{};
    };

    struct Model
    {
        /**
         * @brief N/D
        */
        char name[MAX_MODEL_NAME]{};

        /**
         * @brief N/D
        */
        qboolean need_load{};

        /**
         * @brief N/D
        */
        ModelType type{};

        /**
         * @brief N/D
        */
        int num_frames{};

        /**
         * @brief N/D
        */
        SyncType sync{};

        /**
         * @brief N/D
        */
        int flags{};

        //
        // Volume occupied by the model.
        //

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
        float radius{};

        //
        // Brush model.
        //

        /**
         * @brief N/D
        */
        int first_model_surface{};

        /**
         * @brief N/D
        */
        int num_model_surfaces{};

        /**
         * @brief N/D
        */
        int num_submodels{};

        /**
         * @brief N/D
        */
        struct DModel* submodels{};

        /**
         * @brief N/D
        */
        int num_planes{};

        /**
         * @brief N/D
        */
        MPlane* planes{};

        /**
         * @brief Number of visible leafs, not counting 0.
        */
        int num_leafs{};

        /**
         * @brief N/D
        */
        struct MLeaf* leafs{};

        /**
         * @brief N/D
        */
        int num_vertexes{};

        /**
         * @brief N/D
        */
        MVertex* vertexes{};

        /**
         * @brief N/D
        */
        int num_edges{};

        /**
         * @brief N/D
        */
        struct MEdge* edges{};

        /**
         * @brief N/D
        */
        int num_nodes{};

        /**
         * @brief N/D
        */
        struct MNode* nodes{};

        /**
         * @brief N/D
        */
        int num_tex_info{};

        /**
         * @brief N/D
        */
        struct MTexInfo* tex_info{};

        /**
         * @brief N/D
        */
        int num_surfaces{};

        /**
         * @brief N/D
        */
        struct MSurface* surfaces{};

        /**
         * @brief N/D
        */
        int num_surf_edges{};

        /**
         * @brief N/D
        */
        int* surf_edges{};

        /**
         * @brief N/D
        */
        int num_clip_nodes{};

        /**
         * @brief N/D
        */
        DClipNode* clip_nodes{};

        /**
         * @brief N/D
        */
        int num_mark_surfaces{};

        /**
         * @brief N/D
        */
        MSurface** mark_surfaces{};

        /**
         * @brief N/D
        */
        Hull hulls[MAX_MAP_HULLS]{};

        /**
         * @brief N/D
        */
        int num_textures{};

        /**
         * @brief N/D
        */
        struct Texture** textures{};

        /**
         * @brief N/D
        */
        byte* vis_data{};

        /**
         * @brief N/D
        */
        Color24* light_data{};

        /**
         * @brief N/D
        */
        char* entities{};

        //
        // Additional model data
        //

        /**
         * @brief Only access through \c Mod_Extradata.
        */
        CacheUser cache{};
    };
}
