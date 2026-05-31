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
#include "consts.h"
#include <amxx/api.h>
#include <array>
#include <cassert>

namespace mhooks::detail
{
    class BlockMessage final
    {
        std::array<int, MAX_MESSAGES + 1> original_block_{};

    public:
        BlockMessage() noexcept
        {
            original_block_.fill(-1);
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        [[nodiscard]] int GetCurrentBlock(const int id) const
        {
            assert(IsValidMessageId(id));

            auto opt = AMXX_BLOCK_NOT;
            amxx::MessageBlock(AMXX_MSG_BLOCK_GET, id, &opt);

            return opt;
        }

        void SetCurrentBlock(const int id, const bool save_original)
        {
            assert(IsValidMessageId(id));

            if (save_original) {
                SaveOriginalBlock(id);
            }

            auto opt = AMXX_BLOCK_SET;
            amxx::MessageBlock(AMXX_MSG_BLOCK_SET, id, &opt);
        }

        [[nodiscard]] int GetOriginalBlock(const int id) const
        {
            assert(IsValidMessageId(id));
            assert(original_block_[id] != -1);

            return original_block_[id];
        }

        void SetOriginalBlock(const int id) const
        {
            assert(IsValidMessageId(id));

            auto opt = GetOriginalBlock(id);
            amxx::MessageBlock(AMXX_MSG_BLOCK_SET, id, &opt);
        }

        void RestoreOriginalBlock(const int id)
        {
            assert(IsValidMessageId(id));
            assert(original_block_[id] != -1);

            amxx::MessageBlock(AMXX_MSG_BLOCK_SET, id, &original_block_[id]);
            original_block_[id] = -1;
        }

    private:
        void SaveOriginalBlock(const int id)
        {
            assert(IsValidMessageId(id));

            if (original_block_[id] == -1) {
                original_block_[id] = GetCurrentBlock(id);
            }
        }
    };
}
#else
namespace mhooks::detail
{
    struct BlockMessage
    {
        // ReSharper disable once CppMemberFunctionMayBeStatic
        int GetCurrentBlock(const int)
        {
            return 0;
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        void SetCurrentBlock(const int, const bool = true)
        {
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        int GetOriginalBlock(const int)
        {
            return 0;
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        void SetOriginalBlock(const int)
        {
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        void RestoreOriginalBlock(const int)
        {
        }
    };
}
#endif
