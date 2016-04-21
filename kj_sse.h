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

#define kj_sse_read_fence() _mm_lfence()
#define kj_sse_write_fence() _mm_sfence()
#define kj_sse_rw_fence() _mm_mfence()

#define kj_ssef(a, b, c, d) _mm_set_ps(a, b, c, d)
#define kj_sse_reversef(a, b, c, d) _mm_setr_ps(a, b, c, d)
#define kj_sse_allf(a) _mm_set1_ps(a)
#define kj_sse_zerof() kj_sse_all(0.0f)
#define kj_sse_onef() kj_sse_all(1.0f)

#define kj_sse_addf(a, b) _mm_add_ps(a, b)
#define kj_sse_subf(a, b) _mm_sub_ps(a, b)
#define kj_sse_mulf(a, b) _mm_mul_ps(a, b)
#define kj_sse_divf(a, b) _mm_div_ps(a, b)

#define kj_sse_loadf(src) _mm_load_ps(src)
#define kj_sse_loadf_unaligned(src) _mm_loadu_ps(src)
#define kj_sse_loadf_reverse(src) _mm_loadr_ps(src)
#define kj_sse_storef(dst, src) _mm_store_ps(dst, src)
#define kj_sse_storef_unaligned(dst, src) _mm_storeu_ps(dst, src)
#define kj_sse_storef_reverse(dst, src) _mm_storer_ps(dst, src)

#define kj_sse_sqrtf(a) _mm_sqrt_ps(a)
#define kj_sse_rsqrtf(a) _mm_rsqrt_ps(a)
#define kj_sse_rcpf(a) _mm_rcp_ps(a)

#define kj_sse_cmpf_eq(a, b) _mm_cmpeq_ps(a, b)
#define kj_sse_cmpf_neq(a, b) _mm_cmpneq_ps(a, b)
#define kj_sse_cmpf_lt(a, b) _mm_cmplt_ps(a, b)
#define kj_sse_cmpf_nlt(a, b) _mm_cmpnlt_ps(a, b)
#define kj_sse_cmpf_le(a, b) _mm_cmple_ps(a, b)
#define kj_sse_cmpf_nle(a, b) _mm_cmpnle_ps(a, b)
#define kj_sse_cmpf_gt(a, b) _mm_cmpgt_ps(a, b)
#define kj_sse_cmpf_ngt(a, b) _mm_cmpngt_ps(a, b)
#define kj_sse_cmpf_ge(a, b) _mm_cmpge_ps(a, b)
#define kj_sse_cmpf_nge(a, b) _mm_cmpnge_ps(a, b)

#define kj_sse_cvtf(a) _mm_cvtss_f32(a)

#define kj_sse_minf(a, b) _mm_min_ps(a, b)
#define kj_sse_maxf(a, b) _mm_max_ps(a, b)
#define kj_sse_clampf(a, min, max) kj_sse_max((min), kj_sse_min((a), (max)))

#define kj_sse_shuffle_mask(a, b, c, d) _MM_SHUFFLE(a, b, c, d)
#define kj_sse_shufflef(a, b, m) _mm_shuffle_ps((a), (b), (m));
#define kj_sse_shufflef_abcd(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(3, 2, 1, 0))
#define kj_sse_shufflef_abdc(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(3, 2, 0, 1))
#define kj_sse_shufflef_acbd(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(3, 1, 2, 0))
#define kj_sse_shufflef_acdb(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(3, 1, 0, 2))
#define kj_sse_shufflef_adbc(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(3, 0, 2, 1))
#define kj_sse_shufflef_adcb(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(3, 0, 1, 2))
#define kj_sse_shufflef_bacd(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(2, 3, 1, 0))
#define kj_sse_shufflef_badc(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(2, 3, 0, 1))
#define kj_sse_shufflef_bcad(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(2, 1, 3, 0))
#define kj_sse_shufflef_bcda(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(2, 1, 0, 3))
#define kj_sse_shufflef_bdac(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(2, 0, 3, 1))
#define kj_sse_shufflef_bdca(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(2, 0, 1, 3))
#define kj_sse_shufflef_cabd(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(1, 3, 2, 0))
#define kj_sse_shufflef_cadb(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(1, 3, 0, 2))
#define kj_sse_shufflef_cbad(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(1, 2, 3, 0))
#define kj_sse_shufflef_cbda(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(1, 2, 0, 3))
#define kj_sse_shufflef_cdab(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(1, 0, 3, 2))
#define kj_sse_shufflef_cdba(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(1, 0, 2, 3))
#define kj_sse_shufflef_dabc(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(0, 3, 2, 1))
#define kj_sse_shufflef_dacb(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(0, 3, 1, 2))
#define kj_sse_shufflef_dbac(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(0, 2, 3, 1))
#define kj_sse_shufflef_dbca(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(0, 2, 1, 3))
#define kj_sse_shufflef_dcab(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(0, 1, 3, 2))
#define kj_sse_shufflef_dcba(a) kj_sse_shufflef((a), (a), kj_sse_shuffle_mask(0, 1, 2, 3))

#if defined(__cplusplus)
}
#endif

#endif
