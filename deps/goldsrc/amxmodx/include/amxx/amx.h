/*
 *  Copyright (C) 2020 ITB CompuPhase, 1997-2005.
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

#include <cstddef>
#include <cstdint>
#include <string>

//-V::122

#if !defined AMX_NATIVE_CALL
#define AMX_NATIVE_CALL
#endif

#if !defined AMXAPI
#if defined STDECL
#define AMXAPI __stdcall
#elif defined CDECL
#define AMXAPI __cdecl
#else
#define AMXAPI
#endif
#endif

#if !defined PAWN_CELL_SIZE
#define PAWN_CELL_SIZE 32 // NOLINT(cppcoreguidelines-macro-usage)
#endif

#if PAWN_CELL_SIZE == 32
using cell = int32_t;
using ucell = uint32_t;
using real = float;
#elif PAWN_CELL_SIZE == 64
using cell = uint64_t;
using ucell = uint64_t;
using real = double;
#else
#error Unsupported cell size (PAWN_CELL_SIZE)
#endif

#if !defined _FAR
// ReSharper disable once CppInconsistentNaming
// NOLINTNEXTLINE(bugprone-reserved-identifier, clang-diagnostic-reserved-id-macro, clang-diagnostic-reserved-macro-identifier)
#define _FAR
#endif

/*
 * File format version							Required AMX version
 *	0 (original version)						0
 *	1 (opcodes JUMP.pri, SWITCH and CASETBL)	1
 *	2 (compressed files)						2
 *	3 (public variables)						2
 *	4 (opcodes SWAP.pri/alt and PUSHADDR)		4
 *	5 (tagnames table)							4
 *	6 (reformatted header)						6
 *	7 (name table, opcodes SYMTAG & SYSREQ.D)	7
 *	8 (opcode STMT, renewed debug interface)	8
 */

/**
 * @brief Current file version; also the current AMX version.
*/
constexpr auto CUR_FILE_VERSION = 8;

/**
 * @brief Lowest supported file format version for the current AMX version.
*/
constexpr auto MIN_FILE_VERSION = 6;

/**
 * @brief Minimum AMX version needed to support the current file format.
*/
constexpr auto MIN_AMX_VERSION = 8;

/**
 * @brief 0xF1E0 for a 32-bit cell;
 * 0xF1E1 for a 64-bit cell;
 * 0xF1E2 for a 16-bit cell.
*/
constexpr auto AMX_MAGIC = 0xF1E0;

/**
 * @brief Symbolic info available.
*/
constexpr auto AMX_FLAG_DEBUG = 0x02;

/**
 * @brief Compact encoding.
*/
constexpr auto AMX_FLAG_COMPACT = 0x04;

/**
 * @brief Opcode is a byte (not a cell).
*/
constexpr auto AMX_FLAG_BYTE_OPC = 0x08;

/**
 * @brief no array bounds checking; no STMT opcode.
*/
constexpr auto AMX_FLAG_NO_CHECKS = 0x10;

/**
 * @brief All native functions are registered.
*/
constexpr auto AMX_FLAG_NTV_REG = 0x1000;

/**
 * @brief Abstract machine is JIT compiled.
*/
constexpr auto AMX_FLAG_JIT_C = 0x2000;

/**
 * @brief Busy browsing.
*/
constexpr auto AMX_FLAG_BROWSE = 0x4000;

/**
 * @brief Jump/call addresses relocated.
*/
constexpr auto AMX_FLAG_RELOC = 0x8000;

/**
 * @brief Start at program entry point.
*/
constexpr auto AMX_EXEC_MAIN = -1;

/**
 * @brief Continue from last address.
*/
constexpr auto AMX_EXEC_CONT = -2;

/**
 * @brief N/D
*/
constexpr auto AMX_USER_NUM = 4;

/**
 * @brief Maximum name length for file version <= 6.
*/
constexpr auto AMX_EXP_MAX = 19;

/**
 * @brief Maximum name length of symbol name.
*/
constexpr auto AMX_NAME_MAX = 63;

enum class AmxError
{
    None = 0,

    //
    // Reserve the first 15 error codes for exit codes of the abstract machine.
    //

    /**
     * @brief Forced exit.
    */
    Exit,

    /**
     * @brief Assertion failed.
    */
    Assert,

    /**
     * @brief Stack/heap collision.
    */
    StackErr,

    /**
     * @brief Index out of bounds.
    */
    Bounds,

    /**
     * @brief Invalid memory access.
    */
    MemAccess,

    /**
     * @brief Invalid instruction.
    */
    InvalidInstr,

    /**
     * @brief Stack underflow.
    */
    StackLow,

    /**
     * @brief Heap underflow.
    */
    HeapLow,

    /**
     * @brief No callback, or invalid callback.
    */
    Callback,

    /**
     * @brief Native function failed.
    */
    Native,

    /**
     * @brief Divide by zero.
    */
    Divide,

    /**
     * @brief Go into sleep mode - code can be restarted.
    */
    Sleep,

    /**
     * @brief Invalid state for this access.
    */
    InvalidState,

    /**
     * @brief Out of memory.
    */
    Memory = 16,

    /**
     * @brief Invalid file format.
    */
    Format,

    /**
     * @brief File is for a newer version of the AMX.
    */
    Version,

    /**
     * @brief Function not found.
    */
    NotFound,

    /**
     * @brief Invalid index parameter (bad entry point).
    */
    Index,

    /**
     * @brief Debugger cannot run.
    */
    Debug,

    /**
     * @brief AMX not initialized (or doubly initialized).
    */
    Init,

    /**
     * @brief Unable to set user data field (table full).
    */
    UserData,

    /**
     * @brief Cannot initialize the JIT.
    */
    InitJit,

    /**
     * @brief Parameter error.
    */
    Params,

    /**
     * @brief Domain error, expression result does not fit in range.
    */
    Domain,

    /**
     * @brief General error (unknown or unspecific error).
    */
    General
};

struct Amx;
using AmxDebug = int(AMXAPI*)(Amx* amx);
using AmxNative = cell(AMX_NATIVE_CALL*)(Amx* amx, cell* params);
using AmxCallback = int(AMXAPI*)(Amx* amx, cell index, cell* result, cell* params);

/*
 * Some compilers do not support the #pragma align, which should be fine. Some
 * compilers give a warning on unknown #pragmas, which is not so fine...
 */
#if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
#define AMX_NO_ALIGN
#endif

#ifdef _MSC_VER
#define PACKED
#else
#define PACKED __attribute__((packed))
#endif

#ifndef AMX_NO_ALIGN
#if defined __LINUX__ || defined __FreeBSD__ || defined __APPLE__
#pragma pack(1) /* structures must be packed (byte-aligned) */
#elif defined MACOS && defined __MWERKS__
#pragma options align = mac68k
#else
#pragma pack(push)
#pragma pack(1) /* structures must be packed (byte-aligned) */
#endif
#endif

struct AmxNativeInfo
{
    const char _FAR* name PACKED;
    AmxNative func PACKED;
} PACKED;

struct AmxFuncStub
{
    ucell address PACKED;
    char name[AMX_EXP_MAX + 1];
} PACKED;

struct AmxFuncStubNt
{
    ucell address PACKED;

    /**
     * @brief We need this for amxx to be backwards compatible.
    */
    ucell name_offset PACKED;
} PACKED;

/**
 * @brief The AmxHeader structure is both the memory format as the file format.
 * The structure is used internaly.
*/
struct AmxHeader
{
    /**
     * @brief Size of the memory image, excluding the stack and heap.
    */
    std::int32_t size PACKED;

    /**
     * @brief Indicates the format and cell size.
    */
    std::uint16_t magic PACKED;

    /**
     * @brief File format version.
    */
    std::byte file_version;

    /**
     * @brief Required minimal version of the abstract machine.
    */
    std::byte amx_version;

    /**
     * @brief Flags.
    */
    std::int16_t flags PACKED;

    /**
     * @brief Size of a structure in the "native functions" and the "public functions" tables.
    */
    std::int16_t definition_size PACKED;

    /**
     * @brief Offset to the start of the code section.
    */
    std::int32_t cod PACKED;

    /**
     * @brief Offset to the start of the data section.
    */
    std::int32_t dat PACKED;

    /**
     * @brief Initial value of the heap, end of the data section.
    */
    std::int32_t hea PACKED;

    /**
     * @brief Stack top value (the total memory requirements).
    */
    std::int32_t stp PACKED;

    /**
     * @brief Starting address (main() function), -1 if none.
    */
    std::int32_t cip PACKED;

    /**
     * @brief Offset to the "public functions" table.
    */
    std::int32_t publics PACKED;

    /**
     * @brief Offset to the "native functions" table.
    */
    std::int32_t natives PACKED;

    /**
     * @brief Offset to the table of libraries.
    */
    std::int32_t libraries PACKED;

    /**
     * @brief Offset to the "public variables" table.
    */
    std::int32_t public_vars PACKED;

    /**
     * @brief Offset to the "public tags" table.
    */
    std::int32_t tags PACKED;

    /**
     * @brief Offset to the symbol name table.
    */
    std::int32_t name_table PACKED;
} PACKED;

/**
 * @brief The AMX structure is the internal structure for many functions.
 * Not all fields are valid at all times; many fields are cached in local variables.
*/
struct Amx
{
    /**
     * @brief Points to the AMX header plus the code, optionally also the data.
    */
    unsigned char _FAR* base PACKED;

    /**
     * @brief Points to separate data + stack + heap, may be NULL.
    */
    unsigned char _FAR* data PACKED;

    /**
     * @brief N/D
    */
    AmxCallback callback PACKED;

    /**
     * @brief Debug callback.
    */
    AmxDebug debug PACKED;

    //
    // For external functions a few registers must be accessible from the outside.
    //

    /**
     * @brief Instruction pointer: relative to base + AmxHeader->cod.
    */
    cell cip PACKED;

    /**
     * @brief Stack frame base: relative to base + AmxHeader->dat.
    */
    cell frm PACKED;

    /**
     * @brief Top of the heap: relative to base + AmxHeader->dat.
    */
    cell hea PACKED;

    /**
     * @brief Bottom of the heap: relative to base + AmxHeader->dat.
    */
    cell hlw PACKED;

    /**
     * @brief Stack pointer: relative to base + AmxHeader->dat.
    */
    cell stk PACKED;

    /**
     * @brief Top of the stack: relative to base + AmxHeader->dat.
    */
    cell stp PACKED;

    /**
     * @brief Current status.
    */
    int flags PACKED;

    //
    // User data.
    //

    /**
     * @brief N/D
    */
    long user_tags[AMX_USER_NUM] PACKED; //-V126

    /**
     * @brief N/D
    */
    void _FAR* user_data[AMX_USER_NUM] PACKED;

    //
    // Native functions can raise an error.
    //

    /**
     * @brief N/D
    */
    int error PACKED;

    //
    // Passing parameters requires a "count" field.
    //

    /**
     * @brief N/D
    */
    int param_count;

    //
    // The sleep opcode needs to store the full AMX status.
    //

    /**
     * @brief N/D
    */
    cell pri PACKED;

    /**
     * @brief N/D
    */
    cell alt PACKED;

    /**
     * @brief N/D
    */
    cell reset_stk PACKED;

    /**
     * @brief N/D
    */
    cell reset_hea PACKED;

    /**
     * @brief Relocated address/value for the SYSREQ.D opcode.
    */
    cell sysreq_d PACKED;

    //
    // Support variables for the JIT.
    //

    /**
     * @brief Required temporary buffer for relocations.
    */
    int reloc_size PACKED;

    /**
     * @brief Estimated memory footprint of the native code.
    */
    long code_size PACKED; //-V126
} PACKED;

#ifndef AMX_NO_ALIGN
#if defined __LINUX__ || defined __FreeBSD__ || defined __APPLE__
#pragma pack() /* reset previous packing */
#elif defined MACOS && defined __MWERKS__
#pragma options align = reset
#else
#pragma pack(pop) /* reset previous packing */
#endif
#endif

namespace amx
{
    /**
     * @brief Real to cell.
    */
    inline cell FloatToCell(const real& value)
    {
        // cppcheck-suppress invalidPointerCast
        return *reinterpret_cast<const cell*>(&value); // NOLINT(clang-diagnostic-undefined-reinterpret-cast)
    }

    /**
     * @brief Cell to real.
    */
    inline real CellToFloat(const cell& value)
    {
        // cppcheck-suppress invalidPointerCast
        return *reinterpret_cast<const real*>(&value); // NOLINT(clang-diagnostic-undefined-reinterpret-cast)
    }

    /**
     * @brief N/D
    */
    inline cell* Address(const Amx* amx, const ucell address)
    {
        //-V:address:104, 206
        return reinterpret_cast<cell*>( // cppcheck-suppress invalidPointerCast
            amx->base + reinterpret_cast<const AmxHeader*>(amx->base)->dat + address);
    }

    /**
     * @brief N/D
    */
    inline std::size_t GetStringLen(const cell* const address)
    {
        std::size_t length{0};

        while (address[length]) {
            ++length;
        }

        return length;
    }

    /**
     * @brief N/D
    */
    inline std::size_t GetStringLen(const Amx* const amx, const cell address)
    {
        return GetStringLen(Address(amx, address));
    }

    /**
     * @brief N/D
    */
    inline std::string GetString(const cell* const address)
    {
        std::string string{};

        if (const auto length = GetStringLen(address)) {
            string.resize(length);

            for (std::size_t i = 0; i < length; ++i) {
                string[i] = static_cast<std::string::value_type>(address[i]);
            }
        }

        return string;
    }

    /**
     * @brief N/D
    */
    inline std::string GetString(const Amx* const amx, const cell address)
    {
        return GetString(Address(amx, address));
    }
}
