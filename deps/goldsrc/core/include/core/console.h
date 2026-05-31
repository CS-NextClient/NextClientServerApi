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

#ifdef HAS_AMXX_LIB
#include <amxx/config.h>
#else
#include <metamod/config.h>
#endif

#include <core/strings/format.h>
#include <cssdk/engine/eiface.h>
#include <cssdk/public/os_defs.h>
#include <cstdio>
#include <string>
#include <utility>

namespace core::console
{
#ifdef HAS_AMXX_LIB
    /**
     * @brief Log tag.
    */
    constexpr auto LOG_TAG = amxx::MODULE_LOG_TAG;
#else
    /**
     * @brief Log tag.
    */
    constexpr auto LOG_TAG = metamod::PLUGIN_LOG_TAG;
#endif

    /**
     * @brief Prints a message to the server console.
    */
    template <bool LogTag = true, bool LineFeed = true, typename... Args>
    ATTR_MINSIZE void Message(const std::string& format, Args&&... args)
    {
        const auto& message = str::Format(format, std::forward<Args>(args)...);

        if constexpr (LogTag) {
            if constexpr (LineFeed) {
                std::printf("[%s] %s\n", LOG_TAG, message.c_str());
            }
            else {
                std::printf("[%s] %s", LOG_TAG, message.c_str());
            }
        }
        else if constexpr (LineFeed) {
            std::printf("%s\n", message.c_str());
        }
        else {
            std::printf("%s", message.c_str());
        }
    }

    /**
     * @brief Prints a warning message with a log-tag to the server console.
    */
    template <bool LogTag = true, bool LineFeed = true, typename... Args>
    ATTR_MINSIZE void Warning(const std::string& format, Args&&... args)
    {
        const auto& message = str::Format(format, std::forward<Args>(args)...);

        if (LogTag) {
            if constexpr (LineFeed) {
                std::printf("[%s] WARNING! %s\n", LOG_TAG, message.c_str());
            }
            else {
                std::printf("[%s] WARNING! %s", LOG_TAG, message.c_str());
            }
        }
        else if constexpr (LineFeed) {
            std::printf("WARNING! %s\n", message.c_str());
        }
        else {
            std::printf("WARNING! %s", message.c_str());
        }
    }

    /**
     * @brief Prints an error message with a log-tag to the server console.
    */
    template <bool LogTag = true, bool LineFeed = true, typename... Args>
    ATTR_MINSIZE void Error(const std::string& format, Args&&... args)
    {
        const auto& message = str::Format(format, std::forward<Args>(args)...);

        if (LogTag) {
            if constexpr (LineFeed) {
                std::printf("[%s] ERROR! %s\n", LOG_TAG, message.c_str());
            }
            else {
                std::printf("[%s] ERROR! %s", LOG_TAG, message.c_str());
            }
        }
        else if constexpr (LineFeed) {
            std::printf("ERROR! %s\n", message.c_str());
        }
        else {
            std::printf("ERROR! %s", message.c_str());
        }
    }

#ifdef HAS_METAMOD_LIB
    /**
     * @brief Prints a log message using the 'alert_message' function from the HLDS engine.
     *
     * @note The value of the 'log' cvar should be 'on'.
    */
    template <bool LineFeed = true, typename... Args>
    ATTR_MINSIZE void AlertMessage(const std::string& format, Args&&... args)
    {
        if (cssdk::g_engine_funcs.alert_message) {
            if constexpr (LineFeed) {
                const auto& message = str::Format(format + "\n", std::forward<Args>(args)...);
                cssdk::g_engine_funcs.alert_message(cssdk::AlertType::Logged, message.c_str());
            }
            else {
                const auto& message = str::Format(format, std::forward<Args>(args)...);
                cssdk::g_engine_funcs.alert_message(cssdk::AlertType::Logged, message.c_str());
            }
        }
    }

    /**
     * @brief Prints a log message using the 'alert_message' function from the HLDS engine.
     *
     * @note The value of the 'log' cvar should be 'on'.
     * @note The value of the 'developer' cvar should be '1' or '2'.
    */
    template <bool LineFeed = true, typename... Args>
    ATTR_MINSIZE void AlertMessageDeveloper(const std::string& format, Args&&... args)
    {
        if (cssdk::g_engine_funcs.cvar_get_float &&
            static_cast<bool>(cssdk::g_engine_funcs.cvar_get_float("developer"))) {
            AlertMessage<LineFeed>(format, std::forward<Args>(args)...);
        }
    }
#endif
}
