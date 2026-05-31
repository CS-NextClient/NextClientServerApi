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

#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN // NOLINT(clang-diagnostic-unused-macros)
#include <Windows.h>
#else
#include <cerrno>
#include <cstring>
#endif

namespace core::system
{
#ifdef _WIN32
    /**
     * @brief Returns a textual description of the system error code.
    */
    [[nodiscard]] inline std::string StrError(const DWORD error_code, const unsigned lang = LANG_ENGLISH,
                                              const unsigned sublang = SUBLANG_ENGLISH_US)
    {
        CHAR buffer[512]{};

        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, error_code,
                      MAKELANGID(lang, sublang), buffer, sizeof buffer - 1, nullptr);

        return std::string{buffer};
    }

    /**
     * @brief Returns a textual description of the last system error.
    */
    [[nodiscard]] inline std::string GetLastErrorStr()
    {
        return StrError(GetLastError());
    }
#else
    /**
     * @brief Returns a textual description of the system error code.
    */
    [[nodiscard]] inline std::string StrError(const int error_code)
    {
        return std::string{std::strerror(error_code)}; // NOLINT(concurrency-mt-unsafe)
    }

    /**
     * @brief Returns a textual description of the last system error.
    */
    [[nodiscard]] inline std::string GetLastErrorStr()
    {
        return StrError(errno);
    }
#endif
}
