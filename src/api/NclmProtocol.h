#pragma once

#include "EventManager.h"
#include <events.h>
#include <vector>
#include <rehlds_api_provider.h>

class NclmProtocol : public IEventHandleNclMessage {
	EventManager* event_manager_;

	void OnVerificationRequest(int client);
	void OnVerificationResponse(int client);

	sizebuf_t* GetClientReliableChannel(int client);
	sizebuf_t* GetClientUnrealibleChannel(int client);

public:
	NclmProtocol(EventManager* event_manager);
	void OnHandleNCLMessage(int client, NCLM_C2S opcode) override;

	void SendVerificationPayload(int client, std::vector<uint8_t> payload);
};