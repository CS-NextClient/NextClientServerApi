#pragma once
#include "amxxmodule.h"

extern AMX* g_CurrentAmx;

class AmxContextGuard
{
    AMX* prev_;

public:
    explicit AmxContextGuard(AMX* amx);
    ~AmxContextGuard();
};
