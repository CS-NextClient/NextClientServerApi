#pragma once
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>
#include "game_events/GameEventsManager.h"
#include "INextClientInfo.h"

class HealthNext : public sigslot::observer
{
    INextClientInfo& next_client_info_;

    int message_HealthNEx_{};
    int message_Health_{};

    bool should_send_health_ex_{};
    int msg_save_hp_{};
    int msg_save_dest_{};
    float msg_save_origin_[3]{};
    edict_t* msg_save_ed_{};

public:
    explicit HealthNext(GameEventsManager& game_events_manager, INextClientInfo& next_client_info);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
    void MessageBeginPostHandler(MessageBeginPostEvent event);
    void MessageEndPostHandler();
};

struct HealthNextService : kgr::single_service<HealthNext, kgr::dependency<GameEventsManagerService, INextClientInfoService>> {};
