#pragma once
#include "NextClientVersion.h"

struct PlayerData
{
    NextClientVersionLegacy deprecated_client_version{};
    NextClientVersion client_version;
    bool is_using_nextclient{};
    bool is_api_ready{};
    bool is_verified{};
};
