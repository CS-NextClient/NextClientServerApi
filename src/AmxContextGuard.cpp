#include "AmxContextGuard.h"

Amx* g_CurrentAmx = nullptr;

AmxContextGuard::AmxContextGuard(Amx* amx) :
    prev_(g_CurrentAmx)
{
    g_CurrentAmx = amx;
}

AmxContextGuard::~AmxContextGuard()
{
    g_CurrentAmx = prev_;
}
