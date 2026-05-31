#include "NextClientApi.h"

#include <amxx/api.h>
#include <metamod/engine.h>
#include <core/type_conversion.h>

#include <easylogging++.h>

using namespace core;
using namespace metamod;

NextClientApi::NextClientApi(ServerEventsManager& server_events_manager, NclmProtocol& nclm_protocol) :
    server_events_manager_(server_events_manager),
    nclm_protocol_(nclm_protocol)
{
    server_events_manager_.on_server_activated().connect(&NextClientApi::ServerActivatedHandler, this);
    server_events_manager_.on_player_think_post().connect(&NextClientApi::PlayerPostThinkHandler, this);
    server_events_manager_.on_client_connecting().connect(&NextClientApi::ClientConnectingHandler, this);
    server_events_manager_.on_client_drop_connection().connect(&NextClientApi::ClientDropConnectionHandler, this);
    nclm_protocol_.on_client_auth().connect(&NextClientApi::ClientAuthHandler, this);
    nclm_protocol_.on_hwid_received().connect(&NextClientApi::HwidReceivedHandler, this);
}

bool NextClientApi::IsClientReady(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
    {
        return false;
    }

    return it->second.is_api_ready;
}

NextClientVersionLegacy NextClientApi::GetNextClientVersionLegacy(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
    {
        return NextClientVersionLegacy::NOT_NEXTCLIENT;
    }

    return it->second.deprecated_client_version;
}

NextClientUsing NextClientApi::IsClientUsingNextClient(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
    {
        return NextClientUsing::NOT_USING;
    }

    const PlayerData& player = it->second;

    if (player.is_verified)
    {
        return NextClientUsing::USING_VERIFIED;
    }

    if (player.is_using_nextclient)
    {
        return NextClientUsing::DECLARE_USING;
    }

    return NextClientUsing::NOT_USING;
}

bool NextClientApi::GetNextClientVersion(ClientId client, NextClientVersion& version_out)
{
    auto it = players_.find(client);
    if (it == players_.end())
    {
        return false;
    }

    const PlayerData& player_data = it->second;

    version_out = it->second.client_version;

    if (!player_data.is_using_nextclient)
    {
        return false;
    }

    return true;
}

int NextClientApi::GetSupportedFeatures(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
    {
        return 0;
    }

    const PlayerData& player_data = it->second;
    const NextClientVersion& version = it->second.client_version;

    if (!player_data.is_using_nextclient)
    {
        return 0;
    }

    int features = 0;

    if (version >= NextClientVersion{2, 1, 6})
    {
        features |= (FEATURE_CVARS_SANDBOX | FEATURE_VIEWMODEL_FX);
    }

    if (version >= NextClientVersion{2, 1, 9})
    {
        features |= FEATURE_HUD_SPRITE;
    }

    if (version >= NextClientVersion{2, 2, 0})
    {
        features |= FEATURE_HUD_SPRITE_RENDERMODE;
    }

    if (version >= NextClientVersion{2, 3, 0})
    {
        features |= (FEATURE_VERIFICATION | FEATURE_DEATHMSG_WPN_ICON);
    }

    if (version >= NextClientVersion{2, 4, 0})
    {
        features |= FEATURE_PRIVATE_PRECACHE;
    }

    if (version >= NextClientVersion{2, 5, 0})
    {
        features |= (FEATURE_WEAPON_SOUND_OVERRIDE | FEATURE_INVERT_MOUSE);
    }

    return features;
}

bool NextClientApi::TryGetClientHwid(ClientId client, std::string& hwid_out)
{
    auto it = players_.find(client);
    if (it == players_.end())
    {
        return false;
    }

    const std::string& hwid = it->second.hwid;
    if (hwid.empty())
    {
        return false;
    }

    hwid_out = hwid;
    return true;
}

bool NextClientApi::ParseVersion(const std::string& in, NextClientVersion& out)
{
    if (in.size() > 10)
    {
        return false;
    }

    int major, minor, patch;
    int num = sscanf(in.c_str(), "%d.%d.%d", &major, &minor, &patch);

    if (num != 3)
    {
        return false;
    }

    if (major < 0 || minor < 0 || patch < 0)
    {
        return false;
    }

    out = {(size_t)major, (size_t)minor, (size_t)patch};
    return true;
}

void NextClientApi::ServerActivatedHandler(ServerActivatedEvent event)
{
    forward_api_ready_ =
        amxx::RegisterForward("ncl_client_api_ready", amxx::ForwardExecType::Ignore, amxx::ForwardParam::Cell, amxx::ForwardParam::Done);

    forward_hwid_received_ = amxx::RegisterForward(
        "ncl_hwid_received", amxx::ForwardExecType::Ignore, amxx::ForwardParam::Cell, amxx::ForwardParam::String, amxx::ForwardParam::Done
    );
}

void NextClientApi::ClientAuthHandler(ClientAuthEvent event)
{
    auto it = players_.find(event.client_id);
    if (it == players_.end())
    {
        PlayerData data{};
        data.is_api_ready = false;
        data.is_verified = false;
        data.client_version = NextClientVersion{};
        it = players_.emplace(event.client_id, data).first;
    }

    PlayerData& player = it->second;
    player.is_verified = event.is_verified;
    player.is_using_nextclient = true;

    const char* name = amxx::GetPlayerName(event.client_id);

    if (!ParseVersion(event.client_version, player.client_version))
    {
        LOG(INFO) << name << " has a bogus version of NextClient (" << event.client_version << ")";
    }

    if (event.is_verified)
    {
        LOG(INFO) << "Verified user " << name << " has joined the game (" << event.client_version << ")!";
    }
    else
    {
        LOG(INFO) << "NextClient compatible user " << name << " has joined the game (" << event.client_version << ")!";
    }
}

void NextClientApi::HwidReceivedHandler(HwidReceivedEvent event)
{
    auto it = players_.find(event.client_id);
    if (it == players_.end())
        return;

    PlayerData& player = it->second;

    if (!player.is_verified)
    {
        LOG(WARNING) << "hwid: received from non-verified client " << amxx::GetPlayerName(event.client_id) << " — ignored";
        return;
    }

    if (!player.hwid.empty())
    {
        LOG(WARNING) << "hwid: duplicate from " << amxx::GetPlayerName(event.client_id) << " — ignored";
        return;
    }

    player.hwid = event.hwid;

    LOG(INFO) << "hwid: stored for " << amxx::GetPlayerName(event.client_id) << " [" << player.hwid << "]";

    amxx::ExecuteForward(forward_hwid_received_, event.client_id, player.hwid.c_str());
}

void NextClientApi::PlayerPostThinkHandler(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
        return;

    PlayerData& data = it->second;
    if (!data.is_api_ready && data.is_using_nextclient)
    {
        data.is_api_ready = true;

        amxx::ExecuteForward(forward_api_ready_, client);
    }
}

void NextClientApi::ClientConnectingHandler(ClientConnectingEvent event)
{
    auto it = players_.find(event.client_id);
    if (it == players_.end())
    {
        PlayerData data{};
        data.is_api_ready = false;
        data.is_verified = false;
        data.client_version = NextClientVersion{};
        data.hwid = {};
        it = players_.emplace(event.client_id, data).first;
    }

    PlayerData& data = it->second;

    cssdk::Edict* entity = type_conversion::EdictByIndex(event.client_id);
    if (!entity)
    {
        LOG(ERROR) << "entity is null (client: " << event.client_id << ")";
        return;
    }

    std::string value = engine::InfoKeyValue(engine::GetInfoKeyBuffer(entity), "_ncl");

    if (!value.empty())
    {
        if (value == "20")
        {
            data.client_version = {2, 2, 0};
            data.deprecated_client_version = NextClientVersionLegacy::V_2_2_0;
        }
        else if (value == "18")
        {
            data.client_version = {2, 1, 8};
            data.deprecated_client_version = NextClientVersionLegacy::V_2_1_8;
        }
        else if (value == "19")
        {
            data.client_version = {2, 1, 9};
            data.deprecated_client_version = NextClientVersionLegacy::V_2_1_9;
        }
        else if (value == "110")
        {
            data.client_version = {2, 1, 10};
            data.deprecated_client_version = NextClientVersionLegacy::V_2_1_10;
        }
        else if (value == "111")
        {
            data.client_version = {2, 1, 11};
            data.deprecated_client_version = NextClientVersionLegacy::V_2_1_11;
        }
        else if (value == "112")
        {
            data.client_version = {2, 1, 12};
            data.deprecated_client_version = NextClientVersionLegacy::V_2_1_12;
        }
        else if (value[0] == '1')
        {
            data.deprecated_client_version = NextClientVersionLegacy::V_2_1_7_OR_LOWER;
        }

        data.is_using_nextclient = true;
    }
}

void NextClientApi::ClientDropConnectionHandler(ClientDropConnectionEvent event)
{
    players_.erase(event.client_id);
}
