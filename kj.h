// `kj.h`
// public domain - no warranty implied; use at your own risk
//
// usage:
//      #define KJ_IMPL
//      #include "kj.h"

#ifndef KJ_H
#define KJ_H

#if defined(__cplusplus)
#define KJ_EXTERN_BEGIN extern "C" {
#define KJ_EXTERN_END }
#else
#define KJ_EXTERN_BEGIN
#define KJ_EXTERN_END
#endif

KJ_EXTERN_BEGIN

#define KJ_VERSION_MAJOR 0
#define KJ_VERSION_MINOR 5
#define KJ_VERSION_PATCH 3

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
#include <windows.h>
#elif defined(__linux__)
#define KJ_SYS_LINUX
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif
#else
#error KJ_SYS_UNSUPPORTED
#endif

#if defined(_MSC_VER)
#define KJ_COMPILER_MSVC
#elif defined(__clang__)
#define KJ_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define KJ_COMPILER_GNU
#else
#error KJ_COMPILER_UNSUPPORTED
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define KJ_ARCH_64_BIT
#elif defined(__i386) || defined(_M_IX86)
#define KJ_ARCH_32_BIT
#else
#error KJ_ARCH_UNSUPPORTED
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
#else
#error KJ_EXPORT_UNSUPPORTED
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
#else
#error KJ_ALIGN_UNSUPPORTED
#endif
#endif

#if !defined(kj_align_on)
#define kj_align_on(p, a) (((p) + ((a) - 1)) & ~((a) - 1))
#endif

#if !defined(kj_concat)
#define kj_concat(a, b) a##b
#define kj_join(a, b) kj_concat(a, b)
#endif

#if !defined(kj_unused)
#if defined(KJ_COMPILER_MSVC)
#define kj_unused(a) __pragma(warning(suppress:4100)) (a)
#else
#define kj_unused(a) kj_cast(void, (a))
#endif
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
#endif

#if !defined(kj_kb)
#define kj_kb(a) ((a) * 1024)
#define kj_mb(a) (kj_kb((a)) * 1024)
#define kj_gb(a) (kj_mb((a)) * 1024)
#define kj_tb(a) (kj_gb((a)) * 1024)
#define kj_b_kb(a) ((a) / 1024)
#define kj_b_mb(a) (kj_b_kb((a)) / 1024)
#define kj_b_gb(a) (kj_b_mb((a)) / 1024)
#define kj_b_tb(a) (kj_b_gb((a)) / 1024)
#endif

#if !defined(KJ_BIT_FLAG)
#define KJ_BIT_ZERO (0x00 << 0x00)
#define KJ_BIT_FLAG(a) (0x01 << (a))
#define KJ_BIT_SET(a, n) (((a) >> (n)) & 0x01)
#define KJ_BIT_GET(a, n) ((a) |  (0x01 << (n)))
#define KJ_BIT_CLEAR(a, n) ((a) & ~(0x01 << (n)))
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

#if defined(KJ_COMPILER_MSVC)
typedef signed __int8 i8;
typedef unsigned __int8 u8;
typedef signed __int16 i16;
typedef unsigned __int16 u16;
typedef signed __int32 i32;
typedef unsigned __int32 u32;
typedef signed __int64 i64;
typedef unsigned __int64 u64;
#else
#include <stdint.h>
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
#endif

#if !defined(I8_MIN)
#define I8_MIN kj_cast(i8, -128)
#define I8_MAX kj_cast(i8, 127)

#define I16_MIN kj_cast(i16, -32768)
#define I16_MAX kj_cast(i16, 32767)

#define I32_MIN kj_cast(i32, -2147483648)
#define I32_MAX kj_cast(i32, 2147483647)

#define I64_MIN kj_cast(i64, -9223372036854775808)
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
#else
#error KJ_ARCH_UNSUPPORTED
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
#else
#error KJ_ARCH_UNSUPPORTED
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

typedef enum kjType {
    KJ_TYPE_NONE = 0,
    KJ_TYPE_CHAR = 1,
    KJ_TYPE_I8 = 2,
    KJ_TYPE_U8 = 3,
    KJ_TYPE_I16 = 4,
    KJ_TYPE_U16 = 5,
    KJ_TYPE_I32 = 6,
    KJ_TYPE_U32 = 7,
    KJ_TYPE_I64 = 8,
    KJ_TYPE_U64 = 9,
    KJ_TYPE_ISIZE = 10,
    KJ_TYPE_USIZE = 11,
    KJ_TYPE_F32 = 12,
    KJ_TYPE_F64 = 13,
    KJ_TYPE_B8 = 14,
    KJ_TYPE_B16 = 15,
    KJ_TYPE_B32 = 16,
    KJ_TYPE_B64 = 17,
    KJ_TYPE_UNKNOWN,
    KJ_TYPE_COUNT
} kjType;

KJ_API const char* kj_type_to_str(kjType type);
KJ_API isize kj_type_to_isize(kjType type);

typedef i32 kjErr;
#define KJ_ERR_NONE 0
#define KJ_ERR_UNKNOWN -1
#define KJ_ERR_BAD_HANDLE 1
#define KJ_ERR_PERMISSION_DENIED 2
#define KJ_ERR_NOT_FOUND 3
#define KJ_ERR_BROKEN_PIPE 4
#define KJ_ERR_ALREADY_EXISTS 5
#define KJ_ERR_TIMED_OUT 6
#define KJ_ERR_INVALID_INPUT 7
#define KJ_ERR_INTERRUPED 8
#define KJ_ERR_ILLEGAL_SEEK 9

/// Memory

typedef struct kjAllocator kjAllocator;

#define KJ_ALLOCATOR_ALLOC_FN(name)                                             \
    void* name(kjAllocator* allocator, isize size)
typedef KJ_ALLOCATOR_ALLOC_FN(kjAllocatorAllocFn);
#define KJ_ALLOCATOR_FREE_FN(name)                                              \
    void name(kjAllocator* allocator, void* ptr)
typedef KJ_ALLOCATOR_FREE_FN(kjAllocatorFreeFn);
#define KJ_ALLOCATOR_REALLOC_FN(name)                                           \
    void* name(kjAllocator* allocator, void* ptr, isize size)
typedef KJ_ALLOCATOR_REALLOC_FN(kjAllocatorReallocFn);

struct kjAllocator {
    kjAllocatorAllocFn* alloc;
    kjAllocatorFreeFn* free;
    kjAllocatorReallocFn* realloc;
};

#define kj_allocator_alloc(a, s) kj_cast(kjAllocator*, (a))->alloc((a), (s))
#define kj_allocator_free(a, p) kj_cast(kjAllocator*, (a))->free((a), (p))
#define kj_allocator_realloc(a, p, s)                                           \
    kj_cast(kjAllocator*, (a))->realloc((a), (p), (s))

typedef kjAllocator kjHeapAllocator;

KJ_API kjHeapAllocator kj_heap_allocator(void);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_heap_free);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc);

/// Debug

KJ_API void kj_assert_handler(
        const char* expr, const char* file, u64 line, const char* msg);

#if defined(KJ_DEBUG)
#if defined(KJ_COMPILER_MSVC)
#define kj_break() do {                                                         \
    if(IsDebuggerPresent()) { __debugbreak(); } else { ExitProcess(0); }        \
} while(0)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_break() __builtin_trap()
#else
#error KJ_BREAK_UNSUPPORTED
#endif
#define kj_assert_msg(expr, msg, ...) do {                                      \
    if(!(expr)) {                                                               \
        kj_assert_handler(kj_string_of(expr), __FILE__, __LINE__, msg);         \
        kj_break();                                                             \
    }                                                                           \
} while(0)
#define kj_assert(expr) kj_assert_msg(expr, NULL)
#define kj_panic(msg) kj_assert_msg(0, msg)
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
#elif define(KJ_ARCH_32_BIT)
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
#else
#error KJ_SYSCALL_UNSUPPORTED
#endif
#endif
#endif

/// Printing

#if !defined(KJ_NO_STDIO)
#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_FMT_VARGS(a) __attribute__((format(printf, (a), ((a) + 1))))
#else
#define KJ_FMT_VARGS(a)
#endif

#include <stdarg.h>

KJ_API i32 kj_vprintf(char const* fmt, va_list v);
KJ_API i32 kj_printf(char const* fmt, ...) KJ_FMT_VARGS(1);
KJ_API i32 kj_vsnprintf(char* buf, isize size, char const* fmt, va_list v);
KJ_API i32 kj_snprintf(
        char* buf, isize size, char const* fmt, ...) KJ_FMT_VARGS(3);
#endif

/// Strings/Characters

typedef char utf8;
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

KJ_API isize kj_str_size(const char* s);
KJ_API isize kj_str_cmp_n(const char* s1, const char* s2, isize n);
KJ_API isize kj_str_cmp(const char* s1, const char* s2);
KJ_API isize kj_str_case_cmp_n(const char* s1, const char* s2, isize n);
KJ_API isize kj_str_case_cmp(const char* s1, const char* s2);
KJ_API isize kj_str_to_u64(const char* s, u64* v);
KJ_API isize kj_str_to_i64(const char* s, i64* v);

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

#if defined(KJ_SYS_WIN32)
#include <windows.h>
typedef struct kjIo {
    void* handle;
    u32 flags;
    kjErr err;
} kjIo;
#elif defined(KJ_SYS_LINUX)
typedef struct kjIo {
    i32 handle;
    u32 flags;
    kjErr err;
} kjIo;
#else
#error KJ_IO_UNSUPPORTED
#endif

typedef struct kjIoStat {
    i64 size;
    kjDateTime last_access;
    kjDateTime last_write;
} kjIoStat;

#define kj_io_has_err(io) ((io)->err != KJ_ERR_NONE)

KJ_API kjIo kj_io_open(const char* path, u32 flags);
KJ_API kjErr kj_io_close(kjIo* io);
KJ_API kjErr kj_io_seek(kjIo* io, i64 offset, kjIoSeek seek);
KJ_API isize kj_io_read(kjIo* io, void* buf, isize size);
KJ_API isize kj_io_write(kjIo* io, void* buf, isize size);
KJ_API isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset);
KJ_API isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset);
KJ_API void* kj_io_slurp(const char* path, b32 teminate, isize* size);

KJ_API kjIoStat kj_io_stat(kjIo* io);
KJ_API i64 kj_io_size(kjIo* io);

KJ_API const char* kj_io_err_str(kjIo* io);

/// Paths

KJ_API const char* kj_path_extension_with_size(const char* path, isize size);
KJ_API const char* kj_path_extension(const char* path);

KJ_EXTERN_END

#endif

#if defined(KJ_IMPL) && !defined(KJ_IMPLEMENTED)
#define KJ_IMPLEMENTED

KJ_INLINE const char* kj_type_to_str(kjType type) {
    static const char* KJ_TYPE_STR[] = {
        "none",
        "char",
        "i8",
        "u8",
        "i16",
        "u16",
        "i32",
        "u32",
        "i64",
        "u64",
        "isize",
        "usize",
        "f32",
        "f64",
        "b8",
        "b16",
        "b32",
        "b64",
        "unknown",
    };
    return type < KJ_TYPE_NONE || type > KJ_TYPE_UNKNOWN ?
        KJ_TYPE_STR[KJ_TYPE_UNKNOWN]: KJ_TYPE_STR[type];
}

KJ_INLINE isize kj_type_to_isize(kjType type) {
    static const isize KJ_TYPE_ISIZE[] = {
        0,
        kj_isize_of(char),
        kj_isize_of(i8),
        kj_isize_of(u8),
        kj_isize_of(i16),
        kj_isize_of(u16),
        kj_isize_of(i32),
        kj_isize_of(u32),
        kj_isize_of(i64),
        kj_isize_of(u64),
        kj_isize_of(isize),
        kj_isize_of(usize),
        kj_isize_of(f32),
        kj_isize_of(f64),
        kj_isize_of(b8),
        kj_isize_of(b16),
        kj_isize_of(b32),
        kj_isize_of(b64),
        0,
    };
    return type < KJ_TYPE_NONE || type > KJ_TYPE_UNKNOWN ?
        0: KJ_TYPE_ISIZE[type];
}

#if defined(KJ_SYS_WIN32)
KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc) {
    kj_unused(allocator);
    void* res = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_heap_free) {
    kj_unused(allocator);
    if(ptr) {
        HeapFree(GetProcessHeap(), 0, ptr);
    }
}

KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc) {
    kj_unused(allocator);
    void* res = NULL;
    res = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, size);
    return res;
}
#elif defined(KJ_SYS_LINUX)
KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc) {
    kj_unused(allocator);
    void* res = NULL;
    res = calloc(size, kj_isize_of(u8));
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_heap_free) {
    kj_unused(allocator);
    if(ptr) {
        free(ptr);
    }
}

KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc) {
    kj_unused(allocator);
    void* res = NULL;
    res = realloc(ptr, size * kj_isize_of(u8));
    return res;
}
#else
#error KJ_MEM_UNSUPPORTED
#endif

kjHeapAllocator kj_heap_allocator(void) {
    kjHeapAllocator res;
    res.alloc = kj_heap_alloc;
    res.free = kj_heap_free;
    res.realloc = kj_heap_realloc;
    return res;
}

#if defined(KJ_ASSERT_IMPL) && !defined(KJ_ASSERT_IMPLEMENTED)
#define KJ_ASSERT_IMPLEMENTED
#if defined(KJ_SYS_WIN32)
void kj_assert_handler(
        const char* expr, const char* file, u64 line, const char* msg) {
    static char buf[4096] = {0};
    kj_snprintf(
            buf, kj_isize_of(buf) - 1,
            "%s:%lu - %s %s", file, line, expr, msg ? msg: "");
    buf[kj_isize_of(buf) - 1] = '\0';
    MessageBoxA(NULL, buf, "Assertion", MB_OK);
}
#else
void kj_assert_handler(
        const char* expr, const char* file, u64 line, const char* msg) {
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

#if !defined(KJ_NO_STDIO)
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
#endif

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

isize kj_str_size(const char* s) {
    const char* e = s;
    while(*e) { e++; }
    return (e - s);
}

isize kj_str_cmp_n(const char* s1, const char* s2, isize n) {
    while(*s1 && *s2 && n) {
        if(*s1 != *s2) {
            return kj_cast(uptr, *s1) < kj_cast(uptr, *s2) ? -1: +1;
        }
        s1++;
        s2++;
        n--;
    }
    return 0;
}

isize kj_str_cmp(const char* s1, const char* s2) {
    while(*s1 && *s2) {
        if(*s1 != *s2) {
            return kj_cast(uptr, *s1) < kj_cast(uptr, *s2) ? -1: +1;
        }
        s1++;
        s2++;
    }
    return 0;
}

isize kj_str_case_cmp_n(const char* s1, const char* s2, isize n) {
    while(*s1 && *s2 && n) {
        if(kj_char_to_lower(*s1) != kj_char_to_lower(*s2)) {
            return kj_cast(uptr, *s1) < kj_cast(uptr, *s2) ? -1: +1;
        }
        s1++;
        s2++;
        n--;
    }
    return 0;
}

isize kj_str_case_cmp(const char* s1, const char* s2) {
    while(*s1 && *s2) {
        if(kj_char_to_lower(*s1) != kj_char_to_lower(*s2)) {
            return kj_cast(uptr, *s1) < kj_cast(uptr, *s2) ? -1: +1;
        }
        s1++;
        s2++;
    }
    return 0;
}

isize kj_str_to_u64(const char* s, u64* v) {
    isize res = -1;
    if(s && v) {
        const char* str = s;
        i64 base = 10;
        if(kj_str_case_cmp_n(s, "0x", 2) == 0) {
            base = 16;
            s += 2;
        } elif(kj_str_case_cmp_n(s, "0o", 2) == 0) {
            base = 8;
            s += 2;
        } elif(kj_str_case_cmp_n(s, "0b", 2) == 0) {
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

isize kj_str_to_i64(const char* s, i64* v) {
    isize res = -1;
    i64 sign = *s == '-' ? s++, -1: 1;
    u64 tmp;
    res = kj_str_to_u64(s, &tmp);
    if(res > 0) {
        *v = kj_cast(i64, tmp) * sign;
    }
    return res;
}

#if defined(KJ_LIB_IMPL) && !defined(KJ_LIB_IMPLEMENTED)
#define KJ_LIB_IMPLEMENTED
#if defined(KJ_SYS_WIN32)
KJ_INLINE kjLib kj_lib_open(const char* path) {
    return kj_cast(kjLib, LoadLibrary(path));
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
#else
#error KJ_LIB_UNSUPPORTED
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
    static LARGE_INTEGER freq = {0};
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
#else
#error KJ_DATETIME_UNSUPPORTED
#endif

u32 kj_hash_str_n(const char* s, isize size) {
    u32 res = 0;
    for(isize i = 0; i < size; i++) {
        res += (*s++) * (kj_cast(u32, i % U32_MAX) + 119);
    }
    return res;
}

u32 kj_hash_str(const char* s) {
    return kj_hash_str_n(s, kj_str_size(s));
}

#define KJ_IO_INVALID_MODE U32_MAX

const char* kj_io_err_str(kjIo* io) {
    switch(io->err) {
        case KJ_ERR_NONE: return "None";
        case KJ_ERR_BAD_HANDLE: return "Bad Handle";
        case KJ_ERR_PERMISSION_DENIED: return "Permission Denied";
        case KJ_ERR_NOT_FOUND: return "Not Found";
        case KJ_ERR_BROKEN_PIPE: return "Broken Pipe";
        case KJ_ERR_ALREADY_EXISTS: return "Already Exists";
        case KJ_ERR_TIMED_OUT: return "Timed Out";
        case KJ_ERR_INVALID_INPUT: return "Invalid Input";
        case KJ_ERR_INTERRUPED: return "Interrupted";
        case KJ_ERR_ILLEGAL_SEEK: return "Illegal Seek";
        default: return "Unknown";
    }
}

#if defined(KJ_SYS_WIN32)
KJ_INTERN kjErr kj_io_err_from_sys(u32 err) {
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

kjIo kj_io_open(const char* path, u32 flags) {
    kjIo res;
    u32 access = kj_io_gen_access_mode(flags);
    u32 create = kj_io_gen_create_mode(flags);
    if((access | create) == KJ_IO_INVALID_MODE) {
        res.handle = NULL;
        res.flags = 0;
        res.err = KJ_ERR_INVALID_INPUT;
    } else {
        i32 size = MultiByteToWideChar(CP_UTF8, 0, path, -1, 0, 0);
        WCHAR* wide_path = kj_cast(WCHAR*, _alloca(size * sizeof(WCHAR)));
        MultiByteToWideChar(CP_UTF8, 0, path, -1, wide_path, size);
        res.handle = CreateFileW(
                wide_path, access,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                NULL, create, 0, NULL);
        res.flags = flags;
        res.err = res.handle == INVALID_HANDLE_VALUE ? KJ_ERR_BAD_HANDLE:
            kj_io_err_from_sys(GetLastError());
    }
    return res;
}

kjErr kj_io_close(kjIo* io) {
    kjErr res = KJ_ERR_NONE;
    if(!CloseHandle(io->handle)) {
        res = kj_io_err_from_sys(GetLastError());
    }
    io->handle = NULL;
    return res;
}

kjErr kj_io_seek(kjIo* io, i64 offset, kjIoSeek seek) {
    kjErr res = KJ_ERR_NONE;
    LARGE_INTEGER new_offset;
    new_offset.QuadPart = offset;
    if(SetFilePointerEx(io->handle, new_offset, &new_offset, seek) == 0) {
        res = kj_io_err_from_sys(GetLastError());
        io->err = res;
    }
    return res;
}

isize kj_io_read(kjIo* io, void* buf, isize size) {
    isize res = -1;
    DWORD read = 0;
    if(ReadFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), NULL)) {
        res = read;
    } else {
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

isize kj_io_write(kjIo* io, void* buf, isize size) {
    isize res = -1;
    DWORD wrote = 0;
    if(WriteFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), NULL)) {
        res = wrote;
    } else {
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset) {
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
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset) {
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
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

kjIoStat kj_io_stat(kjIo* io) {
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
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}
#elif defined(KJ_SYS_LINUX)
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

KJ_INTERN kjErr kj_io_err_from_sys(u32 err) {
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

kjIo kj_io_open(const char* path, u32 flags) {
    kjIo res;
    u32 access = kj_io_gen_access_mode(flags);
    u32 create = kj_io_gen_create_mode(flags);
    if((access | create) == KJ_IO_INVALID_MODE) {
        res.handle = -1;
        res.flags = 0;
        res.err = KJ_ERR_INVALID_INPUT;
    } else {
        u32 perm = 0666;
        kj_syscall3(KJ_SYSCALL_OPEN, res.handle, path, (access | create), perm);
        res.flags = flags;
        res.err = kj_io_err_from_sys(res.handle < 0 ? -res.handle: 0);
    }
    return res;
}

kjErr kj_io_close(kjIo* io) {
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
    kjErr res = KJ_ERR_NONE;
    isize out = -1;
    kj_syscall3(KJ_SYSCALL_LSEEK, out, io->handle, offset, seek);
    res = kj_io_err_from_sys(out < 0 ? -out: 0);
    io->err = res;
    return res;
}

isize kj_io_read(kjIo* io, void* buf, isize size) {
    isize res = -1;
    kj_syscall3(KJ_SYSCALL_READ, res, io->handle, buf, size);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_write(kjIo* io, void* buf, isize size) {
    isize res = -1;
    kj_syscall3(KJ_SYSCALL_WRITE, res, io->handle, buf, size);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
    kj_syscall4(KJ_SYSCALL_PREAD, res, io->handle, buf, size, offset);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
    kj_syscall4(KJ_SYSCALL_PWRITE, res, io->handle, buf, size, offset);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

kjIoStat kj_io_stat(kjIo* io) {
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
#else
#error KJ_IO_UNSUPPORTED
#endif

#if defined(KJ_SYS_WIN32) || defined(KJ_SYS_LINUX)
void* kj_io_slurp(const char* path, b32 terminate, isize* size) {
    void* res = NULL;
    kjIo io = kj_io_open(path, KJ_IO_FLAG_READ);
    if(!kj_io_has_err(&io)) {
        kjIoStat stat = kj_io_stat(&io);
        if(stat.size > 0) {
            res = kj_heap_alloc(NULL, terminate ? stat.size + 1: stat.size);
            if(kj_io_read(&io, res, stat.size) == stat.size) {
                if(terminate) {
                    u8* s = kj_cast(u8*, res);
                    s[stat.size] = '\0';
                }
                if(size) {
                    *size = stat.size;
                }
            } else {
                kj_heap_free(NULL, res);
                res = NULL;
            }
        }
        kj_io_close(&io);
    }
    return res;
}

i64 kj_io_size(kjIo* io) {
    i64 res = 0;
    kjIoStat stat = kj_io_stat(io);
    if(!kj_io_has_err(io)) {
        res = stat.size;
    }
    return res;
}
#endif

const char* kj_path_extension_with_size(const char* path, isize size) {
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
        isize size = kj_str_size(path);
        res = kj_path_extension_with_size(path, size);
    }
    return res;
}

#endif
