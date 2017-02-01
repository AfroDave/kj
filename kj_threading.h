/*
 * `kj_threading.h`
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
 *      #define KJ_THREADING_IMPL
 *      #include "kj_threading.h"
 */

#ifndef KJ_THREADING_H
#define KJ_THREADING_H

#define KJ_THREADING_VERSION_MAJOR 0
#define KJ_THREADING_VERSION_MINOR 4
#define KJ_THREADING_VERSION_PATCH 0

#if defined(__cplusplus)
extern "C" {
#endif

enum {
    KJ_THREAD_NONE = KJ_FLAG_NONE
};

#if defined(KJ_SYS_WIN32)
typedef CRITICAL_SECTION kjMutex;
typedef HANDLE kjSemaphore;
typedef u32 kjTls;
#define KJ_TLS_INVALID U32_MAX
#elif defined(KJ_SYS_UNIX)
#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <sys/syscall.h>
typedef pthread_mutex_t kjMutex;
typedef sem_t kjSemaphore;
typedef pthread_key_t kjTls;
#define KJ_TLS_INVALID kj_cast(pthread_key_t, U32_MAX)
#endif

#define KJ_THREAD_FN(name) void* name(void* data)
typedef KJ_THREAD_FN(kjThreadFn);

typedef struct kjThread {
#if defined(KJ_SYS_WIN32)
    HANDLE handle;
#elif defined(KJ_SYS_UNIX)
    pthread_t handle;
#endif
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
typedef volatile LONG kjAtomic32;
typedef volatile LONGLONG kjAtomic64;
typedef volatile PVOID kjAtomicPtr;
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
typedef KJ_ALIGN(4) volatile u32 kjAtomic32;
typedef KJ_ALIGN(8) volatile u64 kjAtomic64;
#if defined(KJ_ARCH_32_BIT)
typedef KJ_ALIGN(4) volatile void* kjAtomicPtr;
#elif defined(KJ_ARCH_64_BIT)
typedef KJ_ALIGN(8) volatile void* kjAtomicPtr;
#endif
#endif

#if defined(KJ_ARCH_64_BIT)
typedef kjAtomic64 kjAtomic;
#elif defined(KJ_ARCH_32_BIT)
typedef kjAtomic32 kjAtomic;
#endif

typedef struct kjProcess {
    kjFd fd;
    kjFd in, out, err;
} kjProcess;

KJ_API void kj_yield(void);
KJ_API void kj_sleep_ms(u32 ms);

KJ_API kjResult kj_thread(kjThread* thread, kjThreadFn* fn, void* data, u32 flags);
KJ_API void* kj_thread_join(kjThread* thread);
KJ_API void kj_thread_detach(kjThread* thread);
KJ_API void kj_thread_set_name(kjThread* thread, const char* name, isize size);
KJ_API u32 kj_thread_id(void);

KJ_API kjResult kj_tls(kjTls* tls);
KJ_API void kj_tls_destroy(kjTls tls);
KJ_API void kj_tls_set(kjTls tls, void* value);
KJ_API void* kj_tls_get(kjTls tls);

KJ_API kjResult kj_mutex(kjMutex* mutex);
KJ_API void kj_mutex_destroy(kjMutex* mutex);
KJ_API void kj_mutex_lock(kjMutex* mutex);
KJ_API b32 kj_mutex_try_lock(kjMutex* mutex);
KJ_API void kj_mutex_unlock(kjMutex* mutex);

KJ_API kjResult kj_semaphore(kjSemaphore* semaphore, i32 count);
KJ_API void kj_semaphore_destroy(kjSemaphore* semaphore);
KJ_API b32 kj_semaphore_wait(kjSemaphore* semaphore, i32 ms);
KJ_API b32 kj_semaphore_try_wait(kjSemaphore* semaphore);
KJ_API void kj_semaphore_signal(kjSemaphore* semaphore, i32 count);

KJ_API void kj_atomic_read_fence(void);
KJ_API void kj_atomic_write_fence(void);
KJ_API void kj_atomic_rw_fence(void);
KJ_API u32 kj_atomic32_cmp_swap(kjAtomic32* v, u32 cmp, u32 swap);
KJ_API u64 kj_atomic64_cmp_swap(kjAtomic64* v, u64 cmp, u64 swap);
KJ_API void* kj_atomic_cmp_swap_ptr(kjAtomicPtr* v, void* cmp, void* swap);
KJ_API u32 kj_atomic32_swap(kjAtomic32* v, u32 swap);
KJ_API u64 kj_atomic64_swap(kjAtomic64* v, u64 swap);
KJ_API void* kj_atomic_swap_ptr(kjAtomicPtr* v, void* swap);
KJ_API u32 kj_atomic32_inc(kjAtomic32* v);
KJ_API u64 kj_atomic64_inc(kjAtomic64* v);
KJ_API u32 kj_atomic32_dec(kjAtomic32* v);
KJ_API u64 kj_atomic64_dec(kjAtomic64* v);
KJ_API u32 kj_atomic32_fetch_add(kjAtomic32* v, u32 op);
KJ_API u64 kj_atomic64_fetch_add(kjAtomic64* v, u64 op);
KJ_API u32 kj_atomic32_fetch_sub(kjAtomic32* v, u32 op);
KJ_API u64 kj_atomic64_fetch_sub(kjAtomic64* v, u64 op);
KJ_API u32 kj_atomic32_or(kjAtomic32* v, u32 op);
KJ_API u64 kj_atomic64_or(kjAtomic64* v, u64 op);
KJ_API u32 kj_atomic32_and(kjAtomic32* v, u32 op);
KJ_API u64 kj_atomic64_and(kjAtomic64* v, u64 op);
KJ_API u32 kj_atomic32_xor(kjAtomic32* v, u32 op);
KJ_API u64 kj_atomic64_xor(kjAtomic64* v, u64 op);

#if defined(KJ_ARCH_64_BIT)
#define kj_atomic_cmp_swap(v, c, s) kj_atomic_cmp_swap(v, c, s)
#define kj_atomic_cmp(v, c, s) kj_atomic64_swap(v, c, s)
#define kj_atomic_inc(v) kj_atomic64_inc(v)
#define kj_atomic_dec(v) kj_atomic64_dec(v)
#define kj_atomic_fetch_add(v, op) kj_atomic64_fetch_add(v, op)
#define kj_atomic_fetch_sub(v, op) kj_atomic64_fetch_sub(v, op)
#define kj_atomic_or(v, op) kj_atomic64_or(v, op)
#define kj_atomic_and(v, op) kj_atomic64_and(v, op)
#define kj_atomic_xor(v, op) kj_atomic64_xor(v, op)
#elif defined(KJ_ARCH_32_BIT)
#define kj_atomic_cmp_swap(v, c, s) kj_atomic32_cmp_swap(v, c, s)
#define kj_atomic_cmp(v, c, s) kj_atomic32_swap(v, c, s)
#define kj_atomic_inc(v) kj_atomic32_inc(v)
#define kj_atomic_dec(v) kj_atomic32_dec(v)
#define kj_atomic_fetch_add(v, op) kj_atomic32_fetch_add(v, op)
#define kj_atomic_fetch_sub(v, op) kj_atomic32_fetch_sub(v, op)
#define kj_atomic_or(v, op) kj_atomic32_or(v, op)
#define kj_atomic_and(v, op) kj_atomic32_and(v, op)
#define kj_atomic_xor(v, op) kj_atomic32_xor(v, op)
#endif

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_THREADING_IMPL)

KJ_INLINE void kj_yield(void) {
#if defined(KJ_SYS_WIN32)
    SwitchToThread();
#elif defined(KJ_SYS_UNIX)
    syscall(SYS_sched_yield);
#endif
}

KJ_INLINE void kj_sleep_ms(u32 ms) {
#if defined(KJ_SYS_WIN32)
    Sleep(ms);
#elif defined(KJ_SYS_UNIX)
    struct timespec ts;
    struct timespec elapsed;
    elapsed.tv_sec = kj_cast(time_t, ms / 1000),
    elapsed.tv_nsec = kj_cast(u32, (ms % 1000) * 1000000);
    i32 err = 0;
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
KJ_INTERN DWORD __cdecl _kj_win32_fn(LPVOID p) {
    kjThread* thread = kj_cast(kjThread*, p);
    if(thread) {
        thread->res = thread->fn(thread->data);
    }
    return 0;
}
#elif defined(KJ_SYS_UNIX)
KJ_INTERN void* _kj_pthread_fn(void* p) {
    kjThread* thread = kj_cast(kjThread*, p);
    if(thread) {
        thread->res = thread->fn(thread->data);
    }
    return NULL;
}
#endif

kjResult kj_thread(kjThread* thread, kjThreadFn* fn, void* data, u32 flags) {
    kj_validate(thread != NULL && fn != NULL, { return KJ_ERROR_PARAM; });
    kj_unused(flags);

    kjResult res = KJ_SUCCESS;
    thread->fn = fn;
    thread->data = data;
    thread->res = NULL;
#if defined(KJ_SYS_WIN32)
    if((thread->handle = CreateThread(NULL, 0, _kj_win32_fn, thread, 0, NULL)) == NULL) {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    res = kj_error_from_os(pthread_create(&thread->handle, NULL, _kj_pthread_fn, thread));
#endif
    return res;
}

KJ_INLINE void* kj_thread_join(kjThread* thread) {
    kj_validate(thread != NULL, { return NULL; });

#if defined(KJ_SYS_WIN32)
    WaitForSingleObjectEx(thread->handle, INFINITE, FALSE);
    CloseHandle(thread->handle);
#elif defined(KJ_SYS_UNIX)
    pthread_join(thread->handle, NULL);
#endif
    return thread->res;
}

KJ_INLINE void kj_thread_detach(kjThread* thread) {
    kj_validate(thread != NULL, { return; });

#if defined(KJ_SYS_WIN32)
    CloseHandle(thread->handle);
    thread->handle = NULL;
#elif defined(KJ_SYS_UNIX)
    pthread_detach(thread->handle);
#endif
}

KJ_INLINE void kj_thread_set_name(kjThread* thread, const char* name, isize size) {
    kj_validate(thread != NULL && name != NULL && size >= 0, { return; });

#if defined(KJ_SYS_WIN32)
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
        RaiseException(MS_VC_EXCEPTION, 0, kj_isize_of(info) / kj_isize_of(ULONG_PTR), kj_cast(ULONG_PTR*, &info));
    } __except (EXCEPTION_EXECUTE_HANDLER) {
    }
#elif defined(KJ_SYS_UNIX)
    pthread_setname_np(thread->handle, name);
#endif
}

KJ_INLINE u32 kj_thread_id(void) {
    u32 res = 0;
#if defined(KJ_COMPILER_MSVC)
    u8* tls = kj_cast(u8*, __readgsqword(0x38));
    res = *kj_cast(u32*, tls + 0x48);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#if defined(__APPLE__) && defined(KJ_ARCH_X86) && defined(KJ_ARCH_64_BIT)
    __asm ("mov %%gs:0x00,%0" : "=r" (res));
#elif defined(KJ_ARCH_X86) && defined(KJ_ARCH_32_BIT)
    __asm ("mov %%gs:0x08,%0" : "=r" (res));
#elif defined(KJ_ARCH_X86) && defined(KJ_ARCH_64_BIT)
    __asm ("mov %%fs:0x10,%0" : "=r" (res));
#else
#error "Unsupported Architecture"
#endif
#endif
    return res;
}

kjResult kj_tls(kjTls* tls) {
    kj_validate(tls != NULL, { return KJ_ERROR_PARAM; });

    isize res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    if((*tls = TlsAlloc()) == TLS_OUT_OF_INDEXES) {
        *tls = KJ_TLS_INVALID;
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if((res = pthread_key_create(tls, NULL)) != 0) {
        *tls = KJ_TLS_INVALID;
        res = kj_error_from_os(res);
    }
#endif
    return kj_cast(kjResult, res);
}

KJ_INLINE void kj_tls_destroy(kjTls tls) {
    kj_validate(tls != KJ_TLS_INVALID, { return; });

#if defined(KJ_SYS_WIN32)
    TlsFree(tls);
#elif defined(KJ_SYS_UNIX)
    pthread_key_delete(tls);
#endif
}

KJ_INLINE void kj_tls_set(kjTls tls, void* value) {
    kj_validate(tls != KJ_TLS_INVALID, { return; });

#if defined(KJ_SYS_WIN32)
    TlsSetValue(tls, value);
#elif defined(KJ_SYS_UNIX)
    pthread_setspecific(tls, value);
#endif
}

KJ_INLINE void* kj_tls_get(kjTls tls) {
    kj_validate(tls != KJ_TLS_INVALID, { return NULL; });

#if defined(KJ_SYS_WIN32)
    return TlsGetValue(tls);
#elif defined(KJ_SYS_UNIX)
    return pthread_getspecific(tls);
#endif
}

kjResult kj_mutex(kjMutex* mutex) {
    kj_validate(mutex != NULL, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    if(!InitializeCriticalSectionAndSpinCount(mutex, 4000)) {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    res = kj_error_from_os(pthread_mutex_init(mutex, &attr));
    pthread_mutexattr_destroy(&attr);
#endif
    return res;
}

KJ_INLINE void kj_mutex_destroy(kjMutex* mutex) {
    kj_validate(mutex != NULL, { return; });

#if defined(KJ_SYS_WIN32)
    DeleteCriticalSection(mutex);
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_destroy(mutex);
#endif
}

KJ_INLINE void kj_mutex_lock(kjMutex* mutex) {
    kj_validate(mutex != NULL, { return; });

#if defined(KJ_SYS_WIN32)
    EnterCriticalSection(mutex);
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_lock(mutex);
#endif
}

KJ_INLINE b32 kj_mutex_try_lock(kjMutex* mutex) {
    kj_validate(mutex != NULL, { return KJ_FALSE; });

#if defined(KJ_SYS_WIN32)
    return TryEnterCriticalSection(mutex) != 0;
#elif defined(KJ_SYS_UNIX)
    return pthread_mutex_trylock(mutex) == 0;
#endif
}

KJ_INLINE void kj_mutex_unlock(kjMutex* mutex) {
    kj_validate(mutex != NULL, { return; });

#if defined(KJ_SYS_WIN32)
    LeaveCriticalSection(mutex);
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_unlock(mutex);
#endif
}

kjResult kj_semaphore(kjSemaphore* semaphore, i32 count) {
    kj_validate(semaphore != NULL && count > 0, { return KJ_ERROR_PARAM; });

    kjResult res = KJ_SUCCESS;
#if defined(KJ_SYS_WIN32)
    if((*semaphore = CreateSemaphore(NULL, count, count, NULL)) == NULL) {
        res = kj_os_error();
    }
#elif defined(KJ_SYS_UNIX)
    if(sem_init(semaphore, 0, count) == -1) {
        res = kj_os_error();
    }
#endif
    return res;
}

KJ_INLINE void kj_semaphore_destroy(kjSemaphore* semaphore) {
    kj_validate(semaphore != NULL, { return; });

#if defined(KJ_SYS_WIN32)
    CloseHandle(semaphore);
#elif defined(KJ_SYS_UNIX)
    sem_destroy(semaphore);
#endif
}

KJ_INLINE b32 kj_semaphore_wait(kjSemaphore* semaphore, i32 ms) {
    kj_validate(semaphore != NULL, { return KJ_FALSE; });

#if defined(KJ_SYS_WIN32)
    u32 res = WaitForSingleObject(semaphore, ms < 0 ? INFINITE: ms);
    return res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT;
#elif defined(KJ_SYS_UNIX)
    if(ms <= 0) {
        return sem_wait(semaphore) == 0;
    } else {
        struct timespec ts;
        kj_mem_zero(&ts, kj_isize_of(struct timespec));
        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000;
        return sem_timedwait(semaphore, &ts) == 0;
    }
#endif
}

KJ_INLINE b32 kj_semaphore_try_wait(kjSemaphore* semaphore) {
    kj_validate(semaphore != NULL, { return KJ_FALSE; });

#if defined(KJ_SYS_WIN32)
    return WaitForSingleObject(semaphore, 0) == WAIT_OBJECT_0;
#elif defined(KJ_SYS_UNIX)
    return sem_trywait(semaphore) == 0;
#endif
}

KJ_INLINE void kj_semaphore_signal(kjSemaphore* semaphore, i32 count) {
    kj_validate(semaphore != NULL && count > 0, { return; });

#if defined(KJ_SYS_WIN32)
    ReleaseSemaphore(semaphore, count, NULL);
#elif defined(KJ_SYS_UNIX)
    while(count--) { sem_post(semaphore); }
#endif
}

KJ_INLINE void kj_atomic_read_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _ReadBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

KJ_INLINE void kj_atomic_write_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _WriteBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

KJ_INLINE void kj_atomic_rw_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _ReadWriteBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

KJ_INLINE u32 kj_atomic32_cmp_swap(kjAtomic32* v, u32 cmp, u32 swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchange(v, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_val_compare_and_swap(v, cmp, swap);
#endif
}

KJ_INLINE u64 kj_atomic64_cmp_swap(kjAtomic64* v, u64 cmp, u64 swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchange64(v, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_val_compare_and_swap(v, cmp, swap);
#endif
}

KJ_INLINE void* kj_atomic_cmp_swap_ptr(kjAtomicPtr* v, void* cmp, void* swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchangePointer(v, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return kj_cast(void*, __sync_val_compare_and_swap(v, cmp, swap));
#endif
}

KJ_INLINE u32 kj_atomic32_swap(kjAtomic32* v, u32 swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchange(v, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_lock_test_and_set(v, swap);
#endif
}

KJ_INLINE u64 kj_atomic64_swap(kjAtomic64* v, u64 swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchange64(v, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_lock_test_and_set(v, swap);
#endif
}

KJ_INLINE void* kj_atomic_swap_ptr(kjAtomicPtr* v, void* swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangePointer(v, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return kj_cast(void*, __sync_lock_test_and_set(v, swap));
#endif
}

KJ_INLINE u32 kj_atomic32_inc(kjAtomic32* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedIncrement(v);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_add_and_fetch(v, 1);
#endif
}

KJ_INLINE u64 kj_atomic64_inc(kjAtomic64* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedIncrement64(v);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_add_and_fetch(v, 1);
#endif
}

KJ_INLINE u32 kj_atomic32_dec(kjAtomic32* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedDecrement(v);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_sub_and_fetch(v, 1);
#endif
}

KJ_INLINE u64 kj_atomic64_dec(kjAtomic64* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedDecrement64(v);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_sub_and_fetch(v, 1);
#endif
}

KJ_INLINE u32 kj_atomic32_fetch_add(kjAtomic32* v, u32 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_add(v, op);
#endif
}

KJ_INLINE u64 kj_atomic64_fetch_add(kjAtomic64* v, u64 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd64(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_add(v, op);
#endif
}

KJ_INLINE u32 kj_atomic32_fetch_sub(kjAtomic32* v, u32 op) {
#if defined(KJ_COMPILER_MSVC)
    return InterlockedExchangeAdd(v, -kj_cast(i32, op));
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_sub(v, op);
#endif
}

KJ_INLINE u64 kj_atomic64_fetch_sub(kjAtomic64* v, u64 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd64(v, -kj_cast(i64, op));
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_sub(v, op);
#endif
}

KJ_INLINE u32 kj_atomic32_or(kjAtomic32* v, u32 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedOr(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_or(v, op);
#endif
}

KJ_INLINE u64 kj_atomic64_or(kjAtomic64* v, u64 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedOr64(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_or(v, op);
#endif
}

KJ_INLINE u32 kj_atomic32_and(kjAtomic32* v, u32 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedAnd(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_and(v, op);
#endif
}

KJ_INLINE u64 kj_atomic64_and(kjAtomic64* v, u64 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedAnd64(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_and(v, op);
#endif
}

KJ_INLINE u32 kj_atomic32_xor(kjAtomic32* v, u32 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedXor(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_xor(v, op);
#endif
}

KJ_INLINE u64 kj_atomic64_xor(kjAtomic64* v, u64 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedXor64(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_xor(v, op);
#endif
}

#endif
