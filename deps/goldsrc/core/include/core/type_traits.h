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

#include <string>
#include <string_view>
#include <type_traits>

namespace core::type_traits::detail
{
    template <typename T>
    struct StringType : std::false_type
    {
    };

    template <>
    struct StringType<std::string> : std::true_type
    {
    };

    template <typename T>
    struct StringViewType : std::false_type
    {
    };

    template <>
    struct StringViewType<std::string_view> : std::true_type
    {
    };
}

namespace core::type_traits
{
    template <typename T>
    constexpr auto IsPod()
    {
        return std::is_pod_v<std::decay_t<T>>;
    }

    template <typename T>
    constexpr auto IsString()
    {
        return detail::StringType<std::decay_t<T>>::value;
    }

    template <typename T>
    constexpr auto IsStringView()
    {
        return detail::StringViewType<std::decay_t<T>>::value;
    }
}
