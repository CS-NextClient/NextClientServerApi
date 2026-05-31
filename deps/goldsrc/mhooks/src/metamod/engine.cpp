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

#ifdef HAS_METAMOD_LIB
#include "createhook.h"
#include <mhooks/metamod/engine.h>

using namespace cssdk;
using namespace metamod::engine;
using namespace mhooks::detail;

namespace mhooks
{
    MHook* MHookEngineMessageBegin(const EngineMessageBeginMCallback callback, const bool post,
                                   const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineMessageBegin;
        return CreateHook<EngineMessageBegin>(HookMessageBegin, callback, priority, post, enable);
    }

    MHook* MHookEngineMessageEnd(const EngineMessageEndMCallback callback, const bool post,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineMessageEnd;
        return CreateHook<EngineMessageEnd>(HookMessageEnd, callback, priority, post, enable);
    }

    MHook* MHookEngineWriteByte(const EngineWriteByteMCallback callback, const bool post,
                                const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineWriteByte;
        return CreateHook<EngineWriteByte>(HookWriteByte, callback, priority, post, enable);
    }

    MHook* MHookEngineWriteChar(const EngineWriteCharMCallback callback, const bool post,
                                const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineWriteChar;
        return CreateHook<EngineWriteChar>(HookWriteChar, callback, priority, post, enable);
    }

    MHook* MHookEngineWriteShort(const EngineWriteShortMCallback callback, const bool post,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineWriteShort;
        return CreateHook<EngineWriteShort>(HookWriteShort, callback, priority, post, enable);
    }

    MHook* MHookEngineWriteLong(const EngineWriteLongMCallback callback, const bool post,
                                const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineWriteLong;
        return CreateHook<EngineWriteLong>(HookWriteLong, callback, priority, post, enable);
    }

    MHook* MHookEngineWriteAngle(const EngineWriteAngleMCallback callback, const bool post,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineWriteAngle;
        return CreateHook<EngineWriteAngle>(HookWriteAngle, callback, priority, post, enable);
    }

    MHook* MHookEngineWriteCoord(const EngineWriteCoordMCallback callback, const bool post,
                                 const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineWriteCoord;
        return CreateHook<EngineWriteCoord>(HookWriteCoord, callback, priority, post, enable);
    }

    MHook* MHookEngineWriteString(const EngineWriteStringMCallback callback, const bool post,
                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineWriteString;
        return CreateHook<EngineWriteString>(HookWriteString, callback, priority, post, enable);
    }

    MHook* MHookEngineWriteEntity(const EngineWriteEntityMCallback callback, const bool post,
                                  const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineWriteEntity;
        return CreateHook<EngineWriteEntity>(HookWriteEntity, callback, priority, post, enable);
    }

    MHook* MHookEngineRegUserMessage(const EngineRegUserMessageMCallback callback, const bool post,
                                     const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineRegUserMessage;
        return CreateHook<EngineRegUserMessage>(HookRegUserMessage, callback, priority, post, enable);
    }

    MHook* MHookEnginePrecacheModel(const EnginePrecacheModelMCallback callback, const bool post,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EnginePrecacheModel;
        return CreateHook<EnginePrecacheModel>(HookPrecacheModel, callback, priority, post, enable);
    }

    MHook* MHookEnginePrecacheSound(const EnginePrecacheSoundMCallback callback, const bool post,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EnginePrecacheSound;
        return CreateHook<EnginePrecacheSound>(HookPrecacheSound, callback, priority, post, enable);
    }

    MHook* MHookEnginePrecacheGeneric(const EnginePrecacheGenericMCallback callback, const bool post,
                                      const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EnginePrecacheGeneric;
        return CreateHook<EnginePrecacheGeneric>(HookPrecacheGeneric, callback, priority, post, enable);
    }

    MHook* MHookEnginePrecacheEvent(const EnginePrecacheEventMCallback callback, const bool post,
                                    const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EnginePrecacheEvent;
        return CreateHook<EnginePrecacheEvent>(HookPrecacheEvent, callback, priority, post, enable);
    }

    MHook* MHookEngineTraceLine(const EngineTraceLineMCallback callback, const bool post,
                                const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineTraceLine;
        return CreateHook<EngineTraceLine>(HookTraceLine, callback, priority, post, enable);
    }

    MHook* MHookEngineTraceHull(const EngineTraceHullMCallback callback, const bool post,
                                const HookChainPriority priority, const bool enable)
    {
        assert(!!callback);
        struct EngineTraceHull;
        return CreateHook<EngineTraceHull>(HookTraceHull, callback, priority, post, enable);
    }
}
#endif
