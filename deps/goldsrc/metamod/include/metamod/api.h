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

#include <cssdk/public/os_defs.h>
#include <metamod/config.h>

namespace metamod
{
    enum class Status : int
    {
        Failed = 0,
        Ok
    };

    /**
     * @brief Metamod interface version.
    */
    constexpr auto INTERFACE_VERSION = "5:13";

    /**
     * @brief Flags returned by a plugin's API function.
     *
     * @note Order is crucial, as greater/less comparisons are made.
    */
    enum class Result
    {
        /**
         * @brief N/D
        */
        Unset = 0,

        /**
         * @brief Plugin didn't take any action.
        */
        Ignored,

        /**
         * @brief Plugin did something, but real function should still be called.
        */
        Handled,

        /**
         * @brief Call real function, but use my return value.
        */
        Override,

        /**
         * @brief Skip real function; use my return value.
        */
        Supercede
    };

    /**
     * @brief Variables provided to plugins.
    */
    struct Globals
    {
        /**
         * @brief Writable; plugin's return flag.
        */
        Result result{};

        /**
         * @brief Readable; return flag of the previous plugin called.
        */
        Result prev_result{};

        /**
         * @brief Readable; "highest" return flag so far.
        */
        Result status{};

        /**
         * @brief Readable; return value from "real" function.
        */
        const void* orig_ret{}; //-V122

        /**
         * @brief Readable; return value from overriding/superceding plugin.
        */
        const void* override_ret{}; //-V122
    };

    /**
     * @brief Metamod globals.
    */
    inline Globals* g_globals{};

    /**
     * @brief Sets the meta result (plugin's return flag).
    */
    FORCEINLINE void SetResult(const Result result)
    {
        if (g_globals->result < result) {
            g_globals->result = result;
        }
    }

    /**
     * @brief Gets the meta result status ("highest" return flag so far).
    */
    FORCEINLINE Result ResultStatus()
    {
        return g_globals->status;
    }

    /**
     * @brief Gets the previous meta result (return flag of the previous plugin called).
    */
    FORCEINLINE Result PreviousResult()
    {
        return g_globals->prev_result;
    }

    /**
     * @brief Returns value from "real" function.
    */
    template <typename T>
    FORCEINLINE T OrigRet()
    {
        return *static_cast<const T*>(g_globals->orig_ret);
    }

    /**
     * @brief Returns value from overriding/superceding plugin.
    */
    template <typename T>
    FORCEINLINE T OverrideRet()
    {
        return *static_cast<const T*>(g_globals->override_ret);
    }

    /**
     * @brief Returns original or overridden value.
    */
    template <typename T>
    FORCEINLINE T GetRetValue()
    {
        return g_globals->status < Result::Override ? OrigRet<T>() : OverrideRet<T>();
    }
}

#define RETURN_META(r)                  \
    do {                                \
        metamod::g_globals->result = r; \
        return;                         \
    }                                   \
    while (0)

#define RETURN_META_VALUE(r, v)         \
    do {                                \
        metamod::g_globals->result = r; \
        return v;                       \
    }                                   \
    while (0)

#ifdef META_INIT
void META_INIT();
#endif

#ifdef META_QUERY
void META_QUERY();
#endif

#ifdef META_ATTACH
metamod::Status META_ATTACH();
#endif

#ifdef META_DETACH
void META_DETACH();
#endif

using MetaStatus = metamod::Status;
using MetaResult = metamod::Result;
using MetaGlobals = metamod::Globals;

constexpr auto MetaSetResult = metamod::SetResult;
constexpr auto MetaResultStatus = metamod::ResultStatus;
constexpr auto MetaPreviousResult = metamod::PreviousResult;
