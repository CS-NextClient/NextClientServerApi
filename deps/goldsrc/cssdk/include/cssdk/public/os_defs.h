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

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif !defined(WINAPI)
#define WINAPI
#endif

#ifndef _WIN32
#include <climits>
constexpr auto MAX_PATH = PATH_MAX;
#endif

#undef MSVC_COMPILER
#undef GCC_COMPILER
#undef CLANG_COMPILER
#undef INTEL_COMPILER
#undef INTEL_LLVM_COMPILER

#undef DLLEXPORT
#undef NOINLINE
#undef INLINE_STATIC
#undef FORCE_STACK_ALIGN
#undef LIKELY
#undef UNLIKELY
#undef AT_LOADED
#undef ATTR_CONST
#undef ATTR_MINSIZE
#undef ATTR_MINSIZE_INLINE
#undef ATTR_OPTIMIZE
#undef ATTR_OPTIMIZE_INLINE
#undef ATTR_OPTIMIZE_HOT
#undef ATTR_OPTIMIZE_HOT_INLINE

#ifdef _MSC_VER
#define MSVC_COMPILER
#elif defined(__INTEL_LLVM_COMPILER)
#define INTEL_LLVM_COMPILER
#elif defined(__INTEL_COMPILER)
#define INTEL_COMPILER
#elif !defined(__llvm__) && (defined(__GNUC__) || defined(__GNUG__))
#define GCC_COMPILER // probably
#elif defined(__clang__) && defined(__llvm__)
#define CLANG_COMPILER // probably
#endif

// DLLEXPORT
#ifdef MSVC_COMPILER
#define DLLEXPORT __declspec(dllexport)
#elif defined(CLANG_COMPILER) || defined(INTEL_LLVM_COMPILER)
#define DLLEXPORT __attribute__((visibility("default")))
#elif defined(GCC_COMPILER) || defined(INTEL_COMPILER)
#define DLLEXPORT __attribute__((visibility("default"), externally_visible))
#endif

// NOINLINE
#ifdef MSVC_COMPILER
#define NOINLINE __declspec(noinline)
#elif defined(GCC_COMPILER) || defined(CLANG_COMPILER) || defined(INTEL_COMPILER) || defined(INTEL_LLVM_COMPILER)
#define NOINLINE __attribute__((noinline))
#endif

// INLINE_STATIC
#ifdef MSVC_COMPILER
#define INLINE_STATIC FORCEINLINE static
#elif defined(GCC_COMPILER) || defined(CLANG_COMPILER) || defined(INTEL_COMPILER) || defined(INTEL_LLVM_COMPILER)
#undef FORCEINLINE
#define FORCEINLINE __attribute__((always_inline)) inline
#define INLINE_STATIC __attribute__((always_inline)) static inline
#endif

// FORCE_STACK_ALIGN
#ifdef MSVC_COMPILER
#define FORCE_STACK_ALIGN
#elif defined(GCC_COMPILER) || defined(CLANG_COMPILER) || defined(INTEL_COMPILER) || defined(INTEL_LLVM_COMPILER)
#define FORCE_STACK_ALIGN __attribute__((force_align_arg_pointer))
#endif

// LIKELY UNLIKELY
#ifdef MSVC_COMPILER
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#elif defined(GCC_COMPILER) || defined(CLANG_COMPILER) || defined(INTEL_COMPILER) || defined(INTEL_LLVM_COMPILER)
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

// AT_LOADED
#ifdef MSVC_COMPILER
#define AT_LOADED(f)     \
    static void f(void); \
    struct f##_t_        \
    {                    \
        f##_t_(void)     \
        {                \
            f();         \
        }                \
    };                   \
    static f##_t_ f##_;  \
    static void f(void)
#elif defined(GCC_COMPILER) || defined(CLANG_COMPILER) || defined(INTEL_COMPILER) || defined(INTEL_LLVM_COMPILER)
#define AT_LOADED(f)                                        \
    __attribute__((constructor, used)) static void f(void); \
    static void f(void)
#endif

#ifdef NDEBUG
// ATTR_CONST
#ifndef _MSC_VER
#define ATTR_CONST [[gnu::const]]
#else
#define ATTR_CONST
#endif

// ATTR_MINSIZE
#ifdef GCC_COMPILER
#define ATTR_MINSIZE [[gnu::optimize("-Os")]]
#elif defined(CLANG_COMPILER) || defined(INTEL_LLVM_COMPILER)
#define ATTR_MINSIZE [[clang::minsize]]
#else
#define ATTR_MINSIZE
#endif

// ATTR_MINSIZE_INLINE
#ifdef GCC_COMPILER
#define ATTR_MINSIZE_INLINE [[gnu::always_inline, gnu::optimize("-Os")]]
#elif defined(CLANG_COMPILER) || defined(INTEL_LLVM_COMPILER)
#define ATTR_MINSIZE_INLINE [[gnu::always_inline, clang::minsize]]
#elif !defined(MSVC_COMPILER)
#define ATTR_MINSIZE_INLINE [[gnu::always_inline]]
#else
#define ATTR_MINSIZE_INLINE FORCEINLINE
#endif

// ATTR_OPTIMIZE
#ifdef GCC_COMPILER
#define ATTR_OPTIMIZE [[gnu::optimize("-O3")]]
#else
#define ATTR_OPTIMIZE
#endif

// ATTR_OPTIMIZE_INLINE
#ifdef GCC_COMPILER
#define ATTR_OPTIMIZE_INLINE [[gnu::always_inline, gnu::optimize("-O3")]]
#elif !defined(MSVC_COMPILER)
#define ATTR_OPTIMIZE_INLINE [[gnu::always_inline]]
#else
#define ATTR_OPTIMIZE_INLINE FORCEINLINE
#endif

// ATTR_OPTIMIZE_HOT
#ifdef GCC_COMPILER
#define ATTR_OPTIMIZE_HOT [[gnu::optimize("-O3"), gnu::hot]]
#elif !defined(MSVC_COMPILER)
#define ATTR_OPTIMIZE_HOT [[gnu::hot]]
#else
#define ATTR_OPTIMIZE_HOT
#endif

// ATTR_OPTIMIZE_HOT_INLINE
#ifdef GCC_COMPILER
#define ATTR_OPTIMIZE_HOT_INLINE [[gnu::always_inline, gnu::optimize("-O3"), gnu::hot]]
#elif !defined(MSVC_COMPILER)
#define ATTR_OPTIMIZE_HOT_INLINE [[gnu::always_inline, gnu::hot]]
#else
#define ATTR_OPTIMIZE_HOT_INLINE FORCEINLINE
#endif
#else
#define ATTR_CONST
#define ATTR_MINSIZE
#define ATTR_MINSIZE_INLINE
#define ATTR_OPTIMIZE
#define ATTR_OPTIMIZE_INLINE
#define ATTR_OPTIMIZE_HOT
#define ATTR_OPTIMIZE_HOT_INLINE
#endif
