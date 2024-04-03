#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <memory>

#include <events.h>
#include <EventManager.h>
#include <stddef.h>

#include "CvarSandbox.h"
#include "PrivatePrecache.h"
#include "Verificator.h"
#include "ViewmodelFX.h"
#include "HealthNext.h"
#include "NclmProtocol.h"
#include "DeathMsgWpnIcon.h"

class NextClientApi : public INextClientAPI, public IEventClientVerificated
{
    struct PlayerData {
        ncl_deprecated::NextClientVersion deprecated_client_version;
        std::unique_ptr<NextClientVersion> client_version;
        bool is_using_nextclient;
        bool is_api_ready;
        bool is_verificated;
        bool is_first_frame;
    };
	std::unordered_map<int, PlayerData> players_;

	std::unique_ptr<EventManager> event_manager_;

    int forward_api_ready_{};
	int message_SetFOVEx_{};
    int message_HudSprite_{};

	std::shared_ptr<::CvarSandbox> cvar_sandbox_;
	std::shared_ptr<::PrivatePrecache> private_precache_;
	std::shared_ptr<::ViewmodelFX> viewmodel_fx_;
	std::shared_ptr<Verificator> verificator_;
    std::shared_ptr<HealthNext> health_next_;
    std::shared_ptr<NclmProtocol> nclm_protocol_;
    std::shared_ptr<::DeathMsgWpnIcon> deathmsg_wpn_icon;

public:
    explicit NextClientApi();

	IViewmodelFX* ViewmodelFX() override;
	IPrivatePrecache* PrivatePrecache() override;
	ICvarSandbox* CvarSandbox() override;
    IDeathMsgWpnIcon* DeathMsgWpnIcon() override;

	bool ClientIsReady(int client) override;
	void ClientSetFOV(int client, int fov, float lerpTime) override;

	ncl_deprecated::NextClientVersion deprecated_GetNextClientVersion(int client) override;
    NextClientUsing ClientIsUsingNextClient(int client) override;
    bool GetNextClientVersion(int client, NextClientVersion& version) override;
    int GetSupportedFeatures(int client) override;

    void SendHudSprite(
        int client,
        int channel,
        const char* spritePath,
        const uint8_t spriteColor[3],
        uint8_t alpha,
        int frame,
        float frameRate,
        float inTime,
        float holdTime,
        float outTime,
        float x,
        float y,
        const int spriteRect[4],
        float scaleX,
        float scaleY,
        int renderMode
    ) override;

    void SendHudSpriteFullScreen(
        int client,
        int channel,
        const char* spritePath,
        const uint8_t spriteColor[3],
        uint8_t alpha,
        int frame,
        float frameRate,
        float inTime,
        float holdTime,
        float outTime,
        int renderMode
    ) override;

    void ClearHudSprite(int client, int channel) override;

    // events
	void OnPlayerPostThink(int client);
	void OnClientDisconnect(int client);
	void OnClientConnect(int client);
    void OnClientPutInServer(int client);
	void OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax);
	void OnHandleNCLMessage(int, NCLM_C2S opcode);
    void OnMessageBeginPost(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
    void OnMessageEndPost();
    void OnSendServerInfo(int client);
    void OnClientEstablishConnection(int client);
    void OnClientDropConnection(int client, bool crash, const char* reason);
    void OnAmxxPluginsLoaded();

    void OnClientVerificated(int client, std::string clientVersion, std::string rsaKeyVersion) override; 
};
