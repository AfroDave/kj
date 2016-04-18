#ifndef KJ_SSE_H
#define KJ_SSE_H

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(KJ_SYS_WIN32)
#include <intrin.h>
#elif defined(KJ_SYS_LINUX)
#include <x86intrin.h>
#endif

typedef __m128 f128;

#define kyj_sse_read_fence() _mm_lfence()
#define kyj_sse_write_fence() _mm_sfence()
#define kyj_sse_rw_fence() _mm_mfence()

#define kj_sse(a, b, c, d) _mm_set_ps(a, b, c, d)
#define kj_sser(a, b, c, d) _mm_setr_ps(a, b, c, d)
#define kj_sse_all(a) _mm_set1_ps(a)
#define kj_sse_zero() kj_sse_all(0.0f)
#define kj_sse_one() kj_sse_all(1.0f)

#define kj_sse_add(a, b) _mm_add_ps(a, b)
#define kj_sse_sub(a, b) _mm_sub_ps(a, b)
#define kj_sse_mul(a, b) _mm_mul_ps(a, b)
#define kj_sse_div(a, b) _mm_div_ps(a, b)

#define kj_sse_load(src) _mm_load_ps(src)
#define kj_sse_loadu(src) _mm_loadu_ps(src)
#define kj_sse_loadr(src) _mm_loadr_ps(src)
#define kj_sse_store(dst, src) _mm_store_ps(dst, src)
#define kj_sse_storeu(dst, src) _mm_storeu_ps(dst, src)
#define kj_sse_storer(dst, src) _mm_storer_ps(dst, src)

#define kj_sse_sqrt(a) _mm_sqrt_ps(a)
#define kj_sse_rsqrt(a) _mm_rsqrt_ps(a)

#define kj_sse_min(a, b) _mm_min_ps(a, b)
#define kj_sse_max(a, b) _mm_max_ps(a, b)
#define kj_sse_clamp(a, min, max) kj_sse_max((min), kj_sse_min((a), (max)))

#define kj_sse_shuffle_mask(a, b, c, d) _MM_SHUFFLE(a, b, c, d)
#define kj_sse_shuffle(a, b, m) _mm_shuffle_ps((a), (b), (m));
#define kj_sse_shuffle_abcd(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(3, 2, 1, 0))
#define kj_sse_shuffle_abdc(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(3, 2, 0, 1))
#define kj_sse_shuffle_acbd(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(3, 1, 2, 0))
#define kj_sse_shuffle_acdb(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(3, 1, 0, 2))
#define kj_sse_shuffle_adbc(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(3, 0, 2, 1))
#define kj_sse_shuffle_adcb(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(3, 0, 1, 2))
#define kj_sse_shuffle_bacd(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(2, 3, 1, 0))
#define kj_sse_shuffle_badc(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(2, 3, 0, 1))
#define kj_sse_shuffle_bcad(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(2, 1, 3, 0))
#define kj_sse_shuffle_bcda(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(2, 1, 0, 3))
#define kj_sse_shuffle_bdac(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(2, 0, 3, 1))
#define kj_sse_shuffle_bdca(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(2, 0, 1, 3))
#define kj_sse_shuffle_cabd(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(1, 3, 2, 0))
#define kj_sse_shuffle_cadb(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(1, 3, 0, 2))
#define kj_sse_shuffle_cbad(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(1, 2, 3, 0))
#define kj_sse_shuffle_cbda(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(1, 2, 0, 3))
#define kj_sse_shuffle_cdab(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(1, 0, 3, 2))
#define kj_sse_shuffle_cdba(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(1, 0, 2, 3))
#define kj_sse_shuffle_dabc(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(0, 3, 2, 1))
#define kj_sse_shuffle_dacb(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(0, 3, 1, 2))
#define kj_sse_shuffle_dbac(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(0, 2, 3, 1))
#define kj_sse_shuffle_dbca(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(0, 2, 1, 3))
#define kj_sse_shuffle_dcab(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(0, 1, 3, 2))
#define kj_sse_shuffle_dcba(a) kj_sse_shuffle((a), (a), kj_sse_shuffle_mask(0, 1, 2, 3))

#if defined(__cplusplus)
}
#endif

#endif
