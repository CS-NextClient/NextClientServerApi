#pragma once
#include <core/rehlds_api.h>

namespace server_test
{
    using namespace cssdk;
    class FakeIReHldsServerStatic : public IReHldsServerStatic
    {
    public:
        int max_clients = 1;
        int GetMaxClients() override
        {
            return max_clients;
        }
        bool IsLogActive() override
        {
            return {};
        }
        IGameClient* GetGameClient(int id) override
        {
            return {};
        }
        Client* GetClient(int id) override
        {
            return {};
        }
        int GetIndexOfClient(Client* client) override
        {
            return {};
        }
        int GetMaxClientsLimit() override
        {
            return {};
        }
        Client* GetNextClient(Client* client) override
        {
            return {};
        }
        int GetSpawnCount() override
        {
            return {};
        }
        void SetSpawnCount(int count) override {}
        ServerLog* GetLog() override
        {
            return {};
        }
        bool IsSecure() override
        {
            return {};
        }
        void SetSecure(bool value) override {}
    };
    class FakeIReHldsServerData : public IReHldsServerData
    {
    public:
        double time = 1.0;
        const char* GetModelName() override
        {
            return {};
        }
        const char* GetName() override
        {
            return {};
        }
        uint32 GetWorldMapCrc() override
        {
            return {};
        }
        uint8* GetClientDllMd5() override
        {
            return {};
        }
        SizeBuf* GetDatagram() override
        {
            return {};
        }
        SizeBuf* GetReliableDatagram() override
        {
            return {};
        }
        void SetModelName(const char* model_name) override {}
        void SetConsistencyNum(int num) override {}
        int GetConsistencyNum() override
        {
            return {};
        }
        int GetResourcesNum() override
        {
            return {};
        }
        int GetDecalNameNum() override
        {
            return {};
        }
        double GetTime() override
        {
            return time;
        }
        void SetResourcesNum(int num) override {}
        Resource* GetResource(int index) override
        {
            return {};
        }
        void SetName(const char* name) override {}
        class ISteamGameServer* GetSteamGameServer() override
        {
            return {};
        }
        NetAddress* GetNetFrom() override
        {
            return {};
        }
        double GetOldTime() override
        {
            return {};
        }
        void SetNetFrom(NetAddress* from) override {}
        void SetWorldMapCrc(uint32 value) override {}
        void SetDecalNameNum(int num) override {}
        bool IsActive() override
        {
            return {};
        }
        void SetActive(bool state) override {}
        bool IsPaused() override
        {
            return {};
        }
        void SetPaused(bool state) override {}
        int GetLastIndexCheckInPvs() override
        {
            return {};
        }
        void SetLastIndexCheckInPvs(int id) override {}
        double GetLastIndexCheckTimeInPvs() override
        {
            return {};
        }
        void SetLastIndexCheckTimeInPvs(double time) override {}
        const char* GetOldName() override
        {
            return {};
        }
        void SetOldName(const char* name) override {}
        const char* GetStartSpotName() override
        {
            return {};
        }
        void SetStartSpotName(const char* start_spot) override {}
        Model* GetWorldModel() override
        {
            return {};
        }
        void SetWorldModel(Model* model) override {}
        Consistency* GetConsistency(int index) override
        {
            return {};
        }
        Model* GetModel(int index) override
        {
            return {};
        }
        Event* GetEventPrecache(int index) override
        {
            return {};
        }
        EntityState* GetEntityBaseline(int index) override
        {
            return {};
        }
        ExtraBaselines* GetEntityInstanceBaselines() override
        {
            return {};
        }
        int GetNumGenericNames() override
        {
            return {};
        }
        void SetNumGenericNames(int num) override {}
        int GetNumEdicts() override
        {
            return {};
        }
        void SetNumEdicts(int num_edicts) override {}
        int GetMaxEdicts() override
        {
            return {};
        }
        void SetMaxEdicts(int max_edicts) override {}
        Edict* GetEdict(int index) override
        {
            return {};
        }
        ServerState GetState() override
        {
            return {};
        }
        void SetState(ServerState value) override {}
        SizeBuf* GetMulticastBuf() override
        {
            return {};
        }
        SizeBuf* GetSpectatorBuf() override
        {
            return {};
        }
        SizeBuf* GetSignOnBuf() override
        {
            return {};
        }
    };
} // namespace server_test
