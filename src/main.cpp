#include <elpplog.h>
#include <kangaru/container.hpp>
#include <natives/natives.h>

#include "rehlds_api_provider.h"
#include "services/HealthNext.h"
#include "services/NextClientApi.h"
#include "services/game_events/GameEventsManager.h"
#include "services/CvarSandbox.h"
#include "services/PrivatePrecache.h"
#include "services/ViewmodelFX.h"
#include "services/DeathMsgWpnIcon.h"
#include "services/HudSprite.h"
#include "services/Miscellaneous.h"
#include "services/RehldsHookchainsService.h"

std::unique_ptr<kgr::container> g_RootContainer;

char g_ModuleVersion[] {MODULE_VERSION};
cvar_t cvar_nclapi_version = {"nclapi_version", g_ModuleVersion, FCVAR_SERVER | FCVAR_SPONLY};

void Initialize()
{
    ConfigureElppLogger();

    if (!RehldsApi_Init())
    {
        return;
    }

    g_RootContainer = std::make_unique<kgr::container>();
    g_RootContainer->emplace<RehldsHookchainsService>(g_RehldsHookchains);
    g_RootContainer->service<NextClientApiService>();
    g_RootContainer->service<GameEventsManagerService>();
    g_RootContainer->service<NclmProtocolService>();
    g_RootContainer->service<CvarSandboxService>();
    g_RootContainer->service<PrivatePrecacheService>();
    g_RootContainer->service<ViewmodelFXService>();
    g_RootContainer->service<DeathMsgWpnIconService>();
    g_RootContainer->service<HudSpriteService>();
    g_RootContainer->service<MiscellaneousService>();
    g_RootContainer->service<HealthNextService>();

    CVAR_REGISTER(&cvar_nclapi_version);

    AddNatives_All();

    MF_PrintSrvConsole("[%s] Successfully loaded, version %s\n", MODULE_NAME, MODULE_VERSION);
}

void Deinitialize()
{
    g_RootContainer.reset();
}

void OnAmxxAttach()
{
    Initialize();
}

void OnAmxxDetach()
{
    Deinitialize();
}

void GameShutdown()
{
    Deinitialize();
}
