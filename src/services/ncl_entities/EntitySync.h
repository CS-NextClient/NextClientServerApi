#pragma once
#include <unordered_map>
#include <unordered_set>

#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>

#include <nextclientapi_amxx/ncl_entity.h>
#include <cssdk/engine/edict.h>

#include "services/server_events/ServerEventsManager.h"
#include "services/StringRegistry.h"
#include "services/INextClientInfo.h"
#include "services/nclm_protocol/NclmProtocol.h"

class EntitySync : public sigslot::observer
{
    StringRegistry& string_registry_;
    INextClientInfo& next_client_api_;

    int message_nsync_create_{};
    int message_nsync_update_{};
    int message_nsync_destroy_{};

    uint32_t next_entity_id_ = 1;

    double last_processed_time_ = -1.0;

    std::unordered_map<uint8_t, ncl_entity::EntityTypeDescriptor> types_;
    std::unordered_map<uint16_t, ncl_entity::SyncedEntity> entities_;
    std::unordered_map<ClientId, std::unordered_set<uint16_t>> client_visible_entities_;
    std::unordered_set<ClientId> clients_ready_for_sync_;

public:
    explicit EntitySync(ServerEventsManager& server_events_manager, StringRegistry& string_registry, INextClientInfo& next_client_api);

    void RegisterType(ncl_entity::EntityTypeDescriptor& descriptor);

    // Generic entity API
    uint16_t Create(
        uint8_t type_id,
        cssdk::Edict* bound_edict,
        std::unordered_map<uint16_t, ncl_entity::FieldValue> fields,
        const ncl_entity::VisibilityReference& initial_visibility
    );
    void Update(uint16_t entity_id, const std::unordered_map<uint16_t, ncl_entity::FieldValue>& fields);
    void Update(uint16_t entity_id, uint16_t field_bit, ncl_entity::FieldValue value);
    void Destroy(uint16_t entity_id);
    void SetAnchor(uint16_t entity_id, const ncl_entity::VisibilityReference& visibility_ref);
    bool Exists(uint16_t entity_id) const;

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
    void ClientFirstFrameHandler(ClientId client);
    void ClientDisconnectedHandler(ClientId client);
    void FrameHandler();

    void ApplyFieldUpdate(
        ncl_entity::SyncedEntity& entity,
        const ncl_entity::EntityTypeDescriptor& type,
        uint16_t field_bit,
        ncl_entity::FieldValue value,
        uint16_t& actual_field_mask
    );

    bool IsEntityVisibleToClient(ClientId client, const ncl_entity::SyncedEntity& entity) const;

    void SendEntityCreate(ClientId client, const ncl_entity::SyncedEntity& entity);
    void SendEntityUpdate(ClientId client, const ncl_entity::SyncedEntity& entity, uint16_t field_mask);
    void SendEntityDestroy(ClientId client, const ncl_entity::SyncedEntity& entity);

    void EnsureStringsForClient(ClientId client, const ncl_entity::SyncedEntity& entity);
    void BroadcastEntityUpdate(ncl_entity::SyncedEntity& entity, uint16_t field_mask);

    bool ClientSupportsEntitySync(ClientId client) const;
};

struct EntitySyncService
    : kgr::single_service<EntitySync, kgr::dependency<ServerEventsManagerService, StringRegistryService, INextClientInfoService>>
{};
