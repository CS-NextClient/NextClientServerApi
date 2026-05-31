#include "DeathMsgWpnIcon.h"

#include <metamod/engine.h>
#include <core/type_conversion.h>

#include "utils/msg_ex.h"

using namespace metamod;
using namespace core;
using namespace msg_ex;

DeathMsgWpnIcon::DeathMsgWpnIcon(ServerEventsManager& server_events_manager)
{
    server_events_manager.on_server_activated().connect(&DeathMsgWpnIcon::ServerActivatedHandler, this);
}

void DeathMsgWpnIcon::SetIconForNextMessage(
    const std::string& sprite,
    int frame,
    int rendermode,
    int r,
    int g,
    int b,
    int a,
    int recipient_id
)
{
    if (message_deathmsg_wpn_icon_ <= 0)
        return;

    if (recipient_id != 0)
    {
        MessageBegin(cssdk::MessageType::One, message_deathmsg_wpn_icon_, nullptr, type_conversion::EdictByIndex(recipient_id));
    }
    else
    {
        MessageBegin(cssdk::MessageType::All, message_deathmsg_wpn_icon_);
    }
    WriteString(sprite.c_str());
    WriteByte(frame);
    WriteByte(rendermode);
    WriteByte(r);
    WriteByte(g);
    WriteByte(b);
    WriteByte(a);
    MessageEnd();
}

void DeathMsgWpnIcon::ServerActivatedHandler(ServerActivatedEvent server_activated_event)
{
    message_deathmsg_wpn_icon_ = RegUserMsgSafe("DeathMsgWpn", -1);
}
