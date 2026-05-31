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
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string_view>

#ifdef _MSC_VER
#include <Shlwapi.h>
#define strcasestr StrStrI
#pragma comment(lib, "ShLwApi.Lib")
#else
#include <strings.h>
#endif

namespace core::str
{
    /**
     * @brief Returns \c nullptr on success, or the position of the invalid UTF-8 codepoint on failure.
    */
    [[nodiscard]] const char* Utf8Valid(const char* string, std::size_t count = SIZE_MAX);

    /**
     * @brief Returns \c true if the specified string is \c nullptr or an empty string \c "".
    */
    [[nodiscard]] inline bool IsNullOrEmpty(const char* const string) noexcept
    {
        return string == nullptr || *string == EOS;
    }

    /**
     * @brief Returns \c true if the specified string is \c nullptr, empty, or consists only of white-space characters.
    */
    [[nodiscard]] bool IsNullOrWhiteSpace(const char* string);

    /**
     * @brief Returns \c true if the specified string empty or consists only of white-space characters.
    */
    [[nodiscard]] inline bool IsEmptyOrWhiteSpace(const std::string_view string)
    {
        return string.empty() ||
            std::all_of(string.cbegin(), string.cend(), [](const int ch) {
                   return std::isspace(ch);
               });
    }

    /**
     * @brief Determines whether the beginning of the string matches the specified prefix.
    */
    [[nodiscard]] inline bool StartsWith(const char* const string, const char* const prefix)
    {
        assert(string != nullptr);
        assert(prefix != nullptr);

        return std::strncmp(string, prefix, std::strlen(prefix)) == 0;
    }

    /**
     * @brief Determines whether the beginning of the string matches the specified prefix.
    */
    [[nodiscard]] inline bool StartsWith(const std::string& string, const std::string& prefix)
    {
        return StartsWith(string.c_str(), prefix.c_str());
    }

    /**
     * @brief Determines whether the beginning of the string matches the specified prefix (case insensitive).
    */
    [[nodiscard]] inline bool IStartsWith(const char* const string, const char* const prefix)
    {
        assert(string != nullptr);
        assert(prefix != nullptr);

        return ICompare(string, prefix, std::strlen(prefix)) == 0;
    }

    /**
     * @brief Determines whether the beginning of the string matches the specified prefix (case insensitive).
    */
    [[nodiscard]] inline bool IStartsWith(const std::string& string, const std::string& prefix)
    {
        return IStartsWith(string.c_str(), prefix.c_str());
    }

    /**
     * @brief Determines whether the end of the string matches the specified suffix.
    */
    [[nodiscard]] bool EndsWith(const char* string, const char* suffix);

    /**
     * @brief Determines whether the end of the string matches the specified suffix.
    */
    [[nodiscard]] inline bool EndsWith(const std::string_view string, const std::string_view suffix)
    {
        return string.length() >= suffix.length() && string.rfind(suffix) == string.length() - suffix.length();
    }

    /**
     * @brief Determines whether the end of the string matches the specified suffix (case insensitive).
    */
    [[nodiscard]] bool IEndsWith(const char* string, const char* suffix);

    /**
     * @brief Determines whether the end of the string matches the specified suffix (case insensitive).
    */
    [[nodiscard]] inline bool IEndsWith(const std::string& string, const std::string& suffix)
    {
        return IEndsWith(string.c_str(), suffix.c_str());
    }

    /**
     * @brief Returns a pointer to the first occurrence of substring in string,
     * or a null pointer if substring is not part of string (case insensitive).
    */
    [[nodiscard]] inline char* IFind(char* const string, const char* const substring)
    {
        assert(string != nullptr);
        assert(substring != nullptr);

#ifndef _MSC_VER
        return strcasestr(string, substring);
#else
        auto* const pointer = strcasestr(string, substring);
        return pointer == nullptr && ((*string == EOS && *substring == EOS) || *substring == EOS) ? string : pointer; //-V686
#endif
    }

    /**
     * @brief Returns a pointer to the first occurrence of substring in string,
     * or a null pointer if substring is not part of string (case insensitive).
    */
    [[nodiscard]] inline const char* IFind(const char* const string, const char* const substring)
    {
        assert(string != nullptr);
        assert(substring != nullptr);

#ifndef _MSC_VER
        return strcasestr(string, substring);
#else
        const auto* const pointer = strcasestr(string, substring);
        return pointer == nullptr && ((*string == EOS && *substring == EOS) || *substring == EOS) ? string : pointer; //-V686
#endif
    }

    /**
     * @brief Returns the position of the first occurrence of a substring in a string,
     * or \c npos if the substring is not part of the string (case insensitive).
    */
    [[nodiscard]] inline std::string::size_type IFind(const std::string& string, const std::string& substring,
                                                      const std::string::size_type offset = 0)
    {
        const auto* const pointer = IFind(string.c_str() + offset, substring.c_str());
        return pointer == nullptr ? std::string::npos : static_cast<std::string::size_type>(pointer - string.c_str());
    }

    /**
     * @brief Returns \c true if the specified substring occurs in the string.
    */
    [[nodiscard]] inline bool Contains(const char* string, const char* substring)
    {
        assert(string != nullptr);
        assert(substring != nullptr);

        return std::strstr(string, substring) != nullptr;
    }

    /**
     * @brief Returns \c true if the specified substring occurs in the string.
    */
    [[nodiscard]] inline bool Contains(const std::string_view string, const std::string_view substring)
    {
        return string.find(substring) != std::string_view::npos;
    }

    /**
     * @brief Returns \c true if the specified substring occurs in the string (case insensitive).
    */
    [[nodiscard]] inline bool IContains(const char* string, const char* substring)
    {
        assert(string != nullptr);
        assert(substring != nullptr);

        return IFind(string, substring) != nullptr;
    }

    /**
     * @brief Returns \c true if the specified substring occurs in the string (case insensitive).
    */
    [[nodiscard]] inline bool IContains(const std::string& string, const std::string& substring)
    {
        return IContains(string.c_str(), substring.c_str());
    }
}
