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

#if defined(HAS_AMXX_LIB) && defined(HAS_METAMOD_LIB) && defined(HAS_MHOOKS_LIB)
#include <core/type_conversion.h>
#include <cssdk/dll/player.h>
#include <cssdk/public/utils.h>
#include <array>
#include <cassert>

namespace core::amxx_access::detail
{
    inline std::array<int*, cssdk::MAX_CLIENTS + 1> access_flags{};
}

namespace core::amxx_access
{
    /**
     * @brief Initializes AMXX access. This must be called once before use.
    */
    void Init();

    /**
     * @brief Returns the AMXX player access flags. If the specified player is a bot or HLTV - returns 0.
    */
    inline int Get(const int player)
    {
        assert(cssdk::IsClient(player));
        assert(detail::access_flags[player] != nullptr);

        return *detail::access_flags[player];
    }

    /**
     * @brief Returns the AMXX player access flags. If the specified player is a bot or HLTV - returns 0.
    */
    inline int Get(const cssdk::Edict* const player)
    {
        return Get(type_conversion::IndexOfEntity(player));
    }

    /**
     * @brief Returns the AMXX player access flags. If the specified player is a bot or HLTV - returns 0.
    */
    inline int Get(const cssdk::PlayerBase* const player)
    {
        return Get(type_conversion::IndexOfEntity(player));
    }

    /**
     * @brief Sets the AMXX player access flags.
    */
    inline void Set(const int player, const int flags)
    {
        assert(cssdk::IsClient(player));
        assert(detail::access_flags[player] != nullptr);

        *detail::access_flags[player] = flags;
    }

    /**
     * @brief Sets the AMXX player access flags.
    */
    inline void Set(const cssdk::Edict* const player, const int flags)
    {
        Set(type_conversion::IndexOfEntity(player), flags);
    }

    /**
     * @brief Sets the AMXX player access flags.
    */
    inline void Set(const cssdk::PlayerBase* const player, const int flags)
    {
        Set(type_conversion::IndexOfEntity(player), flags);
    }

    /**
     * @brief Returns \c true if the specified player has the specified flags; \c false otherwise.
    */
    inline bool Has(const int player, const int flags)
    {
        assert(cssdk::IsClient(player));
        assert(detail::access_flags[player] != nullptr);

        return (*detail::access_flags[player] & flags) == flags;
    }

    /**
     * @brief Returns \c true if the specified player has the specified flags; \c false otherwise.
    */
    inline bool Has(const cssdk::Edict* const player, const int flags)
    {
        return Has(type_conversion::IndexOfEntity(player), flags);
    }

    /**
     * @brief Returns \c true if the specified player has the specified flags; \c false otherwise.
    */
    inline bool Has(const cssdk::PlayerBase* const player, const int flags)
    {
        return Has(type_conversion::IndexOfEntity(player), flags);
    }
}
#endif
