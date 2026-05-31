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
#include <core/cvar.h>

using namespace cssdk;
using namespace metamod;

namespace core::cvar
{
    CVar* Register(const char* const name, const char* const value, const int flags)
    {
        auto* cvar = engine::CvarGetPointer(name);

        if (cvar) {
            assert(!str::IsNullOrEmpty(cvar->name));
            engine::CvarDirectSet(cvar, value);

            return cvar;
        }

        static CVar new_cvar{};
        new_cvar.SetName(name).SetString(value).SetFlags(flags);

        engine::CvarRegister(&new_cvar);
        cvar = engine::CvarGetPointer(new_cvar.name);

        if (cvar) {
            engine::CvarDirectSet(cvar, value);
        }

        return cvar;
    }
}
#endif
