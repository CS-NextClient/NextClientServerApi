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
#include <cssdk/public/os_defs.h>
#else
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
#undef INTEL_COMPILER
#undef CLANG_COMPILER

#undef DLLEXPORT
#undef NOINLINE
#undef INLINE_STATIC
#undef FORCE_STACK_ALIGN
#undef LIKELY
#undef UNLIKELY
#undef AT_LOADED
#undef ATTR_MINSIZE
#undef ATTR_MINSIZE_INLINE
#undef ATTR_OPTIMIZE
#undef ATTR_OPTIMIZE_INLINE
#undef ATTR_OPTIMIZE_HOT
#undef ATTR_OPTIMIZE_HOT_INLINE

#ifdef _MSC_VER
#define MSVC_COMPILER
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
#elif defined(CLANG_COMPILER)
#define DLLEXPORT __attribute__((visibility("default")))
#elif defined(GCC_COMPILER) || defined(INTEL_COMPILER)
#define DLLEXPORT __attribute__((visibility("default"), externally_visible))
#endif

// NOINLINE
#ifdef MSVC_COMPILER
#define NOINLINE __declspec(noinline)
#elif defined(GCC_COMPILER) || defined(INTEL_COMPILER) || defined(CLANG_COMPILER)
#define NOINLINE __attribute__((noinline))
#endif

// INLINE_STATIC
#ifdef MSVC_COMPILER
#define INLINE_STATIC FORCEINLINE static
#elif defined(GCC_COMPILER) || defined(INTEL_COMPILER) || defined(CLANG_COMPILER)
#undef FORCEINLINE
#define FORCEINLINE __attribute__((always_inline)) inline
#define INLINE_STATIC __attribute__((always_inline)) static inline
#endif

// FORCE_STACK_ALIGN
#ifdef MSVC_COMPILER
#define FORCE_STACK_ALIGN
#elif defined(GCC_COMPILER) || defined(INTEL_COMPILER) || defined(CLANG_COMPILER)
#define FORCE_STACK_ALIGN __attribute__((force_align_arg_pointer))
#endif

// LIKELY UNLIKELY
#ifdef MSVC_COMPILER
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#elif defined(GCC_COMPILER) || defined(INTEL_COMPILER) || defined(CLANG_COMPILER)
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

// AT_LOADED
#ifdef MSVC_COMPILER
#define AT_LOADED(f)                                                                                                           \
    static void f(void);                                                                                                       \
    struct f##_t_                                                                                                              \
    {                                                                                                                          \
        f##_t_(void)                                                                                                           \
        {                                                                                                                      \
            f();                                                                                                               \
        }                                                                                                                      \
    };                                                                                                                         \
    static f##_t_ f##_;                                                                                                        \
    static void f(void)
#elif defined(GCC_COMPILER) || defined(INTEL_COMPILER) || defined(CLANG_COMPILER)
#define AT_LOADED(f)                                                                                                           \
    __attribute__((constructor, used)) static void f(void);                                                                    \
    static void f(void)
#endif

#ifdef NDEBUG
// ATTR_MINSIZE
#ifdef GCC_COMPILER
#define ATTR_MINSIZE [[gnu::optimize("-Os")]]
#elif defined(CLANG_COMPILER)
#define ATTR_MINSIZE [[clang::minsize]]
#else
#define ATTR_MINSIZE
#endif

// ATTR_MINSIZE_INLINE
#ifdef GCC_COMPILER
#define ATTR_MINSIZE_INLINE [[gnu::always_inline, gnu::optimize("-Os")]]
#elif defined(CLANG_COMPILER)
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
#define ATTR_MINSIZE
#define ATTR_MINSIZE_INLINE
#define ATTR_OPTIMIZE
#define ATTR_OPTIMIZE_INLINE
#define ATTR_OPTIMIZE_HOT
#define ATTR_OPTIMIZE_HOT_INLINE
#endif
#endif
