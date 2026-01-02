#include "DeathMsgWpnIcon.h"
#include "utils/utilfuncs.h"

DeathMsgWpnIcon::DeathMsgWpnIcon(GameEventsManager& game_events_manager)
{
    game_events_manager.on_server_activated().connect(&DeathMsgWpnIcon::ServerActivatedHandler, this);
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
    if (recipient_id != 0)
    {
        MESSAGE_BEGIN(MSG_ONE, message_deathmsg_wpn_icon_, nullptr, INDEXENT(recipient_id));
    }
    else
    {
        MESSAGE_BEGIN(MSG_ALL, message_deathmsg_wpn_icon_);
    }
    WRITE_STRING(sprite.c_str());
    WRITE_BYTE(frame);
    WRITE_BYTE(rendermode);
    WRITE_BYTE(r);
    WRITE_BYTE(g);
    WRITE_BYTE(b);
    WRITE_BYTE(a);
    MESSAGE_END();
}

void DeathMsgWpnIcon::ServerActivatedHandler(ServerActivatedEvent server_activated_event)
{
    message_deathmsg_wpn_icon_ = utils::RegUserMsgSafe("DeathMsgWpn", -1);
}
