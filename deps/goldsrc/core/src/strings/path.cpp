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

#include <core/strings/path.h>
#include <core/strings/consts.h>
#include <core/strings/examination.h>
#include <core/strings/trim.h>
#include <cssdk/engine/eiface.h>
#include <cssdk/public/os_defs.h>
#include <cassert>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

using namespace cssdk;

namespace core::str
{
    std::string GetWorkingDirectory()
    {
        char buffer[MAX_PATH]{};

#ifdef _WIN32
        if (!_getcwd(buffer, sizeof buffer)) {
            assert(false);
        }
#else
        if (!getcwd(buffer, sizeof(buffer))) {
            assert(false);
        }
#endif
        assert(!IsNullOrEmpty(buffer));
        return std::string{buffer};
    }

    std::string GetGameModDirectoryName()
    {
        assert(g_engine_funcs.get_game_dir);

        char buffer[MAX_PATH]{};
        g_engine_funcs.get_game_dir(buffer);
        assert(!IsNullOrEmpty(buffer));

        const auto directory = GetFileNameFromPath(GetDirectoryFromPath(buffer));
        assert(!IsEmptyOrWhiteSpace(directory));

        return std::string{directory};
    }

    std::string_view GetDirectoryFromPath(std::string_view path, const char separator)
    {
        path = TrimRight(path);
        path = TrimRight(path, separator);

        if (!path.empty()) {
            if (const auto offset = path.find_last_of(separator); offset != std::string_view::npos) {
                return path.substr(0, offset);
            }
        }

        return path;
    }

    std::string_view GetFileNameFromPath(const std::string_view path, const char separator)
    {
        if (path.empty() || path.back() == separator) {
            return std::string_view{EMPTY};
        }

        if (const auto offset = path.find_last_of(separator); offset != std::string_view::npos && offset > 0) {
            return path.substr(offset + 1);
        }

        return path;
    }

    std::string_view GetFileNameWithoutExtension(const std::string_view path, const char separator)
    {
        const auto filename = GetFileNameFromPath(path, separator);

        if (!filename.empty()) {
            if (const auto offset = filename.find_last_of('.'); offset != std::string_view::npos && offset > 0) {
                return filename.substr(0, offset);
            }
        }

        return filename;
    }

    std::string_view GetFileExtension(const std::string_view filename, const char separator)
    {
        if (filename.empty() || filename.back() == separator) {
            return std::string_view{EMPTY};
        }

        if (const auto offset = filename.find_last_of('.'); offset != std::string_view::npos && offset > 0) {
            return filename.substr(offset);
        }

        return filename;
    }
}
