#include "NclmProtocol.h"

#include <easylogging++.h>

#include <amxx/api.h>
#include <core/regamedll_api.h>
#include <core/rehlds_api.h>

#include "nclm_proto.h"
#include "NclmSizeBufWriter.h"

using namespace core;

namespace
{
    bool IsValidHwidFormat(const std::string& hwid)
    {
        if (hwid.size() != NCLM_HWID_SIZE)
        {
            return false;
        }

        for (const char c : hwid)
        {
            if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
                return false;
        }
        return true;
    }
} // namespace

NclmProtocol::NclmProtocol(ServerEventsManager& server_events_manager)
{
    if (instance_)
    {
        throw std::runtime_error("NclmProtocol instance already exists");
    }

    instance_ = this;

    rehlds_api::HookChains()->HandleNetCommand()->RegisterHook(nclm_proto::HandleNetCommandHandler);

    server_events_manager.on_send_server_info().connect(&NclmProtocol::SendServerInfoHandler, this);
    server_events_manager.on_server_activated().connect(&NclmProtocol::ServerActivatedHandler, this);
    server_events_manager.on_client_drop_connection().connect(&NclmProtocol::ClientDropConnectionHandler, this);
}

NclmProtocol::~NclmProtocol()
{
    rehlds_api::HookChains()->HandleNetCommand()->UnregisterHook(nclm_proto::HandleNetCommandHandler);

    instance_ = nullptr;
}

sigslot::signal<ClientAuthEvent>& NclmProtocol::on_client_auth()
{
    return on_client_auth_;
}

sigslot::signal<HwidReceivedEvent>& NclmProtocol::on_hwid_received()
{
    return on_hwid_received_;
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

        case NCLM_C2S::HARDWARE_ID:
            HardwareIdHandler(client);
            break;
    }
}

void NclmProtocol::VerificationRequestHandler(ClientId client)
{
    std::string rsa_key_version = rehlds_api::Funcs()->msg_read_string();

    if (*rehlds_api::Funcs()->get_msg_bad_read())
    {
        LOG(ERROR) << "badread on " << amxx::GetPlayerName(client);
        return;
    }

    auto it = player_data_.find(client);
    if (it == player_data_.end())
    {
        return;
    }

    VerificationPayload& player_data = it->second;

    if (!player_data.payload.empty())
    {
        return;
    }

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

    std::string client_version = rehlds_api::Funcs()->msg_read_string();
    rehlds_api::Funcs()->msg_read_buf(payload.size(), payload.data());

    if (*rehlds_api::Funcs()->get_msg_bad_read())
    {
        LOG(ERROR) << "badread on " << amxx::GetPlayerName(client);
        return;
    }

    auto it = player_data_.find(client);
    if (it == player_data_.end())
    {
        return;
    }

    const VerificationPayload& verification_payload = it->second;

    if (verification_payload.payload.empty())
    {
        return;
    }

    bool is_verified = verifier_.ValidateReceivedPayload(client, payload, verification_payload);
    if (is_verified)
    {
        on_client_auth_(ClientAuthEvent{client, client_version, true});
    }
}

void NclmProtocol::DeclareVersionHandler(ClientId client)
{
    std::string client_version = rehlds_api::Funcs()->msg_read_string();

    if (*rehlds_api::Funcs()->get_msg_bad_read())
    {
        LOG(ERROR) << "badread on " << amxx::GetPlayerName(client);
        return;
    }

    on_client_auth_(ClientAuthEvent{client, client_version, false});
}

void NclmProtocol::HardwareIdHandler(ClientId client)
{
    std::string hwid = rehlds_api::Funcs()->msg_read_string();

    if (*rehlds_api::Funcs()->get_msg_bad_read())
    {
        LOG(ERROR) << "hwid: badread on " << amxx::GetPlayerName(client);
        return;
    }

    if (!IsValidHwidFormat(hwid))
    {
        LOG(WARNING) << "hwid: invalid format from " << amxx::GetPlayerName(client) << " (len=" << hwid.size() << ")";
        return;
    }

    for (char& c : hwid)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    LOG(INFO) << "hwid: received from " << amxx::GetPlayerName(client) << " [" << hwid << "]";

    on_hwid_received_(HwidReceivedEvent{client, hwid});
}

void NclmProtocol::ClientMessageHandler(cssdk::ReHookHandleNetCommand* hookchain, cssdk::IGameClient* client, cssdk::uint8 opcode)
{
    if (opcode != clc_ncl_message)
    {
        hookchain->CallNext(client, opcode);
        return;
    }

    ClientId client_id = client->GetId() + 1;

    int read_count = *rehlds_api::Funcs()->get_msg_read_count();
    int32_t header = rehlds_api::Funcs()->msg_read_long();

    if (header != NCLM_HEADER && header != NCLM_HEADER_OLD)
    {
        // rollback read count
        if (*rehlds_api::Funcs()->get_msg_bad_read() == TRUE)
        {
            *rehlds_api::Funcs()->get_msg_bad_read() = FALSE;
        }
        *rehlds_api::Funcs()->get_msg_read_count() = read_count;

        hookchain->CallNext(client, opcode);
        return;
    }

    if (header == NCLM_HEADER)
    {
        int32_t nclm_message_size = rehlds_api::Funcs()->msg_read_long();
        NCLM_C2S nclm_opcode = (NCLM_C2S)rehlds_api::Funcs()->msg_read_byte();

        if (*rehlds_api::Funcs()->get_msg_bad_read())
        {
            LOG(ERROR) << "badread opcode on " << amxx::GetPlayerName(client_id);
            return;
        }

        // the actual message size includes the message size and the opcode,
        // we must subtract them because we read them earlier
        int32_t full_message_size = *rehlds_api::Funcs()->get_msg_read_count() + nclm_message_size - sizeof(int32_t) - sizeof(uint8_t);

        NclMessageHandler(client_id, nclm_opcode);

        int32_t* read_count_ptr = rehlds_api::Funcs()->get_msg_read_count();
        if (*read_count_ptr < full_message_size)
        {
            *read_count_ptr = full_message_size;
        }
    }
    else if (header == NCLM_HEADER_OLD)
    {
        NCLM_C2S nclm_opcode = (NCLM_C2S)rehlds_api::Funcs()->msg_read_byte();

        if (*rehlds_api::Funcs()->get_msg_bad_read())
        {
            LOG(ERROR) << "badread opcode on " << amxx::GetPlayerName(client_id);
            return;
        }

        NclMessageHandler(client_id, nclm_opcode);
    }
}

void NclmProtocol::ServerActivatedHandler(ServerActivatedEvent event)
{
    player_data_.clear();
    for (ClientId i = 1; i <= event.client_max; i++)
    {
        player_data_[i] = VerificationPayload();
    }

    verifier_.ReloadPublicKeys();
}

void NclmProtocol::SendServerInfoHandler(ClientId client)
{
    auto it = player_data_.find(client);
    if (it == player_data_.end())
    {
        return;
    }

    std::vector<uint8_t>& payload = it->second.encrypted_payload;

    if (!payload.empty())
    {
        SendVerificationPayload(client, payload);
        payload.clear();
    }
}

void NclmProtocol::ClientDropConnectionHandler(ClientDropConnectionEvent event)
{
    auto it = player_data_.find(event.client_id);
    if (it == player_data_.end())
    {
        return;
    }

    it->second.payload.clear();
}

void NclmProtocol::SendVerificationPayload(ClientId client, const std::vector<uint8_t>& payload)
{
    cssdk::SizeBuf* channel = GetClientReliableChannel(client);
    if (channel == nullptr)
    {
        return;
    }

    NclmSizeBufWriter(channel, 0x140).WriteByte(static_cast<int>(NCLM_S2C::VERIFICATION_PAYLOAD)).WriteBuf(payload).Send();
}

cssdk::SizeBuf* NclmProtocol::GetClientReliableChannel(ClientId client)
{
    if (client <= 0 || client > rehlds_api::ServerStatic()->GetMaxClients())
    {
        return nullptr;
    }

    cssdk::IGameClient* cl = rehlds_api::ServerStatic()->GetGameClient(client - 1);
    if (cl == nullptr)
    {
        return nullptr;
    }

    cssdk::INetChan* netchan = cl->GetNetChannel();
    if (netchan == nullptr)
    {
        return nullptr;
    }

    return netchan->GetMessageBuf();
}

NclmProtocol* NclmProtocol::instance_ = nullptr;
