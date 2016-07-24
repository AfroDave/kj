// `kj.h`
// public domain - no warranty implied; use at your own risk
//
// usage:
//      #define KJ_IMPL
//      #include "kj.h"

#ifndef KJ_H
#define KJ_H

#define KJ_VERSION_MAJOR 0
#define KJ_VERSION_MINOR 7
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
#elif defined(__linux__)
#define KJ_SYS_LINUX
#include <time.h>
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#else
#error Unsupported Operating System
#endif

#include <stdint.h>
#include <stdarg.h>

#if defined(_MSC_VER)
#define KJ_COMPILER_MSVC
#elif defined(__clang__)
#define KJ_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define KJ_COMPILER_GNU
#else
#error Unsupported Compiler
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define KJ_ARCH_64_BIT
#elif defined(__i386) || defined(_M_IX86)
#define KJ_ARCH_32_BIT
#else
#error Unsupported Architecture
#endif

enum {
    KJ_FALSE = (0 != 0),
    KJ_TRUE = (0 == 0),
    KJ_MAX_ASCII = 0x7F,
    KJ_MAX_LATIN1 = 0xFF,
    KJ_MAX_UNICODE = 0x10FFFF,
#if defined(KJ_SYS_LINUX)
    KJ_PATH_MAX = PATH_MAX,
#elif defined(KJ_SYS_LINUX)
    KJ_PATH_MAX = MAX_PATH,
#endif
    KJ_BIT_FLAG_NONE = 0,
    KJ_LE = 1234,
    KJ_BE = 4321,
#if defined(KJ_SYS_LINUX)
#if __BYTE_ORDER == __BIG_ENDIAN
    KJ_ENDIAN = KJ_BE,
#elif __BYTE_ORDER == __LITTLE_ENDIAN
    KJ_ENDIAN = KJ_LE,
#else
#error "Unsupported Endianness"
#endif
    KJ_PATH_SEPARATOR = '/'
#else
    KJ_ENDIAN = KJ_LE,
    KJ_PATH_SEPARATOR = '\\'
#endif
};

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
#define KJ_INLINE __attribute__((always_inline))
#endif
#endif

#if !defined(KJ_NO_INLINE)
#if defined(KJ_COMPILER_MSVC)
#define KJ_NO_INLINE __declspec(noinline)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_NO_INLINE __attribute__((noinline))
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
#endif

#if !defined(kj_isize_of)
#define kj_isize_of(a) (kj_cast(isize, sizeof(a)))
#define kj_usize_of(a) (kj_cast(usize, sizeof(a)))
#endif

#if !defined(kj_count_of)
#define kj_count_of(a) (kj_isize_of(a) / kj_isize_of((a)[0]))
#endif

#if !defined(kj_string_of)
#define kj_string_of(a) #a
#endif

#if !defined(kj_offset_of)
#define kj_offset_of(s, m) (kj_cast(isize, (&(kj_cast(s*, 0)->m))))
#endif

#if !defined(kj_align_of)
#define kj_align_of(type) (kj_offset_of(struct { u8 c; type member; }, member))
#endif

#if !defined(KJ_ALIGN)
#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_ALIGN(a) __attribute__((aligned(a)))
#elif defined(KJ_COMPILER_MSVC)
#define KJ_ALIGN(a) __declspec(align(a))
#endif
#endif

#if !defined(kj_align_on)
#define kj_align_on(p, a)                                                       \
    kj_cast(void*, (kj_cast(uptr, p) + ((a) - 1)) & ~((a) - 1))
#endif

#if !defined(kj_concat)
#define kj_concat(a, b) a##b
#define kj_join(a, b) kj_concat(a, b)
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
#define kj_swap(T, a, b) { T tmp_##__LINE__ = a; a = b; b = tmp_##__LINE__; }
#define kj_abs(a) ((a) > 0 ? (a): -(a))
#define kj_sign(a) ((a) >= 0 ? 1: -1)
#define kj_round_up(a, b) ((a) + (((b) - 1) - (((a) - 1) % (b))))
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
#endif

#if !defined(KJ_BIT_FLAG)
#define KJ_BIT_FLAG(a) (0x01 << (a))
#endif

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

#if !defined(KJ_TLS)
#if defined(KJ_COMPILER_MSVC)
#define KJ_TLS __declspec(thread)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_TLS __thread
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
#define I8_MIN k-j_cast(i8, 128)
#define I8_MAX kj_cast(i8, 127)

#define I16_MIN -kj_cast(i16, 32768)
#define I16_MAX kj_cast(i16, 32767)

#define I32_MIN -kj_cast(i32, 2147483648)
#define I32_MAX kj_cast(i32, 2147483647)

#define I64_MIN -kj_cast(i64, 9223372036854775808)
#define I64_MAX kj_cast(i64, 9223372036854775807)

#define U8_MIN kj_cast(u8, 0x00)
#define U8_MAX kj_cast(u8, 0xFF)

#define U16_MIN kj_cast(u16, 0x0000)
#define U16_MAX kj_cast(u16, 0xFFFF)

#define U32_MIN kj_cast(u32, 0x00000000)
#define U32_MAX kj_cast(u32, 0xFFFFFFFF)

#define U64_MIN kj_cast(u64, 0x0000000000000000)
#define U64_MAX kj_cast(u64, 0xFFFFFFFFFFFFFFFF)
#endif

typedef i8 b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

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

#define kj_static_assert(n, a) typedef void* kj_static_assert_##n[(a) * 2 - 1]
kj_static_assert(i8, kj_isize_of(i8) == 1);
kj_static_assert(u8, kj_isize_of(u8) == 1);
kj_static_assert(i16, kj_isize_of(i16) == 2);
kj_static_assert(u16, kj_isize_of(u16) == 2);
kj_static_assert(i32, kj_isize_of(i32) == 4);
kj_static_assert(u32, kj_isize_of(u32) == 4);
kj_static_assert(i64, kj_isize_of(i64) == 8);
kj_static_assert(u64, kj_isize_of(u64) == 8);
kj_static_assert(f32, kj_isize_of(f32) == 4);
kj_static_assert(f64, kj_isize_of(f64) == 8);

#define KJ_TYPE_MAP(X)                                                          \
    X(KJ_TYPE_UNKNOWN, 0, "unknown", void*)                                     \
    X(KJ_TYPE_NONE, 1, "none", void*)                                           \
    X(KJ_TYPE_CHAR, 2, "char", char)                                            \
    X(KJ_TYPE_I8, 3, "i8", i8)                                                  \
    X(KJ_TYPE_U8, 4, "u8", u8)                                                  \
    X(KJ_TYPE_I16, 5, "i16", i16)                                               \
    X(KJ_TYPE_U16, 6, "u16", u16)                                               \
    X(KJ_TYPE_I32, 7, "i32", i32)                                               \
    X(KJ_TYPE_U32, 8, "u32", u32)                                               \
    X(KJ_TYPE_I64, 9, "i64", i64)                                               \
    X(KJ_TYPE_U64, 10, "u64", u64)                                              \
    X(KJ_TYPE_ISIZE, 11, "isize", isize)                                        \
    X(KJ_TYPE_USIZE, 12, "usize", usize)                                        \
    X(KJ_TYPE_F32, 13, "f32", f32)                                              \
    X(KJ_TYPE_F64, 14, "f64", f64)                                              \
    X(KJ_TYPE_B8, 15, "b8", b8)                                                 \
    X(KJ_TYPE_B16, 16, "b16", b16)                                              \
    X(KJ_TYPE_B32, 17, "b32", b32)                                              \
    X(KJ_TYPE_B64, 18, "b64", b64)                                              \

typedef enum kjType {
#define KJ_TYPE_ENUM(type, ...) type,
    KJ_TYPE_MAP(KJ_TYPE_ENUM)
#undef KJ_TYPE_ENUM
    KJ_TYPE_COUNT
} kjType;

KJ_API const char* kj_type_to_str(kjType type);
KJ_API isize kj_type_to_isize(kjType type);

#define KJ_ERR_MAP(X)                                                           \
    X(KJ_ERR_UNKNOWN, 0, "Unknown")                                             \
    X(KJ_ERR_NONE, 1, "None")                                                   \
    X(KJ_ERR_BAD_HANDLE, 2, "Bad Handle")                                       \
    X(KJ_ERR_PERMISSION_DENIED, 3, "Permission Denied")                         \
    X(KJ_ERR_NOT_FOUND, 4, "Not Found")                                         \
    X(KJ_ERR_BROKEN_PIPE, 5, "Broken Pipe")                                     \
    X(KJ_ERR_ALREADY_EXISTS, 6, "Already Exists")                               \
    X(KJ_ERR_TIMED_OUT, 7, "Timed Out")                                         \
    X(KJ_ERR_INVALID_PARAMETER, 8, "Invalid Parameter")                         \
    X(KJ_ERR_INTERRUPED, 9, "Interrupted")                                      \
    X(KJ_ERR_ILLEGAL_SEEK, 10, "Illegal Seek")                                  \
    X(KJ_ERR_ALLOC_FAILED, 11, "Alloc Fail")                                      \
    X(KJ_ERR_ADDR_IN_USE, 12, "Address In Use")                                 \
    X(KJ_ERR_ADDR_NOT_AVAILABLE, 13, "Address Not Available")                   \
    X(KJ_ERR_CONNECTION_ABORTED, 14, "Connection Aborted")                      \
    X(KJ_ERR_CONNECTION_REFUSED, 15, "Connection Refused")                      \
    X(KJ_ERR_CONNECTION_RESET, 16, "Connection Reset")                          \
    X(KJ_ERR_NOT_CONNECTED, 17, "Not Connected")                                \
    X(KJ_ERR_WOULD_BLOCK, 18, "Would Block")                                    \
    X(KJ_ERR_INSUFFICIENT_BUFFER, 19, "Insufficient Buffer")

typedef enum kjErr {
#define KJ_ERR_ENUM(type, value, name) type = value,
    KJ_ERR_MAP(KJ_ERR_ENUM)
#undef KJ_ERR_ENUM
    KJ_ERR_COUNT
} kjErr;

KJ_API kjErr kj_err_from_sys(i32 err);
KJ_API const char* kj_err_to_str(kjErr err);

#define kj_result_ok(r) ((r).err == KJ_ERR_NONE)
#define kj_result_err(r) ((r).err != KJ_ERR_NONE)
#define KJ_RESULT(T) struct { T value; kjErr err; }
#define KJ_RESULT_SIZED(T) struct { T value; isize size; kjErr err; }
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
    KJ_ALLOC_FLAG_NONE = KJ_BIT_FLAG_NONE,
    KJ_ALLOC_FLAG_ZERO = KJ_BIT_FLAG(0),
};

KJ_API void* kj_global_alloc(isize size, u32 flags);
KJ_API void kj_global_free(void* data, u32 flags);
KJ_API void* kj_global_realloc(void* data, isize size, u32 flags);
KJ_API void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags);

typedef struct kjAllocator kjAllocator;

#define KJ_ALLOCATOR_ALLOC_FN(name)                                             \
    void* name(kjAllocator* allocator, isize size)
typedef KJ_ALLOCATOR_ALLOC_FN(kjAllocatorAllocFn);
#define KJ_ALLOCATOR_FREE_FN(name)                                              \
    void name(kjAllocator* allocator, void* data)
typedef KJ_ALLOCATOR_FREE_FN(kjAllocatorFreeFn);
#define KJ_ALLOCATOR_REALLOC_FN(name)                                           \
    void* name(kjAllocator* allocator, void* data, isize size)
typedef KJ_ALLOCATOR_REALLOC_FN(kjAllocatorReallocFn);
#define KJ_ALLOCATOR_ALLOC_ALIGNED_FN(name)                                     \
    void* name(kjAllocator* allocator, isize size, isize alignment)
typedef KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kjAllocatorAllocAlignedFn);

typedef struct kjAllocator {
    kjAllocatorAllocFn* alloc;
    kjAllocatorFreeFn* free;
    kjAllocatorReallocFn* realloc;
    kjAllocatorAllocAlignedFn* alloc_aligned;
    u32 flags;
} kjAllocator;

#define kj_allocator_alloc(a, s)                                                \
    kj_cast(kjAllocator*, (a))->alloc( kj_cast(kjAllocator*, (a)), (s))
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
KJ_API void kj_linear_allocator_clear(kjLinearAllocator* allocator);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_linear_alloc);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc);

/// Debug

#define KJ_ASSERT_HANDLER(name) void name(                                      \
        const char* expr, const char* file, u64 line,                           \
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
#define kj_assert(expr) kj_assert_msg_usr(expr, NULL, NULL)
#define kj_panic(msg) kj_assert_msg_usr(!"panic", msg, NULL)
#else
#define kj_assert_msg_usr(expr, msg, usr)
#define kj_assert_msg(expr, msg)
#define kj_assert(expr)
#define kj_panic(msg)
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
#define kj_syscall6(call, res, a, b, c, d, e, f)
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

KJ_API i32 kj_vprintf(const char* fmt, va_list v);
KJ_API i32 kj_printf(KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(1);
KJ_API i32 kj_vsnprintf(char* buf, isize size, const char* fmt, va_list v);
KJ_API i32 kj_snprintf(
        char* buf, isize size, KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(3);

/// Strings/Characters

typedef u8 utf8;
typedef u16 utf16;
typedef i32 utf32;

KJ_API b32 kj_char_is_eol(utf32 c);
KJ_API b32 kj_char_is_ws(utf32 c);
KJ_API b32 kj_char_is_alpha(utf32 c);
KJ_API b32 kj_char_is_digit(utf32 c);
KJ_API b32 kj_char_is_alphanum(utf32 c);
KJ_API b32 kj_char_is_hex_digit(utf32 c);
KJ_API b32 kj_char_is_lower(utf32 c);
KJ_API b32 kj_char_is_upper(utf32 c);

KJ_API utf32 kj_char_to_lower(utf32 c);
KJ_API utf32 kj_char_to_upper(utf32 c);

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

KJ_API isize kj_utf8_count_n(const char* s, isize size);
KJ_API isize kj_utf8_count(const char* s);

#if defined(KJ_SYS_WIN32)
KJ_API i32 kj_utf8_to_ucs(const char* s, WCHAR* ws, i32 size);
KJ_API i32 kj_ucs_to_utf8(const WCHAR* ws, char* s, i32 size);
#endif

/// Dynamic Libraries

typedef void* kjLib;
typedef void (*kjLibFn)(void);
KJ_API kjLib kj_lib_open(const char* path);
KJ_API kjLibFn kj_lib_fn(kjLib lib, const char* name);
KJ_API void kj_lib_close(kjLib lib);

/// Sorting

#define KJ_CMP_FN(name) i32 name(void* arr, isize i, isize j)
typedef KJ_CMP_FN(kjCmpFn);

KJ_API KJ_CMP_FN(kj_cmp_i8);
KJ_API KJ_CMP_FN(kj_cmp_u8);
KJ_API KJ_CMP_FN(kj_cmp_i16);
KJ_API KJ_CMP_FN(kj_cmp_u16);
KJ_API KJ_CMP_FN(kj_cmp_i32);
KJ_API KJ_CMP_FN(kj_cmp_u32);
KJ_API KJ_CMP_FN(kj_cmp_i64);
KJ_API KJ_CMP_FN(kj_cmp_u64);
KJ_API KJ_CMP_FN(kj_cmp_isize);
KJ_API KJ_CMP_FN(kj_cmp_usize);
KJ_API KJ_CMP_FN(kj_cmp_f32);
KJ_API KJ_CMP_FN(kj_cmp_f64);

#define KJ_SWAP_FN(name) void name(void* arr, isize i, isize j)
typedef KJ_SWAP_FN(kjSwapFn);

KJ_API KJ_SWAP_FN(kj_swap_i8);
KJ_API KJ_SWAP_FN(kj_swap_u8);
KJ_API KJ_SWAP_FN(kj_swap_i16);
KJ_API KJ_SWAP_FN(kj_swap_u16);
KJ_API KJ_SWAP_FN(kj_swap_i32);
KJ_API KJ_SWAP_FN(kj_swap_u32);
KJ_API KJ_SWAP_FN(kj_swap_i64);
KJ_API KJ_SWAP_FN(kj_swap_u64);
KJ_API KJ_SWAP_FN(kj_swap_isize);
KJ_API KJ_SWAP_FN(kj_swap_usize);
KJ_API KJ_SWAP_FN(kj_swap_f32);
KJ_API KJ_SWAP_FN(kj_swap_f64);

KJ_API void kj_sort_insertion(
        void* arr, isize count, kjCmpFn cmp, kjSwapFn swap);

/// Date/Time

#define KJ_DATETIME_UTC_ISO_FMT "%04d-%02d-%02dT%02d:%02d:%02dZ"
#define KJ_DATETIME_LOCAL_ISO_FMT "%04d-%02d-%02dT%02d:%02d:%02d%c%02d:%02d"
#define KJ_DATETIME_UTC_EXPAND(dt)                                              \
    (dt)->year, (dt)->month, (dt)->day, (dt)->hour, (dt)->minute, (dt)->second
#define KJ_DATETIME_LOCAL_EXPAND(dt)                                            \
    (dt)->year, (dt)->month, (dt)->day, (dt)->hour, (dt)->minute, (dt)->second, \
    (dt)->tz < 0 ? '-': '+', kj_abs(((dt)->tz / 60)), kj_abs(((dt)->tz % 60))

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

KJ_API kjDateTime kj_datetime_utc(void);
KJ_API kjDateTime kj_datetime_local(void);

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

typedef struct kjFile {
#if defined(KJ_SYS_WIN32)
    HANDLE handle;
#elif defined(KJ_SYS_LINUX)
    i32 handle;
#endif
    u32 flags;
} kjFile;

typedef struct kjFileStat {
    i64 size;
    kjDateTime last_access;
    kjDateTime last_write;
} kjFileStat;

KJ_API kjErr kj_file_open(kjFile* file, const char* path, u32 flags);
KJ_API kjErr kj_file_close(kjFile* file);
KJ_API kjErr kj_file_seek(kjFile* file, i64 offset, kjSeekFrom seek);
KJ_API isize$ kj_file_read(kjFile* file, void* buf, isize size);
KJ_API isize$ kj_file_write(kjFile* file, const void* buf, isize size);
KJ_API isize$ kj_file_read_at(kjFile* file, void* buf, isize size, i64 offset);
KJ_API isize$ kj_file_write_at(
        kjFile* file, const void* buf, isize size, i64 offset);
KJ_API void$$ kj_file_slurp(
        kjAllocator* allocator, const char* path, b32 terminate);

KJ_API kjErr kj_file_stat(kjFile* file, kjFileStat* stat);
KJ_API kjErr kj_file_stat_path(const char* path, kjFileStat* stat);

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

typedef struct kjFileGroup {
    kjErr err;
    isize count;
#if defined(KJ_SYS_WIN32)
    WIN32_FIND_DATAW find;
    HANDLE handle;
#elif defined(KJ_SYS_LINUX)
    DIR* dir;
    struct dirent* entry;
#endif
} kjFileGroup;

KJ_API kjErr kj_file_group_begin(kjFileGroup* g, const char* path);
KJ_API isize kj_file_group_next(kjFileGroup* g, char* path, isize size);
KJ_API void kj_file_group_end(kjFileGroup* g);

/// Buffer

typedef struct kjBuffer {
    kjHeapAllocator* allocator;
    isize granularity;
    isize size;
    isize used;
    u8* data;
} kjBuffer;

KJ_API kjBuffer kj_buffer(kjHeapAllocator* allocator, isize granularity);
KJ_API void kj_buffer_destroy(kjBuffer* buffer);
KJ_API kjErr kj_buffer_write(kjBuffer* buffer, const void* data, isize size);
KJ_API void kj_buffer_clear(kjBuffer* buffer);

KJ_EXTERN_END

#endif

#if defined(KJ_IMPL)
KJ_INLINE const char* kj_type_to_str(kjType type) {
    static const char* KJ_TYPE_STR[] = {
#define KJ_TYPE_NAME(type, value, name, T) name,
    KJ_TYPE_MAP(KJ_TYPE_NAME)
#undef KJ_TYPE_NAME
    };
    return type <= KJ_TYPE_UNKNOWN || type >= KJ_TYPE_COUNT ?
        KJ_TYPE_STR[KJ_TYPE_UNKNOWN]: KJ_TYPE_STR[type];
}

KJ_INLINE isize kj_type_to_isize(kjType type) {
    static const isize KJ_TYPE_ISIZE[] = {
#define KJ_TYPE_SIZE(type, value, name, T) kj_isize_of(T),
    KJ_TYPE_MAP(KJ_TYPE_SIZE)
#undef KJ_TYPE_SIZE
    };
    return type <= KJ_TYPE_NONE || type >= KJ_TYPE_COUNT ?
        0: KJ_TYPE_ISIZE[type];
}

#if defined(KJ_SYS_WIN32)
kjErr kj_err_from_sys(i32 err) {
    switch(err) {
        case ERROR_SUCCESS: return KJ_ERR_NONE;
        case ERROR_ACCESS_DENIED: return KJ_ERR_PERMISSION_DENIED;
        case ERROR_ALREADY_EXISTS: return KJ_ERR_ALREADY_EXISTS;
        case ERROR_BROKEN_PIPE: return KJ_ERR_BROKEN_PIPE;
        case ERROR_FILE_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_PATH_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_NO_DATA: return KJ_ERR_BROKEN_PIPE;
        case ERROR_INVALID_PARAMETER: return KJ_ERR_INVALID_PARAMETER;
        case ERROR_OPERATION_ABORTED: return KJ_ERR_TIMED_OUT;
        case ERROR_SEEK: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_NEGATIVE_SEEK: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_SEEK_ON_DEVICE: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_INSUFFICIENT_BUFFER: return KJ_ERR_INSUFFICIENT_BUFFER;
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
#define KJ_ERR_NAME(type, value, name) name,
    KJ_ERR_MAP(KJ_ERR_NAME)
#undef KJ_ERR_NAME
    };
    const char* res = err <= KJ_ERR_UNKNOWN || err >= KJ_ERR_COUNT ?
        KJ_ERR_STR[KJ_ERR_UNKNOWN]: KJ_ERR_STR[err];
    return res;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_ALLOC_FN(kj_dummy_alloc) {
    kj_unused(allocator);
    kj_unused(size);
    return NULL;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_FREE_FN(kj_dummy_free) {
    kj_unused(allocator);
    kj_unused(data);
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_REALLOC_FN(kj_dummy_realloc) {
    kj_unused(allocator);
    kj_unused(data);
    kj_unused(size);
    return NULL;
}

KJ_INTERN KJ_INLINE KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_dummy_alloc_aligned) {
    kj_unused(allocator);
    kj_unused(size);
    kj_unused(alignment);
    return NULL;
}

#if defined(KJ_SYS_WIN32)
void* kj_global_alloc(isize size, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_FLAG_ZERO) {
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
    if(flags & KJ_ALLOC_FLAG_ZERO) {
        res = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, data, size);
    } else {
        res = HeapReAlloc(GetProcessHeap(), 0, data, size);
    }
    return res;
}

void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_FLAG_ZERO) {
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
    if(flags & KJ_ALLOC_FLAG_ZERO) {
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
    if(flags & KJ_ALLOC_FLAG_ZERO) {
        // size of data is unknown, add small header?
    } else {
        res = realloc(data, size * kj_isize_of(u8));
    }
    return res;
}

void* kj_global_alloc_aligned(isize size, isize alignment, u32 flags) {
    void* res = NULL;
    if(flags & KJ_ALLOC_FLAG_ZERO) {
        res = calloc(size + alignment, kj_isize_of(u8));
    } else {
        res = malloc((size + alignment) * kj_isize_of(u8));
    }
    res = kj_align_on(kj_cast(u8*, res), alignment);
    return res;
}
#endif

KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc) {
    kj_unused(allocator);
    return kj_global_alloc(size, allocator->flags);
}

KJ_ALLOCATOR_FREE_FN(kj_heap_free) {
    kj_unused(allocator);
    kj_global_free(data, allocator->flags);
}

KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc) {
    kj_unused(allocator);
    return kj_global_realloc(data, size, allocator->flags);
}

KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_heap_alloc_aligned) {
    kj_unused(allocator);
    return kj_global_alloc_aligned(size, alignment, allocator->flags);
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
    if(allocator) {
        kjLinearAllocator* a = kj_cast(kjLinearAllocator*, allocator);
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
    if(allocator) {
        kjLinearAllocator* a = kj_cast(kjLinearAllocator*, allocator);
        if(data == (a->data + a->offset)) {
            a->used = a->offset;
        }
    }
}

KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc) {
    void* res = NULL;
    if(allocator) {
        kjLinearAllocator* a = kj_cast(kjLinearAllocator*, allocator);
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
    kj_unused(allocator);
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
    res.data = data;
    res.size = size;
    res.used = 0;
    res.offset = 0;
    return res;
}

void kj_linear_allocator_clear(kjLinearAllocator* allocator) {
    if(allocator) {
        allocator->used = 0;
    }
}

#if defined(KJ_SYS_WIN32)
KJ_ASSERT_HANDLER(kj_assert_handler) {
    kj_unused(usr);
    static char buf[4096] = {0};
    kj_snprintf(
            buf, kj_isize_of(buf) - 1,
            "%s:%lu - %s %s", file, line, expr, msg ? msg: "");
    buf[kj_isize_of(buf) - 1] = '\0';
    MessageBoxA(NULL, buf, "Assertion", MB_OK);
}
#elif defined(KJ_SYS_LINUX)
KJ_ASSERT_HANDLER(kj_assert_handler) {
    kj_unused(usr);
    if(msg) {
        kj_printf("%s:%lu - %s %s", file, line, expr, msg);
    } else {
        kj_printf("%s:%lu - %s", file, line, expr);
    }
}
#endif

KJ_INLINE u16 kj_byte_swap_u16(u16 a) {
    return kj_cast(u16, (a << 8) | (a >> 8));
}

KJ_INLINE u32 kj_byte_swap_u32(u32 a) {
    return kj_cast(u32, (a << 24) | ((a << 8) & 0x00FF0000) |
                       ((a >> 8) & 0x0000FF00) | (a >> 24));
}

KJ_INLINE u64 kj_byte_swap_u64(u64 a) {
    return kj_cast(u64, kj_byte_swap_u32((a & 0xFFFFFFFF00000000) >> 32) |
                        kj_byte_swap_u32((a & 0x00000000FFFFFFFF) << 32));
}

i32 kj_vprintf(const char* fmt, va_list v) {
    return vprintf(fmt, v);
}

i32 kj_printf(KJ_FMT_STR const char* fmt, ...) {
    i32 res;
    va_list v;
    va_start(v, fmt);
    res = kj_vprintf(fmt, v);
    va_end(v);
    return res;
}

i32 kj_vsnprintf(char* buf, isize size, const char* fmt, va_list v) {
    i32 res;
#if defined(KJ_COMPILER_MSVC)
    res = _vsnprintf(buf, size, fmt, v);
#else
    res = vsnprintf(buf, size, fmt, v);
#endif
    if(size) {
        buf[size - 1] = '\0';
    }
    return (res >= size || res < 0) ? -1 : res;
}

i32 kj_snprintf(char* buf, isize size, KJ_FMT_STR const char* fmt, ...) {
    i32 res;
    va_list v;
    va_start(v,fmt);
    res = kj_vsnprintf(buf, size, fmt, v);
    va_end(v);
    return res;
}

KJ_INLINE b32 kj_char_is_eol(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return c == '\r' ||
               c == '\n';
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_ws(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return c == ' '  ||
               c == '\t' ||
               c == '\v' ||
               c == '\f' ||
               c == '\r' ||
               c == '\n' ||
               c == 0x85 ||
               c == 0xA0;
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_alpha(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <='Z');
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_digit(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= '0' && c <= '9');
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_alphanum(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9');
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_hex_digit(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'f') ||
               (c >= 'A' && c <= 'F') ||
               (c >= '0' && c <= '9');
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_lower(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z');
    }
    return KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_upper(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'A' && c <= 'Z');
    }
    return KJ_FALSE;
}

KJ_INLINE utf32 kj_char_to_lower(utf32 c) {
    if(c <= KJ_MAX_ASCII) {
        return (c >= 'A' && c <= 'Z') ? 'a' + (c - 'A'): c;
    }
    return c;
}

KJ_INLINE utf32 kj_char_to_upper(utf32 c) {
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
    isize res = -1;
    if(s && v) {
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
            if(kj_char_is_digit(c)) {
                tmp = tmp * base + c - '0';
            } elif(base == 16 && c >= 'a' && c <= 'f') {
                tmp = tmp * base + c - 'a' + 10;
            } elif(base == 16 && c >= 'A' && c <= 'F') {
                tmp = tmp * base + c - 'A' + 10;
            } else {
                break;
            }
        }
        res = (s - str) - 1;
        if(res > 0) {
            *v = tmp;
        }
    }
    return res;
}

isize kj_cstr_to_i64(const char* s, i64* v) {
    isize res = -1;
    i64 sign = *s == '-' ? s++, -1: 1;
    u64 tmp;
    res = kj_cstr_to_u64(s, &tmp);
    if(res > 0) {
        *v = kj_cast(i64, tmp) * sign;
    }
    return res;
}

KJ_INLINE const char* kj_cstr_find_n(const char* s, isize size, char c) {
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

KJ_INLINE const char* kj_cstr_rfind_n(const char* s, isize size, char c) {
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
i32 kj_utf8_to_ucs(const char* s, WCHAR* ws, i32 size) {
    i32 res = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
    if(res < size) {
        MultiByteToWideChar(CP_UTF8, 0, s, -1, ws, size);
    }
    return res;
}

i32 kj_ucs_to_utf8(const WCHAR* ws, char* s, i32 size) {
    i32 res = WideCharToMultiByte(CP_UTF8, 0, ws, -1, NULL, 0, NULL, NULL);
    if(res < size) {
        WideCharToMultiByte(CP_UTF8, 0, ws, -1, s, size, NULL, NULL);
    }
    return res;
}

#define kj_utf8_to_ucs_scope(s, ws, scope) do {                                 \
    i32 ws##size = MultiByteToWideChar(CP_UTF8, 0, (s), -1, NULL, 0);           \
    WCHAR* (ws) = kj_cast(WCHAR*, _malloca(ws##size * kj_isize_of(WCHAR)));     \
    MultiByteToWideChar(CP_UTF8, 0, (s), -1, (ws), ws##size);                   \
    { scope }                                                                   \
    _freea(ws);                                                                 \
} while(0)

#define kj_ucs_to_utf8_scope(ws, s, scope) do {                                 \
    i32 s##size =                                                               \
        WideCharToMultiByte(CP_UTF8, 0, (ws), -1, NULL, 0, NULL, NULL);         \
    char* (s) = kj_cast(char*, _malloca(s##size * kj_isize_of(char)));          \
    WideCharToMultiByte(CP_UTF8, 0, (ws), -1, (s), s##size, NULL, NULL);        \
    { scope }                                                                   \
    _freea(ws);                                                                 \
} while(0)
#endif

#if defined(KJ_LIB_IMPL)
#if defined(KJ_SYS_WIN32)
KJ_INLINE kjLib kj_lib_open(const char* path) {
    kjLib res = NULL;
    kj_utf8_to_ucs_scope(path, wpath, {
        if(wpath) {
            res = kj_cast(kjLib, LoadLibraryW(wpath));
        }
    });
    return res;
}

KJ_INLINE kjLibFn kj_lib_fn(kjLib lib, const char* name) {
    return kj_cast(kjLibFn, GetProcAddress(kj_cast(HMODULE, lib), name));
}

KJ_INLINE void kj_lib_close(kjLib lib) {
    FreeLibrary(kj_cast(HMODULE, lib));
}
#elif defined(KJ_SYS_LINUX)
KJ_INLINE kjLib kj_lib_open(const char* path) {
    return kj_cast(kjLib, dlopen(path, RTLD_LAZY));
}

KJ_INLINE kjLibFn kj_lib_fn(kjLib lib, const char* name) {
    return kj_cast(kjLibFn, dlsym(lib, name));
}

KJ_INLINE void kj_lib_close(kjLib lib) {
    dlclose(lib);
}
#endif
#endif

#define KJ_CMP_FN_T(T) KJ_INLINE KJ_CMP_FN(kj_cmp_##T) {                        \
    T a = kj_cast(T*, arr)[i];                                                  \
    T b = kj_cast(T*, arr)[j];                                                  \
    return kj_cast(i32, a < b ? -1: a > b);                                     \
}

KJ_CMP_FN_T(i8)
KJ_CMP_FN_T(u8)
KJ_CMP_FN_T(i16)
KJ_CMP_FN_T(u16)
KJ_CMP_FN_T(i32)
KJ_CMP_FN_T(u32)
KJ_CMP_FN_T(i64)
KJ_CMP_FN_T(u64)
KJ_CMP_FN_T(isize)
KJ_CMP_FN_T(usize)
KJ_CMP_FN_T(f32)
KJ_CMP_FN_T(f64)

#undef KJ_CMP_FN_T

#define KJ_SWAP_FN_T(T) KJ_INLINE KJ_SWAP_FN(kj_swap_##T) {                     \
    T* values = kj_cast(T*, arr);                                               \
    T tmp = values[i];                                                          \
    values[i] = values[j];                                                      \
    values[j] = tmp;                                                            \
}

KJ_SWAP_FN_T(i8)
KJ_SWAP_FN_T(u8)
KJ_SWAP_FN_T(i16)
KJ_SWAP_FN_T(u16)
KJ_SWAP_FN_T(i32)
KJ_SWAP_FN_T(u32)
KJ_SWAP_FN_T(i64)
KJ_SWAP_FN_T(u64)
KJ_SWAP_FN_T(isize)
KJ_SWAP_FN_T(usize)
KJ_SWAP_FN_T(f32)
KJ_SWAP_FN_T(f64)

#undef KJ_SWAP_FN_T

void kj_sort_insertion(void* arr, isize count, kjCmpFn cmp, kjSwapFn swap) {
    for(isize i = 1; i < count; i++) {
        for(isize j = i - 1; j >= 0; j--) {
            if(cmp(arr, j, j + 1) > 0) {
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
    dt->tz = 0;
}

kjDateTime kj_datetime_utc(void) {
    kjDateTime res;
    SYSTEMTIME st = {0};
    GetSystemTime(&st);
    kj_systime_to_datetime(&st, &res);
    return res;
}

kjDateTime kj_datetime_local(void) {
    kjDateTime res;
    SYSTEMTIME st = {0};
    GetLocalTime(&st);
    TIME_ZONE_INFORMATION tz = {0};
    switch(GetTimeZoneInformation(&tz)) {
        case 0: { res.tz = kj_cast(i16, tz.Bias); } break;
        case 1: { res.tz = kj_cast(i16, tz.StandardBias); } break;
        case 2: { res.tz = kj_cast(i16, tz.DaylightBias); } break;
    }
    res.year = st.wYear;
    res.month = st.wMonth;
    res.day = st.wDay;
    res.hour = st.wHour;
    res.minute = st.wMinute;
    res.second = st.wSecond;
    res.millisecond = st.wMilliseconds;
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

#define KJ_FILE_INVALID_MODE U32_MAX

#if defined(KJ_SYS_WIN32)
KJ_INTERN u32 kj_file_gen_access_mode(u32 flags) {
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

KJ_INTERN u32 kj_file_gen_create_mode(u32 flags) {
    u32 res = 0;
    if(!(flags & KJ_FILE_WRITE) &&
       !(flags & KJ_FILE_APPEND)) {
        if((flags & KJ_FILE_TRUNCATE) ||
           (flags & KJ_FILE_CREATE) ||
           (flags & KJ_FILE_CREATE_NEW)) {
            res = KJ_FILE_INVALID_MODE;
        }
    } elif(flags & KJ_FILE_APPEND) {
        if((flags & KJ_FILE_TRUNCATE) &&
          !(flags & KJ_FILE_CREATE_NEW)) {
            res = KJ_FILE_INVALID_MODE;
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

kjErr kj_file_open(kjFile* file, const char* path, u32 flags) {
    kj_assert(file);

    kjErr res = KJ_ERR_NONE;
    u32 access = kj_file_gen_access_mode(flags);
    u32 create = kj_file_gen_create_mode(flags);
    if((access | create) == KJ_FILE_INVALID_MODE) {
        file->handle = NULL;
        file->flags = 0;
    } else {
        kj_utf8_to_ucs_scope(path, wpath, {
            if(wpath) {
                file->handle = CreateFileW(
                    wpath, access,
                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    NULL, create, 0, NULL);
                file->flags = flags;
                res = file->handle == INVALID_HANDLE_VALUE ? KJ_ERR_BAD_HANDLE:
                kj_err_from_sys(GetLastError());
            }
        });
    }
    return res;
}

kjErr kj_file_close(kjFile* file) {
    kj_assert(file);

    kjErr res = KJ_ERR_NONE;
    if(!CloseHandle(file->handle)) {
        res = kj_err_from_sys(GetLastError());
    }
    file->handle = NULL;
    return res;
}

kjErr kj_file_seek(kjFile* file, i64 offset, kjSeekFrom seek) {
    kj_assert(file);

    kjErr res = KJ_ERR_NONE;
    LARGE_INTEGER new_offset;
    new_offset.QuadPart = offset;
    if(SetFilePointerEx(file->handle, new_offset, &new_offset, seek) == 0) {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_file_read(kjFile* file, void* buf, isize size) {
    kj_assert(file);

    isize$ res = {0};
    DWORD read = 0;
    if(ReadFile(
        file->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), NULL)) {
        res.value = read;
        res.err = KJ_ERR_NONE;
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_file_write(kjFile* file, const void* buf, isize size) {
    kj_assert(file);

    isize$ res = {0};
    DWORD wrote = 0;
    if(WriteFile(
        file->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), NULL)) {
        res.value = wrote;
        res.err = KJ_ERR_NONE;
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_file_read_at(kjFile* file, void* buf, isize size, i64 offset) {
    kj_assert(file);

    isize$ res = {0};
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(
        file->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), &overlapped)) {
        res.value = read;
        res.err = KJ_ERR_NONE;
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
    return res;
}

isize$ kj_file_write_at(kjFile* file, const void* buf, isize size, i64 offset) {
    kj_assert(file);

    isize$ res = {0};
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(
        file->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), &overlapped)) {
        res.value = wrote;
        res.err = KJ_ERR_NONE;
    } else {
        res.err = kj_err_from_sys(GetLastError());
    }
    return res;
}

kjErr kj_file_stat(kjFile* file, kjFileStat* stat) {
    kj_assert(file);

    kjErr res = KJ_ERR_NONE;
    BY_HANDLE_FILE_INFORMATION io_info = {0};
    if(stat && GetFileInformationByHandle(file->handle, &io_info)) {
        stat->size = (kj_cast(i64, io_info.nFileSizeHigh) << 32) |
                      kj_cast(i64, io_info.nFileSizeLow);
        SYSTEMTIME last_access = {0};
        SYSTEMTIME last_write = {0};
        FileTimeToSystemTime(&io_info.ftLastAccessTime, &last_access);
        FileTimeToSystemTime(&io_info.ftLastWriteTime, &last_write);
        kj_systime_to_datetime(&last_access, &stat->last_access);
        kj_systime_to_datetime(&last_write, &stat->last_write);
    } else {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}
#elif defined(KJ_SYS_LINUX)
KJ_INTERN u32 kj_file_gen_access_mode(u32 flags) {
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

KJ_INTERN u32 kj_file_gen_create_mode(u32 flags) {
    u32 res = 0;
    if(!(flags & KJ_FILE_WRITE) &&
       !(flags & KJ_FILE_APPEND)) {
        if((flags & KJ_FILE_TRUNCATE) ||
           (flags & KJ_FILE_CREATE) ||
           (flags & KJ_FILE_CREATE_NEW)) {
            res = KJ_FILE_INVALID_MODE;
        }
    } elif(flags & KJ_FILE_APPEND) {
        if((flags & KJ_FILE_TRUNCATE) &&
          !(flags & KJ_FILE_CREATE_NEW)) {
            res = KJ_FILE_INVALID_MODE;
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

kjErr kj_file_open(kjFile* file, const char* path, u32 flags) {
    kj_assert(file);

    kjErr res = KJ_ERR_NONE;
    u32 access = kj_file_gen_access_mode(flags);
    u32 create = kj_file_gen_create_mode(flags);
    if((access | create) == KJ_FILE_INVALID_MODE) {
        file->handle = -1;
        file->flags = 0;
        res = KJ_ERR_INVALID_PARAMETER;
    } else {
        u32 perm = 0666;
        kj_syscall3(
                KJ_SYSCALL_OPEN, file->handle, path, (access | create), perm);
        file->flags = flags;
        res = file->handle < 0 ? kj_err_from_sys(-file->handle): KJ_ERR_NONE;
    }
    return res;
}

kjErr kj_file_close(kjFile* file) {
    kj_assert(file);

    kjErr res = KJ_ERR_NONE;
    i32 out = 0;
    kj_syscall1(KJ_SYSCALL_CLOSE, out, file->handle);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    file->handle = -1;
    file->flags = 0;
    return res;
}

kjErr kj_file_seek(kjFile* file, i64 offset, kjSeekFrom seek) {
    kj_assert(file);

    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall3(KJ_SYSCALL_LSEEK, out, file->handle, offset, seek);
    res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    return res;
}

isize$ kj_file_read(kjFile* file, void* buf, isize size) {
    kj_assert(file);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    kj_syscall3(KJ_SYSCALL_READ, res.value, file->handle, buf, size);
    res.err = res.value < 0 ? kj_err_from_sys(-res.value): KJ_ERR_NONE;
    return res;
}

isize$ kj_file_write(kjFile* file, const void* buf, isize size) {
    kj_assert(file);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    kj_syscall3(KJ_SYSCALL_WRITE, res.value, file->handle, buf, size);
    res.err = res.value < 0 ? kj_err_from_sys(-res.value): KJ_ERR_NONE;
    return res;
}

isize$ kj_file_read_at(kjFile* file, void* buf, isize size, i64 offset) {
    kj_assert(file);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    kj_syscall4(KJ_SYSCALL_PREAD, res.value, file->handle, buf, size, offset);
    res.err = res.value < 0 ? kj_err_from_sys(-res.value): KJ_ERR_NONE;
    return res;
}

isize$ kj_file_write_at(kjFile* file, const void* buf, isize size, i64 offset) {
    kj_assert(file);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    kj_syscall4(KJ_SYSCALL_PWRITE, res.value, file->handle, buf, size, offset);
    res.err = res.value < 0 ? kj_err_from_sys(-res.value): KJ_ERR_NONE;
    return res;
}

kjErr kj_file_stat(kjFile* file, kjFileStat* stat) {
    kj_assert(file);
    kj_assert(stat);

    kjErr res = KJ_ERR_NONE;
    struct stat buf;
    isize out = -1;
    kj_syscall2(KJ_SYSCALL_FSTAT, out, file->handle, &buf);
    if(out == -1) {
        res = out < 0 ? kj_err_from_sys(-out): KJ_ERR_NONE;
    } else {
        stat->size = buf.st_size;
        struct tm* last_access = gmtime(&buf.st_atime);
        struct tm* last_write = gmtime(&buf.st_mtime);
        kj_systime_to_datetime(last_access, &stat->last_access);
        kj_systime_to_datetime(last_write, &stat->last_write);
    }
    return res;
}
#endif

void$$ kj_file_slurp(kjAllocator* allocator, const char* path, b32 terminate) {
    kj_assert(allocator);
    kj_assert(path);

    void$$ res;
    res.err = KJ_ERR_NONE;
    kjFile file;
    if((res.err = kj_file_open(&file, path, KJ_FILE_READ)) == KJ_ERR_NONE) {
        kjFileStat stat;
        if((res.err = kj_file_stat(&file, &stat)) == KJ_ERR_NONE) {
            res.value = kj_allocator_alloc(
                    allocator, terminate ? stat.size + 1: stat.size);
            isize$ read = kj_file_read(&file, res.value, stat.size);
            if(kj_result_ok(read) && read.value == stat.size) {
                if(terminate) {
                    kj_cast(u8*, res.value)[stat.size] = '\0';
                }
                res.size = stat.size;
            } else {
                kj_allocator_free(allocator, res.value);
                res.value = NULL;
                res.err = KJ_ERR_ALLOC_FAILED;
                res.size = -1;
            }
        }
        kj_file_close(&file);
    }
    return res;
}

isize$ kj_file_spit(const char* path, const void* buf, isize size) {
    kj_assert(path);
    kj_assert(buf);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    kjFile file;
    if((res.err = kj_file_open(&file, path, KJ_FILE_WRITE)) == KJ_ERR_NONE) {
        res = kj_file_write(&file, buf, size);
        kj_file_close(&file);
    }
    return res;
}

kjErr kj_file_stat_path(const char* path, kjFileStat* stat) {
    kj_assert(path);
    kj_assert(stat);

    kjErr res = KJ_ERR_NONE;
    kjFile file;
    if((res = kj_file_open(&file, path, KJ_FILE_READ)) == KJ_ERR_NONE) {
        if((res = kj_file_stat(&file, stat)) == KJ_ERR_NONE) {
            res = kj_file_close(&file);
        }
    }
    return res;
}

const char* kj_path_extension_n(const char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    const char* res = NULL;
    if(path[size - 1] != '.') {
        for(isize i = size - 1; i > 0; i--) {
            if(path[i] == KJ_PATH_SEPARATOR) {
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

const char* kj_path_basename_n(const char* path, isize size, const char** end) {
    kj_assert(end);

    const char* res = NULL;
    if(size == 1) {
        res = path;
        *end = path + size;
    } else {
        size = path[size - 1] == KJ_PATH_SEPARATOR ? size - 1: size;
        res = kj_cstr_rfind_n(path, size, KJ_PATH_SEPARATOR);
        res = res == NULL ? path: res + 1;
        *end = &path[size];
    }
    return res;
}

KJ_INLINE const char* kj_path_basename(const char* path, const char** end) {
    return kj_path_basename_n(path, kj_cstr_count(path), end);
}

const char* kj_path_dirname_n(const char* path, isize size, const char** end) {
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
    if(path) {
        kj_utf8_to_ucs_scope(path, wpath, {
            if(wpath && !CreateDirectoryW(&wpath[0], NULL)) {
                res = kj_err_from_sys(GetLastError());
            }
        });
    } else {
        res = KJ_ERR_INVALID_PARAMETER;
    }
    return res;
}

kjErr kj_path_remove_dir(const char* path) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    if(path) {
        kj_utf8_to_ucs_scope(path, wpath, {
            if(wpath && !RemoveDirectoryW(&wpath[0])) {
                res = kj_err_from_sys(GetLastError());
            }
        });
    } else {
        res = KJ_ERR_INVALID_PARAMETER;
    }
    return res;
}

kjErr kj_path_rename(const char* from, const char* to) {
    kj_assert(from);
    kj_assert(to);

    kjErr res = KJ_ERR_NONE;
    kj_utf8_to_ucs_scope(from, wfrom, {
        kj_utf8_to_ucs_scope(to, wto, {
            if(wfrom && wto &&
               !MoveFileExW(wfrom, wto, MOVEFILE_REPLACE_EXISTING)) {
                res = kj_err_from_sys(GetLastError());
            }
        });
    });
    return res;
}

isize$ kj_path_current_dir(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    DWORD wsize = GetCurrentDirectoryW(0, NULL);
    WCHAR* wpath = kj_cast(WCHAR*, _malloca((wsize + 1) * kj_isize_of(WCHAR)));
    GetCurrentDirectoryW(wsize, wpath);
    res.value = kj_ucs_to_utf8(wpath, path, kj_cast(i32, size));
    if(res.value < size) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    _freea(wpath);
    return res;
}

kjErr kj_path_set_current_dir(const char* path) {
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    if(path) {
        kj_utf8_to_ucs_scope(path, wpath, {
            if(wpath && !SetCurrentDirectoryW(wpath)) {
                res = kj_err_from_sys(GetLastError());
            }
        });
    } else {
        res = KJ_ERR_INVALID_PARAMETER;
    }
    return res;
}

isize$ kj_path_tmp_dir(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    DWORD wsize = GetTempPathW(0, NULL);
    WCHAR* wpath = kj_cast(WCHAR*, _malloca((wsize + 1) * kj_isize_of(WCHAR)));
    GetTempPathW(wsize, wpath);
    res.value = kj_ucs_to_utf8(wpath, path, kj_cast(i32, size));
    if(res.value < size) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    _freea(wpath);
    return res;
}

isize$ kj_path_self(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    WCHAR* wpath = kj_cast(WCHAR*, _malloca(KJ_PATH_MAX * kj_isize_of(WCHAR)));
    res.value = GetModuleFileNameW(NULL, wpath, KJ_PATH_MAX);
    res.value = kj_ucs_to_utf8(wpath, path, kj_cast(i32, size));
    if(res.value < size) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    _freea(wpath);
    return res;
}

b32 kj_path_exists(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    kj_utf8_to_ucs_scope(path, wpath, {
        if(wpath) {
            HANDLE h = INVALID_HANDLE_VALUE;
            WIN32_FIND_DATAW find;
            if((h = FindFirstFileW(wpath, &find)) != INVALID_HANDLE_VALUE) {
                FindClose(h);
                res = KJ_TRUE;
            }
        }
    });
    return res;
}

b32 kj_path_is_file(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    kj_utf8_to_ucs_scope(path, wpath, {
        if(wpath) {
            DWORD attr = INVALID_FILE_ATTRIBUTES;
            if((attr = GetFileAttributesW(wpath)) != INVALID_FILE_ATTRIBUTES) {
                if(!(attr & FILE_ATTRIBUTE_DIRECTORY)) {
                    res = KJ_TRUE;
                }
            }
        }
    });
    return res;
}

b32 kj_path_is_dir(const char* path) {
    kj_assert(path);

    b32 res = KJ_FALSE;
    kj_utf8_to_ucs_scope(path, wpath, {
        if(wpath) {
            DWORD attr = INVALID_FILE_ATTRIBUTES;
            if((attr = GetFileAttributesW(wpath)) != INVALID_FILE_ATTRIBUTES) {
                if(attr & FILE_ATTRIBUTE_DIRECTORY) {
                    res = KJ_TRUE;
                }
            }
        }
    });
    return res;
}
#elif defined(KJ_SYS_LINUX)
KJ_GLOBAL KJ_TLS char KJ_PATH_BUF[KJ_PATH_MAX] = {0};

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

    isize$ res;
    res.err = KJ_ERR_NONE;
    kj_syscall2(KJ_SYSCALL_GETCWD, res.value, KJ_PATH_BUF, KJ_PATH_MAX - 1);
    if(res.value < 0) {
        res.err = kj_err_from_sys(-res.value);
    } elif(res.value > size) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    } else {
        kj_copy(path, KJ_PATH_BUF, res.value);
        path[res.value] = '\0';
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

    isize$ res;
    res.err = KJ_ERR_NONE;
    const char* tmp = NULL;
    if((tmp = getenv("TMPDIR")) == NULL) {
        tmp = "/tmp";
    }
    isize tmp_size = kj_cstr_count(tmp);
    if(tmp_size < size) {
        kj_copy(path, tmp, tmp_size);
        path[tmp_size] = '\0';
        res.value = tmp_size;
    } else {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    }
    return res;
}

isize$ kj_path_self(char* path, isize size) {
    kj_assert(path);
    kj_assert(size > 0);

    isize$ res;
    res.err = KJ_ERR_NONE;
    kj_syscall3(
            KJ_SYSCALL_READLINK, res.value,
            "/proc/self/exe", KJ_PATH_BUF, KJ_PATH_MAX - 1);
    if(res.value < 0) {
        res.err = kj_err_from_sys(-res.value);
    } elif(res.value > size) {
        res.err = KJ_ERR_INSUFFICIENT_BUFFER;
    } else {
        kj_copy(path, KJ_PATH_BUF, res.value);
        path[res.value] = '\0';
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
kjErr kj_file_group_begin(kjFileGroup* g, const char* path) {
    kj_assert(g);
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    kj_zero(g, kj_isize_of(kjFileGroup));

    WIN32_FIND_DATAW find;
    HANDLE handle = INVALID_HANDLE_VALUE;
    kj_utf8_to_ucs_scope(path, wpath, {
        if(wpath) {
            if((handle = FindFirstFileW(wpath, &find)) == INVALID_HANDLE_VALUE) {
                res = kj_err_from_sys(GetLastError());
            } else {
                do {
                    g->count++;
                    if(!FindNextFileW(handle, &find)) {
                        break;
                    }
                } while(handle != INVALID_HANDLE_VALUE);
                if(handle) {
                    FindClose(handle);
                }
                g->handle = FindFirstFileW(wpath, &g->find);
            }
        }
    });
    return res;
}

isize kj_file_group_next(kjFileGroup* g, char* path, isize size) {
    kj_assert(g);
    kj_assert(path);
    kj_assert(size > 0);

    isize res = -1;
    if(g->handle != INVALID_HANDLE_VALUE) {
        if(kj_ucs_to_utf8(
                    &g->find.cFileName[0], path, kj_cast(i32, size)) > 0) {
            res = kj_cstr_count_n(path, KJ_PATH_MAX);
        }
    }
    if(!FindNextFileW(g->handle, &g->find)) {
        g->handle = INVALID_HANDLE_VALUE;
    }
    return res;
}

void kj_file_group_end(kjFileGroup* g) {
    kj_assert(g);

    if(g->handle) {
        FindClose(g->handle);
    }
}
#elif defined(KJ_SYS_LINUX)
kjErr kj_file_group_begin(kjFileGroup* g, const char* path) {
    kj_assert(g);
    kj_assert(path);

    kjErr res = KJ_ERR_NONE;
    kj_zero(g, kj_isize_of(kjFileGroup));

    if((g->dir = opendir(path)) == NULL) {
        res = kj_err_from_sys(errno);
        g->err = res;
    }
    return res;
}

isize kj_file_group_next(kjFileGroup* g, char* path, isize size) {
    kj_assert(g);
    kj_assert(path);
    kj_assert(size > 0);

    isize res = -1;
    if(g->dir && (g->entry = readdir(g->dir)) == NULL) {
        g->err = kj_err_from_sys(errno);
    } else {
        res = kj_cstr_count_n(g->entry->d_name, 255);
        kj_copy(path, &g->entry->d_name[0], kj_min(size, res));
        path[res - 1] = '\0';
        g->err = KJ_ERR_NONE;
    }
    return res;
}

void kj_file_group_end(kjFileGroup* g) {
    kj_assert(g);

    if(g->dir) {
        closedir(g->dir);
    }
}
#endif

kjBuffer kj_buffer(kjHeapAllocator* allocator, isize granularity) {
    kj_assert(allocator);

    kjBuffer res;
    kj_zero(&res, kj_isize_of(kjBuffer));
    res.granularity = granularity;
    res.allocator = allocator;
    return res;
}

void kj_buffer_destroy(kjBuffer* buffer) {
    kj_assert(buffer);

    if(!buffer->data) {
        kj_allocator_free(buffer->allocator, buffer->data);
        buffer->data = NULL;
    }
}

kjErr kj_buffer_write(kjBuffer* buffer, const void* buf, isize size) {
    kj_assert(buffer);
    kj_assert(buf);
    kj_assert(size > 0);

    kjErr res = KJ_ERR_NONE;
    if(buffer->used + size > buffer->size) {
        isize new_size = kj_round_up(buffer->size + size, buffer->granularity);
        void* new_data = NULL;
        if(buffer->data) {
             new_data = kj_allocator_realloc(
                    buffer->allocator, buffer->data, new_size);
        } else {
             new_data = kj_allocator_alloc(buffer->allocator, new_size);
        }
        if(new_data) {
            buffer->data = kj_cast(u8*, new_data);
            buffer->size = size;
        } else {
            res = KJ_ERR_ALLOC_FAILED;
        }
    }
    if(res == KJ_ERR_NONE) {
        kj_copy(buffer->data + buffer->used, buf, size);
        buffer->used += size;
    }

#if defined(KJ_DEBUG)
    if(buffer->used < buffer->size) {
        buffer->data[buffer->used] = '\0';
    }
#endif

    return res;
}

void kj_buffer_clear(kjBuffer* buffer) {
    kj_assert(buffer);

    kj_zero(buffer->data, buffer->size);
}

#endif
