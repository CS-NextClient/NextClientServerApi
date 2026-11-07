#include "EntitySync.h"

#include <algorithm>

#include <easylogging++.h>

#include <core/rehlds_api.h>
#include <core/type_conversion.h>
#include <metamod/engine.h>

#include "services/ncl_entities/EntitySyncPackets.h"
#include "utils/msg_ex.h"

using namespace ncl_entity;
using namespace core;
using namespace msg_ex;

namespace
{
    std::vector<EntitySyncPackets::Field> PacketSchema(const EntityTypeDescriptor& type)
    {
        std::vector<EntitySyncPackets::Field> fields;
        fields.reserve(type.fields.size());
        for (const EntityFieldDescriptor& field : type.fields)
        {
            fields.push_back({field.field_bit, field.type});
        }
        return fields;
    }

    void SendPackets(const EntitySyncPackets::Result& prepared, cssdk::Edict* player, int create_message, int update_message)
    {
        for (const EntitySyncPackets::Packet& packet : prepared.packets)
        {
            MessageBegin(cssdk::MessageType::One, packet.create ? create_message : update_message, nullptr, player);
            for (uint8_t byte : packet.bytes)
            {
                WriteByte(byte);
            }
            MessageEnd();
        }
    }
} // namespace

EntitySync::EntitySync(ServerEventsManager& server_events_manager, StringRegistry& string_registry, INextClientInfo& next_client_api) :
    string_registry_(string_registry),
    next_client_api_(next_client_api)
{
    server_events_manager.on_client_first_frame().connect(&EntitySync::ClientFirstFrameHandler, this);
    server_events_manager.on_client_disconnected().connect(&EntitySync::ClientDisconnectedHandler, this);
    server_events_manager.on_server_activated().connect(&EntitySync::ServerActivatedHandler, this);
    server_events_manager.on_frame().connect(&EntitySync::FrameHandler, this);
}

void EntitySync::RegisterType(EntityTypeDescriptor& descriptor)
{
    if (descriptor.type_id == 0)
    {
        LOG(ERROR) << "[NclEntitySync] RegisterType: type_id is 0";
        return;
    }

    if (types_.count(descriptor.type_id) > 0)
    {
        LOG(ERROR) << "[NclEntitySync] RegisterType: type_id " << descriptor.type_id << " is already registered";
        return;
    }

    types_[descriptor.type_id] = std::move(descriptor);
}

uint16_t EntitySync::Create(
    uint8_t type_id,
    cssdk::Edict* bound_edict,
    std::unordered_map<uint16_t, FieldValue> fields,
    const VisibilityReference& initial_visibility
)
{
    if (!types_.count(type_id))
    {
        LOG(ERROR) << "[NclEntitySync] Create: unknown type_id " << type_id;
        return 0;
    }

    if (bound_edict == nullptr || bound_edict->free)
    {
        LOG(ERROR) << "[NclEntitySync] Create: bound_edict is null or free";
        return 0;
    }

    for (auto it = entities_.begin(); it != entities_.end();)
    {
        const auto current = it++;
        const uint16_t existing_id = current->first;
        const SyncedEntity& existing_entity = current->second;

        if (existing_entity.bound_edict != bound_edict)
        {
            continue;
        }

        if (existing_entity.last_serialnumber != bound_edict->serial_number)
        {
            Destroy(existing_id);
            continue;
        }

        if (existing_entity.type_id == type_id)
        {
            LOG(WARNING) << "[NclEntitySync] Create: bound_edict already has entity_id=" << existing_id;
            return existing_id;
        }
    }

    // entity_id == 0 is reserved as a sentinel (returned on failure).
    // Search at most 65535 ids; if none free, signal overflow.
    uint16_t entity_id = 0;
    for (uint32_t attempts = 0; attempts < 65535u; ++attempts)
    {
        if (next_entity_id_ == 0 || next_entity_id_ > 65535u)
        {
            next_entity_id_ = 1;
        }

        uint16_t candidate = static_cast<uint16_t>(next_entity_id_++);
        if (!entities_.count(candidate))
        {
            entity_id = candidate;
            break;
        }
    }

    if (entity_id == 0)
    {
        LOG(ERROR) << "[NclEntitySync] Create: no free entity_id (overflow)";
        return 0;
    }

    SyncedEntity entity;
    entity.type_id = type_id;
    entity.entity_id = entity_id;
    entity.bound_edict = bound_edict;
    entity.visibility_ref = initial_visibility;
    entity.field_cache = std::move(fields);
    entity.last_serialnumber = bound_edict->serial_number;
    entity.visibility_ref_serial = initial_visibility.edict ? initial_visibility.edict->serial_number : 0;

    const EntityTypeDescriptor& type = types_.at(type_id);
    for (const EntityFieldDescriptor& field : type.fields)
    {
        if (field.tracking == FieldTracking::BOUND_EDICT && field.getter &&
            entity.field_cache.find(field.field_bit) == entity.field_cache.end())
        {
            entity.field_cache[field.field_bit] = field.getter(bound_edict);
        }
    }

    EntitySyncPackets::Result prepared = EntitySyncPackets::PrepareCreate(type_id, entity_id, PacketSchema(type), entity.field_cache);
    if (!prepared)
    {
        LOG(ERROR) << "[NclEntitySync] Create: " << prepared.error;
        return 0;
    }

    // Only push to clients that are already past their first frame; the rest
    // receive this entity from ClientFirstFrameHandler (avoids duplicate create).
    for (int i = 1; i <= rehlds_api::ServerStatic()->GetMaxClients(); ++i)
    {
        if (!clients_ready_for_sync_.count(i))
        {
            continue;
        }

        if (ClientSupportsEntitySync(i) && IsEntityVisibleToClient(i, entity))
        {
            SendEntityCreate(i, entity);
        }
    }

    entities_[entity_id] = std::move(entity);
    return entity_id;
}

bool EntitySync::ApplyFieldUpdate(
    SyncedEntity& entity,
    const EntityTypeDescriptor& type,
    uint16_t bit,
    FieldValue new_val,
    uint16_t& actual_field_mask
)
{
    const EntityFieldDescriptor* field_ptr = nullptr;
    for (const EntityFieldDescriptor& f : type.fields)
    {
        if (f.field_bit == bit)
        {
            field_ptr = &f;
            break;
        }
    }

    if (field_ptr == nullptr)
    {
        LOG(WARNING) << "[NclEntitySync] Update: unknown field_bit " << bit << " for type_id " << static_cast<int>(entity.type_id);
        return false;
    }

    const EntityFieldDescriptor& field = *field_ptr;
    auto cache_it = entity.field_cache.find(bit);
    const FieldValue* current = cache_it == entity.field_cache.end() ? nullptr : &cache_it->second;
    FieldValue full;
    FieldValue pending;
    EntitySyncPackets::Mutation mutation = EntitySyncPackets::ApplyUpdate(field.type, current, new_val, full, pending);
    if (mutation == EntitySyncPackets::Mutation::Invalid)
    {
        LOG(WARNING) << "[NclEntitySync] Update: invalid field value for bit " << bit;
        return false;
    }
    if (mutation == EntitySyncPackets::Mutation::Unchanged)
    {
        return true;
    }

    EntitySyncPackets::Fields cache = entity.field_cache;
    EntitySyncPackets::Fields deltas = entity.pending_deltas;
    cache[bit] = full;
    if (field.type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA || field.type == FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA)
    {
        deltas[bit] = pending;
    }
    EntitySyncPackets::Result prepared =
        EntitySyncPackets::PrepareUpdate(entity.type_id, entity.entity_id, PacketSchema(type), cache, deltas, bit);
    if (!prepared)
    {
        LOG(WARNING) << "[NclEntitySync] Update: " << prepared.error;
        return false;
    }

    entity.field_cache = std::move(cache);
    entity.pending_deltas = std::move(deltas);
    actual_field_mask |= bit;
    return true;
}

void EntitySync::Update(uint16_t entity_id, const std::unordered_map<uint16_t, FieldValue>& fields)
{
    auto it = entities_.find(entity_id);
    if (it == entities_.end())
    {
        LOG(WARNING) << "[NclEntitySync] Update: entity_id " << entity_id << " not found";
        return;
    }

    SyncedEntity& entity = it->second;

    auto type_it = types_.find(entity.type_id);
    if (type_it == types_.end())
    {
        return;
    }

    const EntityTypeDescriptor& type = type_it->second;

    for (const auto& [bit, value] : fields)
    {
        auto field = std::find_if(type.fields.begin(), type.fields.end(), [bit](const EntityFieldDescriptor& descriptor) {
            return descriptor.field_bit == bit;
        });
        if (field == type.fields.end() || !EntitySyncPackets::IsValueValid(field->type, value, true))
        {
            LOG(WARNING) << "[NclEntitySync] Update: invalid field " << bit;
            return;
        }
    }

    SyncedEntity updated = entity;
    uint16_t actual_field_mask = 0;
    for (const auto& [bit, val] : fields)
    {
        if (!ApplyFieldUpdate(updated, type, bit, val, actual_field_mask))
        {
            return;
        }
    }

    if (actual_field_mask != 0)
    {
        entity = std::move(updated);
        BroadcastEntityUpdate(entity, actual_field_mask);
    }
}

void EntitySync::Update(uint16_t entity_id, uint16_t field_bit, FieldValue value)
{
    Update(entity_id, {{field_bit, std::move(value)}});
}

bool EntitySync::Exists(uint16_t entity_id) const
{
    return entity_id != 0 && entities_.count(entity_id) > 0;
}

bool EntitySync::IsBoundTo(uint16_t entity_id, uint8_t type_id, const cssdk::Edict* bound_edict, int serial_number) const
{
    auto it = entities_.find(entity_id);

    return it != entities_.end() && it->second.type_id == type_id && it->second.bound_edict == bound_edict &&
           it->second.last_serialnumber == serial_number;
}

void EntitySync::Destroy(uint16_t entity_id)
{
    auto it = entities_.find(entity_id);
    if (it == entities_.end())
    {
        return;
    }

    for (int i = 1; i <= rehlds_api::ServerStatic()->GetMaxClients(); ++i)
    {
        auto cv_it = client_visible_entities_.find(i);
        if (cv_it != client_visible_entities_.end() && cv_it->second.count(entity_id))
        {
            SendEntityDestroy(i, it->second);
            cv_it->second.erase(entity_id);
        }
    }
    entities_.erase(it);
}

void EntitySync::SetAnchor(uint16_t entity_id, const VisibilityReference& visibility_ref)
{
    auto it = entities_.find(entity_id);
    if (it == entities_.end())
    {
        return;
    }

    it->second.visibility_ref = visibility_ref;
    it->second.visibility_ref_serial = visibility_ref.edict ? visibility_ref.edict->serial_number : 0;
}

void EntitySync::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_nsync_create_ = RegUserMsgSafe("nsync_create", -1);
    message_nsync_update_ = RegUserMsgSafe("nsync_update", -1);
    message_nsync_destroy_ = RegUserMsgSafe("nsync_destroy", -1);
    next_entity_id_ = 1;
    last_processed_time_ = -1.0;
    entities_.clear();
    types_.clear();
    client_visible_entities_.clear();
    clients_ready_for_sync_.clear();
}

void EntitySync::ClientFirstFrameHandler(ClientId client)
{
    if (!ClientSupportsEntitySync(client))
    {
        return;
    }

    clients_ready_for_sync_.insert(client);

    auto& visible_set = client_visible_entities_[client];
    for (const auto& [_, entity] : entities_)
    {
        if (visible_set.count(entity.entity_id))
        {
            continue;
        }

        if (IsEntityVisibleToClient(client, entity))
        {
            SendEntityCreate(client, entity);
        }
    }
}

void EntitySync::ClientDisconnectedHandler(ClientId client)
{
    client_visible_entities_.erase(client);
    clients_ready_for_sync_.erase(client);

    cssdk::Edict* edict = type_conversion::EdictByIndex(client);
    if (!edict)
    {
        return;
    }

    for (const auto& [entity_id, entity] : entities_)
    {
        if (entity.bound_edict != edict)
        {
            continue;
        }

        for (int i = 1; i <= rehlds_api::ServerStatic()->GetMaxClients(); ++i)
        {
            if (i == client)
            {
                continue;
            }

            auto cv_it = client_visible_entities_.find(i);
            if (cv_it != client_visible_entities_.end() && cv_it->second.count(entity_id))
            {
                SendEntityDestroy(i, entity);
                cv_it->second.erase(entity_id);
            }
        }
    }
}

void EntitySync::FrameHandler()
{
    if (rehlds_api::ServerData()->GetTime() <= last_processed_time_)
    {
        return;
    }

    last_processed_time_ = rehlds_api::ServerData()->GetTime();

    for (auto it = entities_.begin(); it != entities_.end();)
    {
        SyncedEntity& entity = it->second;

        auto type_it = types_.find(entity.type_id);
        if (type_it == types_.end())
        {
            ++it;
            continue;
        }

        const EntityTypeDescriptor& type = type_it->second;
        cssdk::Edict* bound_edict = entity.bound_edict;

        if (bound_edict && (bound_edict->free || bound_edict->serial_number != entity.last_serialnumber))
        {
            for (int i = 1; i <= rehlds_api::ServerStatic()->GetMaxClients(); ++i)
            {
                auto cv_it = client_visible_entities_.find(i);
                if (cv_it != client_visible_entities_.end() && cv_it->second.count(entity.entity_id))
                {
                    SendEntityDestroy(i, entity);
                    cv_it->second.erase(entity.entity_id);
                }
            }
            it = entities_.erase(it);
            continue;
        }

        if (type.visibility_getter && bound_edict)
        {
            entity.visibility_ref = type.visibility_getter(entity.bound_edict);
            entity.visibility_ref_serial = entity.visibility_ref.edict ? entity.visibility_ref.edict->serial_number : 0;
        }

        uint16_t field_mask = 0;
        for (const auto& field : type.fields)
        {
            if (field.tracking != FieldTracking::BOUND_EDICT || !field.getter)
            {
                continue;
            }

            if (!bound_edict)
            {
                continue;
            }

            ApplyFieldUpdate(entity, type, field.field_bit, field.getter(entity.bound_edict), field_mask);
        }

        for (int i = 1; i <= rehlds_api::ServerStatic()->GetMaxClients(); ++i)
        {
            if (!clients_ready_for_sync_.count(i))
            {
                continue;
            }

            if (!ClientSupportsEntitySync(i))
            {
                continue;
            }

            cssdk::Edict* client_edict = type_conversion::EdictByIndex(i);
            if (!client_edict || client_edict->free)
            {
                continue;
            }

            bool visible = IsEntityVisibleToClient(i, entity);
            auto& visible_set = client_visible_entities_[i];
            bool was_visible = visible_set.count(entity.entity_id) > 0;

            if (visible && !was_visible)
            {
                SendEntityCreate(i, entity);
            }
            else if (!visible && was_visible)
            {
                SendEntityDestroy(i, entity);
                visible_set.erase(entity.entity_id);
            }
            else if (visible && was_visible && field_mask != 0)
            {
                SendEntityUpdate(i, entity, field_mask);
            }
        }

        for (auto pending = entity.pending_deltas.begin(); pending != entity.pending_deltas.end();)
        {
            if (field_mask & pending->first)
            {
                pending = entity.pending_deltas.erase(pending);
            }
            else
            {
                ++pending;
            }
        }

        ++it;
    }
}

bool EntitySync::IsEntityVisibleToClient(ClientId client, const SyncedEntity& entity) const
{
    if (entity.visibility_ref.mode == VisibilityRefMode::BROADCAST)
    {
        return true;
    }

    cssdk::Edict* client_edict = type_conversion::EdictByIndex(client);
    if (!client_edict || client_edict->free)
    {
        return false;
    }

    if (entity.visibility_ref.mode == VisibilityRefMode::EDICT_PVS || entity.visibility_ref.mode == VisibilityRefMode::EDICT_PAS)
    {
        cssdk::Edict* anchor_edict = entity.visibility_ref.edict;
        if (!anchor_edict || anchor_edict->free || anchor_edict->serial_number != entity.visibility_ref_serial)
        {
            return false;
        }

        cssdk::Vector& origin = anchor_edict->vars.origin;
        unsigned char* pvs = entity.visibility_ref.mode == VisibilityRefMode::EDICT_PVS ? metamod::engine::SetFatPvs(origin)
                                                                                        : metamod::engine::SetFatPas(origin);
        bool is_visible = metamod::engine::CheckVisibility(client_edict, pvs) != 0;

        return is_visible;
    }

    if (entity.visibility_ref.mode == VisibilityRefMode::POSITION_PVS)
    {
        cssdk::Vector origin;
        std::memcpy(origin.Ptr(), entity.visibility_ref.position, sizeof(float) * 3);

        unsigned char* pvs = metamod::engine::SetFatPvs(origin);
        bool is_visible = metamod::engine::CheckVisibility(client_edict, pvs) != 0;

        return is_visible;
    }

    if (entity.visibility_ref.mode == VisibilityRefMode::POSITION_PAS)
    {
        cssdk::Vector origin;
        std::memcpy(origin.Ptr(), entity.visibility_ref.position, sizeof(float) * 3);

        unsigned char* pvs = metamod::engine::SetFatPas(origin);
        bool is_visible = metamod::engine::CheckVisibility(client_edict, pvs) != 0;

        return is_visible;
    }

    return false;
}

bool EntitySync::SendEntityCreate(ClientId client, const SyncedEntity& entity)
{
    auto type_it = types_.find(entity.type_id);
    cssdk::Edict* player = type_conversion::EdictByIndex(client);
    if (message_nsync_create_ == 0 || message_nsync_update_ == 0 || !player || player->free || type_it == types_.end())
    {
        return false;
    }

    EntitySyncPackets::Result prepared =
        EntitySyncPackets::PrepareCreate(entity.type_id, entity.entity_id, PacketSchema(type_it->second), entity.field_cache);
    if (!prepared)
    {
        LOG(WARNING) << "[NclEntitySync] SendEntityCreate: " << prepared.error;
        return false;
    }

    return EntitySyncPackets::PublishCreate(
        prepared, entity.entity_id, client_visible_entities_[client], [&](const EntitySyncPackets::Result& packets) {
            for (uint16_t id : packets.string_ids)
            {
                string_registry_.EnsureSent(client, id);
            }
            SendPackets(packets, player, message_nsync_create_, message_nsync_update_);
        }
    );
}

void EntitySync::SendEntityUpdate(ClientId client, const SyncedEntity& entity, uint16_t field_mask)
{
    auto type_it = types_.find(entity.type_id);
    cssdk::Edict* player = type_conversion::EdictByIndex(client);
    if (message_nsync_update_ == 0 || !player || player->free || type_it == types_.end())
    {
        return;
    }

    EntitySyncPackets::Result prepared = EntitySyncPackets::PrepareUpdate(
        entity.type_id, entity.entity_id, PacketSchema(type_it->second), entity.field_cache, entity.pending_deltas, field_mask
    );
    if (!prepared)
    {
        LOG(WARNING) << "[NclEntitySync] SendEntityUpdate: " << prepared.error;
        return;
    }

    for (uint16_t id : prepared.string_ids)
    {
        string_registry_.EnsureSent(client, id);
    }
    SendPackets(prepared, player, message_nsync_create_, message_nsync_update_);
}

void EntitySync::SendEntityDestroy(ClientId client, const SyncedEntity& entity)
{
    if (message_nsync_destroy_ == 0)
    {
        return;
    }

    cssdk::Edict* player_edict = type_conversion::EdictByIndex(client);
    if (!player_edict)
    {
        return;
    }

    MessageBegin(cssdk::MessageType::One, message_nsync_destroy_, nullptr, player_edict);
    WriteByte(entity.type_id);
    WriteUShort(entity.entity_id);
    MessageEnd();
}

void EntitySync::BroadcastEntityUpdate(SyncedEntity& entity, uint16_t field_mask)
{
    for (int i = 1; i <= rehlds_api::ServerStatic()->GetMaxClients(); ++i)
    {
        if (!ClientSupportsEntitySync(i))
        {
            continue;
        }

        cssdk::Edict* ent = type_conversion::EdictByIndex(i);
        if (!ent || ent->free)
        {
            continue;
        }

        auto cv_it = client_visible_entities_.find(i);
        if (cv_it != client_visible_entities_.end() && cv_it->second.count(entity.entity_id))
        {
            SendEntityUpdate(i, entity, field_mask);
        }
    }

    for (auto it = entity.pending_deltas.begin(); it != entity.pending_deltas.end();)
    {
        if (field_mask & it->first)
        {
            it = entity.pending_deltas.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool EntitySync::ClientSupportsEntitySync(ClientId client) const
{
    NextClientVersion version;
    return next_client_api_.GetNextClientVersion(client, version) && version >= NextClientVersion{2, 5, 0};
}
