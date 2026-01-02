#pragma once
#include <amxxmodule.h>
#include <eiface.h>
#include <extdll.h>
#include <model.h>
#include <pm_defs.h>
#include <rehlds_api.h>

void ClientConnectedHandler(IRehldsHook_ClientConnected* hookchain, IGameClient* apiClient);
void SV_DropClientHandler(IRehldsHook_SV_DropClient* hookchain, IGameClient* apiClient, bool crash, const char* buf);
void SV_SendServerinfoHandler(IRehldsHook_SV_SendServerinfo* hookchain, sizebuf_t* msg, IGameClient* apiClient);
