// `kj_sse.h`
// public domain - no offered or implied warranty, use at your own risk

#ifndef KJ_SSE_H
#define KJ_SSE_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_SSE_VERSION_MAJOR 0
#define KJ_SSE_VERSION_MINOR 1
#define KJ_SSE_VERSION_PATCH 0

#if defined(KJ_SYS_WIN32)
#include <intrin.h>
#elif defined(KJ_SYS_LINUX)
#include <x86intrin.h>
#endif

typedef __m128 f128;
typedef __m128i i128;
typedef __m128i u128;

#define kj_sse_read_fence() _mm_lfence()
#define kj_sse_write_fence() _mm_sfence()
#define kj_sse_rw_fence() _mm_mfence()

#define kj_ssef(a, b, c, d) _mm_set_ps(a, b, c, d)
#define kj_ssef_reverse(a, b, c, d) _mm_setr_ps(a, b, c, d)
#define kj_ssef_all(a) _mm_set1_ps(a)
#define kj_ssef_zero() kj_ssef_all(0.0f)
#define kj_ssef_one() kj_ssef_all(1.0f)

#define kj_ssef_add(a, b) _mm_add_ps(a, b)
#define kj_ssef_sub(a, b) _mm_sub_ps(a, b)
#define kj_ssef_mul(a, b) _mm_mul_ps(a, b)
#define kj_ssef_div(a, b) _mm_div_ps(a, b)

#define kj_ssef_load(src) _mm_load_ps(src)
#define kj_ssef_loadu(src) _mm_loadu_ps(src)
#define kj_ssef_loadr(src) _mm_loadr_ps(src)
#define kj_ssef_store(dst, src) _mm_store_ps(dst, src)
#define kj_ssef_storeu(dst, src) _mm_storeu_ps(dst, src)
#define kj_ssef_storer(dst, src) _mm_storer_ps(dst, src)

#define kj_ssef_sqrt(a) _mm_sqrt_ps(a)
#define kj_ssef_rsqrt(a) _mm_rsqrt_ps(a)
#define kj_ssef_rcp(a) _mm_rcp_ps(a)

#define kj_ssef_cmpf_eq(a, b) _mm_cmpeq_ps(a, b)
#define kj_ssef_cmpf_neq(a, b) _mm_cmpneq_ps(a, b)
#define kj_ssef_cmpf_lt(a, b) _mm_cmplt_ps(a, b)
#define kj_ssef_cmpf_nlt(a, b) _mm_cmpnlt_ps(a, b)
#define kj_ssef_cmpf_le(a, b) _mm_cmple_ps(a, b)
#define kj_ssef_cmpf_nle(a, b) _mm_cmpnle_ps(a, b)
#define kj_ssef_cmpf_gt(a, b) _mm_cmpgt_ps(a, b)
#define kj_ssef_cmpf_ngt(a, b) _mm_cmpngt_ps(a, b)
#define kj_ssef_cmpf_ge(a, b) _mm_cmpge_ps(a, b)
#define kj_ssef_cmpf_nge(a, b) _mm_cmpnge_ps(a, b)

#define kj_ssef_cvt(a) _mm_cvtss_f32(a)

#define kj_ssef_min(a, b) _mm_min_ps(a, b)
#define kj_ssef_max(a, b) _mm_max_ps(a, b)
#define kj_ssef_clamp(a, min, max) kj_ssef_max((min), kj_ssef_min((a), (max)))

#define kj_sse_shuffle_mask(a, b, c, d) _MM_SHUFFLE(a, b, c, d)
#define kj_ssef_shuffle(a, b, m) _mm_shuffle_ps((a), (b), (m));
#define kj_ssef_shuffle_abcd(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(3, 2, 1, 0))
#define kj_ssef_shuffle_abdc(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(3, 2, 0, 1))
#define kj_ssef_shuffle_acbd(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(3, 1, 2, 0))
#define kj_ssef_shuffle_acdb(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(3, 1, 0, 2))
#define kj_ssef_shuffle_adbc(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(3, 0, 2, 1))
#define kj_ssef_shuffle_adcb(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(3, 0, 1, 2))
#define kj_ssef_shuffle_bacd(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(2, 3, 1, 0))
#define kj_ssef_shuffle_badc(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(2, 3, 0, 1))
#define kj_ssef_shuffle_bcad(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(2, 1, 3, 0))
#define kj_ssef_shuffle_bcda(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(2, 1, 0, 3))
#define kj_ssef_shuffle_bdac(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(2, 0, 3, 1))
#define kj_ssef_shuffle_bdca(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(2, 0, 1, 3))
#define kj_ssef_shuffle_cabd(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(1, 3, 2, 0))
#define kj_ssef_shuffle_cadb(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(1, 3, 0, 2))
#define kj_ssef_shuffle_cbad(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(1, 2, 3, 0))
#define kj_ssef_shuffle_cbda(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(1, 2, 0, 3))
#define kj_ssef_shuffle_cdab(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(1, 0, 3, 2))
#define kj_ssef_shuffle_cdba(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(1, 0, 2, 3))
#define kj_ssef_shuffle_dabc(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(0, 3, 2, 1))
#define kj_ssef_shuffle_dacb(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(0, 3, 1, 2))
#define kj_ssef_shuffle_dbac(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(0, 2, 3, 1))
#define kj_ssef_shuffle_dbca(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(0, 2, 1, 3))
#define kj_ssef_shuffle_dcab(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(0, 1, 3, 2))
#define kj_ssef_shuffle_dcba(a)                                                 \
    kj_ssef_shuffle((a), (a), kj_sse_shuffle_mask(0, 1, 2, 3))

#define kj_ssei(a, b, c, d) _mm_set_epi32(a, b, c, d)
#define kj_ssei_reverse(a, b, c, d) _mm_setr_epi32(a, b, c, d)
#define kj_ssei_all(a) _mm_set1_epi32(a)
#define kj_ssei_zero() kj_ssei_all(0)
#define kj_ssei_one() kj_ssei_all(1)

#define kj_ssei_load(src) _mm_load_si128(src)
#define kj_ssei_loadu(src) _mm_loadu_si128(src)
#define kj_ssei_store(dst, src) _mm_store_si128(dst, src)
#define kj_ssei_storeu(dst, src) _mm_storeu_si128(dst, src)

#define kj_ssei_or(a, b) _mm_or_si128(a, b)
#define kj_ssei_and(a, b) _mm_and_si128(a, b)
#define kj_ssei_xor(a, b) _mm_xor_si128(a, b)

#if defined(__cplusplus)
}
#endif

#endif
