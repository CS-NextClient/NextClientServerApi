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

namespace metamod
{
    /**
     * @brief Flags for plugin to indicate when it can be loaded/unloaded.
     *
     * @note Order is crucial, as greater/less comparisons are made.
    */
    enum class PluginLoadTime
    {
        /**
         * @brief N/D
        */
        Never = 0,

        /**
         * @brief Should only be loaded/unloaded at initial HLDS execution.
        */
        Startup,

        /**
         * @brief Can be loaded/unloaded between maps.
        */
        ChangeLevel,

        /**
         * @brief Can be loaded/unloaded at any time.
        */
        AnyTime,

        /**
         * @brief Can be loaded/unloaded at any time, and can be "paused" during a map.
        */
        AnyPause
    };

    /**
     * @brief Flags to indicate why the plugin is being unloaded.
    */
    enum class PluginUnloadReason
    {
        /**
         * @brief N/D
        */
        Null = 0,

        /**
         * @brief Was deleted from plugins.ini.
        */
        IniDeleted,

        /**
         * @brief File on disk is newer than last load.
        */
        FileNewer,

        /**
         * @brief Requested by server/console command.
        */
        Command,

        /**
         * @brief Forced by server/console command.
        */
        CommandForced,

        /**
         * @brief Delayed from previous request;
         * can't tell origin only used for 'real_reason' on MPlugin::unload().
        */
        Delayed,

        /**
         * @brief Requested by plugin function call.
        */
        Plugin,

        /**
         * @brief Forced by plugin function call.
        */
        PluginForced,

        /**
         * @brief Forced unload by reload().
        */
        Reload
    };

    //-V::122

    /**
     * @brief Information plugin provides about itself.
    */
    struct PluginInfo
    {
        /**
         * @brief Metamod interface version.
        */
        const char* interface_version{};

        /**
         * @brief Full name of the plugin.
        */
        const char* name{};

        /**
         * @brief Plugin version.
        */
        const char* version{};

        /**
         * @brief Plugin date.
        */
        const char* date{};

        /**
         * @brief Plugin author.
        */
        const char* author{};

        /**
         * @brief Plugin URL.
        */
        const char* url{};

        /**
         * @brief Plugin log tag.
        */
        const char* log_tag{};

        /**
         * @brief Loadable flags.
        */
        PluginLoadTime loadable{};

        /**
         * @brief Unloadable flags.
        */
        PluginLoadTime unloadable{};
    };
}
