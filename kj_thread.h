// `kj_thread.h`
// public domain - no warranty implied; use at your own risk
//
// usage:
//      #define KJ_THREAD_IMPL
//      #include "kj_thread.h"

#ifndef KJ_THREAD_H
#define KJ_THREAD_H

#define KJ_THREAD_VERSION_MAJOR 0
#define KJ_THREAD_VERSION_MINOR 1
#define KJ_THREAD_VERSION_PATCH 1

enum {
    KJ_THREAD_FLAG_NONE = KJ_BIT_ZERO,
};

#define KJ_THREAD_FN(name) void name(void* data)
typedef KJ_THREAD_FN(kjThreadFn);

#if defined(KJ_SYS_WIN32)
#include <windows.h>
typedef struct kjThread {
    i32 id;
    u32 flags;
    HANDLE handle;
    struct {
        kjThreadFn* fn;
        void* data;
    } ctx;
} kjThread;
#elif defined(KJ_SYS_LINUX)
#include <pthread.h>
typedef struct kjThread {
    i32 id;
    u32 flags;
    pthread_t handle;
    struct {
        kjThreadFn* fn;
        void* data;
    } ctx;
} kjThread;
#else
#error KJ_THREAD_UNSUPPORTED
#endif

KJ_EXTERN_BEGIN

KJ_API kjThread kj_thread(kjThreadFn* fn, void* data, u32 flags);
KJ_API void kj_thread_join(kjThread* thread);
KJ_API void kj_thread_detach(kjThread* thread);

KJ_EXTERN_END

#endif

#if defined(KJ_THREAD_IMPL)
volatile u32 THREAD_COUNTER = 0;

#if defined(KJ_SYS_WIN32)
kjThread kj_thread(kjThreadFn* fn, void* data, u32 flags) {
    kjThread res;
    res.id = _InterlockedIncrement(kj_cast(volatile LONG*, &THREAD_COUNTER));
    res.ctx.fn = fn;
    res.ctx.data = data;
    res.flags = flags;
    res.handle = CreateThread(
            NULL, 0, kj_cast(LPTHREAD_START_ROUTINE, fn), data, 0, NULL);
    return res;
}

void kj_thread_join(kjThread* thread) {
    WaitForSingleObjectEx(thread->handle, INFINITE, FALSE);
    CloseHandle(thread->handle);
}

void kj_thread_detach(kjThread* thread) {
    CloseHandle(thread->handle);
    thread->handle = NULL;
}

#elif defined(KJ_SYS_LINUX)
kjThread kj_thread(kjThreadFn* fn, void* data, u32 flags) {
    kjThread res;
    res.id = __sync_add_and_fetch(&THREAD_COUNTER, 1);
    res.ctx.fn = fn;
    res.ctx.data = data;
    res.flags = flags;
    pthread_create(&res.handle, NULL, kj_cast(void* (*)(void*), fn), data);
    return res;
}

void kj_thread_join(kjThread* thread) {
    pthread_join(thread->handle, NULL);
}

void kj_thread_detach(kjThread* thread) {
    pthread_detach(thread->handle);
}
#else
#error KJ_MUTEX_UNSUPPORTED
#endif

#endif
