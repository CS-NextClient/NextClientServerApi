#pragma once
#include <mhooks/reapi.h>

struct AddPlayerItemEvent
{
    bool added;
    cssdk::PlayerBase* player;
    cssdk::PlayerItemBase* item;
};

struct RemovePlayerItemEvent
{
    bool removed;
    cssdk::PlayerBase* player;
    cssdk::PlayerItemBase* item;
};
