#ifndef KJ_MUTEX_H
#define KJ_MUTEX_H

#define KJ_MUTEX_VERSION_MAJOR 0
#define KJ_MUTEX_VERSION_MINOR 1
#define KJ_MUTEX_VERSION_PATCH 0

#if defined(KJ_SYS_WIN32)
#include <windows.h>
typedef CRITICAL_SECTION kjMutex;
#elif defined(KJ_SYS_LINUX)
#include <pthread.h>
typedef pthread_mutex_t kjMutex;
#else
#error KJ_MUTEX_UNSUPPORTED
#endif

#if defined(__cplusplus)
extern "C" {
#endif

KJ_API kjMutex kj_mutex(void);
KJ_API void kj_mutex_lock(kjMutex* mutex);
KJ_API b32 kj_mutex_try_lock(kjMutex* mutex);
KJ_API void kj_mutex_unlock(kjMutex* mutex);
KJ_API void kj_mutex_destroy(kjMutex* mutex);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_MUTEX_IMPLEMENTATION)

#if defined(KJ_SYS_WIN32)

kjMutex kj_mutex(void)
{
    kjMutex mutex;
    InitializeCriticalSectionAndSpinCount(&mutex, 1000);
    return mutex;
}

void kj_mutex_lock(kjMutex* mutex)
{
    EnterCriticalSection(mutex);
}

b32 kj_mutex_try_lock(kjMutex* mutex)
{
    return TryEnterCriticalSection(mutex) > 0;
}

void kj_mutex_unlock(kjMutex* mutex)
{
    LeaveCriticalSection(mutex);
}

void kj_mutex_destroy(kjMutex* mutex)
{
    DeleteCriticalSection(mutex);
}

#elif defined(KJ_SYS_LINUX)

kjMutex kj_mutex(void)
{
    kjMutex mutex;
    pthread_mutex_init(&mutex, NULL);
    return mutex;
}

void kj_mutex_lock(kjMutex* mutex)
{
    pthread_mutex_lock(mutex);
}

b32 kj_mutex_try_lock(kjMutex* mutex)
{
    return pthread_mutex_trylock(mutex) == 0;
}

void kj_mutex_unlock(kjMutex* mutex)
{
    pthread_mutex_unlock(mutex);
}

void kj_mutex_destroy(kjMutex* mutex)
{
    pthread_mutex_destroy(mutex);
}
#else
#error KJ_MUTEX_UNSUPPORTED
#endif
#endif
