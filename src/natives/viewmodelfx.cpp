#include <easylogging++.h>

#include <amxx/api.h>

#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_viewmodelfx_begin(Amx* amx, cell* params)
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

    GetViewmodelFX().Begin(params[arg_index]);
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_viewmodelfx_end(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    GetViewmodelFX().End();
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_write_rendermode(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_rendermode
    };

    GetViewmodelFX().WriteRenderMode(params[arg_rendermode]);
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_write_renderamt(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_renderamt
    };

    GetViewmodelFX().WriteRenderAmt(params[arg_renderamt]);
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_write_renderfx(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_renderfx
    };

    GetViewmodelFX().WriteRenderFX(params[arg_renderfx]);
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_write_renderskin(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_skin
    };

    GetViewmodelFX().WriteSkin(params[arg_skin]);
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_write_renderbody(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_body
    };

    GetViewmodelFX().WriteBody(params[arg_body]);
    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_write_rendercolor(Amx* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_r,
        arg_g,
        arg_b
    };

    GetViewmodelFX().WriteRenderColor(params[arg_r], params[arg_g], params[arg_b]);
    return TRUE;
}

static AmxNativeInfo g_Natives[] = {
    {"ncl_viewmodelfx_begin", ncl_viewmodelfx_begin},
    {"ncl_viewmodelfx_end", ncl_viewmodelfx_end},
    {"ncl_write_rendermode", ncl_write_rendermode},
    {"ncl_write_renderamt", ncl_write_renderamt},
    {"ncl_write_renderfx", ncl_write_renderfx},
    {"ncl_write_renderskin", ncl_write_renderskin},
    {"ncl_write_renderbody", ncl_write_renderbody},
    {"ncl_write_rendercolor", ncl_write_rendercolor},
    {nullptr, nullptr}
};

void AddNatives_ViewmodelFX()
{
    amxx::AddNatives(g_Natives);
}
