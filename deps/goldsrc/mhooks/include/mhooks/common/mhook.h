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

#include <core/observer.h>
#include <cssdk/common/hook_chain_priority.h>
#include <cssdk/public/os_defs.h>
#include <memory>

namespace mhooks
{
    enum class MHookNotice
    {
        Enable,
        Disable,
        Destroy
    };

    class MHook : public core::Observable<const MHook*, MHookNotice>
    {
        mutable bool destroy_at_detach_;
        cssdk::HookChainPriority priority_;

    protected:
        bool enabled_;

    public:
        /**
         * @brief Constructor.
        */
        MHook(cssdk::HookChainPriority priority, bool enable);

        /**
         * @brief Move constructor.
        */
        MHook(MHook&&) noexcept = default;

        /**
         * @brief Copy constructor.
        */
        MHook(const MHook&) = delete;

        /**
         * @brief Destructor.
        */
        ~MHook() override;

        /**
         * @brief Enables hook.
        */
        virtual void Enable();

        /**
         * @brief Disables hook.
        */
        virtual void Disable();

        /**
         * @brief Toggles the hook state (enables or disables).
        */
        void Toggle(bool enable) noexcept;

        /**
         * @brief Set to \c true to automatically destroy this hook when this library is detached, \c false otherwise.
        */
        ATTR_MINSIZE void DestroyAtDetach(bool destroy) const;

        /**
         * @brief Move assignment operator.
        */
        MHook& operator=(MHook&&) noexcept = default;

        /**
         * @brief Copy assignment operator.
        */
        MHook& operator=(const MHook&) = delete;

        /**
         * @brief Returns \c true if the hook is enabled; \c false otherwise.
        */
        [[nodiscard]] bool IsEnabled() const noexcept
        {
            return enabled_;
        }

        /**
         * @brief Returns the hook priority.
        */
        [[nodiscard]] cssdk::HookChainPriority Priority() const noexcept
        {
            return priority_;
        }

        /**
         * @brief Returns \c true if this hook will automatically be destroyed when this library is detached,
         * \c false otherwise.
        */
        [[nodiscard]] bool DestroyAtDetach() const noexcept
        {
            return destroy_at_detach_;
        }

        /**
         * @brief Wraps a raw hook pointer in a \c std::unique_ptr<MHook>
        */
        [[nodiscard]] std::unique_ptr<MHook> Unique() noexcept
        {
            DestroyAtDetach(false);
            return std::unique_ptr<MHook>(this);
        }

        /**
         * @brief Wraps a raw hook pointer in a \c std::unique_ptr<const MHook>.
        */
        [[nodiscard]] std::unique_ptr<const MHook> Unique() const noexcept
        {
            DestroyAtDetach(false);
            return std::unique_ptr<const MHook>(this);
        }

        /**
         * @brief Destroys the specified hook.
        */
        static void Destroy(MHook*& hook)
        {
            delete hook;
            hook = nullptr;
        }

        /**
         * @brief Destroys the specified hook.
        */
        static void Destroy(const MHook*& hook)
        {
            delete hook;
            hook = nullptr;
        }
    };
}
