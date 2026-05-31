#include "StringRegistry.h"

#include <easylogging++.h>

#include <core/type_conversion.h>

#include "utils/msg_ex.h"

using namespace core;
using namespace msg_ex;

StringRegistry::StringRegistry(ServerEventsManager& server_events_manager)
{
    server_events_manager.on_server_activated().connect(&StringRegistry::ServerActivatedHandler, this);
    server_events_manager.on_client_connecting().connect(&StringRegistry::ClientConnectingHandler, this);
    server_events_manager.on_client_disconnected().connect(&StringRegistry::ClientDisconnectedHandler, this);
}

uint16_t StringRegistry::GetOrRegister(const std::string& str)
{
    if (str.empty())
    {
        return 0;
    }

    auto it = string_to_id_.find(str);
    if (it != string_to_id_.end())
    {
        return it->second;
    }

    if (next_id_ == 0)
    {
        LOG(ERROR) << "StringRegistry::GetOrRegister: string_id overflow";
        return 0;
    }

    uint16_t new_id = next_id_++;
    string_to_id_[str] = new_id;
    id_to_value_[new_id] = str;
    return new_id;
}

void StringRegistry::EnsureSent(ClientId client, uint16_t string_id)
{
    if (string_id == 0)
    {
        return;
    }

    auto it = id_to_value_.find(string_id);
    if (it == id_to_value_.end())
    {
        return;
    }

    auto& known = client_known_ids_[client];
    if (known.count(string_id))
    {
        return;
    }

    known.insert(string_id);
    SendRegistration(client, string_id, it->second);
}

void StringRegistry::EnsureSentForAll(uint16_t string_id)
{
    if (string_id == 0)
    {
        return;
    }

    auto it = id_to_value_.find(string_id);
    if (it == id_to_value_.end())
    {
        return;
    }

    for (auto& [client_id, known] : client_known_ids_)
    {
        if (!known.count(string_id))
        {
            known.emplace(string_id);
            SendRegistration(client_id, string_id, it->second);
        }
    }
}

void StringRegistry::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_str_reg_ = RegUserMsgSafe("ncl_str_reg", -1);

    string_to_id_.clear();
    id_to_value_.clear();
    next_id_ = 1;
    client_known_ids_.clear();
}

void StringRegistry::ClientDisconnectedHandler(ClientId client)
{
    client_known_ids_.erase(client);
}

void StringRegistry::ClientConnectingHandler(ClientConnectingEvent event)
{
    client_known_ids_[event.client_id] = {};
}

void StringRegistry::SendRegistration(ClientId client, uint16_t string_id, const std::string& str)
{
    if (message_str_reg_ <= 0)
    {
        return;
    }

    cssdk::Edict* player_edict = type_conversion::EdictByIndex(client);
    if (player_edict == nullptr)
    {
        return;
    }

    MessageBegin(cssdk::MessageType::One, message_str_reg_, nullptr, player_edict);
    WriteUShort(string_id);
    WriteString(str.c_str());
    MessageEnd();
}
