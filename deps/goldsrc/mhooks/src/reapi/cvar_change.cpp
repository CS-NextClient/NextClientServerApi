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

#if defined(HAS_CSSDK_LIB) && defined(HAS_CORE_LIB)
#include <mhooks/reapi/cvar_change.h>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;
using namespace core;
using namespace cssdk;
using namespace mhooks;

namespace
{
    struct Data
    {
        MHook* hook{};
        const CVar* cvar{};
        CVarChangeMCallback callback{};
    };

    MHook* g_cvar_direct_set_hook{};
    vector<Data>* g_cvar_change_hooks{};

    [[nodiscard]] bool IsCvarChangeHooked(const CVar* const cvar)
    {
        assert(cvar != nullptr);
        assert(g_cvar_change_hooks != nullptr);

        const auto predicate = [cvar](const auto& element) {
            return element.cvar == cvar && element.hook->IsEnabled();
        };

        return any_of(g_cvar_change_hooks->cbegin(), g_cvar_change_hooks->cend(), predicate);
    }

    void OnCvarDirectSet(const ReHldsCvarDirectSetMChain& chain, CVar* const cvar, const char* const value)
    {
        if (!IsCvarChangeHooked(cvar) || !cvar->string || !value) {
            chain.CallNext(cvar, value);
            return;
        }

        const string_view old_value{cvar->string};
        string new_value{value};

        // NOLINTNEXTLINE(modernize-loop-convert)
        for (vector<Data>::size_type i = 0; i < g_cvar_change_hooks->size(); ++i) {
            if (const auto& data = g_cvar_change_hooks->at(i); data.cvar == cvar && data.hook->IsEnabled()) {
                data.callback(cvar, old_value, new_value);
            }
        }

        chain.CallNext(cvar, new_value.c_str());
    }

    ATTR_MINSIZE void RemoveHook(const MHook* const hook)
    {
        assert(hook != nullptr);
        assert(g_cvar_change_hooks != nullptr);

        const auto predicate = [hook](const auto& element) {
            return element.hook == hook;
        };

        g_cvar_change_hooks->erase(remove_if(g_cvar_change_hooks->begin(), g_cvar_change_hooks->end(), predicate),
                                   g_cvar_change_hooks->end());
    }

    ATTR_MINSIZE [[nodiscard]] bool IsAllHooksDisabled()
    {
        assert(g_cvar_change_hooks != nullptr);

        constexpr auto predicate = [](const auto& element) {
            return element.hook->IsEnabled();
        };

        return all_of(g_cvar_change_hooks->cbegin(), g_cvar_change_hooks->cend(), predicate);
    }

    ATTR_MINSIZE [[nodiscard]] bool IsAllHooksDestroyed()
    {
        return g_cvar_change_hooks == nullptr || g_cvar_change_hooks->empty();
    }

    ATTR_MINSIZE void OnHookNotify(const MHook* const hook, const MHookNotice notice)
    {
        assert(g_cvar_direct_set_hook != nullptr);

        switch (notice) {
        case MHookNotice::Enable:
            g_cvar_direct_set_hook->Enable();
            break;

        case MHookNotice::Disable:
            if (IsAllHooksDisabled()) {
                g_cvar_direct_set_hook->Disable();
            }
            break;

        case MHookNotice::Destroy:
            RemoveHook(hook);

            if (IsAllHooksDestroyed()) {
                delete g_cvar_direct_set_hook;
                g_cvar_direct_set_hook = nullptr;

                delete g_cvar_change_hooks;
                g_cvar_change_hooks = nullptr;
            }
            break;
        }
    }

    ATTR_MINSIZE MHook* CreateHook(const CVar* const cvar, const CVarChangeMCallback& callback, const bool enable)
    {
        auto* const hook = new MHook{HookChainPriority::Normal, false};
        Data data{hook, cvar, callback};

        if (g_cvar_direct_set_hook == nullptr) {
            g_cvar_direct_set_hook = MHookReHldsCvarDirectSet(DELEGATE_ARG<OnCvarDirectSet>, HookChainPriority::Medium);
            g_cvar_direct_set_hook->DestroyAtDetach(false); // It will be manually destroyed in OnHookNotify
        }

        if (g_cvar_change_hooks == nullptr) {
            g_cvar_change_hooks = new vector<Data>{};
        }

        g_cvar_change_hooks->emplace_back(data);
        hook->Subscribe<OnHookNotify>();
        hook->Toggle(enable);

        return hook;
    }
}

namespace mhooks
{
    MHook* MHookCVarChange(const CVar* const cvar, const CVarChangeMCallback callback, const bool enable)
    {
        assert(!!callback);
        return CreateHook(cvar, callback, enable);
    }
}
#endif
