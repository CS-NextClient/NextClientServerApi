/*
 *  Half Life 1 SDK Copyright(c) Valve Corp.
 *
 *  THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE CORPORATION ("Valve").
 *  PLEASE READ IT BEFORE DOWNLOADING OR USING THE HALF LIFE 1 SDK ("SDK"). BY
 *  DOWNLOADING AND/OR USING THE HALF LIFE 1 SDK YOU ACCEPT THIS LICENSE. IF YOU DO
 *  NOT AGREE TO THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.
 *
 *  You may, free of charge, download and use the SDK to develop a modified Valve
 *  game running on the Half-Life 1 engine. You may distribute your modified Valve
 *  game in source and object code form, but only for free. Terms of use for Valve
 *  games are found in the Steam Subscriber Agreement located here:
 *  http://store.steampowered.com/subscriber_agreement/
 *
 *  You may copy, modify, and distribute the SDK and any modifications you make to
 *  the SDK in source and object code form, but only for free. Any distribution of
 *  this SDK must include this LICENSE file.
 *
 *  Any distribution of the SDK or a substantial portion of the SDK must include
 *  the above copyright notice and the following:
 *
 *    DISCLAIMER OF WARRANTIES. THE HALF LIFE 1 SDK AND ANY OTHER MATERIAL
 *    DOWNLOADED BY LICENSEE IS PROVIDED "AS IS". VALVE AND ITS SUPPLIERS
 *    DISCLAIM ALL WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS OR IMPLIED,
 *    INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY,
 *    NON-INFRINGEMENT, TITLE AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    LIMITATION OF LIABILITY. IN NO EVENT SHALL VALVE OR ITS SUPPLIERS BE LIABLE
 *    FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 *    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
 *    LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THE ENGINE AND/OR THE
 *    SDK, EVEN IF VALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *  If you would like to use the SDK for a commercial purpose, please contact Valve
 *  at sourceengine@valvesoftware.com.
 */

#pragma once

#include <cssdk/common/const.h>
#include <cssdk/common/entity_state.h>
#include <cssdk/common/model.h>
#include <cssdk/common/net_address.h>
#include <cssdk/common/user_cmd.h>
#include <cssdk/engine/consistency.h>
#include <cssdk/engine/custom.h>
#include <cssdk/engine/edict.h>
#include <cssdk/engine/prog_defs.h>
#include <cssdk/engine/server.h>
#include <cssdk/engine/server_static.h>
#include <cssdk/public/rehlds/common_rehlds.h>
#include <cssdk/public/rehlds/userid_rehlds.h>
#include <cstdio>

namespace cssdk
{
    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class INetChan // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        virtual const NetAddress* GetRemoteAdr() = 0;

        /**
         * @brief N/D
        */
        virtual SizeBuf* GetMessageBuf() = 0;

#ifdef REHLDS_SELF
        /**
         * @brief This must be the last virtual function in class.
        */
        virtual NetChan* GetNetChannel() = 0;
#endif
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class IGameClient // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        virtual int GetId() = 0;

        /**
         * @brief false = client is free.
        */
        virtual bool IsActive() = 0;

        /**
         * @brief N/D
        */
        virtual void SetActive(bool active) = 0;

        /**
         * @brief false = don't send datagrams.
        */
        virtual bool IsSpawned() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSpawned(bool spawned) = 0;

        /**
         * @brief The client's net connection.
        */
        virtual INetChan* GetNetChannel() = 0;

        /**
         * @brief The datagram is written to after every frame, but only cleared when
         * it is sent out to the client. It can be harmlessly overflowed.
        */
        virtual SizeBuf* GetDatagram() = 0;

        /**
         * @brief EDICT_NUM(client num + 1).
        */
        virtual Edict* GetEdict() = 0;

        /**
         * @brief N/D
        */
        virtual UserId* GetNetworkUserId() = 0;

        /**
         * @brief N/D
        */
        virtual const char* GetName() = 0;

        /**
         * @brief N/D
        */
        virtual bool IsConnected() = 0;

        /**
         * @brief N/D
        */
        virtual void SetConnected(bool connected) = 0;

        /**
         * @brief Which other clients does this guy's voice stream go to?
        */
        virtual uint32 GetVoiceStream(int stream_id) = 0;

        /**
         * @brief N/D
        */
        virtual void SetLastVoiceTime(double time) = 0;

        /**
         * @brief N/D
        */
        virtual double GetLastVoiceTime() = 0;

        /**
         * @brief Does this client want to hear his own voice?
        */
        virtual bool GetLoopback() = 0;

        /**
         * @brief N/D
        */
        virtual UserCmd* GetLastCmd() = 0;

        /**
         * @brief This is spectator proxy (HLTV).
        */
        virtual bool IsProxy() = 0;

        /**
         * @brief N/D
        */
        virtual void SetProxy(bool proxy) = 0;

        /**
         * @brief This client is a fake player controlled by the game DLL.
        */
        virtual bool IsFakeClient() = 0;

        /**
         * @brief N/D
        */
        virtual void SetFakeClient(bool state) = 0;

        /**
         * @brief On server, getting data.
        */
        virtual bool IsFullyConnected() = 0;

        /**
         * @brief N/D
        */
        virtual void SetFullyConnected(bool state) = 0;

        /**
         * @brief N/D
        */
        virtual bool IsUploading() = 0;

        /**
         * @brief N/D
        */
        virtual void SetUploading(bool state) = 0;

        /**
         * @brief N/D
        */
        virtual bool IsHasUserMessages() = 0;

        /**
         * @brief N/D
        */
        virtual void SetHasUserMessages(bool value) = 0;

        /**
         * @brief N/D
        */
        virtual bool HasForceUnmodified() = 0;

        /**
         * @brief N/D
        */
        virtual void SetHasForceUnmodified(bool value) = 0;

        /**
         * @brief Number of packets choked at the server
         * because the client - server network channel is backlogged with too much data.
        */
        virtual int GetChokeCount() = 0;

        /**
         * @brief N/D
        */
        virtual void SetChokeCount(int count) = 0;

        /**
         * @brief -1 = no compression. This is where the server is creating the compressed info from.
        */
        virtual int GetDeltaSequence() = 0;

        /**
         * @brief N/D
        */
        virtual void SetDeltaSequence(int value) = 0;

        /**
         * @brief For filling in big drops.
        */
        virtual void SetLastCmd(UserCmd* user_cmd) = 0;

        /**
         * @brief N/D
        */
        virtual double GetConnectTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetConnectTime(double time) = 0;

        /**
         * @brief N/D
        */
        virtual double GetCmdTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetCmdTime(double time) = 0;

        /**
         * @brief N/D
        */
        virtual double GetIgnoreCmdTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetIgnoreCmdTime(double time) = 0;

        /**
         * @brief N/D
        */
        virtual float GetLatency() = 0;

        /**
         * @brief N/D
        */
        virtual void SetLatency(float latency) = 0;

        /**
         * @brief N/D
        */
        virtual float GetPacketLoss() = 0;

        /**
         * @brief N/D
        */
        virtual void SetPacketLoss(float packet_loss) = 0;

        /**
         * @brief N/D
        */
        virtual double GetLocalTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetLocalTime(double time) = 0;

        /**
         * @brief N/D
        */
        virtual double GetSvTimeBase() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSvTimeBase(double time) = 0;

        /**
         * @brief Or time of disconnect for zombies.
        */
        virtual double GetConnectionStartedTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetConnectionStartedTime(double time) = 0;

        /**
         * @brief Time when we should send next world state update (datagram).
        */
        virtual double GetNextMessageTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetNextMessageTime(double time) = 0;

        /**
         * @brief Default time to wait for next message.
        */
        virtual double GetNextMessageIntervalTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetNextMessageIntervalTime(double time_interval) = 0;

        /**
         * @brief false - only send messages if the client has sent one and the bandwidth is not choked.
        */
        virtual bool GetSendMessageState() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSendMessageState(bool state) = 0;

        /**
         * @brief N/D
        */
        virtual bool GetSkipMessageState() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSkipMessageState(bool state) = 0;

        /**
         * @brief N/D
        */
        virtual bool GetSendInfoState() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSendInfoState(bool state) = 0;

        /**
         * @brief N/D
        */
        virtual float GetSendInfoTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSendInfoTime(float time) = 0;

        /**
         * @brief Updates can be deltad from here.
        */
        virtual ClientFrame* GetFrames() = 0;

        /**
         * @brief Per edict events.
        */
        virtual EventState* GetEvents() = 0;

        /**
         * @brief View Entity (camera or the client itself) svc_set_view.
        */
        virtual const Edict* GetViewEntity() = 0;

        /**
         * @brief N/D
        */
        virtual void SetViewEntity(const Edict* entity) = 0;

        /**
         * @brief Identifying number on server.
        */
        virtual int GetUserId() = 0;

        /**
         * @brief N/D
        */
        virtual void SetUserId(int user_id) = 0;

        /**
         * @brief Name, etc (received from client).
        */
        virtual char* GetUserInfo() = 0;

        /**
         * @brief MD5 hash is 32 hex #'s, plus trailing 0.
         * Hashed CD Key (32 hex alphabetic chars + 0 terminator)
        */
        virtual char* GetHashedCdKey() = 0;

        /**
         * @brief N/D
        */
        virtual int GetTopColor() = 0;

        /**
         * @brief N/D
        */
        virtual void SetTopColor(int color) = 0;

        /**
         * @brief N/D
        */
        virtual int GetBottomColor() = 0;

        /**
         * @brief N/D
        */
        virtual void SetBottomColor(int color) = 0;

        /**
         * @brief N/D
        */
        virtual Resource* GetResourcesOnHand() = 0;

        /**
         * @brief N/D
        */
        virtual Resource* GetResourcesNeeded() = 0;

        /**
         * @brief N/D
        */
        virtual std::FILE* GetUploadFileHandle() = 0;

        /**
         * @brief N/D
        */
        virtual void SetUploadFileHandle(std::FILE* file) = 0;

        /**
         * @brief N/D
        */
        virtual bool IsUploadDoneRegistering() = 0;

        /**
         * @brief N/D
        */
        virtual void SetUploadDoneRegistering(bool state) = 0;

        /**
         * @brief N/D
        */
        virtual Customization* GetCustomizationData() = 0;

        /**
         * @brief N/D
        */
        virtual int GetCrc32MapValue() = 0;

        /**
         * @brief N/D
        */
        virtual void SetCrc32MapValue(int value) = 0;

        /**
         * @brief Perform client side prediction of weapon effects.
         * Determines that the client enabled prediction weapons and will be handled get_weapon_data.
        */
        virtual bool IsClientPredictingWeapons() = 0;

        /**
         * @brief N/D
        */
        virtual void SetClientPredictingWeapons(bool state) = 0;

        /**
         * @brief Perform server side lag compensation of player movement.
         * Determines that the client is requesting lag compensation.
        */
        virtual bool IsClientLagCompensation() = 0;

        /**
         * @brief N/D
        */
        virtual void SetClientLagCompensation(bool state) = 0;

        /**
         * @brief Set on server (transmit to client).
        */
        virtual char* GetPhysInfo() = 0;

        /**
         * @brief N/D
        */
        virtual void SetVoiceStream(int stream_id, int value) = 0;

        /**
         * @brief N/D
        */
        virtual int GetSendResourceCount() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSendResourceCount(int count) = 0;

        /**
         * @brief N/D
        */
        virtual bool IsSentNewResponse() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSentNewResponse(bool state) = 0;

#ifdef REHLDS_SELF
        /**
         * @brief This must be the last virtual function in class.
        */
        virtual Client* GetClient() = 0;
#endif
    };

    class IReHldsServerStatic // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        virtual ~IReHldsServerStatic() = default;

        /**
         * @brief N/D
        */
        virtual int GetMaxClients() = 0;

        /**
         * @brief N/D
        */
        virtual bool IsLogActive() = 0;

        /**
         * @brief N/D
        */
        virtual IGameClient* GetGameClient(int id) = 0;

        /**
         * @brief N/D
        */
        virtual Client* GetClient(int id) = 0;

        /**
         * @brief N/D
        */
        virtual int GetIndexOfClient(Client* client) = 0;

        /**
         * @brief N/D
        */
        virtual int GetMaxClientsLimit() = 0;

        /**
         * @brief N/D
        */
        virtual Client* GetNextClient(Client* client) = 0;

        /**
         * @brief N/D
        */
        virtual int GetSpawnCount() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSpawnCount(int count) = 0;

        /**
         * @brief N/D
        */
        virtual ServerLog* GetLog() = 0;

        /**
         * @brief N/D
        */
        virtual bool IsSecure() = 0;

        /**
         * @brief N/D
        */
        virtual void SetSecure(bool value) = 0;
    };

    class IReHldsServerData // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        virtual ~IReHldsServerData() = default;

        /**
         * @brief N/D
        */
        virtual const char* GetModelName() = 0;

        /**
         * @brief N/D
        */
        virtual const char* GetName() = 0;

        /**
         * @brief N/D
        */
        virtual uint32 GetWorldMapCrc() = 0;

        /**
         * @brief N/D
        */
        virtual uint8* GetClientDllMd5() = 0;

        /**
         * @brief N/D
        */
        virtual SizeBuf* GetDatagram() = 0;

        /**
         * @brief N/D
        */
        virtual SizeBuf* GetReliableDatagram() = 0;

        /**
         * @brief N/D
        */
        virtual void SetModelName(const char* model_name) = 0;

        /**
         * @brief N/D
        */
        virtual void SetConsistencyNum(int num) = 0;

        /**
         * @brief N/D
        */
        virtual int GetConsistencyNum() = 0;

        /**
         * @brief N/D
        */
        virtual int GetResourcesNum() = 0;

        /**
         * @brief N/D
        */
        virtual int GetDecalNameNum() = 0;

        /**
         * @brief N/D
        */
        virtual double GetTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetResourcesNum(int num) = 0;

        /**
         * @brief N/D
        */
        virtual Resource* GetResource(int index) = 0;

        /**
         * @brief N/D
        */
        virtual void SetName(const char* name) = 0;

        /**
         * @brief N/D
        */
        virtual class ISteamGameServer* GetSteamGameServer() = 0;

        /**
         * @brief N/D
        */
        virtual NetAddress* GetNetFrom() = 0;

        /**
         * @brief N/D
        */
        virtual double GetOldTime() = 0;

        /**
         * @brief N/D
        */
        virtual void SetNetFrom(NetAddress* from) = 0;

        /**
         * @brief N/D
        */
        virtual void SetWorldMapCrc(uint32 value) = 0;

        /**
         * @brief N/D
        */
        virtual void SetDecalNameNum(int num) = 0;

        /**
         * @brief N/D
        */
        virtual bool IsActive() = 0;

        /**
         * @brief N/D
        */
        virtual void SetActive(bool state) = 0;

        /**
         * @brief N/D
        */
        virtual bool IsPaused() = 0;

        /**
         * @brief N/D
        */
        virtual void SetPaused(bool state) = 0;

        /**
         * @brief N/D
        */
        virtual int GetLastIndexCheckInPvs() = 0;

        /**
         * @brief N/D
        */
        virtual void SetLastIndexCheckInPvs(int id) = 0;

        /**
         * @brief N/D
        */
        virtual double GetLastIndexCheckTimeInPvs() = 0;

        /**
         * @brief N/D
        */
        virtual void SetLastIndexCheckTimeInPvs(double time) = 0;

        /**
         * @brief N/D
        */
        virtual const char* GetOldName() = 0;

        /**
         * @brief N/D
        */
        virtual void SetOldName(const char* name) = 0;

        /**
         * @brief N/D
        */
        virtual const char* GetStartSpotName() = 0;

        /**
         * @brief N/D
        */
        virtual void SetStartSpotName(const char* start_spot) = 0;

        /**
         * @brief N/D
        */
        virtual Model* GetWorldModel() = 0;

        /**
         * @brief N/D
        */
        virtual void SetWorldModel(Model* model) = 0;

        /**
         * @brief N/D
        */
        virtual Consistency* GetConsistency(int index) = 0;

        /**
         * @brief N/D
        */
        virtual Model* GetModel(int index) = 0;

        /**
         * @brief N/D
        */
        virtual Event* GetEventPrecache(int index) = 0;

        /**
         * @brief N/D
        */
        virtual EntityState* GetEntityBaseline(int index) = 0;

        /**
         * @brief N/D
        */
        virtual ExtraBaselines* GetEntityInstanceBaselines() = 0;

        /**
         * @brief N/D
        */
        virtual int GetNumGenericNames() = 0;

        /**
         * @brief N/D
        */
        virtual void SetNumGenericNames(int num) = 0;

        /**
         * @brief N/D
        */
        virtual int GetNumEdicts() = 0;

        /**
         * @brief N/D
        */
        virtual void SetNumEdicts(int num_edicts) = 0;

        /**
         * @brief N/D
        */
        virtual int GetMaxEdicts() = 0;

        /**
         * @brief N/D
        */
        virtual void SetMaxEdicts(int max_edicts) = 0;

        /**
         * @brief N/D
        */
        virtual Edict* GetEdict(int index) = 0;

        /**
         * @brief N/D
        */
        virtual ServerState GetState() = 0;

        /**
         * @brief N/D
        */
        virtual void SetState(ServerState value) = 0;

        /**
         * @brief N/D
        */
        virtual SizeBuf* GetMulticastBuf() = 0;

        /**
         * @brief N/D
        */
        virtual SizeBuf* GetSpectatorBuf() = 0;

        /**
         * @brief N/D
        */
        virtual SizeBuf* GetSignOnBuf() = 0;
    };
}
