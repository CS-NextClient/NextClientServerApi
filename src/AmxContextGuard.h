#pragma once
#include <amxx/api.h>

extern Amx* g_CurrentAmx;

class AmxContextGuard
{
    Amx* prev_;

public:
    explicit AmxContextGuard(Amx* amx);
    ~AmxContextGuard();
};
