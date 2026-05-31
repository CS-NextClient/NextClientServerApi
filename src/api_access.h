#pragma once
#include <kangaru/container.hpp>

#include "services/NextClientApi.h"
#include "services/ViewmodelFX.h"
#include "services/CvarSandbox.h"
#include "services/PrivatePrecache.h"
#include "services/DeathMsgWpnIcon.h"
#include "services/HudSprite.h"
#include "services/Miscellaneous.h"
#include "services/StringRegistry.h"
#include "services/ncl_entities/WeaponEntitySync.h"

extern std::unique_ptr<kgr::container> g_RootContainer;

inline NextClientApi& NAPI()
{
    return g_RootContainer->service<NextClientApiService>();
}

inline StringRegistry& GetStringRegistry()
{
    return g_RootContainer->service<StringRegistryService>();
}

inline ViewmodelFX& GetViewmodelFX()
{
    return g_RootContainer->service<ViewmodelFXService>();
}

inline CvarSandbox& GetCvarSandbox()
{
    return g_RootContainer->service<CvarSandboxService>();
}

inline PrivatePrecache& GetPrivatePrecache()
{
    return g_RootContainer->service<PrivatePrecacheService>();
}

inline DeathMsgWpnIcon& GetDeathMsgWpnIcon()
{
    return g_RootContainer->service<DeathMsgWpnIconService>();
}

inline HudSprite& GetHudSprite()
{
    return g_RootContainer->service<HudSpriteService>();
}

inline Miscellaneous& GetMiscellaneous()
{
    return g_RootContainer->service<MiscellaneousService>();
}

inline WeaponEntitySync& GetWeaponNclEntitySync()
{
    return g_RootContainer->service<WeaponNclEntitySyncService>();
}
