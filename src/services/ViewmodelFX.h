#pragma once
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>

#include "game_events/GameEventsManager.h"

class ViewmodelFX : public sigslot::observer
{
    enum class VFX
    {
        VMFX_RENDERMODE,
        VMFX_RENDERFX,
        VMFX_RENDERAMT,
        VMFX_RENDERCOLOR,
        VMFX_SKIN,
        VMFX_BODY,
    };

    GameEventsManager& game_events_manager_;

    int message_viewmodelFX_{};
    int client_{};
    int bit_state_set_{};
    int bit_state_reset_{};
    bool is_message_building_{};

    struct VFXState
    {
        int rendermode{};
        int renderamt{};
        color24 rendercolor{};
        int renderfx{};
        int skin{};
        int body{};
    } stateVFX_{};

public:
    explicit ViewmodelFX(GameEventsManager& game_events_manager);

    void Begin(int client);
    void End();
    void WriteRenderMode(int rendermode);
    void WriteRenderAmt(int renderamt);
    void WriteRenderColor(int r, int g, int b);
    void WriteRenderFX(int renderfx);
    void WriteSkin(int skin);
    void WriteBody(int body);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);

    void StateSet(VFX state);
    bool StateIsSet(VFX state) const;
    void StateReset(VFX state);
};

struct ViewmodelFXService : kgr::single_service<ViewmodelFX, kgr::dependency<GameEventsManagerService>> {};
