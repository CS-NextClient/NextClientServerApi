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

#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <string>
#include <string_view>

#ifdef _MSC_VER
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#else
#include <strings.h>
#endif

namespace core::str
{
    /**
     * @brief Compares two strings lexicographically (case insensitive).
     *
     * @return Negative value if lhs appears before rhs in lexicographical order.\n
     * Zero if lhs and rhs compare equal.\n
     * Positive value if lhs appears after rhs in lexicographical order.
    */
    [[nodiscard]] inline int ICompare(const char* const lhs, const char* const rhs)
    {
        assert(lhs != nullptr);
        assert(rhs != nullptr);

        return strcasecmp(lhs, rhs);
    }

    /**
     * @brief Compares two strings lexicographically (case insensitive).
     *
     * @return Negative value if lhs appears before rhs in lexicographical order.\n
     * Zero if lhs and rhs compare equal.\n
     * Positive value if lhs appears after rhs in lexicographical order.
    */
    [[nodiscard]] inline int ICompare(const std::string& lhs, const std::string& rhs)
    {
        return strcasecmp(lhs.c_str(), rhs.c_str());
    }

    /**
     * @brief Compares two strings lexicographically (case insensitive).
     *
     * @param lhs String to be compared.
     * @param rhs String to be compared.
     * @param count Maximum number of characters to compare.
     *
     * @return Negative value if lhs appears before rhs in lexicographical order.\n
     * Zero if lhs and rhs compare equal.\n
     * Positive value if lhs appears after rhs in lexicographical order.
    */
    [[nodiscard]] inline int ICompare(const char* const lhs, const char* const rhs, const std::size_t count)
    {
        assert(lhs != nullptr);
        assert(rhs != nullptr);

        return strncasecmp(lhs, rhs, count);
    }

    /**
     * @brief Compares two strings lexicographically (case insensitive).
     *
     * @param lhs String to be compared.
     * @param rhs String to be compared.
     * @param count Maximum number of characters to compare.
     *
     * @return Negative value if lhs appears before rhs in lexicographical order.\n
     * Zero if lhs and rhs compare equal.\n
     * Positive value if lhs appears after rhs in lexicographical order.
    */
    [[nodiscard]] inline int ICompare(const std::string& lhs, const std::string& rhs, const std::size_t count)
    {
        return strncasecmp(lhs.c_str(), rhs.c_str(), count);
    }

    /**
     * @brief Determines whether two strings have the same value.
    */
    [[nodiscard]] inline bool Equals(const char* const lhs, const char* const rhs)
    {
        assert(lhs != nullptr);
        assert(rhs != nullptr);

        return std::strcmp(lhs, rhs) == 0;
    }

    /**
     * @brief Determines whether two strings have the same value.
    */
    [[nodiscard]] inline bool Equals(const std::string_view lhs, const std::string_view rhs)
    {
        return lhs == rhs;
    }

    /**
     * @brief Determines whether two characters have the same value (case insensitive).
    */
    [[nodiscard]] inline bool IEquals(const char lhs, const char rhs)
    {
        return lhs == rhs ||
            std::tolower(static_cast<unsigned char>(lhs)) == std::tolower(static_cast<unsigned char>(rhs));
    }

    /**
     * @brief Determines whether two strings have the same value (case insensitive).
    */
    [[nodiscard]] inline bool IEquals(const char* const lhs, const char* const rhs)
    {
        assert(lhs != nullptr);
        assert(rhs != nullptr);

        return strcasecmp(lhs, rhs) == 0;
    }

    /**
     * @brief Determines whether two strings have the same value (case insensitive).
    */
    [[nodiscard]] inline bool IEquals(const std::string& lhs, const std::string& rhs)
    {
        return IEquals(lhs.c_str(), rhs.c_str());
    }
}
