#pragma once
#include <string>

#include <cssdk/engine/eiface.h>

namespace utils
{
    size_t FileSize(const std::string& path);
    bool CRC_File(const std::string& path, cssdk::crc32* crc);
} // namespace utils
