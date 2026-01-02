#pragma once
#include <vector>
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>
#include "services/game_events/GameEventsManager.h"
#include "nclm_proto.h"
#include "events.h"
#include "rehlds_events.h"
#include "Verifier.h"

class NclmProtocol : public sigslot::observer
{
    friend void HandleNetCommand(IRehldsHook_HandleNetCommand* hookchain, IGameClient* apiClient, int8 opcode);

    Verifier verifier_;
    sigslot::signal<ClientAuthEvent> on_client_auth_;
    std::unordered_map<ClientId, VerificationPayload> player_data_;

    static NclmProtocol* instance_;

public:
    explicit NclmProtocol(GameEventsManager& game_events_manager);
    ~NclmProtocol() override;

    sigslot::signal<ClientAuthEvent>& on_client_auth();

private:
    void NclMessageHandler(ClientId client, NCLM_C2S opcode);
    void VerificationRequestHandler(ClientId client);
    void VerificationChallengeHandler(ClientId client);
    void DeclareVersionHandler(ClientId client);
    void ClientMessageHandler(IRehldsHook_HandleNetCommand* hookchain, IGameClient* apiClient, int8 opcode);
    void ServerActivatedHandler(ServerActivatedEvent event);
    void SendServerInfoHandler(ClientId);
    void ClientDropConnectionHandler(ClientDropConnectionEvent event);

    void SendVerificationPayload(ClientId client, const std::vector<uint8_t>& payload);

    sizebuf_t* GetClientReliableChannel(ClientId client);
};

struct NclmProtocolService : kgr::single_service<NclmProtocol, kgr::dependency<GameEventsManagerService>> {};
