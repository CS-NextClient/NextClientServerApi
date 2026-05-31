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

#if defined(HAS_AMXX_LIB) && defined(HAS_METAMOD_LIB) && defined(HAS_MHOOKS_LIB)
#include <amxx/api.h>
#include <core/amxx_access.h>
#include <core/strings/examination.h>
#include <cssdk/public/utils.h>
#include <mhooks/amxxapi/amxxapi.h>
#include <mhooks/metamod.h>

using namespace core;
using namespace cssdk;
using namespace mhooks;
using namespace amxx_access::detail;

namespace
{
    std::array<int, access_flags.size()> g_no_flags{};

    void FillAccessFlags()
    {
        for (std::array<int*, 0>::size_type i = 0; i < access_flags.size(); ++i) {
            g_no_flags[i] = 0;
            access_flags[i] = &g_no_flags[i];
        }

        if (g_global_vars && g_global_vars->max_clients > 0 && g_global_vars->max_clients <= MAX_CLIENTS) {
            for (auto i = 1; i <= g_global_vars->max_clients; ++i) {
                access_flags[i] = static_cast<int*>(PlayerPropAddress(i, amxx::PlayerProp::Flags));
                assert(access_flags[i] != nullptr);
            }
        }
    }

    bool IsBot(const Edict* const client, const char* const auth)
    {
        return client->vars.flags & FL_FAKE_CLIENT || str::IsNullOrEmpty(auth) || str::IEquals(auth, "BOT");
    }

    bool IsHltv(const Edict* const client, const char* const auth)
    {
        return client->vars.flags & FL_PROXY || (!str::IsNullOrEmpty(auth) && str::IEquals(auth, "HLTV"));
    }

    void OnServerActivatePost(const GameDllServerActivateMChain& chain, Edict* const edict_list,
                              const int edict_count, const int client_max)
    {
        FillAccessFlags();
        chain.CallNext(edict_list, edict_count, client_max);
    }

    qboolean OnClientConnect(const GameDllClientConnectMChain& chain, Edict* const client,
                             const char* const name, const char* const address, char* const reject_reason)
    {
        if (IsValidEntity(client)) {
            if (const auto index = type_conversion::IndexOfEntity(client); IsClient(index)) {
                g_no_flags[index] = 0;
                access_flags[index] = &g_no_flags[index];
            }
        }

        return chain.CallNext(client, name, address, reject_reason);
    }

    void OnClientAuthorized(const AmxxClientAuthorizedMChain& chain, const int index, const char* const auth)
    {
        if (const auto* const client = type_conversion::EdictByIndex(index);
            IsBot(client, auth) || IsHltv(client, auth)) {
            g_no_flags[index] = 0;
            access_flags[index] = &g_no_flags[index];
        }
        else {
            access_flags[index] = static_cast<int*>(PlayerPropAddress(index, amxx::PlayerProp::Flags));
        }

        chain.CallNext(index, auth);
    }
}

namespace core::amxx_access
{
    void Init()
    {
        if (access_flags[0] != nullptr) {
            return;
        }

        FillAccessFlags();
        type_conversion::Init();
        MHookAmxxClientAuthorized(DELEGATE_ARG<OnClientAuthorized>, HookChainPriority::Uninterruptable);
        MHookGameDllServerActivate(DELEGATE_ARG<OnServerActivatePost>, true, HookChainPriority::Uninterruptable);
        MHookGameDllClientConnect(DELEGATE_ARG<OnClientConnect>, false, HookChainPriority::Uninterruptable);
    }
}
#endif
