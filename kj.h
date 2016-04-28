// `kj.h`
// public domain - no offered or implied warranty, use at your own risk

#ifndef KJ_H
#define KJ_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_VERSION_MAJOR 0
#define KJ_VERSION_MINOR 2
#define KJ_VERSION_PATCH 1

#if defined(_WIN32) || defined(_WIN64)
#define KJ_SYS_WIN32
#if !defined(WIN32_LEAN_AND_MEAN)
#define NOMINMAX 1
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1
#endif
#include <windows.h>
#elif defined(__linux__)
#define KJ_SYS_LINUX
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
#define NULL (cast_of(void*, 0))
#endif
#endif

#if !defined(KJ_API)
#if defined(KJ_STATIC)
#define KJ_API static
#else
#define KJ_API extern
#endif
#endif

#if !defined(KJ_EXPORT)
#if defined(KJ_COMPILER_MSVC)
#if defined(__cplusplus)
#define KJ_EXPORT extern "C" __declspec(dllexport)
#else
#define KJ_EXPORT __declspec(dllexport)
#endif
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#if defined(__cplusplus)
#define KJ_EXPORT extern "C"
#else
#define KJ_EXPORT
#endif
#else
#error KJ_EXPORT_UNSUPPORTED
#endif
#endif

#if !defined(inline)
#if defined(KJ_COMPILER_MSVC) && !defined(__cplusplus) && _MSC_VER <= 1800
#define inline __inline
#define restrict __restrict
#endif
#endif

#if !defined(__cplusplus)
#if !defined(thread_local)
#if defined(KJ_COMPILER_MSVC)
#define thread_local __declspec(thread)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define thread_local __thread
#endif
#endif
#endif

#if !defined(force_inline)
#if defined(KJ_COMPILER_MSVC)
#define force_inline __forceinline
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define force_inline __attribute__((always_inline))
#endif
#endif

#if !defined(no_inline)
#if defined(KJ_COMPILER_MSVC)
#define no_inline __declspec(noinline)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define no_inline __attribute__((noinline))
#endif
#endif

#if !defined(global)
#define global static
#endif

#if !defined(internal)
#define internal static
#endif

#if !defined(elif)
#define elif else if
#endif

#if !defined(loop)
#define loop for(;;)
#endif

#if !defined(cast_of)
#define cast_of(t, e) ((t) (e))
#endif

#if !defined(isize_of)
#define isize_of(a) (cast_of(isize, sizeof(a)))
#define usize_of(a) (cast_of(usize, sizeof(a)))
#endif

#if !defined(count_of)
#define count_of(a) (isize_of(a) / isize_of((a)[0]))
#endif

#if !defined(string_of)
#define string_of(a) #a
#endif

#if !defined(offset_of)
#define offset_of(s, m) (cast_of(isize, (&(cast_of(s*, 0)->m))))
#endif

#if !defined(align_of)
#define align_of(type) (offset_of(struct { u8 c; type member; }, member))
#endif

#if !defined(unused)
#if defined(KJ_COMPILER_MSVC)
#define unused(a) __pragma(warning(suppress:4100)) (a)
#else
#define unused(a) cast_of(void, (a))
#endif
#endif

#if !defined(align_to)
#if defined(__GNUC__)
#define align_to(a) __attribute__((aligned(a)))
#elif defined(__clang__)
#define align_to(a) __attribute__((align_value((a)))
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
#define align_to(a) __declspec(align(a))
#else
#error KJ_ALIGN_UNSUPPORTED
#endif
#endif

#if !defined(__cplusplus)
#if !defined(true)
#define true 1
#endif
#if !defined(false)
#define false 0
#endif
#endif

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
typedef signed char i8;
typedef unsigned char u8;
typedef signed short i16;
typedef unsigned short u16;
typedef signed int i32;
typedef unsigned int u32;
typedef signed long long i64;
typedef unsigned long long u64;
#endif

#if !defined(I8_MIN)
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
#define F32_MIN cast_of(f32, -3.402823e+38)
#define F32_MAX cast_of(f32, 3.402823e+38)
#define F32_EPS cast_of(f32, 1.192093e-07)

#define F64_MIN cast_of(f64, -1.797693e+308)
#define F64_MAX cast_of(f64, 1.797693e+308)
#define F64_EPS cast_of(f64, 2.220446e-16)
#endif

#define kj_static_assert(n, a) typedef void* kj_static_assert_##n[(a) * 2 - 1]
kj_static_assert(i8, isize_of(i8) == 1);
kj_static_assert(u8, isize_of(u8) == 1);
kj_static_assert(i16, isize_of(i16) == 2);
kj_static_assert(u16, isize_of(u16) == 2);
kj_static_assert(i32, isize_of(i32) == 4);
kj_static_assert(u32, isize_of(u32) == 4);
kj_static_assert(i64, isize_of(i64) == 8);
kj_static_assert(u64, isize_of(u64) == 8);
kj_static_assert(f32, isize_of(f32) == 4);
kj_static_assert(f64, isize_of(f64) == 8);

#if defined(KJ_SYS_WIN32)
#define KJ_PATH_SEPARATOR '\\'
#else
#define KJ_PATH_SEPARATOR '/'
#endif

#if defined(KJ_SYS_WIN32)
#define kj_copy CopyMemory
#define kj_set FillMemory
#define kj_zero ZeroMemory
#define kj_one(p, s) kj_set(p, s, 1)
#define kj_move MoveMemory
#else
#define kj_copy __builtin_memcpy
#define kj_set(p, s, v) __builtin_memset((p), (v), (s))
#define kj_zero(p, s) kj_set(p, s, 0)
#define kj_one(p, s) kj_set(p, s, 1)
#define kj_move __builtin_memmove
#endif

void kj_assert_handler(const char* expr, const char* file, u64 line, const char* msg);

#if defined(KJ_DEBUG)
#if defined(KJ_COMPILER_MSVC)
#define kj_break() __debugbreak()
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_break() __builtin_trap()
#else
#error KJ_BREAK_UNSUPPORTED
#endif

#define kj_assert_msg(expr, msg) do {                                           \
    if(!(expr)) {                                                               \
        kj_assert_handler(string_of(expr), __FILE__, __LINE__, msg);            \
        kj_break();                                                             \
    }                                                                           \
} while(0)

#define kj_assert(expr) kj_assert_msg(expr, NULL)
#else
#define kj_assert_msg(expr, msg)
#define kj_assert(expr)
#define kj_panic(msg)
#endif

typedef enum kjType {
    KJ_TYPE_NONE = 0,
    KJ_TYPE_CHAR = 1,
    KJ_TYPE_I8 = 2,
    KJ_TYPE_U8 = 3,
    KJ_TYPE_I16 = 4,
    KJ_TYPE_U16 = 5,
    KJ_TYPE_I32 = 6,
    KJ_TYPE_U32 = 7,
    KJ_TYPE_B32 = 8,
    KJ_TYPE_I64 = 9,
    KJ_TYPE_U64 = 10,
    KJ_TYPE_ISIZE = 11,
    KJ_TYPE_USIZE = 12,
    KJ_TYPE_F32 = 13,
    KJ_TYPE_F64 = 14,
    KJ_TYPE_UNKNOWN,
    KJ_TYPE_COUNT
} kjType;

KJ_API const char* kj_type_to_str(kjType type);
KJ_API isize kj_type_to_size(kjType type);

KJ_API u16 kj_swap16(u16 a);
KJ_API u32 kj_swap32(u32 a);
KJ_API u64 kj_swap64(u64 a);

#if !defined(kj_encode64)
#if KJ_ENDIAN == KJ_LE
#define kj_encode64(a, b, c, d, e, f, g, h)                                     \
    (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24) | ((e) << 32) | ((f) << 40) | ((g) << 48) | ((h) << 56))
#define kj_encode32(a, b, c, d) (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#define kj_encode16(a, b) (((a) << 0) | ((b) << 8))
#define kj_swap16_le(a) (a)
#define kj_swap32_le(a) (a)
#define kj_swap64_le(a) (a)
#define kj_swap16_be(a) kj_swap16(a)
#define kj_swap32_be(a) kj_swap32(a)
#define kj_swap64_be(a) kj_swap64(a)
#else
#define kj_encode64(a, b, c, d, e, f, g, h)                                     \
    (((h) << 0) | ((g) << 8) | ((f) << 16) | ((e) << 24) | ((d) << 32) | ((c) << 40) | ((b) << 48) | ((a) << 56))
#define kj_encode32(a, b, c, d) (((d) << 0) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#define kj_encode16(a, b) (((b) << 0) | ((a) << 8))
#define kj_swap16_le(a) kj_swap16(a)
#define kj_swap32_le(a) kj_swap32(a)
#define kj_swap64_le(a) kj_swap64(a)
#define kj_swap16_be(a) (a)
#define kj_swap32_be(a) (a)
#define kj_swap64_be(a) (a)
#endif
#endif

#if !defined(kj_min)
#define kj_min(a, b) ((a) < (b) ? (a): (b))
#define kj_max(a, b) ((a) > (b) ? (a): (b))
#define kj_clamp(a, min, max) (kj_max((min), kj_min((a), (max))))
#define kj_range(a, fl, fu, tl, tu) ((a - fl) * (tu - tl) / ((fu - fl) + tl))
#define kj_swap(T, a, b) { T tmp_##__LINE__ = a; a = b; b = tmp_##__LINE__; }
#define kj_abs(a) ((a) > 0 ? (a) : -(a))
#define kj_sign(a) ((a) >= 0 ? 1 : -1)
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

#if defined(KJ_SYS_LINUX)
#if !defined(kj_syscall1)
#if defined(KJ_ARCH_64_BIT)
#define KJ_SYSCALL_CLOSE 3
#define KJ_SYSCALL_OPEN 2
#define KJ_SYSCALL_READ 0
#define KJ_SYSCALL_PREAD 17
#define KJ_SYSCALL_WRITE 1
#define KJ_SYSCALL_PWRITE 18
#define KJ_SYSCALL_READLINK 89
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
#define KJ_SYSCALL_CLOSE 6
#define KJ_SYSCALL_OPEN 5
#define KJ_SYSCALL_READ 3
#define KJ_SYSCALL_PREAD 180
#define KJ_SYSCALL_WRITE 4
#define KJ_SYSCALL_PWRITE 181
#define KJ_SYSCALL_READLINK 85
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
        : "0" ((call)), "b" ((a)), "c" ((b)), "d" ((c)))
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

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_printf_vargs(a) __attribute__((format(printf, a, (a+1))))
#else
#define kj_printf_vargs(a)
#endif

#include <stdarg.h>

KJ_API i32 kj_vprintf(char const* fmt, va_list v);
KJ_API i32 kj_printf(char const* fmt, ...) kj_printf_vargs(1);
KJ_API i32 kj_vsnprintf(char* buf, isize size, char const* fmt, va_list v);
KJ_API i32 kj_snprintf(char* buf, isize size, char const* fmt, ...) kj_printf_vargs(3);

KJ_API b32 kj_char_is_eol(char c);
KJ_API b32 kj_char_is_ws(char c);
KJ_API b32 kj_char_is_alpha(char c);
KJ_API b32 kj_char_is_digit(char c);
KJ_API b32 kj_char_is_alphanum(char c);
KJ_API b32 kj_char_is_hex_letter(char c);
KJ_API b32 kj_char_is_hex_digit(char c);
KJ_API char kj_char_is_lower(char c);
KJ_API char kj_char_is_upper(char c);
KJ_API char kj_char_to_lower(char c);
KJ_API char kj_char_to_upper(char c);
KJ_API isize kj_str_size(const char* s);
KJ_API isize kj_str_cmp_n(const char* s1, const char* s2, isize n);
KJ_API isize kj_str_cmp(const char* s1, const char* s2);

typedef void* kjLib;
KJ_API kjLib kj_lib_open(const char* path);
KJ_API void* kj_lib_fn(kjLib lib, const char* name);
KJ_API void kj_lib_close(kjLib lib);

#if !defined(KJ_ERR_NONE)
#define KJ_ERR_NONE (0)
#endif
typedef u32 kjErr;

#if defined(__cplusplus)
}
#endif
#endif

#if defined(KJ_IMPLEMENTATION)

const char* kj_type_to_str(kjType type) {
    static const char* KJ_TYPE_STR[] = {
        "none",
        "char",
        "i8",
        "u8",
        "i16",
        "u16",
        "i32",
        "u32",
        "b32",
        "i64",
        "u64",
        "isize",
        "usize",
        "f32",
        "f64",
        "unknown",
    };
    return KJ_TYPE_STR[type];
}

isize kj_type_to_isize(kjType type) {
    static const isize KJ_TYPE_ISIZE[] = {
        0,
        isize_of(char),
        isize_of(i8),
        isize_of(u8),
        isize_of(i16),
        isize_of(u16),
        isize_of(i32),
        isize_of(u32),
        isize_of(b32),
        isize_of(i64),
        isize_of(u64),
        isize_of(isize),
        isize_of(usize),
        isize_of(f32),
        isize_of(f64),
        0,
    };
    return KJ_TYPE_ISIZE[type];
}

u16 kj_swap16(u16 a) { return cast_of(u16, (a << 8) | (a >> 8)); }
u32 kj_swap32(u32 a) { return cast_of(u32, (a << 24) | ((a << 8) & 0x00FF0000) | ((a >> 8) & 0x0000FF00) | (a >> 24)); }
u64 kj_swap64(u64 a) { return cast_of(u64, kj_swap32((a & 0xFFFFFFFF00000000) >> 32) | kj_swap32((a & 0x00000000FFFFFFFF) << 32)); }

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
    int res;
    va_list v;
    va_start(v,fmt);
    res = kj_vsnprintf(buf, size, fmt, v);
    va_end(v);
    return res;
}

b32 kj_char_is_eol(char c) { return c == '\r' || c == '\n'; }
b32 kj_char_is_ws(char c) { return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n'; }
b32 kj_char_is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z'); }
b32 kj_char_is_digit(char c) { return (c >= '0' && c <= '9'); }
b32 kj_char_is_alphanum(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z') || (c >= '0' && c <= '9'); }
b32 kj_char_is_hex_letter(char c) { return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
b32 kj_char_is_hex_digit(char c) { return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'); }
char kj_char_is_lower(char c) { return (c >= 'a' && c <= 'z'); }
char kj_char_is_upper(char c) { return (c >= 'A' && c <= 'Z'); }
char kj_char_to_lower(char c) { return (c >= 'A' && c <= 'Z') ? 'a' + (c - 'A'): c; }
char kj_char_to_upper(char c) { return (c >= 'a' && c <= 'z') ? 'A' + (c - 'a'): c; }
isize kj_str_size(const char* s) { const char* e = s; while(*e) { e++; } return (e - s); }

isize kj_str_cmp_n(const char* s1, const char* s2, isize n) {
    while(*s1 && *s2 && n) {
        if(*s1 != *s2) {
            return cast_of(uptr, *s1) < cast_of(uptr, *s2) ? -1: +1;
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
            return cast_of(uptr, *s1) < cast_of(uptr, *s2) ? -1: +1;
        }
        s1++;
        s2++;
    }
    return 0;
}

#if defined(KJ_SYS_WIN32)
kjLib kj_lib_open(const char* path) { return cast_of(kjLib, LoadLibrary(path)); }
void* kj_lib_fn(kjLib lib, const char* name) { return cast_of(void*, GetProcAddress(cast_of(HMODULE, lib), name)); }
void kj_lib_close(kjLib lib) { FreeLibrary(cast_of(HMODULE, lib)); }
#elif defined(KJ_SYS_LINUX)
#include <dlfcn.h>
kjLib kj_lib_open(const char* path) { return cast_of(kjLib, dlopen(path, RTLD_LAZY)); }
void* kj_lib_fn(kjLib lib, const char* name) { return cast_of(void*, dlsym(lib, name)); }
void kj_lib_close(kjLib lib) { dlclose(lib); }
#else
#error KJ_LIB_UNSUPPORTED
#endif

#endif
