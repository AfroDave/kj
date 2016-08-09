// `kj.h`
//
// ---------------------------------- LICENSE ----------------------------------
// This software is in the public domain.  Where that dedication is not
// recognized, you are granted a perpetual, irrevocable license to copy,
// distribute, and modify the source code as you see fit.
//
// The source code is provided "as is", without warranty of any kind, express
// or implied. No attribution is required, but always appreciated.
// =============================================================================
//
// usage:
//      #define KJ_IMPL
//      #include "kj.h"

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
#if !defined(_UNICODE)
#define _UNICODE
#endif
#if !defined(UNICODE)
#define UNICODE
#endif
#include <windows.h>
#include <stdarg.h>
#include <stdint.h>
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
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
#error Unsupported Operating System
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_X86
#define KJ_ARCH_NAME "x86_64"
#elif defined(__i386) || defined(_M_IX86)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_X86
#define KJ_ARCH_NAME "x86"
#elif defined(__aarch64__)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_ARM
#define KJ_ARCH_NAME "arm64"
#elif defined(__arm__)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_ARM
#define KJ_ARCH_NAME "arm"
#else
#error Unsupported Architecture
#endif

#if !defined(kj_str_of)
#define kj_str_of(a) #a
#endif

#if defined(_MSC_VER)
#define KJ_COMPILER_MSVC
#define KJ_COMPILER_WARNING_BEGIN __pragma(warning(push))
#define KJ_COMPILER_WARNING_END __pragma(warning(pop))
#define KJ_COMPILER_WARNING(W) __pragma(warning(disable:W))
#define KJ_COMPILER_WARNING_PEDANTIC
#define KJ_COMPILER_WARNING_ZERO_SIZED_ARRAY 4200
#define KJ_COMPILER_WARNING_ANONYMOUS_STRUCT 4201
#define KJ_COMPILER_WARNING_MISSING_BRACES
#define KJ_COMPILER_WARNING_DEPRECATED 4996
#define KJ_COMPILER_WARNING_LOSS_OF_DATA 4244
#define KJ_COMPILER_WARNING_VARIADIC_MACROS
#elif defined(__clang__)
#define KJ_COMPILER_CLANG
#define KJ_COMPILER_WARNING_BEGIN _Pragma("clang diagnostic push")
#define KJ_COMPILER_WARNING_END _Pragma("clang diagnostic pop")
#define KJ_COMPILER_WARNING(W) _Pragma(kj_str_of(clang diagnostic ignored W))
#define KJ_COMPILER_WARNING_PEDANTIC "-Wpedantic"
#define KJ_COMPILER_WARNING_ZERO_SIZED_ARRAY "-Wzero-length-array"
#define KJ_COMPILER_WARNING_ANONYMOUS_STRUCT KJ_COMPILER_WARNING_PEDANTIC
#define KJ_COMPILER_WARNING_MISSING_BRACES "-Wmissing-braces"
#define KJ_COMPILER_WARNING_DEPRECATED KJ_COMPILER_WARNING_PEDANTIC
#define KJ_COMPILER_WARNING_LOSS_OF_DATA KJ_COMPILER_WARNING_PEDANTIC
#define KJ_COMPILER_WARNING_VARIADIC_MACROS "-Wvariadic-macros"
#elif defined(__clang__)
#elif defined(__GNUC__) || defined(__GNUG__)
#define KJ_COMPILER_GNU
#define KJ_COMPILER_WARNING_BEGIN _Pragma("GCC diagnostic push")
#define KJ_COMPILER_WARNING_END _Pragma("GCC diagnostic pop")
#define KJ_COMPILER_WARNING(W) _Pragma(kj_str_of(GCC diagnostic ignored W))
#define KJ_COMPILER_WARNING_PEDANTIC "-Wpedantic"
#define KJ_COMPILER_WARNING_ZERO_SIZED_ARRAY KJ_COMPILER_WARNING_PEDANTIC
#define KJ_COMPILER_WARNING_ANONYMOUS_STRUCT KJ_COMPILER_WARNING_PEDANTIC
#define KJ_COMPILER_WARNING_MISSING_BRACES "-Wmissing-braces"
#define KJ_COMPILER_WARNING_DEPRECATED KJ_COMPILER_WARNING_PEDANTIC
#define KJ_COMPILER_WARNING_LOSS_OF_DATA KJ_COMPILER_WARNING_PEDANTIC
#define KJ_COMPILER_WARNING_VARIADIC_MACROS "-Wvariadic-macros"
#else
#error Unsupported Compiler
#endif

KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_VARIADIC_MACROS)

#if defined(KJ_COMPILER_MSVC)
#define KJ_PRAGMA(...) __pragma(__VA_ARGS__)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_PRAGMA(...) _Pragma(kj_str_of(__VA_ARGS__))
#endif

KJ_COMPILER_WARNING_BEGIN

#define KJ_FALSE (0 != 0)
#define KJ_TRUE (0 == 0)

enum {
    KJ_MAX_ASCII = 0x7F,
    KJ_MAX_LATIN1 = 0xFF,
    KJ_MAX_UNICODE = 0x10FFFF,
    KJ_BIT_FLAG_NONE = 0,
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
#error Unsupported Endianness
#endif
#elif defined(KJ_SYS_WIN32)
#define KJ_ENDIAN KJ_LE
#else
#error Unsupported Endianness
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
#if defined(__cplusplus)
#define KJ_EXTERN extern "C" __declspec(dllexport)
#else
#define KJ_EXTERN __declspec(dllexport)
#endif
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#if defined(__cplusplus)
#define KJ_EXTERN extern "C"
#else
#define KJ_EXTERN
#endif
#endif
#endif

#if !defined(restrict)
#if defined(KJ_COMPILER_MSVC) && !defined(__cplusplus) && _MSC_VER <= 1800
#define restrict __restrict
#endif
#endif

#if !defined(KJ_INLINE)
#if defined(KJ_COMPILER_MSVC)
#define KJ_INLINE __forceinline
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_INLINE __attribute__((always_inline)) inline
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

/// Utility Macros

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
#define KJ_ISIZE_OF(a) kj_isize_of(a)
#define KJ_USIZE_OF(a) kj_usize_of(a)
#endif

#if !defined(kj_count_of)
#define kj_count_of(a) (kj_isize_of(a) / kj_isize_of((a)[0]))
#define KJ_COUNT_OF(a) kj_count_of(a)
#endif

#if !defined(kj_str_of)
#define kj_str_of(a) #a
#define KJ_STR_OF(a) kj_str_of(a)
#endif

#if !defined(kj_offset_of)
#define kj_offset_of(s, m) (kj_cast(isize, (&(kj_cast(s*, 0)->m))))
#define KJ_OFFSET_OF(s, m) kj_offset_of(s, m)
#endif

#if !defined(kj_align_of)
#define kj_align_of(type) (kj_offset_of(struct { u8 c; type member; }, member))
#define KJ_ALIGN_OF(type) kj_align_of(type)
#endif

#if !defined(KJ_ALIGN)
#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_align(a) __attribute__((aligned(a)))
#define KJ_ALIGN(a) kj_align(a)
#elif defined(KJ_COMPILER_MSVC)
#define kj_align(a) __declspec(align(a))
#define KJ_ALIGN(a) kj_align(a)
#endif
#endif

#if !defined(kj_align_on)
#define kj_align_on(p, a)                                                       \
    kj_cast(void*, (kj_cast(uptr, p) + ((a) - 1)) & ~((a) - 1))
#define KJ_ALIGN_ON(p, a) kj_align_on(p, a)
#endif

#if !defined(kj_concat)
#define kj_join(a, b) kj_join1(a, b)
#define kj_join1(a, b) kj_join2(a, b)
#define kj_join2(a, b) a##b
#define KJ_JOIN(a, b) kj_join(a, b)
#endif

#if !defined(kj_unused)
#define kj_unused(a) kj_cast(void, (a))
#define KJ_UNUSED(a) kj_unused(a)
#endif

#if !defined(kj_min)
#define kj_min(a, b) ((a) < (b) ? (a): (b))
#define kj_max(a, b) ((a) > (b) ? (a): (b))
#define kj_clamp(a, min, max) (kj_max((min), kj_min((a), (max))))
#define kj_wrap(a, min, max) ((a) > (max) ? (min): (a) < (min) ? (max): (a))
#define kj_lerp(t, min, max) ((1.0f - (t)) * (min) + (t) * (max))
#define kj_range(a, fmin, fmax, tmin, tmax)                                     \
    (((a) - (fmin)) * ((tmax) - (tmin)) / (((fmax) - (fmin)) + (tmin)))
#define kj_swap(T, a, b) { T tmp_##__LINE__ = a; a = b; b = tmp_##__LINE__; }
#define kj_abs(a) ((a) > 0 ? (a): -(a))
#define kj_sign(a) ((a) >= 0 ? 1: -1)
#define kj_round_to(a, b) ((a) + (((b) - 1) - (((a) - 1) % (b))))
#define KJ_MIN(a, b) kj_min(a, b)
#define KJ_MAX(a, b) kj_max(a, b)
#define KJ_CLAMP(a, min, max) kj_clamp(a, min, max)
#define KJ_WRAP(a, min, max) kj_wrap(a, min, max)
#define KJ_LERP(t, min, max) kj_lerp(t, min, max)
#define KJ_RANGE(a, fmin, fmax, tmin, tmax) kj_range(a, fmin, fmax, tmin, tmax)
#define KJ_SWAP(T, a, b) kj_swap(T, a, b)
#define KJ_ABS(a) kj_abs(a)
#define KJ_SIGN(a) kj_sign(a)
#define KJ_ROUND_TO(a, b) kj_round_to(a, b)
#endif

#if !defined(kj_kb_to_bytes)
#define kj_kb_to_bytes(a) ((a) * 1024)
#define kj_mb_to_bytes(a) (kj_kb_to_bytes((a)) * 1024)
#define kj_gb_to_bytes(a) (kj_mb_to_bytes((a)) * 1024)
#define kj_tb_to_bytes(a) (kj_gb_to_bytes((a)) * 1024)
#define kj_bytes_to_kb(a) ((a) / 1024)
#define kj_bytes_to_mb(a) (kj_bytes_to_kb((a)) / 1024)
#define kj_bytes_to_gb(a) (kj_bytes_to_mb((a)) / 1024)
#define kj_bytes_to_tb(a) (kj_bytes_to_gb((a)) / 1024)
#define KJ_KB_TO_BYTES(a) kj_kb_to_bytes(a)
#define KJ_MB_TO_BYTES(a) kj_mb_to_bytes(a)
#define KJ_GB_TO_BYTES(a) kj_gb_to_bytes(a)
#define KJ_TB_TO_BYTES(a) kj_tb_to_bytes(a)
#define KJ_BYTES_TO_KB(a) kj_bytes_to_kb(a)
#define KJ_BYTES_TO_MB(a) kj_bytes_to_mb(a)
#define KJ_BYTES_TO_GB(a) kj_bytes_to_gb(a)
#define KJ_BYTES_TO_TB(a) kj_bytes_to_tb(a)
#endif

#if !defined(KJ_BIT_FLAG)
#define KJ_BIT_FLAG(a) (0x01 << (a))
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

#define KJ_COPY kj_copy
#define KJ_SET kj_set
#define KJ_ZERO kj_zero
#define KJ_MOVE kj_move
#define kj_one(p, s) kj_set(p, s, 1)
#define kj_fill(p, s) kj_set(p, s, 0xFF)
#define KJ_ONE(p, s) KJ_SET(p, s, 1)
#define KJ_FILL(p, s) KJ_SET(p, s, 0xFF)
#endif

#if !defined(KJ_TLS)
#if defined(KJ_COMPILER_MSVC)
#define kj_tls __declspec(thread)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_tls __thread
#endif
#define KJ_TLS kj_tls
#endif

/// Types

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#if !defined(KJ_I8_MIN)
#define KJ_I8_MIN (-128)
#define KJ_I8_MAX (127)
#define KJ_I16_MIN (-32768)
#define KJ_I16_MAX (32767)
#define KJ_I32_MIN (-2147483648)
#define KJ_I32_MAX (2147483647)
#define KJ_I64_MIN (-9223372036854775807)
#define KJ_I64_MAX (9223372036854775807)

#define KJ_U8_MIN (0x00)
#define KJ_U8_MAX (0xFF)
#define KJ_U16_MIN (0x0000)
#define KJ_U16_MAX (0xFFFF)
#define KJ_U32_MIN (0x00000000)
#define KJ_U32_MAX (0xFFFFFFFF)
#define KJ_U64_MIN (0x0000000000000000)
#define KJ_U64_MAX (0xFFFFFFFFFFFFFFFF)
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

#if !defined(KJ_ISIZE_MIN)
#if defined(KJ_ARCH_64_BIT)
#define KJ_ISIZE_MIN KJ_I64_MIN
#define KJ_ISIZE_MAX KJ_I64_MAX

#define KJ_USIZE_MIN KJ_U64_MIN
#define KJ_USIZE_MAX KJ_U64_MAX
#elif defined(KJ_ARCH_32_BIT)
#define KJ_ISIZE_MIN KJ_I32_MIN
#define KJ_ISIZE_MAX KJ_I32_MAX

#define KJ_USIZE_MIN KJ_U32_MIN
#define KJ_USIZE_MAX KJ_U32_MAX
#endif
#endif

typedef isize iptr;
typedef usize uptr;
typedef isize dptr;

typedef float f32;
typedef double f64;

#if !defined(KJ_F32_MIN)
#define KJ_F32_MIN kj_cast(f32, -3.402823e+38)
#define KJ_F32_MAX kj_cast(f32, 3.402823e+38)
#define KJ_F32_EPS kj_cast(f32, 1.192093e-07)

#define KJ_F64_MIN kj_cast(f64, -1.797693e+308)
#define KJ_F64_MAX kj_cast(f64, 1.797693e+308)
#define KJ_F64_EPS kj_cast(f64, 2.220446e-16)
#endif

#define KJ_STATIC_ASSERT(n, a) typedef void* KJ_STATIC_ASSERT_##n[(a) * 2 - 1]
KJ_STATIC_ASSERT(I8, kj_isize_of(i8) == 1);
KJ_STATIC_ASSERT(U8, kj_isize_of(u8) == 1);
KJ_STATIC_ASSERT(I16, kj_isize_of(i16) == 2);
KJ_STATIC_ASSERT(U16, kj_isize_of(u16) == 2);
KJ_STATIC_ASSERT(I32, kj_isize_of(i32) == 4);
KJ_STATIC_ASSERT(U32, kj_isize_of(u32) == 4);
KJ_STATIC_ASSERT(I64, kj_isize_of(i64) == 8);
KJ_STATIC_ASSERT(U64, kj_isize_of(u64) == 8);
KJ_STATIC_ASSERT(F32, kj_isize_of(f32) == 4);
KJ_STATIC_ASSERT(F64, kj_isize_of(f64) == 8);

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
    X(KJ_ERR_ADDR_IN_USE, "Address In Use")                                     \
    X(KJ_ERR_ADDR_NOT_AVAILABLE, "Address Not Available")                       \
    X(KJ_ERR_CONNECTION_ABORTED, "Connection Aborted")                          \
    X(KJ_ERR_CONNECTION_REFUSED, "Connection Refused")                          \
    X(KJ_ERR_CONNECTION_RESET, "Connection Reset")                              \
    X(KJ_ERR_NOT_CONNECTED, "Not Connected")                                    \
    X(KJ_ERR_WOULD_BLOCK, "Would Block")                                        \
    X(KJ_ERR_NO_MORE_FILES, "No More Files")                                    \
    X(KJ_ERR_RANGE, "Out of Range")                                             \
    X(KJ_ERR_SYNTAX, "Invalid Syntax")

typedef enum kjErr {
    KJ_ERR_UNKNOWN = KJ_I8_MIN,
#define KJ_ERR_ENUM(type, name) type,
    KJ_ERR_MAP(KJ_ERR_ENUM)
#undef KJ_ERR_ENUM
    KJ_ERR_COUNT,
    KJ_ERR_NONE = 0
} kjErr;

KJ_API const char* kj_err_str(kjErr err);

#define kj_is_ok(v) (!((v) < KJ_ERR_NONE))
#define kj_is_err(v) ((v) < KJ_ERR_NONE)

/// Memory

enum {
    KJ_ALLOC_NONE = KJ_BIT_FLAG_NONE
};

KJ_API void* kj_global_alloc(isize size, u32 flags);
KJ_API void* kj_global_zalloc(isize size, u32 flags);
KJ_API void kj_global_free(void* data, u32 flags);
KJ_API void* kj_global_realloc(void* data, isize size, u32 flags);
KJ_API void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags);

typedef struct kjAllocator kjAllocator;

#define KJ_ALLOCATOR_ALLOC_FN(name)                                             \
    void* name(const kjAllocator* self, isize size)
typedef KJ_ALLOCATOR_ALLOC_FN(kjAllocatorAllocFn);
#define KJ_ALLOCATOR_ZALLOC_FN(name)                                            \
    void* name(const kjAllocator* self, isize size)
typedef KJ_ALLOCATOR_ZALLOC_FN(kjAllocatorZallocFn);
#define KJ_ALLOCATOR_FREE_FN(name)                                              \
    void name(const kjAllocator* self, void* data)
typedef KJ_ALLOCATOR_FREE_FN(kjAllocatorFreeFn);
#define KJ_ALLOCATOR_REALLOC_FN(name)                                           \
    void* name(const kjAllocator* self, void* data, isize size)
typedef KJ_ALLOCATOR_REALLOC_FN(kjAllocatorReallocFn);
#define KJ_ALLOCATOR_ALLOC_ALIGNED_FN(name)                                     \
    void* name(const kjAllocator* self, isize size, isize alignment)
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

typedef kjAllocator kjHeapAllocator;

KJ_API kjHeapAllocator kj_heap_allocator(u32 flags);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc);
KJ_API KJ_ALLOCATOR_ZALLOC_FN(kj_heap_zalloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_heap_free);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc);
KJ_API KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_heap_alloc_aligned);

/// Debug

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

KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_VARIADIC_MACROS)

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

KJ_COMPILER_WARNING_END

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

#define kj_unimplemented() kj_panic("UNIMPLEMENTED")

/// Endian

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

/// Printing

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

/// Strings/Characters

typedef i32 rune;

typedef u8 utf8;

KJ_API b32 kj_char_is_eol(u32 c);
KJ_API b32 kj_char_is_ws(u32 c);
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

#if defined(KJ_SYS_WIN32)
KJ_API i32 kj_utf8_to_ucs(WCHAR* ws, i32 count, const char* s);
KJ_API i32 kj_ucs_to_utf8(char* s, i32 count, const WCHAR* ws);
#endif

typedef char* kjStr;

#define KJ_STR_HEADER(s) (kj_cast(kjStrHeader*, (s)) - 1)

KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_ZERO_SIZED_ARRAY)
KJ_PRAGMA(pack(push, 1))

typedef struct kjStrHeader {
    kjAllocator* allocator;
    isize size;
    isize capacity;
    char data[0];
} kjStrHeader;

KJ_PRAGMA(pack(pop))
KJ_COMPILER_WARNING_END

KJ_API kjStr kj_string(kjAllocator* allocator, const char* s, isize capacity);
KJ_API isize kj_string_size(kjStr s);
KJ_API isize kj_string_capacity(kjStr s);
KJ_API isize kj_string_available(kjStr s);
KJ_API void kj_string_destroy(kjStr s);
KJ_API void kj_string_reset(kjStr s);
KJ_API kjStr kj_string_append(kjStr s1, kjStr s2);
KJ_API kjStr kj_string_append_str(kjStr s1, const char* s2, isize size);

/// Dynamic Libraries

#if defined(KJ_SYS_WIN32)
typedef HMODULE kjLib;
typedef FARPROC kjLibFn;
#elif defined(KJ_SYS_UNIX)
typedef void* kjLib;
typedef void (*kjLibFn)(void);
#endif
KJ_API kjErr kj_lib_open(kjLib* self, const char* path);
KJ_API kjErr kj_lib_fn(const kjLib* self, kjLibFn* fn, const char* name);
KJ_API void kj_lib_close(const kjLib* self);

/// Filtering

#define KJ_PREDICATE_FN(name) b32 name(const void* value)
typedef KJ_PREDICATE_FN(kjPredicateFn);

/// Sorting

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

/// Date/Time

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

/// Hashing

KJ_API u32 kj_hash_str(const char* s, isize size);

/// I/O

enum {
    KJ_FILE_NONE = KJ_BIT_FLAG_NONE,
    KJ_FILE_READ = KJ_BIT_FLAG(0),
    KJ_FILE_WRITE = KJ_BIT_FLAG(1),
    KJ_FILE_RDWR = KJ_FILE_READ | KJ_FILE_WRITE,
    KJ_FILE_CREATE = KJ_BIT_FLAG(2),
    KJ_FILE_CREATE_NEW = KJ_BIT_FLAG(3),
    KJ_FILE_APPEND = KJ_BIT_FLAG(4),
    KJ_FILE_TRUNCATE = KJ_BIT_FLAG(5)
};

typedef enum kjSeekFrom {
    KJ_SEEK_BEGIN = 0,
    KJ_SEEK_CURRENT = 1,
    KJ_SEEK_END = 2
} kjSeekFrom;

#if defined(KJ_SYS_WIN32)
typedef HANDLE kjFile;
#elif defined(KJ_SYS_UNIX)
typedef i32 kjFile;
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

KJ_API kjErr kj_file_create(kjFile* self, const char* path);
KJ_API kjErr kj_file_open(kjFile* self, const char* path, u32 flags);
KJ_API kjErr kj_file_close(const kjFile* self);
KJ_API kjErr kj_file_seek(const kjFile* self, i64 offset, kjSeekFrom seek);
KJ_API isize kj_file_read(const kjFile* self, void* buf, isize size);
KJ_API isize kj_file_write(const kjFile* self, const void* buf, isize size);
KJ_API isize kj_file_read_at(
        const kjFile* self, void* buf, isize size, i64 offset);
KJ_API isize kj_file_write_at(
        const kjFile* self, const void* buf, isize size, i64 offset);
KJ_API kjErr kj_file_sync(const kjFile* self);
KJ_API isize kj_file_slurp(
        void** data, kjAllocator* allocator, const char* path, b32 terminate);
KJ_API isize kj_file_spit(const char* path, const void* buf, isize size);

KJ_API kjErr kj_file_metadata(kjFileMetadata* self, const kjFile* file);
KJ_API kjErr kj_file_metadata_path(kjFileMetadata* self, const char* path);
KJ_API u64 kj_file_last_write(const kjFile* file);
KJ_API u64 kj_file_last_write_path(const char* path);

/// Paths

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

typedef struct kjReadDir {
#if defined(KJ_SYS_WIN32)
    WIN32_FIND_DATAW find;
    HANDLE handle;
    b32 first;
#elif defined(KJ_SYS_UNIX)
    DIR* dir;
#endif
} kjReadDir;

KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_ANONYMOUS_STRUCT)

typedef struct kjDirEntry {
    isize count;
    char path[KJ_PATH_MAX + 1];
} kjDirEntry;

KJ_COMPILER_WARNING_END

KJ_API kjErr kj_read_dir_begin(kjReadDir* self, const char* path);
KJ_API kjErr kj_read_dir_next(kjReadDir* self, kjDirEntry* entry);
KJ_API void kj_read_dir_end(kjReadDir* self);

/// Buffer

typedef struct kjBuffer {
    kjAllocator* allocator;
    isize granularity;
    isize capacity;
    isize size;
    u8* data;
} kjBuffer;

KJ_API kjErr kj_buffer(
        kjBuffer* self, kjAllocator* allocator, isize granularity);
KJ_API void kj_buffer_destroy(kjBuffer* self);
KJ_API kjErr kj_buffer_write(kjBuffer* self, const void* buf, isize size);
KJ_API void kj_buffer_reset(kjBuffer* self);

/// Dialog

enum {
    KJ_DIALOG_OPEN = KJ_BIT_FLAG(0),
    KJ_DIALOG_SAVE = KJ_BIT_FLAG(1),
    KJ_DIALOG_DIR = KJ_BIT_FLAG(2)
};

KJ_API isize kj_file_dialog(
        char* path, isize size, u32 mode, const char* filters);

KJ_EXTERN_END

#endif

#if defined(KJ_IMPL)

KJ_INTERN KJ_TLS char KJ__CHAR_BUF[KJ_PATH_MAX + 1] = {0};

#if defined(KJ_SYS_WIN32)
KJ_INTERN KJ_TLS WCHAR KJ__WCHAR_BUFA[KJ_PATH_MAX + 1] = {0};
KJ_INTERN KJ_TLS WCHAR KJ__WCHAR_BUFB[KJ_PATH_MAX + 1] = {0};
#endif

#if defined(KJ_SYS_LINUX)
#if !defined(kj_syscall1)
#if defined(KJ_ARCH_64_BIT)
enum {
    KJ_SYSCALL_CLOSE = 3,
    KJ_SYSCALL_OPEN = 2,
    KJ_SYSCALL_LSEEK = 8,
    KJ_SYSCALL_READ = 0,
    KJ_SYSCALL_PREAD = 17,
    KJ_SYSCALL_WRITE = 1,
    KJ_SYSCALL_PWRITE = 18,
    KJ_SYSCALL_ACCESS = 21,
    KJ_SYSCALL_GETCWD = 79,
    KJ_SYSCALL_CHDIR = 80,
    KJ_SYSCALL_RENAME = 82,
    KJ_SYSCALL_MKDIR = 83,
    KJ_SYSCALL_RMDIR = 84,
    KJ_SYSCALL_STAT = 4,
    KJ_SYSCALL_FSTAT = 5,
    KJ_SYSCALL_FSYNC = 74,
    KJ_SYSCALL_READLINK = 89
};

#if defined(KJ_ARCH_X86)
#define kj_syscall1(call, res, a) do {                                          \
    __asm__ __volatile__(                                                       \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a))                                               \
        : "memory");                                                            \
} while(0)
#define kj_syscall2(call, res, a, b) do {                                       \
    __asm__ __volatile__(                                                       \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b))                                    \
        : "memory");                                                            \
} while(0)
#define kj_syscall3(call, res, a, b, c) do {                                    \
    __asm__ __volatile__(                                                       \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)), "d" ((c))                         \
        : "memory");                                                            \
} while(0)
#define kj_syscall4(call, res, a, b, c, d) do {                                 \
    register __typeof__(d) r10 __asm("r10") = (d);                              \
    __asm__ __volatile__(                                                       \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)), "d" ((c)), "r" (r10)              \
        : "memory");                                                            \
} while(0)
#define kj_syscall5(call, res, a, b, c, d, e) do {                              \
    register __typeof__(d) r10 __asm("r10") = (d);                              \
    register __typeof__(e) r8 __asm("r8") = (e);                                \
    __asm__ __volatile__(                                                       \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)), "d" ((c)), "r" (r10), "r", (r8)   \
        : "memory");                                                            \
} while(0)
#define kj_syscall6(call, res, a, b, c, d, e, f) do {                           \
    register __typeof__(d) r10 __asm("r10") = (d);                              \
    register __typeof__(e) r8 __asm("r8") = (e);                                \
    register __typeof__(g) r9 __asm("r9") = (f);                                \
    __asm__ __volatile__(                                                       \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)), "d" ((c)), "r" (r10), "r", (r8),  \
          "r", (r9)                                                             \
        : "memory");                                                            \
} while(0)
#endif
#elif defined(KJ_ARCH_32_BIT)
enum {
    KJ_SYSCALL_CLOSE = 6,
    KJ_SYSCALL_OPEN = 5,
    KJ_SYSCALL_LSEEK = 19,
    KJ_SYSCALL_READ = 3,
    KJ_SYSCALL_PREAD = 180,
    KJ_SYSCALL_WRITE = 4,
    KJ_SYSCALL_PWRITE = 181,
    KJ_SYSCALL_ACCESS = 33,
    KJ_SYSCALL_RENAME = 38,
    KJ_SYSCALL_GETCWD = 183,
    KJ_SYSCALL_CHDIR = 12,
    KJ_SYSCALL_MKDIR = 39,
    KJ_SYSCALL_RMDIR = 40,
    KJ_SYSCALL_STAT = 106,
    KJ_SYSCALL_FSTAT = 108,
    KJ_SYSCALL_FSYNC = 11,
    KJ_SYSCALL_READLINK = 85
};

#if defined(KJ_ARCH_X86)
#define kj_syscall1(call, res, a) do {                                          \
    __asm__ __volatile__(                                                       \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a))                                               \
        : "memory");                                                            \
} while(0)
#define kj_syscall2(call, res, a, b) do {                                       \
    __asm__ __volatile__(                                                       \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)), "c" ((b))                                    \
        : "memory");                                                            \
} while(0)
#define kj_syscall3(call, res, a, b, c) do {                                    \
    __asm__ __volatile__(                                                       \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)), "c" ((b)), "d" ((c)))                        \
        : "memory");                                                            \
} while(0)
#define kj_syscall4(call, res, a, b, c, d) do {                                 \
    __asm__ __volatile__(                                                       \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)), "c" ((b)), "d" ((c)), "s" ((d))              \
        : "memory");                                                            \
} while(0)
#define kj_syscall5(call, res, a, b, c, d, e) do {                              \
    __asm__ __volatile__(                                                       \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)), "c" ((b)), "d" ((c)), "s" ((d)), "D" ((e))   \
        : "memory");                                                            \
} while(0)
#define kj_syscall6(call, res, a, b, c, d, e, f) kj_panic("x86 syscall6")
#elif defined(KJ_ARCH_ARM)
#define kj_syscall1(call, res, a) kj_panic("ARM syscall1")
#define kj_syscall2(call, res, a, b) kj_panic("ARM syscall2")
#define kj_syscall3(call, res, a, b, c) kj_panic("ARM syscall3")
#define kj_syscall4(call, res, a, b, c, d) kj_panic("ARM syscall4")
#define kj_syscall5(call, res, a, b, c, d, e) kj_panic("ARM syscall5")
#define kj_syscall6(call, res, a, b, c, d, e, f) kj_panic("ARM syscall6")
#endif
#endif
#endif
#endif

KJ_INLINE kjErr kj_err_from_sys(i32 err) {
    switch(err) {
#if defined(KJ_SYS_WIN32)
        case ERROR_SUCCESS: return KJ_ERR_NONE;
        case ERROR_ACCESS_DENIED: return KJ_ERR_PERMISSION_DENIED;
        case ERROR_ALREADY_EXISTS: return KJ_ERR_ALREADY_EXISTS;
        case ERROR_FILE_EXISTS: return KJ_ERR_ALREADY_EXISTS;
        case ERROR_BROKEN_PIPE: return KJ_ERR_BROKEN_PIPE;
        case ERROR_FILE_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_PATH_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_MOD_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_PROC_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_NOT_EMPTY: return KJ_ERR_NOT_EMPTY;
        case ERROR_NO_DATA: return KJ_ERR_BROKEN_PIPE;
        case ERROR_INVALID_PARAMETER: return KJ_ERR_INVALID_PARAMETER;
        case ERROR_OPERATION_ABORTED: return KJ_ERR_TIMED_OUT;
        case ERROR_SEEK: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_NEGATIVE_SEEK: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_SEEK_ON_DEVICE: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_INSUFFICIENT_BUFFER: return KJ_ERR_RANGE;
        case ERROR_NO_MORE_FILES: return KJ_ERR_NO_MORE_FILES;
        case WSAEBADF: return KJ_ERR_BAD_HANDLE;
        case WSAEACCES: return KJ_ERR_PERMISSION_DENIED;
        case WSAETIMEDOUT: return KJ_ERR_TIMED_OUT;
        case WSAEINVAL: return KJ_ERR_INVALID_PARAMETER;
        case WSAEINTR: return KJ_ERR_INTERRUPED;
        case WSAEADDRINUSE: return KJ_ERR_ADDR_IN_USE;
        case WSAEADDRNOTAVAIL: return KJ_ERR_ADDR_NOT_AVAILABLE;
        case WSAECONNABORTED: return KJ_ERR_CONNECTION_ABORTED;
        case WSAECONNREFUSED: return KJ_ERR_CONNECTION_REFUSED;
        case WSAECONNRESET: return KJ_ERR_CONNECTION_RESET;
        case WSAENOTCONN: return KJ_ERR_NOT_CONNECTED;
        case WSAEWOULDBLOCK: return KJ_ERR_WOULD_BLOCK;
#elif defined(KJ_SYS_UNIX)
        case 0: return KJ_ERR_NONE;
        case -EBADF:
        case EBADF: return KJ_ERR_BAD_HANDLE;
        case -EPERM:
        case EPERM: return KJ_ERR_PERMISSION_DENIED;
        case -EACCES:
        case EACCES: return KJ_ERR_PERMISSION_DENIED;
        case -EEXIST:
        case EEXIST: return KJ_ERR_ALREADY_EXISTS;
        case -EPIPE:
        case EPIPE: return KJ_ERR_BROKEN_PIPE;
        case -ENOENT:
        case ENOENT: return KJ_ERR_NOT_FOUND;
        case -ENOTEMPTY:
        case ENOTEMPTY: return KJ_ERR_NOT_EMPTY;
        case -ETIMEDOUT:
        case ETIMEDOUT: return KJ_ERR_TIMED_OUT;
        case -EINVAL:
        case EINVAL: return KJ_ERR_INVALID_PARAMETER;
        case -EINTR:
        case EINTR: return KJ_ERR_INTERRUPED;
        case -ESPIPE:
        case ESPIPE: return KJ_ERR_ILLEGAL_SEEK;
        case -EADDRINUSE:
        case EADDRINUSE: return KJ_ERR_ADDR_IN_USE;
        case -EADDRNOTAVAIL:
        case EADDRNOTAVAIL: return KJ_ERR_ADDR_NOT_AVAILABLE;
        case -ECONNABORTED:
        case ECONNABORTED: return KJ_ERR_CONNECTION_ABORTED;
        case -ECONNREFUSED:
        case ECONNREFUSED: return KJ_ERR_CONNECTION_REFUSED;
        case -ECONNRESET:
        case ECONNRESET: return KJ_ERR_CONNECTION_RESET;
        case -ENOTCONN:
        case ENOTCONN: return KJ_ERR_NOT_CONNECTED;
        case -EAGAIN:
        case EAGAIN: return KJ_ERR_WOULD_BLOCK;
        case -ERANGE:
        case ERANGE: return KJ_ERR_RANGE;
#endif
        default: return KJ_ERR_UNKNOWN;
    }
}

KJ_CONST KJ_INLINE const char* kj_err_str(kjErr err) {
    switch(err) {
#define KJ_ERR_NAME(type, name) case (type): return (name);
        KJ_ERR_MAP(KJ_ERR_NAME)
#undef KJ_ERR_NAME
        default: return err < 0 ? "Unknown": "None";
    }
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_FN(kj__dummy_alloc) {
    kj_unused(self);
    kj_unused(size);
    return NULL;
}

KJ_INLINE KJ_ALLOCATOR_FREE_FN(kj__dummy_free) {
    kj_unused(self);
    kj_unused(data);
}

KJ_INLINE KJ_ALLOCATOR_REALLOC_FN(kj__dummy_realloc) {
    kj_unused(self);
    kj_unused(data);
    kj_unused(size);
    return NULL;
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj__dummy_alloc_aligned) {
    kj_unused(self);
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
        res = kj_align_on(
                kj_cast(u8*, header) + kj_isize_of(isize),
                alignment);
        *KJ__ALLOC_ADDR(res) = kj_cast(isize, header);
    }
    return res;
}

KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc) {
    return kj_global_alloc(size, self->flags);
}

KJ_ALLOCATOR_ALLOC_FN(kj_heap_zalloc) {
    return kj_global_zalloc(size, self->flags);
}

KJ_ALLOCATOR_FREE_FN(kj_heap_free) {
    kj_global_free(data, self->flags);
}

KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc) {
    return kj_global_realloc(data, size, self->flags);
}

KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_heap_alloc_aligned) {
    return kj_global_alloc_aligned(size, alignment, self->flags);
}

kjHeapAllocator kj_heap_allocator(u32 flags) {
    kjHeapAllocator res;
    res.alloc = kj_heap_alloc;
    res.free = kj_heap_free;
    res.realloc = kj_heap_realloc;
    res.alloc_aligned = kj_heap_alloc_aligned;
    res.flags = flags;
    return res;
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

KJ_INTERN kjStr kj__string_extend(kjStr s, isize size) {
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

kjStr kj_string_append(kjStr s1, kjStr s2) {
    return kj_string_append_str(s1, s2, kj_string_size(s2));
}

kjStr kj_string_append_str(kjStr s1, const char* s2, isize size) {
    kjStr res = NULL;
    isize s1_size = kj_string_size(s1);
    res = kj__string_extend(s1, size);
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

KJ_CONST KJ_INLINE const char* kj_priority_str(kjPriority priority) {
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
    kj_unused(usr);
    va_list v;
    va_start(v, fmt);
#if defined(KJ_SYS_WIN32)
    char buf[4096];
    kj_zero(buf, kj_isize_of(buf));
    isize used = kj_snprintf(
            buf, kj_isize_of(buf),
            "FILE: %s\nLINE: %ld\nFUNC: %s\nPRIORITY: %s\nMSG:\n",
            file, line, fn, kj_priority_str(priority));
    used += kj_vsnprintf(buf + used, kj_isize_of(buf) - used, fmt, v);
    buf[used] = '\0';
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
    kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), buf);
    MessageBoxW(NULL, KJ__WCHAR_BUFA, L"Log", flags);
#else
    kj_printf(
            "FILE: %s\nLINE: %ld\nFUNC: %s\nPRIORITY: %s\nMSG:\n",
            file, line, fn, kj_priority_str(priority));
    kj_vprintf(fmt, v);
#endif
    va_end(v);
}

KJ_ASSERT_HANDLER(kj_assert_handler) {
    kj_unused(usr);
    va_list v;
    va_start(v, fmt);
#if defined(KJ_SYS_WIN32)
    char buf[4096];
    kj_zero(buf, kj_isize_of(buf));
    isize used = kj_snprintf(
            buf, kj_isize_of(buf),
            "FILE: %s\nLINE: %ld\nFUNC: %s\nEXPR: %s\nMSG:\n",
            file, line, fn, expr);
    used += kj_vsnprintf(buf + used, kj_isize_of(buf) - used, fmt, v);
    buf[used] = '\0';
    kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), buf);
    MessageBoxW(NULL, KJ__WCHAR_BUFA, L"Assert", MB_OK | MB_ICONERROR);
#else
    kj_printf(
            "FILE: %s\nLINE: %ld\nFUNC: %s\nEXPR: %s\nMSG:\n",
            file, line, fn, expr);
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
KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_DEPRECATED)
    res = _vsnprintf(buf, size, fmt, v);
KJ_COMPILER_WARNING_END
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
    if(c <= KJ_MAX_LATIN1) {
        return c == '\r' ||
               c == '\n' ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_ws(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
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
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <='Z') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_digit(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= '0' && c <= '9') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_alphanum(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_hex_digit(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'f') ||
               (c >= 'A' && c <= 'F') ||
               (c >= '0' && c <= '9') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_lower(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_upper(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'A' && c <= 'Z') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_separator(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
#if defined(KJ_SYS_WIN32)
        return (c == '\\' || c == '/') ? KJ_TRUE: KJ_FALSE;
#else
        return (c == '/') ? KJ_TRUE: KJ_FALSE;
#endif
    }
    return KJ_FALSE;
}

KJ_INLINE u32 kj_char_to_lower(u32 c) {
    if(c <= KJ_MAX_ASCII) {
        return (c >= 'A' && c <= 'Z') ? 'a' + (c - 'A'): c;
    }
    return c;
}

KJ_INLINE u32 kj_char_to_upper(u32 c) {
    if(c <= KJ_MAX_ASCII) {
        return (c >= 'a' && c <= 'z') ? 'A' + (c - 'a'): c;
    }
    return c;
}

KJ_INLINE isize kj_str_size(const char* s, isize size) {
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
        u64 overflow = KJ_U64_MAX / base + 1;
        u64 v;
        for(isize i = 0; i < size; i++) {
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
                *value = KJ_U64_MAX;
                res = KJ_ERR_RANGE;
                break;
            }
            *value *= base;
            u64 tmp = *value + v;
            if(tmp < *value || tmp > KJ_U64_MAX) {
                *value = KJ_U64_MAX;
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
        if(u <= KJ_I64_MAX) {
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
        for(isize i = 0; i < size; i++) {
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

const char* kj_str_find_predicate(
        const char* s, isize size, kjPredicateFn* fn) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    const char* sp = s;
    while(sp < (s + size) || (*sp && size == 0)) {
        if(fn(kj_cast(const void*, sp))) {
            res = sp;
            break;
        }
        sp++;
    }
    return res;
}

const char* kj_str_rfind_predicate(
        const char* s, isize size, kjPredicateFn* fn) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(s, 0): size;
    for(isize i = size - 1; i >= 0; i--) {
        if(fn(&s[i])) {
            res = &s[i];
            break;
        }
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
    for(isize i = size - 1; i >= 0; i--) {
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
        if(!kj_char_is_ws(*res)) {
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
    for(isize i = size - 1; i >= 0 && kj_char_is_ws(s[i]); i--, res--);
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

#if defined(KJ_SYS_WIN32)
i32 kj_utf8_to_ucs(WCHAR* ws, i32 count, const char* s) {
    if(s == NULL || ws == NULL || count <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    i32 res = KJ_ERR_NONE;
    res = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
    if(res < count) {
        MultiByteToWideChar(CP_UTF8, 0, s, -1, ws, count);
    } elif(ws != NULL && count != 0) {
        res = KJ_ERR_RANGE;
    }
    return res;
}

i32 kj_ucs_to_utf8(char* s, i32 count, const WCHAR* ws) {
    if(s == NULL || ws == NULL || count <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    i32 res = KJ_ERR_NONE;
    res = WideCharToMultiByte(CP_UTF8, 0, ws, -1, NULL, 0, NULL, NULL);
    if(res < count) {
        WideCharToMultiByte(
                CP_UTF8, 0, ws, -1,
                s, count, NULL, NULL);
    } elif(s != NULL && count != 0) {
        res = KJ_ERR_RANGE;
    }
    return res;
}

#endif

#if defined(KJ_LIB_IMPL)
KJ_INLINE kjErr kj_lib_open(kjLib* self, const char* path) {
    if(self == NULL || path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_isize_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(res)) {
        if((*self = LoadLibraryW(KJ__WCHAR_BUFA)) == NULL) {
            res = kj_err_from_sys(GetLastError());
        }
    }
#elif defined(KJ_SYS_UNIX)
    if((*self = kj_cast(kjLib, dlopen(path, RTLD_LAZY))) == NULL) {
        res = kj_err_from_sys(errno);
    }
#endif
    return kj_cast(kjErr, res);
}

KJ_INLINE kjErr kj_lib_fn(const kjLib* self, kjLibFn* fn, const char* name) {
    if(self == NULL || fn == NULL || name == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if((*fn = GetProcAddress(*self, name)) == NULL) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_PEDANTIC)
    if((*fn = kj_cast(kjLibFn, dlsym(*self, name))) == NULL) {
        res = kj_err_from_sys(errno);
    }
KJ_COMPILER_WARNING_END
#endif
    return res;
}

KJ_INLINE void kj_lib_close(const kjLib* self) {
    if(self == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    FreeLibrary(*self);
#elif defined(KJ_SYS_UNIX)
    dlclose(*self);
#endif
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
    for(isize i = 1; i < count; i++) {
        for(isize j = i - 1; j >= 0; j--) {
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
#if defined(KJ_SYS_WIN32)
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    return kj__filetime_to_unix(&ft);
#elif defined(KJ_SYS_UNIX)
    time_t t;
    time(&t);
    return kj_cast(u64, t);
#endif
}

u64 kj_datetime_to_timestamp(kjDateTime dt) {
    u64 res = KJ_U64_MAX;
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
#if defined(CLOCK_MONOTONIC_RAW)
#define KJ_CLOCK_MONOTONIC CLOCK_MONOTONIC_RAW
#elif defined(CLOCK_MONOTONIC)
#define KJ_CLOCK_MONOTONIC CLOCK_MONOTONIC
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
    for(isize i = 0; i < size; i++) {
        res += (*s++) * (kj_cast(u32, i % KJ_U32_MAX) + 119);
    }
    return res;
}

#define KJ_FILE_INVALID_FLAGS KJ_U32_MAX

kjErr kj_file_create(kjFile* self, const char* path) {
    return kj_file_open(
            self, path, KJ_FILE_WRITE | KJ_FILE_CREATE | KJ_FILE_TRUNCATE);
}

KJ_INLINE u32 kj__file_access_flags(u32 flags) {
    u32 res = 0;
#if defined(KJ_SYS_WIN32)
    if((flags & KJ_FILE_READ) &&
      !(flags & KJ_FILE_WRITE) &&
      !(flags & KJ_FILE_APPEND)) {
        res = GENERIC_READ;
    } elif(!(flags & KJ_FILE_READ) &&
            (flags & KJ_FILE_WRITE) &&
           !(flags & KJ_FILE_APPEND)) {
        res = GENERIC_WRITE;
    } elif((flags & KJ_FILE_READ) &&
           (flags & KJ_FILE_WRITE) &&
          !(flags & KJ_FILE_APPEND)) {
        res = GENERIC_READ | GENERIC_WRITE;
    } elif(!(flags & KJ_FILE_READ) &&
            (flags & KJ_FILE_APPEND)) {
        res = FILE_GENERIC_WRITE & ~FILE_WRITE_DATA;
    } elif((flags & KJ_FILE_READ) &&
           (flags & KJ_FILE_APPEND)) {
        res = GENERIC_READ | (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA);
    }
#elif defined(KJ_SYS_UNIX)
    if((flags & KJ_FILE_READ) &&
      !(flags & KJ_FILE_WRITE) &&
      !(flags & KJ_FILE_APPEND)) {
        res = O_RDONLY;
    } elif(!(flags & KJ_FILE_READ) &&
            (flags & KJ_FILE_WRITE) &&
           !(flags & KJ_FILE_APPEND)) {
        res = O_WRONLY;
    } elif((flags & KJ_FILE_READ) &&
           (flags & KJ_FILE_WRITE) &&
          !(flags & KJ_FILE_APPEND)) {
        res = O_RDWR;
    } elif(!(flags & KJ_FILE_READ) &&
            (flags & KJ_FILE_APPEND)) {
        res = O_WRONLY | O_APPEND;
    } elif((flags & KJ_FILE_READ) &&
           (flags & KJ_FILE_APPEND)) {
        res = O_RDWR | O_APPEND;
    }
#endif
    return res;
}

KJ_INLINE u32 kj__file_create_flags(u32 flags) {
    u32 res = 0;
#if defined(KJ_SYS_WIN32)
    if(!(flags & KJ_FILE_WRITE) &&
       !(flags & KJ_FILE_APPEND)) {
        if((flags & KJ_FILE_TRUNCATE) ||
           (flags & KJ_FILE_CREATE) ||
           (flags & KJ_FILE_CREATE_NEW)) {
            res = KJ_FILE_INVALID_FLAGS;
        }
    } elif(flags & KJ_FILE_APPEND) {
        if((flags & KJ_FILE_TRUNCATE) &&
          !(flags & KJ_FILE_CREATE_NEW)) {
            res = KJ_FILE_INVALID_FLAGS;
        }
    }
    if(res == 0) {
        if(!(flags & KJ_FILE_CREATE) &&
           !(flags & KJ_FILE_TRUNCATE) &&
           !(flags & KJ_FILE_CREATE_NEW)) {
            res = OPEN_EXISTING;
        } elif((flags & KJ_FILE_CREATE) &&
              !(flags & KJ_FILE_TRUNCATE) &&
              !(flags & KJ_FILE_CREATE_NEW)) {
            res = OPEN_ALWAYS;
        } elif(!(flags & KJ_FILE_CREATE) &&
                (flags & KJ_FILE_TRUNCATE) &&
               !(flags & KJ_FILE_CREATE_NEW)) {
            res = TRUNCATE_EXISTING;
        } elif((flags & KJ_FILE_CREATE) &&
               (flags & KJ_FILE_TRUNCATE) &&
              !(flags & KJ_FILE_CREATE_NEW)) {
            res = CREATE_ALWAYS;
        } elif(flags & KJ_FILE_CREATE_NEW) {
            res = CREATE_NEW;
        }
    }
#elif defined(KJ_SYS_UNIX)
    if(!(flags & KJ_FILE_WRITE) &&
       !(flags & KJ_FILE_APPEND)) {
        if((flags & KJ_FILE_TRUNCATE) ||
           (flags & KJ_FILE_CREATE) ||
           (flags & KJ_FILE_CREATE_NEW)) {
            res = KJ_FILE_INVALID_FLAGS;
        }
    } elif(flags & KJ_FILE_APPEND) {
        if((flags & KJ_FILE_TRUNCATE) &&
          !(flags & KJ_FILE_CREATE_NEW)) {
            res = KJ_FILE_INVALID_FLAGS;
        }
    }
    if(res == 0) {
        if((flags & KJ_FILE_CREATE) &&
          !(flags & KJ_FILE_TRUNCATE) &&
          !(flags & KJ_FILE_CREATE_NEW)) {
            res = O_CREAT;
        } elif(!(flags & KJ_FILE_CREATE) &&
                (flags & KJ_FILE_TRUNCATE) &&
               !(flags & KJ_FILE_CREATE_NEW)) {
            res = O_TRUNC;
        } elif((flags & KJ_FILE_CREATE) &&
               (flags & KJ_FILE_TRUNCATE) &&
              !(flags & KJ_FILE_CREATE_NEW)) {
            res = O_CREAT | O_TRUNC;
        } elif(flags & KJ_FILE_CREATE_NEW) {
            res = O_CREAT | O_EXCL;
        }
    }
#endif
    return res;
}

kjErr kj_file_open(kjFile* self, const char* path, u32 flags) {
    if(self == NULL || path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    u32 access = kj__file_access_flags(flags);
    u32 create = kj__file_create_flags(flags);
#if defined(KJ_SYS_WIN32)
    res = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_isize_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(res)) {
        *self = CreateFileW(
                KJ__WCHAR_BUFA, access,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                NULL, create, 0, NULL);
        if(*self == INVALID_HANDLE_VALUE) {
            res = kj_err_from_sys(GetLastError());
        } else {
            res = KJ_ERR_NONE;
        }
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    u32 perm = 0666;
    kj_syscall3(KJ_SYSCALL_OPEN, *self, path, (access | create), perm);
    res = *self < 0 ? kj_err_from_sys(-*self): KJ_ERR_NONE;
#else
    u32 perm = 0666;
    *self = open(path, (access | create), perm);
    res = *self < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
#endif
    return kj_cast(kjErr, res);
}

kjErr kj_file_close(const kjFile* self) {
    if(self == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!CloseHandle(*self)) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall1(KJ_SYSCALL_CLOSE, res, *self);
    res = res < 0 ? kj_err_from_sys(res): KJ_ERR_NONE;
#else
    res = close(*self);
    res = res < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
#endif
    return res;
}

kjErr kj_file_seek(const kjFile* self, i64 offset, kjSeekFrom seek) {
    if(self == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    LARGE_INTEGER li_offset;
    li_offset.QuadPart = offset;
    if(SetFilePointerEx(*self, li_offset, &li_offset, seek) == 0) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall3(KJ_SYSCALL_LSEEK, res, *self, offset, seek);
    res = res < 0 ? kj_err_from_sys(res): KJ_ERR_NONE;
#else
    res = lseek(*self, offset, seek);
    res = res < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
#endif
    return res;
}

isize kj_file_read(const kjFile* self, void* buf, isize size) {
    if(self == NULL || buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    DWORD read = 0;
    if(ReadFile(*self, buf, kj_cast(DWORD, size), &read, NULL)) {
        res = read;
    } else {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall3(KJ_SYSCALL_READ, res, *self, buf, size);
    res = res < 0 ? kj_cast(isize, kj_err_from_sys(res)): res;
#else
    res = read(*self, buf, size);
    res = res < 0 ? kj_err_from_sys(errno): res;
#endif
#endif
    return res;
}

isize kj_file_write(const kjFile* self, const void* buf, isize size) {
    if(self == NULL || buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    DWORD wrote = 0;
    if(WriteFile(*self, buf, kj_cast(DWORD, size), &wrote, NULL)) {
        res = wrote;
    } else {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall3(KJ_SYSCALL_WRITE, res, *self, buf, size);
    res = res < 0 ? kj_cast(isize, kj_err_from_sys(res)): res;
#else
    res = write(*self, buf, size);
    res = res < 0 ? kj_err_from_sys(errno): res;
#endif
#endif
    return res;
}

isize kj_file_read_at(const kjFile* self, void* buf, isize size, i64 offset) {
    if(self == NULL || buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped;
    kj_zero(&overlapped, kj_isize_of(OVERLAPPED));
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(*self, buf, kj_cast(DWORD, size), &read, &overlapped)) {
        res = read;
    } else {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall4(KJ_SYSCALL_PREAD, res, *self, buf, size, offset);
    res = res < 0 ? kj_cast(isize, kj_err_from_sys(res)): res;
#else
    res = pread(*self, buf, size, offset);
    res = res < 0 ? kj_err_from_sys(errno): res;
#endif
#endif
    return res;
}

isize kj_file_write_at(
        const kjFile* self, const void* buf, isize size, i64 offset) {
    if(self == NULL || buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped;
    kj_zero(&overlapped, kj_isize_of(OVERLAPPED));
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(*self, buf, kj_cast(DWORD, size), &wrote, &overlapped)) {
        res = wrote;
    } else {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall4(KJ_SYSCALL_PWRITE, res, *self, buf, size, offset);
    res = res < 0 ? kj_cast(isize, kj_err_from_sys(res)): res;
#else
    res = pwrite(*self, buf, size, offset);
    res = res < 0 ? kj_err_from_sys(errno): res;
#endif
#endif
    return res;
}

kjErr kj_file_sync(const kjFile* self) {
    if(self == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!FlushFileBuffers(*self)) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall1(KJ_SYSCALL_FSYNC, res, *self);
    res = res < 0 ? kj_err_from_sys(res): KJ_ERR_NONE;
#else
    res = fsync(*self);
    res = res < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
#endif
    return res;
}

kjErr kj_file_metadata(kjFileMetadata* self, const kjFile* file) {
    if(self == NULL || file == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    BY_HANDLE_FILE_INFORMATION info;
    if(GetFileInformationByHandle(*file, &info)) {
        self->size =
            (kj_cast(i64, info.nFileSizeHigh) << 32) |
            (kj_cast(i64, info.nFileSizeLow));
        self->last_access = kj__filetime_to_unix(&info.ftLastAccessTime);
        self->last_write = kj__filetime_to_unix(&info.ftLastWriteTime);
        if(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            self->type = KJ_DIR;
        } else {
            self->type = KJ_FILE;
        }
    } else {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_zero(&st, kj_isize_of(struct stat));
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall2(KJ_SYSCALL_FSTAT, res, *file, &st);
    res = res < 0 ? kj_err_from_sys(res): KJ_ERR_NONE;
#else
    res = fstat(*file, &st);
    res = res < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
    if(kj_is_ok(res)) {
        self->size = st.st_size;
        self->last_access = kj_cast(u64, st.st_atime);
        self->last_write = kj_cast(u64, st.st_mtime);
    }
#endif
    return kj_cast(kjErr, res);
}

kjErr kj_file_metadata_path(kjFileMetadata* self, const char* path) {
    if(self == NULL || path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    kjFile file;
    res = kj_file_open(&file, path, KJ_FILE_READ);
    if(kj_is_ok(res)) {
        res = kj_file_metadata(self, &file);
        kj_file_close(&file);
    }
    return res;
}

u64 kj_file_last_write_path(const char* path) {
    if(path == NULL) {
        return KJ_U64_MAX;
    }

    u64 res = KJ_U64_MAX;
    kjFileMetadata meta;
    if(kj_is_ok(kj_file_metadata_path(&meta, path))) {
        res = meta.last_write;
    }
    return res;
}

isize kj_file_slurp(
        void** data, kjAllocator* allocator, const char* path, b32 terminate) {
    if(data == NULL || allocator == NULL || path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    kjFile file;
    res = kj_file_open(&file, path, KJ_FILE_READ);
    if(kj_is_ok(res)) {
        kjFileMetadata meta;
        res = kj_file_metadata(&meta, &file);
        if(kj_is_ok(res)) {
            *data = kj_allocator_alloc(allocator, meta.size + 1);
            if(*data) {
                isize read = kj_file_read(&file, *data, meta.size);
                if(kj_is_ok(read)) {
                    if(terminate) {
                        kj_cast(u8*, *data)[meta.size] = '\0';
                    }
                    res = read;
                } else {
                    kj_allocator_free(allocator, *data);
                    *data = NULL;
                    res = read;
                }
            } else {
                res = KJ_ERR_ALLOC_FAILED;
            }
        }
        kj_file_close(&file);
    }
    return res;
}

isize kj_file_spit(const char* path, const void* buf, isize size) {
    if(path == NULL || buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    kjFile file;
    res = kj_file_open(&file, path, KJ_FILE_WRITE);
    if(kj_is_ok(res)) {
        res = kj_file_write(&file, buf, size);
        kj_file_close(&file);
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
        for(isize i = size - 1; i >= 0; i--) {
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

KJ_INTERN KJ_INLINE KJ_PREDICATE_FN(kj_path_is_separator) {
    return value && kj_char_is_separator(*kj_cast(const char*, value)) ?
        KJ_TRUE: KJ_FALSE;
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
        res = kj_str_rfind_predicate(path, size, kj_path_is_separator);
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
    *end = kj_str_rfind_predicate(path, size, kj_path_is_separator);
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

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(res) && !CreateDirectoryW(KJ__WCHAR_BUFA, NULL)) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall2(KJ_SYSCALL_MKDIR, res, path, S_IRWXU | S_IRGRP | S_IROTH);
    res = res < 0 ? kj_err_from_sys(res): KJ_ERR_NONE;
#else
    res = mkdir(path, S_IRWXU | S_IRGRP | S_IROTH);
    res = res < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
#endif
    return kj_cast(kjErr, res);
}

kjErr kj_path_remove_dir(const char* path) {
    if(path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(res) && !RemoveDirectoryW(KJ__WCHAR_BUFA)) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall1(KJ_SYSCALL_RMDIR, res, path);
    res = res < 0 ? kj_err_from_sys(res): KJ_ERR_NONE;
#else
    res = rmdir(path);
    res = res < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
#endif
    return kj_cast(kjErr, res);
}

kjErr kj_path_rename(const char* from, const char* to) {
    if(from == NULL || to == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    i32 ucs1 = kj_utf8_to_ucs(
            KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), from);
    i32 ucs2 = kj_utf8_to_ucs(KJ__WCHAR_BUFB, kj_count_of(KJ__WCHAR_BUFB), to);
    if(kj_is_ok(ucs1)) {
        if(kj_is_ok(ucs2)) {
            if(!MoveFileExW(
                        KJ__WCHAR_BUFA, KJ__WCHAR_BUFB,
                        MOVEFILE_REPLACE_EXISTING)) {
                res = kj_err_from_sys(GetLastError());
            }
        } else {
            res = ucs2;
        }
    } else {
        res = ucs1;
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall2(KJ_SYSCALL_RENAME, res, from, to);
    res = res < 0 ? kj_err_from_sys(res): KJ_ERR_NONE;
#else
    res = rename(from, to);
    res = res < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
#endif
    return kj_cast(kjErr, res);
}

isize kj_path_current_dir(char* path, isize size) {
    if(path == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    GetCurrentDirectoryW(kj_count_of(KJ__WCHAR_BUFA), KJ__WCHAR_BUFA);
    res = kj_ucs_to_utf8(path, kj_cast(i32, size), KJ__WCHAR_BUFA);
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall2(
            KJ_SYSCALL_GETCWD, res,
            KJ__CHAR_BUF, kj_count_of(KJ__CHAR_BUF));
    if(res < 0) {
        res = kj_err_from_sys(res);
#else
    char* cwd = getcwd(KJ__CHAR_BUF, kj_count_of(KJ__CHAR_BUF));
    res = kj_str_size(KJ__CHAR_BUF, 0);
    if(cwd == NULL) {
        res = kj_err_from_sys(errno);
#endif
    } elif(res > size) {
        res = KJ_ERR_RANGE;
    } else {
        kj_copy(path, KJ__CHAR_BUF, res);
        path[res] = '\0';
    }
#endif
    return kj_cast(kjErr, res);
}

kjErr kj_path_set_current_dir(const char* path) {
    if(path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(res) && !SetCurrentDirectoryW(KJ__WCHAR_BUFA)) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall1(KJ_SYSCALL_CHDIR, res, path);
    res = res < 0 ? kj_err_from_sys(res): KJ_ERR_NONE;
#else
    res = chdir(path);
    res = res < 0 ? kj_err_from_sys(errno): KJ_ERR_NONE;
#endif
#endif
    return kj_cast(kjErr, res);
}

isize kj_path_tmp_dir(char* path, isize size) {
    if(path == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    DWORD wsize = GetTempPathW(0, NULL);
    GetTempPathW(wsize, KJ__WCHAR_BUFA);
    res = kj_ucs_to_utf8(path, kj_cast(i32, size), KJ__WCHAR_BUFA);
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
        res = KJ_ERR_RANGE;
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
    res = GetModuleFileNameW(
            NULL, KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA));
    res = kj_ucs_to_utf8(path, kj_cast(i32, size), KJ__WCHAR_BUFA);
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall3(
            KJ_SYSCALL_READLINK, res, "/proc/self/exe",
            KJ__CHAR_BUF, kj_count_of(KJ__CHAR_BUF));
    if(res < 0) {
        res = kj_err_from_sys(res);
#else
    res = chdir(path);
    if(res < 0) {
        res = kj_err_from_sys(errno);
#endif
    } elif(res > size) {
        res = KJ_ERR_RANGE;
    } else {
        kj_copy(path, KJ__CHAR_BUF, res);
        path[res] = '\0';
    }
#endif
    return res;
}

b32 kj_path_exists(const char* path) {
    if(path == NULL) {
        return KJ_FALSE;
    }

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    i32 ucs = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(ucs)) {
        HANDLE h = INVALID_HANDLE_VALUE;
        WIN32_FIND_DATAW find;
        if((h = FindFirstFileW(KJ__WCHAR_BUFA, &find)) !=
                INVALID_HANDLE_VALUE) {
            FindClose(h);
            res = KJ_TRUE;
        }
    }
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall2(KJ_SYSCALL_ACCESS, res, path, 0);
    res = res == 0 ? KJ_TRUE: KJ_FALSE;
#else
    res = access(path, 0);
    res = res == 0 ? KJ_TRUE: KJ_FALSE;
#endif
#endif
    return res;
}

b32 kj_path_is_file(const char* path) {
    if(path == NULL) {
        return KJ_FALSE;
    }

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    i32 ucs = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(ucs)) {
        DWORD attr = INVALID_FILE_ATTRIBUTES;
        if((attr = GetFileAttributesW(KJ__WCHAR_BUFA))
                != INVALID_FILE_ATTRIBUTES) {
            res = attr & FILE_ATTRIBUTE_DIRECTORY ? KJ_FALSE: KJ_TRUE;
        }
    }
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_zero(&st, kj_isize_of(struct stat));
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall2(KJ_SYSCALL_STAT, res, path, &st);
#else
    res = stat(path, &st);
#endif
    res = res == 0 ? S_ISREG(st.st_mode) != 0: KJ_FALSE;
#endif
    return res;
}

b32 kj_path_is_dir(const char* path) {
    if(path == NULL) {
        return KJ_FALSE;
    }

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    i32 ucs = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(ucs)) {
        DWORD attr = INVALID_FILE_ATTRIBUTES;
        if((attr = GetFileAttributesW(KJ__WCHAR_BUFA)) !=
                INVALID_FILE_ATTRIBUTES) {
            res = attr & FILE_ATTRIBUTE_DIRECTORY ? KJ_TRUE: KJ_FALSE;
        }
    }
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_zero(&st, kj_isize_of(struct stat));
#if defined(KJ_SYS_LINUX) && defined(KJ_ARCH_X86)
    kj_syscall2(KJ_SYSCALL_STAT, res, path, &st);
#else
    res = stat(path, &st);
#endif
    res = res == 0 ? S_ISDIR(st.st_mode) != 0: KJ_FALSE;
#endif
    return res;
}

kjErr kj_read_dir_begin(kjReadDir* self, const char* path) {
    if(self == NULL || path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    kj_zero(self, kj_isize_of(kjReadDir));
#if defined(KJ_SYS_WIN32)
    WIN32_FIND_DATAW find;
    i32 ucs = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_count_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(ucs)) {
        if(KJ__WCHAR_BUFA[ucs - 1] == KJ_PATH_SEPARATOR) {
            KJ__WCHAR_BUFA[ucs] = '*';
            KJ__WCHAR_BUFA[ucs + 1] = '\0';
        } else {
            KJ__WCHAR_BUFA[ucs - 1] = KJ_PATH_SEPARATOR;
            KJ__WCHAR_BUFA[ucs] = '*';
            KJ__WCHAR_BUFA[ucs + 1] = '\0';
        }
        HANDLE handle = FindFirstFileW(KJ__WCHAR_BUFA, &find);
        if(handle != INVALID_HANDLE_VALUE) {
            self->find = find;
            self->handle = handle;
            self->first = KJ_TRUE;
        } else {
            res = kj_err_from_sys(GetLastError());
        }
    }
#elif defined(KJ_SYS_UNIX)
    if((self->dir = opendir(path)) == NULL) {
        res = kj_err_from_sys(errno);
    }
#endif
    return kj_cast(kjErr, res);
}

kjErr kj_read_dir_next(kjReadDir* self, kjDirEntry* entry) {
    if(self == NULL || entry == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(self->first || FindNextFileW(self->handle, &self->find)) {
        res = kj_ucs_to_utf8(
                entry->path, kj_count_of(entry->path), self->find.cFileName);
        entry->count = res - 1;
        self->first = KJ_FALSE;
    } else {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_UNIX)
    struct dirent* result = NULL;
    struct dirent* ent = kj_cast(struct dirent*, entry->path);
    i32 err = 0;
    if((err = readdir_r(self->dir, ent, &result)) != 0) {
        res = kj_err_from_sys(err);
    }
    if(result) {
        isize size = kj_str_size(ent->d_name, KJ_PATH_MAX);
        kj_copy(entry->path, &ent->d_name[0], size);
        entry->path[size] = '\0';
    } else {
        res = KJ_ERR_NO_MORE_FILES;
    }
#endif
    return kj_cast(kjErr, res);
}

void kj_read_dir_end(kjReadDir* self) {
    if(self == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    if(self->handle) {
        FindClose(self->handle);
    }
#elif defined(KJ_SYS_UNIX)
    if(self->dir) {
        closedir(self->dir);
    }
#endif
}

kjErr kj_buffer(
        kjBuffer* self, kjAllocator* allocator, isize granularity) {
    if(self == NULL || allocator == NULL || granularity <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    self->data = NULL;
    self->capacity = 0;
    self->size = 0;
    self->granularity = granularity;
    self->allocator = allocator;
    return res;
}

void kj_buffer_destroy(kjBuffer* self) {
    if(self && self->data) {
        kj_allocator_free(self->allocator, self->data);
        self->data = NULL;
    }
}

kjErr kj_buffer_write(kjBuffer* self, const void* buf, isize size) {
    if(self == NULL || buf == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
    if(self->size + size > self->capacity) {
        isize new_size = kj_round_to(self->capacity + size, self->granularity);
        void* new_data = NULL;
        if(self->data) {
             new_data = kj_allocator_realloc(
                    self->allocator, self->data, new_size);
        } else {
             new_data = kj_allocator_alloc(self->allocator, new_size);
        }
        if(new_data) {
            self->data = kj_cast(u8*, new_data);
            self->capacity = size;
        } else {
            res = KJ_ERR_ALLOC_FAILED;
        }
    }
    if(kj_is_ok(res)) {
        kj_copy(self->data + self->size, buf, size);
        self->size += size;
    }

#if defined(KJ_DEBUG)
    if(self->size < self->capacity) {
        self->data[self->size] = '\0';
    }
#endif

    return kj_cast(kjErr, res);
}

void kj_buffer_reset(kjBuffer* self) {
    if(self == NULL || self->data == NULL) {
        return;
    }

    self->size = 0;
}

#if defined(KJ_DIALOG_IMPL)

#if defined(KJ_SYS_WIN32)
#include <commdlg.h>
#pragma comment(lib, "comdlg32.lib")
#elif defined(KJ_SYS_LINUX)
#undef loop
#include <gtk/gtk.h>
#endif

isize kj_file_dialog(char* path, isize size, u32 mode, const char* filters) {
    if(path == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    static const WCHAR* ALL_FILES = L"All Files (*.*)|*.*|";
    static const i32 ALL_FILES_SIZE = 20 * kj_isize_of(WCHAR);
    kj_copy(KJ__WCHAR_BUFB, ALL_FILES, ALL_FILES_SIZE);
    res = kj_utf8_to_ucs(
            KJ__WCHAR_BUFB + (ALL_FILES_SIZE / kj_isize_of(WCHAR)),
            kj_count_of(KJ__WCHAR_BUFB) - (ALL_FILES_SIZE / kj_isize_of(WCHAR)),
            filters);
    if(kj_is_ok(res)) {
        for(i32 i = 0; KJ__WCHAR_BUFB[i] != '\0'; i++) {
            if(KJ__WCHAR_BUFB[i] == '|') {
                KJ__WCHAR_BUFB[i] = '\0';
            }
        }
        OPENFILENAMEW ofn;
        kj_zero(&ofn, kj_isize_of(OPENFILENAMEW));
        ofn.lStructSize = kj_isize_of(OPENFILENAMEW);
        ofn.hwndOwner = GetActiveWindow();
        ofn.lpstrFilter = KJ__WCHAR_BUFB;
        ofn.lpstrFile = KJ__WCHAR_BUFA;
        ofn.nMaxFile = KJ_PATH_MAX;
        ofn.lpstrTitle = mode & KJ_DIALOG_OPEN ? L"Open": L"Save As";
        ofn.Flags =
            OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |
            OFN_NOLONGNAMES | OFN_NOCHANGEDIR | OFN_CREATEPROMPT;
        b32 success = mode & KJ_DIALOG_OPEN ?
            GetOpenFileNameW(&ofn): GetSaveFileNameW(&ofn);
        if(success) {
            res = kj_ucs_to_utf8(path, kj_cast(i32, size), KJ__WCHAR_BUFA);
        } else {
            switch(CommDlgExtendedError()) {
                case 0x3003: { res = KJ_ERR_RANGE; } break;
                case 0x3002: { res = KJ_ERR_NOT_FOUND; } break;
                default: { res = KJ_ERR_UNKNOWN; } break;
            }
        }
    }
#else
    if(gtk_init_check(NULL, NULL)) {
        GtkWidget* gwindow = gtk_window_new(GTK_WINDOW_POPUP);
        GtkWidget* gdialog = gtk_file_chooser_dialog_new(
                mode & KJ_DIALOG_OPEN ? "Open": "Save As",
                GTK_WINDOW(gwindow),
                mode & KJ_DIALOG_OPEN ? GTK_FILE_CHOOSER_ACTION_OPEN:
                GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL,
                mode & KJ_DIALOG_OPEN ? "_Open": "_Save", GTK_RESPONSE_ACCEPT,
                NULL);
        if(mode & KJ_DIALOG_SAVE) {
            gtk_file_chooser_set_do_overwrite_confirmation(
                    GTK_FILE_CHOOSER(gdialog), KJ_TRUE);
        }

        GtkFileChooser* gchooser = GTK_FILE_CHOOSER(gdialog);
        GtkFileFilter* gfilter = gtk_file_filter_new();
        gtk_file_filter_set_name(gfilter, "All Files (*.*)");
        gtk_file_filter_add_pattern(gfilter, "*.*");
        gtk_file_chooser_add_filter(gchooser, gfilter);
        gfilter = gtk_file_filter_new();

        isize offset = 0;
        isize filters_size = kj_str_size(filters, 0);
        if(filters_size < kj_count_of(KJ__CHAR_BUF)) {
            kj_copy(KJ__CHAR_BUF, filters, filters_size);
            KJ__CHAR_BUF[filters_size] = '\0';
            b32 pattern = KJ_FALSE;
            for(isize i = 0; i <= filters_size; i++) {
                if(KJ__CHAR_BUF[i] == '|' && !pattern) {
                    pattern = KJ_TRUE;
                    KJ__CHAR_BUF[i] = '\0';
                    gtk_file_filter_set_name(gfilter, KJ__CHAR_BUF + offset);
                    offset = i + 1;
                } elif(KJ__CHAR_BUF[i] == ';' && pattern) {
                    KJ__CHAR_BUF[i] = '\0';
                    gtk_file_filter_add_pattern(gfilter, KJ__CHAR_BUF + offset);
                    offset = i + 1;
                } elif(KJ__CHAR_BUF[i] == '|') {
                    pattern = KJ_FALSE;
                    KJ__CHAR_BUF[i] = '\0';
                    gtk_file_filter_add_pattern(gfilter, KJ__CHAR_BUF + offset);
                    gtk_file_chooser_add_filter(gchooser, gfilter);
                    gfilter = gtk_file_filter_new();
                    offset = i + 1;
                } elif(KJ__CHAR_BUF[i] == '\0') {
                    gtk_file_chooser_add_filter(gchooser, gfilter);
                }
            }

            gint response = gtk_dialog_run(GTK_DIALOG(gdialog));
            if(response == GTK_RESPONSE_ACCEPT) {
                char* gpath = gtk_file_chooser_get_filename(gchooser);
                if(gpath != NULL) {
                    isize gpath_size = kj_str_size(gpath, 0);
                    if(gpath_size < size) {
                        kj_copy(path, gpath, gpath_size);
                    } else {
                        res = KJ_ERR_RANGE;
                    }
                    g_free(gpath);
                } else {
                    switch(GTK_FILE_CHOOSER_ERROR) {
                        case GTK_FILE_CHOOSER_ERROR_NONEXISTENT:
                        case GTK_FILE_CHOOSER_ERROR_BAD_FILENAME: {
                            res = KJ_ERR_NOT_FOUND;
                        } break;
                        case GTK_FILE_CHOOSER_ERROR_ALREADY_EXISTS: {
                            res = KJ_ERR_ALREADY_EXISTS;
                        } break;
                        default: {
                            res = KJ_ERR_UNKNOWN;
                        } break;
                    }
                }
            }
        } else {
            res = KJ_ERR_RANGE;
        }
        while(gtk_events_pending()) {
            gtk_main_iteration();
        }
        gtk_widget_destroy(gdialog);
        gtk_widget_destroy(gwindow);
    } else {
        res = kj_err_from_sys(errno);
    }
#endif
    return res;
}
#endif

#endif
