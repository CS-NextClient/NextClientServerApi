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

#include <cssdk/common/strind.h>
#include <cssdk/common/vector.h>
#include <cssdk/engine/edict.h>

namespace cssdk
{
    /**
     * @brief These are encoded in the lower 16 bits of \c EntityTable::flags.
    */
    constexpr auto MAX_LEVEL_CONNECTIONS = 16;

    /**
     * @brief This field is masked for global entity save/restore.
    */
    constexpr auto FTYPE_DESC_GLOBAL = 0x0001;

    /**
     * @brief This is a global entity.
     * The engine uses this to merge changes made to global entities.
    */
    constexpr auto FENT_TABLE_GLOBAL = 0x10000000;

    /**
     * @brief Entities that return \c FCAP_ACROSS_TRANSITION from \c ObjectCaps are flagged with this.
    */
    constexpr auto FENT_TABLE_MOVEABLE = 0x20000000;

    /**
     * @brief Flags the entity as having been removed.
     * Done by the engine when reading .HL1 save patch files.
    */
    constexpr auto FENT_TABLE_REMOVED = 0x40000000;

    /**
     * @brief This entity is a player.
    */
    constexpr auto FENT_TABLE_PLAYER = 0x80000000;

    enum class FieldType
    {
        /**
         * @brief Any floating point value.
        */
        FieldFloat = 0,

        /**
         * @brief A string ID (return from alloc_string).
        */
        FieldString,

        /**
         * @brief An entity offset.
        */
        FieldEntity,

        /**
         * @brief \c EntityBase*.
        */
        FieldClassPtr,

        /**
         * @brief Entity handle.
        */
        FieldEntHandle,

        /**
         * @brief \c EntityVars*.
        */
        FieldEntVars,

        /**
         * @brief \c Edict*.
        */
        FieldEdict,

        /**
         * @brief Any vector.
        */
        FieldVector,

        /**
         * @brief A world coordinate (these are fixed up across level transitions automagically).
        */
        FieldPositionVector,

        /**
         * @brief Arbitrary data pointer... to be removed, use an array of \c field_character.
        */
        FieldPointer,

        /**
         * @brief Any integer or enum.
        */
        FieldInteger,

        /**
         * @brief A class function pointer (think, use, etc).
        */
        FieldFunction,

        /**
         * @brief Boolean, implemented as an int, I may use this as a hint for compression.
        */
        FieldBoolean,

        /**
         * @brief 2 byte integer.
        */
        FieldShort,

        /**
         * @brief A byte.
        */
        FieldCharacter,

        /**
         * @brief A floating point time (these are fixed up automatically too!).
        */
        FieldTime,

        /**
         * @brief Engine string that is a model name (needs precache).
        */
        FieldModelName,

        /**
         * @brief Engine string that is a sound name (needs precache).
        */
        FieldSoundName,

        /**
         * @brief Must be last.
        */
        FieldTypeCount
    };

    struct TypeDescription
    {
        /**
         * @brief N/D
        */
        FieldType type{};

        /**
         * @brief N/D
        */
        const char* name{};

        /**
         * @brief N/D
        */
        int offset{};

        /**
         * @brief N/D
        */
        short size{};

        /**
         * @brief N/D
        */
        short flags{};
    };

    /**
     * @brief Represents a transition to another level.
    */
    struct LevelList
    {
        /**
         * @brief Name of the map to transition to.
        */
        char map_name[32]{};

        /**
         * @brief Name of the landmark in this and the next map.
        */
        char landmark_name[32]{};

        /**
         * @brief Landmark entity.
        */
        Edict* ent_landmark{};

        /**
         * @brief Landmark origin in this map.
        */
        Vector landmark_origin{};
    };

    /**
     * @brief Describes one entity in the save restore data.
    */
    struct EntityTable
    {
        /**
         * @brief The identifier.
        */
        int id{};

        /**
         * @brief Pointer to the in-game entity.
        */
        Edict* entity{};

        /**
         * @brief Offset from the base data of this entity.
        */
        int location{};

        /**
         * @brief Byte size of this entity's data.
        */
        int size{};

        /**
         * @brief This could be a short -- bit mask of transitions that this entity is in the PVS of.
        */
        unsigned int flags{};

        /**
         * @brief Entity class name.
        */
        Strind class_name{};
    };

    /**
     * @brief Save data for a single level.
    */
    struct SaveRestoreData
    {
        /**
         * @brief Start of all entity save data.
        */
        char* base_data{};

        /**
         * @brief Current buffer pointer for sequential access.
        */
        char* current_data{};

        /**
         * @brief Current data size.
        */
        int size{};

        /**
         * @brief Total space for data.
        */
        int buffer_size{};

        /**
         * @brief Size of the linear list of tokens.
        */
        int token_size{};

        /**
         * @brief Number of elements in the tokens table.
        */
        int token_count{};

        /**
         * @brief Hash table of entity strings (sparse).
        */
        char** tokens{};

        /**
         * @brief Holds a global entity table ID.
        */
        int current_index{};

        /**
         * @brief Number of elements in the entity table.
        */
        int table_count{};

        /**
         * @brief Number of elements in the LevelList[].
        */
        int connection_count{};

        /**
         * @brief Array of \c EntityTable elements (1 for each entity).
        */
        EntityTable* table{};

        /**
         * @brief List of connections from this level.
        */
        LevelList lvl_list[MAX_LEVEL_CONNECTIONS]{};

        /**
         * @brief Smooth transition.
        */
        int use_landmark{};

        /**
         * @brief Landmark we'll spawn near in next level.
        */
        char landmark_name[20]{};

        /**
         * @brief For landmark transitions.
        */
        Vector landmark_offset{};

        /**
         * @brief Game time when the save game was written.
        */
        float time{};

        /**
         * @brief To check global entities.
        */
        char current_map_name[32]{};
    };

    /**
     * @brief N/D
    */
    class Save;

    /**
     * @brief N/D
    */
    class Restore;
}
