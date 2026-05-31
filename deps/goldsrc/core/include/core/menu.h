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

#if defined(HAS_AMXX_LIB) && defined(HAS_METAMOD_LIB) && defined(HAS_MHOOKS_LIB)
#include <core/delegate.h>
#include <core/type_conversion.h>
#include <cssdk/public/utils.h>
#include <mhooks/messages.h>
#include <mhooks/metamod.h>
#include <array>
#include <cassert>
#include <string_view>
#include <vector>

namespace core
{
    /**
     * @brief Menu handler delegate.
    */
    using MenuHandler = Delegate<void(cssdk::Edict* client, int selected_item)>;

    class Menu
    {
        MenuHandler handler_;
        std::vector<std::unique_ptr<mhooks::MHook>> hooks_{};

        std::array<int, cssdk::MAX_CLIENTS + 1> keys_{};
        std::array<int*, cssdk::MAX_CLIENTS + 1> player_prop_menu_{};
        std::array<int*, cssdk::MAX_CLIENTS + 1> player_prop_newmenu_{};

    public:
        /**
         * @brief Constructor.
         *
         * @param handler The menu handler function.
        */
        explicit Menu(MenuHandler handler = nullptr);

        /**
         * @brief Destructor.
        */
        ~Menu() = default;

        /**
         * @brief Move constructor.
        */
        Menu(Menu&& other) noexcept;

        /**
         * @brief Copy constructor.
        */
        Menu(const Menu&) = delete;

        /**
         * @brief Move assignment operator.
        */
        Menu& operator=(Menu&& other) noexcept;

        /**
         * @brief Copy assignment operator.
        */
        Menu& operator=(const Menu& other) = delete;

        /**
         * @brief Displays the menu to one client. Returns \c true if successful; \c false otherwise.
        */
        bool Show(cssdk::Edict* client, int keys, std::string_view text, int time = -1);

        /**
         * @brief Displays the menu to all clients. Returns \c true if successful; \c false otherwise.
        */
        bool Show(int keys, std::string_view text, int time = -1);

        /**
         * @brief Closes the menu for the specified player (or all players if \c client is \c nullptr).
        */
        void Close(cssdk::Edict* client);

        /**
         * @brief Sets the menu handler function.
        */
        void SetHandler(const MenuHandler handler)
        {
            handler_ = handler;
        }

        /**
         * @brief Invokes the menu handler function.
        */
        void InvokeHandler(cssdk::Edict* const client, const int selected_item) const
        {
            if (handler_) {
                handler_(client, selected_item);
            }
        }

        /**
         * @brief Returns \c true if the menu is open for the specified player; \c false otherwise.
        */
        [[nodiscard]] bool IsOpen(const int player) const
        {
            assert(cssdk::IsClient(player));
            return keys_[player] != 0;
        }

        /**
         * @brief Returns \c true if the menu is open for the specified player; \c false otherwise.
        */
        [[nodiscard]] bool IsOpen(const cssdk::Edict* const player) const
        {
            return IsOpen(type_conversion::IndexOfEntity(player));
        }

        /**
         * @brief Returns \c true if the menu is open for the specified player; \c false otherwise.
        */
        [[nodiscard]] bool IsOpen(const cssdk::EntityBase* const player) const
        {
            return IsOpen(type_conversion::IndexOfEntity(player));
        }

    private:
        void CreateHooks();
        void InitPlayerProps();
        void OnServerActivatePost(const GameDllServerActivateMChain& chain, cssdk::Edict* edict_list, int edict_count, int client_max);
        void OnShowMenu(cssdk::MessageType type, int id, const float* origin, const cssdk::Edict* client, const mhooks::MessageArgs& args);
        void OnClientCommand(const GameDllClientCommandMChain& chain, cssdk::Edict* client);
        void OnPlayerPreThink(const GameDllPlayerPreThinkMChain& chain, cssdk::Edict* client);
    };
}
#endif
