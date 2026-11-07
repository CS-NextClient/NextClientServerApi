#include "MaterialEntitySync.h"

#include <cassert>
#include <cmath>
#include <cstring>

#include <easylogging++.h>
#include <metamod/api.h>
#include <metamod/gamedll_hooks.h>
#include <metamod/engine_hooks.h>

#include <core/type_conversion.h>

using namespace ncl_entity;
using namespace core;

namespace
{
    constexpr uint8_t kMaterialTypeId = static_cast<uint8_t>(EntityTypeId::Material);

    // The order of this list is the order the fields are written when an entity is created,
    // so it has to match the client's declaration exactly.
    constexpr uint16_t FIELD_ENTITY_INDEX = 1u << 0;
    constexpr uint16_t FIELD_MATERIALS = 1u << 1;
    constexpr uint16_t FIELD_PARAMS = 1u << 2;

    // Separates the texture from the parameter in an instance key. Safe because a studio
    // texture name is a file name without a path.
    constexpr char kParamScopeSeparator = '/';

    // How far an owner chain is followed. A carried weapon is one hop from the player and a
    // packed one is one hop from the box; a longer chain is a mod doing something this cannot
    // guess at, and a cycle must not be walked forever.
    constexpr int kMaxOwnerHops = 4;

    // The client keys a binding on the entity whose model the engine is drawing, and an edict
    // the engine never sends is drawn by nobody: a carried weapon is EF_NO_DRAW with no model
    // index, and what the player sees is the owner's own model - the view model and the
    // attached p_ model both come out under the player's index, and a dropped weapon is drawn
    // by the box that packed it. So the index reported is the nearest owner that is actually
    // drawn, which is the edict itself for everything else.
    //
    // Read every frame through BOUND_EDICT tracking, so picking a weapon up and dropping it
    // moves the binding across with no plugin involved.
    edict_t* ResolveDrawnEntity(edict_t* edict)
    {
        edict_t* drawn = edict;

        for (int hop = 0; hop < kMaxOwnerHops; hop++)
        {
            if (drawn == nullptr || drawn->free)
            {
                return nullptr;
            }

            bool invisible = (drawn->vars.effects & cssdk::EF_NO_DRAW) != 0 || drawn->vars.model_index == 0;

            if (!invisible || drawn->vars.owner == nullptr || drawn->vars.owner == drawn)
            {
                break;
            }

            drawn = drawn->vars.owner;
        }

        return drawn != nullptr && !drawn->free ? drawn : nullptr;
    }

    uint32_t EntityIndexGetter(edict_t* edict)
    {
        edict_t* drawn = ResolveDrawnEntity(edict);
        return type_conversion::IndexOfEntity(drawn != nullptr ? drawn : edict);
    }

    std::vector<std::pair<uint16_t, float>> ParamMapToVector(const std::unordered_map<uint16_t, float>& params)
    {
        std::vector<std::pair<uint16_t, float>> result;
        result.reserve(params.size());

        for (const auto& [key_id, value] : params)
        {
            result.emplace_back(key_id, value);
        }

        return result;
    }
} // namespace

MaterialEntitySync::MaterialEntitySync(
    ServerEventsManager& server_events_manager,
    StringRegistry& string_registry,
    EntitySync& entity_sync,
    INextClientInfo& next_client_info
) :
    server_events_manager_(server_events_manager),
    string_registry_(string_registry),
    entity_sync_(entity_sync),
    next_client_info_(next_client_info)
{
    server_events_manager_.on_server_activated().connect(&MaterialEntitySync::ServerActivatedHandler, this);
    server_events_manager_.on_frame().connect(&MaterialEntitySync::RefreshVisibility, this);
    assert(instance_ == nullptr);
    instance_ = this;
    metamod::gamedll::HookAddToFullPack(PackPre, false);
    metamod::gamedll::HookAddToFullPack(PackPost, true);
    metamod::engine::HookCheckVisibility(VisibilityPre, false);
}

MaterialEntitySync::DressedEntity* MaterialEntitySync::Ensure(cssdk::Edict* entity)
{
    if (entity == nullptr || entity->free)
    {
        LOG(ERROR) << "[MaterialNclEntitySync] Entity edict is free or null "
                   << (entity ? type_conversion::IndexOfEntity(entity) : 0);
        return nullptr;
    }

    int index = type_conversion::IndexOfEntity(entity);

    auto it = entities_.find(index);

    if (it != entities_.end() && it->second.source_serial == entity->serial_number &&
        entity_sync_.IsBoundTo(it->second.ncl_entity_id, kMaterialTypeId, entity, it->second.source_serial))
    {
        return &it->second;
    }

    DressedEntity preserved;

    if (it != entities_.end())
    {
        if (it->second.source_serial == entity->serial_number)
        {
            preserved.materials = std::move(it->second.materials);
            preserved.params = std::move(it->second.params);
        }
        else if (entity_sync_.IsBoundTo(it->second.ncl_entity_id, kMaterialTypeId, entity, it->second.source_serial))
        {
            entity_sync_.Destroy(it->second.ncl_entity_id);
        }

        entities_.erase(it);
    }

    std::unordered_map<uint16_t, FieldValue> initial_fields;

    if (!preserved.materials.empty())
    {
        initial_fields[FIELD_MATERIALS] = FieldValue{preserved.materials};
    }

    if (!preserved.params.empty())
    {
        initial_fields[FIELD_PARAMS] = FieldValue{ParamMapToVector(preserved.params)};
    }

    uint16_t entity_id = entity_sync_.Create(
        kMaterialTypeId,
        entity,
        std::move(initial_fields),
        VisibilityReference::BindEdictPAS(entity)
    );

    if (entity_id == 0)
    {
        return nullptr;
    }

    preserved.ncl_entity_id = entity_id;
    preserved.source_serial = entity->serial_number;
    visibility_.Disable(index);
    entities_[index] = std::move(preserved);

    return &entities_[index];
}

bool MaterialEntitySync::Bind(cssdk::Edict* entity, const std::string& preset, const std::string& material)
{
    if (!StringRegistry::IsRegistrable(preset) || !StringRegistry::IsRegistrable(material))
    {
        return false;
    }

    DressedEntity* dressed = Ensure(entity);

    if (dressed == nullptr)
    {
        return false;
    }

    uint16_t preset_id = string_registry_.GetOrRegister(preset);
    uint16_t material_id = string_registry_.GetOrRegister(material);

    if (preset_id == 0 || material_id == 0)
    {
        return false;
    }

    std::pair<uint16_t, uint16_t> pair{preset_id, material_id};

    for (const auto& worn : dressed->materials)
    {
        if (worn == pair)
        {
            return true;
        }
    }

    dressed->materials.push_back(pair);

    entity_sync_.Update(dressed->ncl_entity_id, FIELD_MATERIALS, FieldValue{dressed->materials});

    return true;
}

bool MaterialEntitySync::Unbind(cssdk::Edict* entity, const std::string& preset, const std::string& material)
{
    if (entity == nullptr || entity->free || !StringRegistry::IsRegistrable(preset) || !StringRegistry::IsRegistrable(material))
    {
        return false;
    }

    auto it = entities_.find(type_conversion::IndexOfEntity(entity));

    if (it == entities_.end() || it->second.source_serial != entity->serial_number ||
        !entity_sync_.IsBoundTo(it->second.ncl_entity_id, kMaterialTypeId, entity, it->second.source_serial))
    {
        return false;
    }

    uint16_t preset_id = string_registry_.GetOrRegister(preset);
    uint16_t material_id = string_registry_.GetOrRegister(material);

    std::pair<uint16_t, uint16_t> pair{preset_id, material_id};

    std::vector<std::pair<uint16_t, uint16_t>>& materials = it->second.materials;

    for (size_t i = materials.size(); i > 0; i--)
    {
        if (materials[i - 1] == pair)
        {
            materials.erase(materials.begin() + (i - 1));
            if (materials.empty())
            {
                SetThroughWalls(entity, false);
            }

            entity_sync_.Update(
                it->second.ncl_entity_id, FIELD_MATERIALS, FieldValue{materials});

            return true;
        }
    }

    return false;
}

void MaterialEntitySync::Clear(cssdk::Edict* entity)
{
    if (entity == nullptr)
    {
        return;
    }
    visibility_.Disable(type_conversion::IndexOfEntity(entity));

    auto it = entities_.find(type_conversion::IndexOfEntity(entity));

    if (it == entities_.end())
    {
        return;
    }

    // Destroyed rather than emptied: an entity wearing nothing has nothing to synchronize,
    // and the client drops what it knows when the synchronized entity goes.
    if (entity_sync_.IsBoundTo(it->second.ncl_entity_id, kMaterialTypeId, entity, it->second.source_serial))
    {
        entity_sync_.Destroy(it->second.ncl_entity_id);
    }

    entities_.erase(it);
}

bool MaterialEntitySync::SetParam(cssdk::Edict* entity, const std::string& texture, const std::string& name, float value)
{
    if (!std::isfinite(value) || name.empty())
    {
        return false;
    }

    std::string key = texture.empty() ? name : texture + kParamScopeSeparator + name;

    if (!StringRegistry::IsRegistrable(key))
    {
        return false;
    }

    DressedEntity* dressed = Ensure(entity);

    if (dressed == nullptr)
    {
        return false;
    }

    uint16_t key_id = string_registry_.GetOrRegister(key);

    if (key_id == 0)
    {
        return false;
    }

    auto it_param = dressed->params.find(key_id);

    if (it_param != dressed->params.end() && std::memcmp(&it_param->second, &value, sizeof(value)) == 0)
    {
        return true;
    }

    dressed->params[key_id] = value;

    entity_sync_.Update(dressed->ncl_entity_id, FIELD_PARAMS, FieldValue{ArrayStringIdFloatPairsDelta{{{key_id, value}}}});

    return true;
}

void MaterialEntitySync::ServerActivatedHandler(ServerActivatedEvent event)
{
    visibility_.Clear();
    entities_.clear();

    static EntityTypeDescriptor material_type;

    material_type.type_id = kMaterialTypeId;
    material_type.fields = {
        {FIELD_ENTITY_INDEX, FieldType::UINT, FieldTracking::BOUND_EDICT, EntityIndexGetter},
        {FIELD_MATERIALS, FieldType::ARRAY_STRING_ID_PAIRS_DELTA, FieldTracking::MANUAL, nullptr},
        {FIELD_PARAMS, FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA, FieldTracking::MANUAL, nullptr},
    };

    entity_sync_.RegisterType(material_type);
}

MaterialEntitySync* MaterialEntitySync::instance_{};

MaterialEntitySync::~MaterialEntitySync()
{
    metamod::gamedll::HookAddToFullPack(nullptr, false);
    metamod::gamedll::HookAddToFullPack(nullptr, true);
    metamod::engine::HookCheckVisibility(nullptr, false);
    instance_ = nullptr;
    visibility_.Clear();
}

bool MaterialEntitySync::SetThroughWalls(cssdk::Edict* entity, bool enabled)
{
    if (entity == nullptr || entity->free)
    {
        return false;
    }
    const int index = type_conversion::IndexOfEntity(entity);
    auto found = entities_.find(index);
    if (!enabled)
    {
        visibility_.Disable(index);
        if (found != entities_.end() && found->second.source_serial == entity->serial_number &&
            entity_sync_.IsBoundTo(found->second.ncl_entity_id, kMaterialTypeId, entity, found->second.source_serial))
        {
            entity_sync_.SetAnchor(found->second.ncl_entity_id, VisibilityReference::BindEdictPAS(entity));
        }
        return true;
    }
    if (found == entities_.end() || found->second.source_serial != entity->serial_number || found->second.materials.empty() ||
        !entity_sync_.IsBoundTo(found->second.ncl_entity_id, kMaterialTypeId, entity, found->second.source_serial))
    {
        return false;
    }
    cssdk::Edict* drawn = ResolveDrawnEntity(entity);
    if (drawn == nullptr)
    {
        return false;
    }
    if (!visibility_.Enable({index, entity->serial_number}, {type_conversion::IndexOfEntity(drawn), drawn->serial_number}, true))
    {
        return false;
    }
    entity_sync_.SetAnchor(found->second.ncl_entity_id, VisibilityReference::Broadcast());
    return true;
}

void MaterialEntitySync::RefreshVisibility()
{
    if (visibility_.is_empty())
    {
        return;
    }
    for (const auto& item : entities_)
    {
        if (!visibility_.ContainsSource(item.first))
        {
            continue;
        }
        cssdk::Edict* source = type_conversion::EdictByIndex(item.first);
        if (source->free || source->serial_number != item.second.source_serial ||
            !entity_sync_.IsBoundTo(item.second.ncl_entity_id, kMaterialTypeId, source, item.second.source_serial) ||
            item.second.materials.empty())
        {
            visibility_.Disable(item.first);
            continue;
        }
        cssdk::Edict* drawn = ResolveDrawnEntity(source);
        const MaterialEntityIdentity destination = drawn != nullptr
                                                       ? MaterialEntityIdentity{type_conversion::IndexOfEntity(drawn), drawn->serial_number}
                                                       : MaterialEntityIdentity{};
        if (!visibility_.Update({item.first, source->serial_number}, destination, drawn != nullptr))
        {
            entity_sync_.SetAnchor(item.second.ncl_entity_id, VisibilityReference::BindEdictPAS(source));
        }
    }
}

bool MaterialEntitySync::CheckRecipient(cssdk::Edict* host) const
{
    if (host == nullptr || host->free)
    {
        return false;
    }
    const int client = type_conversion::IndexOfEntity(host);
    NextClientVersion version;
    return next_client_info_.IsClientReady(client) && next_client_info_.GetNextClientVersion(client, version) &&
           version >= NextClientVersion{2, 6, 0};
}

cssdk::qboolean MaterialEntitySync::PackPre(
    cssdk::EntityState*,
    int,
    cssdk::Edict* entity,
    cssdk::Edict* host,
    int,
    cssdk::qboolean,
    unsigned char*
)
{
    instance_->RefreshVisibility();
    instance_->visibility_.BeginPack(
        {type_conversion::IndexOfEntity(entity), entity->serial_number},
        {type_conversion::IndexOfEntity(host), host->serial_number},
        !instance_->visibility_.is_empty() && instance_->CheckRecipient(host)
    );
    RETURN_META_VALUE(metamod::Result::Ignored, 0);
}

cssdk::qboolean MaterialEntitySync::PackPost(cssdk::EntityState*, int, cssdk::Edict*, cssdk::Edict*, int, cssdk::qboolean, unsigned char*)
{
    instance_->visibility_.EndPack();
    RETURN_META_VALUE(metamod::Result::Ignored, 0);
}

cssdk::qboolean MaterialEntitySync::VisibilityPre(cssdk::Edict* entity, unsigned char*)
{
    instance_->RefreshVisibility();
    const MaterialEntityIdentity identity = instance_->visibility_.get_host();
    if (identity.index > 0)
    {
        cssdk::Edict* host = type_conversion::EdictByIndex(identity.index);
        if (instance_->CheckRecipient(host) && !entity->free &&
            instance_->visibility_.Check(
                {type_conversion::IndexOfEntity(entity), entity->serial_number}, {identity.index, host->serial_number}
            ))
        {
            RETURN_META_VALUE(metamod::Result::Supercede, 1);
        }
    }
    RETURN_META_VALUE(metamod::Result::Ignored, 0);
}
