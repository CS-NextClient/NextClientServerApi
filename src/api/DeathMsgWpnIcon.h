#pragma once

#include <events.h>
#include <unordered_map>
#include <vector>

class DeathMsgWpnIcon : public IDeathMsgWpnIcon,
						public IEventServerActivated {
	int message_deathmsg_wpn_icon;

public:
	void OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax) override;
	void SetIconForNextMessage(const std::string& sprite, int frame, int rendermode, 
		int r, int g, int b, int a, int recipient_id) override;
};