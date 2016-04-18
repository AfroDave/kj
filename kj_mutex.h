#ifndef KJ_MUTEX_H
#define KJ_MUTEX_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct kj_mutex kj_mutex_t;

kj_mutex_t kj_mutex(void);
void kj_mutex_lock(kj_mutex_t* mutex);
b32 kj_mutex_try_lock(kj_mutex_t* mutex);
void kj_mutex_unlock(kj_mutex_t* mutex);
void kj_mutex_destroy(kj_mutex_t* mutex);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_MUTEX_IMPLEMENTATION)

#if defined(KJ_COMPILER_MSVC)

#include <windows.h>

struct kj_mutex {
    CRITICAL_SECTION handle;
};

kj_mutex_t kj_mutex(void)
{
    kj_mutex_t mutex;
    InitialiseCriticalSectionAndSpinCount(&mutex.handle, 1000);
    return mutex;
}

void kj_mutex_lock(kj_mutex_t* mutex)
{
    EnterCriticalSection(&mutex->handle);
}

b32 kj_mutex_try_lock(kj_mutex_t* mutex)
{
    return TryEnterCriticalSection(&mutex->handle) > 0;
}

void kj_mutex_unlock(kj_mutex_t* mutex)
{
    LeaveCriticalSection(&mutex->handle);
}

void kj_mutex_destroy(kj_mutex_t* mutex)
{
    DeleteCriticalSection(&mutex->handle);
}

#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)

#include <pthread.h>

struct kj_mutex {
    pthread_mutex_t handle;
};

kj_mutex_t kj_mutex(void)
{
    kj_mutex_t mutex;
    pthread_mutex_init(&mutex.handle, NULL);
    return mutex;
}

void kj_mutex_lock(kj_mutex_t* mutex)
{
    pthread_mutex_lock(&mutex->handle);
}

b32 kj_mutex_try_lock(kj_mutex_t* mutex)
{
    return pthread_mutex_trylock(&mutex->handle) == 0;
}

void kj_mutex_unlock(kj_mutex_t* mutex)
{
    pthread_mutex_unlock(&mutex->handle);
}

void kj_mutex_destroy(kj_mutex_t* mutex)
{
    pthread_mutex_destroy(&mutex->handle);
}
#define KJ_MUTEX_UNSUPPORTED
#endif

#endif
