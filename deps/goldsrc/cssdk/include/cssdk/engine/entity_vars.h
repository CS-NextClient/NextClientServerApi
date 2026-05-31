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
#include <cssdk/common/strind.h>
#include <cssdk/common/vector.h>

namespace cssdk
{
    struct Edict;

    /**
     * @brief Contains entity variables that the engine needs to access for graphics, networking and physics.
    */
    struct EntityVars
    {
        /**
         * @brief The class name of the entity.
        */
        Strind class_name{};

        /**
         * @brief Global entity name.
         * Used for entities that carry their state across level transitions in single player.
        */
        Strind global_name{};

        /**
         * @brief Absolute origin in the world.
         * Networked.
        */
        Vector origin{};

        /**
         * @brief Old entity origin.
         * Used in the engine to store the player's old origin when no clip is turned off.
        */
        Vector old_origin{};

        /**
         * @brief The entity's absolute velocity.
         * Networked.
        */
        Vector velocity{};

        /**
         * @brief Base velocity to apply when standing on conveyors or swimming in water with current contents set.
         * Networked.
        */
        Vector base_velocity{};

        /**
         * @brief Base velocity that was passed in to server physics so client can predict conveyors correctly.
         * Server zeroes it, so we need to store here, too.
         * Zeroed out prior to \c DllFunctions::pre_think being called, set to the player's basevelocity
         * after the player's think has been called, before \c DllFunctions::post_think is called.
        */
        Vector cl_base_velocity{};

        /**
         * @brief Movement direction and speed.
        */
        Vector move_direction{};

        /**
         * @brief Model angles.
         * Networked.
        */
        Vector angles{};

        /**
         * @brief Angle velocity (degrees per second).
        */
        Vector angle_velocity{};

        /**
         * @brief Auto-decaying view angle adjustment.
         * Decayed in \c PM_CheckParameters.
         * Networked.
        */
        Vector punch_angle{};

        /**
         * @brief Viewing angle (player only).
        */
        Vector viewing_angle{};

        /**
         * @brief Parametric end position.
         * Networked.
        */
        Vector end_pos{};

        /**
         * @brief Parametric start position.
         * Networked.
        */
        Vector start_pos{};

        /**
         * @brief Time at which the entity will have traversed the distance between start pos and end pos.
         * Networked.
        */
        float impact_time{};

        /**
         * @brief Time at which the entity has started its parametric movement.
         * Networked.
        */
        float start_time{};

        /**
         * @brief Player only. Sets the player's view angles on the client.
         * The server's angles are not modified automatically.
        */
        FixAngleMode fix_angle{};

        /**
         * @brief The ideal pitch for this entity. \c EngineFunctions::change_pitch
         * will adjust the entity's pitch to approach this value.
        */
        float ideal_pitch{};

        /**
         * @brief The pitch speed for this entity. \c EngineFunctions::change_pitch
         * will adjust the entity's pitch at this speed.
        */
        float pitch_speed{};

        /**
         * @brief The ideal yaw for this entity. \c EngineFunctions::change_yaw
         * will adjust the entity's yaw to approach this value.
        */
        float ideal_yaw{};

        /**
         * @brief The yaw speed for this entity. \c EngineFunctions::change_yaw
         * will adjust the entity's yaw at this speed.
        */
        float yaw_speed{};

        /**
         * @brief If this entity has a model, this is the index of that model. Otherwise, is 0.
         * Set by \c EngineFunctions::set_model.
         * Networked.
        */
        int model_index{};

        /**
         * @brief If this entity has a model, this is the name of that model. Otherwise, is 0.
        */
        Strind model{};

        /**
         * @brief The player's viewmodel (v_*.mdl).
         * Networked.
        */
        int view_model{};

        /**
         * @brief What other players see; the player's third person viewmodel (p_*.mdl).
         * Networked.
        */
        int weapon_model{};

        /**
         * @brief Bounding box max translated to world coord.
         * Set by the engine whenever the entity moves, set by game code to adjust the size.
        */
        Vector abs_min{};

        /**
         * @brief Bounding box max translated to world coord.
         * Set by the engine whenever the entity moves, set by game code to adjust the size.
        */
        Vector abs_max{};

        /**
         * @brief Local bounding box min.
        */
        Vector min_size{};

        /**
         * @brief Local bounding box max.
        */
        Vector max_size{};

        /**
         * @brief max_size - min_size.
        */
        Vector size{};

        /**
         * @brief Last think time for brush entities (\c MoveTypeEntity::Push).
        */
        float last_think{};

        /**
         * @brief Next think time. Should be \c GlobalVars::time + delay for all entities
         * except \c MoveTypeEntity::Push entities; use \c last_think + delay for those instead.
        */
        float next_think{};

        /**
         * @brief Move type.
         * Networked.
        */
        MoveTypeEntity move_type{};

        /**
         * @brief Solid type.
         * Networked.
        */
        SolidType solid{};

        /**
         * @brief Studio model skin index. Seems to affect the player's z velocity if the FL_ON_TARGET flag is set.
         * Networked.
        */
        int skin{};

        /**
         * @brief Sub-model selection for studio models.
         * Networked.
        */
        int body{};

        /**
         * @brief Effects flags.
         * Networked.
        */
        int effects{};

        /**
         * @brief % of "normal" gravity. Default 1.0.
         * Networked.
        */
        float gravity{};

        /**
         * @brief Inverse elasticity of \c MoveTypeEntity::Bounce.
         * Networked.
        */
        float friction{};

        /**
         * @brief The stored light level for this entity.
         * Use \c EngineFunctions::get_entity_illumination to retrieve this.
        */
        int light_level{};

        /**
         * @brief Animation sequence.
         * Networked.
        */
        int sequence{};

        /**
         * @brief Movement animation sequence for player (0 for none).
         * Networked for clients only.
        */
        int gait_sequence{};

        /**
         * @brief % playback position in animation sequences (0..255).
         * Networked.
        */
        float frame{};

        /**
         * @brief World time when frame was set.
         * Networked.
        */
        float anim_time{};

        /**
         * @brief Animation playback rate (-8x to 8x).
         * Networked.
        */
        float frame_rate{};

        /**
         * @brief Bone controller setting (0..255).
         * Networked.
        */
        byte controller[4]{};

        /**
         * @brief Blending amount between sub-sequences (0..255).
         * Networked.
        */
        byte blending[2]{};

        /**
         * @brief Sprite rendering scale (0..255).
         * Networked.
        */
        float scale{};

        /**
         * @brief Render mode.
         * Networked.
        */
        Rendering render_mode{};

        /**
         * @brief Render amount.
         * Networked.
        */
        float render_amount{};

        /**
         * @brief Render color. Each component is in the range [0, 255].
         * Networked.
        */
        Vector render_color{};

        /**
         * @brief Render FX.
         * Networked.
        */
        RenderingFx render_fx{};

        /**
         * @brief Health.
         * Networked.
        */
        float health{};

        /**
         * @brief Frags. Player score.
        */
        float frags{};

        /**
         * @brief Bit mask for available weapons.
         * Networked.
        */
        int weapons{};

        /**
         * @brief Whether this entity can take damage, and whether the player's auto aim can snap to this entity.
        */
        float take_damage{};

        /**
         * @brief Current entity death state.
         * Networked.
        */
        DeathState dead_flag{};

        /**
         * @brief Eye position.
         * Networked.
        */
        Vector view_ofs{};

        /**
         * @brief Buttons that the player currently has pressed in.
         * Stores the use type for delayed triggers.
        */
        int button{};

        /**
         * @brief Current player impulse command.
        */
        int impulse{};

        /**
         * @brief Entity pointer when linked into a linked list.
         * Used by \c EngineFunctions::entities_in_pvs to return a list of entities.
        */
        Edict* chain{};

        /**
         * @brief Used in \c MonsterBase::take_damage and
         * \c PlayerBase::update_client_data to track the last damage inflictor.
        */
        Edict* damage_inflictor{};

        /**
         * @brief Used as a destination for \c EngineFunctions::move_to_origin when the entity is flying or swimming.
        */
        Edict* enemy{};

        /**
         * @brief Entity pointer when \c MoveTypeEntity::Follow.
        */
        Edict* aim_entity{};

        /**
         * @brief The entity that owns this entity, or null if it has no owner.
        */
        Edict* owner{};

        /**
         * @brief The entity that this entity is currently standing on, or null if it isn't standing on anything.
        */
        Edict* ground_entity{};

        /**
         * @brief Spawn flags. These are specific to each entity.
        */
        int spawn_flags{};

        /**
         * @brief Flags.
        */
        int flags{};

        /**
         * @brief Low byte - top color, high byte - bottom color.
         * Networked.
        */
        int color_map{};

        /**
         * @brief The team that this entity belongs to. 0 For no team.
         * The engine will check this to see if auto aim should snap to this entity.
         * Entities on the same team are never targeted by auto aim.
        */
        int team{};

        /**
         * @brief Maximum health that this entity can have.
         * Entities cannot have a health higher than this when given using GiveHealth.
         * Also used by some entities as a counter.
         * The engine does not access this.
        */
        float max_health{};

        /**
         * @brief Used in physics code as \c PlayerMove::water_jump_time, is save/restored.
         * Copied to \c ClientData::water_jump_time.
        */
        float teleport_time{};

        /**
         * @brief Never used, is save/restored.
        */
        float armor_type{};

        /**
         * @brief The amount of armor that this player has.
         * Also used by some entities for other purposes.
        */
        float armor_value{};

        /**
         * @brief The current water level.
         * Networked.
        */
        int water_level{};

        /**
         * @brief The type of water the player is currently in.
         * Only valid if the player is in water, is CONTENTS_EMPTY otherwise.
        */
        int water_type{};

        /**
         * @brief Target name of the entity to trigger when this entity fires its targets.
        */
        Strind target{};

        /**
         * @brief Target name of this entity.
        */
        Strind target_name{};

        /**
         * @brief Name of this player. Set by players using the "name" command.
         * Also used by other entities for various purposes.
        */
        Strind net_name{};

        /**
         * @brief Generic string member used by various entities. game_text stores its message here.
        */
        Strind message{};

        /**
         * @brief Tracks the amount of damage that the player took since the
         * last time \c PlayerBase::UpdateClientData was called, or since they spawned.
         * Also used by other entities for various purposes.
        */
        float damage_take{};

        /**
         * @brief Used by entities for various purposes.
        */
        float damage_save{};

        /**
         * @brief Used by \c MoveTypeEntity::PushStep and \c MoveTypeEntity::Step while the entity is swimming.
         * Damage taken while submerged. Engine handling is obsolete for players.
         * The engine code has been superseded by game code player physics.
        */
        float damage{};

        /**
         * @brief Used by \c MoveTypeEntity::PushStep and \c MoveTypeEntity::Step while the entity is swimming.
         * Next time lava/slime damage should be taken. Engine handling is obsolete for players.
         * The engine code has been superseded by game code player physics.
        */
        float damage_time{};

        /**
         * @brief Generic string 1.
        */
        Strind noise{};

        /**
         * @brief Generic string 2.
        */
        Strind noise1{};

        /**
         * @brief Generic string 3.
        */
        Strind noise2{};

        /**
         * @brief Generic string 4.
        */
        Strind noise3{};

        /**
         * @brief The entity's movement speed, in units/second.
        */
        float speed{};

        /**
         * @brief Used by \c MoveTypeEntity::PushStep and \c MoveTypeEntity::Step while the entity is swimming.
         * When the entity runs out of air. Engine handling is obsolete for players.
         * The engine code has been superseded by game code player physics.
        */
        float air_finished{};

        /**
         * @brief Used by \c MoveTypeEntity::PushStep and \c MoveTypeEntity::Step while the entity is swimming.
         * Next time drown damage should be taken. Engine handling is obsolete for players.
         * The engine code has been superseded by game code player physics.
        */
        float pain_finished{};

        /**
         * @brief Used by \c MoveTypeEntity::PushStep and \c MoveTypeEntity::Step while the entity is swimming.
         * When the player's protection against lava/slime has run out. Engine handling is obsolete for players.
         * The engine code has been superseded by game code player physics.
        */
        float rad_suit_finished{};

        /**
         * @brief The \c Edict instance that this \c EntityVars instance belongs to.
         * Should be \c reinterpret_cast<Edict*>(reinterpret_cast<byte*>(&class_name) - \c offsetof(Edict, vars)).
        */
        Edict* containing_entity{};

        /**
         * @brief The player's class. Mod specific.
         * If this is a \c SolidType::Bsp, this will determine whether damage decals will be applied to the bsp model.
         * A setting of 1 enables damage decals.
         * Networked.
        */
        int player_class{};

        /**
         * @brief Maximum movement speed.
         * Networked.
        */
        float max_speed{};

        /**
         * @brief This player's field of view.
         * Networked in \c ClientData.
        */
        float field_of_view{};

        /**
         * @brief The player's current weapon animation.
         * Networked in \c ClientData.
        */
        int weapon_anim{};

        /**
         * @brief Never used on the server side. This variable is completely unused.
        */
        int push_msec{};

        /**
         * @brief Whether the player is currently ducking. This state is synchronized with \c PlayerMove.
         * Networked in \c ClientData.
        */
        qboolean in_duck{};

        /**
         * @brief Time until the next step sound should be played for this player.
         * This state is synchronized with \c PlayerMove.
         * Networked in \c ClientData.
        */
        int time_step_sound{};

        /**
         * @brief Time until the next swim sound should be played for this player.
         * This state is synchronized with \c PlayerMove.
         * Networked in \c ClientData.
        */
        int swim_time{};

        /**
         * @brief How much longer until the player is fully ducked. This state is synchronized with \c PlayerMove.
         * Networked in \c ClientData.
        */
        int duck_time{};

        /**
         * @brief Whether the last step sound was a left or right step sound.
         * This state is synchronized with \c PlayerMove.
         * Networked in \c ClientData.
        */
        int step_left{};

        /**
         * @brief The player's current fall velocity. This state is synchronized with \c PlayerMove.
         * Networked in \c ClientData.
        */
        float fall_velocity{};

        /**
         * @brief Special variable used to tell the engine to skip the shield hit box for CS shield weapons.
         * 0: don't skip.
         * 1: skip.
        */
        int game_state{};

        /**
         * @brief Player button states for the previous frame.
         * Networked.
        */
        int old_buttons{};

        /**
         * @brief Trace line group.
        */
        int group_info{};

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
        Edict* e_user1{};

        /**
         * @brief N/D
        */
        Edict* e_user2{};

        /**
         * @brief N/D
        */
        Edict* e_user3{};

        /**
         * @brief N/D
        */
        Edict* e_user4{};
    };
}
