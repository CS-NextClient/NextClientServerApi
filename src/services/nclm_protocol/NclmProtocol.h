#pragma once
#include <vector>

#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>

#include <cssdk/public/rehlds.h>

#include "nclm_proto.h"
#include "events.h"
#include "Verifier.h"
#include "services/server_events/ServerEventsManager.h"

namespace nclm_proto
{
    void HandleNetCommandHandler(cssdk::ReHookHandleNetCommand* hookchain, cssdk::IGameClient* client, cssdk::uint8 opcode);
}

class NclmProtocol : public sigslot::observer
{
    Verifier verifier_;
    sigslot::signal<ClientAuthEvent> on_client_auth_;
    sigslot::signal<HwidReceivedEvent> on_hwid_received_;
    std::unordered_map<ClientId, VerificationPayload> player_data_;

    static NclmProtocol* instance_;

public:
    explicit NclmProtocol(ServerEventsManager& server_events_manager);
    ~NclmProtocol() override;

    sigslot::signal<ClientAuthEvent>& on_client_auth();
    sigslot::signal<HwidReceivedEvent>& on_hwid_received();

private:
    void NclMessageHandler(ClientId client, NCLM_C2S opcode, int32_t payload_size);
    void VerificationRequestHandler(ClientId client);
    void VerificationChallengeHandler(ClientId client);
    void DeclareVersionHandler(ClientId client);
    void HardwareIdHandler(ClientId client, int32_t payload_size);
    void ClientMessageHandler(cssdk::ReHookHandleNetCommand* hookchain, cssdk::IGameClient* client, cssdk::uint8 opcode);
    void ServerActivatedHandler(ServerActivatedEvent event);
    void SendServerInfoHandler(ClientId);
    void ClientDropConnectionHandler(ClientDropConnectionEvent event);

    void SendServerHello(ClientId client);
    void SendVerificationPayload(ClientId client, const std::vector<uint8_t>& payload);

    cssdk::SizeBuf* GetClientReliableChannel(ClientId client);

    friend void nclm_proto::HandleNetCommandHandler(
        cssdk::ReHookHandleNetCommand* hookchain,
        cssdk::IGameClient* client,
        cssdk::uint8 opcode
    );
};

struct NclmProtocolService : kgr::single_service<NclmProtocol, kgr::dependency<ServerEventsManagerService>>
{};
