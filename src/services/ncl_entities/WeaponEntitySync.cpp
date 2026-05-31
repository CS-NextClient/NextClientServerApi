#include "WeaponEntitySync.h"

#include <easylogging++.h>

#include <core/type_conversion.h>

using namespace ncl_entity;
using namespace core;

namespace
{
    constexpr uint16_t FIELD_WEAPON_ID = 1u << 0;
    constexpr uint16_t FIELD_SOUND_OVERRIDES = 1u << 1;

    uint32_t WeaponIdGetter(edict_t* edict)
    {
        return type_conversion::IndexOfEntity(edict);
    }

    std::vector<std::pair<uint16_t, uint16_t>> SoundOverrideMapToVector(const std::unordered_map<uint16_t, uint16_t>& sound_override)
    {
        std::vector<std::pair<uint16_t, uint16_t>> result;
        result.reserve(sound_override.size());
        for (const auto& [original_id, replacement_id] : sound_override)
        {
            result.emplace_back(original_id, replacement_id);
        }
        return result;
    }
} // namespace

WeaponEntitySync::WeaponEntitySync(ServerEventsManager& server_events_manager, StringRegistry& string_registry, EntitySync& entity_sync) :
    server_events_manager_(server_events_manager),
    string_registry_(string_registry),
    entity_sync_(entity_sync)
{
    server_events_manager_.on_server_activated().connect(&WeaponEntitySync::ServerActivatedHandler, this);
}

uint16_t WeaponEntitySync::BindWeapon(cssdk::Edict* weapon)
{
    if (weapon == nullptr || weapon->free)
    {
        LOG(ERROR) << "[WeaponNclEntitySync] BindWeapon: Weapon edict is free or null "
                   << (weapon ? type_conversion::IndexOfEntity(weapon) : 0);
        return 0;
    }

    const char* classname = weapon->vars.class_name.CStr();
    if (!*classname || std::strncmp(classname, "weapon_", 7) != 0)
    {
        LOG(ERROR) << "[WeaponNclEntitySync] BindWeapon: Entity " << weapon << " is not a weapon (classname: " << classname << ")";
        return 0;
    }

    int weapon_id = type_conversion::IndexOfEntity(weapon);

    auto it = weapon_entities_.find(weapon_id);
    if (it != weapon_entities_.end() && entity_sync_.Exists(it->second.ncl_entity_id))
    {
        return it->second.ncl_entity_id;
    }

    std::unordered_map<uint16_t, uint16_t> preserved_overrides;
    if (it != weapon_entities_.end())
    {
        preserved_overrides = std::move(it->second.sound_override);
        weapon_entities_.erase(it);
    }

    std::unordered_map<uint16_t, FieldValue> initial_fields;
    if (!preserved_overrides.empty())
    {
        initial_fields[FIELD_SOUND_OVERRIDES] = FieldValue{SoundOverrideMapToVector(preserved_overrides)};
    }

    uint16_t entity_id = entity_sync_.Create(
        static_cast<uint8_t>(EntityTypeId::Weapon), weapon, std::move(initial_fields), VisibilityReference::BindEdictPAS(weapon)
    );

    if (entity_id == 0)
    {
        return 0;
    }

    WeaponData data;
    data.ncl_entity_id = entity_id;
    data.sound_override = std::move(preserved_overrides);
    weapon_entities_[weapon_id] = std::move(data);
    return entity_id;
}

void WeaponEntitySync::AddSoundOverride(cssdk::Edict* weapon, const std::string& original, const std::string& replacement)
{
    if (weapon == nullptr || weapon->free)
    {
        LOG(ERROR) << "[WeaponNclEntitySync] AddSoundOverride: Weapon edict is free or null "
                   << (weapon ? type_conversion::IndexOfEntity(weapon) : 0);
        return;
    }

    int weapon_id = type_conversion::IndexOfEntity(weapon);

    auto it_weapon = weapon_entities_.find(weapon_id);
    if (it_weapon == weapon_entities_.end() || !entity_sync_.Exists(it_weapon->second.ncl_entity_id))
    {
        LOG(ERROR) << "[WeaponNclEntitySync] AddSoundOverride: Weapon with id " << weapon_id
                   << " is not registered (call BindWeapon first)";
        return;
    }

    uint16_t original_id = string_registry_.GetOrRegister(original);
    uint16_t replacement_id = string_registry_.GetOrRegister(replacement);

    if (original_id == 0 || replacement_id == 0)
    {
        return;
    }

    auto& sound_override = it_weapon->second.sound_override;

    auto it_sound = sound_override.find(original_id);
    if (it_sound != sound_override.end())
    {
        if (it_sound->second == replacement_id)
        {
            return;
        }

        it_sound->second = replacement_id;
    }
    else
    {
        sound_override[original_id] = replacement_id;
    }

    entity_sync_.Update(it_weapon->second.ncl_entity_id, FIELD_SOUND_OVERRIDES, ArrayStringIdPairsDelta{{{original_id, replacement_id}}});
}

void WeaponEntitySync::RemoveSoundOverride(cssdk::Edict* weapon, const std::string& original)
{
    if (weapon == nullptr || weapon->free)
    {
        LOG(ERROR) << "[WeaponNclEntitySync] RemoveSoundOverride: Weapon edict is free or null "
                   << (weapon ? type_conversion::IndexOfEntity(weapon) : 0);
        return;
    }

    int weapon_id = type_conversion::IndexOfEntity(weapon);

    auto it_weapon = weapon_entities_.find(weapon_id);
    if (it_weapon == weapon_entities_.end() || !entity_sync_.Exists(it_weapon->second.ncl_entity_id))
    {
        LOG(ERROR) << "[WeaponNclEntitySync] RemoveSoundOverride: Weapon with id " << weapon_id << " is not registered";
        return;
    }

    uint16_t original_id = string_registry_.GetOrRegister(original);
    if (original_id == 0)
    {
        return;
    }

    auto& sound_override = it_weapon->second.sound_override;

    auto it_sound = sound_override.find(original_id);
    if (it_sound == sound_override.end())
    {
        return;
    }

    entity_sync_.Update(it_weapon->second.ncl_entity_id, FIELD_SOUND_OVERRIDES, ArrayStringIdPairsDelta{{}, {{original_id, 0}}});

    sound_override.erase(it_sound);
}

void WeaponEntitySync::RemoveSoundOverride(cssdk::Edict* weapon)
{
    if (weapon == nullptr || weapon->free)
    {
        LOG(ERROR) << "[WeaponNclEntitySync] RemoveSoundOverride: Weapon edict is free or null "
                   << (weapon ? type_conversion::IndexOfEntity(weapon) : 0);
        return;
    }

    int weapon_id = type_conversion::IndexOfEntity(weapon);

    auto it_weapon = weapon_entities_.find(weapon_id);
    if (it_weapon == weapon_entities_.end())
    {
        return;
    }

    auto& sound_override = it_weapon->second.sound_override;
    if (sound_override.empty())
    {
        return;
    }

    if (entity_sync_.Exists(it_weapon->second.ncl_entity_id))
    {
        entity_sync_.Update(it_weapon->second.ncl_entity_id, FIELD_SOUND_OVERRIDES, ArrayStringIdPairsDelta{{}, {}, /*clear=*/true});
    }

    sound_override.clear();
}

void WeaponEntitySync::ServerActivatedHandler(ServerActivatedEvent event)
{
    weapon_entities_.clear();

    EntityTypeDescriptor weapon_type;
    weapon_type.type_id = static_cast<uint8_t>(EntityTypeId::Weapon);
    weapon_type.fields = {
        {FIELD_WEAPON_ID, FieldType::UINT, FieldTracking::BOUND_EDICT, WeaponIdGetter},
        {FIELD_SOUND_OVERRIDES, FieldType::ARRAY_STRING_ID_PAIRS_DELTA, FieldTracking::MANUAL, nullptr},
    };

    entity_sync_.RegisterType(weapon_type);
}
