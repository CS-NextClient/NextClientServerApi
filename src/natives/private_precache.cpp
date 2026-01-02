#include <easylogging++.h>
#include "amxxmodule.h"
#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_precache_model(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = MF_GetAmxString(amx, params[arg_filepath], 0, nullptr);
    std::string ncl_filepath = MF_GetAmxString(amx, params[arg_nclFilepath], 1, nullptr);

    int model_index = GetPrivatePrecache().PrecacheModel(filepath, ncl_filepath);
    if (model_index == 0)
    {
        LOG(ERROR) << "Can't find file '" << ncl_filepath << "' (is a replacement for '" << filepath << "')";
        return FALSE;
    }

    return model_index;
}

static cell AMX_NATIVE_CALL ncl_precache_sound(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = MF_GetAmxString(amx, params[arg_filepath], 0, nullptr);
    std::string ncl_filepath = MF_GetAmxString(amx, params[arg_nclFilepath], 1, nullptr);

    int sound_index = GetPrivatePrecache().PrecacheSound(filepath, ncl_filepath);
    if (sound_index == 0)
    {
        LOG(ERROR) << "Can't find file '" << ncl_filepath << "' (is a replacement for '" << filepath << "')";
        return FALSE;
    }

    return sound_index;
}

static cell AMX_NATIVE_CALL ncl_upload_file(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = MF_GetAmxString(amx, params[arg_filepath], 0, nullptr);
    std::string ncl_filepath = MF_GetAmxString(amx, params[arg_nclFilepath], 1, nullptr);

    int result = GetPrivatePrecache().UploadFile(filepath, ncl_filepath);
    if (result == 0)
    {
        LOG(ERROR) << "Can't find file '" << ncl_filepath << "' (is a replacement for '" << filepath << "')";
        return FALSE;
    }

    return TRUE;
}

static AMX_NATIVE_INFO nativeInfoPrivatePrecache[] = {
    { "ncl_precache_model", ncl_precache_model },
    { "ncl_precache_sound", ncl_precache_sound },
    { "ncl_upload_file", ncl_upload_file },
    { nullptr, nullptr }
};

void AddNatives_PrivatePrecache()
{
    MF_AddNatives(nativeInfoPrivatePrecache);
}
