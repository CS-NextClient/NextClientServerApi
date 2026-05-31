/*
 *  Half Life 1 SDK Copyright(c) Valve Corp.
 *
 *  THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE CORPORATION ("Valve").
 *  PLEASE READ IT BEFORE DOWNLOADING OR USING THE HALF LIFE 1 SDK ("SDK"). BY
 *  DOWNLOADING AND/OR USING THE HALF LIFE 1 SDK YOU ACCEPT THIS LICENSE. IF YOU DO
 *  NOT AGREE TO THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.
 *
 *  You may, free of charge, download and use the SDK to develop a modified Valve
 *  game running on the Half-Life 1 engine. You may distribute your modified Valve
 *  game in source and object code form, but only for free. Terms of use for Valve
 *  games are found in the Steam Subscriber Agreement located here:
 *  http://store.steampowered.com/subscriber_agreement/
 *
 *  You may copy, modify, and distribute the SDK and any modifications you make to
 *  the SDK in source and object code form, but only for free. Any distribution of
 *  this SDK must include this LICENSE file.
 *
 *  Any distribution of the SDK or a substantial portion of the SDK must include
 *  the above copyright notice and the following:
 *
 *    DISCLAIMER OF WARRANTIES. THE HALF LIFE 1 SDK AND ANY OTHER MATERIAL
 *    DOWNLOADED BY LICENSEE IS PROVIDED "AS IS". VALVE AND ITS SUPPLIERS
 *    DISCLAIM ALL WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS OR IMPLIED,
 *    INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY,
 *    NON-INFRINGEMENT, TITLE AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    LIMITATION OF LIABILITY. IN NO EVENT SHALL VALVE OR ITS SUPPLIERS BE LIABLE
 *    FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 *    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
 *    LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THE ENGINE AND/OR THE
 *    SDK, EVEN IF VALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *  If you would like to use the SDK for a commercial purpose, please contact Valve
 *  at sourceengine@valvesoftware.com.
 */

#pragma once

namespace cssdk
{
    /**
     * @brief Set to cause it to be saved to vars.rc.
    */
    constexpr auto FCVAR_ARCHIVE = 1 << 0;

    /**
     * @brief Changes the client's info string.
    */
    constexpr auto FCVAR_USER_INFO = 1 << 1;

    /**
     * @brief Notifies players when changed.
    */
    constexpr auto FCVAR_SERVER = 1 << 2;

    /**
     * @brief Defined by external DLL.
    */
    constexpr auto FCVAR_EXT_DLL = 1 << 3;

    /**
     * @brief Defined by the client dll.
    */
    constexpr auto FCVAR_CLIENT_DLL = 1 << 4;

    /**
     * @brief It's a server cvar, but we don't send the data since it's a password, etc.
     * Sends 1 if it's not bland/zero, 0 otherwise as value.
    */
    constexpr auto FCVAR_PROTECTED = 1 << 5;

    /**
     * @brief This cvar cannot be changed by clients connected to a multiplayer server.
    */
    constexpr auto FCVAR_SP_ONLY = 1 << 6;

    /**
     * @brief This cvar's string cannot contain unprintable characters (e.g., used for player name etc).
    */
    constexpr auto FCVAR_PRINTABLE_ONLY = 1 << 7;

    /**
     * @brief If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log.
    */
    constexpr auto FCVAR_UNLOGGED = 1 << 8;

    /**
     * @brief Strip trailing/leading whitespace from this cvar.
    */
    constexpr auto FCVAR_NO_EXTRA_WHITESPACE = 1 << 9;

    struct CVar
    {
        /**
         * @brief N/D
        */
        const char* name{};

        /**
         * @brief N/D
        */
        const char* string{};

        /**
         * @brief N/D
        */
        int flags{};

        /**
         * @brief N/D
        */
        float value{};

        /**
         * @brief N/D
        */
        CVar* next{};

        CVar& SetName(const char* const t_value)
        {
            name = t_value;
            return *this;
        }

        CVar& SetString(const char* const t_value)
        {
            string = t_value;
            return *this;
        }

        CVar& SetFlags(const int t_value)
        {
            flags = t_value;
            return *this;
        }

        CVar& SetValue(const float t_value)
        {
            value = t_value;
            return *this;
        }

        CVar& SetNext(CVar* const t_value)
        {
            next = t_value;
            return *this;
        }
    };

    /**
     * @brief N/D
    */
    using CVarCallback = void (*)(const char* new_value);

    struct CVarListener
    {
        /**
         * @brief Constructor.
        */
        CVarListener(const char* const var_name, const CVarCallback handler)
            : func(handler), name(var_name)
        {
        }

        /**
         * @brief N/D
        */
        CVarCallback func{};

        /**
         * @brief N/D
        */
        const char* name{};
    };
}
