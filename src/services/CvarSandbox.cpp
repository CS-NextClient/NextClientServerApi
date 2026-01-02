#include "CvarSandbox.h"
#include <easylogging++.h>
#include "utils/utilfuncs.h"

CvarSandbox::CvarSandbox(GameEventsManager& game_events_manager) :
    game_events_manager_(game_events_manager)
{
    game_events_manager_.on_server_activated().connect(&CvarSandbox::ServerActivatedHandler, this);
}

void CvarSandbox::Begin(ClientId client)
{
    if (is_message_building_)
    {
        LOG(ERROR) << "Repeating of message beginning";
        return;
    }

    MESSAGE_BEGIN(MSG_ONE, message_sandbox_cvar_, nullptr, INDEXENT(client));
    WRITE_BYTE(255);

    is_message_building_ = true;
}

void CvarSandbox::End()
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Ending with no started message";
        return;
    }

    MESSAGE_END();

    is_message_building_ = false;
}

void CvarSandbox::WriteCvar(SandboxCvar cvar, const std::string& value)
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Writing cvar with no started message";
        return;
    }

    WRITE_BYTE((int)cvar);
    WRITE_STRING(value.c_str());
}

void CvarSandbox::ServerActivatedHandler(ServerActivatedEvent server_activated_event)
{
    message_sandbox_cvar_ = utils::RegUserMsgSafe("SandboxCvar", -1);
}
