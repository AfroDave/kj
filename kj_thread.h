#ifndef KJ_THREAD_H
#define KJ_THREAD_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_THREAD_VERSION_MAJOR 0
#define KJ_THREAD_VERSION_MINOR 1
#define KJ_THREAD_VERSION_PATCH 0

typedef struct kj_thread kj_thread_t;

#define kj_thread_fn(name) void* name(void* data)
typedef kj_thread_fn(kj_thread_fn);

kj_thread_t kj_thread(kj_thread_fn* fn, void* data);
void kj_thread_join(kj_thread_t* thread);
void kj_thread_detach(kj_thread_t* thread);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_THREAD_IMPLEMENTATION)
global u32 THREAD_COUNTER = 0;

#if defined(KJ_COMPILER_MSVC)

#include <windows.h>

struct kj_thread {
    u32 id;
    HANDLE handle;
    struct {
        kj_thread_fn* fn;
        void* data;
    } ctx;
};

kj_thread_t kj_thread(kj_thread_fn* fn, void* data)
{
    kj_thread_t res;
    res.id = THREAD_COUNTER++;
    res.ctx.fn = fn;
    res.ctx.data = data;
    res.handle = CreateThread(NULL, 0, cast(LPTHREAD_START_ROUTINE, fn), data, 0, NULL);
}

void kj_thread_join(kj_thread_t* thread)
{
    WaitForSingleObjectEx(thread->handle, INFINITE, FALSE);
    CloseHandle(thread->handle);
}

void kj_thread_detach(kj_thread_t* thread)
{
    CloseHandle(thread->handle);
    thread->handle = NULL;
}

#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)

#include <pthread.h>

struct kj_thread {
    u32 id;
    pthread_t handle;
    struct {
        kj_thread_fn* fn;
        void* data;
    } ctx;
};

kj_thread_t kj_thread(kj_thread_fn* fn, void* data)
{
    kj_thread_t res;
    res.id = THREAD_COUNTER++;
    res.ctx.fn = fn;
    res.ctx.data = data;
    pthread_create(&res.handle, NULL, fn, data);
    return res;
}

void kj_thread_join(kj_thread_t* thread)
{
    pthread_join(thread->handle, NULL);
}

void kj_thread_detach(kj_thread_t* thread)
{
    pthread_detach(thread->handle);
}

#define KJ_MUTEX_UNSUPPORTED
#endif

#endif
