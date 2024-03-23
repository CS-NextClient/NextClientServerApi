#include "utilfuncs.h"
#include "amxxmodule.h"
#include <fstream>
#include <string>
#include <vector>

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
            MF_Log("Unable to register %s message", pszName);

        return messageid;
    }

    using std::ifstream;

    size_t FileSize(const std::string& path)
    {
        ifstream file(path, ifstream::binary);
        file.seekg(0, ifstream::end);
        size_t size = file.tellg();
        if (size == -1)
            return 0;

        return size;
    }

    bool CRC_File(const std::string& path, CRC32_t* crc)
    {
        ifstream file(path, ifstream::binary);

        CRC32_INIT(crc);

        char buffer[1024];
        long long readed;

        while (file.good())
        {
            readed = file.rdbuf()->sgetn(buffer, 1024);
            if (readed != 1024)
                file.setstate(ifstream::eofbit | ifstream::failbit);
            else
                file.setstate(ifstream::goodbit);

            CRC32_PROCESS_BUFFER(crc, buffer, readed);
        }

        *crc = CRC32_FINAL(*crc);

        return !file.fail();
    }
}
