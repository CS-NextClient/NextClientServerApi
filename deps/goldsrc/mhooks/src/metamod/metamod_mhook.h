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

#include <mhooks/common/mhook.h>

namespace mhooks::detail
{
    class MetamodMHook final : public MHook
    {
    public:
        MetamodMHook(const cssdk::HookChainPriority priority, const bool enable, const bool post)
            : MHook(priority, enable), post_(post)
        {
        }

        [[nodiscard]] bool Post() const noexcept
        {
            return post_;
        }

    private:
        const bool post_;
    };
}
