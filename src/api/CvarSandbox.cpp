#include "CvarSandbox.h"
#include "utilfuncs.h"
#include "asserts.h"

void CvarSandbox::OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax)
{
    message_sandbox_cvar_ = utils::RegUserMsgSafe("SandboxCvar", -1);
}

void CvarSandbox::Begin(int client)
{
    NAPI_ASSERT(!is_message_building_, "Repeating of message beginning");

    MESSAGE_BEGIN(MSG_ONE, message_sandbox_cvar_, NULL, INDEXENT(client));
    WRITE_BYTE(255);

    is_message_building_ = true;
}

void CvarSandbox::End()
{
    NAPI_ASSERT(is_message_building_, "Ending with no started message")

    MESSAGE_END();

    is_message_building_ = false;
}

void CvarSandbox::WriteCvar(SandboxCvar cvar, const std::string& value)
{
    NAPI_ASSERT(is_message_building_, "Writing cvar with no started message")

    WRITE_BYTE(cvar);
    WRITE_STRING(value.c_str());
}
