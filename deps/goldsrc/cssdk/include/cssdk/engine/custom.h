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
     * @brief Must match value in quakedefs.h.
    */
    constexpr auto MAX_QPATH = 64;

    /**
     * @brief N/D
    */
    constexpr auto MAX_RESOURCE_LIST = 1280;

    /**
     * @brief Disconnect if we can't get this file.
    */
    constexpr auto RES_FATAL_IF_MISSING = 1 << 0;

    /**
     * @brief Do we have the file locally, did we get it ok?
    */
    constexpr auto RES_WAS_MISSING = 1 << 1;

    /**
     * @brief Is this resource one that corresponds to another player's customization
     * or is it a server startup resource.
    */
    constexpr auto RES_CUSTOM = 1 << 2;

    /**
     * @brief Already requested a download of this one.
    */
    constexpr auto RES_REQUESTED = 1 << 3;

    /**
     * @brief Already precached.
    */
    constexpr auto RES_PRECACHED = 1 << 4;

    /**
     * @brief Download always even if available on client.
    */
    constexpr auto RES_ALWAYS = 1 << 5;

    /**
     * @brief N/D
    */
    constexpr auto RES_UNK_6 = 1 << 6;

    /**
     * @brief Check file on client.
    */
    constexpr auto RES_CHECK_FILE = 1 << 7;

    /**
     * @brief N/D
    */
    constexpr auto FCUST_FROM_HPAK = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto FCUST_WIPE_DATA = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto FCUST_IGNORE_INIT = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto FCUST_VALIDATED = 1 << 3;

    enum class ResourceType
    {
        /**
         * @brief N/D
        */
        Sound = 0,

        /**
         * @brief N/D
        */
        Skin,

        /**
         * @brief N/D
        */
        Model,

        /**
         * @brief N/D
        */
        Decal,

        /**
         * @brief N/D
        */
        Generic,

        /**
         * @brief N/D
        */
        EventScript,

        /**
         * @brief N/D
        */
        World,

        /**
         * @brief N/D
        */
        Unk,

        /**
         * @brief N/D
        */
        Max
    };

    struct ResourceInfoS
    {
        /**
         * @brief N/D
        */
        int size{};
    };

    struct ResourceInfo
    {
        /**
         * @brief N/D
        */
        ResourceInfoS info[static_cast<int>(ResourceType::Max)]{};
    };

    struct Resource
    {
        /**
         * @brief File name to download/precache.
        */
        char file_name[MAX_QPATH]{};

        /**
         * @brief N/D
        */
        ResourceType type{};

        /**
         * @brief For \c ResourceType::Decal
        */
        int index{};

        /**
         * @brief Size in bytes if this must be downloaded.
        */
        int download_size{};

        /**
         * @brief N/D
        */
        unsigned char flags{};

        /**
         * @brief To determine if we already have it.
        */
        unsigned char md5_hash[16]{};

        /**
         * @brief Which player index this resource is associated with, if it's a custom resource.
        */
        unsigned char player_num{};

        /**
         * @brief For future expansion.
        */
        unsigned char reserved[32]{};

        /**
         * @brief Next in chain.
        */
        Resource* next{};

#if !defined(HLTV)
        /**
         * @brief N/D
        */
        Resource* prev{};
#else
        /**
         * @brief N/D
        */
        unsigned char* data{};
#endif
    };

    struct Customization
    {
        /**
         * @brief Is this customization in use.
        */
        qboolean in_use{};

        /**
         * @brief The resource for this customization.
        */
        Resource resource{};

        /**
         * @brief Has the raw data been translated into a useable format? (e.g., raw decal .wad make into \c Texture*).
        */
        qboolean translated{};

        /**
         * @brief Customization specific data.
        */
        int user_data1{};

        /**
         * @brief Customization specific data.
        */
        int user_data2{};

        /**
         * @brief Buffer that holds the data structure that references the data (e.g., the cache_wad_t).
        */
        void* info{};

        /**
         * @brief Buffer that holds the data for the customization (the raw .wad data).
        */
        void* buffer{};

        /**
         * @brief Next in chain.
        */
        Customization* next{};
    };
}
