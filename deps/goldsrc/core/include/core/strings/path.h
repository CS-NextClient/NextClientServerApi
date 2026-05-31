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

#include <core/strings/format.h>
#include <cassert>
#include <string>
#include <string_view>
#include <utility>

namespace core::str
{
    /**
     * @brief Retrieves the directory path from the file path.
    */
    [[nodiscard]] std::string_view GetDirectoryFromPath(std::string_view path, char separator);

    /**
     * @brief Retrieves the directory path from the file path.
    */
    [[nodiscard]] inline std::string_view GetDirectoryFromPath(const std::string_view path)
    {
#ifdef _WIN32
        return GetDirectoryFromPath(path, '\\');
#else
        return GetDirectoryFromPath(path, '/');
#endif
    }

    /**
     * @brief Retrieves the file name from the file path.
     *
     * @note Returns an empty string on error.
    */
    [[nodiscard]] std::string_view GetFileNameFromPath(std::string_view path, char separator);

    /**
     * @brief Retrieves the file name from the file path.
     *
     * @note Returns an empty string on error.
    */
    [[nodiscard]] inline std::string_view GetFileNameFromPath(const std::string_view path)
    {
#ifdef _WIN32
        return GetFileNameFromPath(path, '\\');
#else
        return GetFileNameFromPath(path, '/');
#endif
    }

    /**
     * @brief Retrieves the file name without extension from the file path.
     *
     * @note Returns an empty string on error.
    */
    [[nodiscard]] std::string_view GetFileNameWithoutExtension(std::string_view path, char separator);

    /**
     * @brief Retrieves the file name without extension from the file path.
     *
     * @note Returns an empty string on error.
    */
    [[nodiscard]] inline std::string_view GetFileNameWithoutExtension(const std::string_view filename)
    {
#ifdef _WIN32
        return GetFileNameWithoutExtension(filename, '\\');
#else
        return GetFileNameWithoutExtension(filename, '/');
#endif
    }

    /**
     * @brief Retrieves the file extension from the file name.
     *
     * @note Returns an empty string on error.
    */
    [[nodiscard]] std::string_view GetFileExtension(std::string_view filename, char separator);

    /**
     * @brief Retrieves the file extension from the file name.
     *
     * @note Returns an empty string on error.
    */
    [[nodiscard]] inline std::string_view GetFileExtension(const std::string_view filename)
    {
#ifdef _WIN32
        return GetFileExtension(filename, '\\');
#else
        return GetFileExtension(filename, '/');
#endif
    }

    /**
     * @brief Returns the current working directory path.
    */
    [[nodiscard]] std::string GetWorkingDirectory();

    /**
     * @brief Returns the game mod directory name.
    */
    [[nodiscard]] std::string GetGameModDirectoryName();

    /**
     * @brief Returns the game mod directory path.
    */
    [[nodiscard]] inline std::string GetGameModDirectoryPath()
    {
        const auto working_dir = GetWorkingDirectory();
        const auto game_mod_dir = GetGameModDirectoryName();

#ifdef _WIN32
        return Format("%s\\%s", working_dir.c_str(), game_mod_dir.c_str());
#else
        return Format("%s/%s", working_dir.c_str(), game_mod_dir.c_str());
#endif
    }
}

#ifdef HAS_AMXX_LIB
#include <amxx/api.h>

namespace core::str
{
    /**
     * @brief Returns the path to the AMXX logs directory relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxLogsDir()
    {
        const auto* const local_info = amxx::GetLocalInfo("amxx_logs", "addons/amxmodx/logs");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX configs directory relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxConfigsDir()
    {
        const auto* const local_info = amxx::GetLocalInfo("amxx_configsdir", "addons/amxmodx/configs");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX data directory relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxDataDir()
    {
        const auto* const local_info = amxx::GetLocalInfo("amxx_datadir", "addons/amxmodx/data");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX lang directory relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxLangDir()
    {
        return GetAmxxDataDir() + "/lang";
    }

    /**
     * @brief Returns the path to the AMXX modules directory relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxModulesDir()
    {
        const auto* const local_info = amxx::GetLocalInfo("amxx_modulesdir", "addons/amxmodx/modules");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX plugins directory relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxPluginsDir()
    {
        const auto* const local_info = amxx::GetLocalInfo("amxx_pluginsdir", "addons/amxmodx/plugins");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX modules.ini file relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxModulesIni()
    {
        const auto* const local_info = amxx::GetLocalInfo("amxx_modules", "addons/amxmodx/configs/modules.ini");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX plugins.ini file relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxPluginsIni()
    {
        const auto* const local_info = amxx::GetLocalInfo("amxx_plugins", "addons/amxmodx/configs/plugins.ini");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX vault.ini file relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxVaultIni()
    {
        const auto* const local_info = amxx::GetLocalInfo("amxx_vault", "addons/amxmodx/data/vault.ini");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX csstats.dat file relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxCsStatsDat()
    {
        const auto* const local_info = amxx::GetLocalInfo("csstats", "addons/amxmodx/data/csstats.dat");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path to the AMXX csstats.amxx file relative to the game mod directory.
     *
     * @note The path separator is always a forward slash / regardless of the current platform.
    */
    [[nodiscard]] inline std::string GetAmxxCsStatsPlugin()
    {
        const auto* const local_info = amxx::GetLocalInfo("csstats_score", "addons/amxmodx/data/csstats.amxx");
        assert(local_info != nullptr);

        return std::string{local_info};
    }

    /**
     * @brief Returns the path relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    template <typename... Args>
    [[nodiscard]] std::string BuildPathName(const std::string& format, Args&&... args)
    {
        const auto fmt = Format(format, std::forward<Args>(args)...);
        const auto* const path = amxx::BuildPathName(fmt.c_str());
        assert(path != nullptr);

        return std::string{path};
    }

    /**
     * @brief Returns the path to the AMXX logs directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxLogs()
    {
        return BuildPathName(GetAmxxLogsDir());
    }

    /**
     * @brief Returns the path to the file in the AMXX logs directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxLogs(const std::string& filename)
    {
        const auto directory = GetAmxxLogsDir();
        return BuildPathName("%s/%s", directory.c_str(), filename.c_str());
    }

    /**
     * @brief Returns the path to the AMXX configs directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxConfigs()
    {
        return BuildPathName(GetAmxxConfigsDir());
    }

    /**
     * @brief Returns the path to the file in the AMXX configs directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxConfigs(const std::string& filename)
    {
        const auto directory = GetAmxxConfigsDir();
        return BuildPathName("%s/%s", directory.c_str(), filename.c_str());
    }

    /**
     * @brief Returns the path to the AMXX data directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxData()
    {
        return BuildPathName(GetAmxxDataDir());
    }

    /**
     * @brief Returns the path to the file in the AMXX data directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxData(const std::string& filename)
    {
        const auto directory = GetAmxxDataDir();
        return BuildPathName("%s/%s", directory.c_str(), filename.c_str());
    }

    /**
     * @brief Returns the path to the AMXX lang directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxLang()
    {
        return BuildPathName(GetAmxxLangDir());
    }

    /**
     * @brief Returns the path to the file in the AMXX lang directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxLang(const std::string& filename)
    {
        const auto directory = GetAmxxLangDir();
        return BuildPathName("%s/%s", directory.c_str(), filename.c_str());
    }

    /**
     * @brief Returns the path to the AMXX modules directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxModules()
    {
        return BuildPathName(GetAmxxModulesDir());
    }

    /**
     * @brief Returns the path to the file in the AMXX modules directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxModules(const std::string& filename)
    {
        const auto directory = GetAmxxModulesDir();
        return BuildPathName("%s/%s", directory.c_str(), filename.c_str());
    }

    /**
     * @brief Returns the path to the AMXX plugins directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxPlugins()
    {
        return BuildPathName(GetAmxxPluginsDir());
    }

    /**
     * @brief Returns the path to the file in the AMXX plugins directory relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxPlugins(const std::string& filename)
    {
        const auto directory = GetAmxxPluginsDir();
        return BuildPathName("%s/%s", directory.c_str(), filename.c_str());
    }

    /**
     * @brief Returns the path to the AMXX modules.ini file relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxModulesIni()
    {
        return BuildPathName(GetAmxxModulesIni());
    }

    /**
     * @brief Returns the path to the AMXX plugins.ini file relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxPluginsIni()
    {
        return BuildPathName(GetAmxxPluginsIni());
    }

    /**
     * @brief Returns the path to the AMXX vault.ini file relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxVaultIni()
    {
        return BuildPathName(GetAmxxVaultIni());
    }

    /**
     * @brief Returns the path to the AMXX csstats.dat file relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxCsStatsDat()
    {
        return BuildPathName(GetAmxxCsStatsDat());
    }

    /**
     * @brief Returns the path to the AMXX csstats.amxx file relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    [[nodiscard]] inline std::string BuildPathAmxxCsStatsPlugin()
    {
        return BuildPathName(GetAmxxCsStatsPlugin());
    }
}
#else
#include <core/strings/mutation.h>

namespace core::str
{
    /**
     * @brief Returns the path relative to the working directory.
     *
     * @note The path separator can be a forward slash / or a backslash \ depending on the current platform.
    */
    template <typename... Args>
    [[nodiscard]] std::string BuildPathName(const std::string& format, Args&&... args)
    {
#ifdef _WIN32
        static const auto mod_directory = GetGameModDirectoryName() + '\\';
        auto path = mod_directory + Format(format, std::forward<Args>(args)...);
        ReplaceAll(path, '/', '\\');
#else
        static const auto mod_directory = GetGameModDirectoryName() + '/';
        auto path = mod_directory + Format(format, std::forward<Args>(args)...);
        ReplaceAll(path, '\\', '/');
#endif

        return path;
    }
}
#endif
