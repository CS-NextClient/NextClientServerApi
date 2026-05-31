#include "amxx/api.h"
#include "metamod/engine.h"

#include <easylogging++.h>
#include <elpplog.h>
#include <kangaru/container.hpp>

#include <core/amxx_access.h>
#include <core/regamedll_api.h>
#include <core/messages.h>
#include <core/rehlds_api.h>
#include <metamod/gamedll_hooks.h>
#include <mhooks/amxxapi/amxxapi.h>

#include "natives/natives.h"
#include "services/HealthNext.h"
#include "services/NextClientApi.h"
#include "services/server_events/ServerEventsManager.h"
#include "services/mod_events/ModEventsManager.h"
#include "services/CvarSandbox.h"
#include "services/PrivatePrecache.h"
#include "services/ViewmodelFX.h"
#include "services/DeathMsgWpnIcon.h"
#include "services/HudSprite.h"
#include "services/Miscellaneous.h"
#include "services/StringRegistry.h"
#include "services/ncl_entities/EntitySync.h"
#include "services/ncl_entities/PlayerEntitySync.h"
#include "services/ncl_entities/WeaponEntitySync.h"

cssdk::CVar cvar_nclapi_version = {"nclapi_version", amxx::MODULE_VERSION, cssdk::FCVAR_SERVER | cssdk::FCVAR_SP_ONLY};

std::unique_ptr<kgr::container> g_RootContainer;

bool Initialize()
{
    if (!core::rehlds_api::Init())
    {
        amxx::PrintConsole("[%s] Failed to initialize ReHLDS API\n", amxx::MODULE_LOG_TAG);
        return false;
    }

    if (!core::regamedll_api::Init())
    {
        amxx::PrintConsole("[%s] Failed to initialize ReGameDLL API\n", amxx::MODULE_LOG_TAG);
        return false;
    }

    ConfigureElppLogger();

    core::amxx_access::Init();
    core::type_conversion::Init();

    g_RootContainer = std::make_unique<kgr::container>();
    g_RootContainer->service<ServerEventsManagerService>();
    g_RootContainer->service<ModEventsManagerService>();
    g_RootContainer->service<NclmProtocolService>();
    g_RootContainer->service<NextClientApiService>();
    g_RootContainer->service<StringRegistryService>();
    g_RootContainer->service<CvarSandboxService>();
    g_RootContainer->service<PrivatePrecacheService>();
    g_RootContainer->service<ViewmodelFXService>();
    g_RootContainer->service<DeathMsgWpnIconService>();
    g_RootContainer->service<HudSpriteService>();
    g_RootContainer->service<MiscellaneousService>();
    g_RootContainer->service<HealthNextService>();
    g_RootContainer->service<EntitySyncService>();
    g_RootContainer->service<PlayerNclEntitySyncService>();
    g_RootContainer->service<WeaponNclEntitySyncService>();

    metamod::engine::CvarRegister(&cvar_nclapi_version);

    AddNatives_All();

    LOG(INFO) << amxx::MODULE_NAME << " Successfully loaded, version " << amxx::MODULE_VERSION;

    return true;
}

void Deinitialize()
{
    g_RootContainer.reset();
}

void AmxxPluginsLoadedHandler()
{
    if (!ServerEventsManager::instance_)
    {
        return;
    }

    ServerEventsManager::instance_->amxx_plugins_loaded_();
}

void GameShutdownHandler()
{
    Deinitialize();
}

void AmxxDetachHandler()
{
    Deinitialize();
}

amxx::Status AmxxAttachHandler()
{
    bool result = Initialize();

    return result ? amxx::Status::Ok : amxx::Status::Failed;
}

void Main()
{
    mhooks::MHookAmxxAttach(core::DELEGATE_ARG<AmxxAttachHandler>);
    mhooks::MHookAmxxDetach(core::DELEGATE_ARG<AmxxDetachHandler>);
    mhooks::MHookAmxxPluginsLoaded(core::DELEGATE_ARG<AmxxPluginsLoadedHandler>);
    metamod::gamedll::HookGameShutdown(GameShutdownHandler, false);
}
