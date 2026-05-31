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

#ifdef HAS_CSSDK_LIB
#include <core/console.h>
#include <core/rehlds_api.h>
#include <core/reunion_api.h>

#ifdef HAS_AMXX_LIB
#include <amxx/config.h>
#else
#include <metamod/config.h>
#endif

using namespace core;
using namespace reunion_api;

namespace
{
#ifdef HAS_AMXX_LIB
    constexpr auto MODULE_NAME = amxx::MODULE_NAME;
#else
    constexpr auto MODULE_NAME = metamod::PLUGIN_NAME;
#endif

    template <typename... Args>
    void Error(const bool silent, const std::string& format, Args&&... args)
    {
        if (!silent) {
            console::Message<false>(str::EMPTY); // Line feed
            console::Error(format, std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void Message(const bool silent, const std::string& format, Args&&... args)
    {
        if (!silent) {
            console::Message<false>(format, std::forward<Args>(args)...);
        }
    }
}

namespace core::reunion_api
{
    bool Init(const bool silent)
    {
        if (Initialized()) {
            return true;
        }

        if (!rehlds_api::Init(silent)) {
            return false;
        }

        if (!((detail::reunion_api = static_cast<IReunionApi*>(rehlds_api::Funcs()->get_plugin_api("reunion"))))) {
            Error(silent, "Failed to retrieve \"reunion\" plugin API.");
            return false;
        }

        const auto major_version = MajorVersion();
        const auto minor_version = MinorVersion();

        if (major_version != REUNION_API_VERSION_MAJOR) {
            Error(silent, "Reunion API major version mismatch; expected %d, real %d.",
                  REUNION_API_VERSION_MAJOR, major_version);

            if (major_version < REUNION_API_VERSION_MAJOR) {
                Message(silent, "Please update the Reunion up to a major version API >= %d.\n",
                        REUNION_API_VERSION_MAJOR);
            }
            else {
                Message(silent, "Please update the %s up to a major version API >= %d.\n",
                        MODULE_NAME, REUNION_API_VERSION_MAJOR);
            }

            return false;
        }

        if (minor_version < REUNION_API_VERSION_MINOR) {
            Error(silent, "Reunion API minor version mismatch; expected %d, real %d.",
                  REUNION_API_VERSION_MINOR, minor_version);

            Message(silent, "Please update the Reunion up to a minor version API >= %d.\n",
                    REUNION_API_VERSION_MINOR);

            return false;
        }

        return Initialized();
    }
}
#endif
