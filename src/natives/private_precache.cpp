#include "main.h"
#include "amxxmodule.h"
#include "asserts.h"

cell AMX_NATIVE_CALL ncl_precache_model(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = MF_GetAmxString(amx, params[arg_filepath], 0, NULL);
    std::string nclFilepath = MF_GetAmxString(amx, params[arg_nclFilepath], 1, NULL);

    int modelIndex = NAPI()->PrivatePrecache()->PrecacheModel(filepath, nclFilepath);
    if (modelIndex == 0)
        MF_LogError(amx, AMX_ERR_NATIVE, "Can't find file '%s' (is a replacement for '%s')", nclFilepath.c_str(), filepath.c_str());

    ASSERT_NO_NAPI_ERRORS();
    return modelIndex;
}

cell AMX_NATIVE_CALL ncl_precache_sound(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = MF_GetAmxString(amx, params[arg_filepath], 0, NULL);
    std::string nclFilepath = MF_GetAmxString(amx, params[arg_nclFilepath], 1, NULL);

    int soundIndex = NAPI()->PrivatePrecache()->PrecacheSound(filepath, nclFilepath);
    if (soundIndex == 0)
        MF_LogError(amx, AMX_ERR_NATIVE, "Can't find file '%s' (is a replacement for '%s')", nclFilepath.c_str(), filepath.c_str());

    ASSERT_NO_NAPI_ERRORS();
    return soundIndex;
}

cell AMX_NATIVE_CALL ncl_upload_file(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_filepath,
        arg_nclFilepath
    };

    std::string filepath = MF_GetAmxString(amx, params[arg_filepath], 0, NULL);
    std::string nclFilepath = MF_GetAmxString(amx, params[arg_nclFilepath], 1, NULL);

    int result = NAPI()->PrivatePrecache()->UploadFile(filepath, nclFilepath);
    if (result == 0)
        MF_LogError(amx, AMX_ERR_NATIVE, "Can't find file '%s' (is a replacement for '%s')", nclFilepath.c_str(), filepath.c_str());

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

AMX_NATIVE_INFO nativeInfoPrivatePrecache[] = {
        {"ncl_precache_model",  ncl_precache_model},
        {"ncl_precache_sound",  ncl_precache_sound},
        {"ncl_upload_file",     ncl_upload_file},

        {nullptr,                    nullptr}
};

void AddNatives_PrivatePrecache()
{
    MF_AddNatives(nativeInfoPrivatePrecache);
}