#pragma once
#include <string>

#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>

#include "server_events/ServerEventsManager.h"

class DeathMsgWpnIcon : public sigslot::observer
{
    int message_deathmsg_wpn_icon_{};

public:
    explicit DeathMsgWpnIcon(ServerEventsManager& server_events_manager);

    // clang-format off
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
    // clang-format on

private:
    void ServerActivatedHandler(ServerActivatedEvent server_activated_event);
};

struct DeathMsgWpnIconService : kgr::single_service<DeathMsgWpnIcon, kgr::dependency<ServerEventsManagerService>>
{};
