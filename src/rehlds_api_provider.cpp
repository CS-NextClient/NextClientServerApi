#include "rehlds_api_provider.h"

IRehldsApi* g_RehldsApi;
const RehldsFuncs_t* g_RehldsFuncs;
IRehldsServerData* g_RehldsData;
IRehldsHookchains* g_RehldsHookchains;
IRehldsServerStatic* g_RehldsSvs;

bool RehldsApi_Init()
{
    if (!IS_DEDICATED_SERVER())
        return false;


#ifdef WIN32
	CSysModule* engineModule = Sys_LoadModule("swds.dll");
#else
	CSysModule* engineModule = Sys_LoadModule("engine_i486.so");
#endif

	if (!engineModule)
		return false;

	CreateInterfaceFn ifaceFactory = Sys_GetFactory(engineModule);
	if (!ifaceFactory)
		return false;

	int retCode = 0;
	g_RehldsApi = (IRehldsApi*)ifaceFactory(VREHLDS_HLDS_API_VERSION, &retCode);

	if (!g_RehldsApi)
    {
        MF_PrintSrvConsole("[%s]: ReHLDS API not found\n", Plugin_info.logtag);
        return false;
    }

	int majorVersion = g_RehldsApi->GetMajorVersion();
	int minorVersion = g_RehldsApi->GetMinorVersion();

	if (majorVersion != REHLDS_API_VERSION_MAJOR)
	{
		MF_PrintSrvConsole("[%s]: ReHLDS API major version mismatch; expected %d, real %d\n", Plugin_info.logtag, REHLDS_API_VERSION_MAJOR, majorVersion);

		// need to notify that it is necessary to update the ReHLDS.
		if (majorVersion < REHLDS_API_VERSION_MAJOR)
		{
			MF_PrintSrvConsole("[%s]: Please update the ReHLDS up to a major version API >= %d\n", Plugin_info.logtag, REHLDS_API_VERSION_MAJOR);
		}

		// need to notify that it is necessary to update the module.
		else if (majorVersion > REHLDS_API_VERSION_MAJOR)
		{
			MF_PrintSrvConsole("[%s]: Please update the %s up to a major version API >= %d\n", Plugin_info.logtag, Plugin_info.logtag, majorVersion);
		}

		return false;
	}

	if (minorVersion < REHLDS_API_VERSION_MINOR)
	{
		MF_PrintSrvConsole("[%s]: ReHLDS API minor version mismatch; expected at least %d, real %d\n", Plugin_info.logtag, REHLDS_API_VERSION_MINOR, minorVersion);
		MF_PrintSrvConsole("[%s]: Please update the ReHLDS up to a minor version API >= %d\n", Plugin_info.logtag, REHLDS_API_VERSION_MINOR);
		return false;
	}

	g_RehldsFuncs = g_RehldsApi->GetFuncs();
	g_RehldsData = g_RehldsApi->GetServerData();
	g_RehldsHookchains = g_RehldsApi->GetHookchains();
	g_RehldsSvs = g_RehldsApi->GetServerStatic();

	return true;
}