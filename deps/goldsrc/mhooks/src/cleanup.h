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

#include <cssdk/public/os_defs.h>
#include <mhooks/common/mhook.h>
#include <algorithm>
#include <cassert>
#include <vector>

namespace mhooks::detail
{
    inline std::vector<const MHook*>* g_hooks_to_destroy{};

    ATTR_MINSIZE inline void DestroyHooks()
    {
        while (g_hooks_to_destroy && !g_hooks_to_destroy->empty()) {
            delete g_hooks_to_destroy->front();
        }
    }

    ATTR_MINSIZE inline void AddToDestroyList(const MHook* const hook)
    {
        if (g_hooks_to_destroy == nullptr) {
            g_hooks_to_destroy = new std::vector<const MHook*>{};
        }

        assert(hook != nullptr);
        assert(g_hooks_to_destroy != nullptr); // Makes the GCC static analyzer happy.

        g_hooks_to_destroy->push_back(hook);
    }

    ATTR_MINSIZE inline void RemoveFromDestroyList(const MHook* const hook)
    {
        assert(hook != nullptr);

        if (g_hooks_to_destroy != nullptr) {
            g_hooks_to_destroy->erase(
                std::remove(g_hooks_to_destroy->begin(), g_hooks_to_destroy->end(), hook), g_hooks_to_destroy->end());

            if (g_hooks_to_destroy->empty()) {
                delete g_hooks_to_destroy;
                g_hooks_to_destroy = nullptr;
            }
        }
    }
}
