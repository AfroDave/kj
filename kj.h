/*
 * `kj.h`
 *
 * ---------------------------------- LICENSE ----------------------------------
 * This software is in the public domain.  Where that dedication is not
 * recognized, you are granted a perpetual, irrevocable license to copy,
 * distribute, and modify the source code as you see fit.
 *
 * The source code is provided "as is", without warranty of any kind, express
 * or implied. No attribution is required, but always appreciated.
 * =============================================================================
 *
 * usage:
 *      #define KJ_IMPL
 *     #include "kj.h"
 */

#ifndef KJ_H
#define KJ_H

#define KJ_VERSION_MAJOR 0
#define KJ_VERSION_MINOR 11
#define KJ_VERSION_PATCH 0

#if defined(__cplusplus)
#define KJ_EXTERN_BEGIN extern "C" {
#define KJ_EXTERN_END }
#else
#define KJ_EXTERN_BEGIN
#define KJ_EXTERN_END
#endif

KJ_EXTERN_BEGIN

#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_X86
#define KJ_ARCH_NAME "x86_64"
#elif defined(__i386__) || defined(_M_IX86) || defined(_X86_)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_X86
#define KJ_ARCH_NAME "x86"
#elif defined(__aarch64__)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_ARM
#define KJ_ARCH_NAME "arm64"
#elif defined(__arm__) || defined(_M_ARM)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_ARM
#define KJ_ARCH_NAME "arm"
#elif defined(__mips__)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_MIPS
#define KJ_ARCH_NAME "mips"
#else
#error "Unsupported Architecture"
#endif

#if defined(_WIN32) || defined(_WIN64)
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#if !defined(VC_EXTRALEAN)
#define VC_EXTRALEAN
#endif
#if !defined(UNICODE)
#define UNICODE
#endif
#include <windows.h>
#include <stdio.h>
#define KJ_SYS_WIN32
#define KJ_SYS_NAME "windows"
#define KJ_SYS_DLL_EXT "dll"
#define KJ_SYS_EXE_EXT "exe"
#pragma comment(lib, "kernel32.lib")
#elif defined(__unix__)
#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#if !defined(_LARGEFILE64_SOURCE)
#define _LARGEFILE64_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#if defined(__linux__)
#define KJ_SYS_LINUX
#define KJ_SYS_NAME "linux"
#else
#define KJ_SYS_NAME "unix"
#endif
#define KJ_SYS_DLL_EXT "so"
#define KJ_SYS_EXE_EXT ""
#define KJ_SYS_UNIX
#else
#error "Unsupported Operating System"
#endif

#if !defined(kj_str_of)
#define kj_str_of(a) #a
#endif

#if defined(_MSC_VER)
#define KJ_COMPILER_MSVC
#define KJ_WARNING_DISABLE_BEGIN __pragma(warning(push))
#define KJ_WARNING_DISABLE_END __pragma(warning(pop))
#define KJ_WARNING_DISABLE_ANONYMOUS_STRUCT __pragma(warning(disable:4201))
#define KJ_WARNING_DISABLE_DEPRECATED __pragma(warning(disable:4996))
#define KJ_WARNING_DISABLE_LOSS_OF_DATA __pragma(warning(disable:4244))
#define KJ_WARNING_DISABLE_MISSING_BRACES
#define KJ_WARNING_DISABLE_VARIADIC_MACROS
#define KJ_WARNING_DISABLE_ZERO_SIZED_ARRAY __pragma(warning(disable:4200))
#define KJ_WARNING_DISABLE_STRICT_ALIASING
#elif defined(__clang__)
#ifndef va_start
typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif
#define KJ_COMPILER_CLANG
#define KJ_WARNING_DISABLE_BEGIN _Pragma("clang diagnostic push")
#define KJ_WARNING_DISABLE_END _Pragma("clang diagnostic pop")
#define KJ_WARNING_DISABLE_ANONYMOUS_STRUCT                                     \
    _Pragma("clang diagnostic ignored \"-Wc11-extensions\"")                    \
    _Pragma("clang diagnostic ignored \"-Wgnu-anonymous-struct\"")              \
    _Pragma("clang diagnostic ignored \"-Wnested-anon-types\"")
#define KJ_WARNING_DISABLE_DEPRECATED
#define KJ_WARNING_DISABLE_LOSS_OF_DATA
#define KJ_WARNING_DISABLE_MISSING_BRACES                                       \
    _Pragma("clang diagnostic ignored \"-Wmissing-braces\"")
#define KJ_WARNING_DISABLE_VARIADIC_MACROS                                      \
    _Pragma("clang diagnostic ignored \"-Wvariadic-macros\"")
#define KJ_WARNING_DISABLE_ZERO_SIZED_ARRAY                                     \
    _Pragma("clang diagnostic ignored \"-Wzero-length-array\"")
#define KJ_WARNING_DISABLE_STRICT_ALIASING
#elif defined(__GNUC__) || defined(__GNUG__)
#ifndef va_start
typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif
#define KJ_COMPILER_GNU
#define KJ_WARNING_DISABLE_BEGIN _Pragma("GCC diagnostic push")
#define KJ_WARNING_DISABLE_END _Pragma("GCC diagnostic pop")
#define KJ_WARNING_DISABLE_ANONYMOUS_STRUCT                                     \
    _Pragma("GCC diagnostic ignored \"-Wpedantic\"")
#define KJ_WARNING_DISABLE_DEPRECATED
#define KJ_WARNING_DISABLE_LOSS_OF_DATA
#define KJ_WARNING_DISABLE_MISSING_BRACES                                       \
    _Pragma("GCC diagnostic ignored \"-Wmissing-braces\"")
#define KJ_WARNING_DISABLE_VARIADIC_MACROS
    _Pragma("GCC diagnostic ignored \"-Wvariadic-macros\"")
#define KJ_WARNING_DISABLE_ZERO_SIZED_ARRAY                                     \
    _Pragma("GCC diagnostic ignored \"-Wpedantic\"")
#define KJ_WARNING_DISABLE_STRICT_ALIASING                                      \
    _Pragma("GCC diagnostic ignored \"-Wstrict-aliasing\"")
#else
#error "Unsupported Compiler"
#endif

#if !defined(KJ_ALIGN)
#if defined(KJ_COMPILER_MSVC)
#define kj_align(a) __declspec(align(a))
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_align(a) __attribute__((aligned(a)))
#endif
#define KJ_ALIGN(a) kj_align(a)
#endif

#if defined(KJ_ARCH_X86)
#if defined(KJ_SYS_WIN32)
#include <intrin.h>
#elif defined(KJ_SYS_UNIX)
#include <x86intrin.h>
#endif

typedef KJ_ALIGN(16) __m128 f32x4;
typedef KJ_ALIGN(16) __m128i i32x4;
#elif defined(KJ_ARCH_ARM) && defined(__ARM_NEON)
#include <arm_neon.h>

typedef KJ_ALIGN(16) float32x4_t f32x4;
typedef KJ_ALIGN(16) int32x4_t i32x4;
#endif

#define KJ_FALSE (0 != 0)
#define KJ_TRUE (0 == 0)

#if defined(__cplusplus)
#define KJ_CPP
#endif

#if defined(__STDC_VERSION__)
#if __STDC_VERSION__ >= 201112L
#define KJ_C11
#endif
#if __STDC_VERSION__ >= 199901L
#define KJ_C99
#endif
#endif

enum {
    KJ_ASCII_MAX = 0x7F,
    KJ_LATIN1_MAX = 0xFF,
    KJ_UNICODE_MAX = 0x10FFFF,
    KJ_UNICODE_REPLACEMENT = 0xFFFD,
    KJ_PATH_MAX = 4096,
    KJ_NAME_MAX = 255,
#if defined(KJ_SYS_WIN32)
    KJ_PATH_SEPARATOR = '\\'
#elif defined(KJ_SYS_UNIX)
    KJ_PATH_SEPARATOR = '/'
#endif
};

#if defined(KJ_SYS_WIN32)
#define KJ_PATH_SEPARATOR_STR "\\"
#elif defined(KJ_SYS_UNIX)
#define KJ_PATH_SEPARATOR_STR "/"
#endif

#define KJ_LE 1234
#define KJ_BE 4321

#if defined(KJ_SYS_UNIX)
#if __BYTE_ORDER == __BIG_ENDIAN
#define KJ_ENDIAN KJ_BE
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define KJ_ENDIAN KJ_LE
#else
#error "Unsupported Endianness"
#endif
#elif defined(KJ_SYS_WIN32)
#define KJ_ENDIAN KJ_LE
#else
#error "Unsupported Endianness"
#endif

#if !defined(NULL)
#if defined(KJ_COMPILER_MSVC)
#define NULL 0
#elif defined(KJ_COMPILER_GNU)
#define NULL __null
#else
#define NULL (kj_cast(void*, 0))
#endif
#endif

#if !defined(KJ_API)
#if defined(KJ_STATIC)
#define KJ_API static
#else
#define KJ_API extern
#endif
#endif

#if !defined(KJ_EXTERN)
#if defined(KJ_COMPILER_MSVC)
#if defined(KJ_CPP)
#define KJ_EXTERN extern "C" __declspec(dllexport)
#else
#define KJ_EXTERN __declspec(dllexport)
#endif
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#if defined(KJ_CPP)
#define KJ_EXTERN extern "C"
#else
#define KJ_EXTERN
#endif
#endif
#endif

#if !defined(restrict)
#if defined(KJ_COMPILER_MSVC) && !defined(KJ_CPP) && _MSC_VER <= 1800
#define restrict __restrict
#endif
#endif

#if !defined(KJ_INLINE)
#if defined(KJ_COMPILER_MSVC)
#define KJ_INLINE __forceinline
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#if defined(KJ_C99)
#define KJ_INLINE __attribute__((always_inline)) inline
#else
#define KJ_INLINE
#endif
#endif
#endif

#if !defined(KJ_NO_INLINE)
#if defined(KJ_COMPILER_MSVC)
#define KJ_NO_INLINE __declspec(noinline)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_NO_INLINE __attribute__((noinline))
#endif
#endif

#if !defined(KJ_CONST)
#if defined(KJ_COMPILER_MSVC)
#define KJ_CONST
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_CONST __attribute__((const))
#endif
#endif

#if !defined(KJ_GLOBAL)
#define KJ_GLOBAL static
#endif

#if !defined(KJ_INTERN)
#define KJ_INTERN static
#endif

/* Utility Macros */

#if !defined(elif)
#define elif else if
#endif

#if !defined(loop)
#define loop for(;;)
#endif

#if !defined(kj_cast)
#define kj_cast(t, e) ((t) (e))
#define KJ_CAST(t, e) ((t) (e))
#endif

#if !defined(kj_isize_of)
#define kj_isize_of(a) (kj_cast(isize, sizeof(a)))
#define kj_usize_of(a) (kj_cast(usize, sizeof(a)))
#endif

#if !defined(kj_count_of)
#define kj_count_of(a) (kj_isize_of(a) / kj_isize_of((a)[0]))
#endif

#if !defined(kj_offset_of)
#define kj_offset_of(s, m) (kj_cast(isize, (&(kj_cast(s*, 0)->m))))
#endif

#if !defined(kj_align_of)
#define kj_align_of(type) (kj_offset_of(struct { u8 c; type member; }, member))
#endif

#if !defined(kj_align_on)
#define kj_align_on(p, a)                                                       \
    kj_cast(void*, (kj_cast(uptr, p) + ((a) - 1)) & ~((a) - 1))
#endif

#if !defined(kj_concat)
#define KJ_JOIN(a, b) KJ_JOIN1(a, b)
#define KJ_JOIN1(a, b) KJ_JOIN2(a, b)
#define KJ_JOIN2(a, b) a##b
#endif

#if !defined(kj_unused)
#define kj_unused(a) kj_cast(void, (a))
#endif

#if !defined(kj_min)
#define kj_min(a, b) ((a) < (b) ? (a): (b))
#define kj_max(a, b) ((a) > (b) ? (a): (b))
#define kj_clamp(a, min, max) (kj_max((min), kj_min((a), (max))))
#define kj_wrap(a, min, max) ((a) > (max) ? (min): (a) < (min) ? (max): (a))
#define kj_lerp(t, min, max) ((1.0f - (t)) * (min) + (t) * (max))
#define kj_range(a, fmin, fmax, tmin, tmax)                                     \
    (((a) - (fmin)) * ((tmax) - (tmin)) / (((fmax) - (fmin)) + (tmin)))
#define kj_swap(T, a, b)                                                        \
    do { T tmp_##__LINE__ = a; a = b; b = tmp_##__LINE__; } while(0)
#define kj_abs(a) ((a) > 0 ? (a): -(a))
#define kj_sign(a) ((a) >= 0 ? 1: -1)
#define kj_round_to(a, b) ((a) + (((b) - 1) - (((a) - 1) % (b))))
#endif

#if !defined(kj_kb_to_b)
#define kj_kb_to_b(a) ((a) * 1024)
#define kj_mb_to_b(a) (kj_kb_to_b((a)) * 1024)
#define kj_gb_to_b(a) (kj_mb_to_b((a)) * 1024)
#define kj_tb_to_b(a) (kj_gb_to_b((a)) * 1024)
#define kj_b_to_kb(a) ((a) / 1024)
#define kj_b_to_mb(a) (kj_b_to_kb((a)) / 1024)
#define kj_b_to_gb(a) (kj_b_to_mb((a)) / 1024)
#define kj_b_to_tb(a) (kj_b_to_gb((a)) / 1024)
#endif

#if !defined(KJ_FLAG)
#define KJ_FLAG(a) (0x01 << (a))
#define KJ_FLAG_NONE (0)
#define KJ_FLAG_ALL (I32_MAX)
#endif

#if !defined(kj_copy)
#if defined(KJ_SYS_WIN32)
#define kj_copy CopyMemory
#define kj_set FillMemory
#define kj_zero ZeroMemory
#define kj_move MoveMemory
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_copy __builtin_memcpy
#define kj_set(p, s, v) __builtin_memset((p), (v), (s))
#define kj_zero(p, s) kj_set(p, s, 0)
#define kj_move __builtin_memmove
#endif

#define kj_one(p, s) kj_set(p, s, 1)
#define kj_fill(p, s) kj_set(p, s, 0xFF)
#endif

#if defined(KJ_C11)
#define KJ_STATIC_ASSERT(expr) _Static_assert(expr, kj_str_of(expr))
#else
#define KJ_STATIC_ASSERT(expr)                                                  \
    typedef void* KJ_JOIN(KJ_STATIC_ASSERT_, __LINE__)[(expr) * 2 - 1]
#endif

/* Types */

#if defined(KJ_C99)
#include <stdint.h>
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
#elif defined(KJ_COMPILER_MSVC)
typedef signed __int8 i8;
typedef unsigned __int8 u8;
typedef signed __int16 i16;
typedef unsigned __int16 u16;
typedef signed __int32 i32;
typedef unsigned __int32 u32;
typedef signed __int64 i64;
typedef unsigned __int64 u64;
#else
typedef signed char i8;
typedef unsigned char u8;
typedef signed short i16;
typedef unsigned short u16;
typedef signed int i32;
typedef unsigned int u32;
typedef signed long i64;
typedef unsigned long u64;
#endif

#if !defined(KJ_I8_MIN)
#define I8_MIN (-128)
#define I8_MAX (127)
#define I16_MIN (-32768)
#define I16_MAX (32767)
#define I32_MIN (-2147483648)
#define I32_MAX (2147483647)
#define I64_MIN (-9223372036854775808)
#define I64_MAX (9223372036854775807)

#define U8_MIN (0x00)
#define U8_MAX (0xFF)
#define U16_MIN (0x0000)
#define U16_MAX (0xFFFF)
#define U32_MIN (0x00000000)
#define U32_MAX (0xFFFFFFFF)
#define U64_MIN (0x0000000000000000)
#define U64_MAX (0xFFFFFFFFFFFFFFFF)
#endif

typedef i8 b8;
typedef i32 b32;

#if defined(KJ_ARCH_64_BIT)
typedef i64 isize;
typedef u64 usize;
#elif defined(KJ_ARCH_32_BIT)
typedef i32 isize;
typedef u32 usize;
#endif

KJ_STATIC_ASSERT(sizeof(void*) == sizeof(isize));
KJ_STATIC_ASSERT(sizeof(void*) == sizeof(usize));

#if !defined(ISIZE_MIN)
#if defined(ARCH_64_BIT)
#define ISIZE_MIN I64_MIN
#define ISIZE_MAX I64_MAX

#define USIZE_MIN U64_MIN
#define USIZE_MAX U64_MAX
#elif defined(ARCH_32_BIT)
#define ISIZE_MIN I32_MIN
#define ISIZE_MAX I32_MAX

#define USIZE_MIN U32_MIN
#define USIZE_MAX U32_MAX
#endif
#endif

typedef isize iptr;
typedef usize uptr;
typedef isize dptr;

typedef float f32;
typedef double f64;

#if !defined(F32_MIN)
#define F32_MIN (-3.402823e+38f)
#define F32_MAX (3.402823e+38f)
#define F32_EPS (1.192093e-07f)

#define F64_MIN (-1.797693e+308)
#define F64_MAX (1.797693e+308)
#define F64_EPS (2.220446e-16)
#endif

KJ_STATIC_ASSERT(sizeof(i8) == 1);
KJ_STATIC_ASSERT(sizeof(u8) == 1);
KJ_STATIC_ASSERT(sizeof(i16) == 2);
KJ_STATIC_ASSERT(sizeof(u16) == 2);
KJ_STATIC_ASSERT(sizeof(i32) == 4);
KJ_STATIC_ASSERT(sizeof(u32) == 4);
KJ_STATIC_ASSERT(sizeof(i64) == 8);
KJ_STATIC_ASSERT(sizeof(u64) == 8);
KJ_STATIC_ASSERT(sizeof(f32) == 4);
KJ_STATIC_ASSERT(sizeof(f64) == 8);

#define KJ_TYPE_MAP(X)                                                          \
    X(KJ_TYPE_CHAR, "char", char)                                               \
    X(KJ_TYPE_I8, "i8", i8)                                                     \
    X(KJ_TYPE_U8, "u8", u8)                                                     \
    X(KJ_TYPE_I16, "i16", i16)                                                  \
    X(KJ_TYPE_U16, "u16", u16)                                                  \
    X(KJ_TYPE_I32, "i32", i32)                                                  \
    X(KJ_TYPE_U32, "u32", u32)                                                  \
    X(KJ_TYPE_I64, "i64", i64)                                                  \
    X(KJ_TYPE_U64, "u64", u64)                                                  \
    X(KJ_TYPE_ISIZE, "isize", isize)                                            \
    X(KJ_TYPE_USIZE, "usize", usize)                                            \
    X(KJ_TYPE_F32, "f32", f32)                                                  \
    X(KJ_TYPE_F64, "f64", f64)                                                  \
    X(KJ_TYPE_B32, "b32", b32)

#define KJ_ERR_MAP(X)                                                           \
    X(KJ_ERR_BAD_HANDLE, "Bad Handle")                                          \
    X(KJ_ERR_PERMISSION_DENIED, "Permission Denied")                            \
    X(KJ_ERR_NOT_FOUND, "Not Found")                                            \
    X(KJ_ERR_NOT_EMPTY, "Not Empty")                                            \
    X(KJ_ERR_BROKEN_PIPE, "Broken Pipe")                                        \
    X(KJ_ERR_ALREADY_EXISTS, "Already Exists")                                  \
    X(KJ_ERR_TIMED_OUT, "Timed Out")                                            \
    X(KJ_ERR_INVALID_PARAMETER, "Invalid Parameter")                            \
    X(KJ_ERR_INTERRUPED, "Interrupted")                                         \
    X(KJ_ERR_ILLEGAL_SEEK, "Illegal Seek")                                      \
    X(KJ_ERR_ALLOC_FAILED, "Allocation Failed")                                 \
    X(KJ_ERR_WOULD_BLOCK, "Would Block")                                        \
    X(KJ_ERR_RANGE, "Out of Range")                                             \
    X(KJ_ERR_BUSY, "Device or Resource Busy")                                   \
    X(KJ_ERR_SYNTAX, "Invalid Syntax")

enum {
    KJ_ERR_UNKNOWN = I8_MIN,
#define KJ_ERR_ENUM(type, name) type,
    KJ_ERR_MAP(KJ_ERR_ENUM)
#undef KJ_ERR_ENUM
    KJ_ERR_COUNT,
    KJ_ERR_NONE = 0
};

typedef isize kjErr;

KJ_API const char* kj_err_str(kjErr err);
KJ_API kjErr kj_err_from_sys(void);

#define kj_is_ok(v) (!((v) < KJ_ERR_NONE))
#define kj_is_err(v) ((v) < KJ_ERR_NONE)

/* Memory */

enum {
    KJ_ALLOC_NONE = KJ_FLAG_NONE
};

#if defined(kj_alloc) && defined(kj_free) && defined(kj_realloc)
#elif !defined(kj_alloc) && !defined(kj_free) && !defined(kj_realloc)
#else
#error "kj_alloc, kj_free and kj_realloc must all be defined."
#endif

#if !defined(kj_alloc)
#define kj_alloc(s) kj_global_alloc(s, KJ_ALLOC_NONE)
#define kj_zalloc(s) kj_global_zalloc(s, KJ_ALLOC_NONE)
#define kj_free(d) kj_global_free(d, KJ_ALLOC_NONE)
#define kj_realloc(d, s) kj_global_realloc(d, s, KJ_ALLOC_NONE)
#define kj_alloc_aligned(s, a) kj_global_alloc_aligned(s, a, KJ_ALLOC_NONE)
#endif

KJ_API void* kj_global_alloc(isize size, u32 flags);
KJ_API void* kj_global_zalloc(isize size, u32 flags);
KJ_API void kj_global_free(void* data, u32 flags);
KJ_API void* kj_global_realloc(void* data, isize size, u32 flags);
KJ_API void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags);

typedef struct kjAllocator kjAllocator;

#define KJ_ALLOCATOR_ALLOC_FN(name)                                             \
    void* name(kjAllocator* allocator, isize size)
typedef KJ_ALLOCATOR_ALLOC_FN(kjAllocatorAllocFn);
#define KJ_ALLOCATOR_ZALLOC_FN(name)                                            \
    void* name(kjAllocator* allocator, isize size)
typedef KJ_ALLOCATOR_ZALLOC_FN(kjAllocatorZallocFn);
#define KJ_ALLOCATOR_FREE_FN(name)                                              \
    void name(kjAllocator* allocator, void* data)
typedef KJ_ALLOCATOR_FREE_FN(kjAllocatorFreeFn);
#define KJ_ALLOCATOR_REALLOC_FN(name)                                           \
    void* name(kjAllocator* allocator, void* data, isize size)
typedef KJ_ALLOCATOR_REALLOC_FN(kjAllocatorReallocFn);
#define KJ_ALLOCATOR_ALLOC_ALIGNED_FN(name)                                     \
    void* name(kjAllocator* allocator, isize size, isize alignment)
typedef KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kjAllocatorAllocAlignedFn);

struct kjAllocator {
    kjAllocatorAllocFn* alloc;
    kjAllocatorZallocFn* zalloc;
    kjAllocatorFreeFn* free;
    kjAllocatorReallocFn* realloc;
    kjAllocatorAllocAlignedFn* alloc_aligned;
    u32 flags;
};

#define kj_allocator_alloc(a, s)                                                \
    kj_cast(kjAllocator*, (a))->alloc(kj_cast(kjAllocator*, (a)), (s))
#define kj_allocator_zalloc(a, s)                                               \
    kj_cast(kjAllocator*, (a))->zalloc(kj_cast(kjAllocator*, (a)), (s))
#define kj_allocator_free(a, p)                                                 \
    kj_cast(kjAllocator*, (a))->free(kj_cast(kjAllocator*, (a)), (p))
#define kj_allocator_realloc(a, p, s)                                           \
    kj_cast(kjAllocator*, (a))->realloc(kj_cast(kjAllocator*, (a)), (p), (s))
#define kj_allocator_alloc_aligned(a, s, alignment)                             \
    kj_cast(kjAllocator*, (a))->alloc_aligned(                                  \
            kj_cast(kjAllocator*, (a)), (s), (alignment))

KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc);
KJ_API KJ_ALLOCATOR_ZALLOC_FN(kj_heap_zalloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_heap_free);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc);
KJ_API KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_heap_alloc_aligned);

KJ_GLOBAL const kjAllocator KJ_HEAP_ALLOCATOR = {
    kj_heap_alloc,
    kj_heap_zalloc,
    kj_heap_free,
    kj_heap_realloc,
    kj_heap_alloc_aligned,
    0
};

typedef struct kjLinearAllocator {
    kjAllocator allocator;
    u8* data;
    isize size;
    isize used;
    isize offset;
} kjLinearAllocator;

KJ_API kjLinearAllocator kj_linear_allocator(void* data, isize size, u32 flags);
KJ_API void kj_linear_allocator_reset(kjLinearAllocator* self);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_linear_alloc);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_linear_zalloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_linear_free);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc);
KJ_API KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_linear_alloc_aligned);

/* Debug */

#define KJ_PRIORITY_MAP(X)                                                      \
    X(KJ_PRIORITY_CRITICAL, "Critical")                                         \
    X(KJ_PRIORITY_ERROR, "Error")                                               \
    X(KJ_PRIORITY_WARN, "Warn")                                                 \
    X(KJ_PRIORITY_INFO, "Info")                                                 \
    X(KJ_PRIORITY_DEBUG, "Debug")                                               \
    X(KJ_PRIORITY_VERBOSE, "Verbose")

typedef enum kjPriority {
#define KJ_PRIORITY_ENUM(type, name) type,
    KJ_PRIORITY_MAP(KJ_PRIORITY_ENUM)
#undef KJ_PRIORITY_ENUM
    KJ_PRIORITY_COUNT
} kjPriority;

KJ_API const char* kj_priority_str(kjPriority priority);

#define KJ_LOG_HANDLER(name) void name(                                         \
        const char* file, isize line, const char* fn,                           \
        kjPriority priority, void* usr, const char* fmt, ...)

KJ_API KJ_LOG_HANDLER(kj_log_handler);

#if !defined(KJ_CUSTOM_LOG_HANDLER)
#define KJ_CUSTOM_LOG_HANDLER kj_log_handler
#endif

#if !defined(KJ_CUSTOM_LOG_USR)
#define KJ_CUSTOM_LOG_USR NULL
#endif

KJ_WARNING_DISABLE_BEGIN
KJ_WARNING_DISABLE_VARIADIC_MACROS

#if !defined(kj_log)
#define kj_log(priority, ...) KJ_CUSTOM_LOG_HANDLER(                            \
        KJ_CUR_FILE, KJ_CUR_LINE, KJ_CUR_FN,                                    \
        priority, KJ_CUSTOM_LOG_USR, __VA_ARGS__)
#define kj_log_critical(...) kj_log(KJ_PRIORITY_CRITICAL, __VA_ARGS__)
#define kj_log_error(...) kj_log(KJ_PRIORITY_ERROR, __VA_ARGS__)
#define kj_log_warn(...) kj_log(KJ_PRIORITY_WARN, __VA_ARGS__)
#define kj_log_info(...) kj_log(KJ_PRIORITY_INFO, __VA_ARGS__)
#define kj_log_debug(...) kj_log(KJ_PRIORITY_DEBUG, __VA_ARGS__)
#define kj_log_verbose(...) kj_log(KJ_PRIORITY_VERBOSE, __VA_ARGS__)
#endif

#define KJ_ASSERT_HANDLER(name) void name(                                      \
        const char* expr, const char* file, isize line, const char* fn,         \
        void* usr, const char* fmt, ...)

KJ_API KJ_ASSERT_HANDLER(kj_assert_handler);

#if !defined(KJ_CUSTOM_ASSERT_HANDLER)
#define KJ_CUSTOM_ASSERT_HANDLER kj_assert_handler
#endif

#if !defined(KJ_CUSTOM_ASSERT_USR)
#define KJ_CUSTOM_ASSERT_USR NULL
#endif

#define KJ_CUR_FILE __FILE__
#define KJ_CUR_LINE __LINE__

#if defined(KJ_COMPILER_MSVC)
#define KJ_CUR_FN __FUNCSIG__
#elif defined(KJ_COMPILER_GNU)
#define KJ_CUR_FN __extension__ __PRETTY_FUNCTION__
#elif defined(KJ_COMPILER_CLANG)
#define KJ_CUR_FN __PRETTY_FUNCTION__
#else
#define KJ_CUR_FN __func__
#endif

#if defined(KJ_COMPILER_MSVC)
#define kj_break() __debugbreak()
#define kj_unreachable() __assume(0)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_break() __builtin_trap()
#define kj_unreachable() __builtin_unreachable()
#endif

#if !defined(KJ_NO_DEBUG)
#define kj_assert(expr, ...) do {                                               \
    if(!(expr)) {                                                               \
        KJ_CUSTOM_ASSERT_HANDLER(                                               \
                kj_str_of(expr),                                                \
                KJ_CUR_FILE, KJ_CUR_LINE, KJ_CUR_FN,                            \
                KJ_CUSTOM_ASSERT_USR, __VA_ARGS__);                             \
        kj_break();                                                             \
    }                                                                           \
} while(0)
#define kj_panic(...) do {                                                      \
    KJ_CUSTOM_ASSERT_HANDLER(                                                   \
            "PANIC",                                                            \
            KJ_CUR_FILE, KJ_CUR_LINE, KJ_CUR_FN,                                \
            KJ_CUSTOM_ASSERT_USR, __VA_ARGS__);                                 \
    kj_break();                                                                 \
} while(0)
#else
#define kj_assert(expr, ...)
#define kj_panic(...)
#endif

KJ_WARNING_DISABLE_END

#define kj_unimplemented() kj_panic("UNIMPLEMENTED")

/* Endian */

KJ_API u16 kj_byte_swap_u16(u16 a);
KJ_API u32 kj_byte_swap_u32(u32 a);
KJ_API u64 kj_byte_swap_u64(u64 a);

#if !defined(kj_encode64)
#if KJ_ENDIAN == KJ_LE
#define kj_encode64(a, b, c, d, e, f, g, h)                                     \
    (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24) |                      \
     ((e) << 32) | ((f) << 40) | ((g) << 48) | ((h) << 56))
#define kj_encode32(a, b, c, d)                                                 \
    (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#define kj_encode16(a, b) (((a) << 0) | ((b) << 8))
#define kj_byte_swap_u16_le(a) (a)
#define kj_byte_swap_u32_le(a) (a)
#define kj_byte_swap_u64_le(a) (a)
#define kj_byte_swap_u16_be(a) kj_byte_swap_u16(a)
#define kj_byte_swap_u32_be(a) kj_byte_swap_u32(a)
#define kj_byte_swap_u64_be(a) kj_byte_swap_u64(a)
#else
#define kj_encode64(a, b, c, d, e, f, g, h)                                     \
    (((h) << 0) | ((g) << 8) | ((f) << 16) | ((e) << 24) |                      \
     ((d) << 32) | ((c) << 40) | ((b) << 48) | ((a) << 56))
#define kj_encode32(a, b, c, d)                                                 \
    (((d) << 0) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#define kj_encode16(a, b) (((b) << 0) | ((a) << 8))
#define kj_byte_swap_u16_le(a) kj_byte_swap_u16(a)
#define kj_byte_swap_u32_le(a) kj_byte_swap_u32(a)
#define kj_byte_swap_u64_le(a) kj_byte_swap_u64(a)
#define kj_byte_swap_u16_be(a) (a)
#define kj_byte_swap_u32_be(a) (a)
#define kj_byte_swap_u64_be(a) (a)
#endif
#endif

/* Printing */

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_FMT_VARGS(a) __attribute__((format(printf, (a), ((a) + 1))))
#else
#define KJ_FMT_VARGS(a)
#endif

#if defined(KJ_COMPILER_MSVC)
#define KJ_FMT_STR _Printf_format_string_
#else
#define KJ_FMT_STR
#endif

KJ_API isize kj_vprintf(const char* fmt, va_list v);
KJ_API isize kj_printf(KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(1);
KJ_API isize kj_vsnprintf(char* buf, isize size, const char* fmt, va_list v);
KJ_API isize kj_snprintf(
        char* buf, isize size, KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(3);

/* Strings/Characters */

typedef u8 utf8;

KJ_API b32 kj_char_is_eol(u32 c);
KJ_API b32 kj_char_is_whitespace(u32 c);
KJ_API b32 kj_char_is_alpha(u32 c);
KJ_API b32 kj_char_is_digit(u32 c);
KJ_API b32 kj_char_is_alphanum(u32 c);
KJ_API b32 kj_char_is_hex_digit(u32 c);
KJ_API b32 kj_char_is_lower(u32 c);
KJ_API b32 kj_char_is_upper(u32 c);
KJ_API b32 kj_char_is_separator(u32 c);

KJ_API u32 kj_char_to_lower(u32 c);
KJ_API u32 kj_char_to_upper(u32 c);

KJ_API isize kj_str_size(const char* s, isize size);
KJ_API isize kj_str_cmp(const char* s1, const char* s2, isize size);
KJ_API isize kj_str_case_cmp(const char* s1, const char* s2, isize size);
KJ_API isize kj_str_to_u64(u64* value, const char* s, isize size);
KJ_API isize kj_str_to_i64(i64* value, const char* s, isize size);
KJ_API isize kj_str_to_f64(f64* value, const char* s, isize size);
KJ_API const char* kj_str_find(const char* s, isize size, char c);
KJ_API const char* kj_str_rfind(const char* s, isize size, char c);
KJ_API char* kj_str_replace_char(char* s, isize size, char o, char n);
KJ_API const char* kj_str_trim(const char* s, isize size, const char** end);
KJ_API const char* kj_str_ltrim(const char* s, isize size);
KJ_API const char* kj_str_rtrim(const char* s, isize size);

KJ_API isize kj_utf8_count(const char* s, isize size);
KJ_API isize kj_utf8_size(char c);

#if defined(KJ_SYS_WIN32)
KJ_API i32 kj_utf8_to_ucs(WCHAR* ws, i32 wcount, const char* s);
KJ_API i32 kj_ucs_to_utf8(char* s, i32 count, const WCHAR* ws);
KJ_API WCHAR* kj_utf8_to_ucs_alloc(const char* s);
KJ_API char* kj_ucs_to_utf8_alloc(const WCHAR* ws);
#endif

typedef char* kjStr;

#define KJ_STR_HEADER(s) (kj_cast(kjStrHeader*, (s)) - 1)
#define kj_string_set_size(s, sz) (kj_cast(kjStrHeader*, (s)) - 1)->size = sz

KJ_WARNING_DISABLE_BEGIN
KJ_WARNING_DISABLE_ZERO_SIZED_ARRAY
#pragma pack(push, 1)

typedef struct kjStrHeader {
    kjAllocator* allocator;
    isize size;
    isize capacity;
    char data[0];
} kjStrHeader;

#pragma pack(pop)
KJ_WARNING_DISABLE_END

KJ_API kjStr kj_string(kjAllocator* allocator, const char* s, isize capacity);
KJ_API isize kj_string_size(kjStr s);
KJ_API isize kj_string_capacity(kjStr s);
KJ_API isize kj_string_available(kjStr s);
KJ_API void kj_string_destroy(kjStr s);
KJ_API void kj_string_reset(kjStr s);
KJ_API kjStr kj_string_extend(kjStr s, isize size);
KJ_API kjStr kj_string_resize(kjStr s, isize size);
KJ_API kjStr kj_string_append(kjStr s1, kjStr s2);
KJ_API kjStr kj_string_append_str(kjStr s1, const char* s2, isize size);

/* Sorting */

typedef enum kjOrdering {
    KJ_ORDERING_LESS = -1,
    KJ_ORDERING_EQUAL = 0,
    KJ_ORDERING_GREATER = 1
} kjOrdering;

#define KJ_CMP_FN(name) kjOrdering name(void* arr, isize i, isize j)
typedef KJ_CMP_FN(kjCmpFn);

#define KJ_CMP_FN_PROTO(type, name, T) KJ_API KJ_CMP_FN(kj_cmp_##T);
    KJ_TYPE_MAP(KJ_CMP_FN_PROTO)
#undef KJ_CMP_FN_PROTO

#define KJ_SWAP_FN(name) void name(void* arr, isize i, isize j)
typedef KJ_SWAP_FN(kjSwapFn);

#define KJ_SWAP_FN_PROTO(type, name, T) KJ_API KJ_SWAP_FN(kj_swap_##T);
    KJ_TYPE_MAP(KJ_SWAP_FN_PROTO)
#undef KJ_SWAP_FN_PROTO

KJ_API void kj_sort_insertion(
        void* arr, isize count, kjCmpFn cmp, kjSwapFn swap);

/* Date/Time */

#define KJ_DATETIME_UTC_ISO_FMT "%04d-%02d-%02dT%02d:%02d:%02dZ"
#define KJ_DATETIME_LOCAL_ISO_FMT "%04d-%02d-%02dT%02d:%02d:%02d%c%02d:%02d"
#define KJ_DATETIME_UTC_EXPAND(dt)                                              \
    (dt)->year, (dt)->month, (dt)->day, (dt)->hour, (dt)->minute, (dt)->second
#define KJ_DATETIME_LOCAL_EXPAND(dt)                                            \
    (dt)->year, (dt)->month, (dt)->day, (dt)->hour, (dt)->minute, (dt)->second, \
    (dt)->tz < 0 ? '+': '-', kj_abs(((dt)->tz / 60)), kj_abs(((dt)->tz % 60))

typedef struct kjDateTime {
    i16 year;
    i16 month;
    i16 day;
    i16 hour;
    i16 minute;
    i16 second;
    i16 millisecond;
    i16 tz;
} kjDateTime;

KJ_API u64 kj_timestamp_utc(void);
KJ_API kjDateTime kj_datetime_utc(void);
KJ_API kjDateTime kj_datetime_local(void);
KJ_API u64 kj_datetime_to_timestamp(kjDateTime dt);

KJ_API u64 kj_time_ms(void);

/* Hashing */

KJ_API u32 kj_hash_str(const char* s, isize size);

/* I/O */

enum {
    KJ_O_READ = KJ_FLAG(0),
    KJ_O_WRITE = KJ_FLAG(1),
    KJ_O_RDWR = KJ_O_READ | KJ_O_WRITE,
    KJ_O_CREATE = KJ_FLAG(2),
    KJ_O_CREATE_NEW = KJ_FLAG(3),
    KJ_O_APPEND = KJ_FLAG(4),
    KJ_O_TRUNCATE = KJ_FLAG(5),
    KJ_O_INVALID = KJ_FLAG_ALL
};

typedef enum kjSeekFrom {
    KJ_SEEK_BEGIN = 0,
    KJ_SEEK_CURRENT = 1,
    KJ_SEEK_END = 2
} kjSeekFrom;

#if defined(KJ_SYS_WIN32)
typedef HANDLE kjFd;
#define KJ_FILE_INVALID NULL
#elif defined(KJ_SYS_UNIX)
typedef i32 kjFd;
#define KJ_FILE_INVALID -1
#endif

typedef enum kjFileType {
    KJ_FILE,
    KJ_DIR,
    KJ_SYMLINK
} kjFileType;

typedef struct kjFileMetadata {
    i64 size;
    u64 last_access;
    u64 last_write;
    kjFileType type;
} kjFileMetadata;

KJ_API kjErr kj_file_create(kjFd* fd, const char* path);
KJ_API kjErr kj_file_open(kjFd* fd, const char* path, u32 flags);
KJ_API kjErr kj_file_close(kjFd fd);
KJ_API isize kj_file_seek(kjFd fd, i64 offset, kjSeekFrom seek);
KJ_API isize kj_file_read(kjFd fd, void* buf, isize size);
KJ_API isize kj_file_write(kjFd fd, void* buf, isize size);
KJ_API isize kj_file_read_at(kjFd fd, void* buf, isize size, i64 offset);
KJ_API isize kj_file_write_at(kjFd fd, void* buf, isize size, i64 offset);
KJ_API kjErr kj_file_sync(kjFd fd);
KJ_API kjErr kj_file_map(void** buf, kjFd fd, u32 flags);
KJ_API kjErr kj_file_map_path(
        void** buf, kjFd* fd, const char* path, u32 flags);
KJ_API kjErr kj_file_unmap(void* buf);

KJ_API isize kj_file_slurp(void** buf, const char* path);

KJ_API kjErr kj_file_metadata(kjFileMetadata* meta, kjFd fd);
KJ_API kjErr kj_file_metadata_path(kjFileMetadata* meta, const char* path);

/* Paths */

KJ_API const char* kj_path_ext(const char* path, isize size);
KJ_API const char* kj_path_base(const char* path, isize size, const char** end);
KJ_API const char* kj_path_dir(const char* path, isize size, const char** end);
KJ_API kjErr kj_path_create_dir(const char* path);
KJ_API kjErr kj_path_remove_dir(const char* path);
KJ_API kjErr kj_path_rename(const char* from, const char* to);
KJ_API isize kj_path_current_dir(char* path, isize size);
KJ_API kjErr kj_path_set_current_dir(const char* path);
KJ_API isize kj_path_tmp_dir(char* path, isize size);
KJ_API isize kj_path_self(char* path, isize size);
KJ_API b32 kj_path_exists(const char* path);
KJ_API b32 kj_path_is_file(const char* path);
KJ_API b32 kj_path_is_dir(const char* path);

/* Buf */

typedef struct kjBuf {
    kjAllocator* allocator;
    isize size;
    isize capacity;
    isize granularity;
    u8* data;
} kjBuf;

KJ_API kjErr kj_buf(kjBuf* buf, kjAllocator* allocator, isize granularity);
KJ_API void kj_buf_destroy(kjBuf* buf);
KJ_API kjBuf kj_buf_slice(kjBuf* buf, isize start, isize end);
KJ_API kjErr kj_buf_append(kjBuf* buf, const void* data, isize size);
KJ_API void kj_buf_reset(kjBuf* self);

KJ_EXTERN_END

#endif

#if defined(KJ_IMPL)

kjErr kj_err_from_sys(void) {
    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    switch(GetLastError()) {
        case ERROR_SUCCESS: res = KJ_ERR_NONE; break;
        case ERROR_ACCESS_DENIED: res = KJ_ERR_PERMISSION_DENIED; break;
        case ERROR_ALREADY_EXISTS: res = KJ_ERR_ALREADY_EXISTS; break;
        case ERROR_FILE_EXISTS: res = KJ_ERR_ALREADY_EXISTS; break;
        case ERROR_BROKEN_PIPE: res = KJ_ERR_BROKEN_PIPE; break;
        case ERROR_FILE_NOT_FOUND: res = KJ_ERR_NOT_FOUND; break;
        case ERROR_PATH_NOT_FOUND: res = KJ_ERR_NOT_FOUND; break;
        case ERROR_MOD_NOT_FOUND: res = KJ_ERR_NOT_FOUND; break;
        case ERROR_PROC_NOT_FOUND: res = KJ_ERR_NOT_FOUND; break;
        case ERROR_NOT_EMPTY: res = KJ_ERR_NOT_EMPTY; break;
        case ERROR_NO_DATA: res = KJ_ERR_BROKEN_PIPE; break;
        case ERROR_INVALID_PARAMETER: res = KJ_ERR_INVALID_PARAMETER; break;
        case ERROR_OPERATION_ABORTED: res = KJ_ERR_TIMED_OUT; break;
        case ERROR_SEEK: res = KJ_ERR_ILLEGAL_SEEK; break;
        case ERROR_NEGATIVE_SEEK: res = KJ_ERR_ILLEGAL_SEEK; break;
        case ERROR_SEEK_ON_DEVICE: res = KJ_ERR_ILLEGAL_SEEK; break;
        case ERROR_INSUFFICIENT_BUFFER: res = KJ_ERR_RANGE; break;
#elif defined(KJ_SYS_UNIX)
    switch(errno) {
        case 0: res = KJ_ERR_NONE; break;
        case EBADF: res = KJ_ERR_BAD_HANDLE; break;
        case EPERM: res = KJ_ERR_PERMISSION_DENIED; break;
        case EACCES: res = KJ_ERR_PERMISSION_DENIED; break;
        case EEXIST: res = KJ_ERR_ALREADY_EXISTS; break;
        case EPIPE: res = KJ_ERR_BROKEN_PIPE; break;
        case ENOENT: res = KJ_ERR_NOT_FOUND; break;
        case ENOTEMPTY: res = KJ_ERR_NOT_EMPTY; break;
        case ETIMEDOUT: res = KJ_ERR_TIMED_OUT; break;
        case EINVAL: res = KJ_ERR_INVALID_PARAMETER; break;
        case EINTR: res = KJ_ERR_INTERRUPED; break;
        case ESPIPE: res = KJ_ERR_ILLEGAL_SEEK; break;
        case EAGAIN: res = KJ_ERR_WOULD_BLOCK; break;
        case ERANGE: res = KJ_ERR_RANGE; break;
        case ENOMEM: res = KJ_ERR_ALLOC_FAILED; break;
        case EBUSY: res = KJ_ERR_BUSY; break;
#endif
        default: res = KJ_ERR_UNKNOWN; break;
    }
    return res;
}

KJ_CONST const char* kj_err_str(kjErr err) {
    switch(err) {
#define KJ_ERR_NAME(type, name) case (type): return (name);
        KJ_ERR_MAP(KJ_ERR_NAME)
#undef KJ_ERR_NAME
        default: return err < 0 ? "Unknown": "None";
    }
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_FN(kj__dummy_alloc) {
    kj_unused(allocator);
    kj_unused(size);
    return NULL;
}

KJ_INLINE KJ_ALLOCATOR_FREE_FN(kj__dummy_free) {
    kj_unused(allocator);
    kj_unused(data);
}

KJ_INLINE KJ_ALLOCATOR_REALLOC_FN(kj__dummy_realloc) {
    kj_unused(allocator);
    kj_unused(data);
    kj_unused(size);
    return NULL;
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj__dummy_alloc_aligned) {
    kj_unused(allocator);
    kj_unused(size);
    kj_unused(alignment);
    return NULL;
}

#define KJ__DEFAULT_ALIGNMENT (kj_cast(isize, (2 * kj_isize_of(isize))))
#define KJ__ALIGN_SIZE(s, a) kj_cast(isize, (s) + (a) - 1 + kj_isize_of(isize))
#define KJ__ALLOC_ADDR(p) (kj_cast(isize*, (p)) - 1)
#define KJ__HEADER_ALLOC_ADDR(p) (kj_cast(void*, *KJ__ALLOC_ADDR(p)))

void* kj_global_alloc(isize size, u32 flags) {
    return kj_global_alloc_aligned(size, KJ__DEFAULT_ALIGNMENT, flags);
}

void* kj_global_zalloc(isize size, u32 flags) {
    void* res = kj_global_alloc(size, flags);
    if(res) {
        kj_zero(res, size);
    }
    return res;
}

void kj_global_free(void* data, u32 flags) {
    kj_unused(flags);
    if(data) {
        void* header = KJ__HEADER_ALLOC_ADDR(data);
#if defined(KJ_SYS_WIN32)
        HeapFree(GetProcessHeap(), 0, header);
#elif defined(KJ_SYS_UNIX)
        free(header);
#endif
    }
}

void* kj_global_realloc(void* data, isize size, u32 flags) {
    void* res = NULL;
    if(data == NULL) {
        res = kj_global_alloc(size, flags);
    } elif(size == 0) {
        kj_global_free(data, flags);
    } else {
        void* header = KJ__HEADER_ALLOC_ADDR(data);
        isize aligned = KJ__ALIGN_SIZE(size, KJ__DEFAULT_ALIGNMENT);
#if defined(KJ_SYS_WIN32)
        header = HeapReAlloc(GetProcessHeap(), 0, header, aligned);
#elif defined(KJ_SYS_UNIX)
        header = realloc(header, aligned);
#endif
        if(header) {
            res = kj_align_on(
                    kj_cast(u8*, header) + kj_isize_of(isize),
                    KJ__DEFAULT_ALIGNMENT);
            *KJ__ALLOC_ADDR(res) = kj_cast(isize, header);
        }
    }
    return res;
}

void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags) {
    kj_unused(flags);
    void* res = NULL;
    isize aligned = KJ__ALIGN_SIZE(size, alignment);
    void* header = NULL;
#if defined(KJ_SYS_WIN32)
    header = HeapAlloc(GetProcessHeap(), 0, aligned);
#elif defined(KJ_SYS_UNIX)
    header = malloc(aligned);
#endif
    if(header) {
        res = kj_align_on(kj_cast(u8*, header) + kj_isize_of(isize), alignment);
        *KJ__ALLOC_ADDR(res) = kj_cast(isize, header);
    }
    return res;
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc) {
    return kj_global_alloc(size, allocator->flags);
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_FN(kj_heap_zalloc) {
    return kj_global_zalloc(size, allocator->flags);
}

KJ_INLINE KJ_ALLOCATOR_FREE_FN(kj_heap_free) {
    kj_global_free(data, allocator->flags);
}

KJ_INLINE KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc) {
    return kj_global_realloc(data, size, allocator->flags);
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_heap_alloc_aligned) {
    return kj_global_alloc_aligned(size, alignment, allocator->flags);
}

KJ_ALLOCATOR_ALLOC_FN(kj_linear_alloc) {
    return kj_allocator_alloc_aligned(allocator, size, KJ__DEFAULT_ALIGNMENT);
}

KJ_ALLOCATOR_ALLOC_FN(kj_linear_zalloc) {
    void* res = kj_allocator_alloc(allocator, size);
    if(res) {
        kj_zero(kj_cast(u8*, res) - size, size);
    }
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_linear_free) {
    if(allocator == NULL || data == NULL) {
        return;
    }

    kjLinearAllocator* a = kj_cast(kjLinearAllocator*, allocator);
    if(data == (a->data + a->offset)) {
        a->used = a->offset;
    }
}

KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc) {
    if(allocator == NULL || data == NULL || size <= 0) {
        return NULL;
    }

    void* res = NULL;
    kjLinearAllocator* a = kj_cast(kjLinearAllocator*, allocator);
    if((a->data + a->offset) == data) {
        isize new_size = a->used + (size - (a->used - a->offset));
        if(new_size < a->size) {
            a->used = new_size;
            res = data;
        }
    }
    return res;
}

KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_linear_alloc_aligned) {
    if(allocator == NULL || size <= 0) {
        return NULL;
    }

    void* res = NULL;
    kjLinearAllocator* a = kj_cast(kjLinearAllocator*, allocator);
    isize new_size = kj_round_to(a->used + size, alignment);
    if(new_size < a->size) {
        a->offset = kj_round_to(a->used, alignment);
        res = kj_cast(void*, a->data + a->offset);
        a->used = new_size;
    }
    return res;
}

kjLinearAllocator kj_linear_allocator(void* data, isize size, u32 flags) {
    kjLinearAllocator res;
    res.allocator.alloc = kj_linear_alloc;
    res.allocator.zalloc = kj_linear_zalloc;
    res.allocator.free = kj_linear_free;
    res.allocator.realloc = kj_linear_realloc;
    res.allocator.alloc_aligned = kj_linear_alloc_aligned;
    res.allocator.flags = flags;
    res.data = kj_cast(u8*, data);
    res.size = size;
    res.used = 0;
    res.offset = 0;
    return res;
}

void kj_linear_allocator_reset(kjLinearAllocator* self) {
    if(self == NULL) {
        return;
    }

    self->used = 0;
    self->offset = 0;
}


kjStr kj_string(kjAllocator* allocator, const char* s, isize size) {
    if(allocator == NULL || size < 0) {
        return NULL;
    }

    kjStr res = NULL;
    size = size == 0 ? kj_str_size(s, 0): size;
    kjStrHeader* header = kj_cast(kjStrHeader*, kj_allocator_alloc(
            allocator, kj_isize_of(kjStrHeader) + size + 1));
    if(header) {
        header->allocator = allocator;
        header->size = size;
        header->capacity = size;
        if(s) {
            kj_copy(header->data, s, size);
            header->data[size] = '\0';
        } else {
            kj_zero(header->data, size + 1);
        }
        res = header->data;
    }
    return res;
}

isize kj_string_size(kjStr s) {
    if(s == NULL) {
        return -1;
    }

    kjStrHeader* header = KJ_STR_HEADER(s);
    isize res = header->size;
    return res;
}

isize kj_string_capacity(kjStr s) {
    if(s == NULL) {
        return -1;
    }

    kjStrHeader* header = KJ_STR_HEADER(s);
    isize res = header->capacity;
    return res;
}

isize kj_string_available(kjStr s) {
    if(s == NULL) {
        return -1;
    }

    kjStrHeader* header = KJ_STR_HEADER(s);
    isize res = header->capacity - header->size;
    return res;
}

void kj_string_destroy(kjStr s) {
    if(s == NULL) {
        return;
    }

    kjStrHeader* header = KJ_STR_HEADER(s);
    kj_allocator_free(header->allocator, header);
}

void kj_string_reset(kjStr s) {
    if(s == NULL) {
        return;
    }

    kjStrHeader* header = KJ_STR_HEADER(s);
    header->size = 0;
    s[0] = '\0';
}

kjStr kj_string_extend(kjStr s, isize size) {
    if(s == NULL || size <= 0) {
        return NULL;
    }

    kjStr res = s;
    if(kj_string_available(s) < size) {
        kjAllocator* allocator = KJ_STR_HEADER(s)->allocator;
        isize new_capacity = kj_string_size(s) + kj_cast(isize, size * 2.0f);

        kjStrHeader* new_header = kj_cast(
                kjStrHeader* , kj_allocator_realloc(
                allocator, KJ_STR_HEADER(s),
                kj_isize_of(kjStrHeader) + new_capacity + 1));
        if(new_header != NULL) {
            res = new_header->data;
            new_header->capacity = new_capacity;
        } else {
            res = NULL;
        }
    }
    return res;
}

kjStr kj_string_resize(kjStr s, isize size) {
    return kj_string_extend(s, kj_abs(kj_string_size(s) - size));
}

kjStr kj_string_append(kjStr s1, kjStr s2) {
    return kj_string_append_str(s1, s2, kj_string_size(s2));
}

kjStr kj_string_append_str(kjStr s1, const char* s2, isize size) {
    kjStr res = NULL;
    isize s1_size = kj_string_size(s1);
    res = kj_string_extend(s1, size);
    if(res != NULL) {
        kj_copy(res + s1_size, s2, size);
        kjStrHeader* header = KJ_STR_HEADER(res);
        header->size = s1_size + size;
        res[header->size] = '\0';
    }
    return res;
}

kjStr kj_string_dup(kjStr s) {
    if(s == NULL) {
        return NULL;
    }

    kjStrHeader* header = kj_cast(kjStrHeader*, s) - 1;
    return kj_string(header->allocator, s, kj_string_size(s));
}

KJ_CONST const char* kj_priority_str(kjPriority priority) {
    switch(priority) {
#define KJ_LOG_CASE(type, name) case type: return (name);
        KJ_PRIORITY_MAP(KJ_LOG_CASE)
#undef KJ_LOG_CASE
        default: return "Unknown";
    }
}

#if defined(KJ_SYS_WIN32)
#pragma comment(lib, "user32.lib")
#endif

KJ_LOG_HANDLER(kj_log_handler) {
    kj_unused(file);
    kj_unused(usr);
    va_list v;
    va_start(v, fmt);
#if defined(KJ_SYS_WIN32)
    char buf[4096];
    kj_zero(buf, kj_isize_of(buf));
    isize used = kj_snprintf(
            buf, 4096, "%s:%ld:%s:%s\nMessage: ",
            file, line, fn, kj_priority_str(priority));
    used += kj_vsnprintf(buf + used, kj_isize_of(buf) - used, fmt, v);
    u32 flags = MB_OK;
    switch(priority) {
        case KJ_PRIORITY_CRITICAL:
        case KJ_PRIORITY_ERROR: {
            flags |= MB_ICONERROR | MB_SYSTEMMODAL;
        } break;
        case KJ_PRIORITY_WARN: {
            flags |= MB_ICONWARNING;
        } break;
        default: {
            flags |= MB_ICONINFORMATION;
        } break;
    }
    WCHAR* ws = kj_utf8_to_ucs_alloc(buf);
    MessageBoxW(NULL, ws, L"Log", flags);
    kj_global_free(ws, KJ_ALLOC_NONE);
#else
    kj_printf(
            "%s:%ld:%s:%s\nMessage: ",
            file, line, fn, kj_priority_str(priority));
    kj_vprintf(fmt, v);
#endif
    va_end(v);
}

KJ_ASSERT_HANDLER(kj_assert_handler) {
    kj_unused(file);
    kj_unused(usr);
    va_list v;
    va_start(v, fmt);
#if defined(KJ_SYS_WIN32)
    char buf[4096];
    kj_zero(buf, kj_isize_of(buf));
    isize used = kj_snprintf(
            buf, 4096, "%s:%ld:%s:%s\nMessage: ", file, line, fn, expr);
    used += kj_vsnprintf(buf + used, kj_isize_of(buf) - used, fmt, v);
    WCHAR* ws = kj_utf8_to_ucs_alloc(buf);
    MessageBoxW(NULL, ws, L"Assert", MB_OK | MB_ICONERROR);
    kj_global_free(ws, KJ_ALLOC_NONE);
#else
    kj_printf("%s:%ld:%s:%s\nMessage: ", file, line, fn, expr);
    kj_vprintf(fmt, v);
#endif
    va_end(v);
}

KJ_INLINE u16 kj_byte_swap_u16(u16 a) {
    return kj_cast(u16,
            ((a << 8) & 0xFF00) |
            ((a >> 8) & 0x00FF));
}

KJ_INLINE u32 kj_byte_swap_u32(u32 a) {
    return kj_cast(u32,
            ((a << 24) & 0xFF000000) |
            ((a <<  8) & 0x00FF0000) |
            ((a >>  8) & 0x0000FF00) |
            ((a >> 24) & 0x000000FF));
}

KJ_INLINE u64 kj_byte_swap_u64(u64 a) {
    return kj_cast(u64,
            kj_byte_swap_u32((a & 0xFFFFFFFF00000000) >> 32) |
            kj_byte_swap_u32((a & 0x00000000FFFFFFFF) << 32));
}

isize kj_vprintf(const char* fmt, va_list v) {
    return vprintf(fmt, v);
}

isize kj_printf(KJ_FMT_STR const char* fmt, ...) {
    isize res = -1;
    va_list v;
    kj_zero(&v, kj_isize_of(v));
    va_start(v, fmt);
    res = kj_vprintf(fmt, v);
    va_end(v);
    return res;
}

isize kj_vsnprintf(char* buf, isize size, const char* fmt, va_list v) {
    isize res = -1;
#if defined(KJ_COMPILER_MSVC)
KJ_WARNING_DISABLE_BEGIN
KJ_WARNING_DISABLE_DEPRECATED
    res = _vsnprintf(buf, size, fmt, v);
KJ_WARNING_DISABLE_END
#else
    res = vsnprintf(buf, size, fmt, v);
#endif
    return res;
}

isize kj_snprintf(char* buf, isize size, KJ_FMT_STR const char* fmt, ...) {
    isize res = -1;
    va_list v;
    kj_zero(&v, kj_isize_of(v));
    va_start(v,fmt);
    res = kj_vsnprintf(buf, size, fmt, v);
    va_end(v);
    return res;
}

KJ_INLINE b32 kj_char_is_eol(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
        return c == '\r' ||
               c == '\n' ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_whitespace(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
        return (c == ' '  ||
                c == '\t' ||
                c == '\v' ||
                c == '\f' ||
                c == '\r' ||
                c == '\n' ||
                c == 0x85 ||
                c == 0xA0) ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_alpha(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <='Z') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_digit(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
        return (c >= '0' && c <= '9') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_alphanum(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_hex_digit(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
        return (c >= 'a' && c <= 'f') ||
               (c >= 'A' && c <= 'F') ||
               (c >= '0' && c <= '9') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_lower(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
        return (c >= 'a' && c <= 'z') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_upper(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
        return (c >= 'A' && c <= 'Z') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_separator(u32 c) {
    if(c <= KJ_LATIN1_MAX) {
#if defined(KJ_SYS_WIN32)
        return (c == '\\' || c == '/') ? KJ_TRUE: KJ_FALSE;
#else
        return (c == '/') ? KJ_TRUE: KJ_FALSE;
#endif
    }
    return KJ_FALSE;
}

KJ_INLINE u32 kj_char_to_lower(u32 c) {
    if(c <= KJ_ASCII_MAX) {
        return (c >= 'A' && c <= 'Z') ? 'a' + (c - 'A'): c;
    }
    return c;
}

KJ_INLINE u32 kj_char_to_upper(u32 c) {
    if(c <= KJ_ASCII_MAX) {
        return (c >= 'a' && c <= 'z') ? 'A' + (c - 'a'): c;
    }
    return c;
}

KJ_INLINE isize kj_str_size(const char* s, isize size) {
    if(s == NULL || size < 0) {
        return 0;
    }

    const char* e = s;
    while(e < (s + size) || (*e && size == 0)) {
        e++;
    }
    return (e - s);
}

KJ_INLINE isize kj_str_cmp(const char* s1, const char* s2, isize size) {
    if(size == 0) {
        for(; *s1 == *s2 && *s1; s1++, s2++);
    } else {
        if(!size--) return 0;
        for(; *s1 && *s2 && size && *s1 == *s2; s1++, s2++, size--);
    }
    return *s1 - *s2;
}

KJ_INLINE isize kj_str_case_cmp(const char* s1, const char* s2, isize size) {
    if(size == 0) {
        for(; *s1 && kj_char_to_lower(*s1) == kj_char_to_lower(*s2);
                s1++, s2++);
    } else {
        if(!size--) return 0;
        for(; *s1 && *s2 && size &&
                kj_char_to_lower(*s1) == kj_char_to_lower(*s2);
                s1++, s2++, size--);
    }
    return *s1 - *s2;
}

isize kj_str_to_u64(u64* value, const char* s, isize size) {
    if(value == NULL || s == NULL || size < 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    *value = 0;
    size = size == 0 ? kj_str_size(s, 0): size;
    u64 base = 10;
    if(*s == '0' && size > 1){
        if(kj_str_case_cmp(s, "0x", 2) == 0) {
            base = 16;
            s += 2;
        } elif(kj_str_case_cmp(s, "0o", 2) == 0) {
            base = 8;
            s += 2;
        } elif(kj_str_case_cmp(s, "0b", 2) == 0) {
            base = 2;
            s += 2;
        } else {
            base = 0;
            res = KJ_ERR_SYNTAX;
        }
    }
    if(base > 0) {
        u64 overflow = U64_MAX / base + 1;
        u64 v;
        isize i;
        for(i = 0; i < size; i++) {
            if(s[i] >= '0' && s[i] <= '9') {
                v = s[i] - '0';
            } elif(base == 16 && s[i] >= 'a' && s[i] <= 'f') {
                v = s[i] - 'a' + 10;
            } elif(base == 16 && s[i] >= 'A' && s[i] <= 'F') {
                v = s[i] - 'A' + 10;
            } elif(s[i] == '_') {
                continue;
            } else {
                res = KJ_ERR_SYNTAX;
                break;
            }
            if(v > base) {
                res = KJ_ERR_SYNTAX;
                break;
            }
            if(*value > overflow) {
                *value = U64_MAX;
                res = KJ_ERR_RANGE;
                break;
            }
            *value *= base;
            u64 tmp = *value + v;
            if(tmp < *value || tmp > U64_MAX) {
                *value = U64_MAX;
                res = KJ_ERR_RANGE;
                break;
            }
            *value = tmp;
            res++;
        }
    }
    return res;
}

isize kj_str_to_i64(i64* value, const char* s, isize size) {
    if(value == NULL || s == NULL || size < 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    size = size == 0 ? kj_str_size(s, 0): size;
    i64 sign = *s == '-' ? s++, size--, -1: *s == '+' ? s++, size--, 1: 1;
    u64 u;
    if(kj_is_ok(res = kj_str_to_u64(&u, s, size))) {
        if(u <= I64_MAX) {
            *value = kj_cast(i64, u) * sign;
        } else {
            res = KJ_ERR_RANGE;
        }
    }
    return res;
}

isize kj_str_to_f64(f64* value, const char* s, isize size) {
    if(value == NULL || s == NULL || size < 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    *value = 0;
    size = size == 0 ? kj_str_size(s, 0): size;
    i64 sign = *s == '-' ? s++, size--, -1: *s == '+' ? s++, size--, 1: 1;
    const char* dot = kj_str_find(s, size, '.');
    if(dot) {
        isize i;
        for(i = 0; i < size; i++) {
            if(s[i] >= '0' && s[i] <= '9') {
                *value = *value * 10 + (s[i] - '0');
            } elif(s[i] == '_') {
                continue;
            } elif(s[i] != '.') {
                res = KJ_ERR_SYNTAX;
                break;
            }
            res++;
        }
        while(++dot < (s + size)) {
            *value *= 0.1;
        }
        *value *= sign;
    } else {
        res = KJ_ERR_SYNTAX;
    }
    return res;
}

const char* kj_str_find(const char* s, isize size, char c) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    const char* sp = s;
    while(sp < (s + size) || (*sp && size == 0)) {
        if(*sp == c) {
            res = sp;
            break;
        }
        sp++;
    }
    return res;
}

const char* kj_str_rfind(const char* s, isize size, char c) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(s, 0): size;
    isize i;
    for(i = size - 1; i >= 0; i--) {
        if(s[i] == c) {
            res = &s[i];
            break;
        }
    }
    return res;
}

char* kj_str_replace_char(char* s, isize size, char o, char n) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    char* res = s;
    while(res < (s + size) || *res) {
        if(*res == o) {
            *res = n;
        }
        res++;
    }
    return res;
}

const char* kj_str_trim(const char* s, isize size, const char** end) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = kj_str_ltrim(s, size);
    size = size == 0 ? kj_str_size(s, 0): size;
    *end = kj_str_rtrim(s, size);
    return res;
}

const char* kj_str_ltrim(const char* s, isize size) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = s;
    while((res < (s + size) || *res)) {
        if(!kj_char_is_whitespace(*res)) {
            break;
        }
        res++;
    }
    return res;
}

const char* kj_str_rtrim(const char* s, isize size) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = s + size;
    size = size == 0 ? kj_str_size(s, 0): size;
    isize i;
    for(i = size - 1; i >= 0 && kj_char_is_whitespace(s[i]); i--, res--);
    return res;
}

isize kj_utf8_count(const char* s, isize size) {
    if(s == NULL) {
        return -1;
    }

    isize res = 0;
    const char* sp = s;
    while(sp < (s + size) || (*sp && size == 0)) {
        if((*sp & 0xC0) != 0x80) {
            res++;
        }
        sp++;
    }
    return res;
}

KJ_INLINE isize kj_utf8_size(char c) {
    u8 u = kj_cast(u8, c);
    isize res = 0;
    if(u < 0x80) {
        res = 1;
    } elif(u >= 0xC2 && u <= 0xDF) {
        res = 2;
    } elif(u >= 0xE0 && u <= 0xEF) {
        res = 3;
    } elif(u >= 0xF0 && u <= 0xF4) {
        res = 4;
    }
    return res;
}

#if defined(KJ_SYS_WIN32)
i32 kj_utf8_to_ucs(WCHAR* ws, i32 wcount, const char* s) {
    if(s == NULL || ws == NULL || wcount < 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    i32 res = KJ_ERR_NONE;
    res = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
    if(res < wcount) {
        MultiByteToWideChar(CP_UTF8, 0, s, -1, ws, wcount);
    }
    return res;
}

i32 kj_ucs_to_utf8(char* s, i32 count, const WCHAR* ws) {
    if(s == NULL || ws == NULL || count < 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    i32 res = KJ_ERR_NONE;
    res = WideCharToMultiByte(CP_UTF8, 0, ws, -1, NULL, 0, NULL, NULL);
    if(res < count) {
        WideCharToMultiByte(CP_UTF8, 0, ws, -1, s, count, NULL, NULL);
    }
    return res;
}

WCHAR* kj_utf8_to_ucs_alloc(const char* s) {
    if(s == NULL) {
        return NULL;
    }

    WCHAR* res = NULL;
    i32 wcount = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
    if((res = kj_cast(WCHAR*, kj_alloc(wcount * kj_isize_of(WCHAR)))) != NULL) {
        MultiByteToWideChar(CP_UTF8, 0, s, -1, res, wcount);
    }
    return res;
}

char* kj_ucs_to_utf8_alloc(const WCHAR* ws) {
    if(ws == NULL) {
        return NULL;
    }

    char* res = NULL;
    i32 count = WideCharToMultiByte(CP_UTF8, 0, ws, -1, NULL, 0, NULL, NULL);
    if((res = kj_cast(char*, kj_alloc(count))) != NULL) {
        WideCharToMultiByte(CP_UTF8, 0, ws, -1, res, count, NULL, NULL);
    }
    return res;
}
#endif


#define KJ_CMP_FN_DEF(type, name, T)                                            \
    KJ_INLINE KJ_CMP_FN(kj_cmp_##T) {                                           \
        T a = kj_cast(T*, arr)[i];                                              \
        T b = kj_cast(T*, arr)[j];                                              \
        return kj_cast(kjOrdering, a < b ? -1: a > b);                          \
    }
    KJ_TYPE_MAP(KJ_CMP_FN_DEF)
#undef KJ_CMP_FN_DEF

#define KJ_SWAP_FN_DEF(type, name, T)                                           \
    KJ_INLINE KJ_SWAP_FN(kj_swap_##T) {                                         \
        T* values = kj_cast(T*, arr);                                           \
        T tmp = values[i];                                                      \
        values[i] = values[j];                                                  \
        values[j] = tmp;                                                        \
    }
    KJ_TYPE_MAP(KJ_SWAP_FN_DEF)
#undef KJ_SWAP_FN_DEF

void kj_sort_insertion(void* arr, isize count, kjCmpFn cmp, kjSwapFn swap) {
    isize i, j;
    for(i = 1; i < count; i++) {
        for(j = i - 1; j >= 0; j--) {
            if(cmp(arr, j, j + 1) == KJ_ORDERING_GREATER) {
                swap(arr, j, j + 1);
            }
        }
    }
}

#if defined(KJ_SYS_WIN32)
KJ_INLINE void kj__systime_to_datetime(SYSTEMTIME* st, kjDateTime* dt) {
#elif defined(KJ_SYS_UNIX)
KJ_INLINE void kj__systime_to_datetime(struct tm* tm, kjDateTime* dt) {
#endif
#if defined(KJ_SYS_WIN32)
    dt->year = st->wYear;
    dt->month = st->wMonth;
    dt->day = st->wDay;
    dt->hour = st->wHour;
    dt->minute = st->wMinute;
    dt->second = st->wSecond;
    dt->millisecond = st->wMilliseconds;
    dt->tz = 0;
#elif defined(KJ_SYS_UNIX)
    dt->year = 1900 + tm->tm_year;
    dt->month = tm->tm_mon + 1;
    dt->day = tm->tm_mday;
    dt->hour = tm->tm_hour;
    dt->minute = tm->tm_min;
    dt->second = tm->tm_sec;
    dt->millisecond = 0;
    dt->tz = 0;
#endif
}

#if defined(KJ_SYS_WIN32)
KJ_INLINE u64 kj__filetime_to_unix(FILETIME* ft) {
    ULARGE_INTEGER ul;
    ul.LowPart = ft->dwLowDateTime;
    ul.HighPart = ft->dwHighDateTime;
    return ul.QuadPart / 10000000 - 11644473600;
}
#endif

u64 kj_timestamp_utc(void) {
    u64 res = 0;
#if defined(KJ_SYS_WIN32)
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    res = kj__filetime_to_unix(&ft);
#elif defined(KJ_SYS_UNIX)
    time_t t;
    if(time(&t) != kj_cast(time_t, -1)) {
        res = kj_cast(u64, t);
    }
#endif
    return res;
}

u64 kj_datetime_to_timestamp(kjDateTime dt) {
    u64 res = 0;
#if defined(KJ_SYS_WIN32)
    SYSTEMTIME st;
    kj_zero(&st, kj_isize_of(st));
    st.wYear = dt.year;
    st.wMonth = dt.month;
    st.wDay = dt.day;
    st.wHour = dt.hour;
    st.wMinute = dt.minute;
    st.wSecond = dt.second;
    st.wMilliseconds = dt.millisecond;
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    res = kj__filetime_to_unix(&ft);
#elif defined(KJ_SYS_UNIX)
    struct tm tm;
    kj_zero(&tm, kj_isize_of(struct tm));
    tm.tm_year = dt.year - 1900;
    tm.tm_mon = dt.month - 1;
    tm.tm_mday = dt.day;
    tm.tm_hour = dt.hour;
    tm.tm_min = dt.minute;
    tm.tm_sec = dt.second;
    time_t t = mktime(&tm);
    res = kj_cast(u64, t);
#endif
    return res;
}

kjDateTime kj_datetime_utc(void) {
    kjDateTime res;
#if defined(KJ_SYS_WIN32)
    SYSTEMTIME st;
    kj_zero(&st, kj_isize_of(st));
    GetSystemTime(&st);
    kj__systime_to_datetime(&st, &res);
    res.tz = 0;
#elif defined(KJ_SYS_UNIX)
    time_t t;
    time(&t);
    struct tm* tm = gmtime(&t);
    kj__systime_to_datetime(tm, &res);
#endif
    return res;
}

kjDateTime kj_datetime_local(void) {
    kjDateTime res;
#if defined(KJ_SYS_WIN32)
    SYSTEMTIME st;
    GetLocalTime(&st);
    kj__systime_to_datetime(&st, &res);
    TIME_ZONE_INFORMATION tz;
    switch(GetTimeZoneInformation(&tz)) {
        case 0: { res.tz = kj_cast(i16, tz.Bias); } break;
        case 1: { res.tz = kj_cast(i16, tz.StandardBias); } break;
        case 2: { res.tz = kj_cast(i16, tz.DaylightBias); } break;
    }
#elif defined(KJ_SYS_UNIX)
    time_t t;
    time(&t);
    struct tm* tm = localtime(&t);
    kj__systime_to_datetime(tm, &res);
#endif
    return res;
}

#if defined(KJ_SYS_UNIX)
#if !defined(KJ_CLOCK_MONOTONIC)
#if defined(CLOCK_MONOTONIC_RAW)
#define KJ_CLOCK_MONOTONIC CLOCK_MONOTONIC_RAW
#elif defined(CLOCK_MONOTONIC)
#define KJ_CLOCK_MONOTONIC CLOCK_MONOTONIC
#endif
#endif
#endif

u64 kj_time_ms(void) {
#if defined(KJ_SYS_WIN32)
    static LARGE_INTEGER freq = {0};
    if(freq.QuadPart == 0) {
        QueryPerformanceFrequency(&freq);
    }
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return kj_cast(u64, counter.QuadPart * 1000 / freq.QuadPart);
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_CLOCK_MONOTONIC)
    struct timespec ts;
    clock_gettime(KJ_CLOCK_MONOTONIC, &ts);
    return kj_cast(u64, ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return kj_cast(u64, tv.tv_sec * 1000 + tv.tv_usec / 1000);
#endif
#endif
}

u32 kj_hash_str(const char* s, isize size) {
    if(s == NULL || size < 0) {
        return 0;
    }

    u32 res = 0;
    size = size == 0 ? kj_str_size(s, 0): size;
    isize i;
    for(i = 0; i < size; i++) {
        res += (*s++) * (kj_cast(u32, i % U32_MAX) + 119);
    }
    return res;
}

kjErr kj_file_create(kjFd* fd, const char* path) {
    return kj_file_open(fd, path, KJ_O_WRITE | KJ_O_CREATE | KJ_O_TRUNCATE);
}

KJ_INLINE u32 kj__file_access_flags(u32 flags) {
    u32 res = 0;
#if defined(KJ_SYS_WIN32)
    if((flags & KJ_O_READ) &&
      !(flags & KJ_O_WRITE) &&
      !(flags & KJ_O_APPEND)) {
        res = GENERIC_READ;
    } elif(!(flags & KJ_O_READ) &&
            (flags & KJ_O_WRITE) &&
           !(flags & KJ_O_APPEND)) {
        res = GENERIC_WRITE;
    } elif((flags & KJ_O_READ) &&
           (flags & KJ_O_WRITE) &&
          !(flags & KJ_O_APPEND)) {
        res = GENERIC_READ | GENERIC_WRITE;
    } elif(!(flags & KJ_O_READ) &&
            (flags & KJ_O_APPEND)) {
        res = FILE_GENERIC_WRITE & ~FILE_WRITE_DATA;
    } elif((flags & KJ_O_READ) &&
           (flags & KJ_O_APPEND)) {
        res = GENERIC_READ | (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA);
    }
#elif defined(KJ_SYS_UNIX)
    if((flags & KJ_O_READ) &&
      !(flags & KJ_O_WRITE) &&
      !(flags & KJ_O_APPEND)) {
        res = O_RDONLY;
    } elif(!(flags & KJ_O_READ) &&
            (flags & KJ_O_WRITE) &&
           !(flags & KJ_O_APPEND)) {
        res = O_WRONLY;
    } elif((flags & KJ_O_READ) &&
           (flags & KJ_O_WRITE) &&
          !(flags & KJ_O_APPEND)) {
        res = O_RDWR;
    } elif(!(flags & KJ_O_READ) &&
            (flags & KJ_O_APPEND)) {
        res = O_WRONLY | O_APPEND;
    } elif((flags & KJ_O_READ) &&
           (flags & KJ_O_APPEND)) {
        res = O_RDWR | O_APPEND;
    }
#endif
    return res;
}

KJ_INLINE u32 kj__file_create_flags(u32 flags) {
    u32 res = 0;
#if defined(KJ_SYS_WIN32)
    if(!(flags & KJ_O_WRITE) &&
       !(flags & KJ_O_APPEND)) {
        if((flags & KJ_O_TRUNCATE) ||
           (flags & KJ_O_CREATE) ||
           (flags & KJ_O_CREATE_NEW)) {
            res = kj_cast(u32, KJ_O_INVALID);
        }
    } elif(flags & KJ_O_APPEND) {
        if((flags & KJ_O_TRUNCATE) &&
          !(flags & KJ_O_CREATE_NEW)) {
            res = kj_cast(u32, KJ_O_INVALID);
        }
    }
    if(res == 0) {
        if(!(flags & KJ_O_CREATE) &&
           !(flags & KJ_O_TRUNCATE) &&
           !(flags & KJ_O_CREATE_NEW)) {
            res = OPEN_EXISTING;
        } elif((flags & KJ_O_CREATE) &&
              !(flags & KJ_O_TRUNCATE) &&
              !(flags & KJ_O_CREATE_NEW)) {
            res = OPEN_ALWAYS;
        } elif(!(flags & KJ_O_CREATE) &&
                (flags & KJ_O_TRUNCATE) &&
               !(flags & KJ_O_CREATE_NEW)) {
            res = TRUNCATE_EXISTING;
        } elif((flags & KJ_O_CREATE) &&
               (flags & KJ_O_TRUNCATE) &&
              !(flags & KJ_O_CREATE_NEW)) {
            res = CREATE_ALWAYS;
        } elif(flags & KJ_O_CREATE_NEW) {
            res = CREATE_NEW;
        }
    }
#elif defined(KJ_SYS_UNIX)
    if(!(flags & KJ_O_WRITE) &&
       !(flags & KJ_O_APPEND)) {
        if((flags & KJ_O_TRUNCATE) ||
           (flags & KJ_O_CREATE) ||
           (flags & KJ_O_CREATE_NEW)) {
            res = KJ_O_INVALID;
        }
    } elif(flags & KJ_O_APPEND) {
        if((flags & KJ_O_TRUNCATE) &&
          !(flags & KJ_O_CREATE_NEW)) {
            res = KJ_O_INVALID;
        }
    }
    if(res == 0) {
        if((flags & KJ_O_CREATE) &&
          !(flags & KJ_O_TRUNCATE) &&
          !(flags & KJ_O_CREATE_NEW)) {
            res = O_CREAT;
        } elif(!(flags & KJ_O_CREATE) &&
                (flags & KJ_O_TRUNCATE) &&
               !(flags & KJ_O_CREATE_NEW)) {
            res = O_TRUNC;
        } elif((flags & KJ_O_CREATE) &&
               (flags & KJ_O_TRUNCATE) &&
              !(flags & KJ_O_CREATE_NEW)) {
            res = O_CREAT | O_TRUNC;
        } elif(flags & KJ_O_CREATE_NEW) {
            res = O_CREAT | O_EXCL;
        }
    }
#endif
    return res;
}

kjErr kj_file_open(kjFd* fd, const char* path, u32 flags) {
    if(path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    u32 access = kj__file_access_flags(flags);
    u32 create = kj__file_create_flags(flags);
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_utf8_to_ucs_alloc(path);
    *fd = CreateFileW(
            wpath, access, FILE_SHARE_READ | FILE_SHARE_DELETE,
            NULL, create, FILE_ATTRIBUTE_NORMAL, NULL);
    if(*fd == INVALID_HANDLE_VALUE) {
        *fd = KJ_FILE_INVALID;
        res = kj_err_from_sys();
    }
    kj_free(wpath);
#elif defined(KJ_SYS_UNIX)
    u32 perm = 0666;
    if((*fd = open(path, (access | create), perm)) == -1) {
        *fd = KJ_FILE_INVALID;
        res = kj_err_from_sys();
    }
#endif
    return res;
}

kjErr kj_file_close(kjFd fd) {
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!CloseHandle(fd)) {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    if(close(fd) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

isize kj_file_seek(kjFd fd, i64 offset, kjSeekFrom seek) {
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    LARGE_INTEGER li_offset;
    li_offset.QuadPart = offset;
    if(SetFilePointerEx(fd, li_offset, &li_offset, seek) == 0) {
        res = kj_err_from_sys();
    } else {
        res = kj_cast(isize, li_offset.QuadPart);
    }
#elif defined(KJ_SYS_UNIX)
    if((res = lseek64(fd, offset, seek)) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

isize kj_file_read(kjFd fd, void* buf, isize size) {
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    } elif(buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    DWORD read = 0;
    if(ReadFile(fd, buf, kj_cast(DWORD, size), &read, NULL)) {
        res = read;
    } else {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = read(fd, buf, size)) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

isize kj_file_write(kjFd fd, void* buf, isize size) {
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    } elif(buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    DWORD wrote = 0;
    if(WriteFile(fd, buf, kj_cast(DWORD, size), &wrote, NULL)) {
        res = wrote;
    } else {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = write(fd, buf, size)) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

isize kj_file_read_at(kjFd fd, void* buf, isize size, i64 offset) {
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    } elif(buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped;
    kj_zero(&overlapped, kj_isize_of(OVERLAPPED));
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(fd, buf, kj_cast(DWORD, size), &read, &overlapped)) {
        res = read;
    } else {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = pread(fd, buf, size, offset)) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

isize kj_file_write_at(kjFd fd, void* buf, isize size, i64 offset) {
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    } elif(buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped;
    kj_zero(&overlapped, kj_isize_of(OVERLAPPED));
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(fd, buf, kj_cast(DWORD, size), &wrote, &overlapped)) {
        res = wrote;
    } else {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = pwrite(fd, buf, size, offset)) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

kjErr kj_file_sync(kjFd fd) {
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!FlushFileBuffers(fd)) {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    if(fsync(fd) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

kjErr kj_file_map(void** buf, kjFd fd, u32 flags) {
    kj_unused(flags);
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    } elif(buf == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    kjFd map = CreateFileMappingW(fd, NULL, PAGE_WRITECOPY, 0, 0, NULL);
    if(map == NULL) {
        res = kj_err_from_sys();
    } elif((*buf = MapViewOfFileEx(map, FILE_MAP_COPY, 0, 0, 0, 0)) == NULL) {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    kjFileMetadata meta;
    if(kj_is_ok(res = kj_file_metadata(&meta, fd))) {
        if((*buf = mmap(
                NULL, meta.size, PROT_READ | PROT_WRITE,
                MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
            res = kj_err_from_sys();
        }
    }
#endif
    return res;
}

kjErr kj_file_map_path(void** buf, kjFd* fd, const char* path, u32 flags) {
    if(fd == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    if(kj_is_ok(res = kj_file_open(fd, path, KJ_O_READ))) {
        res = kj_file_map(buf, *fd, flags);
    }
    return res;
}

kjErr kj_file_unmap(void* buf) {
    if(buf == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!UnmapViewOfFile(buf)) {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    if(munmap(buf, 0) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

isize kj_file_slurp(void** buf, const char* path) {
    if(buf == NULL || path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    kjFd fd;
    if(kj_is_ok(res = kj_file_open(&fd, path, KJ_O_READ))) {
        kjFileMetadata meta;
        if(kj_is_ok(res = kj_file_metadata(&meta, fd))) {
            *buf = kj_alloc(meta.size + 1);
            if(*buf) {
                res = kj_file_read(fd, *buf, meta.size);
                kj_cast(char*, *buf)[res] = '\0';
            } else {
                res = KJ_ERR_ALLOC_FAILED;
            }
        }
    }
    return res;
}

kjErr kj_file_metadata(kjFileMetadata* meta, kjFd fd) {
    if(fd == KJ_FILE_INVALID) {
        return KJ_ERR_BAD_HANDLE;
    } elif(meta == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    BY_HANDLE_FILE_INFORMATION info;
    if(GetFileInformationByHandle(fd, &info)) {
        meta->size =
            (kj_cast(i64, info.nFileSizeHigh) << 32) |
            (kj_cast(i64, info.nFileSizeLow));
        meta->last_access = kj__filetime_to_unix(&info.ftLastAccessTime);
        meta->last_write = kj__filetime_to_unix(&info.ftLastWriteTime);
        if(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            meta->type = KJ_DIR;
        } else {
            meta->type = KJ_FILE;
        }
    } else {
        res = kj_err_from_sys();
    }
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_zero(&st, kj_isize_of(struct stat));
    if(fstat(fd, &st) == -1) {
        res = kj_err_from_sys();
    } else {
        meta->size = st.st_size;
        meta->last_access = kj_cast(u64, st.st_atime);
        meta->last_write = kj_cast(u64, st.st_mtime);
    }
#endif
    return res;
}

kjErr kj_file_metadata_path(kjFileMetadata* meta, const char* path) {
    if(meta == NULL || path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    kjFd fd;
    if(kj_is_ok(res = kj_file_open(&fd, path, KJ_O_READ))) {
        res = kj_file_metadata(meta, fd);
        kj_file_close(fd);
    }
    return res;
}

const char* kj_path_ext(const char* path, isize size) {
    if(path == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(path, 0): size;
    if(path[size - 1] != '.') {
        isize i;
        for(i = size - 1; i >= 0; i--) {
            if(kj_char_is_separator(path[i])) {
                break;
            } elif(path[i] == '.') {
                res = &path[i + 1];
                break;
            }
        }
    }
    return res;
}

const char* kj_path_base(const char* path, isize size, const char** end) {
    if(path == NULL || size < 0 || end == NULL) {
        return ".";
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(path, 0): size;
    if(size == 0) {
        res = ".";
    } elif(size == 1) {
        res = path;
        *end = path + size;
    } else {
        size = kj_char_is_separator(path[size - 1]) ? size - 1: size;
        res = kj_str_rfind(path, size, KJ_PATH_SEPARATOR);
#if defined(KJ_SYS_WIN32)
        if(res == NULL) {
            res = kj_str_rfind(path, size, '/');
        }
#endif
        res = res == NULL ? path: res + 1;
        *end = &path[size] == res ? &path[size + 1]: &path[size];
    }
    return res;
}

const char* kj_path_dir(const char* path, isize size, const char** end) {
    if(path == NULL || size < 0 || end == NULL) {
        return ".";
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(path, 0): size;
    size = kj_char_is_separator(path[size - 1]) ? size - 1: size;
    *end = kj_str_rfind(path, size, KJ_PATH_SEPARATOR);
#if defined(KJ_SYS_WIN32)
    if(*end == NULL) {
        *end = kj_str_rfind(path, size, '/');
    }
#endif
    if(kj_char_is_separator(path[0])) {
        *end = *end == path ? *end + 1: *end;
        res = path;
    } else {
        res = *end ? path: ".";
        *end = *end == NULL ? res + 1: *end;
    }
    return res;
}

kjErr kj_path_create_dir(const char* path) {
    if(path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_utf8_to_ucs_alloc(path);
    if(CreateDirectoryW(wpath, NULL) == FALSE) {
        res = kj_err_from_sys();
    }
    kj_free(wpath);
#elif defined(KJ_SYS_UNIX)
    if(mkdir(path, S_IRWXU | S_IRGRP | S_IROTH) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

kjErr kj_path_remove_dir(const char* path) {
    if(path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_utf8_to_ucs_alloc(path);
    if(RemoveDirectoryW(wpath) == FALSE) {
        res = kj_err_from_sys();
    }
    kj_free(wpath);
#elif defined(KJ_SYS_UNIX)
    if(rmdir(path) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

kjErr kj_path_rename(const char* from, const char* to) {
    if(from == NULL || to == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wfrom = kj_utf8_to_ucs_alloc(from);
    WCHAR* wto = kj_utf8_to_ucs_alloc(to);
    if(MoveFileExW(wfrom, wto, MOVEFILE_REPLACE_EXISTING) == FALSE) {
        res = kj_err_from_sys();
    }
    kj_free(wfrom);
    kj_free(wto);
#elif defined(KJ_SYS_UNIX)
    if(rename(from, to) < 0) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

#if defined(KJ_SYS_WIN32)
KJ_INTERN isize kj__wchar_compute(
        char* out, isize size, DWORD (*fn)(DWORD, WCHAR*)) {
    if(out == NULL || size <= 0 || fn == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    WCHAR stack[512];
    kj_zero(stack, kj_isize_of(stack));
    DWORD n = kj_count_of(stack);
    WCHAR* ptr = stack;
    WCHAR* heap = NULL;
    loop {
        SetLastError(0);
        n = fn(n, ptr);
        if(n == 0) {
            res = kj_err_from_sys();
            break;
        } elif(kj_err_from_sys() == KJ_ERR_RANGE) {
            n *= 2;
            ptr = kj_cast(WCHAR*, kj_realloc(heap, n * kj_isize_of(WCHAR)));
            if(ptr == NULL) {
                kj_free(heap);
                res = KJ_ERR_ALLOC_FAILED;
                break;
            }
            heap = ptr;
        } else {
            res = kj_ucs_to_utf8(out, kj_cast(i32, size), ptr);
            break;
        }
    }
    kj_free(heap);
    return res;
}

KJ_INTERN KJ_INLINE DWORD kj__GetModuleFileNameW(DWORD n, WCHAR* buf) {
    return GetModuleFileNameW(NULL, buf, n);
}

KJ_INTERN KJ_INLINE DWORD kj__GetTempPathW(DWORD n, WCHAR* buf) {
    return GetTempPathW(n, buf);
}

KJ_INTERN KJ_INLINE DWORD kj__GetCurrentDirectoryW(DWORD n, WCHAR* buf) {
    return GetCurrentDirectoryW(n, buf);
}
#elif defined(KJ_SYS_UNIX)
KJ_INTERN isize kj__char_compute(
        char* out, isize size, isize (*fn)(isize, char*)) {
    if(out == NULL || size <= 0 || fn == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    char stack[512];
    kj_zero(stack, kj_isize_of(stack));
    isize n = kj_count_of(stack);
    char* ptr = stack;
    char* heap = NULL;
    loop {
        errno = 0;
        res = fn(n, ptr);
        if(n == 0) {
            res = kj_err_from_sys();
            break;
        } elif(res == n && errno == ERANGE) {
            n *= 2;
            ptr = kj_cast(char*, kj_realloc(heap, n));
            if(ptr == NULL) {
                kj_free(heap);
                res = KJ_ERR_ALLOC_FAILED;
                break;
            }
            heap = ptr;
        } else {
            res = kj_str_size(ptr, 0);
            if(res < size) {
                kj_copy(out, ptr, res);
                out[res] = '\0';
            }
            break;
        }
    }
    kj_free(heap);
    return res;
}

KJ_INTERN KJ_INLINE isize kj__getcwd(isize n, char* buf) {
    return getcwd(buf, n) == NULL && errno != ERANGE ? 0: n;
}

KJ_INTERN KJ_INLINE isize kj__readlink_self(isize n, char* buf) {
    isize res = readlink("/proc/self/exe", buf, n);
    if(res == -1) {
        res = 0;
    } elif(res == n) {
        errno = ERANGE;
        buf[res] = '\0';
    } else {
        buf[res] = '\0';
    }
    return res;
}
#endif

isize kj_path_current_dir(char* path, isize size) {
    if(path == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj__wchar_compute(path, size, kj__GetCurrentDirectoryW);
#elif defined(KJ_SYS_UNIX)
    res = kj__char_compute(path, size, kj__getcwd);
#endif
    return res;
}

kjErr kj_path_set_current_dir(const char* path) {
    if(path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_utf8_to_ucs_alloc(path);
    if(SetCurrentDirectoryW(wpath) == FALSE) {
        res = kj_err_from_sys();
    }
    kj_free(wpath);
#elif defined(KJ_SYS_UNIX)
    if(chdir(path) == -1) {
        res = kj_err_from_sys();
    }
#endif
    return res;
}

isize kj_path_tmp_dir(char* path, isize size) {
    if(path == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj__wchar_compute(path, size, kj__GetTempPathW);
#elif defined(KJ_SYS_UNIX)
    const char* tmp = NULL;
    if((tmp = getenv("TMPDIR")) == NULL) {
        tmp = "/tmp";
    }
    isize tmp_size = kj_str_size(tmp, 0);
    if(tmp_size < size) {
        kj_copy(path, tmp, tmp_size);
        path[tmp_size] = '\0';
        res = tmp_size;
    } else {
        res = tmp_size;
    }
#endif
    return res;
}

isize kj_path_self(char* path, isize size) {
    if(path == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj__wchar_compute(path, size, kj__GetModuleFileNameW);
#elif defined(KJ_SYS_UNIX)
    res = kj__char_compute(path, size, kj__readlink_self);
#endif
    return res;
}

b32 kj_path_exists(const char* path) {
    if(path == NULL) {
        return KJ_FALSE;
    }

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_utf8_to_ucs_alloc(path);
    HANDLE h = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAW find;
    if((h = FindFirstFileW(wpath, &find)) != INVALID_HANDLE_VALUE) {
        FindClose(h);
        res = KJ_TRUE;
    }
    kj_free(wpath);
#elif defined(KJ_SYS_UNIX)
    if(access(path, 0) == 0) {
        res = KJ_TRUE;
    }
#endif
    return res;
}

b32 kj_path_is_file(const char* path) {
    if(path == NULL) {
        return KJ_FALSE;
    }

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_utf8_to_ucs_alloc(path);
    DWORD attr = INVALID_FILE_ATTRIBUTES;
    if((attr = GetFileAttributesW(wpath)) != INVALID_FILE_ATTRIBUTES) {
        res = attr & FILE_ATTRIBUTE_DIRECTORY ? KJ_FALSE: KJ_TRUE;
    }
    kj_free(wpath);
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_zero(&st, kj_isize_of(struct stat));
    if(stat(path, &st) == 0) {
        res = S_ISREG(st.st_mode) != 0;
    }
#endif
    return res;
}

b32 kj_path_is_dir(const char* path) {
    if(path == NULL) {
        return KJ_FALSE;
    }

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_utf8_to_ucs_alloc(path);
    DWORD attr = INVALID_FILE_ATTRIBUTES;
    if((attr = GetFileAttributesW(wpath)) != INVALID_FILE_ATTRIBUTES) {
        res = attr & FILE_ATTRIBUTE_DIRECTORY ? KJ_TRUE: KJ_FALSE;
    }
    kj_free(wpath);
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_zero(&st, kj_isize_of(struct stat));
    if(stat(path, &st) == 0) {
        res = S_ISDIR(st.st_mode) != 0;
    }
#endif
    return res;
}

kjBuf kj_buf_slice(kjBuf* buf, isize start, isize end) {
    kjBuf res;
    kj_buf(&res, buf->allocator, end - start + 1);
    kj_copy(res.data, buf->data + start, end - start);
    res.size = end - start;
    res.data[res.size] = '\0';
    return res;
}

kjErr kj_buf(kjBuf* buf, kjAllocator* allocator, isize granularity) {
    if(buf == NULL || allocator == NULL || granularity <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    buf->data = NULL;
    buf->capacity = 0;
    buf->size = 0;
    buf->granularity = granularity;
    buf->allocator = allocator;
    return res;
}

void kj_buf_destroy(kjBuf* buf) {
    if(buf && buf->data) {
        kj_allocator_free(buf->allocator, buf->data);
        buf->data = NULL;
    }
}

kjErr kj_buf_append(kjBuf* buf, const void* data, isize size) {
    if(buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    if(buf->size + size > buf->capacity) {
        isize new_size = 1 + kj_round_to(
                buf->capacity + size, buf->granularity);
        void* new_data = NULL;
        new_data = kj_allocator_realloc(buf->allocator, buf->data, new_size);
        if(new_data) {
            buf->data = kj_cast(u8*, new_data);
            buf->capacity = size;
        } else {
            return KJ_ERR_ALLOC_FAILED;
        }
    }

    kj_copy(buf->data + buf->size, data, size);
    buf->size += size;
    buf->data[buf->size] = '\0';
    return res;
}

void kj_buf_reset(kjBuf* self) {
    if(self == NULL || self->data == NULL) {
        return;
    }

    self->size = 0;
}

#endif
