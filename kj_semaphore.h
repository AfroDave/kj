#ifndef KJ_SEMAPHORE_H
#define KJ_SEMAPHORE_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_SEMAPHORE_VERSION_MAJOR 0
#define KJ_SEMAPHORE_VERSION_MINOR 1
#define KJ_SEMAPHORE_VERSION_PATCH 0

#define KJ_TIMEOUT_INFINITE 0xFFFFFFFF

typedef struct kj_semaphore kj_semaphore_t;

kj_semaphore_t kj_semaphore(u32 count, u32 max);
b32 kj_semaphore_wait(kj_semaphore_t* semaphore, u32 timeout);
b32 kj_semaphore_try_wait(kj_semaphore_t* semaphore);
u32 kj_semaphore_count(kj_semaphore_t* semaphore);
void kj_semaphore_signal(kj_semaphore_t* semaphore);
void kj_semaphore_destroy(kj_semaphore_t* semaphore);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_SEMAPHORE_IMPLEMENTATION)

#if defined(KJ_COMPILER_MSVC)

#include <windows.h>

struct kj_semaphore {
    HANDLE handle;
    u32 count;
    u32 max;
};

kj_semaphore_t kj_semaphore(u32 count, u32 max)
{
    kj_semaphore_t semaphore;
    semaphore.handle = CreateSemaphore(NULL, count, max, NULL);
    semaphore.count = count;
    semaphore.max = max;
    return semaphore;
}

b32 kj_semaphore_wait(kj_semaphore_t* semaphore, u32 timeout)
{
    timeout = timeout == KJ_TIMEOUT_INFINITE ? INFINITE: timeout;
    u32 res = WaitForSingleObject(semaphore->handle, timeout);
    return res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT;
}

b32 kj_semaphore_try_wait(kj_semaphore_t* semaphore)
{
    return kj_semaphore_wait(semaphore, 0);
}

u32 kj_semaphore_count(kj_semaphore_t* semaphore)
{
    return semaphore->count;
}

void kj_semaphore_signal(kj_semaphore_t* semaphore)
{
    ReleaseSemaphore(semaphore->handle, 1, NULL);
}

void kj_semaphore_destroy(kj_semaphore_t* semaphore)
{
    CloseHandle(&semaphore->handle);
    semaphore->handle = NULL;
}

#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)

#include <semaphore.h>
#include <pthread.h>

struct kj_semaphore {
    sem_t handle;
    u32 count;
    u32 max;
};

kj_semaphore_t kj_semaphore(u32 count, u32 max)
{
    kj_semaphore_t semaphore;
    sem_init(&semaphore.handle, 0, count);
    semaphore.count = count;
    semaphore.max = max;
    return semaphore;
}

b32 kj_semaphore_wait(kj_semaphore_t* semaphore, u32 timeout)
{
    struct timespec ts;
    ts.tv_nsec = timeout * 1000000;
    return sem_timedwait(&semaphore->handle, &ts);
}

b32 kj_semaphore_try_wait(kj_semaphore_t* semaphore)
{
    return kj_semaphore_wait(semaphore, 0);
}

u32 kj_semaphore_count(kj_semaphore_t* semaphore)
{
    return semaphore->count;
}

void kj_semaphore_signal(kj_semaphore_t* semaphore)
{
    sem_post(&semaphore->handle);
}

void kj_semaphore_destroy(kj_semaphore_t* semaphore)
{
    sem_destroy(&semaphore->handle);
}

#define KJ_SEMAPHORE_UNSUPPORTED
#endif

#endif
