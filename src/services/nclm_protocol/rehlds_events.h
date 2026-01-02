#pragma once
#include <amxxmodule.h>
#include <eiface.h>
#include <extdll.h>
#include <model.h>
#include <pm_defs.h>
#include <rehlds_api.h>

void HandleNetCommand(IRehldsHook_HandleNetCommand* hookchain, IGameClient* apiClient, int8 opcode);
