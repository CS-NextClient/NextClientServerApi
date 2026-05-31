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

#ifdef HAS_METAMOD_LIB
#include "../cleanup.h"
#include "../hookchain_manager.h"
#include <mhooks/metaapi/metaapi.h>
#include <mhooks/metaapi/metaapi_mhookchain.h>
#include <cassert>

using namespace core;
using namespace cssdk;
using namespace mhooks;
using namespace mhooks::detail;

namespace
{
    struct Init;
    struct Query;
    struct Attach;
    struct Detach;

    template <typename T, typename Ret = void, typename... Args>
    HookChainManager<MetaApiMHookChain<Ret(Args...)>>* g_hookchain_manager{};

    template <typename T, typename Ret, typename... Args>
    ATTR_MINSIZE void OnHookChainManagerEmpty()
    {
        delete g_hookchain_manager<T, Ret, Args...>;
        g_hookchain_manager<T, Ret, Args...> = nullptr;
    }

    template <typename T, typename Ret, typename... Args>
    ATTR_MINSIZE FORCEINLINE MHook* CreateHook(const Delegate<Ret(const MetaApiMHookChain<Ret(Args...)>&, Args...)>& callback,
                                               const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        auto*& hookchain_manager = g_hookchain_manager<T, Ret, Args...>;

        if (hookchain_manager == nullptr) {
            hookchain_manager = new HookChainManager{MetaApiMHookChain<Ret(Args...)>{}, OnHookChainManagerEmpty<T, Ret, Args...>};
        }

        auto* const hook = new MHook{priority, enable};
        hookchain_manager->AddHook(hook, callback);

        return hook;
    }
}

namespace mhooks
{
    MHook* MHookMetaInit(const MetaInitMCallback callback, const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<Init>(callback, priority, enable);
    }

    MHook* MHookMetaQuery(const MetaQueryMCallback callback, const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<Query>(callback, priority, enable);
    }

    MHook* MHookMetaAttach(const MetaAttachMCallback callback, const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<Attach>(callback, priority, enable);
    }

    MHook* MHookMetaDetach(const MetaDetachMCallback callback, const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        return CreateHook<Detach>(callback, priority, enable);
    }
}

#if defined(META_INIT) && defined(HAS_AMXX_LIB)
ATTR_MINSIZE void META_INIT() // NOLINT(bugprone-reserved-identifier)
{
    if (g_hookchain_manager<Init> != nullptr) {
        g_hookchain_manager<Init>->StartChain();
    }
}
#endif

#ifdef META_QUERY
ATTR_MINSIZE void META_QUERY() // NOLINT(bugprone-reserved-identifier)
{
    if (g_hookchain_manager<Query> != nullptr) {
        g_hookchain_manager<Query>->StartChain();
    }
}
#endif

#ifdef META_ATTACH
ATTR_MINSIZE metamod::Status META_ATTACH() // NOLINT(bugprone-reserved-identifier)
{
    auto status = metamod::Status::Ok;

    if (auto*& manager = g_hookchain_manager<Attach, metamod::Status>; manager != nullptr) {
        status = manager->StartChain();
    }

    return status;
}
#endif

ATTR_MINSIZE void META_DETACH() // NOLINT(bugprone-reserved-identifier)
{
    if (g_hookchain_manager<Detach> != nullptr) {
        g_hookchain_manager<Detach>->StartChain();
    }

    DestroyHooks();
}
#endif
