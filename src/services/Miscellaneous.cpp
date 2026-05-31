#include "Miscellaneous.h"

#include <metamod/engine.h>
#include <core/type_conversion.h>

#include "utils/msg_ex.h"

using namespace metamod;
using namespace core;
using namespace msg_ex;

Miscellaneous::Miscellaneous(ServerEventsManager& server_events_manager)
{
    server_events_manager.on_server_activated().connect(&Miscellaneous::ServerActivatedHandler, this);
}

void Miscellaneous::ClientSetFOV(ClientId client, int fov, float lerp_time)
{
    MessageBegin(cssdk::MessageType::One, message_set_fov_ex_, nullptr, type_conversion::EdictByIndex(client));
    WriteByte(fov & 0xFF);
    WriteFloat(lerp_time);
    MessageEnd();
}

void Miscellaneous::ClientInvertMouse(ClientId client, bool invert_pitch, bool invert_yaw)
{
    MessageBegin(cssdk::MessageType::One, message_invert_mouse_, nullptr, type_conversion::EdictByIndex(client));
    WriteByte(static_cast<uint8_t>(invert_pitch) | static_cast<uint8_t>(invert_yaw) << 1);
    MessageEnd();
}

void Miscellaneous::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_set_fov_ex_ = RegUserMsgSafe("SetFOVEx", -1);
    message_invert_mouse_ = RegUserMsgSafe("InvertMouse", -1);
}
