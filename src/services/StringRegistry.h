#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

#include "server_events/ServerEventsManager.h"

class StringRegistry
{
    std::unordered_map<std::string, uint16_t> string_to_id_;
    std::unordered_map<uint16_t, std::string> id_to_value_;
    uint16_t next_id_ = 1;
    std::unordered_map<ClientId, std::unordered_set<uint16_t>> client_known_ids_;
    int message_str_reg_{};

public:
    explicit StringRegistry(ServerEventsManager& server_events_manager);

    uint16_t GetOrRegister(const std::string& str);
    void EnsureSent(ClientId client, uint16_t string_id);
    void EnsureSentForAll(uint16_t string_id);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
    void ClientConnectingHandler(ClientConnectingEvent event);
    void ClientDisconnectedHandler(ClientId client);
    void SendRegistration(ClientId client, uint16_t string_id, const std::string& str);
};

struct StringRegistryService : kgr::single_service<StringRegistry, kgr::dependency<ServerEventsManagerService>>
{};
