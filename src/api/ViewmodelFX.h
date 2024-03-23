#pragma once

#include <cstring>
#include <events.h>

class ViewmodelFX : public IViewmodelFX,
                    public IEventServerActivated {
	enum class VFX {
		VMFX_RENDERMODE,
		VMFX_RENDERAMT,
		VMFX_RENDERCOLOR,
		VMFX_RENDERFX,
		VMFX_SKIN,
		VMFX_BODY,
	};

	int message_viewmodelFX_{};
	int client_{};
	int bit_state_set_{};
	int bit_state_reset_{};
	bool is_message_building_{};

	struct VFXState {
		int rendermode;
		int renderamt;
		color24 rendercolor;
		int renderfx;
		int skin;
		int body;
	} stateVFX_{};

public:
	ViewmodelFX() = default;

	void Begin(int client) override;
	void End() override;
	void WriteRenderMode(int rendermode) override;
	void WriteRenderAmt(int renderamt) override;
	void WriteRenderColor(int r, int g, int b) override;
	void WriteRenderFX(int renderfx) override;
	void WriteSkin(int skin) override;
	void WriteBody(int body) override;

	void OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax) override;

private:
	void StateSet(VFX state);
	bool StateIsSet(VFX state) const;
	void StateReset(VFX state);
};