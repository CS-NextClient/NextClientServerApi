#include "NclmProtocol.h"
#include <easylogging++.h>
#include "nclm_proto.h"
#include "NclmSizeBufWriter.h"

NclmProtocol* NclmProtocol::instance_ = nullptr;

NclmProtocol::NclmProtocol(GameEventsManager& game_events_manager)
{
    if (instance_)
        throw std::runtime_error("NclmProtocol instance already exists");

    instance_ = this;

    g_RehldsHookchains->HandleNetCommand()->registerHook(HandleNetCommand);
    game_events_manager.on_send_server_info().connect(&NclmProtocol::SendServerInfoHandler, this);
    game_events_manager.on_server_activated().connect(&NclmProtocol::ServerActivatedHandler, this);
    game_events_manager.on_client_drop_connection().connect(&NclmProtocol::ClientDropConnectionHandler, this);
}

NclmProtocol::~NclmProtocol()
{
    g_RehldsHookchains->HandleNetCommand()->unregisterHook(HandleNetCommand);

    instance_ = nullptr;
}

sigslot::signal<ClientAuthEvent>& NclmProtocol::on_client_auth()
{
    return on_client_auth_;
}

void NclmProtocol::NclMessageHandler(ClientId client, NCLM_C2S opcode)
{
    switch (opcode)
    {
    case NCLM_C2S::VERIFICATION_REQUEST:
        VerificationRequestHandler(client);
        break;

    case NCLM_C2S::VERIFICATION_RESPONSE:
        VerificationChallengeHandler(client);
        break;

    case NCLM_C2S::DECLARE_VERSION_REQUEST:
        DeclareVersionHandler(client);
        break;
    }
}

void NclmProtocol::VerificationRequestHandler(ClientId client)
{
    std::string rsa_key_version = MSG_ReadString();

    if (MSG_IsBadRead())
    {
        LOG(ERROR) << "badread on " << MF_GetPlayerName(client);
        return;
    }

    auto it = player_data_.find(client);
    if (it == player_data_.end())
        return;

    VerificationPayload& player_data = it->second;

    if (!player_data.payload.empty())
        return;

    VerificationPayload verification_payload;
    if (verifier_.TryCreateVerificationPayload(client, rsa_key_version, verification_payload))
    {
        player_data = verification_payload;
    }
}

void NclmProtocol::VerificationChallengeHandler(ClientId client)
{
    std::vector<uint8_t> payload;
    payload.assign(NCLM_VERIF_PAYLOAD_SIZE, 0x00);

    std::string client_version = MSG_ReadString();
    MSG_ReadBuf(payload.size(), payload.data());

    if (MSG_IsBadRead())
    {
        LOG(ERROR) << "badread on " << MF_GetPlayerName(client);
        return;
    }

    auto it = player_data_.find(client);
    if (it == player_data_.end())
        return;

    const VerificationPayload& verification_payload = it->second;

    if (verification_payload.payload.empty())
        return;

    bool is_verified = verifier_.ValidateReceivedPayload(client, payload, verification_payload);
    if (is_verified)
    {
        on_client_auth_(ClientAuthEvent{client, client_version, true});
    }
}

void NclmProtocol::DeclareVersionHandler(ClientId client)
{
    std::string client_version = MSG_ReadString();

    if (MSG_IsBadRead())
    {
        LOG(ERROR) << "badread on " << MF_GetPlayerName(client);
        return;
    }

    on_client_auth_(ClientAuthEvent{client, client_version, false});
}


void NclmProtocol::ClientMessageHandler(IRehldsHook_HandleNetCommand* hookchain, IGameClient* apiClient, int8 opcode)
{
    if (opcode == clc_ncl_message)
    {
        ClientId client = apiClient->GetId() + 1;
        int32_t header = MSG_ReadLong();

        if (header != NCLM_HEADER && header != NCLM_HEADER_OLD)
        {
            // rollback read count
            *g_RehldsFuncs->GetMsgReadCount() -= 4;

            hookchain->callNext(apiClient, opcode);
            return;
        }

        if (header == NCLM_HEADER)
        {
            int32_t nclm_message_size = MSG_ReadLong();
            NCLM_C2S nclm_opcode = (NCLM_C2S)MSG_ReadByte();

            if (MSG_IsBadRead())
            {
                LOG(ERROR) << "badread opcode on " << MF_GetPlayerName(client);
                return;
            }

            // the actual message size includes the message size and the opcode,
            // we must subtract them because we read them earlier
            int32_t full_message_size = *g_RehldsFuncs->GetMsgReadCount() + nclm_message_size - 4 - 1;

            NclMessageHandler(client, nclm_opcode);

            int32_t* read_count = g_RehldsFuncs->GetMsgReadCount();
            if (*read_count < full_message_size)
            {
                *read_count = full_message_size;
            }
        }
        else if (header == NCLM_HEADER_OLD)
        {
            NCLM_C2S nclm_opcode = (NCLM_C2S)MSG_ReadByte();

            if (MSG_IsBadRead())
            {
                LOG(ERROR) << "badread opcode on " << MF_GetPlayerName(client);
                return;
            }

            NclMessageHandler(client, nclm_opcode);
        }
    }

    hookchain->callNext(apiClient, opcode);
}


void NclmProtocol::ServerActivatedHandler(ServerActivatedEvent event)
{
    for (ClientId i = 0; i <= event.clientMax; i++)
    {
        player_data_[i] = VerificationPayload();
    }

    verifier_.ReloadPublicKeys();
}

void NclmProtocol::SendServerInfoHandler(ClientId client)
{
    auto it = player_data_.find(client);
    if (it == player_data_.end())
        return;

    std::vector<uint8_t>& payload = it->second.encrypted_payload;

    if (!payload.empty())
    {
        SendVerificationPayload(client, payload);
        payload.clear();
    }
}

void NclmProtocol::ClientDropConnectionHandler(ClientDropConnectionEvent event)
{
    auto it = player_data_.find(event.client);
    if (it == player_data_.end())
        return;

    it->second.payload.clear();
}

void NclmProtocol::SendVerificationPayload(ClientId client, const std::vector<uint8_t>& payload)
{
    NclmSizeBufWriter message(GetClientReliableChannel(client), 0x140);

    message.WriteByte((int)NCLM_S2C::VERIFICATION_PAYLOAD)
           ->WriteBuf(payload)
           ->Send();
}

sizebuf_t* NclmProtocol::GetClientReliableChannel(ClientId client)
{
    IGameClient* cl = g_RehldsApi->GetServerStatic()->GetClient(client - 1);
    return cl->GetNetChan()->GetMessageBuf();
}
