// `kj_sync.h`
// public domain - no offered or implied warranty, use at your own risk
//
// usage:
//      #define KJ_SYNC_IMPL
//      #include "kj_sync.h"

#ifndef KJ_SYNC_H
#define KJ_SYNC_H

#define KJ_SYNC_VERSION_MAJOR 0
#define KJ_SYNC_VERSION_MINOR 1
#define KJ_SYNC_VERSION_PATCH 0

#if defined(KJ_SYS_WIN32)
#include <windows.h>
typedef CRITICAL_SECTION kjMutex;
typedef struct kjSemaphore {
    HANDLE handle;
} kjSemaphore;
#elif defined(KJ_SYS_LINUX)
#include <pthread.h>
#include <semaphore.h>
typedef pthread_mutex_t kjMutex;
typedef sem_t kjSemaphore;
#else
#error KJ_SYNC_UNSUPPORTED
#endif

#if defined(__cplusplus)
extern "C" {
#endif

KJ_API kjMutex kj_mutex(void);
KJ_API void kj_mutex_lock(kjMutex* mutex);
KJ_API b32 kj_mutex_try_lock(kjMutex* mutex);
KJ_API void kj_mutex_unlock(kjMutex* mutex);
KJ_API void kj_mutex_destroy(kjMutex* mutex);

KJ_API kjSemaphore kj_semaphore(u32 count, u32 max);
KJ_API b32 kj_semaphore_wait(kjSemaphore* semaphore);
KJ_API b32 kj_semaphore_try_wait(kjSemaphore* semaphore);
KJ_API void kj_semaphore_signal(kjSemaphore* semaphore, i32 count);
KJ_API void kj_semaphore_destroy(kjSemaphore* semaphore);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_SYNC_IMPL)

#if defined(KJ_SYS_WIN32)

kjMutex kj_mutex(void) {
    kjMutex mutex;
    InitializeCriticalSectionAndSpinCount(&mutex, 1000);
    return mutex;
}

void kj_mutex_lock(kjMutex* mutex) {
    EnterCriticalSection(mutex);
}

b32 kj_mutex_try_lock(kjMutex* mutex) {
    return TryEnterCriticalSection(mutex) > 0;
}

void kj_mutex_unlock(kjMutex* mutex) {
    LeaveCriticalSection(mutex);
}

void kj_mutex_destroy(kjMutex* mutex) {
    DeleteCriticalSection(mutex);
}

kjSemaphore kj_semaphore(u32 count, u32 max) {
    kjSemaphore res;
    res.handle = CreateSemaphore(NULL, count, max, NULL);
    return res;
}

b32 kj_semaphore_wait(kjSemaphore* semaphore) {
    u32 res = WaitForSingleObject(semaphore->handle, INFINITE);
    return res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT;
}

b32 kj_semaphore_try_wait(kjSemaphore* semaphore) {
    u32 res = WaitForSingleObject(semaphore->handle, 0);
    return res == WAIT_OBJECT_0;
}

void kj_semaphore_signal(kjSemaphore* semaphore, i32 count) {
    ReleaseSemaphore(semaphore->handle, count, NULL);
}

void kj_semaphore_destroy(kjSemaphore* semaphore) {
    CloseHandle(semaphore->handle); semaphore->handle = NULL;
}

#elif defined(KJ_SYS_LINUX)

kjMutex kj_mutex(void) {
    kjMutex mutex;
    pthread_mutex_init(&mutex, NULL);
    return mutex;
}

void kj_mutex_lock(kjMutex* mutex) {
    pthread_mutex_lock(mutex);
}

b32 kj_mutex_try_lock(kjMutex* mutex) {
    return pthread_mutex_trylock(mutex) == 0;
}

void kj_mutex_unlock(kjMutex* mutex) {
    pthread_mutex_unlock(mutex);
}

void kj_mutex_destroy(kjMutex* mutex) {
    pthread_mutex_destroy(mutex);
}


kjSemaphore kj_semaphore(u32 count, u32 max) {
    kjSemaphore res;
    kj_unused(max);
    sem_init(&res, 0, count);
    return res;
}

b32 kj_semaphore_wait(kjSemaphore* semaphore) {
    return sem_wait(semaphore);
}

b32 kj_semaphore_try_wait(kjSemaphore* semaphore) {
    return sem_trywait(semaphore);
}

void kj_semaphore_signal(kjSemaphore* semaphore, i32 count) {
    while(count-- > 0) {
        sem_post(semaphore);
    }
}

void kj_semaphore_destroy(kjSemaphore* semaphore) {
    sem_destroy(semaphore);
}

#else
#error KJ_SYNC_UNSUPPORTED
#endif
#endif
