/*
 * `kj_thread.h`
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

#if !defined(KJ_FORCE_INLINE)
#if defined(KJ_COMPILER_MSVC)
#define KJ_FORCE_INLINE __forceinline
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_FORCE_INLINE __attribute__((always_inline)) inline
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
typedef uint32_t kjThreadLocal;
#define KJ_THREAD_LOCAL_INVALID ((uint32_t) -1)
#elif defined(KJ_SYS_UNIX)
typedef pthread_mutex_t kjMutex;
typedef sem_t kjSemaphore;
typedef pthread_key_t kjThreadLocal;
#define KJ_THREAD_LOCAL_INVALID ((pthread_key_t) -1)
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
    void* result;
} kjThread;

#if !defined(KJ_THREAD_LOCAL)
#if defined(KJ_COMPILER_MSVC)
#define KJ_THREAD_LOCAL __declspec(thread)
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_THREAD_LOCAL __thread
#endif
#endif

typedef enum kjMemoryOrder {
    KJ_MEMORY_ORDER_RELAXED,
    KJ_MEMORY_ORDER_CONSUME,
    KJ_MEMORY_ORDER_ACQUIRE,
    KJ_MEMORY_ORDER_RELEASE,
    KJ_MEMORY_ORDER_ACQ_REL,
    KJ_MEMORY_ORDER_SEQ_CST,
    KJ_MEMORY_ORDER_COUNT
} kjMemoryOrder;

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

typedef kjAtomic32 kjSpinLock;

KJ_API void kj_yield(void);
KJ_API uint32_t kj_hardware_thread_count(void);
KJ_API void kj_sleep_ms(uint32_t ms);

KJ_API kjThread kj_thread(kjThreadFn* fn, void* data, uint32_t flags);
KJ_API void kj_thread_start(kjThread* thread);
KJ_API void* kj_thread_join(kjThread* thread);
KJ_API void kj_thread_detach(kjThread* thread);
KJ_API void kj_thread_set_name(kjThread* thread, const char* name);
KJ_API uint32_t kj_thread_id(void);
KJ_API kjThread kj_thread_current(void);

KJ_API kjThreadLocal kj_thread_local(void);
KJ_API void kj_thread_local_destroy(kjThreadLocal tls);
KJ_API void kj_thread_local_set(kjThreadLocal tls, void* value);
KJ_API void* kj_thread_local_get(kjThreadLocal tls);

KJ_API kjMutex kj_mutex(void);
KJ_API void kj_mutex_destroy(kjMutex* mutex);
KJ_API void kj_mutex_lock(kjMutex* mutex);
KJ_API bool kj_mutex_try_lock(kjMutex* mutex);
KJ_API void kj_mutex_unlock(kjMutex* mutex);

KJ_API kjSemaphore kj_semaphore(int32_t count);
KJ_API void kj_semaphore_destroy(kjSemaphore* semaphore);
KJ_API bool kj_semaphore_wait(kjSemaphore* semaphore);
KJ_API bool kj_semaphore_try_wait(kjSemaphore* semaphore);
KJ_API void kj_semaphore_signal(kjSemaphore* semaphore, uint32_t count);

KJ_API kjSpinLock kj_spinlock(void);
KJ_API void kj_spinlock_lock(kjSpinLock* spinlock);
KJ_API void kj_spinlock_unlock(kjSpinLock* spinlock);

KJ_API void kj_atomic_read_fence(void);
KJ_API void kj_atomic_write_fence(void);
KJ_API void kj_atomic_read_write_fence(void);

KJ_API void kj_atomic32_set(kjAtomic32* v, uint32_t value);
KJ_API uint32_t kj_atomic32_load(kjAtomic32* v);
KJ_API void kj_atomic32_store(kjAtomic32* v, uint32_t value);
KJ_API bool kj_atomic32_cmp_swap(kjAtomic32* v, uint32_t cmp, uint32_t swap);
KJ_API uint32_t kj_atomic32_swap(kjAtomic32* v, uint32_t swap);
KJ_API uint32_t kj_atomic32_fetch_add(kjAtomic32* v, uint32_t op);
KJ_API uint32_t kj_atomic32_fetch_sub(kjAtomic32* v, uint32_t op);
KJ_API uint32_t kj_atomic32_fetch_or(kjAtomic32* v, uint32_t op);
KJ_API uint32_t kj_atomic32_fetch_and(kjAtomic32* v, uint32_t op);
KJ_API uint32_t kj_atomic32_fetch_xor(kjAtomic32* v, uint32_t op);

KJ_API void kj_atomic64_set(kjAtomic64* v, uint64_t value);
KJ_API uint64_t kj_atomic64_load(kjAtomic64* v);
KJ_API void kj_atomic64_store(kjAtomic64* v, uint64_t value);
KJ_API bool kj_atomic64_cmp_swap(kjAtomic64* v, uint64_t cmp, uint64_t swap);
KJ_API uint64_t kj_atomic64_swap(kjAtomic64* v, uint64_t swap);
KJ_API uint64_t kj_atomic64_fetch_add(kjAtomic64* v, uint64_t op);
KJ_API uint64_t kj_atomic64_fetch_sub(kjAtomic64* v, uint64_t op);
KJ_API uint64_t kj_atomic64_fetch_or(kjAtomic64* v, uint64_t op);
KJ_API uint64_t kj_atomic64_fetch_and(kjAtomic64* v, uint64_t op);
KJ_API uint64_t kj_atomic64_fetch_xor(kjAtomic64* v, uint64_t op);

KJ_API void kj_atomic_ptr_set(kjAtomicPtr* v, void* value);
KJ_API void* kj_atomic_ptr_load(kjAtomicPtr* v);
KJ_API void kj_atomic_ptr_store(kjAtomicPtr* v, void* value);
KJ_API bool kj_atomic_ptr_cmp_swap(kjAtomicPtr* v, void* cmp, void* swap);
KJ_API void* kj_atomic_ptr_swap(kjAtomicPtr* v, void* swap);

KJ_API uint32_t kj_atomic32_load_explicit(kjAtomic32* v, kjMemoryOrder order);
KJ_API void kj_atomic32_store_explicit(kjAtomic32* v, uint32_t value, kjMemoryOrder order);
KJ_API bool kj_atomic32_cmp_swap_explicit(kjAtomic32* v, uint32_t cmp, uint32_t swap, kjMemoryOrder success, kjMemoryOrder failure);
KJ_API uint32_t kj_atomic32_swap_explicit(kjAtomic32* v, uint32_t swap, kjMemoryOrder order);
KJ_API uint32_t kj_atomic32_fetch_add_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order);
KJ_API uint32_t kj_atomic32_fetch_sub_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order);
KJ_API uint32_t kj_atomic32_fetch_or_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order);
KJ_API uint32_t kj_atomic32_fetch_and_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order);
KJ_API uint32_t kj_atomic32_fetch_xor_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order);

KJ_API uint64_t kj_atomic64_load_explicit(kjAtomic64* v, kjMemoryOrder order);
KJ_API void kj_atomic64_store_explicit(kjAtomic64* v, uint64_t value, kjMemoryOrder order);
KJ_API bool kj_atomic64_cmp_swap_explicit(kjAtomic64* v, uint64_t cmp, uint64_t swap, kjMemoryOrder success, kjMemoryOrder failure);
KJ_API uint64_t kj_atomic64_swap_explicit(kjAtomic64* v, uint64_t swap, kjMemoryOrder order);
KJ_API uint64_t kj_atomic64_fetch_add_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order);
KJ_API uint64_t kj_atomic64_fetch_sub_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order);
KJ_API uint64_t kj_atomic64_fetch_or_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order);
KJ_API uint64_t kj_atomic64_fetch_and_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order);
KJ_API uint64_t kj_atomic64_fetch_xor_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order);

KJ_API void* kj_atomic_ptr_load_explicit(kjAtomicPtr* v, kjMemoryOrder order);
KJ_API void kj_atomic_ptr_store_explicit(kjAtomicPtr* v, void* value, kjMemoryOrder order);
KJ_API bool kj_atomic_ptr_cmp_swap_explicit(kjAtomicPtr* v, void* cmp, void* swap, kjMemoryOrder success, kjMemoryOrder failure);
KJ_API void* kj_atomic_ptr_swap_explicit(kjAtomicPtr* v, void* swap, kjMemoryOrder order);

#if 0
typedef struct kjSpScQueue {
    kjAtomic64 read;
    kjAtomic64 write;
    uint64_t capacity;
    uint64_t stride;
    uint8_t data[];
} kjSpScQueue;

KJ_API void kj_spsc_queue(kjSpScQueue* queue, uint64_t capacity, uint64_t stride);
KJ_API bool kj_spsc_queue_enqueue(kjSpScQueue* queue, void* value);
KJ_API bool kj_spsc_queue_dequeue(kjSpScQueue* queue, void* value);
KJ_API bool kj_spsc_queue_peek(kjSpScQueue* queue, void* value);
#endif

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_THREAD_IMPL)

static KJ_THREAD_LOCAL kjThread _KJ_THREAD_CURRENT;

#if !defined(KJ_ASSERT)
#include <assert.h>
#define KJ_ASSERT assert
#endif

#if !defined(KJ_MEMCPY)
#include <string.h>
#define KJ_MEMCPY memcpy
#endif

void kj_yield(void) {
#if defined(KJ_SYS_WIN32)
    SwitchToThread();
#elif defined(KJ_SYS_UNIX)
    sched_yield();
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

uint32_t kj_hardware_thread_count(void) {
#if defined(KJ_SYS_WIN32)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif defined(KJ_SYS_UNIX)
    uint32_t res = sysconf(_SC_NPROCESSORS_ONLN);
    return res < 0 ? 1: res;
#endif
}

#if defined(KJ_SYS_WIN32)
static DWORD __cdecl _kj_win32_thread_fn(LPVOID ptr) {
    kjThread* thread = (kjThread*) ptr;
    if(thread) {
        thread->result = thread->fn(thread->data);
    }
    return 0;
}
#elif defined(KJ_SYS_UNIX)
static void* _kj_posix_thread_fn(void* ptr) {
    kjThread* thread = (kjThread*) ptr;
    if(thread) {
        thread->result = thread->fn(thread->data);
    }
    return NULL;
}
#endif

static bool _kj_thread_create(kjThread* thread) {
#if defined(KJ_SYS_WIN32)
    thread->handle = CreateThread(NULL, 0, _kj_win32_thread_fn, thread, 0, NULL);
    return thread->handle != INVALID_HANDLE_VALUE;
#elif defined(KJ_SYS_UNIX)
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    int32_t err = pthread_create(&thread->handle, &attr, _kj_posix_thread_fn, thread);
    pthread_attr_destroy(&attr);
    return err == 0;
#endif
}

kjThread kj_thread(kjThreadFn* fn, void* data, uint32_t flags) {
    _KJ_THREAD_CURRENT.fn = fn;
    _KJ_THREAD_CURRENT.data = data;
    _KJ_THREAD_CURRENT.result = NULL;
    _KJ_THREAD_CURRENT.flags = flags;
    _kj_thread_create(&_KJ_THREAD_CURRENT);
    return _KJ_THREAD_CURRENT;
}

void kj_thread_start(kjThread* thread) {
    if(thread->flags & KJ_THREAD_SUSPENDED) {
        thread->flags &= ~KJ_THREAD_SUSPENDED;
        _kj_thread_create(thread);
    }
}

void* kj_thread_join(kjThread* thread) {
#if defined(KJ_SYS_WIN32)
    WaitForSingleObjectEx(thread->handle, INFINITE, FALSE);
    CloseHandle(thread->handle);
    thread->handle = INVALID_HANDLE_VALUE;
#elif defined(KJ_SYS_UNIX)
    pthread_join(thread->handle, NULL);
    thread->handle = 0;
#endif
    return thread->result;
}

void kj_thread_set_name(kjThread* thread, const char* name) {
#if defined(KJ_SYS_WIN32)
    (void) thread;
    (void) name;
#if 0
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
#endif
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

kjThread kj_thread_current(void) {
    return _KJ_THREAD_CURRENT;
}

kjThreadLocal kj_thread_local(void) {
    kjThreadLocal res;
#if defined(KJ_SYS_WIN32)
    res = TlsAlloc();
    KJ_ASSERT(res != TLS_OUT_OF_INDEXES);
#elif defined(KJ_SYS_UNIX)
    res = pthread_key_create(tls, NULL);
    KJ_ASSERT(res == 0);
#endif
    return true;
}

KJ_FORCE_INLINE void kj_thread_local_destroy(kjThreadLocal tls) {
#if defined(KJ_SYS_WIN32)
    TlsFree(tls);
#elif defined(KJ_SYS_UNIX)
    pthread_key_delete(tls);
#endif
}

KJ_FORCE_INLINE void kj_thread_local_set(kjThreadLocal tls, void* value) {
#if defined(KJ_SYS_WIN32)
    TlsSetValue(tls, value);
#elif defined(KJ_SYS_UNIX)
    pthread_setspecific(tls, value);
#endif
}

KJ_FORCE_INLINE void* kj_thread_local_get(kjThreadLocal tls) {
#if defined(KJ_SYS_WIN32)
    return TlsGetValue(tls);
#elif defined(KJ_SYS_UNIX)
    return pthread_getspecific(tls);
#endif
}

kjMutex kj_mutex(void) {
    kjMutex res;
#if defined(KJ_SYS_WIN32)
    InitializeCriticalSectionAndSpinCount(&res, 4000);
#elif defined(KJ_SYS_UNIX)
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&res, &attr);
    pthread_mutexattr_destroy(&attr);
#endif
    return res;
}

KJ_FORCE_INLINE void kj_mutex_destroy(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    DeleteCriticalSection(mutex);
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_destroy(mutex);
#endif
}

KJ_FORCE_INLINE void kj_mutex_lock(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    EnterCriticalSection(mutex);
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_lock(mutex);
#endif
}

KJ_FORCE_INLINE bool kj_mutex_try_lock(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    return TryEnterCriticalSection(mutex) != 0;
#elif defined(KJ_SYS_UNIX)
    return pthread_mutex_trylock(mutex) == 0;
#endif
}

KJ_FORCE_INLINE void kj_mutex_unlock(kjMutex* mutex) {
#if defined(KJ_SYS_WIN32)
    LeaveCriticalSection(mutex);
#elif defined(KJ_SYS_UNIX)
    pthread_mutex_unlock(mutex);
#endif
}

kjSemaphore kj_semaphore(int32_t count) {
#if defined(KJ_SYS_WIN32)
    return CreateSemaphore(NULL, count, count, NULL);
#elif defined(KJ_SYS_UNIX)
    kjSemaphore res;
    sem_init(&res, 0, count);
    return res;
#endif
}

KJ_FORCE_INLINE void kj_semaphore_destroy(kjSemaphore* semaphore) {
#if defined(KJ_SYS_WIN32)
    CloseHandle(semaphore);
#elif defined(KJ_SYS_UNIX)
    sem_destroy(semaphore);
#endif
}

KJ_FORCE_INLINE bool kj_semaphore_wait(kjSemaphore* semaphore) {
#if defined(KJ_SYS_WIN32)
    return WaitForSingleObject(semaphore, INFINITE) == WAIT_OBJECT_0;
#elif defined(KJ_SYS_UNIX)
    int32_t err = 0;
    do {
        err = sem_wait(semaphore) == 0;
    } while(err == -1 && errno == EINTR);
    return err == 0;
#endif
}

KJ_FORCE_INLINE bool kj_semaphore_try_wait(kjSemaphore* semaphore) {
#if defined(KJ_SYS_WIN32)
    return WaitForSingleObject(semaphore, 0) == WAIT_OBJECT_0;
#elif defined(KJ_SYS_UNIX)
    return sem_trywait(semaphore) == 0;
#endif
}

KJ_FORCE_INLINE void kj_semaphore_signal(kjSemaphore* semaphore, uint32_t count) {
#if defined(KJ_SYS_WIN32)
    ReleaseSemaphore(semaphore, count, NULL);
#elif defined(KJ_SYS_UNIX)
    while(count--) { sem_post(semaphore); }
#endif
}

kjSpinLock kj_spinlock(void) {
    kjSpinLock res;
    kj_atomic32_store(&res, 0);
    return res;
}

KJ_FORCE_INLINE void kj_spinlock_lock(kjSpinLock* spinlock) {
    while(kj_atomic32_cmp_swap(spinlock, 1, 0) != 0) {
        kj_yield();
    }
}

KJ_FORCE_INLINE void kj_spinlock_unlock(kjSpinLock* spinlock) {
    kj_atomic32_store(spinlock, 0);
}

KJ_FORCE_INLINE void kj_atomic_read_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _ReadBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

KJ_FORCE_INLINE void kj_atomic_write_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _WriteBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

KJ_FORCE_INLINE void kj_atomic_read_write_fence(void) {
#if defined(KJ_COMPILER_MSVC)
    _ReadWriteBarrier();
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

//#if defined(KJ_SYS_WIN32)
//    _mm_mfence();
//#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
//    __sync_synchronize();
//#endif

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
const uint32_t _KJ_MEMORY_ORDER[KJ_MEMORY_ORDER_COUNT] = {
    __ATOMIC_RELAXED,
    __ATOMIC_CONSUME,
    __ATOMIC_ACQUIRE,
    __ATOMIC_RELEASE,
    __ATOMIC_ACQ_REL,
    __ATOMIC_SEQ_CST,
};
#endif

KJ_FORCE_INLINE void kj_atomic32(kjAtomic32* v, uint32_t value) {
    v->value = value;
}

KJ_FORCE_INLINE uint32_t kj_atomic32_load_explicit(kjAtomic32* v, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchange(&v->value, v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_load_n(&v->value, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE void kj_atomic32_store_explicit(kjAtomic32* v, uint32_t value, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    _InterlockedExchange(&v->value, value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __atomic_store_n(&v->value, value, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE bool kj_atomic32_cmp_swap_explicit(kjAtomic32* v, uint32_t cmp, uint32_t swap, kjMemoryOrder success, kjMemoryOrder failure) {
#if defined(KJ_COMPILER_MSVC)
    (void) success;
    (void) failure;
    return _InterlockedCompareExchange(&v->value, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_compare_exchange_n(&v->value, &cmp, swap, false, _KJ_MEMORY_ORDER[success], _KJ_MEMORY_ORDER[failure]);
#endif
}

KJ_FORCE_INLINE uint32_t kj_atomic32_swap_explicit(kjAtomic32* v, uint32_t swap, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchange(&v->value, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_exchange_n(&v->value, swap, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_add_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchangeAdd(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_add(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_sub_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return InterlockedExchangeAdd(&v->value, -((int32_t) op));
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_sub(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_or_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedOr(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_or(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_and_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedAnd(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_and(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_xor_explicit(kjAtomic32* v, uint32_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedXor(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_xor(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE void kj_atomic64(kjAtomic64* v, uint64_t value) {
    v->value = value;
}

KJ_FORCE_INLINE uint64_t kj_atomic64_load_explicit(kjAtomic64* v, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchange64(&v->value, v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_load_n(&v->value, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE void kj_atomic64_store_explicit(kjAtomic64* v, uint64_t value, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    _InterlockedExchange64(&v->value, value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __atomic_store_n(&v->value, value, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE bool kj_atomic64_cmp_swap_explicit(kjAtomic64* v, uint64_t cmp, uint64_t swap, kjMemoryOrder success, kjMemoryOrder failure) {
#if defined(KJ_COMPILER_MSVC)
    (void) success;
    (void) failure;
    return _InterlockedCompareExchange64(&v->value, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_compare_exchange_n(&v->value, &cmp, swap, false, _KJ_MEMORY_ORDER[success], _KJ_MEMORY_ORDER[failure]);
#endif
}

KJ_FORCE_INLINE uint64_t kj_atomic64_swap_explicit(kjAtomic64* v, uint64_t swap, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchange64(&v->value, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_exchange_n(&v->value, swap, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_add_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchangeAdd64(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_add(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_sub_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchangeAdd64(&v->value, -((int64_t) op));
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_sub(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_or_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedOr64(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_or(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_and_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedAnd64(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_and(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_xor_explicit(kjAtomic64* v, uint64_t op, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedXor64(&v->value, op);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_fetch_xor(&v->value, op, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE void kj_atomic_ptr(kjAtomicPtr* v, void* value) {
    v->value = value;
}

KJ_FORCE_INLINE void* kj_atomic_ptr_load_explicit(kjAtomicPtr* v, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchangePointer(&v->value, v->value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return (void*) __atomic_load_n(&v->value, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE void kj_atomic_ptr_store_explicit(kjAtomicPtr* v, void* value, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    _InterlockedExchangePointer(&v->value, value);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    __atomic_store_n(&v->value, value, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE bool kj_atomic_ptr_cmp_swap_explicit(kjAtomicPtr* v, void* cmp, void* swap, kjMemoryOrder success, kjMemoryOrder failure) {
#if defined(KJ_COMPILER_MSVC)
    (void) success;
    (void) failure;
    return _InterlockedCompareExchangePointer(&v->value, swap, cmp);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return __atomic_compare_exchange_n(&v->value, cmp, swap, false, _KJ_MEMORY_ORDER[success], _KJ_MEMORY_ORDER[failure]);
#endif
}

KJ_FORCE_INLINE void* kj_atomic_ptr_swap_explicit(kjAtomicPtr* v, void* swap, kjMemoryOrder order) {
#if defined(KJ_COMPILER_MSVC)
    (void) order;
    return _InterlockedExchangePointer(&v->value, swap);
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
    return (void*) __atomic_exchange_n(&v->value, swap, _KJ_MEMORY_ORDER[order]);
#endif
}

KJ_FORCE_INLINE uint32_t kj_atomic32_load(kjAtomic32* v) {
    return kj_atomic32_load_explicit(v, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE void kj_atomic32_store(kjAtomic32* v, uint32_t value) {
    kj_atomic32_store_explicit(v, value, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE bool kj_atomic32_cmp_swap(kjAtomic32* v, uint32_t cmp, uint32_t swap) {
    return kj_atomic32_cmp_swap_explicit(v, cmp, swap, KJ_MEMORY_ORDER_SEQ_CST, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint32_t kj_atomic32_swap(kjAtomic32* v, uint32_t swap) {
    return kj_atomic32_swap_explicit(v, swap, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_add(kjAtomic32* v, uint32_t op) {
    return kj_atomic32_fetch_add_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_sub(kjAtomic32* v, uint32_t op) {
    return kj_atomic32_fetch_sub_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_or(kjAtomic32* v, uint32_t op) {
    return kj_atomic32_fetch_or_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_and(kjAtomic32* v, uint32_t op) {
    return kj_atomic32_fetch_and_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint32_t kj_atomic32_fetch_xor(kjAtomic32* v, uint32_t op) {
    return kj_atomic32_fetch_xor_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint64_t kj_atomic64_load(kjAtomic64* v) {
    return kj_atomic64_load_explicit(v, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE void kj_atomic64_store(kjAtomic64* v, uint64_t value) {
    kj_atomic64_store_explicit(v, value, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE bool kj_atomic64_cmp_swap(kjAtomic64* v, uint64_t cmp, uint64_t swap) {
    return kj_atomic64_cmp_swap_explicit(v, cmp, swap, KJ_MEMORY_ORDER_SEQ_CST, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint64_t kj_atomic64_swap(kjAtomic64* v, uint64_t swap) {
    return kj_atomic64_swap_explicit(v, swap, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_add(kjAtomic64* v, uint64_t op) {
    return kj_atomic64_fetch_add_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_sub(kjAtomic64* v, uint64_t op) {
    return kj_atomic64_fetch_sub_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_or(kjAtomic64* v, uint64_t op) {
    return kj_atomic64_fetch_or_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_and(kjAtomic64* v, uint64_t op) {
    return kj_atomic64_fetch_and_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE uint64_t kj_atomic64_fetch_xor(kjAtomic64* v, uint64_t op) {
    return kj_atomic64_fetch_xor_explicit(v, op, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE void* kj_atomic_ptr_load(kjAtomicPtr* v) {
    return kj_atomic_ptr_load_explicit(v, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE void kj_atomic_ptr_store(kjAtomicPtr* v, void* value) {
    kj_atomic_ptr_store_explicit(v, value, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE bool kj_atomic_ptr_cmp_swap(kjAtomicPtr* v, void* cmp, void* swap) {
    return kj_atomic_ptr_cmp_swap_explicit(v, cmp, swap, KJ_MEMORY_ORDER_SEQ_CST, KJ_MEMORY_ORDER_SEQ_CST);
}

KJ_FORCE_INLINE void* kj_atomic_ptr_swap(kjAtomicPtr* v, void* swap) {
    return kj_atomic_ptr_swap_explicit(v, swap, KJ_MEMORY_ORDER_SEQ_CST);
}

#if 0
void kj_spsc_queue(kjSpScQueue* queue, uint64_t capacity, uint64_t stride) {
    kj_atomic64(&queue->read, 0);
    kj_atomic64(&queue->write, 0);
    queue->capacity = capacity;
    queue->stride = stride;
}

void kj_spsc_queue_reset(kjSpScQueue* queue) {
    kj_atomic64(&queue->read, 0);
    kj_atomic64(&queue->write, 0);
}

KJ_FORCE_INLINE bool kj_spsc_queue_enqueue(kjSpScQueue* queue, void* value) {
    uint64_t stride = queue->stride;
    uint64_t capacity = queue->capacity;
    uint64_t read = kj_atomic64_load_explicit(&queue->read, KJ_MEMORY_ORDER_ACQUIRE);
    uint64_t write = kj_atomic64_load_explicit(&queue->write, KJ_MEMORY_ORDER_RELAXED);
    uint32_t count = write - read;
    if(count >= capacity) { return false; }
    KJ_MEMCPY(queue->data + write * stride, value, stride);
    kj_atomic64_store_explicit(&queue->write, (write + 1) % capacity, KJ_MEMORY_ORDER_RELEASE);
    return true;
}

KJ_FORCE_INLINE bool kj_spsc_queue_dequeue(kjSpScQueue* queue, void* value) {
    uint64_t stride = queue->stride;
    uint64_t capacity = queue->capacity;
    uint64_t read = kj_atomic64_load_explicit(&queue->read, KJ_MEMORY_ORDER_RELAXED);
    uint64_t write = kj_atomic64_load_explicit(&queue->write, KJ_MEMORY_ORDER_ACQUIRE);
    if(read == write) { return false; }
    KJ_MEMCPY(value, queue->data + read * stride, stride);
    kj_atomic64_store_explicit(&queue->read, (read + 1) % capacity, KJ_MEMORY_ORDER_RELEASE);
    return true;
}

KJ_FORCE_INLINE bool kj_spsc_queue_peek(kjSpScQueue* queue, void* value) {
    uint64_t stride = queue->stride;
    uint64_t read = kj_atomic64_load_explicit(&queue->read, KJ_MEMORY_ORDER_RELAXED);
    uint64_t write = kj_atomic64_load_explicit(&queue->write, KJ_MEMORY_ORDER_ACQUIRE);
    if(read == write) { return false; }
    KJ_MEMCPY(value, queue->data + read * stride, stride);
    return true;
}
#endif

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
