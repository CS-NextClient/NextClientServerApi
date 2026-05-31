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
#include <core/strings.h>
#include <cssdk/engine/edict.h>
#include <cssdk/public/os_defs.h>
#include <cstddef>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace core
{
    class Localization
    {
        std::string filepath_;
        std::string notfound_{"ML_NOTFOUND"};
        std::vector<std::string> languages_{};
        std::unordered_map<std::size_t, std::string> localization_{};

    public:
        /**
         * @brief Constructor.
         *
         * @param filepath The path to the localization file.
        */
        explicit Localization(std::string filepath);

        /**
         * @brief Reloads the localization file.
        */
        void Reload();

        /**
         * @brief Gets the text by the text label.
         *
         * @note Set lang value to \c "server" to get the language from the amx_language CVar.
         * @note Set lang value to \c "player" to get the language from the player config (setinfo "lang").
        */
        [[nodiscard]] const std::string& GetText(const std::string& lang, std::string_view label,
                                                 cssdk::Edict* client = nullptr) const;
        /**
         * @brief Gets the text by the text label.
         *
         * @note Set lang value to \c "server" to get the language from the amx_language CVar.
         * @note Set lang value to \c "player" to get the language from the player config (setinfo "lang").
        */
        template <typename... Args>
        [[nodiscard]] std::string GetTextFormat(const std::string& lang, std::string_view label, Args&&... args) const;

        /**
         * @brief Gets the text by the text label.
         *
         * @note Set lang value to \c "server" to get the language from the amx_language CVar.
         * @note Set lang value to \c "player" to get the language from the player config (setinfo "lang").
        */
        template <typename... Args>
        [[nodiscard]] std::string GetTextFormat(const std::string& lang, std::string_view label,
                                                cssdk::Edict* client, Args&&... args) const;
    };

    template <typename... Args>
    FORCEINLINE std::string Localization::GetTextFormat(const std::string& lang, const std::string_view label, Args&&... args) const
    {
        return str::Format(GetText(lang, label), std::forward<Args>(args)...);
    }

    template <typename... Args>
    FORCEINLINE std::string Localization::GetTextFormat(const std::string& lang, const std::string_view label,
                                                        cssdk::Edict* const client, Args&&... args) const
    {
        return str::Format(GetText(lang, label, client), std::forward<Args>(args)...);
    }
}
#endif
