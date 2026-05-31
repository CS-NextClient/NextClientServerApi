#include <easylogging++.h>

#include <amxx/api.h>

#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_precache_model(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = amx::GetString(amx, params[arg_filepath]);
    std::string ncl_filepath = amx::GetString(amx, params[arg_nclFilepath]);

    int model_index = GetPrivatePrecache().PrecacheModel(filepath, ncl_filepath);
    if (model_index == 0)
    {
        LOG(ERROR) << "Can't find file '" << ncl_filepath << "' (is a replacement for '" << filepath << "')";
        return FALSE;
    }

    return model_index;
}

static cell AMX_NATIVE_CALL ncl_precache_sound(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = amx::GetString(amx, params[arg_filepath]);
    std::string ncl_filepath = amx::GetString(amx, params[arg_nclFilepath]);

    int sound_index = GetPrivatePrecache().PrecacheSound(filepath, ncl_filepath);
    if (sound_index == 0)
    {
        LOG(ERROR) << "Can't find file '" << ncl_filepath << "' (is a replacement for '" << filepath << "')";
        return FALSE;
    }

    return sound_index;
}

static cell AMX_NATIVE_CALL ncl_upload_file(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = amx::GetString(amx, params[arg_filepath]);
    std::string ncl_filepath = amx::GetString(amx, params[arg_nclFilepath]);

    int result = GetPrivatePrecache().UploadFile(filepath, ncl_filepath);
    if (result == 0)
    {
        LOG(ERROR) << "Can't find file '" << ncl_filepath << "' (is a replacement for '" << filepath << "')";
        return FALSE;
    }

    return TRUE;
}

static AmxNativeInfo g_Natives[] = {
    {"ncl_precache_model", ncl_precache_model},
    {"ncl_precache_sound", ncl_precache_sound},
    {"ncl_upload_file", ncl_upload_file},
    {nullptr, nullptr}
};

void AddNatives_PrivatePrecache()
{
    amxx::AddNatives(g_Natives);
}
