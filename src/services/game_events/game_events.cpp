#include "game_events.h"
#include <meta_api.h>
#include "GameEventsManager.h"

BOOL ClientConnect(edict_t* pEntity, const char* pszName, const char* pszAddress, char szRejectReason[128])
{
    if (!GameEventsManager::instance_)
    {
        SET_META_RESULT(MRES_IGNORED);
        return TRUE;
    }

    GameEventsManager::instance_->client_connecting_(ClientConnectingEvent{ENTINDEX(pEntity), pszName, pszAddress});

    SET_META_RESULT(MRES_IGNORED);
    return TRUE;
}

void ClientConnectedHandler(IRehldsHook_ClientConnected* hookchain, IGameClient* apiClient)
{
    hookchain->callNext(apiClient);

    if (!GameEventsManager::instance_)
        return;

    GameEventsManager::instance_->client_connected_(apiClient->GetId() + 1);
}

void ClientPutInServer_Post(edict_t* pEntity)
{
    if (!GameEventsManager::instance_)
    {
        SET_META_RESULT(MRES_IGNORED);
        return;
    }

    GameEventsManager::instance_->client_putinserver_(ENTINDEX(pEntity));
    SET_META_RESULT(MRES_IGNORED);
}

void PlayerPostThink(edict_t* pEntity)
{
    if (!GameEventsManager::instance_)
    {
        SET_META_RESULT(MRES_IGNORED);
        return;
    }

    GameEventsManager::instance_->PlayerPostThinkHandler(pEntity);
    SET_META_RESULT(MRES_IGNORED);
}

void ClientDisconnect(edict_t* pEntity)
{
    if (!GameEventsManager::instance_)
    {
        SET_META_RESULT(MRES_IGNORED);
        return;
    }

    GameEventsManager::instance_->client_disconnected_(ENTINDEX(pEntity));
    SET_META_RESULT(MRES_IGNORED);
}

void SV_DropClientHandler(IRehldsHook_SV_DropClient* hookchain, IGameClient* apiClient, bool crash, const char *buf)
{
    hookchain->callNext(apiClient, crash, buf);

    if (!GameEventsManager::instance_)
        return;

    GameEventsManager::instance_->ClientDropConnectionHandler(apiClient, crash, buf);
}

void MessageBegin_Post(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed)
{
    if (!GameEventsManager::instance_)
    {
        SET_META_RESULT(MRES_IGNORED);
        return;
    }

    GameEventsManager::instance_->message_begin_post_(MessageBeginPostEvent{msg_dest, msg_type, pOrigin, ed});
    SET_META_RESULT(MRES_IGNORED);
}

void MessageEnd_Post()
{
    if (!GameEventsManager::instance_)
    {
        SET_META_RESULT(MRES_IGNORED);
        return;
    }

    GameEventsManager::instance_->message_end_post_();
    SET_META_RESULT(MRES_IGNORED);
}

void SV_SendServerinfoHandler(IRehldsHook_SV_SendServerinfo* hookchain, sizebuf_t *msg, IGameClient* apiClient)
{
    if (!GameEventsManager::instance_)
    {
        hookchain->callNext(msg, apiClient);
        return;
    }

    GameEventsManager::instance_->send_server_info_(apiClient->GetId() + 1);
    hookchain->callNext(msg, apiClient);
}

void ServerActivate_Post(edict_t* pEdictList, int edictCount, int clientMax)
{
    if (!GameEventsManager::instance_)
    {
        SET_META_RESULT(MRES_IGNORED);
        return;
    }

    GameEventsManager::instance_->server_activated_(ServerActivatedEvent{pEdictList, edictCount, clientMax});
    SET_META_RESULT(MRES_IGNORED);
}

void OnPluginsLoaded()
{
    if (!GameEventsManager::instance_)
    {
        SET_META_RESULT(MRES_IGNORED);
        return;
    }

    GameEventsManager::instance_->amxx_plugins_loaded_();
}