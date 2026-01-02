#pragma once
#include <amxxmodule.h>
#include <eiface.h>
#include <extdll.h>
#include <model.h>
#include <pm_defs.h>
#include "module_types.h"

struct ClientConnectingEvent
{
    ClientId client;
    const char* pszName;
    const char* pszAddress;
};

struct ServerActivatedEvent
{
    edict_t* pEdictList;
    int edictCount;
    int clientMax;
};

struct MessageBeginPostEvent
{
    int msg_dest;
    int msg_type;
    const float* pOrigin;
    edict_t* ed;
};

struct ClientDropConnectionEvent
{
    ClientId client;
    bool crash;
    const char* reason;
};
