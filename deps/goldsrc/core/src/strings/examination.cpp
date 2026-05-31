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

#include <core/strings/examination.h>
#include <core/strings/consts.h>

namespace core::str
{
    const char* Utf8Valid(const char* string, const std::size_t count) // NOLINT(readability-function-cognitive-complexity)
    {
        assert(string != nullptr);

        const auto* const s = string;
        std::size_t consumed{};

        while ((void)(consumed = static_cast<std::size_t>(string - s)), consumed < count && EOS != *string) {
            if (const auto remained = count - consumed; 0xF0 == (0xF8 & *string)) {
                // ensure that there's 4 bytes or more remained
                if (remained < 4) {
                    return string;
                }

                // ensure each of the 3 following bytes in this 4-byte
                // UTF-8 codepoint began with 0b10xxxxxx
                if ((0x80 != (0xC0 & string[1])) || (0x80 != (0xC0 & string[2])) || (0x80 != (0xC0 & string[3]))) {
                    return string;
                }

                // ensure that our UTF-8 codepoint ended after 4 bytes
                if (0x80 == (0xC0 & string[4])) {
                    return string;
                }

                // ensure that the top 5 bits of this 4-byte UTF-8
                // codepoint were not 0, as then we could have used
                // one of the smaller encodings
                if ((0 == (0x07 & string[0])) && (0 == (0x30 & string[1]))) {
                    return string;
                }

                // 4-byte UTF-8 code point (began with 0b11110xxx)
                string += 4;
            }
            else if (0xE0 == (0xF0 & *string)) {
                // ensure that there's 3 bytes or more remained
                if (remained < 3) {
                    return string;
                }

                // ensure each of the 2 following bytes in this 3-byte
                // UTF-8 codepoint began with 0b10xxxxxx
                if ((0x80 != (0xC0 & string[1])) || (0x80 != (0xC0 & string[2]))) {
                    return string;
                }

                // ensure that our UTF-8 codepoint ended after 3 bytes
                if (0x80 == (0xC0 & string[3])) {
                    return string;
                }

                // ensure that the top 5 bits of this 3-byte UTF-8
                // codepoint were not 0, as then we could have used
                // one of the smaller encodings
                if ((0 == (0x0F & string[0])) && (0 == (0x20 & string[1]))) {
                    return string;
                }

                // 3-byte UTF-8 code point (began with 0b1110xxxx)
                string += 3;
            }
            else if (0xC0 == (0xE0 & *string)) {
                // ensure that there's 2 bytes or more remained
                if (remained < 2) {
                    return string;
                }

                // ensure the 1 following byte in this 2-byte
                // UTF-8 codepoint began with 0b10xxxxxx
                if (0x80 != (0xC0 & string[1])) {
                    return string;
                }

                // ensure that our UTF-8 codepoint ended after 2 bytes
                if (0x80 == (0xC0 & string[2])) {
                    return string;
                }

                // ensure that the top 4 bits of this 2-byte UTF-8
                // codepoint were not 0, as then we could have used
                // one of the smaller encodings
                if (0 == (0x1E & string[0])) {
                    return string;
                }

                // 2-byte UTF-8 code point (began with 0b110xxxxx)
                string += 2;
            }
            else if (0x00 == (0x80 & *string)) {
                // 1-byte ASCII (began with 0b0xxxxxxx)
                string += 1;
            }
            else {
                // we have an invalid 0b1xxxxxxx UTF-8 code point entry
                return string;
            }
        }

        return nullptr;
    }

    bool IsNullOrWhiteSpace(const char* const string)
    {
        if (string) {
            const auto* ch = reinterpret_cast<const unsigned char*>(string);

            while (*ch != EOS) {
                if (!std::isspace(*ch++)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool EndsWith(const char* const string, const char* const suffix)
    {
        assert(string != nullptr);
        assert(suffix != nullptr);

        const auto string_length = std::strlen(string);
        const auto suffix_length = std::strlen(suffix);

        if (string_length < suffix_length) {
            return false;
        }

        return std::strncmp(string + string_length - suffix_length, suffix, suffix_length) == 0;
    }

    bool IEndsWith(const char* const string, const char* const suffix)
    {
        assert(string != nullptr);
        assert(suffix != nullptr);

        const auto string_length = std::strlen(string);
        const auto suffix_length = std::strlen(suffix);

        if (string_length < suffix_length) {
            return false;
        }

        return ICompare(string + string_length - suffix_length, suffix, suffix_length) == 0;
    }
}
