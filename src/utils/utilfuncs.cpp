#include "utilfuncs.h"

#include <fstream>
#include <string>

#include <easylogging++.h>

#include <metamod/utils.h>
#include <metamod/engine.h>
#include <core/type_conversion.h>

using namespace metamod;
using namespace core;

namespace utils
{
    size_t FileSize(const std::string& path)
    {
        std::ifstream file(path, std::ifstream::binary);
        if (!file.is_open())
        {
            return 0;
        }

        file.seekg(0, std::ifstream::end);
        std::streampos pos = file.tellg();
        if (pos == std::streampos(-1))
        {
            return 0;
        }

        return static_cast<size_t>(pos);
    }

    bool CRC_File(const std::string& path, cssdk::crc32* crc)
    {
        std::ifstream file(path, std::ifstream::binary);
        if (!file.is_open())
        {
            return false;
        }

        engine::Crc32Init(crc);

        char buffer[1024];
        std::streamsize readed;

        while (file)
        {
            readed = file.rdbuf()->sgetn(buffer, sizeof(buffer));

            if (readed > 0)
            {
                engine::Crc32ProcessBuffer(crc, buffer, static_cast<int>(readed));
            }

            if (readed < static_cast<std::streamsize>(sizeof(buffer)))
            {
                break;
            }
        }

        *crc = engine::Crc32Final(*crc);

        return true;
    }
} // namespace utils
