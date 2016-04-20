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

kj_api kj_semaphore_t kj_semaphore(u32 count, u32 max);
kj_api b32 kj_semaphore_wait(kj_semaphore_t* semaphore);
kj_api b32 kj_semaphore_try_wait(kj_semaphore_t* semaphore);
kj_api void kj_semaphore_signal(kj_semaphore_t* semaphore);
kj_api void kj_semaphore_destroy(kj_semaphore_t* semaphore);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_SEMAPHORE_IMPLEMENTATION)

#if defined(KJ_SYS_WIN32)

#include <windows.h>

struct kj_semaphore {
    HANDLE handle;
};

inline kj_semaphore_t kj_semaphore(u32 count, u32 max)
{
    kj_semaphore_t semaphore;
    semaphore.handle = CreateSemaphore(NULL, count, max, NULL);
    return semaphore;
}

inline b32 kj_semaphore_wait(kj_semaphore_t* semaphore)
{
    u32 res = WaitForSingleObject(semaphore->handle, INFINITE);
    return res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT;
}

inline b32 kj_semaphore_try_wait(kj_semaphore_t* semaphore)
{
    u32 res = WaitForSingleObject(semaphore->handle, 0);
    return res == WAIT_OBJECT_0;
}

inline void kj_semaphore_signal(kj_semaphore_t* semaphore)
{
    ReleaseSemaphore(semaphore->handle, 1, NULL);
}

inline void kj_semaphore_destroy(kj_semaphore_t* semaphore)
{
    CloseHandle(&semaphore->handle);
    semaphore->handle = NULL;
}

#elif defined(KJ_SYS_LINUX)

#include <semaphore.h>

struct kj_semaphore {
    sem_t handle;
};

inline kj_semaphore_t kj_semaphore(u32 count, u32 max)
{
    kj_semaphore_t semaphore;
    unused(max);
    sem_init(&semaphore.handle, 0, count);
    return semaphore;
}

inline b32 kj_semaphore_wait(kj_semaphore_t* semaphore)
{
    return sem_wait(&semaphore->handle);
}

inline b32 kj_semaphore_try_wait(kj_semaphore_t* semaphore)
{
    return sem_trywait(&semaphore->handle);
}

inline void kj_semaphore_signal(kj_semaphore_t* semaphore)
{
    sem_post(&semaphore->handle);
}

inline void kj_semaphore_destroy(kj_semaphore_t* semaphore)
{
    sem_destroy(&semaphore->handle);
}

#else
#error KJ_SEMAPHORE_UNSUPPORTED
#endif
#endif
