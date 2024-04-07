#include "NextClientApi.h"
#include "utilfuncs.h"
#include <utility>
#include <sstream>
#include <stdio.h>

NextClientApi::NextClientApi()
{
    event_manager_ = std::make_unique<EventManager>();
    event_manager_->AddEventListener(std::shared_ptr<NextClientApi>(this));

    cvar_sandbox_ = std::make_shared<::CvarSandbox>();
    event_manager_->AddEventListener(cvar_sandbox_);

    private_precache_ = std::make_shared<::PrivatePrecache>();
    event_manager_->AddEventListener(private_precache_);

    viewmodel_fx_ = std::make_shared<::ViewmodelFX>();
    event_manager_->AddEventListener(viewmodel_fx_);

    health_next_ = std::make_shared<HealthNext>();
    event_manager_->AddEventListener(health_next_);

    nclm_protocol_ = std::make_shared<NclmProtocol>(event_manager_.get());

    verificator_ = std::make_shared<Verificator>(nclm_protocol_.get(), event_manager_.get());
    event_manager_->AddEventListener(verificator_);

    deathmsg_wpn_icon = std::make_shared<::DeathMsgWpnIcon>();
    event_manager_->AddEventListener(deathmsg_wpn_icon);
}

IViewmodelFX* NextClientApi::ViewmodelFX()
{
    return viewmodel_fx_.get();
}

IPrivatePrecache* NextClientApi::PrivatePrecache()
{
    return private_precache_.get();
}

ICvarSandbox* NextClientApi::CvarSandbox()
{
    return cvar_sandbox_.get();
}

IDeathMsgWpnIcon* NextClientApi::DeathMsgWpnIcon() {
    return deathmsg_wpn_icon.get();
}

bool NextClientApi::ClientIsReady(int client)
{
    if (players_.count(client) == 0)
        return false;

    return players_[client].is_api_ready;
}

void NextClientApi::ClientSetFOV(int client, int fov, float lerpTime)
{
    MESSAGE_BEGIN(MSG_ONE, message_SetFOVEx_, NULL, INDEXENT(client));
    WRITE_BYTE(fov & 0xFF);
    WRITE_LONG(lerpTime);
    MESSAGE_END();
}

void NextClientApi::SendHudSprite(
    int client,
    int channel,
    const char* spritePath,
    const uint8_t spriteColor[3],
    uint8_t alpha,
    int frame,
    float frameRate,
    float inTime,
    float holdTime,
    float outTime,
    float x,
    float y,
    const int spriteRect[4],
    float scaleX,
    float scaleY,
    int renderMode
)
{
    MESSAGE_BEGIN(MSG_ONE, message_HudSprite_, nullptr, INDEXENT(client));
    WRITE_BYTE(channel);
    WRITE_STRING(spritePath);
    WRITE_BYTE(0);
    WRITE_BYTE(spriteColor[0]);
    WRITE_BYTE(spriteColor[1]);
    WRITE_BYTE(spriteColor[2]);
    WRITE_BYTE(alpha);
    WRITE_SHORT(frame);
    WRITE_LONG(frameRate);
    WRITE_LONG(inTime);
    WRITE_LONG(holdTime);
    WRITE_LONG(outTime);
    WRITE_LONG(x);
    WRITE_LONG(y);
    WRITE_SHORT(spriteRect[0]);
    WRITE_SHORT(spriteRect[1]);
    WRITE_SHORT(spriteRect[2]);
    WRITE_SHORT(spriteRect[3]);
    WRITE_LONG(scaleX);
    WRITE_LONG(scaleY);
    WRITE_BYTE(renderMode);
    MESSAGE_END();
}

void NextClientApi::SendHudSpriteFullScreen(
    int client,
    int channel,
    const char* spritePath,
    const uint8_t spriteColor[3],
    uint8_t alpha,
    int frame,
    float frameRate,
    float inTime,
    float holdTime,
    float outTime,
    int renderMode
)
{
    MESSAGE_BEGIN(MSG_ONE, message_HudSprite_, nullptr, INDEXENT(client));
    WRITE_BYTE(channel);
    WRITE_STRING(spritePath);
    WRITE_BYTE(1);
    WRITE_BYTE(spriteColor[0]);
    WRITE_BYTE(spriteColor[1]);
    WRITE_BYTE(spriteColor[2]);
    WRITE_BYTE(alpha);
    WRITE_SHORT(frame);
    WRITE_LONG(frameRate);
    WRITE_LONG(inTime);
    WRITE_LONG(holdTime);
    WRITE_LONG(outTime);
    WRITE_BYTE(renderMode);
    MESSAGE_END();
}

void NextClientApi::ClearHudSprite(int client, int channel)
{
    MESSAGE_BEGIN(MSG_ONE, message_HudSprite_, nullptr, INDEXENT(client));
    WRITE_BYTE(channel);
    WRITE_STRING("");
    MESSAGE_END();
}

void NextClientApi::OnPlayerPostThink(int client)
{
    using ncl_deprecated::NextClientVersion;

    if (players_.count(client) == 0)
        return;

    auto data = &players_[client];
    if (!data->is_api_ready && data->is_using_nextclient) {
        data->is_api_ready = true;

        MF_ExecuteForward(forward_api_ready_, client);
    }

    if(data->is_first_frame) {
        event_manager_->OnClientFirstFrame(client);
        data->is_first_frame = false;
    }

    event_manager_->OnPlayerPostThink(client);
}

void NextClientApi::OnClientEstablishConnection(int client) {
    PlayerData data{};

    data.is_api_ready = false;
    data.is_verificated = false;
    data.client_version = std::make_unique<NextClientVersion>();

    std::string value = INFOKEY_VALUE(GET_INFOKEYBUFFER(INDEXENT(client)), "_ncl");

    if (!value.empty())
    {
        using ncl_deprecated::NextClientVersion;

        if (value == "20") {
            *data.client_version = { 2, 2, 0 };
            data.deprecated_client_version = NextClientVersion::V_2_2_0;
        }
        else if (value == "18") {
            *data.client_version = { 2, 1, 8 };
            data.deprecated_client_version = NextClientVersion::V_2_1_8;
        }
        else if (value == "19") {
            *data.client_version = { 2, 1, 9 };
            data.deprecated_client_version = NextClientVersion::V_2_1_9;
        }
        else if (value == "110") {
            *data.client_version = { 2, 1, 10 };
            data.deprecated_client_version = NextClientVersion::V_2_1_10;
        }
        else if (value == "111") {
            *data.client_version = { 2, 1, 11 };
            data.deprecated_client_version = NextClientVersion::V_2_1_11;
        }
        else if (value == "112") {
            *data.client_version = { 2, 1, 12 };
            data.deprecated_client_version = NextClientVersion::V_2_1_12;
        }
        else if (value[0] == '1')
            data.deprecated_client_version = NextClientVersion::V_2_1_7_OR_LOWER;

        data.is_using_nextclient = true;
    }

    players_[client] = std::move(data);

    event_manager_->OnClientEstablishConnection(client);
}

void NextClientApi::OnClientConnect(int client)
{
    if (players_.count(client) != 0)
        players_[client].is_api_ready = false;

    event_manager_->OnClientConnect(client);
}

ncl_deprecated::NextClientVersion NextClientApi::deprecated_GetNextClientVersion(int client)
{
    using ncl_deprecated::NextClientVersion;
    
    if (players_.count(client) == 0)
        return NextClientVersion::NOT_NEXTCLIENT;

    return players_[client].deprecated_client_version;
}

bool NextClientApi::GetNextClientVersion(int client, NextClientVersion& version) 
{
    if (players_.count(client) == 0)
        return false;

    auto ver = players_[client].client_version.get();
    if(ver == nullptr)
        return false;

    version = *ver;

    return true;
}

bool ParseVersion(std::string in, NextClientVersion& out) {
    if(in.size() > 10) 
        return false;

    size_t major, minor, patch;
    int num = sscanf(in.c_str(), "%d.%d.%d", &major, &minor, &patch);
    if(num != 3)
        return false;

    out = { major, minor, patch };
    return true;
}

void NextClientApi::OnClientVerificated(int client, std::string clientVersion, std::string rsaKeyVersion) 
{
    if (players_.count(client) == 0)
        return;

    auto player = &players_[client];
    player->is_verificated = true;
    player->is_using_nextclient = true;

    auto name = MF_GetPlayerName(client);

    if(!ParseVersion(clientVersion, *player->client_version.get()))
        MF_Log("%s has a bogus version of nextclient (%s)", name, clientVersion.c_str());

    MF_Log("Verificated user %s has joined the game (%s, %s)!\n", name, clientVersion.c_str(), rsaKeyVersion.c_str());
}

void NextClientApi::OnNclmDeclareVersionRequest(int client, std::string clientVersion)
{
    if (players_.count(client) == 0)
        return;

    auto player = &players_[client];
    player->is_verificated = false;
    player->is_using_nextclient = true;

    auto name = MF_GetPlayerName(client);

    if(!ParseVersion(clientVersion, *player->client_version.get()))
        MF_Log("%s has a bogus version of nextclient (%s)", name, clientVersion.c_str());

    MF_Log("NextClient compatibile user %s has joined the game (%s)!\n", name, clientVersion.c_str());
}

int NextClientApi::GetSupportedFeatures(int client)
{
    if (players_.count(client) == 0)
        return 0;

    auto version = players_[client].client_version.get();
    if (version == nullptr)
        return 0;

    int features = 0;

    if (*version >= NextClientVersion{2, 1, 6})
        features |= (FEATURE_CVARS_SANDBOX | FEATURE_VIEWMODEL_FX);

    if (*version >= NextClientVersion{2, 1, 9})
        features |= FEATURE_HUD_SPRITE;

    if (*version >= NextClientVersion{2, 2, 0})
        features |= FEATURE_HUD_SPRITE_RENDERMODE;

    if (*version >= NextClientVersion{2, 3, 0})
        features |= (FEATURE_VERIFICATION | FEATURE_DEATHMSG_WPN_ICON);

    if (*version >= NextClientVersion{2, 4, 0})
        features |= FEATURE_PRIVATE_PRECACHE;

    return features;
}

NextClientUsing NextClientApi::ClientIsUsingNextClient(int client) {
    if (players_.count(client) == 0)
        return NextClientUsing::NOT_USING;

    auto player = &players_[client];
    if(player->is_verificated) 
        return NextClientUsing::USING_VERIFICATED;

    if(player->is_using_nextclient)
        return NextClientUsing::DECLARE_USING;

    return NextClientUsing::NOT_USING;
}

void NextClientApi::OnClientPutInServer(int client) 
{
    if(players_.count(client) == 0) return;

    players_[client].is_first_frame = true;
    event_manager_->OnClientPutInServer(client);
}

void NextClientApi::OnClientDropConnection(int client, bool crash, const char* reason) {
    players_.erase(client);
    event_manager_->OnClientDropConnection(client, crash, reason);
}

void NextClientApi::OnClientDisconnect(int index)
{
    event_manager_->OnClientDisconnect(index);
}

void NextClientApi::OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax)
{
    forward_api_ready_ = MF_RegisterForward("ncl_client_api_ready", ET_IGNORE, FP_CELL, FP_DONE);

    message_SetFOVEx_ = utils::RegUserMsgSafe("SetFOVEx", -1);
    message_HudSprite_ = utils::RegUserMsgSafe("HudSprite", -1);

    event_manager_->OnServerActivated(pEdictList, edictCount, clientMax);
}

void NextClientApi::OnHandleNCLMessage(int client, NCLM_C2S opcode)
{
    nclm_protocol_->OnHandleNCLMessage(client, opcode);
}

void NextClientApi::OnMessageBeginPost(int msg_dest, int msg_type, const float* pOrigin, edict_t* ed)
{
    event_manager_->OnMessageBeginPost(msg_dest, msg_type, pOrigin, ed);
}

void NextClientApi::OnMessageEndPost()
{
    event_manager_->OnMessageEndPost();
}

void NextClientApi::OnSendServerInfo(int client) {
    event_manager_->OnSendServerInfo(client);
}

void NextClientApi::OnAmxxPluginsLoaded()
{
    event_manager_->OnAmxxPluginsLoaded();
}