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

#ifdef HAS_METAMOD_LIB
#include "message_mhok.h"
#include <mhooks/messages/message_mhookchain.h>

namespace mhooks
{
    bool MessageMHookChain::FindNext(const int id) const noexcept
    {
        const auto count = enabled_hooks_.size();

        while (current_ < count) {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
            if (id == static_cast<const detail::MessageMHook*>(enabled_hooks_[current_].first)->MessageId()) {
                return true;
            }

            ++current_;
        }

        return false;
    }
}
#endif
