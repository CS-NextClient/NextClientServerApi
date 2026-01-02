#include <easylogging++.h>
#include "amxxmodule.h"
#include "api_access.h"
#include "AmxContextGuard.h"

constexpr int MAX_HUD_SPRITES = 32;

static cell AMX_NATIVE_CALL ncl_send_hud_sprite(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum
    {
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

    if (MF_IsPlayerBot(params[arg_player]))
        return FALSE;

    if (!MF_IsPlayerValid(params[arg_player]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_player];
        return FALSE;
    }

    int player = params[arg_player];
    int channel = params[arg_channel];

    if (channel < 0 || channel >= MAX_HUD_SPRITES)
    {
        LOG(ERROR) << "channel " << channel << " out of bounds";
        return FALSE;
    }

    const char* sprite_path = MF_GetAmxString(amx, params[arg_sprite_path], 0, nullptr);
    const cell* sprite_color = MF_GetAmxAddr(amx, params[arg_sprite_color]);

    uint8_t color[3] =
    {
        (uint8_t)sprite_color[0],
        (uint8_t)sprite_color[1],
        (uint8_t)sprite_color[2]
    };
    int alpha = params[arg_alpha];
    int frame = params[arg_frame];
    float frame_rate = amx_ctof(params[arg_frame_rate]);
    float in_time = amx_ctof(params[arg_in_time]);
    float hold_time = amx_ctof(params[arg_hold_time]);
    float out_time = amx_ctof(params[arg_out_time]);
    float x = amx_ctof(params[arg_x]);
    float y = amx_ctof(params[arg_y]);
    cell* sprite_rect = MF_GetAmxAddr(amx, params[arg_sprite_rect]);
    int rect[4] =
    {
        sprite_rect[0],
        sprite_rect[1],
        sprite_rect[2],
        sprite_rect[3]
    };
    float scale_x = amx_ctof(params[arg_scale_x]);
    float scale_y = amx_ctof(params[arg_scale_y]);
    cell render_mode = params[arg_render_mode];

    GetHudSprite().SendHudSprite(
        player,
        channel,
        sprite_path,
        color,
        alpha,
        frame,
        frame_rate,
        in_time,
        hold_time,
        out_time,
        x,
        y,
        rect,
        scale_x,
        scale_y,
        render_mode
    );

    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_send_hud_sprite_full_screen(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum
    {
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

    if (MF_IsPlayerBot(params[arg_player]))
        return FALSE;

    if (!MF_IsPlayerValid(params[arg_player]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_player];
        return FALSE;
    }

    const int player = params[arg_player];
    const int channel = params[arg_channel];
    if (channel < 0 || channel >= MAX_HUD_SPRITES)
    {
        LOG(ERROR) << "channel " << channel << " out of bounds";
        return FALSE;
    }
    const auto sprite_path = MF_GetAmxString(amx, params[arg_sprite_path], 0, nullptr);
    const auto sprite_color = MF_GetAmxAddr(amx, params[arg_sprite_color]);
    const uint8_t color[3] = {
        (uint8_t)sprite_color[0],
        (uint8_t)sprite_color[1],
        (uint8_t)sprite_color[2]
    };
    const int alpha = params[arg_alpha];
    const int frame = params[arg_frame];
    const auto frame_rate = amx_ctof(params[arg_frame_rate]);
    const auto in_time = amx_ctof(params[arg_in_time]);
    const auto hold_time = amx_ctof(params[arg_hold_time]);
    const auto out_time = amx_ctof(params[arg_out_time]);
    const auto render_mode = params[arg_render_mode];
    GetHudSprite().SendHudSpriteFullScreen(
        player,
        channel,
        sprite_path,
        color,
        alpha,
        frame,
        frame_rate,
        in_time,
        hold_time,
        out_time,
        render_mode
    );

    return TRUE;
}

static cell AMX_NATIVE_CALL ncl_clear_hud_sprite(AMX* amx, cell* params)
{
    AmxContextGuard guard(amx);
    enum
    {
        arg_count,
        arg_player,
        arg_channel,
    };

    if (MF_IsPlayerBot(params[arg_player]))
        return FALSE;

    if (!MF_IsPlayerValid(params[arg_player]))
    {
        LOG(ERROR) << "invalid player index " << params[arg_player];
        return FALSE;
    }

    int player = params[arg_player];
    int channel = params[arg_channel];

    if (channel < 0 || channel >= MAX_HUD_SPRITES)
    {
        LOG(ERROR) << "channel " << channel << " out of bounds";
        return FALSE;
    }

    GetHudSprite().ClearHudSprite(player, channel);
    return TRUE;
}

static AMX_NATIVE_INFO g_NativeInfo[] =
{
    { "ncl_send_hud_sprite", ncl_send_hud_sprite },
    { "ncl_send_hud_sprite_full_screen", ncl_send_hud_sprite_full_screen },
    { "ncl_clear_hud_sprite", ncl_clear_hud_sprite },
    { nullptr, nullptr }
};

void AddNatives_HudSprite()
{
    MF_AddNatives(g_NativeInfo);
}
