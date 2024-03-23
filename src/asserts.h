#pragma once

#include <string>
#include "amxxmodule.h"
#include "utilfuncs.h"

void NApiAssert_SetError(const std::string& text);
bool NApiAssert_ReadAndClearError(std::string& text);

#define NAPI_ASSERT(predicate, message)       \
	if (!(predicate)) {                       \
		NApiAssert_SetError(message); \
		return;                               \
	}

#define NAPI_LOG_ASSERT(predicate, ...) \
    if (!(predicate)) {                 \
        MF_Log(__VA_ARGS__);            \
        return;                         \
    }

#define ASSERT_NO_NAPI_ERRORS()                                                         \
	std::string _errorString;                                                           \
	if (NApiAssert_ReadAndClearError(_errorString)) {                                   \
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: %s", __FUNCTION__, _errorString.c_str()); \
		return FALSE;                                                                   \
	}

#define ASSERT_ARG_IS_PLAYER(x)                                                                            \
	if (MF_IsPlayerBot(params[x])) {                                                                       \
		return FALSE;                                                                                      \
	}                                                                                                      \
	if (!MF_IsPlayerValid(params[x])) {                                                                    \
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: invalid player index %i [%s]", __FUNCTION__, params[x], #x); \
		return FALSE;                                                                                      \
	}                                                                                                      \
	if (utils::PlayerByIndex(params[x]) == NULL) {                                                         \
		MF_LogError(amx, AMX_ERR_NATIVE, "%s: disconnected player %i [%s]", __FUNCTION__, params[x], #x);  \
		return FALSE;                                                                                      \
	}
