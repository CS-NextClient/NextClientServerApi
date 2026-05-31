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

#include <cssdk/public/os_defs.h>
#include <mhooks/common/mhook.h>
#include <cassert>
#include <type_traits>
#include <utility>

namespace mhooks::detail
{
    template <typename HookChain>
    class HookChainManager final
    {
        using OnEmptyType = std::add_pointer_t<void()>;
        using CallbackType = typename HookChain::CallbackType;

        HookChain hook_chain_;
        OnEmptyType on_empty_;
        bool empty_;

    public:
        HookChainManager(HookChain hook_chain, OnEmptyType on_empty);

        ~HookChainManager() = default;
        HookChainManager(HookChainManager&&) = delete;
        HookChainManager(const HookChainManager&) = delete;
        HookChainManager& operator=(HookChainManager&&) = delete;
        HookChainManager& operator=(const HookChainManager&) = delete;

        ATTR_MINSIZE void AddHook(MHook* hook, const CallbackType& callback);

        template <typename... Args>
        ATTR_OPTIMIZE_HOT_INLINE typename HookChain::ReturnType StartChain(Args... args);

        [[nodiscard]] const HookChain& HookChainInstance() const noexcept
        {
            return hook_chain_;
        }

    private:
        void OnHookNotify(const MHook* hook, MHookNotice notice);
    };

    template <typename HookChain>
    void HookChainManager<HookChain>::OnHookNotify(const MHook* const hook, const MHookNotice notice)
    {
        assert(hook != nullptr);

        switch (notice) {
        case MHookNotice::Enable:
            hook_chain_.EnableHook(hook);
            break;

        case MHookNotice::Disable:
            hook_chain_.DisableHook(hook);
            break;

        case MHookNotice::Destroy:
            hook_chain_.RemoveHook(hook);

            if (hook_chain_.TotalHooksCount() == 0) {
                empty_ = hook_chain_.Current() != 0;

                if (!empty_) {
                    on_empty_();
                }
            }
            break;
        }
    }

    template <typename HookChain>
    void HookChainManager<HookChain>::AddHook(MHook* const hook, const CallbackType& callback)
    {
        assert(hook != nullptr);
        assert(!!callback);

        empty_ = false;
        hook->Subscribe<&HookChainManager::OnHookNotify>(this);

        if (hook->IsEnabled()) {
            hook_chain_.AddEnabledHook({hook, callback});
        }
        else {
            hook_chain_.AddDisabledHook({hook, callback});
        }
    }

    // ReSharper disable once CppNotAllPathsReturnValue
    // ReSharper disable once CppRedundantInlineSpecifier
    template <typename HookChain>
    template <typename... Args>
    inline typename HookChain::ReturnType HookChainManager<HookChain>::StartChain(Args... args)
    {
        if constexpr (std::is_void_v<typename HookChain::ReturnType>) {
            hook_chain_.CallNext(args...);
            hook_chain_.Current() = 0;

            if (empty_) {
                on_empty_();
            } // cppcheck-suppress missingReturn
        }
        else {
            auto result = hook_chain_.CallNext(args...);
            hook_chain_.Current() = 0;

            if (empty_) {
                on_empty_();
            }

            return result;
        }
    }

    template <typename HookChain>
    HookChainManager<HookChain>::HookChainManager(HookChain hook_chain, const OnEmptyType on_empty)
        : hook_chain_(std::move(hook_chain)), on_empty_(on_empty), empty_(false)
    {
        assert(!!on_empty_);
    }
}
