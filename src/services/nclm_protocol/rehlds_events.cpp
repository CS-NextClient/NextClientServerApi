#include "rehlds_events.h"

#include "NclmProtocol.h"

namespace nclm_proto
{
    void HandleNetCommandHandler(cssdk::ReHookHandleNetCommand* hookchain, cssdk::IGameClient* client, cssdk::uint8 opcode)
    {
        if (NclmProtocol::instance_ == nullptr)
        {
            hookchain->CallNext(client, opcode);
            return;
        }

        NclmProtocol::instance_->ClientMessageHandler(hookchain, client, opcode);
    }
} // namespace nclm_proto
