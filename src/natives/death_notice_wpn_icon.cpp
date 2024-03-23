#include "main.h"
#include "amxxmodule.h"
#include "asserts.h"

cell AMX_NATIVE_CALL ncl_set_wpn_icon_for_next_deathmsg(AMX* amx, cell* params)
{
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
    
    const auto recipient = params[arg_recipient];
    if(recipient != 0) {
        ASSERT_ARG_IS_PLAYER(arg_recipient)
    }

    const auto sprite = MF_GetAmxString(amx, params[arg_sprite], 0, NULL);
    const auto color = MF_GetAmxAddr(amx, params[arg_color]);

    NAPI()->DeathMsgWpnIcon()->SetIconForNextMessage(sprite, params[arg_frame], 
        params[arg_rendermode], color[0], color[1], color[2], params[arg_alpha], recipient);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

static AMX_NATIVE_INFO nativeInfo[] = {
	{"ncl_set_wpn_icon_for_next_deathmsg", ncl_set_wpn_icon_for_next_deathmsg},

	{nullptr, nullptr}
};

void AddNatives_DeathNoticeWpnIcon() {
	MF_AddNatives(nativeInfo);
}