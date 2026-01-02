#include <easylogging++.h>
#include "amxxmodule.h"
#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_set_wpn_icon_for_next_deathmsg(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum args_e
    {
        arg_count,
        arg_sprite,
        arg_frame,
        arg_rendermode,
        arg_color,
        arg_alpha,
        arg_recipient
    };

    cell recipient = params[arg_recipient];
    if (recipient != 0)
    {
        if (MF_IsPlayerBot(params[arg_recipient]))
            return FALSE;

        if (!MF_IsPlayerValid(params[arg_recipient]))
        {
            LOG(ERROR) << ": invalid player index " << params[arg_recipient];
            return FALSE;
        }
    }

    const char* sprite = MF_GetAmxString(amx, params[arg_sprite], 0, nullptr);
    const cell* color = MF_GetAmxAddr(amx, params[arg_color]);

    GetDeathMsgWpnIcon().SetIconForNextMessage(
        sprite,
        params[arg_frame],
        params[arg_rendermode],
        color[0],
        color[1],
        color[2],
        params[arg_alpha],
        recipient);

    return TRUE;
}

static AMX_NATIVE_INFO g_NativeInfo[] =
{
    { "ncl_set_wpn_icon_for_next_deathmsg", ncl_set_wpn_icon_for_next_deathmsg },
    { nullptr, nullptr }
};

void AddNatives_DeathNoticeWpnIcon()
{
    MF_AddNatives(g_NativeInfo);
}
