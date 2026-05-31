#pragma once
#include <sigslot/signal.hpp>
#include <kangaru/kangaru.hpp>

#include <mhooks/reapi.h>

#include "events.h"
#include "mod_events.h"

class ModEventsManager
{
    sigslot::signal<AddPlayerItemEvent> add_player_item_;
    sigslot::signal<RemovePlayerItemEvent> remove_player_item_;

    static ModEventsManager* instance_;
    bool moved_ = false;

public:
    explicit ModEventsManager();
    ModEventsManager(ModEventsManager&& other) noexcept;
    ~ModEventsManager();

    sigslot::signal<AddPlayerItemEvent>& on_add_player_item() noexcept;
    sigslot::signal<RemovePlayerItemEvent>& on_remove_player_item() noexcept;

    friend cssdk::qboolean mod_events::AddPlayerItemHook(
        cssdk::ReHookPlayerAddPlayerItem* hookchain,
        cssdk::PlayerBase* player,
        cssdk::PlayerItemBase* item
    );

    friend cssdk::qboolean mod_events::RemovePlayerItemHook(
        cssdk::ReHookPlayerRemovePlayerItem* hookchain,
        cssdk::PlayerBase* player,
        cssdk::PlayerItemBase* item
    );
};

struct ModEventsManagerService : kgr::single_service<ModEventsManager>
{};
