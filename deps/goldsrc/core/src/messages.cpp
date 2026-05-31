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
#include <core/messages.h>
#include <core/strings/mutation.h>
#include <cssdk/public/utils.h>
#include <metamod/engine.h>
#include <metamod/utils.h>

using namespace cssdk;
using namespace metamod;

namespace
{
    void SendMessageInternal(const int id, Edict* const client, const int dest, const std::string& text)
    {
        engine::MessageBegin(client ? MessageType::One : MessageType::All, id, nullptr, client);
        engine::WriteByte(dest);

        if (text.size() > 190) {
            const auto text_copy = core::str::Utf8Truncate(text, 190);
            engine::WriteString(text_copy.c_str());
        }
        else {
            engine::WriteString(text.c_str());
        }

        engine::MessageEnd();
    }
}

namespace core::messages
{
    void SendTextMessage(Edict* const client, const HudPrint dest, const std::string& text)
    {
        if (static auto msg_text = 0; msg_text || ((msg_text = utils::GetUserMsgId("TextMsg")))) {
            SendMessageInternal(msg_text, client, static_cast<int>(dest), text);
        }
    }

    void SendChatMessage(Edict* const client, const int sender, const std::string& text)
    {
        if (static auto msg_say_text = 0; msg_say_text || ((msg_say_text = utils::GetUserMsgId("SayText")))) {
            SendMessageInternal(msg_say_text, client, sender, text);
        }
    }

    void SendChatColorMessage(Edict* const client, const std::string& text, const SayTextTeamColor color)
    {
        const auto client_index = engine::IndexOfEdict(client);
        SendChatMessage(client, color == SayTextTeamColor::Default ? client_index : static_cast<int>(color), text);
    }

    void SendChatColorMessage(Edict* const client, const int sender, const std::string& text, const SayTextTeamColor color)
    {
        SendChatMessage(client, color == SayTextTeamColor::Default ? sender : static_cast<int>(color), text);
    }

    void SendHudMessage(Edict* const client, const HudTextParams& hud_params, const std::string& text)
    {
        if (constexpr auto svc_temp_entity = static_cast<int>(SvcMessage::TempEntity); client) {
            engine::MessageBegin(MessageType::OneUnreliable, svc_temp_entity, nullptr, client);
        }
        else {
            engine::MessageBegin(MessageType::Broadcast, svc_temp_entity);
        }

        engine::WriteByte(TE_TEXT_MESSAGE);
        engine::WriteByte(hud_params.channel & 0xFF);
        engine::WriteShort(FixedSigned16(hud_params.x, 1 << 13));
        engine::WriteShort(FixedSigned16(hud_params.y, 1 << 13));
        engine::WriteByte(hud_params.effect);
        engine::WriteByte(hud_params.red1);
        engine::WriteByte(hud_params.green1);
        engine::WriteByte(hud_params.blue1);
        engine::WriteByte(hud_params.alpha1);
        engine::WriteByte(hud_params.red2);
        engine::WriteByte(hud_params.green2);
        engine::WriteByte(hud_params.blue2);
        engine::WriteByte(hud_params.alpha2);
        engine::WriteShort(FixedUnsigned16(hud_params.fade_in_time, 1 << 8));
        engine::WriteShort(FixedUnsigned16(hud_params.fade_out_time, 1 << 8));
        engine::WriteShort(FixedUnsigned16(hud_params.hold_time, 1 << 8));

        if (hud_params.effect == 2) {
            engine::WriteShort(FixedUnsigned16(hud_params.fx_time, 1 << 8));
        }

        // The maximum net message size is 512 bytes. There are only 489 bytes left for the string.
        if (text.size() > 489) {
            const auto text_copy = str::Utf8Truncate(text, 489);
            engine::WriteString(text_copy.c_str());
        }
        else {
            engine::WriteString(text.c_str());
        }

        engine::MessageEnd();
    }
}
#endif
