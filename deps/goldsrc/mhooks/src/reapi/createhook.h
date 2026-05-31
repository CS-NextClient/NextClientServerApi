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

#pragma once

#if defined(HAS_CSSDK_LIB) && defined(HAS_CORE_LIB)
#include "../hookchain_manager.h"
#include <core/delegate.h>
#include <cssdk/public/os_defs.h>
#include <mhooks/common/mhook.h>
#include <mhooks/reapi/reapi_mhookchain.h>
#include <cassert>

namespace mhooks::detail
{
    template <typename OrigChain>
    OrigChain* g_orig_chain{};

    template <typename T, typename Registrar>
    Registrar* g_registrar{};

    template <cssdk::HookChainPriority Priority, typename T, typename OrigChain, typename Ret, typename... Args>
    HookChainManager<ReApiMHookChain<OrigChain, Ret(Args...)>>* g_hookchain_manager{};

    template <cssdk::HookChainPriority Priority, typename T, typename OrigChain, typename Ret, typename... Args>
    ATTR_OPTIMIZE_HOT Ret ReHookCallback(OrigChain* const orig_chain, Args... args)
    {
        g_orig_chain<OrigChain> = orig_chain;
        return g_hookchain_manager<Priority, T, OrigChain, Ret, Args...>->StartChain(args...);
    }

    template <cssdk::HookChainPriority Priority, typename T, typename Registrar, typename OrigChain, typename Ret, typename... Args>
    ATTR_MINSIZE void OnHookChainManagerEmpty()
    {
        if (g_registrar<T, Registrar> != nullptr) {
            g_registrar<T, Registrar>->UnregisterHook(ReHookCallback<Priority, T, OrigChain, Ret, Args...>);
        }

        delete g_hookchain_manager<Priority, T, OrigChain, Ret, Args...>;
        g_hookchain_manager<Priority, T, OrigChain, Ret, Args...> = nullptr;
    }

    template <cssdk::HookChainPriority Priority, typename T, typename Registrar, typename OrigChain, typename Ret, typename... Args>
    ATTR_MINSIZE void OnHookNotify(const MHook* const, const MHookNotice notice)
    {
        if (notice != MHookNotice::Enable && notice != MHookNotice::Disable) {
            return;
        }

        assert((g_hookchain_manager<Priority, T, OrigChain, Ret, Args...> != nullptr));
        const auto& chain = g_hookchain_manager<Priority, T, OrigChain, Ret, Args...>->HookChainInstance();

        if (notice == MHookNotice::Enable) {
            if (chain.EnabledHooksCount() == 1) {
                g_registrar<T, Registrar>->RegisterHook(ReHookCallback<Priority, T, OrigChain, Ret, Args...>, Priority);
            }
        }
        else {
            if (chain.EnabledHooksCount() == 0) {
                g_registrar<T, Registrar>->UnregisterHook(ReHookCallback<Priority, T, OrigChain, Ret, Args...>);
            }
        }
    }

    template <cssdk::HookChainPriority Priority, typename T, typename Registrar, typename OrigChain, typename Ret, typename... Args>
    ATTR_MINSIZE void AddHook(MHook* const hook, const core::Delegate<Ret(const ReApiMHookChain<OrigChain, Ret(Args...)>&, Args...)>& callback)
    {
        assert(hook);
        assert(!!callback);

        if (g_hookchain_manager<Priority, T, OrigChain, Ret, Args...> == nullptr) {
            g_hookchain_manager<Priority, T, OrigChain, Ret, Args...> = new HookChainManager{
                ReApiMHookChain<OrigChain, Ret(Args...)>{g_orig_chain<OrigChain>},
                OnHookChainManagerEmpty<Priority, T, Registrar, OrigChain, Ret, Args...>};
        }

        g_hookchain_manager<Priority, T, OrigChain, Ret, Args...>->AddHook(hook, callback);
        hook->Subscribe<OnHookNotify<Priority, T, Registrar, OrigChain, Ret, Args...>>();
    }

    template <typename T, typename Registrar, typename OrigChain, typename Ret, typename... Args>
    ATTR_MINSIZE FORCEINLINE MHook* CreateHook(Registrar* registrar,
                                               const core::Delegate<Ret(const ReApiMHookChain<OrigChain, Ret(Args...)>&, Args...)>& callback,
                                               const cssdk::HookChainPriority priority, const bool enable)
    {
        assert(registrar);

        g_registrar<T, Registrar> = registrar;
        auto* const hook = new MHook{priority, false};

        switch (priority) {
        case cssdk::HookChainPriority::Uninterruptable:
            AddHook<cssdk::HookChainPriority::Uninterruptable, T, Registrar, OrigChain, Ret, Args...>(hook, callback);
            break;

        case cssdk::HookChainPriority::High:
            AddHook<cssdk::HookChainPriority::High, T, Registrar, OrigChain, Ret, Args...>(hook, callback);
            break;

        case cssdk::HookChainPriority::Normal:
            AddHook<cssdk::HookChainPriority::Normal, T, Registrar, OrigChain, Ret, Args...>(hook, callback);
            break;

        case cssdk::HookChainPriority::Medium:
            AddHook<cssdk::HookChainPriority::Medium, T, Registrar, OrigChain, Ret, Args...>(hook, callback);
            break;

        case cssdk::HookChainPriority::Low:
            AddHook<cssdk::HookChainPriority::Low, T, Registrar, OrigChain, Ret, Args...>(hook, callback);
            break;
        }

        assert(hook);
        hook->Toggle(enable);

        return hook;
    }
}
#endif
