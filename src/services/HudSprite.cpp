#include "HudSprite.h"

#include <metamod/engine.h>
#include <core/type_conversion.h>

#include "utils/msg_ex.h"

using namespace metamod;
using namespace core;
using namespace msg_ex;

HudSprite::HudSprite(ServerEventsManager& server_events_manager)
{
    server_events_manager.on_server_activated().connect(&HudSprite::ServerActivatedHandler, this);
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
    if (message_hud_sprite_ <= 0)
    {
        return;
    }

    MessageBegin(cssdk::MessageType::One, message_hud_sprite_, nullptr, type_conversion::EdictByIndex(client));
    WriteByte(channel);
    WriteString(sprite_path);
    WriteByte(0);
    WriteByte(sprite_color[0]);
    WriteByte(sprite_color[1]);
    WriteByte(sprite_color[2]);
    WriteByte(alpha);
    WriteShort(frame);
    WriteFloat(frame_rate);
    WriteFloat(in_time);
    WriteFloat(hold_time);
    WriteFloat(out_time);
    WriteFloat(x);
    WriteFloat(y);
    WriteShort(sprite_rect[0]);
    WriteShort(sprite_rect[1]);
    WriteShort(sprite_rect[2]);
    WriteShort(sprite_rect[3]);
    WriteFloat(scale_x);
    WriteFloat(scale_y);
    WriteByte(render_mode);
    MessageEnd();
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
    if (message_hud_sprite_ <= 0)
    {
        return;
    }

    MessageBegin(cssdk::MessageType::One, message_hud_sprite_, nullptr, type_conversion::EdictByIndex(client));
    WriteByte(channel);
    WriteString(sprite_path);
    WriteByte(1);
    WriteByte(sprite_color[0]);
    WriteByte(sprite_color[1]);
    WriteByte(sprite_color[2]);
    WriteByte(alpha);
    WriteShort(frame);
    WriteFloat(frame_rate);
    WriteFloat(in_time);
    WriteFloat(hold_time);
    WriteFloat(out_time);
    WriteByte(render_mode);
    MessageEnd();
}

void HudSprite::ClearHudSprite(int client, int channel)
{
    if (message_hud_sprite_ <= 0)
        return;

    MessageBegin(cssdk::MessageType::One, message_hud_sprite_, nullptr, type_conversion::EdictByIndex(client));
    WriteByte(channel);
    WriteString("");
    MessageEnd();
}

void HudSprite::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_hud_sprite_ = RegUserMsgSafe("HudSprite", -1);
}
