#include <easylogging++.h>

#include <amxx/api.h>

#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_is_client_api_ready(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index
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

    cell result = NAPI().IsClientReady(params[arg_index]);
    return result;
}

static cell AMX_NATIVE_CALL ncl_is_next_client(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index
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

    return 0;
}

static cell AMX_NATIVE_CALL ncl_is_using_nextclient(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index
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

    cell result = (cell)NAPI().IsClientUsingNextClient(params[arg_index]);
    return result;
}

static cell AMX_NATIVE_CALL ncl_get_nextclient_version(Amx* amx, cell* params)
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

    if (amxx::IsPlayerBot(params[arg_index]))
    {
        return FALSE;
    }

    if (!amxx::IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return FALSE;
    }

    NextClientVersion version;
    bool result = NAPI().GetNextClientVersion(params[arg_index], version);

    *amx::Address(amx, params[arg_major]) = (cell)version.major;
    *amx::Address(amx, params[arg_minor]) = (cell)version.minor;
    *amx::Address(amx, params[arg_patch]) = (cell)version.patch;

    return result;
}

static cell AMX_NATIVE_CALL ncl_get_supported_features(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index
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

    cell result = NAPI().GetSupportedFeatures(params[arg_index]);
    return result;
}

static cell AMX_NATIVE_CALL ncl_get_client_platform(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_index
    };

    // NCL_PLATFORM_UNKNOWN in next_client_api.inc
    constexpr cell platform_unknown = -1;

    if (amxx::IsPlayerBot(params[arg_index]))
    {
        return platform_unknown;
    }

    if (!amxx::IsPlayerValid(params[arg_index]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_index];
        return platform_unknown;
    }

    NCLM_PLATFORM platform;
    if (!NAPI().TryGetClientPlatform(params[arg_index], platform))
    {
        return platform_unknown;
    }

    return static_cast<cell>(platform);
}

static AmxNativeInfo g_Natives[] = {
    {"ncl_is_client_api_ready", ncl_is_client_api_ready},
    {"ncl_is_next_client", ncl_is_next_client},
    {"ncl_is_using_nextclient", ncl_is_using_nextclient},
    {"ncl_get_nextclient_version", ncl_get_nextclient_version},
    {"ncl_get_supported_features", ncl_get_supported_features},
    {"ncl_get_client_platform", ncl_get_client_platform},
    {nullptr, nullptr}
};

void AddNatives_NextClient()
{
    amxx::AddNatives(g_Natives);
}
