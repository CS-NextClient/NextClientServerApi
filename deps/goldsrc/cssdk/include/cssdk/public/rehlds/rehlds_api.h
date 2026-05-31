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
#include <cssdk/common/event_args.h>
#include <cssdk/common/hook_chains.h>
#include <cssdk/engine/consistency.h>
#include <cssdk/engine/delta_packet.h>
#include <cssdk/engine/eiface.h>
#include <cssdk/engine/pr_dlls.h>
#include <cssdk/engine/server.h>
#include <cssdk/public/rehlds/cmd_rehlds.h>
#include <cssdk/public/rehlds/flight_recorder.h>
#include <cssdk/public/rehlds/rehlds_interfaces.h>
#include <cstddef>

namespace cssdk
{
    /**
     * @brief N/D
    */
    constexpr auto REHLDS_API_VERSION_MAJOR = 3;

    /**
     * @brief N/D
    */
    constexpr auto REHLDS_API_VERSION_MINOR = 11;

    /**
     * @brief N/D
    */
    constexpr auto VREHLDS_HLDS_API_VERSION = "VREHLDS_HLDS_API_VERSION001";

    // Steam_NotifyClientConnect hook
    using ReHookSteamNotifyClientConnect = IHookChain<qboolean, IGameClient*, const void*, unsigned int>;
    using ReHookRegistrySteamNotifyClientConnect = IHookChainRegistry<qboolean, IGameClient*, const void*, unsigned int>;

    // SV_ConnectClient hook
    using ReHookSvConnectClient = IHookChainVoid<>;
    using ReHookRegistrySvConnectClient = IHookChainVoidRegistry<>;

    // SV_GetIDString hook
    using ReHookSvGetIdString = IHookChain<char*, UserId*>;
    using ReHookRegistrySvGetIdString = IHookChainRegistry<char*, UserId*>;

    // SV_SendServerinfo hook
    using ReHookSvSendServerInfo = IHookChainVoid<SizeBuf*, IGameClient*>;
    using ReHookRegistrySvSendServerInfo = IHookChainVoidRegistry<SizeBuf*, IGameClient*>;

    // SV_CheckProtocol hook
    using ReHookSvCheckProtocol = IHookChain<int, NetAddress*, int>;
    using ReHookRegistrySvCheckProtocol = IHookChainRegistry<int, NetAddress*, int>;

    // SVC_GetChallenge_mod hook
    using ReHookSvcGetChallengeMod = IHookChainVoid<char*, int>;
    using ReHookRegistrySvcGetChallengeMod = IHookChainVoidRegistry<char*, int>;

    // SV_CheckKeyInfo hook
    using ReHookSvCheckKeyInfo = IHookChain<int, NetAddress*, char*, uint16*, int*, char*, char*>;
    using ReHookRegistrySvCheckKeyInfo = IHookChainRegistry<int, NetAddress*, char*, uint16*, int*, char*, char*>;

    // SV_CheckIPRestrictions hook
    using ReHookSvCheckIpRestrictions = IHookChain<int, NetAddress*, int>;
    using ReHookRegistrySvCheckIpRestrictions = IHookChainRegistry<int, NetAddress*, int>;

    // SV_FinishCertificateCheck hook
    using ReHookSvFinishCertificateCheck = IHookChain<int, NetAddress*, int, char*, char*>;
    using ReHookRegistrySvFinishCertificateCheck = IHookChainRegistry<int, NetAddress*, int, char*, char*>;

    // Steam_NotifyBotConnect hook
    using ReHookSteamNotifyBotConnect = IHookChain<qboolean, IGameClient*>;
    using ReHookRegistrySteamNotifyBotConnect = IHookChainRegistry<qboolean, IGameClient*>;

    // SerializeSteamId
    using ReHookSerializeSteamId = IHookChainVoid<UserId*, UserId*>;
    using ReHookRegistrySerializeSteamId = IHookChainVoidRegistry<UserId*, UserId*>;

    // SV_CompareUserID hook
    using ReHookSvCompareUserId = IHookChain<qboolean, UserId*, UserId*>;
    using ReHookRegistrySvCompareUserId = IHookChainRegistry<qboolean, UserId*, UserId*>;

    // Steam_NotifyClientDisconnect
    using ReHookSteamNotifyClientDisconnect = IHookChainVoid<IGameClient*>;
    using ReHookRegistrySteamNotifyClientDisconnect = IHookChainVoidRegistry<IGameClient*>;

    // PreProcessPacket
    using ReHookPreprocessPacket = IHookChain<bool, uint8*, unsigned int, const NetAddress&>;
    using ReHookRegistryPreprocessPacket = IHookChainRegistry<bool, uint8*, unsigned int, const NetAddress&>;

    // ValidateCommand
    using ReHookValidateCommand = IHookChain<bool, const char*, CmdSource, IGameClient*>;
    using ReHookRegistryValidateCommand = IHookChainRegistry<bool, const char*, CmdSource, IGameClient*>;

    // ExecuteServerStringCmd
    using ReHookExecuteServerStringCmd = IHookChainVoid<const char*, CmdSource, IGameClient*>;
    using ReHookRegistryExecuteServerStringCmd = IHookChainVoidRegistry<const char*, CmdSource, IGameClient*>;

    // ClientConnected
    using ReHookClientConnected = IHookChainVoid<IGameClient*>;
    using ReHookRegistryClientConnected = IHookChainVoidRegistry<IGameClient*>;

    // HandleNetCommand
    using ReHookHandleNetCommand = IHookChainVoid<IGameClient*, uint8>;
    using ReHookRegistryHandleNetCommand = IHookChainVoidRegistry<IGameClient*, uint8>;

    // Mod_LoadBrushModel
    using ReHookModLoadBrushModel = IHookChainVoid<Model*, void*>;
    using ReHookRegistryModLoadBrushModel = IHookChainVoidRegistry<Model*, void*>;

    // Mod_LoadStudioModel
    using ReHookModLoadStudioModel = IHookChainVoid<Model*, void*>;
    using ReHookRegistryModLoadStudioModel = IHookChainVoidRegistry<Model*, void*>;

    // SV_EmitEvents hook
    using ReHookSvEmitEvents = IHookChainVoid<IGameClient*, PacketEntities*, SizeBuf*>;
    using ReHookRegistrySvEmitEvents = IHookChainVoidRegistry<IGameClient*, PacketEntities*, SizeBuf*>;

    // EV_PlayReliableEvent hook
    using ReHookEvPlayReliableEvent = IHookChainVoid<IGameClient*, int, unsigned short, float, EventArgs*>;
    using ReHookRegistryEvPlayReliableEvent = IHookChainVoidRegistry<IGameClient*, int, unsigned short, float, EventArgs*>;

    // SV_StartSound hook
    using ReHookSvStartSound = IHookChainVoid<int, Edict*, int, const char*, int, float, int, int>;
    using ReHookRegistrySvStartSound = IHookChainVoidRegistry<int, Edict*, int, const char*, int, float, int, int>;

    // PF_Remove_I hook
    using ReHookPfRemoveI = IHookChainVoid<Edict*>;
    using ReHookRegistryPfRemoveI = IHookChainVoidRegistry<Edict*>;

    // PF_BuildSoundMsg_I hook
    using ReHookPfBuildSoundMsgI =
        IHookChainVoid<Edict*, int, const char*, float, float, int, int, int, int, const float*, Edict*>;
    using ReHookRegistryPfBuildSoundMsgI =
        IHookChainVoidRegistry<Edict*, int, const char*, float, float, int, int, int, int, const float*, Edict*>;

    // SV_WriteFullClientUpdate hook
    using ReHookSvWriteFullClientUpdate = IHookChainVoid<IGameClient*, char*, std::size_t, SizeBuf*, IGameClient*>;
    using ReHookRegistrySvWriteFullClientUpdate =
        IHookChainVoidRegistry<IGameClient*, char*, std::size_t, SizeBuf*, IGameClient*>;

    // SV_CheckConsistencyResponse hook
    using ReHookSvCheckConsistencyResponse = IHookChain<bool, IGameClient*, Resource*, uint32>;
    using ReHookRegistrySvCheckConsistencyResponse = IHookChainRegistry<bool, IGameClient*, Resource*, uint32>;

    // SV_DropClient hook
    using ReHookSvDropClient = IHookChainVoid<IGameClient*, bool, const char*>;
    using ReHookRegistrySvDropClient = IHookChainVoidRegistry<IGameClient*, bool, const char*>;

    // SV_ActivateServer hook
    using ReHookSvActivateServer = IHookChainVoid<int>;
    using ReHookRegistrySvActivateServer = IHookChainVoidRegistry<int>;

    // SV_WriteVoiceCodec hook
    using ReHookSvWriteVoiceCodec = IHookChainVoid<SizeBuf*>;
    using ReHookRegistrySvWriteVoiceCodec = IHookChainVoidRegistry<SizeBuf*>;

    // Steam_GSGetSteamID hook
    using ReHookSteamGsGetSteamId = IHookChain<uint64>;
    using ReHookRegistrySteamGsGetSteamId = IHookChainRegistry<uint64>;

    // SV_TransferConsistencyInfo hook
    using ReHookSvTransferConsistencyInfo = IHookChain<int>;
    using ReHookRegistrySvTransferConsistencyInfo = IHookChainRegistry<int>;

    // Steam_GSBUpdateUserData hook
    using ReHookSteamGsbUpdateUserData = IHookChain<bool, uint64, const char*, uint32>;
    using ReHookRegistrySteamGsbUpdateUserData = IHookChainRegistry<bool, uint64, const char*, uint32>;

    // Cvar_DirectSet hook
    using ReHookCvarDirectSet = IHookChainVoid<CVar*, const char*>;
    using ReHookRegistryCvarDirectSet = IHookChainVoidRegistry<CVar*, const char*>;

    // SV_EstablishTimeBase hook
    using ReHookSvEstablishTimeBase = IHookChainVoid<IGameClient*, UserCmd*, int, int, int>;
    using ReHookRegistrySvEstablishTimeBase = IHookChainVoidRegistry<IGameClient*, UserCmd*, int, int, int>;

    // SV_Spawn_f hook
    using ReHookSvSpawnF = IHookChainVoid<>;
    using ReHookRegistrySvSpawnF = IHookChainVoidRegistry<>;

    // SV_CreatePacketEntities hook
    using ReHookSvCreatePacketEntities = IHookChain<int, SvDelta, IGameClient*, PacketEntities*, SizeBuf*>;
    using ReHookRegistrySvCreatePacketEntities = IHookChainRegistry<int, SvDelta, IGameClient*, PacketEntities*, SizeBuf*>;

    // SV_EmitSound2 hook
    using ReHookSvEmitSound2 =
        IHookChain<bool, Edict*, IGameClient*, int, const char*, float, float, int, int, int, const float*>;
    using ReHookRegistrySvEmitSound2 =
        IHookChainRegistry<bool, Edict*, IGameClient*, int, const char*, float, float, int, int, int, const float*>;

    // CreateFakeClient hook
    using ReHookCreateFakeClient = IHookChain<Edict*, const char*>;
    using ReHookRegistryCreateFakeClient = IHookChainRegistry<Edict*, const char*>;

    // SV_CheckConnectionLessRateLimits
    using ReHookSvCheckConnectionLessRateLimits = IHookChain<bool, NetAddress&, const uint8*, int>;
    using ReHookRegistrySvCheckConnectionLessRateLimits = IHookChainRegistry<bool, NetAddress&, const uint8*, int>;

    // SV_Frame hook
    using ReHookSvFrame = IHookChainVoid<>;
    using ReHookRegistrySvFrame = IHookChainVoidRegistry<>;

    // SV_ShouldSendConsistencyList hook
    using ReHookSvShouldSendConsistencyList = IHookChain<bool, IGameClient*, bool>;
    using ReHookRegistrySvShouldSendConsistencyList = IHookChainRegistry<bool, IGameClient*, bool>;

    // GetEntityInit hook
    using ReHookGetEntityInit = IHookChain<EntityInitFunction, const char*>;
    using ReHookRegistryGetEntityInit = IHookChainRegistry<EntityInitFunction, const char*>;

    // SV_EmitPings hook
    using ReHookSvEmitPings = IHookChain<void, IGameClient*, SizeBuf*>;
    using ReHookRegistrySvEmitPings = IHookChainRegistry<void, IGameClient*, SizeBuf*>;

    // ED_Alloc hook
    using ReHookEdAlloc = IHookChain<Edict*>;
    using ReHookRegistryEdAlloc = IHookChainRegistry<Edict*>;

    // ED_Free hook
    using ReHookEdFree = IHookChainVoid<Edict*>;
    using ReHookRegistryEdFree = IHookChainVoidRegistry<Edict*>;

    // Con_Printf hook
    using ReHookConPrintf = IHookChain<void, const char*>;
    using ReHookRegistryConPrintf = IHookChainRegistry<void, const char*>;

    class IReHldsHookChains // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        virtual ~IReHldsHookChains() = default;

        virtual ReHookRegistrySteamNotifyClientConnect* SteamNotifyClientConnect() = 0;
        virtual ReHookRegistrySvConnectClient* SvConnectClient() = 0;
        virtual ReHookRegistrySvGetIdString* SvGetIdString() = 0;
        virtual ReHookRegistrySvSendServerInfo* SvSendServerInfo() = 0;
        virtual ReHookRegistrySvCheckProtocol* SvCheckProtocol() = 0;
        virtual ReHookRegistrySvcGetChallengeMod* SvcGetChallengeMod() = 0;
        virtual ReHookRegistrySvCheckKeyInfo* SvCheckKeyInfo() = 0;
        virtual ReHookRegistrySvCheckIpRestrictions* SvCheckIpRestrictions() = 0;
        virtual ReHookRegistrySvFinishCertificateCheck* SvFinishCertificateCheck() = 0;
        virtual ReHookRegistrySteamNotifyBotConnect* SteamNotifyBotConnect() = 0;
        virtual ReHookRegistrySerializeSteamId* SerializeSteamId() = 0;
        virtual ReHookRegistrySvCompareUserId* SvCompareUserId() = 0;
        virtual ReHookRegistrySteamNotifyClientDisconnect* SteamNotifyClientDisconnect() = 0;
        virtual ReHookRegistryPreprocessPacket* PreprocessPacket() = 0;
        virtual ReHookRegistryValidateCommand* ValidateCommand() = 0;
        virtual ReHookRegistryClientConnected* ClientConnected() = 0;
        virtual ReHookRegistryHandleNetCommand* HandleNetCommand() = 0;
        virtual ReHookRegistryModLoadBrushModel* ModLoadBrushModel() = 0;
        virtual ReHookRegistryModLoadStudioModel* ModLoadStudioModel() = 0;
        virtual ReHookRegistryExecuteServerStringCmd* ExecuteServerStringCmd() = 0;
        virtual ReHookRegistrySvEmitEvents* SvEmitEvents() = 0;
        virtual ReHookRegistryEvPlayReliableEvent* EvPlayReliableEvent() = 0;
        virtual ReHookRegistrySvStartSound* SvStartSound() = 0;
        virtual ReHookRegistryPfRemoveI* PfRemoveI() = 0;
        virtual ReHookRegistryPfBuildSoundMsgI* PfBuildSoundMsgI() = 0;
        virtual ReHookRegistrySvWriteFullClientUpdate* SvWriteFullClientUpdate() = 0;
        virtual ReHookRegistrySvCheckConsistencyResponse* SvCheckConsistencyResponse() = 0;
        virtual ReHookRegistrySvDropClient* SvDropClient() = 0;
        virtual ReHookRegistrySvActivateServer* SvActivateServer() = 0;
        virtual ReHookRegistrySvWriteVoiceCodec* SvWriteVoiceCodec() = 0;
        virtual ReHookRegistrySteamGsGetSteamId* SteamGsGetSteamId() = 0;
        virtual ReHookRegistrySvTransferConsistencyInfo* SvTransferConsistencyInfo() = 0;
        virtual ReHookRegistrySteamGsbUpdateUserData* SteamGsbUpdateUserData() = 0;
        virtual ReHookRegistryCvarDirectSet* CvarDirectSet() = 0;
        virtual ReHookRegistrySvEstablishTimeBase* SvEstablishTimeBase() = 0;
        virtual ReHookRegistrySvSpawnF* SvSpawnF() = 0;
        virtual ReHookRegistrySvCreatePacketEntities* SvCreatePacketEntities() = 0;
        virtual ReHookRegistrySvEmitSound2* SvEmitSound2() = 0;
        virtual ReHookRegistryCreateFakeClient* CreateFakeClient() = 0;
        virtual ReHookRegistrySvCheckConnectionLessRateLimits* SvCheckConnectionLessRateLimits() = 0;
        virtual ReHookRegistrySvFrame* SvFrame() = 0;
        virtual ReHookRegistrySvShouldSendConsistencyList* SvShouldSendConsistencyList() = 0;
        virtual ReHookRegistryGetEntityInit* GetEntityInit() = 0;
        virtual ReHookRegistrySvEmitPings* SvEmitPings() = 0;
        virtual ReHookRegistryEdAlloc* EdAlloc() = 0;
        virtual ReHookRegistryEdFree* EdFree() = 0;
        virtual ReHookRegistryConPrintf* ConPrintf() = 0;
    };

    struct ReHldsFuncs
    {
        /**
         * @brief N/D
        */
        void (*drop_client)(IGameClient* client, bool crash, const char* format, ...){};

        /**
         * @brief N/D
        */
        void (*reject_connection)(NetAddress* address, char* format, ...){};

        /**
         * @brief N/D
        */
        qboolean (*steam_notify_bot_connect)(IGameClient* client){};

        /**
         * @brief N/D
        */
        SizeBuf* (*get_net_message)(){};

        /**
         * @brief N/D
        */
        IGameClient* (*get_host_client)(){};

        /**
         * @brief N/D
        */
        int* (*get_msg_read_count)(){};

        /**
         * @brief N/D
        */
        qboolean (*filter_user)(UserId* user_id){};

        /**
         * @brief N/D
        */
        void (*net_send_packet)(unsigned int length, void* data, const NetAddress& to){};

        /**
         * @brief N/D
        */
        void (*tokenize_string)(char* text){};

        /**
         * @brief N/D
        */
        bool (*check_challenge)(const NetAddress& address, int challenge){};

        /**
         * @brief N/D
        */
        void (*send_user_reg)(SizeBuf* message){};

        /**
         * @brief N/D
        */
        void (*write_delta_descriptions_to_client)(SizeBuf* message){};

        /**
         * @brief N/D
        */
        void (*set_move_vars)(){};

        /**
         * @brief N/D
        */
        void (*write_move_vars_to_client)(SizeBuf* message){};

        /**
         * @brief N/D
        */
        char* (*get_client_fallback)(){};

        /**
         * @brief N/D
        */
        int* (*get_allow_cheats)(){};

        /**
         * @brief N/D
        */
        bool (*gsb_secure)(){};

        /**
         * @brief N/D
        */
        int (*get_build_number)(){};

        /**
         * @brief N/D
        */
        double (*get_real_time)(){};

        /**
         * @brief N/D
        */
        int* (*get_msg_bad_read)(){};

        /**
         * @brief N/D
        */
        CmdSource* (*get_cmd_source)(){};

        /**
         * @brief N/D
        */
        void (*log)(const char* prefix, const char* message){};

        /**
         * @brief N/D
        */
        DllFunctions* (*get_entity_interface)(){};

        /**
         * @brief N/D
        */
        void (*ev_play_reliable_event)(IGameClient* client, int entity_index, unsigned short event_index, float delay,
                                       EventArgs* args){};

        /**
         * @brief N/D
        */
        int (*sv_lookup_sound_index)(const char* sample){};

        /**
         * @brief N/D
        */
        void (*msg_start_bit_writing)(SizeBuf* buf){};

        /**
         * @brief N/D
        */
        void (*msg_write_bits)(uint32 data, int num_bits){};

        /**
         * @brief N/D
        */
        void (*msg_write_bit_vec3_coord)(const Vector& coord){};

        /**
         * @brief N/D
        */
        void (*msg_end_bit_writing)(SizeBuf* buf){};

        /**
         * @brief N/D
        */
        void* (*sz_get_space)(SizeBuf* buf, int length){};

        /**
         * @brief N/D
        */
        CVar* (*get_cvar_vars)(){};

        /**
         * @brief N/D
        */
        int (*sv_get_challenge)(const NetAddress& address){};

        /**
         * @brief N/D
        */
        void (*sv_add_resource)(ResourceType type, const char* name, int size, byte flags, int index){};

        /**
         * @brief N/D
        */
        int (*msg_read_short)(){};

        /**
         * @brief N/D
        */
        int (*msg_read_buf)(int size, void* buf){};

        /**
         * @brief N/D
        */
        void (*msg_write_buf)(SizeBuf* buf, int size, void* data){};

        /**
         * @brief N/D
        */
        void (*msg_write_byte)(SizeBuf* buf, int c){};

        /**
         * @brief N/D
        */
        void (*msg_write_short)(SizeBuf* buf, int c){};

        /**
         * @brief N/D
        */
        void (*msg_write_string)(SizeBuf* buf, const char* s){};

        /**
         * @brief N/D
        */
        void* (*get_plugin_api)(const char* name){};

        /**
         * @brief N/D
        */
        void (*register_plugin_api)(const char* name, void* impl){};

        /**
         * @brief N/D
        */
        qboolean (*sv_file_in_consistency_list)(const char* file_name, Consistency** consist){};

        /**
         * @brief N/D
        */
        qboolean (*steam_notify_client_connect)(IGameClient* client, const void* steam_auth_buf, unsigned int size){};

        /**
         * @brief N/D
        */
        void (*steam_notify_client_disconnect)(IGameClient* client){};

        /**
         * @brief N/D
        */
        void (*sv_start_sound)(int recipients, Edict* entity, int channel, const char* sample, int volume, float attenuation,
                               int flags, int pitch){};

        /**
         * @brief N/D
        */
        bool (*sv_emit_sound2)(Edict* entity, IGameClient* receiver, SoundChannel channel, const char* sample, float volume,
                               float attenuation, int flags, int pitch, int emit_flags, const float* origin){};

        /**
         * @brief N/D
        */
        void (*sv_update_user_info)(IGameClient* client){};

        /**
         * @brief N/D
        */
        bool (*strip_unprintable_and_space)(char* string){};

        /**
         * @brief N/D
        */
        void (*cmd_remove_cmd)(const char* cmd_name){};

        /**
         * @brief N/D
        */
        void (*get_command_matches)(const char* string, class object_list* match_list){};

        /**
         * @brief N/D
        */
        bool (*add_ext_dll)(void* module_handle){};

        /**
         * @brief N/D
        */
        void (*add_cvar_listener)(const char* cvar_name, CVarCallback func){};

        /**
         * @brief N/D
        */
        void (*remove_ext_dll)(void* module_handle){};

        /**
         * @brief N/D
        */
        void (*remove_cvar_listener)(const char* cvar_name, CVarCallback func){};

        /**
         * @brief N/D
        */
        EntityInitFunction (*get_entity_init)(char* class_name){};

        //
        // Read functions.
        //

        /**
         * @brief N/D
        */
        int (*msg_read_char)(){};

        /**
         * @brief N/D
        */
        int (*msg_read_byte)(){};

        /**
         * @brief N/D
        */
        int (*msg_read_long)(){};

        /**
         * @brief N/D
        */
        float (*msg_read_float)(){};

        /**
         * @brief N/D
        */
        char* (*msg_read_string)(){};

        /**
         * @brief N/D
        */
        char* (*msg_read_string_line)(){};

        /**
         * @brief N/D
        */
        float (*msg_read_angle)(){};

        /**
         * @brief N/D
        */
        float (*msg_read_hires_angle)(){};

        /**
         * @brief N/D
        */
        void (*msg_read_user_cmd)(UserCmd* to, UserCmd* from){};

        /**
         * @brief N/D
        */
        float (*msg_read_coord)(){};

        /**
         * @brief N/D
        */
        void (*msg_read_vec3_coord)(SizeBuf* sb, Vector& vec){};

        //
        // Read bit functions.
        //

        /**
         * @brief N/D
        */
        bool (*msg_is_bit_reading)(){};

        /**
         * @brief N/D
        */
        void (*msg_start_bit_reading)(SizeBuf* buf){};

        /**
         * @brief N/D
        */
        void (*msg_end_bit_reading)(SizeBuf* buf){};

        /**
         * @brief N/D
        */
        uint32 (*msg_peek_bits)(int num_bits){};

        /**
         * @brief N/D
        */
        int (*msg_read_one_bit)(){};

        /**
         * @brief N/D
        */
        uint32 (*msg_read_bits)(int num_bits){};

        /**
         * @brief N/D
        */
        int (*msg_read_s_bits)(int num_bits){};

        /**
         * @brief N/D
        */
        float (*msg_read_bit_coord)(){};

        /**
         * @brief N/D
        */
        void (*msg_read_bit_vec3_coord)(Vector& vec){};

        /**
         * @brief N/D
        */
        float (*msg_read_bit_angle)(int num_bits){};

        /**
         * @brief N/D
        */
        int (*msg_read_bit_data)(void* dest, int length){};

        /**
         * @brief N/D
        */
        char* (*msg_read_bit_string)(){};

        /**
         * @brief N/D
        */
        int (*msg_current_bit)(){};

        //
        // Write functions.
        //

        /**
         * @brief N/D
        */
        void (*msg_write_long)(SizeBuf* sb, int c){};

        /**
         * @brief N/D
        */
        void (*msg_write_float)(SizeBuf* sb, float f){};

        /**
         * @brief N/D
        */
        void (*msg_write_angle)(SizeBuf* sb, float f){};

        /**
         * @brief N/D
        */
        void (*msg_write_hires_angle)(SizeBuf* sb, float f){};

        /**
         * @brief N/D
        */
        void (*msg_write_user_cmd)(SizeBuf* sb, UserCmd* to, UserCmd* from){};

        /**
         * @brief N/D
        */
        void (*msg_write_coord)(SizeBuf* sb, float f){};

        /**
         * @brief N/D
        */
        void (*msg_write_vec3_coord)(SizeBuf* sb, Vector& vec){};

        //
        // Write bit functions.
        //

        /**
         * @brief N/D
        */
        bool (*msg_is_bit_writing)(){};

        /**
         * @brief N/D
        */
        void (*msg_write_one_bit)(int value){};

        /**
         * @brief N/D
        */
        void (*msg_write_s_bits)(uint32 data, int num_bits){};

        /**
         * @brief N/D
        */
        void (*msg_write_bit_coord)(float f){};

        /**
         * @brief N/D
        */
        void (*msg_write_bit_angle)(float angle, int num_bits){};

        /**
         * @brief N/D
        */
        void (*msg_write_bit_data)(void* src, int length){};

        /**
         * @brief N/D
        */
        void (*msg_write_bit_string)(const char* string){};

        /**
         * @brief N/D
        */
        void (*sz_write)(SizeBuf* buf, const void* data, int length){};

        /**
         * @brief N/D
        */
        void (*sz_print)(SizeBuf* buf, const char* data){};

        /**
         * @brief N/D
        */
        void (*sz_clear)(SizeBuf* buf){};

        /**
         * @brief N/D
        */
        void (*msg_begin_reading)(){};

        /**
         * @brief N/D
        */
        double (*get_host_frame_time)(){};

        /**
         * @brief N/D
        */
        CmdFunction* (*get_first_cmd_function_handle)(){};
    };

    class IReHldsApi // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        virtual ~IReHldsApi() = default;

        /**
         * @brief N/D
        */
        virtual int GetMajorVersion() = 0;

        /**
         * @brief N/D
        */
        virtual int GetMinorVersion() = 0;

        /**
         * @brief N/D
        */
        virtual const ReHldsFuncs* GetFuncs() = 0;

        /**
         * @brief N/D
        */
        virtual IReHldsHookChains* GetHookChains() = 0;

        /**
         * @brief N/D
        */
        virtual IReHldsServerStatic* GetServerStatic() = 0;

        /**
         * @brief N/D
        */
        virtual IReHldsServerData* GetServerData() = 0;

        /**
         * @brief N/D
        */
        virtual IReHldsFlightRecorder* GetFlightRecorder() = 0;
    };
}
