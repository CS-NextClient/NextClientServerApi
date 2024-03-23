#include "main.h"
#include "amxxmodule.h"
#include "asserts.h"
#include "natives.h"

cell AMX_NATIVE_CALL ncl_is_client_api_ready(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_index
    };
    ASSERT_ARG_IS_PLAYER(arg_index);

    cell result = NAPI()->ClientIsReady(params[arg_index]);

    ASSERT_NO_NAPI_ERRORS();
    return result;
}

cell AMX_NATIVE_CALL ncl_is_next_client(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_index
    };
    ASSERT_ARG_IS_PLAYER(arg_index);

    cell result = (cell) NAPI()->deprecated_GetNextClientVersion(params[arg_index]);

    ASSERT_NO_NAPI_ERRORS();
    return result;
}

cell AMX_NATIVE_CALL ncl_is_using_nextclient(AMX* amx, cell* params) {
    enum args_e
    {
        arg_count,
        arg_index
    };
    ASSERT_ARG_IS_PLAYER(arg_index);

    cell result = (cell) NAPI()->ClientIsUsingNextClient(params[arg_index]);

    ASSERT_NO_NAPI_ERRORS();
    return result;
}

cell AMX_NATIVE_CALL ncl_get_nextclient_version(AMX* amx, cell* params) {
    enum args_e
    {
        arg_count,
        arg_index,
        arg_major,
        arg_minor,
        arg_patch
    };
    ASSERT_ARG_IS_PLAYER(arg_index);

    NextClientVersion version;
    bool result = NAPI()->GetNextClientVersion(params[arg_index], version);

    *MF_GetAmxAddr(amx, params[arg_major]) = version.major;
    *MF_GetAmxAddr(amx, params[arg_minor]) = version.minor;
    *MF_GetAmxAddr(amx, params[arg_patch]) = version.patch;

    ASSERT_NO_NAPI_ERRORS();
    return result;
}

cell AMX_NATIVE_CALL ncl_get_supported_features(AMX* amx, cell* params) {
    enum args_e
    {
        arg_count,
        arg_index
    };
    ASSERT_ARG_IS_PLAYER(arg_index);

    cell result = (cell) NAPI()->GetSupportedFeatures(params[arg_index]);

    ASSERT_NO_NAPI_ERRORS();
    return result;
}

cell AMX_NATIVE_CALL ncl_setfov(AMX* amx, cell* params)
{
    enum args_e
    {
        arg_count,
        arg_index,
        arg_fov,
        arg_lerpTime
    };
    ASSERT_ARG_IS_PLAYER(arg_index);

    NAPI()->ClientSetFOV(params[arg_index], params[arg_fov], params[arg_lerpTime]);

    ASSERT_NO_NAPI_ERRORS();
    return TRUE;
}

cell AMX_NATIVE_CALL ncl_send_hud_sprite(AMX* amx, cell* params)
{
    enum {
        arg_count,
        arg_player,
        arg_channel,
        arg_sprite_path,
        arg_sprite_color,
        arg_alpha,
        arg_frame,
        arg_frame_rate,
        arg_in_time,
        arg_hold_time,
        arg_out_time,
        arg_x,
        arg_y,
        arg_sprite_rect,
        arg_scale_x,
        arg_scale_y,
        arg_render_mode
    };

    ASSERT_ARG_IS_PLAYER(arg_player);
    const int player = params[arg_player];
    const int channel = params[arg_channel];
    if (channel < 0 || channel >= MAX_HUD_SPRITES) {
        MF_LogError(amx, AMX_ERR_NATIVE, "%s: channel %d out of bounds", __FUNCTION__, channel);
        return false;
    }
    const auto spritePath = MF_GetAmxString(amx, params[arg_sprite_path], 0, nullptr);
    const auto spriteColor = MF_GetAmxAddr(amx, params[arg_sprite_color]);
    const uint8_t color[3] = {
        static_cast<uint8_t>(spriteColor[0]),
        static_cast<uint8_t>(spriteColor[1]),
        static_cast<uint8_t>(spriteColor[2])
    };
    const int alpha = params[arg_alpha];
    const int frame = params[arg_frame];
    const auto frameRate = params[arg_frame_rate];
    const auto inTime = params[arg_in_time];
    const auto holdTime = params[arg_hold_time];
    const auto outTime = params[arg_out_time];
    const auto x = params[arg_x];
    const auto y = params[arg_y];
    const auto spriteRect = MF_GetAmxAddr(amx, params[arg_sprite_rect]);
    const int rect[4] = {
        spriteRect[0],
        spriteRect[1],
        spriteRect[2],
        spriteRect[3]
    };
    const auto scaleX = params[arg_scale_x];
    const auto scaleY = params[arg_scale_y];
    const auto renderMode = params[arg_render_mode];
    NAPI()->SendHudSprite(
        player,
        channel,
        spritePath,
        color,
        alpha,
        frame,
        frameRate,
        inTime,
        holdTime,
        outTime,
        x,
        y,
        rect,
        scaleX,
        scaleY,
        renderMode
    );
    ASSERT_NO_NAPI_ERRORS();
    return true;
}

cell AMX_NATIVE_CALL ncl_send_hud_sprite_full_screen(AMX* amx, cell* params)
{
    enum {
        arg_count,
        arg_player,
        arg_channel,
        arg_sprite_path,
        arg_sprite_color,
        arg_alpha,
        arg_frame,
        arg_frame_rate,
        arg_in_time,
        arg_hold_time,
        arg_out_time,
        arg_render_mode
    };

    ASSERT_ARG_IS_PLAYER(arg_player);
    const int player = params[arg_player];
    const int channel = params[arg_channel];
    if (channel < 0 || channel >= MAX_HUD_SPRITES) {
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: channel %d out of bounds", __FUNCTION__, channel);
		return false;
	}
    const auto spritePath = MF_GetAmxString(amx, params[arg_sprite_path], 0, nullptr);
    const auto spriteColor = MF_GetAmxAddr(amx, params[arg_sprite_color]);
    const uint8_t color[3] = {
        static_cast<uint8_t>(spriteColor[0]),
        static_cast<uint8_t>(spriteColor[1]),
        static_cast<uint8_t>(spriteColor[2])
    };
    const int alpha = params[arg_alpha];
    const int frame = params[arg_frame];
    const auto frameRate = amx_ctof(params[arg_frame_rate]);
    const auto inTime = params[arg_in_time];
    const auto holdTime = params[arg_hold_time];
    const auto outTime = params[arg_out_time];
    const auto renderMode = params[arg_render_mode];
    NAPI()->SendHudSpriteFullScreen(
        player,
        channel,
        spritePath,
        color,
        alpha,
        frame,
        frameRate,
        inTime,
        holdTime,
        outTime,
        renderMode
    );
    ASSERT_NO_NAPI_ERRORS();
    return true;
}

cell AMX_NATIVE_CALL ncl_clear_hud_sprite(AMX* amx, cell* params)
{
    enum {
        arg_count,
        arg_player,
        arg_channel,
    };

    ASSERT_ARG_IS_PLAYER(arg_player);
    const int player = params[arg_player];
    const int channel = params[arg_channel];
    if (channel < 0 || channel >= MAX_HUD_SPRITES) {
        MF_LogError(amx, AMX_ERR_NATIVE, "%s: channel %d out of bounds", __FUNCTION__, channel);
        return false;
    }
    NAPI()->ClearHudSprite(player, channel);
    ASSERT_NO_NAPI_ERRORS();
    return true;
}

AMX_NATIVE_INFO nativeInfoNextClient[] = {
    {"ncl_is_client_api_ready",         ncl_is_client_api_ready},
    {"ncl_is_next_client",              ncl_is_next_client},
    {"ncl_is_using_nextclient",         ncl_is_using_nextclient},
    {"ncl_get_nextclient_version",      ncl_get_nextclient_version},
    {"ncl_get_supported_features",      ncl_get_supported_features},

    {"ncl_setfov",                      ncl_setfov},
    {"ncl_send_hud_sprite",             ncl_send_hud_sprite},
    {"ncl_send_hud_sprite_full_screen", ncl_send_hud_sprite_full_screen},
    {"ncl_clear_hud_sprite",            ncl_clear_hud_sprite},

    {nullptr,                           nullptr}
};

void AddNatives_NextClient()
{
    MF_AddNatives(nativeInfoNextClient);
}