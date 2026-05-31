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

#include <core/strings/compare.h>
#include <core/strings/consts.h>
#include <cctype>
#include <string_view>

namespace core::str
{
    /**
     * @brief Removes all leading occurrences of a specified character from the specified string.
    */
    [[nodiscard]] inline std::string_view TrimLeft(const std::string_view string, const char ch)
    {
        const auto first = string.find_first_not_of(ch);
        return first == std::string_view::npos ? std::string_view{EMPTY} : string.substr(first, string.length() - first);
    }

    /**
     * @brief Removes all trailing occurrences of a specified character from the specified string.
    */
    [[nodiscard]] inline std::string_view TrimRight(const std::string_view string, const char ch)
    {
        const auto last = string.find_last_not_of(ch);
        return last == std::string_view::npos ? std::string_view{EMPTY} : string.substr(0, last + 1);
    }

    /**
     * @brief Removes all leading and trailing occurrences of the specified character from the specified string.
    */
    [[nodiscard]] inline std::string_view Trim(const std::string_view string, const char ch)
    {
        return TrimRight(TrimLeft(string, ch), ch);
    }

    /**
     * @brief Removes all leading occurrences of a specified character from the specified string (case insensitive).
    */
    [[nodiscard]] inline std::string_view ITrimLeft(std::string_view string, const char ch)
    {
        while (!string.empty() && IEquals(string.front(), ch)) {
            string = TrimLeft(string, string.front());
        }

        return string;
    }

    /**
     * @brief Removes all trailing occurrences of a specified character from the specified string (case insensitive).
    */
    [[nodiscard]] inline std::string_view ITrimRight(std::string_view string, const char ch)
    {
        while (!string.empty() && IEquals(string.back(), ch)) {
            string = TrimRight(string, string.back());
        }

        return string;
    }

    /**
     * @brief Removes all leading and trailing occurrences of the specified character
     * from the specified string (case insensitive).
    */
    [[nodiscard]] inline std::string_view ITrim(const std::string_view string, const char ch)
    {
        return ITrimRight(ITrimLeft(string, ch), ch);
    }

    /**
     * @brief Removes all leading white-space characters from the specified string.
    */
    [[nodiscard]] inline std::string_view TrimLeft(std::string_view string)
    {
        while (!string.empty() && std::isspace(static_cast<unsigned char>(string.front()))) {
            string = TrimLeft(string, string.front());
        }

        return string;
    }

    /**
     * @brief Removes all trailing white-space characters from the specified string.
    */
    [[nodiscard]] inline std::string_view TrimRight(std::string_view string)
    {
        while (!string.empty() && std::isspace(static_cast<unsigned char>(string.back()))) {
            string = TrimRight(string, string.back());
        }

        return string;
    }

    /**
     * @brief Removes all leading and trailing white-space characters from the specified string.
    */
    [[nodiscard]] inline std::string_view Trim(const std::string_view string)
    {
        return TrimRight(TrimLeft(string));
    }
}
