#pragma once
#include <cssdk/public/rehlds.h>

namespace nclm_proto
{
    void HandleNetCommandHandler(cssdk::ReHookHandleNetCommand* hookchain, cssdk::IGameClient* client, cssdk::uint8 opcode);
} // namespace nclm_proto
