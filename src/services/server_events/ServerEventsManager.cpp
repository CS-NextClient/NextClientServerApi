#include "ServerEventsManager.h"

#include <core/type_conversion.h>
#include <mhooks/metamod.h>
#include <mhooks/reapi.h>

#include <easylogging++.h>

using namespace core;
using namespace sv_events;

ServerEventsManager::ServerEventsManager()
{
    if (instance_)
    {
        throw std::runtime_error("ServerEventsManager instance already exists");
    }

    instance_ = this;

    metamod::gamedll::HookClientConnect(ClientConnectPostMetamodHandler, true);
    metamod::gamedll::HookClientDisconnect(ClientDisconnectPostMetamodHandler, true);
    metamod::gamedll::HookClientPutInServer(ClientPutInServerPostMetamodHandler, true);
    metamod::gamedll::HookPlayerPostThink(PlayerPostThinkPostMetamodHandler, true);
    metamod::engine::HookMessageBegin(MessageBeginPostMetamodHandler, true);
    metamod::engine::HookMessageEnd(MessageEndPostMetamodHandler, true);
    metamod::gamedll::HookServerActivate(ServerActivatePostMetamodHandler, true);

    rehlds_api::HookChains()->SvDropClient()->RegisterHook(SV_DropClientHandler);
    rehlds_api::HookChains()->SvSendServerInfo()->RegisterHook(SV_SendServerInfoHandler);
    rehlds_api::HookChains()->SvFrame()->RegisterHook(SV_FrameHandler);
}

ServerEventsManager::~ServerEventsManager()
{
    rehlds_api::HookChains()->SvDropClient()->UnregisterHook(SV_DropClientHandler);
    rehlds_api::HookChains()->SvSendServerInfo()->UnregisterHook(SV_SendServerInfoHandler);
    rehlds_api::HookChains()->SvFrame()->UnregisterHook(SV_FrameHandler);

    instance_ = nullptr;
}

sigslot::signal<ClientConnectingEvent>& ServerEventsManager::on_client_connecting() noexcept
{
    return client_connecting_;
}

sigslot::signal<ClientId>& ServerEventsManager::on_client_putinserver() noexcept
{
    return client_putinserver_;
}

sigslot::signal<ClientId>& ServerEventsManager::on_client_first_frame() noexcept
{
    return client_first_frame_;
}

sigslot::signal<>& ServerEventsManager::on_frame() noexcept
{
    return frame_;
}

sigslot::signal<ClientId>& ServerEventsManager::on_player_think_post() noexcept
{
    return player_think_post_;
}

sigslot::signal<ClientId>& ServerEventsManager::on_client_disconnected() noexcept
{
    return client_disconnected_;
}

sigslot::signal<ClientDropConnectionEvent>& ServerEventsManager::on_client_drop_connection() noexcept
{
    return client_drop_connection_;
}

sigslot::signal<MessageBeginPostEvent>& ServerEventsManager::on_message_begin_post() noexcept
{
    return message_begin_post_;
}

sigslot::signal<>& ServerEventsManager::on_message_end_post() noexcept
{
    return message_end_post_;
}

sigslot::signal<ClientId>& ServerEventsManager::on_send_server_info() noexcept
{
    return send_server_info_;
}

sigslot::signal<ServerActivatedEvent>& ServerEventsManager::on_server_activated() noexcept
{
    return server_activated_;
}

sigslot::signal<>& ServerEventsManager::on_amxx_plugins_loaded() noexcept
{
    return amxx_plugins_loaded_;
}

void ServerEventsManager::PlayerPostThinkHandler(cssdk::Edict* pEntity)
{
    ClientId client = type_conversion::IndexOfEntity(pEntity);

    auto it = players_.find(client);
    if (it != players_.end())
    {
        InternalData& data = it->second;

        if (data.need_first_frame_trigger)
        {
            client_first_frame_(client);
            data.need_first_frame_trigger = false;
        }
    }

    player_think_post_(client);
}

void ServerEventsManager::ClientDropConnectionHandler(cssdk::IGameClient* client, bool crash, const char* buf)
{
    ClientId client_id = client->GetId() + 1;

    client_drop_connection_(ClientDropConnectionEvent{client_id, crash, buf});
    players_.erase(client_id);
}

void ServerEventsManager::ClientPutInServerHandler(cssdk::Edict* client)
{
    ClientId client_id = type_conversion::IndexOfEntity(client);

    auto it = players_.find(client_id);
    if (it != players_.end())
    {
        it->second.need_first_frame_trigger = true;
    }

    client_putinserver_(client_id);
}

void ServerEventsManager::ServerActivatePostHandler(cssdk::Edict* edict_list, int edict_count, int client_max)
{
    players_.clear();
    server_activated_(ServerActivatedEvent{edict_list, edict_count, client_max});
}

void ServerEventsManager::ClientConnectPostHandler(cssdk::Edict* client, const char* name, const char* address)
{
    ClientId client_id = type_conversion::IndexOfEntity(client);
    players_.try_emplace(client_id, InternalData{});

    client_connecting_(ClientConnectingEvent{client_id, name, address});
}

sigslot::signal<AddToFullPackEvent>& ServerEventsManager::on_add_to_full_pack() noexcept
{
    return add_to_full_pack_;
}

ServerEventsManager* ServerEventsManager::instance_ = nullptr;
