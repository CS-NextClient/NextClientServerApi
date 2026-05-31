#pragma once
#include <cssdk/public/rehlds.h>

namespace sv_events
{
    void SV_DropClientHandler(cssdk::ReHookSvDropClient* hookchain, cssdk::IGameClient* client, bool crash, const char* buf);
    void SV_SendServerInfoHandler(cssdk::ReHookSvSendServerInfo* hookchain, cssdk::SizeBuf* msg, cssdk::IGameClient* client);
    void SV_FrameHandler(cssdk::ReHookSvFrame* hookchain);

    cssdk::qboolean ClientConnectPostMetamodHandler(cssdk::Edict* client, const char* name, const char* address, char* reject_reason);
    void ClientDisconnectPostMetamodHandler(cssdk::Edict* client);
    void ClientPutInServerPostMetamodHandler(cssdk::Edict* client);
    void PlayerPostThinkPostMetamodHandler(cssdk::Edict* client);
    void MessageBeginPostMetamodHandler(cssdk::MessageType msg_type, int msg_id, const float* origin, cssdk::Edict* client);
    void MessageEndPostMetamodHandler();
    void ServerActivatePostMetamodHandler(cssdk::Edict* edict_list, int edict_count, int client_max);
} // namespace sv_events
