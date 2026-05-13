#include <easylogging++.h>
#include "amxxmodule.h"
#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_setfov(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index,
        arg_fov,
        arg_lerpTime
    };

    if (MF_IsPlayerBot(params[arg_index]))
        return FALSE;

    if (!MF_IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    GetMiscellaneous().ClientSetFOV(params[arg_index], params[arg_fov], amx_ctof(params[arg_lerpTime]));
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_invert_mouse(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index,
        arg_invert_pitch,
        arg_invert_yaw,
    };

    if (MF_IsPlayerBot(params[arg_index]))
        return FALSE;

    if (!MF_IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    GetMiscellaneous().ClientInvertMouse(params[arg_index], params[arg_invert_pitch], params[arg_invert_yaw]);
    return TRUE;
}

static AMX_NATIVE_INFO g_NativeInfo[] =
{
    { "ncl_setfov", ncl_setfov },
    { "ncl_invert_mouse", ncl_invert_mouse },
    { nullptr, nullptr }
};

void AddNatives_Miscellaneous()
{
    MF_AddNatives(g_NativeInfo);
}
