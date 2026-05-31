/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#pragma once

#include <cstddef>

namespace amxx
{
    class TextListener;

    enum class ConfigFieldType
    {
        None,

        /**
         * @brief Floating point value.
        */
        Float,

        /**
         * @brief String ID (return from ALLOC_STRING).
        */
        StringInt,

        /**
         * @brief String, pointer-to-char.
        */
        StringPtr,

        /**
         * @brief String, fixed size.
        */
        String,

        /**
         * @brief Classes pointer derived of \c cssdk::EntityBase.
        */
        ClassPtr,

        /**
         * @brief Arbitrary classes, direct.
        */
        Class,

        /**
         * @brief Arbitrary structures, direct.
        */
        Structure,

        /**
         * @brief Entity handle.
        */
        EntHandle,

        /**
         * @brief \c cssdk::EntityVars*
        */
        EntVars,

        /**
         * @brief \c cssdk::Edict*
        */
        Edict,

        /**
         * @brief cssdk::Vector
        */
        Vector,

        /**
         * @brief cssdk::Arbitrary data pointer.
        */
        Pointer,

        /**
         * @brief Integer or enum.
        */
        Integer,

        /**
         * @brief Class function pointer (think, use, etc).
        */
        Function,

        /**
         * @brief \c bool.
        */
        Boolean,

        /**
         * @brief 2 bytes integer.
        */
        Short,

        /**
         * @brief 1 byte.
        */
        Character
    };

    struct ConfigTypeDescription
    {
        /**
         * @brief N/D
        */
        ConfigTypeDescription()
        {
            Reset();
        }

        /**
         * @brief N/D
        */
        void Reset()
        {
            field_type = ConfigFieldType::None;
            field_offset = 0;
            field_size = 0;
            field_unsigned = false;
        }

        /**
         * @brief N/D
        */
        ConfigFieldType field_type{};

        /**
         * @brief N/D
        */
        int field_offset{};

        /**
         * @brief N/D
        */
        int field_size{};

        /**
         * @brief N/D
        */
        bool field_unsigned{};
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class GameConfig
    {
    public:
        /**
         * @brief Returns an offset value.
         *
         * @param key Key to retrieve from the offset section.
         * @param value Pointer to store the ConfigTypeDescription reference in.
         *
         * @return \c true if found, \c false otherwise.
        */
        virtual bool GetOffset(const char* key, ConfigTypeDescription* value) = 0;

        /**
         * @brief Returns an offset value from given class.
         *
         * @param classname Class name to match from the offset section.
         * @param key Key to retrieve from the offset section.
         * @param value Pointer to store the ConfigTypeDescription reference in.
         *
         * @return \c true if found, \c false otherwise.
        */
        virtual bool GetOffsetByClass(const char* classname, const char* key, ConfigTypeDescription* value) = 0;

        /**
         * @brief Returns the value of a key from the "Keys" section.
         *
         * @param key Key to retrieve from the Keys section.
         *
         * @return String containing the value, or NULL if not found.
        */
        virtual const char* GetKeyValue(const char* key) = 0;

        /**
         * @brief Retrieves a cached memory signature.
         *
         * @param key Name of the signature.
         * @param address Pointer to store the memory address in (NULL is copied if signature is not found in binary).
         *
         * @return \c true if the section exists and key for current platform was found; \c false otherwise.
        */
        virtual bool GetMemSig(const char* key, void** address) = 0;

        /**
         * @brief Retrieves the value of an address from the "Address" section.
         *
         * @param key Key to retrieve from the Address section.
         * @param address Pointer to store the memory address.
         *
         * @return \c true on success, \c false on failure.
        */
        virtual bool GetAddress(const char* key, void** address) = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class GameConfigManager
    {
    public:
        /**
         * @brief Loads or finds an already loaded game config file.
         *
         * @param file File to load. The path must be relative to the 'gamedata' folder and the extension should be omitted.
         * @param config Pointer to store the game config pointer. Pointer will be valid even on failure.
         * @param error Optional error message buffer.
         * @param maxlength Maximum length of the error buffer.
         *
         * @return \c true on success, \c false if the file failed.
        */
        virtual bool LoadGameConfigFile(const char* file, GameConfig** config, char* error, std::size_t maxlength) = 0;

        /**
         * @brief Closes an \c GameConfig pointer. Since a file can be loaded more than once, the file will not actually
         * be removed from memory until it is closed once for each call to \c load_game_config_file.
         *
         * @param config Pointer to the \c GameConfig to close.
        */
        virtual void CloseGameConfigFile(GameConfig* config) = 0;

        /**
         * @brief Adds a custom gamedata section hook.
         *
         * @param section_name Section name to hook.
         * @param listener Listener callback.
        */
        virtual void AddUserConfigHook(const char* section_name, TextListener* listener) = 0;

        /**
         * @brief Removes a custom gamedata section hook.
         *
         * @param section_name Section name to unhook.
         * @param listener Listener callback.
        */
        virtual void RemoveUserConfigHook(const char* section_name, TextListener* listener) = 0;
    };
}
