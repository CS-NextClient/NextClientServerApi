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
#include <utility>

//-V::106

namespace metamod::engine
{
    /**
     * @brief Precaches a model.
     *
     * @param path Path to the model. Starts in the game directory.
     * This string must live for at least as long as the map itself.
     *
     * @return Index of the model.
     *
     * @note If path is null, is empty or contains an invalid value in the first character, triggers a host error.
     * @note If the maximum number of model precacheable resources has been reached, triggers a host error.
     * @note If this is called after \c ServerActivate, triggers a host error.
    */
    inline int PrecacheModel(const char* const path)
    {
        return cssdk::g_engine_funcs.precache_model(path);
    }

    /**
     * @brief Precaches a sound.
     *
     * @param path Path tot the sound. Starts in the sound/ directory.
     * This string must live for at least as long as the map itself.
     *
     * @return Index of the sound.
     *
     * @note If path is null, is empty or contains an invalid value in the first character, triggers a host error.
     * @note If the maximum number of sound precacheable resources has been reached, triggers a host error.
     * @note If this is called after \c ServerActivate, triggers a host error.
    */
    inline int PrecacheSound(const char* const path)
    {
        return cssdk::g_engine_funcs.precache_sound(path);
    }

    /**
     * @brief Sets the model of the given entity. Also changes the entity bounds based on the model.
     *
     * @param entity Entity to set the model on.
     * @param model Path to the model.
     * This string must live for at least as long as the map itself.
    */
    inline void SetModel(cssdk::Edict* const entity, const char* const model)
    {
        cssdk::g_engine_funcs.set_model(entity, model);
    }

    /**
     * @brief Gets the index of the given model.
     *
     * @param model Path to the model whose index is to be returned.
     *
     * @return Index of the model.
     *
     * @note If the given model was not precached, shuts the game down.
    */
    inline int ModelIndex(const char* const model)
    {
        return cssdk::g_engine_funcs.model_index(model);
    }

    /**
     * @brief Gets the number of frames in the given model.
     *
     * @param model_index Index of the model whose frame count is to be returned.
     *
     * @return Frame count of the model.
     *
     * @note If this is a sprite, returns the number of sprite frames.
     * @note If this is a studio model, this is all of the submodels in each body part multiplied with each-other.
     * It represents the number of variations that can be created by changing submodels (e.g. heads, weapons, etc).
     * Otherwise, returns 1.
    */
    inline int ModelFrames(const int model_index)
    {
        return cssdk::g_engine_funcs.model_frames(model_index);
    }

    /**
     * @brief Sets the entity bounds. Also relinks the entity:
     * \c EntityVars::min_size, \c EntityVars::max_size and \c EntityVars::size are changed.
     *
     * @param entity Entity whose bounds are to be changed.
     * @param min Minimum relative bounds.
     * @param max Maximum relative bounds.
     *
     * @note If the bounds are backwards (max smaller than min), a host error is triggered.
    */
    inline void SetSize(cssdk::Edict* const entity, const cssdk::Vector& min, const cssdk::Vector& max)
    {
        cssdk::g_engine_funcs.set_size(entity, min, max);
    }

    /**
     * @brief Changes the level. This will append a changelevel command to the server command buffer.
     *
     * @param level_name Name of the level to change to.
     * @param landmark_name Name of the landmark to use. If null, no landmark is used.
     *
     * @note Calling \c ServerExecute will trigger the changelevel.
     * Subsequent calls made during the same map will be ignored.
    */
    inline void ChangeLevel(const char* const level_name, const char* const landmark_name)
    {
        cssdk::g_engine_funcs.change_level(level_name, landmark_name);
    }

    /**
     * @brief Does nothing useful. Will trigger a host error if the given entity is not a client.
    */
    inline void GetSpawnParams(cssdk::Edict* const client)
    {
        cssdk::g_engine_funcs.get_spawn_params(client);
    }

    /**
     * @brief Does nothing useful. Will trigger a host error if the given entity is not a client.
     * Will trigger a sys error if the given entity is invalid.
    */
    inline void SaveSpawnParams(cssdk::Edict* const client)
    {
        cssdk::g_engine_funcs.save_spawn_params(client);
    }

    /**
     * @brief Converts a direction vector to a yaw angle.
     *
     * @param direction Direction vector.
     *
     * @return Yaw angle.
    */
    inline float VecToYaw(const cssdk::Vector& direction)
    {
        return cssdk::g_engine_funcs.vec_to_yaw(direction);
    }

    /**
     * @brief Converts a direction vector to angles.
     *
     * @param direction_in Direction vector.
     * @param angles_out Angles.
    */
    inline void VecToAngles(const cssdk::Vector& direction_in, cssdk::Vector& angles_out)
    {
        cssdk::g_engine_funcs.vec_to_angles(direction_in, angles_out);
    }

    /**
     * @brief Moves the given entity to the given destination.
     *
     * @param entity Entity to move.
     * @param goal Destination.
     * @param distance Distance to cover in this movement operation, in units.
     * @param move_type Move type.
    */
    inline void MoveToOrigin(cssdk::Edict* const entity, const cssdk::Vector& goal,
                             const float distance, const cssdk::MoveTypeNpc move_type)
    {
        cssdk::g_engine_funcs.move_to_origin(entity, goal, distance, move_type);
    }

    /**
     * @brief Changes the entity's yaw angle to approach its ideal yaw.
     * Yaw is updated at \c EntityVars::yaw_speed speed to match \c EntityVars::ideal_yaw.
     *
     * @param entity Entity whose yaw is to be changed.
    */
    inline void ChangeYaw(cssdk::Edict* const entity)
    {
        cssdk::g_engine_funcs.change_yaw(entity);
    }

    /**
     * @brief Changes the entity's pitch angle to approach its ideal pitch.
     * Pitch is updated at \c EntityVars::pitch_speed speed to match \c EntityVars::ideal_pitch.
     *
     * @param entity Entity whose pitch is to be changed.
    */
    inline void ChangePitch(cssdk::Edict* const entity)
    {
        cssdk::g_engine_funcs.change_pitch(entity);
    }

    /**
     * @brief Finds an entity by comparing strings.
     *
     * @param edict_start_search_after cssdk::Edict to start searching after.
     * @param field Entity field to compare. Only string fields in \c EntityVars are considered.
     * @param value Value to compare to.
     *
     * @return If the given field exists, and the given value is not null,
     * and an entity has a matching value, returns the edict of that entity.
     * Otherwise, returns null.
    */
    inline cssdk::Edict* FindEntityByString(cssdk::Edict* const edict_start_search_after,
                                            const char* const field, const char* const value)
    {
        return cssdk::g_engine_funcs.find_entity_by_string(edict_start_search_after, field, value);
    }

    /**
     * @brief N/D
     *
     * @param entity Entity whose light value is to be retrieved.
     *
     * @return If the given entity is null, returns -1. \n
     * If the given entity is a client or the world, returns \c EntityVars::light_level. \n
     * Otherwise, returns the color of the floor that the entity is standing on.
    */
    inline int GetEntityIllumination(cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.get_entity_illumination(entity);
    }

    /**
     * @brief Finds an entity in a sphere.
     *
     * @param edict_start_search_after cssdk::Edict to start searching after.
     * @param origin Origin in the world to center the sphere around.
     * @param radius Sphere radius.
     *
     * @return The first valid entity in the sphere's radius, or null if no entity can be found.
    */
    inline cssdk::Edict* FindEntityInSphere(cssdk::Edict* const edict_start_search_after,
                                            const cssdk::Vector& origin, const float radius)
    {
        return cssdk::g_engine_funcs.find_entity_in_sphere(edict_start_search_after, origin, radius);
    }

    /**
     * @brief Finds a client in the Potentially Visible Set.
     *
     * @param entity Entity whose origin and view offset should be used to determine which client is visible.
     *
     * @return Client, or null if no client could be found.
     *
     * @note This function's behavior is unexpected: it will get the next client every 0.1 seconds,
     * and check if the entity can see it.
     * If so, the client is returned. Otherwise, the world is returned.
    */
    inline cssdk::Edict* FindClientInPvs(cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.find_client_in_pvs(entity);
    }

    /**
     * @brief Find entities in Potentially Visible Set.
     *
     * @param entity Entity whose origin and view offset should be used to determine which entities are visible.
     *
     * @return First entity in the chain of entities that are visible, or worldspawn if no entities are visible.
     *
     * @note This builds a list of entities using \c EntityVars::chain.
     * @note This list is temporary, so store its results elsewhere if it is needed later on.
     * @note This operation is expensive as it checks every entity. Avoid using this unless it is absolutely necessary.
    */
    inline cssdk::Edict* EntitiesInPvs(cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.entities_in_pvs(entity);
    }

    /**
     * @brief Make direction vectors from angles.
     *
     * @param angles Angles to convert to direction vectors.
     *
     * @note The results are stored in \c g_global_vars->vec_forward,
     * \c g_global_vars->vec_right and \c g_global_vars->vec_up.
    */
    inline void MakeVectors(const cssdk::Vector& angles)
    {
        cssdk::g_engine_funcs.make_vectors(angles);
    }

    /**
     * @brief Make direction vectors from angles.
     *
     * @param angles Angles to convert to direction vectors.
     * @param forward Stores the forward direction vector.
     * @param right Stores the right direction vector.
     * @param up Stores the up direction vector.
    */
    inline void AngleVectors(const cssdk::Vector& angles, cssdk::Vector& forward, cssdk::Vector& right, cssdk::Vector& up)
    {
        cssdk::g_engine_funcs.angle_vectors(angles, forward, right, up);
    }

    /**
     * @brief Allocates an edict for use with an entity.
     *
     * @return Newly allocated edict.
     *
     * @note If the engine is out of edicts, triggers a sys error.
     * @note If the engine is not ready for entity instantiation yet (e.g. during restore), triggers a sys error.
    */
    inline cssdk::Edict* CreateEntity()
    {
        return cssdk::g_engine_funcs.create_entity();
    }

    /**
     * @brief Immediately removes the given entity.
     * Increments the edict serial number.
     *
     * @param entity Entity to remove.
    */
    inline void RemoveEntity(cssdk::Edict* const entity)
    {
        cssdk::g_engine_funcs.remove_entity(entity);
    }

    /**
     * @brief Creates an entity of the class \c classname.
     *
     * @param classname Name of the class to instantiate.
     *
     * @return cssdk::Edict of the entity that was instantiated, or null if no such entity exists.
     *
     * @note This will not fall back to invoking the custom entity handler if the given class does not exist.
    */
    inline cssdk::Edict* CreateNamedEntity(const cssdk::Strind& classname)
    {
        return cssdk::g_engine_funcs.create_named_entity(classname);
    }

    /**
     * @brief Makes an entity inline.
     *
     * @param entity Entity to make inline.
     *
     * @note Static entities are copied to the client side and are removed on the server side.
     * @note Only valid during map spawn.
    */
    inline void MakeStatic(cssdk::Edict* const entity)
    {
        cssdk::g_engine_funcs.make_static(entity);
    }

    /**
     * @brief Returns whether the given entity is on the floor.
     *
     * @param entity Entity to check.
     *
     * @return 1 if the entity is on the floor, 0 otherwise.
    */
    inline cssdk::qboolean EntIsOnFloor(cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.ent_is_on_floor(entity);
    }

    /**
     * @brief Drops the entity to the floor.
     * The entity will be moved down to the floor, effectively being teleported.
     *
     * @param entity Entity to drop.
     *
     * @return -1 if the entity is stuck inside a solid object. \n
     * 0 if the floor is further than 256 units away. \n
     * 1 if the entity was dropped to the floor.
     *
     * @note Maximum drop distance is 256 units.
     * If the floor is further than that away, the entity will not be moved.
    */
    inline int DropToFloor(cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.drop_to_floor(entity);
    }

    /**
     * @brief Makes the entity walk.
     *
     * @param entity Entity to move.
     * @param yaw Yaw distance. This is the entity's current movement direction in the XY plane.
     * @param dist Distance to move, in units.
     * @param mode Movement type.
     *
     * @return 1 if the move succeeded (no obstacles in the way), 0 otherwise.
     *
     * @note The entity must be capable of flying (\c FL_FLY) or swimming (\c FL_SWIM),
     * or be on the ground (\c FL_ON_GROUND).
    */
    inline cssdk::qboolean WalkMove(cssdk::Edict* const entity, const float yaw, const float dist,
                                    const cssdk::WalkMoveMode mode)
    {
        return cssdk::g_engine_funcs.walk_move(entity, yaw, dist, mode);
    }

    /**
     * @brief Sets the origin of the given entity.
     *
     * @param entity Entity whose origin is to be set.
     * @param origin Origin to set.
    */
    inline void SetOrigin(cssdk::Edict* const entity, const cssdk::Vector& origin)
    {
        cssdk::g_engine_funcs.set_origin(entity, origin);
    }

    /**
     * @brief Emits a sounds from the given entity.
     *
     * @param entity Entity that is emitting the sound.
     * @param channel Channel to play the sound on.
     * @param sample Sample to play. The sound must be precached.
     * @param volume Sound volume. Must be a value in the range 0 - 1.
     * @param attenuation Sound attenuation.
     * @param flags Sound flags.
     * @param pitch Sound pitch. Must be a value in the range 0 - 255.
    */
    inline void EmitSound(cssdk::Edict* const entity, const cssdk::SoundChannel channel, const char* const sample,
                          const float volume, const float attenuation, const int flags, const int pitch)
    {
        cssdk::g_engine_funcs.emit_sound(entity, channel, sample, volume, attenuation, flags, pitch);
    }

    /**
     * @brief Emits a sounds from the given entity.
     *
     * @param entity Entity that is emitting the sound.
     * @param origin Position in the world to play the sound at.
     * @param sample Sample to play. The sound must be precached.
     * @param volume Sound volume. Must be a value in the range 0 - 1.
     * @param attenuation Sound attenuation.
     * @param flags Sound flags.
     * @param pitch Sound pitch. Must be a value in the range 0 - 255.
    */
    inline void EmitAmbientSound(cssdk::Edict* const entity, cssdk::Vector& origin, const char* const sample,
                                 const float volume, const float attenuation, const int flags, const int pitch)
    {
        cssdk::g_engine_funcs.emit_ambient_sound(entity, origin, sample, volume, attenuation, flags, pitch);
    }

    /**
     * @brief Performs a trace between a starting and ending position.
     *
     * @param start_pos Start position.
     * @param end_pos End position.
     * @param trace_ignore_flags Bit vector containing trace flags (see \c TR_IGNORE_* flags).
     * @param entity_to_ignore Entity to ignore during the trace.
     * @param result Trace result instance.
    */
    inline void TraceLine(const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, const int trace_ignore_flags,
                          cssdk::Edict* const entity_to_ignore, cssdk::TraceResult* result)
    {
        cssdk::g_engine_funcs.trace_line(start_pos, end_pos, trace_ignore_flags, entity_to_ignore, result);
    }

    /**
     * @brief Traces a toss.
     * This simulates tossing the entity using its current origin, velocity, angular velocity, angles and gravity.
     *
     * @param entity Entity to toss.
     * @param entity_to_ignore Entity to ignore during the trace.
     * @param result Trace result instance.
     *
     * @note This does not use the same code as \c MoveTypeEntity::Toss, and may return different results.
    */
    inline void TraceToss(cssdk::Edict* const entity, cssdk::Edict* const entity_to_ignore, cssdk::TraceResult* const result)
    {
        cssdk::g_engine_funcs.trace_toss(entity, entity_to_ignore, result);
    }

    /**
     * @brief Performs a trace between a starting and ending position, using the given entity's min_size and max_size.
     *
     * @param entity Entity whose hull will be used.
     * @param start_pos Start position.
     * @param end_pos End position.
     * @param trace_ignore_flags Bit vector containing trace flags (see \c TR_IGNORE_* flags).
     * @param entity_to_ignore Entity to ignore during the trace.
     * @param result Trace result instance.
     *
     * @return 1 if the trace was entirely in a solid object, or if it hit something.
     *
     * @note This can be any entity, not just monsters.
    */
    inline cssdk::qboolean TraceMonsterHull(cssdk::Edict* const entity, const cssdk::Vector& start_pos,
                                            const cssdk::Vector& end_pos, const int trace_ignore_flags,
                                            cssdk::Edict* const entity_to_ignore, cssdk::TraceResult* const result)
    {
        return cssdk::g_engine_funcs.trace_monster_hull(entity, start_pos, end_pos,
                                                        trace_ignore_flags, entity_to_ignore, result);
    }

    /**
     * @brief Performs a trace between a starting and ending position, using the specified hull.
     *
     * @param start_pos Start position.
     * @param end_pos End position.
     * @param trace_ignore_flags Bit vector containing trace flags (see \c TR_IGNORE_* flags).
     * @param hull_number Hull to use.
     * @param entity_to_ignore Entity to ignore during the trace.
     * @param result Trace result instance.
    */
    inline void TraceHull(const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, const int trace_ignore_flags,
                          const int hull_number, cssdk::Edict* const entity_to_ignore, cssdk::TraceResult* const result)
    {
        cssdk::g_engine_funcs.trace_hull(start_pos, end_pos, trace_ignore_flags, hull_number, entity_to_ignore, result);
    }

    /**
     * @brief Performs a trace between a starting and ending position.
     * Similar to \c trace_hull, but will instead perform a trace in the given world hull using the given entity's model's hulls.
     * For studio models this will use the model's hit boxes.
     *
     * @param start_pos Start position.
     * @param end_pos End position.
     * @param hull_number Hull to use.
     * @param entity Entity whose hull will be used.
     * @param result Trace result instance.
     *
     * @note If the given entity's model is a studio model, uses its hit boxes.
     * @note If it's a brush model, the brush model's hull for the given hull number is used
     * (this may differ if custom brush hull sizes are in use).
     * @note Otherwise, the entity bounds are converted into a hull.
    */
    inline void TraceModel(const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, const int hull_number,
                           cssdk::Edict* const entity, cssdk::TraceResult* const result)
    {
        cssdk::g_engine_funcs.trace_model(start_pos, end_pos, hull_number, entity, result);
    }

    /**
     * @brief Used to get texture info.
     * The given entity must have a brush model set.
     *
     * @param texture_entity Entity whose texture is to be retrieved.
     * @param start_pos Start position.
     * @param end_pos End position.
     *
     * @return Texture instance, or null if no texture could be found.
     *
     * @note If the trace line intersects the model, the texture of the surface it intersected is returned.
     * Otherwise, returns null.
    */
    inline const char* TraceTexture(cssdk::Edict* texture_entity, const cssdk::Vector& start_pos, const cssdk::Vector& end_pos)
    {
        return cssdk::g_engine_funcs.trace_texture(texture_entity, start_pos, end_pos);
    }

    /**
     * @brief Not implemented. Triggers a sys error.
    */
    inline void TraceSphere(const cssdk::Vector& start_pos, const cssdk::Vector& end_pos, const int trace_ignore_flags,
                            const float radius, cssdk::Edict* const entity_to_ignore, cssdk::TraceResult* const result)
    {
        cssdk::g_engine_funcs.trace_sphere(start_pos, end_pos, trace_ignore_flags, radius, entity_to_ignore, result);
    }

    /**
     * @brief Get the aim vector for the given entity.
     * Assumes \c make_vectors was called with \c entity->vars.angles beforehand.
     *
     * @param entity Entity to retrieve the aim vector for.
     * @param speed Unused.
     * @param vec_return The resulting aim vector.
     *
     * @note The aim vector is the auto aim vector used when sv_aim is enabled.
     * @note It will snap to entities that are close to the entity's forward vector axis.
    */
    inline void GetAimVector(cssdk::Edict* const entity, const float speed, cssdk::Vector& vec_return)
    {
        cssdk::g_engine_funcs.get_aim_vector(entity, speed, vec_return);
    }

    /**
     * @brief Issues a command to the server.
     *
     * @param command Command to execute.
     *
     * @note The command must end with either a newline or a semicolon in order to be considered valid by the engine.
     * @note The command will be enqueued for execution at a later point.
    */
    inline void ServerCommand(const char* const command)
    {
        cssdk::g_engine_funcs.server_command(command);
    }

    /**
     * @brief Executes all pending server commands.
     *
     * @note If a changelevel command is in the buffer, this can result in the caller being freed before this call returns.
    */
    inline void ServerExecute()
    {
        cssdk::g_engine_funcs.server_execute();
    }

    /**
     * @brief Sends a client command to the given client.
     *
     * @param client \c cssdk::Edict of the client that should execute the command.
     * @param format Format string.
     * @param args Format arguments.
    */
    template <typename... Args>
    void ClientCommand(cssdk::Edict* const client, const char* const format, Args&&... args)
    {
        cssdk::g_engine_funcs.client_command(client, format, std::forward<Args>(args)...);
    }

    /**
     * @brief Creates a particle effect.
     *
     * @param origin Origin in the world.
     * @param direction Direction of the effect.
     * @param color Color of the effect.
     * @param count Number of particles to create.
    */
    inline void ParticleEffect(const cssdk::Vector& origin, const cssdk::Vector& direction, const float color, const float count)
    {
        cssdk::g_engine_funcs.particle_effect(origin, direction, color, count);
    }

    /**
     * @brief Sets the given light style to the given value.
     *
     * @param style Style index.
     * @param value Value to set. This string must live for at least as long as the map itself.
    */
    inline void LightStyle(const int style, const char* const value)
    {
        cssdk::g_engine_funcs.light_style(style, value);
    }

    /**
     * @brief Gets the index of the given decal.
     *
     * @param name Name of the decal.
     *
     * @return Index of the decal, or -1 if the decal couldn't be found.
    */
    inline int DecalIndex(const char* const name)
    {
        return cssdk::g_engine_funcs.decal_index(name);
    }

    /**
     * @brief Gets the contents of the given location in the world.
     *
     * @param origin Location in the world.
     *
     * @return Contents of the location in the world (see \c CONTENTS_* constants).
    */
    inline int PointContents(const cssdk::Vector& origin)
    {
        return cssdk::g_engine_funcs.point_contents(origin);
    }

    /**
     * @brief Begins a new network message.
     *
     * @param msg_type Message type.
     * @param msg_id Message ID.
     * @param origin Origin to use for PVS and PAS checks (optional).
     * @param client If it's a message to one client, client to send the message to (optional).
     *
     * @note If the message type is to one client, and no client is provided, triggers a sys error.
     * @note If the message type is to all clients, and a client is provided, triggers a sys error.
     * @note If another message had already been started and was not ended, triggers a sys error.
    */
    inline void MessageBegin(const cssdk::MessageType msg_type, const int msg_id,
                             const float* const origin = nullptr, cssdk::Edict* const client = nullptr)
    {
        cssdk::g_engine_funcs.message_begin(msg_type, msg_id, origin, client);
    }

    /**
     * @brief Begins a new network message.
     *
     * @param msg_type Message type.
     * @param msg_id Message ID.
     * @param origin Origin to use for PVS and PAS checks (optional).
     * @param client If it's a message to one client, client to send the message to (optional).
     *
     * @note If the message type is to one client, and no client is provided, triggers a sys error.
     * @note If the message type is to all clients, and a client is provided, triggers a sys error.
     * @note If another message had already been started and was not ended, triggers a sys error.
    */
    inline void MessageBegin(const cssdk::MessageType msg_type, const int msg_id, const cssdk::Vector& origin,
                             cssdk::Edict* const client)
    {
        cssdk::g_engine_funcs.message_begin(msg_type, msg_id, static_cast<const float*>(origin), client);
    }

    /**
     * @brief Ends a network message.
     *
     * @note If no message had been started, triggers a sys error.
     * @note If the buffer had overflowed, triggers a sys error.
     * @note If the message is a user message, and exceeds 192 bytes, triggers a host error.
     * @note If the message has a fixed size and the wrong size was written, triggers a sys error.
     * @note If the given client is invalid, triggers a host error.
    */
    inline void MessageEnd()
    {
        cssdk::g_engine_funcs.message_end();
    }

    /**
     * @brief Writes a single unsigned byte.
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteByte(const int value)
    {
        cssdk::g_engine_funcs.write_byte(value);
    }

    /**
     * @brief Writes a single character.
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteChar(const int value)
    {
        cssdk::g_engine_funcs.write_char(value);
    }

    /**
     * @brief Writes a single unsigned short.
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteShort(const int value)
    {
        cssdk::g_engine_funcs.write_short(value);
    }

    /**
     * @brief Writes a single unsigned int.
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteLong(const int value)
    {
        cssdk::g_engine_funcs.write_long(value);
    }

    /**
     * @brief Writes a single angle value.
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteAngle(const float value)
    {
        cssdk::g_engine_funcs.write_angle(value);
    }

    /**
     * @brief Writes a single coordinate value.
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteCoord(const float value)
    {
        cssdk::g_engine_funcs.write_coord(value);
    }

    /**
     * @brief Writes a coordinates (x, y, z).
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteCoord(const cssdk::Vector& value)
    {
        cssdk::g_engine_funcs.write_coord(value.x);
        cssdk::g_engine_funcs.write_coord(value.y);
        cssdk::g_engine_funcs.write_coord(value.z);
    }

    /**
     * @brief Writes a coordinates (x, y, z).
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteCoord(const float* const value)
    {
        cssdk::g_engine_funcs.write_coord(value[0]);
        cssdk::g_engine_funcs.write_coord(value[1]);
        cssdk::g_engine_funcs.write_coord(value[2]);
    }

    /**
     * @brief Writes a single null terminated string.
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteString(const char* const value)
    {
        cssdk::g_engine_funcs.write_string(value);
    }

    /**
     * @brief Writes a single entity index.
     *
     * @note If no message had been started, triggers a sys error.
    */
    inline void WriteEntity(const int value)
    {
        cssdk::g_engine_funcs.write_entity(value);
    }

    /**
     * @brief Registers a cvar.
     * Sets the flag \c FCVAR_EXT_DLL on the cvar.
     *
     * @param cvar Cvar to register.
    */
    inline void CvarRegister(cssdk::CVar* const cvar)
    {
        cssdk::g_engine_funcs.cvar_register(cvar);
    }

    /**
     * @brief Gets the value of a cvar as a float.
     *
     * @param cvar_name Name of the cvar whose value is to be retrieved.
     *
     * @return Value of the cvar, or 0 if the cvar doesn't exist.
    */
    inline float CvarGetFloat(const char* const cvar_name)
    {
        return cssdk::g_engine_funcs.cvar_get_float(cvar_name);
    }

    /**
     * @brief Gets the value of a cvar as a string.
     *
     * @param cvar_name Name of the cvar whose value is to be retrieved.
     *
     * @return Value of the cvar, or an empty string if the cvar doesn't exist.
    */
    inline const char* CvarGetString(const char* const cvar_name)
    {
        return cssdk::g_engine_funcs.cvar_get_string(cvar_name);
    }

    /**
     * @brief Sets the value of a cvar as a float.
     *
     * @param cvar_name Name of the cvar whose value to set.
     * @param value Value to set.
    */
    inline void CvarSetFloat(const char* const cvar_name, const float value)
    {
        cssdk::g_engine_funcs.cvar_set_float(cvar_name, value);
    }

    /**
     * @brief Sets the value of a cvar as a string.
     *
     * @param cvar_name Name of the cvar whose value to set.
     * @param value Value to set. The string is copied.
    */
    inline void CvarSetString(const char* const cvar_name, const char* const value)
    {
        cssdk::g_engine_funcs.cvar_set_string(cvar_name, value);
    }

    /**
     * @brief Outputs a message to the server console.
     *
     * @param type Type of message.
     * @param format Format string.
     * @param args Format arguments.
     *
     * @note If \c type is \c AlertType::Logged and this is a multiplayer game, logs the message to the log file.
     * @note Otherwise, if the developer cvar is not 0, outputs the message to the console.
    */
    template <typename... Args>
    void AlertMessage(const cssdk::AlertType type, const char* const format, Args&&... args)
    {
        cssdk::g_engine_funcs.alert_message(type, format, std::forward<Args>(args)...);
    }

    /**
     * @brief Obsolete. Will print a message to the server console using \c alert_message indicating if it's being used.
    */
    template <typename... Args>
    void EngineFilePrint(void* const file, const char* const format, Args&&... args)
    {
        cssdk::g_engine_funcs.engine_file_print(file, format, std::forward<Args>(args)...);
    }

    /**
     * @brief Allocates memory for \c EntityBase instances.
     * The memory will be zeroed out.
     *
     * @param entity Entity to allocate memory for.
     * @param size Number of bytes to allocate.
     *
     * @return Pointer to \c EntityBase memory, or null if it could not be allocated.
    */
    inline void* AllocEntPrivateData(cssdk::Edict* const entity, const cssdk::int32 size)
    {
        return cssdk::g_engine_funcs.alloc_ent_private_data(entity, size);
    }

    /**
     * @brief N/D
     *
     * @param entity Entity whose entity memory is to be retrieved.
     *
     * @return Pointer to entity \c EntityBase instance, or null if edict is null or there is no entity assigned to it.
    */
    inline void* EntPrivateData(cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.ent_private_data(entity);
    }

    /**
     * @brief Frees the \c EntityBase memory assigned to entity.
     *
     * @param entity Entity whose memory should be freed.
    */
    inline void FreeEntPrivateData(cssdk::Edict* const entity)
    {
        cssdk::g_engine_funcs.free_ent_private_data(entity);
    }

    /**
     * @brief Gets the string assigned to the index.
     *
     * @param string String index whose string should be retrieved.
     *
     * @return String.
     *
     * @note If the index is invalid, returns a pointer to invalid memory.
    */
    inline const char* SzFromIndex(const unsigned int string)
    {
        return cssdk::g_engine_funcs.sz_from_index(string);
    }

    /**
     * @brief Allocates a string in the string pool.
     *
     * @param value String to allocate.
     *
     * @return Index assigned to the string.
     *
     * @note This will allocate memory from the hunk. If the hunk runs out of memory, will trigger sys error.
     * @note Each call allocates new memory. No actual pooling of strings occurs.
    */
    inline cssdk::Strind AllocString(const char* const value)
    {
        return cssdk::Strind(cssdk::g_engine_funcs.alloc_string(value));
    }

    /**
     * @brief Gets the \c EntityVars instance assigned to the given \c cssdk::Edict instance.
     *
     * @param entity Entity whose \c EntityVars is to be retrieved.
     *
     * @return \c EntityVars
     *
     * @note In effect, returns \c &entity->vars.
     * @note If \c entity is null, causes a crash.
    */
    inline cssdk::EntityVars* GetVarsOfEnt(cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.get_vars_of_ent(entity);
    }

    /**
     * @brief Gets an edict by offset.
     *
     * @param entity_offset Entity offset.
     *
     * @return cssdk::Edict at the given offset.
     *
     * @note This uses the byte offset of the edict to retrieve it.
     * @note DO NOT USE THIS. Use \c EntityOfEntIndex.
    */
    inline cssdk::Edict* EntityOfEntOffset(const cssdk::eoffset entity_offset)
    {
        return cssdk::g_engine_funcs.entity_of_ent_offset(entity_offset);
    }

    /**
     * @brief Gets the entity offset of the edict.
     *
     * @param entity cssdk::Edict whose offset is to be retrieved.
     *
     * @return Entity offset.
     *
     * @note DO NOT USE THIS. Use \c IndexOfEdict.
    */
    inline cssdk::eoffset EntOffsetOfEntity(const cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.ent_offset_of_entity(entity);
    }

    /**
     * @brief Gets the entity index of the edict.
     *
     * @param edict cssdk::Edict whose entity index is to be retrieved.
     *
     * @return If \c edict is null, returns 0. \n
     * If \c edict is not managed by the engine, triggers a sys error. \n
     * Otherwise, returns the entity index.
    */
    inline int IndexOfEdict(const cssdk::Edict* const edict)
    {
        return cssdk::g_engine_funcs.index_of_edict(edict);
    }

    /**
     * @brief Gets the edict at the given entity index.
     *
     * @param entity_index Entity index.
     *
     * @return If the given index is not valid, returns null. \n
     * Otherwise, if the entity at the given index is not in use, returns null. \n
     * Otherwise, if the entity at the given index is not a player and does not have a \c EntityBase instance, returns null. \n
     * Otherwise, returns the entity.
    */
    inline cssdk::Edict* EntityOfEntIndex(const int entity_index)
    {
        return cssdk::g_engine_funcs.entity_of_ent_index(entity_index);
    }

    /**
     * @brief Gets the edict of an \c EntityVars.
     *
     * @param vars EntityVars.
     *
     * @return cssdk::Edict.
     *
     * @note This will enumerate all entities, so this operation can be very expensive.
     * @note Use \c vars->containing_entity if possible.
    */
    inline cssdk::Edict* FindEntityByVars(cssdk::EntityVars* const vars)
    {
        return cssdk::g_engine_funcs.find_entity_by_vars(vars);
    }

    /**
     * @brief Gets the model pointer of the given entity.
     *
     * @param entity Entity.
     *
     * @return Pointer to the model, or null if the entity doesn't have one.
     * Triggers a sys error if the model wasn't loaded and couldn't be loaded.
    */
    inline void* GetModelPointer(cssdk::Edict* const entity)
    {
        return cssdk::g_engine_funcs.get_model_pointer(entity);
    }

    /**
     * @brief Registers a user message.
     *
     * @param name Name of the message. Maximum length is 12, excluding null terminator. Can be a temporary string.
     * @param size Size of the message, in bytes. Maximum size is 192 bytes. Specify -1 for variable length messages.
     *
     * @return Message ID, or 0 if the message could not be registered.
     *
     * @note The name of the message is used to find an exported function in the client library.
     * @note The format is MsgFunc_<name>.
    */
    inline int RegUserMessage(const char* const name, const int size)
    {
        return cssdk::g_engine_funcs.reg_user_message(name, size);
    }

    /**
     * @brief Does nothing.
    */
    inline void AnimationAutoMove(const cssdk::Edict* const entity, const float time)
    {
        cssdk::g_engine_funcs.animation_auto_move(entity, time);
    }

    /**
     * @brief Gets the bone position and angles for the given entity and bone.
     *
     * @param entity Entity whose model should be queried.
     * @param bone Bone index.
     * @param origin Origin of the bone.
     * @param angles Angles of the bone. Is not set by the engine.
     *
     * @note If the given entity is invalid, or does not have a studio model,
     * or the bone index is invalid, will cause invalid accesses to occur.
    */
    inline void GetBonePosition(const cssdk::Edict* const entity, const int bone, cssdk::Vector& origin, cssdk::Vector& angles)
    {
        cssdk::g_engine_funcs.get_bone_position(entity, bone, origin, angles);
    }

    /**
     * @brief Gets the index of an exported function.
     *
     * @param name Name of the function.
     *
     * @return Index of the function, or 0 if the function couldn't be found.
    */
    inline cssdk::uint32 FunctionFromName(const char* const name)
    {
        return cssdk::g_engine_funcs.function_from_name(name);
    }

    /**
     * @brief Gets the name of an exported function.
     *
     * @param function Function index.
     *
     * @return Function name, or null if no function exists at that index.
    */
    inline const char* NameForFunction(const cssdk::uint32 function)
    {
        return cssdk::g_engine_funcs.name_for_function(function);
    }

    /**
     * @brief Sends a message to the client console.
     *
     * @param entity Client to send the message to.
     * @param type Where to print the message.
     * @param message Message to send.
     *
     * @note \c PrintType::Chat outputs to the console, just as \c PrintType::Console.
    */
    inline void ClientPrint(cssdk::Edict* const entity, const cssdk::PrintType type, const char* const message)
    {
        cssdk::g_engine_funcs.client_print(entity, type, message);
    }

    /**
     * @brief Sends a message to the server console.
     *
     * @param message Message to send.
     *
     * @note The message is output regardless of the value of the developer cvar.
    */
    inline void ServerPrint(const char* const message)
    {
        cssdk::g_engine_funcs.server_print(message);
    }

    /**
     * @brief N/D
     *
     * @return String containing all of the command arguments, not including the command name.
    */
    inline const char* CmdArgs()
    {
        return cssdk::g_engine_funcs.cmd_args();
    }

    /**
     * @brief Gets the command argument at the given index.
     *
     * @param argc Argument index.
     *
     * @return Command argument.
     *
     * @note Argument 0 is the command name.
    */
    inline const char* CmdArgv(const int argc)
    {
        return cssdk::g_engine_funcs.cmd_argv(argc);
    }

    /**
     * @brief N/D
     *
     * @return The number of command arguments. This includes the command name.
    */
    inline int CmdArgc()
    {
        return cssdk::g_engine_funcs.cmd_argc();
    }

    /**
     * @brief Gets the attachment origin and angles.
     *
     * @param entity Entity whose model will be queried for the attachment data.
     * @param attachment Attachment index.
     * @param origin Attachment origin.
     * @param angles Attachment angles.
     *
     * @note If the entity is null, or does not have a studio model, illegal access will occur.
    */
    inline void GetAttachment(const cssdk::Edict* const entity, const int attachment, cssdk::Vector& origin, cssdk::Vector& angles)
    {
        cssdk::g_engine_funcs.get_attachment(entity, attachment, origin, angles);
    }

    /**
     * @brief Initializes the CRC instance.
    */
    inline void Crc32Init(cssdk::crc32* const pul_crc)
    {
        cssdk::g_engine_funcs.crc32_init(pul_crc);
    }

    /**
     * @brief Processes a buffer and updates the CRC.
     *
     * @param pul_crc CRC instance.
     * @param buffer Buffer to process.
     * @param len Number of bytes in the buffer to process.
    */
    inline void Crc32ProcessBuffer(cssdk::crc32* const pul_crc, void* const buffer, const int len)
    {
        cssdk::g_engine_funcs.crc32_process_buffer(pul_crc, buffer, len);
    }

    /**
     * @brief Processes a single byte.
     *
     * @param pul_crc CRC instance.
     * @param ch Byte.
    */
    inline void Crc32ProcessByte(cssdk::crc32* const pul_crc, const unsigned char ch)
    {
        cssdk::g_engine_funcs.crc32_process_byte(pul_crc, ch);
    }

    /**
     * @brief Finalizes the CRC instance.
     *
     * @param pul_crc CRC instance.
     *
     * @return CRC value.
    */
    inline cssdk::crc32 Crc32Final(const cssdk::crc32 pul_crc)
    {
        return cssdk::g_engine_funcs.crc32_final(pul_crc);
    }

    /**
     * @brief Generates a random long number in the range \c low - \c high.
     *
     * @param low Lower bound.
     * @param high Higher bound.
     *
     * @return Random number, or \c low if \c high is smaller than or equal to \c low.
    */
    inline cssdk::int32 RandomLong(const cssdk::int32 low, const cssdk::int32 high)
    {
        return cssdk::g_engine_funcs.random_long(low, high);
    }

    /**
     * @brief Generates a random long number in the range \c low - \c high.
     *
     * @param low Lower bound.
     * @param high Higher bound.
     *
     * @return Random number, or \c low if \c high is smaller than or equal to \c low.
    */
    inline float RandomFloat(const float low, const float high)
    {
        return cssdk::g_engine_funcs.random_float(low, high);
    }

    /**
     * @brief Sets the view of a client to the given entity.
     *
     * @param client Client whose view is to be set.
     * @param view_entity Entity to use as the client's viewpoint.
     *
     * @note If \c client is not a client, triggers a host error.
     * @note Set the view to the client itself to reset it.
    */
    inline void SetView(const cssdk::Edict* const client, const cssdk::Edict* const view_entity)
    {
        cssdk::g_engine_funcs.set_view(client, view_entity);
    }

    /**
     * @brief N/D
     *
     * @return The time since the first call to Time.
     *
     * @note Used for delta operations that operate in real world time,
     * as opposed to game world time (which will advance frame by frame, and can be paused).
    */
    inline float Time()
    {
        return cssdk::g_engine_funcs.time();
    }

    /**
     * @brief Sets the angles of the given player's crosshairs to the given settings.
     *
     * @param client Client whose crosshair settings should be set.
     * @param pitch Pitch.
     * @param yaw Yaw.
     *
     * @note Set both to 0 to disable.
    */
    inline void CrosshairAngle(const cssdk::Edict* const client, const float pitch, const float yaw)
    {
        cssdk::g_engine_funcs.crosshair_angle(client, pitch, yaw);
    }

    /**
     * @brief Loads a file from disk.
     *
     * @param file_name Name of the file. Path starts in the game directory.
     * @param length If not null, is set to the size of the file, in bytes.
     *
     * @return Pointer to the file buffer, or null if the file could not be loaded.
    */
    inline cssdk::byte* LoadFileForMe(const char* const file_name, int* const length)
    {
        return cssdk::g_engine_funcs.load_file_for_me(file_name, length);
    }

    /**
     * @brief Frees the buffer provided by \c load_file_for_me.
     *
     * @param buffer Pointer to buffer.
    */
    inline void FreeFile(void* const buffer)
    {
        cssdk::g_engine_funcs.free_file(buffer);
    }

    /**
     * @brief Signals the engine that a section has ended.
     *
     * @param section_name Possible values: \n
     * _oem_end_training \n
     * _oem_end_logo \n
     * _oem_end_demo
     *
     * @note A disconnect command is sent by this call.
    */
    inline void EndSection(const char* const section_name)
    {
        cssdk::g_engine_funcs.end_section(section_name);
    }

    /**
     * @brief Compares file times.
     *
     * @param file_name1 First file to compare.
     * @param file_name2 Second file to compare.
     * @param compare If both files are equal, 0. \n
     * If the first file is older, -1. \n
     * If the second file is older, 1.
     *
     * @return True if both file names are non-null, false otherwise.
    */
    inline cssdk::qboolean CompareFileTime(char* const file_name1, char* const file_name2, int* const compare)
    {
        return cssdk::g_engine_funcs.compare_file_time(file_name1, file_name2, compare);
    }

    /**
     * @brief Gets the game directory name.
     *
     * @param game_dir Buffer to store the game directory name in. Must be at least MAX_PATH bytes large.
    */
    inline void GetGameDir(char* const game_dir)
    {
        cssdk::g_engine_funcs.get_game_dir(game_dir);
    }

    /**
     * @brief Registers a CVar.
     * Identical to \c cvar_register, except it doesn't set the \c FCVAR_EXT_DLL flag.
    */
    inline void CvarRegisterVariable(cssdk::CVar* const variable)
    {
        cssdk::g_engine_funcs.cvar_register_variable(variable);
    }

    /**
     * @brief Fades the given client's volume.
     *
     * @param client Client.
     * @param fade_percent Percentage volume to fade out to.
     * @param fade_out_seconds How long it takes to fade out, in seconds.
     * @param hold_time How long to stay faded out, in seconds.
     * @param fade_in_seconds How long it takes to fade in, in seconds.
    */
    inline void FadeClientVolume(const cssdk::Edict* const client, const int fade_percent, const int fade_out_seconds,
                                 const int hold_time, const int fade_in_seconds)
    {
        cssdk::g_engine_funcs.fade_client_volume(client, fade_percent, fade_out_seconds, hold_time, fade_in_seconds);
    }

    /**
     * @brief Sets the client's maximum speed value.
     *
     * @param client Client to set.
     * @param new_max_speed Maximum speed value.
     *
     * @note Effectively sets \c cssdk::Edict->vars.max_speed.
    */
    inline void SetClientMaxSpeed(cssdk::Edict* const client, const float new_max_speed)
    {
        cssdk::g_engine_funcs.set_client_max_speed(client, new_max_speed);
    }

    /**
     * @brief Creates a fake client (bot).
     *
     * @param name Name of the client to show.
     *
     * @return The fake client, or null if it can't be created.
    */
    inline cssdk::Edict* CreateFakeClient(const char* const name)
    {
        return cssdk::g_engine_funcs.create_fake_client(name);
    }

    /**
     * @brief Runs player movement for a fake client.
     *
     * @param fake_client Client to move. Must be a fake client.
     * @param view_angles Client view angles.
     * @param forward_move Velocity X value.
     * @param side_move Velocity Y value.
     * @param up_move Velocity Z value.
     * @param buttons Buttons that are currently pressed in. Equivalent to player \c vars.button..
     * @param impulse Impulse commands to execute. Equivalent to player \c vars.impulse..
     * @param msec Time between now and previous \c run_player_move call.
    */
    inline void RunPlayerMove(cssdk::Edict* const fake_client, const cssdk::Vector& view_angles, const float forward_move,
                              const float side_move, const float up_move, const unsigned short buttons,
                              const cssdk::byte impulse, const cssdk::byte msec)
    {
        cssdk::g_engine_funcs.run_player_move(fake_client, view_angles, forward_move, side_move,
                                              up_move, buttons, impulse, msec);
    }

    /**
     * @brief Computes the total number of entities currently in existence.
     *
     * @return Number of entities.
     *
     * @note This will calculate the number of entities in real-time. May be expensive if called many times.
    */
    inline int NumberOfEntities()
    {
        return cssdk::g_engine_funcs.number_of_entities();
    }

    /**
     * @brief Gets the given client's info key buffer.
     *
     * @param client Client.
     *
     * @return Info key buffer.
     *
     * @note Passing in the world gets the server info.
     * @note Passing in null gets the local info. Local info is not used by the engine itself, only the game.
     * @note This function checks the max players value incorrectly and may crash if the wrong edict gets passed in.
    */
    inline char* GetInfoKeyBuffer(cssdk::Edict* const client)
    {
        return cssdk::g_engine_funcs.get_info_key_buffer(client);
    }

    /**
     * @brief Gets the value of the given key from the given buffer.
     *
     * @param info_buffer Buffer to query.
     * @param key Key whose value to retrieve.
     *
     * @return The requested value, or an empty string.
    */
    inline char* InfoKeyValue(char* const info_buffer, const char* const key)
    {
        return cssdk::g_engine_funcs.info_key_value(info_buffer, key);
    }

    /**
     * @brief Sets the value of the given key in the given buffer.
     *
     * @param info_buffer Buffer to modify.
     * @param key Key whose value to set.
     * @param value Value to set.
     *
     * @note If the given buffer is not the local info or server info buffer, triggers a sys error.
    */
    inline void SetKeyValue(char* const info_buffer, const char* const key, const char* const value)
    {
        cssdk::g_engine_funcs.set_key_value(info_buffer, key, value);
    }

    /**
     * @brief Sets the value of the given key in the given buffer.
     * This only works for client buffers.
     *
     * @param client_index Entity index of the client.
     * @param info_buffer Buffer to modify.
     * @param key Key whose value to set.
     * @param value Value to set.
    */
    inline void SetClientKeyValue(const int client_index, char* const info_buffer,
                                  const char* const key, const char* const value)
    {
        cssdk::g_engine_funcs.set_client_key_value(client_index, info_buffer, key, value);
    }

    /**
     * @brief Checks if the given filename is a valid map.
     *
     * @param file_name Name of the map to check.
     *
     * @return True if the map is valid, false otherwise.
    */
    inline cssdk::qboolean IsMapValid(const char* const file_name)
    {
        return cssdk::g_engine_funcs.is_map_valid(file_name);
    }

    /**
     * @brief Projects a inline decal in the world.
     *
     * @param origin Origin in the world to project the decal at.
     * @param decal_index Index of the decal to project.
     * @param entity_index Index of the entity to project the decal onto.
     * @param model_index Index of the model to project the decal onto.
    */
    inline void StaticDecal(const cssdk::Vector& origin, const int decal_index, const int entity_index, const int model_index)
    {
        cssdk::g_engine_funcs.static_decal(origin, decal_index, entity_index, model_index);
    }

    /**
     * @brief Precaches a file.
     *
     * @param path Name of the file to precache. Starts in the game directory.
     * This string must live for at least as long as the map itself.
     *
     * @return Index of the file.
     *
     * @note If \c path is null, is empty or contains an invalid value in the first character, triggers a host error.
     * @note If the maximum number of generic precacheable resources has been reached, triggers a host error.
     * @note If this is called after \c server_activate, triggers a host error.
    */
    inline int PrecacheGeneric(const char* const path)
    {
        return cssdk::g_engine_funcs.precache_generic(path);
    }

    /**
     * @brief Returns the server assigned userid for this player.
     *
     * @param client Client.
     *
     * @return User ID or -1 if the edict couldn't be found in the list of clients.
    */
    inline int GetPlayerUserId(cssdk::Edict* const client)
    {
        return cssdk::g_engine_funcs.get_player_user_id(client);
    }

    /**
     * @brief Builds a sound message to send to a client.
     *
     * @param entity Entity that is playing the sound.
     * @param channel Channel to play the sound on.
     * @param sample Sound to play.
     * @param volume Volume of the sound. Must be in the range 0 - 1.
     * @param attenuation Attenuation.
     * @param flags Sound flags.
     * @param pitch Pitch. Must be in the range 0 - 255.
     * @param msg_type Message type.
     * @param msg_id Message ID.
     * @param origin Origin in the world to use for PAS and PVS messages.
     * @param client Client to send the message to for message types that target one client.
    */
    inline void BuildSoundMsg(cssdk::Edict* const entity, const int channel, const char* const sample, const float volume,
                              const float attenuation, const int flags, const int pitch, const cssdk::MessageType msg_type,
                              const int msg_id, const cssdk::Vector& origin, cssdk::Edict* const client)
    {
        cssdk::g_engine_funcs.build_sound_msg(entity, channel, sample, volume, attenuation,
                                              flags, pitch, msg_type, msg_id, origin, client);
    }

    /**
     * @brief N/D
     *
     * @return Whether this is a dedicated server.
    */
    inline cssdk::qboolean IsDedicatedServer()
    {
        return cssdk::g_engine_funcs.is_dedicated_server();
    }

    /**
     * @brief N/D
     *
     * @param cvar_name Name of the CVar to retrieve.
     *
     * @return CVar pointer, or null if the cvar doesn't exist.
    */
    inline cssdk::CVar* CvarGetPointer(const char* const cvar_name)
    {
        return cssdk::g_engine_funcs.cvar_get_pointer(cvar_name);
    }

    /**
     * @brief Returns the server assigned WONid for this player.
     *
     * @param client Client.
     *
     * @return WON ID, or -1 if the edict couldn't be found in the list of clients.
     *
     * @note Always returns -1 when using the Steam version.
    */
    inline unsigned int GetPlayerWonId(cssdk::Edict* const client)
    {
        return cssdk::g_engine_funcs.get_player_won_id(client);
    }

    /**
     * @brief Removes a key from the info buffer.
     *
     * @param info_buffer Buffer to modify.
     * @param key Key to remove.
    */
    inline void InfoRemoveKey(char* const info_buffer, const char* const key)
    {
        cssdk::g_engine_funcs.info_remove_key(info_buffer, key);
    }

    /**
     * @brief Gets the given physics key-value from the given client's buffer.
     *
     * @param client Client whose buffer will be queried.
     * @param key Key whose value will be retrieved.
     *
     * @return The value, or an empty string if the key does not exist.
    */
    inline const char* GetPhysicsKeyValue(const cssdk::Edict* const client, const char* const key)
    {
        return cssdk::g_engine_funcs.get_physics_key_value(client, key);
    }

    /**
     * @brief Sets the given physics key-value in the given client's buffer.
     *
     * @param client Client whose buffer will be modified.
     * @param key Key whose value will be set.
     * @param value Value to set.
    */
    inline void SetPhysicsKeyValue(const cssdk::Edict* const client, const char* const key, const char* const value)
    {
        cssdk::g_engine_funcs.set_physics_key_value(client, key, value);
    }

    /**
     * @brief Gets the physics info string for the given client.
     *
     * @param client Client whose buffer will be retrieved.
     *
     * @return Buffer, or an empty string if the client is invalid.
    */
    inline const char* GetPhysicsInfoString(const cssdk::Edict* const client)
    {
        return cssdk::g_engine_funcs.get_physics_info_string(client);
    }

    /**
     * @brief Precaches an event.
     *
     * @param type Should always be 1.
     * @param path Name of the event. Format should be events/<name>.sc, including the directory and extension.
     *
     * @return Event index. Used with \c playback_event.
    */
    inline unsigned short PrecacheEvent(const int type, const char* const path)
    {
        return cssdk::g_engine_funcs.precache_event(type, path);
    }

    /**
     * @brief N/D
     *
     * @param flags Event flags.
     * @param invoker Client that triggered the event.
     * @param event_index Event index.
     * @param delay Delay before the event should be run.
     * @param origin If not zero vector, this is the origin parameter sent to the clients.
     * @param angles If not zero vector, this is the angles parameter sent to the clients.
     * @param f_param1 Float parameter 1.
     * @param f_param2 Float parameter 2.
     * @param i_param1 Integer parameter 1.
     * @param i_param2 Integer parameter 2.
     * @param b_param1 Boolean parameter 1.
     * @param b_param2 Boolean parameter 2.
    */
    inline void PlaybackEvent(const int flags, const cssdk::Edict* const invoker, const unsigned short event_index,
                              const float delay, cssdk::Vector& origin, cssdk::Vector& angles, const float f_param1,
                              const float f_param2, const int i_param1, const int i_param2,
                              const cssdk::qboolean b_param1, const cssdk::qboolean b_param2)
    {
        cssdk::g_engine_funcs.playback_event(flags, invoker, event_index, delay, origin, angles,
                                             f_param1, f_param2, i_param1, i_param2, b_param1, b_param2);
    }

    /**
     * @brief Sets the Fat Potentially Visible Set buffer to contain data based on the given origin.
     *
     * @param origin Origin.
     *
     * @return PVS data.
    */
    inline unsigned char* SetFatPvs(cssdk::Vector& origin)
    {
        return cssdk::g_engine_funcs.set_fat_pvs(origin);
    }

    /**
     * @brief Sets the Fat Potentially Audible Set buffer to contain data based on the given origin.
     *
     * @param origin Origin.
     *
     * @return PAS data.
    */
    inline unsigned char* SetFatPas(cssdk::Vector& origin)
    {
        return cssdk::g_engine_funcs.set_fat_pas(origin);
    }

    /**
     * @brief Checks if the given entity is visible in the given visible set.
     *
     * @param entity Entity to check.
     * @param set Buffer detailing the current visible set.
     *
     * @return Whether the given entity is visible in the given visible set.
    */
    inline cssdk::qboolean CheckVisibility(cssdk::Edict* const entity, unsigned char* const set)
    {
        return cssdk::g_engine_funcs.check_visibility(entity, set);
    }

    /**
     * @brief Marks the given field in the given list as set.
     *
     * @param fields List of fields.
     * @param field_name Field name.
    */
    inline void DeltaSetField(void* const fields, const char* const field_name)
    {
        cssdk::g_engine_funcs.delta_set_field(fields, field_name);
    }

    /**
     * @brief Marks the given field in the given list as not set.
     *
     * @param fields List of fields.
     * @param field_name Field name.
    */
    inline void DeltaUnsetField(void* const fields, const char* const field_name)
    {
        cssdk::g_engine_funcs.delta_unset_field(fields, field_name);
    }

    /**
     * @brief Adds a delta encoder.
     *
     * @param name Name of the delta.lst entry to add the encoder for.
     * @param conditional_encode Encoder function.
    */
    inline void DeltaAddEncoder(const char* const name,
                                void (*conditional_encode)(void* fields, const unsigned char* from,
                                                           const unsigned char* to))
    {
        cssdk::g_engine_funcs.delta_add_encoder(name, conditional_encode);
    }

    /**
     * @brief Returns the client index of the client that is currently being handled by an engine callback.
     *
     * @return -1 if no client is currently being handled.
    */
    inline int GetCurrentPlayer()
    {
        return cssdk::g_engine_funcs.get_current_player();
    }

    /**
     * @brief N/D
     *
     * @param client Client.
     *
     * @return True if the given client has cl_lw (weapon prediction) enabled.
    */
    inline cssdk::qboolean CanSkipPlayer(const cssdk::Edict* const client)
    {
        return cssdk::g_engine_funcs.can_skip_player(client);
    }

    /**
     * @brief Finds the index of a delta field.
     *
     * @param fields List of fields.
     * @param field_name Name of the field to find.
     *
     * @return Index of the delta field, or -1 if the field couldn't be found.
    */
    inline int DeltaFindField(void* const fields, const char* const field_name)
    {
        return cssdk::g_engine_funcs.delta_find_field(fields, field_name);
    }

    /**
     * @brief Marks a delta field as set by index.
     *
     * @param fields List of fields.
     * @param field_number Index of the field.
     *
     * @note If the index is invalid, causes illegal access.
    */
    inline void DeltaSetFieldByIndex(void* const fields, const int field_number)
    {
        cssdk::g_engine_funcs.delta_set_field_by_index(fields, field_number);
    }

    /**
     * @brief Marks a delta field as not set by index.
     *
     * @param fields List of fields.
     * @param field_number Index of the field.
     *
     * @note If the index is invalid, causes illegal access.
    */
    inline void DeltaUnsetFieldByIndex(void* const fields, const int field_number)
    {
        cssdk::g_engine_funcs.delta_unset_field_by_index(fields, field_number);
    }

    /**
     * @brief Used to filter contents checks.
     *
     * @param mask Mask to check.
     * @param operation Operation to perform during masking.
    */
    inline void SetGroupMask(const int mask, const int operation)
    {
        cssdk::g_engine_funcs.set_group_mask(mask, operation);
    }

    /**
     * @brief Creates an instanced baseline. Used to define a baseline for a particular entity type.
     *
     * @param classname Name of the entity class.
     * @param baseline Baseline to set.
    */
    inline int CreateInstancedBaseline(const cssdk::Strind& classname, cssdk::EntityState* baseline)
    {
        return cssdk::g_engine_funcs.create_instanced_baseline(classname, baseline);
    }

    /**
     * @brief Directly sets a CVar value.
     *
     * @param cvar CVar.
     * @param value Value to set.
    */
    inline void CvarDirectSet(cssdk::CVar* const cvar, const char* const value)
    {
        cssdk::g_engine_funcs.cvar_direct_set(cvar, value);
    }

    /**
     * @brief Forces the client and server to be running with the same version of the specified file (e.g., a player model).
     *
     * @param type Force type.
     * @param min_size If not null, the minimum bounds that a model can be.
     * @param max_size If not null, the maximum bounds that a model can be.
     * @param file_name File to verify. This string must live for at least as long as the map itself.
     *
     * @note Calling this has no effect in single player.
    */
    inline void ForceUnmodified(const cssdk::ForceType type, cssdk::Vector& min_size, cssdk::Vector& max_size,
                                const char* const file_name)
    {
        cssdk::g_engine_funcs.force_unmodified(type, min_size, max_size, file_name);
    }

    /**
     * @brief Get player statistics.
     *
     * @param client Client to query.
     * @param ping Current ping.
     * @param packet_loss Current packet loss, measured in percentage.
    */
    inline void GetPlayerStats(const cssdk::Edict* const client, int* const ping, int* const packet_loss)
    {
        cssdk::g_engine_funcs.get_player_stats(client, ping, packet_loss);
    }

    /**
     * @brief Adds a server command.
     *
     * @param cmd_name Name of the command to add. This string must live for the rest of the server's lifetime.
     * @param callback Function to invoke when the command is received.
    */
    inline void AddServerCommand(const char* const cmd_name, void (*callback)())
    {
        cssdk::g_engine_funcs.add_server_command(cmd_name, callback);
    }

    /**
     * @brief Gets whether the given receiver can hear the given sender.
     *
     * @param receiver Receiver. This is an entity index.
     * @param sender Sender. This is an entity index.
     *
     * @return Whether the given receiver can hear the given sender.
    */
    inline cssdk::qboolean VoiceGetClientListening(const int receiver, const int sender)
    {
        return cssdk::g_engine_funcs.voice_get_client_listening(receiver, sender);
    }

    /**
     * @brief Sets whether the given receiver can hear the given sender.
     *
     * @param receiver Receiver. This is an entity index.
     * @param sender Sender. This is an entity index.
     * @param listen Whether the given receiver can hear the given sender.
     *
     * @return Whether the setting was changed.
    */
    inline cssdk::qboolean VoiceSetClientListening(const int receiver, const int sender, const cssdk::qboolean listen)
    {
        return cssdk::g_engine_funcs.voice_set_client_listening(receiver, sender, listen);
    }

    /**
     * @brief Gets the player's auth ID.
     *
     * @param client Client.
     *
     * @return The player's auth ID, or an empty string. This points to a temporary buffer, copy the results.
    */
    inline const char* GetPlayerAuthId(cssdk::Edict* const client)
    {
        return cssdk::g_engine_funcs.get_player_auth_id(client);
    }

    /**
     * @brief Gets the sequence that has the given entry name.
     *
     * @param file_name Ignored.
     * @param entry_name Entry name.
     *
     * @return Sequence, or null if no such sequence exists.
    */
    inline cssdk::SequenceEntry* SequenceGet(const char* const file_name, const char* const entry_name)
    {
        return cssdk::g_engine_funcs.sequence_get(file_name, entry_name);
    }

    /**
     * @brief Picks a sentence from the given group.
     *
     * @param group_name Group from which to select a sentence.
     * @param pick_method Ignored.
     * @param picked If not null, this is set to the index of the sentence that was picked.
     *
     * @return Sentence that was picked, or null if there is no group by that name, or no sentences in the group.
    */
    inline cssdk::SentenceEntry* SequencePickSentence(const char* const group_name, const int pick_method, int* const picked)
    {
        return cssdk::g_engine_funcs.sequence_pick_sentence(group_name, pick_method, picked);
    }

    /**
     * @brief LH: Give access to file size via filesystem.
     *
     * @param file_name Name of the file whose size is to be queried.
     *
     * @return File size, or -1 if the file doesn't exist.
    */
    inline int GetFileSize(const char* const file_name)
    {
        return cssdk::g_engine_funcs.get_file_size(file_name);
    }

    /**
     * @brief Gets the average wave length in seconds.
     *
     * @param file_path Name of the sound.
     *
     * @return Length of the sound file, in seconds.
    */
    inline unsigned int GetApproxWavePlayLen(const char* const file_path)
    {
        return cssdk::g_engine_funcs.get_approx_wave_play_len(file_path);
    }

    /**
     * @brief MDC: Added for CZ career-mode.
     *
     * @return Whether this is a Condition Zero Career match.
    */
    inline cssdk::qboolean IsCareerMatch()
    {
        return cssdk::g_engine_funcs.is_career_match();
    }

    /**
     * @brief N/D
     *
     * @param label Label.
     *
     * @return Number of characters of the localized string referenced by using label.
    */
    inline int GetLocalizedStringLength(const char* const label)
    {
        return cssdk::g_engine_funcs.get_localized_string_length(label);
    }

    /**
     * @brief Marks the message with the given ID as having been shown.
     *
     * @param message_id Message ID.
    */
    inline void RegisterTutorMessageShown(const int message_id)
    {
        cssdk::g_engine_funcs.register_tutor_message_shown(message_id);
    }

    /**
     * @brief Gets the number of times the message with the given ID has been shown.
     *
     * @param message_id Message ID.
     *
     * @return Number of times the message with the given ID has been shown.
    */
    inline int GetTimesTutorMessageShown(const int message_id)
    {
        return cssdk::g_engine_funcs.get_times_tutor_message_shown(message_id);
    }

    /**
     * @brief Processes the tutor message decay buffer.
     *
     * @param buffer Buffer.
     * @param buffer_length Size of the buffer, in bytes.
    */
    inline void ProcessTutorMessageDecayBuffer(int* const buffer, const int buffer_length)
    {
        cssdk::g_engine_funcs.process_tutor_message_decay_buffer(buffer, buffer_length);
    }

    /**
     * @brief Constructs the tutor message decay buffer.
     *
     * @param buffer Buffer.
     * @param buffer_length Size of the buffer, in bytes.
    */
    inline void ConstructTutorMessageDecayBuffer(int* const buffer, const int buffer_length)
    {
        cssdk::g_engine_funcs.construct_tutor_message_decay_buffer(buffer, buffer_length);
    }

    /**
     * @brief Resets tutor message decay data.
    */
    inline void ResetTutorMessageDecayData()
    {
        cssdk::g_engine_funcs.reset_tutor_message_decay_data();
    }

    /**
     * @brief Queries the given client for a cvar value.
     *
     * @param client Player to query.
     * @param cvar_name CVar to query.
     *
     * @note The response is sent to \c GameDllNewHooks::cvar_value.
    */
    inline void QueryClientCvarValue(const cssdk::Edict* const client, const char* const cvar_name)
    {
        cssdk::g_engine_funcs.query_client_cvar_value(client, cvar_name);
    }

    /**
     * @brief Queries the given client for a cvar value.
     *
     * @param client Player to query.
     * @param cvar_name CVar to query.
     * @param request_id Request ID to pass to \c cvar_value2
     *
     * @note The response is sent to \c GameDllNewHooks::cvar_value2.
    */
    inline void QueryClientCvarValue2(const cssdk::Edict* const client, const char* const cvar_name, const int request_id)
    {
        cssdk::g_engine_funcs.query_client_cvar_value2(client, cvar_name, request_id);
    }

    /**
     * @brief Checks if a command line parameter was provided.
     *
     * @param cmd_line_token Command key to look for.
     * @param next If the key was found, this is set to the value.
     *
     * @return Key index in the command line buffer, or 0 if it wasn't found.
    */
    inline int EngCheckParam(const char* const cmd_line_token, char** const next)
    {
        return cssdk::g_engine_funcs.eng_check_param(cmd_line_token, next);
    }
}
