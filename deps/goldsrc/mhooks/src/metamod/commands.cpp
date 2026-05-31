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
#include <mhooks/metamod/commands.h>
#include <core/strings/compare.h>
#include <core/strings/examination.h>
#include <cssdk/public/utils.h>
#include <metamod/engine.h>
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

using namespace std;
using namespace core;
using namespace cssdk;
using namespace mhooks;
using namespace metamod;

// ReSharper disable CppUseStructuredBinding
// ReSharper disable CppClangTidyModernizeLoopConvert

namespace client_impulse
{
    struct Data
    {
        MHook* hook{};
        cssdk::byte impulse{};
        ClientImpulseMCallback callback{};
    };

    MHook* g_cmd_start_hook{};
    vector<Data>* g_impulse_hooks{};

    ATTR_OPTIMIZE_HOT static void OnCmdStart(const GameDllCmdStartMChain& chain, const Edict* const client,
                                             const UserCmd* const cmd, const unsigned int random_seed)
    {
        chain.CallNext(client, cmd, random_seed);

        if (!IsValidEntity(client) || cmd == nullptr) {
            return;
        }

        assert(g_impulse_hooks != nullptr);
        const auto impulse = cmd->impulse;

        // NOLINTNEXTLINE(modernize-loop-convert)
        for (vector<Data>::size_type i = 0; i < g_impulse_hooks->size(); ++i) {
            if (const auto& data = g_impulse_hooks->at(i); data.impulse == impulse && data.hook->IsEnabled()) {
                data.callback(impulse, client, cmd, random_seed);
            }
        }
    }

    static void RemoveHook(const MHook* const hook)
    {
        assert(hook != nullptr);
        assert(g_impulse_hooks != nullptr);

        g_impulse_hooks->erase(remove_if(g_impulse_hooks->begin(), g_impulse_hooks->end(), [hook](const auto& element) {
                                   return element.hook == hook;
                               }),
                               g_impulse_hooks->end());
    }

    ATTR_MINSIZE static bool IsAllHooksDisabled()
    {
        assert(g_impulse_hooks != nullptr);

        constexpr auto predicate = [](const auto& element) {
            return element.hook->IsEnabled();
        };

        return std::all_of(g_impulse_hooks->cbegin(), g_impulse_hooks->cend(), predicate);
    }

    ATTR_MINSIZE static bool IsAllHooksDestroyed()
    {
        return g_impulse_hooks == nullptr || g_impulse_hooks->empty();
    }

    ATTR_MINSIZE static void OnHookNotify(const MHook* const hook, const MHookNotice notice)
    {
        assert(g_cmd_start_hook != nullptr);

        switch (notice) {
        case MHookNotice::Enable:
            g_cmd_start_hook->Enable();
            break;

        case MHookNotice::Disable:
            if (IsAllHooksDisabled()) {
                g_cmd_start_hook->Disable();
            }
            break;

        case MHookNotice::Destroy:
            RemoveHook(hook);

            if (IsAllHooksDestroyed()) {
                MHook::Destroy(g_cmd_start_hook);

                delete g_impulse_hooks;
                g_impulse_hooks = nullptr;
            }
            break;
        }
    }

    ATTR_MINSIZE static MHook* CreateHook(const cssdk::byte impulse, const ClientImpulseMCallback& callback,
                                          const bool enable)
    {
        auto* const hook = new MHook{HookChainPriority::Normal, false};
        Data data{hook, impulse, callback};

        if (g_cmd_start_hook == nullptr) {
            g_cmd_start_hook = MHookGameDllCmdStart(DELEGATE_ARG<OnCmdStart>, false);
        }

        if (g_impulse_hooks == nullptr) {
            g_impulse_hooks = new vector<Data>{};
        }

        g_impulse_hooks->emplace_back(data);
        hook->Subscribe<OnHookNotify>();
        hook->Toggle(enable);

        return hook;
    }
}

namespace client_command
{
    MHook* g_client_command_hook{};

    struct Data
    {
        MHook* hook{};
        string command{};
        ClientCommandMCallback callback{};
    };

    vector<Data>* g_chat_hooks{};
    vector<Data>* g_console_hooks{};

    ATTR_OPTIMIZE_HOT static void OnChatCommand(Edict* const client)
    {
        assert(client != nullptr);

        if (g_chat_hooks) {
            const auto* const text = engine::CmdArgv(1);

            if (str::IsNullOrEmpty(text)) {
                return;
            }

            // NOLINTNEXTLINE(modernize-loop-convert)
            for (vector<Data>::size_type i = 0; i < g_chat_hooks->size(); ++i) {
                if (const auto& data = g_chat_hooks->at(i); data.hook->IsEnabled() &&
                    str::IEquals(text, data.command.c_str())) {
                    data.callback(client, text, true);
                }
            }
        }
    }

    ATTR_OPTIMIZE_HOT static void OnConsoleCommand(const char* const command, Edict* const client)
    {
        assert(client != nullptr);
        assert(command != nullptr);

        if (g_console_hooks) {
            // NOLINTNEXTLINE(modernize-loop-convert)
            for (vector<Data>::size_type i = 0; i < g_console_hooks->size(); ++i) {
                if (const auto& data = g_console_hooks->at(i); data.hook->IsEnabled() &&
                    str::IEquals(command, data.command.c_str())) {
                    data.callback(client, command, false);
                }
            }
        }
    }

    ATTR_OPTIMIZE_HOT static void OnClientCommand(const GameDllClientCommandMChain& chain, Edict* const client)
    {
        chain.CallNext(client);

        if (IsValidEntity(client)) {
            if (const auto* const command = engine::CmdArgv(0); !str::IsNullOrEmpty(command)) {
                if (str::Equals(command, "say") || str::Equals(command, "say_team")) {
                    OnChatCommand(client);
                }
                else {
                    OnConsoleCommand(command, client);
                }
            }
        }
    }

    static void RemoveHook(const MHook* const hook)
    {
        assert(hook != nullptr);

        if (g_chat_hooks) {
            g_chat_hooks->erase(remove_if(g_chat_hooks->begin(), g_chat_hooks->end(), [hook](const auto& element) {
                                    return element.hook == hook;
                                }),
                                g_chat_hooks->end());
        }

        if (g_console_hooks) {
            g_console_hooks->erase(
                remove_if(g_console_hooks->begin(), g_console_hooks->end(), [hook](const auto& element) {
                    return element.hook == hook;
                }),
                g_console_hooks->end());
        }
    }

    ATTR_MINSIZE static bool IsAllHooksDisabled()
    {
        constexpr auto predicate = [](const auto& element) {
            return element.hook->IsEnabled();
        };

        if (g_chat_hooks) {
            if (std::any_of(g_chat_hooks->cbegin(), g_chat_hooks->cend(), predicate)) {
                return false;
            }
        }

        if (g_console_hooks) {
            if (std::any_of(g_console_hooks->cbegin(), g_console_hooks->cend(), predicate)) {
                return false;
            }
        }

        return true;
    }

    ATTR_MINSIZE static bool IsAllHooksDestroyed()
    {
        if (g_chat_hooks && !g_chat_hooks->empty()) {
            return false;
        }

        if (g_console_hooks && !g_console_hooks->empty()) {
            return false;
        }

        return true;
    }

    ATTR_MINSIZE static void OnHookNotify(const MHook* const hook, const MHookNotice notice)
    {
        assert(g_client_command_hook != nullptr);

        switch (notice) {
        case MHookNotice::Enable:
            g_client_command_hook->Enable();
            break;

        case MHookNotice::Disable:
            if (IsAllHooksDisabled()) {
                g_client_command_hook->Disable();
            }
            break;

        case MHookNotice::Destroy:
            RemoveHook(hook);

            if (IsAllHooksDestroyed()) {
                MHook::Destroy(g_client_command_hook);

                delete g_chat_hooks;
                g_chat_hooks = nullptr;

                delete g_console_hooks;
                g_console_hooks = nullptr;
            }
            break;
        }
    }

    ATTR_MINSIZE static MHook* CreateHook(string&& command, const ClientCommandMCallback& callback,
                                          const bool enable, const bool chat)
    {
        auto* const hook = new MHook{HookChainPriority::Normal, false};
        Data data{hook, std::move(command), callback};

        if (g_client_command_hook == nullptr) {
            g_client_command_hook = MHookGameDllClientCommand(DELEGATE_ARG<OnClientCommand>, false);
        }

        if (chat) {
            if (g_chat_hooks == nullptr) {
                g_chat_hooks = new vector<Data>{};
            }

            g_chat_hooks->emplace_back(std::move(data));
        }
        else {
            if (g_console_hooks == nullptr) {
                g_console_hooks = new vector<Data>{};
            }

            g_console_hooks->emplace_back(std::move(data));
        }

        hook->Subscribe<OnHookNotify>();
        hook->Toggle(enable);

        return hook;
    }
}

namespace mhooks
{
    MHook* MHookClientImpulse(const cssdk::byte impulse, const ClientImpulseMCallback callback, const bool enable)
    {
        assert(!!callback);
        return client_impulse::CreateHook(impulse, callback, enable);
    }

    MHook* MHookClientCommandChat(string command, const ClientCommandMCallback callback, const bool enable)
    {
        assert(!!callback);
        assert(!str::IsEmptyOrWhiteSpace(command));

        return client_command::CreateHook(std::move(command), callback, enable, true);
    }

    MHook* MHookClientCommandConsole(string command, const ClientCommandMCallback callback, const bool enable)
    {
        assert(!!callback);
        assert(!str::IsEmptyOrWhiteSpace(command));

        return client_command::CreateHook(std::move(command), callback, enable, false);
    }
}
#endif
