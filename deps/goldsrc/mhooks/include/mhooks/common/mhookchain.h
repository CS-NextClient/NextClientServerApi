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

#include <core/delegate.h>
#include <cssdk/public/os_defs.h>
#include <mhooks/common/mhook.h>
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace mhooks
{
    namespace detail
    {
        template <typename Chain>
        class HookChainManager;
    }

    template <typename Implementation, typename Ret, typename... Args>
    class MHookChain
    {
        template <typename>
        friend class detail::HookChainManager;

        [[nodiscard]] auto* Impl()
        {
            return static_cast<Implementation*>(this); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
        }

        [[nodiscard]] const auto* Impl() const
        {
            return static_cast<const Implementation*>(this); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
        }

    public:
        using ReturnType = Ret;
        using CallbackType = core::Delegate<Ret(const Implementation&, Args...)>;
        using HooksContainerElementType = std::pair<const MHook*, CallbackType>;
        using HooksContainerType = std::vector<HooksContainerElementType>;
        using HooksContainerSizeType = typename HooksContainerType::size_type;

        /**
         * @brief Constructor.
        */
        MHookChain() = default;

        /**
         * @brief Destructor.
        */
        virtual ~MHookChain() = default;

        /**
         * @brief Move constructor.
        */
        MHookChain(MHookChain&&) = default;

        /**
         * @brief Copy constructor.
        */
        MHookChain(const MHookChain&) = default;

        /**
         * @brief Move assignment operator.
        */
        MHookChain& operator=(MHookChain&&) = default;

        /**
         * @brief Copy assignment operator.
        */
        MHookChain& operator=(const MHookChain&) = default;

        /**
         * @brief Returns the number of enabled hooks in the chain.
        */
        [[nodiscard]] auto EnabledHooksCount() const noexcept
        {
            return Impl()->enabled_hooks_.size();
        }

        /**
         * @brief Returns the number of disabled hooks in the chain.
        */
        [[nodiscard]] auto DisabledHooksCount() const noexcept
        {
            return Impl()->disabled_hooks_.size();
        }

        /**
         * @brief Returns the number of hooks (enabled + disabled) in the chain.
        */
        [[nodiscard]] auto TotalHooksCount() const noexcept
        {
            return EnabledHooksCount() + DisabledHooksCount();
        }

    private:
        [[nodiscard]] auto& Current() noexcept
        {
            return Impl()->current_;
        }

        [[nodiscard]] auto& EnabledHooks() noexcept
        {
            return Impl()->enabled_hooks_;
        }

        [[nodiscard]] auto& DisabledHooks() noexcept
        {
            return Impl()->disabled_hooks_;
        }

        void AddEnabledHook(const HooksContainerElementType& hook);
        void AddDisabledHook(const HooksContainerElementType& hook);

        void EnableHook(const MHook* hook);
        void DisableHook(const MHook* hook);
        void RemoveHook(const MHook* hook);

        static auto FindHookPredicate(const MHook* const hook) noexcept
        {
            assert(hook != nullptr);

            return [hook](const auto& element) {
                return element.first == hook;
            };
        }
    };

    template <typename Implementation, typename Ret, typename... Args>
    void MHookChain<Implementation, Ret, Args...>::AddEnabledHook(const HooksContainerElementType& hook)
    {
        assert(hook.first != nullptr);
        assert(!!hook.second);

        auto& hooks = EnabledHooks();
        const auto count = EnabledHooksCount();
        const auto priority = hook.first->Priority();

        for (HooksContainerSizeType i = 0; i < count; ++i) {
            if (hooks[i].first->Priority() < priority) {
                hooks.insert(hooks.begin() + i, hook);

                if (i < Current()) {
                    ++Current();
                }

                return;
            }
        }

        hooks.emplace_back(hook);
    }

    template <typename Implementation, typename Ret, typename... Args>
    void MHookChain<Implementation, Ret, Args...>::AddDisabledHook(const HooksContainerElementType& hook)
    {
        assert(hook.first != nullptr);
        assert(!!hook.second);

        DisabledHooks().emplace_back(hook);
    }

    template <typename Implementation, typename Ret, typename... Args>
    void MHookChain<Implementation, Ret, Args...>::EnableHook(const MHook* const hook)
    {
        assert(hook != nullptr);
        auto& hooks = DisabledHooks();

        auto it_hook = std::find_if(hooks.begin(), hooks.end(), FindHookPredicate(hook));
        assert(it_hook != hooks.end());

        AddEnabledHook(*it_hook);
        hooks.erase(it_hook);
    }

    template <typename Implementation, typename Ret, typename... Args>
    void MHookChain<Implementation, Ret, Args...>::DisableHook(const MHook* const hook)
    {
        assert(hook != nullptr);
        auto& hooks = EnabledHooks();

        const auto& it_hook = std::find_if(hooks.begin(), hooks.end(), FindHookPredicate(hook));
        assert(it_hook != hooks.end());

        const auto index = static_cast<HooksContainerSizeType>(it_hook - hooks.begin());
        AddDisabledHook(*it_hook);
        hooks.erase(it_hook);

        if (index < Current() && EnabledHooksCount() > 0) {
            --Current();
        }
    }

    template <typename Implementation, typename Ret, typename... Args>
    void MHookChain<Implementation, Ret, Args...>::RemoveHook(const MHook* const hook)
    {
        assert(hook != nullptr);

        if (hook->IsEnabled()) {
            // This should never happen.
            // The hooks to be removed should already be disabled.
            DisableHook(hook);
        }

        auto& hooks = DisabledHooks();
        hooks.erase(std::remove_if(hooks.begin(), hooks.end(), FindHookPredicate(hook)), hooks.end());
    }
}
