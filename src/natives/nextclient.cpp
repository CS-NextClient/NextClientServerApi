#include <easylogging++.h>
#include "amxxmodule.h"
#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_is_client_api_ready(AMX* amx, cell* params)
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
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    cell result = NAPI().IsClientReady(params[arg_index]);
    return result;
}

static cell AMX_NATIVE_CALL ncl_is_next_client(AMX* amx, cell* params)
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
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    cell result = (cell)NAPI().GetNextClientVersionLegacy(params[arg_index]);
    return result;
}

static cell AMX_NATIVE_CALL ncl_is_using_nextclient(AMX* amx, cell* params)
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
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    cell result = (cell)NAPI().IsClientUsingNextClient(params[arg_index]);
    return result;
}

static cell AMX_NATIVE_CALL ncl_get_nextclient_version(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index,
        arg_major,
        arg_minor,
        arg_patch
    };

    if (MF_IsPlayerBot(params[arg_index]))
        return FALSE;

    if (!MF_IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    NextClientVersion version;
    bool result = NAPI().GetNextClientVersion(params[arg_index], version);

    *MF_GetAmxAddr(amx, params[arg_major]) = (cell)version.major;
    *MF_GetAmxAddr(amx, params[arg_minor]) = (cell)version.minor;
    *MF_GetAmxAddr(amx, params[arg_patch]) = (cell)version.patch;

    return result;
}

static cell AMX_NATIVE_CALL ncl_get_supported_features(AMX* amx, cell* params)
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
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    cell result = (cell)NAPI().GetSupportedFeatures(params[arg_index]);
    return result;
}

static AMX_NATIVE_INFO g_NativeInfo[] = {
    { "ncl_is_client_api_ready", ncl_is_client_api_ready },
    { "ncl_is_next_client", ncl_is_next_client },
    { "ncl_is_using_nextclient", ncl_is_using_nextclient },
    { "ncl_get_nextclient_version", ncl_get_nextclient_version },
    { "ncl_get_supported_features", ncl_get_supported_features },
    { nullptr, nullptr }
};

void AddNatives_NextClient()
{
    MF_AddNatives(g_NativeInfo);
}
