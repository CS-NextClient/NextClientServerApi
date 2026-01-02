#pragma once
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>
#include "game_events/GameEventsManager.h"

class HudSprite : public sigslot::observer
{
    int message_hud_sprite_{};

public:
    explicit HudSprite(GameEventsManager& game_events_manager);

    void SendHudSprite(
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
    );

    void SendHudSpriteFullScreen(
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
    );

    void ClearHudSprite(int client, int channel);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
};

struct HudSpriteService : kgr::single_service<HudSprite, kgr::dependency<GameEventsManagerService>> {};
