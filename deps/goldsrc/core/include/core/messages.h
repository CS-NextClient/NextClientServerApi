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
#include <core/strings/format.h>
#include <cssdk/common/const.h>
#include <cssdk/dll/cdll_dll.h>
#include <cssdk/engine/edict.h>
#include <cssdk/public/os_defs.h>

namespace core::messages
{
    enum class SayTextTeamColor
    {
        /**
         * @brief Default color.
        */
        Default = 0,

        /**
         * @brief Grey color.
        */
        Grey = 33,

        /**
         * @brief Red color.
        */
        Red,

        /**
         * @brief Blue color.
        */
        Blue
    };

    /**
     * @brief Sends a text message to clients.
    */
    void SendTextMessage(cssdk::Edict* client, cssdk::HudPrint dest, const std::string& text);

    /**
     * @brief Sends chat message to clients.
    */
    void SendChatMessage(cssdk::Edict* client, int sender, const std::string& text);

    /**
     * @brief Sends colored chat message to clients.
    */
    void SendChatColorMessage(cssdk::Edict* client, const std::string& text,
                              SayTextTeamColor color = SayTextTeamColor::Default);
    /**
     * @brief Sends colored chat message to clients.
    */
    void SendChatColorMessage(cssdk::Edict* client, int sender, const std::string& text,
                              SayTextTeamColor color = SayTextTeamColor::Default);
    /**
     * @brief Sends a HUD message to clients.
    */
    void SendHudMessage(cssdk::Edict* client, const cssdk::HudTextParams& hud_params, const std::string& text);

    /**
     * @brief Sends a text message to clients.
    */
    template <typename... Args>
    ATTR_MINSIZE void SendTextMessage(cssdk::Edict* const client, const cssdk::HudPrint dest,
                                      const std::string& format, Args&&... args)
    {
        const auto& text = str::Format(format, std::forward<Args>(args)...);
        SendTextMessage(client, dest, text);
    }

    /**
     * @brief Sends chat message to clients.
    */
    template <typename... Args>
    ATTR_MINSIZE void SendChatMessage(cssdk::Edict* const client, const int sender,
                                      const std::string& format, Args&&... args)
    {
        const auto& text = str::Format(format, std::forward<Args>(args)...);
        SendChatMessage(client, sender, text);
    }

    /**
     * @brief Sends colored chat message to clients.
    */
    template <SayTextTeamColor Color = SayTextTeamColor::Default, typename... Args>
    ATTR_MINSIZE void SendChatColorMessage(cssdk::Edict* const client,
                                           const std::string& format, Args&&... args)
    {
        const auto& text = str::Format(format, std::forward<Args>(args)...);
        SendChatColorMessage(client, text, Color);
    }

    /**
     * @brief Sends colored chat message to clients.
    */
    template <SayTextTeamColor Color = SayTextTeamColor::Default, typename... Args>
    ATTR_MINSIZE void SendChatColorMessage(cssdk::Edict* const client, const int sender,
                                           const std::string& format, Args&&... args)
    {
        const auto& text = str::Format(format, std::forward<Args>(args)...);
        SendChatColorMessage(client, sender, text, Color);
    }

    /**
     * @brief Sends a HUD message to clients.
    */
    template <typename... Args>
    ATTR_MINSIZE void SendHudMessage(cssdk::Edict* const client, const cssdk::HudTextParams& hud_params,
                                     const std::string& format, Args&&... args)
    {
        const auto& text = str::Format(format, std::forward<Args>(args)...);
        SendHudMessage(client, hud_params, text);
    }
}
#endif
