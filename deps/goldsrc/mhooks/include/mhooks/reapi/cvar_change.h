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

#if defined(HAS_CSSDK_LIB) && defined(HAS_CORE_LIB)
#include <mhooks/reapi/rehlds.h>
#include <cassert>
#include <string>
#include <string_view>

using CVarChangeMCallback =
    core::Delegate<void(const cssdk::CVar* cvar, std::string_view old_value, std::string& new_value)>;

namespace mhooks
{
    /**
     * @brief Creates a hook for when a cvar's value is changed.
    */
    ATTR_MINSIZE MHook* MHookCVarChange(const cssdk::CVar* cvar, CVarChangeMCallback callback, bool enable = true);

    /**
     * @brief Creates a hook for when a cvar's value is changed.
    */
    ATTR_MINSIZE inline MHook* MHookCVarChange(const char* const name, const CVarChangeMCallback callback,
                                               const bool enable = true)
    {
        assert(!!callback);

        assert(name != nullptr);
        assert(cssdk::g_engine_funcs.cvar_get_pointer != nullptr);

        const auto* const cvar = cssdk::g_engine_funcs.cvar_get_pointer(name);
        assert(cvar != nullptr);

        return MHookCVarChange(cvar, callback, enable);
    }
}
#endif
