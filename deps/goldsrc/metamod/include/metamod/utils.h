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

#include <cssdk/engine/eiface.h>
#include <cssdk/public/os_defs.h>
#include <metamod/plugin_info.h>
#include <cstdarg>
#include <type_traits>
#include <utility>

//-V:Funcs:591, 730

namespace metamod::utils
{
    enum class GameInfo;
}

namespace metamod::utils::detail
{
    struct Funcs
    {
        using EngFuncs = cssdk::EngineFunctions;
        using DllFuncs = cssdk::DllFunctions;
        using DllNewFuncs = cssdk::DllNewFunctions;

        std::add_pointer_t<void(PluginInfo* plugin, const char* format, ...)> log_console{};
        std::add_pointer_t<void(PluginInfo* plugin, const char* format, ...)> log_message{};
        std::add_pointer_t<void(PluginInfo* plugin, const char* format, ...)> log_error{};
        std::add_pointer_t<void(PluginInfo* plugin, const char* format, ...)> log_developer{};
        std::add_pointer_t<void(PluginInfo* plugin, const char* format, ...)> center_say{};
        std::add_pointer_t<void(PluginInfo* plugin, cssdk::HudTextParams hud_params, const char* format, ...)> center_say_params{};
        std::add_pointer_t<void(PluginInfo* plugin, cssdk::HudTextParams hud_params, const char* format, std::va_list args)> center_say_varargs{};
        std::add_pointer_t<cssdk::qboolean(PluginInfo* plugin, const char* game_entity, cssdk::EntityVars* entity_vars)> call_game_entity{};
        std::add_pointer_t<int(PluginInfo* plugin, const char* msg_name, int* size)> get_user_msg_id{};
        std::add_pointer_t<const char*(PluginInfo* plugin, int msg_id, int* size)> get_user_msg_name{};
        std::add_pointer_t<const char*(PluginInfo* plugin)> get_plugin_path{};
        std::add_pointer_t<const char*(PluginInfo* plugin, GameInfo tag)> get_game_info{};
        std::add_pointer_t<int(PluginInfo* plugin, const char* cmdline, PluginLoadTime now, void** plugin_handle)> load_plugin{};
        std::add_pointer_t<int(PluginInfo* plugin, const char* cmdline, PluginLoadTime now, PluginUnloadReason reason)> unload_plugin{};
        std::add_pointer_t<int(PluginInfo* plugin, void* plugin_handle, PluginLoadTime now, PluginUnloadReason reason)> unload_plugin_by_handle{};
        std::add_pointer_t<const char*(PluginInfo* plugin, const cssdk::Edict* edict)> is_querying_client_cvar{};
        std::add_pointer_t<int(PluginInfo* plugin)> make_request_id{};
        std::add_pointer_t<void(PluginInfo* plugin, EngFuncs** engine_funcs, DllFuncs** dll_funcs, DllNewFuncs** dll_new_funcs)> get_hook_tables{};
    };

    inline const Funcs* funcs{};
    inline PluginInfo* plugin{};
}

namespace metamod::utils
{
    enum class GameInfo
    {
        /**
         * @brief Game name.
        */
        Name = 0,

        /**
         * @brief Game description.
        */
        Description,

        /**
         * @brief Game directory.
        */
        Directory,

        /**
         * @brief Game DLL full path.
        */
        DllFullPath,

        /**
         * @brief Game DLL file name.
        */
        DllFileName,

        /**
         * @brief Game real DLL full path.
        */
        RealDllFullPath
    };

    /**
     * @brief Log to console; newline added.
    */
    template <typename... TArgs>
    ATTR_MINSIZE void LogConsole(const char* const format, TArgs&&... args)
    {
        detail::funcs->log_console(detail::plugin, format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Log regular message to logs; newline added.
    */
    template <typename... TArgs>
    ATTR_MINSIZE void LogMessage(const char* const format, TArgs&&... args)
    {
        detail::funcs->log_message(detail::plugin, format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Log an error message to logs; newline added.
    */
    template <typename... TArgs>
    ATTR_MINSIZE void LogError(const char* const format, TArgs&&... args)
    {
        detail::funcs->log_error(detail::plugin, format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Log a message only if cvar "developer" set; newline added.
    */
    template <typename... TArgs>
    ATTR_MINSIZE void LogDeveloper(const char* const format, TArgs&&... args)
    {
        detail::funcs->log_developer(detail::plugin, format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Print message on center of all player's screens.
     * Uses default text parameters (color green, 10 second fade-in).
    */
    template <typename... TArgs>
    ATTR_MINSIZE void CenterSay(const char* const format, TArgs&&... args)
    {
        detail::funcs->center_say(detail::plugin, format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Print a center-message, with given text parameters.
    */
    template <typename... TArgs>
    ATTR_MINSIZE void CenterSayParams(const cssdk::HudTextParams& params, const char* const format, TArgs&&... args)
    {
        detail::funcs->center_say_params(detail::plugin, params, format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Print a center-message, with text parameters and varargs.
    */
    inline void CenterSayVarargs(const cssdk::HudTextParams& params, const char* const format, std::va_list&& arg_list)
    {
        detail::funcs->center_say_varargs(detail::plugin, params, format, std::forward<va_list>(arg_list));
    }

    /**
     * @brief Allow plugins to call the entity functions in the GameDLL.
     * In particular, calling "player()" as needed by most Bots.
    */
    inline cssdk::qboolean CallGameEntity(const char* const ent_str, cssdk::EntityVars* const vars)
    {
        return detail::funcs->call_game_entity(detail::plugin, ent_str, vars);
    }

    /**
     * @brief Find a user message, registered by the gamedll, with the corresponding message name,
     * and return remaining info about it (message id, size).
    */
    inline int GetUserMsgId(const char* const message_name, int* const size = nullptr)
    {
        return detail::funcs->get_user_msg_id(detail::plugin, message_name, size);
    }

    /**
     * @brief Find a user message, registered by the gamedll, with the corresponding message id,
     * and return remaining info about it (message name, size).
    */
    inline const char* GetUserMsgName(const int message_id, int* const size = nullptr)
    {
        return detail::funcs->get_user_msg_name(detail::plugin, message_id, size);
    }

    /**
     * @brief Return various string-based info about the game/MOD/gamedll.
    */
    inline const char* GetGameInfo(const GameInfo tag)
    {
        return detail::funcs->get_game_info(detail::plugin, tag);
    }

    /**
     * @brief Return the full path of the plugin's loaded dll/so file.
    */
    inline const char* GetPluginPath()
    {
        return detail::funcs->get_plugin_path(detail::plugin);
    }

    /**
     * @brief N/D
    */
    inline int LoadPlugin(const char* const cmd_line, const PluginLoadTime load_time, void** const plugin_handle)
    {
        return detail::funcs->load_plugin(detail::plugin, cmd_line, load_time, plugin_handle);
    }

    /**
     * @brief N/D
    */
    inline int UnloadPlugin(const char* const cmd_line, const PluginLoadTime load_time, const PluginUnloadReason reason)
    {
        return detail::funcs->unload_plugin(detail::plugin, cmd_line, load_time, reason);
    }

    /**
     * @brief N/D
    */
    inline int UnloadPluginByHandle(void* const plugin_handle, const PluginLoadTime load_time, const PluginUnloadReason reason)
    {
        return detail::funcs->unload_plugin_by_handle(detail::plugin, plugin_handle, load_time, reason);
    }

    /**
     * @brief N/D
    */
    inline const char* IsQueryingClientCvar(const cssdk::Edict* const edict)
    {
        return detail::funcs->is_querying_client_cvar(detail::plugin, edict);
    }

    /**
     * @brief N/D
    */
    inline int MakeRequestId()
    {
        return detail::funcs->make_request_id(detail::plugin);
    }

    /**
     * @brief N/D
    */
    inline void GetHookTables(cssdk::EngineFunctions** const engine_funcs, cssdk::DllFunctions** const dll_funcs,
                              cssdk::DllNewFunctions** const new_dll_funcs)
    {
        detail::funcs->get_hook_tables(detail::plugin, engine_funcs, dll_funcs, new_dll_funcs);
    }
}
