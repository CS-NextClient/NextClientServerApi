#include "EntitySync.h"

#include <algorithm>

#include <easylogging++.h>

#include <core/rehlds_api.h>
#include <core/type_conversion.h>
#include <metamod/engine.h>

#include "utils/msg_ex.h"

using namespace ncl_entity;
using namespace core;
using namespace msg_ex;

namespace
{
    void WriteArrayFull(const std::vector<std::pair<uint16_t, uint16_t>>& arr)
    {
        if (arr.size() > 254)
        {
            LOG(WARNING) << "[NclEntitySync] WriteArrayFull: array truncated from " << arr.size() << " to 254 pairs";
        }

        uint8_t count = static_cast<uint8_t>(std::min(arr.size(), static_cast<size_t>(254)));
        WriteByte(count);
        for (uint8_t i = 0; i < count; ++i)
        {
            WriteUShort(arr[i].first);
            WriteUShort(arr[i].second);
        }
        WriteByte(0);
    }

    void WriteArrayDelta(const ArrayStringIdPairsDelta& delta)
    {
        if (delta.clear)
        {
            WriteByte(0xFF);
            return;
        }

        uint8_t added_count = static_cast<uint8_t>(std::min(delta.added.size(), static_cast<size_t>(254)));
        uint8_t removed_count = static_cast<uint8_t>(std::min(delta.removed.size(), static_cast<size_t>(255)));

        WriteByte(added_count);
        for (uint8_t i = 0; i < added_count; ++i)
        {
            WriteUShort(delta.added[i].first);
            WriteUShort(delta.added[i].second);
        }
        WriteByte(removed_count);
        for (uint8_t i = 0; i < removed_count; ++i)
        {
            WriteUShort(delta.removed[i].first);
            WriteUShort(delta.removed[i].second);
        }
    }

    void WriteScalarFieldValue(const FieldValue& fv, FieldType type)
    {
        switch (type)
        {
            case FieldType::BYTE:
                WriteByte(std::get<uint8_t>(fv.value));
                break;
            case FieldType::USHORT:
                WriteUShort(std::get<uint16_t>(fv.value));
                break;
            case FieldType::UINT:
                WriteUInt(std::get<uint32_t>(fv.value));
                break;
            case FieldType::FLOAT:
                WriteFloat(std::get<float>(fv.value));
                break;
            case FieldType::COORD:
                WriteCoord(std::get<float>(fv.value));
                break;
            case FieldType::STRING_ID:
                WriteUShort(std::get<uint16_t>(fv.value));
                break;
            default:
                break;
        }
    }

    void WriteDefaultFieldValue(FieldType type)
    {
        switch (type)
        {
            case FieldType::BYTE:
                WriteByte(0);
                break;
            case FieldType::USHORT:
                WriteUShort(0);
                break;
            case FieldType::UINT:
                WriteUInt(0);
                break;
            case FieldType::FLOAT:
                WriteFloat(0);
                break;
            case FieldType::COORD:
                WriteCoord(.0f);
                break;
            case FieldType::STRING_ID:
                WriteUShort(0);
                break;
            case FieldType::ARRAY_STRING_ID_PAIRS:
            case FieldType::ARRAY_STRING_ID_PAIRS_DELTA:
                WriteByte(0);
                WriteByte(0);
                break;
        }
    }

    const std::vector<std::pair<uint16_t, uint16_t>>* GetArrayFromCache(const FieldValue& fv)
    {
        return std::holds_alternative<std::vector<std::pair<uint16_t, uint16_t>>>(fv.value)
                   ? &std::get<std::vector<std::pair<uint16_t, uint16_t>>>(fv.value)
                   : nullptr;
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

    for (const auto& [existing_id, existing_entity] : entities_)
    {
        if (existing_entity.bound_edict == bound_edict && existing_entity.type_id == type_id)
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
            client_visible_entities_[i].insert(entity_id);
        }
    }

    entities_[entity_id] = std::move(entity);
    return entity_id;
}

void EntitySync::ApplyFieldUpdate(
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
        return;
    }

    const EntityFieldDescriptor& field = *field_ptr;
    auto cache_it = entity.field_cache.find(bit);

    if (field.type == FieldType::ARRAY_STRING_ID_PAIRS)
    {
        // Full snapshot only.
        if (!std::holds_alternative<std::vector<std::pair<uint16_t, uint16_t>>>(new_val.value))
        {
            LOG(WARNING) << "[NclEntitySync] Update: ARRAY_STRING_ID_PAIRS expects a vector value (field_bit " << bit << ")";
            return;
        }

        if (cache_it == entity.field_cache.end() || cache_it->second != new_val)
        {
            entity.field_cache[bit] = std::move(new_val);
            actual_field_mask |= bit;
        }
    }
    else if (field.type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA)
    {
        if (std::holds_alternative<ArrayStringIdPairsDelta>(new_val.value))
        {
            const auto& delta = std::get<ArrayStringIdPairsDelta>(new_val.value);

            std::vector<std::pair<uint16_t, uint16_t>> current;
            if (cache_it != entity.field_cache.end())
            {
                const auto* arr_ptr = GetArrayFromCache(cache_it->second);
                if (arr_ptr)
                {
                    current = *arr_ptr;
                }
            }

            if (delta.clear)
            {
                current.clear();
            }

            for (const auto& p : delta.added)
            {
                auto cur_it = std::find_if(current.begin(), current.end(), [&p](const auto& pair) { return pair.first == p.first; });
                if (cur_it != current.end())
                {
                    *cur_it = p;
                }
                else
                {
                    current.push_back(p);
                }
            }

            for (const auto& p : delta.removed)
            {
                auto cur_it = std::find_if(current.begin(), current.end(), [&p](const auto& pair) { return pair.first == p.first; });
                if (cur_it != current.end())
                {
                    current.erase(cur_it);
                }
            }

            entity.field_cache[bit] = FieldValue{std::move(current)};
            entity.pending_deltas[bit] = std::move(new_val);
            actual_field_mask |= bit;
        }
        else if (std::holds_alternative<std::vector<std::pair<uint16_t, uint16_t>>>(new_val.value))
        {
            // Full snapshot for a delta-typed field: compute delta against the cache.
            const auto& new_vec = std::get<std::vector<std::pair<uint16_t, uint16_t>>>(new_val.value);

            ArrayStringIdPairsDelta delta;
            if (cache_it != entity.field_cache.end())
            {
                const auto* old_arr_ptr = GetArrayFromCache(cache_it->second);
                if (old_arr_ptr)
                {
                    auto old_sorted = *old_arr_ptr;
                    auto new_sorted = new_vec;
                    std::sort(old_sorted.begin(), old_sorted.end());
                    std::sort(new_sorted.begin(), new_sorted.end());

                    std::set_difference(
                        old_sorted.begin(), old_sorted.end(), new_sorted.begin(), new_sorted.end(), std::back_inserter(delta.removed)
                    );
                    std::set_difference(
                        new_sorted.begin(), new_sorted.end(), old_sorted.begin(), old_sorted.end(), std::back_inserter(delta.added)
                    );
                }
                else
                {
                    delta.added = new_vec;
                }
            }
            else
            {
                delta.added = new_vec;
            }

            if (!delta.added.empty() || !delta.removed.empty())
            {
                entity.field_cache[bit] = std::move(new_val);
                entity.pending_deltas[bit] = FieldValue{std::move(delta)};
                actual_field_mask |= bit;
            }
        }
        else
        {
            LOG(WARNING) << "[NclEntitySync] Update: ARRAY_STRING_ID_PAIRS_DELTA expects a vector or delta value (field_bit " << bit << ")";
        }
    }
    else
    {
        if (cache_it == entity.field_cache.end() || cache_it->second != new_val)
        {
            entity.field_cache[bit] = std::move(new_val);
            actual_field_mask |= bit;
        }
    }
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

    uint16_t actual_field_mask = 0;
    for (const auto& [bit, val] : fields)
    {
        ApplyFieldUpdate(entity, type, bit, val, actual_field_mask);
    }

    if (actual_field_mask != 0)
    {
        BroadcastEntityUpdate(entity, actual_field_mask);
    }
}

void EntitySync::Update(uint16_t entity_id, uint16_t field_bit, FieldValue value)
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

    uint16_t actual_field_mask = 0;
    ApplyFieldUpdate(entity, type_it->second, field_bit, std::move(value), actual_field_mask);

    if (actual_field_mask != 0)
    {
        BroadcastEntityUpdate(entity, actual_field_mask);
    }
}

bool EntitySync::Exists(uint16_t entity_id) const
{
    return entity_id != 0 && entities_.count(entity_id) > 0;
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
            visible_set.insert(entity.entity_id);
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

            FieldValue new_value = field.getter(entity.bound_edict);
            auto cache_it = entity.field_cache.find(field.field_bit);
            if (cache_it == entity.field_cache.end() || cache_it->second != new_value)
            {
                entity.field_cache[field.field_bit] = std::move(new_value);
                field_mask |= field.field_bit;
            }
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
                visible_set.insert(entity.entity_id);
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

void EntitySync::SendEntityCreate(ClientId client, const SyncedEntity& entity)
{
    if (message_nsync_create_ == 0)
    {
        return;
    }

    EnsureStringsForClient(client, entity);

    cssdk::Edict* player_edict = type_conversion::EdictByIndex(client);
    if (!player_edict)
    {
        return;
    }

    auto type_it = types_.find(entity.type_id);
    if (type_it == types_.end())
    {
        return;
    }

    const EntityTypeDescriptor& type = type_it->second;

    MessageBegin(cssdk::MessageType::One, message_nsync_create_, nullptr, player_edict);
    WriteByte(entity.type_id);
    WriteUShort(entity.entity_id);

    for (const EntityFieldDescriptor& field : type.fields)
    {
        auto it = entity.field_cache.find(field.field_bit);
        if (it == entity.field_cache.end())
        {
            WriteDefaultFieldValue(field.type);
            continue;
        }

        if (field.type == FieldType::ARRAY_STRING_ID_PAIRS || field.type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA)
        {
            const auto* arr = GetArrayFromCache(it->second);
            if (arr)
            {
                WriteArrayFull(*arr);
            }
            else
            {
                WriteDefaultFieldValue(field.type);
            }
        }
        else
        {
            WriteScalarFieldValue(it->second, field.type);
        }
    }

    metamod::engine::MessageEnd();
}

void EntitySync::SendEntityUpdate(ClientId client, const SyncedEntity& entity, uint16_t field_mask)
{
    if (message_nsync_update_ == 0)
    {
        return;
    }

    EnsureStringsForClient(client, entity);

    cssdk::Edict* player_edict = type_conversion::EdictByIndex(client);
    if (!player_edict)
    {
        return;
    }

    auto type_it = types_.find(entity.type_id);
    if (type_it == types_.end())
    {
        return;
    }

    const EntityTypeDescriptor& type = type_it->second;

    MessageBegin(cssdk::MessageType::One, message_nsync_update_, nullptr, player_edict);
    WriteByte(entity.type_id);
    WriteUShort(entity.entity_id);
    WriteUShort(field_mask);

    for (const EntityFieldDescriptor& field : type.fields)
    {
        if ((field_mask & field.field_bit) == 0)
        {
            continue;
        }

        if (field.type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA)
        {
            auto pending_it = entity.pending_deltas.find(field.field_bit);
            if (pending_it != entity.pending_deltas.end() && std::holds_alternative<ArrayStringIdPairsDelta>(pending_it->second.value))
            {
                WriteArrayDelta(std::get<ArrayStringIdPairsDelta>(pending_it->second.value));
            }
            else
            {
                // No pending delta: stream the current cached state as an empty-delta snapshot.
                auto cache_it = entity.field_cache.find(field.field_bit);
                const std::vector<std::pair<uint16_t, uint16_t>>* arr =
                    cache_it != entity.field_cache.end() ? GetArrayFromCache(cache_it->second) : nullptr;
                if (arr)
                {
                    WriteArrayFull(*arr);
                }
                else
                {
                    WriteDefaultFieldValue(field.type);
                }
            }
        }
        else if (field.type == FieldType::ARRAY_STRING_ID_PAIRS)
        {
            auto cache_it = entity.field_cache.find(field.field_bit);
            const std::vector<std::pair<uint16_t, uint16_t>>* arr =
                cache_it != entity.field_cache.end() ? GetArrayFromCache(cache_it->second) : nullptr;
            if (arr)
            {
                WriteArrayFull(*arr);
            }
            else
            {
                WriteDefaultFieldValue(field.type);
            }
        }
        else
        {
            auto cache_it = entity.field_cache.find(field.field_bit);
            if (cache_it != entity.field_cache.end())
            {
                WriteScalarFieldValue(cache_it->second, field.type);
            }
            else
            {
                WriteDefaultFieldValue(field.type);
            }
        }
    }

    metamod::engine::MessageEnd();
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

void EntitySync::EnsureStringsForClient(ClientId client, const SyncedEntity& entity)
{
    auto type_it = types_.find(entity.type_id);
    if (type_it == types_.end())
    {
        return;
    }

    for (const EntityFieldDescriptor& field : type_it->second.fields)
    {
        if (field.type == FieldType::STRING_ID)
        {
            auto it = entity.field_cache.find(field.field_bit);
            if (it != entity.field_cache.end())
            {
                string_registry_.EnsureSent(client, std::get<uint16_t>(it->second.value));
            }
        }
        else if (field.type == FieldType::ARRAY_STRING_ID_PAIRS || field.type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA)
        {
            auto it = entity.field_cache.find(field.field_bit);
            if (it != entity.field_cache.end())
            {
                const auto* arr = GetArrayFromCache(it->second);
                if (arr)
                {
                    for (const auto& p : *arr)
                    {
                        string_registry_.EnsureSent(client, p.first);
                        string_registry_.EnsureSent(client, p.second);
                    }
                }
            }
        }
    }
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
