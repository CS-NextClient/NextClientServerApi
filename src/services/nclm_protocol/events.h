#pragma once
#include <string>
#include "module_types.h"

struct ClientAuthEvent
{
    ClientId client_id;
    std::string client_version;
    bool is_verified;
};

struct HwidReceivedEvent
{
    ClientId client_id;
    std::string hwid;
    bool valid;
};
