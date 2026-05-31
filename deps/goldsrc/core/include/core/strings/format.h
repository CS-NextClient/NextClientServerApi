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

#include <core/strings/consts.h>
#include <core/type_traits.h>
#include <cssdk/public/os_defs.h>
#include <cstdio>
#include <string>
#include <utility>

#if defined(CLANG_COMPILER) || (defined(_MSC_VER) && defined(__clang__)) || defined(INTEL_LLVM_COMPILER)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#elif defined(GCC_COMPILER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
#endif

namespace core::str
{
    namespace detail
    {
        template <typename T>
        ATTR_CONST decltype(auto) Cast(T&& v)
        {
            if constexpr (type_traits::IsString<T>()) {
                return std::forward<T>(v).c_str();
            }
            else if constexpr (type_traits::IsStringView<T>()) {
                // WARNING! The string_view in some cases can be without a null-terminator character. So be careful!
                return std::forward<T>(v).data();
            }
            else {
                static_assert(type_traits::IsPod<T>(), "Unsupported type provided.");
                return std::forward<T>(v);
            }
        }
    }

    /**
     * @brief Returns a formatted string (alternative to \c snprintf with a \c string support).
     *
     * @note See https://en.cppreference.com/w/cpp/io/c/fprintf for more details.
    */
    template <typename... Args>
    [[nodiscard]] std::string Format(const std::string& format, Args&&... args)
    {
        std::string string{EMPTY};

        // NOLINTNEXTLINE(clang-diagnostic-format-nonliteral, clang-diagnostic-format-security)
        const auto required = std::snprintf(nullptr, 0, format.c_str(), detail::Cast(std::forward<Args>(args))...); // cppcheck-suppress accessForwarded

        if (required > 0) {
            string.resize(static_cast<std::string::size_type>(required), EOS);

#ifdef _MSC_VER
#pragma warning(disable : 26800)
#endif
            // NOLINTNEXTLINE(clang-diagnostic-format-nonliteral, clang-diagnostic-format-security)
            std::snprintf(string.data(), required + 1, format.c_str(), detail::Cast(std::forward<Args>(args))...); // cppcheck-suppress accessForwarded
#ifdef _MSC_VER
#pragma warning(default : 26800)
#endif
        }

        return string;
    }
}

#if defined(CLANG_COMPILER) || (defined(_MSC_VER) && defined(__clang__)) || defined(INTEL_LLVM_COMPILER)
#pragma clang diagnostic pop
#elif defined(GCC_COMPILER)
#pragma GCC diagnostic pop
#endif
