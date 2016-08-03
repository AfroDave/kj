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
#define KJ_VERSION_MINOR 10
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
#define KJ_SYS_WIN32
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#if !defined(VC_EXTRALEAN)
#define VC_EXTRALEAN
#endif
#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#if !defined(_UNICODE)
#define _UNICODE
#endif
#if !defined(UNICODE)
#define UNICODE
#endif
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <stdint.h>
#define KJ_SYS_NAME "windows"
#define KJ_SYS_DLL_EXT "dll"
#define KJ_SYS_EXE_EXT "exe"
#pragma comment(lib, "kernel32.lib")
#if defined(KJ_MESSAGE_BOX)
#pragma comment(lib, "user32.lib")
#endif
#if defined(KJ_DIALOG)
#include <commdlg.h>
#pragma comment(lib, "comdlg32.lib")
#endif
#elif defined(__linux__)
#define KJ_SYS_LINUX
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <time.h>
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#define KJ_SYS_NAME "linux"
#define KJ_SYS_DLL_EXT "so"
#define KJ_SYS_EXE_EXT ""
#else
#error Unsupported Operating System
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_NAME "x86_64"
#else
#error Unsupported Architecture
#endif

#if !defined(kj_str_of)
#define kj_str_of(a) #a
#endif

#if defined(_MSC_VER)
#define KJ_COMPILER_MSVC
#define KJ_PRAGMA(...) __pragma(__VA_ARGS__)
#define KJ_COMPILER_WARNING_BEGIN __pragma(warning(push))
#define KJ_COMPILER_WARNING_END __pragma(warning(pop))
#define KJ_COMPILER_WARNING(W) __pragma(warning(disable:W))
#define KJ_COMPILER_WARNING_ZERO_SIZED_ARRAY 4200
#define KJ_COMPILER_WARNING_ANONYMOUS_STRUCT 4201
#define KJ_COMPILER_WARNING_MISSING_BRACES
#elif defined(__clang__)
#define KJ_COMPILER_CLANG
#define KJ_PRAGMA(...) _Pragma(kj_str_of(__VA_ARGS__))
#define KJ_COMPILER_WARNING_BEGIN _Pragma(kj_str_of(clang diagnostic push))
#define KJ_COMPILER_WARNING_END _Pragma(kj_str_of(clang diagnostic pop))
#define KJ_COMPILER_WARNING(W) _Pragma(kj_str_of(clang diagnostic ignored W))
#define KJ_COMPILER_WARNING_ZERO_SIZED_ARRAY kj_str_of(-Wzero-length-array)
#define KJ_COMPILER_WARNING_ANONYMOUS_STRUCT kj_str_of(-Wpedantic)
#define KJ_COMPILER_WARNING_MISSING_BRACES kj_str_of(-Wmissing-braces)
#elif defined(__GNUC__) || defined(__GNUG__)
#define KJ_COMPILER_GNU
#define KJ_PRAGMA(...) _Pragma(kj_str_of(__VA_ARGS__))
#define KJ_COMPILER_WARNING_BEGIN _Pragma(kj_str_of(GCC diagnostic push))
#define KJ_COMPILER_WARNING_END _Pragma(kj_str_of(GCC diagnostic pop))
#define KJ_COMPILER_WARNING(W) _Pragma(kj_str_of(GCC diagnostic ignored W))
#define KJ_COMPILER_WARNING_ZERO_SIZED_ARRAY kj_str_of(-Wpedantic)
#define KJ_COMPILER_WARNING_ANONYMOUS_STRUCT kj_str_of(-Wpedantic)
#define KJ_COMPILER_WARNING_MISSING_BRACES kj_str_of(-Wmissing-braces)
#else
#error Unsupported Compiler
#endif

#define KJ_FALSE (0 != 0)
#define KJ_TRUE (0 == 0)

enum {
    KJ_MAX_ASCII = 0x7F,
    KJ_MAX_LATIN1 = 0xFF,
    KJ_MAX_UNICODE = 0x10FFFF,
    KJ_BIT_FLAG_NONE = 0,
#if defined(KJ_SYS_WIN32)
    KJ_PATH_MAX = 4096,
    KJ_NAME_MAX = 255,
    KJ_PATH_SEPARATOR = '\\'
#elif defined(KJ_SYS_LINUX)
    KJ_PATH_MAX = PATH_MAX,
    KJ_NAME_MAX = NAME_MAX,
    KJ_PATH_SEPARATOR = '/'
#endif
};

#if defined(KJ_SYS_WIN32)
#define KJ_PATH_SEPARATOR_STR "\\"
#elif defined(KJ_SYS_LINUX)
#define KJ_PATH_SEPARATOR_STR "/"
#endif

#define KJ_LE 1234
#define KJ_BE 4321

#if defined(KJ_SYS_LINUX)
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
#define KJ_I8_MIN (-kj_cast(i8, 128))
#define KJ_I8_MAX (kj_cast(i8, 127))
#define KJ_I16_MIN (-kj_cast(i16, 32768))
#define KJ_I16_MAX (kj_cast(i16, 32767))
#define KJ_I32_MIN (-kj_cast(i32, 2147483648))
#define KJ_I32_MAX (kj_cast(i32, 2147483647))
#define KJ_I64_MIN (-kj_cast(i64, 9223372036854775807))
#define KJ_I64_MAX (kj_cast(i64, 9223372036854775807))

#define KJ_U8_MIN (kj_cast(u8, 0x00))
#define KJ_U8_MAX (kj_cast(u8, 0xFF))
#define KJ_U16_MIN (kj_cast(u16, 0x0000))
#define KJ_U16_MAX (kj_cast(u16, 0xFFFF))
#define KJ_U32_MIN (kj_cast(u32, 0x00000000))
#define KJ_U32_MAX (kj_cast(u32, 0xFFFFFFFF))
#define KJ_U64_MIN (kj_cast(u64, 0x0000000000000000))
#define KJ_U64_MAX (kj_cast(u64, 0xFFFFFFFFFFFFFFFF))
#endif

typedef i32 b32;

typedef i64 isize;
typedef u64 usize;

#if !defined(KJ_ISIZE_MIN)
#define KJ_ISIZE_MIN KJ_I64_MIN
#define KJ_ISIZE_MAX KJ_I64_MAX
#define KJ_USIZE_MIN KJ_U64_MIN
#define KJ_USIZE_MAX KJ_U64_MAX
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

typedef enum kjType {
    KJ_TYPE_UNKNOWN = -1,
#define KJ_TYPE_ENUM(type, name, T) type,
    KJ_TYPE_MAP(KJ_TYPE_ENUM)
#undef KJ_TYPE_ENUM
    KJ_TYPE_COUNT
} kjType;

KJ_API const char* kj_type_to_str(kjType type);
KJ_API isize kj_type_to_isize(kjType type);

#define KJ_ERR_MAP(X)                                                           \
    X(KJ_ERR_NONE, "None")                                                      \
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
    X(KJ_ERR_ALLOC_FAILED, "Alloc Fail")                                        \
    X(KJ_ERR_ADDR_IN_USE, "Address In Use")                                     \
    X(KJ_ERR_ADDR_NOT_AVAILABLE, "Address Not Available")                       \
    X(KJ_ERR_CONNECTION_ABORTED, "Connection Aborted")                          \
    X(KJ_ERR_CONNECTION_REFUSED, "Connection Refused")                          \
    X(KJ_ERR_CONNECTION_RESET, "Connection Reset")                              \
    X(KJ_ERR_NOT_CONNECTED, "Not Connected")                                    \
    X(KJ_ERR_WOULD_BLOCK, "Would Block")                                        \
    X(KJ_ERR_INSUFFICIENT_BUFFER, "Insufficient Buffer")                        \
    X(KJ_ERR_INVALID_UTF8, "Invalid UTF-8")                                     \
    X(KJ_ERR_NO_MORE_FILES, "No More Files")                                    \
    X(KJ_ERR_RANGE, "Value Out of Range")                                       \
    X(KJ_ERR_SYNTAX, "Invalid Syntax")

typedef enum kjErr {
    KJ_ERR_UNKNOWN = -1,
#define KJ_ERR_ENUM(type, name) type,
    KJ_ERR_MAP(KJ_ERR_ENUM)
#undef KJ_ERR_ENUM
    KJ_ERR_COUNT
} kjErr;

KJ_API kjErr kj_err_from_sys(i32 err);
KJ_API const char* kj_err_to_str(kjErr err);

#define kj_is_ok(r) ((r).err == KJ_ERR_NONE)
#define kj_is_err(r) ((r).err != KJ_ERR_NONE)
#define KJ_RESULT(T) struct { T val; kjErr err; }
#define KJ_RESULT_SIZED(T) struct { T val; isize size; kjErr err; }
typedef KJ_RESULT(char) char$;
typedef KJ_RESULT(i8) i8$;
typedef KJ_RESULT(u8) u8$;
typedef KJ_RESULT(i16) i16$;
typedef KJ_RESULT(u16) u16$;
typedef KJ_RESULT(i32) i32$;
typedef KJ_RESULT(u32) u32$;
typedef KJ_RESULT(i64) i64$;
typedef KJ_RESULT(u64) u64$;
typedef KJ_RESULT(isize) isize$;
typedef KJ_RESULT(usize) usize$;
typedef KJ_RESULT_SIZED(char*) char$$;
typedef KJ_RESULT_SIZED(i8*) i8$$;
typedef KJ_RESULT_SIZED(u8*) u8$$;
typedef KJ_RESULT_SIZED(i16*) i16$$;
typedef KJ_RESULT_SIZED(u16*) u16$$;
typedef KJ_RESULT_SIZED(i32*) i32$$;
typedef KJ_RESULT_SIZED(u32*) u32$$;
typedef KJ_RESULT_SIZED(i64*) i64$$;
typedef KJ_RESULT_SIZED(u64*) u64$$;
typedef KJ_RESULT_SIZED(isize*) isize$$;
typedef KJ_RESULT_SIZED(usize*) usize$$;
typedef KJ_RESULT_SIZED(void*) void$$;

/// Memory

enum {
    KJ_ALLOC_NONE = KJ_BIT_FLAG_NONE,
    KJ_ALLOC_ZERO = KJ_BIT_FLAG(0)
};

KJ_API void* kj_global_alloc(isize size, u32 flags);
KJ_API void kj_global_free(void* data, u32 flags);
KJ_API void* kj_global_realloc(void* data, isize size, u32 flags);
KJ_API void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags);

typedef struct kjAllocator kjAllocator;

#define KJ_ALLOCATOR_ALLOC_FN(name)                                             \
    void* name(const kjAllocator* self, isize size)
typedef KJ_ALLOCATOR_ALLOC_FN(kjAllocatorAllocFn);
#define KJ_ALLOCATOR_FREE_FN(name)                                              \
    void name(const kjAllocator* self, void* data)
typedef KJ_ALLOCATOR_FREE_FN(kjAllocatorFreeFn);
#define KJ_ALLOCATOR_REALLOC_FN(name)                                           \
    void* name(const kjAllocator* self, void* data, isize size)
typedef KJ_ALLOCATOR_REALLOC_FN(kjAllocatorReallocFn);
#define KJ_ALLOCATOR_ALLOC_ALIGNED_FN(name)                                     \
    void* name(const kjAllocator* self, isize size, isize alignment)
typedef KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kjAllocatorAllocAlignedFn);

typedef struct kjAllocator {
    kjAllocatorAllocFn* alloc;
    kjAllocatorFreeFn* free;
    kjAllocatorReallocFn* realloc;
    kjAllocatorAllocAlignedFn* alloc_aligned;
    u32 flags;
} kjAllocator;

#define kj_allocator_alloc(a, s)                                                \
    kj_cast(kjAllocator*, (a))->alloc(kj_cast(kjAllocator*, (a)), (s))
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
KJ_API KJ_ALLOCATOR_FREE_FN(kj_heap_free);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc);

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
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc);

/// Debug

#define KJ_ASSERT_HANDLER(name) void name(                                      \
        const char* expr, const char* file, isize line, const char* fn,         \
        const char* msg, void* usr)

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
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_CUR_FN __PRETTY_FUNCTION__
#endif

#if defined(KJ_COMPILER_MSVC)
#define kj_break() do { __debugbreak(); } while(0)
#define kj_unreachable() do { __assume(0); } while(0)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_break() do { __builtin_trap(); } while(0)
#define kj_unreachable() do { __builtin_unreachable(); } while(0)
#endif

#if !defined(KJ_NO_DEBUG)
#define kj_assert(expr, msg) do {                                               \
    if(!(expr)) {                                                               \
        KJ_CUSTOM_ASSERT_HANDLER(                                               \
                kj_str_of(expr),                                                \
                KJ_CUR_FILE, KJ_CUR_LINE, KJ_CUR_FN,                            \
                msg, KJ_CUSTOM_ASSERT_USR);                                     \
        kj_break();                                                             \
    }                                                                           \
} while(0)
#define kj_panic(msg) do {                                                      \
    KJ_CUSTOM_ASSERT_HANDLER(                                                   \
            "PANIC",                                                            \
            KJ_CUR_FILE, KJ_CUR_LINE, KJ_CUR_FN,                                \
            msg, KJ_CUSTOM_ASSERT_USR);                                         \
    kj_break();                                                                 \
} while(0)
#else
#define kj_assert(expr, msg)
#define kj_panic(msg)
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

/// Linux syscalls

#if defined(KJ_SYS_LINUX)
#if !defined(kj_syscall1)
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

#define kj_syscall1(call, res, a) do {                                          \
    __asm volatile(                                                             \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)));                                             \
} while(0)
#define kj_syscall2(call, res, a, b) do {                                       \
    __asm volatile(                                                             \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)));                                  \
} while(0)
#define kj_syscall3(call, res, a, b, c) do {                                    \
    __asm volatile(                                                             \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)), "d" ((c)));                       \
} while(0)
#define kj_syscall4(call, res, a, b, c, d) do {                                 \
    register i64 r10 __asm("r10") = (d);                                        \
    __asm volatile(                                                             \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)), "d" ((c)), "r" (r10));            \
} while(0)
#define kj_syscall5(call, res, a, b, c, d, e) do {                              \
    register i64 r10 __asm("r10") = (d);                                        \
    register i64 r8 __asm("r8") = (e);                                          \
    __asm volatile(                                                             \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)), "d" ((c)), "r" (r10), "r", (r8)); \
} while(0)
#define kj_syscall6(call, res, a, b, c, d, e, f) do {                           \
    register i64 r10 __asm("r10") = (d);                                        \
    register i64 r8 __asm("r8") = (e);                                          \
    register i64 r9 __asm("r9") = (f);                                          \
    __asm volatile(                                                             \
        "syscall"                                                               \
        : "=a" (res)                                                            \
        : "0" ((call)), "D" ((a)), "S" ((b)), "d" ((c)), "r" (r10), "r", (r8),  \
          "r", (r9));                                                           \
} while(0)
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

KJ_API isize kj_str_size_limit(const char* s, isize limit);
KJ_API isize kj_str_size(const char* s);

KJ_API isize kj_str_cmp_limit(const char* s1, const char* s2, isize limit);
KJ_API isize kj_str_cmp(const char* s1, const char* s2);
KJ_API isize kj_str_case_cmp_limit(const char* s1, const char* s2, isize limit);
KJ_API isize kj_str_case_cmp(const char* s1, const char* s2);

KJ_API u64$ kj_str_to_u64(const char* s, isize size);
KJ_API i64$ kj_str_to_i64(const char* s, isize size);

KJ_API const char* kj_str_find(const char* s, isize size, char c);
KJ_API const char* kj_str_rfind(const char* s, isize size, char c);

KJ_API char* kj_str_replace_char(char* s, isize size, char o, char n);

KJ_API const char* kj_str_trim(const char* s, isize size, const char** end);
KJ_API const char* kj_str_ltrim(const char* s, isize size);
KJ_API const char* kj_str_rtrim(const char* s, isize size);

KJ_API isize kj_utf8_count_limit(const char* s, isize limit);
KJ_API isize kj_utf8_count(const char* s);

#if defined(KJ_SYS_WIN32)
typedef KJ_RESULT_SIZED(WCHAR*) WCHAR$$;
KJ_API i32$ kj_utf8_to_ucs(const char* s, WCHAR* ws, i32 count);
KJ_API i32$ kj_ucs_to_utf8(const WCHAR* ws, char* s, i32 count);
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
#elif defined(KJ_SYS_LINUX)
typedef void* kjLib;
typedef void (*kjLibFn)(void);
#endif
typedef KJ_RESULT(kjLib) kjLib$;
typedef KJ_RESULT(kjLibFn) kjLibFn$;
KJ_API kjLib$ kj_lib_open(const char* path);
KJ_API kjLibFn$ kj_lib_fn(kjLib* self, const char* name);
KJ_API void kj_lib_close(kjLib* self);

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
#elif defined(KJ_SYS_LINUX)
typedef i32 kjFile;
#endif

typedef KJ_RESULT(kjFile) kjFile$;

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

typedef KJ_RESULT(kjFileMetadata) kjFileMetadata$;

KJ_API kjFile$ kj_file_create(const char* path);
KJ_API kjFile$ kj_file_open(const char* path, u32 flags);
KJ_API kjErr kj_file_close(const kjFile* self);
KJ_API kjErr kj_file_seek(const kjFile* self, i64 offset, kjSeekFrom seek);
KJ_API isize$ kj_file_read(const kjFile* self, void* buf, isize size);
KJ_API isize$ kj_file_write(const kjFile* self, const void* buf, isize size);
KJ_API isize$ kj_file_read_at(
        const kjFile* self, void* buf, isize size, i64 offset);
KJ_API isize$ kj_file_write_at(
        const kjFile* self, const void* buf, isize size, i64 offset);
KJ_API kjErr kj_file_sync(const kjFile* self);
KJ_API void$$ kj_file_slurp(kjAllocator* self, const char* path, b32 terminate);
KJ_API isize$ kj_file_spit(const char* path, const void* buf, isize size);

KJ_API kjFileMetadata$ kj_file_metadata(const kjFile* file);
KJ_API kjFileMetadata$ kj_file_metadata_path(const char* path);

/// Paths

KJ_API const char* kj_path_ext(const char* path, isize size);
KJ_API const char* kj_path_base(const char* path, isize size, const char** end);
KJ_API const char* kj_path_dir(const char* path, isize size, const char** end);
KJ_API kjErr kj_path_create_dir(const char* path);
KJ_API kjErr kj_path_remove_dir(const char* path);
KJ_API kjErr kj_path_rename(const char* from, const char* to);
KJ_API isize$ kj_path_current_dir(char* path, isize size);
KJ_API kjErr kj_path_set_current_dir(const char* path);
KJ_API isize$ kj_path_tmp_dir(char* path, isize size);
KJ_API isize$ kj_path_self(char* path, isize size);
KJ_API b32 kj_path_exists(const char* path);
KJ_API b32 kj_path_is_file(const char* path);
KJ_API b32 kj_path_is_dir(const char* path);

typedef struct kjReadDir {
#if defined(KJ_SYS_WIN32)
    WIN32_FIND_DATAW find;
    HANDLE handle;
    b32 first;
#elif defined(KJ_SYS_LINUX)
    DIR* dir;
#endif
} kjReadDir;

typedef struct kjDirEntry {
    char path[KJ_PATH_MAX + 1];
    isize count;
} kjDirEntry;

KJ_API kjErr kj_read_dir_begin(kjReadDir* self, const char* path);
KJ_API kjErr kj_read_dir_next(kjReadDir* self, kjDirEntry* entry);
KJ_API void kj_read_dir_end(kjReadDir* self);

/// Buffer

typedef struct kjBuffer {
    kjAllocator* allocator;
    isize granularity;
    isize size;
    isize used;
    u8* data;
} kjBuffer;

KJ_API kjBuffer kj_buffer(kjAllocator* allocator, isize granularity);
KJ_API void kj_buffer_destroy(kjBuffer* self);
KJ_API kjErr kj_buffer_write(kjBuffer* self, const void* buf, isize size);
KJ_API void kj_buffer_reset(kjBuffer* self);

/// Dialog

enum {
    KJ_DIALOG_OPEN = KJ_BIT_FLAG(0),
    KJ_DIALOG_SAVE = KJ_BIT_FLAG(1),
    KJ_DIALOG_DIR = KJ_BIT_FLAG(2)
};

kjErr kj_file_dialog(char* path, isize size, u32 mode);

KJ_EXTERN_END

#endif

#if defined(KJ_IMPL)

KJ_INTERN KJ_TLS char KJ__PATH_BUF[KJ_PATH_MAX + 1] = {0};

#if defined(KJ_SYS_WIN32)
KJ_INTERN KJ_TLS WCHAR KJ__WPATH_BUF[KJ_PATH_MAX + 1] = {0};
#endif

KJ_INTERN const char* KJ__TYPE_STRS[] = {
#define KJ_TYPE_NAME(type, name, T) name,
    KJ_TYPE_MAP(KJ_TYPE_NAME)
#undef KJ_TYPE_NAME
};

const char* kj_type_to_str(kjType type) {
    return type <= KJ_TYPE_UNKNOWN || type >= KJ_TYPE_COUNT ?
        "Unknown": KJ__TYPE_STRS[type];
}

KJ_INTERN const isize KJ_TYPE_SIZES[] = {
#define KJ_TYPE_SIZE(type, name, T) kj_isize_of(T),
    KJ_TYPE_MAP(KJ_TYPE_SIZE)
#undef KJ_TYPE_SIZE
};

isize kj_type_to_isize(kjType type) {
    return type <= KJ_TYPE_UNKNOWN || type >= KJ_TYPE_COUNT ?
        -1: KJ_TYPE_SIZES[type];
}

#if defined(KJ_SYS_WIN32)
kjErr kj_err_from_sys(i32 err) {
    switch(err) {
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
        case ERROR_INSUFFICIENT_BUFFER: return KJ_ERR_INSUFFICIENT_BUFFER;
        case ERROR_NO_UNICODE_TRANSLATION: return KJ_ERR_INVALID_UTF8;
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
        default: return KJ_ERR_UNKNOWN;
    }
}
#elif defined(KJ_SYS_LINUX)
kjErr kj_err_from_sys(i32 err) {
    switch(err) {
        case 0: return KJ_ERR_NONE;
        case EBADF: return KJ_ERR_BAD_HANDLE;
        case EPERM: return KJ_ERR_PERMISSION_DENIED;
        case EACCES: return KJ_ERR_PERMISSION_DENIED;
        case EEXIST: return KJ_ERR_ALREADY_EXISTS;
        case EPIPE: return KJ_ERR_BROKEN_PIPE;
        case ENOENT: return KJ_ERR_NOT_FOUND;
        case ENOTEMPTY: return KJ_ERR_NOT_EMPTY;
        case ETIMEDOUT: return KJ_ERR_TIMED_OUT;
        case EINVAL: return KJ_ERR_INVALID_PARAMETER;
        case EINTR: return KJ_ERR_INTERRUPED;
        case ESPIPE: return KJ_ERR_ILLEGAL_SEEK;
        case EADDRINUSE: return KJ_ERR_ADDR_IN_USE;
        case EADDRNOTAVAIL: return KJ_ERR_ADDR_NOT_AVAILABLE;
        case ECONNABORTED: return KJ_ERR_CONNECTION_ABORTED;
        case ECONNREFUSED: return KJ_ERR_CONNECTION_REFUSED;
        case ECONNRESET: return KJ_ERR_CONNECTION_RESET;
        case ENOTCONN: return KJ_ERR_NOT_CONNECTED;
        case EAGAIN: return KJ_ERR_WOULD_BLOCK;
        case ERANGE: return KJ_ERR_INSUFFICIENT_BUFFER;
        default: return KJ_ERR_UNKNOWN;
    }
}
#endif

KJ_INTERN const char* KJ__ERR_STRS[] = {
#define KJ_ERR_NAME(type, name) name,
    KJ_ERR_MAP(KJ_ERR_NAME)
#undef KJ_ERR_NAME
};

const char* kj_err_to_str(kjErr err) {
    const char* res = err <= KJ_ERR_UNKNOWN || err >= KJ_ERR_COUNT ?
        "Unknown": KJ__ERR_STRS[err];
    return res;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_ALLOC_FN(kj__dummy_alloc) {
    kj_unused(self);
    kj_unused(size);
    return NULL;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_FREE_FN(kj__dummy_free) {
    kj_unused(self);
    kj_unused(data);
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_REALLOC_FN(kj__dummy_realloc) {
    kj_unused(self);
    kj_unused(data);
    kj_unused(size);
    return NULL;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj__dummy_alloc_aligned) {
    kj_unused(self);
    kj_unused(size);
    kj_unused(alignment);
    return NULL;
}

void* kj_global_alloc(isize size, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
#if defined(KJ_SYS_WIN32)
        res = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
#elif defined(KJ_SYS_LINUX)
        res = calloc(size, kj_isize_of(u8));
#endif
    } else {
#if defined(KJ_SYS_WIN32)
        res = HeapAlloc(GetProcessHeap(), 0, size);
#elif defined(KJ_SYS_LINUX)
        res = malloc(size * kj_isize_of(u8));
#endif
    }
    return res;
}

void kj_global_free(void* data, u32 flags) {
    kj_unused(flags);
    if(data) {
#if defined(KJ_SYS_WIN32)
        HeapFree(GetProcessHeap(), 0, data);
#elif defined(KJ_SYS_LINUX)
        free(data);
#endif
    }
}

void* kj_global_realloc(void* data, isize size, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
#if defined(KJ_SYS_WIN32)
        res = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, data, size);
#elif defined(KJ_SYS_LINUX)
        res = realloc(data, size * kj_isize_of(u8));
#endif
    } else {
#if defined(KJ_SYS_WIN32)
        res = HeapReAlloc(GetProcessHeap(), 0, data, size);
#elif defined(KJ_SYS_LINUX)
        res = realloc(data, size * kj_isize_of(u8));
#endif
    }
    return res;
}

void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
#if defined(KJ_SYS_WIN32)
        res = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size + alignment);
#elif defined(KJ_SYS_LINUX)
        res = calloc(size + alignment, kj_isize_of(u8));
#endif
    } else {
#if defined(KJ_SYS_WIN32)
        res = HeapAlloc(GetProcessHeap(), 0, size + alignment);
#elif defined(KJ_SYS_LINUX)
        res = malloc((size + alignment) * kj_isize_of(u8));
#endif
    }
    res = kj_align_on(kj_cast(u8*, res), alignment);
    return res;
}

KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc) {
    return kj_global_alloc(size, self->flags);
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

KJ_ALLOCATOR_ALLOC_FN(kj_linear_alloc) {
    if(self == NULL || size <= 0) {
        return NULL;
    }

    void* res = NULL;
    kjLinearAllocator* a = kj_cast(kjLinearAllocator*, self);
    isize new_size = a->used + size;
    if(new_size < a->size) {
        a->offset = a->used;
        res = kj_cast(void*, a->data + a->offset);
        a->used = new_size;
    }
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_linear_free) {
    if(self == NULL || data == NULL) {
        return;
    }

    kjLinearAllocator* a = kj_cast(kjLinearAllocator*, self);
    if(data == (a->data + a->offset)) {
        a->used = a->offset;
    }
}

KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc) {
    if(self == NULL || data == NULL || size <= 0) {
        return NULL;
    }

    void* res = NULL;
    kjLinearAllocator* a = kj_cast(kjLinearAllocator*, self);
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
    kj_unused(self);
    kj_unused(size);
    kj_unused(alignment);
    kj_unimplemented();
    kj_unreachable();
}

kjLinearAllocator kj_linear_allocator(void* data, isize size, u32 flags) {
    kjLinearAllocator res;
    res.allocator.alloc = kj_linear_alloc;
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
    size = size == 0 ? kj_str_size(s): size;
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

kjStr kj_string_append(kjStr s1, kjStr s2) {
    kj_unused(s1);
    kj_unused(s2);
    kj_unimplemented();
    kj_unreachable();
}

kjStr kj_string_append_str(kjStr s1, const char* s2, isize size) {
    kj_unused(s1);
    kj_unused(s2);
    kj_unused(size);
    kj_unimplemented();
    kj_unreachable();
}

kjStr kj_string_dup(kjStr s) {
    if(s == NULL) {
        return NULL;
    }

    kjStrHeader* header = kj_cast(kjStrHeader*, s) - 1;
    return kj_string(header->allocator, s, kj_string_size(s));
}

KJ_ASSERT_HANDLER(kj_assert_handler) {
    kj_unused(usr);
#if defined(KJ_SYS_WIN32) && defined(KJ_MESSAGE_BOX)
    static char buf[4096];
    kj_zero(buf, kj_isize_of(buf));
    kj_snprintf(
            buf, 4096,
            "FILE: %s\nLINE: %ld\nFUNC: %s\nEXPR: %s\nMSG: %s",
            file, line, fn, expr, msg == NULL ? "NONE": msg);
    buf[4095] = '\0';
    MessageBoxA(NULL, buf, "Assertion", MB_OK);
#else
    kj_printf(
            "FILE: %s\nLINE: %ld\nFUNC: %s\nEXPR: %s\nMSG: %s",
            file, line, fn, expr, msg == NULL ? "NONE": msg);
#endif
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
    va_start(v, fmt);
    res = kj_vprintf(fmt, v);
    va_end(v);
    return res;
}

isize kj_vsnprintf(char* buf, isize size, const char* fmt, va_list v) {
    isize res = -1;
#if defined(KJ_COMPILER_MSVC)
    res = _vsnprintf(buf, size, fmt, v);
#else
    res = vsnprintf(buf, size, fmt, v);
#endif
    return res;
}

isize kj_snprintf(char* buf, isize size, KJ_FMT_STR const char* fmt, ...) {
    isize res = -1;
    va_list v;
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

KJ_INLINE isize kj_str_size_limit(const char* s, isize limit) {
    const char* e = s;
    while(*e && limit--) { e++; }
    return (e - s);
}

KJ_INLINE isize kj_str_size(const char* s) {
    const char* e = s;
    while(*e) { e++; }
    return (e - s);
}

KJ_INLINE isize kj_str_cmp_limit(const char* s1, const char* s2, isize limit) {
    if(!limit--) return 0;
    for(; *s1 && *s2 && limit && *s1 == *s2; s1++, s2++, limit--);
    return *s1 - *s2;
}

KJ_INLINE isize kj_str_cmp(const char* s1, const char* s2) {
    for(; *s1 == *s2 && *s1; s1++, s2++);
    return *s1 - *s2;
}

KJ_INLINE isize kj_str_case_cmp_limit(
        const char* s1, const char* s2, isize limit) {
    if(!limit--) return 0;
    for(; *s1 && *s2 && limit &&
            (*s1 == *s2 || kj_char_to_lower(*s1) == kj_char_to_lower(*s2));
            s1++, s2++, limit--);
    return *s1 - *s2;
}

KJ_INLINE isize kj_str_case_cmp(const char* s1, const char* s2) {
    for(; (*s1 == *s2 || kj_char_to_lower(*s1) == kj_char_to_lower(*s2)) &&
            *s1; s1++, s2++);
    return *s1 - *s2;
}

u64$ kj_str_to_u64(const char* s, isize size) {
    u64$ res;
    if(s == NULL || size < 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(u64$));

    size = size == 0 ? kj_str_size(s): size;
    u64 base = 10;
    u64 overflow = KJ_U64_MAX;
    if(*s == '0'){
        if(kj_str_case_cmp_limit(s, "0x", 2) == 0) {
            base = 16;
            s += 2;
        } elif(kj_str_case_cmp_limit(s, "0o", 2) == 0) {
            base = 8;
            s += 2;
        } elif(kj_str_case_cmp_limit(s, "0b", 2) == 0) {
            base = 2;
            s += 2;
        } else {
            base = 0;
            res.err = KJ_ERR_SYNTAX;
        }
        overflow = KJ_U64_MAX / base + 1;
    }
    if(base > 0) {
        u64 v;
        for(isize i = 0; i < size; i++) {
            char c = s[i];
            if(c >= '0' && c <= '9') {
                v = c - '0';
            } elif(base == 16 && c >= 'a' && c <= 'f') {
                v = c - 'a' + 10;
            } elif(base == 16 && c >= 'A' && c <= 'F') {
                v = c - 'A' + 10;
            } else {
                res.err = KJ_ERR_SYNTAX;
                break;
            }
            if(v > base) {
                res.err = KJ_ERR_SYNTAX;
                break;
            }
            if(res.val > overflow) {
                res.val = KJ_U64_MAX;
                res.err = KJ_ERR_RANGE;
                break;
            }
            res.val *= base;
            u64 tmp = res.val + v;
            if(tmp < res.val || tmp > KJ_U64_MAX) {
                res.val = KJ_U64_MAX;
                res.err = KJ_ERR_RANGE;
                break;
            }
            res.val = tmp;
        }
    }
    return res;
}

i64$ kj_str_to_i64(const char* s, isize size) {
    i64$ res;
    if(s == NULL || size < 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(i64$));

    size = size == 0 ? kj_str_size(s): size;
    i64 sign = *s == '-' ? s++, -1: 1;
    u64$ u = kj_str_to_u64(s, size);
    if(kj_is_ok(u)) {
        if(kj_cast(i64, u.val) <= KJ_I64_MAX) {
            res.val = kj_cast(i64, u.val) * sign;
        } else {
            res.err = KJ_ERR_RANGE;
        }
    } else {
        res.err = KJ_ERR_SYNTAX;
    }
    return res;
}

const char* kj_str_find_predicate(
        const char* s, isize size, kjPredicateFn* fn) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(s): size;
    for(isize i = 0; i < size; i++) {
        if(fn(&s[i])) {
            res = &s[i];
            break;
        }
    }
    return res;
}

const char* kj_str_rfind_predicate(
        const char* s, isize size, kjPredicateFn* fn) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(s): size;
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
    size = size == 0 ? kj_str_size(s): size;
    for(isize i = 0; i < size; i++) {
        if(s[i] == c) {
            res = &s[i];
            break;
        }
    }
    return res;
}

const char* kj_str_rfind(const char* s, isize size, char c) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(s): size;
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
    size = size == 0 ? kj_str_size(s): size;
    for(isize i = 0; i < size; i++) {
        if(s[i] == o) {
            s[i] = n;
            break;
        }
    }
    return res;
}

const char* kj_str_trim(const char* s, isize size, const char** end) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = kj_str_ltrim(s, size);
    size = size == 0 ? kj_str_size(s): size;
    *end = kj_str_rtrim(s, size);
    return res;
}

const char* kj_str_ltrim(const char* s, isize size) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = s;
    size = size == 0 ? kj_str_size(s): size;
    for(isize i = 0; i < size && kj_char_is_ws(s[i]); i++, res++);
    return res;
}

const char* kj_str_rtrim(const char* s, isize size) {
    if(s == NULL || size < 0) {
        return NULL;
    }

    const char* res = s + size;
    size = size == 0 ? kj_str_size(s): size;
    for(isize i = size - 1; i >= 0 && kj_char_is_ws(s[i]); i--, res--);
    return res;
}

isize kj_utf8_count_limit(const char* s, isize limit) {
    if(s == NULL || limit <= 0) {
        return -1;
    }

    isize res = 0;
    for(; *s && res < limit; s++) {
        if((*s & 0xC0) != 0x80) {
            res++;
        }
    }
    return res;
}

isize kj_utf8_count(const char* s) {
    if(s == NULL) {
        return -1;
    }

    isize res = 0;
    while(*s++) {
        if((*s & 0xC0) != 0x80) {
            res++;
        }
    }
    return res;
}

#if defined(KJ_SYS_WIN32)
i32$ kj_utf8_to_ucs(const char* s, WCHAR* ws, i32 count) {
    i32$ res;
    if(s == NULL || ws == NULL || count <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(i32$));

    res.val = MultiByteToWideChar(
            CP_UTF8, MB_ERR_INVALID_CHARS, s, -1, NULL, 0);
    if(res.val == 0xFFFD) {
        res.err = KJ_ERR_INVALID_UTF8;
    } elif(res.val < count) {
        MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s, -1, ws, count);
    } elif(ws != NULL && count != 0) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    return res;
}

i32$ kj_ucs_to_utf8(const WCHAR* ws, char* s, i32 count) {
    i32$ res;
    if(s == NULL || ws == NULL || count <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(i32$));

    res.val = WideCharToMultiByte(
            CP_UTF8, WC_ERR_INVALID_CHARS, ws, -1, NULL, 0, NULL, NULL);
    if(res.val == 0xFFFD) {
        res.err = KJ_ERR_INVALID_UTF8;
    } elif(res.val < count) {
        WideCharToMultiByte(
                CP_UTF8, WC_ERR_INVALID_CHARS, ws, -1,
                s, count, NULL, NULL);
    } elif(s != NULL && count != 0) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    return res;
}

#endif

#if defined(KJ_LIB_IMPL)
KJ_INLINE kjLib$ kj_lib_open(const char* path) {
    kjLib$ res;
    if(path == NULL) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(kjLib$));

#if defined(KJ_SYS_WIN32)
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, kj_isize_of(KJ__WPATH_BUF));
    if(kj_is_ok(ucs)) {
        if((res.val = LoadLibraryW(KJ__WPATH_BUF)) == NULL) {
            res.err = kj_err_from_sys(GetLastError());
        }
    } else {
        res.err = ucs.err;
    }
#elif defined(KJ_SYS_LINUX)
    if((res.val = kj_cast(kjLib, dlopen(path, RTLD_LAZY))) == NULL) {
        res.err = kj_err_from_sys(errno);
    }
#endif
    return res;
}

KJ_INLINE kjLibFn$ kj_lib_fn(kjLib* self, const char* name) {
    kjLibFn$ res;
    if(self == NULL || name == NULL) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(kjLibFn$));

#if defined(KJ_SYS_WIN32)
    if((res.val = GetProcAddress(*self, name)) == NULL) {
        res.err = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    if((res.val = kj_cast(kjLibFn, dlsym(self, name))) == NULL) {
        res.err = kj_err_from_sys(errno);
    }
#endif
    return res;
}

KJ_INLINE void kj_lib_close(kjLib* self) {
    if(self == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    FreeLibrary(*self);
#elif defined(KJ_SYS_LINUX)
    dlclose(self);
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
KJ_INTERN KJ_INLINE void kj__systime_to_datetime(
        SYSTEMTIME* st, kjDateTime* dt) {
    dt->year = st->wYear;
    dt->month = st->wMonth;
    dt->day = st->wDay;
    dt->hour = st->wHour;
    dt->minute = st->wMinute;
    dt->second = st->wSecond;
    dt->millisecond = st->wMilliseconds;
}

KJ_INTERN KJ_INLINE u64 kj__filetime_to_unix(FILETIME* ft) {
    ULARGE_INTEGER ul;
    ul.LowPart = ft->dwLowDateTime;
    ul.HighPart = ft->dwHighDateTime;
    return ul.QuadPart / 10000000 - 11644473600;
}

u64 kj_timestamp_utc(void) {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    return kj__filetime_to_unix(&ft);
}

u64 kj_datetime_to_timestamp(kjDateTime dt) {
    u64 res;
    SYSTEMTIME st;
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
    return res;
}

kjDateTime kj_datetime_utc(void) {
    kjDateTime res;
    SYSTEMTIME st = {0};
    GetSystemTime(&st);
    kj__systime_to_datetime(&st, &res);
    res.tz = 0;
    return res;
}

kjDateTime kj_datetime_local(void) {
    kjDateTime res;
    SYSTEMTIME st = {0};
    GetLocalTime(&st);
    kj__systime_to_datetime(&st, &res);
    TIME_ZONE_INFORMATION tz = {0};
    switch(GetTimeZoneInformation(&tz)) {
        case 0: { res.tz = kj_cast(i16, tz.Bias); } break;
        case 1: { res.tz = kj_cast(i16, tz.StandardBias); } break;
        case 2: { res.tz = kj_cast(i16, tz.DaylightBias); } break;
    }
    return res;
}

u64 kj_time_ms(void) {
    static LARGE_INTEGER freq = {{0}};
    if(freq.QuadPart == 0) {
        QueryPerformanceFrequency(&freq);
    }
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return (kj_cast(u64, counter.QuadPart) * 1000) /
        kj_cast(u64, freq.QuadPart);
}
#elif defined(KJ_SYS_LINUX)
KJ_INTERN void kj__systime_to_datetime(struct tm* tm, kjDateTime* dt) {
    dt->year = 1900 + tm->tm_year;
    dt->month = tm->tm_mon + 1;
    dt->day = tm->tm_mday;
    dt->hour = tm->tm_hour;
    dt->minute = tm->tm_min;
    dt->second = tm->tm_sec;
    dt->millisecond = 0;
    dt->tz = 0;
}

u64 kj_timestamp_utc(void) {
    time_t t;
    time(&t);
    return kj_cast(u64, t);
}

u64 kj_datetime_to_timestamp(kjDateTime dt) {
    u64 res = 0;
    struct tm tm;
    tm.tm_year = dt.year - 1900;
    tm.tm_mon = dt.month - 1;
    tm.tm_mday = dt.day;
    tm.tm_hour = dt.hour;
    tm.tm_min = dt.minute;
    tm.tm_sec = dt.second;
    time_t t = mktime(&tm);
    res = kj_cast(u64, t);
    return res;
}

kjDateTime kj_datetime_utc(void) {
    kjDateTime res;
    time_t t;
    time(&t);
    struct tm* tm = gmtime(&t);
    kj__systime_to_datetime(tm, &res);
    return res;
}

kjDateTime kj_datetime_local(void) {
    kjDateTime res;
    time_t t;
    time(&t);
    struct tm* tm = localtime(&t);
    res.year = 1900 + tm->tm_year;
    res.month = tm->tm_mon + 1;
    res.day = tm->tm_mday;
    res.hour = tm->tm_hour;
    res.minute = tm->tm_min;
    res.second = tm->tm_sec;
    res.millisecond = 0;
    return res;
}

u64 kj_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec + ts.tv_nsec) / 1000000;
}
#endif

u32 kj_hash_str(const char* s, isize size) {
    if(s == NULL || size < 0) {
        return 0;
    }

    u32 res = 0;
    size = size == 0 ? kj_str_size(s): size;
    for(isize i = 0; i < size; i++) {
        res += (*s++) * (kj_cast(u32, i % KJ_U32_MAX) + 119);
    }
    return res;
}

#define KJ_FILE_INVALID_FLAGS KJ_U32_MAX

kjFile$ kj_file_create(const char* path) {
    return kj_file_open(
            path, KJ_FILE_WRITE | KJ_FILE_CREATE | KJ_FILE_TRUNCATE);
}

KJ_INTERN u32 kj__file_access_flags(u32 flags) {
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
#elif defined(KJ_SYS_LINUX)
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

KJ_INTERN u32 kj__file_create_flags(u32 flags) {
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
#elif defined(KJ_SYS_LINUX)
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

kjFile$ kj_file_open(const char* path, u32 flags) {
    kjFile$ res;
    if(path == NULL) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(kjFile$));

    u32 access = kj__file_access_flags(flags);
    u32 create = kj__file_create_flags(flags);
#if defined(KJ_SYS_WIN32)
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, kj_isize_of(KJ__WPATH_BUF));
    if(kj_is_ok(ucs)) {
        res.val = CreateFileW(
                KJ__WPATH_BUF, access,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                NULL, create, 0, NULL);
        if(res.val == INVALID_HANDLE_VALUE) {
            res.err = kj_err_from_sys(GetLastError());
        }
    } else {
        res.err = ucs.err;
    }
#elif defined(KJ_SYS_LINUX)
    u32 perm = 0666;
    kj_syscall3(KJ_SYSCALL_OPEN, res.val, path, (access | create), perm);
    res.err = res.val < 0 ? kj_err_from_sys(-res.val): KJ_ERR_NONE;
#endif
    return res;
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
#elif defined(KJ_SYS_LINUX)
    i32 out = 0;
    kj_syscall1(KJ_SYSCALL_CLOSE, out, self);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
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
#elif defined(KJ_SYS_LINUX)
    isize out = -1;
    kj_syscall3(KJ_SYSCALL_LSEEK, out, self, offset, seek);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
#endif
    return res;
}

isize$ kj_file_read(const kjFile* self, void* buf, isize size) {
    isize$ res;
    if(self == NULL || buf == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

#if defined(KJ_SYS_WIN32)
    DWORD read = 0;
    if(ReadFile(*self, buf, kj_cast(DWORD, size), &read, NULL)) {
        res.val = read;
        res.err = KJ_ERR_NONE;
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    kj_syscall3(KJ_SYSCALL_READ, res.val, self, buf, size);
    res.err = res.val < 0 ? kj_err_from_sys(-res.val): KJ_ERR_NONE;
#endif
    return res;
}

isize$ kj_file_write(const kjFile* self, const void* buf, isize size) {
    isize$ res;
    if(self == NULL || buf == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

#if defined(KJ_SYS_WIN32)
    DWORD wrote = 0;
    if(WriteFile(*self, buf, kj_cast(DWORD, size), &wrote, NULL)) {
        res.val = wrote;
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    kj_syscall3(KJ_SYSCALL_WRITE, res.val, self, buf, size);
    res.err = res.val < 0 ? kj_err_from_sys(-res.val): KJ_ERR_NONE;
#endif
    return res;
}

isize$ kj_file_read_at(const kjFile* self, void* buf, isize size, i64 offset) {
    isize$ res;
    if(self == NULL || buf == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(*self, buf, kj_cast(DWORD, size), &read, &overlapped)) {
        res.val = read;
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    kj_syscall4(KJ_SYSCALL_PREAD, res.val, self, buf, size, offset);
    res.err = res.val < 0 ? kj_err_from_sys(-res.val): KJ_ERR_NONE;
#endif
    return res;
}

isize$ kj_file_write_at(
        const kjFile* self, const void* buf, isize size, i64 offset) {
    isize$ res;
    if(self == NULL || buf == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(*self, buf, kj_cast(DWORD, size), &wrote, &overlapped)) {
        res.val = wrote;
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    kj_syscall4(KJ_SYSCALL_PWRITE, res.val, self, buf, size, offset);
    res.err = res.val < 0 ? kj_err_from_sys(-res.val): KJ_ERR_NONE;
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
#elif defined(KJ_SYS_LINUX)
    kj_syscall1(KJ_SYSCALL_FSYNC, res, self);
    res = res < 0 ? kj_err_from_sys(-res): KJ_ERR_NONE;
#endif
    return res;
}

kjFileMetadata$ kj_file_metadata(const kjFile* file) {
    kjFileMetadata$ res;
    if(file == NULL) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(kjFileMetadata$));

#if defined(KJ_SYS_WIN32)
    BY_HANDLE_FILE_INFORMATION info = {0};
    if(GetFileInformationByHandle(*file, &info)) {
        res.val.size =
            (kj_cast(i64, info.nFileSizeHigh) << 32) |
            (kj_cast(i64, info.nFileSizeLow));
        res.val.last_access = kj__filetime_to_unix(&info.ftLastAccessTime);
        res.val.last_write = kj__filetime_to_unix(&info.ftLastWriteTime);
        if(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            res.val.type = KJ_DIR;
        } else {
            res.val.type = KJ_FILE;
        }
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    struct stat st;
    kj_zero(&st, kj_isize_of(struct stat));
    isize out = -1;
    kj_syscall2(KJ_SYSCALL_FSTAT, out, *file, &st);
    if(out == -1) {
        res.err = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    } else {
        res.val.size = st.st_size;
        res.val.last_access = kj_cast(u64, st.st_atime);
        res.val.last_write = kj_cast(u64, st.st_mtime);
    }
#endif
    return res;
}

void$$ kj_file_slurp(kjAllocator* self, const char* path, b32 terminate) {
    void$$ res;
    if(self == NULL || path == NULL) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(void$$));

    kjFile$ file = kj_file_open(path, KJ_FILE_READ);
    if(kj_is_ok(file)) {
        kjFileMetadata$ metadata = kj_file_metadata(&file.val);
        if(kj_is_ok(metadata)) {
            kjFileMetadata* meta = &metadata.val;
            res.val = kj_allocator_alloc(self, meta->size + 1);
            isize$ read = kj_file_read(&file.val, res.val, meta->size);
            if(kj_is_ok(read)) {
                if(terminate) {
                    kj_cast(u8*, res.val)[meta->size] = '\0';
                }
                res.size = meta->size;
            } else {
                kj_allocator_free(self, res.val);
                res.val = NULL;
                res.err = KJ_ERR_ALLOC_FAILED;
                res.size = -1;
            }
        }
        kj_file_close(&file.val);
    } else {
        res.err = file.err;
    }
    return res;
}

isize$ kj_file_spit(const char* path, const void* buf, isize size) {
    isize$ res;
    if(path == NULL || buf == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

    kjFile$ file = kj_file_open(path, KJ_FILE_WRITE);
    if(kj_is_ok(file)) {
        res = kj_file_write(&file.val, buf, size);
        kj_file_close(&file.val);
    } else {
        res.err = file.err;
    }
    return res;
}

kjFileMetadata$ kj_file_metadata_path(const char* path) {
    kjFileMetadata$ res;
    if(path == NULL) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(kjFileMetadata$));

    kjFile$ file = kj_file_open(path, KJ_FILE_READ);
    if(kj_is_ok(file)) {
        res = kj_file_metadata(&file.val);
        kj_file_close(&file.val);
    }
    return res;
}

const char* kj_path_ext(const char* path, isize size) {
    if(path == NULL || size < 0) {
        return NULL;
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(path): size;
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
    return kj_char_is_separator(*kj_cast(char*, value)) ? KJ_TRUE: KJ_FALSE;
}

const char* kj_path_base(const char* path, isize size, const char** end) {
    if(path == NULL || size < 0 || end == NULL) {
        return ".";
    }

    const char* res = NULL;
    size = size == 0 ? kj_str_size(path): size;
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
    size = kj_char_is_separator(path[size - 1]) ? size - 1: kj_str_size(path);
    *end = kj_str_rfind(path, size, KJ_PATH_SEPARATOR);
    if(path[0] == KJ_PATH_SEPARATOR) {
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
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, KJ_PATH_MAX);
    if(kj_is_ok(ucs) && !CreateDirectoryW(KJ__WPATH_BUF, NULL)) {
        res = kj_err_from_sys(GetLastError());
    } else {
        res = ucs.err;
    }
#elif defined(KJ_SYS_LINUX)
    isize out = -1;
    kj_syscall2(KJ_SYSCALL_MKDIR, out, path, S_IRWXU | S_IRGRP | S_IROTH);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
#endif
    return res;
}

kjErr kj_path_remove_dir(const char* path) {
    if(path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, KJ_PATH_MAX);
    if(kj_is_ok(ucs) && !RemoveDirectoryW(KJ__WPATH_BUF)) {
        res = kj_err_from_sys(GetLastError());
    } else {
        res = ucs.err;
    }
#elif defined(KJ_SYS_LINUX)
    isize out = -1;
    kj_syscall1(KJ_SYSCALL_RMDIR, out, path);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
#endif
    return res;
}

kjErr kj_path_rename(const char* from, const char* to) {
    if(from == NULL || to == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    static WCHAR wto[KJ_PATH_MAX + 1] = {0};
    i32$ ucs1 = kj_utf8_to_ucs(from, KJ__WPATH_BUF, KJ_PATH_MAX);
    i32$ ucs2 = kj_utf8_to_ucs(to, wto, kj_isize_of(wto));
    if(kj_is_ok(ucs1)) {
        if(kj_is_ok(ucs2)) {
            if(!MoveFileExW(KJ__WPATH_BUF, wto, MOVEFILE_REPLACE_EXISTING)) {
                res = kj_err_from_sys(GetLastError());
            }
        } else {
            res = ucs2.err;
        }
    } else {
        res = ucs1.err;
    }
#elif defined(KJ_SYS_LINUX)
    isize out = -1;
    kj_syscall2(KJ_SYSCALL_RENAME, out, from, to);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
#endif
    return res;
}

isize$ kj_path_current_dir(char* path, isize size) {
    isize$ res;
    if(path == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

#if defined(KJ_SYS_WIN32)
    GetCurrentDirectoryW(KJ_PATH_MAX, KJ__WPATH_BUF);
    i32$ utf = kj_ucs_to_utf8(KJ__WPATH_BUF, path, kj_cast(i32, size));
    res.val = utf.val;
    res.err = utf.err;
#elif defined(KJ_SYS_LINUX)
    kj_syscall2(
            KJ_SYSCALL_GETCWD, res.val,
            KJ__PATH_BUF, kj_count_of(KJ__PATH_BUF));
    if(res.val < 0) {
        res.err = kj_err_from_sys(-res.val);
    } elif(res.val > size) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    } else {
        kj_copy(path, KJ__PATH_BUF, res.val);
        path[res.val] = '\0';
    }
#endif
    return res;
}

kjErr kj_path_set_current_dir(const char* path) {
    if(path == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, KJ_PATH_MAX);
    if(kj_is_ok(ucs) && !SetCurrentDirectoryW(KJ__WPATH_BUF)) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    isize out = -1;
    kj_syscall1(KJ_SYSCALL_CHDIR, out, path);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
#endif
    return res;
}

isize$ kj_path_tmp_dir(char* path, isize size) {
    isize$ res;
    if(path == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

#if defined(KJ_SYS_WIN32)
    DWORD wsize = GetTempPathW(0, NULL);
    GetTempPathW(wsize, KJ__WPATH_BUF);
    i32$ utf = kj_ucs_to_utf8(KJ__WPATH_BUF, path, kj_cast(i32, size));
    res.val = utf.val;
    res.err = utf.err;
#elif defined(KJ_SYS_LINUX)
    const char* tmp = NULL;
    if((tmp = getenv("TMPDIR")) == NULL) {
        tmp = "/tmp";
    }
    isize tmp_size = kj_str_size(tmp);
    if(tmp_size < size) {
        kj_copy(path, tmp, tmp_size);
        path[tmp_size] = '\0';
        res.val = tmp_size;
    } else {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    }
#endif
    return res;
}

isize$ kj_path_self(char* path, isize size) {
    isize$ res;
    if(path == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

#if defined(KJ_SYS_WIN32)
    res.val = GetModuleFileNameW(
            NULL, KJ__WPATH_BUF, KJ_PATH_MAX);
    i32$ utf = kj_ucs_to_utf8(KJ__WPATH_BUF, path, kj_cast(i32, size));
    res.val = utf.val;
    res.err = utf.err;
#elif defined(KJ_SYS_LINUX)
    kj_syscall3(
            KJ_SYSCALL_READLINK, res.val, "/proc/self/exe",
            KJ__PATH_BUF, kj_count_of(KJ__PATH_BUF));
    if(res.val < 0) {
        res.err = kj_err_from_sys(-res.val);
    } elif(res.val > size) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    } else {
        kj_copy(path, KJ__PATH_BUF, res.val);
        path[res.val] = '\0';
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
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, KJ_PATH_MAX);
    if(kj_is_ok(ucs)) {
        HANDLE h = INVALID_HANDLE_VALUE;
        WIN32_FIND_DATAW find;
        if((h = FindFirstFileW(KJ__WPATH_BUF, &find)) != INVALID_HANDLE_VALUE) {
            FindClose(h);
            res = KJ_TRUE;
        }
    }
#elif defined(KJ_SYS_LINUX)
    kj_syscall2(KJ_SYSCALL_ACCESS, res, path, 0);
    res = res == 0 ? KJ_TRUE: KJ_FALSE;
#endif
    return res;
}

b32 kj_path_is_file(const char* path) {
    if(path == NULL) {
        return KJ_FALSE;
    }

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, KJ_PATH_MAX);
    if(kj_is_ok(ucs)) {
        DWORD attr = INVALID_FILE_ATTRIBUTES;
        if((attr = GetFileAttributesW(KJ__WPATH_BUF))
                != INVALID_FILE_ATTRIBUTES) {
            res = attr & FILE_ATTRIBUTE_DIRECTORY ? KJ_FALSE: KJ_TRUE;
        }
    }
#elif defined(KJ_SYS_LINUX)
    struct stat st;
    kj_syscall2(KJ_SYSCALL_STAT, res, path, &st);
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
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, KJ_PATH_MAX);
    if(kj_is_ok(ucs)) {
        DWORD attr = INVALID_FILE_ATTRIBUTES;
        if((attr = GetFileAttributesW(KJ__WPATH_BUF)) !=
                INVALID_FILE_ATTRIBUTES) {
            res = attr & FILE_ATTRIBUTE_DIRECTORY ? KJ_TRUE: KJ_FALSE;
        }
    }
#elif defined(KJ_SYS_LINUX)
    struct stat st;
    kj_syscall2(KJ_SYSCALL_STAT, res, path, &st);
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
    i32$ ucs = kj_utf8_to_ucs(path, KJ__WPATH_BUF, KJ_PATH_MAX);
    if(kj_is_ok(ucs)) {
        if(KJ__WPATH_BUF[ucs.val - 1] == KJ_PATH_SEPARATOR) {
            KJ__WPATH_BUF[ucs.val] = '*';
            KJ__WPATH_BUF[ucs.val + 1] = '\0';
        } else {
            KJ__WPATH_BUF[ucs.val - 1] = KJ_PATH_SEPARATOR;
            KJ__WPATH_BUF[ucs.val] = '*';
            KJ__WPATH_BUF[ucs.val + 1] = '\0';
        }
        HANDLE handle = FindFirstFileW(KJ__WPATH_BUF, &find);
        if(handle != INVALID_HANDLE_VALUE) {
            self->find = find;
            self->handle = handle;
            self->first = KJ_TRUE;
        } else {
            res = kj_err_from_sys(GetLastError());
        }
    }
#elif defined(KJ_SYS_LINUX)
    if((self->dir = opendir(path)) == NULL) {
        res = kj_err_from_sys(errno);
    }
#endif
    return res;
}

kjErr kj_read_dir_next(kjReadDir* self, kjDirEntry* entry) {
    if(self == NULL || entry == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(self->first || FindNextFileW(self->handle, &self->find)) {
        i32$ utf = kj_ucs_to_utf8(
                self->find.cFileName, entry->path, kj_count_of(entry->path));
        res = utf.err;
        entry->count = utf.val - 1;
        self->first = KJ_FALSE;
    } else {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    struct dirent* result = NULL;
    struct dirent* ent = kj_cast(struct dirent*, entry->path);
    i32 err = 0;
    if((err = readdir_r(self->dir, ent, &result)) != 0) {
        res = kj_err_from_sys(err);
    }
    if(result) {
        isize size = kj_str_size_limit(ent->d_name, KJ_PATH_MAX);
        kj_copy(entry->path, &ent->d_name[0], size);
        entry->path[size] = '\0';
    } else {
        res = KJ_ERR_NO_MORE_FILES;
    }
#endif
    return res;
}

void kj_read_dir_end(kjReadDir* self) {
    if(self == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    if(self->handle) {
        FindClose(self->handle);
    }
#elif defined(KJ_SYS_LINUX)
    if(self->dir) {
        closedir(self->dir);
    }
#endif
}

kjBuffer kj_buffer(kjAllocator* allocator, isize granularity) {
    kjBuffer res;
    kj_zero(&res, kj_isize_of(kjBuffer));
    res.granularity = granularity;
    res.allocator = allocator;
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

    kjErr res = KJ_ERR_NONE;
    if(self->used + size > self->size) {
        isize new_size = kj_round_to(self->size + size, self->granularity);
        void* new_data = NULL;
        if(self->data) {
             new_data = kj_allocator_realloc(
                    self->allocator, self->data, new_size);
        } else {
             new_data = kj_allocator_alloc(self->allocator, new_size);
        }
        if(new_data) {
            self->data = kj_cast(u8*, new_data);
            self->size = size;
        } else {
            res = KJ_ERR_ALLOC_FAILED;
        }
    }
    if(res == KJ_ERR_NONE) {
        kj_copy(self->data + self->used, buf, size);
        self->used += size;
    }

#if defined(KJ_DEBUG)
    if(self->used < self->size) {
        self->data[self->used] = '\0';
    }
#endif

    return res;
}

void kj_buffer_reset(kjBuffer* self) {
    if(self == NULL || self->data == NULL) {
        return;
    }

    self->size = 0;
}

#if defined(KJ_DIALOG_IMPL) && defined(KJ_DIALOG)
kjErr kj_file_dialog(char* path, isize size, u32 mode) {
    if(path == NULL || size <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    OPENFILENAMEW ofn = {0};
    ofn.lStructSize = kj_isize_of(OPENFILENAMEW);
    ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = KJ__WPATH_BUF;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = KJ_PATH_MAX;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = mode & KJ_DIALOG_OPEN ? L"Open...": L"Save...";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |
        OFN_NOLONGNAMES | OFN_NOCHANGEDIR;
    b32 success = mode & KJ_DIALOG_OPEN ?
        GetOpenFileNameW(&ofn): GetSaveFileNameW(&ofn);
    if(success) {
        i32$ utf = kj_ucs_to_utf8(KJ__WPATH_BUF, path, kj_cast(i32, size));
        res = utf.err;
    } else {
        res = kj_err_from_sys(GetLastError());
    }
#else
    kj_unimplemented();
#endif
    return res;
}
#endif

#endif
