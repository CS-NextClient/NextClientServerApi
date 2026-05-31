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
#include <cstring>
#include <type_traits>

namespace metamod::gamedll::detail
{
    inline cssdk::DllFunctions* dll_hooks = new cssdk::DllFunctions{};
    inline cssdk::DllFunctions* dll_post_hooks = new cssdk::DllFunctions{};

    inline cssdk::DllNewFunctions* dll_new_hooks = new cssdk::DllNewFunctions{};
    inline cssdk::DllNewFunctions* dll_new_post_hooks = new cssdk::DllNewFunctions{};

    inline void ClearGameDllHooks()
    {
        if (dll_hooks) {
            // ReSharper disable once CppRedundantCastExpression
            std::memset(static_cast<void*>(dll_hooks), 0, sizeof(cssdk::DllFunctions));
        }

        if (dll_post_hooks) {
            // ReSharper disable once CppRedundantCastExpression
            std::memset(static_cast<void*>(dll_post_hooks), 0, sizeof(cssdk::DllFunctions));
        }

        if (dll_new_hooks) {
            // ReSharper disable once CppRedundantCastExpression
            std::memset(static_cast<void*>(dll_new_hooks), 0, sizeof(cssdk::DllNewFunctions));
        }

        if (dll_new_post_hooks) {
            // ReSharper disable once CppRedundantCastExpression
            std::memset(static_cast<void*>(dll_new_post_hooks), 0, sizeof(cssdk::DllNewFunctions));
        }
    }

    template <typename TMember, typename TCallback>
    void SetHook(TMember cssdk::DllFunctions::*member, const TCallback callback, const bool post)
    {
        if (post) {
            assert(dll_post_hooks != nullptr);
            dll_post_hooks->*member = callback;
        }
        else {
            assert(dll_hooks != nullptr);
            dll_hooks->*member = callback;
        }
    }

    template <typename TMember, typename TCallback>
    void SetHook(TMember cssdk::DllNewFunctions::*member, const TCallback callback, const bool post)
    {
        if (post) {
            assert(dll_new_post_hooks != nullptr);
            dll_new_post_hooks->*member = callback;
        }
        else {
            assert(dll_new_hooks != nullptr);
            dll_new_hooks->*member = callback;
        }
    }
}

namespace metamod::gamedll
{
    /**
     * @brief Called when the game loads this DLL.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGameInit(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::game_init, callback, post);
    }

    /**
     * @brief Called by the engine to spawn an entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSpawn(const std::add_pointer_t<int(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::spawn, callback, post);
    }

    /**
     * @brief Called by the engine to run this entity's think function.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookThink(const std::add_pointer_t<void(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::think, callback, post);
    }

    /**
     * @brief Called by the engine to trigger \c entity_used \c use function, using \c entity_other as the activator and caller.
     * Obsolete. This is never called by the engine.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookUse(const std::add_pointer_t<void(cssdk::Edict* entity_used, cssdk::Edict* entity_other)> callback,
                        const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::use, callback, post);
    }

    /**
     * @brief Called by the engine to run \c entity_touched's \c touch function with \c entity_other as the other entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTouch(const std::add_pointer_t<void(cssdk::Edict* entity_touched, cssdk::Edict* entity_other)> callback,
                          const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::touch, callback, post);
    }

    /**
     * @brief Called by the engine to run \c entity_blocked's \c blocked function with \c entity_other as the other entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookBlocked(const std::add_pointer_t<void(cssdk::Edict* entity_blocked, cssdk::Edict* entity_other)> callback,
                            const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::blocked, callback, post);
    }

    /**
     * @brief Called by the engine to run \c entity_key_value's \c key_value function with \c data as the key-value data.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookKeyValue(const std::add_pointer_t<void(cssdk::Edict* entity_key_value, cssdk::KeyValueData* data)> callback,
                             const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::key_value, callback, post);
    }

    /**
     * @brief Called by the engine to save the given entity's state to the given save data block.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSave(const std::add_pointer_t<void(cssdk::Edict* entity, cssdk::SaveRestoreData* save_data)> callback,
                         const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::save, callback, post);
    }

    /**
     * @brief Called by the engine to restore the given entity's state from the given save data block.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRestore(const std::add_pointer_t<int(cssdk::Edict* entity, cssdk::SaveRestoreData* save_data, cssdk::qboolean global_entity)> callback,
                            const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::restore, callback, post);
    }

    /**
     * @brief Called by the engine to set the given entity's absolute bounding box.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetAbsBox(const std::add_pointer_t<void(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::set_abs_box, callback, post);
    }

    /**
     * @brief Called by the engine to save a named block of data to the given save data block.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSaveWriteFields(
        const std::add_pointer_t<void(cssdk::SaveRestoreData* save_data, const char* name, void* base_data, cssdk::TypeDescription* fields, int field_count)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::save_write_fields, callback, post);
    }

    /**
     * @brief Called by the engine to restore a named block of data from the given save data block.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSaveReadFields(
        const std::add_pointer_t<void(cssdk::SaveRestoreData* save_data, const char* name, void* base_data, cssdk::TypeDescription* fields, int field_count)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::save_read_fields, callback, post);
    }

    /**
     * @brief Called by the engine to save global state.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSaveGlobalState(const std::add_pointer_t<void(cssdk::SaveRestoreData* save_data)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::save_global_state, callback, post);
    }

    /**
     * @brief Called by the engine to restore global state.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRestoreGlobalState(const std::add_pointer_t<void(cssdk::SaveRestoreData* save_data)> callback,
                                       const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::restore_global_state, callback, post);
    }

    /**
     * @brief Called by the engine to reset global state.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookResetGlobalState(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::reset_global_state, callback, post);
    }

    /**
     * @brief Called by the engine when a client connects.
     * Returning false rejects the client's connection. Setting \c reject_reason presents that to the client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookClientConnect(
        const std::add_pointer_t<cssdk::qboolean(cssdk::Edict* client, const char* name, const char* address, char* reject_reason)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::client_connect, callback, post);
    }

    /**
     * @brief Called when a client disconnects.
     * This will not be called if the client connection was rejected in \c ClientConnect.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookClientDisconnect(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::client_disconnect, callback, post);
    }

    /**
     * @brief Called by the engine when the player has issued a "kill" command.
     * Only if the player's health is larger than 0.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookClientKill(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::client_kill, callback, post);
    }

    /**
     * @brief Called by the engine when the client has finished connecting.
     * This is where the player should be spawned and put into the world, or given a spectator position to view from.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookClientPutInServer(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::client_put_in_server, callback, post);
    }

    /**
     * @brief Called by the engine when it has received a command from the given client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookClientCommand(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::client_command, callback, post);
    }

    /**
     * @brief Called by the engine whenever the client's user info string changes.
     * This includes the player's model.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookClientUserInfoChanged(const std::add_pointer_t<void(cssdk::Edict* client, char* info_buffer)> callback,
                                          const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::client_user_info_changed, callback, post);
    }

    /**
     * @brief Called when the engine has finished spawning the map.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookServerActivate(const std::add_pointer_t<void(cssdk::Edict* edict_list, int edict_count, int client_max)> callback,
                                   const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::server_activate, callback, post);
    }

    /**
     * @brief Called when the map has ended.
     * This happens before entities are destroyed.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookServerDeactivate(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::server_deactivate, callback, post);
    }

    /**
     * @brief Called by the engine before it runs physics.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPlayerPreThink(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::player_pre_think, callback, post);
    }

    /**
     * @brief Called by the engine after it runs physics.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPlayerPostThink(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::player_post_think, callback, post);
    }

    /**
     * @brief Called at the start of a server game frame.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookStartFrame(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::start_frame, callback, post);
    }

    /**
     * @brief Obsolete.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookParamsNewLevel(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::params_new_level, callback, post);
    }

    /**
     * @brief Called by the engine when a level is saved.
     * Also called when a player has spawned after a saved game has been loaded.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookParamsChangeLevel(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::params_change_level, callback, post);
    }

    /**
     * @brief Returns string describing current .dll. E.g., TeamFortress 2, Half-Life.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetGameDescription(const std::add_pointer_t<const char*()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::get_game_description, callback, post);
    }

    /**
     * @brief Notify dll about a player customization.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPlayerCustomization(const std::add_pointer_t<void(cssdk::Edict* client, cssdk::Customization* custom)> callback,
                                        const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::player_customization, callback, post);
    }

    /**
     * @brief Called when a HLTV spectator has connected.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSpectatorConnect(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::spectator_connect, callback, post);
    }

    /**
     * @brief Called when a HLTV spectator has disconnected.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSpectatorDisconnect(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::spectator_disconnect, callback, post);
    }

    /**
     * @brief Called when a HLTV spectator's think function has to run.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSpectatorThink(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::spectator_think, callback, post);
    }

    /**
     * @brief Notify game .dll that engine is going to shut down. Allows mod authors to set a breakpoint.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSysError(const std::add_pointer_t<void(const char* error_string)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::sys_error, callback, post);
    }

    /**
     * @brief Called by the engine to run player physics.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPmMove(const std::add_pointer_t<void(cssdk::PlayerMove* move, cssdk::qboolean server)> callback,
                           const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::pm_move, callback, post);
    }

    /**
     * @brief Called by the engine to initialize the player physics data.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPmInit(const std::add_pointer_t<void(cssdk::PlayerMove* move)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::pm_init, callback, post);
    }

    /**
     * @brief Called by the engine to find the texture type of a given texture.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPmFindTextureType(const std::add_pointer_t<char(char* name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::pm_find_texture_type, callback, post);
    }

    /**
     * @brief Set up visibility for the given client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetupVisibility(const std::add_pointer_t<void(cssdk::Edict* view_entity, cssdk::Edict* client, unsigned char** pvs, unsigned char** pas)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::setup_visibility, callback, post);
    }

    /**
     * @brief Updates the given client's data.
     * This function can be used to implement first person observer views.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookUpdateClientData(const std::add_pointer_t<void(const cssdk::Edict* client, cssdk::qboolean send_weapons, cssdk::ClientData* data)> callback,
                                     const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::update_client_data, callback, post);
    }

    /**
     * @brief Called by the engine to determine whether the given entity should be added
     * to the given client's list of visible entities.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookAddToFullPack(
        const std::add_pointer_t<cssdk::qboolean(cssdk::EntityState* state, int entity_index, cssdk::Edict* entity, cssdk::Edict* host, int host_flags, cssdk::qboolean player, unsigned char* set)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::add_to_full_pack, callback, post);
    }

    /**
     * @brief Called by the engine to create a baseline for the given entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCreateBaseline(
        const std::add_pointer_t<void(cssdk::qboolean client, int entity_index, cssdk::EntityState* baseline, cssdk::Edict* entity, int player_model_index, cssdk::Vector player_min_size, cssdk::Vector player_max_size)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::create_baseline, callback, post);
    }

    /**
     * @brief Called by the engine to allow the server to register delta encoders.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRegisterEncoders(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::register_encoders, callback, post);
    }

    /**
     * @brief Called by the engine to retrieve weapon data.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetWeaponData(const std::add_pointer_t<cssdk::qboolean(cssdk::Edict* client, cssdk::WeaponData* info)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::get_weapon_data, callback, post);
    }

    /**
     * @brief Called by the engine when a user command has been received and is about to begin processing.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCmdStart(const std::add_pointer_t<void(const cssdk::Edict* client, const cssdk::UserCmd* cmd, unsigned int random_seed)> callback,
                             const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::cmd_start, callback, post);
    }

    /**
     * @brief Called by the engine when a user command has finished processing.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCmdEnd(const std::add_pointer_t<void(const cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::cmd_end, callback, post);
    }

    /**
     * @brief Return 1 if the packet is valid. Set response_buffer_size if you want to send a response packet.
     * Incoming, it holds the max size of the \c response_buffer, so you must zero it out if you choose not to respond.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookConnectionlessPacket(
        const std::add_pointer_t<cssdk::qboolean(const cssdk::NetAddress* net_from, const char* args, char* response_buffer, int* response_buffer_size)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::connectionless_packet, callback, post);
    }

    /**
     * @brief Enumerates player hulls. Returns 0 if the hull number doesn't exist, 1 otherwise.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetHullBounds(const std::add_pointer_t<cssdk::qboolean(int hull_number, cssdk::Vector& min_size, cssdk::Vector& max_size)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::get_hull_bounds, callback, post);
    }

    /**
     * @brief Create baselines for certain "unplaced" items.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCreateInstancedBaselines(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::create_instanced_baselines, callback, post);
    }

    /**
     * @brief One of the \c force_unmodified files failed the consistency check for the specified player.
     * Return 0 to allow the client to continue, 1 to force immediate disconnection
     * (with an optional disconnect message of up to 256 characters).
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookInconsistentFile(const std::add_pointer_t<cssdk::qboolean(const cssdk::Edict* client, const char* file_name, char* disconnect_message)> callback,
                                     const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::inconsistent_file, callback, post);
    }

    /**
     * @brief The game .dll should return 1 if lag compensation should be allowed (could also just set the sv_unlag cvar).
     * Most games right now should return 0, until client-side weapon prediction code is written and tested for them.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookAllowLagCompensation(const std::add_pointer_t<cssdk::qboolean()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllFunctions::allow_lag_compensation, callback, post);
    }

    /**
     * @brief Called when an entity is freed by the engine, right before the object's memory is freed.
     * Calls \c OnDestroy and runs the destructor.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFreeEntityPrivateData(const std::add_pointer_t<void(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllNewFunctions::free_entity_private_data, callback, post);
    }

    /**
     * @brief Called when the game unloads this DLL.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGameShutdown(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllNewFunctions::game_shutdown, callback, post);
    }

    /**
     * @brief Called when the engine believes two entities are about to collide.
     * Return 0 if you want the two entities to just pass through each other without colliding or calling the touch function.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookShouldCollide(const std::add_pointer_t<cssdk::qboolean(cssdk::Edict* entity_touched, cssdk::Edict* entity_other)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::DllNewFunctions::should_collide, callback, post);
    }

    /**
     * @brief Called when the engine has received a cvar value from the client in response
     * to an \c engine_func_pointers::query_client_cvar_value call.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarValue(const std::add_pointer_t<void(const cssdk::Edict* client, const char* value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::DllNewFunctions::cvar_value, callback, post);
    }

    /**
     * @brief Called when the engine has received a cvar value from the client in response
     * to a \c engine_func_pointers::query_client_cvar_value2 call.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarValue2(const std::add_pointer_t<void(const cssdk::Edict* client, int request_id, const char* cvar_name, const char* value)> callback,
                               const bool post)
    {
        detail::SetHook(&cssdk::DllNewFunctions::cvar_value2, callback, post);
    }
}
