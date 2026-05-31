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

#pragma once

#ifdef HAS_METAMOD_LIB
#include <core/delegate.h>
#include <metamod/api.h>
#include <metamod/config.h>
#include <mhooks/common/mhook.h>
#include <mhooks/metaapi/metaapi_mhookchain.h>

#ifndef META_DETACH
#error META_DETACH function required. Please check your CMakeLists.txt
#endif

// Meta_Init
using MetaInitMChain = mhooks::MetaApiMHookChain<void()>;
using MetaInitMCallback = core::Delegate<void(const MetaInitMChain& chain)>;

// Meta_Query
using MetaQueryMChain = mhooks::MetaApiMHookChain<void()>;
using MetaQueryMCallback = core::Delegate<void(const MetaQueryMChain& chain)>;

// Meta_Attach
using MetaAttachMChain = mhooks::MetaApiMHookChain<MetaStatus()>;
using MetaAttachMCallback = core::Delegate<MetaStatus(const MetaAttachMChain& chain)>;

// Meta_Detach
using MetaDetachMChain = mhooks::MetaApiMHookChain<void()>;
using MetaDetachMCallback = core::Delegate<void(const MetaDetachMChain& chain)>;

namespace mhooks
{
#if defined(META_INIT) && defined(HAS_AMXX_LIB)
    /**
     * @brief Hooks the \c Meta_Init function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookMetaInit(
        MetaInitMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif

#ifdef META_QUERY
    /**
     * @brief Hooks the \c Meta_Query function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookMetaQuery(
        MetaQueryMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif

#ifdef META_ATTACH
    /**
     * @brief Hooks the \c Meta_Attach function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookMetaAttach(
        MetaAttachMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
#endif
    /**
     * @brief Hooks the \c Meta_Detach function.
     *
     * @param callback Hook callback function.
     * @param priority Hook priority.
     * @param enable Should a hook be enabled?
    */
    ATTR_MINSIZE MHook* MHookMetaDetach(
        MetaDetachMCallback callback,
        cssdk::HookChainPriority priority = cssdk::HookChainPriority::Normal, bool enable = true);
}
#endif
