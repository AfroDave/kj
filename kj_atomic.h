// `kj_atomic.h`
// public domain - no warranty implied; use at your own risk
//
// usage:
//      #define KJ_ATOMIC_IMPL
//      #include "kj_atomic.h"

#ifndef KJ_ATOMIC_H
#define KJ_ATOMIC_H

#define KJ_ATOMIC_VERSION_MAJOR 0
#define KJ_ATOMIC_VERSION_MINOR 1
#define KJ_ATOMIC_VERSION_PATCH 1

KJ_EXTERN_BEGIN

KJ_API void kj_atomic_read_fence(void);
KJ_API void kj_atomic_write_fence(void);
KJ_API void kj_atomic_rw_fence(void);
KJ_API u32 kj_atomic_cmp_swap_u32(
        volatile u32* value, u32 expected_value, u32 new_value);
KJ_API u64 kj_atomic_cmp_swap_u64(
        volatile u64* value, u64 expected_value, u64 new_value);
KJ_API void* kj_atomic_cmp_swap_ptr(
        volatile void** value, void* expected_value, void* new_value);
KJ_API u32 kj_atomic_swap_u32(volatile u32* value, u32 new_value);
KJ_API u64 kj_atomic_swap_u64(volatile u64* value, u64 new_value);
KJ_API void* kj_atomic_swap_ptr(volatile void** value, void* new_value);
KJ_API u32 kj_atomic_inc_u32(volatile u32* value);
KJ_API u64 kj_atomic_inc_u64(volatile u64* value);
KJ_API u32 kj_atomic_dec_u32(volatile u32* value);
KJ_API u64 kj_atomic_dec_u64(volatile u64* value);
KJ_API u32 kj_atomic_fetch_add_u32(volatile u32* value, u32 add);
KJ_API u64 kj_atomic_fetch_add_u64(volatile u64* value, u64 add);
KJ_API u32 kj_atomic_fetch_sub_u32(volatile u32* value, u32 sub);
KJ_API u64 kj_atomic_fetch_sub_u64(volatile u64* value, u64 sub);

KJ_EXTERN_END

#endif

#if defined(KJ_ATOMIC_IMPL)

#if defined(KJ_COMPILER_MSVC)
#include <intrin.h>
#include <windows.h>

force_inline void kj_atomic_read_fence(void) {
    _ReadBarrier();
}

force_inline void kj_atomic_write_fence(void) {
    _WriteBarrier();
}

force_inline void kj_atomic_rw_fence(void) {
    _ReadWriteBarrier();
}

force_inline u32 kj_atomic_cmp_swap_u32(
        volatile u32* value, u32 expected_value, u32 new_value) {
    return _InterlockedCompareExchange(
            kj_cast(volatile LONG*, value), new_value, expected_value);
}

force_inline u64 kj_atomic_cmp_swap_u64(
        volatile u64* value, u64 expected_value, u64 new_value) {
    return _InterlockedCompareExchange64(
            kj_cast(volatile LONGLONG*, value), new_value, expected_value);
}

force_inline void* kj_atomic_cmp_swap_ptr(
        volatile void** value, void* expected_value, void* new_value) {
    return _InterlockedCompareExchangePointer(
            kj_cast(volatile PVOID*, value), new_value, expected_value);
}

force_inline u32 kj_atomic_swap_u32(volatile u32* value, u32 new_value) {
    return _InterlockedExchange(kj_cast(volatile LONG*, value), new_value);
}

force_inline u64 kj_atomic_swap_u64(volatile u64* value, u64 new_value) {
    return _InterlockedExchange64(
            kj_cast(volatile LONGLONG*, value), new_value);
}

force_inline void* kj_atomic_swap_ptr(volatile void** value, void* new_value) {
    return _InterlockedExchangePointer(
            kj_cast(volatile PVOID*, value), new_value);
}

force_inline u32 kj_atomic_inc_u32(volatile u32* value) {
    return _InterlockedIncrement(kj_cast(volatile LONG*, value));
}

force_inline u64 kj_atomic_inc_u64(volatile u64* value) {
    return _InterlockedIncrement64(kj_cast(volatile LONGLONG*, value));
}

force_inline u32 kj_atomic_dec_u32(volatile u32* value) {
    return _InterlockedDecrement(kj_cast(volatile LONG*, value));
}

force_inline u64 kj_atomic_dec_u64(volatile u64* value) {
    return _InterlockedDecrement64(kj_cast(volatile LONGLONG*, value));
}

force_inline u32 kj_atomic_fetch_add_u32(volatile u32* value, u32 add) {
    return _InterlockedExchangeAdd(kj_cast(volatile LONG*, value), add);
}

force_inline u64 kj_atomic_fetch_add_u64(volatile u64* value, u64 add) {
    return _InterlockedExchangeAdd64(kj_cast(volatile LONGLONG*, value), add);
}

force_inline u32 kj_atomic_fetch_sub_u32(volatile u32* value, u32 sub) {
    return InterlockedExchangeAdd(
            kj_cast(volatile LONG*, value), -kj_cast(i32, sub));
}

force_inline u64 kj_atomic_fetch_sub_u64(volatile u64* value, u64 sub) {
    return _InterlockedExchangeAdd64(
            kj_cast(volatile LONGLONG*, value), -kj_cast(i64, sub));
}

#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
force_inline void kj_atomic_read_fence(void) {
    __asm__ __volatile__ ("" ::: "memory");
}

force_inline void kj_atomic_write_fence(void) {
    __asm__ __volatile__ ("" ::: "memory");
}

force_inline void kj_atomic_rw_fence(void) {
    __asm__ __volatile__ ("" ::: "memory");
}

force_inline u32 kj_atomic_cmp_swap_u32(
        volatile u32* value, u32 expected_value, u32 new_value) {
    return __sync_val_compare_and_swap(value, expected_value, new_value);
}

force_inline u64 kj_atomic_cmp_swap_u64(
        volatile u64* value, u64 expected_value, u64 new_value) {
    return __sync_val_compare_and_swap(value, expected_value, new_value);
}

force_inline void* kj_atomic_cmp_swap_ptr(
        volatile void** value, void* expected_value, void* new_value) {
    return kj_cast(void*,
            __sync_val_compare_and_swap(value, expected_value, new_value));
}

force_inline u32 kj_atomic_swap_u32(volatile u32* value, u32 new_value) {
    return __sync_lock_test_and_set(value, new_value);
}

force_inline u64 kj_atomic_swap_u64(volatile u64* value, u64 new_value) {
    return __sync_lock_test_and_set(value, new_value);
}

force_inline void* kj_atomic_swap_ptr(volatile void** value, void* new_value) {
    return kj_cast(void*, __sync_lock_test_and_set(value, new_value));
}

force_inline u32 kj_atomic_inc_u32(volatile u32* value) {
    return __sync_add_and_fetch(value, 1);
}

force_inline u64 kj_atomic_inc_u64(volatile u64* value) {
    return __sync_add_and_fetch(value, 1);
}

force_inline u32 kj_atomic_dec_u32(volatile u32* value) {
    return __sync_sub_and_fetch(value, 1);
}

force_inline u64 kj_atomic_dec_u64(volatile u64* value) {
    return __sync_sub_and_fetch(value, 1);
}

force_inline u32 kj_atomic_fetch_add_u32(volatile u32* value, u32 add) {
    return __sync_fetch_and_add(value, add);
}

force_inline u64 kj_atomic_fetch_add_u64(volatile u64* value, u64 add) {
    return __sync_fetch_and_add(value, add);
}

force_inline u32 kj_atomic_fetch_sub_u32(volatile u32* value, u32 sub) {
    return __sync_fetch_and_sub(value, sub);
}

force_inline u64 kj_atomic_fetch_sub_u64(volatile u64* value, u64 sub) {
    return __sync_fetch_and_sub(value, sub);
}
#else
#error KJ_ATOMIC_UNSUPPORTED
#endif
#endif
