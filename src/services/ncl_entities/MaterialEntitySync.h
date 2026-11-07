#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>

#include "EntitySync.h"
#include "MaterialVisibilityPolicy.h"
#include <cssdk/common/entity_state.h>
#include "services/StringRegistry.h"
#include "services/server_events/ServerEventsManager.h"

// What a server has dressed an entity in.
//
// A type of its own rather than a field of the weapon: wearing a material is not a property
// of being a weapon, and the client that draws them knows only entity indices. Anything with
// an edict can wear one.
//
// Nothing announces the presets. A binding names the file its material comes from, and the
// client reads that file the first time it needs it; delivering the file is ncl_upload_file's
// job and nothing else's.
class MaterialEntitySync : public sigslot::observer
{
    struct DressedEntity
    {
        uint16_t ncl_entity_id{};
        int source_serial{};

        // Pairs of string ids: which preset a material came from and its name there.
        std::vector<std::pair<uint16_t, uint16_t>> materials{};

        // Instance values, keyed by the string id of "uWear" or "texture/uWear".
        std::unordered_map<uint16_t, float> params{};
    };

    ServerEventsManager& server_events_manager_;
    StringRegistry& string_registry_;
    EntitySync& entity_sync_;
    INextClientInfo& next_client_info_;
    MaterialVisibilityPolicy visibility_;
    static MaterialEntitySync* instance_;

    std::unordered_map<int, DressedEntity> entities_;

public:
    explicit MaterialEntitySync(
        ServerEventsManager& server_events_manager,
        StringRegistry& string_registry,
        EntitySync& entity_sync,
        INextClientInfo& next_client_info
    );
    ~MaterialEntitySync();
    bool SetThroughWalls(cssdk::Edict* entity, bool enabled);

    // Puts one material of one preset on an entity. Binding is idempotent, and the client
    // replaces whatever else dressed the same texture.
    bool Bind(cssdk::Edict* entity, const std::string& preset, const std::string& material);

    bool Unbind(cssdk::Edict* entity, const std::string& preset, const std::string& material);

    // Takes everything off and stops synchronizing the entity.
    void Clear(cssdk::Edict* entity);

    // One finite instance value in the declared parameter units. An empty
    // texture writes it over every material the entity wears that declares the parameter.
    bool SetParam(cssdk::Edict* entity, const std::string& texture, const std::string& name, float value);

private:
    void ServerActivatedHandler(ServerActivatedEvent event);
    void RefreshVisibility();
    bool CheckRecipient(cssdk::Edict* host) const;
    static cssdk::qboolean PackPre(cssdk::EntityState*, int, cssdk::Edict*, cssdk::Edict*, int, cssdk::qboolean, unsigned char*);
    static cssdk::qboolean PackPost(cssdk::EntityState*, int, cssdk::Edict*, cssdk::Edict*, int, cssdk::qboolean, unsigned char*);
    static cssdk::qboolean VisibilityPre(cssdk::Edict*, unsigned char*);

    // The synchronized entity is created on the first thing said about it, so a plugin never
    // has to register anything first.
    DressedEntity* Ensure(cssdk::Edict* entity);
};

struct MaterialNclEntitySyncService
    : kgr::single_service<
          MaterialEntitySync,
          kgr::dependency<ServerEventsManagerService, StringRegistryService, EntitySyncService, INextClientInfoService>>
{};
