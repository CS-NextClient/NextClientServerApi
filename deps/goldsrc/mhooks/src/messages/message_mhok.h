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
#include "consts.h"
#include <core/strings/compare.h>
#include <core/strings/examination.h>
#include <metamod/api.h>
#include <metamod/utils.h>
#include <mhooks/common/mhook.h>
#include <mhooks/metamod/engine.h>
#include <cassert>
#include <string>
#include <utility>

namespace mhooks::detail
{
    class MessageMHook final : public MHook
    {
        int message_id_;
        std::string message_name_;
        std::unique_ptr<MHook> reg_user_message_hook_post_{};

    public:
        MessageMHook(const cssdk::HookChainPriority priority, const bool enable, std::string message_name)
            : MHook(priority, enable), message_id_(-1), message_name_(std::move(message_name))
        {
            assert(!core::str::IsEmptyOrWhiteSpace(message_name_));

            if (metamod::utils::detail::funcs != nullptr) {
                message_id_ = metamod::utils::GetUserMsgId(message_name_.c_str());
            }

            if (!IsValidMessageId(message_id_)) {
                reg_user_message_hook_post_ =
                    MHookEngineRegUserMessage(
                        {core::DELEGATE_ARG<&MessageMHook::OnRegUserMessageHookPost>, this},
                        true, cssdk::HookChainPriority::Uninterruptable)
                        ->Unique();
            }
        }

        ~MessageMHook() override = default;
        MessageMHook(MessageMHook&&) = delete;
        MessageMHook(const MessageMHook&) = delete;
        MessageMHook& operator=(MessageMHook&&) = delete;
        MessageMHook& operator=(const MessageMHook&) = delete;

        void Enable() override
        {
            if (IsValidMessageId(message_id_)) {
                MHook::Enable();
            }
            else {
                enabled_ = true;
            }
        }

        void Disable() override
        {
            if (IsValidMessageId(message_id_)) {
                MHook::Disable();
            }
            else {
                enabled_ = false;
            }
        }

        [[nodiscard]] int MessageId() const noexcept
        {
            return message_id_;
        }

        [[nodiscard]] const std::string& MessageName() const noexcept
        {
            return message_name_;
        }

    private:
        int OnRegUserMessageHookPost(const EngineRegUserMessageMChain& chain, const char* const name, const int size)
        {
            if (!core::str::IsNullOrEmpty(name) && core::str::IEquals(name, message_name_.c_str())) {
                message_id_ = metamod::GetRetValue<int>();
                reg_user_message_hook_post_.reset();

                if (enabled_) {
                    enabled_ = false;
                    Enable();
                }
            }

            return chain.CallNext(name, size);
        }
    };
}
#endif
