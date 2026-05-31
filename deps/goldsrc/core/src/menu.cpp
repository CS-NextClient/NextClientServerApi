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

#if defined(HAS_AMXX_LIB) && defined(HAS_METAMOD_LIB) && defined(HAS_MHOOKS_LIB)
#include <core/menu.h>
#include <amxx/api.h>
#include <core/strings.h>
#include <cssdk/public/utils.h>
#include <metamod/engine.h>
#include <metamod/utils.h>
#include <algorithm>
#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <utility>

using namespace core;
using namespace amxx;
using namespace cssdk;
using namespace mhooks;
using namespace metamod;

namespace
{
    auto TruncateMenuText(const std::string_view text)
    {
        return str::Utf8Truncate(std::string{text}, 507);
    }

    bool SetPlayerMenuOff(PlayerBase* const player)
    {
        if (player->has_disconnected) {
            return false;
        }

        if (player->joining_state == JoinState::Joined ||
            (player->menu != MenuName::ChooseTeam && player->menu != MenuName::ChooseAppearance)) {
            player->menu = MenuName::Off;
        }

        return player->menu == MenuName::Off;
    }

    bool SetPlayerMenuOff(const Edict* const client)
    {
        return SetPlayerMenuOff(cssdk::EntityPrivateData<PlayerBase>(client));
    }

    bool SendShowMenu(Edict* const client, const int keys, const int time, const std::string& text)
    {
        static int msg_show_menu{};
        static EngineFunctions* engine_funcs{};
        assert(metamod::utils::detail::funcs != nullptr);

        if (!msg_show_menu && !((msg_show_menu = utils::GetUserMsgId("ShowMenu")))) {
            return false;
        }

        if (engine_funcs == nullptr) {
            utils::GetHookTables(&engine_funcs, nullptr, nullptr);

            if (engine_funcs == nullptr) {
                return false;
            }
        }

        const auto text_length = text.length();
        std::string_view::size_type sent{0};
        auto more = false;

        do {
            constexpr std::string_view::size_type chunk_size = 172; // Max 187
            const auto chunk = std::string{text.substr(sent, chunk_size)};

            sent += chunk_size;
            more = sent < text_length;

            engine_funcs->message_begin(MessageType::One, msg_show_menu, nullptr, client);
            engine_funcs->write_short(keys);
            engine_funcs->write_char(time);
            engine_funcs->write_byte(more);
            engine_funcs->write_string(chunk.c_str());
            engine_funcs->message_end();
        }
        while (more);

        return true;
    }
}

namespace core
{
    bool Menu::Show(Edict* const client, const int keys, const std::string_view text, const int time)
    {
        const auto client_index = type_conversion::IndexOfEntity(client);
        assert(IsClient(client_index));

        if (SetPlayerMenuOff(client) && SendShowMenu(client, keys, time, TruncateMenuText(text))) {
            keys_[client_index] = keys;
            return true;
        }

        return false;
    }

    bool Menu::Show(const int keys, const std::string_view text, const int time)
    {
        const auto max_clients = g_global_vars->max_clients;

        if (max_clients < 1 || max_clients > MAX_CLIENTS) {
            return false;
        }

        auto result{false};
        const auto text_copy{TruncateMenuText(text)};

        for (auto i = 1; i <= max_clients; ++i) {
            Edict* const client = type_conversion::EdictByIndex(i);

            if (!IsValidEntity(client) || IsBot(client) || IsHltv(client)) {
                continue;
            }

            if (SetPlayerMenuOff(client) && SendShowMenu(client, keys, time, text_copy)) {
                keys_[i] = keys;
                result = true;
            }
        }

        return result;
    }

    void Menu::Close(Edict* const client)
    {
        if (client) {
            assert(IsValidEntity(client));

            if (IsOpen(client)) {
                Show(client, 0, " ");
            }
        }
        else {
            if (const auto max_clients = g_global_vars->max_clients; max_clients > 0 && max_clients <= MAX_CLIENTS) {
                for (auto i = 1; i <= max_clients; ++i) {
                    if (IsOpen(i)) {
                        if (Edict* const edict = type_conversion::EdictByIndex(i); IsValidEntity(edict)) {
                            Show(edict, 0, " ");
                        }
                    }
                }
            }
        }
    }

    void Menu::InitPlayerProps()
    {
        player_prop_menu_.fill(nullptr);
        player_prop_newmenu_.fill(nullptr);

        for (auto i = 1; i <= g_global_vars->max_clients; ++i) {
            player_prop_menu_[i] = static_cast<int*>(PlayerPropAddress(i, PlayerProp::Menu));
            assert(player_prop_menu_[i] != nullptr);
        }

        for (auto i = 1; i <= g_global_vars->max_clients; ++i) {
            player_prop_newmenu_[i] = static_cast<int*>(PlayerPropAddress(i, PlayerProp::NewMenu));
            assert(player_prop_newmenu_[i] != nullptr);
        }
    }

    void Menu::OnServerActivatePost(const GameDllServerActivateMChain& chain, Edict* const edict_list,
                                    const int edict_count, const int client_max)
    {
        InitPlayerProps();
        chain.CallNext(edict_list, edict_count, client_max);
    }

    void Menu::OnShowMenu(const MessageType, const int, const float* const, const Edict* const client, const MessageArgs&)
    {
        if (!IsValidEntity(client)) {
            return;
        }

        if (const auto client_index = type_conversion::IndexOfEntity(client); IsClient(client_index)) {
            keys_[client_index] = 0;
        }
    }

    void Menu::OnClientCommand(const GameDllClientCommandMChain& chain, Edict* const client)
    {
        chain.CallNext(client);

        if (IsValidEntity(client)) {
            const auto client_index = type_conversion::IndexOfEntity(client);

            if (!IsClient(client_index) || !keys_[client_index]) {
                return;
            }

            if (const auto* const cmd = engine::CmdArgv(0); str::IsNullOrEmpty(cmd) || !str::Equals(cmd, "menuselect")) {
                return;
            }

            if (const auto* const cmd_arg = engine::CmdArgv(1); !str::IsNullOrWhiteSpace(cmd_arg)) {
                errno = 0;

                if (!handler_) {
                    keys_[client_index] = 0;
                }
                else if (auto selected_item = static_cast<int>(std::strtol(cmd_arg, nullptr, 10));
                         errno == 0 && selected_item != 0) {
                    selected_item = std::clamp(selected_item, 1, 10);

                    if (keys_[client_index] & (1 << (selected_item - 1))) {
                        keys_[client_index] = 0;
                        handler_(client, selected_item == 10 ? 0 : selected_item);
                    }
                }
            }
        }
    }

    void Menu::OnPlayerPreThink(const GameDllPlayerPreThinkMChain& chain, Edict* const client)
    {
        chain.CallNext(client);

        if (!IsValidEntity(client)) {
            return;
        }

        if (const auto client_index = type_conversion::IndexOfEntity(client);
            IsClient(client_index) && keys_[client_index]) {
            assert(player_prop_menu_[client_index] != nullptr);
            assert(player_prop_newmenu_[client_index] != nullptr);

            if ((client->vars.flags & FL_FAKE_CLIENT) || (client->vars.flags & FL_PROXY) ||
                *player_prop_menu_[client_index] != 0 || *player_prop_newmenu_[client_index] != -1) {
                keys_[client_index] = 0;
            }
        }
    }

    void Menu::CreateHooks()
    {
        hooks_.clear();

        hooks_.emplace_back(
            MHookGameEvent("ShowMenu", {DELEGATE_ARG<&Menu::OnShowMenu>, this}, HookChainPriority::Uninterruptable)
                ->Unique());

        hooks_.emplace_back(
            MHookGameEvent("VGUIMenu", {DELEGATE_ARG<&Menu::OnShowMenu>, this}, HookChainPriority::Uninterruptable)
                ->Unique());

        hooks_.emplace_back(
            MHookGameDllClientCommand({DELEGATE_ARG<&Menu::OnClientCommand>, this},
                                      false, HookChainPriority::Uninterruptable)
                ->Unique());

        hooks_.emplace_back(
            MHookGameDllPlayerPreThink({DELEGATE_ARG<&Menu::OnPlayerPreThink>, this},
                                       false, HookChainPriority::Uninterruptable)
                ->Unique());

        hooks_.emplace_back(
            MHookGameDllServerActivate({DELEGATE_ARG<&Menu::OnServerActivatePost>, this},
                                       true, HookChainPriority::Uninterruptable)
                ->Unique());
    }

    Menu::Menu(const MenuHandler handler)
        : handler_(handler)
    {
        keys_.fill(0);
        type_conversion::Init();
        InitPlayerProps();
        CreateHooks();
    }

    Menu::Menu(Menu&& other) noexcept // NOLINT(bugprone-exception-escape)
        : handler_(other.handler_)
    {
        *this = std::move(other);
    }

    Menu& Menu::operator=(Menu&& other) noexcept // NOLINT(bugprone-exception-escape)
    {
        keys_ = other.keys_;
        handler_ = other.handler_;
        player_prop_menu_ = other.player_prop_menu_;
        player_prop_newmenu_ = other.player_prop_newmenu_;

        // We cannot move the hooks (Delegates).
        // Because they will hold the old class pointer.
        // Create again.
        CreateHooks();

        return *this;
    }
}
#endif
