#include <easylogging++.h>

#include <amxx/api.h>
#include <core/type_conversion.h>

#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_override_weapon_sound(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_weapon_id,
        arg_original,
        arg_replacement
    };

    int weapon_id = params[arg_weapon_id];

    cssdk::Edict* weapon_edict = core::type_conversion::EdictByIndex(weapon_id);
    if (!weapon_edict || weapon_edict->free)
    {
        LOG(ERROR) << "Invalid weapon entity " << weapon_id;
        return FALSE;
    }

    std::string original = amx::GetString(amx, params[arg_original]);
    std::string replacement = amx::GetString(amx, params[arg_replacement]);

    GetWeaponNclEntitySync().BindWeapon(weapon_edict);
    GetWeaponNclEntitySync().AddSoundOverride(weapon_edict, original, replacement);

    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_override_weapon_sound_clear(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_weapon_id
    };

    int weapon_id = params[arg_weapon_id];

    cssdk::Edict* weapon_edict = core::type_conversion::EdictByIndex(weapon_id);
    if (!weapon_edict || weapon_edict->free)
    {
        LOG(ERROR) << "Invalid weapon entity " << weapon_id;
        return FALSE;
    }

    GetWeaponNclEntitySync().RemoveSoundOverride(weapon_edict);
    return TRUE;
}

static AmxNativeInfo g_Natives[] = {
    {"ncl_override_weapon_sound", ncl_override_weapon_sound},
    {"ncl_override_weapon_sound_clear", ncl_override_weapon_sound_clear},
    {nullptr, nullptr}
};

void AddNatives_WeaponSoundOverride()
{
    amxx::AddNatives(g_Natives);
}
