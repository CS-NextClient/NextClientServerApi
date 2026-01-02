#include "utilfuncs.h"
#include <fstream>
#include <string>
#include <easylogging++.h>
#include "amxxmodule.h"

namespace utils
{
    CBasePlayer* PlayerByIndex(int playerIndex)
    {
        return (CBasePlayer*) GET_PRIVATE(INDEXENT(playerIndex));
    }

    int RegUserMsgSafe(const char* pszName, int iSize)
    {
        int messageid = GET_USER_MSG_ID(&Plugin_info, pszName, NULL);

        if (messageid == 0)
            messageid = REG_USER_MSG(pszName, iSize);

        if (messageid == 0)
            LOG(ERROR) << "Unable to register message " << pszName;

        return messageid;
    }

    size_t FileSize(const std::string& path)
    {
        std::ifstream file(path, std::ifstream::binary);
        if (!file.is_open())
            return 0;

        file.seekg(0, std::ifstream::end);
        std::streampos pos = file.tellg();
        if (pos == std::streampos(-1))
            return 0;

        return pos;
    }

    bool CRC_File(const std::string& path, CRC32_t* crc)
    {
        std::ifstream file(path, std::ifstream::binary);
        if (!file.is_open())
            return false;

        CRC32_INIT(crc);

        char buffer[1024];
        std::streamsize readed;

        while (file)
        {
            readed = file.rdbuf()->sgetn(buffer, sizeof(buffer));

            if (readed > 0)
                CRC32_PROCESS_BUFFER(crc, buffer, readed);

            if (readed < (std::streamsize)sizeof(buffer))
                break;
        }

        *crc = CRC32_FINAL(*crc);

        return true;
    }
}
