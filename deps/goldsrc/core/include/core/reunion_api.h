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

#ifdef HAS_CSSDK_LIB
#include <cssdk/public/rehlds/userid_rehlds.h>
#include <cassert>
#include <cstddef>

namespace core::reunion_api
{
    constexpr auto REUNION_API_VERSION_MAJOR = 1;
    constexpr auto REUNION_API_VERSION_MINOR = 4;
    constexpr auto LONG_AUTHID_LEN = 16;

    enum class AuthKind
    {
        None = 0,
        Dproto,
        Steam,
        SteamEmu,
        RevEmu,
        OldRevEmu,
        Hltv,
        Sc2009,
        Avsmp,
        Sxei,
        RevEmu2013,
        Sse3
    };

    enum class AuthKeyKind
    {
        Unknown = -1,
        Steam,
        VolumeId,
        HddSn,
        FileId,
        SxeId,
        Other,
        Max
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class IReunionApi // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        [[nodiscard]] virtual int GetClientProtocol(int index) = 0;
        [[nodiscard]] virtual AuthKind GetClientAuthType(int index) = 0;
        [[nodiscard]] virtual std::size_t GetClientAuthData(int index, void* data, int max_len) = 0; // deprecated
        [[nodiscard]] virtual const char* GetClientAuthDataString(int index, char* data, int max_len) = 0; // deprecated
        [[nodiscard]] virtual int GetMajorVersion() = 0;
        [[nodiscard]] virtual int GetMinorVersion() = 0;
        virtual void GetLongAuthId(int index, std::byte* auth_id) = 0;
        [[nodiscard]] virtual AuthKeyKind GetAuthKeyKind(int index) = 0;
        virtual void SetConnectTime(int index, double time) = 0;
        [[nodiscard]] virtual cssdk::UserId* GetSerializedId(int index) const = 0;
        [[nodiscard]] virtual cssdk::UserId* GetStorageId(int index) const = 0;
        [[nodiscard]] virtual cssdk::uint64 GetDisplaySteamId(int index) const = 0;
    };

    namespace detail
    {
        inline IReunionApi* reunion_api{};
    }

    /**
     * @brief Initializes the Reunion API. Returns true on success or false on failure.
    */
    bool Init(bool silent = false);

    /**
     * @brief Returns \c true if the Reunion API was successfully initialized, otherwise \c false.
    */
    [[nodiscard]] inline bool Initialized()
    {
        return detail::reunion_api != nullptr;
    }

    /**
     * @brief Returns the major version number of Reunion API.
    */
    [[nodiscard]] inline int MajorVersion()
    {
        assert(detail::reunion_api != nullptr);
        return detail::reunion_api->GetMajorVersion();
    }

    /**
     * @brief Returns the minor version number of Reunion API.
    */
    [[nodiscard]] inline int MinorVersion()
    {
        assert(detail::reunion_api != nullptr);
        return detail::reunion_api->GetMinorVersion();
    }

    /**
     * @brief N/D
    */
    [[nodiscard]] inline int GetClientProtocol(const int index)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetClientProtocol(index);
    }

    /**
     * @brief N/D
    */
    [[nodiscard]] inline AuthKind GetClientAuthType(const int index)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetClientAuthType(index);
    }

    /**
     * @brief Deprecated.
    */
    [[nodiscard]] inline std::size_t GetClientAuthData(const int index, void* const data, const int max_len)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetClientAuthData(index, data, max_len);
    }

    /**
     * @brief Deprecated.
    */
    [[nodiscard]] inline const char* GetClientAuthDataString(const int index, char* const data, const int max_len)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetClientAuthDataString(index, data, max_len);
    }

    /**
     * @brief N/D
    */
    inline void GetLongAuthId(const int index, std::byte (&auth_id)[LONG_AUTHID_LEN])
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        assert(auth_id != nullptr);
        detail::reunion_api->GetLongAuthId(index, auth_id);
    }

    /**
     * @brief N/D
    */
    [[nodiscard]] inline AuthKeyKind GetAuthKeyKind(const int index)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetAuthKeyKind(index);
    }

    /**
     * @brief N/D
    */
    inline void SetConnectTime(const int index, const double time)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        detail::reunion_api->SetConnectTime(index, time);
    }

    /**
     * @brief N/D
    */
    [[nodiscard]] inline cssdk::UserId* GetSerializedId(const int index)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetSerializedId(index);
    }

    /**
     * @brief N/D
    */
    [[nodiscard]] inline cssdk::UserId* GetStorageId(const int index)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetStorageId(index);
    }

    /**
     * @brief N/D
    */
    [[nodiscard]] inline cssdk::uint64 GetDisplaySteamId(const int index)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetDisplaySteamId(index);
    }

    /**
     * @brief N/D
    */
    [[nodiscard]] inline bool IsUserSteam(const int index)
    {
        assert(detail::reunion_api != nullptr);
        assert(index >= 0 && index < cssdk::MAX_CLIENTS);
        return detail::reunion_api->GetClientAuthType(index) == AuthKind::Steam;
    }
}
#endif
