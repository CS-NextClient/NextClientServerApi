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

#include <core/strings/consts.h>
#include <core/strings/mutation.h>
#include <core/strings/examination.h>

namespace core::str
{
    std::string Utf8Truncate(const std::string& string, const std::string::size_type max_size)
    {
        if (string.empty() || string.size() <= max_size) {
            return string;
        }

        if (max_size == 0) {
            return std::string{};
        }

        const auto* c_str = string.c_str();
        const auto* invalid_ptr = Utf8Valid(c_str, max_size);
        const std::string::size_type invalid_pos = invalid_ptr - c_str;

        return invalid_pos == 0 ? string : string.substr(0, invalid_pos);
    }

    void ReplaceAll(char* string, const char what, const char with)
    {
        assert(string != nullptr);

        while (*string != EOS) {
            if (*string == what) {
                *string = with;
            }

            ++string;
        }
    }

    void ReplaceAll(std::string& string, const std::string_view what, const std::string_view with,
                    std::string::size_type offset)
    {
        assert(offset == 0 || offset < string.length());

        while ((offset = string.find(what, offset)) != std::string::npos) {
            string.replace(offset, what.length(), with);
            offset += with.length();
        }
    }

    void IReplaceAll(char* string, const char what, const char with)
    {
        assert(string != nullptr);

        const auto uwhat = static_cast<unsigned char>(what);
        const auto lwhat = std::tolower(uwhat);

        while (*string != EOS) {
            if (*reinterpret_cast<unsigned char*>(string) == uwhat ||
                std::tolower(*reinterpret_cast<unsigned char*>(string)) == lwhat) {
                *string = with;
            }

            ++string;
        }
    }

    void IReplaceAll(std::string& string, const std::string::value_type what, const std::string::value_type with,
                     const std::string::size_type offset)
    {
        assert(offset == 0 || offset < string.length());

        const auto uwhat = static_cast<unsigned char>(what);
        const auto lwhat = std::tolower(uwhat);

        std::replace_if(
            string.begin() + static_cast<std::string::difference_type>(offset), string.end(),
            [uwhat, lwhat](const unsigned char ch) {
                return ch == uwhat || std::tolower(ch) == lwhat;
            },
            with);
    }

    void IReplaceAll(std::string& string, const std::string& what, const std::string& with,
                     std::string::size_type offset)
    {
        assert(offset == 0 || offset < string.length());

        while ((offset = IFind(string, what, offset)) != std::string::npos) {
            string.replace(offset, what.length(), with);
            offset += with.length();
        }
    }
}
