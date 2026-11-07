#include <easylogging++.h>

#include <amxx/api.h>

#include <core/type_conversion.h>

#include "AmxContextGuard.h"
#include "api_access.h"

namespace
{
    // Anything with an edict can wear a material, so the only question about the entity is
    // whether it is there.
    cssdk::Edict* EntityOf(cell entity_index)
    {
        if (entity_index <= 0 || !cssdk::IsValidEntityIndex(entity_index))
        {
            LOG(ERROR) << "invalid entity index " << entity_index;
            return nullptr;
        }

        cssdk::Edict* entity = core::type_conversion::EdictByIndex(entity_index);

        if (entity == nullptr)
        {
            LOG(ERROR) << "no entity with index " << entity_index;
        }

        return entity;
    }
} // namespace

static cell AMX_NATIVE_CALL ncl_mat_bind(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_entity,
        arg_preset,
        arg_material
    };

    cssdk::Edict* entity = EntityOf(params[arg_entity]);

    if (entity == nullptr)
    {
        return FALSE;
    }

    std::string preset = amx::GetString(amx, params[arg_preset]);
    std::string material = amx::GetString(amx, params[arg_material]);

    if (preset.empty() || material.empty())
    {
        LOG(ERROR) << "a binding needs both a preset and a material name";
        return FALSE;
    }

    return GetMaterialNclEntitySync().Bind(entity, preset, material) ? TRUE : FALSE;
}

static cell AMX_NATIVE_CALL ncl_mat_unbind(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_entity,
        arg_preset,
        arg_material
    };

    cssdk::Edict* entity = EntityOf(params[arg_entity]);

    if (entity == nullptr)
    {
        return FALSE;
    }

    std::string preset = amx::GetString(amx, params[arg_preset]);
    std::string material = amx::GetString(amx, params[arg_material]);

    return GetMaterialNclEntitySync().Unbind(entity, preset, material) ? TRUE : FALSE;
}

static cell AMX_NATIVE_CALL ncl_mat_clear(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_entity
    };

    cssdk::Edict* entity = EntityOf(params[arg_entity]);

    if (entity == nullptr)
    {
        return FALSE;
    }

    GetMaterialNclEntitySync().Clear(entity);
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_mat_param(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_entity,
        arg_texture,
        arg_name,
        arg_value
    };

    cssdk::Edict* entity = EntityOf(params[arg_entity]);

    if (entity == nullptr)
    {
        return FALSE;
    }

    std::string texture = amx::GetString(amx, params[arg_texture]);
    std::string name = amx::GetString(amx, params[arg_name]);

    if (texture.empty() || name.empty())
    {
        LOG(ERROR) << "a scoped parameter needs both a texture and a parameter name";
        return FALSE;
    }

    return GetMaterialNclEntitySync().SetParam(entity, texture, name, amx::CellToFloat(params[arg_value])) ? TRUE : FALSE;
}

static cell AMX_NATIVE_CALL ncl_mat_param_all(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_entity,
        arg_name,
        arg_value
    };

    cssdk::Edict* entity = EntityOf(params[arg_entity]);

    if (entity == nullptr)
    {
        return FALSE;
    }

    std::string name = amx::GetString(amx, params[arg_name]);

    if (name.empty())
    {
        LOG(ERROR) << "empty parameter name";
        return FALSE;
    }

    return GetMaterialNclEntitySync().SetParam(entity, "", name, amx::CellToFloat(params[arg_value])) ? TRUE : FALSE;
}

static cell AMX_NATIVE_CALL ncl_mat_through_walls(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    cssdk::Edict* entity = EntityOf(params[1]);
    return entity != nullptr && GetMaterialNclEntitySync().SetThroughWalls(entity, params[2] != 0) ? TRUE : FALSE;
}

static AmxNativeInfo g_Natives[] = {
    {"ncl_mat_through_walls", ncl_mat_through_walls},
    {"ncl_mat_bind", ncl_mat_bind},
    {"ncl_mat_unbind", ncl_mat_unbind},
    {"ncl_mat_clear", ncl_mat_clear},
    {"ncl_mat_param", ncl_mat_param},
    {"ncl_mat_param_all", ncl_mat_param_all},
    {nullptr, nullptr}
};

void AddNatives_Material()
{
    amxx::AddNatives(g_Natives);
}
