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
#include <metamod/utils.h>
#include <mhooks/messages/message_args.h>
#include <cassert>
#include <cstddef>

namespace mhooks::detail
{
    enum class MessageArgType
    {
        Byte,
        Char,
        Short,
        Long,
        Angle,
        Coord,
        String,
        Entity
    };

    class Message final
    {
        std::vector<MessageArgType> arg_types_{};
        cssdk::EngineFunctions* engine_functions_{};

    public:
        [[nodiscard]] std::vector<MessageArgType>& ArgTypes() noexcept
        {
            return arg_types_;
        }

        void Send(const cssdk::MessageType type, const int id, const float* const origin, cssdk::Edict* const client, const MessageArgs& args)
        {
            if (engine_functions_ == nullptr) {
                metamod::utils::GetHookTables(&engine_functions_, nullptr, nullptr);
                assert(engine_functions_ != nullptr);
            }

            engine_functions_->message_begin(type, id, origin, client);
            const auto count = arg_types_.size();

            for (std::size_t i = 0; i < count; ++i) {
                switch (arg_types_[i]) {
                case MessageArgType::Byte:
                    engine_functions_->write_byte(args.GetInteger(i));
                    break;

                case MessageArgType::Char:
                    engine_functions_->write_char(args.GetInteger(i));
                    break;

                case MessageArgType::Short:
                    engine_functions_->write_short(args.GetInteger(i));
                    break;

                case MessageArgType::Long:
                    engine_functions_->write_long(args.GetInteger(i));
                    break;

                case MessageArgType::Angle:
                    engine_functions_->write_angle(args.GetFloating(i));
                    break;

                case MessageArgType::Coord:
                    engine_functions_->write_coord(args.GetFloating(i));
                    break;

                case MessageArgType::String:
                    engine_functions_->write_string(args.GetString(i).c_str());
                    break;

                case MessageArgType::Entity:
                    engine_functions_->write_entity(args.GetInteger(i));
                    break;
                }
            }

            engine_functions_->message_end();
        }
    };
}
#endif
