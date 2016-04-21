#ifndef KJ_H
#define KJ_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_VERSION_MAJOR 0
#define KJ_VERSION_MINOR 1
#define KJ_VERSION_PATCH 0

#if defined(_WIN32) || defined(_WIN64)
#define KJ_SYS_WIN32
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
#if defined(KJ_COMPILER_GNU)
#define NULL __null
#else
#define NULL (cast_of(void*, 0))
#endif
#endif

#if !defined(kj_api)
#if defined(kj_static)
#define kj_api static
#else
#if defined(__cplusplus)
#define kj_api extern "C"
#else
#define kj_api extern
#endif
#endif
#endif

#if !defined(inline)
#if defined(KJ_COMPILER_MSVC) && !defined(__cplusplus) && _MSC_VER <= 1800
#define inline __inline
#define restrict __restrict
#endif
#endif

#if !defined(thread_local)
#if defined(KJ_COMPILER_MSVC)
#define thread_local __declspec(thread)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define thread_local __thread
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

#if !defined(size_of)
#define size_of sizeof
#endif

#if !defined(count_of)
#define count_of(a) (size_of(a) / size_of((a)[0]))
#endif

#if !defined(string_of)
#define string_of(a) #a
#endif

#if !defined(offset_of)
#define offset_of(s, m) (cast_of(usize, (&(cast_of(s*, 0)->m))))
#endif

#if !defined(align_of)
#define align_of(type) offset_of(struct { u8 c; type member; }, member)
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
typedef unsigned __int8 u8;
typedef signed __int8 i8;
typedef unsigned __int16 u16;
typedef signed __int16 i16;
typedef unsigned __int32 u32;
typedef signed __int32 i32;
typedef unsigned __int64 u64;
typedef signed __int64 i64;
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
#define I8_MIN (-128)
#define I8_MAX (127)

#define I16_MIN (-32768)
#define I16_MAX (32767)

#define I32_MIN (-2147483648)
#define I32_MAX (2147483647)

#define I64_MIN (-9223372036854775808)
#define I64_MAX (9223372036854775807)

#define U8_MIN (0)
#define U8_MAX (256)

#define U16_MIN (0)
#define U16_MAX (65536)

#define U32_MIN (0)
#define U32_MAX (4294967296)

#define U64_MIN (0)
#define U64_MAX (18446744073709551616)
#endif

typedef u32 b32;

typedef i64 isize;
typedef u64 usize;

#if !defined(ISIZE_MIN)
#define ISIZE_MIN I64_MIN
#define ISIZE_MAX I64_MAX

#define USIZE_MIN U64_MIN
#define USIZE_MAX U64_MAX
#endif

typedef isize iptr;
typedef usize uptr;
typedef isize dptr;

typedef float f32;
typedef double f64;

#if !defined(F32_MIN)
#define F32_MIN (-3.402823e+38)
#define F32_MAX (3.402823e+38)
#define F32_EPS (1.192093e-07)

#define F64_MIN (-1.797693e+308)
#define F64_MAX (1.797693e+308)
#define F64_EPS (2.220446e-16)
#endif

#define kj_static_assert(n, a) typedef i32 kj_static_assert_##n[(a) * 2 - 1]
kj_static_assert(i8, size_of(i8) == 1);
kj_static_assert(u8, size_of(u8) == 1);
kj_static_assert(i16, size_of(i16) == 2);
kj_static_assert(u16, size_of(u16) == 2);
kj_static_assert(i32, size_of(i32) == 4);
kj_static_assert(u32, size_of(u32) == 4);
kj_static_assert(i64, size_of(i64) == 8);
kj_static_assert(u64, size_of(u64) == 8);
kj_static_assert(f32, size_of(f32) == 4);
kj_static_assert(f64, size_of(f64) == 8);

#if defined(KJ_SYS_WIN32)
#define kj_copy CopyMemory
#define kj_set FillMemory
#define kj_zero ZeroMemory
#define kj_move MoveMemory
#else
#define kj_copy memcpy
#define kj_set(p, s, v) memset((p), (v), (s))
#define kj_zero(p, s) kj_set(p, s, 0)
#define kj_move memmove
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
        kj_assert_handler(                                                      \
                string_of(expr), __FILE__, __LINE__, msg);                      \
        kj_break();                                                             \
    }                                                                           \
} while(0)

#define kj_assert(expr) kj_assert_msg(expr, NULL)
#else
#define kj_assert_msg(expr, msg)
#define kj_assert(expr)
#define kj_panic(msg)
#endif

typedef enum kj_type {
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
    KJ_TYPE_UNKNOWN = 15,
    KJ_TYPE_COUNT
} kj_type_t;

const char* kj_type_to_str(kj_type_t type)
{
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

usize kj_type_to_size(kj_type_t type)
{
    static const usize KJ_TYPE_SIZE[] = {
        0,
        size_of(char),
        size_of(i8),
        size_of(u8),
        size_of(i16),
        size_of(u16),
        size_of(i32),
        size_of(u32),
        size_of(b32),
        size_of(i64),
        size_of(u64),
        size_of(isize),
        size_of(usize),
        size_of(f32),
        size_of(f64),
        0,
    };
    return KJ_TYPE_SIZE[type];
}

#define kj_swap16(a) (((a) << 8) | ((a) >> 8))
#define kj_swap32(a) ((a) >> 24) | (((a) << 8) & 0x00FF0000) | (((a) >> 8) & 0x0000FF00) | ((a) << 24)
#define kj_swap64(a) kj_swap32(((a) & 0xFFFFFFFF00000000) >> 32) | kj_swap32(((a) & 0x00000000FFFFFFFF) << 32)

#if KJ_ENDIAN == KJ_LE
#define kj_encode64(a, b, c, d, e, f, g, h) (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24) | ((e) << 32) | ((f) << 40) | ((g) << 48) | ((h) << 56))
#define kj_encode32(a, b, c, d) (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#define kj_encode16(a, b) (((a) << 0) | ((b) << 8))
#define kj_swap16_le(a) (a)
#define kj_swap32_le(a) (a)
#define kj_swap64_le(a) (a)
#define kj_swap16_be(a) kj_swap16(a)
#define kj_swap32_be(a) kj_swap32(a)
#define kj_swap64_be(a) kj_swap64(a)
#else
#define kj_encode64(a, b, c, d, e, f, g, h) (((h) << 0) | ((g) << 8) | ((f) << 16) | ((e) << 24) | ((d) << 32) | ((c) << 40) | ((b) << 48) | ((a) << 56))
#define kj_encode32(a, b, c, d) (((d) << 0) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#define kj_encode16(a, b) (((b) << 0) | ((a) << 8))
#define kj_swap16_le(a) kj_swap16(a)
#define kj_swap32_le(a) kj_swap32(a)
#define kj_swap64_le(a) kj_swap64(a)
#define kj_swap16_be(a) (a)
#define kj_swap32_be(a) (a)
#define kj_swap64_be(a) (a)
#endif

#define kj_min(a, b) ((a) < (b) ? (a): (b))
#define kj_max(a, b) ((a) > (b) ? (a): (b))
#define kj_clamp(a, min, max) kj_max((min), kj_min((a), (max)))
#define kj_range(a, fl, fu, tl, tu) ((a - fl) * (tu - tl) / ((fu - fl) + tl))
#define kj_swap(T, a, b) { T tmp = a; a = b; b = a; }

#define kj_kb(a) ((a) * 1024)
#define kj_mb(a) (kj_kb((a)) * 1024)
#define kj_gb(a) (kj_mb((a)) * 1024)
#define kj_tb(a) (kj_gb((a)) * 1024)
#define kj_b_kb(a) ((a) / 1024)
#define kj_b_mb(a) (kj_b_kb((a)) / 1024)
#define kj_b_gb(a) (kj_b_mb((a)) / 1024)
#define kj_b_tb(a) (kj_b_gb((a)) / 1024)

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_printf_vargs(a) __attribute__((format(printf, a, (a+1))))
#else
#define kj_printf_vargs(a)
#endif

#if defined(KJ_PRINTF)
#include <stdarg.h>
#include <stdio.h>
kj_api inline i32 kj_vprintf(char const* fmt, va_list v);
kj_api inline i32 kj_printf(char const* fmt, ...) kj_printf_vargs(1);
kj_api inline i32 kj_vsnprintf(char* buf, isize size, char const* fmt, va_list v);
kj_api i32 kj_snprintf(char* buf, isize size, char const* fmt, ...) kj_printf_vargs(3);

inline i32 kj_vprintf(char const* fmt, va_list v)
{
    return vfprintf(stdout, fmt, v);
}

inline i32 kj_printf(char const* fmt, ...)
{
    i32 res;
    va_list v;
    va_start(v, fmt);
    res = kj_vprintf(fmt, v);
    va_end(v);
    return res;
}

inline i32 kj_vsnprintf(char* buf, isize size, char const* fmt, va_list v)
{
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

inline i32 kj_snprintf(char* buf, isize size, char const* fmt, ...)
{
    int res;
    va_list v;
    va_start(v,fmt);
    res = kj_vsnprintf(buf, size, fmt, v);
    va_end(v);
    return res;
}
#endif

kj_api inline b32 kj_char_is_eol(char c)
{
    return c == '\r' || c == '\n';
}

kj_api inline b32 kj_char_is_ws(char c)
{
    return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n';
}

kj_api inline b32 kj_char_is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z');
}

kj_api inline b32 kj_char_is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

kj_api inline b32 kj_char_is_alphanum(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z') || (c >= '0' && c <= '9');
}

kj_api inline b32 kj_char_is_hex_letter(char c)
{
    return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

kj_api inline b32 kj_char_is_hex_digit(char c)
{
    return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9');
}

kj_api inline char kj_char_is_lower(char c)
{
    return (c >= 'a' && c <= 'z');
}

kj_api inline char kj_char_is_upper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

kj_api inline char kj_char_to_lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? 'a' + (c - 'A'): c;
}

kj_api inline char kj_char_to_upper(char c)
{
    return (c >= 'a' && c <= 'z') ? 'A' + (c - 'a'): c;
}

kj_api inline isize kj_str_size(const char* s)
{
    const char* e = s;
    while(*e) { e++; }
    return (e - s);
}

kj_api inline isize kj_str_cmp_n(const char* s1, const char* s2, usize n)
{
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

kj_api inline isize kj_str_cmp(const char* s1, const char* s2)
{
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
#define KJ_PATH_SEPARATOR '\\'
#define KJ_NEWLINE '\r\n'
#else
#define KJ_PATH_SEPARATOR '/'
#define KJ_NEWLINE '\n'
#endif

#define KJ_ERR_NONE (0)
typedef u32 kj_err_t;

#if defined(__cplusplus)
}
#endif
#endif
