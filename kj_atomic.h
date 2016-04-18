#ifndef KJ_ATOMIC_H
#define KJ_ATOMIC_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_ATOMIC_VERSION_MAJOR 0
#define KJ_ATOMIC_VERSION_MINOR 1
#define KJ_ATOMIC_VERSION_PATCH 0

kj_def void kj_atomic_read_fence(void);
kj_def void kj_atomic_write_fence(void);
kj_def void kj_atomic_rw_fence(void);
kj_def u32 kj_atomic_cmp_swap_u32(u32* value, u32 expected_value, u32 new_value);
kj_def u64 kj_atomic_cmp_swap_u64(u64* value, u64 expected_value, u64 new_value);
kj_def void* kj_atomic_cmp_swap_ptr(void** value, void* expected_value, void* new_value);
kj_def u32 kj_atomic_swap_u32(u32* value, u32 new_value);
kj_def u64 kj_atomic_swap_u64(u64* value, u64 new_value);
kj_def void* kj_atomic_swap_ptr(void** value, void* new_value);
kj_def u32 kj_atomic_inc_u32(u32* value);
kj_def u64 kj_atomic_inc_u64(u64* value);
kj_def u32 kj_atomic_dec_u32(u32* value);
kj_def u64 kj_atomic_dec_u64(u64* value);
kj_def u32 kj_atomic_fetch_add_u32(u32* value, u32 add);
kj_def u64 kj_atomic_fetch_add_u64(u64* value, u64 add);
kj_def u32 kj_atomic_fetch_sub_u32(u32* value, u32 sub);
kj_def u64 kj_atomic_fetch_sub_u64(u64* value, u64 sub);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_ATOMIC_IMPLEMENTATION)

#if defined(KJ_COMPILER_MSVC)

#include <windows.h>

inline void kj_atomic_read_fence(void)
{
    _ReadBarrier();
}

inline void kj_atomic_write_fence(void)
{
    _WriteBarrier();
}

inline void kj_atomic_rw_fence(void)
{
    _ReadWriteBarrier();
}

inline u32 kj_atomic_cmp_swap_u32(u32* value, u32 expected_value, u32 new_value)
{
    return _InterlockedCompareExchange(value, new_value, expected_value);
}

inline u64 kj_atomic_cmp_swap_u64(u64* value, u64 expected_value, u64 new_value)
{
    return _InterlockedCompareExchange64(cast(volatile LONGLONG*, value), new_value, expected_value);
}

inline void* kj_atomic_cmp_swap_ptr(void** value, void* expected_value, void* new_value)
{
    return _InterlockedCompareExchangePointer(cast(volatile PVOID*, value), new_value, expected_value);
}

inline u32 kj_atomic_swap_u32(u32* value, u32 new_value)
{
    return _InterlockedExchange(value, new_value);
}

inline u64 kj_atomic_swap_u64(u64* value, u64 new_value)
{
    return _InterlockedExchange64(cast(volatile LONGLONG*, value), new_value);
}

inline void* kj_atomic_swap_ptr(void** value, void* new_value)
{
    return _InterlockedExchangePointer(cast(volatile PVOID*, value), new_value);
}

inline u32 kj_atomic_inc_u32(u32* value)
{
    return _InterlockedIncrement(value);
}

inline u64 kj_atomic_inc_u64(u64* value)
{
    return _InterlockedIncrement64(cast(volatile LONGLONG*, value));
}

inline u32 kj_atomic_dec_u32(u32* value)
{
    return _InterlockedDecrement(value);
}

inline u64 kj_atomic_dec_u64(u64* value)
{
    return _InterlockedDecrement64(cast(volatile LONGLONG*, value));
}

inline u32 kj_atomic_fetch_add_u32(u32* value, u32 add)
{
    return _InterlockedExchangeAdd(value, add);
}

inline u64 kj_atomic_fetch_add_u64(u64* value, u64 add)
{
    return _InterlockedExchangeAdd64(cast(volatile LONGLONG*, value), add);
}

inline u32 kj_atomic_fetch_sub_u32(u32* value, u32 sub)
{
    return InterlockedExchangeAdd(value, -cast(i32, sub));
}

inline u64 kj_atomic_fetch_sub_u64(u64* value, u64 sub)
{
    return _InterlockedExchangeAdd64(cast(volatile LONGLONG*, value), -cast(i64, sub));
}

#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)

inline void kj_atomic_read_fence(void)
{
    __asm__ __volatile__ ("" ::: "memory");
}

inline void kj_atomic_write_fence(void)
{
    __asm__ __volatile__ ("" ::: "memory");
}

inline void kj_atomic_rw_fence(void)
{
    __asm__ __volatile__ ("" ::: "memory");
}

inline u32 kj_atomic_cmp_swap_u32(u32* value, u32 expected_value, u32 new_value)
{
    return __sync_val_compare_and_swap(value, expected_value, new_value);
}

inline u64 kj_atomic_cmp_swap_u64(u64* value, u64 expected_value, u64 new_value)
{
    return __sync_val_compare_and_swap(value, expected_value, new_value);
}

inline void* kj_atomic_cmp_swap_ptr(void** value, void* expected_value, void* new_value)
{
    return __sync_val_compare_and_swap(value, expected_value, new_value);
}

inline u32 kj_atomic_swap_u32(u32* value, u32 new_value)
{
    return __sync_lock_test_and_set(value, new_value);
}

inline u64 kj_atomic_swap_u64(u64* value, u64 new_value)
{
    return __sync_lock_test_and_set(value, new_value);
}

inline void* kj_atomic_swap_ptr(void** value, void* new_value)
{
    return __sync_lock_test_and_set(value, new_value);
}

inline u32 kj_atomic_inc_u32(u32* value)
{
    return __sync_add_and_fetch(value, 1);
}

inline u64 kj_atomic_inc_u64(u64* value)
{
    return __sync_add_and_fetch(value, 1);
}

inline u32 kj_atomic_dec_u32(u32* value)
{
    return __sync_sub_and_fetch(value, 1);
}

inline u64 kj_atomic_dec_u64(u64* value)
{
    return __sync_sub_and_fetch(value, 1);
}

inline u32 kj_atomic_fetch_add_u32(u32* value, u32 add)
{
    return __sync_fetch_and_add(value, add);
}

inline u64 kj_atomic_fetch_add_u64(u64* value, u64 add)
{
    return __sync_fetch_and_add(value, add);
}

inline u32 kj_atomic_fetch_sub_u32(u32* value, u32 sub)
{
    return __sync_fetch_and_sub(value, sub);
}

inline u64 kj_atomic_fetch_sub_u64(u64* value, u64 sub)
{
    return __sync_fetch_and_sub(value, sub);
}
#else
#error KJ_ATOMIC_UNSUPPORTED
#endif
#endif
