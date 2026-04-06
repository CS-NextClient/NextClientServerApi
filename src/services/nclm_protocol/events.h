#pragma once
#include <string>
#include "module_types.h"

struct ClientAuthEvent
{
    ClientId client;
    std::string clientVersion;
    bool isVerified;
};

struct HwidReceivedEvent
{
    ClientId    client;
    std::string hwid;   // 64-char hex SHA-256
};
