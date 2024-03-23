#pragma once

namespace ncl_deprecated {

enum class NextClientVersion {
	NOT_NEXTCLIENT,
	V_2_1_7_OR_LOWER,
	V_2_1_8,
	V_2_1_9,
	V_2_1_10,
	V_2_1_11,
	V_2_1_12,
	V_2_2_0,
	V_2_3_0_OR_HIGHER
};

class INextClientAPI {
public:
	virtual NextClientVersion deprecated_GetNextClientVersion(int client) = 0;
};

}