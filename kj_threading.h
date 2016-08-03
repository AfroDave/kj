// `kj_threading.h`
//
// ---------------------------------- LICENSE ----------------------------------
// This software is in the public domain.  Where that dedication is not
// recognized, you are granted a perpetual, irrevocable license to copy,
// distribute, and modify the source code as you see fit.
//
// The source code is provided "as is", without warranty of any kind, express
// or implied. No attribution is required, but always appreciated.
// =============================================================================
//
// usage:
//      #define KJ_THREADING_IMPL
//      #include "kj_threading.h"

#ifndef KJ_THREADING_H
#define KJ_THREADING_H

#define KJ_THREADING_VERSION_MAJOR 0
#define KJ_THREADING_VERSION_MINOR 3
#define KJ_THREADING_VERSION_PATCH 0

KJ_EXTERN_BEGIN

enum {
    KJ_THREADING_FLAG_NONE = KJ_BIT_FLAG_NONE
};

#if defined(KJ_SYS_WIN32)
typedef HANDLE kjThreadHandle;
typedef CRITICAL_SECTION kjMutex;
typedef HANDLE kjSemaphore;
#elif defined(KJ_SYS_LINUX)
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sched.h>
typedef pthread_t kjThreadHandle;
typedef pthread_mutex_t kjMutex;
typedef sem_t kjSemaphore;
#else
#error Unsupported Operating System
#endif

#if !defined(KJ_TLS)
#if defined(KJ_COMPILER_MSVC)
#define KJ_TLS __declspec(thread)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_TLS __thread
#endif
#endif

#if defined(KJ_COMPILER_MSVC)
#include <intrin.h>
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
#else
#error Unsupported Architecture
#endif
#else
#error Unsupported Compiler
#endif

#define KJ_THREAD_FN(name) void name(void* data)
typedef KJ_THREAD_FN(kjThreadFn);

typedef struct kjThread {
    i32 id;
    u32 flags;
    kjThreadHandle handle;
    struct {
        kjThreadFn* fn;
        void* data;
    } ctx;
} kjThread;

KJ_API void kj_yield(void);
KJ_API void kj_sleep_ms(u32 ms);

KJ_API kjErr kj_thread(kjThread* thread, kjThreadFn* fn, void* data, u32 flags);
KJ_API void kj_thread_join(kjThread* thread);
KJ_API void kj_thread_detach(kjThread* thread);

KJ_API kjErr kj_mutex(kjMutex* mutex);
KJ_API void kj_mutex_lock(kjMutex* mutex);
KJ_API b32 kj_mutex_try_lock(kjMutex* mutex);
KJ_API void kj_mutex_unlock(kjMutex* mutex);
KJ_API void kj_mutex_destroy(kjMutex* mutex);

KJ_API kjErr kj_semaphore(kjSemaphore* semaphore, i32 count, i32 max);
KJ_API b32 kj_semaphore_wait(kjSemaphore* semaphore);
KJ_API b32 kj_semaphore_try_wait(kjSemaphore* semaphore);
KJ_API void kj_semaphore_signal(kjSemaphore* semaphore, i32 count);
KJ_API void kj_semaphore_destroy(kjSemaphore* semaphore);

KJ_API void kj_atomic_read_fence(void);
KJ_API void kj_atomic_write_fence(void);
KJ_API void kj_atomic_rw_fence(void);
KJ_API u32 kj_atomic_cmp_swap_u32(kjAtomic32* v, u32 cmp, u32 swap);
KJ_API u64 kj_atomic_cmp_swap_u64(kjAtomic64* v, u64 cmp, u64 swap);
KJ_API void* kj_atomic_cmp_swap_ptr(kjAtomicPtr* v, void* cmp, void* swap);
KJ_API u32 kj_atomic_swap_u32(kjAtomic32* v, u32 swap);
KJ_API u64 kj_atomic_swap_u64(kjAtomic64* v, u64 swap);
KJ_API void* kj_atomic_swap_ptr(kjAtomicPtr* v, void* swap);
KJ_API u32 kj_atomic_inc_u32(kjAtomic32* v);
KJ_API u64 kj_atomic_inc_u64(kjAtomic64* v);
KJ_API u32 kj_atomic_dec_u32(kjAtomic32* v);
KJ_API u64 kj_atomic_dec_u64(kjAtomic64* v);
KJ_API u32 kj_atomic_fetch_add_u32(kjAtomic32* v, u32 add);
KJ_API u64 kj_atomic_fetch_add_u64(kjAtomic64* v, u64 add);
KJ_API u32 kj_atomic_fetch_sub_u32(kjAtomic32* v, u32 sub);
KJ_API u64 kj_atomic_fetch_sub_u64(kjAtomic64* v, u64 sub);
KJ_API u32 kj_atomic_or_u32(kjAtomic32* v, u32 op);
KJ_API u64 kj_atomic_or_u64(kjAtomic64* v, u64 op);
KJ_API u32 kj_atomic_and_u32(kjAtomic32* v, u32 op);
KJ_API u64 kj_atomic_and_u64(kjAtomic64* v, u64 op);
KJ_API u32 kj_atomic_xor_u32(kjAtomic32* v, u32 op);
KJ_API u64 kj_atomic_xor_u64(kjAtomic64* v, u64 op);

KJ_EXTERN_END

#endif

#if defined(KJ_THREADING_IMPL)

kjAtomic32 THREAD_COUNTER = 0;

KJ_INLINE void kj_yield(void) {
#if defined(KJ_SYS_WIN32)
    SwitchToThread();
#elif defined(KJ_SYS_LINUX)
    sched_yield();
#endif
}

KJ_INLINE void kj_sleep_ms(u32 ms) {
#if defined(KJ_SYS_WIN32)
    Sleep(ms);
#elif defined(KJ_SYS_LINUX)
    struct timespec req = {
        kj_cast(time_t, ms / 1000),
        kj_cast(u32, ((ms % 1000) * 1000000))
    };
    struct timespec rem = { 0, 0 };
    nanosleep(&req, &rem);
#endif
}

kjErr kj_thread(kjThread* thread, kjThreadFn* fn, void* data, u32 flags) {
    if(thread == NULL || fn == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if((thread->handle = CreateThread(
            NULL, 0, kj_cast(LPTHREAD_START_ROUTINE, fn),
            data, 0, NULL)) == NULL) {
        res = kj_err_from_sys(GetLastError());
    } else {
        thread->id = kj_atomic_inc_u32(&THREAD_COUNTER);
        thread->ctx.fn = fn;
        thread->ctx.data = data;
        thread->flags = flags;
    }
#elif defined(KJ_SYS_LINUX)
    if(kj_err_from_sys(pthread_create(
        &thread->handle, NULL, kj_cast(void* (*)(void*), fn), data))
            == KJ_ERR_NONE) {
        thread->id = kj_atomic_inc_u32(&THREAD_COUNTER);
        thread->ctx.fn = fn;
        thread->ctx.data = data;
        thread->flags = flags;
    }
#endif
    return res;
}

KJ_INLINE void kj_thread_join(kjThread* thread) {
    if(thread == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    WaitForSingleObjectEx(thread->handle, INFINITE, FALSE);
    CloseHandle(thread->handle);
#elif defined(KJ_SYS_LINUX)
    pthread_join(thread->handle, NULL);
#endif
}

KJ_INLINE void kj_thread_detach(kjThread* thread) {
    if(thread == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    CloseHandle(thread->handle);
    thread->handle = NULL;
#elif defined(KJ_SYS_LINUX)
    pthread_detach(thread->handle);
#endif
}

kjErr kj_mutex(kjMutex* mutex) {
    if(mutex == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if(!InitializeCriticalSectionAndSpinCount(mutex, 1000)) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    res = kj_err_from_sys(pthread_mutex_init(mutex, NULL));
#endif
    return res;
}

KJ_INLINE void kj_mutex_lock(kjMutex* mutex) {
    if(mutex == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    EnterCriticalSection(mutex);
#elif defined(KJ_SYS_LINUX)
    pthread_mutex_lock(mutex);
#endif
}

KJ_INLINE b32 kj_mutex_try_lock(kjMutex* mutex) {
    if(mutex == NULL) {
        return KJ_FALSE;
    }

#if defined(KJ_SYS_WIN32)
    return TryEnterCriticalSection(mutex) > 0 ? KJ_TRUE: KJ_FALSE;
#elif defined(KJ_SYS_LINUX)
    return pthread_mutex_trylock(mutex) == 0;
#endif
}

KJ_INLINE void kj_mutex_unlock(kjMutex* mutex) {
    if(mutex == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    LeaveCriticalSection(mutex);
#elif defined(KJ_SYS_LINUX)
    pthread_mutex_unlock(mutex);
#endif
}

KJ_INLINE void kj_mutex_destroy(kjMutex* mutex) {
    if(mutex == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    DeleteCriticalSection(mutex);
#elif defined(KJ_SYS_LINUX)
    pthread_mutex_destroy(mutex);
#endif
}

kjErr kj_semaphore(kjSemaphore* semaphore, i32 count, i32 max) {
    if(semaphore == NULL || count <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
#if defined(KJ_SYS_WIN32)
    if((*semaphore = CreateSemaphore(NULL, count, max, NULL)) == NULL) {
        res = kj_err_from_sys(GetLastError());
    }
#elif defined(KJ_SYS_LINUX)
    kj_unused(max);
    if(sem_init(semaphore, 0, count) == -1) {
        res = kj_err_from_sys(errno);
    }
#endif
    return res;
}

KJ_INLINE b32 kj_semaphore_wait(kjSemaphore* semaphore) {
    if(semaphore == NULL) {
        return KJ_FALSE;
    }

#if defined(KJ_SYS_WIN32)
    u32 res = WaitForSingleObject(semaphore, INFINITE);
    return res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT;
#elif defined(KJ_SYS_LINUX)
    return sem_wait(semaphore);
#endif
}

KJ_INLINE b32 kj_semaphore_try_wait(kjSemaphore* semaphore) {
    if(semaphore == NULL) {
        return KJ_FALSE;
    }

#if defined(KJ_SYS_WIN32)
    u32 res = WaitForSingleObject(semaphore, 0);
    return res == WAIT_OBJECT_0;
#elif defined(KJ_SYS_LINUX)
    return sem_trywait(semaphore);
#endif
}

KJ_INLINE void kj_semaphore_signal(kjSemaphore* semaphore, i32 count) {
    if(semaphore == NULL || count <= 0) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    ReleaseSemaphore(semaphore, count, NULL);
#elif defined(KJ_SYS_LINUX)
    while(count-- > 0) {
        sem_post(semaphore);
    }
#endif
}

KJ_INLINE void kj_semaphore_destroy(kjSemaphore* semaphore) {
    if(semaphore == NULL) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    CloseHandle(semaphore);
#elif defined(KJ_SYS_LINUX)
    sem_destroy(semaphore);
#endif
}

KJ_INLINE void kj_atomic_read_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _ReadBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm __volatile__ ("" ::: "memory");
#endif
}

KJ_INLINE void kj_atomic_write_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _WriteBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm __volatile__ ("" ::: "memory");
#endif
}

KJ_INLINE void kj_atomic_rw_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _ReadWriteBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm __volatile__ ("" ::: "memory");
#endif
}

KJ_INLINE u32 kj_atomic_cmp_swap_u32(kjAtomic32* v, u32 cmp, u32 swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchange(v, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_val_compare_and_swap(v, cmp, swap);
#endif
}

KJ_INLINE u64 kj_atomic_cmp_swap_u64(kjAtomic64* v, u64 cmp, u64 swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchange64(v, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_val_compare_and_swap(v, cmp, swap);
#endif
}

KJ_INLINE void* kj_atomic_cmp_swap_ptr(
        kjAtomicPtr* v, void* cmp, void* swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedCompareExchangePointer(v, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return kj_cast(void*, __sync_val_compare_and_swap(v, cmp, swap));
#endif
}

KJ_INLINE u32 kj_atomic_swap_u32(kjAtomic32* v, u32 swap) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchange(v, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_lock_test_and_set(v, swap);
#endif
}

KJ_INLINE u64 kj_atomic_swap_u64(kjAtomic64* v, u64 swap) {
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

KJ_INLINE u32 kj_atomic_inc_u32(kjAtomic32* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedIncrement(v);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_add_and_fetch(v, 1);
#endif
}

KJ_INLINE u64 kj_atomic_inc_u64(kjAtomic64* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedIncrement64(v);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_add_and_fetch(v, 1);
#endif
}

KJ_INLINE u32 kj_atomic_dec_u32(kjAtomic32* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedDecrement(v);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_sub_and_fetch(v, 1);
#endif
}

KJ_INLINE u64 kj_atomic_dec_u64(kjAtomic64* v) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedDecrement64(v);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_sub_and_fetch(v, 1);
#endif
}

KJ_INLINE u32 kj_atomic_fetch_add_u32(kjAtomic32* v, u32 add) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd(v, add);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_add(v, add);
#endif
}

KJ_INLINE u64 kj_atomic_fetch_add_u64(kjAtomic64* v, u64 add) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd64(v, add);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_add(v, add);
#endif
}

KJ_INLINE u32 kj_atomic_fetch_sub_u32(kjAtomic32* v, u32 sub) {
#if defined(KJ_COMPILER_MSVC)
    return InterlockedExchangeAdd(v, -kj_cast(i32, sub));
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_sub(v, sub);
#endif
}

KJ_INLINE u64 kj_atomic_fetch_sub_u64(kjAtomic64* v, u64 sub) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedExchangeAdd64(v, -kj_cast(i64, sub));
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_sub(v, sub);
#endif
}

KJ_INLINE u32 kj_atomic_or_u32(kjAtomic32* v, u32 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedOr(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_or(v, op);
#endif
}

KJ_INLINE u64 kj_atomic_or_u64(kjAtomic64* v, u64 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedOr64(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_or(v, op);
#endif
}

KJ_INLINE u32 kj_atomic_and_u32(kjAtomic32* v, u32 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedAnd(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_and(v, op);
#endif
}

KJ_INLINE u64 kj_atomic_and_u64(kjAtomic64* v, u64 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedAnd64(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_and(v, op);
#endif
}

KJ_INLINE u32 kj_atomic_xor_u32(kjAtomic32* v, u32 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedXor(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_xor(v, op);
#endif
}

KJ_INLINE u64 kj_atomic_xor_u64(kjAtomic64* v, u64 op) {
#if defined(KJ_COMPILER_MSVC)
    return _InterlockedXor64(v, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __sync_fetch_and_xor(v, op);
#endif
}

#endif
