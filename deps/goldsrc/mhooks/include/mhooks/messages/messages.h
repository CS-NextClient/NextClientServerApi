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
#include <core/delegate.h>
#include <metamod/engine_hooks.h>
#include <mhooks/common/mhook.h>
#include <mhooks/messages/message_args.h>
#include <mhooks/messages/message_mhookchain.h>
#include <string_view>

// Message
using NetworkMessageMChain = mhooks::MessageMHookChain;
using NetworkMessageMCallback = core::Delegate<bool(const NetworkMessageMChain& chain, cssdk::MessageType& type, int id, float*& origin, cssdk::Edict*& client, mhooks::MessageArgs& args)>;

// GameEvent
using GameEventMChain = NetworkMessageMChain;
using GameEventMCallback = core::Delegate<void(cssdk::MessageType type, int id, const float* origin, const cssdk::Edict* client, const mhooks::MessageArgs& args)>;

namespace mhooks
{
    /**
     * @brief Hooks the network message by name.
     *
     * @param message Message to hook.
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
     *
     * @note Return \c true from the hook to block the message, \c false otherwise;
    */
    ATTR_MINSIZE MHook* MHookNetworkMessage(std::string_view message, NetworkMessageMCallback callback,
                                            cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal,
                                            bool enable = true);
    /**
     * @brief This is the same as the \c MHookNetworkMessage,
     * except that you cannot change the message arguments or block the message.
     *
     * @param message Message to hook.
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookGameEvent(std::string_view message, GameEventMCallback callback,
                                       cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal,
                                       bool enable = true);
}
#endif
