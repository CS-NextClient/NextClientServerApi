#include "main.h"
#include "rehlds_api_provider.h"
#include "EventManager.h"
#include "api/NextClientApi.h"
#include "natives/natives.h"

std::unique_ptr<NextClientApi> g_NextClientApi;

INextClientAPI* NAPI()
{
    return g_NextClientApi.get();
}

void ServerActivate_Post(edict_t* pEdictList, int edictCount, int clientMax)
{
    if (g_NextClientApi)
        g_NextClientApi->OnServerActivated(pEdictList, edictCount, clientMax);

    SET_META_RESULT(MRES_IGNORED);
}

void PlayerPostThink(edict_t* pEntity)
{
    if (g_NextClientApi)
        g_NextClientApi->OnPlayerPostThink(ENTINDEX(pEntity));

    SET_META_RESULT(MRES_IGNORED);
}

void ClientPutInServer_Post(edict_t *pEntity)
{
   if (g_NextClientApi)
        g_NextClientApi->OnClientPutInServer(ENTINDEX(pEntity));

    SET_META_RESULT(MRES_IGNORED);
}

BOOL ClientConnect(edict_t* pEntity, const char* pszName, const char* pszAddress, char szRejectReason[128])
{
    if (g_NextClientApi)
        g_NextClientApi->OnClientConnect(ENTINDEX(pEntity));

    RETURN_META_VALUE(MRES_IGNORED, true);
}

void ClientDisconnect(edict_t *pEntity)
{
    if (g_NextClientApi)
        g_NextClientApi->OnClientDisconnect(ENTINDEX(pEntity));

    SET_META_RESULT(MRES_IGNORED);
}

void MessageBegin_Post(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed)
{
    if (g_NextClientApi)
        g_NextClientApi->OnMessageBeginPost(msg_dest, msg_type, pOrigin, ed);

    SET_META_RESULT(MRES_IGNORED);
}

void MessageEnd_Post()
{
    if (g_NextClientApi)
        g_NextClientApi->OnMessageEndPost();

    SET_META_RESULT(MRES_IGNORED);
}

void SV_HandleClientMessage(IRehldsHook_HandleNetCommand* hookchain, IGameClient* apiClient, int8 opcode)
{
    if (opcode == clc_ncl_message)
    {
        auto netMessage = g_RehldsFuncs->GetNetMessage();
        int* readcount = g_RehldsFuncs->GetMsgReadCount();

        uint32_t header = *(uint32_t*) (netMessage->data + *readcount);
        if (header == NCLM_HEADER || header == NCLM_HEADER_OLD)
            *readcount += sizeof(uint32_t);

        if (header == NCLM_HEADER)
        {
            int32_t size = MSG_ReadLong();
            int32_t fullreadcount = *readcount + size - (int32_t)sizeof(size);

            auto nclm_opcode = static_cast<NCLM_C2S>(MSG_ReadByte());

            if (g_NextClientApi)
                g_NextClientApi->OnHandleNCLMessage(apiClient->GetId() + 1, nclm_opcode);

            if (*readcount < fullreadcount)
                *readcount = fullreadcount;

            return;
        }

        if (header == NCLM_HEADER_OLD)
        {
            auto nclm_opcode = static_cast<NCLM_C2S>(MSG_ReadByte());

            if (g_NextClientApi)
                g_NextClientApi->OnHandleNCLMessage(apiClient->GetId() + 1, nclm_opcode);

            return;
        }
    }

    hookchain->callNext(apiClient, opcode);
}

void SV_SendServerinfo(IRehldsHook_SV_SendServerinfo* hookchain, sizebuf_t *msg, IGameClient* apiClient) {
    if (g_NextClientApi)
        g_NextClientApi->OnSendServerInfo(apiClient->GetId() + 1);

    hookchain->callNext(msg, apiClient);
}

void ClientConnected(IRehldsHook_ClientConnected* hookchain, IGameClient* apiClient) {
    hookchain->callNext(apiClient);

    if (g_NextClientApi)
        g_NextClientApi->OnClientEstablishConnection(apiClient->GetId() + 1);
}

void SV_DropClient(IRehldsHook_SV_DropClient* hookchain, IGameClient* apiClient, bool crash, const char *buf) {
    hookchain->callNext(apiClient, crash, buf);

    if (g_NextClientApi)
        g_NextClientApi->OnClientDropConnection(apiClient->GetId() + 1, crash, buf);
}

cvar_t cvar_nclapi_version = {"nclapi_version", MODULE_VERSION, FCVAR_SERVER | FCVAR_SPONLY};

void OnAmxxAttach()
{
    if (!RehldsApi_Init())
        return;

    g_NextClientApi = std::make_unique<NextClientApi>();
    g_RehldsHookchains->HandleNetCommand()->registerHook(SV_HandleClientMessage);
    g_RehldsHookchains->SV_SendServerinfo()->registerHook(SV_SendServerinfo);
    g_RehldsHookchains->ClientConnected()->registerHook(ClientConnected);
    g_RehldsHookchains->SV_DropClient()->registerHook(SV_DropClient);

    CVAR_REGISTER(&cvar_nclapi_version);

    AddNatives_All();

    MF_PrintSrvConsole("[%s] Successfully loaded, version %s\n", MODULE_NAME, MODULE_VERSION);
}

void OnPluginsLoaded()
{
    if (g_NextClientApi)
        g_NextClientApi->OnAmxxPluginsLoaded();
}

void OnAmxxDetach()
{
    g_NextClientApi = nullptr;
    g_RehldsHookchains->HandleNetCommand()->unregisterHook(SV_HandleClientMessage);
    g_RehldsHookchains->SV_SendServerinfo()->unregisterHook(SV_SendServerinfo);
    g_RehldsHookchains->ClientConnected()->unregisterHook(ClientConnected);
    g_RehldsHookchains->SV_DropClient()->unregisterHook(SV_DropClient);
}