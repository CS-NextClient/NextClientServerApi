#include "PrivatePrecache.h"

#include <easylogging++.h>

#include <amxx/api.h>
#include <metamod/engine.h>
#include <core/type_conversion.h>
#include <core/strings/caseconv.h>

#include "utils/msg_ex.h"
#include "utils/utilfuncs.h"

#undef close

using namespace metamod;
using namespace msg_ex;

constexpr int kSvcStuffText = 9;

PrivatePrecache::PrivatePrecache(
    ServerEventsManager& server_events_manager,
    NclmProtocol& nclm_protocol,
    INextClientInfo& next_client_info
) :
    next_client_info_(next_client_info)
{
    filepath_resource_list_relative_ = std::string(amxx::GetLocalInfo("amxx_datadir", "addons/amxmodx/data")) + "/ncl_private_precache.txt";

    payload_resource_list_location_ = std::string("\x02ncl\x07") + filepath_resource_list_relative_;
    filepath_resource_list_absolute_ = amxx::BuildPathName(filepath_resource_list_relative_.c_str());

    DeleteResourceListFromDisk();

    server_events_manager.on_client_connecting().connect(&PrivatePrecache::ClientConnectingHandler, this);
    server_events_manager.on_amxx_plugins_loaded().connect(&PrivatePrecache::AmxxPluginsLoadedHandler, this);
    nclm_protocol.on_client_auth().connect(&PrivatePrecache::ClientAuthHandler, this);
}

int PrivatePrecache::PrecacheModel(const std::string& filepath, const std::string& nclFilepath)
{
    bool result = AppendResource(filepath, nclFilepath, true);
    if (!result)
    {
        return 0;
    }

    return engine::PrecacheModel(filepath.c_str());
}

int PrivatePrecache::PrecacheSound(const std::string& filepath, const std::string& nclFilepath)
{
    bool result = AppendResource("sound/" + filepath, "sound/" + nclFilepath, true);
    if (!result)
    {
        return 0;
    }

    return engine::PrecacheSound(filepath.c_str());
}

bool PrivatePrecache::UploadFile(const std::string& filepath, const std::string& nclFilepath)
{
    return AppendResource(filepath, nclFilepath, false);
}

void PrivatePrecache::ClientAuthHandler(ClientAuthEvent event)
{
    TrySendPrivateResourceListLocation(event.client_id);
}

void PrivatePrecache::ClientConnectingHandler(ClientConnectingEvent event)
{
    TrySendPrivateResourceListLocation(event.client_id);
}

void PrivatePrecache::AmxxPluginsLoadedHandler()
{
    ClearPrivatePrecache();
}

void PrivatePrecache::TrySendPrivateResourceListLocation(ClientId client_id)
{
    if (!is_resource_list_written_)
    {
        is_resource_list_written_ = WriteResourceListToDisk();

        if (!is_resource_list_written_)
        {
            return;
        }
    }

    NextClientVersion version;
    if (!next_client_info_.GetNextClientVersion(client_id, version) || version < NextClientVersion{2, 4, 0})
    {
        return;
    }

    MessageBegin(cssdk::MessageType::One, kSvcStuffText, nullptr, core::type_conversion::EdictByIndex(client_id));
    WriteString(payload_resource_list_location_.c_str());
    MessageEnd();
}

bool PrivatePrecache::AppendResource(const std::string& filepath, const std::string& nclFilepath, bool replace)
{
    if (map_resource_list_.count(filepath) != 0)
    {
        return true;
    }

    std::string filepath_absolute = amxx::BuildPathName(nclFilepath.c_str());

    size_t filesize = utils::FileSize(filepath_absolute);
    if (filesize == 0)
    {
        LOG(ERROR) << "File not found or empty: '" << nclFilepath << "'";
        return false;
    }

    cssdk::crc32 checksum = 0;
    if (!utils::CRC_File(filepath_absolute, &checksum) || checksum == 0)
    {
        LOG(ERROR) << "Failed to calculate CRC for file: '" << nclFilepath << "'";
        return false;
    }

    char buffer[768];
    int result = snprintf(buffer, sizeof(buffer), "%d:%s:%s:%x:%zu", replace, filepath.c_str(), nclFilepath.c_str(), checksum, filesize);

    if (result < 0 || result >= (int)sizeof(buffer))
    {
        LOG(ERROR) << "Failed to format resource entry for '" << filepath << "'";
        return false;
    }

    map_resource_list_[filepath] = buffer;
    std::remove((filepath_absolute + ".ztmp").c_str());

    return true;
}

void PrivatePrecache::ClearPrivatePrecache()
{
    is_resource_list_written_ = false;
    map_resource_list_.clear();
    DeleteResourceListFromDisk();
}

bool PrivatePrecache::WriteResourceListToDisk()
{
    if (map_resource_list_.empty())
        return false;

    std::ofstream file(filepath_resource_list_absolute_);
    if (!file.is_open())
        return false;

    for (const auto& entry : map_resource_list_)
    {
        file << entry.second << std::endl;
    }

    if (!file.good())
    {
        LOG(ERROR) << "failed to write resource list to disk";
        file.close();
        return false;
    }

    file.close();
    return true;
}

void PrivatePrecache::DeleteResourceListFromDisk()
{
    std::remove(filepath_resource_list_absolute_.c_str());
    std::remove((filepath_resource_list_absolute_ + ".ztmp").c_str());
}
