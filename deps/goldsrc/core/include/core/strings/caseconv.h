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
#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>
#include <string_view>

namespace core::str
{
    /**
     * @brief Converts a string to lowercase.
    */
    inline void ToLower(char* string)
    {
        assert(string != nullptr);

        while (*string != EOS) {
            *string = static_cast<char>(std::tolower(static_cast<unsigned char>(*string)));
            ++string;
        }
    }

    /**
     * @brief Converts a string to lowercase.
    */
    inline void ToLower(std::string& string, const std::string::size_type offset = 0)
    {
        assert(offset == 0 || offset < string.length());
        const auto& begin = string.begin() + static_cast<std::string::difference_type>(offset);

        std::transform(begin, string.end(), begin, [](const unsigned char ch) {
            return static_cast<std::string::value_type>(std::tolower(ch));
        });
    }

    /**
     * @brief Returns a copy of the supplied string converted to lowercase.
    */
    [[nodiscard]] inline std::string ToLowerCopy(const std::string_view string, const std::string::size_type offset = 0)
    {
        std::string string_copy{string};
        ToLower(string_copy, offset);

        return string_copy;
    }

    /**
     * @brief Converts a string to uppercase.
    */
    inline void ToUpper(char* string)
    {
        assert(string != nullptr);

        while (*string != EOS) {
            *string = static_cast<char>(std::toupper(static_cast<unsigned char>(*string)));
            ++string;
        }
    }

    /**
     * @brief Converts a string to uppercase.
    */
    inline void ToUpper(std::string& string, const std::string::size_type offset = 0)
    {
        assert(offset == 0 || offset < string.length());
        const auto& begin = string.begin() + static_cast<std::string::difference_type>(offset);

        std::transform(begin, string.end(), begin, [](const unsigned char ch) {
            return static_cast<std::string::value_type>(std::toupper(ch));
        });
    }

    /**
     * @brief Returns a copy of the supplied string converted to uppercase.
    */
    [[nodiscard]] inline std::string ToUpperCopy(const std::string_view string, const std::string::size_type offset = 0)
    {
        std::string string_copy{string};
        ToUpper(string_copy, offset);

        return string_copy;
    }
}
