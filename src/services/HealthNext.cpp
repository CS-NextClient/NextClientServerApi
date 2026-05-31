#include "HealthNext.h"

#include <easylogging++.h>

#include <metamod/utils.h>
#include <core/type_conversion.h>

#include "utils/msg_ex.h"

using namespace metamod;
using namespace core;
using namespace msg_ex;

HealthNext::HealthNext(ServerEventsManager& server_events_manager, INextClientInfo& next_client_info) :
    next_client_info_(next_client_info)
{
    server_events_manager.on_server_activated().connect(&HealthNext::ServerActivatedHandler, this);
    server_events_manager.on_message_begin_post().connect(&HealthNext::MessageBeginPostHandler, this);
    server_events_manager.on_message_end_post().connect(&HealthNext::MessageEndPostHandler, this);
}

void HealthNext::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_HealthNEx_ = RegUserMsgSafe("HealthNEx", -1);
    message_Health_ = utils::GetUserMsgId("Health", &message_Health_);
}

void HealthNext::MessageBeginPostHandler(MessageBeginPostEvent event)
{
    NextClientVersion version;
    if (event.edict == nullptr || !next_client_info_.GetNextClientVersion(type_conversion::IndexOfEntity(event.edict), version))
    {
        return;
    }

    if (event.msg_id == message_Health_ && event.edict != nullptr && event.edict->vars.health > 255 &&
        version >= NextClientVersion{2, 2, 0})
    {
        should_send_health_ex_ = true;

        msg_save_hp_ = version >= NextClientVersion{2, 3, 0} ? static_cast<int>(event.edict->vars.health)
                                                             : std::min(static_cast<int>(event.edict->vars.health), 999);
        msg_save_dest_ = event.msg_dest;
        msg_save_ed_ = event.edict;

        if (event.origin)
        {
            memcpy(msg_save_origin_, event.origin, sizeof(msg_save_origin_));
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

        MessageBegin(msg_save_dest_, message_HealthNEx_, msg_save_origin_, msg_save_ed_);
        WriteInt(msg_save_hp_);
        MessageEnd();
    }
}
