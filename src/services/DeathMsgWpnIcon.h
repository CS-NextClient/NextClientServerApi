#pragma once
#include <string>
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>
#include "game_events/GameEventsManager.h"

class DeathMsgWpnIcon : public sigslot::observer
{
	int message_deathmsg_wpn_icon_{};

public:
	explicit DeathMsgWpnIcon(GameEventsManager& game_events_manager);

	void SetIconForNextMessage(
		const std::string& sprite,
		int frame,
		int rendermode,
		int r,
		int g,
		int b,
		int a,
		int recipient_id
	);

private:
	void ServerActivatedHandler(ServerActivatedEvent server_activated_event);
};

struct DeathMsgWpnIconService : kgr::single_service<DeathMsgWpnIcon, kgr::dependency<GameEventsManagerService>> {};
