#include "NextClientApi.h"
#include <easylogging++.h>
#include "utils/utilfuncs.h"

NextClientApi::NextClientApi(GameEventsManager& game_events_manager, NclmProtocol& nclm_protocol) :
    game_events_manager_(game_events_manager),
    nclm_protocol_(nclm_protocol)
{
    game_events_manager_.on_player_think_post().connect(&NextClientApi::PlayerPostThinkHandler, this);
    game_events_manager_.on_client_connected().connect(&NextClientApi::ClientConnectedHandler, this);
    game_events_manager_.on_client_connecting().connect(&NextClientApi::ClientConnectingHandler, this);
    nclm_protocol_.on_client_auth().connect(&NextClientApi::ClientAuthHandler, this);
}

bool NextClientApi::IsClientReady(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
        return false;

    return it->second.is_api_ready;
}

NextClientVersionLegacy NextClientApi::GetNextClientVersionLegacy(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
        return NextClientVersionLegacy::NOT_NEXTCLIENT;

    return it->second.deprecated_client_version;
}

NextClientUsing NextClientApi::IsClientUsingNextClient(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
        return NextClientUsing::NOT_USING;

    const PlayerData& player = it->second;

    if (player.is_verified)
        return NextClientUsing::USING_VERIFIED;

    if (player.is_using_nextclient)
        return NextClientUsing::DECLARE_USING;

    return NextClientUsing::NOT_USING;
}

bool NextClientApi::GetNextClientVersion(ClientId client, NextClientVersion& version_out)
{
    auto it = players_.find(client);
    if (it == players_.end())
        return false;

    const PlayerData& player_data = it->second;

    version_out = it->second.client_version;

    if (!player_data.is_using_nextclient)
        return false;

    return true;
}

int NextClientApi::GetSupportedFeatures(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
        return 0;

    const PlayerData& player_data = it->second;
    const NextClientVersion& version = it->second.client_version;

    if (!player_data.is_using_nextclient)
        return 0;

    int features = 0;

    if (version >= NextClientVersion{2, 1, 6})
        features |= (FEATURE_CVARS_SANDBOX | FEATURE_VIEWMODEL_FX);

    if (version >= NextClientVersion{2, 1, 9})
        features |= FEATURE_HUD_SPRITE;

    if (version >= NextClientVersion{2, 2, 0})
        features |= FEATURE_HUD_SPRITE_RENDERMODE;

    if (version >= NextClientVersion{2, 3, 0})
        features |= (FEATURE_VERIFICATION | FEATURE_DEATHMSG_WPN_ICON);

    if (version >= NextClientVersion{2, 4, 0})
        features |= FEATURE_PRIVATE_PRECACHE;

    return features;
}

bool NextClientApi::ParseVersion(const std::string& in, NextClientVersion& out)
{
    if (in.size() > 10)
        return false;

    int major, minor, patch;
    int num = sscanf(in.c_str(), "%d.%d.%d", &major, &minor, &patch);

    if (num != 3)
        return false;

    if (major < 0 || minor < 0 || patch < 0)
        return false;

    out = {(size_t)major, (size_t)minor, (size_t)patch};
    return true;
}

void NextClientApi::ClientAuthHandler(ClientAuthEvent event)
{
    auto it = players_.find(event.client);
    if (it == players_.end())
        return;

    PlayerData& player = it->second;
    player.is_verified = event.isVerified;
    player.is_using_nextclient = true;

    const char* name = MF_GetPlayerName(event.client);

    if (!ParseVersion(event.clientVersion, player.client_version))
    {
        LOG(INFO) << name << " has a bogus version of NextClient (" << event.clientVersion << ")";
    }

    if (event.isVerified)
    {
        LOG(INFO) << "Verified user " << name << " has joined the game (" <<  event.clientVersion << ")!";
    }
    else
    {
        LOG(INFO) << "NextClient compatible user " << name << " has joined the game (" <<  event.clientVersion << ")!";
    }
}

void NextClientApi::PlayerPostThinkHandler(ClientId client)
{
    auto it = players_.find(client);
    if (it == players_.end())
        return;

    PlayerData* data = &it->second;
    if (!data->is_api_ready && data->is_using_nextclient)
    {
        data->is_api_ready = true;

        MF_ExecuteForward(forward_api_ready_, client);
    }
}

void NextClientApi::ClientConnectedHandler(ClientId client)
{
    PlayerData data{};

    data.is_api_ready = false;
    data.is_verified = false;
    data.client_version = NextClientVersion{};

    edict_t* entity = INDEXENT(client);
    if (!entity)
    {
        LOG(ERROR) << "entity is null (client: " << client << ")";
        players_[client] = data;
        return;
    }

    std::string value = INFOKEY_VALUE(GET_INFOKEYBUFFER(entity), "_ncl");

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

    players_[client] = data;
}

void NextClientApi::ClientConnectingHandler(ClientConnectingEvent event)
{
    auto it = players_.find(event.client);
    if (it != players_.end())
    {
        it->second.is_api_ready = false;
    }
}
