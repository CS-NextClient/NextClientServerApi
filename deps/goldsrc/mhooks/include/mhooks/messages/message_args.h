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
#include <cassert>
#include <cstddef>
#include <string>
#include <variant>
#include <vector>

//-V::659

namespace mhooks
{
    class MessageArgs final
    {
        std::vector<std::variant<int, float, std::string>> args_{};

    public:
        /**
         * @brief Gets the message argument as an \c int& value.
        */
        [[nodiscard]] int& GetInteger(const std::size_t index)
        {
            assert(index < Count());
            return *&std::get<0>(args_[index]);
        }

        /**
         * @brief Gets the message argument as a \c float& value.
        */
        [[nodiscard]] float& GetFloating(const std::size_t index)
        {
            assert(index < Count());
            return *&std::get<1>(args_[index]);
        }

        /**
         * @brief Gets the message argument as a \c string& value.
        */
        [[nodiscard]] std::string& GetString(const std::size_t index)
        {
            assert(index < Count());
            return *&std::get<2>(args_[index]);
        }

        /**
         * @brief Gets an array with all the message arguments.
        */
        [[nodiscard]] auto& GetArgs() noexcept
        {
            return args_;
        }

        /**
         * @brief Gets the message argument as an \c int value.
        */
        [[nodiscard]] int GetInteger(const std::size_t index) const
        {
            assert(index < Count());
            return std::get<0>(args_[index]);
        }

        /**
         * @brief Gets the message argument as a \c float value.
        */
        [[nodiscard]] float GetFloating(const std::size_t index) const
        {
            assert(index < Count());
            return std::get<1>(args_[index]);
        }

        /**
         * @brief Gets the message argument as a \c const string& value.
        */
        [[nodiscard]] const std::string& GetString(const std::size_t index) const
        {
            assert(index < Count());
            return *&std::get<2>(args_[index]);
        }

        /**
         * @brief Gets an array with all the message arguments.
        */
        [[nodiscard]] const auto& GetArgs() const noexcept
        {
            return args_;
        }

        /**
         * @brief Gets the number of arguments.
        */
        [[nodiscard]] std::size_t Count() const noexcept
        {
            return args_.size();
        }
    };
}
#endif
