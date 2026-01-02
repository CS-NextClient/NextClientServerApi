#pragma once
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>
#include "game_events/GameEventsManager.h"

class Miscellaneous : public sigslot::observer
{
    int message_set_fov_ex_{};

public:
    explicit Miscellaneous(GameEventsManager& game_events_manager);

    void ClientSetFOV(ClientId client, int fov, float lerp_time);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
};

struct MiscellaneousService : kgr::single_service<Miscellaneous, kgr::dependency<GameEventsManagerService>> {};
