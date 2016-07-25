// `kj_threading.h`
// public domain - no warranty implied; use at your own risk
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

KJ_API kjErr kj_semaphore(kjSemaphore* semaphore, u32 count, u32 max);
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

#if defined(KJ_SYS_WIN32)
KJ_INLINE void kj_yield(void) {
    SwitchToThread();
}

KJ_INLINE void kj_sleep_ms(u32 ms) {
    Sleep(ms);
}

kjErr kj_thread(kjThread* thread, kjThreadFn* fn, void* data, u32 flags) {
    kj_assert(thread);
    kj_assert(fn);

    kjErr res = KJ_ERR_NONE;
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
    return res;
}

KJ_INLINE void kj_thread_join(kjThread* thread) {
    kj_assert(thread);

    WaitForSingleObjectEx(thread->handle, INFINITE, FALSE);
    CloseHandle(thread->handle);
}

KJ_INLINE void kj_thread_detach(kjThread* thread) {
    kj_assert(thread);

    CloseHandle(thread->handle);
    thread->handle = NULL;
}

kjErr kj_mutex(kjMutex* mutex) {
    kj_assert(mutex);

    kjErr res = KJ_ERR_NONE;
    if(!InitializeCriticalSectionAndSpinCount(mutex, 1000)) {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}

KJ_INLINE void kj_mutex_lock(kjMutex* mutex) {
    kj_assert(mutex);

    EnterCriticalSection(mutex);
}

KJ_INLINE b32 kj_mutex_try_lock(kjMutex* mutex) {
    kj_assert(mutex);

    return TryEnterCriticalSection(mutex) > 0;
}

KJ_INLINE void kj_mutex_unlock(kjMutex* mutex) {
    kj_assert(mutex);

    LeaveCriticalSection(mutex);
}

KJ_INLINE void kj_mutex_destroy(kjMutex* mutex) {
    kj_assert(mutex);

    DeleteCriticalSection(mutex);
}

kjErr kj_semaphore(kjSemaphore* semaphore, u32 count, u32 max) {
    kj_assert(semaphore);

    kjErr res = KJ_ERR_NONE;
    if((*semaphore = CreateSemaphore(NULL, count, max, NULL)) == NULL) {
        res = kj_err_from_sys(GetLastError());
    }
    return res;
}

KJ_INLINE b32 kj_semaphore_wait(kjSemaphore* semaphore) {
    kj_assert(semaphore);

    u32 res = WaitForSingleObject(semaphore, INFINITE);
    return res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT;
}

KJ_INLINE b32 kj_semaphore_try_wait(kjSemaphore* semaphore) {
    kj_assert(semaphore);

    u32 res = WaitForSingleObject(semaphore, 0);
    return res == WAIT_OBJECT_0;
}

KJ_INLINE void kj_semaphore_signal(kjSemaphore* semaphore, i32 count) {
    kj_assert(semaphore);

    ReleaseSemaphore(semaphore, count, NULL);
}

KJ_INLINE void kj_semaphore_destroy(kjSemaphore* semaphore) {
    kj_assert(semaphore);

    CloseHandle(semaphore); semaphore = NULL;
}
#elif defined(KJ_SYS_LINUX)
KJ_INLINE void kj_yield(void) {
    sched_yield();
}

KJ_INLINE void kj_sleep_ms(u32 ms) {
    struct timespec req = {
        kj_cast(time_t, ms / 1000),
        kj_cast(u32, ((ms % 1000) * 1000000))
    };
    struct timespec rem = { 0, 0 };
    nanosleep(&req, &rem);
}

kjErr kj_thread(kjThread* thread, kjThreadFn* fn, void* data, u32 flags) {
    kj_assert(thread);
    kj_assert(fn);

    kjErr res = KJ_ERR_NONE;
    if(kj_err_from_sys(pthread_create(
        &thread->handle, NULL, kj_cast(void* (*)(void*), fn), data))
            == KJ_ERR_NONE) {
        thread->id = kj_atomic_inc_u32(&THREAD_COUNTER);
        thread->ctx.fn = fn;
        thread->ctx.data = data;
        thread->flags = flags;
    }
    return res;
}

KJ_INLINE void kj_thread_join(kjThread* thread) {
    kj_assert(thread);

    pthread_join(thread->handle, NULL);
}

KJ_INLINE void kj_thread_detach(kjThread* thread) {
    kj_assert(thread);

    pthread_detach(thread->handle);
}

kjErr kj_mutex(kjMutex* mutex) {
    kj_assert(mutex);

    kjErr res = kj_err_from_sys(pthread_mutex_init(mutex, NULL));
    return res;
}

KJ_INLINE void kj_mutex_lock(kjMutex* mutex) {
    kj_assert(mutex);

    pthread_mutex_lock(mutex);
}

KJ_INLINE b32 kj_mutex_try_lock(kjMutex* mutex) {
    kj_assert(mutex);

    return pthread_mutex_trylock(mutex) == 0;
}

KJ_INLINE void kj_mutex_unlock(kjMutex* mutex) {
    kj_assert(mutex);

    pthread_mutex_unlock(mutex);
}

KJ_INLINE void kj_mutex_destroy(kjMutex* mutex) {
    kj_assert(mutex);

    pthread_mutex_destroy(mutex);
}

kjErr kj_semaphore(kjSemaphore* semaphore, u32 count, u32 max) {
    kj_unused(max);

    kjErr res = KJ_ERR_NONE;
    if(sem_init(semaphore, 0, count) == -1) {
        res = kj_err_from_sys(errno);
    }
    return res;
}

KJ_INLINE b32 kj_semaphore_wait(kjSemaphore* semaphore) {
    kj_assert(semaphore);

    return sem_wait(semaphore);
}

KJ_INLINE b32 kj_semaphore_try_wait(kjSemaphore* semaphore) {
    kj_assert(semaphore);

    return sem_trywait(semaphore);
}

KJ_INLINE void kj_semaphore_signal(kjSemaphore* semaphore, i32 count) {
    kj_assert(semaphore);

    while(count-- > 0) {
        sem_post(semaphore);
    }
}

KJ_INLINE void kj_semaphore_destroy(kjSemaphore* semaphore) {
    kj_assert(semaphore);

    sem_destroy(semaphore);
}
#endif

#if defined(KJ_COMPILER_MSVC)
KJ_INLINE void kj_atomic_read_fence(void) {
    _ReadBarrier();
}

KJ_INLINE void kj_atomic_write_fence(void) {
    _WriteBarrier();
}

KJ_INLINE void kj_atomic_rw_fence(void) {
    _ReadWriteBarrier();
}

KJ_INLINE u32 kj_atomic_cmp_swap_u32(kjAtomic32* v, u32 cmp, u32 swap) {
    return _InterlockedCompareExchange(v, swap, cmp);
}

KJ_INLINE u64 kj_atomic_cmp_swap_u64(kjAtomic64* v, u64 cmp, u64 swap) {
    return _InterlockedCompareExchange64(v, swap, cmp);
}

KJ_INLINE void* kj_atomic_cmp_swap_ptr(
        kjAtomicPtr* v, void* cmp, void* swap) {
    return _InterlockedCompareExchangePointer(v, swap, cmp);
}

KJ_INLINE u32 kj_atomic_swap_u32(kjAtomic32* v, u32 swap) {
    return _InterlockedExchange(v, swap);
}

KJ_INLINE u64 kj_atomic_swap_u64(kjAtomic64* v, u64 swap) {
    return _InterlockedExchange64(v, swap);
}

KJ_INLINE void* kj_atomic_swap_ptr(kjAtomicPtr* v, void* swap) {
    return _InterlockedExchangePointer(v, swap);
}

KJ_INLINE u32 kj_atomic_inc_u32(kjAtomic32* v) {
    return _InterlockedIncrement(v);
}

KJ_INLINE u64 kj_atomic_inc_u64(kjAtomic64* v) {
    return _InterlockedIncrement64(v);
}

KJ_INLINE u32 kj_atomic_dec_u32(kjAtomic32* v) {
    return _InterlockedDecrement(v);
}

KJ_INLINE u64 kj_atomic_dec_u64(kjAtomic64* v) {
    return _InterlockedDecrement64(v);
}

KJ_INLINE u32 kj_atomic_fetch_add_u32(kjAtomic32* v, u32 add) {
    return _InterlockedExchangeAdd(v, add);
}

KJ_INLINE u64 kj_atomic_fetch_add_u64(kjAtomic64* v, u64 add) {
    return _InterlockedExchangeAdd64(v, add);
}

KJ_INLINE u32 kj_atomic_fetch_sub_u32(kjAtomic32* v, u32 sub) {
    return InterlockedExchangeAdd(v, -kj_cast(i32, sub));
}

KJ_INLINE u64 kj_atomic_fetch_sub_u64(kjAtomic64* v, u64 sub) {
    return _InterlockedExchangeAdd64(v, -kj_cast(i64, sub));
}

KJ_INLINE u32 kj_atomic_or_u32(kjAtomic32* v, u32 op) {
    return _InterlockedOr(v, op);
}

KJ_INLINE u64 kj_atomic_or_u64(kjAtomic64* v, u64 op) {
    return _InterlockedOr64(v, op);
}

KJ_INLINE u32 kj_atomic_and_u32(kjAtomic32* v, u32 op) {
    return _InterlockedAnd(v, op);
}

KJ_INLINE u64 kj_atomic_and_u64(kjAtomic64* v, u64 op) {
    return _InterlockedAnd64(v, op);
}

KJ_INLINE u32 kj_atomic_xor_u32(kjAtomic32* v, u32 op) {
    return _InterlockedXor(v, op);
}

KJ_INLINE u64 kj_atomic_xor_u64(kjAtomic64* v, u64 op) {
    return _InterlockedXor64(v, op);
}
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
KJ_INLINE void kj_atomic_read_fence(void) {
    __asm __volatile__ ("" ::: "memory");
}

KJ_INLINE void kj_atomic_write_fence(void) {
    __asm __volatile__ ("" ::: "memory");
}

KJ_INLINE void kj_atomic_rw_fence(void) {
    __asm __volatile__ ("" ::: "memory");
}

KJ_INLINE u32 kj_atomic_cmp_swap_u32(kjAtomic32* v, u32 cmp, u32 swap) {
    return __sync_val_compare_and_swap(v, cmp, swap);
}

KJ_INLINE u64 kj_atomic_cmp_swap_u64(kjAtomic64* v, u64 cmp, u64 swap) {
    return __sync_val_compare_and_swap(v, cmp, swap);
}

KJ_INLINE void* kj_atomic_cmp_swap_ptr(kjAtomicPtr* v, void* cmp, void* swap) {
    return kj_cast(void*, __sync_val_compare_and_swap(v, cmp, swap));
}

KJ_INLINE u32 kj_atomic_swap_u32(kjAtomic32* v, u32 swap) {
    return __sync_lock_test_and_set(v, swap);
}

KJ_INLINE u64 kj_atomic_swap_u64(kjAtomic64* v, u64 swap) {
    return __sync_lock_test_and_set(v, swap);
}

KJ_INLINE void* kj_atomic_swap_ptr(kjAtomicPtr* v, void* swap) {
    return kj_cast(void*, __sync_lock_test_and_set(v, swap));
}

KJ_INLINE u32 kj_atomic_inc_u32(kjAtomic32* v) {
    return __sync_add_and_fetch(v, 1);
}

KJ_INLINE u64 kj_atomic_inc_u64(kjAtomic64* v) {
    return __sync_add_and_fetch(v, 1);
}

KJ_INLINE u32 kj_atomic_dec_u32(kjAtomic32* v) {
    return __sync_sub_and_fetch(v, 1);
}

KJ_INLINE u64 kj_atomic_dec_u64(kjAtomic64* v) {
    return __sync_sub_and_fetch(v, 1);
}

KJ_INLINE u32 kj_atomic_fetch_add_u32(kjAtomic32* v, u32 add) {
    return __sync_fetch_and_add(v, add);
}

KJ_INLINE u64 kj_atomic_fetch_add_u64(kjAtomic64* v, u64 add) {
    return __sync_fetch_and_add(v, add);
}

KJ_INLINE u32 kj_atomic_fetch_sub_u32(kjAtomic32* v, u32 sub) {
    return __sync_fetch_and_sub(v, sub);
}

KJ_INLINE u64 kj_atomic_fetch_sub_u64(kjAtomic64* v, u64 sub) {
    return __sync_fetch_and_sub(v, sub);
}

KJ_INLINE u32 kj_atomic_or_u32(kjAtomic32* v, u32 op) {
    return __sync_fetch_and_or(v, op);
}

KJ_INLINE u64 kj_atomic_or_u64(kjAtomic64* v, u64 op) {
    return __sync_fetch_and_or(v, op);
}

KJ_INLINE u32 kj_atomic_and_u32(kjAtomic32* v, u32 op) {
    return __sync_fetch_and_and(v, op);
}

KJ_INLINE u64 kj_atomic_and_u64(kjAtomic64* v, u64 op) {
    return __sync_fetch_and_and(v, op);
}

KJ_INLINE u32 kj_atomic_xor_u32(kjAtomic32* v, u32 op) {
    return __sync_fetch_and_xor(v, op);
}

KJ_INLINE u64 kj_atomic_xor_u64(kjAtomic64* v, u64 op) {
    return __sync_fetch_and_xor(v, op);
}
#endif

#endif
