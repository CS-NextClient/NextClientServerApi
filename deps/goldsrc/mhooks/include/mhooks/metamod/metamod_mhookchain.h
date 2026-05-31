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
#include <mhooks/common/mhookchain.h>

namespace mhooks
{
    template <typename Signature>
    class MetamodMHookChain;

    template <typename Ret, typename... Args>
    class MetamodMHookChain<Ret(Args...)> final : public MHookChain<MetamodMHookChain<Ret(Args...)>, Ret, Args...>
    {
        using MHookChainType = MHookChain<MetamodMHookChain<Ret(Args...)>, Ret, Args...>;
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
        ATTR_OPTIMIZE_HOT_INLINE Ret CallNext(Args... args) const
        {
            if (current_ < enabled_hooks_.size()) {
                return enabled_hooks_[current_++].second(*this, args...);
            }

            return Ret();
        }
    };
}
#endif
