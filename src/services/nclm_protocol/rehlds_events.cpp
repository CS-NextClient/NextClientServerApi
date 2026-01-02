#include "rehlds_events.h"
#include "NclmProtocol.h"

void HandleNetCommand(IRehldsHook_HandleNetCommand* hookchain, IGameClient* apiClient, int8 opcode)
{
    if (!NclmProtocol::instance_)
    {
        hookchain->callNext(apiClient, opcode);
        return;
    }

    NclmProtocol::instance_->ClientMessageHandler(hookchain, apiClient, opcode);
}
