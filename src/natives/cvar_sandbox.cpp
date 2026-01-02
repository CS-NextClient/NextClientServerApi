#include <easylogging++.h>
#include "amxxmodule.h"
#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_sandbox_cvar_begin(AMX* amx, cell* params)
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
        LOG(ERROR) << ": invalid player index " << params[arg_index];
        return FALSE;
    }

    int client = params[arg_index];
    GetCvarSandbox().Begin(client);

    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_sandbox_cvar_end(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    GetCvarSandbox().End();

    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_write_sandbox_cvar(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_cvar,
        arg_value,
    };

    SandboxCvar cvar = (SandboxCvar)params[arg_cvar];
    std::string value = MF_GetAmxString(amx, params[arg_value], 0, nullptr);

    GetCvarSandbox().WriteCvar(cvar, value);

    return TRUE;
}

static AMX_NATIVE_INFO g_NativeInfo[] =
{
    { "ncl_sandbox_cvar_begin", ncl_sandbox_cvar_begin },
    { "ncl_sandbox_cvar_end", ncl_sandbox_cvar_end },
    { "ncl_write_sandbox_cvar", ncl_write_sandbox_cvar },
    { nullptr, nullptr }
};

void AddNatives_CvarSandbox()
{
    MF_AddNatives(g_NativeInfo);
}
