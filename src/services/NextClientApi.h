#pragma once
#include <unordered_map>
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>
#include "IDeprecatedAPI.h"
#include "INextClientAPI.h"
#include "INextClientInfo.h"
#include "NextClientVersion.h"
#include "PlayerData.h"
#include "game_events/GameEventsManager.h"
#include "nclm_protocol/NclmProtocol.h"
#include "nclm_protocol/events.h"

class NextClientApi : public sigslot::observer, public INextClientInfo
{
    std::unordered_map<ClientId, PlayerData> players_;
    int forward_api_ready_{};
    int forward_hwid_received_{};

    GameEventsManager& game_events_manager_;
    NclmProtocol& nclm_protocol_;

public:
    explicit NextClientApi(GameEventsManager& game_events_manager, NclmProtocol& nclm_protocol);

    bool IsClientReady(ClientId client) override;
    NextClientVersionLegacy GetNextClientVersionLegacy(ClientId client);
    NextClientUsing IsClientUsingNextClient(ClientId client);
    bool GetNextClientVersion(ClientId client, NextClientVersion& version_out) override;
    int GetSupportedFeatures(ClientId client) override;

    bool GetClientHwid(ClientId client, std::string& hwid_out);

private:
    bool ParseVersion(const std::string& in, NextClientVersion& out);

    void ServerActivatedHandler(ServerActivatedEvent event);
    void ClientAuthHandler(ClientAuthEvent event);
    void HwidReceivedHandler(HwidReceivedEvent event);
    void PlayerPostThinkHandler(ClientId client);
    void ClientConnectedHandler(ClientId client);
    void ClientConnectingHandler(ClientConnectingEvent event);
};

struct NextClientApiService :
    kgr::single_service<NextClientApi, kgr::dependency<GameEventsManagerService, NclmProtocolService>>,
    kgr::overrides<INextClientInfoService>, kgr::final{};
