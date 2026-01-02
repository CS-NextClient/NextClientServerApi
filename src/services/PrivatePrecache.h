#pragma once
#include <string>
#include <unordered_map>

#include <kangaru/kangaru.hpp>
#include <sigslot/signal.hpp>

#include "INextClientInfo.h"
#include "game_events/GameEventsManager.h"
#include "nclm_protocol/NclmProtocol.h"

class PrivatePrecache : public sigslot::observer
{
	INextClientInfo& next_client_info_;

	std::string filepath_resource_list_absolute_;
	std::string filepath_resource_list_relative_;
	std::string payload_resource_list_location_;
	std::unordered_map<std::string, std::string> map_resource_list_;
	bool is_resource_list_written_{};

public:
	explicit PrivatePrecache(
		GameEventsManager& game_events_manager,
		NclmProtocol& nclm_protocol,
		INextClientInfo& next_client_info
	);

	int PrecacheModel(const std::string& filepath, const std::string& nclFilepath);
	int PrecacheSound(const std::string& filepath, const std::string& nclFilepath);
	bool UploadFile(const std::string& filepath, const std::string& nclFilepath);

private:
	void ClientConnectingHandler(ClientConnectingEvent event);
	void AmxxPluginsLoadedHandler();

	void TrySendPrivateResourceListLocation(int client);
    bool WriteResourceListToDisk();
    void DeleteResourceListFromDisk();
    bool AppendResource(const std::string& filepath, const std::string& nclFilepath, bool replace);
	void ClearPrivatePrecache();

	void ClientAuthHandler(ClientAuthEvent event);
};

struct PrivatePrecacheService : kgr::single_service<PrivatePrecache, kgr::dependency<GameEventsManagerService, NclmProtocolService, INextClientInfoService>> {};
