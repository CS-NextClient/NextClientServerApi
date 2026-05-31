#pragma once
#include <mhooks/reapi.h>

namespace mod_events
{
    cssdk::qboolean AddPlayerItemHook(
        cssdk::ReHookPlayerAddPlayerItem* hookchain,
        cssdk::PlayerBase* player,
        cssdk::PlayerItemBase* item
    );

    cssdk::qboolean RemovePlayerItemHook(
        cssdk::ReHookPlayerRemovePlayerItem* hookchain,
        cssdk::PlayerBase* player,
        cssdk::PlayerItemBase* item
    );
} // namespace mod_events
