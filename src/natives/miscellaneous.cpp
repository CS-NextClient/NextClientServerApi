#include <easylogging++.h>

#include <amxx/api.h>

#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_setfov(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index,
        arg_fov,
        arg_lerpTime
    };

    if (amxx::IsPlayerBot(params[arg_index]))
    {
        return FALSE;
    }

    if (!amxx::IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    GetMiscellaneous().ClientSetFOV(params[arg_index], params[arg_fov], amx::CellToFloat(params[arg_lerpTime]));
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_invert_mouse(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index,
        arg_invert_pitch,
        arg_invert_yaw,
    };

    if (amxx::IsPlayerBot(params[arg_index]))
    {
        return FALSE;
    }

    if (!amxx::IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    GetMiscellaneous().ClientInvertMouse(params[arg_index], params[arg_invert_pitch], params[arg_invert_yaw]);
    return TRUE;
}

// clang-format off
static AmxNativeInfo g_Natives[] = {
    {"ncl_setfov", ncl_setfov}, 
    {"ncl_invert_mouse", ncl_invert_mouse}, 
    {nullptr, nullptr}
};
// clang-format on

void AddNatives_Miscellaneous()
{
    amxx::AddNatives(g_Natives);
}
