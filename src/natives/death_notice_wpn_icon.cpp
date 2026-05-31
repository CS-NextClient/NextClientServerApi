#include <easylogging++.h>

#include <amxx/api.h>

#include "api_access.h"
#include "AmxContextGuard.h"

static cell AMX_NATIVE_CALL ncl_set_wpn_icon_for_next_deathmsg(Amx* amx, cell* params)
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
        if (amxx::IsPlayerBot(params[arg_recipient]))
        {
            return FALSE;
        }

        if (!amxx::IsPlayerValid(params[arg_recipient]))
        {
            LOG(ERROR) << "invalid player index " << params[arg_recipient];
            return FALSE;
        }
    }

    const char* sprite = amxx::GetAmxString(amx, params[arg_sprite], 0, nullptr);
    const cell* color = amx::Address(amx, params[arg_color]);

    // clang-format off
    GetDeathMsgWpnIcon().SetIconForNextMessage(
        sprite,
        params[arg_frame],
        params[arg_rendermode],
        color[0],
        color[1],
        color[2],
        params[arg_alpha],
        recipient);
    // clang-format on

    return TRUE;
}

// clang-format off
static AmxNativeInfo g_Natives[] =
{
    { "ncl_set_wpn_icon_for_next_deathmsg", ncl_set_wpn_icon_for_next_deathmsg },
    { nullptr, nullptr }
};
// clang-format on

void AddNatives_DeathNoticeWpnIcon()
{
    amxx::AddNatives(g_Natives);
}
