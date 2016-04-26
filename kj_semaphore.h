#ifndef KJ_SEMAPHORE_H
#define KJ_SEMAPHORE_H

#define KJ_SEMAPHORE_VERSION_MAJOR 0
#define KJ_SEMAPHORE_VERSION_MINOR 1
#define KJ_SEMAPHORE_VERSION_PATCH 0

#define KJ_TIMEOUT_INFINITE 0xFFFFFFFF

#if defined(KJ_SYS_WIN32)
#include <windows.h>
typedef struct kjSemaphore {
    HANDLE handle;
} kjSemaphore;
#elif defined(KJ_SYS_LINUX)
#include <semaphore.h>
typedef sem kjSemaphore;
#else
#error KJ_SEMAPHORE_UNSUPPORTED
#endif

#if defined(__cplusplus)
extern "C" {
#endif

KJ_API kjSemaphore kj_semaphore(u32 count, u32 max);
KJ_API b32 kj_semaphore_wait(kjSemaphore* semaphore);
KJ_API b32 kj_semaphore_try_wait(kjSemaphore* semaphore);
KJ_API void kj_semaphore_signal(kjSemaphore* semaphore);
KJ_API void kj_semaphore_destroy(kjSemaphore* semaphore);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_SEMAPHORE_IMPLEMENTATION)

#if defined(KJ_SYS_WIN32)

kjSemaphore kj_semaphore(u32 count, u32 max)
{
    kjSemaphore res;
    res.handle = CreateSemaphore(NULL, count, max, NULL);
    return res;
}

b32 kj_semaphore_wait(kjSemaphore* semaphore)
{
    u32 res = WaitForSingleObject(semaphore->handle, INFINITE);
    return res == WAIT_OBJECT_0 || res == WAIT_TIMEOUT;
}

b32 kj_semaphore_try_wait(kjSemaphore* semaphore)
{
    u32 res = WaitForSingleObject(semaphore->handle, 0);
    return res == WAIT_OBJECT_0;
}

void kj_semaphore_signal(kjSemaphore* semaphore)
{
    ReleaseSemaphore(semaphore->handle, 1, NULL);
}

void kj_semaphore_destroy(kjSemaphore* semaphore)
{
    CloseHandle(semaphore->handle);
    semaphore->handle = NULL;
}

#elif defined(KJ_SYS_LINUX)

kjSemaphore kj_semaphore(u32 count, u32 max)
{
    kjSemaphore res;
    unused(max);
    sem_init(&res, 0, count);
    return res;
}

b32 kj_semaphore_wait(kjSemaphore* semaphore)
{
    return sem_wait(semaphore);
}

b32 kj_semaphore_try_wait(kjSemaphore* semaphore)
{
    return sem_trywait(semaphore);
}

void kj_semaphore_signal(kjSemaphore* semaphore)
{
    sem_post(semaphore);
}

void kj_semaphore_destroy(kjSemaphore* semaphore)
{
    sem_destroy(semaphore);
}

#else
#error KJ_SEMAPHORE_UNSUPPORTED
#endif
#endif
