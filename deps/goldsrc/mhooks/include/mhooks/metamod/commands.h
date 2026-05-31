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

#ifdef HAS_METAMOD_LIB
#include <mhooks/metamod/gamedll.h>
#include <string>

using ClientCommandMCallback = core::Delegate<void(cssdk::Edict* client, const char* command, bool chat)>;
using ClientImpulseMCallback = core::Delegate<void(cssdk::byte impulse, const cssdk::Edict* client, const cssdk::UserCmd* cmd, unsigned int random_seed)>;

namespace mhooks
{
    /**
     * @brief Hooks the client impulse command.
    */
    ATTR_MINSIZE MHook* MHookClientImpulse(cssdk::byte impulse, ClientImpulseMCallback callback, bool enable = true);

    /**
     * @brief Hooks the client chat command.
    */
    ATTR_MINSIZE MHook* MHookClientCommandChat(std::string command, ClientCommandMCallback callback, bool enable = true);

    /**
     * @brief Hooks the client console command.
    */
    ATTR_MINSIZE MHook* MHookClientCommandConsole(std::string command, ClientCommandMCallback callback, bool enable = true);
}
#endif
