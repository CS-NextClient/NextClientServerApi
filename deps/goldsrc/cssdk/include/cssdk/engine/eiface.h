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
#include <cssdk/common/cvar.h>
#include <cssdk/common/entity_state.h>
#include <cssdk/common/net_address.h>
#include <cssdk/common/sequence.h>
#include <cssdk/common/vector.h>
#include <cssdk/common/weapon_data.h>
#include <cssdk/dll/save_restore.h>
#include <cssdk/engine/custom.h>
#include <cssdk/engine/edict.h>
#include <cssdk/pm_shared/pm_defs.h>

//-V::730

namespace cssdk
{
#ifdef HLDEMO_BUILD
    /**
     * @brief N/D
    */
    constexpr auto INTERFACE_VERSION = 001;
#else
    /**
     * @brief N/D
    */
    constexpr auto INTERFACE_VERSION = 140;
#endif

    /**
     * @brief N/D
    */
    constexpr auto ENGINE_INTERFACE_VERSION = 138;

    /**
     * @brief N/D
    */
    constexpr auto DLL_NEW_FUNCTIONS_VERSION = 1;

    /**
     * @brief Returned by trace_line.
    */
    struct TraceResult
    {
        /**
         * @brief If \c true, plane is not valid.
        */
        qboolean all_solid{};

        /**
         * @brief If \c true, the initial point was in a solid area.
        */
        qboolean start_solid{};

        /**
         * @brief Trace crossed open space.
        */
        qboolean in_open{};

        /**
         * @brief Trace crossed a water boundary.
        */
        qboolean in_water{};

        /**
         * @brief How far the trace went until hitting something.
         * This is a fraction of end - start, equal to \c (end_pos - start).length() / (end - start).length()
         * If 1.0, the trace didn't hit anything.
        */
        float fraction{};

        /**
         * @brief Final position.
        */
        Vector end_position{};

        /**
         * @brief Distance from origin that the plane is positioned at.
         * \c plane_normal * plane_dist represents a point that lies on the plane.
        */
        float plane_distance{};

        /**
         * @brief Surface normal at impact.
        */
        Vector plane_normal{};

        /**
         * @brief Entity the surface is on.
        */
        Edict* entity_hit{};

        /**
         * @brief Hit specific body part.
        */
        HitBoxGroup hit_group{};
    };

    /**
     * @brief Passed to \c Key_value
    */
    struct KeyValueData
    {
        /**
         * @brief In: entity class name.
        */
        char* class_name{};

        /**
         * @brief In: name of key.
        */
        char* key_name{};

        /**
         * @brief In: value of key.
        */
        char* value{};

        /**
         * @brief Out: DLL sets to true if key-value pair was understood.
        */
        qboolean handled{};
    };

    /**
     * @brief Engine hands this to DLLs for functionality callbacks.
    */
    struct EngineFunctions
    {
        /**
         * @brief Precaches a model.
        */
        int (*precache_model)(const char* path){};

        /**
         * @brief Precaches a sound.
        */
        int (*precache_sound)(const char* path){};

        /**
         * @brief Sets the model of the given entity. Also changes the entity bounds based on the model.
        */
        void (*set_model)(Edict* entity, const char* model){};

        /**
         * @brief Gets the index of the given model.
        */
        int (*model_index)(const char* model){};

        /**
         * @brief Gets the number of frames in the given model.
        */
        int (*model_frames)(int model_index){};

        /**
         * @brief Sets the entity bounds. Also relinks the entity.
        */
        void (*set_size)(Edict* entity, const Vector& min, const Vector& max){};

        /**
         * @brief Changes the level. This will append a change level command to the server command buffer.
        */
        void (*change_level)(const char* level_name, const char* landmark_name){};

        /**
         * @brief Does nothing useful. Will trigger a host error if the given entity is not a client.
        */
        void (*get_spawn_params)(Edict* client){};

        /**
         * @brief Does nothing useful. Will trigger a host error if the given entity is not a client.
        */
        void (*save_spawn_params)(Edict* client){};

        /**
         * @brief Converts a direction vector to a yaw angle.
        */
        float (*vec_to_yaw)(const Vector& direction){};

        /**
         * @brief Converts a direction vector to angles.
        */
        void (*vec_to_angles)(const Vector& direction_in, Vector& angles_out){};

        /**
         * @brief Moves the given entity to the given destination.
        */
        void (*move_to_origin)(Edict* entity, const Vector& goal, float distance, MoveTypeNpc move_type){};

        /**
         * @brief Changes the entity's yaw angle to approach its ideal yaw.
        */
        void (*change_yaw)(Edict* entity){};

        /**
         * @brief Changes the entity's pitch angle to approach its ideal pitch.
        */
        void (*change_pitch)(Edict* entity){};

        /**
         * @brief Finds an entity by comparing strings.
        */
        Edict* (*find_entity_by_string)(Edict* edict_start_search_after, const char* field, const char* value){};

        /**
         * @brief N/D
        */
        int (*get_entity_illumination)(Edict* entity){};

        /**
         * @brief Finds an entity in a sphere.
        */
        Edict* (*find_entity_in_sphere)(Edict* edict_start_search_after, const Vector& origin, float radius){};

        /**
         * @brief Finds a client in the potentially visible set.
        */
        Edict* (*find_client_in_pvs)(Edict* entity){};

        /**
         * @brief Find entities in potentially visible set.
        */
        Edict* (*entities_in_pvs)(Edict* entity){};

        /**
         * @brief Make direction vectors from angles.
        */
        void (*make_vectors)(const Vector& angles){};

        /**
         * @brief Make direction vectors from angles.
        */
        void (*angle_vectors)(const Vector& angles, Vector& forward, Vector& right, Vector& up){};

        /**
         * @brief Allocates an entity dictionary for use with an entity.
        */
        Edict* (*create_entity)(){};

        /**
         * @brief Immediately removes the given entity.
        */
        void (*remove_entity)(Edict* entity){};

        /**
         * @brief Creates an entity of the class \c class_name.
        */
        Edict* (*create_named_entity)(Strind class_name){};

        /**
         * @brief Makes an entity static.
         * Static entities are copied to the client side and are removed on the server side.
        */
        void (*make_static)(Edict* entity){};

        /**
         * @brief N/D
        */
        qboolean (*ent_is_on_floor)(Edict* entity){};

        /**
         * @brief Drops the entity to the floor.
        */
        int (*drop_to_floor)(Edict* entity){};

        /**
         * @brief Makes the entity walk.
        */
        qboolean (*walk_move)(Edict* entity, float yaw, float dist, WalkMoveMode mode){};

        /**
         * @brief Sets the origin of the given entity.
        */
        void (*set_origin)(Edict* entity, const Vector& origin){};

        /**
         * @brief Emits a sounds from the given entity.
        */
        void (*emit_sound)(Edict* entity, SoundChannel channel, const char* sample,
                           float volume, float attenuation, int flags, int pitch){};

        /**
         * @brief Emits a sounds from the given entity.
        */
        void (*emit_ambient_sound)(Edict* entity, Vector& origin, const char* sample,
                                   float volume, float attenuation, int flags, int pitch){};

        /**
         * @brief Performs a trace between a starting and ending position.
        */
        void (*trace_line)(const Vector& start_pos, const Vector& end_pos, int trace_ignore_flags,
                           Edict* entity_to_ignore, TraceResult* result){};

        /**
         * @brief Traces a toss.
        */
        void (*trace_toss)(Edict* entity, Edict* entity_to_ignore, TraceResult* result){};

        /**
         * @brief Performs a trace between a starting and ending position, using the given entity's min size and max size.
        */
        qboolean (*trace_monster_hull)(Edict* entity, const Vector& start_pos, const Vector& end_pos,
                                       int trace_ignore_flags, Edict* entity_to_ignore, TraceResult* result){};

        /**
         * @brief Performs a trace between a starting and ending position, using the specified hull.
        */
        void (*trace_hull)(const Vector& start_pos, const Vector& end_pos, int trace_ignore_flags,
                           int hull_number, Edict* entity_to_ignore, TraceResult* result){};

        /**
         * @brief Performs a trace between a starting and ending position. Similar to \c trace_hull,
         * but will instead perform a trace in the given world hull using the given entity's model's hulls.
         * For studio models this will use the model's hit boxes.
        */
        void (*trace_model)(const Vector& start_pos, const Vector& end_pos,
                            int hull_number, Edict* entity, TraceResult* result){};

        /**
         * @brief Used to get texture info.
        */
        const char* (*trace_texture)(Edict* texture_entity, const Vector& start_pos, const Vector& end_pos){};

        /**
         * @brief Not implemented. Triggers a sys error.
        */
        void (*trace_sphere)(const Vector& start_pos, const Vector& end_pos, int trace_ignore_flags, float radius,
                             Edict* entity_to_ignore, TraceResult* result){};

        /**
         * @brief Get the aim vector for the given entity.
         * Assumes \c make_vectors was called with \c entity->vars.angles beforehand.
        */
        void (*get_aim_vector)(Edict* entity, float speed, Vector& vec_return){};

        /**
         * @brief Issues a command to the server.
        */
        void (*server_command)(const char* command){};

        /**
         * @brief Executes all pending server commands.
        */
        void (*server_execute)(){};

        /**
         * @brief Sends a client command to the given client.
        */
        void (*client_command)(Edict* client, const char* format, ...){};

        /**
         * @brief Creates a particle effect.
        */
        void (*particle_effect)(const Vector& origin, const Vector& direction, float color, float count){};

        /**
         * @brief Sets the given light style to the given value.
        */
        void (*light_style)(int style, const char* value){};

        /**
         * @brief Gets the index of the given decal.
        */
        int (*decal_index)(const char* name){};

        /**
         * @brief Gets the contents of the given location in the world.
        */
        int (*point_contents)(const Vector& origin){};

        /**
         * @brief Begins a new network message.
        */
        void (*message_begin)(MessageType msg_type, int msg_id, const float* origin, Edict* client){};

        /**
         * @brief Ends a network message.
        */
        void (*message_end)(){};

        /**
         * @brief Writes a single unsigned byte.
        */
        void (*write_byte)(int value){};

        /**
         * @brief Writes a single character.
        */
        void (*write_char)(int value){};

        /**
         * @brief Writes a single unsigned short.
        */
        void (*write_short)(int value){};

        /**
         * @brief Writes a single unsigned int.
        */
        void (*write_long)(int value){};

        /**
         * @brief Writes a single angle value.
        */
        void (*write_angle)(float value){};

        /**
         * @brief Writes a single coordinate value.
        */
        void (*write_coord)(float value){};

        /**
         * @brief Writes a single null terminated string.
        */
        void (*write_string)(const char* value){};

        /**
         * @brief Writes a single entity index.
        */
        void (*write_entity)(int value){};

        /**
         * @brief Registers a console variable.
        */
        void (*cvar_register)(CVar* cvar){};

        /**
         * @brief Gets the value of console variable as a float.
        */
        float (*cvar_get_float)(const char* cvar_name){};

        /**
         * @brief Gets the value of console variable as a string.
        */
        const char* (*cvar_get_string)(const char* cvar_name){};

        /**
         * @brief Sets the value of console variable as a float.
        */
        void (*cvar_set_float)(const char* cvar_name, float value){};

        /**
         * @brief Sets the value of console variable as a string.
        */
        void (*cvar_set_string)(const char* cvar_name, const char* value){};

        /**
         * @brief Outputs a message to the server console.
        */
        void (*alert_message)(AlertType type, const char* format, ...){};

        /**
         * @brief Obsolete. Will print a message to the server console using alert_message indicating if it's being used.
        */
        void (*engine_file_print)(void* file, const char* format, ...){};

        /**
         * @brief Allocates memory for \c EntityBase instances.
        */
        void* (*alloc_ent_private_data)(Edict* entity, int32 size){};

        /**
         * @brief N/D
        */
        void* (*ent_private_data)(Edict* entity){};

        /**
         * @brief Frees the \c EntityBase memory assigned to entity.
        */
        void (*free_ent_private_data)(Edict* entity){};

        /**
         * @brief Gets the string assigned to the index.
        */
        const char* (*sz_from_index)(unsigned int string){};

        /**
         * @brief Allocates a string in the string pool.
        */
        unsigned int (*alloc_string)(const char* value){};

        /**
         * @brief Gets the \c EntityVars instance assigned to the given entity instance.
        */
        EntityVars* (*get_vars_of_ent)(Edict* entity){};

        /**
         * @brief Gets an entity by offset.
         * This uses the byte offset of the entity to retrieve it.
         * DO NOT USE THIS. Use the \c entity_of_ent_index instead.
        */
        Edict* (*entity_of_ent_offset)(eoffset entity_offset){};

        /**
         * @brief Gets the entity offset of the entity.
        */
        eoffset (*ent_offset_of_entity)(const Edict* entity){};

        /**
         * @brief Gets the entity index of the entity dictionary.
        */
        int (*index_of_edict)(const Edict* edict){};

        /**
         * @brief Gets the entity at the given entity index.
        */
        Edict* (*entity_of_ent_index)(int entity_index){};

        /**
         * @brief Gets the entity of an \c EntityVars.
        */
        Edict* (*find_entity_by_vars)(EntityVars* vars){};

        /**
         * @brief Gets the model pointer of the given entity.
        */
        void* (*get_model_pointer)(Edict* entity){};

        /**
         * @brief Registers a user message.
        */
        int (*reg_user_message)(const char* name, int size){};

        /**
         * @brief Does nothing.
        */
        void (*animation_auto_move)(const Edict* entity, float time){};

        /**
         * @brief Gets the bone position and angles for the given entity and bone.
        */
        void (*get_bone_position)(const Edict* entity, int bone, Vector& origin, Vector& angles){};

        /**
         * @brief Gets the index of an exported function.
        */
        uint32 (*function_from_name)(const char* name){};

        /**
         * @brief Gets the name of an exported function.
        */
        const char* (*name_for_function)(uint32 function){};

        /**
         * @brief Sends a message to the client console.
        */
        void (*client_print)(Edict* entity, PrintType type, const char* message){};

        /**
         * @brief Sends a message to the server console.
         * The message is output regardless of the value of the developer cvar.
        */
        void (*server_print)(const char* message){};

        /**
         * @brief N/D
        */
        const char* (*cmd_args)(){};

        /**
         * @brief Gets the command argument at the given index.
        */
        const char* (*cmd_argv)(int argc){};

        /**
         * @brief N/D
        */
        int (*cmd_argc)(){};

        /**
         * @brief Gets the attachment origin and angles.
        */
        void (*get_attachment)(const Edict* entity, int attachment, Vector& origin, Vector& angles){};

        /**
         * @brief Initializes the CRC instance.
        */
        void (*crc32_init)(crc32* pul_crc){};

        /**
         * @brief Processes a buffer and updates the CRC.
        */
        void (*crc32_process_buffer)(crc32* pul_crc, void* buffer, int len){};

        /**
         * @brief Processes a single byte.
        */
        void (*crc32_process_byte)(crc32* pul_crc, unsigned char ch){};

        /**
         * @brief Finalizes the CRC instance.
        */
        crc32 (*crc32_final)(crc32 pul_crc){};

        /**
         * @brief Generates a random long number in the range [low, high].
        */
        int32 (*random_long)(int32 low, int32 high){};

        /**
         * @brief Generates a random float number in the range [low, high].
        */
        float (*random_float)(float low, float high){};

        /**
         * @brief Sets the view of a client to the given entity.
        */
        void (*set_view)(const Edict* client, const Edict* view_entity){};

        /**
         * @brief N/D
        */
        float (*time)(){};

        /**
         * @brief Sets the angles of the given client's crosshairs to the given settings.
        */
        void (*crosshair_angle)(const Edict* client, float pitch, float yaw){};

        /**
         * @brief Loads a file from disk.
        */
        byte* (*load_file_for_me)(const char* file_name, int* length){};

        /**
         * @brief Frees the buffer provided by the \c load_file_for_me.
        */
        void (*free_file)(void* buffer){};

        /**
         * @brief Signals the engine that a section has ended.
        */
        void (*end_section)(const char* section_name){};

        /**
         * @brief Compares file times.
        */
        qboolean (*compare_file_time)(char* file_name1, char* file_name2, int* compare){};

        /**
         * @brief Gets the game directory name.
        */
        void (*get_game_dir)(char* game_dir){};

        /**
         * @brief Registers a Cvar. Identical to \c cvar_register, except it doesn't set the \c FCVAR_EXT_DLL flag.
        */
        void (*cvar_register_variable)(CVar* variable){};

        /**
         * @brief Fades the given client's volume.
        */
        void (*fade_client_volume)(const Edict* client, int fade_percent, int fade_out_seconds, int hold_time,
                                   int fade_in_seconds){};

        /**
         * @brief Sets the client's maximum speed value.
        */
        void (*set_client_max_speed)(Edict* client, float new_max_speed){};

        /**
         * @brief Creates a fake client (bot).
        */
        Edict* (*create_fake_client)(const char* name){};

        /**
         * @brief Runs client movement for a fake client.
        */
        void (*run_player_move)(Edict* fake_client, const Vector& view_angles, float forward_move, float side_move,
                                float up_move, unsigned short buttons, byte impulse, byte msec){};

        /**
         * @brief Computes the total number of entities currently in existence.
        */
        int (*number_of_entities)(){};

        /**
         * @brief Gets the given client's info key buffer.
        */
        char* (*get_info_key_buffer)(Edict* client){};

        /**
         * @brief Gets the value of the given key from the given buffer.
        */
        char* (*info_key_value)(char* info_buffer, const char* key){};

        /**
         * @brief Sets the value of the given key in the given buffer.
        */
        void (*set_key_value)(char* info_buffer, const char* key, const char* value){};

        /**
         * @brief Sets the value of the given key in the given buffer.
        */
        void (*set_client_key_value)(int client_index, char* info_buffer, const char* key, const char* value){};

        /**
         * @brief Checks if the given file_name is a valid map.
        */
        qboolean (*is_map_valid)(const char* file_name){};

        /**
         * @brief Projects a static decal in the world.
        */
        void (*static_decal)(const Vector& origin, int decal_index, int entity_index, int model_index){};

        /**
         * @brief Precaches a file.
        */
        int (*precache_generic)(const char* path){};

        /**
         * @brief Returns the server assigned user id for this client.
        */
        int (*get_player_user_id)(Edict* client){};

        /**
         * @brief Builds a sound message to send to a client.
        */
        void (*build_sound_msg)(Edict* entity, int channel, const char* sample, float volume, float attenuation, int flags,
                                int pitch, MessageType msg_type, int msg_id, const Vector& origin, Edict* client){};
        /**
         * @brief N/D
        */
        qboolean (*is_dedicated_server)(){};

        /**
         * @brief N/D
        */
        CVar* (*cvar_get_pointer)(const char* cvar_name){};

        /**
         * @brief Returns the server assigned WON id for this client.
        */
        unsigned int (*get_player_won_id)(Edict* client){};

        /**
         * @brief Removes a key from the info buffer.
        */
        void (*info_remove_key)(char* info_buffer, const char* key){};

        /**
         * @brief Gets the given physics key-value from the given client's buffer.
        */
        const char* (*get_physics_key_value)(const Edict* client, const char* key){};

        /**
         * @brief Sets the given physics key-value in the given client's buffer.
        */
        void (*set_physics_key_value)(const Edict* client, const char* key, const char* value){};

        /**
         * @brief Gets the physics info string for the given client.
        */
        const char* (*get_physics_info_string)(const Edict* client){};

        /**
         * @brief Precaches an event.
        */
        unsigned short (*precache_event)(int type, const char* path){};

        /**
         * @brief N/D
        */
        void (*playback_event)(int flags, const Edict* invoker, unsigned short event_index, float delay,
                               Vector& origin, Vector& angles, float f_param1, float f_param2, int i_param1,
                               int i_param2, qboolean b_param1, qboolean b_param2){};
        /**
         * @brief Sets the fat potentially visible set buffer to contain data based on the given origin.
        */
        unsigned char* (*set_fat_pvs)(Vector& origin){};

        /**
         * @brief Sets the fat potentially audible set buffer to contain data based on the given origin.
        */
        unsigned char* (*set_fat_pas)(Vector& origin){};

        /**
         * @brief Checks if the given entity is visible in the given visible set.
        */
        qboolean (*check_visibility)(Edict* entity, unsigned char* set){};

        /**
         * @brief Marks the given field in the given list as set.
        */
        void (*delta_set_field)(void* fields, const char* field_name){};

        /**
         * @brief Marks the given field in the given list as not set.
        */
        void (*delta_unset_field)(void* fields, const char* field_name){};

        /**
         * @brief Adds a delta encoder.
        */
        void (*delta_add_encoder)(const char* name,
                                  void (*conditional_encode)(void* fields, const unsigned char* from,
                                                             const unsigned char* to)){};
        /**
         * @brief N/D
        */
        int (*get_current_player)(){};

        /**
         * @brief N/D
        */
        qboolean (*can_skip_player)(const Edict* client){};

        /**
         * @brief Finds the index of a delta field.
        */
        int (*delta_find_field)(void* fields, const char* field_name){};

        /**
         * @brief Marks a delta field as set by index.
        */
        void (*delta_set_field_by_index)(void* fields, int field_number){};

        /**
         * @brief Marks a delta field as not set by index.
        */
        void (*delta_unset_field_by_index)(void* fields, int field_number){};

        /**
         * @brief Used to filter contents checks.
        */
        void (*set_group_mask)(int mask, int operation){};

        /**
         * @brief Creates an instanced baseline. Used to define a baseline for a particular entity type.
        */
        int (*create_instanced_baseline)(Strind class_name, EntityState* baseline){};

        /**
         * @brief Directly sets a console variable value.
        */
        void (*cvar_direct_set)(CVar* cvar, const char* value){};

        /**
         * @brief Forces the client and server to be running with the same version of the specified file
         * (e.g., a client model).
        */
        void (*force_unmodified)(ForceType type, Vector& min_size, Vector& max_size, const char* file_name){};

        /**
         * @brief Get client statistics.
        */
        void (*get_player_stats)(const Edict* client, int* ping, int* packet_loss){};

        /**
         * @brief Adds a server command.
        */
        void (*add_server_command)(const char* cmd_name, void (*callback)()){};

        /**
         * @brief Gets whether the given receiver can hear the given sender.
        */
        qboolean (*voice_get_client_listening)(int receiver, int sender){};

        /**
         * @brief Sets whether the given receiver can hear the given sender.
        */
        qboolean (*voice_set_client_listening)(int receiver, int sender, qboolean listen){};

        /**
         * @brief Gets the client's auth ID.
        */
        const char* (*get_player_auth_id)(Edict* client){};

        /**
         * @brief Gets the sequence that has the given entry name.
        */
        SequenceEntry* (*sequence_get)(const char* file_name, const char* entry_name){};

        /**
         * @brief Picks a sentence from the given group.
        */
        SentenceEntry* (*sequence_pick_sentence)(const char* group_name, int pick_method, int* picked){};

        /**
         * @brief LH: Give access to file size via filesystem.
        */
        int (*get_file_size)(const char* file_name){};

        /**
         * @brief Gets the average wave length in seconds.
        */
        unsigned int (*get_approx_wave_play_len)(const char* file_path){};

        /**
         * @brief N/D
        */
        qboolean (*is_career_match)(){};

        /**
         * @brief N/D
        */
        int (*get_localized_string_length)(const char* label){};

        /**
         * @brief Marks the message with the given ID as having been shown.
        */
        void (*register_tutor_message_shown)(int message_id){};

        /**
         * @brief Gets the number of times the message with the given ID has been shown.
        */
        int (*get_times_tutor_message_shown)(int message_id){};

        /**
         * @brief Processes the tutor message decay buffer.
        */
        void (*process_tutor_message_decay_buffer)(int* buffer, int buffer_length){};

        /**
         * @brief Constructs the tutor message decay buffer.
        */
        void (*construct_tutor_message_decay_buffer)(int* buffer, int buffer_length){};

        /**
         * @brief Resets tutor message decay data.
        */
        void (*reset_tutor_message_decay_data)(){};

        /**
         * @brief Queries the given client for a cvar value.
        */
        void (*query_client_cvar_value)(const Edict* client, const char* cvar_name){};

        /**
         * @brief Queries the given client for a cvar value.
        */
        void (*query_client_cvar_value2)(const Edict* client, const char* cvar_name, int request_id){};

        /**
         * @brief Checks if a command line parameter was provided.
        */
        int (*eng_check_param)(const char* cmd_line_token, char** next){};
    };

    /**
     * @brief Server library interface to the engine.
    */
    struct DllFunctions
    {
        /**
         * @brief Called when the game loads this DLL.
        */
        void (*game_init)(){};

        /**
         * @brief Called by the engine to spawn an entity.
        */
        int (*spawn)(Edict* entity){};

        /**
         * @brief Called by the engine to run this entity's think function.
        */
        void (*think)(Edict* entity){};

        /**
         * @brief Called by the engine to trigger \c entity_used's \c use function,
         * using \c entity_other as the activator and caller.
         * Obsolete. This is never called by the engine.
        */
        void (*use)(Edict* entity_used, Edict* entity_other){};

        /**
         * @brief Called by the engine to run \c entity_touched's \c touch function with \c entity_other as the other entity.
        */
        void (*touch)(Edict* entity_touched, Edict* entity_other){};

        /**
         * @brief Called by the engine to run \c entity_blocked's \c blocked function with \c entity_other as the other entity.
        */
        void (*blocked)(Edict* entity_blocked, Edict* entity_other){};

        /**
         * @brief Called by the engine to run \c entity_key_value's \c key_value function with \c data as the key-value data.
        */
        void (*key_value)(Edict* entity_key_value, KeyValueData* data){};

        /**
         * @brief Called by the engine to save the given entity's state to the given save data block.
        */
        void (*save)(Edict* entity, SaveRestoreData* save_data){};

        /**
         * @brief Called by the engine to restore the given entity's state from the given save data block.
        */
        int (*restore)(Edict* entity, SaveRestoreData* save_data, qboolean global_entity){};

        /**
         * @brief Called by the engine to set the given entity's absolute bounding box.
        */
        void (*set_abs_box)(Edict* entity){};

        /**
         * @brief Called by the engine to save a named block of data to the given save data block.
        */
        void (*save_write_fields)(SaveRestoreData* save_data, const char* name, void* base_data,
                                  TypeDescription* fields, int field_count){};

        /**
         * @brief Called by the engine to restore a named block of data from the given save data block.
        */
        void (*save_read_fields)(SaveRestoreData* save_data, const char* name, void* base_data,
                                 TypeDescription* fields, int field_count){};

        /**
         * @brief Called by the engine to save global state.
        */
        void (*save_global_state)(SaveRestoreData* save_data){};

        /**
         * @brief Called by the engine to restore global state.
        */
        void (*restore_global_state)(SaveRestoreData* save_data){};

        /**
         * @brief Called by the engine to reset global state.
        */
        void (*reset_global_state)(){};

        /**
         * @brief Called by the engine when a client connects.
         * Returning false rejects the client's connection. Setting \c reject_reason presents that to the client.
        */
        qboolean (*client_connect)(Edict* client, const char* name, const char* address, char reject_reason[128]){};

        /**
         * @brief Called when a client disconnects.
         * This will not be called if the client connection was rejected in \c client_connect.
        */
        void (*client_disconnect)(Edict* client){};

        /**
         * @brief Called by the engine when the player has issued a "kill" command.
         * Only if the player's health is larger than 0.
        */
        void (*client_kill)(Edict* client){};

        /**
         * @brief Called by the engine when the client has finished connecting.
         * This is where the player should be spawned and put into the world, or given a spectator position to view from.
        */
        void (*client_put_in_server)(Edict* client){};

        /**
         * @brief Called by the engine when it has received a command from the given client.
        */
        void (*client_command)(Edict* client){};

        /**
         * @brief Called by the engine whenever the client's user info string changes.
         * This includes the player's model.
        */
        void (*client_user_info_changed)(Edict* client, char* info_buffer){};

        /**
         * @brief Called when the engine has finished spawning the map.
        */
        void (*server_activate)(Edict* edict_list, int edict_count, int client_max){};

        /**
         * @brief Called when the map has ended.
         * This happens before entities are destroyed.
        */
        void (*server_deactivate)(){};

        /**
         * @brief Called by the engine before it runs physics.
        */
        void (*player_pre_think)(Edict* client){};

        /**
         * @brief Called by the engine after it runs physics.
        */
        void (*player_post_think)(Edict* client){};

        /**
         * @brief Called at the start of a server game frame.
        */
        void (*start_frame)(){};

        /**
         * @brief Obsolete.
        */
        void (*params_new_level)(){};

        /**
         * @brief Called by the engine when a level is saved.
         * Also called when a player has spawned after a saved game has been loaded.
        */
        void (*params_change_level)(){};

        /**
         * @brief Returns string describing current .dll. E.g., TeamFortress 2, Half-Life.
        */
        const char* (*get_game_description)(){};

        /**
         * @brief Notify dll about a player customization.
        */
        void (*player_customization)(Edict* client, Customization* custom){};

        /**
         * @brief Called when a HLTV spectator has connected.
        */
        void (*spectator_connect)(Edict* client){};

        /**
         * @brief Called when a HLTV spectator has disconnected.
        */
        void (*spectator_disconnect)(Edict* client){};

        /**
         * @brief Called when a HLTV spectator's think function has to run.
        */
        void (*spectator_think)(Edict* client){};

        /**
         * @brief Notify game .dll that engine is going to shut down. Allows mod authors to set a breakpoint.
        */
        void (*sys_error)(const char* error_string){};

        /**
         * @brief Called by the engine to run player physics.
        */
        void (*pm_move)(PlayerMove* move, qboolean server){};

        /**
         * @brief Called by the engine to initialize the player physics data.
        */
        void (*pm_init)(PlayerMove* move){};

        /**
         * @brief Called by the engine to find the texture type of a given texture.
        */
        char (*pm_find_texture_type)(char* name){};

        /**
         * @brief Set up visibility for the given client.
        */
        void (*setup_visibility)(Edict* view_entity, Edict* client, unsigned char** pvs, unsigned char** pas){};

        /**
         * @brief Updates the given client's data.
         * This function can be used to implement first person observer views.
        */
        void (*update_client_data)(const Edict* client, qboolean send_weapons, ClientData* data){};

        /**
         * @brief Called by the engine to determine whether the given entity should be
         * added to the given client's list of visible entities.
        */
        qboolean (*add_to_full_pack)(EntityState* state, int entity_index, Edict* entity, Edict* host,
                                     int host_flags, qboolean player, unsigned char* set){};

        /**
         * @brief Called by the engine to create a baseline for the given entity.
        */
        void (*create_baseline)(qboolean client, int entity_index, EntityState* baseline, Edict* entity, int player_model_index,
                                Vector player_min_size, Vector player_max_size){};

        /**
         * @brief Called by the engine to allow the server to register delta encoders.
        */
        void (*register_encoders)(){};

        /**
         * @brief Called by the engine to retrieve weapon data.
        */
        qboolean (*get_weapon_data)(Edict* client, WeaponData* info){};

        /**
         * @brief Called by the engine when a user command has been received and is about to begin processing.
        */
        void (*cmd_start)(const Edict* client, const UserCmd* cmd, unsigned int random_seed){};

        /**
         * @brief Called by the engine when a user command has finished processing.
        */
        void (*cmd_end)(const Edict* client){};

        /**
         * @brief Return 1 if the packet is valid. Set response_buffer_size if you want to send a response packet.
         * Incoming, it holds the max size of the \c response_buffer,
         * so you must zero it out if you choose not to respond.
        */
        qboolean (*connectionless_packet)(const NetAddress* net_from, const char* args, char* response_buffer,
                                          int* response_buffer_size){};

        /**
         * @brief Enumerates player hulls. Returns 0 if the hull number doesn't exist, 1 otherwise.
        */
        qboolean (*get_hull_bounds)(int hull_number, Vector& min_size, Vector& max_size){};

        /**
         * @brief Create baselines for certain "unplaced" items.
        */
        void (*create_instanced_baselines)(){};

        /**
         * @brief One of the \c force_unmodified files failed the consistency check for the specified player.
         * Return 0 to allow the client to continue, 1 to force immediate disconnection
         * (with an optional disconnect message of up to 256 characters).
        */
        qboolean (*inconsistent_file)(const Edict* client, const char* file_name, char* disconnect_message){};

        /**
         * @brief The game .dll should return 1 if lag compensation should be allowed (could also just set the sv_unlag cvar).
         * Most games right now should return 0, until client-side weapon prediction code is written and tested for them.
        */
        qboolean (*allow_lag_compensation)(){};
    };

    /**
     * @brief Additional server interface to the engine.
    */
    struct DllNewFunctions
    {
        /**
         * @brief Called when an entity is freed by the engine, right before the object's memory is freed.
         * Calls \c OnDestroy and runs the destructor.
        */
        void (*free_entity_private_data)(Edict* entity){};

        /**
         * @brief Called when the game unloads this DLL.
        */
        void (*game_shutdown)(){};

        /**
         * @brief Called when the engine believes two entities are about to collide.
         * Return 0 if you want the two entities to just pass through each other without colliding or calling the touch function.
        */
        qboolean (*should_collide)(Edict* entity_touched, Edict* entity_other){};

        /**
         * @brief Called when the engine has received a cvar value from the client in response
         * to an \c EngineFuncPointers::query_client_cvar_value call.
        */
        void (*cvar_value)(const Edict* client, const char* value){};

        /**
         * @brief Called when the engine has received a cvar value from the client in response to a
         * \c EngineFuncPointers::query_client_cvar_value2 call.
        */
        void (*cvar_value2)(const Edict* client, int request_id, const char* cvar_name, const char* value){};
    };

    /**
     * @brief Must be provided by user of this code (see Metamod SDK).
    */
    inline EngineFunctions g_engine_funcs{};

    /**
     * @brief Must be provided by user of this code (see Metamod SDK).
    */
    inline DllFunctions g_dll_funcs{};

    /**
     * @brief Must be provided by user of this code (see Metamod SDK).
    */
    inline DllNewFunctions g_dll_new_funcs{};
}
