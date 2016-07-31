// `kj_simd.h`
//
// ---------------------------------- LICENSE ----------------------------------
// This software is in the public domain.  Where that dedication is not
// recognized, you are granted a perpetual, irrevocable license to copy,
// distribute, and modify the source code as you see fit.
//
// The source code is provided "as is", without warranty of any kind, express
// or implied. No attribution is required, but always appreciated.
// =============================================================================
//
// usage:
//      #define KJ_SIMD_IMPL
//      #include "kj_simd.h"

#ifndef KJ_SIMD_H
#define KJ_SIMD_H

#define KJ_SIMD_VERSION_MAJOR 0
#define KJ_SIMD_VERSION_MINOR 1
#define KJ_SIMD_VERSION_PATCH 2

#if defined(KJ_SYS_WIN32)
#include <intrin.h>
#elif defined(KJ_SYS_LINUX)
#include <x86intrin.h>
#endif

typedef __m128 f128;
typedef __m128i i128;
typedef __m128i u128;

KJ_EXTERN_BEGIN

#define kj_simd_read_fence() _mm_lfence()
#define kj_simd_write_fence() _mm_sfence()
#define kj_simd_rw_fence() _mm_mfence()

#define kj_simdf(a, b, c, d) _mm_set_ps(a, b, c, d)
#define kj_simdf_reverse(a, b, c, d) _mm_setr_ps(a, b, c, d)
#define kj_simdf_all(a) _mm_set1_ps(a)
#define kj_simdf_zero() kj_simdf_all(0.0f)
#define kj_simdf_one() kj_simdf_all(1.0f)

#define kj_simdf_add(a, b) _mm_add_ps(a, b)
#define kj_simdf_sub(a, b) _mm_sub_ps(a, b)
#define kj_simdf_mul(a, b) _mm_mul_ps(a, b)
#define kj_simdf_div(a, b) _mm_div_ps(a, b)

#define kj_simdf_load(src) _mm_load_ps(src)
#define kj_simdf_loadu(src) _mm_loadu_ps(src)
#define kj_simdf_loadr(src) _mm_loadr_ps(src)
#define kj_simdf_store(dst, src) _mm_store_ps(dst, src)
#define kj_simdf_storeu(dst, src) _mm_storeu_ps(dst, src)
#define kj_simdf_storer(dst, src) _mm_storer_ps(dst, src)

#define kj_simdf_sqrt(a) _mm_sqrt_ps(a)
#define kj_simdf_rsqrt(a) _mm_rsqrt_ps(a)
#define kj_simdf_rcp(a) _mm_rcp_ps(a)

#define kj_simdf_cmpf_eq(a, b) _mm_cmpeq_ps(a, b)
#define kj_simdf_cmpf_neq(a, b) _mm_cmpneq_ps(a, b)
#define kj_simdf_cmpf_lt(a, b) _mm_cmplt_ps(a, b)
#define kj_simdf_cmpf_nlt(a, b) _mm_cmpnlt_ps(a, b)
#define kj_simdf_cmpf_le(a, b) _mm_cmple_ps(a, b)
#define kj_simdf_cmpf_nle(a, b) _mm_cmpnle_ps(a, b)
#define kj_simdf_cmpf_gt(a, b) _mm_cmpgt_ps(a, b)
#define kj_simdf_cmpf_ngt(a, b) _mm_cmpngt_ps(a, b)
#define kj_simdf_cmpf_ge(a, b) _mm_cmpge_ps(a, b)
#define kj_simdf_cmpf_nge(a, b) _mm_cmpnge_ps(a, b)

#define kj_simdf_cvt(a) _mm_cvtss_f32(a)

#define kj_simdf_min(a, b) _mm_min_ps(a, b)
#define kj_simdf_max(a, b) _mm_max_ps(a, b)
#define kj_simdf_clamp(a, min, max) _mm_max_ps((min), _mm_min_ps((a), (max)))

#define kj_simd_shuf_mask(a, b, c, d) _MM_SHUFFLE(a, b, c, d)
#define kj_simdf_shuf(a, b, m) _mm_shuffle_ps((a), (b), (m));
#define kj_simdf_shuf_abcd(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(3, 2, 1, 0))
#define kj_simdf_shuf_abdc(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(3, 2, 0, 1))
#define kj_simdf_shuf_acbd(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(3, 1, 2, 0))
#define kj_simdf_shuf_acdb(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(3, 1, 0, 2))
#define kj_simdf_shuf_adbc(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(3, 0, 2, 1))
#define kj_simdf_shuf_adcb(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(3, 0, 1, 2))
#define kj_simdf_shuf_bacd(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(2, 3, 1, 0))
#define kj_simdf_shuf_badc(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(2, 3, 0, 1))
#define kj_simdf_shuf_bcad(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(2, 1, 3, 0))
#define kj_simdf_shuf_bcda(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(2, 1, 0, 3))
#define kj_simdf_shuf_bdac(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(2, 0, 3, 1))
#define kj_simdf_shuf_bdca(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(2, 0, 1, 3))
#define kj_simdf_shuf_cabd(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(1, 3, 2, 0))
#define kj_simdf_shuf_cadb(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(1, 3, 0, 2))
#define kj_simdf_shuf_cbad(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(1, 2, 3, 0))
#define kj_simdf_shuf_cbda(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(1, 2, 0, 3))
#define kj_simdf_shuf_cdab(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(1, 0, 3, 2))
#define kj_simdf_shuf_cdba(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(1, 0, 2, 3))
#define kj_simdf_shuf_dabc(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(0, 3, 2, 1))
#define kj_simdf_shuf_dacb(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(0, 3, 1, 2))
#define kj_simdf_shuf_dbac(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(0, 2, 3, 1))
#define kj_simdf_shuf_dbca(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(0, 2, 1, 3))
#define kj_simdf_shuf_dcab(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(0, 1, 3, 2))
#define kj_simdf_shuf_dcba(a) _mm_suffle_ps((a), (a), _MM_SHUFFLE(0, 1, 2, 3))

#define kj_simdi(a, b, c, d) _mm_set_epi32(a, b, c, d)
#define kj_simdi_reverse(a, b, c, d) _mm_setr_epi32(a, b, c, d)
#define kj_simdi_all(a) _mm_set1_epi32(a)
#define kj_simdi_zero() _mm_set1_epi32(0)
#define kj_simdi_one() _mm_set1_epi32(1)

#define kj_simdi_load(src) _mm_load_si128(src)
#define kj_simdi_loadu(src) _mm_loadu_si128(src)
#define kj_simdi_store(dst, src) _mm_store_si128(dst, src)
#define kj_simdi_storeu(dst, src) _mm_storeu_si128(dst, src)

#define kj_simdi_or(a, b) _mm_or_si128(a, b)
#define kj_simdi_and(a, b) _mm_and_si128(a, b)
#define kj_simdi_xor(a, b) _mm_xor_si128(a, b)

KJ_EXTERN_END

#endif
