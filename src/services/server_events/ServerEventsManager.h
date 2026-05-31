#pragma once
#include <sigslot/signal.hpp>
#include <kangaru/kangaru.hpp>

#include <cssdk/public/rehlds.h>

#include "server_events.h"
#include "events.h"

class ServerEventsManager
{
public:
    struct InternalData
    {
        bool need_first_frame_trigger{};
    };

private:
    sigslot::signal<ClientConnectingEvent> client_connecting_;
    sigslot::signal<ClientId> client_putinserver_;
    sigslot::signal<ClientId> client_first_frame_;
    sigslot::signal<> frame_;
    sigslot::signal<ClientId> player_think_post_;
    sigslot::signal<ClientId> client_disconnected_;
    sigslot::signal<ClientDropConnectionEvent> client_drop_connection_;
    sigslot::signal<MessageBeginPostEvent> message_begin_post_;
    sigslot::signal<> message_end_post_;
    sigslot::signal<ClientId> send_server_info_;
    sigslot::signal<ServerActivatedEvent> server_activated_;
    sigslot::signal<> amxx_plugins_loaded_;
    sigslot::signal<AddToFullPackEvent> add_to_full_pack_;

public:
    std::unordered_map<ClientId, InternalData> players_;

private:
    static ServerEventsManager* instance_;

public:
    explicit ServerEventsManager();
    ~ServerEventsManager();

    sigslot::signal<ClientConnectingEvent>& on_client_connecting() noexcept;
    sigslot::signal<ClientId>& on_client_putinserver() noexcept;
    sigslot::signal<ClientId>& on_client_first_frame() noexcept;
    sigslot::signal<>& on_frame() noexcept;
    sigslot::signal<ClientId>& on_player_think_post() noexcept;
    sigslot::signal<ClientId>& on_client_disconnected() noexcept;
    sigslot::signal<ClientDropConnectionEvent>& on_client_drop_connection() noexcept;
    sigslot::signal<MessageBeginPostEvent>& on_message_begin_post() noexcept;
    sigslot::signal<>& on_message_end_post() noexcept;
    sigslot::signal<ClientId>& on_send_server_info() noexcept;

    sigslot::signal<ServerActivatedEvent>& on_server_activated() noexcept;
    sigslot::signal<>& on_amxx_plugins_loaded() noexcept;
    sigslot::signal<AddToFullPackEvent>& on_add_to_full_pack() noexcept;

private:
    void PlayerPostThinkHandler(cssdk::Edict* pEntity);
    void ClientDropConnectionHandler(cssdk::IGameClient* client, bool crash, const char* buf);
    void ClientPutInServerHandler(cssdk::Edict* client);
    void ServerActivatePostHandler(cssdk::Edict* edict_list, int edict_count, int client_max);
    void ClientConnectPostHandler(cssdk::Edict* client, const char* name, const char* address);

    // clang-format off
    friend void sv_events::SV_DropClientHandler(cssdk::ReHookSvDropClient* hookchain,cssdk::IGameClient* client, bool crash, const char* buf);
    friend void sv_events::SV_SendServerInfoHandler(cssdk::ReHookSvSendServerInfo* hookchain, cssdk::SizeBuf* msg, cssdk::IGameClient* client);
    friend void sv_events::SV_FrameHandler(cssdk::ReHookSvFrame* hookchain);
    friend cssdk::qboolean sv_events::ClientConnectPostMetamodHandler(cssdk::Edict* client, const char* name, const char* address, char* reject_reason);
    friend void sv_events::ClientDisconnectPostMetamodHandler(cssdk::Edict* client);
    friend void sv_events::ClientPutInServerPostMetamodHandler(cssdk::Edict* client);
    friend void sv_events::PlayerPostThinkPostMetamodHandler(cssdk::Edict* client);
    friend void sv_events::MessageBeginPostMetamodHandler(cssdk::MessageType msg_type, int msg_id, const float* origin, cssdk::Edict* client);
    friend void sv_events::MessageEndPostMetamodHandler();
    friend void sv_events::ServerActivatePostMetamodHandler(cssdk::Edict* edict_list, int edict_count, int client_max);
    friend void AmxxPluginsLoadedHandler();
    // clang-format on
};

struct ServerEventsManagerService : kgr::single_service<ServerEventsManager>
{};
