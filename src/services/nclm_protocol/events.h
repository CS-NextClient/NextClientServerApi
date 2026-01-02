#pragma once
#include <string>
#include "module_types.h"

struct ClientAuthEvent
{
    ClientId client;
    std::string clientVersion;
    bool isVerified;
};
