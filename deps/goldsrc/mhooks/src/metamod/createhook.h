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

#ifdef HAS_METAMOD_LIB
#include "../hookchain_manager.h"
#include "metamod_mhook.h"
#include <core/delegate.h>
#include <cssdk/public/os_defs.h>
#include <metamod/api.h>
#include <mhooks/metamod/metamod_mhookchain.h>
#include <cassert>
#include <type_traits>

namespace mhooks::detail
{
    template <typename T, typename Ret = void, typename... Args>
    HookChainManager<MetamodMHookChain<Ret(Args...)>>* g_hookchain_manager{};

    template <typename T, typename Ret = void, typename... Args>
    HookChainManager<MetamodMHookChain<Ret(Args...)>>* g_hookchain_manager_post{};

    template <typename T, typename Ret = void, typename... Args>
    std::add_pointer_t<void(std::add_pointer_t<Ret(Args...)>, bool)> g_registrar{};

    template <bool Post, typename T, typename Ret, typename... Args>
    ATTR_OPTIMIZE_HOT Ret MetaCallback(Args... args)
    {
        metamod::g_globals->result = MetaResult::Ignored;

        if constexpr (Post) {
            return g_hookchain_manager_post<T, Ret, Args...>->StartChain(args...);
        }
        else {
            return g_hookchain_manager<T, Ret, Args...>->StartChain(args...);
        }
    }

    template <typename T, typename Ret, typename... Args>
    ATTR_MINSIZE void ToggleMetaCallback(const bool enable, const bool post)
    {
        assert((g_registrar<T, Ret, Args...> != nullptr));

        if (enable) {
            if (post) {
                g_registrar<T, Ret, Args...>(MetaCallback<true, T, Ret, Args...>, true);
            }
            else {
                g_registrar<T, Ret, Args...>(MetaCallback<false, T, Ret, Args...>, false);
            }
        }
        else {
            g_registrar<T, Ret, Args...>(nullptr, post);
        }
    }

    template <bool Post, typename T, typename Ret, typename... Args>
    ATTR_MINSIZE void OnHookChainManagerEmpty()
    {
        if (g_registrar<T, Ret, Args...>) {
            g_registrar<T, Ret, Args...>(nullptr, Post);
        }

        if constexpr (Post) {
            delete g_hookchain_manager_post<T, Ret, Args...>;
            g_hookchain_manager_post<T, Ret, Args...> = nullptr;
        }
        else {
            delete g_hookchain_manager<T, Ret, Args...>;
            g_hookchain_manager<T, Ret, Args...> = nullptr;
        }
    }

    template <typename T, typename Ret, typename... Args>
    ATTR_MINSIZE void OnHookNotify(const MHook* const hook, const MHookNotice notice)
    {
        assert(hook != nullptr);
        const auto post = static_cast<const MetamodMHook*>(hook)->Post(); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)

        if (notice == MHookNotice::Enable) {
            ToggleMetaCallback<T, Ret, Args...>(true, post);
        }
        else if (notice == MHookNotice::Disable) {
            const auto* const manager = post ? g_hookchain_manager_post<T, Ret, Args...> : g_hookchain_manager<T, Ret, Args...>;
            assert(manager != nullptr);

            if (const auto& hook_chain = manager->HookChainInstance(); hook_chain.EnabledHooksCount() == 0) {
                ToggleMetaCallback<T, Ret, Args...>(false, post);
            }
        }
    }

    template <typename T, typename Ret, typename... Args>
    ATTR_MINSIZE auto& GetHookchainManager(const bool post)
    {
        auto*& manager = post ? g_hookchain_manager_post<T, Ret, Args...> : g_hookchain_manager<T, Ret, Args...>;

        if (manager == nullptr) {
            if (post) {
                manager = new HookChainManager{MetamodMHookChain<Ret(Args...)>{}, OnHookChainManagerEmpty<true, T, Ret, Args...>};
            }
            else {
                manager = new HookChainManager{MetamodMHookChain<Ret(Args...)>{}, OnHookChainManagerEmpty<false, T, Ret, Args...>};
            }
        }

        return *manager;
    }

    template <typename T, typename Ret, typename... Args>
    ATTR_MINSIZE FORCEINLINE MHook* CreateHook(const std::add_pointer_t<void(std::add_pointer_t<Ret(Args...)>, bool)> registrar,
                                               const core::Delegate<Ret(const MetamodMHookChain<Ret(Args...)>&, Args...)>& callback,
                                               const cssdk::HookChainPriority priority, const bool post, const bool enable)
    {
        assert(registrar);
        assert(!!callback);

        g_registrar<T, Ret, Args...> = registrar;
        auto* const hook = new MetamodMHook{priority, false, post};

        auto& manager = GetHookchainManager<T, Ret, Args...>(post);
        manager.AddHook(hook, callback);

        hook->Subscribe<OnHookNotify<T, Ret, Args...>>();
        hook->Toggle(enable);

        return hook;
    }
}
#endif
