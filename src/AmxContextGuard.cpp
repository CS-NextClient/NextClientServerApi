#include "AmxContextGuard.h"

AMX* g_CurrentAmx = nullptr;

AmxContextGuard::AmxContextGuard(AMX* amx) :
    prev_(g_CurrentAmx)
{
    g_CurrentAmx = amx;
}

AmxContextGuard::~AmxContextGuard()
{
    g_CurrentAmx = prev_;
}
