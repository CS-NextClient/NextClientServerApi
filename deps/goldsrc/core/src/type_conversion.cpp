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

#if defined(HAS_METAMOD_LIB) && defined(HAS_MHOOKS_LIB)
#include <core/type_conversion.h>
#include <mhooks/metamod.h>

using namespace cssdk;
using namespace mhooks;
using namespace metamod;
using namespace core::type_conversion::detail;

namespace
{
    MHook* g_dispatch_spawn_post_hook{};

    int OnDispatchSpawnPost(const GameDllDispatchSpawnMChain& chain, Edict* const entity)
    {
        if (const auto orig_ret = GetRetValue<int>(); orig_ret == 0 && IsValidEntity(entity)) {
            g_dispatch_spawn_post_hook->Disable();
            first_edict = g_engine_funcs.entity_of_ent_index(0);
        }

        return chain.CallNext(entity);
    }

    void OnServerDeactivatePost(const GameDllServerDeactivateMChain& chain)
    {
        if (g_dispatch_spawn_post_hook) {
            g_dispatch_spawn_post_hook->Enable();
        }

        chain.CallNext();
    }
}

namespace core::type_conversion
{
    void Init()
    {
        if (g_dispatch_spawn_post_hook) {
            return;
        }

        if (g_engine_funcs.entity_of_ent_index) {
            first_edict = g_engine_funcs.entity_of_ent_index(0);
        }

        MHookGameDllServerDeactivate(
            DELEGATE_ARG<OnServerDeactivatePost>, true, HookChainPriority::Uninterruptable);

        g_dispatch_spawn_post_hook =
            MHookGameDllDispatchSpawn(DELEGATE_ARG<OnDispatchSpawnPost>, true, HookChainPriority::Uninterruptable);
    }
}
#endif
