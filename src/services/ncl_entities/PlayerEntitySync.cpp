#include "PlayerEntitySync.h"

#include <easylogging++.h>

#include <core/type_conversion.h>

using namespace ncl_entity;
using namespace core;

namespace
{
    constexpr uint16_t FIELD_PLAYER_ID = 1u << 0;
    constexpr uint16_t FIELD_ACTIVE_WEAPON_ID = 1u << 1;

    uint8_t PlayerIdGetter(edict_t* edict)
    {
        return static_cast<uint8_t>(type_conversion::IndexOfEntity(edict));
    }

    uint32_t ActiveWeaponIdGetter(edict_t* edict)
    {
        cssdk::PlayerBase* player = static_cast<cssdk::PlayerBase*>(edict->private_data);

        if (player == nullptr)
        {
            return 0;
        }

        cssdk::PlayerItemBase* active_item = player->active_item;
        if (active_item == nullptr)
        {
            return 0;
        }

        return static_cast<uint32_t>(type_conversion::IndexOfEntity(active_item));
    }
} // namespace

PlayerEntitySync::PlayerEntitySync(ServerEventsManager& server_events_manager, EntitySync& entity_sync) :
    server_events_manager_(server_events_manager),
    entity_sync_(entity_sync)
{
    server_events_manager_.on_server_activated().connect(&PlayerEntitySync::ServerActivatedHandler, this);
    server_events_manager_.on_client_connecting().connect(&PlayerEntitySync::ClientConnectingHandler, this);
}

void PlayerEntitySync::ServerActivatedHandler(ServerActivatedEvent event)
{
    EntityTypeDescriptor player_type;
    player_type.type_id = static_cast<uint8_t>(EntityTypeId::Player);
    player_type.fields = {
        {FIELD_PLAYER_ID, FieldType::BYTE, FieldTracking::BOUND_EDICT, PlayerIdGetter},
        {FIELD_ACTIVE_WEAPON_ID, FieldType::UINT, FieldTracking::BOUND_EDICT, ActiveWeaponIdGetter},
    };

    entity_sync_.RegisterType(player_type);
}

void PlayerEntitySync::ClientConnectingHandler(ClientConnectingEvent event)
{
    cssdk::Edict* player_edict = type_conversion::EdictByIndex(event.client_id);
    if (!player_edict || player_edict->free)
    {
        return;
    }

    entity_sync_.Create(static_cast<uint8_t>(EntityTypeId::Player), player_edict, {}, VisibilityReference::BindEdictPAS(player_edict));
}
