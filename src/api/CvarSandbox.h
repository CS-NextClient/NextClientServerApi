#pragma once

#include <string>
#include <events.h>

class CvarSandbox : public ICvarSandbox,
                    public IEventServerActivated
{
	int message_sandbox_cvar_{};
	bool is_message_building_{};

public:
	CvarSandbox() = default;

	void Begin(int client) override;
	void End() override;
	void WriteCvar(SandboxCvar cvar, const std::string& value) override;

    void OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax) override;
};
