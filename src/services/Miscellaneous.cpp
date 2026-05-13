#include "Miscellaneous.h"
#include "utils/utilfuncs.h"

Miscellaneous::Miscellaneous(GameEventsManager& game_events_manager)
{
    game_events_manager.on_server_activated().connect(&Miscellaneous::ServerActivatedHandler, this);
}

void Miscellaneous::ClientSetFOV(ClientId client, int fov, float lerp_time)
{
    MESSAGE_BEGIN(MSG_ONE, message_set_fov_ex_, nullptr, INDEXENT(client));
    WRITE_BYTE(fov & 0xFF);
    WRITE_FLOAT(lerp_time);
    MESSAGE_END();
}

void Miscellaneous::ClientInvertMouse(ClientId client, bool invert_pitch, bool invert_yaw)
{
    MESSAGE_BEGIN(MSG_ONE, message_invert_mouse_, nullptr, INDEXENT(client));
    WRITE_BYTE((int)invert_pitch | (int)invert_yaw << 1);
    MESSAGE_END();
}

void Miscellaneous::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_set_fov_ex_ = utils::RegUserMsgSafe("SetFOVEx", -1);
    message_invert_mouse_ = utils::RegUserMsgSafe("InvertMouse", -1);
}
