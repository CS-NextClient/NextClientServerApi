#include "server_events.h"

#include <metamod/api.h>
#include <core/type_conversion.h>

#include "ServerEventsManager.h"

using namespace core;

namespace sv_events
{
    void SV_DropClientHandler(cssdk::ReHookSvDropClient* hookchain, cssdk::IGameClient* client, bool crash, const char* buf)
    {
        hookchain->CallNext(client, crash, buf);

        if (!ServerEventsManager::instance_)
        {
            return;
        }

        ServerEventsManager::instance_->ClientDropConnectionHandler(client, crash, buf);
    }

    void SV_SendServerInfoHandler(cssdk::ReHookSvSendServerInfo* hookchain, cssdk::SizeBuf* msg, cssdk::IGameClient* client)
    {
        if (!ServerEventsManager::instance_)
        {
            hookchain->CallNext(msg, client);
            return;
        }

        ServerEventsManager::instance_->send_server_info_(client->GetId() + 1);
        hookchain->CallNext(msg, client);
    }

    void SV_FrameHandler(cssdk::ReHookSvFrame* hookchain)
    {
        hookchain->CallNext();

        if (!ServerEventsManager::instance_)
        {
            return;
        }

        ServerEventsManager::instance_->frame_();
    }

    cssdk::qboolean ClientConnectPostMetamodHandler(cssdk::Edict* client, const char* name, const char* address, char* reject_reason)
    {
        cssdk::qboolean result = metamod::GetRetValue<cssdk::qboolean>();

        if (!ServerEventsManager::instance_)
        {
            RETURN_META_VALUE(metamod::Result::Ignored, result);
        }

        ServerEventsManager::instance_->ClientConnectPostHandler(client, name, address);
        RETURN_META_VALUE(metamod::Result::Ignored, result);
    }

    void ClientDisconnectPostMetamodHandler(cssdk::Edict* client)
    {
        if (!ServerEventsManager::instance_)
        {
            RETURN_META(metamod::Result::Ignored);
        }

        ServerEventsManager::instance_->client_disconnected_(type_conversion::IndexOfEntity(client));
        RETURN_META(metamod::Result::Ignored);
    }

    void ClientPutInServerPostMetamodHandler(cssdk::Edict* client)
    {
        if (!ServerEventsManager::instance_)
        {
            RETURN_META(metamod::Result::Ignored);
        }

        ServerEventsManager::instance_->ClientPutInServerHandler(client);
        RETURN_META(metamod::Result::Ignored);
    }

    void PlayerPostThinkPostMetamodHandler(cssdk::Edict* client)
    {
        if (!ServerEventsManager::instance_)
        {
            RETURN_META(metamod::Result::Ignored);
        }

        ServerEventsManager::instance_->PlayerPostThinkHandler(client);
        RETURN_META(metamod::Result::Ignored);
    }

    void MessageBeginPostMetamodHandler(cssdk::MessageType msg_type, int msg_id, const float* origin, cssdk::Edict* client)
    {
        if (!ServerEventsManager::instance_)
        {
            RETURN_META(metamod::Result::Ignored);
        }

        ServerEventsManager::instance_->message_begin_post_(MessageBeginPostEvent{msg_type, msg_id, origin, client});
        RETURN_META(metamod::Result::Ignored);
    }

    void MessageEndPostMetamodHandler()
    {
        if (!ServerEventsManager::instance_)
        {
            RETURN_META(metamod::Result::Ignored);
        }

        ServerEventsManager::instance_->message_end_post_();
        RETURN_META(metamod::Result::Ignored);
    }

    void ServerActivatePostMetamodHandler(cssdk::Edict* edict_list, int edict_count, int client_max)
    {
        if (!ServerEventsManager::instance_)
        {
            RETURN_META(metamod::Result::Ignored);
        }

        ServerEventsManager::instance_->ServerActivatePostHandler(edict_list, edict_count, client_max);
        RETURN_META(metamod::Result::Ignored);
    }
} // namespace sv_events
