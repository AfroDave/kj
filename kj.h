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

#define KJ_LE 0xABCD
#define KJ_BE 0xDCBA

#define KJ_ENDIAN KJ_LE

#include <stddef.h>
#include <stdint.h>
#include <float.h>

#if !defined(NULL)
#if defined(KJ_COMPILER_MSVC)
#define NULL 0
#elif defined(KJ_COMPILER_GNU)
#define NULL __null
#else
#define NULL (cast_of(void*, 0))
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

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

#if !defined(I8_MIN)
#define I8_MIN INT8_MIN
#define I8_MAX INT8_MAX

#define I16_MIN INT16_MIN
#define I16_MAX INT16_MAX

#define I32_MIN INT32_MIN
#define I32_MAX INT32_MAX

#define I64_MIN INT64_MIN
#define I64_MAX INT64_MAX

#define U8_MIN 0
#define U8_MAX UINT8_MAX

#define U16_MIN 0
#define U16_MAX UINT16_MAX

#define U32_MIN 0
#define U32_MAX UINT32_MAX

#define U64_MIN 0
#define U64_MAX UINT64_MAX
#endif

typedef u32 b32;

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

typedef intptr_t iptr;
typedef uintptr_t uptr;
typedef ptrdiff_t dptr;

typedef float f32;
typedef double f64;

#if !defined(F32_MIN)
#define F32_MIN -FLT_MAX
#define F32_MAX FLT_MAX
#define F32_EPS FLT_EPSILON

#define F64_MIN -DBL_MAX
#define F64_MAX DBL_MAX
#define F64_EPS DBL_EPSILON
#endif

#define kj_static_assert(n, a) typedef int kj_static_assert_##n[(a) * 2 - 1]
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

void kj_assert_handler(char* expr, char* file, u64 line, char* msg, ...);

#if defined(KJ_DEBUG)
#if defined(KJ_COMPILER_MSVC)
#define kj_break() __debugbreak()
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_break() __builtin_trap()
#else
#error KJ_BREAK_UNSUPPORTED
#endif

#define kj_assert_msg(expr, msg, ...) do {                                      \
    if(!(expr)) {                                                               \
        kj_assert_handler(                                                      \
                string_of(expr), __FILE__, __LINE__, msg, ##__VA_ARGS__);       \
        kj_break();                                                             \
    }                                                                           \
} while(0)

#define kj_assert(expr) kj_assert_msg(expr, NULL)
#else
#define kj_assert_msg(expr, msg, ...)
#define kj_assert(expr)
#define kj_panic(msg)
#endif

typedef enum kj_type {
    KJ_TYPE_NONE,
    KJ_TYPE_CHAR,
    KJ_TYPE_I8,
    KJ_TYPE_U8,
    KJ_TYPE_I16,
    KJ_TYPE_U16,
    KJ_TYPE_I32,
    KJ_TYPE_U32,
    KJ_TYPE_B32,
    KJ_TYPE_I64,
    KJ_TYPE_U64,
    KJ_TYPE_ISIZE,
    KJ_TYPE_USIZE,
    KJ_TYPE_F32,
    KJ_TYPE_F64,
    KJ_TYPE_UNKNOWN,
} kj_type_t;

global const char* KJ_TYPE_STR[] = {
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

global const u32 KJ_TYPE_SIZE[] = {
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

#define kj_swap16(a) (((a) << 8) | ((a) >> 8))
#define kj_swap32(a) ((a) >> 24) | (((a) << 8) & 0x00FF0000) | (((a) >> 8) & 0x0000FF00) | ((a) << 24)
#define kj_swap64(a) kj_swap32(((a) & 0xFFFFFFFF00000000) >> 32) | kj_swap32(((a) & 0x00000000FFFFFFFF) << 32)

#if KJ_ENDIAN == KJ_LE
#define kj_encode(a, b, c, d) ((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24)
#define kj_swap16_le(a) (a)
#define kj_swap32_le(a) (a)
#define kj_swap64_le(a) (a)
#define kj_swap16_be(a) kj_swap16(a)
#define kj_swap32_be(a) kj_swap32(a)
#define kj_swap64_be(a) kj_swap64(a)
#else
#define kj_encode(a, b, c, d) ((d) << 0) | ((c) << 8) | ((b) << 16) | ((a) << 24)
#define kj_swap16_le(a) kj_swap16(a)
#define kj_swap32_le(a) kj_swap32(a)
#define kj_swap64_le(a) kj_swap64(a)
#define kj_swap16_be(a) (a)
#define kj_swap32_be(a) (a)
#define kj_swap64_be(a) (a)
#endif

#define kj_min(a, b) (a) < (b) ? (a): (b)
#define kj_max(a, b) (a) > (b) ? (a): (b)
#define kj_clamp(a, min, max) kj_max((min), kj_min((a), (max)))

#define kj_kb(a) ((a) * 1024)
#define kj_mb(a) (kj_kb((a)) * 1024)
#define kj_gb(a) (kj_mb((a)) * 1024)
#define kj_tb(a) (kj_gb((a)) * 1024)
#define kj_b_kb(a) ((a) / 1024)
#define kj_b_mb(a) (kj_b_kb((a)) / 1024)
#define kj_b_gb(a) (kj_b_mb((a)) / 1024)
#define kj_b_tb(a) (kj_b_gb((a)) / 1024)

inline b32 kj_char_is_eol(char c)
{
    return c == '\r' || c == '\n';
}

inline b32 kj_char_is_ws(char c)
{
    return c == ' ' || c == '\t' || c == '\v' || c == '\f' || kj_char_is_eol(c);
}

inline b32 kj_char_is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z');
}

inline b32 kj_char_is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

inline b32 kj_char_is_alphanum(char c)
{
    return kj_char_is_alpha(c) || kj_char_is_digit(c);
}

inline b32 kj_char_is_hex_letter(char c)
{
    return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

inline b32 kj_char_is_hex_digit(char c)
{
    return kj_char_is_digit(c) || kj_char_is_hex_letter(c);
}

inline char kj_char_is_lower(char c)
{
    return (c >= 'a' && c <= 'z');
}

inline char kj_char_is_upper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

inline char kj_char_to_lower(char c)
{
    return kj_char_is_upper(c) ? 'a' + (c - 'A'): c;
}

inline char kj_char_to_upper(char c)
{
    return kj_char_is_lower(c) ? 'A' + (c - 'a'): c;
}

inline isize kj_str_size(char* s)
{
    char* e = NULL;
    for(e = s; *e; e++) { }
    return (e - s);
}

isize kj_str_cmp_n(char* s1, char* s2, usize n)
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

isize kj_str_cmp(char* s1, char* s2)
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

#define KJ_ERR_NONE (0)
typedef u32 kj_err_t;

#if defined(__cplusplus)
}
#endif

#endif
