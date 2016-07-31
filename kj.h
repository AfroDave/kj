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
#define KJ_VERSION_MINOR 9
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
#include <commdlg.h>
#include <stdint.h>
#define KJ_SYS_NAME "windows"
#define KJ_SYS_DLL_EXT "dll"
#define KJ_SYS_EXE_EXT "exe"
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
#elif defined(__i386) || defined(_M_IX86)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_NAME "x86"
#else
#error Unsupported Architecture
#endif

#if defined(_MSC_VER)
#define KJ_COMPILER_MSVC
#define KJ_COMPILER_WARNING_BEGIN __pragma(warning(push))
#define KJ_COMPILER_WARNING_END __pragma(warning(pop))
#define KJ_COMPILER_WARNING(W) __pragma(warning(disable:W))
#define KJ_COMPILER_WARNING_NONSTANDARD 4201
#define KJ_COMPILER_WARNING_MISSING_BRACES
#elif defined(__clang__)
#define KJ_COMPILER_CLANG
#define KJ_COMPILER_WARNING_BEGIN _Pragma("clang diagnostic push")
#define KJ_COMPILER_WARNING_END _Pragma("clang diagnostic pop")
#define KJ_COMPILER_WARNING(W) _Pragma("clang diagnostic ignored" #W)
#define KJ_COMPILER_WARNING_NONSTANDARD "-Wpedantic"
#define KJ_COMPILER_WARNING_MISSING_BRACES "-Wmissing-braces"
#elif defined(__GNUC__) || defined(__GNUG__)
#define KJ_COMPILER_GNU
#define KJ_COMPILER_WARNING_BEGIN _Pragma("GCC diagnostic push")
#define KJ_COMPILER_WARNING_END _Pragma("GCC diagnostic pop")
#define KJ_COMPILER_WARNING(W) _Pragma("GCC diagnostic ignored" #W)
#define KJ_COMPILER_WARNING_NONSTANDARD "-Wpedantic"
#define KJ_COMPILER_WARNING_MISSING_BRACES "-Wmissing-braces"
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
#if defined(KJ_SYS_LINUX)
    KJ_PATH_MAX = PATH_MAX,
    KJ_NAME_MAX = NAME_MAX,
    KJ_PATH_SEPARATOR = '/'
#elif defined(KJ_SYS_WIN32)
    KJ_PATH_MAX = 4096,
    KJ_NAME_MAX = 255,
    KJ_PATH_SEPARATOR = '\\'
#endif
};

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

#if !defined(kj_string_of)
#define kj_string_of(a) #a
#define KJ_STRING_OF(a) kj_string_of(a)
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
#define kj_concat(a, b) a##b
#define kj_join(a, b) kj_concat(a, b)
#define KJ_CONCAT(a, b) kj_concat(a, b)
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
#define kj_round_up(a, b) ((a) + (((b) - 1) - (((a) - 1) % (b))))
#define KJ_MIN(a, b) kj_min(a, b)
#define KJ_MAX(a, b) kj_max(a, b)
#define KJ_CLAMP(a, min, max) kj_clamp(a, min, max)
#define KJ_WRAP(a, min, max) kj_wrap(a, min, max)
#define KJ_LERP(t, min, max) kj_lerp(t, min, max)
#define KJ_RANGE(a, fmin, fmax, tmin, tmax) kj_range(a, fmin, fmax, tmin, tmax)
#define KJ_SWAP(T, a, b) kj_swap(T, a, b)
#define KJ_ABS(a) kj_abs(a)
#define KJ_SIGN(a) kj_sign(a)
#define KJ_ROUND_UP(a, b) kj_round_up(a, b)
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
#define KJ_TLS kj_tls
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_tls __thread
#define KJ_TLS kj_tls
#endif
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

#if !defined(I8_MIN)
#define I8_MIN (-kj_cast(i8, 128))
#define I8_MAX (kj_cast(i8, 127))

#define I16_MIN (-kj_cast(i16, 32768))
#define I16_MAX (kj_cast(i16, 32767))

#define I32_MIN (-kj_cast(i32, 2147483648))
#define I32_MAX (kj_cast(i32, 2147483647))

#define I64_MIN (-kj_cast(i64, 9223372036854775808))
#define I64_MAX (kj_cast(i64, 9223372036854775807))

#define U8_MIN (kj_cast(u8, 0x00))
#define U8_MAX (kj_cast(u8, 0xFF))

#define U16_MIN (kj_cast(u16, 0x0000))
#define U16_MAX (kj_cast(u16, 0xFFFF))

#define U32_MIN (kj_cast(u32, 0x00000000))
#define U32_MAX (kj_cast(u32, 0xFFFFFFFF))

#define U64_MIN (kj_cast(u64, 0x0000000000000000))
#define U64_MAX (kj_cast(u64, 0xFFFFFFFFFFFFFFFF))
#endif

typedef i32 b32;

#if defined(KJ_ARCH_64_BIT)
typedef i64 isize;
typedef u64 usize;
#elif defined(KJ_ARCH_32_BIT)
typedef i32 isize;
typedef u32 usize;
#endif

#if !defined(ISIZE_MIN)
#if defined(KJ_ARCH_64_BIT)
#define ISIZE_MIN I64_MIN
#define ISIZE_MAX I64_MAX

#define USIZE_MIN U64_MIN
#define USIZE_MAX U64_MAX
#elif defined(KJ_ARCH_32_BIT)
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
#define F32_MIN kj_cast(f32, -3.402823e+38)
#define F32_MAX kj_cast(f32, 3.402823e+38)
#define F32_EPS kj_cast(f32, 1.192093e-07)

#define F64_MIN kj_cast(f64, -1.797693e+308)
#define F64_MAX kj_cast(f64, 1.797693e+308)
#define F64_EPS kj_cast(f64, 2.220446e-16)
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
    KJ_TYPE_UNKNOWN = 0,
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
    X(KJ_ERR_NO_MORE_FILES, "No More Files")

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
#define kj_ok(r) ((r).value)
#define kj_as_ptr(r) (&((r).value))
#define kj_err(r) ((r).err)
#define KJ_RESULT(T) struct { T value; kjErr err; }
#define KJ_RESULT_SIZED(T) struct { T value; isize size; kjErr err; }
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

#define KJ_RESULT_BEGIN(name) typedef struct name {
#define KJ_RESULT_ATTRIB(type, name) type name;
#define KJ_RESULT_END(name) kjErr err; } name;

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

KJ_API kjLinearAllocator kj_linear_allocator(
        const void* data, isize size, u32 flags);
KJ_API void kj_linear_allocator_clear(kjLinearAllocator* self);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_linear_alloc);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc);

/// Debug

#define KJ_ASSERT_HANDLER(name) void name(                                      \
        const char* expr, const char* file, isize line,                         \
        const char* msg, void* usr)

KJ_API KJ_ASSERT_HANDLER(kj_assert_handler);

#if !defined(KJ_CUSTOM_ASSERT_HANDLER)
#define KJ_CUSTOM_ASSERT_HANDLER kj_assert_handler
#endif

#if defined(NDEBUG) || defined(_DEBUG) || defined(KJ_DEBUG)
#if defined(KJ_COMPILER_MSVC)
#define kj_break() do {                                                         \
    if(IsDebuggerPresent()) { __debugbreak(); } else { ExitProcess(0); }        \
} while(0)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_break() do { __builtin_trap(); } while(0)
#endif
#define kj_assert_msg_usr(expr, msg, usr) do {                                  \
    if(!(expr)) {                                                               \
        KJ_CUSTOM_ASSERT_HANDLER(                                               \
                kj_string_of(expr), __FILE__, __LINE__, msg, usr);              \
        kj_break();                                                             \
    }                                                                           \
} while(0)
#define kj_assert_msg(expr, msg) kj_assert_msg_usr(expr, msg, NULL)
#define kj_assert_usr(expr, usr) kj_assert_msg_usr(expr, "", usr)
#define kj_assert(expr) kj_assert_msg_usr(expr, NULL, NULL)
#define kj_panic_msg_usr(msg, usr) do {                                         \
    KJ_CUSTOM_ASSERT_HANDLER("", __FILE__, __LINE__, msg, usr);                 \
    kj_break();                                                                 \
} while(0)
#define kj_panic_usr(usr) kj_panic_msg_usr("", usr)
#define kj_panic(msg) kj_panic_msg_usr(msg, NULL)
#define kj_unimplemented() kj_panic(__FUNCTION__ " - unimplemented")
#define kj_unreachable() kj_panic("unreachable")
#else
#define kj_break()
#define kj_assert_msg_usr(expr, msg, usr)
#define kj_assert_msg(expr, msg)
#define kj_assert_usr(expr, usr)
#define kj_assert(expr)
#define kj_panic_msg_usr(msg, usr)
#define kj_panic_usr(usr)
#define kj_panic(msg)
#define kj_unimplemented()
#define kj_unreachable()
#endif

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
    KJ_SYSCALL_RMDIR = 83,
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
    KJ_SYSCALL_STAT = 18,
    KJ_SYSCALL_FSTAT = 28,
    KJ_SYSCALL_FSYNC = 11,
    KJ_SYSCALL_READLINK = 85
};

#define kj_syscall1(call, res, a) do {                                          \
    __asm volatile(                                                             \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)));                                             \
} while(0)
#define kj_syscall2(call, res, a, b) do {                                       \
    __asm volatile(                                                             \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)), "c" ((b)));                                  \
} while(0)
#define kj_syscall3(call, res, a, b, c) do {                                    \
    __asm volatile(                                                             \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)), "c" ((b)), "d" ((c)))                        \
} while(0)
#define kj_syscall4(call, res, a, b, c, d) do {                                 \
    __asm volatile(                                                             \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)), "c" ((b)), "d" ((c)), "s" ((d)));            \
} while(0)
#define kj_syscall5(call, res, a, b, c, d, e) do {                              \
    __asm volatile(                                                             \
        "int $0x80"                                                             \
        : "=a" ((res))                                                          \
        : "0" ((call)), "b" ((a)), "c" ((b)), "d" ((c)), "s" ((d)), "D" ((e))); \
} while(0)
#define kj_syscall6(call, res, a, b, c, d, e, f) kj_panic("32-bit syscall6")
#endif
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

typedef struct kjRune {
    i32 codepoint;
    isize size;
} kjRune;

typedef u8 utf8;

KJ_API b32 kj_char_is_eol(u32 c);
KJ_API b32 kj_char_is_ws(u32 c);
KJ_API b32 kj_char_is_alpha(u32 c);
KJ_API b32 kj_char_is_digit(u32 c);
KJ_API b32 kj_char_is_alphanum(u32 c);
KJ_API b32 kj_char_is_hex_digit(u32 c);
KJ_API b32 kj_char_is_lower(u32 c);
KJ_API b32 kj_char_is_upper(u32 c);
KJ_API b32 kj_char_is_path_separator(u32 c);

KJ_API u32 kj_char_to_lower(u32 c);
KJ_API u32 kj_char_to_upper(u32 c);

KJ_API isize kj_cstr_count_n(const char* s, isize size);
KJ_API isize kj_cstr_count(const char* s);

KJ_API isize kj_cstr_cmp_n(const char* s1, const char* s2, isize size);
KJ_API isize kj_cstr_cmp(const char* s1, const char* s2);
KJ_API isize kj_cstr_case_cmp_n(const char* s1, const char* s2, isize size);
KJ_API isize kj_cstr_case_cmp(const char* s1, const char* s2);

KJ_API isize kj_cstr_to_u64(const char* s, u64* v);
KJ_API isize kj_cstr_to_i64(const char* s, i64* v);

KJ_API const char* kj_cstr_find_n(const char* s, isize size, char c);
KJ_API const char* kj_cstr_find(const char* s, char c);
KJ_API const char* kj_cstr_rfind_n(const char* s, isize size, char c);
KJ_API const char* kj_cstr_rfind(const char* s, char c);

KJ_API char* kj_cstr_replace_char_n(char* s, isize size, char o, char n);
KJ_API char* kj_cstr_replace_char(char* s, char o, char n);

KJ_API const char* kj_cstr_trim_n(const char* s, isize size, const char** end);
KJ_API const char* kj_cstr_trim(const char* s, const char** end);
KJ_API const char* kj_cstr_ltrim_n(const char* s, isize size);
KJ_API const char* kj_cstr_ltrim(const char* s);
KJ_API const char* kj_cstr_rtrim_n(const char* s, isize size);
KJ_API const char* kj_cstr_rtrim(const char* s);

KJ_API isize kj_utf8_count_n(const char* s, isize size);
KJ_API isize kj_utf8_count(const char* s);

#if defined(KJ_SYS_WIN32)
KJ_API i32$ kj_utf8_to_ucs(const char* s, WCHAR* ws, i32 size);
KJ_API i32$ kj_ucs_to_utf8(const WCHAR* ws, char* s, i32 size);
#endif

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
KJ_API kjLibFn$ kj_lib_fn(const kjLib* self, const char* name);
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

KJ_API u32 kj_hash_str_n(const char* s, isize size);
KJ_API u32 kj_hash_str(const char* s);

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
KJ_API kjErr kj_file_close(kjFile* self);
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

KJ_API kjFileMetadata$ kj_file_metadata(const kjFile* self);
KJ_API kjFileMetadata$ kj_file_metadata_path(const char* path);

/// Paths

KJ_API const char* kj_path_extension_n(const char* path, isize size);
KJ_API const char* kj_path_extension(const char* path);
KJ_API const char* kj_path_basename_n(
        const char* path, isize size, const char** end);
KJ_API const char* kj_path_basename(const char* path, const char** end);
KJ_API const char* kj_path_dirname_n(
        const char* path, isize size, const char** end);
KJ_API const char* kj_path_dirname(const char* path, const char** end);
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
KJ_API kjErr kj_buffer_write(kjBuffer* self, const void* data, isize size);
KJ_API void kj_buffer_clear(kjBuffer* self);

/// Dialog

#if defined(KJ_SYS_WIN32)
enum {
    KJ_DIALOG_OPEN = KJ_BIT_FLAG(0),
    KJ_DIALOG_SAVE = KJ_BIT_FLAG(1),
    KJ_DIALOG_DIR = KJ_BIT_FLAG(2)
};

kjErr kj_file_dialog(char* path, isize size, u32 mode);
#else
#error Unsupported Platform
#endif

KJ_EXTERN_END

#endif

#if defined(KJ_IMPL)

KJ_GLOBAL KJ_TLS char KJ_PATH_BUF[KJ_PATH_MAX + 1] = {0};

#if defined(KJ_SYS_WIN32)
KJ_GLOBAL KJ_TLS WCHAR KJ_WPATH_BUF[KJ_PATH_MAX + 1] = {0};
#endif

KJ_INLINE const char* kj_type_to_str(kjType type) {
    static const char* KJ_TYPE_STR[] = {
#define KJ_TYPE_NAME(type, name, T) name,
    KJ_TYPE_MAP(KJ_TYPE_NAME)
#undef KJ_TYPE_NAME
    };
    return type <= KJ_TYPE_UNKNOWN || type >= KJ_TYPE_COUNT ?
        "Unknown": KJ_TYPE_STR[type];
}

KJ_INLINE isize kj_type_to_isize(kjType type) {
    static const isize KJ_TYPE_ISIZE[] = {
#define KJ_TYPE_SIZE(type, name, T) kj_isize_of(T),
    KJ_TYPE_MAP(KJ_TYPE_SIZE)
#undef KJ_TYPE_SIZE
    };
    return type <= KJ_TYPE_UNKNOWN || type >= KJ_TYPE_COUNT ?
        -1: KJ_TYPE_ISIZE[type];
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

KJ_INLINE const char* kj_err_to_str(kjErr err) {
    static const char* KJ_ERR_STR[] = {
#define KJ_ERR_NAME(type, name) name,
    KJ_ERR_MAP(KJ_ERR_NAME)
#undef KJ_ERR_NAME
    };
    const char* res = err <= KJ_ERR_UNKNOWN || err >= KJ_ERR_COUNT ?
        "Unknown": KJ_ERR_STR[err];
    return res;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_ALLOC_FN(kj_dummy_alloc) {
    kj_unused(self);
    kj_unused(size);
    return NULL;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_FREE_FN(kj_dummy_free) {
    kj_unused(self);
    kj_unused(data);
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_REALLOC_FN(kj_dummy_realloc) {
    kj_unused(self);
    kj_unused(data);
    kj_unused(size);
    return NULL;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_dummy_alloc_aligned) {
    kj_unused(self);
    kj_unused(size);
    kj_unused(alignment);
    return NULL;
}

#if defined(KJ_SYS_WIN32)
void* kj_global_alloc(isize size, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
        res = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    } else {
        res = HeapAlloc(GetProcessHeap(), 0, size);
    }
    return res;
}

void kj_global_free(void* data, u32 flags) {
    kj_unused(flags);
    if(data) {
        HeapFree(GetProcessHeap(), 0, data);
    }
}

void* kj_global_realloc(void* data, isize size, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
        res = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, data, size);
    } else {
        res = HeapReAlloc(GetProcessHeap(), 0, data, size);
    }
    return res;
}

void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
        res = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size + alignment);
    } else {
        res = HeapAlloc(GetProcessHeap(), 0, size + alignment);
    }
    res = kj_align_on(kj_cast(u8*, res), alignment);
    return res;
}
#elif defined(KJ_SYS_LINUX)
void* kj_global_alloc(isize size, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
        res = calloc(size, kj_isize_of(u8));
    } else {
        res = malloc(size * kj_isize_of(u8));
    }
    return res;
}

void kj_global_free(void* data, u32 flags) {
    kj_unused(flags);
    if(data) {
        free(data);
    }
}

void* kj_global_realloc(void* data, isize size, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
        // size of data is unknown, add small header?
        res = realloc(data, size * kj_isize_of(u8));
    } else {
        res = realloc(data, size * kj_isize_of(u8));
    }
    return res;
}

void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_ZERO) {
        res = calloc(size + alignment, kj_isize_of(u8));
    } else {
        res = malloc((size + alignment) * kj_isize_of(u8));
    }
    res = kj_align_on(kj_cast(u8*, res), alignment);
    return res;
}
#endif

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
    kj_unused(size);

    void* res = NULL;
    if(self) {
        kjLinearAllocator* a = kj_cast(kjLinearAllocator*, self);
        isize new_size = a->used + size;
        if(new_size < a->size) {
            a->offset = a->used;
            res = kj_cast(void*, a->data + a->offset);
            a->used = new_size;
        }
    }
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_linear_free) {
    if(self) {
        kjLinearAllocator* a = kj_cast(kjLinearAllocator*, self);
        if(data == (a->data + a->offset)) {
            a->used = a->offset;
        }
    }
}

KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc) {
    void* res = NULL;
    if(self) {
        kjLinearAllocator* a = kj_cast(kjLinearAllocator*, self);
        if((a->data + a->offset) == data) {
            isize new_size = a->used + (size - (a->used - a->offset));
            if(new_size < a->size) {
                a->used = new_size;
                res = data;
            }
        }
    }
    return res;
}

KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_linear_alloc_aligned) {
    kj_unused(self);
    kj_unused(size);
    kj_unused(alignment);
    void* res = NULL;
    return res;
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

void kj_linear_allocator_clear(kjLinearAllocator* self) {
    if(self) {
        self->used = 0;
    }
}

#if defined(KJ_SYS_WIN32)
KJ_ASSERT_HANDLER(kj_assert_handler) {
    kj_unused(usr);
    static char buf[4096] = {0};
    kj_snprintf(buf, 4096, "%s:%ld - %s %s", file, line, expr, msg ? msg: "");
    buf[4095] = '\0';
    MessageBoxA(NULL, buf, "Assertion", MB_OK);
}
#elif defined(KJ_SYS_LINUX)
KJ_ASSERT_HANDLER(kj_assert_handler) {
    kj_unused(usr);
    if(msg) {
        kj_printf("%s:%ld - %s %s", file, line, expr, msg);
    } else {
        kj_printf("%s:%ld - %s", file, line, expr);
    }
}
#endif

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

#if defined(KJ_SYS_WIN32)
KJ_INLINE b32 kj_char_is_path_separator(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c == '\\' || c == '/') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}
#else
KJ_INLINE b32 kj_char_is_path_separator(u32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c == '/') ? KJ_TRUE: KJ_FALSE;
    }
    return KJ_FALSE;
}
#endif

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

KJ_INLINE isize kj_cstr_count_n(const char* s, isize n) {
    const char* e = s;
    while(*e && n--) { e++; }
    return (e - s);
}

KJ_INLINE isize kj_cstr_count(const char* s) {
    const char* e = s;
    while(*e) { e++; }
    return (e - s);
}

KJ_INLINE isize kj_cstr_cmp_n(const char* s1, const char* s2, isize n) {
    if(!n--) return 0;
    for(; *s1 && *s2 && n && *s1 == *s2; s1++, s2++, n--);
    return *s1 - *s2;
}

KJ_INLINE isize kj_cstr_cmp(const char* s1, const char* s2) {
    for(; *s1 == *s2 && *s1; s1++, s2++);
    return *s1 - *s2;
}

KJ_INLINE isize kj_cstr_case_cmp_n(const char* s1, const char* s2, isize n) {
    if(!n--) return 0;
    for(; *s1 && *s2 && n &&
            (*s1 == *s2 || kj_char_to_lower(*s1) == kj_char_to_lower(*s2));
            s1++, s2++, n--);
    return *s1 - *s2;
}

KJ_INLINE isize kj_cstr_case_cmp(const char* s1, const char* s2) {
    for(; (*s1 == *s2 || kj_char_to_lower(*s1) == kj_char_to_lower(*s2)) &&
            *s1; s1++, s2++);
    return *s1 - *s2;
}

isize kj_cstr_to_u64(const char* s, u64* v) {
    kj_assert(s);
    kj_assert(v);

    isize res = -1;
    const char* str = s;
    i64 base = 10;
    if(kj_cstr_case_cmp_n(s, "0x", 2) == 0) {
        base = 16;
        s += 2;
    } elif(kj_cstr_case_cmp_n(s, "0o", 2) == 0) {
        base = 8;
        s += 2;
    } elif(kj_cstr_case_cmp_n(s, "0b", 2) == 0) {
        base = 2;
        s += 2;
    }
    i64 tmp = 0;
    char c = '\0';
    while((c = *s++) != '\0') {
        if(c >= '0' && c <= '9') {
            tmp = tmp * base + c - '0';
        } elif(base == 16 && c >= 'a' && c <= 'f') {
            tmp = tmp * base + c - 'a' + 10;
        } elif(base == 16 && c >= 'A' && c <= 'F') {
            tmp = tmp * base + c - 'A' + 10;
        } else {
            break;
        }
    }
    if(((s - str) - 1) > 0) {
        *v = tmp;
        res = (s - str) - 1;
    }
    return res;
}

isize kj_cstr_to_i64(const char* s, i64* v) {
    isize res = -1;
    i64 sign = *s == '-' ? s++, -1: 1;
    u64 tmp;
    isize size = kj_cstr_to_u64(s, &tmp);
    if(size > 0 && tmp <= I64_MAX) {
        *v = kj_cast(i64, tmp) * sign;
        res = size;
    }
    return res;
}

const char* kj_cstr_find_predicate_n(
        const char* s, isize size, kjPredicateFn* fn) {
    const char* res = NULL;
    for(isize i = 0; i < size; i++) {
        if(fn(&s[i])) {
            res = &s[i];
            break;
        }
    }
    return res;
}

KJ_INLINE const char* kj_cstr_find_predicate(const char* s, kjPredicateFn* fn) {
    return kj_cstr_find_predicate_n(s, kj_cstr_count(s), fn);
}

const char* kj_cstr_rfind_predicate_n(
        const char* s, isize size, kjPredicateFn* fn) {
    const char* res = NULL;
    for(isize i = size - 1; i >= 0; i--) {
        if(fn(&s[i])) {
            res = &s[i];
            break;
        }
    }
    return res;
}

KJ_INLINE const char* kj_cstr_rfind_predicate(const char* s, kjPredicateFn* fn) {
    return kj_cstr_rfind_predicate_n(s, kj_cstr_count(s), fn);
}

const char* kj_cstr_find_n(const char* s, isize size, char c) {
    const char* res = NULL;
    for(isize i = 0; i < size; i++) {
        if(s[i] == c) {
            res = &s[i];
            break;
        }
    }
    return res;
}

KJ_INLINE const char* kj_cstr_find(const char* s, char c) {
    return kj_cstr_find_n(s, kj_cstr_count(s), c);
}

const char* kj_cstr_rfind_n(const char* s, isize size, char c) {
    const char* res = NULL;
    for(isize i = size - 1; i >= 0; i--) {
        if(s[i] == c) {
            res = &s[i];
            break;
        }
    }
    return res;
}

KJ_INLINE const char* kj_cstr_rfind(const char* s, char c) {
    return kj_cstr_rfind_n(s, kj_cstr_count(s), c);
}

char* kj_cstr_replace_char_n(char* s, isize size, char o, char n) {
    kj_assert(s);
    char* res = s;
    for(isize i = 0; i < size; i++) {
        if(s[i] == o) {
            s[i] = n;
            break;
        }
    }
    return res;
}

KJ_INLINE char* kj_cstr_replace_char(char* s, char o, char n) {
    return kj_cstr_replace_char_n(s, kj_cstr_count(s), o, n);
}

const char* kj_cstr_trim_n(const char* s, isize size, const char** end) {
    const char* res = kj_cstr_ltrim_n(s, size);
    *end = kj_cstr_rtrim_n(s, size);
    return res;
}

KJ_INLINE const char* kj_cstr_trim(const char* s, const char** end) {
    return kj_cstr_trim_n(s, kj_cstr_count(s), end);
}

const char* kj_cstr_ltrim_n(const char* s, isize size) {
    const char* res = s;
    for(isize i = 0; i < size && kj_char_is_ws(s[i]); i++, res++);
    return res;
}

KJ_INLINE const char* kj_cstr_ltrim(const char* s) {
    return kj_cstr_ltrim_n(s, kj_cstr_count(s));
}

const char* kj_cstr_rtrim_n(const char* s, isize size) {
    const char* res = s + size;
    for(isize i = size - 1; i >= 0 && kj_char_is_ws(s[i]); i--, res--);
    return res;
}

KJ_INLINE const char* kj_cstr_rtrim(const char* s) {
    return kj_cstr_rtrim_n(s, kj_cstr_count(s));
}

isize kj_utf8_count_n(const char* s, isize n) {
    isize res = 0;
    for(; *s && res < n; s++) {
        if((*s & 0xC0) != 0x80) {
            res++;
        }
    }
    return res;
}

isize kj_utf8_count(const char* s) {
    isize res = 0;
    while(*s++) {
        if((*s & 0xC0) != 0x80) {
            res++;
        }
    }
    return res;
}

#if defined(KJ_SYS_WIN32)
i32$ kj_utf8_to_ucs(const char* s, WCHAR* ws, i32 size) {
    i32$ res;
    kj_err(res) = KJ_ERR_NONE;
    kj_ok(res) = MultiByteToWideChar(
            CP_UTF8, MB_ERR_INVALID_CHARS, s, -1, NULL, 0);
    if(kj_ok(res) == 0xFFFD) {
        kj_err(res) = KJ_ERR_INVALID_UTF8;
    } elif(kj_ok(res) < size) {
        MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s, -1, ws, size);
    } elif(ws != NULL && size != 0) {
        kj_err(res) = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    return res;
}

i32$ kj_ucs_to_utf8(const WCHAR* ws, char* s, i32 size) {
    i32$ res;
    kj_err(res) = KJ_ERR_NONE;
    kj_ok(res) = WideCharToMultiByte(
            CP_UTF8, WC_ERR_INVALID_CHARS, ws, -1, NULL, 0, NULL, NULL);
    if(kj_ok(res) == 0xFFFD) {
        kj_err(res) = KJ_ERR_INVALID_UTF8;
    } elif(kj_ok(res) < size) {
        WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, ws, -1,
                s, size, NULL, NULL);
    } elif(s != NULL && size != 0) {
        kj_err(res) = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    return res;
}

#endif

#if defined(KJ_LIB_IMPL)
#if defined(KJ_SYS_WIN32)
KJ_INLINE kjLib$ kj_lib_open(const char* path) {
    kj_assert(path);

    kjLib$ res = {0};
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_isize_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs)) {
        if((kj_ok(res) = LoadLibraryW(KJ_WPATH_BUF)) == NULL) {
            kj_err(res) = kj_err_from_sys(GetLastError());
        }
    } else {
        kj_err(res) = kj_err(ucs);
    }
    return res;
}

KJ_INLINE kjLibFn$ kj_lib_fn(const kjLib* self, const char* name) {
    kj_assert(self);
    kj_assert(name);

    kjLibFn$ res = {0};
    if((kj_ok(res) = GetProcAddress(*self, name)) == NULL) {
        kj_err(res) = kj_err_from_sys(GetLastError());
    }
    return res;
}

KJ_INLINE void kj_lib_close(const kjLib* self) {
    kj_assert(self);

    FreeLibrary(*self);
}
#elif defined(KJ_SYS_LINUX)
KJ_INLINE kjErr kj_lib_open(kjLib* self, const char* path) {
    kj_assert(self);

    kjErr res = KJ_ERR_NONE;
    if((*self = kj_cast(kjLib, dlopen(path, RTLD_LAZY))) == NULL) {
        res = kj_err_from_sys(errno);
    }
    return res;
}

KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_NONSTANDARD)

KJ_INLINE kjLibFn kj_lib_fn(kjLib* self, const char* name) {
    kj_assert(self);

    return kj_cast(kjLibFn, dlsym(*self, name));
}

KJ_COMPILER_WARNING_END

KJ_INLINE void kj_lib_close(kjLib* self) {
    kj_assert(self);

    dlclose(*self);
}
#endif
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
KJ_INTERN void kj_systime_to_datetime(SYSTEMTIME* st, kjDateTime* dt) {
    dt->year = st->wYear;
    dt->month = st->wMonth;
    dt->day = st->wDay;
    dt->hour = st->wHour;
    dt->minute = st->wMinute;
    dt->second = st->wSecond;
    dt->millisecond = st->wMilliseconds;
}

KJ_INTERN u64 kj_filetime_to_unix(FILETIME* ft) {
    ULARGE_INTEGER ul;
    ul.LowPart = ft->dwLowDateTime;
    ul.HighPart = ft->dwHighDateTime;
    return ul.QuadPart / 10000000 - 11644473600;
}

u64 kj_timestamp_utc(void) {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    return kj_filetime_to_unix(&ft);
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
    res = kj_filetime_to_unix(&ft);
    return res;
}

kjDateTime kj_datetime_utc(void) {
    kjDateTime res;
    SYSTEMTIME st = {0};
    GetSystemTime(&st);
    kj_systime_to_datetime(&st, &res);
    res.tz = 0;
    return res;
}

kjDateTime kj_datetime_local(void) {
    kjDateTime res;
    SYSTEMTIME st = {0};
    GetLocalTime(&st);
    kj_systime_to_datetime(&st, &res);
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
KJ_INTERN void kj_systime_to_datetime(struct tm* tm, kjDateTime* dt) {
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
    kj_systime_to_datetime(tm, &res);
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

u32 kj_hash_str_n(const char* s, isize size) {
    u32 res = 0;
    for(isize i = 0; i < size; i++) {
        res += (*s++) * (kj_cast(u32, i % U32_MAX) + 119);
    }
    return res;
}

u32 kj_hash_str(const char* s) {
    return kj_hash_str_n(s, kj_cstr_count(s));
}

#define KJ_FILE_INVALID_FLAGS U32_MAX

kjFile$ kj_file_create(const char* path) {
    return kj_file_open(
            path, KJ_FILE_WRITE | KJ_FILE_CREATE | KJ_FILE_TRUNCATE);
}

#if defined(KJ_SYS_WIN32)
KJ_INTERN u32 kj_file_access_flags(u32 flags) {
    u32 res = 0;
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
    return res;
}

KJ_INTERN u32 kj_file_create_flags(u32 flags) {
    u32 res = 0;
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
    return res;
}

KJ_INTERN kjFileType kj_file_attr_to_type(DWORD attr) {
    kjFileType res;
    if(attr & FILE_ATTRIBUTE_DIRECTORY) {
        res = KJ_DIR;
    } else {
        res = KJ_FILE;
    }
    return res;
}

kjFile$ kj_file_open(const char* path, u32 flags) {
    kjFile$ res = {0};
    u32 access = kj_file_access_flags(flags);
    u32 create = kj_file_create_flags(flags);
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_isize_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs)) {
        kj_ok(res) = CreateFileW(
                KJ_WPATH_BUF, access,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                NULL, create, 0, NULL);
        if(kj_ok(res) == INVALID_HANDLE_VALUE) {
            kj_err(res) = kj_err_from_sys(GetLastError());
        }
    } else {
        kj_err(res) = kj_err(ucs);
    }
    return res;
}

kjErr kj_file_close(const kjFile* self) {
    kj_assert(self);

    kjErr res = KJ_ERR_NONE;
    if(!CloseHandle(*self)) {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}

kjErr kj_file_seek(const kjFile* self, i64 offset, kjSeekFrom seek) {
    kj_assert(self);

    kjErr res = KJ_ERR_NONE;
    LARGE_INTEGER new_offset;
    new_offset.QuadPart = offset;
    if(SetFilePointerEx(*self, new_offset, &new_offset, seek) == 0) {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_file_read(const kjFile* self, void* buf, isize size) {
    kj_assert(self);

    isize$ res = {0};
    DWORD read = 0;
    if(ReadFile(
        *self, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), NULL)) {
        kj_ok(res) = read;
        kj_err(res) = KJ_ERR_NONE;
    } else {
        kj_err(res) = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_file_write(const kjFile* self, const void* buf, isize size) {
    kj_assert(self);

    isize$ res = {0};
    DWORD wrote = 0;
    if(WriteFile(
        *self, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), NULL)) {
        kj_ok(res) = wrote;
        kj_err(res) = KJ_ERR_NONE;
    } else {
        kj_err(res) = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_file_read_at(const kjFile* self, void* buf, isize size, i64 offset) {
    kj_assert(self);

    isize$ res = {0};
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(
        *self, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), &overlapped)) {
        kj_ok(res) = read;
        kj_err(res) = KJ_ERR_NONE;
    } else {
        kj_err(res) = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_file_write_at(
        const kjFile* self, const void* buf, isize size, i64 offset) {
    kj_assert(self);

    isize$ res = {0};
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(
        *self, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), &overlapped)) {
        kj_ok(res) = wrote;
        kj_err(res) = KJ_ERR_NONE;
    } else {
        kj_err(res) = kj_err_from_sys(GetLastError());
    }
    return res;
}

kjErr kj_file_sync(const kjFile* self) {
    kj_assert(self);

    kjErr res = KJ_ERR_NONE;
    if(!FlushFileBuffers(*self)) {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}

kjFileMetadata$ kj_file_metadata(const kjFile* file) {
    kj_assert(file);

    kjFileMetadata$ res = {0};
    BY_HANDLE_FILE_INFORMATION info = {0};
    if(GetFileInformationByHandle(*file, &info)) {
        kj_ok(res).size =
            (kj_cast(i64, info.nFileSizeHigh) << 32) |
            (kj_cast(i64, info.nFileSizeLow));
        kj_ok(res).last_access =
            kj_filetime_to_unix(&info.ftLastAccessTime);
        kj_ok(res).last_write =
            kj_filetime_to_unix(&info.ftLastWriteTime);
        kj_ok(res).type =
            kj_file_attr_to_type(info.dwFileAttributes);
    } else {
        kj_err(res) = kj_err_from_sys(GetLastError());
    }
    return res;
}
#elif defined(KJ_SYS_LINUX)
KJ_INTERN u32 kj_file_access_flags(u32 flags) {
    u32 res = 0;
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
    return res;
}

KJ_INTERN u32 kj_file_create_flags(u32 flags) {
    u32 res = 0;
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
    return res;
}

kjErr kj_file_open(kjFile* self, const char* path, u32 flags) {
    kj_assert(self);

    kjErr res = KJ_ERR_NONE;
    u32 access = kj_file_access_flags(flags);
    u32 create = kj_file_create_flags(flags);
    u32 perm = 0666;
    kj_syscall3(KJ_SYSCALL_OPEN, *self, path, (access | create), perm);
    res = *self < 0 ? kj_err_from_sys(-*self): KJ_ERR_NONE;
    return res;
}

kjErr kj_file_close(kjFile* self) {
    kj_assert(self);

    kjErr res = KJ_ERR_NONE;
    i32 out = 0;
    kj_syscall1(KJ_SYSCALL_CLOSE, out, *self);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    return res;
}

kjErr kj_file_seek(kjFile* self, i64 offset, kjSeekFrom seek) {
    kj_assert(self);

    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall3(KJ_SYSCALL_LSEEK, out, *self, offset, seek);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    return res;
}

isize$ kj_file_read(kjFile* self, void* buf, isize size) {
    kj_assert(self);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    kj_err(res) = KJ_ERR_NONE;
    kj_syscall3(KJ_SYSCALL_READ, kj_ok(res), *self, buf, size);
    kj_err(res) = kj_ok(res) < 0 ? kj_err_from_sys(-kj_ok(res)): KJ_ERR_NONE;
    return res;
}

isize$ kj_file_write(kjFile* self, const void* buf, isize size) {
    kj_assert(self);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    kj_err(res) = KJ_ERR_NONE;
    kj_syscall3(KJ_SYSCALL_WRITE, kj_ok(res), *self, buf, size);
    kj_err(res) = kj_ok(res) < 0 ? kj_err_from_sys(-kj_ok(res)): KJ_ERR_NONE;
    return res;
}

isize$ kj_file_read_at(kjFile* self, void* buf, isize size, i64 offset) {
    kj_assert(self);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    kj_err(res) = KJ_ERR_NONE;
    kj_syscall4(KJ_SYSCALL_PREAD, kj_ok(res), *self, buf, size, offset);
    kj_err(res) = kj_ok(res) < 0 ? kj_err_from_sys(-kj_ok(res)): KJ_ERR_NONE;
    return res;
}

isize$ kj_file_write_at(kjFile* self, const void* buf, isize size, i64 offset) {
    kj_assert(self);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    kj_err(res) = KJ_ERR_NONE;
    kj_syscall4(KJ_SYSCALL_PWRITE, kj_ok(res), *self, buf, size, offset);
    kj_err(res) = kj_ok(res) < 0 ? kj_err_from_sys(-kj_ok(res)): KJ_ERR_NONE;
    return res;
}

kjErr kj_file_sync(kjFile* self) {
    kj_assert(self);

    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall1(KJ_SYSCALL_FSYNC, out, *self);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    return res;
}

kjErr kj_file_metadata(kjFile* self, kjFileMetadata* metadata) {
    kj_assert(self);
    kj_assert(metadata);

    kjErr res = KJ_ERR_NONE;
    struct stat st;
    kj_zero(&st, kj_isize_of(struct stat));
    isize out = -1;
    kj_syscall2(KJ_SYSCALL_FSTAT, out, *self, &st);
    if(out == -1) {
        res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    } else {
        metadata->size = st.st_size;
        metadata->last_access = kj_cast(u64, st.st_atime);
        metadata->last_write = kj_cast(u64, st.st_mtime);
    }
    return res;
}
#endif

void$$ kj_file_slurp(kjAllocator* self, const char* path, b32 terminate) {
    kj_assert(self);
    kj_assert(path);

    void$$ res = {0};
    kjFile$ file = kj_file_open(path, KJ_FILE_READ);
    if(kj_is_ok(file)) {
        kjFileMetadata$ metadata = kj_file_metadata(kj_as_ptr(file));
        if(kj_is_ok(metadata)) {
            kjFileMetadata* meta = kj_as_ptr(metadata);
            kj_ok(res) = kj_allocator_alloc(self, meta->size + 1);
            isize$ read = kj_file_read(kj_as_ptr(file), kj_ok(res), meta->size);
            if(kj_is_ok(read)) {
                if(terminate) {
                    kj_cast(u8*, kj_ok(res))[meta->size] = '\0';
                }
                res.size = meta->size;
            } else {
                kj_allocator_free(self, kj_ok(res));
                kj_ok(res) = NULL;
                kj_err(res) = KJ_ERR_ALLOC_FAILED;
                res.size = -1;
            }
        }
        kj_file_close(kj_as_ptr(file));
    } else {
        kj_err(res) = kj_err(file);
    }
    return res;
}

isize$ kj_file_spit(const char* path, const void* buf, isize size) {
    kj_assert(path);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res = {0};
    kjFile$ file = kj_file_open(path, KJ_FILE_WRITE);
    if(kj_is_ok(file)) {
        res = kj_file_write(kj_as_ptr(file), buf, size);
        kj_file_close(kj_as_ptr(file));
    } else {
        kj_err(res) = kj_err(file);
    }
    return res;
}

kjFileMetadata$ kj_file_metadata_path(const char* path) {
    kj_assert(path);

    kjFileMetadata$ res = {0};
    kjFile$ file = kj_file_open(path, KJ_FILE_READ);
    if(kj_is_ok(file)) {
        res = kj_file_metadata(kj_as_ptr(file));
        kj_file_close(kj_as_ptr(file));
    }
    return res;
}

const char* kj_path_extension_n(const char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    const char* res = NULL;
    if(path[size - 1] != '.') {
        for(isize i = size - 1; i >= 0; i--) {
            if(kj_char_is_path_separator(path[i])) {
                break;
            } elif(path[i] == '.') {
                res = &path[i + 1];
                break;
            }
        }
    }
    return res;
}

KJ_INLINE const char* kj_path_extension(const char* path) {
    return kj_path_extension_n(path, kj_cstr_count(path));
}

KJ_INTERN KJ_INLINE KJ_PREDICATE_FN(kj_path_is_separator) {
    return kj_char_is_path_separator(
            *kj_cast(char*, value)) ? KJ_TRUE: KJ_FALSE;
}

const char* kj_path_basename_n(const char* path, isize size, const char** end) {
    kj_assert(path);
    kj_assert(end);

    const char* res = NULL;
    if(size == 1) {
        res = path;
        *end = path + size;
    } else {
        size = kj_char_is_path_separator(path[size - 1]) ? size - 1: size;
        res = kj_cstr_rfind_predicate_n(path, size, kj_path_is_separator);
        res = res == NULL ? path: res + 1;
        *end = &path[size] == res ? &path[size + 1]: &path[size];
    }
    return res;
}

KJ_INLINE const char* kj_path_basename(const char* path, const char** end) {
    return kj_path_basename_n(path, kj_cstr_count(path), end);
}

const char* kj_path_dirname_n(const char* path, isize size, const char** end) {
    kj_assert(path);
    kj_assert(end);

    const char* res = NULL;
    size = path[size - 1] == KJ_PATH_SEPARATOR ? size - 1: size;
    *end = kj_cstr_rfind_n(path, size, KJ_PATH_SEPARATOR);
    if(path[0] == KJ_PATH_SEPARATOR) {
        *end = *end == path ? *end + 1: *end;
        res = path;
    } else {
        res = *end ? path: ".";
        *end = *end == NULL ? res + 1: *end;
    }
    return res;
}

KJ_INLINE const char* kj_path_dirname(const char* path, const char** end) {
    return kj_path_dirname_n(path, kj_cstr_count(path), end);
}

#if defined(KJ_SYS_WIN32)
kjErr kj_path_create_dir(const char* path) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs) && !CreateDirectoryW(KJ_WPATH_BUF, NULL)) {
        res = kj_err_from_sys(GetLastError());
    } else {
        res = kj_err(ucs);
    }
    return res;
}

kjErr kj_path_remove_dir(const char* path) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs) && !RemoveDirectoryW(KJ_WPATH_BUF)) {
        res = kj_err_from_sys(GetLastError());
    } else {
        res = kj_err(ucs);
    }
    return res;
}

kjErr kj_path_rename(const char* from, const char* to) {
    kj_assert(from);
    kj_assert(to);

    kjErr res = KJ_ERR_NONE;
    static WCHAR wto[KJ_PATH_MAX + 1] = {0};

    i32$ ucs1 = kj_utf8_to_ucs(from, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    i32$ ucs2 = kj_utf8_to_ucs(to, wto, kj_isize_of(wto));
    if(kj_is_ok(ucs1)) {
        if(kj_is_ok(ucs2)) {
            if(!MoveFileExW(KJ_WPATH_BUF, wto, MOVEFILE_REPLACE_EXISTING)) {
                res = kj_err_from_sys(GetLastError());
            }
        } else {
            res = kj_err(ucs2);
        }
    } else {
        res = kj_err(ucs1);
    }
    return res;
}

isize$ kj_path_current_dir(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res = {0};
    GetCurrentDirectoryW(kj_count_of(KJ_WPATH_BUF), KJ_WPATH_BUF);
    i32$ utf = kj_ucs_to_utf8(KJ_WPATH_BUF, path, kj_cast(i32, size));
    kj_ok(res) = kj_ok(utf);
    kj_err(res) = kj_err(utf);
    return res;
}

kjErr kj_path_set_current_dir(const char* path) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs) && !SetCurrentDirectoryW(KJ_WPATH_BUF)) {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_path_tmp_dir(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res = {0};
    DWORD wsize = GetTempPathW(0, NULL);
    GetTempPathW(wsize, KJ_WPATH_BUF);
    i32$ utf = kj_ucs_to_utf8(KJ_WPATH_BUF, path, kj_cast(i32, size));
    kj_ok(res) = kj_ok(utf);
    kj_err(res) = kj_err(utf);
    return res;
}

isize$ kj_path_self(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res = {0};
    kj_ok(res) = GetModuleFileNameW(
            NULL, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    i32$ utf = kj_ucs_to_utf8(KJ_WPATH_BUF, path, kj_cast(i32, size));
    kj_ok(res) = kj_ok(utf);
    kj_err(res) = kj_err(utf);
    return res;
}

b32 kj_path_exists(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs)) {
        HANDLE h = INVALID_HANDLE_VALUE;
        WIN32_FIND_DATAW find;
        if((h = FindFirstFileW(KJ_WPATH_BUF, &find)) != INVALID_HANDLE_VALUE) {
            FindClose(h);
            res = KJ_TRUE;
        }
    }
    return res;
}

b32 kj_path_is_file(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs)) {
        DWORD attr = INVALID_FILE_ATTRIBUTES;
        if((attr = GetFileAttributesW(KJ_WPATH_BUF))
                != INVALID_FILE_ATTRIBUTES) {
            res = kj_file_attr_to_type(attr) == KJ_FILE;
        }
    }
    return res;
}

b32 kj_path_is_dir(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs)) {
        DWORD attr = INVALID_FILE_ATTRIBUTES;
        if((attr = GetFileAttributesW(KJ_WPATH_BUF)) !=
                INVALID_FILE_ATTRIBUTES) {
            res = kj_file_attr_to_type(attr) == KJ_DIR ? KJ_TRUE: KJ_FALSE;
        }
    }
    return res;
}
#elif defined(KJ_SYS_LINUX)
kjErr kj_path_create_dir(const char* path) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall2(KJ_SYSCALL_RMDIR, out, path, S_IRWXU | S_IRGRP | S_IROTH);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    return res;
}

kjErr kj_path_remove_dir(const char* path) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall1(KJ_SYSCALL_RMDIR, out, path);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    return res;
}

kjErr kj_path_rename(const char* from, const char* to) {
    kj_assert(from);
    kj_assert(to);

    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall2(KJ_SYSCALL_RENAME, out, from, to);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    return res;
}

isize$ kj_path_current_dir(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res = {0};
    kj_syscall2(
            KJ_SYSCALL_GETCWD, kj_ok(res),
            KJ_PATH_BUF, kj_count_of(KJ_PATH_BUF));
    if(kj_ok(res) < 0) {
        kj_err(res) = kj_err_from_sys(-kj_ok(res));
    } elif(kj_ok(res) > size) {
        kj_err(res) = KJ_ERR_INSUFFICIENT_BUFFER;
    } else {
        kj_copy(path, KJ_PATH_BUF, kj_ok(res));
        path[kj_ok(res)] = '\0';
    }
    return res;
}

kjErr kj_path_set_current_dir(const char* path) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall1(KJ_SYSCALL_CHDIR, out, path);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    return res;
}

isize$ kj_path_tmp_dir(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res = {0};
    const char* tmp = NULL;
    if((tmp = getenv("TMPDIR")) == NULL) {
        tmp = "/tmp";
    }
    isize tmp_size = kj_cstr_count(tmp);
    if(tmp_size < size) {
        kj_copy(path, tmp, tmp_size);
        path[tmp_size] = '\0';
        kj_ok(res) = tmp_size;
    } else {
        kj_err(res) = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    return res;
}

isize$ kj_path_self(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res = {0};
    kj_syscall3(
            KJ_SYSCALL_READLINK, kj_ok(res), "/proc/self/exe",
            KJ_PATH_BUF, kj_count_of(KJ_PATH_BUF));
    if(kj_ok(res) < 0) {
        kj_err(res) = kj_err_from_sys(-kj_ok(res));
    } elif(kj_ok(res) > size) {
        kj_err(res) = KJ_ERR_INSUFFICIENT_BUFFER;
    } else {
        kj_copy(path, KJ_PATH_BUF, kj_ok(res));
        path[kj_ok(res)] = '\0';
    }
    return res;
}

b32 kj_path_exists(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    kj_syscall2(KJ_SYSCALL_ACCESS, res, path, 0);
    res = res == 0 ? KJ_TRUE: KJ_FALSE;
    return res;
}

b32 kj_path_is_file(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    struct stat st;
    kj_syscall2(KJ_SYSCALL_STAT, res, path, &st);
    res = res == 0 ? S_ISREG(st.st_mode) != 0: KJ_FALSE;
    return res;
}

b32 kj_path_is_dir(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    struct stat st;
    kj_syscall2(KJ_SYSCALL_STAT, res, path, &st);
    res = res == 0 ? S_ISDIR(st.st_mode) != 0: KJ_FALSE;
    return res;
}
#endif

#if defined(KJ_SYS_WIN32)
kjErr kj_read_dir_begin(kjReadDir* self, const char* path) {
    kj_assert(self);
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    kj_zero(self, kj_isize_of(kjReadDir));

    WIN32_FIND_DATAW find;
    i32$ ucs = kj_utf8_to_ucs(path, KJ_WPATH_BUF, kj_count_of(KJ_WPATH_BUF));
    if(kj_is_ok(ucs)) {
        if(KJ_WPATH_BUF[kj_ok(ucs) - 1] == KJ_PATH_SEPARATOR) {
            KJ_WPATH_BUF[kj_ok(ucs)] = '*';
            KJ_WPATH_BUF[kj_ok(ucs) + 1] = '\0';
        } else {
            KJ_WPATH_BUF[kj_ok(ucs) - 1] = KJ_PATH_SEPARATOR;
            KJ_WPATH_BUF[kj_ok(ucs)] = '*';
            KJ_WPATH_BUF[kj_ok(ucs) + 1] = '\0';
        }
        HANDLE handle = FindFirstFileW(KJ_WPATH_BUF, &find);
        if(handle != INVALID_HANDLE_VALUE) {
            self->find = find;
            self->handle = handle;
            self->first = KJ_TRUE;
        } else {
            res = kj_err_from_sys(GetLastError());
        }
    }
    return res;
}

kjErr kj_read_dir_next(kjReadDir* self, kjDirEntry* entry) {
    kj_assert(self);
    kj_assert(entry);

    kjErr res = KJ_ERR_NONE;
    if(self->first || FindNextFileW(self->handle, &self->find)) {
        i32$ utf = kj_ucs_to_utf8(
                self->find.cFileName, entry->path, kj_count_of(entry->path));
        res = kj_err(utf);
        entry->count = kj_ok(utf) - 1;
        self->first = KJ_FALSE;
    } else {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}

void kj_read_dir_end(kjReadDir* self) {
    kj_assert(self);

    if(self->handle) {
        FindClose(self->handle);
    }
}
#elif defined(KJ_SYS_LINUX)
kjErr kj_read_dir_begin(kjReadDir* self, const char* path) {
    kj_assert(self);
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    kj_zero(self, kj_isize_of(kjReadDir));

    if((self->dir = opendir(path)) == NULL) {
        res = kj_err_from_sys(errno);
    }
    return res;
}

kjErr kj_read_dir_next(kjReadDir* self, kjDirEntry* entry) {
    kj_assert(self);
    kj_assert(path);
    kj_assert(size > 0);

    kjErr res = KJ_ERR_NONE;
    struct dirent* result = NULL;
    struct dirent* ent = kj_cast(struct dirent*, entry->path);
    i32 err = 0;
    if((err = readdir_r(self->dir, ent, &result)) != 0) {
        res = kj_err_from_sys(err);
    }
    if(result) {
        isize size = kj_cstr_count_n(ent->d_name, KJ_PATH_MAX);
        kj_copy(entry->path, &ent->d_name[0], size);
        entry->path[size] = '\0';
    } else {
        res = KJ_ERR_NO_MORE_FILES;
    }
    return res;
}

void kj_read_dir_end(kjReadDir* self) {
    kj_assert(self);

    if(self->dir) {
        closedir(self->dir);
    }
}
#endif

kjBuffer kj_buffer(kjAllocator* allocator, isize granularity) {
    kj_assert(allocator);

    kjBuffer res;
    kj_zero(&res, kj_isize_of(kjBuffer));
    res.granularity = granularity;
    res.allocator = allocator;
    return res;
}

void kj_buffer_destroy(kjBuffer* self) {
    kj_assert(self);

    if(!self->data) {
        kj_allocator_free(self->allocator, self->data);
        self->data = NULL;
    }
}

kjErr kj_buffer_write(kjBuffer* self, const void* buf, isize size) {
    kj_assert(self);
    kj_assert(buf);
    kj_assert(size > 0);

    kjErr res = KJ_ERR_NONE;
    if(self->used + size > self->size) {
        isize new_size = kj_round_up(self->size + size, self->granularity);
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

void kj_buffer_clear(kjBuffer* self) {
    kj_assert(self);

    kj_zero(self->data, self->size);
}

#if defined(KJ_SYS_WIN32)
#if defined(KJ_DIALOG_IMPL)
kjErr kj_file_dialog(char* path, isize size, u32 mode) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    OPENFILENAMEW ofn = {0};
    ofn.lStructSize = kj_isize_of(OPENFILENAMEW);
    ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = KJ_WPATH_BUF;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = kj_count_of(KJ_WPATH_BUF);
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = mode & KJ_DIALOG_OPEN ? L"Open...": L"Save...";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |
        OFN_NOLONGNAMES | OFN_NOCHANGEDIR;
    b32 success = mode & KJ_DIALOG_OPEN ?
        GetOpenFileNameW(&ofn): GetSaveFileNameW(&ofn);
    if(success) {
        i32$ utf = kj_ucs_to_utf8(KJ_WPATH_BUF, path, kj_cast(i32, size));
        res = kj_err(utf);
    } else {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}
#endif
#endif

#endif
