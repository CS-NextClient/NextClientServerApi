#include "mod_events.h"

#include "ModEventsManager.h"

namespace mod_events
{
    cssdk::qboolean AddPlayerItemHook(
        cssdk::ReHookPlayerAddPlayerItem* hookchain,
        cssdk::PlayerBase* player,
        cssdk::PlayerItemBase* item
    )
    {
        cssdk::qboolean result = hookchain->CallNext(player, item);

        if (ModEventsManager::instance_)
        {
            ModEventsManager::instance_->add_player_item_(AddPlayerItemEvent{result != FALSE, player, item});
        }

        return result;
    }

    cssdk::qboolean RemovePlayerItemHook(
        cssdk::ReHookPlayerRemovePlayerItem* hookchain,
        cssdk::PlayerBase* player,
        cssdk::PlayerItemBase* item
    )
    {
        cssdk::qboolean result = hookchain->CallNext(player, item);

        if (ModEventsManager::instance_)
        {
            ModEventsManager::instance_->remove_player_item_(RemovePlayerItemEvent{result != FALSE, player, item});
        }

        return result;
    }
} // namespace mod_events
