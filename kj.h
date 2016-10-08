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
 *      #include "kj.h"
 */

#ifndef KJ_H
#define KJ_H

#define KJ_VERSION_MAJOR 0
#define KJ_VERSION_MINOR 11
#define KJ_VERSION_PATCH 0

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_X86
#define KJ_ARCH_NAME x86_64
#elif defined(__i386__) || defined(_M_IX86) || defined(_X86_)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_X86
#define KJ_ARCH_NAME x86
#elif defined(__aarch64__)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_ARM
#define KJ_ARCH_NAME arm64
#elif defined(__arm__) || defined(_M_ARM)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_ARM
#define KJ_ARCH_NAME arm
#elif defined(__mips__)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_MIPS
#define KJ_ARCH_NAME mips
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
#define KJ_SYS_NAME windows
#define KJ_SYS_DLL_EXT dll
#define KJ_SYS_EXE_EXT exe
#pragma comment(lib, "kernel32.lib")
#elif defined(__unix__) || defined(__CYGWIN__) || defined(__MSYS__)
#if !defined(_XOPEN_SOURCE)
#define _XOPEN_SOURCE 700
#endif
#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#if !defined(_LARGEFILE64_SOURCE)
#define _LARGEFILE64_SOURCE
#endif
#if !defined(_FILE_OFFSET_BITS)
#define _FILE_OFFSET_BITS 64
#endif
#if !defined(O_RDONLY)
#define O_RDONLY 00
#endif
#if !defined(O_WRONLY)
#define O_WRONLY 01
#endif
#if !defined(O_RDWR)
#define O_RDWR 02
#endif
#if !defined(O_CREAT)
#define O_CREAT 0100
#endif
#if !defined(O_EXCL)
#define O_EXCL 0200
#endif
#if !defined(O_TRUNC)
#define O_TRUNC 01000
#endif
#if !defined(O_APPEND)
#define O_APPEND 02000
#endif
#if !defined(O_NONBLOCK)
#define O_NONBLOCK 04000
#endif
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#if defined(__linux__)
#define KJ_SYS_LINUX
#define KJ_SYS_NAME linux
#elif defined(__CYGWIN__) || defined(__MSYS__)
#define KJ_SYS_NAME windows
#elif defined(__FreeBSD__)
#define KJ_SYS_FREEBSD
#define KJ_SYS_NAME freebsd
#else
#define KJ_SYS_NAME unix
#endif
#define KJ_SYS_DLL_EXT so
#define KJ_SYS_EXE_EXT
#define KJ_SYS_UNIX
#else
#error "Unsupported Operating System"
#endif

#if !defined(kj_str_of)
#define kj_str_of(a) #a
#endif

#if defined(_MSC_VER)
#define KJ_COMPILER msvc
#define KJ_COMPILER_MSVC
#define KJ_WARNING_DISABLE_BEGIN() __pragma(warning(push))
#define KJ_WARNING_DISABLE_END() __pragma(warning(pop))
#define KJ_WARNING_DISABLE_MSVC(w) __pragma(warning(disable:w))
#elif defined(__clang__)
#if !defined(va_start)
typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif
#define KJ_COMPILER clang
#define KJ_COMPILER_CLANG
#define KJ_WARNING_DISABLE_BEGIN() _Pragma("clang diagnostic push")
#define KJ_WARNING_DISABLE_END() _Pragma("clang diagnostic pop")
#define KJ_WARNING_DISABLE_CLANG(w)                                             \
    _Pragma(kj_str_of(clang diagnostic ignored w))
#elif defined(__GNUC__) || defined(__GNUG__)
#if !defined(va_start)
typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif
#define KJ_COMPILER gnu
#define KJ_COMPILER_GNU
#define KJ_WARNING_DISABLE_BEGIN() _Pragma("GCC diagnostic push")
#define KJ_WARNING_DISABLE_END() _Pragma("GCC diagnostic pop")
#define KJ_WARNING_DISABLE_GNU(w)                                               \
    _Pragma(kj_str_of(GCC diagnostic ignored w))
#else
#error "Unsupported Compiler"
#endif

#if !defined(KJ_WARNING_DISABLE_MSVC)
#define KJ_WARNING_DISABLE_MSVC(w)
#endif

#if !defined(KJ_WARNING_DISABLE_CLANG)
#define KJ_WARNING_DISABLE_CLANG(w)
#endif

#if !defined(KJ_WARNING_DISABLE_GNU)
#define KJ_WARNING_DISABLE_GNU(w)
#endif


#if !defined(KJ_PACK_BEGIN)
#if defined(KJ_COMPILER_MSVC)
#define KJ_PACK_BEGIN(n) __pragma(pack(push, n))
#define KJ_PACK_END() __pragma(pack(pop))
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_PACK_BEGIN(n) _Pragma(kj_str_of(pack(push, n)))
#define KJ_PACK_END() _Pragma(kj_str_of(pack(pop)))
#endif
#endif

#if !defined(KJ_ALIGN)
#if defined(KJ_COMPILER_MSVC)
#define KJ_ALIGN(a) __declspec(align(a))
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_ALIGN(a) __attribute__((aligned(a)))
#endif
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

#if defined(__cplusplus)
#define KJ_CPP
#if __cplusplus >= 201103L
#define KJ_CPP11
#endif
#endif

#if defined(__STDC_VERSION__)
#if __STDC_VERSION__ >= 201112L
#define KJ_C11
#endif
#if __STDC_VERSION__ >= 199901L
#define KJ_C99
#endif
#endif

#define KJ_ENUM(type, name) typedef type name; enum kj__##type##name

enum {
    KJ_FALSE = 0,
    KJ_TRUE = 1,
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

#if !defined(KJ_EXPORT)
#if defined(KJ_COMPILER_MSVC)
#define KJ_EXPORT __declspec(dllexport)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#if defined(KJ_CPP)
#define KJ_EXPORT extern "C"
#else
#define KJ_EXPORT
#endif
#endif
#endif

#if !defined(KJ_API)
#if defined(KJ_STATIC)
#define KJ_API static
#elif defined(KJ_SHARED)
#define KJ_API KJ_EXPORT
#else
#define KJ_API extern
#endif
#endif

#if !defined(KJ_INLINE)
#if defined(KJ_COMPILER_MSVC)
#define KJ_INLINE __forceinline
#elif (defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)) && defined(KJ_C99)
#define KJ_INLINE __attribute__((always_inline)) inline
#else
#define KJ_INLINE
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
#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_align_of __alignof__
#else
#define kj_align_of(type) (kj_offset_of(struct { u8 c; type member; }, member))
#endif
#endif

#if !defined(kj_align_on)
#define kj_align_on(p, a)                                                       \
    kj_cast(void*, (kj_cast(uptr, p) + ((a) - 1)) & ~((a) - 1))
#endif

#if !defined(kj_join)
#define kj_join(a, b) kj_join1(a, b)
#define kj_join1(a, b) kj_join2(a, b)
#define kj_join2(a, b) a##b
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
#define kj_map_range(a, fmin, fmax, tmin, tmax)                                 \
    (((a) - (fmin)) * ((tmax) - (tmin)) / (((fmax) - (fmin)) + (tmin)))
#define kj_swap(T, a, b)                                                        \
    do { T tmp_##__LINE__ = a; (a) = b; (b) = tmp_##__LINE__; } while(0)
#define kj_abs(a) ((a) >= 0 ? (a): -(a))
#define kj_sign(a) ((a) >= 0 ? KJ_TRUE: KJ_FALSE)
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

#if !defined(kj_mem_copy)
#if defined(KJ_SYS_WIN32)
#define kj_mem_copy CopyMemory
#define kj_mem_set FillMemory
#define kj_mem_zero ZeroMemory
#define kj_mem_move MoveMemory
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_mem_copy __builtin_memcpy
#define kj_mem_set(p, s, v) __builtin_memset((p), (v), (s))
#define kj_mem_zero(p, s) kj_mem_set(p, s, 0)
#define kj_mem_move __builtin_memmove
#endif

#define kj_mem_one(p, s) kj_mem_set(p, s, 1)
#define kj_mem_fill(p, s) kj_mem_set(p, s, 0xFF)
#endif

#if defined(KJ_C11)
#define KJ_STATIC_ASSERT(expr) _Static_assert(expr, kj_str_of(expr))
#elif defined(KJ_CPP11)
#define KJ_STATIC_ASSERT(expr) static_assert(expr, kj_str_of(expr))
#else
#define KJ_STATIC_ASSERT(expr)                                                  \
    typedef void* kj_join(KJ_STATIC_ASSERT_, __LINE__)[(expr) * 2 - 1]
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

KJ_STATIC_ASSERT(sizeof(i8) == 1);
KJ_STATIC_ASSERT(sizeof(u8) == 1);
KJ_STATIC_ASSERT(sizeof(i16) == 2);
KJ_STATIC_ASSERT(sizeof(u16) == 2);
KJ_STATIC_ASSERT(sizeof(i32) == 4);
KJ_STATIC_ASSERT(sizeof(u32) == 4);
KJ_STATIC_ASSERT(sizeof(i64) == 8);
KJ_STATIC_ASSERT(sizeof(u64) == 8);

#if !defined(KJ_I8_MIN)
#define I8_MIN (-127 - 1)
#define I8_MAX (127)
#define I16_MIN (-32767 - 1)
#define I16_MAX (32767)
#define I32_MIN (-2147483647 - 1)
#define I32_MAX (2147483647)
#define I64_MIN (-9223372036854775807 - 1)
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
#define F32_MIN (-3.4028234663852886e+38f)
#define F32_MAX (3.4028234663852886e+38f)
#define F32_EPS (1.1920928955078125e-07f)

#define F64_MIN (-1.7976931348623157e+308)
#define F64_MAX (1.7976931348623157e+308)
#define F64_EPS (2.2204460492503131e-16)
#endif

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
    X(KJ_TYPE_B8, "b8", b8)                                                     \
    X(KJ_TYPE_B32, "b32", b32)

#define KJ_ERR_MAP(X)                                                           \
    X(KJ_ERR_BAD_HANDLE, "Bad Handle")                                          \
    X(KJ_ERR_PERMISSION_DENIED, "Permission Denied")                            \
    X(KJ_ERR_NOT_FOUND, "Not Found")                                            \
    X(KJ_ERR_NOT_EMPTY, "Not Empty")                                            \
    X(KJ_ERR_NO_DEVICE, "No Device")                                            \
    X(KJ_ERR_BROKEN_PIPE, "Broken Pipe")                                        \
    X(KJ_ERR_ALREADY_EXISTS, "Already Exists")                                  \
    X(KJ_ERR_TIMED_OUT, "Timed Out")                                            \
    X(KJ_ERR_PARAM, "Invalid Parameter")                                        \
    X(KJ_ERR_INTERRUPED, "Interrupted")                                         \
    X(KJ_ERR_ILLEGAL_SEEK, "Illegal Seek")                                      \
    X(KJ_ERR_ALLOC, "Allocation Failed")                                        \
    X(KJ_ERR_WOULD_BLOCK, "Would Block")                                        \
    X(KJ_ERR_RANGE, "Out of Range")                                             \
    X(KJ_ERR_BUSY, "Device or Resource Busy")                                   \
    X(KJ_ERR_SYNTAX, "Invalid Syntax")                                          \
    X(KJ_ERR_ADDR_IN_USE, "Address In Use")                                     \
    X(KJ_ERR_ADDR_NOT_AVAILABLE, "Address Not Available")                       \
    X(KJ_ERR_CONN_ABORTED, "Connection Aborted")                                \
    X(KJ_ERR_CONN_REFUSED, "Connection Refused")                                \
    X(KJ_ERR_CONN_RESET, "Connection Reset")                                    \
    X(KJ_ERR_NOT_CONNECTED, "Not Connected")

KJ_ENUM(isize, kjErr) {
    KJ_ERR_UNKNOWN = I8_MIN,
#define KJ_ERR_ENUM(type, name) type,
    KJ_ERR_MAP(KJ_ERR_ENUM)
#undef KJ_ERR_ENUM
    KJ_ERR_COUNT,
    KJ_ERR_NONE = 0
};

#if 0
#if defined(KJ_COMPILER_MSVC)
KJ_GLOBAL __declspec(thread) kjErr KJ__ERRNO = KJ_ERR_NONE;
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
KJ_GLOBAL __thread kjErr KJ__ERRNO = KJ_ERR_NONE;
#endif
#endif

KJ_API const char* kj_err_str(kjErr err);
KJ_API kjErr kj_os_err(void);
KJ_API kjErr kj_err_from_os(i32 err);

#define kj_is_ok(v) ((v) >= KJ_ERR_NONE)
#define kj_is_err(v) ((v) < KJ_ERR_NONE)

/* Process */

KJ_API void kj_process_exit(isize code);

/* System */

KJ_API isize kj_sys_cpu_count();

/* Environment */

KJ_API isize kj_env_var(const char* name, char* out, isize size);
KJ_API isize kj_env_home_dir(char* path, isize size);

/* Memory */

#if defined(kj_realloc) && defined(kj_free)
#elif !defined(kj_realloc) && !defined(kj_free)
#else
#error "kj_realloc and kj_free must be defined."
#endif

#if !defined(kj_alloc)
#define kj_alloc(s) kj_allocator_alloc(&KJ_HEAP_ALLOCATOR, s)
#define kj_zalloc(s) kj_allocator_zalloc(&KJ_HEAP_ALLOCATOR, s)
#define kj_free(d) kj_allocator_free(&KJ_HEAP_ALLOCATOR, d)
#define kj_realloc(d, s) kj_allocator_realloc(&KJ_HEAP_ALLOCATOR, d, s)
#define kj_alloc_aligned(s, a)                                                  \
    kj_allocator_alloc_align(&KJ_HEAP_ALLOCATOR, s, a)
#define kj_alloc_type(t) kj_cast(t, kj_alloc(kj_isize_of(t)))
#endif

typedef struct kjAllocatorHeader {
    isize size;
} kjAllocatorHeader;

typedef struct kjAllocator kjAllocator;

#define KJ_ALLOCATOR_ALLOC_FN(name)                                             \
    void* name(const kjAllocator* a, isize size)
typedef KJ_ALLOCATOR_ALLOC_FN(kjAllocatorAllocFn);
#define KJ_ALLOCATOR_ZALLOC_FN(name)                                            \
    void* name(const kjAllocator* a, isize size)
typedef KJ_ALLOCATOR_ZALLOC_FN(kjAllocatorZallocFn);
#define KJ_ALLOCATOR_FREE_FN(name)                                              \
    void name(const kjAllocator* a, void* data)
typedef KJ_ALLOCATOR_FREE_FN(kjAllocatorFreeFn);
#define KJ_ALLOCATOR_REALLOC_FN(name)                                           \
    void* name(const kjAllocator* a, void* data, isize size)
typedef KJ_ALLOCATOR_REALLOC_FN(kjAllocatorReallocFn);
#define KJ_ALLOCATOR_ALLOC_ALIGNED_FN(name)                                     \
    void* name(const kjAllocator* a, isize size, isize alignment)
typedef KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kjAllocatorAllocAlignedFn);
#define KJ_ALLOCATOR_IS_OWNER_OF_FN(name)                                       \
    void* name(const kjAllocator* a, void* data)
typedef KJ_ALLOCATOR_IS_OWNER_OF_FN(kjAllocatorIsOwnerOfFn);
#define KJ_ALLOCATOR_DESTROY_FN(name)                                           \
    void name(const kjAllocator* a)
typedef KJ_ALLOCATOR_DESTROY_FN(kjAllocatorDestroyFn);

struct kjAllocator {
    u32 flags;
    kjAllocatorAllocFn* alloc;
    kjAllocatorZallocFn* zalloc;
    kjAllocatorFreeFn* free;
    kjAllocatorReallocFn* realloc;
    kjAllocatorAllocAlignedFn* alloc_aligned;
    kjAllocatorIsOwnerOfFn* is_owner_of;
    kjAllocatorDestroyFn* destroy;
};

#define kj_allocator_alloc(a, s)                                                \
    kj_cast(kjAllocator*, (a))->alloc(kj_cast(kjAllocator*, (a)), (s))
#define kj_allocator_zalloc(a, s)                                               \
    kj_cast(kjAllocator*, (a))->zalloc(kj_cast(kjAllocator*, (a)), (s))
#define kj_allocator_free(a, d)                                                 \
    kj_cast(kjAllocator*, (a))->free(kj_cast(kjAllocator*, (a)), (d))
#define kj_allocator_realloc(a, d, s)                                           \
    kj_cast(kjAllocator*, (a))->realloc(kj_cast(kjAllocator*, (a)), (d), (s))
#define kj_allocator_alloc_aligned(a, s, alignment)                             \
    kj_cast(kjAllocator*, (a))->alloc_aligned(                                  \
            kj_cast(kjAllocator*, (a)), (s), (alignment))
#define kj_allocator_is_owner_of(a, d)                                          \
    kj_cast(kjAllocator*, (a))->is_owner_of(kj_cast(kjAllocator*, (a)), (d))
#define kj_allocator_destroy(a)                                                 \
    kj_cast(kjAllocator*, (a))->destroy(kj_cast(kjAllocator*, (a)))
#define kj_allocator_alloc_type(a, t)                                           \
    kj_cast(t, kj_allocator_alloc(a, kj_isize_of(t)))

KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc);
KJ_API KJ_ALLOCATOR_ZALLOC_FN(kj_heap_zalloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_heap_free);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc);
KJ_API KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_heap_alloc_aligned);

KJ_API const kjAllocator KJ_HEAP_ALLOCATOR;

typedef struct kjArenaAllocator {
    kjAllocator allocator;
    u8* data;
    isize size;
    isize used;
    isize offset;
} kjArenaAllocator;

KJ_API kjErr kj_arena_allocator(kjArenaAllocator* a, void* data, isize size);
KJ_API void kj_arena_allocator_reset(kjArenaAllocator* a);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_arena_alloc);
KJ_API KJ_ALLOCATOR_ALLOC_FN(kj_arena_zalloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_arena_free);
KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_arena_realloc);
KJ_API KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_arena_alloc_aligned);
KJ_API KJ_ALLOCATOR_IS_OWNER_OF_FN(kj_arena_is_owner_of);
KJ_API KJ_ALLOCATOR_DESTROY_FN(kj_arena_destroy);

/* Libs */

#if defined(KJ_SYS_WIN32)
typedef HMODULE kjLib;
typedef FARPROC kjLibFn;
#elif defined(KJ_SYS_UNIX)
typedef void* kjLib;
typedef void (*kjLibFn)(void);
#endif
KJ_API kjLib kj_lib_open(const char* path);
KJ_API kjLibFn kj_lib_fn(kjLib* lib, const char* name);
KJ_API void kj_lib_close(kjLib lib);

/* Debug */

KJ_API b32 kj_is_debugger_present();

#define KJ_PRIORITY_MAP(X)                                                      \
    X(KJ_PRIORITY_CRITICAL, "Critical")                                         \
    X(KJ_PRIORITY_ERROR, "Error")                                               \
    X(KJ_PRIORITY_WARN, "Warn")                                                 \
    X(KJ_PRIORITY_INFO, "Info")                                                 \
    X(KJ_PRIORITY_DEBUG, "Debug")                                               \
    X(KJ_PRIORITY_VERBOSE, "Verbose")

KJ_ENUM(i32, kjPriority) {
#define KJ_PRIORITY_ENUM(type, name) type,
    KJ_PRIORITY_MAP(KJ_PRIORITY_ENUM)
#undef KJ_PRIORITY_ENUM
    KJ_PRIORITY_COUNT
};

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

KJ_WARNING_DISABLE_BEGIN()
KJ_WARNING_DISABLE_CLANG("-Wvariadic-macros")
KJ_WARNING_DISABLE_GNU("-Wvariadic-macros")

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

# if !defined(kj_assert)
#if defined(KJ_DISABLE_DEBUG)
#define kj_assert(expr, ...) do { if((!expr)) { kj_unreachable(); } } while(0)
#define kj_panic(...) kj_unreachable()
#else
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
#endif
#endif

#if !defined(kj_check)
#if !defined(KJ_DISABLE_CHECK)
#if defined(KJ_CHECK_ASSERT)
#define kj_check(expr, scope) kj_assert(expr, kj_str_of(expr))
#else
#define kj_check(expr, scope) do { if(!(expr)) { scope } } while(0)
#endif
#else
#define kj_check(expr, scope)
#endif
#endif

KJ_WARNING_DISABLE_END()

#define kj_unimplemented() kj_panic("UNIMPLEMENTED")

/* Endian */

KJ_API u16 kj_byte_swap_u16(u16 a);
KJ_API u32 kj_byte_swap_u32(u32 a);
KJ_API u64 kj_byte_swap_u64(u64 a);

#if !defined(KJ_CC8)
#if KJ_ENDIAN == KJ_LE
#define KJ_CC8(a, b, c, d, e, f, g, h)                                          \
    (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24) |                      \
     ((e) << 32) | ((f) << 40) | ((g) << 48) | ((h) << 56))
#define KJ_CC4(a, b, c, d)                                                      \
    (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#define KJ_CC2(a, b) (((a) << 0) | ((b) << 8))
#define kj_byte_swap_u16_le(a) (a)
#define kj_byte_swap_u32_le(a) (a)
#define kj_byte_swap_u64_le(a) (a)
#define kj_byte_swap_u16_be(a) kj_byte_swap_u16(a)
#define kj_byte_swap_u32_be(a) kj_byte_swap_u32(a)
#define kj_byte_swap_u64_be(a) kj_byte_swap_u64(a)
#else
#define KJ_CC8(a, b, c, d, e, f, g, h)                                          \
    (((h) << 0) | ((g) << 8) | ((f) << 16) | ((e) << 24) |                      \
     ((d) << 32) | ((c) << 40) | ((b) << 48) | ((a) << 56))
#define KJ_CC4(a, b, c, d)                                                      \
    (((d) << 0) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#define KJ_CC2(a, b) (((b) << 0) | ((a) << 8))
#define kj_byte_swap_u16_le(a) kj_byte_swap_u16(a)
#define kj_byte_swap_u32_le(a) kj_byte_swap_u32(a)
#define kj_byte_swap_u64_le(a) kj_byte_swap_u64(a)
#define kj_byte_swap_u16_be(a) (a)
#define kj_byte_swap_u32_be(a) (a)
#define kj_byte_swap_u64_be(a) (a)
#endif
#endif

/* Strings/Characters */

typedef u8 utf8;

KJ_API b32 kj_char_is_eol(const char* s);
KJ_API b32 kj_char_is_whitespace(const char* s);
KJ_API b32 kj_char_is_alpha(const char* s);
KJ_API b32 kj_char_is_digit(const char* s);
KJ_API b32 kj_char_is_alphanum(const char* s);
KJ_API b32 kj_char_is_hex_digit(const char* s);
KJ_API b32 kj_char_is_lower(const char* s);
KJ_API b32 kj_char_is_upper(const char* s);
KJ_API b32 kj_char_is_separator(const char* s);

KJ_API char kj_char_to_lower(const char* c);
KJ_API char kj_char_to_upper(const char* c);

KJ_API isize kj_str_size(const char* s, isize size);
KJ_API isize kj_str_cmp(const char* a, const char* b, isize size);
KJ_API isize kj_str_icmp(const char* a, const char* b, isize size);
KJ_API const char* kj_str_find_char(const char* s, isize size, char c);
KJ_API const char* kj_str_rfind_char(const char* s, isize size, char c);
KJ_API const char* kj_str_find(const char* a, const char* b);
KJ_API b32 kj_str_prefix(const char* s, const char* prefix);
KJ_API b32 kj_str_suffix(const char* s, const char* suffix);
KJ_API char* kj_str_cat(
        char* dst, isize dst_size,
        const char* a, isize a_size,
        const char* b, isize b_size);
KJ_API char* kj_str_copy(char* dst, const char* src, isize src_size);
KJ_API char* kj_str_sub_char(char* s, isize size, char o, char n);
KJ_API char* kj_str_to_lower(char* s, isize size);
KJ_API char* kj_str_to_upper(char* s, isize size);
KJ_API const char* kj_str_trim(const char** end, const char* s, isize size);
KJ_API const char* kj_str_ltrim(const char* s, isize size);
KJ_API const char* kj_str_rtrim(const char* s, isize size);
KJ_API isize kj_u64_from_str(u64* value, const char* s, isize size);
KJ_API isize kj_u32_from_str(u32* value, const char* s, isize size);
KJ_API isize kj_i64_from_str(i64* value, const char* s, isize size);
KJ_API isize kj_i32_from_str(i32* value, const char* s, isize size);
KJ_API isize kj_f64_from_str(f64* value, const char* s, isize size);
KJ_API isize kj_f32_from_str(f32* value, const char* s, isize size);

KJ_API isize kj_utf8_size(const char* s, isize size);
KJ_API isize kj_utf8_char_size(const char* c);

#if !defined(KJ_STACK_BUF_SIZE)
#define KJ_STACK_BUF_SIZE 512
#endif

#if defined(KJ_SYS_WIN32)
KJ_API i32 kj_ucs_from_utf8(WCHAR* ws, i32 wsize, const char* s, i32 size);
KJ_API i32 kj_utf8_from_ucs(char* s, i32 size, const WCHAR* ws, i32 wsize);
KJ_API WCHAR* kj_ucs_from_utf8_alloc(const char* s, i32 size);
KJ_API char* kj_utf8_from_ucs_alloc(const WCHAR* ws, i32 wsize);
KJ_API WCHAR* kj_ucs_from_utf8_malloca(const char* s, i32 size);
KJ_API char* kj_utf8_from_ucs_malloca(const WCHAR* ws, i32 wsize);
KJ_API void kj_ucs_from_utf8_freea(WCHAR* ws);
KJ_API void kj_utf8_from_ucs_freea(char* s);
#endif

typedef char* kjString;

#define KJ_STR_HEADER(s) (kj_cast(kjStringHeader*, (s)) - 1)
#define kj_string_set_size(s, sz) (kj_cast(kjStringHeader*, (s)) - 1)->size = sz

KJ_WARNING_DISABLE_BEGIN()
KJ_WARNING_DISABLE_MSVC(4200)
KJ_WARNING_DISABLE_CLANG("-Wzero-length-array")
KJ_WARNING_DISABLE_GNU("-Wpedantic")
KJ_PACK_BEGIN(1)

typedef struct kjStringHeader {
    const kjAllocator* allocator;
    i16 size;
    i16 capacity;
    char data[0];
} kjStringHeader;

KJ_PACK_END()
KJ_WARNING_DISABLE_END()

KJ_API kjString kj_string(const char* s, i16 size, const kjAllocator* a);
KJ_API void kj_string_destroy(kjString s);
KJ_API void kj_string_reset(kjString s);
KJ_API i16 kj_string_size(kjString s);
KJ_API i16 kj_string_capacity(kjString s);
KJ_API i16 kj_string_available(kjString s);
KJ_API kjString kj_string_end(kjString s);
KJ_API kjString kj_string_extend(kjString s, i16 size);
KJ_API kjString kj_string_resize(kjString s, i16 size);
KJ_API kjString kj_string_append(kjString a, kjString b);
KJ_API kjString kj_string_append_str(kjString a, const char* b, i16 size);
KJ_API kjString kj_string_duplicate(kjString s);
KJ_API kjString kj_string_slice(kjString s, i16 start, i16 end);

/* Sorting */

KJ_ENUM(i32, kjOrdering) {
    KJ_ORDERING_LESS = -1,
    KJ_ORDERING_EQUAL = 0,
    KJ_ORDERING_GREATER = 1
};

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

KJ_API u64 kj_time_raw(void);
KJ_API u64 kj_time_raw_freq(void);
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
    KJ_O_NONBLOCK = KJ_FLAG(6),
    KJ_O_USR_R = KJ_FLAG(22),
    KJ_O_USR_W = KJ_FLAG(23),
    KJ_O_USR_X = KJ_FLAG(24),
    KJ_O_USR_RWX = KJ_O_USR_R | KJ_O_USR_W | KJ_O_USR_X,
    KJ_O_GRP_R = KJ_FLAG(25),
    KJ_O_GRP_W = KJ_FLAG(26),
    KJ_O_GRP_X = KJ_FLAG(27),
    KJ_O_GRP_RWX = KJ_O_GRP_R | KJ_O_GRP_W | KJ_O_GRP_X,
    KJ_O_OTH_R = KJ_FLAG(28),
    KJ_O_OTH_W = KJ_FLAG(29),
    KJ_O_OTH_X = KJ_FLAG(30),
    KJ_O_OTH_RWX = KJ_O_OTH_R | KJ_O_OTH_W | KJ_O_OTH_X,
    KJ_O_INVALID = KJ_FLAG_ALL
};

KJ_ENUM(i32, kjSeekFrom) {
    KJ_SEEK_BEGIN = 0,
    KJ_SEEK_CURRENT = 1,
    KJ_SEEK_END = 2
};

#if defined(KJ_SYS_WIN32)
typedef HANDLE kjFd;
#define KJ_FD_INVALID (INVALID_HANDLE_VALUE)
#define KJ_FD_STDIN STD_INPUT_HANDLE
#define KJ_FD_STDOUT STD_OUTPUT_HANDLE
#define KJ_FD_STDERR STD_ERROR_HANDLE
#elif defined(KJ_SYS_UNIX)
typedef i32 kjFd;
#define KJ_FD_INVALID (-1)
#define KJ_FD_STDIN 0
#define KJ_FD_STDOUT 1
#define KJ_FD_STDERR 2
#endif

KJ_ENUM(i32, kjFileType) {
    KJ_FILE,
    KJ_DIR,
    KJ_SYMLINK
};

typedef struct kjFileMetadata {
    kjFileType type;
    i64 size;
    u64 last_access;
    u64 last_write;
} kjFileMetadata;

KJ_API kjErr kj_file_create(kjFd* fd, const char* path, u32 flags);
KJ_API kjErr kj_file_open(kjFd* fd, const char* path, u32 flags);
KJ_API kjErr kj_file_close(kjFd fd);
KJ_API isize kj_file_seek(kjFd fd, i64 offset, kjSeekFrom seek);
KJ_API isize kj_file_pos(kjFd fd);
KJ_API isize kj_file_read(kjFd fd, void* buf, isize size);
KJ_API isize kj_file_write(kjFd fd, void* buf, isize size);
KJ_API isize kj_file_read_at(kjFd fd, void* buf, isize size, i64 offset);
KJ_API isize kj_file_write_at(kjFd fd, void* buf, isize size, i64 offset);
KJ_API kjErr kj_file_sync(kjFd fd);
KJ_API isize kj_file_path(kjFd fd, char* path, isize size);
KJ_API isize kj_file_map(void** buf, kjFd fd, u32 flags);
KJ_API isize kj_file_map_path(
        void** buf, kjFd* fd, const char* path, u32 flags);
KJ_API kjErr kj_file_unmap(void* buf);

KJ_API isize kj_file_slurp(void** buf, const char* path, const kjAllocator* a);

KJ_API kjErr kj_file_metadata(kjFileMetadata* meta, kjFd fd);
KJ_API kjErr kj_file_metadata_path(kjFileMetadata* meta, const char* path);

/* Paths */

KJ_API const char* kj_path_ext(const char* path, isize size);
KJ_API const char* kj_path_base(const char** end, const char* path, isize size);
KJ_API const char* kj_path_dir(const char** end, const char* path, isize size);
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
    HANDLE dir;
    WIN32_FIND_DATAW ent;
    char buf[MAX_PATH * 2 + 1];
#elif defined(KJ_SYS_UNIX)
    DIR* dir;
    struct dirent* ent;
#endif
} kjReadDir;

KJ_API kjErr kj_read_dir(kjReadDir* dir, const char* path);
KJ_API kjErr kj_read_dir_next(kjReadDir* dir, const char** path);

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

KJ_API isize kj_vdprintf(kjFd fd, const char* fmt, va_list v);
KJ_API isize kj_dprintf(kjFd fd, KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(2);
KJ_API isize kj_vprintf(const char* fmt, va_list v);
KJ_API isize kj_printf(KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(1);
KJ_API isize kj_vsnprintf(char* buf, isize size, const char* fmt, va_list v);
KJ_API isize kj_snprintf(
        char* buf, isize size, KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(3);

#if defined(KJ_SYS_WIN32)
#if !defined(_WINSOCK_DEPRECATED_NO_WARNINGS)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#elif defined(KJ_SYS_LINUX)
#include <netinet/in.h>
#else
#error Unsupported Operating System
#endif

enum {
    KJ_SOCKET_NONE = KJ_FLAG_NONE,
    KJ_SOCKET_LOCAL = KJ_FLAG(0)
};

typedef struct kjSocket {
#if defined(KJ_SYS_WIN32)
    SOCKET handle;
#elif defined(KJ_SYS_LINUX)
    i32 handle;
#endif
    struct sockaddr_in addr;
} kjSocket;

KJ_ENUM(i32, kjSocketAddr) {
    KJ_SOCKET_ADDR_V4,
    KJ_SOCKET_ADDR_V6
};

KJ_API b32 kj_networking_begin(void);
KJ_API void kj_networking_end(void);
KJ_API kjErr kj_socket_open(kjSocket* sock, kjSocketAddr addr);
KJ_API void kj_socket_close(kjSocket* sock);
KJ_API kjErr kj_socket_connect(kjSocket* sock, const char* ip, u16 port);
KJ_API kjErr kj_socket_bind(kjSocket* sock, u16 port, u32 flags);
KJ_API kjErr kj_socket_listen(kjSocket* sock, isize conn);
KJ_API kjErr kj_socket_accept(kjSocket* sock, kjSocket* client);
KJ_API isize kj_socket_read(kjSocket* sock, void* buf, isize size);
KJ_API isize kj_socket_write(kjSocket* sock, const void* buf, isize size);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_IMPL)

KJ_INLINE const char* kj_err_str(kjErr err) {
    switch(err) {
#define KJ_ERR_NAME(type, name) case (type): return (name);
        KJ_ERR_MAP(KJ_ERR_NAME)
#undef KJ_ERR_NAME
        default: return err < 0 ? "Unknown": "None";
    }
}

kjErr kj_err_from_os(i32 err) {
    kjErr res = KJ_ERR_NONE;
    switch(err) {
#if defined(KJ_SYS_WIN32)
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
        case ERROR_INVALID_PARAMETER: res = KJ_ERR_PARAM; break;
        case ERROR_OPERATION_ABORTED: res = KJ_ERR_TIMED_OUT; break;
        case ERROR_SEEK: res = KJ_ERR_ILLEGAL_SEEK; break;
        case ERROR_NEGATIVE_SEEK: res = KJ_ERR_ILLEGAL_SEEK; break;
        case ERROR_SEEK_ON_DEVICE: res = KJ_ERR_ILLEGAL_SEEK; break;
        case ERROR_INSUFFICIENT_BUFFER: res = KJ_ERR_RANGE; break;
        case WSAEBADF: res = KJ_ERR_BAD_HANDLE; break;
        case WSAEACCES: res = KJ_ERR_PERMISSION_DENIED; break;
        case WSAETIMEDOUT: res = KJ_ERR_TIMED_OUT; break;
        case WSAEINVAL: res = KJ_ERR_PARAM; break;
        case WSAEINTR: res = KJ_ERR_INTERRUPED; break;
        case WSAEADDRINUSE: res = KJ_ERR_ADDR_IN_USE; break;
        case WSAEADDRNOTAVAIL: res = KJ_ERR_ADDR_NOT_AVAILABLE; break;
        case WSAECONNABORTED: res = KJ_ERR_CONN_ABORTED; break;
        case WSAECONNREFUSED: res = KJ_ERR_CONN_REFUSED; break;
        case WSAECONNRESET: res = KJ_ERR_CONN_RESET; break;
        case WSAENOTCONN: res = KJ_ERR_NOT_CONNECTED; break;
        case WSAEWOULDBLOCK: res = KJ_ERR_WOULD_BLOCK; break;
#elif defined(KJ_SYS_UNIX)
        case 0: res = KJ_ERR_NONE; break;
        case EBADF: res = KJ_ERR_BAD_HANDLE; break;
        case EPERM: res = KJ_ERR_PERMISSION_DENIED; break;
        case EACCES: res = KJ_ERR_PERMISSION_DENIED; break;
        case EEXIST: res = KJ_ERR_ALREADY_EXISTS; break;
        case EPIPE: res = KJ_ERR_BROKEN_PIPE; break;
        case ENOENT: res = KJ_ERR_NOT_FOUND; break;
        case ENODEV: res = KJ_ERR_NO_DEVICE; break;
        case ENOTEMPTY: res = KJ_ERR_NOT_EMPTY; break;
        case ETIMEDOUT: res = KJ_ERR_TIMED_OUT; break;
        case EINVAL: res = KJ_ERR_PARAM; break;
        case EINTR: res = KJ_ERR_INTERRUPED; break;
        case ESPIPE: res = KJ_ERR_ILLEGAL_SEEK; break;
        case EAGAIN: res = KJ_ERR_WOULD_BLOCK; break;
        case ERANGE: res = KJ_ERR_RANGE; break;
        case ENOMEM: res = KJ_ERR_ALLOC; break;
        case EBUSY: res = KJ_ERR_BUSY; break;
        case EADDRINUSE: res = KJ_ERR_ADDR_IN_USE; break;
        case EADDRNOTAVAIL: res = KJ_ERR_ADDR_NOT_AVAILABLE; break;
        case ECONNABORTED: res = KJ_ERR_CONN_ABORTED; break;
        case ECONNREFUSED: res = KJ_ERR_CONN_REFUSED; break;
        case ECONNRESET: res = KJ_ERR_CONN_RESET; break;
        case ENOTCONN: res = KJ_ERR_NOT_CONNECTED; break;
#endif
        default: res = KJ_ERR_UNKNOWN; break;
    }
    return res;
}

KJ_INLINE kjErr kj_os_err(void) {
    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj_err_from_os(GetLastError());
#elif defined(KJ_SYS_UNIX)
    res = kj_err_from_os(errno);
#endif
    return res;
}

KJ_ALLOCATOR_ALLOC_FN(kj__stub_alloc) {
    kj_unused(a);
    kj_unused(size);
    return NULL;
}

KJ_ALLOCATOR_FREE_FN(kj__stub_free) {
    kj_unused(a);
    kj_unused(data);
}

KJ_ALLOCATOR_REALLOC_FN(kj__stub_realloc) {
    kj_unused(a);
    kj_unused(data);
    kj_unused(size);
    return NULL;
}

KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj__stub_alloc_aligned) {
    kj_unused(a);
    kj_unused(size);
    kj_unused(alignment);
    return NULL;
}

KJ_ALLOCATOR_IS_OWNER_OF_FN(kj__stub_is_owner_of) {
    kj_unused(a);
    kj_unused(data);
    return NULL;
}

KJ_ALLOCATOR_DESTROY_FN(kj__stub_destroy) {
    kj_unused(a);
}

#define KJ__DEFAULT_ALIGNMENT (kj_cast(isize, (2 * kj_isize_of(isize))))
#define KJ__ALIGN_SIZE(s, a) kj_cast(isize, (s) + (a) - 1 + kj_isize_of(isize))
#define KJ__ALLOC_ADDR(p) (kj_cast(isize*, (p)) - 1)
#define KJ__HEADER_ALLOC_ADDR(p) (kj_cast(void*, *KJ__ALLOC_ADDR(p)))

const kjAllocator KJ_HEAP_ALLOCATOR = {
    KJ_TRUE,
    kj_heap_alloc,
    kj_heap_zalloc,
    kj_heap_free,
    kj_heap_realloc,
    kj_heap_alloc_aligned,
    kj__stub_is_owner_of,
    kj__stub_destroy
};

KJ_ALLOCATOR_ALLOC_FN(kj_heap_alloc) {
    return kj_allocator_alloc_aligned(a, size, KJ__DEFAULT_ALIGNMENT);
}

KJ_ALLOCATOR_ZALLOC_FN(kj_heap_zalloc) {
    void* res = kj_allocator_alloc(a, size);
    if(res) {
        kj_mem_zero(res, size);
    }
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_heap_free) {
    kj_unused(a);
    if(data) {
        void* header = KJ__HEADER_ALLOC_ADDR(data);
#if defined(KJ_SYS_WIN32)
        HeapFree(GetProcessHeap(), 0, header);
#elif defined(KJ_SYS_UNIX)
        free(header);
#endif
    }
}

KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc) {
    void* res = NULL;
    if(data == NULL) {
        res = kj_allocator_alloc(a, size);
    } elif(size == 0) {
        kj_allocator_free(a, data);
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

KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_heap_alloc_aligned) {
    kj_unused(a);
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

KJ_ALLOCATOR_ALLOC_FN(kj_arena_alloc) {
    return kj_allocator_alloc_aligned(a, size, KJ__DEFAULT_ALIGNMENT);
}

KJ_ALLOCATOR_ALLOC_FN(kj_arena_zalloc) {
    void* res = kj_allocator_alloc(a, size);
    if(res) {
        kj_mem_zero(kj_cast(u8*, res) - size, size);
    }
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_arena_free) {
    kj_check(a != NULL && data != NULL, {});

    kjArenaAllocator* la = kj_cast(kjArenaAllocator*, a);
    if(data == (la->data + la->offset)) {
        la->used = la->offset;
    }
}

KJ_ALLOCATOR_REALLOC_FN(kj_arena_realloc) {
    kj_check(a != NULL && data != NULL && size > 0, { return NULL; });

    void* res = NULL;
    kjArenaAllocator* la = kj_cast(kjArenaAllocator*, a);
    if((la->data + la->offset) == data) {
        isize new_size = la->used + (size - (la->used - la->offset));
        if(new_size < la->size) {
            la->used = new_size;
            res = data;
        }
    }
    return res;
}

KJ_ALLOCATOR_ALLOC_ALIGNED_FN(kj_arena_alloc_aligned) {
    kj_check(a != NULL && size > 0, { return NULL; });

    void* res = NULL;
    kjArenaAllocator* la = kj_cast(kjArenaAllocator*, a);
    isize new_size = kj_round_to(la->used + size, alignment);
    if(new_size < la->size) {
        la->offset = kj_round_to(la->used, alignment);
        res = kj_cast(void*, la->data + la->offset);
        la->used = new_size;
    }
    return res;
}

KJ_ALLOCATOR_IS_OWNER_OF_FN(kj_arena_is_owner_of) {
    kj_check(a != NULL && data != NULL, { return NULL; });
    kjArenaAllocator* la = kj_cast(kjArenaAllocator*, a);
    void* res = NULL;
    u8* d = kj_cast(u8*, data);
    if(d >= la->data && d <= (la->data + la->size)) {
        res = data;
    }
    return res;
}

KJ_ALLOCATOR_DESTROY_FN(kj_arena_destroy) {
    kj_check(a != NULL, { return; });
    if(a->flags & 0x1) {
        kjArenaAllocator* la = kj_cast(kjArenaAllocator*, a);
        kj_free(la->data);
    }
}

kjErr kj_arena_allocator(kjArenaAllocator* a, void* data, isize size) {
    kj_check(a != NULL && size > 0, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
    a->allocator.alloc = kj_arena_alloc;
    a->allocator.zalloc = kj_arena_zalloc;
    a->allocator.free = kj_arena_free;
    a->allocator.realloc = kj_arena_realloc;
    a->allocator.alloc_aligned = kj_arena_alloc_aligned;
    a->allocator.is_owner_of = kj_arena_is_owner_of;
    if(data) {
        a->data = kj_cast(u8*, data);
        a->allocator.flags = 0x0;
    } else {
        a->data = kj_cast(u8*, kj_realloc(NULL, size));
        a->allocator.flags = 0x1;
        if(!a->data) {
            res = KJ_ERR_ALLOC;
        }
    }
    a->size = size;
    a->used = 0;
    a->offset = 0;
    return res;
}

void kj_arena_allocator_reset(kjArenaAllocator* a) {
    kj_check(a != NULL, { return; });

    a->used = 0;
    a->offset = 0;
}

#if defined(KJ_LIB_IMPL)
#include <dlfcn.h>
kjLib kj_lib_open(const char* path) {
    kj_check(path != NULL, { return NULL; });

    kjLib res = NULL;
#if defined(KJ_SYS_WIN32)
    res = kj_utf8_to_ucs(KJ__WCHAR_BUFA, kj_isize_of(KJ__WCHAR_BUFA), path);
    if(kj_is_ok(res)) {
        void* ptr;
        if((ptr = LoadLibraryW(KJ__WCHAR_BUFA)) != NULL) {
            *lib = ptr;
        } else {
            res = kj_os_err();
        }
    }
#elif defined(KJ_SYS_UNIX)
    res = kj_cast(kjLib, dlopen(path, RTLD_NOW));
#endif
    return res;
}

kjLibFn kj_lib_fn(kjLib* lib, const char* name) {
    kj_check(lib != NULL && name != NULL, { return NULL; });

    kjLibFn res = NULL;
#if defined(KJ_SYS_WIN32)
    res = GetProcAddress(*lib, name);
#elif defined(KJ_SYS_UNIX)
    KJ_WARNING_DISABLE_BEGIN()
    KJ_WARNING_DISABLE_CLANG("-Wpedantic")
    KJ_WARNING_DISABLE_GNU("-Wpedantic")
    res = kj_cast(kjLibFn, dlsym(*lib, name));
    KJ_WARNING_DISABLE_END()
#endif
    return res;
}

void kj_lib_close(kjLib lib) {
    kj_check(lib != NULL, { return; });

#if defined(KJ_SYS_WIN32)
    FreeLibrary(lib);
#elif defined(KJ_SYS_UNIX)
    dlclose(lib);
#endif
}
#endif

KJ_INLINE void kj_process_exit(isize code) {
#if defined(KJ_SYS_WIN32)
    ExitProcess(kj_cast(UINT, code));
#elif defined(KJ_SYS_UNIX)
    syscall(SYS_exit, code);
#endif
}

KJ_INLINE isize kj_sys_cpu_count(void) {
#if defined(KJ_SYS_WIN32)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif defined(KJ_SYS_UNIX)
    isize res = sysconf(_SC_NPROCESSORS_ONLN);
    if(res < 0) { res = 1; }
    return res;
#endif
}

isize kj_env_var(const char* name, char* out, isize size) {
    kj_check(name != NULL, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR buf[KJ_STACK_BUF_SIZE];
    WCHAR* wname = buf;
    if(kj_ucs_from_utf8(buf, kj_isize_of(buf), name, 0) > kj_isize_of(buf)) {
        wname = kj_ucs_from_utf8_alloc(name, 0);
    }
    DWORD wsize = GetEnvironmentVariableW(wname, NULL, 0);
    if(wsize && out) {
        WCHAR buf2[KJ_STACK_BUF_SIZE];
        WCHAR* wbuf = buf2;
        if(wsize > KJ_STACK_BUF_SIZE && (wbuf = kj_cast(WCHAR*, kj_realloc(
                            NULL, wsize * kj_isize_of(WCHAR)))) == NULL) {
            res = KJ_ERR_ALLOC;
        }
        if(wbuf) {
            if(GetEnvironmentVariableW(wname, buf2, wsize)) {
                res = kj_utf8_from_ucs(
                    out, kj_cast(i32, size), buf2, wsize * kj_isize_of(WCHAR));
            } else {
                res = kj_os_err();
            }
        }
    } elif(wsize) {
        res = kj_utf8_from_ucs(NULL, 0, wname, wsize * kj_isize_of(WCHAR));
    } else {
        res = kj_os_err();
    }
    if(wname != buf) {
        kj_free(wname);
    }
#elif defined(KJ_SYS_UNIX)
    const char* env_var = getenv(name);
    if(env_var) {
        res = kj_str_size(env_var, 0);
        if(out && res < size) {
            kj_mem_copy(out, env_var, res);
        }
    } else {
        res = KJ_ERR_NOT_FOUND;
    }
#endif
    return res;
}

KJ_INLINE isize kj_env_home_dir(char* path, isize size) {
    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj_env_var("USERPROFILE", path, size);
#elif defined(KJ_SYS_UNIX)
    res = kj_env_var("HOME", path, size);
    if(kj_is_err(res)) {
        struct passwd* pw = getpwuid(getuid());
        if(pw) {
            res = kj_str_size(pw->pw_dir, 0);
            if(path && res < size) {
                kj_mem_copy(path, pw->pw_dir, res);
            }
        } else {
            res = KJ_ERR_NOT_FOUND;
        }
    }
#endif
    return res;
}

b32 kj_is_debugger_present() {
    static b32 checked = KJ_FALSE;
    static b32 res = KJ_FALSE;
    if(!checked) {
        checked = KJ_TRUE;
#if defined(KJ_SYS_WIN32)
        res = IsDebuggerPresent() ? KJ_TRUE: KJ_FALSE;
#elif defined(KJ_SYS_UNIX)
        res = ptrace(PTRACE_TRACEME, 0, 0, 0) == -1 ? KJ_TRUE: KJ_FALSE;
#endif
    }
    return res;
}

KJ_INLINE const char* kj_priority_str(kjPriority priority) {
    switch(priority) {
#define KJ_LOG_CASE(type, name) case type: return (name);
        KJ_PRIORITY_MAP(KJ_LOG_CASE)
#undef KJ_LOG_CASE
        default: return "Unknown";
    }
}

KJ_LOG_HANDLER(kj_log_handler) {
    kj_unused(file);
    kj_unused(usr);
    va_list v;
    va_start(v, fmt);
    const char* bb = NULL;
    const char* be = NULL;
    bb = kj_path_base(&be, file, 0);
    i32 size = kj_cast(i32, be - bb);
#if defined(KJ_SYS_WIN32)
    char buf[4096];
    kj_mem_zero(buf, kj_isize_of(buf));
    isize used = kj_snprintf(
            buf, 4096, "[%u][%s][%.*s:%ld][%s] ",
            kj_timestamp_utc(), kj_priority_str(priority), size, bb, line, fn);
    used += kj_vsnprintf(buf + used, kj_isize_of(buf) - used, fmt, v);
    if(kj_is_debugger_present()) {
        OutputDebugStringA(buf);
    } else {
        kj_printf("%s", buf);
    }
#else
    kj_dprintf(KJ_FD_STDERR,
            "[%lu][%s][%.*s:%ld][%s] ",
            kj_timestamp_utc(), kj_priority_str(priority), size, bb, line, fn);
    kj_vdprintf(KJ_FD_STDERR, fmt, v);
#endif
    va_end(v);
}

KJ_ASSERT_HANDLER(kj_assert_handler) {
    kj_unused(file);
    kj_unused(usr);
    va_list v;
    va_start(v, fmt);
    const char* bb = NULL;
    const char* be = NULL;
    bb = kj_path_base(&be, file, 0);
    i32 size = kj_cast(i32, be - bb);
#if defined(KJ_SYS_WIN32)
    char buf[4096];
    kj_mem_zero(buf, kj_isize_of(buf));
    isize used = kj_snprintf(
            buf, 4096, "[%u][%.*s:%ld][%s][%s] ",
            kj_timestamp_utc(), size, bb, line, fn, expr);
    used += kj_vsnprintf(buf + used, kj_isize_of(buf) - used, fmt, v);
    if(kj_is_debugger_present()) {
        OutputDebugStringA(buf);
    } else {
        kj_printf("%s", buf);
    }
#else
    kj_dprintf(
            KJ_FD_STDERR, "[%lu][%.*s:%ld][%s][%s] ",
            kj_timestamp_utc(), size, bb, line, fn, expr);
    kj_vdprintf(KJ_FD_STDERR, fmt, v);
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

isize kj_vdprintf(kjFd fd, const char* fmt, va_list v) {
#if defined(KJ_SYS_WIN32)
    kj_unused(fd);
    return kj_vprintf(fmt, v);
#else
    return vdprintf(fd, fmt, v);
#endif
}

isize kj_dprintf(kjFd fd, KJ_FMT_STR const char* fmt, ...) {
    isize res = -1;
    va_list v;
    kj_mem_zero(&v, kj_isize_of(v));
    va_start(v, fmt);
    res = kj_vdprintf(fd, fmt, v);
    va_end(v);
    return res;
}

isize kj_vprintf(const char* fmt, va_list v) {
    return vprintf(fmt, v);
}

isize kj_printf(KJ_FMT_STR const char* fmt, ...) {
    isize res = -1;
    va_list v;
    kj_mem_zero(&v, kj_isize_of(v));
    va_start(v, fmt);
    res = kj_vprintf(fmt, v);
    va_end(v);
    return res;
}

isize kj_vsnprintf(char* buf, isize size, const char* fmt, va_list v) {
    isize res = -1;
#if defined(KJ_COMPILER_MSVC)
    res = _vsnprintf_s(buf, size, _TRUNCATE, fmt, v);
#else
    res = vsnprintf(buf, size, fmt, v);
#endif
    return res;
}

isize kj_snprintf(char* buf, isize size, KJ_FMT_STR const char* fmt, ...) {
    isize res = -1;
    va_list v;
    kj_mem_zero(&v, kj_isize_of(v));
    va_start(v,fmt);
    res = kj_vsnprintf(buf, size, fmt, v);
    va_end(v);
    return res;
}

#if defined(KJ_SYS_WIN32)
KJ_INTERN isize kj__char_compute_known(
        char* out, isize size, DWORD (*fn)(DWORD, WCHAR*, va_list), ...) {
    isize res = KJ_ERR_NONE;
    WCHAR stack[KJ_STACK_BUF_SIZE];
    DWORD n = kj_count_of(stack);
    WCHAR* ptr = stack;
    WCHAR* heap = NULL;
    va_list v;
    va_start(v, fn);
    DWORD req = fn(n, ptr, v);
    if(req == 0) {
        res = kj_os_err();
    } else {
        if(req > n) {
            ptr = kj_cast(WCHAR*, kj_realloc(heap, req * kj_isize_of(WCHAR)));
            if(ptr == NULL) {
                res = KJ_ERR_ALLOC;
            } else {
                heap = ptr;
                req = fn(req, ptr, v);
            }
        }
        res = kj_utf8_from_ucs(
                out, kj_cast(i32, size), ptr, req * kj_isize_of(WCHAR));
    }
    kj_free(heap);
    va_end(v);
    return res;
}
#endif

#if defined(KJ_SYS_WIN32)
#define KJ_CHAR WCHAR
#define KJ_SIZE DWORD

KJ_INTERN DWORD kj__GetModuleFileNameW(
        DWORD n, WCHAR* buf, va_list v) {
    kj_unused(v);
    return GetModuleFileNameW(NULL, buf, n);
}

KJ_INTERN DWORD kj__GetTempPathW(DWORD n, WCHAR* buf, va_list v) {
    kj_unused(v);
    return GetTempPathW(n, buf);
}

KJ_INTERN DWORD kj__GetCurrentDirectoryW(
        DWORD n, WCHAR* buf, va_list v) {
    kj_unused(v);
    return GetCurrentDirectoryW(n, buf);
}

KJ_INTERN DWORD kj__GetFinalPathNameByHandle(
        DWORD n, WCHAR* buf, va_list v) {
    kjFd fd = va_arg(v, kjFd);
    return GetFinalPathNameByHandleW(fd, buf, n, 0);
}
#elif defined(KJ_SYS_UNIX)
#define KJ_CHAR char
#define KJ_SIZE isize

KJ_INTERN isize kj__getcwd(isize n, char* buf, va_list v) {
    kj_unused(v);
    isize res = syscall(SYS_getcwd, buf, n);
    if(res < 0) {
        res = -res;
        if(res != ERANGE) {
            res = 0;
        } elif(res == ERANGE) {
            res = n;
        } else {
            res = kj_str_size(buf, n);
        }
    }
    return res;
}

KJ_INTERN isize kj__readlink(isize n, char* buf, va_list v) {
    char* link = va_arg(v, char*);
    isize res = syscall(SYS_readlink, link, buf, n);
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

KJ_INTERN isize kj__char_compute_unknown(
        char* out, isize size, KJ_SIZE (*fn)(KJ_SIZE, KJ_CHAR*, va_list), ...) {
    isize res = KJ_ERR_NONE;
    KJ_CHAR stack[KJ_STACK_BUF_SIZE];
    KJ_SIZE n = kj_count_of(stack);
    KJ_CHAR* ptr = stack;
    KJ_CHAR* heap = NULL;
    va_list v;
    va_start(v, fn);
    loop {
#if defined(KJ_SYS_WIN32)
        SetLastError(0);
#elif defined(KJ_SYS_UNIX)
        errno = 0;
#endif
        n = fn(n, ptr, v);
        if(n == 0) {
            res = kj_os_err();
            break;
        } elif(kj_os_err() == KJ_ERR_RANGE) {
            n *= 2;
            ptr = kj_cast(KJ_CHAR*, kj_realloc(heap, n * kj_isize_of(KJ_CHAR)));
            if(ptr == NULL) {
                res = KJ_ERR_ALLOC;
                break;
            }
            heap = ptr;
        } else {
#if defined(KJ_SYS_WIN32)
            res = kj_utf8_from_ucs(
                    out, kj_cast(i32, size), ptr, n * kj_isize_of(KJ_CHAR));
#elif defined(KJ_SYS_UNIX)
            res = n;
            if(n <= size) {
                kj_mem_copy(out, ptr, n);
                if(n < size) {
                    out[n] = '\0';
                }
            }
#endif
            break;
        }
    }
    kj_free(heap);
    va_end(v);
    return res;
}

#undef KJ_CHAR
#undef KJ_SIZE

KJ_INLINE b32 kj_char_is_eol(const char* s) {
    return *s == '\r' || *s == '\n' ? KJ_TRUE: KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_whitespace(const char* s) {
    u8 u = *kj_cast(u8*, s);
    return (u == ' '  ||
            u == '\t' ||
            u == '\v' ||
            u == '\f' ||
            u == '\r' ||
            u == '\n' ||
            u == 0x85 ||
            u == 0xA0) ? KJ_TRUE: KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_alpha(const char* s) {
    u8 u = *kj_cast(u8*, s);
    return (u >= 'a' && u <= 'z') ||
            (u >= 'A' && u <='Z') ? KJ_TRUE: KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_digit(const char* s) {
    return (*s >= '0' && *s <= '9') ? KJ_TRUE: KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_alphanum(const char* s) {
    return (*s >= 'a' && *s <= 'z') ||
           (*s >= 'A' && *s <= 'Z') ||
           (*s >= '0' && *s <= '9') ? KJ_TRUE: KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_hex_digit(const char* s) {
    return (*s >= 'a' && *s <= 'f') ||
           (*s >= 'A' && *s <= 'F') ||
           (*s >= '0' && *s <= '9') ? KJ_TRUE: KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_lower(const char* s) {
    u8 u = *kj_cast(u8*, s);
    return
       (u >= 'a' && u <= 'z') ||
        u == 0x83 || u == 0x9A || u == 0x9C || u == 0x9E ||
       (u >= 0xDF && u <= 0xF6) || u >= 0xF8 ? KJ_TRUE: KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_upper(const char* s) {
    u8 u = *kj_cast(u8*, s);
    return
       (u >= 'A' && u <= 'Z') ||
        u == 0x8A || u == 0x8C || u == 0x8E || u == 0x9F ||
       (u >= 0xC0 && u <= 0xD6) || (u >= 0xD8 && u <= 0xDE) ? KJ_TRUE: KJ_FALSE;
}

KJ_INLINE b32 kj_char_is_separator(const char* s) {
#if defined(KJ_SYS_WIN32)
    return (*s == '\\' || *s == '/') ? KJ_TRUE: KJ_FALSE;
#else
    return (*s == '/') ? KJ_TRUE: KJ_FALSE;
#endif
}

KJ_INLINE char kj_char_to_lower(const char* s) {
    return (*s >= 'A' && *s <= 'Z') ? (*s | 0x20): *s;
}

KJ_INLINE char kj_char_to_upper(const char* s) {
    return (*s >= 'a' && *s <= 'z') ? (*s & ~0x20): *s;
}

KJ_INLINE isize kj_str_size(const char* s, isize size) {
    const char* e = s;
    if(size == 0) {
        while(*e) { e++; };
    } else {
        while(*e && size) { e++; size--; };
    }
    return (e - s);
}

KJ_INLINE isize kj_str_cmp(const char* a, const char* b, isize size) {
    if(size == 0) {
        while(*a && *b && *a == *b) { a++; b++; }
    } else {
        if(!size--) return 0;
        while(*a && *b && size && *a == *b) { a++; b++; size--; }
    }
    return *a - *b;
}

KJ_INLINE isize kj_str_icmp(const char* a, const char* b, isize size) {
    if(size == 0) {
        while(*a && *b && kj_char_to_lower(a) == kj_char_to_lower(b)) {
            a++; b++;
        }
    } else {
        if(!size--) return 0;
        while(*a && *b && size && kj_char_to_lower(a) == kj_char_to_lower(b)) {
            a++; b++; size--;
        }
    }
    return *a - *b;
}

KJ_INLINE const char* kj_str_find_char(const char* s, isize size, char c) {
    kj_check(s != NULL && size >= 0, { return NULL; });

    const char* res = NULL;
    if(size == 0) {
        while(*s) { if(*s == c) { res = s; break; } s++; }
    } else {
        const char* e = s + size;
        while(s < e) { if(*s == c) { res = s; break; } s++; }
    }
    return res;
}

KJ_INLINE const char* kj_str_rfind_char(const char* s, isize size, char c) {
    kj_check(s != NULL && size >= 0, { return NULL; });

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

KJ_INLINE const char* kj_str_find(const char* a, const char* b) {
    kj_check(a != NULL && b != NULL, { return NULL; });

    i32 table[256];
    isize a_size = kj_str_size(a, 0);
    isize b_size = kj_str_size(b, 0);
    for(isize i = 0; i < kj_count_of(table); i++) {
        table[i] = b_size;
    }
    for(isize i = 0; i < b_size; i++) {
        table[kj_cast(isize, b[i])] = b_size - 1 - i;
    }

    isize skip = 0;
    while(a_size - skip >= b_size) {
        isize i = b_size - 1;
        while(a[skip + i] == b[i]) {
            if(i == 0) {
                return a + skip;
            }
            i--;
        }
        skip += table[kj_cast(isize, a[skip + b_size - 1])];
    }
    return NULL;
}

//KJ_INLINE const char* kj_str_find(const char* a, const char* b) {
//    kj_check(a != NULL && b != NULL, { return NULL; });
//
//#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
//    return __builtin_strstr(a, b);
//#else
//    const char* s = a;
//    const char* e = b;
//    const char* res = NULL;
//    loop {
//        char cs = *s;
//        char ce = *e;
//        if(!ce) {
//            res = a;
//            break;
//        }
//        if(cs == ce) {
//            s++;
//            e++;
//        } else {
//            e = b;
//            if(!cs) {
//                break;
//            }
//            s = ++a;
//        }
//    }
//    return res;
//#endif
//}

KJ_INLINE b32 kj_str_prefix(const char* s, const char* prefix) {
    kj_check(s != NULL && prefix != NULL, { return KJ_FALSE; });

    while(*prefix) { if(*s++ != *prefix++) { return KJ_FALSE; } }
    return KJ_TRUE;
}

KJ_INLINE b32 kj_str_suffix(const char* s, const char* suffix) {
    kj_check(s != NULL && suffix != NULL, { return KJ_FALSE; });

    isize s_size = kj_str_size(s, 0);
    isize suffix_size = kj_str_size(suffix, 0);
    if(suffix_size <= s_size) {
        return kj_str_cmp(s + s_size - suffix_size, suffix, 0) == 0;
    }
    return KJ_FALSE;
}

KJ_INLINE char* kj_str_sub_char(char* s, isize size, char o, char n) {
    kj_check(s != NULL && size >= 0, { return NULL; });

    char* res = s;
    if(size == 0) {
        while(*res) { if(*res == o) { *res = n; } res++; }
    } else {
        char* e = s + size;
        while(res < e) { if(*res == o) { *res = n; } res++; }
    }
    return res;
}

KJ_INLINE char* kj_str_to_lower(char* s, isize size) {
    kj_check(s != NULL && size >= 0, { return NULL; });

    char* res = s;
    if(size == 0) {
        while(*s) { *s = kj_char_to_lower(s); s++; }
    } else {
        char* e = s + size;
        while(s < e) { *s = kj_char_to_lower(s); s++; }
    }
    return res;
}

KJ_INLINE char* kj_str_to_upper(char* s, isize size) {
    kj_check(s != NULL && size >= 0, { return NULL; });

    char* res = s;
    if(size == 0) {
        while(*s) { *s = kj_char_to_upper(s); s++; }
    } else {
        char* e = s + size;
        while(s < e) { *s = kj_char_to_upper(s); s++; }
    }
    return res;
}

KJ_INLINE char* kj_str_cat(
        char* dst, isize dst_size,
        const char* a, isize a_size,
        const char* b, isize b_size) {
    kj_check(dst != NULL && a != NULL && b != NULL, { return NULL; });

    dst_size = dst_size == 0 ? kj_str_size(dst, 0): dst_size;
    a_size = a_size == 0 ? kj_str_size(a, 0): a_size;
    b_size = b_size == 0 ? kj_str_size(b, 0): b_size;
    isize total_size = a_size + b_size;
    char* res = NULL;
    if(total_size < dst_size) {
        kj_mem_copy(dst, a, a_size);
        kj_mem_copy(dst + a_size, b, b_size);
        dst[a_size + b_size] = '\0';
        res = dst;
    }
    return res;
}

KJ_INLINE char* kj_str_copy(char* dst, const char* src, isize src_size) {
    kj_check(dst != NULL && src != NULL && src_size >= 0, { return NULL; });

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    if(src_size == 0) {
        return __builtin_strcpy(dst, src);
    } else {
        return __builtin_strncpy(dst, src, src_size);
    }
#else
    char* res = dst;
    if(src_size == 0) {
        while((*dst++ = *src++) != '\0') {}
    } else {
        while(src_size > 0 && *dst) { *dst++ = *src++; src_size--; }
        if(src_size > 0) { kj_mem_zero(dst, src_size); }
    }
    return res;
#endif
}

KJ_INLINE const char* kj_str_trim(const char** end, const char* s, isize size) {
    kj_check(s != NULL && end != NULL && size >= 0, { return NULL; });

    const char* res = kj_str_ltrim(s, size);
    *end = kj_str_rtrim(res, size);
    return res;
}

KJ_INLINE const char* kj_str_ltrim(const char* s, isize size) {
    kj_check(s != NULL && size >= 0, { return NULL; });

    const char* res = s;
    if(size == 0) {
        while(!kj_char_is_whitespace(res)) { res++; }
    } else {
        const char* e = s + size;
        while(res < e && kj_char_is_whitespace(res)) { res++; }
    }
    return res;
}

KJ_INLINE const char* kj_str_rtrim(const char* s, isize size) {
    kj_check(s != NULL && size >= 0, { return NULL; });

    size = size == 0 ? kj_str_size(s, 0): size;
    while(size >= 0 && kj_char_is_whitespace(s + size)) { size--; }
    return s + size;
}

isize kj_u64_from_str(u64* value, const char* s, isize size) {
    kj_check(value != NULL || s != NULL || size >= 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
    *value = 0;
    size = size == 0 ? kj_str_size(s, 0): size;
    u64 base = 10;
    if(*s == '0' && size > 1){
        if(kj_str_icmp(s, "0x", 2) == 0) {
            base = 16;
            s += 2;
        } elif(kj_str_icmp(s, "0o", 2) == 0) {
            base = 8;
            s += 2;
        } elif(kj_str_icmp(s, "0b", 2) == 0) {
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
                res++;
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

KJ_INLINE isize kj_u32_from_str(u32* value, const char* s, isize size) {
    kj_check(value != NULL && s != NULL && size >= 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
    u64 u;
    if(kj_is_ok(res = kj_u64_from_str(&u, s, size))) {
        if(u <= U32_MAX) {
            *value = kj_cast(u32, u);
        } else {
            res = KJ_ERR_RANGE;
        }
    }
    return res;
}

isize kj_i64_from_str(i64* value, const char* s, isize size) {
    kj_check(value != NULL && s != NULL && size >= 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
    size = size == 0 ? kj_str_size(s, 0): size;
    i64 sign = 1;
    if(*s == '-') {
        sign = -1;
        s++;
        size--;
    } elif(*s == '+') {
        s++;
        size--;
    }
    u64 u;
    if(kj_is_ok(res = kj_u64_from_str(&u, s, size))) {
        i64 i = kj_cast(i64, u);
        if(i >= I64_MIN && i <= I64_MAX) {
            *value = kj_cast(i64, u) * sign;
        } else {
            res = KJ_ERR_RANGE;
        }
    }
    return res;
}

KJ_INLINE isize kj_i32_from_str(i32* value, const char* s, isize size) {
    kj_check(value != NULL && s != NULL && size >= 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
    i64 i;
    if(kj_is_ok(res = kj_i64_from_str(&i, s, size))) {
        if(i >= I32_MIN && i <= I32_MAX) {
            *value = kj_cast(i32, i);
        } else {
            res = KJ_ERR_RANGE;
        }
    }
    return res;
}

isize kj_f64_from_str(f64* value, const char* s, isize size) {
    kj_check(value != NULL && s != NULL && size >= 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
    *value = 0;
    size = size == 0 ? kj_str_size(s, 0): size;
    i64 sign = 1;
    if(*s == '-') {
        sign = -1;
        s++;
        size--;
        res++;
    } elif(*s == '+') {
        s++;
        size--;
        res++;
    }
    const char* dot = kj_str_find_char(s, size, '.');
    if(dot) {
        isize i;
        for(i = 0; i < size; i++) {
            if(s[i] >= '0' && s[i] <= '9') {
                *value = *value * 10.0 + (s[i] - '0');
            } elif(s[i] == '_') {
                res++;
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

KJ_INLINE isize kj_f32_from_str(f32* value, const char* s, isize size) {
    kj_check(value != NULL && s != NULL && size >= 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
    f64 v;
    if(kj_is_ok(res = kj_f64_from_str(&v, s, size))) {
        if(v >= F32_MIN  && v < F32_MAX) {
            *value = kj_cast(f32, v);
        } else {
            res = KJ_ERR_RANGE;
        }
    }
    return res;
}

KJ_INLINE isize kj_utf8_size(const char* s, isize size) {
    kj_check(s != NULL && size >= 0, { return -1; });

    isize res = 0;
    if(size == 0) {
        while(*s) { if((*s & 0xC0) != 0x80) { res++; } s++; }
    } else {
        const char* e = s + size;
        while(s < e) { if((*s & 0xC0) != 0x80) { res++; } s++; }
    }
    return res;
}

KJ_INLINE isize kj_utf8_char_size(const char* s) {
    u8 u = *kj_cast(u8*, s);
    if(u < 0x80) {
        return 1;
    } elif((u & 0xE0) == 0xC0)  {
        return 2;
    } elif((u & 0xF0) == 0xE0) {
        return 3;
    } elif((u & 0xF8) == 0xF0 && (u <= 0xF4)) {
        return 4;
    }
    return 0;
}

#if defined(KJ_SYS_WIN32)
i32 kj_ucs_from_utf8(WCHAR* ws, i32 wsize, const char* s, i32 size) {
    i32 res = KJ_ERR_NONE;
    i32 count = size == 0 ? -1: size;
    i32 wc = wsize == 0 ? 0: wsize / kj_isize_of(WCHAR);
    res = MultiByteToWideChar(CP_UTF8, 0, s, count, NULL, 0);
    if(res <= wc) {
        MultiByteToWideChar(CP_UTF8, 0, s, count, ws, res);
        if(res < wc) {
            ws[res] = '\0';
        }
    }
    res *= kj_isize_of(WCHAR);
    return res;
}

i32 kj_utf8_from_ucs(char* s, i32 size, const WCHAR* ws, i32 wsize) {
    i32 res = KJ_ERR_NONE;
    i32 wc = wsize == 0 ? -1: wsize / kj_isize_of(WCHAR);
    res = WideCharToMultiByte(CP_UTF8, 0, ws, wc, NULL, 0, NULL, NULL);
    if(res <= size) {
        WideCharToMultiByte(CP_UTF8, 0, ws, wc, s, res, NULL, NULL);
        if(res < size) {
            s[res] = '\0';
        }
    }
    return res;
}

WCHAR* kj_ucs_from_utf8_alloc(const char* s, i32 size) {
    WCHAR* res = NULL;
    i32 count = size == 0 ? -1: size;
    i32 wc = MultiByteToWideChar(CP_UTF8, 0, s, count, NULL, 0);
    if((res = kj_cast(WCHAR*, kj_realloc(
                        NULL, 1 + wc * kj_isize_of(WCHAR)))) != NULL) {
        MultiByteToWideChar(CP_UTF8, 0, s, count, res, wc);
        res[wc] = '\0';
    }
    return res;
}

char* kj_utf8_from_ucs_alloc(const WCHAR* ws, i32 wsize) {
    char* res = NULL;
    i32 wc = wsize == 0 ? -1: wsize / kj_isize_of(WCHAR);
    i32 count = WideCharToMultiByte(CP_UTF8, 0, ws, wc, NULL, 0, NULL, NULL);
    if((res = kj_cast(char*, kj_realloc(NULL, count + 1))) != NULL) {
        WideCharToMultiByte(CP_UTF8, 0, ws, wc, res, count, NULL, NULL);
        res[count] = '\0';
    }
    return res;
}

KJ_GLOBAL KJ_TLS WCHAR KJ__WCHAR_BUF[KJ_STACK_BUF_SIZE];
#define KJ__WCHAR_SIZE kj_isize_of(KJ__WCHAR_BUF) * KJ_STACK_BUF_SIZE

WCHAR* kj_ucs_from_utf8_malloca(const char* s, i32 size) {
    WCHAR* res = KJ__WCHAR_BUF;
    if(kj_ucs_from_utf8(
                KJ__WCHAR_BUF, KJ__WCHAR_SIZE, s, size) > KJ__WCHAR_SIZE) {
        res = kj_ucs_from_utf8_alloc(s, size);
    }
    return res;
}

KJ_GLOBAL KJ_TLS char KJ__CHAR_BUF[KJ_STACK_BUF_SIZE];
#define KJ__CHAR_SIZE kj_isize_of(KJ__CHAR_BUF) * KJ_STACK_BUF_SIZE

char* kj_utf8_from_ucs_malloca(const WCHAR* ws, i32 wsize) {
    char* res = KJ__CHAR_BUF;
    if(kj_utf8_from_ucs(
                KJ__CHAR_BUF, KJ__CHAR_SIZE, ws, wsize) > KJ__CHAR_SIZE) {
        res = kj_utf8_from_ucs_alloc(ws, wsize);
    }
    return res;
}

void kj_ucs_from_utf8_freea(WCHAR* ws) {
    if(ws != KJ__WCHAR_BUF) {
        kj_free(ws);
    }
}

void kj_utf8_from_ucs_freea(char* s) {
    if(s != KJ__CHAR_BUF) {
        kj_free(s);
    }
}
#endif

kjString kj_string(const char* s, i16 size, const kjAllocator* a) {
    kj_check(size >= 0, { return NULL; });

    kjString res = NULL;
    size = size == 0 ? kj_cast(i16, kj_str_size(s, 0)): size;
    a = a ? a: &KJ_HEAP_ALLOCATOR;
    kjStringHeader* header = kj_cast(kjStringHeader*, kj_allocator_alloc(
            a, kj_isize_of(kjStringHeader) + size + 1));
    if(header) {
        header->allocator = a;
        header->size = size;
        header->capacity = size;
        if(s) {
            kj_mem_copy(header->data, s, size);
            header->data[size] = '\0';
        } else {
            kj_mem_zero(header->data, size + 1);
        }
        res = header->data;
    }
    return res;
}

KJ_INLINE void kj_string_destroy(kjString s) {
    kj_check(s != NULL, { return; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    kj_allocator_free(header->allocator, header);
}

KJ_INLINE void kj_string_reset(kjString s) {
    kj_check(s != NULL, { return; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    header->size = 0;
    s[0] = '\0';
}

KJ_INLINE i16 kj_string_size(kjString s) {
    kj_check(s != NULL, { return -1; });

    return KJ_STR_HEADER(s)->size;
}

KJ_INLINE i16 kj_string_capacity(kjString s) {
    kj_check(s != NULL, { return -1; });

    return KJ_STR_HEADER(s)->capacity;
}

KJ_INLINE i16 kj_string_available(kjString s) {
    kj_check(s != NULL, { return -1; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    i16 res = header->capacity - header->size;
    return res;
}

KJ_INLINE kjString kj_string_end(kjString s) {
    kj_check(s != NULL, { return NULL; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    kjString res = s + header->size;
    return res;
}

KJ_INLINE kjString kj_string_extend(kjString s, i16 size) {
    kj_check(s != NULL && size > 0, { return NULL; });

    kjString res = s;
    if(kj_string_available(s) < size) {
        kjStringHeader* header = KJ_STR_HEADER(s);
        const kjAllocator* a = header->allocator;
        i16 cur_size = header->size;
        i16 new_capacity = cur_size + kj_cast(i16, size * 2.0f);

        kjStringHeader* new_header = kj_cast(kjStringHeader*,
                kj_allocator_realloc(
                    a, KJ_STR_HEADER(s),
                    kj_isize_of(kjStringHeader) + new_capacity + 1));
        if(new_header != NULL) {
            res = new_header->data;
            new_header->capacity = new_capacity;
            new_header->size = cur_size;
            new_header->allocator = a;
        } else {
            res = NULL;
        }
    }
    return res;
}

KJ_INLINE kjString kj_string_resize(kjString s, i16 size) {
    return kj_string_extend(s, kj_abs(kj_string_size(s) - size));
}

KJ_INLINE kjString kj_string_append(kjString a, kjString b) {
    return kj_string_append_str(a, b, kj_string_size(b));
}

KJ_INLINE kjString kj_string_append_str(kjString a, const char* b, i16 size) {
    kj_check(a != NULL && b != NULL && size >= 0, { return NULL; });

    kjString res = NULL;
    i16 a_size = kj_string_size(a);
    i16 b_size = size == 0 ? kj_cast(i16, kj_str_size(b, 0)): size;
    res = kj_string_extend(a, size);
    if(res != NULL) {
        kj_mem_copy(res + a_size, b, b_size);
        kjStringHeader* header = KJ_STR_HEADER(res);
        header->size = a_size + b_size;
        res[header->size] = '\0';
    }
    return res;
}

KJ_INLINE kjString kj_string_duplicate(kjString s) {
    kj_check(s != NULL, { return NULL; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    return kj_string(s, header->size, header->allocator);
}

KJ_INLINE kjString kj_string_slice(kjString s, i16 start, i16 end) {
    kj_check(
        s != NULL &&
        start < kj_string_size(s) &&
        end < kj_string_size(s) &&
        start + end < kj_string_size(s), { return NULL; });
    kjStringHeader* header = KJ_STR_HEADER(s);
    kjString res = kj_string(
            header->data + start, end - start, header->allocator);
    return res;
}

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

KJ_INLINE u64 kj_timestamp_utc(void) {
    u64 res = 0;
#if defined(KJ_SYS_WIN32)
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    res = kj__filetime_to_unix(&ft);
#elif defined(KJ_SYS_UNIX)
    time_t t;
    if(syscall(SYS_time, &t) != kj_cast(time_t, -1)) {
        res = kj_cast(u64, t);
    }
#endif
    return res;
}

KJ_INLINE u64 kj_datetime_to_timestamp(kjDateTime dt) {
    u64 res = 0;
#if defined(KJ_SYS_WIN32)
    SYSTEMTIME st;
    kj_mem_zero(&st, kj_isize_of(st));
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
    kj_mem_zero(&tm, kj_isize_of(struct tm));
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

KJ_INLINE kjDateTime kj_datetime_utc(void) {
    kjDateTime res;
#if defined(KJ_SYS_WIN32)
    SYSTEMTIME st;
    kj_mem_zero(&st, kj_isize_of(st));
    GetSystemTime(&st);
    kj__systime_to_datetime(&st, &res);
    res.tz = 0;
#elif defined(KJ_SYS_UNIX)
    time_t t;
    syscall(SYS_time, &t);
    struct tm* tm = gmtime(&t);
    kj__systime_to_datetime(tm, &res);
#endif
    return res;
}

KJ_INLINE kjDateTime kj_datetime_local(void) {
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
    syscall(SYS_time, &t);
    struct tm* tm = localtime(&t);
    kj__systime_to_datetime(tm, &res);
#if defined(_GNU_SOURCE)
    res.tz = -tm->tm_gmtoff / 60;
#endif
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

KJ_INLINE u64 kj_time_raw(void) {
    u64 res = 0;
#if defined(KJ_SYS_WIN32)
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    res = now.QuadPart;
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_CLOCK_MONOTONIC)
    struct timespec now;
    syscall(SYS_clock_gettime, KJ_CLOCK_MONOTONIC, &now);
    res = now.tv_sec * 1000000000 + now.tv_nsec;
#else
    struct timeval now;
    syscall(SYS_gettimeofday, &now, 0);
    res = now.tv_sec * 1000000 + now.tv_usec;
#endif
#endif
    return res;
}

KJ_INLINE u64 kj_time_raw_freq(void) {
    u64 res = 0;
#if defined(KJ_SYS_WIN32)
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    res = freq.QuadPart;
#elif defined(KJ_SYS_UNIX)
#if defined(KJ_CLOCK_MONOTONIC)
    res = 1000000000;
#else
    res = 1000000;
#endif
#endif
    return res;
}

KJ_INLINE u64 kj_time_ms(void) {
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
    syscall(SYS_clock_gettime, KJ_CLOCK_MONOTONIC, &ts);
    return kj_cast(u64, ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#else
    struct timeval tv;
    syscall(SYS_gettimeofday, &tv, NULL);
    return kj_cast(u64, tv.tv_sec * 1000 + tv.tv_usec / 1000);
#endif
#endif
}


KJ_INLINE u32 kj_hash_str(const char* s, isize size) {
    kj_check(s != NULL && size >= 0, { return 0; });

    u32 res = 0;
    isize i;
    for(i = 0; (i < size) || (*s && size == 0); i++) {
        res += (*s++) * (kj_cast(u32, i % U32_MAX) + 119);
    }
    return res;
}

KJ_INLINE kjErr kj_file_create(kjFd* fd, const char* path, u32 flags) {
    flags &= KJ_O_USR_RWX | KJ_O_GRP_RWX | KJ_O_OTH_RWX;
    return kj_file_open(
            fd, path, KJ_O_WRITE | KJ_O_CREATE | KJ_O_TRUNCATE | flags);
}

KJ_INLINE u32 kj__file_access_flags(u32 flags) {
    u32 res = 0;
    u32 read = flags & KJ_O_READ;
    u32 write = flags & KJ_O_WRITE;
    u32 append = flags & KJ_O_APPEND;
    if(read && !write && !append) {
#if defined(KJ_SYS_WIN32)
        res = GENERIC_READ;
#elif defined(KJ_SYS_UNIX)
        res = O_RDONLY;
#endif
    } elif(!read && write && !append) {
#if defined(KJ_SYS_WIN32)
        res = GENERIC_WRITE;
#elif defined(KJ_SYS_UNIX)
        res = O_WRONLY;
#endif
    } elif(read && write && !append) {
#if defined(KJ_SYS_WIN32)
        res = GENERIC_READ | GENERIC_WRITE;
#elif defined(KJ_SYS_UNIX)
        res = O_RDWR;
#endif
    } elif(!read && append) {
#if defined(KJ_SYS_WIN32)
        res = FILE_GENERIC_WRITE & ~FILE_WRITE_DATA;
#elif defined(KJ_SYS_UNIX)
        res = O_WRONLY | O_APPEND;
#endif
    } elif(read && append) {
#if defined(KJ_SYS_WIN32)
        res = GENERIC_READ | (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA);
#elif defined(KJ_SYS_UNIX)
        res = O_RDWR | O_APPEND;
#endif
    }
#if defined(KJ_SYS_UNIX)
    if(flags & KJ_O_NONBLOCK) {
        res |= O_NONBLOCK;
    }
#endif
    return res;
}

KJ_INLINE u32 kj__file_create_flags(u32 flags) {
    u32 res = 0;
    u32 write = flags & KJ_O_WRITE;
    u32 append = flags & KJ_O_APPEND;
    u32 trunc = flags & KJ_O_TRUNCATE;
    u32 create = flags & KJ_O_CREATE;
    u32 create_new = flags & KJ_O_CREATE_NEW;
    if(!write && !append) {
        if(trunc || create || create_new) {
            res = KJ_O_INVALID;
        }
    } elif(append) {
        if(trunc && !create_new) {
            res = KJ_O_INVALID;
        }
    }
    if(res == 0) {
        if(!create && !trunc && !create_new) {
#if defined(KJ_SYS_WIN32)
            res = OPEN_EXISTING;
#elif defined(KJ_SYS_UNIX)
            res = 0;
#endif
        } elif(create && !trunc && !create_new) {
#if defined(KJ_SYS_WIN32)
            res = OPEN_ALWAYS;
#elif defined(KJ_SYS_UNIX)
            res = O_CREAT;
#endif
        } elif(!create && trunc && !create_new) {
#if defined(KJ_SYS_WIN32)
            res = TRUNCATE_EXISTING;
#elif defined(KJ_SYS_UNIX)
            res = O_TRUNC;
#endif
        } elif(create && trunc && !create_new) {
#if defined(KJ_SYS_WIN32)
            res = CREATE_ALWAYS;
#elif defined(KJ_SYS_UNIX)
            res = O_CREAT | O_TRUNC;
#endif
        } elif(create_new) {
#if defined(KJ_SYS_WIN32)
            res = CREATE_NEW;
#elif defined(KJ_SYS_UNIX)
            res = O_CREAT | O_EXCL;
#endif
        }
    }
    return res;
}

kjErr kj_file_open(kjFd* fd, const char* path, u32 flags) {
    kj_check(path != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
    u32 access = kj__file_access_flags(flags);
    u32 create = kj__file_create_flags(flags);
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    *fd = CreateFileW(
            wpath, access, FILE_SHARE_READ | FILE_SHARE_DELETE,
            NULL, create, FILE_ATTRIBUTE_NORMAL, NULL);
    if(*fd == INVALID_HANDLE_VALUE) {
        *fd = KJ_FD_INVALID;
        res = kj_os_err();
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    u32 perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if((*fd = syscall(SYS_open, path, (access | create), perm)) == -1) {
        *fd = KJ_FD_INVALID;
        res = kj_os_err();
    }
#endif
    return res;
}

kjErr kj_file_close(kjFd fd) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!CloseHandle(fd)) {
        res = kj_os_err();
    }
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_close, fd) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_file_seek(kjFd fd, i64 offset, kjSeekFrom seek) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    LARGE_INTEGER li_offset;
    li_offset.QuadPart = offset;
    if(SetFilePointerEx(fd, li_offset, &li_offset, seek) == 0) {
        res = kj_os_err();
    } else {
        res = kj_cast(isize, li_offset.QuadPart);
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_lseek, fd, offset, seek)) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_file_pos(kjFd fd) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    LARGE_INTEGER li_offset;
    li_offset.QuadPart = 0;
    if(SetFilePointerEx(fd, li_offset, &li_offset, KJ_SEEK_CURRENT) == 0) {
        res = kj_os_err();
    } else {
        res = kj_cast(isize, li_offset.QuadPart);
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_lseek, fd, 0, KJ_SEEK_CURRENT)) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_file_read(kjFd fd, void* buf, isize size) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });
    kj_check(buf != NULL && size > 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    DWORD read = 0;
    if(ReadFile(fd, buf, kj_cast(DWORD, size), &read, NULL)) {
        res = read;
    } else {
        res = kj_os_err();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_read, fd, buf, size)) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_file_write(kjFd fd, void* buf, isize size) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });
    kj_check(buf != NULL && size > 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    DWORD wrote = 0;
    if(WriteFile(fd, buf, kj_cast(DWORD, size), &wrote, NULL)) {
        res = wrote;
    } else {
        res = kj_os_err();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_write, fd, buf, size)) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_file_read_at(kjFd fd, void* buf, isize size, i64 offset) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });
    kj_check(buf != NULL && size > 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped;
    kj_mem_zero(&overlapped, kj_isize_of(OVERLAPPED));
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(fd, buf, kj_cast(DWORD, size), &read, &overlapped)) {
        res = read;
    } else {
        res = kj_os_err();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_pread64, fd, buf, size, offset)) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_file_write_at(kjFd fd, void* buf, isize size, i64 offset) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });
    kj_check(buf != NULL && size > 0, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped;
    kj_mem_zero(&overlapped, kj_isize_of(OVERLAPPED));
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(fd, buf, kj_cast(DWORD, size), &wrote, &overlapped)) {
        res = wrote;
    } else {
        res = kj_os_err();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_pwrite64, fd, buf, size, offset)) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

kjErr kj_file_sync(kjFd fd) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!FlushFileBuffers(fd)) {
        res = kj_os_err();
    }
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_fsync, fd) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}


isize kj_file_path(kjFd fd, char* path, isize size) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj__char_compute_known(path, size, kj__GetFinalPathNameByHandle, fd);
#elif defined(KJ_SYS_UNIX)
    char fd_buf[32];
    kj_mem_zero(fd_buf, kj_isize_of(fd_buf));
    kj_snprintf(fd_buf, kj_isize_of(fd_buf), "/proc/self/fd/%d", fd);
    res = kj__char_compute_unknown(path, size, kj__readlink, fd_buf);
#endif
    return res;
}

isize kj_file_map(void** buf, kjFd fd, u32 flags) {
    kj_unused(flags);
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });
    kj_check(buf != NULL, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    kjFileMetadata meta;
    if(kj_is_ok(res = kj_file_metadata(&meta, fd))) {
        kjFd map = CreateFileMappingW(fd, NULL, PAGE_WRITECOPY, 0, 0, NULL);
        if(map == NULL) {
            res = kj_os_err();
        } else {
            if((*buf = MapViewOfFileEx(
                            map, FILE_MAP_COPY, 0, 0, 0, 0)) == NULL) {
                res = kj_os_err();
            } else {
                res = meta.size;
            }
        }
    }
#elif defined(KJ_SYS_UNIX)
    kjFileMetadata meta;
    if(kj_is_ok(res = kj_file_metadata(&meta, fd))) {
        if((*buf = mmap(NULL, meta.size, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
            res = kj_os_err();
        } else {
            res = meta.size;
        }
    }
#endif
    return res;
}

isize kj_file_map_path(void** buf, kjFd* fd, const char* path, u32 flags) {
    kj_check(fd != NULL, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
    if(kj_is_ok(res = kj_file_open(fd, path, KJ_O_READ))) {
        res = kj_file_map(buf, *fd, flags);
    }
    return res;
}

kjErr kj_file_unmap(void* buf) {
    kj_check(buf != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!UnmapViewOfFile(buf)) {
        res = kj_os_err();
    }
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_munmap, buf, 0) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_file_slurp(void** buf, const char* path, const kjAllocator* a) {
    kj_check(buf != NULL && path != NULL, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
    a = a ? a: &KJ_HEAP_ALLOCATOR;
    kjFd fd;
    if(kj_is_ok(res = kj_file_open(&fd, path, KJ_O_READ))) {
        kjFileMetadata meta;
        if(kj_is_ok(res = kj_file_metadata(&meta, fd))) {
            *buf = kj_allocator_alloc(a, meta.size + 1);
            if(*buf) {
                res = kj_file_read(fd, *buf, meta.size);
                kj_cast(char*, *buf)[res] = '\0';
            } else {
                res = KJ_ERR_ALLOC;
            }
        }
    }
    return res;
}

kjErr kj_file_metadata(kjFileMetadata* meta, kjFd fd) {
    kj_check(fd != KJ_FD_INVALID, { return KJ_ERR_BAD_HANDLE; });
    kj_check(meta != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
    kj_mem_zero(meta, kj_isize_of(kjFileMetadata));
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
        res = kj_os_err();
    }
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_mem_zero(&st, kj_isize_of(struct stat));
    if(syscall(SYS_fstat, fd, &st) == -1) {
        res = kj_os_err();
    } else {
        meta->size = st.st_size;
        meta->last_access = kj_cast(u64, st.st_atime);
        meta->last_write = kj_cast(u64, st.st_mtime);
    }
#endif
    return res;
}

kjErr kj_file_metadata_path(kjFileMetadata* meta, const char* path) {
    kj_check(meta != NULL && path != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_UNIX)
    struct stat st;
    kj_mem_zero(&st, kj_isize_of(struct stat));
    if(syscall(SYS_stat, path, &st) == -1) {
        res = kj_os_err();
    } else {
        meta->size = st.st_size;
        meta->last_access = kj_cast(u64, st.st_atime);
        meta->last_write = kj_cast(u64, st.st_mtime);
    }
#else
    kjFd fd;
    if(kj_is_ok(res = kj_file_open(&fd, path, KJ_O_READ))) {
        res = kj_file_metadata(meta, fd);
        kj_file_close(fd);
    }
#endif
    return res;
}

const char* kj_path_ext(const char* path, isize size) {
    kj_check(path != NULL && size >= 0, { return NULL; });

    const char* res = NULL;
    size = size == 0 ? kj_str_size(path, 0): size;
    if(path[size - 1] != '.') {
        isize i;
        for(i = size - 1; i >= 0; i--) {
            if(kj_char_is_separator(path + i)) {
                break;
            } elif(path[i] == '.' &&
                   i > 0 &&
                   !kj_char_is_separator(path + i - 1)) {
                res = &path[i + 1];
                break;
            }
        }
    }
    return res;
}

const char* kj_path_base(const char** end, const char* path, isize size) {
    kj_check(path != NULL && size >= 0 && end != NULL, { return "."; });

    const char* res = NULL;
    size = size == 0 ? kj_str_size(path, 0): size;
    if(size == 0) {
        res = ".";
    } elif(size == 1) {
        res = path;
        *end = path + size;
    } else {
        size = kj_char_is_separator(path + size - 1) ? size - 1: size;
        res = kj_str_rfind_char(path, size, KJ_PATH_SEPARATOR);
#if defined(KJ_SYS_WIN32)
        if(res == NULL) {
            res = kj_str_rfind_char(path, size, '/');
        }
#endif
        res = res == NULL ? path: res + 1;
        *end = &path[size] == res ? path + size + 1: path + size;
    }
    return res;
}

const char* kj_path_dir(const char** end, const char* path, isize size) {
    kj_check(path != NULL && size >= 0 && end != NULL, { return "."; });

    const char* res = NULL;
    size = size == 0 ? kj_str_size(path, 0): size;
    size = kj_char_is_separator(path + size - 1) ? size - 1: size;
    *end = kj_str_rfind_char(path, size, KJ_PATH_SEPARATOR);
#if defined(KJ_SYS_WIN32)
    if(*end == NULL) {
        *end = kj_str_rfind_char(path, size, '/');
    }
#endif
    if(kj_char_is_separator(path)) {
        *end = *end == path ? *end + 1: *end;
        res = path;
    } else {
        res = *end ? path: ".";
        *end = *end == NULL ? res + 1: *end;
    }
    return res;
}

kjErr kj_path_create_dir(const char* path) {
    kj_check(path != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    if(CreateDirectoryW(wpath, NULL) == FALSE) {
        res = kj_os_err();
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    u32 mode = S_IRWXU | S_IRGRP | S_IROTH;
    if(syscall(SYS_mkdir, path, mode) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

kjErr kj_path_remove_dir(const char* path) {
    kj_check(path != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    if(RemoveDirectoryW(wpath) == FALSE) {
        res = kj_os_err();
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_rmdir, path) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

kjErr kj_path_rename(const char* from, const char* to) {
    kj_check(from != NULL && to != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wfrom = kj_ucs_from_utf8_malloca(from, 0);
    WCHAR* wto = kj_ucs_from_utf8_malloca(to, 0);
    if(MoveFileExW(wfrom, wto, MOVEFILE_REPLACE_EXISTING) == FALSE) {
        res = kj_os_err();
    }
    kj_ucs_from_utf8_freea(wfrom);
    kj_ucs_from_utf8_freea(wto);
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_rename, from, to) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_path_current_dir(char* path, isize size) {
    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj__char_compute_known(path, size, kj__GetCurrentDirectoryW);
#elif defined(KJ_SYS_UNIX)
    res = kj__char_compute_unknown(path, size, kj__getcwd);
#endif
    return res;
}

kjErr kj_path_set_current_dir(const char* path) {
    kj_check(path != NULL, { return KJ_ERR_PARAM; });

    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    if(SetCurrentDirectoryW(wpath) == FALSE) {
        res = kj_os_err();
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_chdir, path) == -1) {
        res = kj_os_err();
    }
#endif
    return res;
}

isize kj_path_tmp_dir(char* path, isize size) {
    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj__char_compute_unknown(path, size, kj__GetTempPathW);
#elif defined(KJ_SYS_UNIX)
    res = kj_env_var("TMPDIR", path, size);
#endif
    return res;
}

isize kj_path_self(char* path, isize size) {
    isize res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    res = kj__char_compute_unknown(path, size, kj__GetModuleFileNameW);
#elif defined(KJ_SYS_UNIX)
    res = kj__char_compute_unknown(path, size, kj__readlink, "/proc/self/exe");
#endif
    return res;
}

b32 kj_path_exists(const char* path) {
    kj_check(path != NULL, { return KJ_FALSE; });

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    HANDLE h = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAW find;
    if((h = FindFirstFileW(wpath, &find)) != INVALID_HANDLE_VALUE) {
        FindClose(h);
        res = KJ_TRUE;
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_access, path, 0) == 0) {
        res = KJ_TRUE;
    }
#endif
    return res;
}

b32 kj_path_is_file(const char* path) {
    kj_check(path != NULL, { return KJ_FALSE; });

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    DWORD attr = INVALID_FILE_ATTRIBUTES;
    if((attr = GetFileAttributesW(wpath)) != INVALID_FILE_ATTRIBUTES) {
        res = attr & FILE_ATTRIBUTE_DIRECTORY ? KJ_FALSE: KJ_TRUE;
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_mem_zero(&st, kj_isize_of(struct stat));
    if(syscall(SYS_stat, path, &st) == 0) {
        res = S_ISREG(st.st_mode) != 0;
    }
#endif
    return res;
}

b32 kj_path_is_dir(const char* path) {
    kj_check(path != NULL, { return KJ_FALSE; });

    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    DWORD attr = INVALID_FILE_ATTRIBUTES;
    if((attr = GetFileAttributesW(wpath)) != INVALID_FILE_ATTRIBUTES) {
        res = attr & FILE_ATTRIBUTE_DIRECTORY ? KJ_TRUE: KJ_FALSE;
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_mem_zero(&st, kj_isize_of(struct stat));
    if(syscall(SYS_stat, path, &st) == 0) {
        res = S_ISDIR(st.st_mode) != 0;
    }
#endif
    return res;
}

kjErr kj_read_dir(kjReadDir* dir, const char* path) {
    kj_check(dir != NULL && path != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    kj_unused(dir);
    kj_unused(path);
#elif defined(KJ_SYS_UNIX)
    dir->dir = opendir(path);
    if(dir->dir) {
        dir->ent = NULL;
    } else {
        dir->ent = NULL;
        res = kj_os_err();
    }
#endif
    return res;
}

kjErr kj_read_dir_next(kjReadDir* dir, const char** path) {
    kj_check(dir != NULL && path != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    kj_unused(dir);
    kj_unused(path);
#elif defined(KJ_SYS_UNIX)
    dir->ent = readdir(dir->dir);
    if(dir->ent) {
        *path = dir->ent->d_name;
    } else {
        *path = NULL;
        closedir(dir->dir);
    }
#endif
    return res;
}

#endif

#if defined(KJ_NETWORKING_IMPL)

#if defined(KJ_SYS_LINUX)
#include <arpa/inet.h>
#include <unistd.h>

typedef i32 SOCKET;

enum {
    INVALID_SOCKET = -1,
    SOCKET_ERROR = -1
};
#endif

b32 kj_networking_begin(void) {
    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    WSADATA wsa;
    if(WSAStartup(0x202, &wsa) == NO_ERROR) {
        res = KJ_TRUE;
    }
#elif defined(KJ_SYS_LINUX)
    res = KJ_TRUE;
#endif
    return res;
}

void kj_networking_end(void) {
#if defined(KJ_SYS_WIN32)
    WSACleanup();
#elif defined(KJ_SYS_LINUX)
#endif
}

kjErr kj_socket_open(kjSocket* sock, kjSocketAddr addr) {
    kj_check(sock != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
    i32 type = addr == KJ_SOCKET_ADDR_V4 ? AF_INET: AF_INET6;
    if((sock->handle = socket(
                    type, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        res = kj_os_err();
    }
    return res;
}

void kj_socket_close(kjSocket* sock) {
    if(sock == NULL || sock->handle == INVALID_SOCKET) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    closesocket(sock->handle);
#elif defined(KJ_SYS_LINUX)
    close(sock->handle);
#endif
}

kjErr kj_socket_connect(kjSocket* sock, const char* ip, u16 port) {
    kj_check(sock != NULL && ip != NULL, { return KJ_ERR_PARAM; });

    kjErr res = KJ_ERR_NONE;
    kj_mem_zero(&sock->addr, kj_isize_of(struct sockaddr_in));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = inet_addr(ip);
    sock->addr.sin_port = htons(port);

    if(connect(sock->handle,
                kj_cast(struct sockaddr*, &sock->addr),
                kj_isize_of(struct sockaddr_in)) == SOCKET_ERROR) {
        res = kj_os_err();
        kj_socket_close(sock);
    }
    return res;
}

kjErr kj_socket_bind(kjSocket* sock, u16 port, u32 flags) {
    kj_check(sock != NULL && sock->handle != INVALID_SOCKET, {
            return KJ_ERR_PARAM;
    });

    kjErr res = KJ_ERR_NONE;
    kj_mem_zero(&sock->addr, kj_isize_of(struct sockaddr_in));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = htonl(
            flags & KJ_SOCKET_LOCAL ? INADDR_LOOPBACK: INADDR_ANY);
    sock->addr.sin_port = htons(port);
    i32 reuse = 1;
#if defined(KJ_SYS_WIN32)
    setsockopt(
            sock->handle, SOL_SOCKET, SO_REUSEADDR,
            kj_cast(char*, &reuse), kj_isize_of(i32));
    reuse = 1;
    setsockopt(
            sock->handle, SOL_SOCKET, SO_EXCLUSIVEADDRUSE,
            kj_cast(char*, &reuse), kj_isize_of(i32));
#elif defined(KJ_SYS_LINUX)
    setsockopt(
            sock->handle, SOL_SOCKET, SO_REUSEADDR, &reuse, kj_isize_of(i32));
#endif
    if(bind(sock->handle,
                kj_cast(struct sockaddr*, &sock->addr),
                kj_isize_of(struct sockaddr_in)) == SOCKET_ERROR) {
        res = kj_os_err();
        kj_socket_close(sock);
    }
    return res;
}

kjErr kj_socket_listen(kjSocket* sock, isize conn) {
    kj_check(sock != NULL && sock->handle != INVALID_SOCKET && conn > 0, {
        return KJ_ERR_PARAM;
    });

    kjErr res = KJ_ERR_NONE;
    if(listen(sock->handle, kj_min(conn, SOMAXCONN)) == SOCKET_ERROR) {
        res = kj_os_err();
        kj_socket_close(sock);
    }
    return res;
}

kjErr kj_socket_accept(kjSocket* sock, kjSocket* client) {
    kj_check(sock != NULL && sock->handle != INVALID_SOCKET && client != NULL, {
        return KJ_ERR_PARAM;
    });

    kjErr res = KJ_ERR_NONE;
    SOCKET s;
    if((s = accept(sock->handle, NULL, NULL)) == SOCKET_ERROR) {
        res = kj_os_err();
        kj_socket_close(sock);
    } else {
        kj_mem_zero(client, kj_isize_of(kjSocket));
        client->handle = s;
    }
    return res;
}

isize kj_socket_read(kjSocket* sock, void* buf, isize size) {
    kj_check(
        sock != NULL && sock->handle != INVALID_SOCKET &&
        buf != NULL && size > 0, {
        return KJ_ERR_PARAM;
    });

    isize res = KJ_ERR_NONE;
    res = recv(
            sock->handle,
#if defined(KJ_SYS_WIN32)
            kj_cast(char*, buf),
            kj_cast(i32, size),
#elif defined(KJ_SYS_LINUX)
            buf,
            size,
#endif
            0);
    if(res == SOCKET_ERROR) {
        res = kj_os_err();
    }
    return res;
}

isize kj_socket_write(kjSocket* sock, const void* buf, isize size) {
    kj_check(
        sock != NULL && sock->handle != INVALID_SOCKET &&
        buf != NULL && size > 0, {
        return KJ_ERR_PARAM;
    });

    isize res = KJ_ERR_NONE;
    res = send(
            sock->handle,
#if defined(KJ_SYS_WIN32)
            kj_cast(const char*, buf),
            kj_cast(i32, size),
#elif defined(KJ_SYS_LINUX)
            buf,
            size,
#endif
            0);
    if(res == SOCKET_ERROR) {
        res = kj_os_err();
    }
    return res;
}

#endif
