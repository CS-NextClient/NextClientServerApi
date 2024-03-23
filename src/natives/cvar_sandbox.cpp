#include "main.h"
#include "amxxmodule.h"
#include "asserts.h"

cell AMX_NATIVE_CALL ncl_sandbox_cvar_begin(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_index
    };
    ASSERT_ARG_IS_PLAYER(arg_index);

    int client = params[arg_index];
    NAPI()->CvarSandbox()->Begin(client);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_sandbox_cvar_end(AMX* amx, cell* params)
{
    NAPI()->CvarSandbox()->End();

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_write_sandbox_cvar(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_cvar,
        arg_value,
    };

    auto cvar = static_cast<SandboxCvar>(params[arg_cvar]);
    std::string value = MF_GetAmxString(amx, params[arg_value], 0, NULL);

    NAPI()->CvarSandbox()->WriteCvar(cvar, value);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

AMX_NATIVE_INFO nativeInfoCvarSandbox[] = {
        {"ncl_sandbox_cvar_begin", ncl_sandbox_cvar_begin},
        {"ncl_sandbox_cvar_end",   ncl_sandbox_cvar_end},
        {"ncl_write_sandbox_cvar", ncl_write_sandbox_cvar},

        {nullptr,                  nullptr}
};

void AddNatives_CvarSandbox()
{
    MF_AddNatives(nativeInfoCvarSandbox);
}