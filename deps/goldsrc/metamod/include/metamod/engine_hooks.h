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

namespace metamod::engine::detail
{
    inline cssdk::EngineFunctions* engine_hooks = new cssdk::EngineFunctions{};
    inline cssdk::EngineFunctions* engine_post_hooks = new cssdk::EngineFunctions{};

    inline void ClearEngineHooks()
    {
        if (engine_hooks != nullptr) {
            // ReSharper disable once CppRedundantCastExpression
            std::memset(static_cast<void*>(engine_hooks), 0, sizeof(cssdk::EngineFunctions));
        }

        if (engine_post_hooks != nullptr) {
            // ReSharper disable once CppRedundantCastExpression
            std::memset(static_cast<void*>(engine_post_hooks), 0, sizeof(cssdk::EngineFunctions));
        }
    }

    template <typename TMember, typename TCallback>
    void SetHook(TMember cssdk::EngineFunctions::*member, const TCallback callback, const bool post)
    {
        if (post) {
            assert(engine_post_hooks != nullptr);
            engine_post_hooks->*member = callback;
        }
        else {
            assert(engine_hooks != nullptr);
            engine_hooks->*member = callback;
        }
    }
}

namespace metamod::engine
{
    /**
     * @brief Precaches a model.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPrecacheModel(const std::add_pointer_t<int(const char* path)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::precache_model, callback, post);
    }

    /**
     * @brief Precaches a sound.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPrecacheSound(const std::add_pointer_t<int(const char* path)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::precache_sound, callback, post);
    }

    /**
     * @brief Sets the model of the given entity. Also changes the entity bounds based on the model.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetModel(const std::add_pointer_t<void(cssdk::Edict* entity, const char* model)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_model, callback, post);
    }

    /**
     * @brief Gets the index of the given model.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookModelIndex(const std::add_pointer_t<int(const char* model)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::model_index, callback, post);
    }

    /**
     * @brief Gets the number of frames in the given model.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookModelFrames(const std::add_pointer_t<int(int model_index)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::model_frames, callback, post);
    }

    /**
     * @brief Sets the entity bounds. Also relinks the entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetSize(
        const std::add_pointer_t<void(cssdk::Edict* entity, const cssdk::Vector& min, const cssdk::Vector& max)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_size, callback, post);
    }

    /**
     * @brief Changes the level. This will append a change level command to the server command buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookChangeLevel(
        const std::add_pointer_t<void(const char* level_name, const char* landmark_name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::change_level, callback, post);
    }

    /**
     * @brief Does nothing useful. Will trigger a host error if the given entity is not a client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetSpawnParams(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_spawn_params, callback, post);
    }

    /**
     * @brief Does nothing useful. Will trigger a host error if the given entity is not a client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSaveSpawnParams(const std::add_pointer_t<void(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::save_spawn_params, callback, post);
    }

    /**
     * @brief Converts a direction vector to a yaw angle.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookVecToYaw(const std::add_pointer_t<float(const cssdk::Vector& direction)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::vec_to_yaw, callback, post);
    }

    /**
     * @brief Converts a direction vector to angles.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookVecToAngles(
        const std::add_pointer_t<void(const cssdk::Vector& direction_in, cssdk::Vector& angles_out)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::vec_to_angles, callback, post);
    }

    /**
     * @brief Moves the given entity to the given destination.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookMoveToOrigin(
        const std::add_pointer_t<void(cssdk::Edict* entity, const cssdk::Vector& goal, float distance, cssdk::MoveTypeNpc move_type)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::move_to_origin, callback, post);
    }

    /**
     * @brief Changes the entity's yaw angle to approach its ideal yaw.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookChangeYaw(const std::add_pointer_t<void(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::change_yaw, callback, post);
    }

    /**
     * @brief Changes the entity's pitch angle to approach its ideal pitch.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookChangePitch(const std::add_pointer_t<void(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::change_pitch, callback, post);
    }

    /**
     * @brief Finds an entity by comparing strings.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFindEntityByString(
        const std::add_pointer_t<cssdk::Edict*(cssdk::Edict* edict_start_search_after, const char* field, const char* value)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::find_entity_by_string, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetEntityIllumination(const std::add_pointer_t<int(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_entity_illumination, callback, post);
    }

    /**
     * @brief Finds an entity in a sphere.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFindEntityInSphere(
        const std::add_pointer_t<cssdk::Edict*(cssdk::Edict* edict_start_search_after, const cssdk::Vector& origin, float radius)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::find_entity_in_sphere, callback, post);
    }

    /**
     * @brief Finds a client in the potentially visible set.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFindClientInPvs(const std::add_pointer_t<cssdk::Edict*(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::find_client_in_pvs, callback, post);
    }

    /**
     * @brief Find entities in potentially visible set.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEntitiesInPvs(const std::add_pointer_t<cssdk::Edict*(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::entities_in_pvs, callback, post);
    }

    /**
     * @brief Make direction vectors from angles.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookMakeVectors(const std::add_pointer_t<void(const cssdk::Vector& angles)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::make_vectors, callback, post);
    }

    /**
     * @brief Make direction vectors from angles.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookAngleVectors(const std::add_pointer_t<void(const cssdk::Vector& angles, cssdk::Vector& forward, cssdk::Vector& right, cssdk::Vector& up)> callback,
                                 const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::angle_vectors, callback, post);
    }

    /**
     * @brief Allocates an entity dictionary for use with an entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCreateEntity(const std::add_pointer_t<cssdk::Edict*()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::create_entity, callback, post);
    }

    /**
     * @brief Immediately removes the given entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRemoveEntity(const std::add_pointer_t<void(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::remove_entity, callback, post);
    }

    /**
     * @brief Creates an entity of the class \c class_name.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCreateNamedEntity(const std::add_pointer_t<cssdk::Edict*(cssdk::Strind class_name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::create_named_entity, callback, post);
    }

    /**
     * @brief Makes an entity inline. Static entities are copied to the client side and are removed on the server side.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookMakeStatic(const std::add_pointer_t<void(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::make_static, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEntIsOnFloor(const std::add_pointer_t<cssdk::qboolean(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::ent_is_on_floor, callback, post);
    }

    /**
     * @brief Drops the entity to the floor.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookDropToFloor(const std::add_pointer_t<int(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::drop_to_floor, callback, post);
    }

    /**
     * @brief Makes the entity walk.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWalkMove(const std::add_pointer_t<cssdk::qboolean(cssdk::Edict* entity, float yaw, float dist, cssdk::WalkMoveMode mode)> callback,
                             const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::walk_move, callback, post);
    }

    /**
     * @brief Sets the origin of the given entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetOrigin(const std::add_pointer_t<void(cssdk::Edict* entity, const cssdk::Vector& origin)> callback,
                              const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_origin, callback, post);
    }

    /**
     * @brief Emits a sounds from the given entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEmitSound(
        const std::add_pointer_t<void(cssdk::Edict* entity, cssdk::SoundChannel channel, const char* sample, float volume, float attenuation, int flags, int pitch)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::emit_sound, callback, post);
    }

    /**
     * @brief Emits a sounds from the given entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEmitAmbientSound(
        const std::add_pointer_t<void(cssdk::Edict* entity, cssdk::Vector& origin, const char* sample, float volume, float attenuation, int flags, int pitch)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::emit_ambient_sound, callback, post);
    }

    /**
     * @brief Performs a trace between a starting and ending position.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTraceLine(
        const std::add_pointer_t<void(const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, int trace_ignore_flags, cssdk::Edict* entity_to_ignore, cssdk::TraceResult* result)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::trace_line, callback, post);
    }

    /**
     * @brief Traces a toss.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTraceToss(const std::add_pointer_t<void(cssdk::Edict* entity, cssdk::Edict* entity_to_ignore, cssdk::TraceResult* result)> callback,
                              const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::trace_toss, callback, post);
    }

    /**
     * @brief Performs a trace between a starting and ending position, using the given entity's min size and max size.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTraceMonsterHull(
        const std::add_pointer_t<cssdk::qboolean(cssdk::Edict* entity, const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, int trace_ignore_flags, cssdk::Edict* entity_to_ignore, cssdk::TraceResult* result)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::trace_monster_hull, callback, post);
    }

    /**
     * @brief Performs a trace between a starting and ending position, using the specified hull.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTraceHull(
        const std::add_pointer_t<void(const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, int trace_ignore_flags, int hull_number, cssdk::Edict* entity_to_ignore, cssdk::TraceResult* result)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::trace_hull, callback, post);
    }

    /**
     * @brief Performs a trace between a starting and ending position.
     * For studio models this will use the model's hit boxes.
     * Similar to \c trace_hull, but will instead perform a trace in the given world hull
     * using the given entity's model's hulls.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTraceModel(
        const std::add_pointer_t<void(const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, int hull_number, cssdk::Edict* entity, cssdk::TraceResult* result)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::trace_model, callback, post);
    }

    /**
     * @brief Used to get texture info.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTraceTexture(const std::add_pointer_t<const char*(cssdk::Edict* texture_entity, const cssdk::Vector& start_pos, const cssdk::Vector& end_pos)> callback,
                                 const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::trace_texture, callback, post);
    }

    /**
     * @brief Not implemented. Triggers a sys error.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTraceSphere(const std::add_pointer_t<void(const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, int trace_ignore_flags, float radius, cssdk::Edict* entity_to_ignore, cssdk::TraceResult* result)> callback,
                                const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::trace_sphere, callback, post);
    }

    /**
     * @brief Get the aim vector for the given entity.
     * Assumes \c MakeVectors was called with \c entity->vars.angles beforehand.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetAimVector(const std::add_pointer_t<void(cssdk::Edict* entity, float speed, cssdk::Vector& vec_return)> callback,
                                 const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_aim_vector, callback, post);
    }

    /**
     * @brief Issues a command to the server.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookServerCommand(const std::add_pointer_t<void(const char* command)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::server_command, callback, post);
    }

    /**
     * @brief Executes all pending server commands.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookServerExecute(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::server_execute, callback, post);
    }

    /**
     * @brief Sends a client command to the given client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    template <typename... TArgs>
    void HookClientCommand(const std::add_pointer_t<void(cssdk::Edict* client, const char* format, TArgs&&... args)> callback,
                           const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::client_command, callback, post);
    }

    /**
     * @brief Creates a particle effect.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookParticleEffect(const std::add_pointer_t<void(const cssdk::Vector& origin, const cssdk::Vector& direction, float color, float count)> callback,
                                   const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::particle_effect, callback, post);
    }

    /**
     * @brief Sets the given light style to the given value.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookLightStyle(const std::add_pointer_t<void(int style, const char* value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::light_style, callback, post);
    }

    /**
     * @brief Gets the index of the given decal.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookDecalIndex(const std::add_pointer_t<int(const char* name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::decal_index, callback, post);
    }

    /**
     * @brief Gets the contents of the given location in the world.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPointContents(const std::add_pointer_t<int(const cssdk::Vector& origin)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::point_contents, callback, post);
    }

    /**
     * @brief Begins a new network message.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookMessageBegin(const std::add_pointer_t<void(cssdk::MessageType msg_type, int msg_id, const float* origin, cssdk::Edict* client)> callback,
                                 const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::message_begin, callback, post);
    }

    /**
     * @brief Ends a network message.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookMessageEnd(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::message_end, callback, post);
    }

    /**
     * @brief Writes a single unsigned \c cssdk::byte.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWriteByte(const std::add_pointer_t<void(int value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::write_byte, callback, post);
    }

    /**
     * @brief Writes a single character.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWriteChar(const std::add_pointer_t<void(int value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::write_char, callback, post);
    }

    /**
     * @brief Writes a single unsigned short.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWriteShort(const std::add_pointer_t<void(int value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::write_short, callback, post);
    }

    /**
     * @brief Writes a single unsigned int.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWriteLong(const std::add_pointer_t<void(int value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::write_long, callback, post);
    }

    /**
     * @brief Writes a single angle value.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWriteAngle(const std::add_pointer_t<void(float value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::write_angle, callback, post);
    }

    /**
     * @brief Writes a single coordinate value.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWriteCoord(const std::add_pointer_t<void(float value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::write_coord, callback, post);
    }

    /**
     * @brief Writes a single null terminated string.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWriteString(const std::add_pointer_t<void(const char* value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::write_string, callback, post);
    }

    /**
     * @brief Writes a single entity index.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookWriteEntity(const std::add_pointer_t<void(int value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::write_entity, callback, post);
    }

    /**
     * @brief Registers a console variable.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarRegister(const std::add_pointer_t<void(cssdk::CVar* cvar)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cvar_register, callback, post);
    }

    /**
     * @brief Gets the value of console variable as a float.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarGetFloat(const std::add_pointer_t<float(const char* cvar_name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cvar_get_float, callback, post);
    }

    /**
     * @brief Gets the value of console variable as a string.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarGetString(const std::add_pointer_t<const char*(const char* cvar_name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cvar_get_string, callback, post);
    }

    /**
     * @brief Sets the value of console variable as a float.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarSetFloat(const std::add_pointer_t<void(const char* cvar_name, float value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cvar_set_float, callback, post);
    }

    /**
     * @brief Sets the value of console variable as a string.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarSetString(const std::add_pointer_t<void(const char* cvar_name, const char* value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cvar_set_string, callback, post);
    }

    /**
     * @brief Outputs a message to the server console.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    template <typename... TArgs>
    void HookAlertMessage(const std::add_pointer_t<void(cssdk::AlertType type, const char* format, TArgs&&... args)> callback,
                          const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::alert_message, callback, post);
    }

    /**
     * @brief Obsolete. Will print a message to the server console using alert_message indicating if it's being used.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    template <typename... TArgs>
    void HookEngineFilePrint(const std::add_pointer_t<void(void* file, const char* format, TArgs&&... args)> callback,
                             const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::engine_file_print, callback, post);
    }

    /**
     * @brief Allocates memory for \c EntityBase instances.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookAllocEntPrivateData(const std::add_pointer_t<void*(cssdk::Edict* entity, cssdk::int32 size)> callback,
                                        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::alloc_ent_private_data, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEntPrivateData(const std::add_pointer_t<void*(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::ent_private_data, callback, post);
    }

    /**
     * @brief Frees the \c EntityBase memory assigned to entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFreeEntPrivateData(const std::add_pointer_t<void(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::free_ent_private_data, callback, post);
    }

    /**
     * @brief Gets the string assigned to the index.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSzFromIndex(const std::add_pointer_t<const char*(unsigned int string)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::sz_from_index, callback, post);
    }

    /**
     * @brief Allocates a string in the string pool.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookAllocString(const std::add_pointer_t<unsigned int(const char* value)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::alloc_string, callback, post);
    }

    /**
     * @brief Gets the \c cssdk::EntityVars instance assigned to the given entity instance.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetVarsOfEnt(const std::add_pointer_t<cssdk::EntityVars*(cssdk::Edict* entity)> callback,
                                 const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_vars_of_ent, callback, post);
    }

    /**
     * @brief Gets an entity by offset.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEntityOfEntOffset(const std::add_pointer_t<cssdk::Edict*(cssdk::eoffset entity_offset)> callback,
                                      const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::entity_of_ent_offset, callback, post);
    }

    /**
     * @brief Gets the entity offset of the entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEntOffsetOfEntity(const std::add_pointer_t<cssdk::eoffset(const cssdk::Edict* entity)> callback,
                                      const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::ent_offset_of_entity, callback, post);
    }

    /**
     * @brief Gets the entity index of the entity dictionary.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookIndexOfEdict(const std::add_pointer_t<int(const cssdk::Edict* edict)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::index_of_edict, callback, post);
    }

    /**
     * @brief Gets the entity at the given entity index.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEntityOfEntIndex(const std::add_pointer_t<cssdk::Edict*(int entity_index)> callback,
                                     const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::entity_of_ent_index, callback, post);
    }

    /**
     * @brief Gets the entity of an \c cssdk::EntityVars.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFindEntityByVars(const std::add_pointer_t<cssdk::Edict*(cssdk::EntityVars* vars)> callback,
                                     const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::find_entity_by_vars, callback, post);
    }

    /**
     * @brief Gets the model pointer of the given entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetModelPointer(const std::add_pointer_t<void*(cssdk::Edict* entity)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_model_pointer, callback, post);
    }

    /**
     * @brief Registers a user message.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRegUserMessage(const std::add_pointer_t<int(const char* name, int size)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::reg_user_message, callback, post);
    }

    /**
     * @brief Does nothing.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookAnimationAutoMove(const std::add_pointer_t<void(const cssdk::Edict* entity, float time)> callback,
                                      const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::animation_auto_move, callback, post);
    }

    /**
     * @brief Gets the bone position and angles for the given entity and bone.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetBonePosition(const std::add_pointer_t<void(const cssdk::Edict* entity, int bone, cssdk::Vector& origin, cssdk::Vector& angles)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_bone_position, callback, post);
    }

    /**
     * @brief Gets the index of an exported function.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFunctionFromName(const std::add_pointer_t<cssdk::uint32(const char* name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::function_from_name, callback, post);
    }

    /**
     * @brief Gets the name of an exported function.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookNameForFunction(const std::add_pointer_t<const char*(cssdk::uint32 function)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::name_for_function, callback, post);
    }

    /**
     * @brief Sends a message to the client console.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookClientPrint(const std::add_pointer_t<void(cssdk::Edict* entity, cssdk::PrintType type, const char* message)> callback,
                                const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::client_print, callback, post);
    }

    /**
     * @brief Sends a message to the server console.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookServerPrint(const std::add_pointer_t<void(const char* message)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::server_print, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCmdArgs(const std::add_pointer_t<const char*()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cmd_args, callback, post);
    }

    /**
     * @brief Gets the command argument at the given index.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCmdArgv(const std::add_pointer_t<const char*(int argc)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cmd_argv, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCmdArgc(const std::add_pointer_t<int()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cmd_argc, callback, post);
    }

    /**
     * @brief Gets the attachment origin and angles.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetAttachment(const std::add_pointer_t<void(const cssdk::Edict* entity, int attachment, cssdk::Vector& origin, cssdk::Vector& angles)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_attachment, callback, post);
    }

    /**
     * @brief Initializes the CRC instance.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCrc32Init(const std::add_pointer_t<void(cssdk::crc32* pul_crc)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::crc32_init, callback, post);
    }

    /**
     * @brief Processes a buffer and updates the CRC.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCrc32ProcessBuffer(const std::add_pointer_t<void(cssdk::crc32* pul_crc, void* buffer, int len)> callback,
                                       const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::crc32_process_buffer, callback, post);
    }

    /**
     * @brief Processes a single cssdk::byte.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCrc32ProcessByte(const std::add_pointer_t<void(cssdk::crc32* pul_crc, unsigned char ch)> callback,
                                     const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::crc32_process_byte, callback, post);
    }

    /**
     * @brief Finalizes the CRC instance.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCrc32Final(const std::add_pointer_t<cssdk::crc32(cssdk::crc32 pul_crc)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::crc32_final, callback, post);
    }

    /**
     * @brief Generates a random long number in the range [low, high].
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRandomLong(const std::add_pointer_t<cssdk::int32(cssdk::int32 low, cssdk::int32 high)> callback,
                               const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::random_long, callback, post);
    }

    /**
     * @brief Generates a random float number in the range [low, high].
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRandomFloat(const std::add_pointer_t<float(float low, float high)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::random_float, callback, post);
    }

    /**
     * @brief Sets the view of a client to the given entity.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetView(const std::add_pointer_t<void(const cssdk::Edict* client, const cssdk::Edict* view_entity)> callback,
                            const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_view, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookTime(const std::add_pointer_t<float()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::time, callback, post);
    }

    /**
     * @brief Sets the angles of the given client's crosshairs to the given settings.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCrosshairAngle(const std::add_pointer_t<void(const cssdk::Edict* client, float pitch, float yaw)> callback,
                                   const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::crosshair_angle, callback, post);
    }

    /**
     * @brief Loads a file from disk.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookLoadFileForMe(const std::add_pointer_t<cssdk::byte*(const char* file_name, int* length)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::load_file_for_me, callback, post);
    }

    /**
     * @brief Frees the buffer provided by the \c LoadFileForMe.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFreeFile(const std::add_pointer_t<void(void* buffer)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::free_file, callback, post);
    }

    /**
     * @brief Signals the engine that a section has ended.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEndSection(const std::add_pointer_t<void(const char* section_name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::end_section, callback, post);
    }

    /**
     * @brief Compares file times.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCompareFileTime(const std::add_pointer_t<cssdk::qboolean(char* file_name1, char* file_name2, int* compare)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::compare_file_time, callback, post);
    }

    /**
     * @brief Gets the game directory name.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetGameDir(const std::add_pointer_t<void(char* game_dir)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_game_dir, callback, post);
    }

    /**
     * @brief Registers a Cvar. Identical to \c CvarRegister, except it doesn't set the \c FCVAR_EXT_DLL flag.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarRegisterVariable(const std::add_pointer_t<void(cssdk::CVar* variable)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cvar_register_variable, callback, post);
    }

    /**
     * @brief Fades the given client's volume.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookFadeClientVolume(
        const std::add_pointer_t<void(const cssdk::Edict* client, int fade_percent, int fade_out_seconds, int hold_time, int fade_in_seconds)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::fade_client_volume, callback, post);
    }

    /**
     * @brief Sets the client's maximum speed value.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetClientMaxSpeed(const std::add_pointer_t<void(cssdk::Edict* client, float new_max_speed)> callback,
                                      const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_client_max_speed, callback, post);
    }

    /**
     * @brief Creates a fake client (bot).
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCreateFakeClient(const std::add_pointer_t<cssdk::Edict*(const char* name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::create_fake_client, callback, post);
    }

    /**
     * @brief Runs client movement for a fake client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRunPlayerMove(
        const std::add_pointer_t<void(cssdk::Edict* fake_client, const cssdk::Vector& view_angles, float forward_move, float side_move, float up_move, unsigned short buttons, cssdk::byte impulse, cssdk::byte msec)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::run_player_move, callback, post);
    }

    /**
     * @brief Computes the total number of entities currently in existence.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookNumberOfEntities(const std::add_pointer_t<int()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::number_of_entities, callback, post);
    }

    /**
     * @brief Gets the given client's info key buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetInfoKeyBuffer(const std::add_pointer_t<char*(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_info_key_buffer, callback, post);
    }

    /**
     * @brief Gets the value of the given key from the given buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookInfoKeyValue(const std::add_pointer_t<char*(char* info_buffer, const char* key)> callback,
                                 const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::info_key_value, callback, post);
    }

    /**
     * @brief Sets the value of the given key in the given buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetKeyValue(const std::add_pointer_t<void(char* info_buffer, const char* key, const char* value)> callback,
                                const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_key_value, callback, post);
    }

    /**
     * @brief Sets the value of the given key in the given buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetClientKeyValue(const std::add_pointer_t<void(int client_index, char* info_buffer, const char* key, const char* value)> callback,
                                      const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_client_key_value, callback, post);
    }

    /**
     * @brief Checks if the given file_name is a valid map.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookIsMapValid(const std::add_pointer_t<cssdk::qboolean(const char* file_name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::is_map_valid, callback, post);
    }

    /**
     * @brief Projects a inline decal in the world.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookStaticDecal(const std::add_pointer_t<void(const cssdk::Vector& origin, int decal_index, int entity_index, int model_index)> callback,
                                const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::static_decal, callback, post);
    }

    /**
     * @brief Precaches a file.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPrecacheGeneric(const std::add_pointer_t<int(const char* path)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::precache_generic, callback, post);
    }

    /**
     * @brief Returns the server assigned user id for this client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetPlayerUserId(const std::add_pointer_t<int(cssdk::Edict* client)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_player_user_id, callback, post);
    }

    /**
     * @brief Builds a sound message to send to a client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookBuildSoundMsg(const std::add_pointer_t<void(cssdk::Edict* entity, int channel, const char* sample, float volume, float attenuation, int flags, int pitch, cssdk::MessageType msg_type, int msg_id, const cssdk::Vector& origin, cssdk::Edict* client)> callback,
                                  const bool post)

    {
        detail::SetHook(&cssdk::EngineFunctions::build_sound_msg, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookIsDedicatedServer(const std::add_pointer_t<cssdk::qboolean()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::is_dedicated_server, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarGetPointer(const std::add_pointer_t<cssdk::CVar*(const char* cvar_name)> callback,
                                   const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cvar_get_pointer, callback, post);
    }

    /**
     * @brief Returns the server assigned WON id for this client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetPlayerWonId(const std::add_pointer_t<unsigned int(cssdk::Edict* client)> callback,
                                   const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_player_won_id, callback, post);
    }

    /**
     * @brief Removes a key from the info buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookInfoRemoveKey(const std::add_pointer_t<void(char* info_buffer, const char* key)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::info_remove_key, callback, post);
    }

    /**
     * @brief Gets the given physics key-value from the given client's buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetPhysicsKeyValue(const std::add_pointer_t<const char*(const cssdk::Edict* client, const char* key)> callback,
                                       const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_physics_key_value, callback, post);
    }

    /**
     * @brief Sets the given physics key-value in the given client's buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetPhysicsKeyValue(const std::add_pointer_t<void(const cssdk::Edict* client, const char* key, const char* value)> callback,
                                       const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_physics_key_value, callback, post);
    }

    /**
     * @brief Gets the physics info string for the given client.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetPhysicsInfoString(const std::add_pointer_t<const char*(const cssdk::Edict* client)> callback,
                                         const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_physics_info_string, callback, post);
    }

    /**
     * @brief Precaches an event.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPrecacheEvent(const std::add_pointer_t<unsigned short(int type, const char* path)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::precache_event, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookPlaybackEvent(
        const std::add_pointer_t<void(int flags, const cssdk::Edict* invoker, unsigned short event_index, float delay, cssdk::Vector& origin, cssdk::Vector& angles, float f_param1, float f_param2, int i_param1, int i_param2, cssdk::qboolean b_param1, cssdk::qboolean b_param2)> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::playback_event, callback, post);
    }

    /**
     * @brief Sets the fat potentially visible set buffer to contain data based on the given origin.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetFatPvs(const std::add_pointer_t<unsigned char*(cssdk::Vector& origin)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_fat_pvs, callback, post);
    }

    /**
     * @brief Sets the fat potentially audible set buffer to contain data based on the given origin.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetFatPas(const std::add_pointer_t<unsigned char*(cssdk::Vector& origin)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_fat_pas, callback, post);
    }

    /**
     * @brief Checks if the given entity is visible in the given visible set.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCheckVisibility(const std::add_pointer_t<cssdk::qboolean(cssdk::Edict* entity, unsigned char* set)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::check_visibility, callback, post);
    }

    /**
     * @brief Marks the given field in the given list as set.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookDeltaSetField(const std::add_pointer_t<void(void* fields, const char* field_name)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::delta_set_field, callback, post);
    }

    /**
     * @brief Marks the given field in the given list as not set.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookDeltaUnsetField(const std::add_pointer_t<void(void* fields, const char* field_name)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::delta_unset_field, callback, post);
    }

    /**
     * @brief Adds a delta encoder.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookDeltaAddEncoder(
        const std::add_pointer_t<void(const char* name, void (*conditional_encode)(void* fields, const unsigned char* from, const unsigned char* to))> callback,
        const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::delta_add_encoder, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetCurrentPlayer(const std::add_pointer_t<int()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_current_player, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCanSkipPlayer(const std::add_pointer_t<cssdk::qboolean(const cssdk::Edict* client)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::can_skip_player, callback, post);
    }

    /**
     * @brief Finds the index of a delta field.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookDeltaFindField(const std::add_pointer_t<int(void* fields, const char* field_name)> callback,
                                   const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::delta_find_field, callback, post);
    }

    /**
     * @brief Marks a delta field as set by index.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookDeltaSetFieldByIndex(const std::add_pointer_t<void(void* fields, int field_number)> callback,
                                         const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::delta_set_field_by_index, callback, post);
    }

    /**
     * @brief Marks a delta field as not set by index.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookDeltaUnsetFieldByIndex(const std::add_pointer_t<void(void* fields, int field_number)> callback,
                                           const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::delta_unset_field_by_index, callback, post);
    }

    /**
     * @brief Used to filter contents checks.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSetGroupMask(const std::add_pointer_t<void(int mask, int operation)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::set_group_mask, callback, post);
    }

    /**
     * @brief Creates an instanced baseline. Used to define a baseline for a particular entity type.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCreateInstancedBaseline(const std::add_pointer_t<int(cssdk::Strind class_name, cssdk::EntityState* baseline)> callback,
                                            const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::create_instanced_baseline, callback, post);
    }

    /**
     * @brief Directly sets a console variable value.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookCvarDirectSet(const std::add_pointer_t<void(cssdk::CVar* cvar, const char* value)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::cvar_direct_set, callback, post);
    }

    /**
     * @brief Forces the client and server to be running with the same version of the specified file (e.g., a client model).
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookForceUnmodified(const std::add_pointer_t<void(cssdk::ForceType type, cssdk::Vector& min_size, cssdk::Vector& max_size, const char* file_name)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::force_unmodified, callback, post);
    }

    /**
     * @brief Get client statistics.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetPlayerStats(const std::add_pointer_t<void(const cssdk::Edict* client, int* ping, int* packet_loss)> callback,
                                   const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_player_stats, callback, post);
    }

    /**
     * @brief Adds a server command.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookAddServerCommand(const std::add_pointer_t<void(const char* cmd_name, void (*callback)())> callback,
                                     const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::add_server_command, callback, post);
    }

    /**
     * @brief Gets whether the given receiver can hear the given sender.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookVoiceGetClientListening(const std::add_pointer_t<cssdk::qboolean(int receiver, int sender)> callback,
                                            const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::voice_get_client_listening, callback, post);
    }

    /**
     * @brief Sets whether the given receiver can hear the given sender.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookVoiceSetClientListening(const std::add_pointer_t<cssdk::qboolean(int receiver, int sender, cssdk::qboolean listen)> callback,
                                            const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::voice_set_client_listening, callback, post);
    }

    /**
     * @brief Gets the client's auth ID.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetPlayerAuthId(const std::add_pointer_t<const char*(cssdk::Edict* client)> callback,
                                    const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_player_auth_id, callback, post);
    }

    /**
     * @brief Gets the sequence that has the given entry name.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSequenceGet(const std::add_pointer_t<cssdk::SequenceEntry*(const char* file_name, const char* entry_name)> callback,
                                const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::sequence_get, callback, post);
    }

    /**
     * @brief Picks a sentence from the given group.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookSequencePickSentence(const std::add_pointer_t<cssdk::SentenceEntry*(const char* group_name, int pick_method, int* picked)> callback,
                                         const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::sequence_pick_sentence, callback, post);
    }

    /**
     * @brief LH: Give access to file size via filesystem.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetFileSize(const std::add_pointer_t<int(const char* file_name)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_file_size, callback, post);
    }

    /**
     * @brief Gets the average wave length in seconds.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetApproxWavePlayLen(const std::add_pointer_t<unsigned int(const char* file_path)> callback,
                                         const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_approx_wave_play_len, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookIsCareerMatch(const std::add_pointer_t<cssdk::qboolean()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::is_career_match, callback, post);
    }

    /**
     * @brief N/D
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetLocalizedStringLength(const std::add_pointer_t<int(const char* label)> callback,
                                             const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_localized_string_length, callback, post);
    }

    /**
     * @brief Marks the message with the given ID as having been shown.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookRegisterTutorMessageShown(const std::add_pointer_t<void(int message_id)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::register_tutor_message_shown, callback, post);
    }

    /**
     * @brief Gets the number of times the message with the given ID has been shown.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookGetTimesTutorMessageShown(const std::add_pointer_t<int(int message_id)> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::get_times_tutor_message_shown, callback, post);
    }

    /**
     * @brief Processes the tutor message decay buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookProcessTutorMessageDecayBuffer(const std::add_pointer_t<void(int* buffer, int buffer_length)> callback,
                                                   const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::process_tutor_message_decay_buffer, callback, post);
    }

    /**
     * @brief Constructs the tutor message decay buffer.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookConstructTutorMessageDecayBuffer(const std::add_pointer_t<void(int* buffer, int buffer_length)> callback,
                                                     const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::construct_tutor_message_decay_buffer, callback, post);
    }

    /**
     * @brief Resets tutor message decay data.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookResetTutorMessageDecayData(const std::add_pointer_t<void()> callback, const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::reset_tutor_message_decay_data, callback, post);
    }

    /**
     * @brief Queries the given client for a cvar value.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookQueryClientCvarValue(const std::add_pointer_t<void(const cssdk::Edict* client, const char* cvar_name)> callback,
                                         const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::query_client_cvar_value, callback, post);
    }

    /**
     * @brief Queries the given client for a cvar value.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookQueryClientCvarValue2(const std::add_pointer_t<void(const cssdk::Edict* client, const char* cvar_name, int request_id)> callback,
                                          const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::query_client_cvar_value2, callback, post);
    }

    /**
     * @brief Checks if a command line parameter was provided.
     *
     * @param callback The callback function pointer or \c nullptr to disable this hook.
     * @param post Is this a post hook?
    */
    inline void HookEngCheckParam(const std::add_pointer_t<int(const char* cmd_line_token, char** next)> callback,
                                  const bool post)
    {
        detail::SetHook(&cssdk::EngineFunctions::eng_check_param, callback, post);
    }
}
