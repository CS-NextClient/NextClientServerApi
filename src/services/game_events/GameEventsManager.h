#pragma once
#include <sigslot/signal.hpp>
#include <kangaru/kangaru.hpp>
#include <amxxmodule.h>
#include <eiface.h>
#include <extdll.h>
#include <model.h>
#include <pm_defs.h>
#include <rehlds_api.h>
#include "services/RehldsHookchainsService.h"
#include "events.h"

class GameEventsManager
{
    friend BOOL ClientConnect(edict_t* pEntity, const char* pszName, const char* pszAddress, char szRejectReason[128]);
    friend void ClientConnectedHandler(IRehldsHook_ClientConnected* hookchain, IGameClient* apiClient);
    friend void ClientPutInServer_Post(edict_t* pEntity);
    friend void PlayerPostThink(edict_t* pEntity);
    friend void ClientDisconnect(edict_t* pEntity);
    friend void SV_DropClientHandler(IRehldsHook_SV_DropClient* hookchain, IGameClient* apiClient, bool crash, const char* buf);
    friend void MessageBegin_Post(int msg_dest, int msg_type, const float* pOrigin, edict_t* ed);
    friend void MessageEnd_Post();
    friend void SV_SendServerinfoHandler(IRehldsHook_SV_SendServerinfo* hookchain, sizebuf_t* msg, IGameClient* apiClient);
    friend void ServerActivate_Post(edict_t* pEdictList, int edictCount, int clientMax);
    friend void OnPluginsLoaded();

    struct InternalData
    {
        bool first_frame{};
    };

    IRehldsHookchains* rehlds_hookchains_;

    sigslot::signal<ClientConnectingEvent> client_connecting_;
    sigslot::signal<ClientId> client_connected_;
    sigslot::signal<ClientId> client_putinserver_;
    sigslot::signal<ClientId> client_first_frame_;
    sigslot::signal<ClientId> player_think_post_;
    sigslot::signal<ClientId> client_disconnected_;
    sigslot::signal<ClientDropConnectionEvent> client_drop_connection_;
    sigslot::signal<MessageBeginPostEvent> message_begin_post_;
    sigslot::signal<> message_end_post_;
    sigslot::signal<ClientId> send_server_info_;
    sigslot::signal<ServerActivatedEvent> server_activated_;
    sigslot::signal<> amxx_plugins_loaded_;

    std::unordered_map<ClientId, InternalData> players_;

    static GameEventsManager* instance_;

public:
    explicit GameEventsManager(IRehldsHookchains* rehlds_hookchains);
    ~GameEventsManager();

    sigslot::signal<ClientConnectingEvent>& on_client_connecting() noexcept;
    sigslot::signal<ClientId>& on_client_connected() noexcept;
    sigslot::signal<ClientId>& on_client_putinserver() noexcept;
    sigslot::signal<ClientId>& on_client_first_frame() noexcept;
    sigslot::signal<ClientId>& on_player_think_post() noexcept;
    sigslot::signal<ClientId>& on_client_disconnected() noexcept;
    sigslot::signal<ClientDropConnectionEvent>& on_client_drop_connection() noexcept;
    sigslot::signal<MessageBeginPostEvent>& on_message_begin_post() noexcept;
    sigslot::signal<>& on_message_end_post() noexcept;
    sigslot::signal<ClientId>& on_send_server_info() noexcept;

    sigslot::signal<ServerActivatedEvent>& on_server_activated() noexcept;
    sigslot::signal<>& on_amxx_plugins_loaded() noexcept;

private:
    void PlayerPostThinkHandler(edict_t* pEntity);
    void ClientDropConnectionHandler(IGameClient* apiClient, bool crash, const char* buf);
    void ClientPutInServerHandler(edict_t* pEntity);
};

struct GameEventsManagerService : kgr::single_service<GameEventsManager, kgr::dependency<RehldsHookchainsService>> {};
