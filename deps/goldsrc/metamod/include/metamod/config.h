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

#include <metamod/plugin_info.h>

/*
* -------------------------------------------------------------------------------------------
*	Metamod init function declarations.
* -------------------------------------------------------------------------------------------
*/
/* #undef META_INIT */
/* #undef META_QUERY */
/* #undef META_ATTACH */
#define META_DETACH OnMetaDetach

namespace metamod
{
    /*
    * -------------------------------------------------------------------------------------------
    *	Metamod plugin info.
    * -------------------------------------------------------------------------------------------
    */
    constexpr auto PLUGIN_NAME = "Next Client API";
    constexpr auto PLUGIN_VERSION = "1.6.0";
    constexpr auto PLUGIN_AUTHOR = "Next21 Team";
    constexpr auto PLUGIN_LOG_TAG = "nclapi";
    constexpr auto PLUGIN_URL = "https://github.com/CS-NextClient/NextClientServerApi";
    constexpr auto PLUGIN_LOADABLE = PluginLoadTime::AnyTime;
    constexpr auto PLUGIN_UNLOADABLE = PluginLoadTime::AnyTime;
    constexpr auto PLUGIN_DATE = __DATE__;
}
