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
#define KJ_VERSION_MINOR 12
#define KJ_VERSION_PATCH 0

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_X86
#define KJ_ARCH_NAME x86_64
#define KJ_ARCH_CACHE_LINE_SIZE 64
#elif defined(__i386__) || defined(_M_IX86) || defined(_X86_)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_X86
#define KJ_ARCH_NAME x86
#define KJ_ARCH_CACHE_LINE_SIZE 64
#elif defined(__aarch64__)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_ARM
#define KJ_ARCH_NAME arm64
#define KJ_ARCH_CACHE_LINE_SIZE 64
#elif defined(__arm__) || defined(_M_ARM)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_ARM
#define KJ_ARCH_NAME arm
#define KJ_ARCH_CACHE_LINE_SIZE 64
#elif defined(__mips__)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_MIPS
#define KJ_ARCH_NAME mips
#define KJ_ARCH_CACHE_LINE_SIZE 64
#elif defined(__ppc64__) || defined(__powerpc64__)
#define KJ_ARCH_64_BIT
#define KJ_ARCH_PPC
#define KJ_ARCH_NAME ppc64
#define KJ_ARCH_CACHE_LINE_SIZE 128
#elif defined(_M_PPC) || defined(__powerpc__)
#define KJ_ARCH_32_BIT
#define KJ_ARCH_PPC
#define KJ_ARCH_NAME ppc
#define KJ_ARCH_CACHE_LINE_SIZE 128
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
#define KJ_COMPILER_MSVC
#define KJ_COMPILER_NAME msvc
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
#define KJ_COMPILER_CLANG
#define KJ_COMPILER_NAME clang
#define KJ_WARNING_DISABLE_BEGIN() _Pragma("clang diagnostic push")
#define KJ_WARNING_DISABLE_END() _Pragma("clang diagnostic pop")
#define KJ_WARNING_DISABLE_CLANG(w) _Pragma(kj_str_of(clang diagnostic ignored w))
#elif defined(__GNUC__) || defined(__GNUG__)
#if !defined(va_start)
typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif
#define KJ_COMPILER_GNU
#define KJ_COMPILER_NAME gnu
#define KJ_WARNING_DISABLE_BEGIN() _Pragma("GCC diagnostic push")
#define KJ_WARNING_DISABLE_END() _Pragma("GCC diagnostic pop")
#define KJ_WARNING_DISABLE_GNU(w) _Pragma(kj_str_of(GCC diagnostic ignored w))
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
#else
#define KJ_C
#endif

#if defined(__STDC_VERSION__)
#if __STDC_VERSION__ >= 201112L
#define KJ_C11
#endif
#if __STDC_VERSION__ >= 199901L
#define KJ_C99
#endif
#endif

#define KJ_ENUM(type, name) typedef type name; enum _kj_##type##name

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
#define kj_lerp(min, max, t) (((t) * ((max) - (min))) + (min))
#define kj_map_range(a, fmin, fmax, tmin, tmax) ((((a) - (fmin)) * ((tmax) - (tmin))) / ((fmin) - (fmax) - (tmin)))
#define kj_swap(T, a, b) do { T tmp_##__LINE__ = a; (a) = b; (b) = tmp_##__LINE__; } while(0)
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
#define kj_mem_set(ptr, size, value) __builtin_memset((ptr), (value), (size))
#define kj_mem_zero(ptr, size) kj_mem_set((ptr), (size), 0x00)
#define kj_mem_move __builtin_memmove
#endif

#define kj_mem_fill(p, s) kj_mem_set(p, s, 0xFF)
#endif

#if defined(KJ_C11)
#define KJ_STATIC_ASSERT(expr) _Static_assert(expr, kj_str_of(expr))
#elif defined(KJ_CPP11)
#define KJ_STATIC_ASSERT(expr) static_assert(expr, kj_str_of(expr))
#else
#define KJ_STATIC_ASSERT(expr) typedef void* kj_join(KJ_STATIC_ASSERT_, __LINE__)[(expr) * 2 - 1]
#endif

/* Types */

#if defined(KJ_COMPILER_MSVC)
typedef signed __int8 i8;
typedef unsigned __int8 u8;
typedef signed __int16 i16;
typedef unsigned __int16 u16;
typedef signed __int32 i32;
typedef unsigned __int32 u32;
typedef signed __int64 i64;
typedef unsigned __int64 u64;
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
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

#define KJ_TYPE_MAP(X)                                                                                                  \
    X(KJ_TYPE_CHAR, "char", char)                                                                                       \
    X(KJ_TYPE_I8, "i8", i8)                                                                                             \
    X(KJ_TYPE_U8, "u8", u8)                                                                                             \
    X(KJ_TYPE_I16, "i16", i16)                                                                                          \
    X(KJ_TYPE_U16, "u16", u16)                                                                                          \
    X(KJ_TYPE_I32, "i32", i32)                                                                                          \
    X(KJ_TYPE_U32, "u32", u32)                                                                                          \
    X(KJ_TYPE_I64, "i64", i64)                                                                                          \
    X(KJ_TYPE_U64, "u64", u64)                                                                                          \
    X(KJ_TYPE_ISIZE, "isize", isize)                                                                                    \
    X(KJ_TYPE_USIZE, "usize", usize)                                                                                    \
    X(KJ_TYPE_F32, "f32", f32)                                                                                          \
    X(KJ_TYPE_F64, "f64", f64)                                                                                          \
    X(KJ_TYPE_B8, "b8", b8)                                                                                             \
    X(KJ_TYPE_B32, "b32", b32)

#define KJ_ERROR_MAP(X)                                                                                                 \
    X(KJ_ERROR_UNKNOWN, -1, "Unknown")                                                                                  \
    X(KJ_ERROR_BAD_HANDLE, -2, "Bad Handle")                                                                            \
    X(KJ_ERROR_PERMISSION_DENIED, -3, "Permission Denied")                                                              \
    X(KJ_ERROR_NOT_FOUND, -4, "Not Found")                                                                              \
    X(KJ_ERROR_NOT_EMPTY, -5, "Not Empty")                                                                              \
    X(KJ_ERROR_NO_DEVICE, -6, "No Device")                                                                              \
    X(KJ_ERROR_BROKEN_PIPE, -7, "Broken Pipe")                                                                          \
    X(KJ_ERROR_ALREADY_EXISTS, -8, "Already Exists")                                                                    \
    X(KJ_ERROR_TIMED_OUT, -9, "Timed Out")                                                                              \
    X(KJ_ERROR_PARAM, -10, "Invalid Parameter")                                                                         \
    X(KJ_ERROR_INTERRUPED, -11, "Interrupted")                                                                          \
    X(KJ_ERROR_ILLEGAL_SEEK, -12, "Illegal Seek")                                                                       \
    X(KJ_ERROR_ALLOC, -13, "Allocation Failed")                                                                         \
    X(KJ_ERROR_WOULD_BLOCK, -14, "Would Block")                                                                         \
    X(KJ_ERROR_RANGE, -15, "Out of Range")                                                                              \
    X(KJ_ERROR_BUSY, -16, "Device or Resource Busy")                                                                    \
    X(KJ_ERROR_SYNTAX, -17, "Invalid Syntax")                                                                           \
    X(KJ_ERROR_ADDR_IN_USE, -18, "Address In Use")                                                                      \
    X(KJ_ERROR_ADDR_NOT_AVAILABLE, -19, "Address Not Available")                                                        \
    X(KJ_ERROR_CONN_ABORTED, -20, "Connection Aborted")                                                                 \
    X(KJ_ERROR_CONN_REFUSED, -21, "Connection Refused")                                                                 \
    X(KJ_ERROR_CONN_RESET, -22, "Connection Reset")                                                                     \
    X(KJ_ERROR_NOT_CONNECTED, -23, "Not Connected")

typedef enum kjResult {
#define KJ_ERROR_ENUM(type, value, name) type = value,
    KJ_ERROR_MAP(KJ_ERROR_ENUM)
#undef KJ_ERROR_ENUM
    KJ_SUCCESS = 0
} kjResult;

#if 0
#if defined(KJ_COMPILER_MSVC)
extern __declspec(thread) kjResult _KJ_ERRNO = KJ_SUCCESS;
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
extern __thread kjResult _KJ_ERRNO = KJ_SUCCESS;
#endif
#endif

KJ_API const char* kj_result_str(kjResult result);
KJ_API kjResult kj_os_error(void);
KJ_API kjResult kj_error_from_os(i32 err);

#define kj_is_success(v) ((v) >= KJ_SUCCESS)
#define kj_is_error(v) (!kj_is_success((v)))

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

/* Process */

KJ_API void kj_process_exit(u32 code);

/* System */

KJ_API isize kj_sys_cpu_count(void);

/* Environment */

KJ_API isize kj_env_var(const char* name, char* out, isize size);
KJ_API isize kj_env_home_dir(char* path, isize size);

/* Debug */

KJ_API b32 kj_debugger_attached(void);

/* Memory */

KJ_API void* kj_ptr_align(void* ptr, isize alignment);
KJ_API isize kj_ptr_align_offset(void* ptr, isize alignment);
KJ_API isize kj_ptr_align_offset_sized(void* ptr, isize alignment, isize size);

#if defined(kj_realloc) && defined(kj_free)
#elif !defined(kj_realloc) && !defined(kj_free)
#else
#error "kj_realloc and kj_free must be defined."
#endif

#if !defined(kj_realloc)
#define kj_alloc(s) kj_allocator_realloc(KJ_HEAP_ALLOCATOR, NULL, s)
#define kj_free(d) kj_allocator_free(KJ_HEAP_ALLOCATOR, (d))
#define kj_realloc(d, s) kj_allocator_realloc(KJ_HEAP_ALLOCATOR, (d), (s))
#endif

enum {
    KJ_ALLOCATOR_NONE = KJ_FLAG_NONE,
    KJ_ALLOCATOR_OWNER = KJ_FLAG(0)
};

typedef struct kjAllocationHeader {
    isize size;
} kjAllocationHeader;

typedef struct kjAllocator kjAllocator;

#if defined(KJ_DISABLE_DEBUG)
#define KJ_ALLOCATOR_FREE_FN(name) void name(kjAllocator* a, void* data)
typedef KJ_ALLOCATOR_FREE_FN(kjAllocatorFreeFn);
#define KJ_ALLOCATOR_REALLOC_FN(name) void* name(kjAllocator* a, void* data, isize size)
typedef KJ_ALLOCATOR_REALLOC_FN(kjAllocatorReallocFn);
#define KJ_ALLOCATOR_DESTROY_FN(name) void name(kjAllocator* a)
typedef KJ_ALLOCATOR_DESTROY_FN(kjAllocatorDestroyFn);
#else
#define KJ_ALLOCATOR_FREE_FN(name) void name(kjAllocator* a, void* data, const char* file, isize line)
typedef KJ_ALLOCATOR_FREE_FN(kjAllocatorFreeFn);
#define KJ_ALLOCATOR_REALLOC_FN(name) void* name(kjAllocator* a, void* data, isize size, const char* file, isize line)
typedef KJ_ALLOCATOR_REALLOC_FN(kjAllocatorReallocFn);
#define KJ_ALLOCATOR_DESTROY_FN(name) void name(kjAllocator* a, const char* file, isize line)
typedef KJ_ALLOCATOR_DESTROY_FN(kjAllocatorDestroyFn);
#endif

struct kjAllocator {
    u32 flags;
    kjAllocatorReallocFn* realloc;
    kjAllocatorFreeFn* free;
    kjAllocatorDestroyFn* destroy;
};

#if defined(KJ_DISABLE_DEBUG)
#define kj_allocator_alloc(a, s) kj_cast(kjAllocator*, (a))->realloc(kj_cast(kjAllocator*, (a)), NULL, (s))
#define kj_allocator_realloc(a, d, s) kj_cast(kjAllocator*, (a))->realloc(kj_cast(kjAllocator*, (a)), (d), (s))
#define kj_allocator_free(a, d) kj_cast(kjAllocator*, (a))->free(kj_cast(kjAllocator*, (a)), (d))
#define kj_allocator_destroy(a) kj_cast(kjAllocator*, (a))->destroy(kj_cast(kjAllocator*, (a)))
#else
#define kj_allocator_alloc(a, s)                                                                                        \
    kj_cast(kjAllocator*, (a))->realloc(kj_cast(kjAllocator*, (a)), NULL, (s), __FILE__, __LINE__)
#define kj_allocator_realloc(a, d, s)                                                                                   \
    kj_cast(kjAllocator*, (a))->realloc(kj_cast(kjAllocator*, (a)), (d), (s), __FILE__, __LINE__)
#define kj_allocator_free(a, d) kj_cast(kjAllocator*, (a))->free(kj_cast(kjAllocator*, (a)), (d), __FILE__, __LINE__)
#define kj_allocator_destroy(a) kj_cast(kjAllocator*, (a))->destroy(kj_cast(kjAllocator*, (a)), __FILE__, __LINE__)
#endif

KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_heap_free);

KJ_API kjAllocator* KJ_HEAP_ALLOCATOR;

typedef struct kjArenaAllocator {
    kjAllocator allocator;
    u8* data;
    isize size;
    isize used;
    isize offset;
} kjArenaAllocator;

KJ_API kjResult kj_arena_allocator(kjArenaAllocator* a, void* data, isize size);
KJ_API void kj_arena_allocator_reset(kjArenaAllocator* a);

KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_arena_realloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_arena_free);
KJ_API KJ_ALLOCATOR_DESTROY_FN(kj_arena_destroy);

typedef struct kjFreelistBlock kjFreelistBlock;

struct kjFreelistBlock {
    isize size;
    kjFreelistBlock* next;
};

typedef struct kjFreelistAllocator {
    kjAllocator allocator;
    u8* data;
    isize size;
    isize used;

    kjFreelistBlock* freelist;
} kjFreelistAllocator;

KJ_API kjResult kj_freelist_allocator(kjFreelistAllocator* a, void* data, isize size);

KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_freelist_realloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_freelist_free);
KJ_API KJ_ALLOCATOR_DESTROY_FN(kj_freelist_destroy);

typedef struct kjPoolAllocator {
    kjAllocator allocator;
    u8* data;
    isize size;
    isize used;

    isize item_size;
    void* freelist;
} kjPoolAllocator;

KJ_API kjResult kj_pool_allocator(kjPoolAllocator* a, void* data, isize size, isize item_size);

KJ_API KJ_ALLOCATOR_REALLOC_FN(kj_pool_realloc);
KJ_API KJ_ALLOCATOR_FREE_FN(kj_pool_free);
KJ_API KJ_ALLOCATOR_DESTROY_FN(kj_pool_destroy);

#define KJ_PRIORITY_MAP(X)                                                                                              \
    X(KJ_PRIORITY_CRITICAL, "Critical")                                                                                 \
    X(KJ_PRIORITY_ERROR, "Error")                                                                                       \
    X(KJ_PRIORITY_WARN, "Warning")                                                                                      \
    X(KJ_PRIORITY_INFO, "Info")                                                                                         \
    X(KJ_PRIORITY_DEBUG, "Debug")                                                                                       \
    X(KJ_PRIORITY_VERBOSE, "Verbose")

typedef enum kjPriority {
#define KJ_PRIORITY_ENUM(type, name) type,
    KJ_PRIORITY_MAP(KJ_PRIORITY_ENUM)
#undef KJ_PRIORITY_ENUM
    KJ_PRIORITY_COUNT
} kjPriority;

KJ_API const char* kj_priority_str(kjPriority priority);

#define KJ_LOG_FN(name) void name(const char* file, isize line, kjPriority priority, const char* fmt, ...)
typedef KJ_LOG_FN(kjLoggerFn);

KJ_API KJ_LOG_FN(_kj_default_log_fn);

#if !defined(KJ_CUSTOM_LOG_FN)
#define KJ_CUSTOM_LOG_FN _kj_default_log_fn
#endif

KJ_WARNING_DISABLE_BEGIN()
KJ_WARNING_DISABLE_CLANG("-Wvariadic-macros")
KJ_WARNING_DISABLE_GNU("-Wvariadic-macros")

#if !defined(kj_log)
#define kj_log(priority, ...) KJ_CUSTOM_LOG_FN(KJ_CUR_FILE, KJ_CUR_LINE, (priority), __VA_ARGS__)
#define kj_log_critical(...) kj_log(KJ_PRIORITY_CRITICAL, __VA_ARGS__)
#define kj_log_error(...) kj_log(KJ_PRIORITY_ERROR, __VA_ARGS__)
#define kj_log_warn(...) kj_log(KJ_PRIORITY_WARN, __VA_ARGS__)
#define kj_log_info(...) kj_log(KJ_PRIORITY_INFO, __VA_ARGS__)
#define kj_log_debug(...) kj_log(KJ_PRIORITY_DEBUG, __VA_ARGS__)
#define kj_log_verbose(...) kj_log(KJ_PRIORITY_VERBOSE, __VA_ARGS__)

#define kj_log_manual(file, line, priority, ...) KJ_CUSTOM_LOG_FN((file), (line), (priority), __VA_ARGS__)
#define kj_log_manual_critical(file, line, ...) kj_log_manual((file), (line), KJ_PRIORITY_CRITICAL, __VA_ARGS__)
#define kj_log_manual_error(file, line, ...) kj_log_manual((file), (line), KJ_PRIORITY_ERROR, __VA_ARGS__)
#define kj_log_manual_warn(file, line, ...) kj_log_manual((file), (line), KJ_PRIORITY_WARN, __VA_ARGS__)
#define kj_log_manual_info(file, line, ...) kj_log_manual((file), (line), KJ_PRIORITY_INFO, __VA_ARGS__)
#define kj_log_manual_debug(file, line, ...) kj_log_manual((file), (line), KJ_PRIORITY_DEBUG, __VA_ARGS__)
#define kj_log_manual_verbose(file, line, ...) kj_log_manual((file), (line), KJ_PRIORITY_VERBOSE, __VA_ARGS__)
#endif

#define KJ_ASSERT_FN(name) void name(const char* expr, const char* file, isize line, const char* fmt, ...)
typedef KJ_ASSERT_FN(kjAssertFn);

KJ_API KJ_ASSERT_FN(_kj_default_assert_fn);

#if !defined(KJ_CUSTOM_ASSERT_FN)
#define KJ_CUSTOM_ASSERT_FN _kj_default_assert_fn
#endif

#define KJ_CUR_FILE __FILE__
#define KJ_CUR_LINE __LINE__

#if defined(KJ_COMPILER_MSVC)
#define kj_break() __debugbreak()
#define kj_unreachable() __assume(0)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define kj_break() __builtin_debugtrap()
#define kj_unreachable() __builtin_unreachable()
#endif

# if !defined(kj_assert)
#if defined(KJ_DISABLE_DEBUG)
#define kj_assert(expr, ...) do { if((!expr)) { kj_unreachable(); } } while(0)
#define kj_panic(...) kj_unreachable()
#else
#define kj_assert(expr, ...) do {                                                                                       \
    if(!(expr)) {                                                                                                       \
        KJ_CUSTOM_ASSERT_FN(kj_str_of(expr), KJ_CUR_FILE, KJ_CUR_LINE, __VA_ARGS__);                                    \
        kj_break();                                                                                                     \
    }                                                                                                                   \
} while(0)
#define kj_panic(...) do {                                                                                              \
    KJ_CUSTOM_ASSERT_FN("PANIC", KJ_CUR_FILE, KJ_CUR_LINE, __VA_ARGS__);                                                \
    kj_break();                                                                                                         \
} while(0)
#endif
#endif

#if !defined(kj_validate)
#if !defined(KJ_DISABLE_CHECK)
#if defined(KJ_VALIDATE_ASSERT)
#define kj_validate(expr, scope) kj_assert(expr, "Validation")
#else
#define kj_validate(expr, scope) do { if(!(expr)) { scope } } while(0)
#endif
#else
#define kj_validate(expr, scope)
#endif
#endif

KJ_WARNING_DISABLE_END()

#define kj_unimplemented(...) do {                                                                                      \
    KJ_CUSTOM_ASSERT_FN("UNIMPLEMENTED", KJ_CUR_FILE, KJ_CUR_LINE, __func__);                                           \
    kj_break();                                                                                                         \
} while(0)

/* Endian */

KJ_API u16 kj_byte_swap16(u16 a);
KJ_API u32 kj_byte_swap32(u32 a);
KJ_API u64 kj_byte_swap64(u64 a);

#if !defined(KJ_CC8)
#if KJ_ENDIAN == KJ_LE
#define KJ_CC8(a, b, c, d, e, f, g, h)                                                                                  \
    (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24) | ((e) << 32) | ((f) << 40) | ((g) << 48) | ((h) << 56))
#define KJ_CC4(a, b, c, d) (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#define KJ_CC2(a, b) (((a) << 0) | ((b) << 8))
#define kj_byte_swap16_le(a) (a)
#define kj_byte_swap32_le(a) (a)
#define kj_byte_swap64_le(a) (a)
#define kj_byte_swap16_be(a) kj_byte_swap16(a)
#define kj_byte_swap32_be(a) kj_byte_swap32(a)
#define kj_byte_swap64_be(a) kj_byte_swap64(a)
#else
#define KJ_CC8(a, b, c, d, e, f, g, h)                                                                                  \
    (((h) << 0) | ((g) << 8) | ((f) << 16) | ((e) << 24) | ((d) << 32) | ((c) << 40) | ((b) << 48) | ((a) << 56))
#define KJ_CC4(a, b, c, d) (((d) << 0) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#define KJ_CC2(a, b) (((b) << 0) | ((a) << 8))
#define kj_byte_swap16_le(a) kj_byte_swap16(a)
#define kj_byte_swap32_le(a) kj_byte_swap32(a)
#define kj_byte_swap64_le(a) kj_byte_swap64(a)
#define kj_byte_swap16_be(a) (a)
#define kj_byte_swap32_be(a) (a)
#define kj_byte_swap64_be(a) (a)
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
KJ_API b32 kj_str_eq(const char* a, const char* b, isize size);
KJ_API b32 kj_str_ieq(const char* a, const char* b, isize size);
KJ_API const char* kj_str_find_char(const char* s, isize size, char c);
KJ_API const char* kj_str_rfind_char(const char* s, isize size, char c);
KJ_API const char* kj_str_find(const char* a, const char* b);
KJ_API b32 kj_str_prefix(const char* s, const char* prefix);
KJ_API b32 kj_str_suffix(const char* s, const char* suffix);
KJ_API char* kj_str_cat(char* dst, isize dst_size, const char* a, isize a_size, const char* b, isize b_size);
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
KJ_API isize kj_utf8_to_codepoint(u32* codepoint, const char* s, isize size);

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

KJ_WARNING_DISABLE_BEGIN()
KJ_WARNING_DISABLE_MSVC(4200)
KJ_WARNING_DISABLE_CLANG("-Wzero-length-array")
KJ_WARNING_DISABLE_GNU("-Wpedantic")
KJ_PACK_BEGIN(1)

typedef struct kjStringHeader {
    kjAllocator* allocator;
    isize size;
    isize capacity;
    char data[];
} kjStringHeader;

KJ_PACK_END()
KJ_WARNING_DISABLE_END()

KJ_API kjString kj_string(const char* s, isize size, kjAllocator* a);
KJ_API void kj_string_destroy(kjString s);
KJ_API void kj_string_reset(kjString s);
KJ_API isize kj_string_size(kjString s);
KJ_API isize kj_string_capacity(kjString s);
KJ_API isize kj_string_available(kjString s);
KJ_API kjString kj_string_end(kjString s);
KJ_API kjString kj_string_extend(kjString s, isize size);
KJ_API kjString kj_string_resize(kjString s, isize size);
KJ_API kjString kj_string_append(kjString a, kjString b);
KJ_API kjString kj_string_append_str(kjString a, const char* b, isize size);
KJ_API kjString kj_string_duplicate(kjString s);
KJ_API kjString kj_string_slice(kjString s, isize start, isize end);
KJ_API kjString kj_string_from_file(kjString s, const char* path, kjAllocator* a);

/* Sorting */

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

KJ_API KJ_CMP_FN(kj_cmp_string);

#define KJ_SWAP_FN(name) void name(void* arr, isize i, isize j)
typedef KJ_SWAP_FN(kjSwapFn);

#define KJ_SWAP_FN_PROTO(type, name, T) KJ_API KJ_SWAP_FN(kj_swap_##T);
    KJ_TYPE_MAP(KJ_SWAP_FN_PROTO)
#undef KJ_SWAP_FN_PROTO

KJ_API KJ_SWAP_FN(kj_swap_string);

KJ_API void kj_sort_insertion(void* arr, isize count, kjCmpFn cmp, kjSwapFn swap);

/* Date/Time */

#define KJ_DATETIME_UTC_ISO_FMT "%04d-%02d-%02dT%02d:%02d:%02dZ"
#define KJ_DATETIME_LOCAL_ISO_FMT "%04d-%02d-%02dT%02d:%02d:%02d%c%02d:%02d"
#define KJ_DATETIME_UTC_EXPAND(dt) (dt)->year, (dt)->month, (dt)->day, (dt)->hours, (dt)->minutes, (dt)->seconds
#define KJ_DATETIME_LOCAL_EXPAND(dt)                                                                                    \
    (dt)->year, (dt)->month, (dt)->day, (dt)->hours, (dt)->minutes, (dt)->seconds,                                      \
    (dt)->tz < 0 ? '+': '-', kj_abs(((dt)->tz / 60)), kj_abs(((dt)->tz % 60))

typedef struct kjDateTime {
    i16 year;
    i16 month;
    i16 day;
    i16 hours;
    i16 minutes;
    i16 seconds;
    i16 milliseconds;
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
KJ_API u32 kj_hash_crc32(const void* data, isize size, u32 crc);

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
    KJ_O_USR_RW = KJ_O_USR_R | KJ_O_USR_W,
    KJ_O_GRP_R = KJ_FLAG(25),
    KJ_O_GRP_W = KJ_FLAG(26),
    KJ_O_GRP_X = KJ_FLAG(27),
    KJ_O_GRP_RWX = KJ_O_GRP_R | KJ_O_GRP_W | KJ_O_GRP_X,
    KJ_O_GRP_RW = KJ_O_USR_R | KJ_O_USR_W,
    KJ_O_OTH_R = KJ_FLAG(28),
    KJ_O_OTH_W = KJ_FLAG(29),
    KJ_O_OTH_X = KJ_FLAG(30),
    KJ_O_OTH_RWX = KJ_O_OTH_R | KJ_O_OTH_W | KJ_O_OTH_X,
    KJ_O_OTH_RW = KJ_O_OTH_R | KJ_O_OTH_W,
    KJ_O_INVALID = KJ_FLAG_ALL
};

typedef enum kjSeekFrom {
    KJ_SEEK_BEGIN = 0,
    KJ_SEEK_CURRENT = 1,
    KJ_SEEK_END = 2
} kjSeekFrom;

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

typedef enum kjFileType {
    KJ_FILE,
    KJ_DIR,
    KJ_SYMLINK
} kjFileType;

typedef struct kjFileMetadata {
    kjFileType type;
    i64 size;
    u64 last_access;
    u64 last_write;
} kjFileMetadata;

KJ_API kjResult kj_file_create(kjFd* fd, const char* path, u32 flags);
KJ_API kjResult kj_file_open(kjFd* fd, const char* path, u32 flags);
KJ_API kjResult kj_file_close(kjFd fd);
KJ_API isize kj_file_seek(kjFd fd, i64 offset, kjSeekFrom seek);
KJ_API isize kj_file_pos(kjFd fd);
KJ_API isize kj_file_read(kjFd fd, void* buf, isize size);
KJ_API isize kj_file_write(kjFd fd, void* buf, isize size);
KJ_API isize kj_file_read_at(kjFd fd, void* buf, isize size, i64 offset);
KJ_API isize kj_file_write_at(kjFd fd, void* buf, isize size, i64 offset);
KJ_API kjResult kj_file_sync(kjFd fd);
KJ_API isize kj_file_path(kjFd fd, char* path, isize size);
KJ_API isize kj_file_map(void** buf, kjFd fd, u32 flags);
KJ_API isize kj_file_map_path(void** buf, kjFd* fd, const char* path, u32 flags);
KJ_API kjResult kj_file_unmap(void* buf, kjFd fd);

KJ_API kjResult kj_file_metadata(kjFileMetadata* meta, kjFd fd);
KJ_API kjResult kj_file_metadata_path(kjFileMetadata* meta, const char* path);

KJ_API isize kj_file_slurp(void** out, const char* path, kjAllocator* a);
KJ_API isize kj_file_spit(const char* path, void* buf, isize size);

/* Paths */

enum {
    KJ_RENAME_NONE = KJ_FLAG_NONE,
    KJ_RENAME_NO_REPLACE = KJ_FLAG(0),
};

KJ_API const char* kj_path_ext(const char* path, isize size);
KJ_API const char* kj_path_base(const char** end, const char* path, isize size);
KJ_API const char* kj_path_dir(const char** end, const char* path, isize size);
KJ_API kjResult kj_path_create_dir(const char* path);
KJ_API kjResult kj_path_remove_dir(const char* path);
KJ_API kjResult kj_path_rename(const char* from, const char* to, u32 flags);
KJ_API isize kj_path_current_dir(char* path, isize size);
KJ_API kjResult kj_path_set_current_dir(const char* path);
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

KJ_API kjResult kj_read_dir(kjReadDir* dir, const char* path);
KJ_API kjResult kj_read_dir_next(kjReadDir* dir, const char** path);

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

KJ_API isize kj_vdprintf(kjFd fd, KJ_FMT_STR const char* fmt, va_list v);
KJ_API isize kj_dprintf(kjFd fd, KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(2);
KJ_API isize kj_vprintf(KJ_FMT_STR const char* fmt, va_list v);
KJ_API isize kj_printf(KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(1);
KJ_API isize kj_vsnprintf(char* buf, isize size, KJ_FMT_STR const char* fmt, va_list v);
KJ_API isize kj_snprintf(char* buf, isize size, KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(3);
KJ_API isize kj_vasprintf(char** buf, KJ_FMT_STR const char* fmt, va_list v);
KJ_API isize kj_asprintf(char** buf, KJ_FMT_STR const char* fmt, ...) KJ_FMT_VARGS(2);

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
#error "Unsupported Operating System"
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

typedef enum kjSocketAddr {
    KJ_SOCKET_ADDR_V4,
    KJ_SOCKET_ADDR_V6
} kjSocketAddr;

KJ_API b32 kj_socket_begin(void);
KJ_API void kj_socket_end(void);
KJ_API kjResult kj_socket_open(kjSocket* sock, kjSocketAddr addr);
KJ_API void kj_socket_close(kjSocket* sock);
KJ_API kjResult kj_socket_connect(kjSocket* sock, const char* ip, u16 port);
KJ_API kjResult kj_socket_bind(kjSocket* sock, u16 port, u32 flags);
KJ_API kjResult kj_socket_listen(kjSocket* sock, isize conn);
KJ_API kjResult kj_socket_accept(kjSocket* sock, kjSocket* client);
KJ_API isize kj_socket_read(kjSocket* sock, void* buf, isize size);
KJ_API isize kj_socket_write(kjSocket* sock, const void* buf, isize size);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_IMPL)

KJ_INLINE const char* kj_result_str(kjResult result) {
    switch(result) {
#define KJ_CASE(type, value, name) case (type): return (name);
        KJ_ERROR_MAP(KJ_CASE)
#undef KJ_CASE
        default: return "None";
    }
}

kjResult kj_error_from_os(i32 err) {
    kjResult res = KJ_SUCCESS;
    switch(err) {
#if defined(KJ_SYS_WIN32)
        case ERROR_SUCCESS: res = KJ_SUCCESS; break;
        case ERROR_ACCESS_DENIED: res = KJ_ERROR_PERMISSION_DENIED; break;
        case ERROR_ALREADY_EXISTS: res = KJ_ERROR_ALREADY_EXISTS; break;
        case ERROR_FILE_EXISTS: res = KJ_ERROR_ALREADY_EXISTS; break;
        case ERROR_BROKEN_PIPE: res = KJ_ERROR_BROKEN_PIPE; break;
        case ERROR_FILE_NOT_FOUND: res = KJ_ERROR_NOT_FOUND; break;
        case ERROR_PATH_NOT_FOUND: res = KJ_ERROR_NOT_FOUND; break;
        case ERROR_MOD_NOT_FOUND: res = KJ_ERROR_NOT_FOUND; break;
        case ERROR_PROC_NOT_FOUND: res = KJ_ERROR_NOT_FOUND; break;
        case ERROR_NOT_EMPTY: res = KJ_ERROR_NOT_EMPTY; break;
        case ERROR_NO_DATA: res = KJ_ERROR_BROKEN_PIPE; break;
        case ERROR_INVALID_PARAMETER: res = KJ_ERROR_PARAM; break;
        case ERROR_OPERATION_ABORTED: res = KJ_ERROR_TIMED_OUT; break;
        case ERROR_SEEK: res = KJ_ERROR_ILLEGAL_SEEK; break;
        case ERROR_NEGATIVE_SEEK: res = KJ_ERROR_ILLEGAL_SEEK; break;
        case ERROR_SEEK_ON_DEVICE: res = KJ_ERROR_ILLEGAL_SEEK; break;
        case ERROR_INSUFFICIENT_BUFFER: res = KJ_ERROR_RANGE; break;
        case WSAEBADF: res = KJ_ERROR_BAD_HANDLE; break;
        case WSAEACCES: res = KJ_ERROR_PERMISSION_DENIED; break;
        case WSAETIMEDOUT: res = KJ_ERROR_TIMED_OUT; break;
        case WSAEINVAL: res = KJ_ERROR_PARAM; break;
        case WSAEINTR: res = KJ_ERROR_INTERRUPED; break;
        case WSAEADDRINUSE: res = KJ_ERROR_ADDR_IN_USE; break;
        case WSAEADDRNOTAVAIL: res = KJ_ERROR_ADDR_NOT_AVAILABLE; break;
        case WSAECONNABORTED: res = KJ_ERROR_CONN_ABORTED; break;
        case WSAECONNREFUSED: res = KJ_ERROR_CONN_REFUSED; break;
        case WSAECONNRESET: res = KJ_ERROR_CONN_RESET; break;
        case WSAENOTCONN: res = KJ_ERROR_NOT_CONNECTED; break;
        case WSAEWOULDBLOCK: res = KJ_ERROR_WOULD_BLOCK; break;
#elif defined(KJ_SYS_UNIX)
        case 0: res = KJ_SUCCESS; break;
        case EBADF: res = KJ_ERROR_BAD_HANDLE; break;
        case EPERM: res = KJ_ERROR_PERMISSION_DENIED; break;
        case EACCES: res = KJ_ERROR_PERMISSION_DENIED; break;
        case EEXIST: res = KJ_ERROR_ALREADY_EXISTS; break;
        case EPIPE: res = KJ_ERROR_BROKEN_PIPE; break;
        case ENOENT: res = KJ_ERROR_NOT_FOUND; break;
        case ENODEV: res = KJ_ERROR_NO_DEVICE; break;
        case ENOTEMPTY: res = KJ_ERROR_NOT_EMPTY; break;
        case ETIMEDOUT: res = KJ_ERROR_TIMED_OUT; break;
        case EINVAL: res = KJ_ERROR_PARAM; break;
        case EINTR: res = KJ_ERROR_INTERRUPED; break;
        case ESPIPE: res = KJ_ERROR_ILLEGAL_SEEK; break;
        case EAGAIN: res = KJ_ERROR_WOULD_BLOCK; break;
        case ERANGE: res = KJ_ERROR_RANGE; break;
        case ENOMEM: res = KJ_ERROR_ALLOC; break;
        case EBUSY: res = KJ_ERROR_BUSY; break;
        case EADDRINUSE: res = KJ_ERROR_ADDR_IN_USE; break;
        case EADDRNOTAVAIL: res = KJ_ERROR_ADDR_NOT_AVAILABLE; break;
        case ECONNABORTED: res = KJ_ERROR_CONN_ABORTED; break;
        case ECONNREFUSED: res = KJ_ERROR_CONN_REFUSED; break;
        case ECONNRESET: res = KJ_ERROR_CONN_RESET; break;
        case ENOTCONN: res = KJ_ERROR_NOT_CONNECTED; break;
#endif
        default: res = KJ_ERROR_UNKNOWN; break;
    }
    return res;
}

KJ_INLINE kjResult kj_os_error(void) {
    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    res = kj_error_from_os(GetLastError());
#elif defined(KJ_SYS_UNIX)
    res = kj_error_from_os(errno);
#endif
    return res;
}

#if defined(KJ_LIB_IMPL)
#include <dlfcn.h>
kjLib kj_lib_open(const char* path) {
    kj_validate(path != NULL, { return NULL; });

    kjLib res = NULL;
#if defined(KJ_SYS_WIN32)
    WCHAR* ucs = kj_ucs_from_utf8_malloca(path, 0);
    if(ucs) {
        void* ptr;
        if((ptr = LoadLibraryW(ucs)) != NULL) {
            *lib = ptr;
        } else {
            res = kj_os_error();
        }
        kj_ucs_from_utf8_freea(ucs);
    }
#elif defined(KJ_SYS_UNIX)
    res = kj_cast(kjLib, dlopen(path, RTLD_NOW));
#endif
    return res;
}

kjLibFn kj_lib_fn(kjLib* lib, const char* name) {
    kj_validate(lib != NULL && name != NULL, { return NULL; });

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
    kj_validate(lib != NULL, { return; });

#if defined(KJ_SYS_WIN32)
    FreeLibrary(lib);
#elif defined(KJ_SYS_UNIX)
    dlclose(lib);
#endif
}
#endif

KJ_INLINE void kj_process_exit(u32 code) {
#if defined(KJ_SYS_WIN32)
    ExitProcess(kj_cast(UINT, code));
#elif defined(KJ_SYS_UNIX)
    exit(code);
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
    kj_validate(name != NULL, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    kj_unused(name);
    kj_unused(out);
    kj_unused(size);
    kj_unimplemented();
#elif defined(KJ_SYS_UNIX)
    const char* env_var = getenv(name);
    if(env_var) {
        res = kj_str_size(env_var, 0);
        if(out && res < size) {
            kj_mem_copy(out, env_var, res);
        }
    } else {
        res = KJ_ERROR_NOT_FOUND;
    }
#endif
    return res;
}

KJ_INLINE isize kj_env_home_dir(char* path, isize size) {
    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    res = kj_env_var("USERPROFILE", path, size);
#elif defined(KJ_SYS_UNIX)
    res = kj_env_var("HOME", path, size);
    if(kj_is_error(res)) {
        struct passwd* pw = getpwuid(getuid());
        if(pw) {
            res = kj_str_size(pw->pw_dir, 0);
            if(path && res < size) {
                kj_mem_copy(path, pw->pw_dir, res);
            }
        } else {
            res = KJ_ERROR_NOT_FOUND;
        }
    }
#endif
    return res;
}

b32 kj_debugger_attached(void) {
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

KJ_INLINE void* kj_ptr_align(void* ptr, isize alignment) {
    return kj_cast(void*, (kj_cast(uptr, ptr) + kj_cast(uptr, alignment - 1)) & kj_cast(uptr, ~(alignment - 1)));
}

KJ_INLINE isize kj_ptr_align_offset(void* ptr, isize alignment) {
    isize res = alignment - (kj_cast(uptr, ptr) & kj_cast(uptr, alignment - 1));
    return res == alignment ? 0: res;
}

KJ_INLINE isize kj_ptr_align_offset_sized(void* ptr, isize alignment, isize size) {
    isize res = kj_ptr_align_offset(ptr, alignment);
    if(res < size) {
        size -= res;
        res += (alignment * (size / alignment)) + ((size % alignment > 0) ? alignment: 0);
    }
    return res;
}

KJ_ALLOCATOR_REALLOC_FN(_kj_stub_realloc) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_unused(a);
    kj_unused(data);
    kj_unused(size);
    kj_unimplemented();
    return NULL;
}

KJ_ALLOCATOR_FREE_FN(_kj_stub_free) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_unused(a);
    kj_unused(data);
    kj_unimplemented();
}

KJ_ALLOCATOR_DESTROY_FN(_kj_stub_destroy) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_unused(a);
    kj_unimplemented();
}

kjAllocator _KJ_HEAP_ALLOCATOR = {
    KJ_ALLOCATOR_NONE,
    kj_heap_realloc,
    kj_heap_free,
    _kj_stub_destroy
};

kjAllocator* KJ_HEAP_ALLOCATOR = &_KJ_HEAP_ALLOCATOR;

KJ_ALLOCATOR_REALLOC_FN(kj_heap_realloc) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_unused(a);
    void* res = NULL;
#if defined(KJ_SYS_WIN32)
    res = HeapReAlloc(GetProcessHeap(), 0, data, size);
#elif defined(KJ_SYS_UNIX)
    res = realloc(data, size);
#endif
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_heap_free) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_unused(a);
    if(data) {
#if defined(KJ_SYS_WIN32)
        HeapFree(GetProcessHeap(), 0, data);
#elif defined(KJ_SYS_UNIX)
        free(data);
#endif
    }
}

kjResult kj_arena_allocator(kjArenaAllocator* a, void* data, isize size) {
    kj_validate(a != NULL && size > 0, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
    a->allocator.realloc = kj_arena_realloc;
    a->allocator.free = kj_arena_free;
    a->allocator.destroy = kj_arena_destroy;
    if(data) {
        a->data = kj_cast(u8*, data);
        a->allocator.flags = KJ_ALLOCATOR_NONE;
    } else {
        a->data = kj_cast(u8*, kj_alloc(size));
        a->allocator.flags = KJ_ALLOCATOR_OWNER;
        if(!a->data) {
            res = KJ_ERROR_ALLOC;
        }
    }
    a->size = size;
    a->used = 0;
    a->offset = 0;
    return res;
}

void kj_arena_allocator_reset(kjArenaAllocator* a) {
    kj_validate(a != NULL, { return; });

    a->used = 0;
    a->offset = 0;
}


KJ_ALLOCATOR_REALLOC_FN(kj_arena_realloc) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_validate(a != NULL && size > 0, { return NULL; });

    void* res = NULL;
    kjArenaAllocator* aa = kj_cast(kjArenaAllocator*, a);
    if(data) {
        if((aa->data + aa->offset) == data) {
            isize new_size = aa->used + (size - (aa->used - aa->offset));
            if(new_size < aa->size) {
                aa->used += new_size;
                res = data;
            }
        }
    } else {
        if(size < aa->size) {
            aa->offset = aa->used;
            res = kj_cast(void*, aa->data + aa->used);
            aa->used += size;
        }
    }
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_arena_free) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_validate(a != NULL && data != NULL, { return; });

    kjArenaAllocator* aa = kj_cast(kjArenaAllocator*, a);
    if(data == (aa->data + aa->offset)) {
        aa->used = aa->offset;
    }
}

KJ_ALLOCATOR_DESTROY_FN(kj_arena_destroy) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_validate(a != NULL, { return; });

    if(a->flags & KJ_ALLOCATOR_OWNER) {
        kjArenaAllocator* aa = kj_cast(kjArenaAllocator*, a);
        kj_free(aa->data);
    }
}

KJ_API kjResult kj_freelist_allocator(kjFreelistAllocator* a, void* data, isize size) {
    kj_validate(a != NULL && size > 0, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
    a->allocator.realloc = kj_freelist_realloc;
    a->allocator.free = kj_freelist_free;
    a->allocator.destroy = kj_freelist_destroy;
    if(data) {
        a->data = kj_cast(u8*, data);
        a->allocator.flags = KJ_ALLOCATOR_NONE;
    } else {
        a->data = kj_cast(u8*, kj_alloc(size));
        a->allocator.flags = KJ_ALLOCATOR_OWNER;
        if(!a->data) {
            res = KJ_ERROR_ALLOC;
        }
    }
    a->size = size;
    a->used = 0;
    a->freelist = kj_cast(kjFreelistBlock*, a->data);
    a->freelist->size = size;
    a->freelist->next = NULL;
    return res;
}

KJ_ALLOCATOR_REALLOC_FN(kj_freelist_realloc) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_unused(data);
    kj_validate(a != NULL && size > 0, { return NULL; });

    void* res = NULL;
    kjFreelistAllocator* fa = kj_cast(kjFreelistAllocator*, a);
    kjFreelistBlock* prev = NULL;
    kjFreelistBlock* block = fa->freelist;
    while(block) {
        isize offset = kj_ptr_align_offset_sized(block, 16, kj_isize_of(kjAllocationHeader));
        size += offset;
        if(block->size < size) {
            prev = block;
            block = block->next;
            continue;
        }

        if(block->size - size <= kj_isize_of(kjAllocationHeader)) {
            size = block->size;
            if(prev) {
                prev->next = block->next;
            } else {
                fa->freelist = block->next;
            }
        } else {
            kjFreelistBlock* next = kj_cast(kjFreelistBlock*, kj_cast(uptr, block) + size);
            next->size = block->size - size;
            next->next = block->next;
            if(prev) {
                prev->next = next;
            } else {
                fa->freelist = next;
            }
        }

        kjAllocationHeader* header = kj_cast(kjAllocationHeader*, kj_cast(uptr, block) - kj_isize_of(kjAllocationHeader));
        header->size = size;

        fa->used += size;

        res = kj_cast(void*, block);
        break;
    }
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_freelist_free) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_validate(a != NULL && data != NULL, { return; });

    kjFreelistAllocator* fa = kj_cast(kjFreelistAllocator*, a);
    kjAllocationHeader* header = kj_cast(kjAllocationHeader*, kj_cast(uptr, data) - kj_isize_of(kjAllocationHeader));

    kjFreelistBlock* prev = NULL;
    kjFreelistBlock* block = fa->freelist;

    while(block) {
        if(kj_cast(uptr, block) >= kj_cast(uptr, data) + header->size) {
            break;
        }

        prev = block;
        block = block->next;
    }

    if(!prev) {
        prev = kj_cast(kjFreelistBlock*, data);
        prev->size = header->size;
        prev->next = fa->freelist;
        fa->freelist = prev;
    } elif(kj_cast(uptr, prev) + prev->size == kj_cast(uptr, data)) {
        prev->size += header->size;
    } else {
        kjFreelistBlock* next = kj_cast(kjFreelistBlock*, data);
        next->size = header->size;
        next->next = prev->next;
        prev->next = next;
        prev = next;
    }

    if(block && kj_cast(uptr, block) == kj_cast(uptr, data) + header->size) {
        prev->size = block->size;
        prev->next = block->next;
    }

    fa->used -= header->size;
}

KJ_ALLOCATOR_DESTROY_FN(kj_freelist_destroy) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_validate(a != NULL, { return; });

    if(a->flags & KJ_ALLOCATOR_OWNER) {
        kjFreelistAllocator* fa = kj_cast(kjFreelistAllocator*, a);
        kj_free(fa->data);
    }
}

kjResult kj_pool_allocator(kjPoolAllocator* a, void* data, isize size, isize item_size) {
    kj_validate(a != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
    a->allocator.realloc = kj_pool_realloc;
    a->allocator.free = kj_pool_free;
    a->allocator.destroy = kj_pool_destroy;
    if(data) {
        a->data = kj_cast(u8*, data);
        a->allocator.flags = KJ_ALLOCATOR_NONE;
    } else {
        a->data = kj_cast(u8*, kj_alloc(size));
        a->allocator.flags = KJ_ALLOCATOR_OWNER;
        if(!a->data) {
            res = KJ_ERROR_ALLOC;
        }
    }
    a->size = size;
    a->used = 0;
    a->item_size = item_size;
    a->freelist = kj_cast(void**, a->data);

    void* item = data;
    for(isize i = 0; i < (a->size / a->item_size) - 1; i++) {
        uptr* next = kj_cast(uptr*, item);
        *next = kj_cast(uptr, item) + a->item_size;
        item = kj_cast(void*, kj_cast(uptr, item) + a->item_size);
    }

    return res;
}

KJ_ALLOCATOR_REALLOC_FN(kj_pool_realloc) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_validate(a != NULL && data == NULL && size == 0, { return NULL; });

    void* res = NULL;
    kjPoolAllocator* pa = kj_cast(kjPoolAllocator*, a);
    if(pa->freelist) {
        uptr next = *kj_cast(uptr*, pa->freelist);
        res = pa->freelist;
        pa->freelist = kj_cast(void*, next);
        pa->used += pa->item_size;
        size = pa->item_size;
    }
    return res;
}

KJ_ALLOCATOR_FREE_FN(kj_pool_free) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_validate(a != NULL && data != NULL, { return; });

    kjPoolAllocator* pa = kj_cast(kjPoolAllocator*, a);
    *kj_cast(void**, data) = pa->freelist;
    pa->freelist = kj_cast(void**, data);
    pa->used -= pa->item_size;
}

KJ_ALLOCATOR_DESTROY_FN(kj_pool_destroy) {
#if !defined(KJ_DISABLE_DEBUG)
    kj_unused(line);
    kj_unused(file);
#endif
    kj_validate(a != NULL, { return; });

    if(a->flags & KJ_ALLOCATOR_OWNER) {
        kjPoolAllocator* pa = kj_cast(kjPoolAllocator*, a);
        kj_free(pa->data);
    }
}


KJ_INLINE const char* kj_priority_str(kjPriority priority) {
    switch(priority) {
#define KJ_CASE(type, name) case type: return (name);
        KJ_PRIORITY_MAP(KJ_CASE)
#undef KJ_CASE
        default: return "Unknown";
    }
}

KJ_LOG_FN(_kj_default_log_fn) {
    isize size = kj_dprintf(
            KJ_FD_STDERR, "%llu:%s:%d:%s", kj_timestamp_utc(), file, kj_cast(i32, line), kj_priority_str(priority));
    kj_dprintf(
            KJ_FD_STDERR, "%*.s",
            kj_cast(i32, kj_max(0, 64 - size)), "                                                                ");
    if(fmt) {
        va_list va;
        va_start(va, fmt);
        kj_vdprintf(KJ_FD_STDERR, fmt, va);
        va_end(va);
    }
    kj_dprintf(KJ_FD_STDERR, "\n");
}

KJ_ASSERT_FN(_kj_default_assert_fn) {
    isize size = kj_dprintf(KJ_FD_STDERR, "%llu:%s:%d:Assert ", kj_timestamp_utc(), file, kj_cast(i32, line));
    kj_dprintf(
            KJ_FD_STDERR, "%*.s",
            kj_cast(i32, kj_max(0, 64 - size)), "                                                                ");
    if(expr) {
        kj_dprintf(KJ_FD_STDERR, "`%s` - ", expr);
    }
    if(fmt) {
        va_list va;
        va_start(va, fmt);
        kj_vdprintf(KJ_FD_STDERR, fmt, va);
        va_end(va);
    }
    kj_dprintf(KJ_FD_STDERR, "\n");
}

KJ_INLINE u16 kj_byte_swap16(u16 a) {
    return kj_cast(u16,
            ((a << 8) & 0xFF00) |
            ((a >> 8) & 0x00FF));
}

KJ_INLINE u32 kj_byte_swap32(u32 a) {
#if defined(KJ_COMPILER_MSVC)
    return _bswap(a);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __builtin_bswap32(a);
#else
    return kj_cast(u32,
            ((a << 24) & 0xFF000000) |
            ((a <<  8) & 0x00FF0000) |
            ((a >>  8) & 0x0000FF00) |
            ((a >> 24) & 0x000000FF));
#endif
}

KJ_INLINE u64 kj_byte_swap64(u64 a) {
#if defined(KJ_COMPILER_MSVC)
    return _bswap64(a);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __builtin_bswap64(a);
#else
    return kj_cast(u64,
            kj_byte_swap32((a & 0xFFFFFFFF00000000) >> 32) |
            kj_byte_swap32((a & 0x00000000FFFFFFFF) << 32));
#endif
}

isize kj_vdprintf(kjFd fd, KJ_FMT_STR const char* fmt, va_list v) {
#if defined(KJ_SYS_WIN32)
    static char buf[4096];
    isize size = kj_vsnprintf(buf, kj_isize_of(buf), fmt, v);
    kj_file_write(fd, buf, size - 1);
    kj_file_sync(fd);
    return size;
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

isize kj_vprintf(KJ_FMT_STR const char* fmt, va_list v) {
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

isize kj_vsnprintf(char* buf, isize size, KJ_FMT_STR const char* fmt, va_list v) {
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
KJ_INTERN isize _kj_char_compute_known(char* out, isize size, DWORD (*fn)(DWORD, WCHAR*, va_list), ...) {
    isize res = KJ_SUCCESS;
    WCHAR stack[KJ_STACK_BUF_SIZE];
    DWORD n = kj_count_of(stack);
    WCHAR* ptr = stack;
    WCHAR* heap = NULL;
    va_list v;
    va_start(v, fn);
    DWORD req = fn(n, ptr, v);
    if(req == 0) {
        res = kj_os_error();
    } else {
        if(req > n) {
            ptr = kj_cast(WCHAR*, kj_realloc(heap, req * kj_isize_of(WCHAR)));
            if(ptr == NULL) {
                res = KJ_ERROR_ALLOC;
            } else {
                heap = ptr;
                req = fn(req, ptr, v);
            }
        }
        res = kj_utf8_from_ucs(out, kj_cast(i32, size), ptr, req * kj_isize_of(WCHAR));
    }
    kj_free(heap);
    va_end(v);
    return res;
}
#endif

#if defined(KJ_SYS_WIN32)
#define KJ_CHAR WCHAR
#define KJ_SIZE DWORD

KJ_INTERN DWORD _kj_GetModuleFileNameW(DWORD n, WCHAR* buf, va_list v) {
    kj_unused(v);
    return GetModuleFileNameW(NULL, buf, n);
}

KJ_INTERN DWORD _kj_GetTempPathW(DWORD n, WCHAR* buf, va_list v) {
    kj_unused(v);
    return GetTempPathW(n, buf);
}

KJ_INTERN DWORD _kj_GetCurrentDirectoryW(DWORD n, WCHAR* buf, va_list v) {
    kj_unused(v);
    return GetCurrentDirectoryW(n, buf);
}

KJ_INTERN DWORD _kj_GetFinalPathNameByHandle(DWORD n, WCHAR* buf, va_list v) {
    kjFd fd = va_arg(v, kjFd);
    return GetFinalPathNameByHandleW(fd, buf, n, 0);
}
#elif defined(KJ_SYS_UNIX)
#define KJ_CHAR char
#define KJ_SIZE isize

KJ_INTERN isize _kj_getcwd(isize n, char* buf, va_list v) {
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

KJ_INTERN isize _kj_readlink(isize n, char* buf, va_list v) {
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

KJ_INTERN isize _kj_char_compute_unknown(char* out, isize size, KJ_SIZE (*fn)(KJ_SIZE, KJ_CHAR*, va_list), ...) {
    isize res = KJ_SUCCESS;
    KJ_CHAR stack[KJ_STACK_BUF_SIZE];
    KJ_SIZE n = kj_count_of(stack);
    KJ_CHAR* ptr = stack;
    KJ_CHAR* heap = NULL;
    va_list v;
    va_start(v, fn);
    for(;;) {
#if defined(KJ_SYS_WIN32)
        SetLastError(0);
#elif defined(KJ_SYS_UNIX)
        errno = 0;
#endif
        n = fn(n, ptr, v);
        if(n == 0) {
            res = kj_os_error();
            break;
        } elif(kj_os_error() == KJ_ERROR_RANGE) {
            n *= 2;
            ptr = kj_cast(KJ_CHAR*, kj_realloc(heap, n * kj_isize_of(KJ_CHAR)));
            if(ptr == NULL) {
                res = KJ_ERROR_ALLOC;
                break;
            }
            heap = ptr;
        } else {
#if defined(KJ_SYS_WIN32)
            res = kj_utf8_from_ucs(out, kj_cast(i32, size), ptr, n * kj_isize_of(KJ_CHAR));
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
           (u >= 'A' && u <= 'Z') ? KJ_TRUE: KJ_FALSE;
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
    if(!size) {
        while(*e) { e++; }
    } else {
        while(*e && size) { e++; size--; }
    }
    return (e - s);
}

KJ_INLINE isize kj_str_cmp(const char* a, const char* b, isize size) {
    if(!size) {
        while(*a && *b && *a == *b) { a++; b++; }
    } else {
        if(!size--) return 0;
        while(*a && *b && size && *a == *b) { a++; b++; size--; }
    }
    return *a - *b;
}

KJ_INLINE isize kj_str_icmp(const char* a, const char* b, isize size) {
    if(!size) {
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

KJ_INLINE b32 kj_str_eq(const char* a, const char* b, isize size) {
    kj_validate(a != NULL && b != NULL, { return KJ_FALSE; });

    return kj_str_cmp(a, b, size) == 0;
}

KJ_INLINE b32 kj_str_ieq(const char* a, const char* b, isize size) {
    kj_validate(a != NULL && b != NULL, { return KJ_FALSE; });

    return kj_str_icmp(a, b, size) == 0;
}

KJ_INLINE const char* kj_str_find_char(const char* s, isize size, char c) {
    kj_validate(s != NULL && size >= 0, { return NULL; });

    const char* res = NULL;
    if(!size) {
        while(*s) { if(*s == c) { res = s; break; } s++; }
    } else {
        const char* e = s + size;
        while(s < e) { if(*s == c) { res = s; break; } s++; }
    }
    return res;
}

KJ_INLINE const char* kj_str_rfind_char(const char* s, isize size, char c) {
    kj_validate(s != NULL && size >= 0, { return NULL; });

    const char* res = NULL;
    size = !size ? kj_str_size(s, 0): size;
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
    kj_validate(a != NULL && b != NULL, { return NULL; });

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __builtin_strstr(a, b);
#else
    const char* s = a;
    const char* e = b;
    const char* res = NULL;
    for(;;) {
        char cs = *s;
        char ce = *e;
        if(!ce) {
            res = a;
            break;
        }
        if(cs == ce) {
            s++;
            e++;
        } else {
            e = b;
            if(!cs) {
                break;
            }
            s = ++a;
        }
    }
    return res;
#endif
}

KJ_INLINE b32 kj_str_prefix(const char* s, const char* prefix) {
    kj_validate(s != NULL && prefix != NULL, { return KJ_FALSE; });

    while(*prefix) { if(*s++ != *prefix++) { return KJ_FALSE; } }
    return KJ_TRUE;
}

KJ_INLINE b32 kj_str_suffix(const char* s, const char* suffix) {
    kj_validate(s != NULL && suffix != NULL, { return KJ_FALSE; });

    isize s_size = kj_str_size(s, 0);
    isize suffix_size = kj_str_size(suffix, 0);
    if(suffix_size <= s_size) {
        return kj_str_cmp(s + s_size - suffix_size, suffix, 0) == 0;
    }
    return KJ_FALSE;
}

KJ_INLINE char* kj_str_sub_char(char* s, isize size, char o, char n) {
    kj_validate(s != NULL && size >= 0, { return NULL; });

    char* res = s;
    if(!size) {
        while(*res) { if(*res == o) { *res = n; } res++; }
    } else {
        char* e = s + size;
        while(res < e) { if(*res == o) { *res = n; } res++; }
    }
    return res;
}

KJ_INLINE char* kj_str_to_lower(char* s, isize size) {
    kj_validate(s != NULL && size >= 0, { return NULL; });

    char* res = s;
    if(!size) {
        while(*s) { *s = kj_char_to_lower(s); s++; }
    } else {
        char* e = s + size;
        while(s < e) { *s = kj_char_to_lower(s); s++; }
    }
    return res;
}

KJ_INLINE char* kj_str_to_upper(char* s, isize size) {
    kj_validate(s != NULL && size >= 0, { return NULL; });

    char* res = s;
    if(!size) {
        while(*s) { *s = kj_char_to_upper(s); s++; }
    } else {
        char* e = s + size;
        while(s < e) { *s = kj_char_to_upper(s); s++; }
    }
    return res;
}

KJ_INLINE char* kj_str_cat(char* dst, isize dst_size, const char* a, isize a_size, const char* b, isize b_size) {
    kj_validate(dst != NULL && a != NULL && b != NULL, { return NULL; });

    dst_size = !dst_size ? kj_str_size(dst, 0): dst_size;
    a_size = !a_size ? kj_str_size(a, 0): a_size;
    b_size = !b_size ? kj_str_size(b, 0): b_size;
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
    kj_validate(dst != NULL && src != NULL && src_size >= 0, { return NULL; });

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    if(!src_size) {
        return __builtin_strcpy(dst, src);
    } else {
        return __builtin_strncpy(dst, src, src_size);
    }
#else
    char* res = dst;
    if(!src_size) {
        while((*dst++ = *src++) != '\0') {}
    } else {
        while(src_size > 0 && *dst) { *dst++ = *src++; src_size--; }
        if(src_size > 0) { kj_mem_zero(dst, src_size); }
    }
    return res;
#endif
}

KJ_INLINE const char* kj_str_trim(const char** end, const char* s, isize size) {
    kj_validate(s != NULL && end != NULL && size >= 0, { return NULL; });

    size = !size ? kj_str_size(s, 0): size;
    const char* res = kj_str_ltrim(s, size);
    *end = kj_str_rtrim(res, size);
    return res;
}

KJ_INLINE const char* kj_str_ltrim(const char* s, isize size) {
    kj_validate(s != NULL && size >= 0, { return NULL; });

    const char* res = s;
    if(!size) {
        while(!kj_char_is_whitespace(res)) { res++; }
    } else {
        const char* e = s + size;
        while(res < e && kj_char_is_whitespace(res)) { res++; }
    }
    return res;
}

KJ_INLINE const char* kj_str_rtrim(const char* s, isize size) {
    kj_validate(s != NULL && size >= 0, { return NULL; });

    size = !size ? kj_str_size(s, 0): size;
    while(size >= 0 && kj_char_is_whitespace(s + size)) { size--; }
    return s + size;
}

isize kj_u64_from_str(u64* value, const char* s, isize size) {
    kj_validate(value != NULL || s != NULL || size >= 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    *value = 0;
    size = !size ? kj_str_size(s, 0): size;
    u64 base = 10;
    if(*s == '0' && size > 1){
        if(*(s + 1) == 'x') {
            base = 16;
            s += 2;
        } else if(*(s + 1) == 'o') {
            base = 8;
            s += 2;
        } else if(*(s + 1) == 'b') {
            base = 2;
            s += 2;
        } else {
            base = 0;
            res = KJ_ERROR_SYNTAX;
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
                res = KJ_ERROR_SYNTAX;
                break;
            }
            if(v > base) {
                res = KJ_ERROR_SYNTAX;
                break;
            }
            if(*value > overflow) {
                *value = U64_MAX;
                res = KJ_ERROR_RANGE;
                break;
            }
            *value *= base;
            u64 tmp = *value + v;
            if(tmp < *value || tmp > U64_MAX) {
                *value = U64_MAX;
                res = KJ_ERROR_RANGE;
                break;
            }
            *value = tmp;
            res++;
        }
    }
    return res;
}

KJ_INLINE isize kj_u32_from_str(u32* value, const char* s, isize size) {
    kj_validate(value != NULL && s != NULL && size >= 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    u64 u;
    if(kj_is_success(res = kj_u64_from_str(&u, s, size))) {
        if(u <= U32_MAX) {
            *value = kj_cast(u32, u);
        } else {
            res = KJ_ERROR_RANGE;
        }
    }
    return res;
}

isize kj_i64_from_str(i64* value, const char* s, isize size) {
    kj_validate(value != NULL && s != NULL && size >= 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    size = !size ? kj_str_size(s, 0): size;
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
    if(kj_is_success(res = kj_u64_from_str(&u, s, size))) {
        i64 i = kj_cast(i64, u);
        if(i >= I64_MIN && i <= I64_MAX) {
            *value = kj_cast(i64, u) * sign;
        } else {
            res = KJ_ERROR_RANGE;
        }
    }
    return res;
}

KJ_INLINE isize kj_i32_from_str(i32* value, const char* s, isize size) {
    kj_validate(value != NULL && s != NULL && size >= 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    i64 i;
    if(kj_is_success(res = kj_i64_from_str(&i, s, size))) {
        if(i >= I32_MIN && i <= I32_MAX) {
            *value = kj_cast(i32, i);
        } else {
            res = KJ_ERROR_RANGE;
        }
    }
    return res;
}

isize kj_f64_from_str(f64* value, const char* s, isize size) {
    kj_validate(value != NULL && s != NULL && size >= 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    *value = 0;
    size = !size ? kj_str_size(s, 0): size;
    f64 sign = 1.0;
    if(*s == '-') {
        sign = -1.0;
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
                res = KJ_ERROR_SYNTAX;
                break;
            }
            res++;
        }
        while(++dot < (s + size)) {
            *value *= 0.1;
        }
        *value *= sign;
    } else {
        res = KJ_ERROR_SYNTAX;
    }
    return res;
}

KJ_INLINE isize kj_f32_from_str(f32* value, const char* s, isize size) {
    kj_validate(value != NULL && s != NULL && size >= 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    f64 v;
    if(kj_is_success(res = kj_f64_from_str(&v, s, size))) {
        if(v >= F32_MIN  && v < F32_MAX) {
            *value = kj_cast(f32, v);
        } else {
            res = KJ_ERROR_RANGE;
        }
    }
    return res;
}

KJ_INLINE isize kj_utf8_size(const char* s, isize size) {
    kj_validate(s != NULL && size >= 0, { return -1; });

    isize res = 0;
    if(!size) {
        while(*s) { if((*s & 0xC0) != 0x80) { res++; } s++; }
    } else {
        const char* e = s + size;
        while(s < e) { if((*s & 0xC0) != 0x80) { res++; } s++; }
    }
    return res;
}

KJ_INLINE isize kj_utf8_char_size(const char* s) {
    u8 u = *kj_cast(u8*, s);
    if((u & 0x80) == 0x00) {
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

//
// Based on stb_from_utf8() from github.com/nothings/stb
//
isize kj_utf8_to_codepoint(u32* codepoint, const char* s, isize size) {
    u32 c = kj_cast(u32, -1);
    const u8* str = kj_cast(const u8*, s);
    size = !size ? kj_str_size(s, 0): size;
    if(!(*str & 0x80)) {
        c = kj_cast(u32, *str++);
        *codepoint = c;
        return 1;
    } elif((*str & 0xE0) == 0xC0) {
        *codepoint = 0xFFFD;
        if((s + size) - kj_cast(const char*, str) < 2) return 1;
        if(*str < 0xC2) return 2;
        c = kj_cast(u32, (*str++ & 0x1F) << 6);
        if((*str & 0xC0) != 0x80) return 2;
        c += (*str++ & 0x3F);
        *codepoint = c;
        return 2;
    } elif((*str & 0xF0) == 0xE0) {
        *codepoint = 0xFFFD;
        if((s + size) - kj_cast(const char*, str) < 3) return 1;
        if(*str == 0xE0 && (str[1] < 0xA0 || str[1] > 0xBF)) return 3;
        if(*str == 0xED && str[1] > 0x9F) return 3;
        c = kj_cast(u32, (*str++ & 0x0F) << 12);
        if((*str & 0xC0) != 0x80) return 3;
        c += kj_cast(u32, (*str++ & 0x3F) << 6);
        if((*str & 0xC0) != 0x80) return 3;
        c += (*str++ & 0x3F);
        *codepoint = c;
        return 3;
    } elif((*str & 0xF8) == 0xF0) {
        *codepoint = 0xFFFD;
        if((s + size) - kj_cast(const char*, str) < 4) return 1;
        if(*str > 0xF4) return 4;
        if(*str == 0xF0 && (str[1] < 0x90 || str[1] > 0xBF)) return 4;
        if(*str == 0xF4 && str[1] > 0x8F) return 4;
        c = kj_cast(u32, (*str++ & 0x07) << 18);
        if((*str & 0xC0) != 0x80) return 4;
        c += kj_cast(u32, (*str++ & 0x3F) << 12);
        if((*str & 0xC0) != 0x80) return 4;
        c += kj_cast(u32, (*str++ & 0x3F) << 6);
        if((*str & 0xC0) != 0x80) return 4;
        c += (*str++ & 0x3F);
        if((c & 0xFFFFF800) == 0xD800) return 4;
        *codepoint = c;
        return 4;
    }
    *codepoint = 0;
    return 0;
}

#if defined(KJ_SYS_WIN32)
i32 kj_ucs_from_utf8(WCHAR* ws, i32 wsize, const char* s, i32 size) {
    i32 res = KJ_SUCCESS;
    i32 count = !size ? -1: size;
    i32 wc = !wsize ? 0: wsize / kj_isize_of(WCHAR);
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
    i32 res = KJ_SUCCESS;
    i32 wc = !wsize ? -1: wsize / kj_isize_of(WCHAR);
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
    i32 count = !size ? -1: size;
    i32 wc = MultiByteToWideChar(CP_UTF8, 0, s, count, NULL, 0);
    if((res = kj_cast(WCHAR*, kj_alloc(1 + wc * kj_isize_of(WCHAR)))) != NULL) {
        MultiByteToWideChar(CP_UTF8, 0, s, count, res, wc);
        res[wc] = '\0';
    }
    return res;
}

char* kj_utf8_from_ucs_alloc(const WCHAR* ws, i32 wsize) {
    char* res = NULL;
    i32 wc = !wsize ? -1: wsize / kj_isize_of(WCHAR);
    i32 count = WideCharToMultiByte(CP_UTF8, 0, ws, wc, NULL, 0, NULL, NULL);
    if((res = kj_cast(char*, kj_alloc(count + 1))) != NULL) {
        WideCharToMultiByte(CP_UTF8, 0, ws, wc, res, count, NULL, NULL);
        res[count] = '\0';
    }
    return res;
}

KJ_INTERN __declspec(thread) WCHAR _KJ_WCHAR_BUF[KJ_STACK_BUF_SIZE];
#define _KJ_WCHAR_SIZE kj_isize_of(_KJ_WCHAR_BUF)

WCHAR* kj_ucs_from_utf8_malloca(const char* s, i32 size) {
    WCHAR* res = _KJ_WCHAR_BUF;
    if(kj_ucs_from_utf8(_KJ_WCHAR_BUF, _KJ_WCHAR_SIZE, s, size) > _KJ_WCHAR_SIZE) {
        res = kj_ucs_from_utf8_alloc(s, size);
    }
    return res;
}

KJ_INTERN __declspec(thread) char _KJ_CHAR_BUF[KJ_STACK_BUF_SIZE];
#define _KJ_CHAR_SIZE kj_isize_of(_KJ_CHAR_BUF)

char* kj_utf8_from_ucs_malloca(const WCHAR* ws, i32 wsize) {
    char* res = _KJ_CHAR_BUF;
    if(kj_utf8_from_ucs(_KJ_CHAR_BUF, _KJ_CHAR_SIZE, ws, wsize) > _KJ_CHAR_SIZE) {
        res = kj_utf8_from_ucs_alloc(ws, wsize);
    }
    return res;
}

void kj_ucs_from_utf8_freea(WCHAR* ws) {
    if(ws != _KJ_WCHAR_BUF) {
        kj_free(ws);
    }
}

void kj_utf8_from_ucs_freea(char* s) {
    if(s != _KJ_CHAR_BUF) {
        kj_free(s);
    }
}
#endif

kjString kj_string(const char* s, isize size, kjAllocator* a) {
    kj_validate(size >= 0, { return NULL; });

    kjString res = NULL;
    size = !size ? kj_str_size(s, 0): size;
    a = a ? a: KJ_HEAP_ALLOCATOR;
    kjStringHeader* header = kj_cast(kjStringHeader*, kj_allocator_alloc(a, kj_isize_of(kjStringHeader) + size + 1));
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
    kj_validate(s != NULL, { return; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    kj_allocator_free(header->allocator, header);
}

KJ_INLINE void kj_string_reset(kjString s) {
    kj_validate(s != NULL, { return; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    header->size = 0;
    s[0] = '\0';
}

KJ_INLINE isize kj_string_size(kjString s) {
    kj_validate(s != NULL, { return -1; });

    return KJ_STR_HEADER(s)->size;
}

KJ_INLINE isize kj_string_capacity(kjString s) {
    kj_validate(s != NULL, { return -1; });

    return KJ_STR_HEADER(s)->capacity;
}

KJ_INLINE isize kj_string_available(kjString s) {
    kj_validate(s != NULL, { return -1; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    isize res = header->capacity - header->size;
    return res;
}

KJ_INLINE kjString kj_string_end(kjString s) {
    kj_validate(s != NULL, { return NULL; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    kjString res = s + header->size;
    return res;
}

KJ_INLINE kjString kj_string_extend(kjString s, isize size) {
    kj_validate(s != NULL && size > 0, { return NULL; });

    kjString res = s;
    if(kj_string_available(s) < size) {
        kjStringHeader* header = KJ_STR_HEADER(s);
        kjAllocator* a = header->allocator;
        isize cur_size = header->size;
        isize new_capacity = cur_size + size * 2.0f;

        kjStringHeader* new_header = kj_cast(kjStringHeader*,
                kj_allocator_realloc(a, KJ_STR_HEADER(s), kj_isize_of(kjStringHeader) + new_capacity + 1));
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

KJ_INLINE kjString kj_string_resize(kjString s, isize size) {
    return kj_string_extend(s, kj_abs(kj_string_size(s) - size));
}

KJ_INLINE kjString kj_string_append(kjString a, kjString b) {
    return kj_string_append_str(a, b, kj_string_size(b));
}

KJ_INLINE kjString kj_string_append_str(kjString a, const char* b, isize size) {
    kj_validate(a != NULL && b != NULL && size >= 0, { return NULL; });

    kjString res = NULL;
    isize a_size = kj_string_size(a);
    isize b_size = !size ? kj_str_size(b, 0): size;
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
    kj_validate(s != NULL, { return NULL; });

    kjStringHeader* header = KJ_STR_HEADER(s);
    return kj_string(s, header->size, header->allocator);
}

KJ_INLINE kjString kj_string_slice(kjString s, isize start, isize end) {
    kj_validate(s != NULL && start < kj_string_size(s) && end < kj_string_size(s) && start + end < kj_string_size(s), {
        return NULL;
    });
    kjStringHeader* header = KJ_STR_HEADER(s);
    kjString res = kj_string(header->data + start, end - start, header->allocator);
    return res;
}

kjString kj_string_from_file(kjString s, const char* path, kjAllocator* a) {
    kj_validate(path != NULL, { return NULL; });

    kjString res = NULL;
    kjFd fd;
    if(kj_is_success(kj_file_open(&fd, path, KJ_O_READ))) {
        kjFileMetadata meta;
        if(kj_is_success(kj_file_metadata(&meta, fd))) {
            if(s) {
                res = kj_string_resize(s, meta.size);
            } else {
                res = kj_string(NULL, meta.size, a);
            }
            if(res) {
                kjStringHeader* header = KJ_STR_HEADER(res);
                header->size = kj_cast(i16, kj_file_read(fd, res, meta.size));
            }
        }
    }
    return res;
}

KJ_INLINE KJ_CMP_FN(kj_cmp_string) {
    char* a = kj_cast(char**, arr)[i];
    char* b = kj_cast(char**, arr)[j];
    return kj_cast(kjOrdering, kj_str_cmp(a, b, 0));
}

#define KJ_CMP_FN_DEF(type, name, T)                                                                                    \
    KJ_INLINE KJ_CMP_FN(kj_cmp_##T) {                                                                                   \
        T a = kj_cast(T*, arr)[i];                                                                                      \
        T b = kj_cast(T*, arr)[j];                                                                                      \
        return kj_cast(kjOrdering, a < b ? -1: a > b);                                                                  \
    }
    KJ_TYPE_MAP(KJ_CMP_FN_DEF)
#undef KJ_CMP_FN_DEF

KJ_INLINE KJ_SWAP_FN(kj_swap_string) {
    char** values = kj_cast(char**, arr);
    char* tmp = values[i];
    values[i] = values[j];
    values[j] = tmp;
}

#define KJ_SWAP_FN_DEF(type, name, T)                                                                                   \
    KJ_INLINE KJ_SWAP_FN(kj_swap_##T) {                                                                                 \
        T* values = kj_cast(T*, arr);                                                                                   \
        T tmp = values[i];                                                                                              \
        values[i] = values[j];                                                                                          \
        values[j] = tmp;                                                                                                \
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
KJ_INLINE void _kj_systime_to_datetime(SYSTEMTIME* st, kjDateTime* dt) {
#elif defined(KJ_SYS_UNIX)
KJ_INLINE void _kj_systime_to_datetime(struct tm* tm, kjDateTime* dt) {
#endif
#if defined(KJ_SYS_WIN32)
    dt->year = st->wYear;
    dt->month = st->wMonth;
    dt->day = st->wDay;
    dt->hours = st->wHour;
    dt->minutes = st->wMinute;
    dt->seconds = st->wSecond;
    dt->milliseconds = st->wMilliseconds;
    dt->tz = 0;
#elif defined(KJ_SYS_UNIX)
    dt->year = 1900 + tm->tm_year;
    dt->month = tm->tm_mon + 1;
    dt->day = tm->tm_mday;
    dt->hours = tm->tm_hour;
    dt->minutes = tm->tm_min;
    dt->seconds = tm->tm_sec;
    dt->milliseconds = 0;
    dt->tz = 0;
#endif
}

#if defined(KJ_SYS_WIN32)
KJ_INLINE u64 _kj_filetime_to_unix(FILETIME* ft) {
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
    res = _kj_filetime_to_unix(&ft);
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
    st.wMinute = dt.minutes;
    st.wSecond = dt.seconds;
    st.wMilliseconds = dt.milliseconds;
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    res = _kj_filetime_to_unix(&ft);
#elif defined(KJ_SYS_UNIX)
    struct tm tm;
    kj_mem_zero(&tm, kj_isize_of(struct tm));
    tm.tm_year = dt.year - 1900;
    tm.tm_mon = dt.month - 1;
    tm.tm_mday = dt.day;
    tm.tm_hour = dt.hours;
    tm.tm_min = dt.minutes;
    tm.tm_sec = dt.seconds;
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
    _kj_systime_to_datetime(&st, &res);
    res.tz = 0;
#elif defined(KJ_SYS_UNIX)
    time_t t;
    syscall(SYS_time, &t);
    struct tm* tm = gmtime(&t);
    _kj_systime_to_datetime(tm, &res);
#endif
    return res;
}

KJ_INLINE kjDateTime kj_datetime_local(void) {
    kjDateTime res;
#if defined(KJ_SYS_WIN32)
    SYSTEMTIME st;
    GetLocalTime(&st);
    _kj_systime_to_datetime(&st, &res);
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
    _kj_systime_to_datetime(tm, &res);
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
    kj_validate(s != NULL && size >= 0, { return 0; });

    u32 res = 0;
    size = !size ? kj_str_size(s, 0): size;
    isize i;
    for(i = 0; (i < size) || (*s && !size); i++) {
        res += (*s++) * (kj_cast(u32, i % U32_MAX) + 119);
    }
    return res;
}

KJ_INTERN const u32 _KJ_CRC32_TABLE[256] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

u32 kj_hash_crc32(const void* data, isize size, u32 crc) {
    u32 res = ~kj_cast(u32, crc);
    u8* buf = kj_cast(u8*, data);
    for(isize i = 0; i < size; ++i ) {
        res = (res >> 8) ^ _KJ_CRC32_TABLE[(res ^ buf[i]) & 0xFF];
    }
    res = ~res;
    return res;
}

KJ_INLINE kjResult kj_file_create(kjFd* fd, const char* path, u32 flags) {
    flags &= KJ_O_USR_RWX | KJ_O_GRP_RWX | KJ_O_OTH_RWX;
    return kj_file_open(fd, path, KJ_O_WRITE | KJ_O_CREATE | KJ_O_TRUNCATE | flags);
}

KJ_INLINE u32 _kj_file_access_flags(u32 flags) {
    u32 res = 0;
    u32 read = flags & KJ_O_READ;
    u32 write = flags & KJ_O_WRITE;
    u32 append = flags & KJ_O_APPEND;
    if(read && !write && !append) {
#if defined(KJ_SYS_WIN32)
        res = GENERIC_READ;
#elif defined(KJ_SYS_UNIX)
        res = 00;
#endif
    } elif(!read && write && !append) {
#if defined(KJ_SYS_WIN32)
        res = GENERIC_WRITE;
#elif defined(KJ_SYS_UNIX)
        res = 01;
#endif
    } elif(read && write && !append) {
#if defined(KJ_SYS_WIN32)
        res = GENERIC_READ | GENERIC_WRITE;
#elif defined(KJ_SYS_UNIX)
        res = 02;
#endif
    } elif(!read && append) {
#if defined(KJ_SYS_WIN32)
        res = FILE_GENERIC_WRITE & ~FILE_WRITE_DATA;
#elif defined(KJ_SYS_UNIX)
        res = 01 | 02000;
#endif
    } elif(read && append) {
#if defined(KJ_SYS_WIN32)
        res = GENERIC_READ | (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA);
#elif defined(KJ_SYS_UNIX)
        res = 02 | 02000;
#endif
    }
#if defined(KJ_SYS_UNIX)
    if(flags & KJ_O_NONBLOCK) {
        res |= 04000;
    }
#endif
    return res;
}

KJ_INLINE u32 _kj_file_create_flags(u32 flags) {
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
    if(!res) {
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
            res = 0100;
#endif
        } elif(!create && trunc && !create_new) {
#if defined(KJ_SYS_WIN32)
            res = TRUNCATE_EXISTING;
#elif defined(KJ_SYS_UNIX)
            res = 01000;
#endif
        } elif(create && trunc && !create_new) {
#if defined(KJ_SYS_WIN32)
            res = CREATE_ALWAYS;
#elif defined(KJ_SYS_UNIX)
            res = 0100 | 01000;
#endif
        } elif(create_new) {
#if defined(KJ_SYS_WIN32)
            res = CREATE_NEW;
#elif defined(KJ_SYS_UNIX)
            res = 0100 | 0200;
#endif
        }
    }
    return res;
}

kjResult kj_file_open(kjFd* fd, const char* path, u32 flags) {
    kj_validate(path != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
    u32 access = _kj_file_access_flags(flags);
    u32 create = _kj_file_create_flags(flags);
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    *fd = CreateFileW(wpath, access, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, create, FILE_ATTRIBUTE_NORMAL, NULL);
    if(*fd == INVALID_HANDLE_VALUE) {
        *fd = KJ_FD_INVALID;
        res = kj_os_error();
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    u32 perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if((*fd = syscall(SYS_open, path, (access | create), perm)) == -1) {
        *fd = KJ_FD_INVALID;
        res = kj_os_error();
    }
#endif
    return res;
}

kjResult kj_file_close(kjFd fd) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    if(!CloseHandle(fd)) {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_close, fd) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_file_seek(kjFd fd, i64 offset, kjSeekFrom seek) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    LARGE_INTEGER li_offset;
    li_offset.QuadPart = offset;
    if(!SetFilePointerEx(fd, li_offset, &li_offset, seek)) {
        res = kj_os_error();
    } else {
        res = kj_cast(isize, li_offset.QuadPart);
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_lseek, fd, offset, seek)) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_file_pos(kjFd fd) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    LARGE_INTEGER li_offset;
    li_offset.QuadPart = 0;
    if(!SetFilePointerEx(fd, li_offset, &li_offset, KJ_SEEK_CURRENT)) {
        res = kj_os_error();
    } else {
        res = kj_cast(isize, li_offset.QuadPart);
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_lseek, fd, 0, KJ_SEEK_CURRENT)) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_file_read(kjFd fd, void* buf, isize size) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });
    kj_validate(buf != NULL && size > 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    DWORD read = 0;
    if(ReadFile(fd, buf, kj_cast(DWORD, size), &read, NULL)) {
        res = read;
    } else {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_read, fd, buf, size)) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_file_write(kjFd fd, void* buf, isize size) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });
    kj_validate(buf != NULL && size > 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    DWORD wrote = 0;
    if(WriteFile(fd, buf, kj_cast(DWORD, size), &wrote, NULL)) {
        res = wrote;
    } else {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_write, fd, buf, size)) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_file_read_at(kjFd fd, void* buf, isize size, i64 offset) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });
    kj_validate(buf != NULL && size > 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped;
    kj_mem_zero(&overlapped, kj_isize_of(OVERLAPPED));
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(fd, buf, kj_cast(DWORD, size), &read, &overlapped)) {
        res = read;
    } else {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_pread64, fd, buf, size, offset)) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_file_write_at(kjFd fd, void* buf, isize size, i64 offset) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });
    kj_validate(buf != NULL && size > 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    OVERLAPPED overlapped;
    kj_mem_zero(&overlapped, kj_isize_of(OVERLAPPED));
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(fd, buf, kj_cast(DWORD, size), &wrote, &overlapped)) {
        res = wrote;
    } else {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = syscall(SYS_pwrite64, fd, buf, size, offset)) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

kjResult kj_file_sync(kjFd fd) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    if(!FlushFileBuffers(fd)) {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_fsync, fd) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_file_path(kjFd fd, char* path, isize size) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    res = _kj_char_compute_known(path, size, _kj_GetFinalPathNameByHandle, fd);
#elif defined(KJ_SYS_UNIX)
    char fd_buf[32];
    kj_mem_zero(fd_buf, kj_isize_of(fd_buf));
    kj_snprintf(fd_buf, kj_isize_of(fd_buf), "/proc/self/fd/%d", fd);
    res = _kj_char_compute_unknown(path, size, _kj_readlink, fd_buf);
#endif
    return res;
}

isize kj_file_map(void** buf, kjFd fd, u32 flags) {
    kj_unused(flags);
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });
    kj_validate(buf != NULL, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    kjFileMetadata meta;
    if(kj_is_success(res = kj_file_metadata(&meta, fd))) {
        kjFd map = CreateFileMappingW(fd, NULL, PAGE_WRITECOPY, 0, 0, NULL);
        if(map == NULL) {
            res = kj_os_error();
        } else {
            if((*buf = MapViewOfFileEx(map, FILE_MAP_COPY, 0, 0, 0, 0)) == NULL) {
                res = kj_os_error();
            } else {
                res = meta.size;
            }
        }
    }
#elif defined(KJ_SYS_UNIX)
    kjFileMetadata meta;
    if(kj_is_success(res = kj_file_metadata(&meta, fd))) {
        if((*buf = mmap(NULL, meta.size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
            res = kj_os_error();
        } else {
            res = meta.size;
        }
    }
#endif
    return res;
}

isize kj_file_map_path(void** buf, kjFd* fd, const char* path, u32 flags) {
    kj_validate(fd != NULL, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    if(kj_is_success(res = kj_file_open(fd, path, KJ_O_READ))) {
        res = kj_file_map(buf, *fd, flags);
    }
    return res;
}

kjResult kj_file_unmap(void* buf, kjFd fd) {
    kj_validate(buf != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    if(!UnmapViewOfFile(buf)) {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_munmap, buf, 0) == -1) {
        res = kj_os_error();
    }
#endif
    kj_file_close(fd);
    return res;
}

isize kj_file_slurp(void** out, const char* path, kjAllocator* a) {
    kj_validate(out != NULL && path != NULL, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    a = a ? a: KJ_HEAP_ALLOCATOR;
    kjFd fd;
    if(kj_is_success(res = kj_file_open(&fd, path, KJ_O_READ))) {
        kjFileMetadata meta;
        if(kj_is_success(res = kj_file_metadata(&meta, fd))) {
            *out = kj_cast(char*, kj_allocator_alloc(a, meta.size + 1));
            if(*out) {
                res = kj_file_read(fd, *out, meta.size);
                if(res <= meta.size) {
                    kj_cast(char*, *out)[res] = '\0';
                }
            } else {
                res = KJ_ERROR_ALLOC;
            }
        }
    }
    return res;
}

isize kj_file_spit(const char* path, void* buf, isize size) {
    kj_validate(buf != NULL && path != NULL && size >= 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
    kjFd fd;
    if(kj_is_success(res = kj_file_create(&fd, path, KJ_O_USR_R | KJ_O_USR_W | KJ_O_GRP_R | KJ_O_OTH_R))) {
        res = kj_file_write(fd, buf, size);
        kj_file_close(fd);
    }
    return res;
}

kjResult kj_file_metadata(kjFileMetadata* meta, kjFd fd) {
    kj_validate(fd != KJ_FD_INVALID, { return KJ_ERROR_BAD_HANDLE; });
    kj_validate(meta != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
    kj_mem_zero(meta, kj_isize_of(kjFileMetadata));
#if defined(KJ_SYS_WIN32)
    BY_HANDLE_FILE_INFORMATION info;
    if(GetFileInformationByHandle(fd, &info)) {
        meta->size =
            (kj_cast(i64, info.nFileSizeHigh) << 32) |
            (kj_cast(i64, info.nFileSizeLow));
        meta->last_access = _kj_filetime_to_unix(&info.ftLastAccessTime);
        meta->last_write = _kj_filetime_to_unix(&info.ftLastWriteTime);
        if(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            meta->type = KJ_DIR;
        } else {
            meta->type = KJ_FILE;
        }
    } else {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    struct stat st;
    kj_mem_zero(&st, kj_isize_of(struct stat));
    if(syscall(SYS_fstat, fd, &st) == -1) {
        res = kj_os_error();
    } else {
        meta->size = st.st_size;
        meta->last_access = kj_cast(u64, st.st_atime);
        meta->last_write = kj_cast(u64, st.st_mtime);
    }
#endif
    return res;
}

kjResult kj_file_metadata_path(kjFileMetadata* meta, const char* path) {
    kj_validate(meta != NULL && path != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_UNIX)
    struct stat st;
    kj_mem_zero(&st, kj_isize_of(struct stat));
    if(syscall(SYS_stat, path, &st) == -1) {
        res = kj_os_error();
    } else {
        meta->size = st.st_size;
        meta->last_access = kj_cast(u64, st.st_atime);
        meta->last_write = kj_cast(u64, st.st_mtime);
    }
#else
    kjFd fd;
    if(kj_is_success(res = kj_file_open(&fd, path, KJ_O_READ))) {
        res = kj_file_metadata(meta, fd);
        kj_file_close(fd);
    }
#endif
    return res;
}

const char* kj_path_ext(const char* path, isize size) {
    kj_validate(path != NULL && size >= 0, { return NULL; });

    const char* res = NULL;
    size = !size ? kj_str_size(path, 0): size;
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
    kj_validate(path != NULL && size >= 0 && end != NULL, { return "."; });

    const char* res = NULL;
    size = !size ? kj_str_size(path, 0): size;
    if(!size) {
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
    kj_validate(path != NULL && size >= 0 && end != NULL, { return "."; });

    const char* res = NULL;
    size = !size ? kj_str_size(path, 0): size;
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

kjResult kj_path_create_dir(const char* path) {
    kj_validate(path != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    if(CreateDirectoryW(wpath, NULL) == FALSE) {
        res = kj_os_error();
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    u32 mode = S_IRWXU | S_IRGRP | S_IROTH;
    if(syscall(SYS_mkdir, path, mode) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

kjResult kj_path_remove_dir(const char* path) {
    kj_validate(path != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    if(RemoveDirectoryW(wpath) == FALSE) {
        res = kj_os_error();
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_rmdir, path) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

kjResult kj_path_rename(const char* from, const char* to, u32 flags) {
    kj_validate(from != NULL && to != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    WCHAR* wfrom = kj_ucs_from_utf8_malloca(from, 0);
    WCHAR* wto = kj_ucs_from_utf8_malloca(to, 0);
    if(MoveFileExW(wfrom, wto, MOVEFILE_REPLACE_EXISTING) == FALSE) {
        res = kj_os_error();
    }
    kj_ucs_from_utf8_freea(wfrom);
    kj_ucs_from_utf8_freea(wto);
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_renameat2, -100, from, -100, to, flags) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_path_current_dir(char* path, isize size) {
    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    res = _kj_char_compute_known(path, size, _kj_GetCurrentDirectoryW);
#elif defined(KJ_SYS_UNIX)
    res = _kj_char_compute_unknown(path, size, _kj_getcwd);
#endif
    return res;
}

kjResult kj_path_set_current_dir(const char* path) {
    kj_validate(path != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    WCHAR* wpath = kj_ucs_from_utf8_malloca(path, 0);
    if(SetCurrentDirectoryW(wpath) == FALSE) {
        res = kj_os_error();
    }
    kj_ucs_from_utf8_freea(wpath);
#elif defined(KJ_SYS_UNIX)
    if(syscall(SYS_chdir, path) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

isize kj_path_tmp_dir(char* path, isize size) {
    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    res = _kj_char_compute_unknown(path, size, _kj_GetTempPathW);
#elif defined(KJ_SYS_UNIX)
    res = kj_env_var("TMPDIR", path, size);
#endif
    return res;
}

isize kj_path_self(char* path, isize size) {
    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    res = _kj_char_compute_unknown(path, size, _kj_GetModuleFileNameW);
#elif defined(KJ_SYS_UNIX)
    res = _kj_char_compute_unknown(path, size, _kj_readlink, "/proc/self/exe");
#endif
    return res;
}

b32 kj_path_exists(const char* path) {
    kj_validate(path != NULL, { return KJ_FALSE; });

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
    kj_validate(path != NULL, { return KJ_FALSE; });

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
    kj_validate(path != NULL, { return KJ_FALSE; });

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

kjResult kj_read_dir(kjReadDir* dir, const char* path) {
    kj_validate(dir != NULL && path != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    kj_unused(dir);
    kj_unused(path);
    kj_unimplemented();
#elif defined(KJ_SYS_UNIX)
    kj_mem_zero(dir, kj_isize_of(kjReadDir));
    dir->dir = opendir(path);
    if(dir->dir) {
        dir->ent = NULL;
    } else {
        dir->ent = NULL;
        res = kj_os_error();
    }
#endif
    return res;
}

kjResult kj_read_dir_next(kjReadDir* dir, const char** path) {
    kj_validate(dir != NULL && path != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    kj_unused(dir);
    kj_unused(path);
    kj_unimplemented();
#elif defined(KJ_SYS_UNIX)
    dir->ent = readdir(dir->dir);
    if(dir->ent) {
        *path = dir->ent->d_name;
    } else {
        *path = NULL;
        closedir(dir->dir);
        res = KJ_ERROR_NOT_FOUND;
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

b32 kj_socket_begin(void) {
#if defined(KJ_SYS_WIN32)
    WSADATA wsa;
    return WSAStartup(0x202, &wsa) == NO_ERROR;
#elif defined(KJ_SYS_LINUX)
    return KJ_TRUE;
#endif
}

void kj_socket_end(void) {
#if defined(KJ_SYS_WIN32)
    WSACleanup();
#elif defined(KJ_SYS_LINUX)
#endif
}

kjResult kj_socket_open(kjSocket* sock, kjSocketAddr addr) {
    kj_validate(sock != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
    i32 type = addr == KJ_SOCKET_ADDR_V4 ? AF_INET: AF_INET6;
    if((sock->handle = socket(type, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        res = kj_os_error();
    }
    return res;
}

void kj_socket_close(kjSocket* sock) {
    kj_validate(sock != NULL && socket->handle != INVALID_SOCKET, { return; });

#if defined(KJ_SYS_WIN32)
    closesocket(sock->handle);
#elif defined(KJ_SYS_LINUX)
    close(sock->handle);
#endif
}

kjResult kj_socket_connect(kjSocket* sock, const char* ip, u16 port) {
    kj_validate(sock != NULL && ip != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
    kj_mem_zero(&sock->addr, kj_isize_of(struct sockaddr_in));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = inet_addr(ip);
    sock->addr.sin_port = htons(port);

    if(connect(sock->handle, kj_cast(struct sockaddr*, &sock->addr), kj_isize_of(struct sockaddr_in)) == SOCKET_ERROR) {
        res = kj_os_error();
        kj_socket_close(sock);
    }
    return res;
}

kjResult kj_socket_bind(kjSocket* sock, u16 port, u32 flags) {
    kj_validate(sock != NULL && sock->handle != INVALID_SOCKET, {
        return KJ_ERROR_PARAM;
    });

    kjResult res = KJ_SUCCESS;
    kj_mem_zero(&sock->addr, kj_isize_of(struct sockaddr_in));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = htonl(flags & KJ_SOCKET_LOCAL ? INADDR_LOOPBACK: INADDR_ANY);
    sock->addr.sin_port = htons(port);
    i32 reuse = 1;
#if defined(KJ_SYS_WIN32)
    setsockopt(sock->handle, SOL_SOCKET, SO_REUSEADDR, kj_cast(char*, &reuse), kj_isize_of(i32));
    reuse = 1;
    setsockopt(sock->handle, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, kj_cast(char*, &reuse), kj_isize_of(i32));
#elif defined(KJ_SYS_LINUX)
    setsockopt(sock->handle, SOL_SOCKET, SO_REUSEADDR, &reuse, kj_isize_of(i32));
#endif
    if(bind(sock->handle, kj_cast(struct sockaddr*, &sock->addr), kj_isize_of(struct sockaddr_in)) == SOCKET_ERROR) {
        res = kj_os_error();
        kj_socket_close(sock);
    }
    return res;
}

kjResult kj_socket_listen(kjSocket* sock, isize conn) {
    kj_validate(sock != NULL && sock->handle != INVALID_SOCKET && conn > 0, {
        return KJ_ERROR_PARAM;
    });

    kjResult res = KJ_SUCCESS;
    if(listen(sock->handle, kj_min(conn, SOMAXCONN)) == SOCKET_ERROR) {
        res = kj_os_error();
        kj_socket_close(sock);
    }
    return res;
}

kjResult kj_socket_accept(kjSocket* sock, kjSocket* client) {
    kj_validate(sock != NULL && sock->handle != INVALID_SOCKET && client != NULL, {
        return KJ_ERROR_PARAM;
    });

    kjResult res = KJ_SUCCESS;
    SOCKET s;
    if((s = accept(sock->handle, NULL, NULL)) == SOCKET_ERROR) {
        res = kj_os_error();
        kj_socket_close(sock);
    } else {
        kj_mem_zero(client, kj_isize_of(kjSocket));
        client->handle = s;
    }
    return res;
}

isize kj_socket_read(kjSocket* sock, void* buf, isize size) {
    kj_validate(sock != NULL && sock->handle != INVALID_SOCKET && buf != NULL && size > 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
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
        res = kj_os_error();
    }
    return res;
}

isize kj_socket_write(kjSocket* sock, const void* buf, isize size) {
    kj_validate(sock != NULL && sock->handle != INVALID_SOCKET && buf != NULL && size > 0, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
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
        res = kj_os_error();
    }
    return res;
}

#endif
