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
#include <core/localization.h>
#include <core/console.h>
#include <cssdk/public/os_defs.h>
#include <cssdk/public/utils.h>
#include <metamod/engine.h>
#include <algorithm>
#include <cstdio>
#include <functional>

using namespace core;
using namespace cssdk;
using namespace metamod;

namespace
{
    bool IsLangInList(const std::vector<std::string>& languages, const std::string_view lang)
    {
        return std::any_of(languages.cbegin(), languages.cend(), [lang](const auto& element) {
            return str::Equals(element, lang);
        });
    }

    std::string_view GetLanguage(Edict* const client, const std::string& language)
    {
        const auto* const amx_language =
            g_engine_funcs.cvar_get_string ? engine::CvarGetString("amx_language") : nullptr;

#ifdef MSVC_COMPILER
#pragma warning(push)
#pragma warning(disable : 6387)
#endif
        const std::string_view server_language = !str::IsNullOrEmpty(amx_language) ? amx_language : "en";
#ifdef MSVC_COMPILER
#pragma warning(pop)
#endif

        if (client && str::IEquals(language, "player")) {
            const auto* const player_lang = EntityKeyValue(client, "lang");
            return !str::IsNullOrEmpty(player_lang) ? std::string_view{player_lang} : server_language;
        }

        if (str::IEquals(language, "server")) {
            return server_language;
        }

        return language;
    }

    bool SplitLabelText(const std::string_view string, std::string_view& label, std::string& text)
    {
        const auto label_end = string.find_first_of('=');

        if (label_end == std::string_view::npos) {
            return false;
        }

        label = string.substr(0, label_end);
        label = str::Trim(label);

        text = string.substr(label_end + 1);
        text = str::Trim(text);

        return !label.empty();
    }

    void Parse(const std::string& filepath, std::vector<std::string>& languages,
               std::unordered_map<std::size_t, std::string>& localization)
    {
#ifdef MSVC_COMPILER
        std::FILE* stream{};
        if (fopen_s(&stream, filepath.c_str(), "rt") || !stream) {
            return;
        }
#else
        std::FILE* stream{};
        if (!((stream = std::fopen(filepath.c_str(), "r")))) {
            return;
        }
#endif

        char buffer[512];
        std::size_t hash_lang{0};
        constexpr std::hash<std::string_view> hasher{};

        while (std::fgets(buffer, sizeof buffer, stream)) {
            const auto buffer_view = str::Trim(buffer);

            // Skip comment
            if (buffer_view.length() < 3 || buffer_view.front() == ';' ||
                buffer_view.front() == '/' || buffer_view.front() == '#') {
                continue;
            }

            // Parse language code
            if (buffer_view.length() == 4 && buffer_view.front() == '[' && buffer_view.back() == ']') {
                const auto lang = buffer_view.substr(1, 2);

                languages.emplace_back(std::string{lang});
                hash_lang = hasher(lang);

                continue;
            }

            // Parse label and text
            if (hash_lang != 0) {
                std::string_view label{};
                std::string text{};

                if (SplitLabelText(buffer_view, label, text)) {
                    str::ReplaceAll(text, "^1", std::string(1, 0x1));
                    str::ReplaceAll(text, "^3", std::string(1, 0x3));
                    str::ReplaceAll(text, "^4", std::string(1, 0x4));

                    localization[hash_lang + hasher(label)] = text;
                }
            }
        }

        std::fclose(stream);
    }
}

namespace core
{
    Localization::Localization(std::string filepath)
        : filepath_(std::move(filepath))
    {
        Reload();
    }

    void Localization::Reload()
    {
        languages_.clear();
        localization_.clear();
        Parse(filepath_, languages_, localization_);

        if (localization_.empty()) {
            console::Message<false>(str::EMPTY);
            console::Warning("Failed to parse localization file. Filepath: \"%s\"\n", filepath_);
        }
    }

    const std::string& Localization::GetText(const std::string& lang, const std::string_view label, Edict* const client) const
    {
        constexpr std::hash<std::string_view> hasher{};

        if (label.empty()) {
            return notfound_;
        }

        const auto language = GetLanguage(client, lang);
        const auto& it_find = localization_.find(hasher(IsLangInList(languages_, language) ? language : "en") + hasher(label));

        return it_find == localization_.end() ? notfound_ : it_find->second;
    }
}
#endif
