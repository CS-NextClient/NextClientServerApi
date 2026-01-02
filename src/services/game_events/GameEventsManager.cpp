#include "GameEventsManager.h"
#include <meta_api.h>
#include "game_events.h"

GameEventsManager* GameEventsManager::instance_ = nullptr;

GameEventsManager::GameEventsManager(IRehldsHookchains* rehlds_hookchains) :
    rehlds_hookchains_(rehlds_hookchains)
{
    if (instance_)
        throw std::runtime_error("GameEventsManager instance already exists");

    instance_ = this;

    rehlds_hookchains_->ClientConnected()->registerHook(ClientConnectedHandler);
    rehlds_hookchains_->SV_SendServerinfo()->registerHook(SV_SendServerinfoHandler);
    rehlds_hookchains_->SV_DropClient()->registerHook(SV_DropClientHandler);
}

GameEventsManager::~GameEventsManager()
{
    rehlds_hookchains_->ClientConnected()->unregisterHook(ClientConnectedHandler);
    rehlds_hookchains_->SV_SendServerinfo()->unregisterHook(SV_SendServerinfoHandler);
    rehlds_hookchains_->SV_DropClient()->unregisterHook(SV_DropClientHandler);

    instance_ = nullptr;
}

sigslot::signal<ClientConnectingEvent>& GameEventsManager::on_client_connecting() noexcept
{
    return client_connecting_;
}

sigslot::signal<ClientId>& GameEventsManager::on_client_connected() noexcept
{
    return client_connected_;
}

sigslot::signal<ClientId>& GameEventsManager::on_client_putinserver() noexcept
{
    return client_putinserver_;
}

sigslot::signal<ClientId>& GameEventsManager::on_client_first_frame() noexcept
{
    return client_first_frame_;
}

sigslot::signal<ClientId>& GameEventsManager::on_player_think_post() noexcept
{
    return player_think_post_;
}

sigslot::signal<ClientId>& GameEventsManager::on_client_disconnected() noexcept
{
    return client_disconnected_;
}

sigslot::signal<ClientDropConnectionEvent>& GameEventsManager::on_client_drop_connection() noexcept
{
    return client_drop_connection_;
}

sigslot::signal<MessageBeginPostEvent>& GameEventsManager::on_message_begin_post() noexcept
{
    return message_begin_post_;
}

sigslot::signal<>& GameEventsManager::on_message_end_post() noexcept
{
    return message_end_post_;
}

sigslot::signal<ClientId>& GameEventsManager::on_send_server_info() noexcept
{
    return send_server_info_;
}

sigslot::signal<ServerActivatedEvent>& GameEventsManager::on_server_activated() noexcept
{
    return server_activated_;
}

sigslot::signal<>& GameEventsManager::on_amxx_plugins_loaded() noexcept
{
    return amxx_plugins_loaded_;
}

void GameEventsManager::PlayerPostThinkHandler(edict_t* pEntity)
{
    ClientId client = ENTINDEX(pEntity);

    auto it = players_.find(client);
    if (it != players_.end())
    {
        InternalData& data = it->second;

        if (data.first_frame)
        {
            client_first_frame_(client);
            data.first_frame = false;
        }
    }

    player_think_post_(client);
}

void GameEventsManager::ClientDropConnectionHandler(IGameClient* apiClient, bool crash, const char* buf)
{
    ClientId client = apiClient->GetId() + 1;

    client_drop_connection_(ClientDropConnectionEvent{client, crash, buf});
    players_.erase(client);
}

void GameEventsManager::ClientPutInServerHandler(edict_t* pEntity)
{
    ClientId client = ENTINDEX(pEntity);

    auto it = players_.find(client);
    if (it != players_.end())
    {
        it->second.first_frame = true;
    }

    client_putinserver_(client);
}
