#include "HealthNext.h"
#include <easylogging++.h>
#include "utils/utilfuncs.h"

HealthNext::HealthNext(GameEventsManager& game_events_manager, INextClientInfo& next_client_info) :
    next_client_info_(next_client_info)
{
    game_events_manager.on_server_activated().connect(&HealthNext::ServerActivatedHandler, this);
    game_events_manager.on_message_begin_post().connect(&HealthNext::MessageBeginPostHandler, this);
    game_events_manager.on_message_end_post().connect(&HealthNext::MessageEndPostHandler, this);
}

void HealthNext::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_HealthNEx_ = utils::RegUserMsgSafe("HealthNEx", -1);
    message_Health_ = GET_USER_MSG_ID(&Plugin_info, "Health", NULL);
}

void HealthNext::MessageBeginPostHandler(MessageBeginPostEvent event)
{
    NextClientVersion version;
    if (event.ed == nullptr || !next_client_info_.GetNextClientVersion(ENTINDEX(event.ed), version))
        return;

    if (event.msg_type == message_Health_
        && event.ed != nullptr
        && event.ed->v.health > 255
        && version >= NextClientVersion{2, 2, 0})
    {
        should_send_health_ex_ = true;

        msg_save_hp_ = version >= NextClientVersion{2, 3, 0} ? (int)event.ed->v.health : std::min((int)event.ed->v.health, 999);
        msg_save_dest_ = event.msg_dest;
        msg_save_ed_ = event.ed;

        if (event.pOrigin)
        {
            memcpy(msg_save_origin_, event.pOrigin, sizeof(msg_save_origin_));
        }
        else
        {
            memset(msg_save_origin_, 0, sizeof(msg_save_origin_));
        }
    }
}

void HealthNext::MessageEndPostHandler()
{
    if (should_send_health_ex_)
    {
        should_send_health_ex_ = false;

        MESSAGE_BEGIN(msg_save_dest_, message_HealthNEx_, msg_save_origin_, msg_save_ed_);
        WRITE_LONG(msg_save_hp_);
        MESSAGE_END();
    }
}
