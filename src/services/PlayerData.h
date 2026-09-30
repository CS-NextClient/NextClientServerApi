#pragma once
#include <optional>
#include <string>

#include "NextClientVersion.h"
#include "nclm_protocol/nclm_proto.h"

struct PlayerData
{
    NextClientVersion client_version{};
    bool is_using_nextclient{};
    bool is_api_ready{};
    bool is_verified{};
    bool connection_logged{};
    std::string hwid{};
    std::optional<NCLM_PLATFORM> platform{};
};
