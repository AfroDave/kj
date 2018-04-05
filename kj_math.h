/*
 * `kj_math.h`
 *
 * usage:
 *      #define KJ_MATH_IMPL
 *      #include "kj_math.h"
 */

#if !defined(KJ_MATH_H)
#define KJ_MATH_H

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_MSC_VER)
#if !defined(KJ_COMPILER_MSVC)
#define KJ_COMPILER_MSVC _MSC_VER
#endif
#elif defined(__clang__)
#if !defined(KJ_COMPILER_CLANG)
#define KJ_COMPILER_CLANG
#endif
#elif defined(__GNUC__) || defined(__GNUG__)
#if !defined(KJ_COMPILER_GNU)
#define KJ_COMPILER_GNU
#endif
#else
#error "Unsupported Compiler"
#endif

#if !defined(NULL)
#if defined(KJ_COMPILER_MSVC)
#define NULL (0)
#elif defined(KJ_COMPILER_GNU)
#define NULL __null
#else
#define NULL ((void*) 0)
#endif
#endif

#if !defined(KJ_ALIGN)
#if defined(KJ_COMPILER_MSVC)
#define KJ_ALIGN(a) __declspec(align(a))
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_ALIGN(a) __attribute__((aligned(a)))
#endif
#endif

#if !defined(KJ_FORCE_INLINE)
#if defined(KJ_COMPILER_MSVC)
#define KJ_FORCE_INLINE __forceinline
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
#define KJ_FORCE_INLINE __attribute__((always_inline)) inline
#endif
#endif

#if defined(KJ_COMPILER_MSVC)
#if KJ_COMPILER_MSVC < 1300
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
#else
typedef signed __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef signed __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include <stdbool.h>

#if defined(KJ_MATH_STATIC)
#define KJ_MATH_API static
#else
#define KJ_MATH_API extern
#endif

typedef union kjBinary32 {
    float f;
    uint32_t i;
} kjBinary32;

typedef struct kjVec2f {
    float x, y;
} kjVec2f;

typedef struct kjVec2i {
    int32_t x, y;
} kjVec2i;

typedef struct kjVec2u {
    uint32_t x, y;
} kjVec2u;

typedef struct kjVec3f {
    float x, y, z;
} kjVec3f;

typedef struct kjVec3i {
    int32_t x, y, z;
} kjVec3i;

typedef struct kjVec3u {
    uint32_t x, y, z;
} kjVec3u;

typedef struct kjVec4f {
    float x, y, z, w;
} kjVec4f KJ_ALIGN(16);

typedef struct kjVec4i {
    int32_t x, y, z, w;
} kjVec4i;

typedef struct kjVec4u {
    uint32_t x, y, z, w;
} kjVec4u;

typedef kjVec4f kjQuatf;

typedef union kjMat2f {
    float e[2][2];
    float a[4];
    kjVec2f c[2];
} kjMat2f;

typedef union kjMat3f {
    float e[3][3];
    float a[9];
    kjVec3f c[3];
} kjMat3f;

typedef union kjMat4f {
    float e[4][4];
    float a[16];
    kjVec4f c[4];
} kjMat4f KJ_ALIGN(16);

#if !defined(KJ_PI)
#define KJ_PI (3.141592653589793f)
#endif

#if !defined(KJ_HALF_PI)
#define KJ_HALF_PI (1.570796326948965f)
#endif

#if !defined(KJ_QUARTER_PI)
#define KJ_QUARTER_PI (0.785398163397448f)
#endif

#if !defined(KJ_TAU)
#define KJ_TAU (6.283185307179586f)
#endif

#if !defined(KJ_E)
#define KJ_E (2.718281828459045f)
#endif

#if !defined(KJ_PHI)
#define KJ_PHI (1.618033988749894f)
#endif

#if !defined(KJ_R2D)
#define KJ_R2D (57.295779513082320f)
#endif

#if !defined(KJ_D2R)
#define KJ_D2R (0.017453292519943f)
#endif

#if !defined(KJ_FLOAT32_EXPONENT_BITS)
#define KJ_FLOAT32_EXPONENT_BITS (8)
#endif

#if !defined(KJ_FLOAT32_EXPONENT_BIAS)
#define KJ_FLOAT32_EXPONENT_BIAS (0x7F)
#endif

#if !defined(KJ_FLOAT32_MIN_EXPONENT)
#define KJ_FLOAT32_MIN_EXPONENT (-126)
#endif

#if !defined(KJ_FLOAT32_MAX_EXPONENT)
#define KJ_FLOAT32_MAX_EXPONENT (127)
#endif

#if !defined(KJ_FLOAT32_SIGN_MASK)
#define KJ_FLOAT32_SIGN_MASK (0x80000000)
#endif

#if !defined(KJ_FLOAT32_EXPONENT_MASK)
#define KJ_FLOAT32_EXPONENT_MASK (0x7F800000)
#endif

#if !defined(KJ_FLOAT32_EXPONENT_SHIFT)
#define KJ_FLOAT32_EXPONENT_SHIFT (0x23)
#endif

#if !defined(KJ_FLOAT32_MANTISSA_MASK)
#define KJ_FLOAT32_MANTISSA_MASK (0x007FFFFF)
#endif

#if !defined(KJ_FLOAT32_MIN)
#define KJ_FLOAT32_MIN (-3.4028234663852886e+38f)
#endif

#if !defined(KJ_FLOAT32_MAX)
#define KJ_FLOAT32_MAX (3.4028234663852886e+38f)
#endif

#if !defined(KJ_FLOAT32_EPS)
#define KJ_FLOAT32_EPS (1.1920928955078125e-07f)
#endif

#if !defined(KJ_FLOAT32_INF)
#define KJ_FLOAT32_INF (kj_float32_inf())
#endif

#if !defined(KJ_FLOAT32_NEGATIVE_INF)
#define KJ_FLOAT32_NEGATIVE_INF (kj_float32_negative_inf())
#endif

#if !defined(KJ_FLOAT32_NAN)
#define KJ_FLOAT32_NAN (kj_float32_nan())
#endif

#if !defined(KJ_INT32_MIN)
#define KJ_INT32_MIN (-2147483647 - 1)
#endif

#if !defined(KJ_INT32_MAX)
#define KJ_INT32_MAX (2147483647)
#endif

#if !defined(KJ_INT64_MIN)
#define KJ_INT64_MIN (-9223372036854775807 - 1)
#endif

#if !defined(KJ_INT64_MAX)
#define KJ_INT64_MAX (9223372036854775807)
#endif

#if !defined(KJ_UINT32_MIN)
#define KJ_UINT32_MIN (0x00000000)
#endif

#if !defined(KJ_UINT32_MAX)
#define KJ_UINT32_MAX (0xFFFFFFFF)
#endif

#if !defined(KJ_UINT64_MIN)
#define KJ_UINT64_MIN (0x0000000000000000)
#endif

#if !defined(KJ_UINT64_MAX)
#define KJ_UINT64_MAX (0xFFFFFFFFFFFFFFFF)
#endif

#if !defined(KJ_MIN)
#define KJ_MIN(a, b) ((a) < (b) ? (a): (b))
#endif

#if !defined(KJ_MAX)
#define KJ_MAX(a, b) ((a) > (b) ? (a): (b))
#endif

#if !defined(KJ_CLAMP)
#define KJ_CLAMP(a, min, max) (KJ_MIN(KJ_MAX((a), (min)), (max)))
#endif

#if !defined(KJ_CLAMP01)
#define KJ_CLAMP01(a) (KJ_CLAMP(a, 0, 1))
#endif

#if !defined(KJ_CLAMP11)
#define KJ_CLAMP11(a) (KJ_CLAMP(a, -1, 1))
#endif

#if !defined(KJ_WRAP)
#define KJ_WRAP(a, min, max) ((a) > (max) ? (min): (a) < (min) ? (max): (a))
#endif

#if !defined(KJ_LERP)
#define KJ_LERP(min, max, t) (((t) * ((max) - (min))) + (min))
#endif

#if !defined(KJ_REMAP)
#define KJ_REMAP(a, fmin, fmax, tmin, tmax) ((tmin) + (((a) - (fmin)) / ((fmax) - (fmin))) * ((tmax) - (tmin)))
#endif

#if !defined(KJ_REMAP01)
#define KJ_REMAP01(a, min, max) (((a) - (min)) / ((max) - (min)))
#endif

#if !defined(KJ_REMAP11)
#define KJ_REMAP11(a, min, max) ((2 * (a) - (max) - (min)) / ((max) - (min)))
#endif

#if !defined(KJ_ABS)
#define KJ_ABS(a) ((a) >= 0 ? (a): -(a))
#endif

#if !defined(KJ_SIGN)
#define KJ_SIGN(a) ((0 < (a)) - ((a) < 0))
#endif

#if !defined(KJ_ROUND_TO)
#define KJ_ROUND_TO(a, b) ((a) + (((b) - 1) - (((a) - 1) % (b))))
#endif

KJ_MATH_API float kj_float32_inf();
KJ_MATH_API float kj_float32_negative_inf();
KJ_MATH_API float kj_float32_nan();
KJ_MATH_API bool kj_float32_is_finite(float f);
KJ_MATH_API bool kj_float32_is_infinity(float f);
KJ_MATH_API bool kj_float32_is_positive(float f);
KJ_MATH_API bool kj_float32_is_negative(float f);
KJ_MATH_API bool kj_float32_signbit(float a);
KJ_MATH_API float kj_float32_set_sign(float f, bool negative);
KJ_MATH_API float kj_float32_fma(float a, float b, float c);

KJ_MATH_API bool kj_float32_eq(float a, float b, float epsilon);

KJ_MATH_API float kj_signf(float a);
KJ_MATH_API float kj_rsqrtf(float a);
KJ_MATH_API float kj_sqrtf(float a);
KJ_MATH_API float kj_cbrtf(float a);
KJ_MATH_API float kj_sinf(float a);
KJ_MATH_API float kj_cosf(float a);
KJ_MATH_API float kj_tanf(float a);
KJ_MATH_API float kj_asinf(float a);
KJ_MATH_API float kj_acosf(float a);
KJ_MATH_API float kj_atanf(float a);
KJ_MATH_API float kj_atan2f(float y, float x);
KJ_MATH_API float kj_expf(float a);
KJ_MATH_API float kj_exp2f(float a);
KJ_MATH_API float kj_lnf(float a);
KJ_MATH_API float kj_log10f(float a);
KJ_MATH_API float kj_log2f(float a);
KJ_MATH_API float kj_powf(float a, float b);
KJ_MATH_API float kj_floorf(float a);
KJ_MATH_API float kj_ceilf(float a);
KJ_MATH_API float kj_roundf(float a);
KJ_MATH_API float kj_absf(float a);
KJ_MATH_API float kj_minf(float a, float b);
KJ_MATH_API float kj_maxf(float a, float b);
KJ_MATH_API float kj_modf(float a, float b);
KJ_MATH_API float kj_fractf(float a);

KJ_MATH_API float kj_radian_wrapf(float a);
KJ_MATH_API float kj_degree_wrapf(float a);
KJ_MATH_API float kj_radian_clampf(float radians, float min, float max);
KJ_MATH_API float kj_degree_clampf(float degrees, float min, float max);
KJ_MATH_API float kj_degree_normalisef(float radians);
KJ_MATH_API float kj_radian_normalisef(float degrees);

KJ_MATH_API float kj_wrapf(float a, float min, float max);
KJ_MATH_API float kj_clampf(float a, float min, float max);
KJ_MATH_API float kj_clamp01f(float a);

KJ_MATH_API float kj_lerpf(float min, float max, float t);
KJ_MATH_API float kj_inv_lerpf(float min, float max, float t);

KJ_MATH_API float kj_radian_lerpf(float min, float max, float t);
KJ_MATH_API float kj_degree_lerpf(float min, float max, float t);

KJ_MATH_API float kj_stepf(float step, float t);
KJ_MATH_API float kj_smoothstepf(float min, float max, float t);

/* Normalised, t = [0.0f, 1.0f] */
KJ_MATH_API float kj_smoothstep01f(float t);

KJ_MATH_API float kj_quadratic_start01f(float t);
KJ_MATH_API float kj_cubic_start01f(float t);
KJ_MATH_API float kj_quartic_start01f(float t);
KJ_MATH_API float kj_quintic_start01f(float t);

KJ_MATH_API float kj_quadratic_stop01f(float t);
KJ_MATH_API float kj_cubic_stop01f(float t);
KJ_MATH_API float kj_quartic_stop01f(float t);
KJ_MATH_API float kj_quintic_stop01f(float t);

KJ_MATH_API kjVec2f kj_quadratic_bezier_vec2f(kjVec2f cp[3], float t);
KJ_MATH_API kjVec2f kj_cubic_bezier_vec2f(kjVec2f cp[4], float t);
KJ_MATH_API kjVec3f kj_quadratic_bezier_vec3f(kjVec3f cp[3], float t);
KJ_MATH_API kjVec3f kj_cubic_bezier_vec3f(kjVec3f cp[4], float t);

KJ_MATH_API kjVec2f kj_vec2f(float x, float y);
KJ_MATH_API kjVec2i kj_vec2i(int32_t x, int32_t y);
KJ_MATH_API kjVec2u kj_vec2u(uint32_t x, uint32_t y);
KJ_MATH_API kjVec2f kj_vec2f_zero(void);
KJ_MATH_API kjVec2i kj_vec2i_zero(void);
KJ_MATH_API kjVec2u kj_vec2u_zero(void);
KJ_MATH_API kjVec2f kj_vec2f_one(void);
KJ_MATH_API kjVec2i kj_vec2i_one(void);
KJ_MATH_API kjVec2u kj_vec2u_one(void);
KJ_MATH_API kjVec2f kj_vec2f_inf(void);
KJ_MATH_API kjVec2f kj_vec2f_all(float a);
KJ_MATH_API kjVec2i kj_vec2i_all(int32_t a);
KJ_MATH_API kjVec2u kj_vec2u_all(uint32_t a);
KJ_MATH_API kjVec2f kj_vec2f_negate(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_add(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_addf(kjVec2f a, float b);
KJ_MATH_API kjVec2f kj_vec2f_sub(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_subf(kjVec2f a, float b);
KJ_MATH_API kjVec2f kj_vec2f_mul(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_mulf(kjVec2f a, float b);
KJ_MATH_API kjVec2f kj_vec2f_div(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_divf(kjVec2f a, float b);
KJ_MATH_API kjVec2f kj_vec2f_rcp(kjVec2f a);
KJ_MATH_API float kj_vec2f_dot(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_perp_dot(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_project(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_projectf(kjVec2f a, kjVec2f b);
KJ_MATH_API kjMat2f kj_vec2f_outer(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_cross(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_length_sq(kjVec2f a);
KJ_MATH_API float kj_vec2f_length(kjVec2f a);
KJ_MATH_API float kj_vec2f_length1(kjVec2f a);
KJ_MATH_API float kj_vec2f_distance_sq(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_distance(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_normalise(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_normalise0(kjVec2f a);
KJ_MATH_API bool kj_vec2f_is_normalised(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_perp(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_inv_perp(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_perpf(kjVec2f a, float b);
KJ_MATH_API kjVec2f kj_vec2f_inv_perpf(kjVec2f a, float b);
KJ_MATH_API kjVec2f kj_vec2f_perp_to(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_reflect(kjVec2f a, kjVec2f n);
KJ_MATH_API kjVec2f kj_vec2f_flatten(kjVec2f a, kjVec2f n);
KJ_MATH_API kjVec2f kj_vec2f_major_axis(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_minor_axis(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_lerpf(kjVec2f a, kjVec2f b, float t);
KJ_MATH_API kjVec2f kj_vec2f_min(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_max(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_hmin(kjVec2f a);
KJ_MATH_API float kj_vec2f_hmax(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_abs(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_clamp(kjVec2f a, kjVec2f min, kjVec2f max);
KJ_MATH_API kjVec2f kj_vec2f_clampf(kjVec2f a, float min, float max);
KJ_MATH_API kjVec2f kj_vec2f_clamp01(kjVec2f a);
KJ_MATH_API kjVec3f kj_vec2f_extend(kjVec2f a, float z);

KJ_MATH_API float kj_vec2f_angle_between(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_rotate(kjVec2f a, float radians);
KJ_MATH_API kjVec2f kj_vec2f_rotate_from_sin_cos(kjVec2f a, float s, float c);

KJ_MATH_API kjVec2f kj_vec2f_from_angle(float radians);
KJ_MATH_API kjVec2f kj_vec2f_cartesian_from_polar(float radius, float radians);
KJ_MATH_API kjVec2f kj_vec2f_polar_from_cartesian(float x, float y);
KJ_MATH_API kjVec2f kj_vec2f_from_sin_cos(float s, float c);
KJ_MATH_API kjVec2f kj_vec2f_identity(void);
KJ_MATH_API float kj_vec2f_angle(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_x_axis(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_y_axis(kjVec2f a);

KJ_MATH_API kjVec3f kj_vec3f(float x, float y, float z);
KJ_MATH_API kjVec3i kj_vec3i(int32_t x, int32_t y, int32_t z);
KJ_MATH_API kjVec3u kj_vec3u(uint32_t x, uint32_t y, uint32_t z);
KJ_MATH_API kjVec3f kj_vec3f_zero(void);
KJ_MATH_API kjVec3i kj_vec3i_zero(void);
KJ_MATH_API kjVec3u kj_vec3u_zero(void);
KJ_MATH_API kjVec3f kj_vec3f_one(void);
KJ_MATH_API kjVec3i kj_vec3i_one(void);
KJ_MATH_API kjVec3u kj_vec3u_one(void);
KJ_MATH_API kjVec3f kj_vec3f_inf(void);
KJ_MATH_API kjVec3f kj_vec3f_all(float a);
KJ_MATH_API kjVec3i kj_vec3i_all(int32_t a);
KJ_MATH_API kjVec3u kj_vec3u_all(uint32_t a);
KJ_MATH_API kjVec3f kj_vec3f_negate(kjVec3f a);
KJ_MATH_API kjVec3f kj_vec3f_add(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_addf(kjVec3f a, float b);
KJ_MATH_API kjVec3f kj_vec3f_sub(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_subf(kjVec3f a, float b);
KJ_MATH_API kjVec3f kj_vec3f_mul(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_mulf(kjVec3f a, float b);
KJ_MATH_API kjVec3f kj_vec3f_div(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_divf(kjVec3f a, float b);
KJ_MATH_API kjVec3f kj_vec3f_rcp(kjVec3f a);
KJ_MATH_API float kj_vec3f_dot(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_project(kjVec3f a, kjVec3f b);
KJ_MATH_API float kj_vec3f_projectf(kjVec3f a, kjVec3f b);
KJ_MATH_API kjMat3f kj_vec3f_outer(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_cross(kjVec3f a, kjVec3f b);
KJ_MATH_API float kj_vec3f_length_sq(kjVec3f a);
KJ_MATH_API float kj_vec3f_length(kjVec3f a);
KJ_MATH_API float kj_vec3f_length1(kjVec3f a);
KJ_MATH_API float kj_vec3f_distance_sq(kjVec3f a, kjVec3f b);
KJ_MATH_API float kj_vec3f_distance(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_normalise(kjVec3f a);
KJ_MATH_API kjVec3f kj_vec3f_normalise0(kjVec3f a);
KJ_MATH_API bool kj_vec3f_is_normalised(kjVec3f a);
KJ_MATH_API kjVec3f kj_vec3f_orthonormalise(kjVec3f normal, kjVec3f ref);
KJ_MATH_API kjVec3f kj_vec3f_lerpf(kjVec3f a, kjVec3f b, float t);
KJ_MATH_API kjVec3f kj_vec3f_min(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_max(kjVec3f a, kjVec3f b);
KJ_MATH_API float kj_vec3f_hmin(kjVec3f a);
KJ_MATH_API float kj_vec3f_hmax(kjVec3f a);
KJ_MATH_API kjVec3f kj_vec3f_abs(kjVec3f a);
KJ_MATH_API kjVec3f kj_vec3f_reflect(kjVec3f a, kjVec3f n);
KJ_MATH_API kjVec3f kj_vec3f_flatten(kjVec3f a, kjVec3f n);
KJ_MATH_API kjVec3f kj_vec3f_clamp(kjVec3f a, kjVec3f b, kjVec3f c);
KJ_MATH_API kjVec3f kj_vec3f_clampf(kjVec3f a, float min, float max);
KJ_MATH_API kjVec3f kj_vec3f_clamp01(kjVec3f a);
KJ_MATH_API kjVec4f kj_vec3f_extend(kjVec3f a, float w);
KJ_MATH_API kjVec2f kj_vec3f_truncate(kjVec3f a);
KJ_MATH_API float kj_vec3f_angle_between(kjVec3f a, kjVec3f b);

KJ_MATH_API kjVec4f kj_vec4f(float x, float y, float z, float w);
KJ_MATH_API kjVec4i kj_vec4i(int32_t x, int32_t y, int32_t z, int32_t w);
KJ_MATH_API kjVec4u kj_vec4u(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
KJ_MATH_API kjVec4f kj_vec4f_zero(void);
KJ_MATH_API kjVec4i kj_vec4i_zero(void);
KJ_MATH_API kjVec4u kj_vec4u_zero(void);
KJ_MATH_API kjVec4f kj_vec4f_one(void);
KJ_MATH_API kjVec4i kj_vec4i_one(void);
KJ_MATH_API kjVec4u kj_vec4u_one(void);
KJ_MATH_API kjVec4f kj_vec4f_inf(void);
KJ_MATH_API kjVec4f kj_vec4f_all(float a);
KJ_MATH_API kjVec4i kj_vec4i_all(int32_t a);
KJ_MATH_API kjVec4u kj_vec4u_all(uint32_t a);
KJ_MATH_API kjVec4f kj_vec4f_negate(kjVec4f a);
KJ_MATH_API kjVec4f kj_vec4f_add(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_addf(kjVec4f a, float b);
KJ_MATH_API kjVec4f kj_vec4f_sub(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_subf(kjVec4f a, float b);
KJ_MATH_API kjVec4f kj_vec4f_mul(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_mulf(kjVec4f a, float b);
KJ_MATH_API kjVec4f kj_vec4f_div(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_divf(kjVec4f a, float b);
KJ_MATH_API kjVec4f kj_vec4f_rcp(kjVec4f a);
KJ_MATH_API float kj_vec4f_dot(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_project(kjVec4f a, kjVec4f b);
KJ_MATH_API float kj_vec4f_projectf(kjVec4f a, kjVec4f b);
KJ_MATH_API kjMat4f kj_vec4f_outer(kjVec4f a, kjVec4f b);
KJ_MATH_API float kj_vec4f_length_sq(kjVec4f a);
KJ_MATH_API float kj_vec4f_length(kjVec4f a);
KJ_MATH_API float kj_vec4f_length1(kjVec4f a);
KJ_MATH_API float kj_vec4f_distance_sq(kjVec4f a, kjVec4f b);
KJ_MATH_API float kj_vec4f_distance(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_normalise(kjVec4f a);
KJ_MATH_API kjVec4f kj_vec4f_normalise0(kjVec4f a);
KJ_MATH_API bool kj_vec4f_is_normalised(kjVec4f a);
KJ_MATH_API kjVec4f kj_vec4f_lerpf(kjVec4f a, kjVec4f b, float t);
KJ_MATH_API kjVec4f kj_vec4f_min(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_max(kjVec4f a, kjVec4f b);
KJ_MATH_API float kj_vec4f_hmin(kjVec4f a);
KJ_MATH_API float kj_vec4f_hmax(kjVec4f a);
KJ_MATH_API kjVec4f kj_vec4f_clamp(kjVec4f a, kjVec4f min, kjVec4f max);
KJ_MATH_API kjVec4f kj_vec4f_clampf(kjVec4f a, float min, float max);
KJ_MATH_API kjVec4f kj_vec4f_clamp01(kjVec4f a);
KJ_MATH_API kjVec3f kj_vec4f_truncate(kjVec4f a);

KJ_MATH_API kjQuatf kj_quatf(float x, float y, float z, float w);
KJ_MATH_API kjQuatf kj_quatf_vec3f(kjVec3f xyz, float w);
KJ_MATH_API kjQuatf kj_quatf_vec4f(kjVec4f xyzw);
KJ_MATH_API kjQuatf kj_quatf_from_euler(float pitch, float yaw, float roll);
KJ_MATH_API kjQuatf kj_quatf_identity(void);
KJ_MATH_API kjQuatf kj_quatf_zero(void);
KJ_MATH_API kjQuatf kj_quatf_one(void);
KJ_MATH_API kjQuatf kj_quatf_conjugate(kjQuatf q);
KJ_MATH_API kjQuatf kj_quatf_add(kjQuatf a, kjQuatf b);
KJ_MATH_API kjQuatf kj_quatf_addf(kjQuatf q, float v);
KJ_MATH_API kjQuatf kj_quatf_sub(kjQuatf a, kjQuatf b);
KJ_MATH_API kjQuatf kj_quatf_subf(kjQuatf q, float v);
KJ_MATH_API kjQuatf kj_quatf_mul(kjQuatf a, kjQuatf b);
KJ_MATH_API kjVec3f kj_quatf_mul_vec3f(kjQuatf q, kjVec3f v);
KJ_MATH_API kjQuatf kj_quatf_mulf(kjQuatf q, float v);
KJ_MATH_API kjQuatf kj_quatf_div(kjQuatf a, kjQuatf b);
KJ_MATH_API kjQuatf kj_quatf_divf(kjQuatf q, float v);
KJ_MATH_API kjQuatf kj_quatf_axis_angle(float radians, float x, float y, float z);
KJ_MATH_API kjQuatf kj_quatf_axis_angle_vec3f(float radians, kjVec3f axis);
KJ_MATH_API kjQuatf kj_quatf_axis_angle_x(float radians);
KJ_MATH_API kjQuatf kj_quatf_axis_angle_y(float radians);
KJ_MATH_API kjQuatf kj_quatf_axis_angle_z(float radians);
KJ_MATH_API kjQuatf kj_quatf_rotate_vec3f(kjVec3f from, kjVec3f to);
KJ_MATH_API kjQuatf kj_quatf_rotate_axis_vec3f(kjVec3f from, kjVec3f to, kjVec3f axis);
KJ_MATH_API kjQuatf kj_quatf_look_at(kjVec3f dir, kjVec3f up);
KJ_MATH_API float kj_quatf_pitch(kjQuatf q);
KJ_MATH_API float kj_quatf_yaw(kjQuatf q);
KJ_MATH_API float kj_quatf_roll(kjQuatf q);
KJ_MATH_API kjVec3f kj_quatf_euler(kjQuatf q);
KJ_MATH_API float kj_quatf_dot(kjQuatf a, kjQuatf b);
KJ_MATH_API kjQuatf kj_quatf_cross(kjQuatf a, kjQuatf b);
KJ_MATH_API float kj_quatf_length_sq(kjQuatf q);
KJ_MATH_API float kj_quatf_length(kjQuatf q);
KJ_MATH_API kjQuatf kj_quatf_normalise(kjQuatf q);
KJ_MATH_API kjQuatf kj_quatf_nlerp(kjQuatf a, kjQuatf b, float t);
KJ_MATH_API kjQuatf kj_quatf_slerp(kjQuatf a, kjQuatf b, float t);
KJ_MATH_API kjQuatf kj_quatf_inverse(kjQuatf q);

KJ_MATH_API kjMat2f kj_mat2f(float c0r0, float c0r1, float c1r0, float c1r1);
KJ_MATH_API kjMat2f kj_mat2f_from_columns(kjVec2f c0, kjVec2f c1);
KJ_MATH_API kjMat2f kj_mat2f_diagonal(float c0r0, float c1r1);
KJ_MATH_API kjMat2f kj_mat2f_identity(void);
KJ_MATH_API kjMat2f kj_mat2f_zero(void);
KJ_MATH_API kjMat2f kj_mat2f_one(void);
KJ_MATH_API kjMat2f kj_mat2f_mul(kjMat2f a, kjMat2f b);
KJ_MATH_API kjVec2f kj_mat2f_mul_vec2f(kjMat2f a, kjVec2f b);
KJ_MATH_API kjMat2f kj_mat2f_transpose(kjMat2f a);
KJ_MATH_API kjMat2f kj_mat2f_rotate(float radians);
KJ_MATH_API float kj_mat2f_determinant(kjMat2f a);
KJ_MATH_API kjMat2f kj_mat2f_inverse(kjMat2f a);

KJ_MATH_API kjMat3f kj_mat3f(
        float c0r0, float c0r1, float c0r2,
        float c1r0, float c1r1, float c1r2,
        float c2r0, float c2r1, float c2r2);
KJ_MATH_API kjMat3f kj_mat3f_from_columns(kjVec3f c0, kjVec3f c1, kjVec3f c2);
KJ_MATH_API kjMat3f kj_mat3f_diagonal(float c0r0, float c1r1, float c2r2);
KJ_MATH_API kjMat3f kj_mat3f_identity(void);
KJ_MATH_API kjMat3f kj_mat3f_zero(void);
KJ_MATH_API kjMat3f kj_mat3f_one(void);
KJ_MATH_API kjMat3f kj_mat3f_mul(kjMat3f a, kjMat3f b);
KJ_MATH_API kjMat3f kj_mat3f_transpose(kjMat3f a);
KJ_MATH_API kjMat3f kj_mat3f_translate(float x, float y);
KJ_MATH_API kjMat3f kj_mat3f_translate_vec2f(kjVec2f xy);
KJ_MATH_API kjMat3f kj_mat3f_rotate_vec3f(float radians, kjVec3f xyz);
KJ_MATH_API kjMat3f kj_mat3f_rotate(float radians, float x, float y, float z);
KJ_MATH_API kjMat3f kj_mat3f_rotate_x(float radians);
KJ_MATH_API kjMat3f kj_mat3f_rotate_y(float radians);
KJ_MATH_API kjMat3f kj_mat3f_rotate_z(float radians);
KJ_MATH_API kjMat3f kj_mat3f_scale(float x, float y);
KJ_MATH_API kjMat3f kj_mat3f_scale_vec2f(kjVec2f xy);
KJ_MATH_API kjMat3f kj_mat3f_shear(float x, float y);
KJ_MATH_API kjMat3f kj_mat3f_shear_vec2f(kjVec2f xy);
KJ_MATH_API float kj_mat3f_determinant(kjMat3f a);
KJ_MATH_API kjMat3f kj_mat3f_inverse(kjMat3f a);
KJ_MATH_API kjMat3f kj_mat3f_from_quatf(kjQuatf q);
KJ_MATH_API kjMat3f kj_mat3f_from_transform(kjVec2f translate, kjQuatf rotate, kjVec2f scale);

KJ_MATH_API kjMat4f kj_mat4f(
        float c0r0, float c0r1, float c0r2, float c0r3,
        float c1r0, float c1r1, float c1r2, float c1r3,
        float c2r0, float c2r1, float c2r2, float c2r3,
        float c3r0, float c3r1, float c3r2, float c3r3);
KJ_MATH_API kjMat4f kj_mat4f_from_columns(kjVec4f c0, kjVec4f c1, kjVec4f c2, kjVec4f c3);
KJ_MATH_API kjMat4f kj_mat4f_diagonal(float c0r0, float c1r1, float c2r2, float c3r3);
KJ_MATH_API kjMat4f kj_mat4f_identity(void);
KJ_MATH_API kjMat4f kj_mat4f_zero(void);
KJ_MATH_API kjMat4f kj_mat4f_one(void);
KJ_MATH_API kjMat4f kj_mat4f_mul(kjMat4f a, kjMat4f b);
KJ_MATH_API kjVec4f kj_mat4f_mul_vec4f(kjMat4f a, kjVec4f b);
KJ_MATH_API kjVec3f kj_mat4f_mul_vec3f(kjMat4f a, kjVec3f b);
KJ_MATH_API kjVec4f kj_mat4f_mul_vec3f_extend(kjMat4f a, kjVec3f b);
KJ_MATH_API kjMat4f kj_mat4f_mulf(kjMat4f a, float b);
KJ_MATH_API kjMat4f kj_mat4f_transpose(kjMat4f a);
KJ_MATH_API kjMat4f kj_mat4f_translate(float x, float y, float z);
KJ_MATH_API kjMat4f kj_mat4f_translate_vec3f(kjVec3f xyz);
KJ_MATH_API kjMat4f kj_mat4f_rotate_x(float radians);
KJ_MATH_API kjMat4f kj_mat4f_rotate_y(float radians);
KJ_MATH_API kjMat4f kj_mat4f_rotate_z(float radians);
KJ_MATH_API kjMat4f kj_mat4f_rotate_vec3f(float radians, kjVec3f xyz);
KJ_MATH_API kjMat4f kj_mat4f_rotate(float radians, float x, float y, float z);
KJ_MATH_API kjMat4f kj_mat4f_scale(float x, float y, float z);
KJ_MATH_API kjMat4f kj_mat4f_scalef(float a);
KJ_MATH_API kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz);
KJ_MATH_API kjMat4f kj_mat4f_ortho(float l, float r, float b, float t, float znear, float zfar);
KJ_MATH_API kjMat4f kj_mat4f_ortho_inf(float l, float r, float b, float t);
KJ_MATH_API kjMat4f kj_mat4f_perspective(float fovy, float aspect, float znear, float zfar);
KJ_MATH_API kjMat4f kj_mat4f_perspective_inf(float fovy, float aspect, float znear);
KJ_MATH_API kjMat4f kj_mat4f_look_at(kjVec3f eye, kjVec3f target, kjVec3f up);
KJ_MATH_API float kj_mat4f_determinant(kjMat4f a);
KJ_MATH_API kjMat4f kj_mat4f_inverse(kjMat4f a);
KJ_MATH_API kjMat4f kj_mat4f_from_quatf(kjQuatf q);
KJ_MATH_API kjMat4f kj_mat4f_from_transform(kjVec3f translate, kjQuatf rotate, kjVec3f scale);

#if defined(__cplusplus)
KJ_MATH_API kjVec2f kj_vec2f(void);
KJ_MATH_API kjVec2f kj_vec2f(float a);
KJ_MATH_API kjVec2f operator+(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f operator+(kjVec2f a, float b);
KJ_MATH_API kjVec2f operator-(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f operator-(kjVec2f a, float b);
KJ_MATH_API kjVec2f operator*(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f operator*(kjVec2f a, float b);
KJ_MATH_API kjVec2f operator/(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f operator/(kjVec2f a, float b);
KJ_MATH_API kjVec3f kj_vec3f(void);
KJ_MATH_API kjVec3f kj_vec3f(float a);
KJ_MATH_API kjVec3f operator+(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f operator+(kjVec3f a, float b);
KJ_MATH_API kjVec3f operator-(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f operator-(kjVec3f a, float b);
KJ_MATH_API kjVec3f operator*(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f operator*(kjVec3f a, float b);
KJ_MATH_API kjVec3f operator/(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f operator/(kjVec3f a, float b);
KJ_MATH_API kjVec4f kj_vec4f(void);
KJ_MATH_API kjVec4f kj_vec4f(float a);
KJ_MATH_API kjVec4f operator+(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f operator+(kjVec4f a, float b);
KJ_MATH_API kjVec4f operator-(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f operator-(kjVec4f a, float b);
KJ_MATH_API kjVec4f operator*(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f operator*(kjVec4f a, float b);
KJ_MATH_API kjVec4f operator/(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f operator/(kjVec4f a, float b);
KJ_MATH_API kjVec3f operator*(kjQuatf q, kjVec3f v);
KJ_MATH_API kjMat3f kj_mat3f(float c0r0, float c1r1, float c2r2);
KJ_MATH_API kjMat3f kj_mat3f(void);
KJ_MATH_API kjMat3f kj_mat3f_rotate(float radians, kjVec3f xyz);
KJ_MATH_API kjMat3f operator*(kjMat3f a, kjMat3f b);
KJ_MATH_API kjMat4f kj_mat4f(float c0r0, float c1r1, float c2r2, float c3r3);
KJ_MATH_API kjMat4f kj_mat4f(void);
KJ_MATH_API kjMat4f kj_mat4f_translate(kjVec3f xyz);
KJ_MATH_API kjMat4f kj_mat4f_rotate(float radians, kjVec3f xyz);
KJ_MATH_API kjMat4f kj_mat4f_scale(float a);
KJ_MATH_API kjMat4f kj_mat4f_scale(kjVec3f xyz);
KJ_MATH_API kjMat4f operator*(kjMat4f a, kjMat4f b);
#endif

KJ_MATH_API kjVec2f kj_aabb2d_half_extents(kjVec2f min, kjVec2f max);
KJ_MATH_API kjVec2f kj_aabb2d_midpoint(kjVec2f min, kjVec2f max);
KJ_MATH_API kjVec2f kj_aabb2d_top_left(kjVec2f min, kjVec2f max);
KJ_MATH_API kjVec2f kj_aabb2d_top_right(kjVec2f min, kjVec2f max);
KJ_MATH_API kjVec2f kj_aabb2d_bottom_left(kjVec2f min, kjVec2f max);
KJ_MATH_API kjVec2f kj_aabb2d_bottom_right(kjVec2f min, kjVec2f max);

KJ_MATH_API bool kj_triangle2d_contains_point(kjVec2f p, kjVec2f a, kjVec2f b, kjVec2f c);

KJ_MATH_API float kj_segment2d_point_side(kjVec2f a, kjVec2f b, kjVec2f p);
KJ_MATH_API kjVec2f kj_segment2d_midpoint(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_segment2d_nearest_point(kjVec2f a, kjVec2f b, kjVec2f p);
KJ_MATH_API float kj_segment2d_distance_sq_to_point(kjVec2f a, kjVec2f b, kjVec2f p);
KJ_MATH_API float kj_segment2d_distance_to_point(kjVec2f a, kjVec2f b, kjVec2f p);
KJ_MATH_API void kj_segment2d_nearest_segment(kjVec2f* a, kjVec2f* b, kjVec2f a0, kjVec2f b0, kjVec2f a1, kjVec2f b1);

KJ_MATH_API kjVec2f kj_arc2d_nearest_point(kjVec2f centre, float radius, float radians, kjVec2f p);
KJ_MATH_API float kj_arc2d_distance_sq_to_point(kjVec2f centre, float radius, float radians, kjVec2f p);
KJ_MATH_API float kj_arc2d_distance_to_point(kjVec2f centre, float radius, float radians, kjVec2f p);

KJ_MATH_API kjVec2f kj_circle_nearest_point(kjVec2f centre, float radius, kjVec2f p);
KJ_MATH_API float kj_circle_distance_sq_to_point(kjVec2f centre, float radius, kjVec2f p);
KJ_MATH_API float kj_circle_distance_to_point(kjVec2f centre, float radius, kjVec2f p);

KJ_MATH_API kjVec2f kj_aabb2d_nearest_point(kjVec2f min, kjVec2f max, kjVec2f p);
KJ_MATH_API float kj_aabb2d_distance_sq_to_point(kjVec2f min, kjVec2f max, kjVec2f p);
KJ_MATH_API float kj_aabb2d_distance_to_point(kjVec2f min, kjVec2f max, kjVec2f p);

KJ_MATH_API kjVec2f kj_capsule2d_nearest_point(kjVec2f a, kjVec2f b, float r, kjVec2f p);
KJ_MATH_API float kj_capsule2d_distance_sq_to_point(kjVec2f a, kjVec2f b, float r, kjVec2f p);
KJ_MATH_API float kj_capsule2d_distance_to_point(kjVec2f a, kjVec2f b, float r, kjVec2f p);

KJ_MATH_API bool kj_intersect2d_segment_segment(kjVec2f a0, kjVec2f a1, kjVec2f b0, kjVec2f b1);
KJ_MATH_API bool kj_intersect2d_aabb_point(kjVec2f min, kjVec2f max, kjVec2f p);
KJ_MATH_API bool kj_intersect2d_point_aabb(kjVec2f p, kjVec2f min, kjVec2f max);
KJ_MATH_API bool kj_intersect2d_circle_point(kjVec2f centre, float radius, kjVec2f p);
KJ_MATH_API bool kj_intersect2d_point_circle(kjVec2f p, kjVec2f centre, float radius);
KJ_MATH_API bool kj_intersect2d_aabb_aabb(kjVec2f min_a, kjVec2f max_a, kjVec2f b_min, kjVec2f b_max);
KJ_MATH_API bool kj_intersect2d_aabb_circle(kjVec2f min_a, kjVec2f max_a, kjVec2f centre, float radius);
KJ_MATH_API bool kj_intersect2d_circle_aabb(kjVec2f centre, float radius, kjVec2f b_min, kjVec2f b_max);
KJ_MATH_API bool kj_intersect2d_circle_circle(kjVec2f c0, float r0, kjVec2f c1, float r1);

KJ_MATH_API bool kj_intersect2d_capsule_capsule(kjVec2f a0, kjVec2f b0, float r0, kjVec2f a1, kjVec2f b1, float r1);
KJ_MATH_API bool kj_intersect2d_capsule_circle(kjVec2f a, kjVec2f b, float r, kjVec2f centre, float radius);
KJ_MATH_API bool kj_intersect2d_circle_capsule(kjVec2f centre, float radius, kjVec2f a, kjVec2f b, float r);
KJ_MATH_API bool kj_intersect2d_capsule_aabb(kjVec2f a, kjVec2f b, float r, kjVec2f min, kjVec2f max);
KJ_MATH_API bool kj_intersect2d_aabb_capsule(kjVec2f min, kjVec2f max, kjVec2f a, kjVec2f b, float r);

#define KJ_CONTACT2D_COUNT (1)

typedef struct kjContact2d {
    float depths[KJ_CONTACT2D_COUNT];
    kjVec2f contacts[KJ_CONTACT2D_COUNT];
    kjVec2f normal;
} kjContact2d;

KJ_MATH_API uint32_t kj_contact2d_segment_segment(kjVec2f* contact, kjVec2f a0, kjVec2f a1, kjVec2f b0, kjVec2f b1);
KJ_MATH_API uint32_t kj_contact2d_circle_circle(kjContact2d* contact, kjVec2f c0, float r0, kjVec2f c1, float r1);
KJ_MATH_API uint32_t kj_contact2d_circle_aabb(kjContact2d* contact, kjVec2f centre, float radius, kjVec2f min, kjVec2f max);
KJ_MATH_API uint32_t kj_contact2d_aabb_circle(kjContact2d* contact, kjVec2f min, kjVec2f max, kjVec2f centre, float radius);
KJ_MATH_API uint32_t kj_contact2d_aabb_aabb(kjContact2d* contact, kjVec2f min_a, kjVec2f max_a, kjVec2f min_b, kjVec2f max_b);

KJ_MATH_API uint32_t kj_contact2d_capsule_capsule(kjContact2d* contact, kjVec2f a0, kjVec2f b0, float r0, kjVec2f a1, kjVec2f b1, float r1);
KJ_MATH_API uint32_t kj_contact2d_capsule_circle(kjContact2d* contact, kjVec2f a, kjVec2f b, float r, kjVec2f centre, float radius);
KJ_MATH_API uint32_t kj_contact2d_circle_capsule(kjContact2d* contact, kjVec2f centre, float radius, kjVec2f a, kjVec2f b, float r);
KJ_MATH_API uint32_t kj_contact2d_capsule_aabb(kjContact2d* contact, kjVec2f a, kjVec2f b, float r, kjVec2f min, kjVec2f max);
KJ_MATH_API uint32_t kj_contact2d_aabb_capsule(kjContact2d* contact, kjVec2f min, kjVec2f max, kjVec2f a, kjVec2f b, float r);

typedef struct kjRay2d {
    kjVec2f pos;
    kjVec2f dir;
    float t;
} kjRay2d;

typedef struct kjRaycast2d {
    kjVec2f pos;
    kjVec2f normal;
    float t;
} kjRaycast2d;

KJ_MATH_API bool kj_raycast2d_ray_aabb(kjRaycast2d* raycast, kjRay2d ray, kjVec2f min, kjVec2f max);
KJ_MATH_API bool kj_raycast2d_ray_circle(kjRaycast2d* raycast, kjRay2d ray, kjVec2f centre, float radius);

KJ_MATH_API bool kj_raycast2d_aabb(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f min, kjVec2f max);
KJ_MATH_API bool kj_raycast2d_circle(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f centre, float radius);

KJ_MATH_API void kj_bounds2d_aabb_circle(kjVec2f* min, kjVec2f* max, kjVec2f centre, float radius);
KJ_MATH_API void kj_bounds2d_circle_aabb(kjVec2f* centre, float* radius, kjVec2f min, kjVec2f max);
KJ_MATH_API void kj_bounds2d_aabb_points(kjVec2f* min, kjVec2f* max, kjVec2f* points, uint32_t count);
KJ_MATH_API void kj_bounds2d_circle_with_centre_points(kjVec2f* centre, float* radius, kjVec2f* points, uint32_t count, kjVec2f c);
KJ_MATH_API void kj_bounds2d_circle_points(kjVec2f* centre, float* radius, kjVec2f* points, uint32_t count);
KJ_MATH_API uint32_t kj_bounds2d_polygon_points(uint32_t* hull, kjVec2f* points, uint32_t count);

KJ_MATH_API bool kj_intersect_aabb_point(kjVec3f min, kjVec3f max, kjVec3f p);
KJ_MATH_API bool kj_intersect_point_aabb(kjVec3f p, kjVec3f min, kjVec3f max);
KJ_MATH_API bool kj_intersect_sphere_point(kjVec3f centre, float radius, kjVec3f p);
KJ_MATH_API bool kj_intersect_point_sphere(kjVec3f p, kjVec3f centre, float radius);

KJ_MATH_API kjVec3f kj_sphere_nearest_point(kjVec3f centre, float radius, kjVec3f p);
KJ_MATH_API float kj_sphere_distance_sq_to_point(kjVec3f centre, float radius, kjVec3f p);
KJ_MATH_API float kj_sphere_distance_to_point(kjVec3f centre, float radius, kjVec3f p);

KJ_MATH_API bool kj_intersect_aabb_aabb(kjVec3f a_min, kjVec3f a_max, kjVec3f b_min, kjVec3f b_max);
KJ_MATH_API bool kj_intersect_aabb_sphere(kjVec3f min, kjVec3f max, kjVec3f centre, float radius);
KJ_MATH_API bool kj_intersect_sphere_aabb(kjVec3f centre, float radius, kjVec3f min, kjVec3f max);
KJ_MATH_API bool kj_intersect_sphere_sphere(kjVec3f c0, float r0, kjVec3f c1, float r1);

typedef struct kjRay {
    kjVec3f pos;
    kjVec3f dir;
    float t;
} kjRay;

typedef struct kjRaycast {
    kjVec3f pos;
    kjVec3f normal;
    float t;
} kjRaycast;

KJ_MATH_API bool kj_raycast_ray_aabb(kjRaycast* raycast, kjRay ray, kjVec3f min, kjVec3f max);
KJ_MATH_API bool kj_raycast_ray_sphere(kjRaycast* raycast, kjRay ray, kjVec3f centre, float radius);

KJ_MATH_API bool kj_raycast_aabb(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f min, kjVec3f max);
KJ_MATH_API bool kj_raycast_sphere(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f centre, float radius);

KJ_MATH_API void kj_rgba_unpack(uint8_t unpacked[4], uint32_t packed);
KJ_MATH_API uint32_t kj_rgba_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
KJ_MATH_API uint32_t kj_rgbav_pack(uint8_t rgba[4]);
KJ_MATH_API void kj_rgbaf_unpack(float unpacked[4], uint32_t packed);
KJ_MATH_API uint32_t kj_rgbaf_pack(float r, float g, float b, float a);
KJ_MATH_API uint32_t kj_rgbafv_pack(float rgba[4]);

KJ_MATH_API void kj_hsv_from_rgb(float hsv[3], float rgb[3]);
KJ_MATH_API void kj_rgb_from_hsv(float rgb[3], float hsv[3]);
KJ_MATH_API void kj_hsva_from_rgba(float hsv[4], float rgb[4]);
KJ_MATH_API void kj_rgba_from_hsva(float rgb[4], float hsv[4]);

typedef struct kjRandomSeries {
    uint64_t state[2];
} kjRandomSeries;

KJ_MATH_API kjRandomSeries kj_random_series(uint64_t seed);

KJ_MATH_API int32_t kj_randomi(kjRandomSeries* series);
KJ_MATH_API int32_t kj_random_rangei(kjRandomSeries* series, int32_t min, int32_t max);
KJ_MATH_API uint32_t kj_randomu(kjRandomSeries* series);
KJ_MATH_API uint32_t kj_random_rangeu(kjRandomSeries* series, uint32_t min, uint32_t max);

KJ_MATH_API float kj_randomf(kjRandomSeries* series);
KJ_MATH_API float kj_random_rangef(kjRandomSeries* series, float min, float max);
KJ_MATH_API float kj_random01f(kjRandomSeries* series);
KJ_MATH_API float kj_random11f(kjRandomSeries* series);

KJ_MATH_API kjVec2f kj_random_vec2f(kjRandomSeries* series);
KJ_MATH_API kjVec3f kj_random_vec3f(kjRandomSeries* series);
KJ_MATH_API kjVec4f kj_random_vec4f(kjRandomSeries* series);
KJ_MATH_API kjVec2f kj_random_unit_vec2f(kjRandomSeries* series);
KJ_MATH_API kjVec3f kj_random_unit_vec3f(kjRandomSeries* series);
KJ_MATH_API kjVec4f kj_random_unit_vec4f(kjRandomSeries* series);

KJ_MATH_API kjVec2f kj_random_in_unit_circle(kjRandomSeries* series);
KJ_MATH_API kjVec2f kj_random_in_rect(kjRandomSeries* series, kjVec2f min, kjVec2f max);

KJ_MATH_API void kj_random_rgba(kjRandomSeries* series, uint8_t rgba[4]);
KJ_MATH_API void kj_random_rgbaf(kjRandomSeries* series, float rgba[4]);

KJ_MATH_API float kj_random_radians(kjRandomSeries* series);
KJ_MATH_API float kj_random_degrees(kjRandomSeries* series);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_MATH_IMPL)

#if defined(KJ_MATH_SIMD)
/* SSE2, SSE3, SSE4.1? */
#include <xmmintrin.h>
#endif

#if defined(KJ_COMPILER_MSVC)
#include <math.h>
#endif

#if !defined(KJ_ASSERT)
#include <assert.h>
#define KJ_ASSERT assert
#endif

KJ_FORCE_INLINE float kj_float32_inf() {
    kjBinary32 res;
    res.i = KJ_FLOAT32_EXPONENT_MASK;
    return res.f;
}

KJ_FORCE_INLINE float kj_float32_negative_inf() {
    kjBinary32 res;
    res.i = KJ_FLOAT32_SIGN_MASK | KJ_FLOAT32_EXPONENT_MASK;
    return res.f;
}

KJ_FORCE_INLINE float kj_float32_nan() {
    kjBinary32 res;
    res.i = KJ_FLOAT32_EXPONENT_MASK | KJ_FLOAT32_MANTISSA_MASK;
    return res.f;
}

KJ_FORCE_INLINE bool kj_float32_is_finite(float f) {
    kjBinary32 b;
    b.f = f;
    uint32_t exp = b.i & KJ_FLOAT32_EXPONENT_MASK;
    return exp | KJ_FLOAT32_EXPONENT_MASK;
}

KJ_FORCE_INLINE bool kj_float32_is_infinity(float f) {
    kjBinary32 b;
    b.f = f;
    uint32_t exp = b.i & KJ_FLOAT32_EXPONENT_MASK;
    uint32_t man = b.i & KJ_FLOAT32_MANTISSA_MASK;
    return exp == KJ_FLOAT32_EXPONENT_MASK && man == 0;
}

KJ_FORCE_INLINE bool kj_float32_is_positive(float f) {
    kjBinary32 b;
    b.f = f;
    return (b.i & KJ_FLOAT32_SIGN_MASK) == 0;
}

KJ_FORCE_INLINE bool kj_float32_is_negative(float f) {
    kjBinary32 b;
    b.f = f;
    return (b.i & KJ_FLOAT32_SIGN_MASK) != 0;
}

KJ_FORCE_INLINE bool kj_float32_signbit(float a) {
    kjBinary32 b;
    b.f = a;
    return b.i >> 0x1F;
}

KJ_FORCE_INLINE float kj_float32_set_sign(float f, bool negative) {
    kjBinary32 b;
    b.f = f;
    b.i &= ~KJ_FLOAT32_SIGN_MASK;
    b.i |= negative ? KJ_FLOAT32_SIGN_MASK: 0;
    return b.f;
}

KJ_FORCE_INLINE float kj_float32_fma(float a, float b, float c) {
#if defined(KJ_COMPILER_MSVC)
    return fmaf(a, b, c);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_fmaf(a, b, c);
#endif
}

KJ_FORCE_INLINE bool kj_float32_eq(float a, float b, float epsilon) {
    return kj_absf(a - b) <= epsilon;
}

KJ_FORCE_INLINE float kj_signf(float a) {
    return (a > 0.0f) - (a < 0.0f);
}

KJ_FORCE_INLINE float kj_rsqrtf(float a) {
    return 1.0f / kj_sqrtf(a);
}

KJ_FORCE_INLINE float kj_sqrtf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return sqrtf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_sqrtf(a);
#endif
}

KJ_FORCE_INLINE float kj_cbrtf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return cbrtf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_cbrtf(a);
#endif
}

KJ_FORCE_INLINE float kj_sinf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return sinf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_sinf(a);
#endif
}

KJ_FORCE_INLINE float kj_cosf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return cosf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_cosf(a);
#endif
}

KJ_FORCE_INLINE float kj_tanf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return tanf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_tanf(a);
#endif
}

KJ_FORCE_INLINE float kj_asinf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return asinf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_asinf(a);
#endif
}

KJ_FORCE_INLINE float kj_acosf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return acosf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_acosf(a);
#endif
}

KJ_FORCE_INLINE float kj_atanf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return atanf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_atanf(a);
#endif
}

KJ_FORCE_INLINE float kj_atan2f(float y, float x) {
#if defined(KJ_COMPILER_MSVC)
    return atan2f(y, x);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_atan2f(y, x);
#endif
}

KJ_FORCE_INLINE float kj_expf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return expf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_expf(a);
#endif
}

KJ_FORCE_INLINE float kj_exp2f(float a) {
#if defined(KJ_COMPILER_MSVC)
    return exp2f(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_exp2f(a);
#endif
}

KJ_FORCE_INLINE float kj_lnf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return logf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_logf(a);
#endif
}

KJ_FORCE_INLINE float kj_log10f(float a) {
#if defined(KJ_COMPILER_MSVC)
    return log10f(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_log10f(a);
#endif
}

KJ_FORCE_INLINE float kj_log2f(float a) {
#if defined(KJ_COMPILER_MSVC)
    return log2f(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_log2f(a);
#endif
}

KJ_FORCE_INLINE float kj_powf(float a, float b) {
#if defined(KJ_COMPILER_MSVC)
    return powf(a, b);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_powf(a, b);
#endif
}

KJ_FORCE_INLINE float kj_floorf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return floorf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_floorf(a);
#endif
}

KJ_FORCE_INLINE float kj_ceilf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return ceilf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_ceilf(a);
#endif
}

KJ_FORCE_INLINE float kj_roundf(float a) {
#if defined(KJ_COMPILER_MSVC)
    return roundf(a);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_roundf(a);
#endif
}

KJ_FORCE_INLINE float kj_absf(float a) {
    kjBinary32 b = { a };
    b.i &= ~KJ_FLOAT32_SIGN_MASK;
    return b.f;
}

KJ_FORCE_INLINE float kj_minf(float a, float b) {
#if defined(KJ_COMPILER_MSVC)
    return fminf(a, b);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_fminf(a, b);
#endif
}

KJ_FORCE_INLINE float kj_maxf(float a, float b) {
#if defined(KJ_COMPILER_MSVC)
    return fmaxf(a, b);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_fmaxf(a, b);
#endif
}

KJ_FORCE_INLINE float kj_modf(float a, float b) {
#if defined(KJ_COMPILER_MSVC)
    return fmodf(a, b);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_fmodf(a, b);
#endif
}

KJ_FORCE_INLINE float kj_fractf(float a) {
    return a - kj_floorf(a);
}

KJ_FORCE_INLINE float kj_radian_wrapf(float a) {
    a = kj_modf(a, KJ_TAU);
    return a < 0.0f ? a + KJ_TAU: a;
}

KJ_FORCE_INLINE float kj_degree_wrapf(float a) {
    a = kj_modf(a, 360.0f);
    return a < 0.0f ? a + 360.0f: a;
}

KJ_FORCE_INLINE float kj_wrapf(float a, float min, float max) {
    KJ_ASSERT(min < max);
    return kj_modf(a, min < 0.0f ? max - min: max) + min;
}

KJ_FORCE_INLINE float kj_radian_normalisef(float radians) {
    radians = kj_radian_wrapf(radians);
    return radians > KJ_PI ? radians - KJ_TAU: radians;
}

KJ_FORCE_INLINE float kj_degree_normalisef(float degrees) {
    degrees = kj_degree_wrapf(degrees);
    return degrees > 180.0f ? degrees - 360.0f: degrees;
}

KJ_FORCE_INLINE float kj_radian_clampf(float radians, float min, float max) {
    max = kj_radian_wrapf(max - min) * 0.5f;
    float midpoint = kj_radian_wrapf(min + max);
    float a = kj_radian_normalisef(radians - midpoint);
    return kj_absf(a) > max ?
        kj_radian_normalisef(midpoint + max * kj_signf(a)):
        kj_radian_normalisef(radians);
}

KJ_FORCE_INLINE float kj_degree_clampf(float degrees, float min, float max) {
    max = kj_degree_wrapf(max - min) * 0.5f;
    float midpoint = kj_degree_wrapf(min + max);
    float a = kj_degree_normalisef(degrees - midpoint);
    return kj_absf(a) > max ?
        kj_degree_normalisef(midpoint + max * kj_signf(a)):
        kj_degree_normalisef(degrees);
}

KJ_FORCE_INLINE float kj_clampf(float a, float min, float max) {
    return kj_minf(kj_maxf(a, min), max);
}

KJ_FORCE_INLINE float kj_clamp01f(float a) {
    return kj_maxf(0.0f, kj_minf(a, 1.0f));
}

KJ_FORCE_INLINE float kj_lerpf(float min, float max, float t) {
    return (t * (max - min)) + min;
}

KJ_FORCE_INLINE float kj_inv_lerpf(float min, float max, float t) {
    return (t - min) * (1.0f / (max - min));
}

KJ_FORCE_INLINE float kj_radian_lerpf(float min, float max, float t) {
    float delta = kj_radian_normalisef(max - min);
    return min + delta * t;
}

KJ_FORCE_INLINE float kj_degree_lerpf(float min, float max, float t) {
    float delta = kj_degree_normalisef(max - min);
    return min + delta * t;
}

KJ_FORCE_INLINE float kj_stepf(float step, float t) {
    return t < step ? 0.0f: 1.0f;
}

KJ_FORCE_INLINE float kj_smoothstepf(float min, float max, float t) {
    float range = max - min;
    KJ_ASSERT(range != 0.0f);
    t = (t - min) * (1.0f / range);
    return (t * t) * (3.0f - 2.0f * t);
}

KJ_FORCE_INLINE float kj_smoothstep01f(float t) {
    return (t * t) * (3.0f - 2.0f * t);
}

KJ_FORCE_INLINE float kj_quadratic_start01f(float t) {
    return t * t;
}

KJ_FORCE_INLINE float kj_cubic_start01f(float t) {
    return t * t * t;
}

KJ_FORCE_INLINE float kj_quartic_start01f(float t) {
    return t * t * t * t;
}

KJ_FORCE_INLINE float kj_quintic_start01f(float t) {
    return t * t * t * t * t;
}

KJ_FORCE_INLINE float kj_quadratic_stop01f(float t) {
    return t * (2.0f - t);
}

KJ_FORCE_INLINE float kj_cubic_stop01f(float t) {
    t -= 1.0f;
    return 1.0f + (t * t * t);
}

KJ_FORCE_INLINE float kj_quartic_stop01f(float t) {
    t -= 1.0f;
    return 1.0f - (t * t * t * t);
}

KJ_FORCE_INLINE float kj_quintic_stop01f(float t) {
    t -= 1.0f;
    return 1.0f + (t * t * t * t * t);
}

KJ_FORCE_INLINE kjVec2f kj_quadratic_bezier_vec2f(kjVec2f cp[3], float t) {
    float it = 1.0f - t;
    float it2 = it * it;
    float t2 = t * t;
    kjVec2f a = kj_vec2f_mulf(cp[0], it2);
    kjVec2f b = kj_vec2f_mulf(cp[1], 2.0f * it * t);
    kjVec2f c = kj_vec2f_mulf(cp[2], t2);
    return kj_vec2f_add(a, kj_vec2f_add(b, c));
}

KJ_FORCE_INLINE kjVec2f kj_cubic_bezier_vec2f(kjVec2f cp[4], float t) {
    float it = 1.0f - t;
    float it3 = it * it * it;
    float it2 = it * it;
    float t2 = t * t;
    float t3 = t * t * t;
    kjVec2f a = kj_vec2f_mulf(cp[0], it3);
    kjVec2f b = kj_vec2f_mulf(cp[1], 3.0f * it2 * t);
    kjVec2f c = kj_vec2f_mulf(cp[2], 3.0f * it * t2);
    kjVec2f d = kj_vec2f_mulf(cp[3], t3);
    return kj_vec2f_add(kj_vec2f_add(a, b), kj_vec2f_add(c, d));
}

KJ_FORCE_INLINE kjVec3f kj_quadratic_bezier_vec3f(kjVec3f cp[3], float t) {
    float it = 1.0f - t;
    float it2 = it * it;
    float t2 = t * t;
    kjVec3f a = kj_vec3f_mulf(cp[0], it2);
    kjVec3f b = kj_vec3f_mulf(cp[1], 2.0f * it * t);
    kjVec3f c = kj_vec3f_mulf(cp[2], t2);
    return kj_vec3f_add(a, kj_vec3f_add(b, c));
}

KJ_FORCE_INLINE kjVec3f kj_cubic_bezier_vec3f(kjVec3f cp[4], float t) {
    float it = 1.0f - t;
    float it3 = it * it * it;
    float it2 = it * it;
    float t2 = t * t;
    float t3 = t * t * t;
    kjVec3f a = kj_vec3f_mulf(cp[0], it3);
    kjVec3f b = kj_vec3f_mulf(cp[1], 3.0f * it2 * t);
    kjVec3f c = kj_vec3f_mulf(cp[2], 3.0f * it * t2);
    kjVec3f d = kj_vec3f_mulf(cp[3], t3);
    return kj_vec3f_add(kj_vec3f_add(a, b), kj_vec3f_add(c, d));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f(float x, float y) {
    kjVec2f res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_FORCE_INLINE kjVec2i kj_vec2i(int32_t x, int32_t y) {
    kjVec2i res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_FORCE_INLINE kjVec2u kj_vec2u(uint32_t x, uint32_t y) {
    kjVec2u res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_zero(void) {
    return kj_vec2f(0.0f, 0.0f);
}

KJ_FORCE_INLINE kjVec2i kj_vec2i_zero(void) {
    return kj_vec2i(0, 0);
}

KJ_FORCE_INLINE kjVec2u kj_vec2u_zero(void) {
    return kj_vec2u(0, 0);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_one(void) {
    return kj_vec2f(1.0f, 1.0f);
}

KJ_FORCE_INLINE kjVec2i kj_vec2i_one(void) {
    return kj_vec2i(1, 1);
}

KJ_FORCE_INLINE kjVec2u kj_vec2u_one(void) {
    return kj_vec2u(1, 1);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_inf(void) {
    return kj_vec2f(KJ_FLOAT32_INF, KJ_FLOAT32_INF);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_all(float a) {
    return kj_vec2f(a, a);
}

KJ_FORCE_INLINE kjVec2i kj_vec2i_all(int32_t a) {
    return kj_vec2i(a, a);
}

KJ_FORCE_INLINE kjVec2u kj_vec2u_all(uint32_t a) {
    return kj_vec2u(a, a);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_negate(kjVec2f a) {
    return kj_vec2f(-a.x, -a.y);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_add(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x + b.x, a.y + b.y);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_addf(kjVec2f a, float b) {
    return kj_vec2f(a.x + b, a.y + b);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_sub(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x - b.x, a.y - b.y);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_subf(kjVec2f a, float b) {
    return kj_vec2f(a.x - b, a.y - b);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_mul(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x * b.x, a.y * b.y);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_mulf(kjVec2f a, float b) {
    return kj_vec2f(a.x * b, a.y * b);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_div(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x * (1.0f / b.x), a.y * (1.0f / b.y));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_divf(kjVec2f a, float b) {
    b = 1.0f / b;
    return kj_vec2f(a.x * b, a.y * b);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_rcp(kjVec2f a) {
    return kj_vec2f(1.0f / a.x, 1.0f / a.y);
}

KJ_FORCE_INLINE float kj_vec2f_dot(kjVec2f a, kjVec2f b) {
    return (a.x * b.x) + (a.y * b.y);
}

KJ_FORCE_INLINE float kj_vec2f_perp_dot(kjVec2f a, kjVec2f b) {
    return (-a.y * b.x) + (a.x * b.y);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_project(kjVec2f a, kjVec2f b) {
    return kj_vec2f_mulf(b, kj_vec2f_projectf(a, b));
}

KJ_FORCE_INLINE float kj_vec2f_projectf(kjVec2f a, kjVec2f b) {
    float length = kj_vec2f_length_sq(b);
    return kj_vec2f_dot(a, b) / length;
}

KJ_FORCE_INLINE kjMat2f kj_vec2f_outer(kjVec2f a, kjVec2f b) {
    return kj_mat2f(a.x * b.x, a.y * b.x, a.x * b.y, a.y * b.y);
}

KJ_FORCE_INLINE float kj_vec2f_cross(kjVec2f a, kjVec2f b) {
    return (a.x * b.y) - (b.x * a.y);
}

KJ_FORCE_INLINE float kj_vec2f_length_sq(kjVec2f a) {
    return kj_vec2f_dot(a, a);
}

KJ_FORCE_INLINE float kj_vec2f_length(kjVec2f a) {
    return kj_sqrtf(kj_vec2f_length_sq(a));
}

KJ_FORCE_INLINE float kj_vec2f_length1(kjVec2f a) {
    float length = kj_vec2f_length(a);
    return length != 0.0f ? length: 1.0f;
}

KJ_FORCE_INLINE float kj_vec2f_distance_sq(kjVec2f a, kjVec2f b) {
    return kj_vec2f_length_sq(kj_vec2f_sub(a, b));
}

KJ_FORCE_INLINE float kj_vec2f_distance(kjVec2f a, kjVec2f b) {
    return kj_sqrtf(kj_vec2f_distance_sq(a, b));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_normalise(kjVec2f a) {
    float length = kj_vec2f_length(a);
    return kj_vec2f_mulf(a, 1.0f / length);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_normalise0(kjVec2f a) {
    float length = kj_vec2f_length(a);
    return length != 0.0f ? kj_vec2f_mulf(a, 1.0f / length): kj_vec2f_zero();
}

KJ_FORCE_INLINE bool kj_vec2f_is_normalised(kjVec2f a) {
    return kj_float32_eq(kj_vec2f_length_sq(a) - 1.0f, 0.0f, 0.1f);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_perp(kjVec2f a) {
    return kj_vec2f(-a.y, a.x);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_inv_perp(kjVec2f a) {
    return kj_vec2f(a.y, -a.x);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_perpf(kjVec2f a, float b) {
    return kj_vec2f(-a.y * b, a.x * b);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_inv_perpf(kjVec2f a, float b) {
    return kj_vec2f(a.y * b, -a.x * b);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_perp_to(kjVec2f a, kjVec2f n) {
    KJ_ASSERT(kj_vec2f_is_normalised(n));
    return kj_vec2f_mulf(n, -kj_vec2f_perp_dot(a, n));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_reflect(kjVec2f a, kjVec2f n) {
    KJ_ASSERT(kj_vec2f_is_normalised(n));
    return kj_vec2f_sub(a, kj_vec2f_mulf(n, 2.0f * kj_vec2f_dot(a, n)));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_flatten(kjVec2f a, kjVec2f n) {
    KJ_ASSERT(kj_vec2f_is_normalised(n));
    return kj_vec2f_sub(a, kj_vec2f_mulf(n, kj_vec2f_dot(a, n)));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_major_axis(kjVec2f a) {
    return kj_absf(a.x) > kj_absf(a.y) ? kj_vec2f(kj_signf(a.x), 0.0f): kj_vec2f(0.0f, kj_signf(a.y));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_minor_axis(kjVec2f a) {
    return kj_absf(a.x) < kj_absf(a.y) ? kj_vec2f(kj_signf(a.x), 0.0f): kj_vec2f(0.0f, kj_signf(a.y));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_lerpf(kjVec2f a, kjVec2f b, float t) {
    return kj_vec2f(kj_lerpf(a.x, b.x, t), kj_lerpf(a.y, b.y, t));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_min(kjVec2f a, kjVec2f b) {
    return kj_vec2f(kj_minf(a.x, b.x), kj_minf(a.y, b.y));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_max(kjVec2f a, kjVec2f b) {
    return kj_vec2f(kj_maxf(a.x, b.x), kj_maxf(a.y, b.y));
}

KJ_FORCE_INLINE float kj_vec2f_hmin(kjVec2f a) {
    return kj_minf(a.x, a.y);
}

KJ_FORCE_INLINE float kj_vec2f_hmax(kjVec2f a) {
    return kj_maxf(a.x, a.y);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_abs(kjVec2f a) {
    return kj_vec2f(kj_absf(a.x), kj_absf(a.y));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_clamp(kjVec2f a, kjVec2f min, kjVec2f max) {
    return kj_vec2f(kj_clampf(a.x, min.x, max.x), kj_clampf(a.y, min.y, max.y));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_clampf(kjVec2f a, float min, float max) {
    return kj_vec2f_clamp(a, kj_vec2f_all(min), kj_vec2f_all(max));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_clamp01(kjVec2f a) {
    return kj_vec2f_clamp(a, kj_vec2f_zero(), kj_vec2f_one());
}

KJ_FORCE_INLINE kjVec3f kj_vec2f_extend(kjVec2f a, float z) {
    return kj_vec3f(a.x, a.y, z);
}

KJ_FORCE_INLINE float kj_vec2f_angle_between(kjVec2f a, kjVec2f b) {
    return kj_atan2f(kj_vec2f_cross(a, b), kj_vec2f_dot(a, b));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_rotate(kjVec2f a, float radians) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    return kj_vec2f(a.x * c - a.y * s, a.x * s + a.y * c);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_rotate_from_sin_cos(kjVec2f a, float s, float c) {
    return kj_vec2f(a.x * c - a.y * s, a.x * s + a.y * c);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_from_angle(float radians) {
    return kj_vec2f(kj_cosf(radians), kj_sinf(radians));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_cartesian_from_polar(float radius, float radians) {
    return kj_vec2f(radius * kj_cosf(radians), radius * kj_sinf(radians));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_polar_from_cartesian(float x, float y) {
    return kj_vec2f(kj_sqrtf(x * x + y * y), kj_atan2f(y, x));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_from_sin_cos(float s, float c) {
    return kj_vec2f(c, s);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_identity(void) {
    return kj_vec2f(0.0f, 1.0f);
}

KJ_FORCE_INLINE float kj_vec2f_angle(kjVec2f a) {
    return kj_atan2f(a.y, a.x);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_x_axis(kjVec2f a) {
    return kj_vec2f(a.y, a.x);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_y_axis(kjVec2f a) {
    return kj_vec2f(-a.x, a.y);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f(float x, float y, float z) {
    kjVec3f res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_FORCE_INLINE kjVec3i kj_vec3i(int32_t x, int32_t y, int32_t z) {
    kjVec3i res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_FORCE_INLINE kjVec3u kj_vec3u(uint32_t x, uint32_t y, uint32_t z) {
    kjVec3u res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_zero(void) {
    return kj_vec3f(0.0f, 0.0f, 0.0f);
}

KJ_FORCE_INLINE kjVec3i kj_vec3i_zero(void) {
    return kj_vec3i(0, 0, 0);
}

KJ_FORCE_INLINE kjVec3u kj_vec3u_zero(void) {
    return kj_vec3u(0, 0, 0);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_one(void) {
    return kj_vec3f(1.0f, 1.0f, 1.0f);
}

KJ_FORCE_INLINE kjVec3i kj_vec3i_one(void) {
    return kj_vec3i(1, 1, 1);
}

KJ_FORCE_INLINE kjVec3u kj_vec3u_one(void) {
    return kj_vec3u(1, 1, 1);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_inf(void) {
    return kj_vec3f(KJ_FLOAT32_INF, KJ_FLOAT32_INF, KJ_FLOAT32_INF);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_all(float a) {
    return kj_vec3f(a, a, a);
}

KJ_FORCE_INLINE kjVec3i kj_vec3i_all(int32_t a) {
    return kj_vec3i(a, a, a);
}

KJ_FORCE_INLINE kjVec3u kj_vec3u_all(uint32_t a) {
    return kj_vec3u(a, a, a);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_negate(kjVec3f a) {
    return kj_vec3f(-a.x, -a.y, -a.z);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_add(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_addf(kjVec3f a, float b) {
    return kj_vec3f(a.x + b, a.y + b, a.z + b);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_sub(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_subf(kjVec3f a, float b) {
    return kj_vec3f(a.x - b, a.y - b, a.z - b);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_mul(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_mulf(kjVec3f a, float b) {
    return kj_vec3f(a.x * b, a.y * b, a.z * b);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_div(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x * (1.0f / b.x), a.y * (1.0f / b.y), a.z * (1.0f / b.z));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_divf(kjVec3f a, float b) {
    b = 1.0f / b;
    return kj_vec3f(a.x * b, a.y * b, a.z * b);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_rcp(kjVec3f a) {
    return kj_vec3f(1.0f / a.x, 1.0f / a.y, 1.0f / a.z);
}

KJ_FORCE_INLINE float kj_vec3f_dot(kjVec3f a, kjVec3f b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_project(kjVec3f a, kjVec3f b) {
    return kj_vec3f_mulf(b, kj_vec3f_projectf(a, b));
}

KJ_FORCE_INLINE float kj_vec3f_projectf(kjVec3f a, kjVec3f b) {
    float length = kj_vec3f_length_sq(b);
    KJ_ASSERT(length > 0.0f);
    return kj_vec3f_dot(a, b) * (1.0f / length);
}

KJ_FORCE_INLINE kjMat3f kj_vec3f_outer(kjVec3f a, kjVec3f b) {
    return kj_mat3f(
            a.x * b.x, a.y * b.x, a.z * b.x,
            a.x * b.y, a.y * b.y, a.z * b.y,
            a.x * b.z, a.y * b.z, a.z * b.z);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_cross(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y);
}

KJ_FORCE_INLINE float kj_vec3f_length_sq(kjVec3f a) {
    return kj_vec3f_dot(a, a);
}

KJ_FORCE_INLINE float kj_vec3f_length(kjVec3f a) {
    return kj_sqrtf(kj_vec3f_length_sq(a));
}

KJ_FORCE_INLINE float kj_vec3f_length1(kjVec3f a) {
    float length = kj_vec3f_length(a);
    return length != 0.0f ? length: 1.0f;
}

KJ_FORCE_INLINE float kj_vec3f_distance_sq(kjVec3f a, kjVec3f b) {
    return kj_vec3f_length_sq(kj_vec3f_sub(a, b));
}

KJ_FORCE_INLINE float kj_vec3f_distance(kjVec3f a, kjVec3f b) {
    return kj_sqrtf(kj_vec3f_distance_sq(a, b));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_normalise(kjVec3f a) {
    float length = kj_vec3f_length(a);
    return kj_vec3f_mulf(a, 1.0f / length);
}

KJ_FORCE_INLINE bool kj_vec3f_is_normalised(kjVec3f a) {
    return kj_float32_eq(kj_vec3f_length_sq(a) - 1.0f, 0.0f, KJ_FLOAT32_EPS);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_orthonormalise(kjVec3f normal, kjVec3f n) {
    KJ_ASSERT(kj_vec3f_is_normalised(n));
    return kj_vec3f_normalise(kj_vec3f_sub(normal, kj_vec3f_mulf(n, kj_vec3f_dot(normal, n))));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_reflect(kjVec3f a, kjVec3f n) {
    KJ_ASSERT(kj_vec3f_is_normalised(n));
    return kj_vec3f_sub(a, kj_vec3f_mulf(n, 2.0f * kj_vec3f_dot(a, n)));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_flatten(kjVec3f a, kjVec3f n) {
    KJ_ASSERT(kj_vec3f_is_normalised(n));
    return kj_vec3f_sub(a, kj_vec3f_mulf(n, kj_vec3f_dot(a, n)));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_lerpf(kjVec3f a, kjVec3f b, float t) {
    return kj_vec3f(kj_lerpf(a.x, b.x, t), kj_lerpf(a.y, b.y, t), kj_lerpf(a.z, b.z, t));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_min(kjVec3f a, kjVec3f b) {
    return kj_vec3f(kj_minf(a.x, b.x), kj_minf(a.y, b.y), kj_minf(a.z, b.z));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_max(kjVec3f a, kjVec3f b) {
    return kj_vec3f(kj_maxf(a.x, b.x), kj_maxf(a.y, b.y), kj_maxf(a.z, b.z));
}

KJ_FORCE_INLINE float kj_vec3f_hmin(kjVec3f a) {
    return kj_minf(kj_minf(a.x, a.y), a.z);
}

KJ_FORCE_INLINE float kj_vec3f_hmax(kjVec3f a) {
    return kj_maxf(kj_maxf(a.x, a.y), a.z);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_abs(kjVec3f a) {
    return kj_vec3f(kj_absf(a.x), kj_absf(a.y), kj_absf(a.z));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_clamp(kjVec3f a, kjVec3f b, kjVec3f c) {
    return kj_vec3f(kj_clampf(a.x, b.x, c.x), kj_clampf(a.y, b.y, c.y), kj_clampf(a.z, b.z, c.z));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_clampf(kjVec3f a, float min, float max) {
    return kj_vec3f_clamp(a, kj_vec3f_all(min), kj_vec3f_all(max));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_clamp01(kjVec3f a) {
    return kj_vec3f_clamp(a, kj_vec3f_zero(), kj_vec3f_one());
}

KJ_FORCE_INLINE kjVec4f kj_vec3f_extend(kjVec3f a, float w) {
    return kj_vec4f(a.x, a.y, a.z, w);
}

KJ_FORCE_INLINE kjVec2f kj_vec3f_truncate(kjVec3f a) {
    return kj_vec2f(a.x, a.y);
}

KJ_FORCE_INLINE float kj_vec3f_angle_between(kjVec3f a, kjVec3f b) {
    return kj_atan2f(kj_vec3f_length(kj_vec3f_cross(a, b)), kj_vec3f_dot(a, b));
}

KJ_FORCE_INLINE kjVec4f kj_vec4f(float x, float y, float z, float w) {
    kjVec4f res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_FORCE_INLINE kjVec4i kj_vec4i(int32_t x, int32_t y, int32_t z, int32_t w) {
    kjVec4i res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_FORCE_INLINE kjVec4u kj_vec4u(uint32_t x, uint32_t y, uint32_t z, uint32_t w) {
    kjVec4u res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_zero(void) {
    return kj_vec4f(0.0f, 0.0f, 0.0f, 0.0f);
}

KJ_FORCE_INLINE kjVec4i kj_vec4i_zero(void) {
    return kj_vec4i(0, 0, 0, 0);
}

KJ_FORCE_INLINE kjVec4u kj_vec4u_zero(void) {
    return kj_vec4u(0, 0, 0, 0);
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_one(void) {
    return kj_vec4f(1.0f, 1.0f, 1.0f, 1.0f);
}

KJ_FORCE_INLINE kjVec4i kj_vec4i_one(void) {
    return kj_vec4i(1, 1, 1, 1);
}

KJ_FORCE_INLINE kjVec4u kj_vec4u_one(void) {
    return kj_vec4u(1, 1, 1, 1);
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_inf(void) {
    return kj_vec4f(KJ_FLOAT32_INF, KJ_FLOAT32_INF, KJ_FLOAT32_INF, KJ_FLOAT32_INF);
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_all(float a) {
    return kj_vec4f(a, a, a, a);
}

KJ_FORCE_INLINE kjVec4i kj_vec4i_all(int32_t a) {
    return kj_vec4i(a, a, a, a);
}

KJ_FORCE_INLINE kjVec4u kj_vec4u_all(uint32_t a) {
    return kj_vec4u(a, a, a, a);
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_negate(kjVec4f a) {
    return kj_vec4f(-a.x, -a.y, -a.z, -a.w);
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_add(kjVec4f a, kjVec4f b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_load_ps(&b.x);
    __m128 m = _mm_add_ps(ma, mb);
    _mm_store_ps(&res.x, m);
    return res;
#else
    return kj_vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_addf(kjVec4f a, float b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_set1_ps(b);
    __m128 m = _mm_add_ps(ma, mb);
    _mm_store_ps(&res.x, m);
    return res;
#else
    return kj_vec4f(a.x + b, a.y + b, a.z + b, a.w + b);
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_sub(kjVec4f a, kjVec4f b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_load_ps(&b.x);
    __m128 m = _mm_sub_ps(ma, mb);
    _mm_store_ps(&res.x, m);
    return res;
#else
    return kj_vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_subf(kjVec4f a, float b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_set1_ps(b);
    __m128 m = _mm_add_ps(ma, mb);
    _mm_store_ps(&res.x, m);
    return res;
#else
    return kj_vec4f(a.x - b, a.y - b, a.z - b, a.w - b);
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_mul(kjVec4f a, kjVec4f b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_load_ps(&b.x);
    __m128 m = _mm_mul_ps(ma, mb);
    _mm_store_ps(&res.x, m);
    return res;
#else
    return kj_vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_mulf(kjVec4f a, float b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_set1_ps(b);
    __m128 m = _mm_mul_ps(ma, mb);
    _mm_store_ps(&res.x, m);
    return res;
#else
    return kj_vec4f(a.x * b, a.y * b, a.z * b, a.w * b);
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_div(kjVec4f a, kjVec4f b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_load_ps(&b.x);
    __m128 m = _mm_div_ps(ma, mb);
    _mm_store_ps(&res.x, m);
    return res;
#else
    return kj_vec4f(a.x * (1.0f / b.x), a.y * (1.0f / b.y), a.z * (1.0f / b.z), a.w * (1.0f / b.w));
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_divf(kjVec4f a, float b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_set1_ps(b);
    __m128 m = _mm_div_ps(ma, mb);
    _mm_store_ps(&res.x, m);
    return res;
#else
    b = 1.0f / b;
    return kj_vec4f(a.x * b, a.y * b, a.z * b, a.w * b);
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_rcp(kjVec4f a) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 m = _mm_rcp_ps(ma);
    _mm_store_ps(&res.x, m);
    return res;
#else
    return kj_vec4f(1.0f / a.x, 1.0f / a.y, 1.0f / a.z, 1.0f / a.w);
#endif
}

KJ_FORCE_INLINE float kj_vec4f_dot(kjVec4f a, kjVec4f b) {
#if defined(KJ_MATH_SIMD)
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_load_ps(&b.x);
    ma = _mm_mul_ps(ma, mb);
    mb = _mm_shuffle_ps(ma, ma, _MM_SHUFFLE(2, 3, 0, 1));
    ma = _mm_add_ps(ma, mb);
    mb = _mm_shuffle_ps(ma, ma, _MM_SHUFFLE(0, 1, 2, 3));
    ma = _mm_add_ps(ma, mb);
    return _mm_cvtss_f32(ma);
#else
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_project(kjVec4f a, kjVec4f b) {
    return kj_vec4f_mulf(b, kj_vec4f_projectf(a, b));
}

KJ_FORCE_INLINE float kj_vec4f_projectf(kjVec4f a, kjVec4f b) {
    float length = kj_vec4f_length_sq(b);
    KJ_ASSERT(length > 0.0f);
    return kj_vec4f_dot(a, b) / length;
}

KJ_FORCE_INLINE kjMat4f kj_vec4f_outer(kjVec4f a, kjVec4f b) {
    return kj_mat4f(
            a.x * b.x, a.y * b.x, a.z * b.x, a.w * b.x,
            a.x * b.y, a.y * b.y, a.z * b.y, a.w * b.y,
            a.x * b.z, a.y * b.z, a.z * b.z, a.w * b.z,
            a.x * b.z, a.y * b.z, a.z * b.z, a.w * b.w);
}

KJ_FORCE_INLINE float kj_vec4f_length_sq(kjVec4f a) {
    return kj_vec4f_dot(a, a);
}

KJ_FORCE_INLINE float kj_vec4f_length(kjVec4f a) {
    return kj_sqrtf(kj_vec4f_length_sq(a));
}

KJ_FORCE_INLINE float kj_vec4f_length1(kjVec4f a) {
    float length = kj_vec4f_length(a);
    return length != 0.0f ? length: 1.0f;
}

KJ_FORCE_INLINE float kj_vec4f_distance_sq(kjVec4f a, kjVec4f b) {
    return kj_vec4f_length_sq(kj_vec4f_sub(a, b));
}

KJ_FORCE_INLINE float kj_vec4f_distance(kjVec4f a, kjVec4f b) {
    return kj_sqrtf(kj_vec4f_distance_sq(a, b));
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_normalise(kjVec4f a) {
    float length = kj_vec4f_length(a);
    return kj_vec4f_mulf(a, 1.0f / length);
}

KJ_FORCE_INLINE bool kj_vec4f_is_normalised(kjVec4f a) {
    return kj_float32_eq(kj_vec4f_length_sq(a) - 1.0f, 0.0f, KJ_FLOAT32_EPS);
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_lerpf(kjVec4f a, kjVec4f b, float t) {
    return kj_vec4f(kj_lerpf(a.x, b.x, t), kj_lerpf(a.y, b.y, t), kj_lerpf(a.z, b.z, t), kj_lerpf(a.w, b.w, t));
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_min(kjVec4f a, kjVec4f b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_load_ps(&b.x);
    __m128 min = _mm_min_ps(ma, mb);
    _mm_store_ps(&res.x, min);
    return res;
#else
    return kj_vec4f(kj_minf(a.x, b.x), kj_minf(a.y, b.y), kj_minf(a.z, b.z), kj_minf(a.w, b.w));
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_max(kjVec4f a, kjVec4f b) {
#if defined(KJ_MATH_SIMD)
    kjVec4f res;
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mb = _mm_load_ps(&b.x);
    __m128 max = _mm_max_ps(ma, mb);
    _mm_store_ps(&res.x, max);
    return res;
#else
    return kj_vec4f(kj_maxf(a.x, b.x), kj_maxf(a.y, b.y), kj_maxf(a.z, b.z), kj_maxf(a.w, b.w));
#endif
}

KJ_FORCE_INLINE float kj_vec4f_hmin(kjVec4f a) {
    return kj_minf(kj_minf(a.x, a.y), kj_minf(a.z, a.w));
}

KJ_FORCE_INLINE float kj_vec4f_hmax(kjVec4f a) {
    return kj_maxf(kj_maxf(a.x, a.y), kj_maxf(a.z, a.w));
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_clamp(kjVec4f a, kjVec4f min, kjVec4f max) {
#if defined(KJ_MATH_SIMD)
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mmin = _mm_load_ps(&min.x);
    __m128 mmax = _mm_load_ps(&max.x);
    kjVec4f res;
    _mm_store_ps(&res.x, _mm_min_ps(_mm_max_ps(ma, mmin), mmax));
    return res;
#else
    return kj_vec4f(
            kj_clampf(a.x, min.x, max.x),
            kj_clampf(a.y, min.y, max.y),
            kj_clampf(a.z, min.z, max.z),
            kj_clampf(a.w, min.w, max.w));
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_clampf(kjVec4f a, float min, float max) {
#if defined(KJ_MATH_SIMD)
    __m128 ma = _mm_load_ps(&a.x);
    __m128 mmin = _mm_set1_ps(min);
    __m128 mmax = _mm_set1_ps(max);
    kjVec4f res;
    _mm_store_ps(&res.x, _mm_min_ps(mmax, _mm_max_ps(mmin, ma)));
    return res;
#else
    return kj_vec4f_clamp(a, kj_vec4f_all(min), kj_vec4f_all(max));
#endif
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_clamp01(kjVec4f a) {
    return kj_vec4f_clamp(a, kj_vec4f_zero(), kj_vec4f_one());
}

KJ_FORCE_INLINE kjVec3f kj_vec4f_truncate(kjVec4f a) {
    return kj_vec3f(a.x, a.y, a.z);
}

KJ_FORCE_INLINE kjQuatf kj_quatf(float x, float y, float z, float w) {
    return kj_vec4f(x, y, z, w);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_vec3f(kjVec3f xyz, float w) {
    return kj_vec4f(xyz.x, xyz.y, xyz.z, w);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_vec4f(kjVec4f xyzw) {
    return kj_quatf(xyzw.x, xyzw.y, xyzw.z, xyzw.w);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_from_euler(float pitch, float yaw, float roll) {
    yaw *= 0.5f;
    pitch *= 0.5f;
    roll *= 0.5f;
    float sy = kj_sinf(yaw);
    float cy = kj_cosf(yaw);
    float sp = kj_sinf(pitch);
    float cp = kj_cosf(pitch);
    float sr = kj_sinf(roll);
    float cr = kj_cosf(roll);
    return kj_quatf(
            sr * cp * cy - cr * sp * sy,
            cr * sp * cy + sr * cp * sy,
            cr * cp * sy - sr * sp * cy,
            cr * cp * cy + sr * sp * sy);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_identity(void) {
    return kj_quatf(0.0f, 0.0f, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_zero(void) {
    return kj_quatf(0.0f, 0.0f, 0.0f, 0.0f);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_one(void) {
    return kj_quatf(1.0f, 1.0f, 1.0f, 1.0f);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_conjugate(kjQuatf q) {
    return kj_quatf(-q.x, -q.y, -q.z, q.w);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_add(kjQuatf a, kjQuatf b) {
    return kj_quatf(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_addf(kjQuatf q, float v) {
    return kj_quatf(q.x + v, q.y + v, q.z + v, q.w + v);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_sub(kjQuatf a, kjQuatf b) {
    return kj_quatf(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_subf(kjQuatf q, float v) {
    return kj_quatf(q.x - v, q.y - v, q.z - v, q.w - v);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_mul(kjQuatf a, kjQuatf b) {
    return kj_quatf(
            a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
            a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
            a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
            a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
}

KJ_FORCE_INLINE kjVec3f kj_quatf_mul_vec3f(kjQuatf q, kjVec3f v) {
    kjVec3f c = kj_vec3f(q.x, q.y, q.z);
    kjVec3f t = kj_vec3f_mulf(kj_vec3f_cross(c, v), 2.0f);
    return kj_vec3f_add(kj_vec3f_add(v, kj_vec3f_mulf(t, q.w)), kj_vec3f_cross(c, t));
}

KJ_FORCE_INLINE kjQuatf kj_quatf_mulf(kjQuatf q, float v) {
    return kj_quatf(q.x * v, q.y * v, q.z * v, q.w * v);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_div(kjQuatf a, kjQuatf b) {
    return kj_quatf(
            a.w * b.x - a.x * b.w - a.y * b.z + a.z * b.y,
            a.w * b.y - a.y * b.w - a.z * b.x + a.x * b.z,
            a.w * b.z - a.z * b.w - a.x * b.y + a.y * b.x,
            a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_divf(kjQuatf q, float v) {
    v = 1.0f / v;
    return kj_quatf(q.x * v, q.y * v, q.z * v, q.w * v);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_axis_angle(float radians, float x, float y, float z) {
    float s = kj_sinf(radians);
    return kj_quatf(x * s, y * s, z * s, kj_cosf(radians));
}

KJ_FORCE_INLINE kjQuatf kj_quatf_axis_angle_vec3f(float radians, kjVec3f axis) {
    return kj_quatf_axis_angle(radians, axis.x, axis.y, axis.z);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_axis_angle_x(float radians) {
    return kj_quatf(kj_sinf(radians) * 0.5f, 0.0f, 0.0f, kj_cosf(radians) * 0.5f);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_axis_angle_y(float radians) {
    return kj_quatf(0.0f, kj_sinf(radians) * 0.5f, 0.0f, kj_cosf(radians) * 0.5f);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_axis_angle_z(float radians) {
    return kj_quatf(0.0f, 0.0f, kj_sinf(radians) * 0.5f, kj_cosf(radians) * 0.5f);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_rotate_vec3f(kjVec3f from, kjVec3f to) {
    kjQuatf q = kj_quatf_vec3f(kj_vec3f_cross(from, to), kj_vec3f_dot(from, to));
    q.w += kj_quatf_length(q);
    return kj_quatf_normalise(q);
}

KJ_FORCE_INLINE float kj_quatf_pitch(kjQuatf q) {
    return kj_atan2f(2.0f * (q.y * q.z + q.w * q.x), (q.w * q.w) - (q.x * q.x) - (q.y * q.y) + (q.z * q.z));
}

KJ_FORCE_INLINE float kj_quatf_yaw(kjQuatf q) {
    return kj_asinf(-2.0f * (q.x * q.z - q.w * q.y));
}

KJ_FORCE_INLINE float kj_quatf_roll(kjQuatf q) {
    return kj_atan2f(2.0f * (q.x * q.y + q.w * q.z), (q.w * q.w) - (q.x * q.x) - (q.y * q.y) + (q.z * q.z));
}

KJ_FORCE_INLINE kjVec3f kj_quatf_euler(kjQuatf q) {
    return kj_vec3f(
            kj_quatf_pitch(q),
            kj_quatf_yaw(q),
            kj_quatf_roll(q));
}

KJ_FORCE_INLINE float kj_quatf_dot(kjQuatf a, kjQuatf b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

KJ_FORCE_INLINE kjQuatf kj_quatf_cross(kjQuatf a, kjQuatf b) {
    return kj_quatf(
            (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z),
            (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y),
            (a.w * b.y) + (a.y * b.w) + (a.z * b.x) - (a.x * b.z),
            (a.w * b.z) + (a.z * b.w) + (a.x * b.y) - (a.y * b.x));
}

KJ_FORCE_INLINE float kj_quatf_length_sq(kjQuatf q) {
    return kj_quatf_dot(q, q);
}

KJ_FORCE_INLINE float kj_quatf_length(kjQuatf q) {
    return kj_sqrtf(kj_quatf_length_sq(q));
}

KJ_FORCE_INLINE kjQuatf kj_quatf_normalise(kjQuatf q) {
    return kj_quatf_mulf(q, 1.0f / kj_quatf_length(q));
}

KJ_FORCE_INLINE kjQuatf kj_quatf_nlerp(kjQuatf from, kjQuatf to, float t) {
    return kj_quatf_normalise(kj_quatf_add(kj_quatf_mulf(from, 1.0f - t), kj_quatf_mulf(to, t)));
}

KJ_FORCE_INLINE kjQuatf kj_quatf_slerp(kjQuatf from, kjQuatf to, float t) {
    float ct = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;
    float rt = 1.0f - t;
    if(ct < 0.0f) {
        ct = -ct;
        to.x = -to.x;
        to.y = -to.y;
        to.z = -to.z;
        to.w = -to.w;
    }
    if((1.0f - ct) > 0.0f) {
        float theta = kj_acosf(ct);
        float t = 1.0f / kj_sinf(theta);
        rt  = kj_sinf(theta * rt) * t;
        t = kj_sinf(theta * t) * t;
    }
    return kj_quatf(
            (rt * from.x) + (t * to.x),
            (rt * from.y) + (t * to.y),
            (rt * from.z) + (t * to.z),
            (rt * from.w) + (t * to.w));
}

KJ_FORCE_INLINE kjQuatf kj_quatf_inverse(kjQuatf q) {
    return kj_quatf_mulf(kj_quatf_conjugate(q), 1.0f / kj_quatf_length_sq(q));
}

KJ_FORCE_INLINE kjMat2f kj_mat2f(
        float c0r0, float c0r1,
        float c1r0, float c1r1) {
    kjMat2f res;
    res.e[0][0] = c0r0;
    res.e[1][0] = c1r0;
    res.e[0][1] = c0r1;
    res.e[1][1] = c1r1;
    return res;
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_from_columns(kjVec2f c0, kjVec2f c1) {
    kjMat2f res;
    res.c[0] = c0;
    res.c[1] = c1;
    return res;
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_diagonal(float c0r0, float c1r1) {
    return kj_mat2f(
            c0r0, 0.0f,
            0.0f, c1r1);
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_identity(void) {
    return kj_mat2f(
            1.0f, 0.0f,
            0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_zero(void) {
    return kj_mat2f(
            0.0f, 0.0f,
            0.0f, 0.0f);
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_one(void) {
    return kj_mat2f(
            1.0f, 1.0f,
            1.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_mul(kjMat2f a, kjMat2f b) {
    return kj_mat2f(
            a.e[0][0] * b.e[0][0] + a.e[1][0] * b.e[0][1],
            a.e[0][1] * b.e[0][0] + a.e[1][1] * b.e[0][1],
            a.e[0][0] * b.e[1][0] + a.e[1][0] * b.e[1][1],
            a.e[0][1] * b.e[1][0] + a.e[1][1] * b.e[1][1]);
}

KJ_FORCE_INLINE kjVec2f kj_mat2f_mul_vec2f(kjMat2f a, kjVec2f b) {
    return kj_vec2f(
            a.e[0][0] * b.x + a.e[1][0] * b.y,
            a.e[0][1] * b.x + a.e[1][1] * b.y);
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_transpose(kjMat2f a) {
    return kj_mat2f(
            a.e[0][0], a.e[1][0],
            a.e[0][1], a.e[1][1]);
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_rotate(float radians) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    return kj_mat2f(
             c, s,
            -s, c);
}

KJ_FORCE_INLINE float kj_mat2f_determinant(kjMat2f a) {
    return a.e[0][0] * a.e[1][1] - a.e[1][0] * a.e[0][1];
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_inverse(kjMat2f a) {
    float det = kj_mat2f_determinant(a);
    KJ_ASSERT(det != 0.0f);
    det = 1.0f / det;
    return kj_mat2f(
             a.e[1][1] * det, -a.e[0][1] * det,
            -a.e[1][0] * det,  a.e[0][0] * det);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f(
        float c0r0, float c0r1, float c0r2,
        float c1r0, float c1r1, float c1r2,
        float c2r0, float c2r1, float c2r2) {
    kjMat3f res;
    res.e[0][0] = c0r0;
    res.e[1][0] = c1r0;
    res.e[2][0] = c2r0;
    res.e[0][1] = c0r1;
    res.e[1][1] = c1r1;
    res.e[2][1] = c2r1;
    res.e[0][2] = c0r2;
    res.e[1][2] = c1r2;
    res.e[2][2] = c2r2;
    return res;
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_from_columns(kjVec3f c0, kjVec3f c1, kjVec3f c2) {
    kjMat3f res;
    res.c[0] = c0;
    res.c[1] = c1;
    res.c[2] = c2;
    return res;
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_diagonal(float c0r0, float c1r1, float c2r2) {
    return kj_mat3f(
            c0r0, 0.0f, 0.0f,
            0.0f, c1r1, 0.0f,
            0.0f, 0.0f, c2r2);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_identity(void) {
    return kj_mat3f(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_zero(void) {
    return kj_mat3f(
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_one(void) {
    return kj_mat3f(
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_mul(kjMat3f a, kjMat3f b) {
    return kj_mat3f(
            a.e[0][0] * b.e[0][0] + a.e[1][0] * b.e[0][1] + a.e[2][0] * b.e[0][2],
            a.e[0][1] * b.e[0][0] + a.e[1][1] * b.e[0][1] + a.e[2][1] * b.e[0][2],
            a.e[0][2] * b.e[0][0] + a.e[1][2] * b.e[0][1] + a.e[2][2] * b.e[0][2],
            a.e[0][0] * b.e[1][0] + a.e[1][0] * b.e[1][1] + a.e[2][0] * b.e[1][2],
            a.e[0][1] * b.e[1][0] + a.e[1][1] * b.e[1][1] + a.e[2][1] * b.e[1][2],
            a.e[0][2] * b.e[1][0] + a.e[1][2] * b.e[1][1] + a.e[2][2] * b.e[1][2],
            a.e[0][0] * b.e[2][0] + a.e[1][0] * b.e[2][1] + a.e[2][0] * b.e[2][2],
            a.e[0][1] * b.e[2][0] + a.e[1][1] * b.e[2][1] + a.e[2][1] * b.e[2][2],
            a.e[0][2] * b.e[2][0] + a.e[1][2] * b.e[2][1] + a.e[2][2] * b.e[2][2]);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_transpose(kjMat3f a) {
    return kj_mat3f(
            a.e[0][0], a.e[1][0], a.e[2][0],
            a.e[0][1], a.e[1][1], a.e[2][1],
            a.e[0][2], a.e[1][2], a.e[2][2]);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_translate(float x, float y) {
    return kj_mat3f(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
               x,    y, 1.0f);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_translate_vec2f(kjVec2f xy) {
    return kj_mat3f_translate(xy.x, xy.y);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate_vec3f(float radians, kjVec3f xyz) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    kjVec3f axis = kj_vec3f_normalise(xyz);
    kjVec3f rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - c));
    return kj_mat3f(
                     c + rot_axis.x * axis.x, rot_axis.x * axis.y + s * axis.z, rot_axis.x * axis.z - s * axis.y,
            rot_axis.y * axis.x - s * axis.z,          c + rot_axis.y * axis.y, rot_axis.y * axis.z + s * axis.x,
            rot_axis.z * axis.x + s * axis.y, rot_axis.z * axis.y - s * axis.x,          c + rot_axis.z * axis.z);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate(float radians, float x, float y, float z) {
    return kj_mat3f_rotate_vec3f(radians, kj_vec3f(x, y, z));
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate_x(float radians) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    return kj_mat3f(
            1.0f, 0.0f, 0.0f,
            0.0f,    c,    s,
            0.0f,   -s,    c);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate_y(float radians) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    return kj_mat3f(
               c, 0.0f,   -s,
            0.0f, 1.0f, 0.0f,
               s, 0.0f,    c);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate_z(float radians) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    return kj_mat3f(
               c,    s, 0.0f,
              -s,    c, 0.0f,
            0.0f, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_scale(float x, float y) {
    return kj_mat3f_diagonal(x, y, 1.0f);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_scale_vec2f(kjVec2f xy) {
    return kj_mat3f_diagonal(xy.x, xy.y, 1.0f);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_shear(float x, float y) {
    return kj_mat3f(
                  1.0f, kj_tanf(y), 0.0f,
            kj_tanf(x),       1.0f, 0.0f,
                  0.0f,       0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_shear_vec2f(kjVec2f xy) {
    return kj_mat3f_shear(xy.x, xy.y);
}

KJ_FORCE_INLINE float kj_mat3f_determinant(kjMat3f a) {
    return
        a.e[0][0] * (a.e[1][1] * a.e[2][2] - a.e[2][1] * a.e[1][2]) -
        a.e[1][0] * (a.e[0][1] * a.e[2][2] - a.e[2][1] * a.e[0][2]) +
        a.e[2][0] * (a.e[0][1] * a.e[1][2] - a.e[1][1] * a.e[0][2]);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_inverse(kjMat3f a) {
    float det = kj_mat3f_determinant(a);
    KJ_ASSERT(det != 0.0f);
    det = 1.0f / det;
    kjMat3f res;
    res.c[0] = kj_vec3f_mulf(kj_vec3f_cross(a.c[1], a.c[2]), det);
    res.c[1] = kj_vec3f_mulf(kj_vec3f_cross(a.c[2], a.c[0]), det);
    res.c[2] = kj_vec3f_mulf(kj_vec3f_cross(a.c[0], a.c[1]), det);
    res = kj_mat3f_transpose(res);
    return res;
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_from_quatf(kjQuatf q) {
    kjQuatf nq = kj_quatf_normalise(q);
    float xx = nq.x * nq.x;
    float yy = nq.y * nq.y;
    float zz = nq.z * nq.z;
    float xz = nq.x * nq.z;
    float xy = nq.x * nq.y;
    float yz = nq.y * nq.z;
    float wx = nq.w * nq.x;
    float wy = nq.w * nq.y;
    float wz = nq.w * nq.z;
    return kj_mat3f(
            1.0f - 2.0f * (yy + zz),        2.0f * (xy + wz),        2.0f * (xz - wy),
                   2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz),        2.0f * (yz + wx),
                   2.0f * (xz + wy),        2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy));
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_from_transform(kjVec2f translate, kjQuatf rotate, kjVec2f scale) {
    kjMat3f res = kj_mat3f_from_quatf(rotate);
    res.e[2][0] = translate.x;
    res.e[2][1] = translate.y;
    res.e[0][0] *= scale.x;
    res.e[0][1] *= scale.x;
    res.e[0][2] *= scale.x;
    res.e[1][0] *= scale.y;
    res.e[1][1] *= scale.y;
    res.e[1][2] *= scale.y;
    return res;
}

KJ_FORCE_INLINE kjMat4f kj_mat4f(
        float c0r0, float c0r1, float c0r2, float c0r3,
        float c1r0, float c1r1, float c1r2, float c1r3,
        float c2r0, float c2r1, float c2r2, float c2r3,
        float c3r0, float c3r1, float c3r2, float c3r3) {
    kjMat4f res;
    res.e[0][0] = c0r0;
    res.e[1][0] = c1r0;
    res.e[2][0] = c2r0;
    res.e[3][0] = c3r0;
    res.e[0][1] = c0r1;
    res.e[1][1] = c1r1;
    res.e[2][1] = c2r1;
    res.e[3][1] = c3r1;
    res.e[0][2] = c0r2;
    res.e[1][2] = c1r2;
    res.e[2][2] = c2r2;
    res.e[3][2] = c3r2;
    res.e[0][3] = c0r3;
    res.e[1][3] = c1r3;
    res.e[2][3] = c2r3;
    res.e[3][3] = c3r3;
    return res;
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_from_columns(kjVec4f c0, kjVec4f c1, kjVec4f c2, kjVec4f c3) {
    kjMat4f res;
    res.c[0] = c0;
    res.c[1] = c1;
    res.c[2] = c2;
    res.c[3] = c3;
    return res;
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_diagonal(float c0r0, float c1r1, float c2r2, float c3r3) {
    return kj_mat4f(
            c0r0, 0.0f, 0.0f, 0.0f,
            0.0f, c1r1, 0.0f, 0.0f,
            0.0f, 0.0f, c2r2, 0.0f,
            0.0f, 0.0f, 0.0f, c3r3);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_identity(void) {
    return kj_mat4f(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_zero(void) {
    return kj_mat4f(
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_one(void) {
    return kj_mat4f(
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_mul(kjMat4f a, kjMat4f b) {
    kjMat4f res;
    res.e[0][0] = a.e[0][0] * b.e[0][0] + a.e[1][0] * b.e[0][1] + a.e[2][0] * b.e[0][2] + a.e[3][0] * b.e[0][3];
    res.e[0][1] = a.e[0][1] * b.e[0][0] + a.e[1][1] * b.e[0][1] + a.e[2][1] * b.e[0][2] + a.e[3][1] * b.e[0][3];
    res.e[0][2] = a.e[0][2] * b.e[0][0] + a.e[1][2] * b.e[0][1] + a.e[2][2] * b.e[0][2] + a.e[3][2] * b.e[0][3];
    res.e[0][3] = a.e[0][3] * b.e[0][0] + a.e[1][3] * b.e[0][1] + a.e[2][3] * b.e[0][2] + a.e[3][3] * b.e[0][3];
    res.e[1][0] = a.e[0][0] * b.e[1][0] + a.e[1][0] * b.e[1][1] + a.e[2][0] * b.e[1][2] + a.e[3][0] * b.e[1][3];
    res.e[1][1] = a.e[0][1] * b.e[1][0] + a.e[1][1] * b.e[1][1] + a.e[2][1] * b.e[1][2] + a.e[3][1] * b.e[1][3];
    res.e[1][2] = a.e[0][2] * b.e[1][0] + a.e[1][2] * b.e[1][1] + a.e[2][2] * b.e[1][2] + a.e[3][2] * b.e[1][3];
    res.e[1][3] = a.e[0][3] * b.e[1][0] + a.e[1][3] * b.e[1][1] + a.e[2][3] * b.e[1][2] + a.e[3][3] * b.e[1][3];
    res.e[2][0] = a.e[0][0] * b.e[2][0] + a.e[1][0] * b.e[2][1] + a.e[2][0] * b.e[2][2] + a.e[3][0] * b.e[2][3];
    res.e[2][1] = a.e[0][1] * b.e[2][0] + a.e[1][1] * b.e[2][1] + a.e[2][1] * b.e[2][2] + a.e[3][1] * b.e[2][3];
    res.e[2][2] = a.e[0][2] * b.e[2][0] + a.e[1][2] * b.e[2][1] + a.e[2][2] * b.e[2][2] + a.e[3][2] * b.e[2][3];
    res.e[2][3] = a.e[0][3] * b.e[2][0] + a.e[1][3] * b.e[2][1] + a.e[2][3] * b.e[2][2] + a.e[3][3] * b.e[2][3];
    res.e[3][0] = a.e[0][0] * b.e[3][0] + a.e[1][0] * b.e[3][1] + a.e[2][0] * b.e[3][2] + a.e[3][0] * b.e[3][3];
    res.e[3][1] = a.e[0][1] * b.e[3][0] + a.e[1][1] * b.e[3][1] + a.e[2][1] * b.e[3][2] + a.e[3][1] * b.e[3][3];
    res.e[3][2] = a.e[0][2] * b.e[3][0] + a.e[1][2] * b.e[3][1] + a.e[2][2] * b.e[3][2] + a.e[3][2] * b.e[3][3];
    res.e[3][3] = a.e[0][3] * b.e[3][0] + a.e[1][3] * b.e[3][1] + a.e[2][3] * b.e[3][2] + a.e[3][3] * b.e[3][3];
    return res;
}

KJ_FORCE_INLINE kjVec4f kj_mat4f_mul_vec4f(kjMat4f a, kjVec4f b) {
    return kj_vec4f(
            a.e[0][0] * b.x + a.e[1][0] * b.y + a.e[2][0] * b.z + a.e[3][0] * b.w,
            a.e[0][1] * b.x + a.e[1][1] * b.y + a.e[2][1] * b.z + a.e[3][1] * b.w,
            a.e[0][2] * b.x + a.e[1][2] * b.y + a.e[2][2] * b.z + a.e[3][2] * b.w,
            a.e[0][3] * b.x + a.e[1][3] * b.y + a.e[2][3] * b.z + a.e[3][3] * b.w);
}

KJ_FORCE_INLINE kjVec3f kj_mat4f_mul_vec3f(kjMat4f a, kjVec3f b) {
    return kj_vec3f(
            a.e[0][0] * b.x + a.e[1][0] * b.y + a.e[2][0] * b.z + a.e[3][0],
            a.e[0][1] * b.x + a.e[1][1] * b.y + a.e[2][1] * b.z + a.e[3][1],
            a.e[0][2] * b.x + a.e[1][2] * b.y + a.e[2][2] * b.z + a.e[3][2]);
}

KJ_FORCE_INLINE kjVec4f kj_mat4f_mul_vec3f_extend(kjMat4f a, kjVec3f b) {
    return kj_vec4f(
            a.e[0][0] * b.x + a.e[1][0] * b.y + a.e[2][0] * b.z + a.e[3][0],
            a.e[0][1] * b.x + a.e[1][1] * b.y + a.e[2][1] * b.z + a.e[3][1],
            a.e[0][2] * b.x + a.e[1][2] * b.y + a.e[2][2] * b.z + a.e[3][2],
            a.e[0][3] * b.x + a.e[1][3] * b.y + a.e[2][3] * b.z + a.e[3][3]);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_mulf(kjMat4f a, float b) {
    return kj_mat4f(
            a.e[0][0] * b, a.e[1][0] * b, a.e[2][0] * b, a.e[3][0] * b,
            a.e[0][1] * b, a.e[1][1] * b, a.e[2][1] * b, a.e[3][1] * b,
            a.e[0][2] * b, a.e[1][2] * b, a.e[2][2] * b, a.e[3][2] * b,
            a.e[0][3] * b, a.e[1][3] * b, a.e[2][3] * b, a.e[3][3] * b);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_transpose(kjMat4f a) {
    return kj_mat4f(
            a.e[0][0], a.e[1][0], a.e[2][0], a.e[3][0],
            a.e[0][1], a.e[1][1], a.e[2][1], a.e[3][1],
            a.e[0][2], a.e[1][2], a.e[2][2], a.e[3][2],
            a.e[0][3], a.e[1][3], a.e[2][3], a.e[3][3]);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_translate(float x, float y, float z) {
    return kj_mat4f(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
               x,    y,    z, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_translate_vec3f(kjVec3f xyz) {
    return kj_mat4f_translate(xyz.x, xyz.y, xyz.z);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate_x(float radians) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    return kj_mat4f(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f,    c,    s, 0.0f,
            0.0f,   -s,    c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate_y(float radians) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    return kj_mat4f(
               c, 0.0f,   -s, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
               s, 0.0f,    c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate_z(float radians) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    return kj_mat4f(
                c,    s, 0.0f, 0.0f,
               -s,    c, 0.0f, 0.0f,
             0.0f, 0.0f, 1.0f, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f);
}


KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate_vec3f(float radians, kjVec3f xyz) {
    float c = kj_cosf(radians);
    float s = kj_sinf(radians);
    kjVec3f axis = kj_vec3f_normalise(xyz);
    kjVec3f rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - c));
    return kj_mat4f(
                     c + rot_axis.x * axis.x, rot_axis.x * axis.y + s * axis.z, rot_axis.x * axis.z - s * axis.y, 0.0f,
            rot_axis.y * axis.x - s * axis.z,          c + rot_axis.y * axis.y, rot_axis.y * axis.z + s * axis.x, 0.0f,
            rot_axis.z * axis.x + s * axis.y, rot_axis.z * axis.y - s * axis.x,          c + rot_axis.z * axis.z, 0.0f,
                                        0.0f,                             0.0f,                             0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate(float radians, float x, float y, float z) {
    return kj_mat4f_rotate_vec3f(radians, kj_vec3f(x, y, z));
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scale(float x, float y, float z) {
    return kj_mat4f_diagonal(x, y, z, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scalef(float a) {
    return kj_mat4f_diagonal(a, a, a, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz) {
    return kj_mat4f_scale(xyz.x, xyz.y, xyz.z);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_ortho(float l, float r, float b, float t, float znear, float zfar) {
    KJ_ASSERT(zfar > znear);
    float depth = zfar - znear;
    float width = r - l;
    float height = t - b;
    KJ_ASSERT(depth != 0.0f);
    KJ_ASSERT(width != 0.0f);
    KJ_ASSERT(height != 0.0f);
    depth = 1.0f / depth;
    width = 1.0f / width;
    height = 1.0f / height;
    return kj_mat4f(
                2.0f * width,              0.0f,                    0.0f, 0.0f,
                        0.0f,     2.0f * height,                    0.0f, 0.0f,
                        0.0f,              0.0f,           -2.0f * depth, 0.0f,
            -(r + l) * width, -(t + b) * height, -(zfar + znear) * depth, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_ortho_inf(float l, float r, float b, float t) {
    return kj_mat4f_ortho(l, r, b, t, -1.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_perspective(float fovy, float aspect, float znear, float zfar) {
    KJ_ASSERT(fovy > 0.0f);
    KJ_ASSERT(fovy < KJ_PI);
    KJ_ASSERT(aspect > 0.0f);
    KJ_ASSERT(zfar > znear);
    float tan_fovy = kj_tanf(fovy * 0.5f);
    float depth = znear - zfar;
    KJ_ASSERT(tan_fovy != 0.0f);
    KJ_ASSERT(depth != 0.0f);
    depth = 1.0f / depth;
    return kj_mat4f(
            1.0f / (tan_fovy * aspect),            0.0f,                          0.0f,  0.0f,
                                  0.0f, 1.0f / tan_fovy,                          0.0f,  0.0f,
                                  0.0f,            0.0f,        (zfar + znear) * depth, -1.0f,
                                  0.0f,            0.0f, (2.0f * zfar * znear) * depth,  0.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_perspective_inf(float fovy, float aspect, float znear) {
    KJ_ASSERT(fovy > 0.0f);
    KJ_ASSERT(fovy < KJ_PI);
    KJ_ASSERT(aspect > 0.0f);
    float tan_fovy = kj_tanf(fovy * 0.5f);
    KJ_ASSERT(tan_fovy != 0.0f);
    return kj_mat4f(
            1.0f / (tan_fovy * aspect),            0.0f,          0.0f,  0.0f,
                                  0.0f, 1.0f / tan_fovy,          0.0f,  0.0f,
                                  0.0f,            0.0f,         -1.0f, -1.0f,
                                  0.0f,            0.0f, -2.0f * znear,  0.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_look_at(kjVec3f eye, kjVec3f target, kjVec3f up) {
    kjVec3f f = kj_vec3f_normalise(kj_vec3f_sub(target, eye));
    kjVec3f r = kj_vec3f_normalise(kj_vec3f_cross(f, up));
    kjVec3f u = kj_vec3f_cross(r, f);
    return kj_mat4f(
                              r.x,                   u.x,                 -f.x, 0.0f,
                              r.y,                   u.y,                 -f.y, 0.0f,
                              r.z,                   u.z,                 -f.z, 0.0f,
            -kj_vec3f_dot(r, eye), -kj_vec3f_dot(u, eye), kj_vec3f_dot(f, eye), 1.0f);
}

KJ_FORCE_INLINE float kj_mat4f_determinant(kjMat4f a) {
    kjMat3f m0 = kj_mat3f(
            a.e[1][1], a.e[2][1], a.e[3][1],
            a.e[1][2], a.e[2][2], a.e[3][2],
            a.e[1][3], a.e[2][3], a.e[3][3]);
    kjMat3f m1 = kj_mat3f(
            a.e[0][1], a.e[2][1], a.e[3][1],
            a.e[0][2], a.e[2][2], a.e[3][2],
            a.e[0][3], a.e[2][3], a.e[3][3]);
    kjMat3f m2 = kj_mat3f(
            a.e[0][1], a.e[1][1], a.e[3][1],
            a.e[0][2], a.e[1][2], a.e[3][2],
            a.e[0][3], a.e[1][3], a.e[3][3]);
    kjMat3f m3 = kj_mat3f(
            a.e[0][1], a.e[1][1], a.e[2][1],
            a.e[0][2], a.e[1][2], a.e[2][2],
            a.e[0][3], a.e[1][3], a.e[2][3]);
    return
        a.e[0][0] * kj_mat3f_determinant(m0) -
        a.e[1][0] * kj_mat3f_determinant(m1) +
        a.e[2][0] * kj_mat3f_determinant(m2) -
        a.e[3][0] * kj_mat3f_determinant(m3);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_inverse(kjMat4f a) {
    float det = kj_mat4f_determinant(a);
    KJ_ASSERT(det != 0.0f);
    det = 1.0 / det;
    kjMat4f res;
    res.e[0][0] = (a.e[1][1] * a.e[2][2] * a.e[3][3] + a.e[3][1] * a.e[1][2] * a.e[2][3] + a.e[2][1] * a.e[3][2] * a.e[1][3] - a.e[1][1] * a.e[3][2] * a.e[2][3] - a.e[2][1] * a.e[1][2] * a.e[3][3] - a.e[3][1] * a.e[2][2] * a.e[1][3]) * det;
    res.e[0][1] = (a.e[0][1] * a.e[3][2] * a.e[2][3] + a.e[2][1] * a.e[0][2] * a.e[3][3] + a.e[3][1] * a.e[2][2] * a.e[0][3] - a.e[3][1] * a.e[0][2] * a.e[2][3] - a.e[2][1] * a.e[3][2] * a.e[0][3] - a.e[0][1] * a.e[2][2] * a.e[3][3]) * det;
    res.e[0][2] = (a.e[0][1] * a.e[1][2] * a.e[3][3] + a.e[3][1] * a.e[0][2] * a.e[1][3] + a.e[1][1] * a.e[3][2] * a.e[0][3] - a.e[0][1] * a.e[3][2] * a.e[1][3] - a.e[1][1] * a.e[0][2] * a.e[3][3] - a.e[3][1] * a.e[1][2] * a.e[0][3]) * det;
    res.e[0][3] = (a.e[0][1] * a.e[2][2] * a.e[1][3] + a.e[1][1] * a.e[0][2] * a.e[2][3] + a.e[2][1] * a.e[1][2] * a.e[0][3] - a.e[0][1] * a.e[1][2] * a.e[2][3] - a.e[2][1] * a.e[0][2] * a.e[1][3] - a.e[1][1] * a.e[2][2] * a.e[0][3]) * det;
    res.e[1][0] = (a.e[1][2] * a.e[3][3] * a.e[2][0] + a.e[2][2] * a.e[1][3] * a.e[3][0] + a.e[3][2] * a.e[2][3] * a.e[1][0] - a.e[1][2] * a.e[2][3] * a.e[3][0] - a.e[3][2] * a.e[1][3] * a.e[2][0] - a.e[2][2] * a.e[3][3] * a.e[1][0]) * det;
    res.e[1][1] = (a.e[0][2] * a.e[2][3] * a.e[3][0] + a.e[3][2] * a.e[0][3] * a.e[2][0] + a.e[2][2] * a.e[3][3] * a.e[0][0] - a.e[0][2] * a.e[3][3] * a.e[2][0] - a.e[2][2] * a.e[0][3] * a.e[3][0] - a.e[3][2] * a.e[2][3] * a.e[0][0]) * det;
    res.e[1][2] = (a.e[0][2] * a.e[3][3] * a.e[1][0] + a.e[1][2] * a.e[0][3] * a.e[3][0] + a.e[3][2] * a.e[1][3] * a.e[0][0] - a.e[0][2] * a.e[1][3] * a.e[3][0] - a.e[3][2] * a.e[0][3] * a.e[1][0] - a.e[1][2] * a.e[3][3] * a.e[0][0]) * det;
    res.e[1][3] = (a.e[0][2] * a.e[1][3] * a.e[2][0] + a.e[2][2] * a.e[0][3] * a.e[1][0] + a.e[1][2] * a.e[2][3] * a.e[0][0] - a.e[0][2] * a.e[2][3] * a.e[1][0] - a.e[1][2] * a.e[0][3] * a.e[2][0] - a.e[2][2] * a.e[1][3] * a.e[0][0]) * det;
    res.e[2][0] = (a.e[1][3] * a.e[2][0] * a.e[3][1] + a.e[3][3] * a.e[1][0] * a.e[2][1] + a.e[2][3] * a.e[3][0] * a.e[1][1] - a.e[1][3] * a.e[3][0] * a.e[2][1] - a.e[2][3] * a.e[1][0] * a.e[3][1] - a.e[3][3] * a.e[2][0] * a.e[1][1]) * det;
    res.e[2][1] = (a.e[0][3] * a.e[3][0] * a.e[2][1] + a.e[2][3] * a.e[0][0] * a.e[3][1] + a.e[3][3] * a.e[2][0] * a.e[0][1] - a.e[0][3] * a.e[2][0] * a.e[3][1] - a.e[3][3] * a.e[0][0] * a.e[2][1] - a.e[2][3] * a.e[3][0] * a.e[0][1]) * det;
    res.e[2][2] = (a.e[0][3] * a.e[1][0] * a.e[3][1] + a.e[3][3] * a.e[0][0] * a.e[1][1] + a.e[1][3] * a.e[3][0] * a.e[0][1] - a.e[0][3] * a.e[3][0] * a.e[1][1] - a.e[1][3] * a.e[0][0] * a.e[3][1] - a.e[3][3] * a.e[1][0] * a.e[0][1]) * det;
    res.e[2][3] = (a.e[0][3] * a.e[2][0] * a.e[1][1] + a.e[1][3] * a.e[0][0] * a.e[2][1] + a.e[2][3] * a.e[1][0] * a.e[0][1] - a.e[0][3] * a.e[1][0] * a.e[2][1] - a.e[2][3] * a.e[0][0] * a.e[1][1] - a.e[1][3] * a.e[2][0] * a.e[0][1]) * det;
    res.e[3][0] = (a.e[1][0] * a.e[3][1] * a.e[2][2] + a.e[2][0] * a.e[1][1] * a.e[3][2] + a.e[3][0] * a.e[2][1] * a.e[1][2] - a.e[1][0] * a.e[2][1] * a.e[3][2] - a.e[3][0] * a.e[1][1] * a.e[2][2] - a.e[2][0] * a.e[3][1] * a.e[1][2]) * det;
    res.e[3][1] = (a.e[0][0] * a.e[2][1] * a.e[3][2] + a.e[3][0] * a.e[0][1] * a.e[2][2] + a.e[2][0] * a.e[3][1] * a.e[0][2] - a.e[0][0] * a.e[3][1] * a.e[2][2] - a.e[2][0] * a.e[0][1] * a.e[3][2] - a.e[3][0] * a.e[2][1] * a.e[0][2]) * det;
    res.e[3][2] = (a.e[0][0] * a.e[3][1] * a.e[1][2] + a.e[1][0] * a.e[0][1] * a.e[3][2] + a.e[3][0] * a.e[1][1] * a.e[0][2] - a.e[0][0] * a.e[1][1] * a.e[3][2] - a.e[3][0] * a.e[0][1] * a.e[1][2] - a.e[1][0] * a.e[3][1] * a.e[0][2]) * det;
    res.e[3][3] = (a.e[0][0] * a.e[1][1] * a.e[2][2] + a.e[2][0] * a.e[0][1] * a.e[1][2] + a.e[1][0] * a.e[2][1] * a.e[0][2] - a.e[0][0] * a.e[2][1] * a.e[1][2] - a.e[1][0] * a.e[0][1] * a.e[2][2] - a.e[2][0] * a.e[1][1] * a.e[0][2]) * det;
    return res;
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_from_quatf(kjQuatf q) {
    kjQuatf nq = kj_quatf_normalise(q);
    float xx = nq.x * nq.x;
    float yy = nq.y * nq.y;
    float zz = nq.z * nq.z;
    float xz = nq.x * nq.z;
    float xy = nq.x * nq.y;
    float yz = nq.y * nq.z;
    float wx = nq.w * nq.x;
    float wy = nq.w * nq.y;
    float wz = nq.w * nq.z;
    return kj_mat4f(
            1.0f - 2.0f * (yy + zz),        2.0f * (xy + wz),        2.0f * (xz - wy), 0.0f,
                   2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz),        2.0f * (yz + wx), 0.0f,
                   2.0f * (xz + wy),        2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy), 0.0f,
                               0.0f,                    0.0f,                    0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_from_transform(kjVec3f translate, kjQuatf rotate, kjVec3f scale) {
    kjMat4f res = kj_mat4f_from_quatf(rotate);
    res.e[3][0] = translate.x;
    res.e[3][1] = translate.y;
    res.e[3][2] = translate.z;
    res.e[0][0] *= scale.x;
    res.e[0][1] *= scale.x;
    res.e[0][2] *= scale.x;
    res.e[1][0] *= scale.y;
    res.e[1][1] *= scale.y;
    res.e[1][2] *= scale.y;
    res.e[2][0] *= scale.z;
    res.e[2][1] *= scale.z;
    res.e[2][2] *= scale.z;
    return res;
}

KJ_MATH_API kjMat4f kj_mat4f(
        float c0r0, float c0r1, float c0r2, float c0r3,
        float c1r0, float c1r1, float c1r2, float c1r3,
        float c2r0, float c2r1, float c2r2, float c2r3,
        float c3r0, float c3r1, float c3r2, float c3r3);

#if defined(__cplusplus)
KJ_FORCE_INLINE kjVec2f kj_vec2f(void) {
    return kj_vec2f_all(0.0f);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f(float a) {
    return kj_vec2f_all(a);
}

KJ_FORCE_INLINE kjVec2f operator+(kjVec2f a, kjVec2f b) {
    return kj_vec2f_add(a, b);
}

KJ_FORCE_INLINE kjVec2f operator+(kjVec2f a, float b) {
    return kj_vec2f_addf(a, b);
}

KJ_FORCE_INLINE kjVec2f operator-(kjVec2f a, kjVec2f b) {
    return kj_vec2f_sub(a, b);
}

KJ_FORCE_INLINE kjVec2f operator-(kjVec2f a, float b) {
    return kj_vec2f_subf(a, b);
}

KJ_FORCE_INLINE kjVec2f operator*(kjVec2f a, kjVec2f b) {
    return kj_vec2f_mul(a, b);
}

KJ_FORCE_INLINE kjVec2f operator*(kjVec2f a, float b) {
    return kj_vec2f_mulf(a, b);
}

KJ_FORCE_INLINE kjVec2f operator/(kjVec2f a, kjVec2f b) {
    return kj_vec2f_div(a, b);
}

KJ_FORCE_INLINE kjVec2f operator/(kjVec2f a, float b) {
    return kj_vec2f_divf(a, b);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f(void) {
    return kj_vec3f_all(0.0f);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f(float a) {
    return kj_vec3f_all(a);
}

KJ_FORCE_INLINE kjVec3f operator+(kjVec3f a, kjVec3f b) {
    return kj_vec3f_add(a, b);
}

KJ_FORCE_INLINE kjVec3f operator+(kjVec3f a, float b) {
    return kj_vec3f_addf(a, b);
}

KJ_FORCE_INLINE kjVec3f operator-(kjVec3f a, kjVec3f b) {
    return kj_vec3f_sub(a, b);
}

KJ_FORCE_INLINE kjVec3f operator-(kjVec3f a, float b) {
    return kj_vec3f_subf(a, b);
}

KJ_FORCE_INLINE kjVec3f operator*(kjVec3f a, kjVec3f b) {
    return kj_vec3f_mul(a, b);
}

KJ_FORCE_INLINE kjVec3f operator*(kjVec3f a, float b) {
    return kj_vec3f_mulf(a, b);
}

KJ_FORCE_INLINE kjVec3f operator/(kjVec3f a, kjVec3f b) {
    return kj_vec3f_div(a, b);
}

KJ_FORCE_INLINE kjVec3f operator/(kjVec3f a, float b) {
    return kj_vec3f_divf(a, b);
}

KJ_FORCE_INLINE kjVec4f kj_vec4f(void) {
    return kj_vec4f_all(0.0f);
}

KJ_FORCE_INLINE kjVec4f kj_vec4f(float a) {
    return kj_vec4f_all(a);
}

KJ_FORCE_INLINE kjVec4f operator+(kjVec4f a, kjVec4f b) {
    return kj_vec4f_add(a, b);
}

KJ_FORCE_INLINE kjVec4f operator+(kjVec4f a, float b) {
    return kj_vec4f_addf(a, b);
}

KJ_FORCE_INLINE kjVec4f operator-(kjVec4f a, kjVec4f b) {
    return kj_vec4f_sub(a, b);
}

KJ_FORCE_INLINE kjVec4f operator-(kjVec4f a, float b) {
    return kj_vec4f_subf(a, b);
}

KJ_FORCE_INLINE kjVec4f operator*(kjVec4f a, kjVec4f b) {
    return kj_vec4f_mul(a, b);
}

KJ_FORCE_INLINE kjVec4f operator*(kjVec4f a, float b) {
    return kj_vec4f_mulf(a, b);
}

KJ_FORCE_INLINE kjVec4f operator/(kjVec4f a, kjVec4f b) {
    return kj_vec4f_div(a, b);
}

KJ_FORCE_INLINE kjVec4f operator/(kjVec4f a, float b) {
    return kj_vec4f_divf(a, b);
}

KJ_FORCE_INLINE kjVec3f operator*(kjQuatf q, kjVec3f v) {
    return kj_quatf_mul_vec3f(q, v);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f(float e00, float e11, float e22) {
    return kj_mat3f_diagonal(e00, e11, e22);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f(void) {
    return kj_mat3f_identity();
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate(float radians, kjVec3f xyz) {
    return kj_mat3f_rotate_vec3f(radians, xyz);
}

KJ_FORCE_INLINE kjMat3f operator*(kjMat3f a, kjMat3f b) {
    return kj_mat3f_mul(a, b);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f(float e00, float e11, float e22, float e33) {
    return kj_mat4f_diagonal(e00, e11, e22, e33);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f(void) {
    return kj_mat4f_identity();
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_translate(kjVec3f xyz) {
    return kj_mat4f_translate_vec3f(xyz);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate(float radians, kjVec3f xyz) {
    return kj_mat4f_rotate_vec3f(radians, xyz);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scale(float a) {
    return kj_mat4f_scalef(a);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scale(kjVec3f xyz) {
    return kj_mat4f_scale_vec3f(xyz);
}

KJ_FORCE_INLINE kjMat4f operator*(kjMat4f a, kjMat4f b) {
    return kj_mat4f_mul(a, b);
}
#endif

KJ_FORCE_INLINE kjVec2f kj_aabb2d_half_extents(kjVec2f min, kjVec2f max) {
    return kj_vec2f_mulf(kj_vec2f_sub(max, min), 0.5f);
}

KJ_FORCE_INLINE kjVec2f kj_aabb2d_midpoint(kjVec2f min, kjVec2f max) {
    return kj_vec2f_mulf(kj_vec2f_add(min, max), 0.5f);
}

KJ_FORCE_INLINE kjVec2f kj_aabb2d_top_left(kjVec2f min, kjVec2f max) {
    (void) max;
    return min;
}

KJ_FORCE_INLINE kjVec2f kj_aabb2d_top_right(kjVec2f min, kjVec2f max) {
    return kj_vec2f(max.x, min.y);
}

KJ_FORCE_INLINE kjVec2f kj_aabb2d_bottom_left(kjVec2f min, kjVec2f max) {
    return kj_vec2f(min.x, max.y);
}

KJ_FORCE_INLINE kjVec2f kj_aabb2d_bottom_right(kjVec2f min, kjVec2f max) {
    (void) min;
    return max;
}

KJ_FORCE_INLINE bool kj_triangle2d_contains_point(kjVec2f p, kjVec2f a, kjVec2f b, kjVec2f c) {
    bool b1 = ((p.x - b.x) * (a.y - b.y) - (p.y - b.y) * (a.x - b.x)) < 0.0f;
    bool b2 = ((p.x - c.x) * (b.y - c.y) - (p.y - c.y) * (b.x - c.x)) < 0.0f;
    bool b3 = ((p.x - a.x) * (c.y - a.y) - (p.y - a.y) * (c.x - a.x)) < 0.0f;
    return b1 == b2 && b2 == b3;
}

KJ_FORCE_INLINE float kj_segment2d_point_side(kjVec2f a, kjVec2f b, kjVec2f p) {
    return kj_vec2f_perp_dot(kj_vec2f_sub(a, b), kj_vec2f_sub(a, p));
}

KJ_FORCE_INLINE kjVec2f kj_segment2d_midpoint(kjVec2f a, kjVec2f b) {
    return kj_vec2f_mulf(kj_vec2f_add(a, b), 0.5f);
}

KJ_FORCE_INLINE kjVec2f kj_segment2d_nearest_point(kjVec2f a, kjVec2f b, kjVec2f p) {
    kjVec2f pa = kj_vec2f_sub(p, a);
    kjVec2f ba = kj_vec2f_sub(b, a);
    float length = 1.0f / kj_vec2f_length_sq(ba);
    return kj_vec2f_add(a, kj_vec2f_mulf(ba, kj_clamp01f(kj_vec2f_dot(pa, ba) * length)));
}

KJ_FORCE_INLINE float kj_segment2d_distance_sq_to_point(kjVec2f a, kjVec2f b, kjVec2f p) {
    return kj_vec2f_distance_sq(p, kj_segment2d_nearest_point(a, b, p));
}

KJ_FORCE_INLINE float kj_segment2d_distance_to_point(kjVec2f a, kjVec2f b, kjVec2f p) {
    return kj_sqrtf(kj_segment2d_distance_sq_to_point(a, b, p));
}

KJ_FORCE_INLINE void kj_segment2d_nearest_segment(kjVec2f* a, kjVec2f* b, kjVec2f a0, kjVec2f b0, kjVec2f a1, kjVec2f b1) {
    kjVec2f b0a0 = kj_vec2f_sub(b0, a0);
    kjVec2f b1a1 = kj_vec2f_sub(b1, a1);
    kjVec2f a0a1 = kj_vec2f_sub(a0, a1);

    float d0 = kj_vec2f_dot(b1a1, a0a1);
    float d1 = kj_vec2f_dot(b0a0, a0a1);
    float d2 = kj_vec2f_dot(b0a0, b1a1);
    float lb0a0 = kj_vec2f_length_sq(b0a0);
    float lb1a1 = kj_vec2f_length_sq(b1a1);

    float denom = lb0a0 * lb1a1 - d2 * d2;
    float m0 = denom != 0.0f ? kj_clamp01f((d2 * d0 - d1 * lb1a1) / denom): 0.0f;
    float m1 = (d2 * (m0) + d0) / lb1a1;
    if (m1 < 0.0f) {
        m0 = kj_clamp01f(-d1 / lb0a0);
    } else if (m1 > 1.0f) {
        m0 = kj_clamp01f((d2 - d1) / lb0a0);
    }
    m1 = kj_clamp01f(m1);
    *a = kj_vec2f_add(kj_vec2f_mulf(b0a0, m0), a0);
    *b = kj_vec2f_add(kj_vec2f_mulf(b1a1, m1), a1);
}

KJ_FORCE_INLINE kjVec2f kj_arc2d_nearest_point(kjVec2f centre, float radius, float radians, kjVec2f p) {
    if(radians >= KJ_TAU) { return kj_circle_nearest_point(centre, radius, p); }
    kjVec2f cp = kj_vec2f_normalise(kj_vec2f_sub(centre, p));
    float a = kj_radian_clampf(kj_atan2f(cp.y, cp.x) + KJ_PI, 0.0f, radians);
    return kj_vec2f_add(centre, kj_vec2f_mulf(kj_vec2f(kj_cosf(a), kj_sinf(a)), radius));
}

KJ_FORCE_INLINE float kj_arc2d_distance_sq_to_point(kjVec2f centre, float radius, float radians, kjVec2f p) {
    return kj_vec2f_distance_sq(p, kj_arc2d_nearest_point(centre, radians, radius, p));
}

KJ_FORCE_INLINE float kj_arc2d_distance_to_point(kjVec2f centre, float radius, float radians, kjVec2f p) {
    return kj_sqrtf(kj_arc2d_distance_sq_to_point(centre, radians, radius, p));
}

KJ_FORCE_INLINE kjVec2f kj_circle_nearest_point(kjVec2f centre, float radius, kjVec2f p) {
    return kj_vec2f_add(centre, kj_vec2f_mulf(kj_vec2f_normalise(kj_vec2f_sub(p, centre)), radius));
}

KJ_FORCE_INLINE float kj_circle_distance_sq_to_point(kjVec2f centre, float radius, kjVec2f p) {
    return kj_vec2f_distance_sq(centre, p) - radius;
}

KJ_FORCE_INLINE float kj_circle_distance_to_point(kjVec2f centre, float radius, kjVec2f p) {
    return kj_vec2f_distance(centre, p) - radius;
}

KJ_FORCE_INLINE kjVec2f kj_aabb2d_nearest_point(kjVec2f min, kjVec2f max, kjVec2f p) {
    p.x = kj_maxf(p.x, min.x);
    p.y = kj_maxf(p.y, min.y);
    p.x = kj_minf(p.x, max.x);
    p.y = kj_minf(p.y, max.y);
    return p;
}

KJ_FORCE_INLINE float kj_aabb2d_distance_sq_to_point(kjVec2f min, kjVec2f max, kjVec2f p) {
    return kj_vec2f_distance_sq(p, kj_aabb2d_nearest_point(min, max, p));
}

KJ_FORCE_INLINE float kj_aabb2d_distance_to_point(kjVec2f min, kjVec2f max, kjVec2f p) {
    return kj_sqrtf(kj_aabb2d_distance_sq_to_point(min, max, p));
}

KJ_FORCE_INLINE kjVec2f kj_capsule2d_nearest_point(kjVec2f a, kjVec2f b, float r, kjVec2f p) {
    kjVec2f np = kj_segment2d_nearest_point(a, b, p);
    return kj_vec2f_add(np, kj_vec2f_mulf(kj_vec2f_normalise(kj_vec2f_sub(p, np)), r));
}

KJ_FORCE_INLINE float kj_capsule2d_distance_sq_to_point(kjVec2f a, kjVec2f b, float r, kjVec2f p) {
    return kj_vec2f_distance_sq(p, kj_capsule2d_nearest_point(a, b, r, p));
}

KJ_FORCE_INLINE float kj_capsule2d_distance_to_point(kjVec2f a, kjVec2f b, float r, kjVec2f p) {
    return kj_sqrtf(kj_capsule2d_distance_sq_to_point(a, b, r, p));
}

KJ_FORCE_INLINE bool kj_intersect2d_segment_segment(kjVec2f a0, kjVec2f a1, kjVec2f b0, kjVec2f b1) {
    float d = ((b1.y - b0.y) * (a1.x - a0.x) - (b1.x - b0.x) * (a1.y - a0.y));
    if(kj_float32_eq(d, 0.0f, KJ_FLOAT32_EPS)) { return false; }
    d = 1.0f / d;
    float ua = ((b1.x - b0.x) * (a0.y - b0.y) - (b1.y - b0.y) * (a0.x - b0.x)) * d;
    float ub = ((a1.x - a0.x) * (a0.y - b0.y) - (a1.y - a0.y) * (a0.x - b0.x)) * d;
    return (ua >= 0.0f && ua <= 1.0f) && (ub >= 0.0f && ub <= 1.0f);
}

KJ_FORCE_INLINE bool kj_intersect2d_aabb_point(kjVec2f min, kjVec2f max, kjVec2f p) {
    return p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y;
}

KJ_FORCE_INLINE bool kj_intersect2d_point_aabb(kjVec2f p, kjVec2f min, kjVec2f max) {
    return kj_intersect2d_aabb_point(min, max, p);
}

KJ_FORCE_INLINE bool kj_intersect2d_aabb_aabb(kjVec2f a_min, kjVec2f a_max, kjVec2f b_min, kjVec2f b_max) {
    return !(b_max.x < a_min.x | a_max.x < b_min.x | b_max.y < a_min.y | a_max.y < b_min.y);
}

KJ_FORCE_INLINE bool kj_intersect2d_aabb_circle(kjVec2f a_min, kjVec2f a_max, kjVec2f centre, float radius) {
    return kj_intersect2d_circle_aabb(centre, radius, a_min, a_max);
}

KJ_FORCE_INLINE bool kj_intersect2d_circle_point(kjVec2f centre, float radius, kjVec2f p) {
    return kj_vec2f_distance_sq(centre, p) < (radius * radius);
}

KJ_FORCE_INLINE bool kj_intersect2d_point_circle(kjVec2f p, kjVec2f centre, float radius) {
    return kj_intersect2d_circle_point(centre, radius, p);
}

KJ_FORCE_INLINE bool kj_intersect2d_circle_aabb(kjVec2f centre, float radius, kjVec2f b_min, kjVec2f b_max) {
    return kj_vec2f_length_sq(kj_vec2f_sub(centre, kj_vec2f_clamp(centre, b_min, b_max))) < (radius * radius);
}

KJ_FORCE_INLINE bool kj_intersect2d_circle_circle(kjVec2f c0, float r0, kjVec2f c1, float r1) {
    kjVec2f xy = kj_vec2f_sub(c0, c1);
    xy = kj_vec2f_mul(xy, xy);
    float r = r0 + r1;
    r *= r;
    return xy.x + xy.y < r;
}

KJ_FORCE_INLINE bool kj_intersect2d_capsule_capsule(kjVec2f a0, kjVec2f b0, float r0, kjVec2f a1, kjVec2f b1, float r1) {
    kjVec2f a, b;
    kj_segment2d_nearest_segment(&a, &b, a0, b0, a1, b1);
    float r = r0 + r1;
    r *= r;
    return kj_vec2f_distance_sq(a, b) < r;
}

KJ_FORCE_INLINE bool kj_intersect2d_capsule_circle(kjVec2f a, kjVec2f b, float r, kjVec2f centre, float radius) {
    r = r + radius;
    r *= r;
    return kj_segment2d_distance_sq_to_point(a, b, centre) < r;
}

KJ_FORCE_INLINE bool kj_intersect2d_circle_capsule(kjVec2f centre, float radius, kjVec2f a, kjVec2f b, float r) {
    return kj_intersect2d_capsule_circle(a, b, r, centre, radius);
}

KJ_FORCE_INLINE bool kj_intersect2d_capsule_aabb(kjVec2f a, kjVec2f b, float r, kjVec2f min, kjVec2f max) {
    kjVec2f c = kj_aabb2d_midpoint(min, max);
    return kj_intersect2d_aabb_point(min, max, kj_capsule2d_nearest_point(a, b, r, c));
}

KJ_FORCE_INLINE bool kj_intersect2d_aabb_capsule(kjVec2f min, kjVec2f max, kjVec2f a, kjVec2f b, float r) {
    return kj_intersect2d_capsule_aabb(a, b, r, min, max);
}

KJ_FORCE_INLINE uint32_t kj_contact2d_segment_segment(kjVec2f* contact, kjVec2f a0, kjVec2f a1, kjVec2f b0, kjVec2f b1) {
    float d = ((b1.y - b0.y) * (a1.x - a0.x) - (b1.x - b0.x) * (a1.y - a0.y));
    if(kj_float32_eq(d, 0.0f, KJ_FLOAT32_EPS)) { return 0; }
    d = 1.0f / d;
    float ua = ((b1.x - b0.x) * (a0.y - b0.y) - (b1.y - b0.y) * (a0.x - b0.x)) * d;
    float ub = ((a1.x - a0.x) * (a0.y - b0.y) - (a1.y - a0.y) * (a0.x - b0.x)) * d;
    *contact = kj_vec2f_add(a0, kj_vec2f_mulf(kj_vec2f_sub(a1, a0), ua));
    return (ua >= 0.0f && ua <= 1.0f) && (ub >= 0.0f && ub <= 1.0f);
}

KJ_FORCE_INLINE uint32_t kj_contact2d_circle_circle(kjContact2d* contact, kjVec2f c0, float r0, kjVec2f c1, float r1) {
    float r = r0 + r1;
    kjVec2f c1c0 = kj_vec2f_sub(c1, c0);
    float d2 = kj_vec2f_length_sq(c1c0);
    if(d2 < (r * r)) {
        float d = kj_sqrtf(d2);
        contact->normal = kj_vec2f_mulf(c1c0, 1.0f / d);
        contact->depths[0] = r - d;
        contact->contacts[0] = kj_vec2f_sub(c1, kj_vec2f_mulf(contact->normal, r1));
        return 1;
    }
    return 0;
}

KJ_FORCE_INLINE uint32_t kj_contact2d_circle_aabb(kjContact2d* contact, kjVec2f centre, float radius, kjVec2f min, kjVec2f max) {
    if(kj_intersect2d_aabb_point(min, max, centre)) {
        kjVec2f n = kj_vec2f_sub(centre, kj_aabb2d_midpoint(min, max));
        kjVec2f abs_n = kj_vec2f_abs(n);
        if(abs_n.x > abs_n.y) {
            contact->normal = kj_vec2f(kj_signf(n.x), 0.0f);
            contact->contacts[0] = kj_vec2f(n.x < 0.0f ? min.x: max.x, centre.y);
            contact->depths[0] = radius + (max.x - min.x) * 0.5f - abs_n.x;
            return 1;
        } else {
            contact->normal = kj_vec2f(0.0f, kj_signf(n.y));
            contact->contacts[0] = kj_vec2f(centre.x, n.y < 0.0f ? min.y: max.y);
            contact->depths[0] = radius + (max.y - min.y) * 0.5f - abs_n.y;
            return 1;
        }
    }
    kjVec2f n = kj_vec2f_sub(kj_vec2f_clamp(centre, min, max), centre);
    float d = kj_vec2f_length(n);
    contact->normal = kj_vec2f_mulf(n, 1.0f / -d);
    contact->contacts[0] = kj_vec2f_add(centre, n);
    contact->depths[0] = radius - d;
    return contact->depths[0] > 0.0f ? 1: 0;
}

KJ_FORCE_INLINE uint32_t kj_contact2d_aabb_circle(kjContact2d* contact, kjVec2f min, kjVec2f max, kjVec2f centre, float radius) {
    return kj_contact2d_circle_aabb(contact, centre, radius, min, max);
}

KJ_FORCE_INLINE uint32_t kj_contact2d_aabb_aabb(kjContact2d* contact, kjVec2f min_a, kjVec2f max_a, kjVec2f min_b, kjVec2f max_b) {
    kjVec2f mid_a = kj_segment2d_midpoint(min_a, max_a);
    kjVec2f mid_b = kj_segment2d_midpoint(min_b, max_b);
    kjVec2f a = kj_vec2f_abs(kj_vec2f_mulf(kj_vec2f_sub(max_a, min_a), 0.5f));
    kjVec2f b = kj_vec2f_abs(kj_vec2f_mulf(kj_vec2f_sub(max_b, min_b), 0.5f));
    kjVec2f d = kj_vec2f_sub(mid_b, mid_a);
    float dx = a.x + b.x - kj_absf(d.x);
    float dy = a.y + b.y - kj_absf(d.y);
    if(dx < 0.0f || dy < 0.0f) {
        return 0;
    } else if(dx < dy) {
        contact->depths[0] = dx;
        contact->normal = kj_vec2f(kj_signf(d.x), 0.0f);
        contact->contacts[0] = kj_vec2f_sub(mid_a, kj_vec2f(a.x, 0.0f));
        return 1;
    } else {
        contact->depths[0] = dy;
        contact->normal = kj_vec2f(0.0f, kj_signf(d.y));
        contact->contacts[0] = kj_vec2f_sub(mid_a, kj_vec2f(0.0f, a.y));
        return 1;
    }
}

KJ_FORCE_INLINE uint32_t kj_contact2d_capsule_capsule(kjContact2d* contact, kjVec2f a0, kjVec2f b0, float r0, kjVec2f a1, kjVec2f b1, float r1) {
    kjVec2f a, b;
    kj_segment2d_nearest_segment(&a, &b, a0, b0, a1, b1);
    float r = r0 + r1;
    r *= r;
    if(kj_vec2f_distance_sq(a, b) < r && !kj_intersect2d_segment_segment(a0, b0, a1, b1)) {
#if 0
        kjVec2f i;
        if(kj_contact2d_segment_segment(&i, a0, b0, a1, b1)) {
            kjRaycast2d raycast;
            if(kj_raycast2d_circle(&raycast, b1, a1, i, r1)) {
                contact->contacts[0] = raycast.pos;
                contact->normal = kj_vec2f_normalise((kj_vec2f_sub(b1, a1)));
                contact->depths[0] = kj_vec2f_distance(raycast.pos, a1);
            } else {
                return 0;
            }
        } else {
#endif
        contact->normal = kj_vec2f_normalise(kj_vec2f_sub(b, a));
        contact->depths[0] = kj_vec2f_length(kj_vec2f_sub(a, kj_capsule2d_nearest_point(a1, b1, r1, a)));
        contact->contacts[0] = kj_capsule2d_nearest_point(a0, b0, r0, b);
#if 0
        }
#endif
        return 1;
    }
    return 0;
}

KJ_FORCE_INLINE uint32_t kj_contact2d_capsule_circle(kjContact2d* contact, kjVec2f a, kjVec2f b, float r, kjVec2f centre, float radius) {
    kjVec2f np = kj_capsule2d_nearest_point(a, b, r, centre);
    kjVec2f n = kj_vec2f_sub(centre, np);
    float d2 = kj_vec2f_length_sq(n);
    float r2 = radius * radius;
    if(d2 < r2) {
        float d = d2 != 0.0f ? kj_sqrtf(d2): 1.0f;
        contact->depths[0] = d;
        contact->normal = kj_vec2f_mulf(n, 1.0f / d);
        contact->contacts[0] = np;
        return 1;
    }
    return 0;
}

KJ_FORCE_INLINE uint32_t kj_contact2d_circle_capsule(kjContact2d* contact, kjVec2f centre, float radius, kjVec2f a, kjVec2f b, float r) {
    return kj_contact2d_capsule_circle(contact, a, b, r, centre, radius);
}

KJ_FORCE_INLINE uint32_t kj_contact2d_capsule_aabb(kjContact2d* contact, kjVec2f a, kjVec2f b, float r, kjVec2f min, kjVec2f max) {
    kjVec2f c = kj_aabb2d_midpoint(min, max);
    kjVec2f np = kj_capsule2d_nearest_point(a, b, r, c);
    if(kj_intersect2d_aabb_point(min, max, np)) {
        kjVec2f d = kj_vec2f_sub(c, np);
        kjVec2f anp = kj_aabb2d_nearest_point(min, max, np);
        kjVec2f dir2 = kj_vec2f_sub(anp, c);
        float depth = kj_vec2f_length1(dir2);
        contact->depths[0] = depth;
        contact->normal = kj_vec2f_mulf(d, 1.0f / depth);
        contact->contacts[0] = np;
        return 1;
    }
    return 0;
}

KJ_FORCE_INLINE uint32_t kj_contact2d_aabb_capsule(kjContact2d* contact, kjVec2f min, kjVec2f max, kjVec2f a, kjVec2f b, float r) {
    return kj_contact2d_capsule_aabb(contact, a, b, r, min, max);
}

KJ_FORCE_INLINE bool kj_raycast2d_ray_aabb(kjRaycast2d* raycast, kjRay2d ray, kjVec2f min, kjVec2f max) {
    KJ_ASSERT(kj_vec2f_is_normalised(ray.dir));
    kjVec2f inv = kj_vec2f(1.0f / ray.dir.x, 1.0f / ray.dir.y);
    kjVec2f d0 = kj_vec2f_mul(kj_vec2f_sub(min, ray.pos), inv);
    kjVec2f d1 = kj_vec2f_mul(kj_vec2f_sub(max, ray.pos), inv);
    float vmin = kj_vec2f_hmax(kj_vec2f_min(d0, d1));
    float vmax = kj_vec2f_hmin(kj_vec2f_max(d0, d1));
    kjVec2f pos = kj_vec2f_add(ray.pos, kj_vec2f_mulf(ray.dir, vmin));
    kjVec2f c = kj_vec2f_sub(pos, kj_segment2d_midpoint(min, max));
    kjVec2f abs_c = kj_vec2f_abs(c);
    raycast->pos = pos;
    raycast->normal = abs_c.x > abs_c.y ? kj_vec2f(kj_signf(c.x), 0.0f): kj_vec2f(0.0f, kj_signf(c.y));
    raycast->t = vmin;
    return vmax >= 0.0f && vmax >= vmin && vmin <= ray.t;
}

KJ_FORCE_INLINE bool kj_raycast2d_ray_circle(kjRaycast2d* raycast, kjRay2d ray, kjVec2f centre, float radius) {
    KJ_ASSERT(kj_vec2f_is_normalised(ray.dir));
    kjVec2f rc = kj_vec2f_sub(ray.pos, centre);
    float c = kj_vec2f_length_sq(rc) - (radius * radius);
    float d = kj_vec2f_dot(rc, ray.dir);
    float dist = (d * d) - c;
    float t = -d - kj_sqrtf(dist);
    kjVec2f pos = kj_vec2f_add(ray.pos, kj_vec2f_mulf(ray.dir, t));
    raycast->pos = pos;
    raycast->normal = kj_vec2f_normalise(kj_vec2f_sub(pos, centre));
    raycast->t = t;
    return dist > 0.0f && (t >= 0.0f && t <= ray.t);
}

KJ_FORCE_INLINE bool kj_raycast2d_aabb(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f min, kjVec2f max) {
    kjVec2f dir = kj_vec2f_sub(to, from);
    float length = kj_vec2f_length(dir);
    KJ_ASSERT(length > 0.0f);
    kjRay2d ray;
    ray.pos = from;
    ray.dir = kj_vec2f_mulf(dir, 1.0f / length);
    ray.t = length;
    return kj_raycast2d_ray_aabb(raycast, ray, min, max);
}

KJ_FORCE_INLINE bool kj_raycast2d_circle(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f centre, float radius) {
    kjVec2f dir = kj_vec2f_sub(to, from);
    float length = kj_vec2f_length(dir);
    KJ_ASSERT(length > 0.0f);
    kjRay2d ray;
    ray.pos = from;
    ray.dir = kj_vec2f_mulf(dir, 1.0f / length);
    ray.t = length;
    return kj_raycast2d_ray_circle(raycast, ray, centre, radius);
}

KJ_FORCE_INLINE void kj_bounds2d_aabb_circle(kjVec2f* min, kjVec2f* max, kjVec2f centre, float radius) {
    *min = kj_vec2f_subf(centre, radius);
    *max = kj_vec2f_addf(centre, radius);
}

KJ_FORCE_INLINE void kj_bounds2d_circle_aabb(kjVec2f* centre, float* radius, kjVec2f min, kjVec2f max) {
    kjVec2f extents = kj_vec2f_sub(max, min);
    *centre = kj_vec2f_add(min, kj_vec2f_mulf(extents, 0.5f));
    *radius = kj_vec2f_length(extents);
}

KJ_FORCE_INLINE void kj_bounds2d_aabb_points(kjVec2f* min, kjVec2f* max, kjVec2f* points, uint32_t count) {
    kjVec2f tmp_min = kj_vec2f_all(KJ_FLOAT32_MAX);
    kjVec2f tmp_max = kj_vec2f_all(KJ_FLOAT32_MIN);
    for(uint32_t i = 0; i < count; i++) {
        kjVec2f p = points[i];
        tmp_min = kj_vec2f_min(tmp_min, p);
        tmp_max = kj_vec2f_max(tmp_max, p);
    }
    *min = tmp_min;
    *max = tmp_max;
}

KJ_FORCE_INLINE void kj_bounds2d_circle_with_centre_points(kjVec2f* centre, float* radius, kjVec2f* points, uint32_t count, kjVec2f c) {
    float r = 0.0f;
    for(uint32_t i = 0; i < count; i++) {
        float d = kj_vec2f_distance_sq(points[i], c);
        if(d > r) {
            r = d;
        }
    }
    *centre = c;
    *radius = kj_sqrtf(r);
}

KJ_FORCE_INLINE void kj_bounds2d_circle_points(kjVec2f* centre, float* radius, kjVec2f* points, uint32_t count) {
    kjVec2f c = kj_vec2f_zero();
    for(uint32_t i = 0; i < count; i++) {
        c = kj_vec2f_add(c, points[i]);
    }
    c = kj_vec2f_divf(c, count);
    kj_bounds2d_circle_with_centre_points(centre, radius, points, count, c);
}

KJ_FORCE_INLINE uint32_t kj_triangulate_fan(uint32_t* triangles, uint32_t count) {
    KJ_ASSERT(triangles != NULL);
    for(uint32_t i = 0; i < count - 2; i++) {
        triangles[i * 3 + 0] = 0;
        triangles[i * 3 + 1] = i + 1;
        triangles[i * 3 + 2] = i + 2;
    }
    return count * 3 - 2;
}

uint32_t kj_bounds2d_polygon_points(uint32_t* hull, kjVec2f* points, uint32_t count) {
    KJ_ASSERT(hull != NULL);
    KJ_ASSERT(points != NULL);
    KJ_ASSERT(count > 0);
    uint32_t res = 0;
    for(uint64_t i = 0; i < count; i++) {
        while(res >= 2 && kj_segment2d_point_side(points[hull[res - 2]], points[hull[res - 1]], points[i]) <= 0.0f) {
            res--;
        }
        hull[res++] = i;
    }

    for(int64_t i = count - 2, j = res + 1; i >= 0; i--) {
        while(res >= j && kj_segment2d_point_side(points[hull[res - 2]], points[hull[res - 1]], points[i]) <= 0.0f) {
            res--;
        }
        hull[res++] = i;
    }

    return res;
}

KJ_FORCE_INLINE bool kj_intersect_aabb_point(kjVec3f min, kjVec3f max, kjVec3f p) {
    return p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y && p.z >= min.z && p.z <= max.z;
}

KJ_FORCE_INLINE bool kj_intersect_point_aabb(kjVec3f p, kjVec3f min, kjVec3f max) {
    return kj_intersect_aabb_point(min, max, p);
}

KJ_FORCE_INLINE bool kj_intersect_sphere_point(kjVec3f centre, float radius, kjVec3f p) {
    return kj_vec3f_distance_sq(centre, p) < (radius * radius);
}

KJ_FORCE_INLINE bool kj_intersect_point_sphere(kjVec3f p, kjVec3f centre, float radius) {
    return kj_intersect_sphere_point(centre, radius, p);
}

KJ_FORCE_INLINE kjVec3f kj_sphere_nearest_point(kjVec3f centre, float radius, kjVec3f p) {
    return kj_vec3f_add(centre, kj_vec3f_mulf(kj_vec3f_normalise(kj_vec3f_sub(p, centre)), radius));
}

KJ_FORCE_INLINE float kj_sphere_distance_sq_to_point(kjVec3f centre, float radius, kjVec3f p) {
    return kj_vec3f_distance_sq(p, kj_sphere_nearest_point(centre, radius, p));
}

KJ_FORCE_INLINE float kj_sphere_distance_to_point(kjVec3f centre, float radius, kjVec3f p) {
    return kj_sqrtf(kj_sphere_distance_sq_to_point(centre, radius, p));
}

KJ_FORCE_INLINE bool kj_intersect_aabb_aabb(kjVec3f a_min, kjVec3f a_max, kjVec3f b_min, kjVec3f b_max) {
    return !(b_max.x < a_min.x | a_max.x < b_min.x | b_max.y < a_min.y | a_max.y < b_min.y | b_max.z < a_min.z | a_max.z < b_min.z);
}

KJ_FORCE_INLINE bool kj_intersect_aabb_sphere(kjVec3f min, kjVec3f max, kjVec3f centre, float radius) {
    return kj_intersect_sphere_aabb(centre, radius, min, max);
}

KJ_FORCE_INLINE bool kj_intersect_sphere_aabb(kjVec3f centre, float radius, kjVec3f min, kjVec3f max) {
    return kj_vec3f_length_sq(kj_vec3f_sub(centre, kj_vec3f_clamp(centre, min, max))) < (radius * radius);
}

KJ_FORCE_INLINE bool kj_intersect_sphere_sphere(kjVec3f c0, float r0, kjVec3f c1, float r1) {
    kjVec3f xyz = kj_vec3f_sub(c0, c1);
    xyz = kj_vec3f_mul(xyz, xyz);
    float r = r0 + r1;
    r *= r;
    return xyz.x + xyz.y + xyz.z < r;
}

KJ_FORCE_INLINE bool kj_raycast_ray_aabb(kjRaycast* raycast, kjRay ray, kjVec3f min, kjVec3f max) {
    KJ_ASSERT(kj_float32_eq(1.0f, kj_vec3f_length(ray.dir), KJ_FLOAT32_EPS));
    kjVec3f inv = kj_vec3f(1.0f / ray.dir.x, 1.0f / ray.dir.y, 1.0f / ray.dir.z);
    kjVec3f d0 = kj_vec3f_mul(kj_vec3f_sub(min, ray.pos), inv);
    kjVec3f d1 = kj_vec3f_mul(kj_vec3f_sub(max, ray.pos), inv);
    kjVec3f v0 = kj_vec3f_min(d0, d1);
    kjVec3f v1 = kj_vec3f_max(d0, d1);
    float vmin = kj_vec3f_hmax(v0);
    float vmax = kj_vec3f_hmin(v1);
    raycast->t = vmin;
    raycast->pos = kj_vec3f_add(ray.pos, kj_vec3f_mulf(ray.dir, vmin));
    kjVec3f c = kj_vec3f_sub(raycast->pos, kj_vec3f_mulf(kj_vec3f_add(min, max), 0.5f));
    kjVec3f abs_c = kj_vec3f_abs(c);
    raycast->normal = abs_c.x > abs_c.y ? kj_vec3f(kj_signf(c.x), 0.0f, 0.0f): abs_c.y > abs_c.z ? kj_vec3f(0.0f, kj_signf(c.y), 0.0f): kj_vec3f(0.0f, 0.0f, kj_signf(c.z));
    return vmax >= 0.0f && vmax >= vmin && vmin <= ray.t;
}

KJ_FORCE_INLINE bool kj_raycast_ray_sphere(kjRaycast* raycast, kjRay ray, kjVec3f centre, float radius) {
    KJ_ASSERT(kj_float32_eq(1.0f, kj_vec3f_length(ray.dir), KJ_FLOAT32_EPS));
    kjVec3f m = kj_vec3f_sub(ray.pos, centre);
    float c = kj_vec3f_length_sq(m) - (radius * radius);
    float d = kj_vec3f_dot(m, ray.dir);
    float dist = (d * d) - c;
    float t = -d - kj_sqrtf(dist);
    raycast->t = t;
    raycast->pos = kj_vec3f_add(ray.pos, kj_vec3f_mulf(ray.dir, t));
    raycast->normal = kj_vec3f_normalise(kj_vec3f_sub(raycast->pos, centre));
    return dist > 0.0f && t >= 0.0f && t <= ray.t;
}

KJ_FORCE_INLINE bool kj_raycast_aabb(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f min, kjVec3f max) {
    kjVec3f dir = kj_vec3f_sub(to, from);
    float length = kj_vec3f_length(dir);
    KJ_ASSERT(length > 0.0f);
    kjRay ray;
    ray.pos = from;
    ray.dir = kj_vec3f_mulf(dir, 1.0f / length);
    ray.t = length;
    return kj_raycast_ray_aabb(raycast, ray, min, max);
}

KJ_FORCE_INLINE bool kj_raycast_sphere(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f centre, float radius) {
    kjVec3f dir = kj_vec3f_sub(to, from);
    float length = kj_vec3f_length(dir);
    KJ_ASSERT(length > 0.0f);
    kjRay ray;
    ray.pos = from;
    ray.dir = kj_vec3f_mulf(dir, 1.0f / length);
    ray.t = length;
    return kj_raycast_ray_sphere(raycast, ray, centre, radius);
}

KJ_FORCE_INLINE void kj_rgba_unpack(uint8_t unpacked[4], uint32_t packed) {
    unpacked[0] = packed >> 24;
    unpacked[1] = (packed >> 16) & 0xFF;
    unpacked[2] = (packed >>  8) & 0xFF;
    unpacked[3] = packed;
}

KJ_FORCE_INLINE uint32_t kj_rgba_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

KJ_FORCE_INLINE uint32_t kj_rgbav_pack(uint8_t rgba[4]) {
    return (rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | rgba[3];
}

/*
 * Optimized http://lolengine.net/blog/2011/3/20/understanding-fast-float-integer-conversions
 */
KJ_FORCE_INLINE void kj_rgbaf_unpack(float unpacked[4], uint32_t packed) {
    kjBinary32 fi0 = { 32768.0f };
    kjBinary32 fi1 = { 32768.0f };
    kjBinary32 fi2 = { 32768.0f };
    kjBinary32 fi3 = { 32768.0f };
    fi0.i |= (packed >> 24);
    fi1.i |= (packed >> 16) & 0xFF;
    fi2.i |= (packed >> 8) & 0xFF;
    fi3.i |= packed & 0xFF;
    unpacked[0] = (fi0.f - 32768.0f) * (256.0f / 255.0f);
    unpacked[1] = (fi1.f - 32768.0f) * (256.0f / 255.0f);
    unpacked[2] = (fi2.f - 32768.0f) * (256.0f / 255.0f);
    unpacked[3] = (fi3.f - 32768.0f) * (256.0f / 255.0f);
}

KJ_FORCE_INLINE uint32_t kj_rgbaf_pack(float r, float g, float b, float a) {
#if defined(KJ_MATH_SIMD)
    __m128 f255_256 = _mm_set1_ps(255.0f / 256.0f);
    __m128 f32768 = _mm_set1_ps(32768.0f);
    __m128 f = _mm_set_ps(r, g, b, a);
    f = _mm_add_ps(_mm_mul_ps(f, f255_256), f32768);
    uint32_t tmp[4];
    _mm_store_si128((__m128i*) tmp, _mm_castps_si128(f));
    return ((uint8_t) tmp[0] << 24) | ((uint8_t) tmp[1] << 16) | ((uint8_t) tmp[2] << 8) | (uint8_t) tmp[3];
#else
/*
 * Optimized http://lolengine.net/blog/2011/3/20/understanding-fast-float-integer-conversions
 */
    kjBinary32 fi0;
    kjBinary32 fi1;
    kjBinary32 fi2;
    kjBinary32 fi3;
    fi0.f = 32768.0f + r * (255.0f / 256.0f);
    fi1.f = 32768.0f + g * (255.0f / 256.0f);
    fi2.f = 32768.0f + b * (255.0f / 256.0f);
    fi3.f = 32768.0f + a * (255.0f / 256.0f);
    return ((uint8_t) fi0.i << 24) | ((uint8_t) fi1.i << 16) | ((uint8_t) fi2.i << 8) | (uint8_t) fi3.i;
#endif
}

KJ_FORCE_INLINE uint32_t kj_rgbafv_pack(float rgba[4]) {
#if defined(KJ_MATH_SIMD)
    __m128 f255_256 = _mm_set1_ps(255.0f / 256.0f);
    __m128 f32768 = _mm_set1_ps(32768.0f);
    __m128 f = _mm_loadu_ps(rgba);
    f = _mm_add_ps(_mm_mul_ps(f, f255_256), f32768);
    uint32_t tmp[4];
    _mm_store_si128((__m128i*) tmp, _mm_castps_si128(f));
    return ((uint8_t) tmp[0] << 24) | ((uint8_t) tmp[1] << 16) | ((uint8_t) tmp[2] << 8) | (uint8_t) tmp[3];
#else
/*
 * Optimized http://lolengine.net/blog/2011/3/20/understanding-fast-float-integer-conversions
 */
    kjBinary32 fi0;
    kjBinary32 fi1;
    kjBinary32 fi2;
    kjBinary32 fi3;
    fi0.f = 32768.0f + rgba[0] * (255.0f / 256.0f);
    fi1.f = 32768.0f + rgba[1] * (255.0f / 256.0f);
    fi2.f = 32768.0f + rgba[2] * (255.0f / 256.0f);
    fi3.f = 32768.0f + rgba[3] * (255.0f / 256.0f);
    return ((uint8_t) fi0.i << 24) | ((uint8_t) fi1.i << 16) | ((uint8_t) fi2.i << 8) | (uint8_t) fi3.i;
#endif
}

/*
 * Convert rgb floats ([0-1],[0-1],[0-1]) to hsv floats ([0-1],[0-1],[0-1]), from Foley & van Dam p592
 * Optimized http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
 */
KJ_FORCE_INLINE void kj_hsv_from_rgb(float hsv[3], float rgb[3]) {
    float r = rgb[0];
    float g = rgb[1];
    float b = rgb[2];
    float K = 0.0f;
    if(g < b) {
        float tmp = g; g = b; b = tmp;
        K = -1.0f;
    }
    if(rgb[0] < g) {
        float tmp = r; r = g; g = tmp;
        K = (-1.0f / 3.0f) - K;
    }
    float chroma = r - (g < b ? g : b);
    hsv[0] = kj_absf(K + (g - b) / (6.0f * chroma + 1e-20f));
    hsv[1] = chroma * (1.0f / (r + 1e-20f));
    hsv[2] = r;
}

/*
 * Convert hsv floats ([0-1],[0-1],[0-1]) to rgb floats ([0-1],[0-1],[0-1]), from Foley & van Dam p593
 * also http://en.wikipedia.org/wiki/HSL_and_HSV
 */
KJ_FORCE_INLINE void kj_rgb_from_hsv(float rgb[3], float hsv[3]) {
    float s = hsv[1];
    float v = hsv[2];
    if(s == 0.0f) {
        rgb[0] = v;
        rgb[1] = v;
        rgb[2] = v;
    } else {
        float h = kj_modf(hsv[0], 1.0f) * (60.0f / 360.0f);
        int32_t i = (int32_t) h;
        float f = h - (float) i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));
        switch(i) {
             case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
             case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
             case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
             case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
             case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
            default: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
        }
    }
}

KJ_FORCE_INLINE void kj_hsva_from_rgba(float hsva[4], float rgba[4]) {
    kj_hsv_from_rgb(hsva, rgba);
    hsva[3] = rgba[3];
}

KJ_FORCE_INLINE void kj_rgba_from_hsva(float rgba[4], float hsva[4]) {
    kj_rgb_from_hsv(rgba, hsva);
    rgba[3] = hsva[3];
}

KJ_FORCE_INLINE kjRandomSeries kj_random_series(uint64_t seed) {
    KJ_ASSERT(seed != 0);
    kjRandomSeries res;
    uint32_t lo = seed & 0xFFFFFFFF;
    uint32_t hi = seed >> 0x20;
    res.state[0] = (((uint64_t) hi) << 0x20) | lo;
    res.state[1] = (((uint64_t) lo) << 0x20) | hi;
    return res;
}

KJ_FORCE_INLINE uint64_t kj_random_uint64(kjRandomSeries* series) {
    // xorshift128+
    uint64_t x = series->state[0];
    uint64_t y = series->state[1];
    series->state[0] = y;
    x ^= x << 0x17;
    series->state[1] = x ^ y ^ (x >> 0x11) ^ (y >> 0x1A);
    return series->state[1] + y;
}

KJ_FORCE_INLINE int64_t kj_random_int64(kjRandomSeries* series) {
    union { uint64_t u; int64_t i; } ui = { kj_random_uint64(series) };
    return ui.i;
}

KJ_FORCE_INLINE int32_t kj_randomi(kjRandomSeries* series) {
    return (int32_t) kj_random_int64(series);
}

KJ_FORCE_INLINE int32_t kj_random_rangei(kjRandomSeries* series, int32_t min, int32_t max) {
    return min + kj_randomi(series) % ((max + 1) - min);
}

KJ_FORCE_INLINE uint32_t kj_randomu(kjRandomSeries* series) {
    return (uint32_t) kj_random_uint64(series);
}

KJ_FORCE_INLINE uint32_t kj_random_rangeu(kjRandomSeries* series, uint32_t min, uint32_t max) {
    return min + kj_randomu(series) % ((max + 1) - min);
}

KJ_FORCE_INLINE float kj_randomf(kjRandomSeries* series) {
    union { uint64_t i; float f; } b = { kj_random_uint64(series) };
    return b.f;
}

KJ_FORCE_INLINE double kj_random_float64(kjRandomSeries* series) {
    union { uint64_t i; double f; } b = { kj_random_uint64(series) };
    return b.f;
}

KJ_FORCE_INLINE float kj_random_rangef(kjRandomSeries* series, float min, float max) {
    return kj_lerpf(min, max, kj_random01f(series));
}

KJ_FORCE_INLINE float kj_random01f(kjRandomSeries* series) {
    return (kj_randomu(series) & 0xFFFFFF) / 16777216.0f;
}

KJ_FORCE_INLINE float kj_random11f(kjRandomSeries* series) {
    return kj_random01f(series) * 2.0f - 1.0f;
}

KJ_FORCE_INLINE kjVec2f kj_random_vec2f(kjRandomSeries* series) {
    return kj_vec2f(kj_randomf(series), kj_randomf(series));
}

KJ_FORCE_INLINE kjVec3f kj_random_vec3f(kjRandomSeries* series) {
    return kj_vec3f(kj_randomf(series), kj_randomf(series), kj_randomf(series));
}

KJ_FORCE_INLINE kjVec4f kj_random_vec4f(kjRandomSeries* series) {
    return kj_vec4f(kj_randomf(series), kj_randomf(series), kj_randomf(series), kj_randomf(series));
}

KJ_FORCE_INLINE kjVec2f kj_random_unit_vec2f(kjRandomSeries* series) {
    return kj_vec2f_normalise(kj_vec2f(kj_random11f(series), kj_random11f(series)));
}

KJ_FORCE_INLINE kjVec3f kj_random_unit_vec3f(kjRandomSeries* series) {
    return kj_vec3f_normalise(kj_vec3f(kj_random11f(series), kj_random11f(series), kj_random11f(series)));
}

KJ_FORCE_INLINE kjVec4f kj_random_unit_vec4f(kjRandomSeries* series) {
    return kj_vec4f_normalise(kj_vec4f(kj_random11f(series), kj_random11f(series), kj_random11f(series), kj_random11f(series)));
}

KJ_FORCE_INLINE kjVec2f kj_random_in_unit_circle(kjRandomSeries* series) {
    return kj_vec2f(kj_cosf(kj_random_rangef(series, 0.0f, KJ_TAU)), kj_cosf(kj_random_rangef(series, 0.0f, KJ_TAU)));
}

KJ_FORCE_INLINE kjVec2f kj_random_in_rect(kjRandomSeries* series, kjVec2f min, kjVec2f max) {
    return kj_vec2f(kj_random_rangef(series, min.x, max.x), kj_random_rangef(series, min.y, max.y));
}

KJ_FORCE_INLINE void kj_random_rgba(kjRandomSeries* series, uint8_t rgba[4]) {
    *((uint64_t*) rgba) = kj_random_uint64(series);
}

KJ_FORCE_INLINE void kj_random_rgbaf(kjRandomSeries* series, float rgba[4]) {
    rgba[0] = kj_random01f(series);
    rgba[1] = kj_random01f(series);
    rgba[2] = kj_random01f(series);
    rgba[3] = kj_random01f(series);
}

KJ_FORCE_INLINE float kj_random_radians(kjRandomSeries* series) {
    return kj_random_rangef(series, 0.0f, KJ_TAU);
}

KJ_FORCE_INLINE float kj_random_degrees(kjRandomSeries* series) {
    return kj_random_rangef(series, 0.0f, 360.0f);
}
#endif

/*
 * ---------------------------------- LICENSE ----------------------------------
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org>
 * =============================================================================
 */
