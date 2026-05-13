#pragma once
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>
#include "game_events/GameEventsManager.h"

class Miscellaneous : public sigslot::observer
{
    int message_set_fov_ex_{};
    int message_invert_mouse_{};

public:
    explicit Miscellaneous(GameEventsManager& game_events_manager);

    void ClientSetFOV(ClientId client, int fov, float lerp_time);
    void ClientInvertMouse(ClientId client, bool invert_pitch, bool invert_yaw);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
};

struct MiscellaneousService : kgr::single_service<Miscellaneous, kgr::dependency<GameEventsManagerService>> {};
