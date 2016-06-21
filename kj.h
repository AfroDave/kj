// `kj.h`
// public domain - no warranty implied; use at your own risk
//
// usage:
//      #define KJ_IMPL
//      #include "kj.h"

#ifndef KJ_H
#define KJ_H

#define KJ_VERSION_MAJOR 0
#define KJ_VERSION_MINOR 6
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
#elif defined(__linux__)
#define KJ_SYS_LINUX
#define _GNU_SOURCE
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

#define KJ_LE 1234
#define KJ_BE 4321

#if defined(KJ_SYS_LINUX)
#include <endian.h>
#define KJ_ENDIAN __BYTE_ORDER
#else
#define KJ_ENDIAN KJ_LE
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
#define KJ_BIT_ZERO (0x00 << 0x00)
#define KJ_BIT_FLAG(a) (0x01 << (a))
#define kj_bit_set(a, n) (((a) >> (n)) & 0x01)
#define kj_bit_get(a, n) ((a) |  (0x01 << (n)))
#define kj_bit_clear(a, n) ((a) & ~(0x01 << (n)))
#endif

#if !defined(__cplusplus)
#if !defined(true)
#define true 1
#endif
#if !defined(false)
#define false 0
#endif
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

typedef u8 b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;

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
    X(KJ_ERR_INVALID_INPUT, 8, "Invalid Input")                                 \
    X(KJ_ERR_INTERRUPED, 9, "Interrupted")                                      \
    X(KJ_ERR_ILLEGAL_SEEK, 10, "Illegal Seek")                                  \
    X(KJ_ERR_MALLOC_FAIL, 11, "Malloc Fail")                                    \
    X(KJ_ERR_ADDR_IN_USE, 12, "Address In Use")                                 \
    X(KJ_ERR_ADDR_NOT_AVAILABLE, 13, "Address Not Available")                   \
    X(KJ_ERR_CONNECTION_ABORTED, 14, "Connection Aborted")                      \
    X(KJ_ERR_CONNECTION_REFUSED, 15, "Connection Refused")                      \
    X(KJ_ERR_CONNECTION_RESET, 16, "Connection Reset")                          \
    X(KJ_ERR_NOT_CONNECTED, 17, "Not Connected")                                \
    X(KJ_ERR_WOULD_BLOCK, 18, "Would Block")

typedef enum kjErr {
#define KJ_ERR_ENUM(type, value, name) type = value,
    KJ_ERR_MAP(KJ_ERR_ENUM)
#undef KJ_ERR_ENUM
    KJ_ERR_COUNT
} kjErr;

KJ_API const char* kj_err_to_str(kjErr err);

/// Memory

KJ_API void* kj_global_alloc(isize size);
KJ_API void kj_global_free(void* data);
KJ_API void* kj_global_realloc(void* data, isize size);

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

KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_dummy_alloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_dummy_free);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_dummy_realloc);
KJ_API KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_dummy_alloc_aligned);

struct kjAllocator {
    kjAllocatorAllocFn* alloc;
    kjAllocatorFreeFn* free;
    kjAllocatorReallocFn* realloc;
    kjAllocatorAllocAlignedFn* alloc_aligned;
};

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

KJ_API kjHeapAllocator kj_heap_allocator(void);
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

KJ_API kjLinearAllocator kj_linear_allocator(void* data, isize size);
KJ_API void kj_linear_allocator_clear(kjLinearAllocator* allocator);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_linear_alloc);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_linear_realloc);

/// Debug

#define KJ_ASSERT_HANDLER(name) void name(                                      \
        const char* expr, const char* file, u64 line, const char* msg)

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
#define kj_assert_msg(expr, msg, ...) do {                                      \
    if(!(expr)) {                                                               \
        KJ_CUSTOM_ASSERT_HANDLER(kj_string_of(expr), __FILE__, __LINE__, msg);  \
        kj_break();                                                             \
    }                                                                           \
} while(0)
#define kj_assert(expr) kj_assert_msg(expr, NULL)
#define kj_panic(msg) kj_assert_msg(!"panic", msg)
#else
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

KJ_API i32 kj_vprintf(char const* fmt, va_list v);
KJ_API i32 kj_printf(char const* fmt, ...) KJ_FMT_VARGS(1);
KJ_API i32 kj_vsnprintf(char* buf, isize size, char const* fmt, va_list v);
KJ_API i32 kj_snprintf(
        char* buf, isize size, char const* fmt, ...) KJ_FMT_VARGS(3);

/// Strings/Characters

typedef u8 utf8;
typedef u16 utf16;
typedef i32 utf32;

enum {
    KJ_MAX_ASCII = 0x7F,
    KJ_MAX_LATIN1 = 0xFF,
    KJ_MAX_UNICODE = 0x10FFFF
};

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

KJ_API isize kj_cstr_count_n(const char* s, isize n);
KJ_API isize kj_cstr_count(const char* s);
KJ_API isize kj_cstr_cmp_n(const char* s1, const char* s2, isize n);
KJ_API isize kj_cstr_cmp(const char* s1, const char* s2);
KJ_API isize kj_cstr_case_cmp_n(const char* s1, const char* s2, isize n);
KJ_API isize kj_cstr_case_cmp(const char* s1, const char* s2);
KJ_API isize kj_cstr_to_u64(const char* s, u64* v);
KJ_API isize kj_cstr_to_i64(const char* s, i64* v);

KJ_API isize kj_utf8_count_n(const char* s, isize n);
KJ_API isize kj_utf8_count(const char* s);

#if defined(KJ_SYS_WIN32)
KJ_API isize kj_utf8_to_ucs(const char* s, WCHAR* ws, isize size);
KJ_API isize kj_ucs_to_utf8(const WCHAR* ws, char* s, isize size);
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

#if !defined(KJ_PATH_SEPARATOR)
#if defined(KJ_SYS_WIN32)
#define KJ_PATH_SEPARATOR '\\'
#else
#define KJ_PATH_SEPARATOR '/'
#endif
#endif

#if !defined(KJ_EOL)
#if defined(KJ_SYS_WIN32)
#define KJ_EOL "\r\n"
#else
#define KJ_EOL "\n"
#endif
#endif

enum {
    KJ_IO_FLAG_INVALID = KJ_BIT_ZERO,
    KJ_IO_FLAG_READ = KJ_BIT_FLAG(0),
    KJ_IO_FLAG_WRITE = KJ_BIT_FLAG(1),
    KJ_IO_FLAG_RDWR = KJ_IO_FLAG_READ | KJ_IO_FLAG_WRITE,
    KJ_IO_FLAG_CREATE = KJ_BIT_FLAG(2),
    KJ_IO_FLAG_CREATE_NEW = KJ_BIT_FLAG(3),
    KJ_IO_FLAG_APPEND = KJ_BIT_FLAG(4),
    KJ_IO_FLAG_TRUNCATE = KJ_BIT_FLAG(5)
};

typedef enum kjIoSeek {
    KJ_SEEK_BEGIN = 0,
    KJ_SEEK_CURRENT = 1,
    KJ_SEEK_END = 2
} kjIoSeek;

typedef struct kjIo {
#if defined(KJ_SYS_WIN32)
    HANDLE handle;
#elif defined(KJ_SYS_LINUX)
    i32 handle;
#endif
    u32 flags;
    kjErr err;
} kjIo;

typedef struct kjIoStat {
    i64 size;
    kjDateTime last_access;
    kjDateTime last_write;
} kjIoStat;

#define kj_io_has_err(io) ((io)->err != KJ_ERR_NONE)

KJ_API kjErr kj_io_open(kjIo* io, const char* path, u32 flags);
KJ_API kjErr kj_io_close(kjIo* io);
KJ_API kjErr kj_io_seek(kjIo* io, i64 offset, kjIoSeek seek);
KJ_API isize kj_io_read(kjIo* io, void* buf, isize size);
KJ_API isize kj_io_write(kjIo* io, void* buf, isize size);
KJ_API isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset);
KJ_API isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset);
KJ_API void* kj_io_slurp(const char* path, b32 teminate, isize* size);

KJ_API kjIoStat kj_io_stat(kjIo* io);
KJ_API i64 kj_io_size(kjIo* io);

/// Paths

KJ_API const char* kj_path_extension_n(const char* path, isize size);
KJ_API const char* kj_path_extension(const char* path);

#if defined(KJ_SYS_WIN32)
typedef struct kjFileGroup {
    kjErr err;
    isize count;
    struct {
        WIN32_FIND_DATAA find;
        HANDLE handle;
    } platform;
} kjFileGroup;

KJ_API kjFileGroup kj_file_group_begin(const char* path);
KJ_API isize kj_file_group_next(kjFileGroup* g, char* path, isize size);
KJ_API void kj_file_group_end(kjFileGroup* g);
#endif

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
KJ_API kjErr kj_buffer_write(kjBuffer* buffer, void* data, isize size);
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

KJ_INLINE const char* kj_err_to_str(kjErr err) {
    static const char* KJ_ERR_STR[] = {
#define KJ_ERR_NAME(type, value, name) name,
    KJ_ERR_MAP(KJ_ERR_NAME)
#undef KJ_ERR_NAME
    };
    return err <= KJ_ERR_UNKNOWN || err >= KJ_ERR_COUNT ?
        KJ_ERR_STR[KJ_ERR_UNKNOWN]: KJ_ERR_STR[err];
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_FN(kj_dummy_alloc) {
    kj_unused(allocator);
    kj_unused(size);
    return NULL;
}

KJ_INLINE KJ_ALLOCATOR_FREE_FN(kj_dummy_free) {
    kj_unused(allocator);
    kj_unused(data);
}

KJ_INLINE KJ_ALLOCATOR_REALLOC_FN(kj_dummy_realloc) {
    kj_unused(allocator);
    kj_unused(data);
    kj_unused(size);
    return NULL;
}

KJ_INLINE KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_dummy_alloc_aligned) {
    kj_unused(allocator);
    kj_unused(size);
    kj_unused(alignment);
    return NULL;
}

#if defined(KJ_SYS_WIN32)
void* kj_global_alloc(isize size) {
    void* res = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    return res;
}

void kj_global_free(void* data) {
    if(data) {
        HeapFree(GetProcessHeap(), 0, data);
    }
}

void* kj_global_realloc(void* data, isize size) {
    void* res = NULL;
    res = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, data, size);
    return res;
}

void* kj_global_alloc_aligned(isize size, isize alignment) {
    void* res = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size + alignment);
    res = kj_align_on(kj_cast(u8*, res), alignment);
    return res;
}
#elif defined(KJ_SYS_LINUX)
#include <stdlib.h>

void* kj_global_alloc(isize size) {
    void* res = NULL;
    res = calloc(size, kj_isize_of(u8));
    return res;
}

void kj_global_free(void* data) {
    if(data) {
        free(data);
    }
}

void* kj_global_realloc(void* data, isize size) {
    void* res = NULL;
    res = realloc(data, size * kj_isize_of(u8));
    return res;
}

void* kj_global_alloc_aligned(isize size, isize alignment) {
    void* res = calloc(size + alignment, kj_isize_of(u8));
    res = kj_align_on(kj_cast(u8*, res), alignment);
    return res;
}
#endif

KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc) {
    kj_unused(allocator);
    return kj_global_alloc(size);
}

KJ_ALLOCATOR_FREE_FN(kj_heap_free) {
    kj_unused(allocator);
    kj_global_free(data);
}

KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc) {
    kj_unused(allocator);
    return kj_global_realloc(data, size);
}

KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_heap_alloc_aligned) {
    kj_unused(allocator);
    return kj_global_alloc_aligned(size, alignment);
}

kjHeapAllocator kj_heap_allocator(void) {
    kjHeapAllocator res;
    res.alloc = kj_heap_alloc;
    res.free = kj_heap_free;
    res.realloc = kj_heap_realloc;
    res.alloc_aligned = kj_heap_alloc_aligned;
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

kjLinearAllocator kj_linear_allocator(void* data, isize size) {
    kjLinearAllocator res;
    res.allocator.alloc = kj_linear_alloc;
    res.allocator.free = kj_linear_free;
    res.allocator.realloc = kj_linear_realloc;
    res.allocator.alloc_aligned = kj_linear_alloc_aligned;
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

#if !defined(KJ_CUSTOM_ASSERT_HANDLER)
#if defined(KJ_SYS_WIN32)
KJ_ASSERT_HANDLER(kj_assert_handler) {
    static char buf[4096] = {0};
    kj_snprintf(
            buf, kj_isize_of(buf) - 1,
            "%s:%lu - %s %s", file, line, expr, msg ? msg: "");
    buf[kj_isize_of(buf) - 1] = '\0';
    MessageBoxA(NULL, buf, "Assertion", MB_OK);
}
#elif defined(KJ_SYS_LINUX)
KJ_ASSERT_HANDLER(kj_assert_handler) {
    if(msg) {
        kj_printf("%s:%lu - %s %s", file, line, expr, msg);
    } else {
        kj_printf("%s:%lu - %s", file, line, expr);
    }
}
#endif
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

#include <stdio.h>

i32 kj_vprintf(char const* fmt, va_list v) {
    return vprintf(fmt, v);
}

i32 kj_printf(char const* fmt, ...) {
    i32 res;
    va_list v;
    va_start(v, fmt);
    res = kj_vprintf(fmt, v);
    va_end(v);
    return res;
}

i32 kj_vsnprintf(char* buf, isize size, char const* fmt, va_list v) {
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

i32 kj_snprintf(char* buf, isize size, char const* fmt, ...) {
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
    return false;
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
    return false;
}

KJ_INLINE b32 kj_char_is_alpha(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <='Z');
    }
    return false;
}

KJ_INLINE b32 kj_char_is_digit(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= '0' && c <= '9');
    }
    return false;
}

KJ_INLINE b32 kj_char_is_alphanum(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9');
    }
    return false;
}

KJ_INLINE b32 kj_char_is_hex_digit(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'f') ||
               (c >= 'A' && c <= 'F') ||
               (c >= '0' && c <= '9');
    }
    return false;
}

KJ_INLINE b32 kj_char_is_lower(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'a' && c <= 'z');
    }
    return false;
}

KJ_INLINE b32 kj_char_is_upper(utf32 c) {
    if(c <= KJ_MAX_LATIN1) {
        return (c >= 'A' && c <= 'Z');
    }
    return false;
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
isize kj_utf8_to_ucs(const char* s, WCHAR* ws, isize size) {
    isize res = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
    if(res < size) {
        MultiByteToWideChar(CP_UTF8, 0, s, -1, ws, kj_cast(i32, size));
        ws[res] = '\0';
        res = 0;
    }
    return res;
}

isize kj_ucs_to_utf8(const WCHAR* ws, char* s, isize size) {
    isize res = WideCharToMultiByte(CP_UTF8, 0, ws, -1, NULL, 0, NULL, NULL);
    if(res < size) {
        WideCharToMultiByte(
                CP_UTF8, 0, ws, -1, s, kj_cast(i32, size), NULL, NULL);
        s[res] = '\0';
        res = 0;
    }
    return res;
}
#endif

#if defined(KJ_LIB_IMPL)
#if defined(KJ_SYS_WIN32)
KJ_INLINE kjLib kj_lib_open(const char* path) {
    kjLib res = NULL;
    static WCHAR wpath[MAX_PATH] = {0};
    if(kj_utf8_to_ucs(path, &wpath[0], kj_count_of(wpath)) == 0) {
        res = kj_cast(kjLib, LoadLibraryW(wpath));
    }
    return res;
}

KJ_INLINE kjLibFn kj_lib_fn(kjLib lib, const char* name) {
    return kj_cast(kjLibFn, GetProcAddress(kj_cast(HMODULE, lib), name));
}

KJ_INLINE void kj_lib_close(kjLib lib) {
    FreeLibrary(kj_cast(HMODULE, lib));
}
#elif defined(KJ_SYS_LINUX)
#include <dlfcn.h>

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

#define KJ_CMP_FN_T(T) KJ_INLINE KJ_CMP_FN(kj_join(kj_cmp_, T)) {               \
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

#define KJ_SWAP_FN_T(T) KJ_INLINE KJ_SWAP_FN(kj_join(kj_swap_, T)) {            \
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
    return (kj_cast(u64, counter.QuadPart) * 1000) / kj_cast(u64, freq.QuadPart);
}
#elif defined(KJ_SYS_LINUX)
#include <time.h>

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

#define KJ_IO_INVALID_MODE U32_MAX

#if defined(KJ_SYS_WIN32)
KJ_INTERN kjErr kj_io_err_from_sys(void) {
    i32 err = GetLastError();
    switch(err) {
        case ERROR_SUCCESS: return KJ_ERR_NONE;
        case ERROR_ACCESS_DENIED: return KJ_ERR_PERMISSION_DENIED;
        case ERROR_ALREADY_EXISTS: return KJ_ERR_ALREADY_EXISTS;
        case ERROR_BROKEN_PIPE: return KJ_ERR_BROKEN_PIPE;
        case ERROR_FILE_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_PATH_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_NO_DATA: return KJ_ERR_BROKEN_PIPE;
        case ERROR_INVALID_PARAMETER: return KJ_ERR_INVALID_INPUT;
        case ERROR_OPERATION_ABORTED: return KJ_ERR_TIMED_OUT;
        case ERROR_SEEK: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_NEGATIVE_SEEK: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_SEEK_ON_DEVICE: return KJ_ERR_ILLEGAL_SEEK;
        default: return KJ_ERR_UNKNOWN;
    }
}

KJ_INTERN u32 kj_io_gen_access_mode(u32 flags) {
    u32 res = 0;
    if((flags & KJ_IO_FLAG_READ) &&
      !(flags & KJ_IO_FLAG_WRITE) &&
      !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ;
    } elif(!(flags & KJ_IO_FLAG_READ) &&
            (flags & KJ_IO_FLAG_WRITE) &&
           !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_WRITE;
    } elif((flags & KJ_IO_FLAG_READ) &&
           (flags & KJ_IO_FLAG_WRITE) &&
          !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ | GENERIC_WRITE;
    } elif(!(flags & KJ_IO_FLAG_READ) &&
            (flags & KJ_IO_FLAG_APPEND)) {
        res = FILE_GENERIC_WRITE & ~FILE_WRITE_DATA;
    } elif((flags & KJ_IO_FLAG_READ) &&
           (flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ | (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA);
    }
    return res;
}

KJ_INTERN u32 kj_io_gen_create_mode(u32 flags) {
    u32 res = 0;
    if(!(flags & KJ_IO_FLAG_WRITE) &&
       !(flags & KJ_IO_FLAG_APPEND)) {
        if((flags & KJ_IO_FLAG_TRUNCATE) ||
           (flags & KJ_IO_FLAG_CREATE) ||
           (flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = KJ_IO_INVALID_MODE;
        }
    } elif(flags & KJ_IO_FLAG_APPEND) {
        if((flags & KJ_IO_FLAG_TRUNCATE) &&
          !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = KJ_IO_INVALID_MODE;
        }
    }
    if(res == 0) {
        if(!(flags & KJ_IO_FLAG_CREATE) &&
           !(flags & KJ_IO_FLAG_TRUNCATE) &&
           !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = OPEN_EXISTING;
        } elif((flags & KJ_IO_FLAG_CREATE) &&
              !(flags & KJ_IO_FLAG_TRUNCATE) &&
              !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = OPEN_ALWAYS;
        } elif(!(flags & KJ_IO_FLAG_CREATE) &&
                (flags & KJ_IO_FLAG_TRUNCATE) &&
               !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = TRUNCATE_EXISTING;
        } elif((flags & KJ_IO_FLAG_CREATE) &&
               (flags & KJ_IO_FLAG_TRUNCATE) &&
              !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = CREATE_ALWAYS;
        } elif(flags & KJ_IO_FLAG_CREATE_NEW) {
            res = CREATE_NEW;
        }
    }
    return res;
}

kjErr kj_io_open(kjIo* io, const char* path, u32 flags) {
    kj_assert(io);

    kjErr res = KJ_ERR_NONE;
    u32 access = kj_io_gen_access_mode(flags);
    u32 create = kj_io_gen_create_mode(flags);
    if((access | create) == KJ_IO_INVALID_MODE) {
        io->handle = NULL;
        io->flags = 0;
        io->err = KJ_ERR_INVALID_INPUT;
    } else {
        static WCHAR wpath[MAX_PATH] = {0};
        if(kj_utf8_to_ucs(path, &wpath[0], kj_count_of(wpath)) == 0) {
            io->handle = CreateFileW(
                    wpath, access,
                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    NULL, create, 0, NULL);
            io->flags = flags;
            io->err = io->handle == INVALID_HANDLE_VALUE ? KJ_ERR_BAD_HANDLE:
                kj_io_err_from_sys();
        }
    }
    res = io->err;
    return res;
}

kjErr kj_io_close(kjIo* io) {
    kj_assert(io);

    kjErr res = KJ_ERR_NONE;
    if(!CloseHandle(io->handle)) {
        res = kj_io_err_from_sys();
    }
    io->handle = NULL;
    return res;
}

kjErr kj_io_seek(kjIo* io, i64 offset, kjIoSeek seek) {
    kj_assert(io);

    kjErr res = KJ_ERR_NONE;
    LARGE_INTEGER new_offset;
    new_offset.QuadPart = offset;
    if(SetFilePointerEx(io->handle, new_offset, &new_offset, seek) == 0) {
        res = kj_io_err_from_sys();
        io->err = res;
    }
    return res;
}

isize kj_io_read(kjIo* io, void* buf, isize size) {
    kj_assert(io);

    isize res = -1;
    DWORD read = 0;
    if(ReadFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), NULL)) {
        res = read;
    } else {
        io->err = kj_io_err_from_sys();
    }
    return res;
}

isize kj_io_write(kjIo* io, void* buf, isize size) {
    kj_assert(io);

    isize res = -1;
    DWORD wrote = 0;
    if(WriteFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), NULL)) {
        res = wrote;
    } else {
        io->err = kj_io_err_from_sys();
    }
    return res;
}

isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset) {
    kj_assert(io);

    isize res = -1;
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), &overlapped)) {
        res = read;
    } else {
        io->err = kj_io_err_from_sys();
    }
    return res;
}

isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset) {
    kj_assert(io);

    isize res = -1;
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), &overlapped)) {
        res = wrote;
    } else {
        io->err = kj_io_err_from_sys();
    }
    return res;
}

kjIoStat kj_io_stat(kjIo* io) {
    kj_assert(io);

    kjIoStat res = {0};
    BY_HANDLE_FILE_INFORMATION io_info = {0};
    if(GetFileInformationByHandle(io->handle, &io_info)) {
        res.size = (kj_cast(i64, io_info.nFileSizeHigh) << 32) |
                    kj_cast(i64, io_info.nFileSizeLow);
        SYSTEMTIME last_access = {0};
        SYSTEMTIME last_write = {0};
        FileTimeToSystemTime(&io_info.ftLastAccessTime, &last_access);
        FileTimeToSystemTime(&io_info.ftLastWriteTime, &last_write);
        kj_systime_to_datetime(&last_access, &res.last_access);
        kj_systime_to_datetime(&last_write, &res.last_write);
    } else {
        io->err = kj_io_err_from_sys();
    }
    return res;
}
#elif defined(KJ_SYS_LINUX)
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

KJ_INTERN kjErr kj_io_err_from_sys(i32 err) {
    switch(err) {
        case 0: return KJ_ERR_NONE;
        case EBADF: return KJ_ERR_BAD_HANDLE;
        case EPERM: return KJ_ERR_PERMISSION_DENIED;
        case EACCES: return KJ_ERR_PERMISSION_DENIED;
        case EEXIST: return KJ_ERR_ALREADY_EXISTS;
        case EPIPE: return KJ_ERR_BROKEN_PIPE;
        case ENOENT: return KJ_ERR_NOT_FOUND;
        case ETIMEDOUT: return KJ_ERR_TIMED_OUT;
        case EINVAL: return KJ_ERR_INVALID_INPUT;
        case EINTR: return KJ_ERR_INTERRUPED;
        case ESPIPE: return KJ_ERR_ILLEGAL_SEEK;
        default: return KJ_ERR_UNKNOWN;
    }
}

KJ_INTERN u32 kj_io_gen_access_mode(u32 flags) {
    u32 res = 0;
    if((flags & KJ_IO_FLAG_READ) &&
      !(flags & KJ_IO_FLAG_WRITE) &&
      !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDONLY;
    } elif(!(flags & KJ_IO_FLAG_READ) &&
            (flags & KJ_IO_FLAG_WRITE) &&
           !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_WRONLY;
    } elif((flags & KJ_IO_FLAG_READ) &&
           (flags & KJ_IO_FLAG_WRITE) &&
          !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDWR;
    } elif(!(flags & KJ_IO_FLAG_READ) &&
            (flags & KJ_IO_FLAG_APPEND)) {
        res = O_WRONLY | O_APPEND;
    } elif((flags & KJ_IO_FLAG_READ) &&
           (flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDWR | O_APPEND;
    }
    return res;
}

KJ_INTERN u32 kj_io_gen_create_mode(u32 flags) {
    u32 res = 0;
    if(!(flags & KJ_IO_FLAG_WRITE) &&
       !(flags & KJ_IO_FLAG_APPEND)) {
        if((flags & KJ_IO_FLAG_TRUNCATE) ||
           (flags & KJ_IO_FLAG_CREATE) ||
           (flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = KJ_IO_INVALID_MODE;
        }
    } elif(flags & KJ_IO_FLAG_APPEND) {
        if((flags & KJ_IO_FLAG_TRUNCATE) &&
          !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = KJ_IO_INVALID_MODE;
        }
    }
    if(res == 0) {
        if((flags & KJ_IO_FLAG_CREATE) &&
          !(flags & KJ_IO_FLAG_TRUNCATE) &&
          !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = O_CREAT;
        } elif(!(flags & KJ_IO_FLAG_CREATE) &&
                (flags & KJ_IO_FLAG_TRUNCATE) &&
               !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = O_TRUNC;
        } elif((flags & KJ_IO_FLAG_CREATE) &&
               (flags & KJ_IO_FLAG_TRUNCATE) &&
              !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = O_CREAT | O_TRUNC;
        } elif(flags & KJ_IO_FLAG_CREATE_NEW) {
            res = O_CREAT | O_EXCL;
        }
    }
    return res;
}

kjErr kj_io_open(kjIo* io, const char* path, u32 flags) {
    kj_assert(io);

    kjErr res = KJ_ERR_NONE;
    u32 access = kj_io_gen_access_mode(flags);
    u32 create = kj_io_gen_create_mode(flags);
    if((access | create) == KJ_IO_INVALID_MODE) {
        io->handle = -1;
        io->flags = 0;
        io->err = KJ_ERR_INVALID_INPUT;
    } else {
        u32 perm = 0666;
        kj_syscall3(KJ_SYSCALL_OPEN, io->handle, path, (access | create), perm);
        io->flags = flags;
        io->err = kj_io_err_from_sys(io->handle < 0 ? -io->handle: 0);
    }
    res = io->err;
    return res;
}

kjErr kj_io_close(kjIo* io) {
    kj_assert(io);

    kjErr res = KJ_ERR_NONE;
    i32 out = 0;
    kj_syscall1(KJ_SYSCALL_CLOSE, out, io->handle);
    if(out < 0) {
        res = kj_io_err_from_sys(out < 0 ? -out: 0);
    }
    io->handle = -1;
    io->flags = 0;
    io->err = res;
    return res;
}

kjErr kj_io_seek(kjIo* io, i64 offset, kjIoSeek seek) {
    kj_assert(io);

    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall3(KJ_SYSCALL_LSEEK, out, io->handle, offset, seek);
    res = kj_io_err_from_sys(out < 0 ? -out: 0);
    io->err = res;
    return res;
}

isize kj_io_read(kjIo* io, void* buf, isize size) {
    kj_assert(io);

    isize res = -1;
    kj_syscall3(KJ_SYSCALL_READ, res, io->handle, buf, size);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_write(kjIo* io, void* buf, isize size) {
    kj_assert(io);

    isize res = -1;
    kj_syscall3(KJ_SYSCALL_WRITE, res, io->handle, buf, size);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset) {
    kj_assert(io);

    isize res = -1;
    kj_syscall4(KJ_SYSCALL_PREAD, res, io->handle, buf, size, offset);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset) {
    kj_assert(io);

    isize res = -1;
    kj_syscall4(KJ_SYSCALL_PWRITE, res, io->handle, buf, size, offset);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

kjIoStat kj_io_stat(kjIo* io) {
    kj_assert(io);

    kjIoStat res;
    kj_zero(&res, kj_isize_of(kjIoStat));
    struct stat buf;
    if(fstat(io->handle, &buf) == -1) {
        io->err = kj_io_err_from_sys(errno);
    } else {
        res.size = buf.st_size;
        struct tm* last_access = gmtime(&buf.st_atime);
        struct tm* last_write = gmtime(&buf.st_mtime);
        kj_systime_to_datetime(last_access, &res.last_access);
        kj_systime_to_datetime(last_write, &res.last_write);
    }
    return res;
}
#endif

#if defined(KJ_SYS_WIN32) || defined(KJ_SYS_LINUX)
void* kj_io_slurp(const char* path, b32 terminate, isize* size) {
    void* res = NULL;
    kjIo io;
    kjErr err = kj_io_open(&io, path, KJ_IO_FLAG_READ);
    if(err == KJ_ERR_NONE) {
        kjIoStat stat = kj_io_stat(&io);
        if(stat.size > 0) {
            res = kj_global_alloc(terminate ? stat.size + 1: stat.size);
            if(kj_io_read(&io, res, stat.size) == stat.size) {
                if(terminate) {
                    u8* s = kj_cast(u8*, res);
                    s[stat.size] = '\0';
                }
                if(size) {
                    *size = stat.size;
                }
            } else {
                kj_global_free(res);
                res = NULL;
            }
        }
        kj_io_close(&io);
    }
    return res;
}

i64 kj_io_size(kjIo* io) {
    kj_assert(io);

    i64 res = 0;
    kjIoStat stat = kj_io_stat(io);
    if(!kj_io_has_err(io)) {
        res = stat.size;
    }
    return res;
}
#endif

const char* kj_path_extension_n(const char* path, isize size) {
    const char* res = NULL;
    if(path) {
        if(size >= 3) {
            for(isize i = size - 1; i >= 0; i--) {
                if(path[i] == KJ_PATH_SEPARATOR) {
                    res = NULL;
                    break;
                } elif(path[i] == '.' &&
                       i > 0 &&
                       path[i - 1] != KJ_PATH_SEPARATOR) {
                        res = &path[i + 1];
                    break;
                }
            }
        }
    }
    return res;
}

const char* kj_path_extension(const char* path) {
    const char* res = NULL;
    if(path) {
        isize size = kj_cstr_count(path);
        res = kj_path_extension_n(path, size);
    }
    return res;
}

#if defined(KJ_SYS_WIN32)
kjFileGroup kj_file_group_begin(const char* path) {
    kjFileGroup res = {0};

    WIN32_FIND_DATAA find;
    HANDLE handle = FindFirstFileA(path, &find);
    do {
        res.count++;
        if(!FindNextFileA(handle, &find)) {
            break;
        }
    } while(handle != INVALID_HANDLE_VALUE);
    FindClose(handle);

    res.platform.handle = FindFirstFileA(path, &res.platform.find);

    return res;
}

isize kj_file_group_next(kjFileGroup* g, char* path, isize size) {
    kj_assert(g);

    isize res = -1;
    if(g->platform.handle != INVALID_HANDLE_VALUE) {
        res = kj_min(size, kj_cstr_count_n(g->platform.find.cFileName, 260));
        kj_copy(path, &g->platform.find.cFileName[0], res);
    }
    if(!FindNextFileA(g->platform.handle, &g->platform.find)) {
        g->platform.handle = INVALID_HANDLE_VALUE;
    }
    return res;
}

void kj_file_group_end(kjFileGroup* g) {
    kj_assert(g);

    if(g->platform.handle) {
        FindClose(g->platform.handle);
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

kjErr kj_buffer_write(kjBuffer* buffer, void* data, isize size) {
    kj_assert(buffer);

    kjErr res = KJ_ERR_NONE;
    if(buffer->used + size > buffer->size) {
        isize new_size = kj_round_up(buffer->size + size, buffer->granularity);
        void* new_data = kj_allocator_realloc(
                buffer->allocator, buffer->data, new_size);
        if(new_data) {
            buffer->data = kj_cast(u8*, new_data);
            buffer->size = size;
        } else {
            res = KJ_ERR_MALLOC_FAIL;
        }
    }
    if(res == KJ_ERR_NONE) {
        kj_copy(buffer->data + buffer->used, data, size);
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
