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

#include <metamod/gamedll_hooks.h>
#include <metamod/engine.h>
#include <cstring>

using namespace cssdk;
using namespace metamod::engine;

namespace metamod::gamedll::detail
{
    /**
     * @brief Exports the GameDLL hooks.
    */
    qboolean ExportDllHooks(DllFunctions* hooks_table, int* interface_version)
    {
        if (hooks_table && *interface_version == INTERFACE_VERSION) {
            std::memcpy(hooks_table, dll_hooks, sizeof(DllFunctions));

            delete dll_hooks;
            dll_hooks = hooks_table;

            return true;
        }

        if (!hooks_table) {
            AlertMessage(AlertType::Logged, "Export gamedll hooks: hooks_table is null.\n");
        }
        else if (*interface_version != INTERFACE_VERSION) {
            AlertMessage(AlertType::Logged, "Export gamedll hooks: interface version mismatch; requested = %d; ours = %d.\n",
                         *interface_version, INTERFACE_VERSION);

            // Tell metamod what version we had, so it can figure out who is out of date.
            *interface_version = INTERFACE_VERSION;
        }

        delete dll_hooks;
        dll_hooks = nullptr;

        return false;
    }

    /**
     * @brief Exports the GameDLL post hooks.
    */
    qboolean ExportDllPostHooks(DllFunctions* hooks_table, int* interface_version)
    {
        if (hooks_table && *interface_version == INTERFACE_VERSION) {
            std::memcpy(hooks_table, dll_post_hooks, sizeof(DllFunctions));

            delete dll_post_hooks;
            dll_post_hooks = hooks_table;

            return true;
        }

        if (!hooks_table) {
            AlertMessage(AlertType::Logged, "Export gamedll post hooks: hooks_table is null.\n");
        }
        else if (*interface_version != INTERFACE_VERSION) {
            AlertMessage(AlertType::Logged, "Export gamedll post hooks: interface version mismatch; requested = %d; ours = %d.\n",
                         *interface_version, INTERFACE_VERSION);

            // Tell metamod what version we had, so it can figure out who is out of date.
            *interface_version = INTERFACE_VERSION;
        }

        delete dll_post_hooks;
        dll_post_hooks = nullptr;

        return false;
    }

    /**
     * @brief Exports the GameDLL new hooks.
    */
    qboolean ExportDllNewHooks(DllNewFunctions* hooks_table, int* interface_version)
    {
        if (hooks_table && *interface_version == DLL_NEW_FUNCTIONS_VERSION) {
            std::memcpy(hooks_table, dll_new_hooks, sizeof(DllNewFunctions));

            delete dll_new_hooks;
            dll_new_hooks = hooks_table;

            return true;
        }

        if (!hooks_table) {
            AlertMessage(AlertType::Logged, "Export gamedll new hooks: hooks_table is null.\n");
        }
        else if (*interface_version != DLL_NEW_FUNCTIONS_VERSION) {
            AlertMessage(AlertType::Logged, "Export gamedll new hooks: interface version mismatch; requested = %d; ours = %d.\n",
                         *interface_version, DLL_NEW_FUNCTIONS_VERSION);

            // Tell metamod what version we had, so it can figure out who is out of date.
            *interface_version = DLL_NEW_FUNCTIONS_VERSION;
        }

        delete dll_new_hooks;
        dll_new_hooks = nullptr;

        return false;
    }

    /**
     * @brief Exports the GameDLL new post hooks.
    */
    qboolean ExportDllNewPostHooks(DllNewFunctions* hooks_table, int* interface_version)
    {
        if (hooks_table && *interface_version == DLL_NEW_FUNCTIONS_VERSION) {
            std::memcpy(hooks_table, dll_new_post_hooks, sizeof(DllNewFunctions));

            delete dll_new_post_hooks;
            dll_new_post_hooks = hooks_table;

            return true;
        }

        if (!hooks_table) {
            AlertMessage(AlertType::Logged, "Export gamedll new post hooks: hooks_table is null.\n");
        }
        else if (*interface_version != DLL_NEW_FUNCTIONS_VERSION) {
            AlertMessage(AlertType::Logged, "Export gamedll new post hooks: interface version mismatch; requested = %d; ours = %d.\n",
                         *interface_version, DLL_NEW_FUNCTIONS_VERSION);

            // Tell metamod what version we had, so it can figure out who is out of date.
            *interface_version = DLL_NEW_FUNCTIONS_VERSION;
        }

        delete dll_new_post_hooks;
        dll_new_post_hooks = nullptr;

        return false;
    }
}
