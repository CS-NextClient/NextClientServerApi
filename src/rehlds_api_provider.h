#pragma once

#include "amxxmodule.h"
#include <eiface.h>
#include <extdll.h>
#include <model.h>
#include <pm_defs.h>
#include <rehlds_api.h>

extern IRehldsApi* g_RehldsApi;
extern const RehldsFuncs_t* g_RehldsFuncs;
extern IRehldsServerData* g_RehldsData;
extern IRehldsHookchains* g_RehldsHookchains;
extern IRehldsServerStatic* g_RehldsSvs;

extern bool RehldsApi_Init();

#define MSG_ReadChar 			g_RehldsFuncs->MSG_ReadChar
#define MSG_ReadByte 			g_RehldsFuncs->MSG_ReadByte
#define MSG_ReadLong 			g_RehldsFuncs->MSG_ReadLong
#define MSG_ReadFloat 			g_RehldsFuncs->MSG_ReadFloat
#define MSG_ReadString 			g_RehldsFuncs->MSG_ReadString
#define MSG_ReadStringLine 		g_RehldsFuncs->MSG_ReadStringLine
#define MSG_ReadAngle 			g_RehldsFuncs->MSG_ReadAngle
#define MSG_ReadHiresAngle 		g_RehldsFuncs->MSG_ReadHiresAngle
#define MSG_ReadUsercmd 		g_RehldsFuncs->MSG_ReadUsercmd
#define MSG_ReadCoord 			g_RehldsFuncs->MSG_ReadCoord
#define MSG_ReadVec3Coord 		g_RehldsFuncs->MSG_ReadVec3Coord
#define MSG_IsBitReading 		g_RehldsFuncs->MSG_IsBitReading
#define MSG_StartBitReading 	g_RehldsFuncs->MSG_StartBitReading
#define MSG_EndBitReading 		g_RehldsFuncs->MSG_EndBitReading
#define MSG_PeekBits			g_RehldsFuncs->MSG_PeekBits
#define MSG_ReadOneBit 			g_RehldsFuncs->MSG_ReadOneBit
#define MSG_ReadBits 			g_RehldsFuncs->MSG_ReadBits
#define MSG_ReadSBits 			g_RehldsFuncs->MSG_ReadSBits
#define MSG_ReadBitCoord 		g_RehldsFuncs->MSG_ReadBitCoord
#define MSG_ReadBitVec3Coord 	g_RehldsFuncs->MSG_ReadBitVec3Coord
#define MSG_ReadBitAngle 		g_RehldsFuncs->MSG_ReadBitAngle
#define MSG_ReadBitData 		g_RehldsFuncs->MSG_ReadBitData
#define MSG_ReadBitString 		g_RehldsFuncs->MSG_ReadBitString
#define MSG_CurrentBit 			g_RehldsFuncs->MSG_CurrentBit
#define MSG_ReadShort			g_RehldsFuncs->MSG_ReadShort
#define MSG_ReadBuf				g_RehldsFuncs->MSG_ReadBuf

#define MSG_IsBadRead			*g_RehldsFuncs->GetMsgBadRead