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

#include <cssdk/dll/player.h>
#include <cssdk/engine/eiface.h>
#include <cssdk/engine/global_vars.h>
#include <cssdk/engine/studio.h>
#include <cssdk/public/os_defs.h>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <utility>

namespace cssdk
{
    /**
     * @brief N/D
    */
    FORCEINLINE bool IsClient(const int index)
    {
        return index > 0 && index <= g_global_vars->max_clients;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE bool IsClient(const Edict* const entity)
    {
        return IsClient(g_engine_funcs.index_of_edict(entity));
    }

    /**
     * @brief N/D
    */
    FORCEINLINE bool IsValidEntityIndex(const int index)
    {
        return index >= 0 && index < g_global_vars->max_entities;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE bool IsValidEntity(const Edict* const entity)
    {
        return entity && !entity->free && entity->private_data && !(entity->vars.flags & FL_KILL_ME);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE bool IsValidEntity(const EntityBase* const entity)
    {
        return entity && entity->vars && IsValidEntity(entity->vars->containing_entity);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE bool IsValidEntity(const EntityVars* const entity)
    {
        return entity && IsValidEntity(entity->containing_entity);
    }

    /**
     * @brief N/D
    */
    template <typename T>
    FORCEINLINE T* EntityPrivateData(const Edict* const entity)
    {
        return static_cast<T*>(entity->private_data);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE const char* EntityKeyValue(Edict* const entity, const char* key)
    {
        auto* buffer = g_engine_funcs.get_info_key_buffer(entity);
        return g_engine_funcs.info_key_value(buffer, key);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE const char* EntityKeyValue(const int entity, const char* key)
    {
        return EntityKeyValue(g_engine_funcs.entity_of_ent_index(entity), key);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE void EntitySetKeyValue(Edict* const entity, const char* key, const char* value)
    {
        const auto index = g_engine_funcs.index_of_edict(entity);
        auto* buffer = g_engine_funcs.get_info_key_buffer(entity);
        g_engine_funcs.set_client_key_value(index, buffer, key, value);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE void EntitySetKeyValue(const int entity, const char* key, const char* value)
    {
        auto* edict = g_engine_funcs.entity_of_ent_index(entity);
        auto* buffer = g_engine_funcs.get_info_key_buffer(edict);
        g_engine_funcs.set_client_key_value(entity, buffer, key, value);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE bool IsPlayerAlive(const Edict* const player)
    {
        return player->vars.dead_flag == DeathState::Alive && player->vars.health > 0.0F;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE bool IsPlayerAlive(const PlayerBase* const player)
    {
        return player->vars->dead_flag == DeathState::Alive && player->vars->health > 0.0F;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE Vector GetGunPosition(const EntityVars& entity_vars)
    {
        return entity_vars.origin + entity_vars.view_ofs;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE EntityBase* FindEntityInSphere(Edict* start_entity, const Vector& center, float radius)
    {
        const auto* entity = g_engine_funcs.find_entity_in_sphere(start_entity, center, radius);
        return IsValidEntity(entity) ? EntityBase::Instance(entity) : nullptr;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE EntityBase* FindEntityByString(Edict* start_entity, const char* field, const char* value)
    {
        const auto* entity = g_engine_funcs.find_entity_by_string(start_entity, field, value);
        return IsValidEntity(entity) ? EntityBase::Instance(entity) : nullptr;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE EntityBase* FindEntityByClassname(Edict* start_entity, const char* class_name)
    {
        return FindEntityByString(start_entity, "classname", class_name);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE EntityBase* FindEntityByTargetName(Edict* start_entity, const char* target_name)
    {
        return FindEntityByString(start_entity, "targetname", target_name);
    }

    /**
     * @brief N/D
    */
    FORCEINLINE EntityBase* FindClientInPvs(Edict* entity)
    {
        entity = g_engine_funcs.find_client_in_pvs(entity);
        return IsValidEntity(entity) ? EntityBase::Instance(entity) : nullptr;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE EntityBase* FindEntityByVars(EntityVars* vars)
    {
        const auto* entity = g_engine_funcs.find_entity_by_vars(vars);
        return IsValidEntity(entity) ? EntityBase::Instance(entity) : nullptr;
    }

    /**
     * @brief N/D
    */
    FORCEINLINE short FixedSigned16(const float value, const float scale)
    {
        return static_cast<short>(std::clamp(static_cast<int>(value * scale), SHRT_MIN, SHRT_MAX));
    }

    /**
     * @brief N/D
    */
    FORCEINLINE unsigned short FixedUnsigned16(const float value, const float scale)
    {
        return static_cast<unsigned short>(std::clamp(static_cast<int>(value * scale), 0, USHRT_MAX));
    }

    /**
     * @brief N/D
    */
    bool IsBot(Edict* client);

    /**
     * @brief N/D
    */
    bool IsHltv(Edict* client);

    /**
     * @brief N/D
    */
    void HudMessage(EntityBase* entity, const HudTextParams& hud_params, const char* message, Edict* client = nullptr);

    /**
     * @brief N/D
    */
    void HudMessage(Edict* client, const HudTextParams& hud_params, const char* message);

    /**
     * @brief N/D
    */
    void HudMessage(int client, const HudTextParams& hud_params, const char* message);

    /**
     * @brief N/D
    */
    template <typename... Args>
    void SysError(const char* format, Args&&... args)
    {
        char error[4096];
        std::snprintf(error, sizeof error, format, std::forward<Args>(args)...);
        std::printf("FATAL ERROR (shutting down): %s\n", error);
        std::exit(-1);
    }
}
