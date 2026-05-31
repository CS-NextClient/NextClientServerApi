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

#include <amxx/amx.h>
#include <amxx/config.h>
#include <amxx/os_defs.h>
#include <type_traits>
#include <utility>

#ifdef USE_METAMOD
#include <cssdk/engine/edict.h>
#else
using Edict = void;
#endif

#ifndef AMXX_182_COMPATIBILITY
#include <amxx/game_configs.h>
#endif

//-V::122
//-V:ApiFuncPointers:730

/**
 * @brief AMXX interface version.
 * 2 - Added log_tag to struct (amxx1.1-rc1).
 * 3 - Added new Amx structure (amxx1.5).
 * 4 - Added new 'library' setting for direct loading.
 *
*/
constexpr auto AMXX_INTERFACE_VERSION = 4;

/**
 * @brief N/D
*/
constexpr auto AMXX_MSG_BLOCK_SET = 0;

/**
 * @brief N/D
*/
constexpr auto AMXX_MSG_BLOCK_GET = 1;

/**
 * @brief N/D
*/
constexpr auto AMXX_BLOCK_NOT = 0;

/**
 * @brief N/D
*/
constexpr auto AMXX_BLOCK_ONCE = 1;

/**
 * @brief N/D
*/
constexpr auto AMXX_BLOCK_SET = 2;

namespace amxx
{
    enum class Status : int
    {
        /**
         * @brief Something went wrong.
        */
        Failed = -1,

        /**
         * @brief No error.
        */
        Ok = 0,

        /**
         * @brief Interface version.
        */
        InterfaceMismatch,

        /**
         * @brief Invalid parameter.
        */
        InvalidParameter,

        /**
         * @brief N/D
        */
        FuncNotPresent
    };

    enum class GameStatus : int
    {
        /**
         * @brief This module can load on the current game mod.
        */
        Ok = 0,

        /**
         * @brief This module can not load on the current game mod.
        */
        Bad
    };

    enum class ForwardExecType
    {
        /**
         * @brief Ignore return value.
        */
        Ignore = 0,

        /**
         * @brief Stop on PLUGIN_HANDLED.
        */
        Stop,

        /**
         * @brief Stop on PLUGIN_HANDLED, continue on other values, return biggest return value.
        */
        Stop2,

        /**
         * @brief Continue; return biggest return value.
        */
        Continue
    };

    enum class ForwardParam
    {
        /**
         * @brief Specify this as the last argument only tells the function that there are no more arguments.
        */
        Done = -1,

        /**
         * @brief Normal cell.
        */
        Cell,

        /**
         * @brief Float; used as normal cell though.
        */
        Float,

        /**
         * @brief String.
        */
        String,

        /**
         * @brief String; will be updated to the last function's value.
        */
        StringEx,

        /**
         * @brief Array; use the return value of prepareArray.
        */
        Array,

        /**
         * @brief Cell; pass by reference.
        */
        CellByRef,

        /**
         * @brief Float; pass by reference.
        */
        FloatByRef,
    };

    enum class PlayerProp
    {
        /**
         * @brief \c string
        */
        Name = 0,

        /**
         * @brief \c string
        */
        Ip,

        /**
         * @brief \c string
        */
        Team,

        /**
         * @brief \c bool
        */
        InGame,

        /**
         * @brief \c bool
        */
        Authorized,

        /**
         * @brief \c bool
        */
        Vgui,

        /**
         * @brief \c float
        */
        Time,

        /**
         * @brief \c float
        */
        PlayTime,

        /**
         * @brief \c float
        */
        MenuExpire,

        /**
         * @brief \c struct{int,int}[32]
        */
        Weapons,

        /**
         * @brief \c int
        */
        CurrentWeapon,

        /**
         * @brief \c int
        */
        TeamId,

        /**
         * @brief \c int
        */
        Deaths,

        /**
         * @brief \c int
        */
        Aiming,

        /**
         * @brief \c int
        */
        Menu,

        /**
         * @brief \c int
        */
        Keys,

        /**
         * @brief \c int[32]
        */
        Flags,

        /**
         * @brief \c int
        */
        NewMenu,

        /**
         * @brief \c int
        */
        NewMenuPage
    };

    enum class LibType
    {
        Library = 0,
        Class
    };

    struct ModuleInfo
    {
        /**
         * @brief N/D
        */
        const char* name{};

        /**
         * @brief N/D
        */
        const char* author{};

        /**
         * @brief N/D
        */
        const char* version{};

        /**
         * @brief Reload on map change when nonzero.
        */
        int reload{};

        /**
         * @brief N/D
        */
        const char* log_tag{};

        /**
         * @brief N/D
        */
        const char* library{};

        /**
         * @brief N/D
        */
        const char* lib_class{};
    };

    struct ApiFuncPointers
    {
        std::add_pointer_t<int(const AmxNativeInfo* list)> add_natives{};
        std::add_pointer_t<int(const AmxNativeInfo* list)> add_new_natives{};
        std::add_pointer_t<char*(const char* format, ...)> build_path_name{};
        std::add_pointer_t<char*(char* buffer, std::size_t max_len, const char* format, ...)> build_path_name_r{};
        std::add_pointer_t<cell*(Amx* amx, cell offset)> get_amx_address{};
        std::add_pointer_t<void(const char* format, ...)> print_console{};
        std::add_pointer_t<const char*()> get_mod_name{};
        std::add_pointer_t<const char*(int id)> get_amx_script_name{};
        std::add_pointer_t<Amx*(int id)> get_amx_script{};
        std::add_pointer_t<int(const Amx* amx)> find_amx_script_by_amx{};
        std::add_pointer_t<int(const char* name)> find_amx_script_by_name{};
        std::add_pointer_t<int(Amx* amx, cell amx_address, const char* source, int max)> set_amx_string{};
        std::add_pointer_t<char*(Amx* amx, cell amx_address, int buffer_id, int* len)> get_amx_string{};
        std::add_pointer_t<int(const cell* ptr)> get_amx_string_len{};
        std::add_pointer_t<char*(Amx* amx, cell* params, int start_param, int* len)> format_amx_string{};
        std::add_pointer_t<void(cell* dest, const cell* src, int len)> copy_amx_memory{};
        std::add_pointer_t<void(const char* format, ...)> log{};
        std::add_pointer_t<void(Amx* amx, AmxError error, const char* format, ...)> log_error{};
        std::add_pointer_t<int(Amx* amx, AmxError error)> raise_amx_error{};
        std::add_pointer_t<int(const char* func_name, ForwardExecType exec_type, ...)> register_forward{};
        std::add_pointer_t<int(int id, ...)> execute_forward{};
        std::add_pointer_t<cell(cell* ptr, std::size_t size)> prepare_cell_array{};
        std::add_pointer_t<cell(char* ptr, std::size_t size)> prepare_char_array{};
        std::add_pointer_t<cell(cell* ptr, std::size_t size, bool copy_back)> prepare_cell_array_a{};
        std::add_pointer_t<cell(char* ptr, std::size_t size, bool copy_back)> prepare_char_array_a{};
        std::add_pointer_t<int(int id)> is_player_valid{};
        std::add_pointer_t<const char*(int id)> get_player_name{};
        std::add_pointer_t<const char*(int id)> get_player_ip{};
        std::add_pointer_t<int(int id)> is_player_in_game{};
        std::add_pointer_t<int(int id)> is_player_bot{};
        std::add_pointer_t<int(int id)> is_player_authorized{};
        std::add_pointer_t<float(int id)> get_player_time{};
        std::add_pointer_t<float(int id)> get_player_play_time{};
        std::add_pointer_t<int(int id)> get_player_flags{};
        std::add_pointer_t<int(int id)> get_player_cur_weapon{};
        std::add_pointer_t<const char*(int id)> get_player_team{};
        std::add_pointer_t<int(int id)> get_player_team_id{};
        std::add_pointer_t<int(int id)> get_player_deaths{};
        std::add_pointer_t<int(int id)> get_player_menu{};
        std::add_pointer_t<int(int id)> get_player_keys{};
        std::add_pointer_t<int(int id)> is_player_alive{};
        std::add_pointer_t<int(int id)> get_player_frags{};
        std::add_pointer_t<int(int id)> is_player_connected{};
        std::add_pointer_t<int(int id)> is_player_hltv{};
        std::add_pointer_t<int(int id)> get_player_armor{};
        std::add_pointer_t<int(int id)> get_player_health{};
        std::add_pointer_t<cssdk::Edict*(int id)> get_player_edict{};
        std::add_pointer_t<void*(int id, PlayerProp prop)> player_prop_address{};
        std::add_pointer_t<int(Amx* amx, cell* return_val, int index)> amx_exec{};
        std::add_pointer_t<int(Amx* amx, cell* return_val, int index, int num_params, cell params[])> amx_exec_v{};
        std::add_pointer_t<int(Amx* amx, int length, cell* amx_address, cell** phys_address)> amx_allot{};
        std::add_pointer_t<int(Amx* amx, const char* func_name, int* index)> amx_find_public{};
        std::add_pointer_t<int(Amx* amx, const char* func_name, int* index)> amx_find_native{};
        std::add_pointer_t<int(Amx* amx, void** code, const char* path, char error_info[64], int debug)> load_amx_script{};
        std::add_pointer_t<int(Amx* amx, void** code)> unload_amx_script{};
        // std::add_pointer_t<cell(real value)> real_to_cell{};
        // std::add_pointer_t<real(cell value)> cell_to_real{};
        std::add_pointer_t<int(Amx* amx, int func, ...)> register_sp_forward{};
        std::add_pointer_t<int(Amx* amx, const char* func_name, ...)> register_sp_forward_by_name{};
        std::add_pointer_t<void(int id)> unregister_sp_forward{};
        std::add_pointer_t<void(const char* file_name)> merge_definition_file{};
        std::add_pointer_t<const char*(const char* format, ...)> format{};
        std::add_pointer_t<void(void* pfn, const char* desc)> register_function{};
        std::add_pointer_t<int(Amx* amx, cell value)> amx_push{};
        std::add_pointer_t<int(int player, int team_id, const char* name)> set_player_team_info{};
        std::add_pointer_t<void(std::add_pointer_t<void(int player, const char* auth_string)> authorize_func)>
            register_auth_func{};
        std::add_pointer_t<void(std::add_pointer_t<void(int player, const char* auth_string)> authorize_func)>
            unregister_auth_func{};
        std::add_pointer_t<int(const char* name, LibType type)> find_library{};
        std::add_pointer_t<std::size_t(const char* name, LibType type, void* parent)> add_libraries{};
        std::add_pointer_t<std::size_t(void* parent)> remove_libraries{};
        std::add_pointer_t<void(AmxNativeInfo* natives, const char* my_name)> override_natives{};
        std::add_pointer_t<const char*(const char* name, const char* def)> get_local_info{};
        std::add_pointer_t<int(Amx* amx, AmxNativeInfo* list, int number)> amx_re_register{};
        std::add_pointer_t<void*(void* pfn, const char* desc)> register_function_ex{};
        std::add_pointer_t<void(int mode, int message, int* opt)> message_block{};

#ifndef AMXX_182_COMPATIBILITY
        std::add_pointer_t<char*(Amx* amx, cell amx_address, int buffer_id, int* len)> get_amx_string_null{};
        std::add_pointer_t<cell*(Amx* amx, cell offset)> get_amx_vector_null{};
        std::add_pointer_t<GameConfigManager*()> get_config_manager{};
        std::add_pointer_t<int(Amx* amx, void** code, const char* path, char* error_info, std::size_t max_length, int debug)>
            load_amx_script_ex{};
        std::add_pointer_t<int(Amx* amx, cell amx_address, const cell* source, std::size_t source_len, std::size_t max_len)>
            set_amx_string_utf8_cell{};
        std::add_pointer_t<int(Amx* amx, cell amx_address, const char* source, std::size_t source_len, std::size_t max_len)>
            set_amx_string_utf8_char{};
#endif
    };

    namespace detail
    {
        inline ApiFuncPointers api_funcs{};
    }

    /**
     * @brief N/D
    */
    const char* FilenameFromPath(const char* path);

    /**
     * @brief N/D
    */
    inline int AddNatives(const AmxNativeInfo* list)
    {
        return detail::api_funcs.add_natives(list);
    }

    /**
     * @brief N/D
    */
    inline int AddNewNatives(const AmxNativeInfo* list)
    {
        return detail::api_funcs.add_new_natives(list);
    }

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    char* BuildPathName(const char* format, TArgs&&... args)
    {
        return detail::api_funcs.build_path_name(format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    char* BuildPathNameR(char* buffer, const std::size_t max_len, const char* format, TArgs&&... args)
    {
        return detail::api_funcs.build_path_name_r(buffer, max_len, format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    // inline cell* GetAmxAddress(Amx* amx, const cell offset)
    //{
    //	return detail::api_funcs.get_amx_address(amx, offset);
    //}

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    void PrintConsole(const char* format, TArgs&&... args)
    {
        detail::api_funcs.print_console(format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    inline const char* GetModName()
    {
        return detail::api_funcs.get_mod_name();
    }

    /**
     * @brief N/D
    */
    inline const char* GetAmxScriptName(const int id, const bool filename = false)
    {
        return filename
            ? FilenameFromPath(detail::api_funcs.get_amx_script_name(id))
            : detail::api_funcs.get_amx_script_name(id);
    }

    /**
     * @brief N/D
    */
    inline Amx* GetAmxScript(const int id)
    {
        return detail::api_funcs.get_amx_script(id);
    }

    /**
     * @brief N/D
    */
    inline int FindAmxScriptByAmx(const Amx* amx)
    {
        return detail::api_funcs.find_amx_script_by_amx(amx);
    }

    /**
     * @brief N/D
    */
    inline int FindAmxScriptByName(const char* name)
    {
        return detail::api_funcs.find_amx_script_by_name(name);
    }

    /**
     * @brief N/D
    */
    inline int SetAmxString(Amx* amx, const cell amx_address, const char* source, const int max)
    {
        return detail::api_funcs.set_amx_string(amx, amx_address, source, max);
    }

    /**
     * @brief N/D
    */
    inline char* GetAmxString(Amx* amx, const cell amx_address, const int buffer_id, int* len)
    {
        return detail::api_funcs.get_amx_string(amx, amx_address, buffer_id, len);
    }

    /**
     * @brief N/D
    */
    inline char* GetAmxString(Amx* amx, const cell amx_address, const int buffer_id = 0)
    {
        auto len = 0;
        return detail::api_funcs.get_amx_string(amx, amx_address, buffer_id, &len);
    }

    /**
     * @brief N/D
    */
    inline int GetAmxStringLen(const cell* ptr)
    {
        return detail::api_funcs.get_amx_string_len(ptr);
    }

    /**
     * @brief N/D
    */
    inline char* FormatAmxString(Amx* amx, cell* params, const int start_param, int* len)
    {
        return detail::api_funcs.format_amx_string(amx, params, start_param, len);
    }

    /**
     * @brief N/D
    */
    inline void CopyAmxMemory(cell* dest, const cell* src, const int len)
    {
        detail::api_funcs.copy_amx_memory(dest, src, len);
    }

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    void Log(const char* format, TArgs&&... args)
    {
        detail::api_funcs.log(format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    void LogError(Amx* amx, const AmxError error, const char* format, TArgs&&... args)
    {
        detail::api_funcs.log_error(amx, error, format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    inline int RaiseAmxError(Amx* amx, const AmxError error)
    {
        return detail::api_funcs.raise_amx_error(amx, error);
    }

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    int RegisterForward(const char* func_name, const ForwardExecType exec_type, TArgs&&... args)
    {
        return detail::api_funcs.register_forward(func_name, exec_type, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    int ExecuteForward(const int id, TArgs&&... args)
    {
        return detail::api_funcs.execute_forward(id, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    inline cell PrepareCellArray(cell* ptr, const std::size_t size)
    {
        return detail::api_funcs.prepare_cell_array(ptr, size);
    }

    /**
     * @brief N/D
    */
    inline cell PrepareCharArray(char* ptr, const std::size_t size)
    {
        return detail::api_funcs.prepare_char_array(ptr, size);
    }

    /**
     * @brief N/D
    */
    inline cell PrepareCellArrayA(cell* ptr, const std::size_t size, const bool copy_back)
    {
        return detail::api_funcs.prepare_cell_array_a(ptr, size, copy_back);
    }

    /**
     * @brief N/D
    */
    inline cell PrepareCharArrayA(char* ptr, const std::size_t size, const bool copy_back)
    {
        return detail::api_funcs.prepare_char_array_a(ptr, size, copy_back);
    }

    /**
     * @brief N/D
    */
    inline int IsPlayerValid(const int id)
    {
        return detail::api_funcs.is_player_valid(id);
    }

    /**
     * @brief N/D
    */
    inline const char* GetPlayerName(const int id)
    {
        return detail::api_funcs.get_player_name(id);
    }

    /**
     * @brief N/D
    */
    inline const char* GetPlayerIp(const int id)
    {
        return detail::api_funcs.get_player_ip(id);
    }

    /**
     * @brief N/D
    */
    inline int IsPlayerInGame(const int id)
    {
        return detail::api_funcs.is_player_in_game(id);
    }

    /**
     * @brief N/D
    */
    inline int IsPlayerBot(const int id)
    {
        return detail::api_funcs.is_player_bot(id);
    }

    /**
     * @brief N/D
    */
    inline int IsPlayerAuthorized(const int id)
    {
        return detail::api_funcs.is_player_authorized(id);
    }

    /**
     * @brief N/D
    */
    inline float GetPlayerTime(const int id)
    {
        return detail::api_funcs.get_player_time(id);
    }

    /**
     * @brief N/D
    */
    inline float GetPlayerPlayTime(const int id)
    {
        return detail::api_funcs.get_player_play_time(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerFlags(const int id)
    {
        return detail::api_funcs.get_player_flags(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerCurWeapon(const int id)
    {
        return detail::api_funcs.get_player_cur_weapon(id);
    }

    /**
     * @brief N/D
    */
    inline const char* GetPlayerTeam(const int id)
    {
        return detail::api_funcs.get_player_team(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerTeamId(const int id)
    {
        return detail::api_funcs.get_player_team_id(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerDeaths(const int id)
    {
        return detail::api_funcs.get_player_deaths(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerMenu(const int id)
    {
        return detail::api_funcs.get_player_menu(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerKeys(const int id)
    {
        return detail::api_funcs.get_player_keys(id);
    }

    /**
     * @brief N/D
    */
    inline int IsPlayerAlive(const int id)
    {
        return detail::api_funcs.is_player_alive(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerFrags(const int id)
    {
        return detail::api_funcs.get_player_frags(id);
    }

    /**
     * @brief N/D
    */
    inline int IsPlayerConnected(const int id)
    {
        return detail::api_funcs.is_player_connected(id);
    }

    /**
     * @brief N/D
    */
    inline int IsPlayerHltv(const int id)
    {
        return detail::api_funcs.is_player_hltv(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerArmor(const int id)
    {
        return detail::api_funcs.get_player_armor(id);
    }

    /**
     * @brief N/D
    */
    inline int GetPlayerHealth(const int id)
    {
        return detail::api_funcs.get_player_health(id);
    }

    /**
     * @brief N/D
    */
    inline cssdk::Edict* GetPlayerEdict(const int id)
    {
        return detail::api_funcs.get_player_edict(id);
    }

    /**
     * @brief N/D
    */
    inline void* PlayerPropAddress(const int id, const PlayerProp prop)
    {
        return detail::api_funcs.player_prop_address(id, prop);
    }

    /**
     * @brief N/D
    */
    inline int AmxExec(Amx* amx, cell* return_val, const int index)
    {
        return detail::api_funcs.amx_exec(amx, return_val, index);
    }

    /**
     * @brief N/D
    */
    inline int AmxExecV(Amx* amx, cell* return_val, const int index, const int num_params, cell params[])
    {
        return detail::api_funcs.amx_exec_v(amx, return_val, index, num_params, params);
    }

    /**
     * @brief N/D
    */
    inline int AmxAllot(Amx* amx, const int length, cell* amx_address, cell** phys_address)
    {
        return detail::api_funcs.amx_allot(amx, length, amx_address, phys_address);
    }

    /**
     * @brief N/D
    */
    inline int AmxFindPublic(Amx* amx, const char* func_name, int* index)
    {
        return detail::api_funcs.amx_find_public(amx, func_name, index);
    }

    /**
     * @brief N/D
    */
    inline int AmxFindNative(Amx* amx, const char* func_name, int* index)
    {
        return detail::api_funcs.amx_find_native(amx, func_name, index);
    }

    /**
     * @brief N/D
    */
    inline int LoadAmxScript(Amx* amx, void** code, const char* path, char error_info[64], const int debug)
    {
        return detail::api_funcs.load_amx_script(amx, code, path, error_info, debug);
    }

    /**
     * @brief N/D
    */
    inline int UnloadAmxScript(Amx* amx, void** code)
    {
        return detail::api_funcs.unload_amx_script(amx, code);
    }

    /**
     * @brief N/D
    */
    // inline cell RealToCell(const real value)
    //{
    //	return detail::api_funcs.real_to_cell(value);
    //}

    /**
     * @brief N/D
    */
    // inline real CellToReal(const cell value)
    //{
    //	return detail::api_funcs.cell_to_real(value);
    //}

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    int RegisterSpForward(Amx* amx, const int func, TArgs&&... args)
    {
        return detail::api_funcs.register_sp_forward(amx, func, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    int RegisterSpForwardByName(Amx* amx, const char* func_name, TArgs&&... args)
    {
        return detail::api_funcs.register_sp_forward_by_name(amx, func_name, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    inline void UnregisterSpForward(const int id)
    {
        detail::api_funcs.unregister_sp_forward(id);
    }

    /**
     * @brief N/D
    */
    inline void MergeDefinitionFile(const char* file_name)
    {
        detail::api_funcs.merge_definition_file(file_name);
    }

    /**
     * @brief N/D
    */
    template <typename... TArgs>
    const char* Format(const char* format, TArgs&&... args)
    {
        return detail::api_funcs.format(format, std::forward<TArgs>(args)...);
    }

    /**
     * @brief N/D
    */
    inline void RegisterFunction(void* pfn, const char* desc)
    {
        detail::api_funcs.register_function(pfn, desc);
    }

    /**
     * @brief N/D
    */
    inline int AmxPush(Amx* amx, const cell value)
    {
        return detail::api_funcs.amx_push(amx, value);
    }

    /**
     * @brief N/D
    */
    inline int SetPlayerTeamInfo(const int player, const int team_id, const char* name)
    {
        return detail::api_funcs.set_player_team_info(player, team_id, name);
    }

    /**
     * @brief N/D
    */
    inline void RegisterAuthFunc(const std::add_pointer_t<void(int, const char*)> authorize_func)
    {
        detail::api_funcs.register_auth_func(authorize_func);
    }

    /**
     * @brief N/D
    */
    inline void UnregisterAuthFunc(const std::add_pointer_t<void(int, const char*)> authorize_func)
    {
        detail::api_funcs.unregister_auth_func(authorize_func);
    }

    /**
     * @brief N/D
    */
    inline int FindLibrary(const char* name, const LibType type)
    {
        return detail::api_funcs.find_library(name, type);
    }

    /**
     * @brief N/D
    */
    inline std::size_t AddLibraries(const char* name, const LibType type, void* parent)
    {
        return detail::api_funcs.add_libraries(name, type, parent);
    }

    /**
     * @brief N/D
    */
    inline std::size_t RemoveLibraries(void* parent)
    {
        return detail::api_funcs.remove_libraries(parent);
    }

    /**
     * @brief N/D
    */
    inline void OverrideNatives(AmxNativeInfo* natives, const char* my_name)
    {
        detail::api_funcs.override_natives(natives, my_name);
    }

    /**
     * @brief N/D
    */
    inline const char* GetLocalInfo(const char* name, const char* def)
    {
        return detail::api_funcs.get_local_info(name, def);
    }

    /**
     * @brief N/D
    */
    inline int AmxReRegister(Amx* amx, AmxNativeInfo* list, const int number)
    {
        return detail::api_funcs.amx_re_register(amx, list, number);
    }

    /**
     * @brief N/D
    */
    inline void* RegisterFunctionEx(void* pfn, const char* desc)
    {
        return detail::api_funcs.register_function_ex(pfn, desc);
    }

    /**
     * @brief N/D
    */
    inline void MessageBlock(const int mode, const int message, int* opt)
    {
        detail::api_funcs.message_block(mode, message, opt);
    }

    /**
     * @brief N/D
    */
    constexpr int ReadFlags(const char* string)
    {
        auto flags = 0;

        while (*string) {
            flags |= 1 << (*string++ - 'a');
        }

        return flags;
    }

#ifndef AMXX_182_COMPATIBILITY
    /**
     * @brief N/D
    */
    inline char* GetAmxStringNull(Amx* amx, const cell amx_address, const int buffer_id, int* len)
    {
        return detail::api_funcs.get_amx_string_null(amx, amx_address, buffer_id, len);
    }

    /**
     * @brief N/D
    */
    inline cell* GetAmxVectorNull(Amx* amx, const cell offset)
    {
        return detail::api_funcs.get_amx_vector_null(amx, offset);
    }

    /**
     * @brief N/D
    */
    inline GameConfigManager* GetConfigManager()
    {
        return detail::api_funcs.get_config_manager();
    }

    /**
     * @brief N/D
    */
    inline int LoadAmxScriptEx(Amx* amx, void** code, const char* path, char* error_info, const std::size_t max_length,
                               const int debug)
    {
        return detail::api_funcs.load_amx_script_ex(amx, code, path, error_info, max_length, debug);
    }

    /**
     * @brief N/D
    */
    inline int SetAmxStringUtf8Cell(Amx* amx, const cell amx_address, const cell* source, const std::size_t source_len,
                                    const std::size_t max_len)
    {
        return detail::api_funcs.set_amx_string_utf8_cell(amx, amx_address, source, source_len, max_len);
    }

    /**
     * @brief N/D
    */
    inline int SetAmxStringUtf8Char(Amx* amx, const cell amx_address, const char* source, const std::size_t source_len,
                                    const std::size_t max_len)
    {
        return detail::api_funcs.set_amx_string_utf8_char(amx, amx_address, source, source_len, max_len);
    }
#endif
}

#ifdef AMXX_QUERY
void AMXX_QUERY();
#endif

#ifdef AMXX_CHECK_GAME
amxx::GameStatus AMXX_CHECK_GAME(const char* game);
#endif

#ifdef AMXX_ATTACH
amxx::Status AMXX_ATTACH();
#endif

#ifdef AMXX_DETACH
void AMXX_DETACH();
#endif

#ifdef AMXX_PLUGINS_LOADED
void AMXX_PLUGINS_LOADED();
#endif

#ifdef AMXX_PLUGINS_UNLOADED
void AMXX_PLUGINS_UNLOADED();
#endif

#ifdef AMXX_PLUGINS_UNLOADING
void AMXX_PLUGINS_UNLOADING();
#endif

using AmxxStatus = amxx::Status;
using AmxxGameStatus = amxx::GameStatus;
using AmxxForwardExecType = amxx::ForwardExecType;
using AmxxForwardParam = amxx::ForwardParam;
using AmxxPlayerProp = amxx::PlayerProp;
using AmxxLibType = amxx::LibType;
using AmxxModuleInfo = amxx::ModuleInfo;
