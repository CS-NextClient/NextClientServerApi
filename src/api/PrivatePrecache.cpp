#include "PrivatePrecache.h"
#include <fstream>
#include <cstdio>
#include "utilfuncs.h"
#include "main.h"

PrivatePrecache::PrivatePrecache()
{
    filepath_resource_list_relative_ = std::string(MF_GetLocalInfo("amxx_datadir", "addons/amxmodx/data")) + "/ncl_private_precache.txt";
    payload_resource_list_location_ = std::string("\x02ncl\x07") + filepath_resource_list_relative_;
    filepath_resource_list_absolute_ = MF_BuildPathname(filepath_resource_list_relative_.c_str());

    DeleteResourceListFromDisk();
}

int PrivatePrecache::PrecacheModel(const std::string& filepath, const std::string& nclFilepath)
{
    bool result = AppendResource(filepath, nclFilepath, true);
    if (!result)
        return 0;

    return PRECACHE_MODEL(filepath.c_str());
}

int PrivatePrecache::PrecacheSound(const std::string& filepath, const std::string& nclFilepath)
{
    bool result = AppendResource("sound/" + filepath, "sound/" + nclFilepath, true);
    if (!result)
        return 0;

    return PRECACHE_SOUND(filepath.c_str());
}

bool PrivatePrecache::PrecacheClientOnly(const std::string& filepath, const std::string& nclFilepath)
{
    return AppendResource(filepath, nclFilepath, false);
}

void PrivatePrecache::OnClientConnect(int client)
{
    if (!is_resource_list_written_)
    {
        is_resource_list_written_ = WriteResourceListToDisk();

        if (!is_resource_list_written_)
            return;
    }

    NextClientVersion version;
    NAPI()->GetNextClientVersion(client, version);

    if (version < NextClientVersion{2, 1, 8})
        return;

    MESSAGE_BEGIN(MSG_ONE, SVC_STUFFTEXT, NULL, INDEXENT(client));
    WRITE_STRING(payload_resource_list_location_.c_str());
    MESSAGE_END();
}

bool PrivatePrecache::AppendResource(const std::string& filepath, const std::string& nclFilepath, bool replace)
{
    if (map_resource_list_.count(filepath) != 0)
        return true;

    std::string filepath_absolute = MF_BuildPathname(nclFilepath.c_str());
    size_t filesize = utils::FileSize(filepath_absolute);
    if (filesize == 0)
        return false;

    CRC32_t checksum = 0;
    utils::CRC_File(filepath_absolute, &checksum);
    if (checksum == 0)
        return false;

    char buffer[256];
    sprintf(buffer, "%d:%s:%s:%x:%d", replace, filepath.c_str(), nclFilepath.c_str(), checksum, filesize);

    map_resource_list_[filepath] = buffer;

    return true;
}

bool PrivatePrecache::WriteResourceListToDisk()
{
    if (map_resource_list_.empty())
        return false;

    std::ofstream file(filepath_resource_list_absolute_);
    if (!file.is_open())
        return false;

    for (const auto& entry: map_resource_list_)
    {
        file << entry.second << std::endl;
    }

    return true;
}

void PrivatePrecache::DeleteResourceListFromDisk()
{
    std::remove(filepath_resource_list_absolute_.c_str());
    std::remove((filepath_resource_list_absolute_ + ".ztmp").c_str());
}