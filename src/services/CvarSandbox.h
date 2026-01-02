#pragma once
#include <string>
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>
#include "SandboxCvar.h"
#include "game_events/GameEventsManager.h"

class CvarSandbox : public sigslot::observer
{
	GameEventsManager& game_events_manager_;

	int message_sandbox_cvar_{};
	bool is_message_building_{};

public:
	explicit CvarSandbox(GameEventsManager& game_events_manager);

	void Begin(ClientId client);
	void End();
	void WriteCvar(SandboxCvar cvar, const std::string& value);

private:
	void ServerActivatedHandler(ServerActivatedEvent server_activated_event);
};

struct CvarSandboxService : kgr::single_service<CvarSandbox, kgr::dependency<GameEventsManagerService>> {};
