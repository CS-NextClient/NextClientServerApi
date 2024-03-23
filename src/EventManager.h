#pragma once

#include <vector>
#include <memory>
#include "events.h"

class EventManager : public IEventPlayerPostThink,
                     public IEventClientDisconnect,
                     public IEventClientConnect,
                     public IEventClientPutInServer,
                     public IEventClientFirstFrame,
                     public IEventServerActivated,
                     public IEventMessageBeginPost,
                     public IEventMessageEndPost,
                     public IEventClientVerificated,
                     public IEventSendServerinfo,
                     public IEventNclmVerificationRequest, public IEventNclmVerificationResponse,
                     public IEventClientEstablishConnection, public IEventClientDropConnection
{
    std::vector<std::shared_ptr<IEventPlayerPostThink>> player_post_think_listeners_;
    std::vector<std::shared_ptr<IEventClientDisconnect>> client_disconnect_listeners_;
    std::vector<std::shared_ptr<IEventClientConnect>> client_connect_listeners_;
    std::vector<std::shared_ptr<IEventClientPutInServer>> client_putinserver_listeners_;
    std::vector<std::shared_ptr<IEventClientFirstFrame>> client_first_frame_listeners_;
    std::vector<std::shared_ptr<IEventServerActivated>> server_activated_listeners_;
    std::vector<std::shared_ptr<IEventMessageBeginPost>> message_begin_post_listeners_;
    std::vector<std::shared_ptr<IEventMessageEndPost>> message_end_post_listeners_;
    std::vector<std::shared_ptr<IEventClientVerificated>> client_verificated_listeners_;
    std::vector<std::shared_ptr<IEventNclmVerificationRequest>> nclm_verification_request_listeners_;
    std::vector<std::shared_ptr<IEventNclmVerificationResponse>> nclm_verification_response_listeners_;
    std::vector<std::shared_ptr<IEventSendServerinfo>> send_server_info_listeners_;
    std::vector<std::shared_ptr<IEventClientEstablishConnection>> client_establish_connection_listeners_;
    std::vector<std::shared_ptr<IEventClientDropConnection>> client_drop_connection_listeners_;

public:
    template<typename T>
    void AddEventListener(std::shared_ptr<T> listener)
    {
        if constexpr (std::is_base_of_v<IEventPlayerPostThink, T>) player_post_think_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventClientDisconnect, T>) client_disconnect_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventClientConnect, T>) client_connect_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventClientPutInServer, T>) client_putinserver_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventClientFirstFrame, T>) client_first_frame_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventServerActivated, T>) server_activated_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventMessageBeginPost, T>) message_begin_post_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventMessageEndPost, T>) message_end_post_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventClientVerificated, T>) client_verificated_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventNclmVerificationRequest, T>) nclm_verification_request_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventNclmVerificationResponse, T>) nclm_verification_response_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventSendServerinfo, T>) send_server_info_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventClientEstablishConnection, T>) client_establish_connection_listeners_.push_back(listener);
        if constexpr (std::is_base_of_v<IEventClientDropConnection, T>) client_drop_connection_listeners_.push_back(listener);
    }

    void OnPlayerPostThink(int client) override;
    void OnClientDisconnect(int client) override;
    void OnClientConnect(int client) override;
    void OnClientPutInServer(int client) override;
    void OnClientFirstFrame(int client) override;
    void OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax) override;
    void OnMessageBeginPost(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed) override;
    void OnMessageEndPost() override;
    void OnClientVerificated(int client, std::string clientVersion, std::string rsaKeyVersion) override;
    void OnNclmVerificationRequest(int client, std::string rsaKeyVersion) override;
    void OnNclmVerificationResponse(int client, std::string clientVersion, std::vector<uint8_t> payload) override;
    void OnSendServerInfo(int client) override;
    void OnClientEstablishConnection(int client) override;
    void OnClientDropConnection(int client, bool crash, const char* reason) override;
};
