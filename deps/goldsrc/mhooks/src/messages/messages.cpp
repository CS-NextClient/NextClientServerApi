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

#ifdef HAS_METAMOD_LIB
#include "../hookchain_manager.h"
#include "block_message.h"
#include "consts.h"
#include "message.h"
#include "message_mhok.h"
#include <mhooks/messages/messages.h>
#include <core/strings/examination.h>
#include <mhooks/messages/message_args.h>
#include <mhooks/messages/message_mhookchain.h>
#include <mhooks/metamod/engine.h>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

using namespace core;
using namespace cssdk;
using namespace metamod;
using namespace mhooks;
using namespace mhooks::detail;

namespace // Message hooks
{
    bool g_skip_message_begin{false};
    bool g_skip_message_args{true};

    std::array<MHook*, 11>* g_hooks{};
    std::array<std::size_t, MAX_MESSAGES + 1> g_hooked_messages{};

    MessageArgs* g_msg_args{};
    BlockMessage* g_block_message{};
    Message* g_network_message{};
    HookChainManager<MessageMHookChain>* g_hookchain_manager{};

    struct MessageBeginArgs
    {
        int id{};
        MessageType type{};
        Edict* client{};
        float* origin{};
    } g_msg_begin_args{};

    void OnMessageBegin(const EngineMessageBeginMChain& chain, const MessageType type,
                        const int id, const float* const origin, Edict* const client)
    {
        chain.CallNext(type, id, origin, client);

        if (g_skip_message_begin || !IsValidMessageId(id) || !g_hooked_messages[id]) {
            return;
        }

        g_msg_begin_args.id = id;
        g_msg_begin_args.type = type;
        g_msg_begin_args.client = client;
        g_msg_begin_args.origin = const_cast<float*>(origin); // NOLINT(cppcoreguidelines-pro-type-const-cast)

        g_skip_message_args = false;
        g_msg_args->GetArgs().clear();
        g_network_message->ArgTypes().clear();

        SetResult(Result::Supercede);
    }

    void OnMessageWriteByte(const EngineWriteByteMChain& chain, const int value)
    {
        chain.CallNext(value);

        if (!g_skip_message_args) {
            g_msg_args->GetArgs().emplace_back(value);
            g_network_message->ArgTypes().push_back(MessageArgType::Byte);
            SetResult(Result::Supercede);
        }
    }

    void OnMessageWriteChar(const EngineWriteCharMChain& chain, const int value)
    {
        chain.CallNext(value);

        if (!g_skip_message_args) {
            g_msg_args->GetArgs().emplace_back(value);
            g_network_message->ArgTypes().push_back(MessageArgType::Char);
            SetResult(Result::Supercede);
        }
    }

    void OnMessageWriteShort(const EngineWriteShortMChain& chain, const int value)
    {
        chain.CallNext(value);

        if (!g_skip_message_args) {
            g_msg_args->GetArgs().emplace_back(value);
            g_network_message->ArgTypes().push_back(MessageArgType::Short);
            SetResult(Result::Supercede);
        }
    }

    void OnMessageWriteLong(const EngineWriteLongMChain& chain, const int value)
    {
        chain.CallNext(value);

        if (!g_skip_message_args) {
            g_msg_args->GetArgs().emplace_back(value);
            g_network_message->ArgTypes().push_back(MessageArgType::Long);
            SetResult(Result::Supercede);
        }
    }

    void OnMessageWriteAngle(const EngineWriteAngleMChain& chain, const float value)
    {
        chain.CallNext(value);

        if (!g_skip_message_args) {
            g_msg_args->GetArgs().emplace_back(value);
            g_network_message->ArgTypes().push_back(MessageArgType::Angle);
            SetResult(Result::Supercede);
        }
    }

    void OnMessageWriteCoord(const EngineWriteCoordMChain& chain, const float value)
    {
        chain.CallNext(value);

        if (!g_skip_message_args) {
            g_msg_args->GetArgs().emplace_back(value);
            g_network_message->ArgTypes().push_back(MessageArgType::Coord);
            SetResult(Result::Supercede);
        }
    }

    void OnMessageWriteString(const EngineWriteStringMChain& chain, const char* const value)
    {
        chain.CallNext(value);

        if (!g_skip_message_args) {
            g_msg_args->GetArgs().emplace_back(value);
            g_network_message->ArgTypes().push_back(MessageArgType::String);
            SetResult(Result::Supercede);
        }
    }

    void OnMessageWriteEntity(const EngineWriteEntityMChain& chain, const int value)
    {
        chain.CallNext(value);

        if (!g_skip_message_args) {
            g_msg_args->GetArgs().emplace_back(value);
            g_network_message->ArgTypes().push_back(MessageArgType::Entity);
            SetResult(Result::Supercede);
        }
    }

    void OnMessageEnd(const EngineMessageEndMChain& chain)
    {
        chain.CallNext();

        if (g_skip_message_args || g_skip_message_begin) {
            return;
        }

        SetResult(Result::Supercede);
        g_block_message->SetOriginalBlock(g_msg_begin_args.id);

        if (g_hookchain_manager->StartChain(g_msg_begin_args.type, g_msg_begin_args.id,
                                            g_msg_begin_args.origin, g_msg_begin_args.client, *g_msg_args)) {
            g_block_message->SetCurrentBlock(g_msg_begin_args.id, false);
        }
    }

    void OnMessageEndPost(const EngineMessageEndMChain& chain)
    {
        chain.CallNext();

        if (g_skip_message_args || g_skip_message_begin) {
            return;
        }

        g_skip_message_begin = true;
        g_skip_message_args = true;

        if (!g_block_message->GetCurrentBlock(g_msg_begin_args.id)) {
            g_network_message->Send(g_msg_begin_args.type, g_msg_begin_args.id,
                                    g_msg_begin_args.origin, g_msg_begin_args.client, *g_msg_args);
        }

        g_skip_message_begin = false;

        if (g_hooked_messages[g_msg_begin_args.id] > 0) {
            g_block_message->SetCurrentBlock(g_msg_begin_args.id, false);
        }
    }

    ATTR_MINSIZE void ToggleHooksState(const bool enable)
    {
        assert(g_hooks != nullptr);

        if (enable) {
            for (auto* const hook : *g_hooks) {
                hook->Enable();
            }
        }
        else {
            for (auto* const hook : *g_hooks) {
                hook->Disable();
            }
        }
    }

    ATTR_MINSIZE void OnHookChainManagerEmpty()
    {
        if (g_hooks != nullptr) {
            for (const auto* const hook : *g_hooks) {
                delete hook;
            }
        }

        delete g_hooks; // cppcheck-suppress autovarInvalidDeallocation
        g_hooks = nullptr;

        delete g_msg_args;
        g_msg_args = nullptr;

        delete g_block_message;
        g_block_message = nullptr;

        delete g_network_message;
        g_network_message = nullptr;

        delete g_hookchain_manager;
        g_hookchain_manager = nullptr;
    }

    ATTR_MINSIZE void OnMessageHookNotify(const MHook* const hook, const MHookNotice notice)
    {
        assert(hook != nullptr);

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
        if (const auto message_id = static_cast<const MessageMHook*>(hook)->MessageId(); IsValidMessageId(message_id)) {
            if (notice == MHookNotice::Enable) {
                assert(g_block_message != nullptr);

                if ((++g_hooked_messages[message_id]) == 1) {
                    g_block_message->SetCurrentBlock(message_id, true);
                }

                ToggleHooksState(true);
            }
            else if (notice == MHookNotice::Disable) {
                assert(g_block_message != nullptr);
                assert(g_hookchain_manager != nullptr);

                if (g_hooked_messages[message_id] > 0 && (--g_hooked_messages[message_id]) == 0) {
                    g_block_message->RestoreOriginalBlock(message_id);
                }

                if (g_hookchain_manager->HookChainInstance().EnabledHooksCount() == 0) {
                    ToggleHooksState(false);
                }
            }
        }
    }

    ATTR_MINSIZE FORCEINLINE MHook* CreateMessageHook(const std::string_view message, const NetworkMessageMCallback& callback,
                                                      const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        assert(!core::str::IsEmptyOrWhiteSpace(message));

        if (g_hookchain_manager == nullptr) {
            g_hookchain_manager = new HookChainManager{MessageMHookChain{}, OnHookChainManagerEmpty};
        }

        if (g_hooks == nullptr) {
            g_skip_message_begin = false;
            g_skip_message_args = true;
            g_hooked_messages.fill(0);

            g_msg_args = new MessageArgs{};
            g_block_message = new BlockMessage{};
            g_network_message = new Message{};
            g_hooks = new std::array<MHook*, 11>{};

            g_hooks->at(0) = MHookEngineMessageBegin(DELEGATE_ARG<OnMessageBegin>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(1) = MHookEngineWriteByte(DELEGATE_ARG<OnMessageWriteByte>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(2) = MHookEngineWriteChar(DELEGATE_ARG<OnMessageWriteChar>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(3) = MHookEngineWriteShort(DELEGATE_ARG<OnMessageWriteShort>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(4) = MHookEngineWriteLong(DELEGATE_ARG<OnMessageWriteLong>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(5) = MHookEngineWriteAngle(DELEGATE_ARG<OnMessageWriteAngle>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(6) = MHookEngineWriteCoord(DELEGATE_ARG<OnMessageWriteCoord>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(7) = MHookEngineWriteString(DELEGATE_ARG<OnMessageWriteString>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(8) = MHookEngineWriteEntity(DELEGATE_ARG<OnMessageWriteEntity>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(9) = MHookEngineMessageEnd(DELEGATE_ARG<OnMessageEnd>, false, HookChainPriority::Uninterruptable, false);
            g_hooks->at(10) = MHookEngineMessageEnd(DELEGATE_ARG<OnMessageEndPost>, true, HookChainPriority::Uninterruptable, false);
        }

        auto* const hook = new MessageMHook{priority, false, std::string{message}};
        g_hookchain_manager->AddHook(hook, callback);

        hook->Subscribe<OnMessageHookNotify>();
        hook->Toggle(enable);

        return hook;
    }
}

namespace // Event hooks
{
    std::vector<std::pair<const MHook*, const GameEventMCallback*>>* g_event_hooks{};

    ATTR_OPTIMIZE_HOT bool OnEngineMessage(const void* const data, const NetworkMessageMChain& chain, MessageType& type,
                                           const int id, float*& origin, Edict*& client, MessageArgs& args)
    {
        assert(data != nullptr);
        const auto result = chain.CallNext(type, id, origin, client, args);

        if (!result) {
            static_cast<const GameEventMCallback*>(data)->operator()(type, id, origin, client, args);
        }

        return result;
    }

    ATTR_MINSIZE void OnEventHookNotify(const MHook* const hook, const MHookNotice notice)
    {
        assert(hook != nullptr);
        assert(g_event_hooks != nullptr);

        if (notice != MHookNotice::Destroy) {
            return;
        }

        const auto& it = std::find_if(g_event_hooks->cbegin(), g_event_hooks->cend(), [hook](const auto& element) {
            return element.first == hook;
        });

        assert(it != g_event_hooks->cend());
        delete it->second;
        g_event_hooks->erase(it);

        if (g_event_hooks->empty()) {
            delete g_event_hooks;
            g_event_hooks = nullptr;
        }
    }

    ATTR_MINSIZE FORCEINLINE MHook* CreateEventHook(const std::string_view message, const GameEventMCallback& callback,
                                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        assert(!core::str::IsEmptyOrWhiteSpace(message));

        if (g_event_hooks == nullptr) {
            g_event_hooks = new std::vector<std::pair<const MHook*, const GameEventMCallback*>>{};
        }

        const auto* const event_callback = new GameEventMCallback{callback};
        auto* const hook = CreateMessageHook(message, {&OnEngineMessage, event_callback}, priority, enable);

        g_event_hooks->emplace_back(std::make_pair(hook, event_callback));
        hook->Subscribe<OnEventHookNotify>();

        return hook;
    }
}

namespace mhooks
{
    MHook* MHookNetworkMessage(const std::string_view message, const NetworkMessageMCallback callback,
                               const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        assert(!core::str::IsEmptyOrWhiteSpace(message));

        return CreateMessageHook(message, callback, priority, enable);
    }

    MHook* MHookGameEvent(const std::string_view message, const GameEventMCallback callback,
                          const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        assert(!core::str::IsEmptyOrWhiteSpace(message));

        return CreateEventHook(message, callback, priority, enable);
    }
}
#endif
