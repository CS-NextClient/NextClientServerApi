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
#include <cssdk/public/os_defs.h>
#include <metamod/api.h>
#include <mhooks/common/mhookchain.h>
#include <type_traits>

namespace mhooks
{
    template <typename Signature>
    class MetaApiMHookChain;

    template <typename Ret, typename... Args>
    class MetaApiMHookChain<Ret(Args...)> final : public MHookChain<MetaApiMHookChain<Ret(Args...)>, Ret, Args...>
    {
        using MHookChainType = MHookChain<MetaApiMHookChain<Ret(Args...)>, Ret, Args...>;
        using HooksContainerType = typename MHookChainType::HooksContainerType;
        using HooksContainerSizeType = typename MHookChainType::HooksContainerSizeType;

        template <typename, typename, typename...>
        friend class MHookChain;

        HooksContainerType enabled_hooks_{};
        HooksContainerType disabled_hooks_{};
        mutable HooksContainerSizeType current_{};

    public:
        /**
         * @brief Invokes the next hook callback in the chain.
        */
        ATTR_MINSIZE Ret CallNext(Args... args) const
        {
            if (current_ < enabled_hooks_.size()) {
                return enabled_hooks_[current_++].second(*this, args...);
            }

            if constexpr (std::is_same_v<Ret, metamod::Status>) {
                return static_cast<Ret>(metamod::Status::Ok);
            }
            else {
                return Ret();
            }
        }
    };
}
#endif
