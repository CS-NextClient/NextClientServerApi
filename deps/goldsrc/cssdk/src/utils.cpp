/*
 *  Half Life 1 SDK Copyright(c) Valve Corp.
 *
 *  THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE CORPORATION ("Valve").
 *  PLEASE READ IT BEFORE DOWNLOADING OR USING THE HALF LIFE 1 SDK ("SDK"). BY
 *  DOWNLOADING AND/OR USING THE HALF LIFE 1 SDK YOU ACCEPT THIS LICENSE. IF YOU DO
 *  NOT AGREE TO THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.
 *
 *  You may, free of charge, download and use the SDK to develop a modified Valve
 *  game running on the Half-Life 1 engine. You may distribute your modified Valve
 *  game in source and object code form, but only for free. Terms of use for Valve
 *  games are found in the Steam Subscriber Agreement located here:
 *  http://store.steampowered.com/subscriber_agreement/
 *
 *  You may copy, modify, and distribute the SDK and any modifications you make to
 *  the SDK in source and object code form, but only for free. Any distribution of
 *  this SDK must include this LICENSE file.
 *
 *  Any distribution of the SDK or a substantial portion of the SDK must include
 *  the above copyright notice and the following:
 *
 *    DISCLAIMER OF WARRANTIES. THE HALF LIFE 1 SDK AND ANY OTHER MATERIAL
 *    DOWNLOADED BY LICENSEE IS PROVIDED "AS IS". VALVE AND ITS SUPPLIERS
 *    DISCLAIM ALL WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS OR IMPLIED,
 *    INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY,
 *    NON-INFRINGEMENT, TITLE AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    LIMITATION OF LIABILITY. IN NO EVENT SHALL VALVE OR ITS SUPPLIERS BE LIABLE
 *    FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 *    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
 *    LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THE ENGINE AND/OR THE
 *    SDK, EVEN IF VALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *  If you would like to use the SDK for a commercial purpose, please contact Valve
 *  at sourceengine@valvesoftware.com.
 */

#include <cssdk/public/utils.h>
#include <cssdk/dll/entity_base.h>
#include <cstring>

using namespace cssdk;

namespace
{
    void MessageBegin(const MessageType msg_type, const int msg_id, const float* const origin = nullptr,
                      Edict* const client = nullptr)
    {
        g_engine_funcs.message_begin(msg_type, msg_id, origin, client);
    }

    void WriteShort(const int value)
    {
        g_engine_funcs.write_short(value);
    }

    void WriteByte(const int value)
    {
        g_engine_funcs.write_byte(value);
    }

    void WriteString(const char* value)
    {
        g_engine_funcs.write_string(value);
    }

    void MessageEnd()
    {
        g_engine_funcs.message_end();
    }
}

namespace cssdk
{
    bool IsBot(Edict* const client)
    {
        if (client->vars.flags & FL_FAKE_CLIENT) {
            return true;
        }

        const auto* auth = g_engine_funcs.get_player_auth_id(client);

        return !auth || !std::strcmp(auth, "BOT");
    }

    bool IsHltv(Edict* const client)
    {
        if (client->vars.flags & FL_PROXY) {
            return true;
        }

        const auto* auth = g_engine_funcs.get_player_auth_id(client);

        return auth && !std::strcmp(auth, "HLTV");
    }

    void HudMessage(EntityBase* const entity, const HudTextParams& hud_params, const char* message, Edict* const client)
    {
        if (constexpr auto svc_temp_entity = static_cast<int>(SvcMessage::TempEntity); entity) {
            if (!entity->IsNetClient()) {
                return;
            }

            MessageBegin(MessageType::OneUnreliable, svc_temp_entity, nullptr, client);
        }
        else {
            MessageBegin(MessageType::Broadcast, svc_temp_entity);
        }

        WriteByte(TE_TEXT_MESSAGE);
        WriteByte(hud_params.channel & 0xFF);
        WriteShort(FixedSigned16(hud_params.x, 1 << 13));
        WriteShort(FixedSigned16(hud_params.y, 1 << 13));
        WriteByte(hud_params.effect);
        WriteByte(hud_params.red1);
        WriteByte(hud_params.green1);
        WriteByte(hud_params.blue1);
        WriteByte(hud_params.alpha1);
        WriteByte(hud_params.red2);
        WriteByte(hud_params.green2);
        WriteByte(hud_params.blue2);
        WriteByte(hud_params.alpha2);
        WriteShort(FixedUnsigned16(hud_params.fade_in_time, 1 << 8));
        WriteShort(FixedUnsigned16(hud_params.fade_out_time, 1 << 8));
        WriteShort(FixedUnsigned16(hud_params.hold_time, 1 << 8));

        if (hud_params.effect == 2) {
            WriteShort(FixedUnsigned16(hud_params.fx_time, 1 << 8));
        }

        if (!message) {
            WriteString(" ");
        }
        else if (std::strlen(message) > 489) {
            // The maximum net message size is 512. There are only 489 bytes left for the string.
            char string[489];
            std::strncpy(string, message, sizeof string - 1);
            string[sizeof string - 1] = '\0';
            WriteString(string);
        }
        else {
            WriteString(message);
        }

        MessageEnd();
    }

    void HudMessage(Edict* const client, const HudTextParams& hud_params, const char* message)
    {
        if (client) {
            auto* entity = EntityPrivateData<EntityBase>(client);
            HudMessage(entity, hud_params, message, client);
        }
        else {
            HudMessage(nullptr, hud_params, message, nullptr);
        }
    }

    void HudMessage(const int client, const HudTextParams& hud_params, const char* message)
    {
        if (client) {
            auto* edict = g_engine_funcs.entity_of_ent_index(client);
            HudMessage(edict, hud_params, message);
        }
        else {
            HudMessage(nullptr, hud_params, message, nullptr);
        }
    }
}
