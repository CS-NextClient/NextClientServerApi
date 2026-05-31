#pragma once
#include <cssdk/common/const.h>
#include <cssdk/common/entity_state.h>
#include "module_types.h"

struct ClientConnectingEvent
{
    ClientId client_id;
    const char* name;
    const char* address;
};

struct ServerActivatedEvent
{
    cssdk::Edict* edict_list;
    int edict_count;
    int client_max;
};

struct MessageBeginPostEvent
{
    cssdk::MessageType msg_dest;
    int msg_id;
    const float* origin;
    cssdk::Edict* edict;
};

struct ClientDropConnectionEvent
{
    ClientId client_id;
    bool crash;
    const char* reason;
};

struct AddToFullPackEvent
{
    cssdk::EntityState* state;
    int e;
    cssdk::Edict* ent;
    cssdk::Edict* host;
    int hostflags;
    int player;
    unsigned char* set;
    int original_result;
};
