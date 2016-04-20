#ifndef KJ_MUTEX_H
#define KJ_MUTEX_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_MUTEX_VERSION_MAJOR 0
#define KJ_MUTEX_VERSION_MINOR 1
#define KJ_MUTEX_VERSION_PATCH 0

typedef struct kj_mutex kj_mutex_t;

kj_api kj_mutex_t kj_mutex(void);
kj_api void kj_mutex_lock(kj_mutex_t* mutex);
kj_api b32 kj_mutex_try_lock(kj_mutex_t* mutex);
kj_api void kj_mutex_unlock(kj_mutex_t* mutex);
kj_api void kj_mutex_destroy(kj_mutex_t* mutex);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_MUTEX_IMPLEMENTATION)

#if defined(KJ_SYS_WIN32)

#include <windows.h>

struct kj_mutex {
    CRITICAL_SECTION handle;
};

inline kj_mutex_t kj_mutex(void)
{
    kj_mutex_t mutex;
    InitializeCriticalSectionAndSpinCount(&mutex.handle, 1000);
    return mutex;
}

inline void kj_mutex_lock(kj_mutex_t* mutex)
{
    EnterCriticalSection(&mutex->handle);
}

inline b32 kj_mutex_try_lock(kj_mutex_t* mutex)
{
    return TryEnterCriticalSection(&mutex->handle) > 0;
}

inline void kj_mutex_unlock(kj_mutex_t* mutex)
{
    LeaveCriticalSection(&mutex->handle);
}

inline void kj_mutex_destroy(kj_mutex_t* mutex)
{
    DeleteCriticalSection(&mutex->handle);
}

#elif defined(KJ_SYS_LINUX)

#include <pthread.h>

struct kj_mutex {
    pthread_mutex_t handle;
};

inline kj_mutex_t kj_mutex(void)
{
    kj_mutex_t mutex;
    pthread_mutex_init(&mutex.handle, NULL);
    return mutex;
}

inline void kj_mutex_lock(kj_mutex_t* mutex)
{
    pthread_mutex_lock(&mutex->handle);
}

inline b32 kj_mutex_try_lock(kj_mutex_t* mutex)
{
    return pthread_mutex_trylock(&mutex->handle) == 0;
}

inline void kj_mutex_unlock(kj_mutex_t* mutex)
{
    pthread_mutex_unlock(&mutex->handle);
}

inline void kj_mutex_destroy(kj_mutex_t* mutex)
{
    pthread_mutex_destroy(&mutex->handle);
}
#else
#error KJ_MUTEX_UNSUPPORTED
#endif
#endif
