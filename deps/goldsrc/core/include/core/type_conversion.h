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

#if defined(HAS_METAMOD_LIB) && defined(HAS_MHOOKS_LIB)
#include <cssdk/dll/player.h>
#include <cssdk/public/utils.h>
#include <cassert>

namespace core::type_conversion::detail
{
    inline cssdk::Edict* first_edict{};
}

namespace core::type_conversion
{
    /**
     * @brief Initializes type conversions. This must be called once before use.
    */
    void Init();

    /**
     * @brief Returns the index of the specified entity.
    */
    [[nodiscard]] inline int IndexOfEntity(const cssdk::Edict* const edict) noexcept
    {
        assert(edict != nullptr);
        assert(detail::first_edict != nullptr);

        return edict - detail::first_edict;
    }

    /**
     * @brief Returns the index of the specified entity.
    */
    [[nodiscard]] inline int IndexOfEntity(const cssdk::EntityBase* const entity) noexcept
    {
        assert(entity != nullptr);
        assert(detail::first_edict != nullptr);

        return entity->vars->containing_entity - detail::first_edict;
    }

    /**
     * @brief Returns the \c Edict* at the specified entity index.
    */
    [[nodiscard]] inline cssdk::Edict* EdictByIndex(const int index) noexcept
    {
        assert(detail::first_edict != nullptr);
        assert(cssdk::IsValidEntityIndex(index));

        return detail::first_edict + index;
    }

    /**
     * @brief Returns the \c EntityBase* at the specified entity index,
     * or \c nullptr if the entity at the specified index is invalid.
    */
    [[nodiscard]] inline cssdk::EntityBase* EntityByIndex(const int index) noexcept
    {
        const auto* const edict = EdictByIndex(index);
        return IsValidEntity(edict) ? cssdk::EntityPrivateData<cssdk::EntityBase>(edict) : nullptr;
    }

    /**
     * @brief Returns the \c PlayerBase* at the specified player index,
     * or \c nullptr if the player at the specified index is invalid.
    */
    [[nodiscard]] inline cssdk::PlayerBase* PlayerByIndex(const int index) noexcept
    {
        if (cssdk::IsClient(index)) {
            const auto* const edict = EdictByIndex(index);
            return IsValidEntity(edict) ? cssdk::EntityPrivateData<cssdk::PlayerBase>(edict) : nullptr;
        }

        return nullptr;
    }
}
#endif
