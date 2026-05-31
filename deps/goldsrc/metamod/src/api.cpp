/*
 *  Copyright (C) 2020 the_hunter
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <metamod/api.h>
#include <cssdk/engine/eiface.h>
#include <cssdk/public/os_defs.h>
#include <metamod/engine_hooks.h>
#include <metamod/gamedll_hooks.h>
#include <metamod/utils.h>
#include <cstring>
#include <type_traits>

using namespace cssdk;
using namespace metamod;
using namespace utils;
using namespace engine;
using namespace gamedll;
using namespace utils::detail;
using namespace engine::detail;
using namespace gamedll::detail;

namespace metamod::engine::detail
{
    qboolean ExportEngineHooks(EngineFunctions* hooks_table, int* interface_version);
    qboolean ExportEnginePostHooks(EngineFunctions* hooks_table, int* interface_version);
}

namespace metamod::gamedll::detail
{
    qboolean ExportDllHooks(DllFunctions* hooks_table, int* interface_version);
    qboolean ExportDllPostHooks(DllFunctions* hooks_table, int* interface_version);

    qboolean ExportDllNewHooks(DllNewFunctions* hooks_table, int* interface_version);
    qboolean ExportDllNewPostHooks(DllNewFunctions* hooks_table, int* interface_version);
}

namespace
{
    struct ExportHooksFuncs
    {
        std::add_pointer_t<qboolean(DllFunctions*, int)> not_used1{};
        std::add_pointer_t<qboolean(DllFunctions*, int)> not_used2{};

        std::add_pointer_t<qboolean(DllFunctions*, int*)> export_dll_hooks{};
        std::add_pointer_t<qboolean(DllFunctions*, int*)> export_dll_post_hooks{};

        std::add_pointer_t<qboolean(DllNewFunctions*, int*)> export_dllnew_hooks{};
        std::add_pointer_t<qboolean(DllNewFunctions*, int*)> export_dllnew_post_hooks{};

        std::add_pointer_t<qboolean(EngineFunctions*, int*)> export_engine_hooks{};
        std::add_pointer_t<qboolean(EngineFunctions*, int*)> export_engine_post_hooks{};
    };

    struct DllFuncsTables
    {
        DllFunctions* dll_funcs_table{};
        DllNewFunctions* dllnew_funcs_table{};
    };

    void FreeAllHookTables()
    {
        delete engine_hooks;
        engine_hooks = nullptr;

        delete engine_post_hooks;
        engine_post_hooks = nullptr;

        delete dll_hooks;
        dll_hooks = nullptr;

        delete dll_post_hooks;
        dll_post_hooks = nullptr;

        delete dll_new_hooks;
        dll_new_hooks = nullptr;

        delete dll_new_post_hooks;
        dll_new_post_hooks = nullptr;
    }
}

extern "C" void DLLEXPORT WINAPI GiveFnptrsToDll(const EngineFunctions* const engine_funcs, GlobalVars* const global_vars)
{
    g_global_vars = global_vars;
    std::memcpy(&g_engine_funcs, engine_funcs, sizeof g_engine_funcs);
}

// NOLINTNEXTLINE(readability-identifier-naming)
extern "C" void DLLEXPORT Meta_Init()
{
#ifdef META_INIT
    META_INIT();
#endif
}

// NOLINTNEXTLINE(readability-identifier-naming)
extern "C" Status DLLEXPORT Meta_Query(const char* const interface_version, PluginInfo** const plugin_info,
                                       const Funcs* const util_funcs)
{
    if (std::strcmp(interface_version, metamod::INTERFACE_VERSION) != 0) {
        FreeAllHookTables();
        return Status::Failed;
    }

    static PluginInfo info = {metamod::INTERFACE_VERSION,
                              PLUGIN_NAME,
                              PLUGIN_VERSION,
                              PLUGIN_DATE,
                              PLUGIN_AUTHOR,
                              PLUGIN_URL,
                              PLUGIN_LOG_TAG,
                              PLUGIN_LOADABLE,
                              PLUGIN_UNLOADABLE};

    *plugin_info = &info;
    funcs = util_funcs;
    plugin = *plugin_info;

#ifdef META_QUERY
    META_QUERY();
#endif

    return Status::Ok;
}

// NOLINTNEXTLINE(readability-identifier-naming)
extern "C" Status DLLEXPORT Meta_Attach(const PluginLoadTime /*load_time*/, ExportHooksFuncs* const export_hooks_funcs,
                                        Globals* const globals, const DllFuncsTables* const dll_funcs_tables)
{
    g_globals = globals;

    export_hooks_funcs->not_used1 = nullptr;
    export_hooks_funcs->not_used2 = nullptr;
    export_hooks_funcs->export_dll_hooks = ExportDllHooks;
    export_hooks_funcs->export_dll_post_hooks = ExportDllPostHooks;
    export_hooks_funcs->export_dllnew_hooks = ExportDllNewHooks;
    export_hooks_funcs->export_dllnew_post_hooks = ExportDllNewPostHooks;
    export_hooks_funcs->export_engine_hooks = ExportEngineHooks;
    export_hooks_funcs->export_engine_post_hooks = ExportEnginePostHooks;

    std::memcpy(&g_dll_funcs, dll_funcs_tables->dll_funcs_table, sizeof g_dll_funcs);
    std::memcpy(&g_dll_new_funcs, dll_funcs_tables->dllnew_funcs_table, sizeof g_dll_new_funcs);

#ifdef META_ATTACH
    if (META_ATTACH() != Status::Ok) {
        FreeAllHookTables();

        export_hooks_funcs->not_used1 = export_hooks_funcs->not_used2 = nullptr;
        export_hooks_funcs->export_dll_hooks = export_hooks_funcs->export_dll_post_hooks = nullptr;
        export_hooks_funcs->export_dllnew_hooks = export_hooks_funcs->export_dllnew_post_hooks = nullptr;
        export_hooks_funcs->export_engine_hooks = export_hooks_funcs->export_engine_post_hooks = nullptr;

        return Status::Failed;
    }
#endif

    return Status::Ok;
}

// NOLINTNEXTLINE(readability-identifier-naming)
extern "C" Status DLLEXPORT Meta_Detach(const PluginLoadTime /*now*/, const PluginUnloadReason /*reason*/)
{
#ifdef META_DETACH
    META_DETACH();
#endif

    ClearEngineHooks();
    ClearGameDllHooks();

    return Status::Ok;
}
