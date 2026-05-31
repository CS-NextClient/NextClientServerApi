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

#include <metamod/engine_hooks.h>
#include <metamod/engine.h>
#include <cstring>

using namespace cssdk;

namespace metamod::engine::detail
{
    /**
     * @brief Exports the engine hooks.
    */
    qboolean ExportEngineHooks(EngineFunctions* hooks_table, int* interface_version)
    {
        if (hooks_table && *interface_version == ENGINE_INTERFACE_VERSION) {
            std::memcpy(hooks_table, engine_hooks, sizeof(EngineFunctions));

            delete engine_hooks;
            engine_hooks = hooks_table;

            return true;
        }

        if (!hooks_table) {
            AlertMessage(AlertType::Logged, "Export engine hooks: hooks_table is null.\n");
        }
        else if (*interface_version != ENGINE_INTERFACE_VERSION) {
            AlertMessage(AlertType::Logged, "Export engine hooks: interface version mismatch; requested = %d; ours = %d.\n",
                         *interface_version, ENGINE_INTERFACE_VERSION);

            // Tell metamod what version we had, so it can figure out who is out of date.
            *interface_version = ENGINE_INTERFACE_VERSION;
        }

        delete engine_hooks;
        engine_hooks = nullptr;

        return false;
    }

    /**
     * @brief Exports the engine post hooks.
    */
    qboolean ExportEnginePostHooks(EngineFunctions* hooks_table, int* interface_version)
    {
        if (hooks_table && *interface_version == ENGINE_INTERFACE_VERSION) {
            std::memcpy(hooks_table, engine_post_hooks, sizeof(EngineFunctions));

            delete engine_post_hooks;
            engine_post_hooks = hooks_table;

            return true;
        }

        if (!hooks_table) {
            AlertMessage(AlertType::Logged, "Export engine post hooks: hooks_table is null.\n");
        }
        else if (*interface_version != ENGINE_INTERFACE_VERSION) {
            AlertMessage(AlertType::Logged, "Export engine post hooks: interface version mismatch; requested = %d; ours = %d.\n",
                         *interface_version, ENGINE_INTERFACE_VERSION);

            // Tell metamod what version we had, so it can figure out who is out of date.
            *interface_version = ENGINE_INTERFACE_VERSION;
        }

        delete engine_post_hooks;
        engine_post_hooks = nullptr;

        return false;
    }
}
