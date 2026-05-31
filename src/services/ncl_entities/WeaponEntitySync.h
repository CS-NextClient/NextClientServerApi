#pragma once
#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>

#include "EntitySync.h"
#include "services/server_events/ServerEventsManager.h"

class WeaponEntitySync : public sigslot::observer
{
    struct WeaponData
    {
        uint16_t ncl_entity_id{};
        // key - original string id, value - replacement string id
        std::unordered_map<uint16_t, uint16_t> sound_override{};
    };

    ServerEventsManager& server_events_manager_;
    StringRegistry& string_registry_;
    EntitySync& entity_sync_;

    std::unordered_map<int, WeaponData> weapon_entities_;

public:
    explicit WeaponEntitySync(ServerEventsManager& server_events_manager, StringRegistry& string_registry, EntitySync& entity_sync);

    uint16_t BindWeapon(cssdk::Edict* weapon);
    void AddSoundOverride(cssdk::Edict* weapon, const std::string& original, const std::string& replacement);
    void RemoveSoundOverride(cssdk::Edict* weapon, const std::string& original);
    void RemoveSoundOverride(cssdk::Edict* weapon);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
};

struct WeaponNclEntitySyncService
    : kgr::single_service<WeaponEntitySync, kgr::dependency<ServerEventsManagerService, StringRegistryService, EntitySyncService>>
{};
