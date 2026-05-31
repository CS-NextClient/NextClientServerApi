/*
 *  Copyright (C) 2020 the_hunter
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifdef HAS_AMXX_LIB
#include "../cleanup.h"
#include "../hookchain_manager.h"
#include <cssdk/public/utils.h>
#include <mhooks/amxxapi/amxxapi.h>
#include <cassert>

using namespace core;
using namespace cssdk;
using namespace mhooks;
using namespace mhooks::detail;

namespace
{
    struct CheckGame;
    struct Attach;
    struct PluginsLoaded;
    struct PluginsUnloading;
    struct PluginsUnloaded;
    struct Detach;
    struct ClientAuthorized;

    template <typename T, typename Ret = void, typename... Args>
    HookChainManager<AmxxApiMHookChain<Ret(Args...)>>* g_hookchain_manager{};

    template <typename T, typename Ret, typename... Args>
    ATTR_MINSIZE void OnHookChainManagerEmpty()
    {
        delete g_hookchain_manager<T, Ret, Args...>;
        g_hookchain_manager<T, Ret, Args...> = nullptr;
    }

    template <typename T, typename Ret, typename... Args>
    ATTR_MINSIZE FORCEINLINE MHook* CreateHook(const Delegate<Ret(const AmxxApiMHookChain<Ret(Args...)>&, Args...)>& callback,
                                               const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        auto*& hookchain_manager = g_hookchain_manager<T, Ret, Args...>;

        if (hookchain_manager == nullptr) {
            hookchain_manager = new HookChainManager{AmxxApiMHookChain<Ret(Args...)>{}, OnHookChainManagerEmpty<T, Ret, Args...>};
        }

        auto* const hook = new MHook{priority, enable};
        hookchain_manager->AddHook(hook, callback);

        return hook;
    }
}

#ifdef AMXX_CHECK_GAME
ATTR_MINSIZE amxx::GameStatus AMXX_CHECK_GAME(const char* const game) // NOLINT(bugprone-reserved-identifier)
{
    auto status = amxx::GameStatus::Ok;

    if (auto*& manager = g_hookchain_manager<CheckGame, amxx::GameStatus, const char*>;
        manager != nullptr && game != nullptr) {
        status = manager->StartChain(game);
    }

    return status;
}
#endif

#ifdef AMXX_ATTACH
ATTR_MINSIZE amxx::Status AMXX_ATTACH() // NOLINT(bugprone-reserved-identifier)
{
    auto status = amxx::Status::Ok;

    if (auto*& manager = g_hookchain_manager<Attach, amxx::Status>; manager != nullptr) {
        status = manager->StartChain();
    }

    return status;
}
#endif

#ifdef AMXX_PLUGINS_LOADED
ATTR_MINSIZE void AMXX_PLUGINS_LOADED() // NOLINT(bugprone-reserved-identifier)
{
    if (g_hookchain_manager<PluginsLoaded> != nullptr) {
        g_hookchain_manager<PluginsLoaded>->StartChain();
    }
}
#endif

#ifdef AMXX_PLUGINS_UNLOADING
ATTR_MINSIZE void AMXX_PLUGINS_UNLOADING() // NOLINT(bugprone-reserved-identifier)
{
    if (g_hookchain_manager<PluginsUnloading> != nullptr) {
        g_hookchain_manager<PluginsUnloading>->StartChain();
    }
}
#endif

#ifdef AMXX_PLUGINS_UNLOADED
ATTR_MINSIZE void AMXX_PLUGINS_UNLOADED() // NOLINT(bugprone-reserved-identifier)
{
    if (g_hookchain_manager<PluginsUnloaded> != nullptr) {
        g_hookchain_manager<PluginsUnloaded>->StartChain();
    }
}
#endif

#ifdef AMXX_DETACH
ATTR_MINSIZE void AMXX_DETACH() // NOLINT(bugprone-reserved-identifier)
{
    if (g_hookchain_manager<Detach> != nullptr) {
        g_hookchain_manager<Detach>->StartChain();
    }

    DestroyHooks();
}
#endif

namespace
{
    NOINLINE void OnClientAuthorized(const int index, const char* const auth)
    {
        if (auto*& manager = g_hookchain_manager<ClientAuthorized, void, int, const char*>;
            manager != nullptr && auth != nullptr && IsClient(index)) {
            manager->StartChain(index, auth);
        }
    }

    void OnClientAuthorizedHookNotify(const MHook* const, const MHookNotice notice)
    {
        const auto* const manager = g_hookchain_manager<ClientAuthorized, void, int, const char*>;
        assert(manager != nullptr);

        if (notice == MHookNotice::Enable) {
            if (manager->HookChainInstance().EnabledHooksCount() == 1) {
                amxx::RegisterAuthFunc(OnClientAuthorized);
            }
        }
        else if (notice == MHookNotice::Disable && manager->HookChainInstance().EnabledHooksCount() == 0) {
            amxx::UnregisterAuthFunc(OnClientAuthorized);
        }
    }
}

namespace mhooks
{
    MHook* MHookAmxxCheckGame(const AmxxCheckGameMCallback callback, const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<CheckGame>(callback, priority, enable);
    }

    MHook* MHookAmxxAttach(const AmxxAttachMCallback callback, const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<Attach>(callback, priority, enable);
    }

    MHook* MHookAmxxPluginsLoaded(const AmxxPluginsLoadedMCallback callback,
                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<PluginsLoaded>(callback, priority, enable);
    }

    MHook* MHookAmxxPluginsUnloading(const AmxxPluginsUnloadingMCallback callback,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<PluginsUnloading>(callback, priority, enable);
    }

    MHook* MHookAmxxPluginsUnloaded(const AmxxPluginsUnloadedMCallback callback,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<PluginsUnloaded>(callback, priority, enable);
    }

    MHook* MHookAmxxDetach(const AmxxDetachMCallback callback, const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<Detach>(callback, priority, enable);
    }

    MHook* MHookAmxxClientAuthorized(const AmxxClientAuthorizedMCallback callback,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        auto* const hook = CreateHook<ClientAuthorized>(callback, priority, false);

        hook->Subscribe(DELEGATE_ARG<OnClientAuthorizedHookNotify>);
        hook->Toggle(enable);

        return hook;
    }
}
#endif
