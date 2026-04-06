#include <easylogging++.h>
#include "amxxmodule.h"
#include "api_access.h"
#include "AmxContextGuard.h"

// ---------------------------------------------------------------------------
// ncl_get_client_hwid(index, hwid[], len)
// ---------------------------------------------------------------------------
static cell AMX_NATIVE_CALL ncl_get_client_hwid(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index,
        arg_hwid,
        arg_len
    };

    if (MF_IsPlayerBot(params[arg_index]))
    {
        MF_SetAmxString(amx, params[arg_hwid], "", params[arg_len]);
        return FALSE;
    }

    if (!MF_IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "ncl_get_client_hwid: invalid player index " << params[arg_index];
        MF_SetAmxString(amx, params[arg_hwid], "", params[arg_len]);
        return FALSE;
    }

    std::string hwid;
    bool has_hwid = NAPI().GetClientHwid(params[arg_index], hwid);

    MF_SetAmxString(amx, params[arg_hwid], hwid.c_str(), params[arg_len]);

    return has_hwid ? TRUE : FALSE;
}

// ---------------------------------------------------------------------------
// ncl_is_hwid_received(index)
// ---------------------------------------------------------------------------
static cell AMX_NATIVE_CALL ncl_is_hwid_received(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index
    };

    if (MF_IsPlayerBot(params[arg_index]))
        return FALSE;

    if (!MF_IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "ncl_is_hwid_received: invalid player index " << params[arg_index];
        return FALSE;
    }

    std::string hwid;
    return NAPI().GetClientHwid(params[arg_index], hwid) ? TRUE : FALSE;
}

static AMX_NATIVE_INFO g_HwidNativeInfo[] = {
    { "ncl_get_client_hwid",  ncl_get_client_hwid  },
    { "ncl_is_hwid_received", ncl_is_hwid_received },
    { nullptr, nullptr }
};

void AddNatives_Hwid()
{
    MF_AddNatives(g_HwidNativeInfo);
}
