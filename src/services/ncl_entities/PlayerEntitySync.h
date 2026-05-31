#pragma once
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>

#include "EntitySync.h"
#include "services/server_events/ServerEventsManager.h"

class PlayerEntitySync : public sigslot::observer
{
    ServerEventsManager& server_events_manager_;
    EntitySync& entity_sync_;

public:
    explicit PlayerEntitySync(ServerEventsManager& server_events_manager, EntitySync& entity_sync);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
    void ClientConnectingHandler(ClientConnectingEvent event);
};

struct PlayerNclEntitySyncService : kgr::single_service<PlayerEntitySync, kgr::dependency<ServerEventsManagerService, EntitySyncService>>
{};
