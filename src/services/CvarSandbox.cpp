#include "CvarSandbox.h"

#include <easylogging++.h>

#include <metamod/engine.h>
#include <core/type_conversion.h>

#include "utils/msg_ex.h"

using namespace metamod;
using namespace core;
using namespace msg_ex;

CvarSandbox::CvarSandbox(ServerEventsManager& server_events_manager) :
    server_events_manager_(server_events_manager)
{
    server_events_manager_.on_server_activated().connect(&CvarSandbox::ServerActivatedHandler, this);
}

void CvarSandbox::Begin(ClientId client)
{
    if (is_message_building_)
    {
        LOG(ERROR) << "Repeating of message beginning";
        return;
    }

    MessageBegin(cssdk::MessageType::One, message_sandbox_cvar_, nullptr, type_conversion::EdictByIndex(client));
    WriteByte(255);

    is_message_building_ = true;
}

void CvarSandbox::End()
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Ending with no started message";
        return;
    }

    MessageEnd();

    is_message_building_ = false;
}

void CvarSandbox::WriteCvar(SandboxCvar cvar, const std::string& value)
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Writing cvar with no started message";
        return;
    }

    WriteByte(static_cast<uint8_t>(cvar));
    WriteString(value.c_str());
}

void CvarSandbox::ServerActivatedHandler(ServerActivatedEvent server_activated_event)
{
    message_sandbox_cvar_ = RegUserMsgSafe("SandboxCvar", -1);
}
