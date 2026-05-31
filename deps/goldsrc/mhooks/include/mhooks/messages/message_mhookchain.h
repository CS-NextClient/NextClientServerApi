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
#include <metamod/engine_hooks.h>
#include <mhooks/common/mhookchain.h>
#include <mhooks/messages/message_args.h>

namespace mhooks
{
    class MessageMHookChain final : public MHookChain<MessageMHookChain, bool, cssdk::MessageType&,
                                                      int, float*&, cssdk::Edict*&, MessageArgs&>
    {
        template <typename, typename, typename...>
        friend class MHookChain;

        HooksContainerType enabled_hooks_{};
        HooksContainerType disabled_hooks_{};
        mutable HooksContainerSizeType current_{};
        ATTR_OPTIMIZE_HOT [[nodiscard]] bool FindNext(int id) const noexcept;

    public:
        /**
         * @brief Invokes the next hook callback in the chain.
        */
        ATTR_OPTIMIZE_HOT_INLINE bool CallNext(cssdk::MessageType& type, const int id, float*& origin,
                                               cssdk::Edict*& client, MessageArgs& args) const
        {
            if (FindNext(id)) {
                return enabled_hooks_[current_++].second(*this, type, id, origin, client, args);
            }

            return false;
        }
    };
}
#endif
