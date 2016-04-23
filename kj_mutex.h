#ifndef KJ_MUTEX_H
#define KJ_MUTEX_H

#define KJ_MUTEX_VERSION_MAJOR 0
#define KJ_MUTEX_VERSION_MINOR 1
#define KJ_MUTEX_VERSION_PATCH 0

#if defined(KJ_SYS_WIN32)
#include <windows.h>
typedef CRITICAL_SECTION kj_mutex_t;
#elif defined(KJ_SYS_LINUX)
#include <pthread.h>
typedef pthread_mutex_t kj_mutex_t;
#else
#error KJ_MUTEX_UNSUPPORTED
#endif

#if defined(__cplusplus)
extern "C" {
#endif

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

kj_mutex_t kj_mutex(void)
{
    kj_mutex_t mutex;
    InitializeCriticalSectionAndSpinCount(&mutex, 1000);
    return mutex;
}

void kj_mutex_lock(kj_mutex_t* mutex)
{
    EnterCriticalSection(mutex);
}

b32 kj_mutex_try_lock(kj_mutex_t* mutex)
{
    return TryEnterCriticalSection(mutex) > 0;
}

void kj_mutex_unlock(kj_mutex_t* mutex)
{
    LeaveCriticalSection(mutex);
}

void kj_mutex_destroy(kj_mutex_t* mutex)
{
    DeleteCriticalSection(mutex);
}

#elif defined(KJ_SYS_LINUX)

kj_mutex_t kj_mutex(void)
{
    kj_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    return mutex;
}

void kj_mutex_lock(kj_mutex_t* mutex)
{
    pthread_mutex_lock(mutex);
}

b32 kj_mutex_try_lock(kj_mutex_t* mutex)
{
    return pthread_mutex_trylock(mutex) == 0;
}

void kj_mutex_unlock(kj_mutex_t* mutex)
{
    pthread_mutex_unlock(mutex);
}

void kj_mutex_destroy(kj_mutex_t* mutex)
{
    pthread_mutex_destroy(mutex);
}
#else
#error KJ_MUTEX_UNSUPPORTED
#endif
#endif
