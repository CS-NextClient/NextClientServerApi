#pragma once

#include <string>

class IDeathMsgWpnIcon
{
public:
    virtual ~IDeathMsgWpnIcon() = default;

    virtual void SetIconForNextMessage(const std::string& sprite, int frame, int rendermode, 
        int r, int g, int b, int a, int recipient_id) = 0;
};