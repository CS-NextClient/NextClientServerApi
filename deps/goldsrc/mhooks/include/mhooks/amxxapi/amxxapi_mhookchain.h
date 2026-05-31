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

#ifdef HAS_AMXX_LIB
#include <amxx/api.h>
#include <cssdk/public/os_defs.h>
#include <mhooks/common/mhookchain.h>
#include <type_traits>

namespace mhooks
{
    template <typename Signature>
    class AmxxApiMHookChain;

    template <typename Ret, typename... Args>
    class AmxxApiMHookChain<Ret(Args...)> final : public MHookChain<AmxxApiMHookChain<Ret(Args...)>, Ret, Args...>
    {
        using MHookChainType = MHookChain<AmxxApiMHookChain<Ret(Args...)>, Ret, Args...>;
        using HooksContainerType = typename MHookChainType::HooksContainerType;
        using HooksContainerSizeType = typename MHookChainType::HooksContainerSizeType;

        template <typename, typename, typename...>
        friend class MHookChain;

    public:
        /**
         * @brief Invokes the next hook callback in the chain.
        */
        ATTR_MINSIZE Ret CallNext(Args... args) const
        {
            if (current_ < enabled_hooks_.size()) {
                return enabled_hooks_[current_++].second(*this, args...);
            }

            if constexpr (std::is_same_v<Ret, amxx::Status>) {
                return static_cast<Ret>(amxx::Status::Ok);
            }
            else if constexpr (std::is_same_v<Ret, amxx::GameStatus>) {
                return static_cast<Ret>(amxx::GameStatus::Ok);
            }
            else {
                return Ret();
            }
        }

    private:
        HooksContainerType enabled_hooks_{};
        HooksContainerType disabled_hooks_{};
        mutable HooksContainerSizeType current_{};
    };
}
#endif
