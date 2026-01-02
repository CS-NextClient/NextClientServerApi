#include "HudSprite.h"
#include "utils/utilfuncs.h"

HudSprite::HudSprite(GameEventsManager& game_events_manager)
{
    game_events_manager.on_server_activated().connect(&HudSprite::ServerActivatedHandler, this);
}

void HudSprite::SendHudSprite(
    int client,
    int channel,
    const char* sprite_path,
    const uint8_t sprite_color[3],
    uint8_t alpha,
    int frame,
    float frame_rate,
    float in_time,
    float hold_time,
    float out_time,
    float x,
    float y,
    const int sprite_rect[4],
    float scale_x,
    float scale_y,
    int render_mode
)
{
    MESSAGE_BEGIN(MSG_ONE, message_hud_sprite_, nullptr, INDEXENT(client));
    WRITE_BYTE(channel);
    WRITE_STRING(sprite_path);
    WRITE_BYTE(0);
    WRITE_BYTE(sprite_color[0]);
    WRITE_BYTE(sprite_color[1]);
    WRITE_BYTE(sprite_color[2]);
    WRITE_BYTE(alpha);
    WRITE_SHORT(frame);
    WRITE_FLOAT(frame_rate);
    WRITE_FLOAT(in_time);
    WRITE_FLOAT(hold_time);
    WRITE_FLOAT(out_time);
    WRITE_FLOAT(x);
    WRITE_FLOAT(y);
    WRITE_SHORT(sprite_rect[0]);
    WRITE_SHORT(sprite_rect[1]);
    WRITE_SHORT(sprite_rect[2]);
    WRITE_SHORT(sprite_rect[3]);
    WRITE_FLOAT(scale_x);
    WRITE_FLOAT(scale_y);
    WRITE_BYTE(render_mode);
    MESSAGE_END();
}

void HudSprite::SendHudSpriteFullScreen(
    int client,
    int channel,
    const char* sprite_path,
    const uint8_t sprite_color[3],
    uint8_t alpha,
    int frame,
    float frame_rate,
    float in_time,
    float hold_time,
    float out_time,
    int render_mode
)
{
    MESSAGE_BEGIN(MSG_ONE, message_hud_sprite_, nullptr, INDEXENT(client));
    WRITE_BYTE(channel);
    WRITE_STRING(sprite_path);
    WRITE_BYTE(1);
    WRITE_BYTE(sprite_color[0]);
    WRITE_BYTE(sprite_color[1]);
    WRITE_BYTE(sprite_color[2]);
    WRITE_BYTE(alpha);
    WRITE_SHORT(frame);
    WRITE_FLOAT(frame_rate);
    WRITE_FLOAT(in_time);
    WRITE_FLOAT(hold_time);
    WRITE_FLOAT(out_time);
    WRITE_BYTE(render_mode);
    MESSAGE_END();
}

void HudSprite::ClearHudSprite(int client, int channel)
{
    MESSAGE_BEGIN(MSG_ONE, message_hud_sprite_, nullptr, INDEXENT(client));
    WRITE_BYTE(channel);
    WRITE_STRING("");
    MESSAGE_END();
}

void HudSprite::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_hud_sprite_ = utils::RegUserMsgSafe("HudSprite", -1);
}
