/*
 * `kj_thread.h`
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
 *      #define KJ_THREAD_IMPL
 *      #include "kj_thread.h"
 */

#ifndef KJ_THREAD_H
#define KJ_THREAD_H

#define KJ_THREAD_VERSION_MAJOR 0
#define KJ_THREAD_VERSION_MINOR 4
#define KJ_THREAD_VERSION_PATCH 0

#if defined(__cplusplus)
extern "C" {
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
#include <intrin.h>
#if !defined(KJ_SYS_WIN32)
#define KJ_SYS_WIN32
#endif
#pragma comment(lib, "kernel32.lib")
#elif defined(__unix__) || defined(__CYGWIN__) || defined(__MSYS__)
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <sys/syscall.h>
#if !defined(KJ_SYS_UNIX)
#define KJ_SYS_UNIX
#endif
#else
#error "Unsupported Operating System"
#endif

#if defined(_MSC_VER)
#if !defined(KJ_COMPILER_MSVC)
#define KJ_COMPILER_MSVC _MSC_VER
#endif
#elif defined(__clang__)
#if !defined(KJ_COMPILER_CLANG)
#define KJ_COMPILER_CLANG
#endif
#elif defined(__GNUC__) || defined(__GNUG__)
#if !defined(KJ_COMPILER_GNU)
#define KJ_COMPILER_GNU
#endif
#else
#error "Unsupported Compiler"
#endif

#if !defined(KJ_ALIGN)
#if defined(KJ_COMPILER_MSVC)
#define KJ_ALIGN(a) __declspec(align(a))
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_ALIGN(a) __attribute__((aligned(a)))
#endif
#endif

#if defined(KJ_COMPILER_MSVC)
#if KJ_COMPILER_MSVC < 1300
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
#else
typedef signed __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef signed __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include <stdbool.h>

#if !defined(KJ_API)
#if defined(KJ_STATIC)
#define KJ_API static
#else
#define KJ_API extern
#endif
#endif

#if !defined(KJ_ARCH)
#if defined(_WIN64) || defined(__x86_64__) || defined(_M_X64) || defined(__64BIT__) || defined(__powerpc64__) || defined(__ppc64__) || defined(__aarch64__)
#define KJ_ARCH (64)
#elif defined(__i386__) || defined(_M_IX86) || defined(_X86_) || defined(__arm__) || defined(_M_ARM) || defined(__mips__) || defined(_M_PPC) || defined(__powerpc__)
#define KJ_ARCH (32)
#endif
#endif

enum {
    KJ_THREAD_NONE = 0,
    KJ_THREAD_SUSPENDED = 1 << 0
};

#if defined(KJ_SYS_WIN32)
typedef CRITICAL_SECTION kjMutex;
typedef HANDLE kjSemaphore;
typedef uint32_t kjTls;
#define KJ_TLS_INVALID ((uint32_t) -1)
#elif defined(KJ_SYS_UNIX)
typedef pthread_mutex_t kjMutex;
typedef sem_t kjSemaphore;
typedef pthread_key_t kjTls;
#define KJ_TLS_INVALID ((pthread_key_t) -1)
#endif

#define KJ_THREAD_FN(name) void* name(void* data)
typedef KJ_THREAD_FN(kjThreadFn);

typedef struct kjThread {
#if defined(KJ_SYS_WIN32)
    HANDLE handle;
#elif defined(KJ_SYS_UNIX)
    pthread_t handle;
#endif
    uint32_t flags;
    kjThreadFn* fn;
    void* data;
    void* res;
} kjThread;

#if !defined(KJ_TLS)
#if defined(KJ_COMPILER_MSVC)
#define KJ_TLS __declspec(thread)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_TLS __thread
#endif
#endif

#if defined(KJ_COMPILER_MSVC)
typedef struct kjAtomic32 { volatile LONG value; } kjAtomic32;
typedef struct kjAtomic64 { volatile LONG64 value; } kjAtomic64;
#if KJ_ARCH == 32
typedef struct kjAtomicPtr { volatile PVOID value; } kjAtomicPtr;
#elif KJ_ARCH == 64
typedef struct kjAtomicPtr { volatile PVOID value; } kjAtomicPtr;
#endif
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
typedef struct kjAtomic32 { KJ_ALIGN(4) volatile uint32_t value; } kjAtomic32;
typedef struct kjAtomic64 { KJ_ALIGN(8) volatile uint64_t value; } kjAtomic64;
#if KJ_ARCH == 32
typedef struct kjAtomicPtr { KJ_ALIGN(4) volatile void* value; } kjAtomicPtr;
#elif KJ_ARCH == 64
typedef struct kjAtomicPtr { KJ_ALIGN(8) volatile void* value; } kjAtomicPtr;
#endif
#endif

KJ_API void kj_yield(void);
KJ_API void kj_sleep_ms(uint32_t ms);

KJ_API bool kj_thread(kjThread* thread, kjThreadFn* fn, void* data, uint32_t flags);
KJ_API void kj_thread_start(kjThread* thread);
KJ_API void* kj_thread_join(kjThread* thread);
KJ_API void kj_thread_detach(kjThread* thread);
KJ_API void kj_thread_set_name(kjThread* thread, const char* name);
KJ_API uint32_t kj_thread_id(void);

KJ_API bool kj_tls(kjTls* tls);
KJ_API void kj_tls_destroy(kjTls tls);
KJ_API void kj_tls_set(kjTls tls, void* value);
KJ_API void* kj_tls_get(kjTls tls);

KJ_API bool kj_mutex(kjMutex* mutex);
KJ_API void kj_mutex_destroy(kjMutex* mutex);
KJ_API void kj_mutex_lock(kjMutex* mutex);
KJ_API bool kj_mutex_try_lock(kjMutex* mutex);
KJ_API void kj_mutex_unlock(kjMutex* mutex);

KJ_API bool kj_semaphore(kjSemaphore* semaphore, int32_t count);
KJ_API void kj_semaphore_destroy(kjSemaphore* semaphore);
KJ_API bool kj_semaphore_wait(kjSemaphore* semaphore, int32_t ms);
KJ_API bool kj_semaphore_try_wait(kjSemaphore* semaphore);
KJ_API void kj_semaphore_signal(kjSemaphore* semaphore, int32_t count);

KJ_API void kj_atomic_read_fence(void);
KJ_API void kj_atomic_write_fence(void);
KJ_API void kj_atomic_rw_fence(void);

KJ_API uint32_t kj_atomic32_load(kjAtomic32* v);
KJ_API void kj_atomic32_store(kjAtomic32* v, uint32_t value);
KJ_API bool kj_atomic32_cmp_swap(kjAtomic32* v, uint32_t cmp, uint32_t swap);
KJ_API uint32_t kj_atomic32_swap(kjAtomic32* v, uint32_t swap);
KJ_API uint32_t kj_atomic32_inc(kjAtomic32* v);
KJ_API uint32_t kj_atomic32_dec(kjAtomic32* v);
KJ_API uint32_t kj_atomic32_fetch_add(kjAtomic32* v, uint32_t op);
KJ_API uint32_t kj_atomic32_fetch_sub(kjAtomic32* v, uint32_t op);
KJ_API uint32_t kj_atomic32_fetch_or(kjAtomic32* v, uint32_t op);
KJ_API uint32_t kj_atomic32_fetch_and(kjAtomic32* v, uint32_t op);
KJ_API uint32_t kj_atomic32_fetch_xor(kjAtomic32* v, uint32_t op);

KJ_API uint64_t kj_atomic64_load(kjAtomic64* v);
KJ_API void kj_atomic64_store(kjAtomic64* v, uint64_t value);
KJ_API bool kj_atomic64_cmp_swap(kjAtomic64* v, uint64_t cmp, uint64_t swap);
KJ_API uint64_t kj_atomic64_swap(kjAtomic64* v, uint64_t swap);
KJ_API uint64_t kj_atomic64_inc(kjAtomic64* v);
KJ_API uint64_t kj_atomic64_dec(kjAtomic64* v);
KJ_API uint64_t kj_atomic64_fetch_add(kjAtomic64* v, uint64_t op);
KJ_API uint64_t kj_atomic64_fetch_sub(kjAtomic64* v, uint64_t op);
KJ_API uint64_t kj_atomic64_fetch_or(kjAtomic64* v, uint64_t op);
KJ_API uint64_t kj_atomic64_fetch_and(kjAtomic64* v, uint64_t op);
KJ_API uint64_t kj_atomic64_fetch_xor(kjAtomic64* v, uint64_t op);

KJ_API void* kj_atomic_ptr_load(kjAtomicPtr* v);
KJ_API void kj_atomic_ptr_store(kjAtomicPtr* v, void* value);
KJ_API bool kj_atomic_ptr_cmp_swap(kjAtomicPtr* v, void* cmp, void* swap);
KJ_API void* kj_atomic_ptr_swap(kjAtomicPtr* v, void* swap);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_THREAD_IMPL)
void kj_yield(void) {
#if defined(KJ_SYS_WIN32)
    SwitchToThread();
#elif defined(KJ_SYS_UNIX)
    syscall(SYS_sched_yield);
#endif
}

void kj_sleep_ms(uint32_t ms) {
#if defined(KJ_SYS_WIN32)
    Sleep(ms);
#elif defined(KJ_SYS_UNIX)
    struct timespec ts;
    struct timespec elapsed;
    elapsed.tv_sec = (time_t) (ms / 1000),
    elapsed.tv_nsec = (uint32_t) ((ms % 1000) * 1000000);
    int32_t err = 0;
    do {
        errno = 0;
        ts.tv_sec = elapsed.tv_sec;
        ts.tv_nsec = elapsed.tv_nsec;
#if _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L
        err = syscall(SYS_clock_nanosleep, CLOCK_MONOTONIC, 0, &ts, &elapsed);
#else
        err = syscall(SYS_nanosleep, &ts, &elapsed);
#endif
    } while(err && errno == EINTR);
#endif
}

#if defined(KJ_SYS_WIN32)
static DWORD __cdecl _kj_win32_fn(LPVOID p) {
    kjThread* thread = (kjThread*) p;
    if(thread) {
        thread->res = thread->fn(thread->data);
    }
    return 0;
}
#elif defined(KJ_SYS_UNIX)
static void* _kj_pthread_fn(void* p) {
    kjThread* thread = (kjThread*) p;
    if(thread) {
        thread->res = thread->fn(thread->data);
    }
    return NULL;
}
#endif

void _kj_thread_start(kjThread* thread) {
#if defined(KJ_SYS_WIN32)
    thread->handle = CreateThread(NULL, 0, _kj_win32_fn, thread, 0, NULL);
#elif defined(KJ_SYS_UNIX)
    pthread_create(&thread->handle, NULL, _kj_pthread_fn, thread) == 0;
#endif
}

bool kj_thread(kjThread* thread, kjThreadFn* fn, void* data, uint32_t flags) {
    thread->fn = fn;
    thread->data = data;
    thread->res = NULL;
    thread->flags = flags;
    if((thread->flags & KJ_THREAD_SUSPENDED) != 1) {
        _kj_thread_start(thread);
        return thread->handle;
    }
    return true;
}

void kj_thread_start(kjThread* thread) {
    if(thread->flags & KJ_THREAD_SUSPENDED) {
        thread->flags &= ~KJ_THREAD_SUSPENDED;
        _kj_thread_start(thread);
    }
}

void* kj_thread_join(kjThread* thread) {
#if defined(KJ_SYS_WIN32)
    WaitForSingleObjectEx(thread->handle, INFINITE, FALSE);
    CloseHandle(thread->handle);
#elif defined(KJ_SYS_UNIX)
    pthread_join(thread->handle, NULL);
#endif
    return thread->res;
}

void kj_thread_detach(kjThread* thread) {
#if defined(KJ_SYS_WIN32)
    CloseHandle(thread->handle);
    thread->handle = NULL;
#elif defined(KJ_SYS_UNIX)
    pthread_detach(thread->handle);
#endif
}

void kj_thread_set_name(kjThread* thread, const char* name) {
#if 0 && defined(KJ_SYS_WIN32)
    const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push, 8)
    typedef struct tagTHREADNAME_INFO {
        DWORD type;
        LPCSTR name;
        DWORD id;
        DWORD flags;
    } THREADNAME_INFO;
#pragma pack(pop)
    THREADNAME_INFO info;
    info.type = 0x1000;
    info.name = name;
    info.id = GetThreadId(thread->handle);
    info.flags = 0;
    __try{
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*) &info);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
    }
#elif defined(KJ_SYS_UNIX)
    pthread_setname_np(thread->handle, name);
#endif
}

uint32_t kj_thread_id(void) {
#if defined(KJ_SYS_WIN32)
    return (uint32_t) GetCurrentThreadId();
#elif defined(KJ_SYS_UNIX)
    return (uint32_t) pthread_self();
#endif
}

bool kj_tls(kjTls* tls) {
#if defined(KJ_SYS_WIN32)
    if((*tls = TlsAlloc()) == TLS_OUT_OF_INDEXES) {
        *tls = KJ_TLS_INVALID;
        return false;
    }
#elif defined(KJ_SYS_UNIX)
    if((res = pthread_key_create(tls, NULL)) != 0) {
        *tls = KJ_TLS_INVALID;
        return false;
    }
#endif
    return true;
}

void kj_tls_destroy(kjTls tls) {
#if defined(KJ_SYS_WIN32)
    TlsFree(tls);
#elif defined(KJ_SYS_UNIX)
    pthread_key_delete(tls);
#endif
}

void kj_tls_set(kjTls tls, void* value) {
#if defined(KJ_SYS_WIN32)
    TlsSetValue(tls, value);
#elif defined(KJ_SYS_UNIX)
    pthread_setspecific(tls, value);
#endif
}

void* kj_tls_get(kjTls tls) {
#if defined(KJ_SYS_WIN32)
    return TlsGetValue(tls);
#elif defined(KJ_SYS_UNIX)
    return pthread_getspecific(tls);
#endif
}

bool kj_mutex(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    return InitializeCriticalSectionAndSpinCount(mutex, 4000);
#elif defined(KJ_SYS_UNIX)
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    bool res = pthread_mutex_init(mutex, &attr) == 0;
    pthread_mutexattr_destroy(&attr);
    return res;
#endif
}

void kj_mutex_destroy(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    DeleteCriticalSection(mutex);
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_destroy(mutex);
#endif
}

void kj_mutex_lock(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    if(kj_mutex_try_lock(mutex)) {
        EnterCriticalSection(mutex);
    }
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_lock(mutex);
#endif
}

bool kj_mutex_try_lock(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    return TryEnterCriticalSection(mutex) != 0;
#elif defined(KJ_SYS_UNIX)
    return pthread_mutex_trylock(mutex) == 0;
#endif
}

void kj_mutex_unlock(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    LeaveCriticalSection(mutex);
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_unlock(mutex);
#endif
}

bool kj_semaphore(kjSemaphore* semaphore, int32_t count) {
#if defined(KJ_SYS_WIN32)
    *semaphore = CreateSemaphore(NULL, count, count, NULL);
    return *semaphore;
#elif defined(KJ_SYS_UNIX)
    return sem_init(semaphore, 0, count) == 0;
#endif
}

void kj_semaphore_destroy(kjSemaphore* semaphore) {
#if defined(KJ_SYS_WIN32)
    CloseHandle(semaphore);
#elif defined(KJ_SYS_UNIX)
    sem_destroy(semaphore);
#endif
}

bool kj_semaphore_wait(kjSemaphore* semaphore, int32_t ms) {
#if defined(KJ_SYS_WIN32)
    uint32_t res = WaitForSingleObject(semaphore, ms < 0 ? INFINITE: ms);
    return res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT;
#elif defined(KJ_SYS_UNIX)
    if(ms <= 0) {
        return sem_wait(semaphore) == 0;
    } else {
        struct timespec ts;
        kj_mem_zero(&ts, sizeof(struct timespec));
        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000;
        return sem_timedwait(semaphore, &ts) == 0;
    }
#endif
}

bool kj_semaphore_try_wait(kjSemaphore* semaphore) {
#if defined(KJ_SYS_WIN32)
    return WaitForSingleObject(semaphore, 0) == WAIT_OBJECT_0;
#elif defined(KJ_SYS_UNIX)
    return sem_trywait(semaphore) == 0;
#endif
}

void kj_semaphore_signal(kjSemaphore* semaphore, int32_t count) {
#if defined(KJ_SYS_WIN32)
    ReleaseSemaphore(semaphore, count, NULL);
#elif defined(KJ_SYS_UNIX)
    while(count--) { sem_post(semaphore); }
#endif
}

void kj_atomic_read_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _ReadBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

void kj_atomic_write_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _WriteBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

void kj_atomic_rw_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _ReadWriteBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

uint32_t kj_atomic32_load(kjAtomic32* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchange(&v->value, v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_load_n(&v->value, __ATOMIC_SEQ_CST);
#endif
}

void kj_atomic32_store(kjAtomic32* v, uint32_t value) {
#if defined(KJ_COMPILER_MSVC)
    _InterlockedExchange(&v->value, value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __atomic_store_n(&v->value, value, __ATOMIC_SEQ_CST);
#endif
}

bool kj_atomic32_cmp_swap(kjAtomic32* v, uint32_t cmp, uint32_t swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchange(&v->value, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_compare_exchange_n(&v->value, &cmp, swap, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
}

uint32_t kj_atomic32_swap(kjAtomic32* v, uint32_t swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchange(&v->value, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_exchange_n(&v->value, swap, __ATOMIC_SEQ_CST);
#endif
}

uint32_t kj_atomic32_inc(kjAtomic32* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedIncrement(&v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_add(&v->value, 1, __ATOMIC_SEQ_CST);
#endif
}

uint32_t kj_atomic32_dec(kjAtomic32* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedDecrement(&v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_sub(&v->value, 1, __ATOMIC_SEQ_CST);
#endif
}

uint32_t kj_atomic32_fetch_add(kjAtomic32* v, uint32_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_add(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint32_t kj_atomic32_fetch_sub(kjAtomic32* v, uint32_t op) {
#if defined(KJ_COMPILER_MSVC)
    return InterlockedExchangeAdd(&v->value, -((int32_t) op));
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_sub(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint32_t kj_atomic32_fetch_or(kjAtomic32* v, uint32_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedOr(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_or(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint32_t kj_atomic32_fetch_and(kjAtomic32* v, uint32_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedAnd(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_and(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint32_t kj_atomic32_fetch_xor(kjAtomic32* v, uint32_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedXor(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_xor(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_load(kjAtomic64* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchange64(&v->value, v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_load_n(&v->value, __ATOMIC_SEQ_CST);
#endif
}

void kj_atomic64_store(kjAtomic64* v, uint64_t value) {
#if defined(KJ_COMPILER_MSVC)
    _InterlockedExchange64(&v->value, value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __atomic_store_n(&v->value, value, __ATOMIC_SEQ_CST);
#endif
}

bool kj_atomic64_cmp_swap(kjAtomic64* v, uint64_t cmp, uint64_t swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchange64(&v->value, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_compare_exchange_n(&v->value, &cmp, swap, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_swap(kjAtomic64* v, uint64_t swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchange64(&v->value, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_exchange_n(&v->value, swap, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_inc(kjAtomic64* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedIncrement64(&v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_add(&v->value, 1, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_dec(kjAtomic64* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedDecrement64(&v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_sub(&v->value, 1, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_fetch_add(kjAtomic64* v, uint64_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd64(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_add(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_fetch_sub(kjAtomic64* v, uint64_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd64(&v->value, -((int64_t) op));
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_sub(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_fetch_or(kjAtomic64* v, uint64_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedOr64(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_or(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_fetch_and(kjAtomic64* v, uint64_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedAnd64(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_and(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

uint64_t kj_atomic64_fetch_xor(kjAtomic64* v, uint64_t op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedXor64(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_xor(&v->value, op, __ATOMIC_SEQ_CST);
#endif
}

void* kj_atomic_load_ptr(kjAtomicPtr* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangePointer(&v->value, v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return (void*) __atomic_load_n(&v->value, __ATOMIC_SEQ_CST);
#endif
}

void kj_atomic_store_ptr(kjAtomicPtr* v, void* value) {
#if defined(KJ_COMPILER_MSVC)
    _InterlockedExchangePointer(&v->value, value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __atomic_store_n(&v->value, value, __ATOMIC_SEQ_CST);
#endif
}

bool kj_atomic_cmp_swap_ptr(kjAtomicPtr* v, void* cmp, void* swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchangePointer(&v->value, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_compare_exchange_n(&v->value, cmp, swap, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
}

void* kj_atomic_swap_ptr(kjAtomicPtr* v, void* swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangePointer(&v->value, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return (void*) __atomic_exchange_n(&v->value, swap, __ATOMIC_SEQ_CST);
#endif
}
#endif

/*
 * ---------------------------------- LICENSE ----------------------------------
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org>
 * =============================================================================
 */
