#ifndef KJ_THREAD_H
#define KJ_THREAD_H

#define KJ_THREAD_VERSION_MAJOR 0
#define KJ_THREAD_VERSION_MINOR 1
#define KJ_THREAD_VERSION_PATCH 0

typedef enum kj_thread_flags {
    KJ_THREAD_FLAG_NONE         = (0 << 0),
} kj_thread_flags_t;

typedef struct kj_thread kj_thread_t;

#define kj_thread_fn(name) void* name(void* data)
typedef kj_thread_fn(kj_thread_fn);

#if defined(__cplusplus)
extern "C" {
#endif

kj_api kj_thread_t kj_thread(kj_thread_fn* fn, void* data, u32 flags);
kj_api void kj_thread_join(kj_thread_t* thread);
kj_api void kj_thread_detach(kj_thread_t* thread);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_THREAD_IMPLEMENTATION)
u32 THREAD_COUNTER = 0;

#if defined(KJ_SYS_WIN32)

#include <windows.h>

struct kj_thread {
    u32 id;
    u32 flags;
    HANDLE handle;
    struct {
        kj_thread_fn* fn;
        void* data;
    } ctx;
};

kj_thread_t kj_thread(kj_thread_fn* fn, void* data, u32 flags);
{
    kj_thread_t res;
    res.id = _InterlockedIncrement(&THREAD_COUNTER);
    res.ctx.fn = fn;
    res.ctx.data = data;
    res.flags = flags;
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

#elif defined(KJ_SYS_LINUX)

#include <pthread.h>

struct kj_thread {
    u32 id;
    u32 flags;
    pthread_t handle;
    pthread_attr_t attr;
    struct {
        kj_thread_fn* fn;
        void* data;
    } ctx;
};

kj_thread_t kj_thread(kj_thread_fn* fn, void* data, u32 flags)
{
    kj_thread_t res;
    res.id = __sync_add_and_fetch(&THREAD_COUNTER, 1);
    res.ctx.fn = fn;
    res.ctx.data = data;
    res.flags = flags;
    pthread_create(&res.handle, &res.attr, fn, data);
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

#else
#error KJ_MUTEX_UNSUPPORTED
#endif

#endif
