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
#include <core/strings/examination.h>
#include <core/type_traits.h>
#include <cssdk/common/cvar.h>
#include <cssdk/public/os_defs.h>
#include <metamod/engine.h>
#include <cassert>

#ifdef GCC_COMPILER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace core::cvar
{
    /**
     * @brief Registers a console variable (CVar).
    */
    cssdk::CVar* Register(const char* name, const char* value, int flags = 0);

    /**
     * @brief Returns \c true if a console variable with the specified name is registered.
    */
    [[nodiscard]] inline bool Exists(const char* const name)
    {
        assert(!str::IsNullOrWhiteSpace(name));
        return metamod::engine::CvarGetPointer(name) != nullptr;
    }

    /**
     * @brief Returns the value of a console variable cast to the specified type.
    */
    template <typename T>
    [[nodiscard]] T GetValue(const cssdk::CVar* const cvar)
    {
        assert(cvar != nullptr);

        if constexpr (std::is_same_v<T, float>) {
            return cvar->value;
        }
        else if constexpr (std::is_same_v<T, const char*>) {
            assert(cvar->string != nullptr);
            return cvar->string;
        }
        else if constexpr (type_traits::IsString<T>()) {
            assert(cvar->string != nullptr);
            return std::string{cvar->string};
        }
        else if constexpr (type_traits::IsStringView<T>()) {
            assert(cvar->string != nullptr);
            return std::string_view{cvar->string};
        }
        else {
            static_assert(type_traits::IsPod<T>(), "Unsupported type provided.");
            return static_cast<T>(cvar->value);
        }
    }

    /**
     * @brief Returns the value of a console variable cast to the specified type.
    */
    template <typename T>
    [[nodiscard]] T GetValue(const char* const name)
    {
        assert(Exists(name));
        return GetValue<T>(metamod::engine::CvarGetPointer(name));
    }
}

#ifdef GCC_COMPILER
#pragma GCC diagnostic pop
#endif
#endif
