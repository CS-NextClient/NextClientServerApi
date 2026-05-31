#include "ModEventsManager.h"

using namespace core;

ModEventsManager::ModEventsManager()
{
    if (instance_)
    {
        throw std::runtime_error("ModEventsManager instance already exists");
    }

    instance_ = this;

    regamedll_api::HookChains()->PlayerAddPlayerItem()->RegisterHook(mod_events::AddPlayerItemHook);
    regamedll_api::HookChains()->PlayerRemovePlayerItem()->RegisterHook(mod_events::RemovePlayerItemHook);
}

ModEventsManager::ModEventsManager(ModEventsManager&& other) noexcept :
    add_player_item_(std::move(other.add_player_item_)),
    remove_player_item_(std::move(other.remove_player_item_))
{
    other.moved_ = true;
    instance_ = this;
}

ModEventsManager::~ModEventsManager()
{
    if (moved_)
    {
        return;
    }

    regamedll_api::HookChains()->PlayerAddPlayerItem()->UnregisterHook(mod_events::AddPlayerItemHook);
    regamedll_api::HookChains()->PlayerRemovePlayerItem()->UnregisterHook(mod_events::RemovePlayerItemHook);

    instance_ = nullptr;
}

sigslot::signal<AddPlayerItemEvent>& ModEventsManager::on_add_player_item() noexcept
{
    return add_player_item_;
}

sigslot::signal<RemovePlayerItemEvent>& ModEventsManager::on_remove_player_item() noexcept
{
    return remove_player_item_;
}

ModEventsManager* ModEventsManager::instance_ = nullptr;
