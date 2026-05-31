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

#include <core/strings/examination.h>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>
#include <string_view>

namespace core::str
{
    /**
     * @brief Returns a UTF-8 string truncated to the specified size.
    */
    [[nodiscard]] std::string Utf8Truncate(const std::string& string, std::string_view::size_type max_size);

    /**
     * @brief Replaces all occurrences of a specified character in the specified string with another specified character.
    */
    void ReplaceAll(char* string, char what, char with);

    /**
     * @brief Replaces all occurrences of a specified character in the specified string with another specified character.
    */
    inline void ReplaceAll(std::string& string, const std::string::value_type what, const std::string::value_type with,
                           const std::string::size_type offset = 0)
    {
        assert(offset == 0 || offset < string.length());
        std::replace(string.begin() + static_cast<std::string::difference_type>(offset), string.end(), what, with);
    }

    /**
     * @brief Replaces all occurrences of a specified string in the specified string with another specified string.
    */
    void ReplaceAll(std::string& string, std::string_view what, std::string_view with,
                    std::string::size_type offset = 0);

    /**
     * @brief Replaces all occurrences of a specified character in the specified string
     * with another specified character (case insensitive).
    */
    void IReplaceAll(char* string, char what, char with);

    /**
     * @brief Replaces all occurrences of a specified character in the specified string
     * with another specified character (case insensitive).
    */
    void IReplaceAll(std::string& string, std::string::value_type what, std::string::value_type with,
                     std::string::size_type offset = 0);

    /**
     * @brief Replaces all occurrences of a specified string in the specified string
     * with another specified string (case insensitive).
    */
    void IReplaceAll(std::string& string, const std::string& what, const std::string& with,
                     std::string::size_type offset = 0);

    /**
     * @brief Returns a new string in which all occurrences of a specified character in the specified string
     * are replaced with another specified character.
    */
    [[nodiscard]] inline std::string ReplaceAllCopy(const std::string_view string, const std::string::value_type what,
                                                    const std::string::value_type with, const std::string::size_type offset = 0)
    {
        std::string string_copy{string};
        ReplaceAll(string_copy, what, with, offset);

        return string_copy;
    }

    /**
     * @brief Returns a new string in which all occurrences of a specified string in the specified string
     * are replaced with another specified string.
    */
    [[nodiscard]] inline std::string ReplaceAllCopy(const std::string_view string, const std::string_view what,
                                                    const std::string_view with, const std::string::size_type offset = 0)
    {
        std::string string_copy{string};
        ReplaceAll(string_copy, what, with, offset);

        return string_copy;
    }

    /**
     * @brief Returns a new string in which all occurrences of a specified character in the specified string
     * are replaced with another specified character (case insensitive).
    */
    [[nodiscard]] inline std::string IReplaceAllCopy(const std::string_view string, const std::string::value_type what,
                                                     const std::string::value_type with, const std::string::size_type offset = 0)
    {
        std::string string_copy{string};
        IReplaceAll(string_copy, what, with, offset);

        return string_copy;
    }

    /**
     * @brief Returns a new string in which all occurrences of a specified string in the specified string
     * are replaced with another specified string (case insensitive).
    */
    [[nodiscard]] inline std::string IReplaceAllCopy(const std::string_view string, const std::string& what,
                                                     const std::string& with, const std::string::size_type offset = 0)
    {
        std::string string_copy{string};
        IReplaceAll(string_copy, what, with, offset);

        return string_copy;
    }
}
