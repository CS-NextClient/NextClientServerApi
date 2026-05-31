/*
 *  Copyright (C) 2020 the_hunter
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <cssdk/engine/eiface.h>

//-V::106

namespace metamod::gamedll
{
    /**
     * @brief Called when the game loads this DLL.
    */
    inline void GameInit()
    {
        cssdk::g_dll_funcs.game_init();
    }

    /**
     * @brief Called by the engine to spawn an entity.
     *
     * @param entity Entity to spawn.
     *
     * @return 0 if the entity was successfully spawned, or -1 if it should be removed.
    */
    inline int Spawn(cssdk::Edict* const entity)
    {
        return cssdk::g_dll_funcs.spawn(entity);
    }

    /**
     * @brief Called by the engine to run this entity's think function.
     *
     * @param entity Entity.
    */
    inline void Think(cssdk::Edict* const entity)
    {
        cssdk::g_dll_funcs.think(entity);
    }

    /**
     * @brief Called by the engine to trigger \c entity_used \c use function,
     * using \c entity_other as the activator and caller.
     *
     * @note Obsolete. This is never called by the engine.
    */
    inline void Use(cssdk::Edict* const entity_used, cssdk::Edict* const entity_other)
    {
        cssdk::g_dll_funcs.use(entity_used, entity_other);
    }

    /**
     * @brief Called by the engine to run \c entity_touched's \c touch function with \c entity_other as the other entity.
    */
    inline void Touch(cssdk::Edict* const entity_touched, cssdk::Edict* const entity_other)
    {
        cssdk::g_dll_funcs.touch(entity_touched, entity_other);
    }

    /**
     * @brief Called by the engine to run \c entity_blocked's \c blocked function with \c entity_other as the other entity.
    */
    inline void Blocked(cssdk::Edict* const entity_blocked, cssdk::Edict* const entity_other)
    {
        cssdk::g_dll_funcs.blocked(entity_blocked, entity_other);
    }

    /**
     * @brief Called by the engine to run \c entity_key_value's \c key_value function with \c data as the key-value data.
    */
    inline void KeyValue(cssdk::Edict* const entity_key_value, cssdk::KeyValueData* const data)
    {
        cssdk::g_dll_funcs.key_value(entity_key_value, data);
    }

    /**
     * @brief Called by the engine to save the given entity's state to the given save data block.
    */
    inline void Save(cssdk::Edict* const entity, cssdk::SaveRestoreData* const save_data)
    {
        cssdk::g_dll_funcs.save(entity, save_data);
    }

    /**
     * @brief Called by the engine to restore the given entity's state from the given save data block.
     *
     * @param entity Entity.
     * @param save_data Block to restore data from.
     * @param global_entity Indicating whether this entity has a global name, or was transitioned from another map.
    */
    inline int Restore(cssdk::Edict* const entity, cssdk::SaveRestoreData* const save_data,
                       const cssdk::qboolean global_entity)
    {
        return cssdk::g_dll_funcs.restore(entity, save_data, global_entity);
    }

    /**
     * @brief Called by the engine to set the given entity's absolute bounding box.
     *
     * @param entity Entity.
    */
    inline void SetAbsBox(cssdk::Edict* const entity)
    {
        cssdk::g_dll_funcs.set_abs_box(entity);
    }

    /**
     * @brief Called by the engine to save a named block of data to the given save data block.
     *
     * @param save_data Block to save data to.
     * @param name Name of the data block.
     * @param base_data Pointer to the object containing the data.
     * @param fields List of type descriptions describing the object's data.
     * @param field_count Number of type descriptions in \c fields.
    */
    inline void SaveWriteFields(cssdk::SaveRestoreData* const save_data, const char* const name, void* const base_data,
                                cssdk::TypeDescription* const fields, const int field_count)
    {
        cssdk::g_dll_funcs.save_write_fields(save_data, name, base_data, fields, field_count);
    }

    /**
     * @brief Called by the engine to restore a named block of data from the given save data block.
     *
     * @param save_data Block to restore data from.
     * @param name Name of the data block.
     * @param base_data Pointer to the object containing the data.
     * @param fields List of type descriptions describing the object's data.
     * @param field_count Number of type descriptions in \c fields.
    */
    inline void SaveReadFields(cssdk::SaveRestoreData* const save_data, const char* const name, void* const base_data,
                               cssdk::TypeDescription* const fields, const int field_count)
    {
        cssdk::g_dll_funcs.save_read_fields(save_data, name, base_data, fields, field_count);
    }

    /**
     * @brief Called by the engine to save global state.
    */
    inline void SaveGlobalState(cssdk::SaveRestoreData* const save_data)
    {
        cssdk::g_dll_funcs.save_global_state(save_data);
    }

    /**
     * @brief Called by the engine to restore global state.
    */
    inline void RestoreGlobalState(cssdk::SaveRestoreData* const save_data)
    {
        cssdk::g_dll_funcs.restore_global_state(save_data);
    }

    /**
     * @brief Called by the engine to reset global state.
    */
    inline void ResetGlobalState()
    {
        cssdk::g_dll_funcs.reset_global_state();
    }

    /**
     * @brief Called by the engine when a client connects.
     *
     * @param client Entity that represents this client.
     * @param name Net name of the player.
     * @param address IP address of the client.
     * @param reject_reason Reason why the client was rejected.
     *
     * @return True if the client should be allowed to connect, false otherwise.
     *
     * @note Returning false rejects the client's connection. Setting \c reject_reason presents that to the client.
     * @note Network messages cannot be sent at this time.
    */
    inline cssdk::qboolean ClientConnect(cssdk::Edict* const client, const char* const name,
                                         const char* const address, char* const reject_reason)
    {
        return cssdk::g_dll_funcs.client_connect(client, name, address, reject_reason);
    }

    /**
     * @brief Called when a client disconnects.
     * This will not be called if the client connection was rejected in \c client_connect.
     *
     * @param client Entity that represents this client.
    */
    inline void ClientDisconnect(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.client_disconnect(client);
    }

    /**
     * @brief Called by the engine when the player has issued a "kill" command.
     * Only if the player's health is larger than 0.
     *
     * @param client Entity that represents this client.
    */
    inline void ClientKill(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.client_kill(client);
    }

    /**
     * @brief Called by the engine when the client has finished connecting.
     * This is where the player should be spawned and put into the world, or given a spectator position to view from.
     *
     * @param client Entity that represents this client.
    */
    inline void ClientPutInServer(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.client_put_in_server(client);
    }

    /**
     * @brief Called by the engine when it has received a command from the given client.
     *
     * @param client Entity that represents this client.
     *
     * @note Command arguments can be retrieved using \c Engine::cmd_args, \c Engine::cmd_argv, \c Engine::cmd_argc.
    */
    inline void ClientCommand(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.client_command(client);
    }

    /**
     * @brief Called by the engine whenever the client's user info string changes.
     * This includes the player's model.
    */
    inline void ClientUserInfoChanged(cssdk::Edict* const client, char* const info_buffer)
    {
        cssdk::g_dll_funcs.client_user_info_changed(client, info_buffer);
    }

    /**
     * @brief Called when the engine has finished spawning the map.
     *
     * @param edict_list Pointer to the list of edicts.
     * @param edict_count Number of valid edicts.
     * @param client_max Maximum number of players that can connect to this server.
    */
    inline void ServerActivate(cssdk::Edict* const edict_list, const int edict_count, const int client_max)
    {
        cssdk::g_dll_funcs.server_activate(edict_list, edict_count, client_max);
    }

    /**
     * @brief Called when the map has ended. This happens before entities are destroyed.
    */
    inline void ServerDeactivate()
    {
        cssdk::g_dll_funcs.server_deactivate();
    }

    /**
     * @brief Called by the engine before it runs physics.
     *
     * @param client Entity that represents this client.
    */
    inline void PlayerPreThink(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.player_pre_think(client);
    }

    /**
     * @brief Called by the engine after it runs physics.
     *
     * @param client Entity that represents this client.
    */
    inline void PlayerPostThink(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.player_post_think(client);
    }

    /**
     * @brief Called at the start of a server game frame.
    */
    inline void StartFrame()
    {
        cssdk::g_dll_funcs.start_frame();
    }

    /**
     * @brief Obsolete.
    */
    inline void ParamsNewLevel()
    {
        cssdk::g_dll_funcs.params_new_level();
    }

    /**
     * @brief Called by the engine when a level is saved.
     * Also called when a player has spawned after a saved game has been loaded.
    */
    inline void ParamsChangeLevel()
    {
        cssdk::g_dll_funcs.params_change_level();
    }

    /**
     * @brief Returns string describing current .dll. E.g., TeamFortress 2, Half-Life.
    */
    inline const char* GetGameDescription()
    {
        return cssdk::g_dll_funcs.get_game_description();
    }

    /**
     * @brief Notify dll about a player customization.
    */
    inline void PlayerCustomization(cssdk::Edict* const client, cssdk::Customization* const custom)
    {
        cssdk::g_dll_funcs.player_customization(client, custom);
    }

    /**
     * @brief Called when a HLTV spectator has connected.
    */
    inline void SpectatorConnect(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.spectator_connect(client);
    }

    /**
     * @brief Called when a HLTV spectator has disconnected.
    */
    inline void SpectatorDisconnect(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.spectator_disconnect(client);
    }

    /**
     * @brief Called when a HLTV spectator's think function has to run.
    */
    inline void SpectatorThink(cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.spectator_think(client);
    }

    /**
     * @brief Notify game .dll that engine is going to shut down.
     * Allows mod authors to set a breakpoint.
    */
    inline void SysError(const char* const error_string)
    {
        cssdk::g_dll_funcs.sys_error(error_string);
    }

    /**
     * @brief Called by the engine to run player physics.
     *
     * @param move Pointer to player movement data.
     * @param server Whether this is the server or client physics code.
    */
    inline void PmMove(cssdk::PlayerMove* const move, const cssdk::qboolean server)
    {
        cssdk::g_dll_funcs.pm_move(move, server);
    }

    /**
     * @brief Called by the engine to initialize the player physics data.
    */
    inline void PmInit(cssdk::PlayerMove* const move)
    {
        cssdk::g_dll_funcs.pm_init(move);
    }

    /**
     * @brief Called by the engine to find the texture type of a given texture.
     *
     * @param name Name of the texture to look up.
     *
     * @return Texture type. Should always return a valid value, even if no data is available for the given texture.
     *
     * @note Never actually called.
    */
    inline char PmFindTextureType(char* const name)
    {
        return cssdk::g_dll_funcs.pm_find_texture_type(name);
    }

    /**
     * @brief Set up visibility for the given client.
     *
     * @param view_entity The client's view entity.
     * This is the entity whose origin and view offset should be used as the client's view position.
     * @param client The client.
     * @param pvs Pointer to Potentially Visible Set to use.
     * @param pas Pointer to Potentially Audible Set to use.
    */
    inline void SetupVisibility(cssdk::Edict* const view_entity, cssdk::Edict* const client,
                                unsigned char** const pvs, unsigned char** const pas)
    {
        cssdk::g_dll_funcs.setup_visibility(view_entity, client, pvs, pas);
    }

    /**
     * @brief Updates the given client's data.
     *
     * @param client Client.
     * @param send_weapons Indicating whether weapon data should be sent.
     * @param data Client data to send. This is zeroed before the call to this function.
    */
    inline void UpdateClientData(const cssdk::Edict* const client, const cssdk::qboolean send_weapons,
                                 cssdk::ClientData* const data)
    {
        cssdk::g_dll_funcs.update_client_data(client, send_weapons, data);
    }

    /**
     * @brief Called by the engine to determine whether the given entity
     * should be added to the given client's list of visible entities.
     *
     * @param state Entity state data for the entity that is being added.
     * @param entity_index Index of the entity being considered for addition.
     * @param entity Entity being considered for addition.
     * @param host Client currently being processed.
     * @param host_flags Host flags.
     * @param player \c true if the entity being added is a player, \c false otherwise.
     * @param set The PVS provided by \c setup_visibility
    */
    inline cssdk::qboolean AddToFullPack(cssdk::EntityState* const state, const int entity_index,
                                         cssdk::Edict* const entity, cssdk::Edict* const host, const int host_flags,
                                         const cssdk::qboolean player, unsigned char* const set)
    {
        return cssdk::g_dll_funcs.add_to_full_pack(state, entity_index, entity, host, host_flags, player, set);
    }

    /**
     * @brief Called by the engine to create a baseline for the given entity.
     *
     * @param client Indicating whether this is a player.
     * @param entity_index Entity index of this entity.
     * @param baseline Baseline to fill.
     * @param entity Entity to make the baseline for.
     * @param player_model_index Index of the model "models/player.mdl".
     * @param player_min_size Array of the player minimum bounds for each hull.
     * @param player_max_size Array of the player maximum bounds for each hull.
    */
    inline void CreateBaseline(const cssdk::qboolean client, const int entity_index, cssdk::EntityState* const baseline,
                               cssdk::Edict* const entity, const int player_model_index,
                               const cssdk::Vector& player_min_size, const cssdk::Vector& player_max_size)
    {
        cssdk::g_dll_funcs.create_baseline(client, entity_index, baseline, entity,
                                           player_model_index, player_min_size, player_max_size);
    }

    /**
     * @brief Called by the engine to allow the server to register delta encoders.
    */
    inline void RegisterEncoders()
    {
        cssdk::g_dll_funcs.register_encoders();
    }

    /**
     * @brief Called by the engine to retrieve weapon data.
     *
     * @param client Player to retrieve weapon info from.
     * @param info Array of \c WeaponData that should receive the player's weapon data. Is an array of MAX_WEAPONS entries.
     *
     * @return \c true if data was added, \c false otherwise.
    */
    inline cssdk::qboolean GetWeaponData(cssdk::Edict* const client, cssdk::WeaponData* const info)
    {
        return cssdk::g_dll_funcs.get_weapon_data(client, info);
    }

    /**
     * @brief Called by the engine when a user command has been received and is about to begin processing.
     *
     * @param client Client.
     * @param cmd Command being executed.
     * @param random_seed The player's current random seed.
    */
    inline void CmdStart(const cssdk::Edict* const client, const cssdk::UserCmd* const cmd, const unsigned int random_seed)
    {
        cssdk::g_dll_funcs.cmd_start(client, cmd, random_seed);
    }

    /**
     * @brief Called by the engine when a user command has finished processing.
     *
     * @param client Client.
    */
    inline void CmdEnd(const cssdk::Edict* const client)
    {
        cssdk::g_dll_funcs.cmd_end(client);
    }

    /**
     * @brief Return 1 if the packet is valid. Set response_buffer_size if you want to send a response packet.
     * Incoming, it holds the max size of the response_buffer, so you must zero it out if you choose not to respond.
     *
     * @param net_from IP address of the sender of this packet.
     * @param args Arguments provided by the sender.
     * @param response_buffer Buffer that a response can be written into.
     * @param response_buffer_size Size of the buffer.
     *
     * @return \c true if the packet has been handled, \c false otherwise.
     *
     * @note This can be used to handle commands akin to rcon. The remote server console can send commands that end up here.
     * @note Anyone can send messages that reach this point, not just rcon.
    */
    inline cssdk::qboolean ConnectionlessPacket(const cssdk::NetAddress* const net_from, const char* const args,
                                                char* const response_buffer, int* const response_buffer_size)
    {
        return cssdk::g_dll_funcs.connectionless_packet(net_from, args, response_buffer, response_buffer_size);
    }

    /**
     * @brief Enumerates player hulls. Returns 0 if the hull number doesn't exist, 1 otherwise.
     *
     * @param hull_number Hull to retrieve the bounds for.
     * @param min_size Minimum bounds.
     * @param max_size Maximum bounds.
     *
     * @return \c true if the hull was successfully retrieved, \c false otherwise.
    */
    inline cssdk::qboolean GetHullBounds(const int hull_number, cssdk::Vector& min_size, cssdk::Vector& max_size)
    {
        return cssdk::g_dll_funcs.get_hull_bounds(hull_number, min_size, max_size);
    }

    /**
     * @brief Create baselines for certain "unplaced" items.
    */
    inline void CreateInstancedBaselines()
    {
        cssdk::g_dll_funcs.create_instanced_baselines();
    }

    /**
     * @brief One of the \c force_unmodified files failed the consistency check for the specified player.
     * Return 0 to allow the client to continue, 1 to force immediate disconnection
     * (with an optional disconnect message of up to 256 characters).
    */
    inline cssdk::qboolean InconsistentFile(const cssdk::Edict* const client, const char* const file_name,
                                            char* const disconnect_message)
    {
        return cssdk::g_dll_funcs.inconsistent_file(client, file_name, disconnect_message);
    }

    /**
     * @brief The game .dll should return 1 if lag compensation should be allowed (could also just set the sv_unlag cvar).
     * Most games right now should return 0, until client-side weapon prediction code is written and tested for them.
    */
    inline cssdk::qboolean AllowLagCompensation()
    {
        return cssdk::g_dll_funcs.allow_lag_compensation();
    }

    /**
     * @brief Called when an entity is freed by the engine, right before the object's memory is freed.
     * Calls \c OnDestroy and runs the destructor.
     *
     * @param entity Entity.
    */
    inline void FreeEntityPrivateData(cssdk::Edict* const entity)
    {
        cssdk::g_dll_new_funcs.free_entity_private_data(entity);
    }

    /**
     * @brief Called when the game unloads this DLL.
    */
    inline void GameShutdown()
    {
        cssdk::g_dll_new_funcs.game_shutdown();
    }

    /**
     * @brief Called when the engine believes two entities are about to collide.
     *
     * @param entity_touched Entity touched.
     * @param entity_other Entity other.
     *
     * @return Return 0 if you want the two entities to just pass through each other without colliding
     * or calling the touch function.
    */
    inline cssdk::qboolean ShouldCollide(cssdk::Edict* const entity_touched, cssdk::Edict* const entity_other)
    {
        return cssdk::g_dll_new_funcs.should_collide(entity_touched, entity_other);
    }

    /**
     * @brief Called when the engine has received a cvar value from the client in response to an
     * \c Engine::query_client_cvar_value call.
     *
     * @param client Client.
     * @param value CVar value.
    */
    inline void CvarValue(const cssdk::Edict* const client, const char* const value)
    {
        cssdk::g_dll_new_funcs.cvar_value(client, value);
    }

    /**
     * @brief Called when the engine has received a cvar value from the client in response to an
     * \c Engine::query_client_cvar_value2 call.
     *
     * @param client Client.
     * @param request_id The ID given to the \c query_client_cvar_value2 function.
     * @param cvar_name Name of the cvar that was queried.
     * @param value CVar value.
    */
    inline void CvarValue2(const cssdk::Edict* const client, const int request_id,
                           const char* const cvar_name, const char* const value)
    {
        cssdk::g_dll_new_funcs.cvar_value2(client, request_id, cvar_name, value);
    }
}
