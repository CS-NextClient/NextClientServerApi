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

#ifdef USE_METAMOD
#include <metamod/config.h>
#endif

/*
 * -------------------------------------------------------------------------------------------
 *	AMXX init function declarations.
 * -------------------------------------------------------------------------------------------
 */

#define AMXX_QUERY Main
/* #undef AMXX_CHECK_GAME */
#define AMXX_ATTACH OnAmxxAttach
#define AMXX_DETACH OnAmxxDetach
#define AMXX_PLUGINS_LOADED OnAmxxPluginsLoaded
/* #undef AMXX_PLUGINS_UNLOADED */
/* #undef AMXX_PLUGINS_UNLOADING */

namespace amxx
{
    /*
    * -------------------------------------------------------------------------------------------
    *	AMXX module info.
    * -------------------------------------------------------------------------------------------
    */
#ifndef USE_METAMOD
    constexpr auto MODULE_NAME = "Next Client API";
    constexpr auto MODULE_VERSION = "1.6.0";
    constexpr auto MODULE_AUTHOR = "Next21 Team";
    constexpr auto MODULE_LOG_TAG = "nclapi";
    constexpr auto MODULE_URL = "https://github.com/CS-NextClient/NextClientServerApi";
    constexpr auto MODULE_DATE = __DATE__;
#else
    constexpr auto MODULE_NAME = metamod::PLUGIN_NAME;
    constexpr auto MODULE_VERSION = metamod::PLUGIN_VERSION;
    constexpr auto MODULE_AUTHOR = metamod::PLUGIN_AUTHOR;
    constexpr auto MODULE_URL = metamod::PLUGIN_URL;
    constexpr auto MODULE_LOG_TAG = metamod::PLUGIN_LOG_TAG;
    constexpr auto MODULE_DATE = metamod::PLUGIN_DATE;
#endif
    constexpr auto MODULE_LIBRARY = "nextclientapi";
    constexpr auto MODULE_LIB_CLASS = "nextclientapi_amxx";
    constexpr auto MODULE_RELOAD_ON_MAP_CHANGE = false; // Only for amxx modules without metamod.
}
