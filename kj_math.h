/*
 * `kj_math.h`
 *
 * ---------------------------------- LICENSE ----------------------------------
 * This software is in the public domain.  Where that dedication is not
 * recognized, you are granted a perpetual, irrevocable license to copy,
 * distribute, and modify the source code as you see fit.
 *
 * The source code is provided "as is", without warranty of any kind, express
 * or implied. No attribution is required, but always appreciated.
 * =============================================================================
 *
 * usage:
 *      #define KJ_MATH_IMPL
 *      #include "kj_math.h"
 */

#if !defined(KJ_MATH_H)
#define KJ_MATH_H

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
    KJ_ALIGN(16) float x, y, z, w;
} kjVec4f;

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
    KJ_ALIGN(16) float e[4][4];
    KJ_ALIGN(16) float a[16];
    KJ_ALIGN(16) kjVec4f c[4];
} kjMat4f;

#define KJ_PI (3.141592653589793f)
#define KJ_TAU (6.283185307179586f)
#define KJ_E (2.718281828459045f)
#define KJ_PHI (1.618033988749894f)
#define KJ_R2D (57.295779513082320f)
#define KJ_D2R (0.017453292519943f)

#define KJ_F32_MIN (-3.4028234663852886e+38f)
#define KJ_F32_MAX (3.4028234663852886e+38f)
#define KJ_F32_EPS (1.1920928955078125e-07f)

#define KJ_MIN(a, b) ((a) < (b) ? (a): (b))
#define KJ_MAX(a, b) ((a) > (b) ? (a): (b))
#define KJ_CLAMP(a, min, max) (KJ_MIN(KJ_MAX((a), (min)), (max)))
#define KJ_SATURATE(a) (KJ_CLAMP(a, 0, 1))
#define KJ_WRAP(a, min, max) ((a) > (max) ? (min): (a) < (min) ? (max): (a))
#define KJ_LERP(min, max, t) (((t) * ((max) - (min))) + (min))
#define KJ_REMAP(a, fmin, fmax, tmin, tmax) (((((a) - (fmin)) * ((tmax) - (tmin))) / ((fmax) - (fmin))) + (tmin))
#define KJ_REMAP01(a, fmin, fmax) (((a) - (fmin)) / ((fmax) - (fmin)))
#define KJ_ABS(a) ((a) >= 0 ? (a): -(a))
#define KJ_SIGN(a) ((a) < 0 ? -1: 1)
#define KJ_ROUND_TO(a, b) ((a) + (((b) - 1) - (((a) - 1) % (b))))

KJ_MATH_API bool kj_signbitf(float a);
KJ_MATH_API float kj_signf(float a);
KJ_MATH_API float kj_rsqrtf(float a);
KJ_MATH_API float kj_sqrtf(float a);
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
KJ_MATH_API float kj_fmaf(float a, float b, float c);
KJ_MATH_API void kj_sincosf(float* sc, float a);

KJ_MATH_API float kj_radian_wrapf(float a);
KJ_MATH_API float kj_degree_wrapf(float a);
KJ_FORCE_INLINE float kj_radian_clampf(float angle, float min, float max);
KJ_FORCE_INLINE float kj_degree_clampf(float angle, float min, float max);
KJ_FORCE_INLINE float kj_degree_normalisef(float angle);
KJ_FORCE_INLINE float kj_radian_normalisef(float angle);

KJ_MATH_API float kj_wrapf(float a, float min, float max);
KJ_MATH_API float kj_clampf(float a, float min, float max);
KJ_MATH_API float kj_saturatef(float a);

KJ_MATH_API float kj_lerpf(float min, float max, float t);
KJ_MATH_API float kj_lerpf_clamped(float min, float max, float t);

KJ_MATH_API float kj_smoothstepf(float min, float max, float t);
KJ_MATH_API float kj_stepf(float step, float t);

KJ_MATH_API kjVec2f kj_vec2f(float x, float y);
KJ_MATH_API kjVec2i kj_vec2i(int32_t x, int32_t y);
KJ_MATH_API kjVec2u kj_vec2u(uint32_t x, uint32_t y);
KJ_MATH_API kjVec2f kj_vec2f_zero(void);
KJ_MATH_API kjVec2i kj_vec2i_zero(void);
KJ_MATH_API kjVec2u kj_vec2u_zero(void);
KJ_MATH_API kjVec2f kj_vec2f_one(void);
KJ_MATH_API kjVec2i kj_vec2i_one(void);
KJ_MATH_API kjVec2u kj_vec2u_one(void);
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
KJ_MATH_API float kj_vec2f_dot(kjVec2f a, kjVec2f b);
KJ_MATH_API kjMat2f kj_vec2f_outer(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_cross(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_length_sq(kjVec2f a);
KJ_MATH_API float kj_vec2f_length(kjVec2f a);
KJ_MATH_API float kj_vec2f_distance_sq(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_distance(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_normalise(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_perp(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_reflect(kjVec2f a, kjVec2f n);
KJ_MATH_API kjVec2f kj_vec2f_lerpf(kjVec2f a, kjVec2f b, float t);
KJ_MATH_API kjVec2f kj_vec2f_min(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_max(kjVec2f a, kjVec2f b);
KJ_MATH_API float kj_vec2f_hmin(kjVec2f a);
KJ_MATH_API float kj_vec2f_hmax(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_abs(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_clamp(kjVec2f a, kjVec2f min, kjVec2f max);
KJ_MATH_API kjVec2f kj_vec2f_clampf(kjVec2f a, float min, float max);
KJ_MATH_API kjVec2f kj_vec2f_saturate(kjVec2f a);
KJ_MATH_API kjVec3f kj_vec2f_extend(kjVec2f a, float z);

KJ_MATH_API kjVec2f kj_vec2f_from_angle(float radians);
KJ_MATH_API float kj_vec2f_angle_between(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_vec2f_from_sin_cos(float s, float c);
KJ_MATH_API kjVec2f kj_vec2f_identity(void);
KJ_MATH_API float kj_vec2f_angle(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_x_axis(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_y_axis(kjVec2f a);
KJ_MATH_API kjVec2f kj_vec2f_rotate(kjVec2f a, float angle);

KJ_MATH_API kjVec3f kj_vec3f(float x, float y, float z);
KJ_MATH_API kjVec3i kj_vec3i(int32_t x, int32_t y, int32_t z);
KJ_MATH_API kjVec3u kj_vec3u(uint32_t x, uint32_t y, uint32_t z);
KJ_MATH_API kjVec3f kj_vec3f_zero(void);
KJ_MATH_API kjVec3i kj_vec3i_zero(void);
KJ_MATH_API kjVec3u kj_vec3u_zero(void);
KJ_MATH_API kjVec3f kj_vec3f_one(void);
KJ_MATH_API kjVec3i kj_vec3i_one(void);
KJ_MATH_API kjVec3u kj_vec3u_one(void);
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
KJ_MATH_API float kj_vec3f_dot(kjVec3f a, kjVec3f b);
KJ_MATH_API kjMat3f kj_vec3f_outer(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_cross(kjVec3f a, kjVec3f b);
KJ_MATH_API float kj_vec3f_length_sq(kjVec3f a);
KJ_MATH_API float kj_vec3f_length(kjVec3f a);
KJ_MATH_API float kj_vec3f_distance_sq(kjVec3f a, kjVec3f b);
KJ_MATH_API float kj_vec3f_distance(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_normalise(kjVec3f a);
KJ_MATH_API kjVec3f kj_vec3f_orthonormalise(kjVec3f normal, kjVec3f ref);
KJ_MATH_API kjVec3f kj_vec3f_lerpf(kjVec3f a, kjVec3f b, float t);
KJ_MATH_API kjVec3f kj_vec3f_min(kjVec3f a, kjVec3f b);
KJ_MATH_API kjVec3f kj_vec3f_max(kjVec3f a, kjVec3f b);
KJ_MATH_API float kj_vec3f_hmin(kjVec3f a);
KJ_MATH_API float kj_vec3f_hmax(kjVec3f a);
KJ_MATH_API kjVec3f kj_vec3f_abs(kjVec3f a);
KJ_MATH_API kjVec3f kj_vec3f_reflect(kjVec3f a, kjVec3f n);
KJ_MATH_API kjVec3f kj_vec3f_clamp(kjVec3f a, kjVec3f b, kjVec3f c);
KJ_MATH_API kjVec3f kj_vec3f_clampf(kjVec3f a, float min, float max);
KJ_MATH_API kjVec3f kj_vec3f_saturate(kjVec3f a);
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
KJ_MATH_API float kj_vec4f_dot(kjVec4f a, kjVec4f b);
KJ_MATH_API kjMat4f kj_vec4f_outer(kjVec4f a, kjVec4f b);
KJ_MATH_API float kj_vec4f_length_sq(kjVec4f a);
KJ_MATH_API float kj_vec4f_length(kjVec4f a);
KJ_MATH_API float kj_vec4f_distance_sq(kjVec4f a, kjVec4f b);
KJ_MATH_API float kj_vec4f_distance(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_normalise(kjVec4f a);
KJ_MATH_API kjVec4f kj_vec4f_lerpf(kjVec4f a, kjVec4f b, float t);
KJ_MATH_API kjVec4f kj_vec4f_min(kjVec4f a, kjVec4f b);
KJ_MATH_API kjVec4f kj_vec4f_max(kjVec4f a, kjVec4f b);
KJ_MATH_API float kj_vec4f_hmin(kjVec4f a);
KJ_MATH_API float kj_vec4f_hmax(kjVec4f a);
KJ_MATH_API kjVec4f kj_vec4f_clamp(kjVec4f a, kjVec4f min, kjVec4f max);
KJ_MATH_API kjVec4f kj_vec4f_clampf(kjVec4f a, float min, float max);
KJ_MATH_API kjVec4f kj_vec4f_saturate(kjVec4f a);
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
KJ_MATH_API kjMat3f kj_mat3f_from_transform(kjVec2f translate, kjVec2f scale, kjQuatf rotate);

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
KJ_MATH_API kjMat4f kj_mat4f_scale_uniform(float a);
KJ_MATH_API kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz);
KJ_MATH_API kjMat4f kj_mat4f_ortho(float l, float r, float b, float t, float znear, float zfar);
KJ_MATH_API kjMat4f kj_mat4f_ortho_inf(float l, float r, float b, float t);
KJ_MATH_API kjMat4f kj_mat4f_perspective(float fovy, float aspect, float znear, float zfar);
KJ_MATH_API kjMat4f kj_mat4f_perspective_fov(float fov, float width, float height, float znear, float zfar);
KJ_MATH_API kjMat4f kj_mat4f_perspective_inf(float fovy, float aspect, float znear);
KJ_MATH_API kjMat4f kj_mat4f_look_at(kjVec3f eye, kjVec3f target, kjVec3f up);
KJ_MATH_API float kj_mat4f_determinant(kjMat4f a);
KJ_MATH_API kjMat4f kj_mat4f_inverse(kjMat4f a);
KJ_MATH_API kjMat4f kj_mat4f_from_quatf(kjQuatf q);
KJ_MATH_API kjMat4f kj_mat4f_from_transform(kjVec3f translate, kjVec3f scale, kjQuatf rotate);

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

KJ_MATH_API bool kj_triangle2d_contains_point(kjVec2f p, kjVec2f a, kjVec2f b, kjVec2f c);
KJ_MATH_API bool kj_aabb2d_contains_point(kjVec2f min, kjVec2f max, kjVec2f p);
KJ_MATH_API bool kj_circle_contains_point(kjVec2f centre, float radius, kjVec2f p);

KJ_MATH_API kjVec2f kj_segment2d_midpoint(kjVec2f a, kjVec2f b);
KJ_MATH_API kjVec2f kj_segment2d_nearest_point(kjVec2f a, kjVec2f b, kjVec2f p);
KJ_MATH_API float kj_segment2d_distance_sq_to_point(kjVec2f a, kjVec2f b, kjVec2f p);
KJ_MATH_API float kj_segment2d_distance_to_point(kjVec2f a, kjVec2f b, kjVec2f p);

KJ_MATH_API kjVec2f kj_arc2d_nearest_point(kjVec2f centre, float angle, float radius, kjVec2f p);
KJ_MATH_API float kj_arc2d_distance_sq_to_point(kjVec2f centre, float angle, float radius, kjVec2f p);
KJ_MATH_API float kj_arc2d_distance_to_point(kjVec2f centre, float angle, float radius, kjVec2f p);

KJ_MATH_API kjVec2f kj_circle_nearest_point(kjVec2f centre, float radius, kjVec2f p);
KJ_MATH_API float kj_circle_distance_sq_to_point(kjVec2f centre, float radius, kjVec2f p);
KJ_MATH_API float kj_circle_distance_to_point(kjVec2f centre, float radius, kjVec2f p);

KJ_MATH_API bool kj_intersect2d_segment_segment(kjVec2f* i, kjVec2f a0, kjVec2f a1, kjVec2f b0, kjVec2f b1);

KJ_MATH_API bool kj_intersect2d_aabb_aabb(kjVec2f min_a, kjVec2f max_a, kjVec2f b_min, kjVec2f b_max);
KJ_MATH_API bool kj_intersect2d_aabb_circle(kjVec2f min_a, kjVec2f max_a, kjVec2f centre, float radius);
KJ_MATH_API bool kj_intersect2d_circle_aabb(kjVec2f centre, float radius, kjVec2f b_min, kjVec2f b_max);
KJ_MATH_API bool kj_intersect2d_circle_circle(kjVec2f c0, float r0, kjVec2f c1, float r1);

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

#if defined(__cplusplus)
KJ_MATH_API bool kj_intersect2d(kjVec2f* i, kjVec2f a0, kjVec2f a1, kjVec2f b0, kjVec2f b1);
KJ_MATH_API bool kj_intersect2d(kjVec2f a_min, kjVec2f a_max, kjVec2f b_min, kjVec2f b_max);
KJ_MATH_API bool kj_intersect2d(kjVec2f a_min, kjVec2f a_max, kjVec2f centre, float radius);
KJ_MATH_API bool kj_intersect2d(kjVec2f centre, float radius, kjVec2f b_min, kjVec2f b_max);
KJ_MATH_API bool kj_intersect2d(kjVec2f c0, float r0, kjVec2f c1, float r1);
KJ_MATH_API bool kj_raycast2d(kjRaycast2d* raycast, kjRay2d ray, kjVec2f min, kjVec2f max);
KJ_MATH_API bool kj_raycast2d(kjRaycast2d* raycast, kjRay2d ray, kjVec2f centre, float radius);
KJ_MATH_API bool kj_raycast2d(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f min, kjVec2f max);
KJ_MATH_API bool kj_raycast2d(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f centre, float radius);
#endif

KJ_MATH_API bool kj_aabb_contains_point(kjVec3f min, kjVec3f max, kjVec3f p);
KJ_MATH_API bool kj_sphere_contains_point(kjVec3f centre, float radius, kjVec3f p);

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

#if defined(__cplusplus)
KJ_MATH_API bool kj_intersect(kjVec3f* i, kjVec3f a0, kjVec3f a1, kjVec3f b0, kjVec3f b1);
KJ_MATH_API bool kj_intersect(kjVec3f a_min, kjVec3f a_max, kjVec3f b_min, kjVec3f b_max);
KJ_MATH_API bool kj_intersect(kjVec3f a_min, kjVec3f a_max, kjVec3f centre, float radius);
KJ_MATH_API bool kj_intersect(kjVec3f centre, float radius, kjVec3f b_min, kjVec3f b_max);
KJ_MATH_API bool kj_intersect(kjVec3f c0, float r0, kjVec3f c1, float r1);
KJ_MATH_API bool kj_raycast(kjRaycast* raycast, kjRay ray, kjVec3f min, kjVec3f max);
KJ_MATH_API bool kj_raycast(kjRaycast* raycast, kjRay ray, kjVec3f centre, float radius);
KJ_MATH_API bool kj_raycast(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f min, kjVec3f max);
KJ_MATH_API bool kj_raycast(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f centre, float radius);
#endif

KJ_MATH_API void kj_rgba_unpack(uint8_t* unpacked, uint32_t packed);
KJ_MATH_API uint32_t kj_rgba_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
KJ_MATH_API uint32_t kj_rgbav_pack(uint8_t* rgba);
KJ_MATH_API void kj_rgbaf_unpack(float* unpacked, uint32_t packed);
KJ_MATH_API uint32_t kj_rgbaf_pack(float r, float g, float b, float a);
KJ_MATH_API uint32_t kj_rgbafv_pack(float* rgba);

KJ_MATH_API uint32_t kj_rgba_mix(uint32_t a, uint32_t b, uint32_t t);

KJ_MATH_API void kj_hsv_from_rgb(float* hsv, float* rgb);
KJ_MATH_API void kj_rgb_from_hsv(float* rgb, float* hsv);

#endif

#if defined(KJ_MATH_IMPL)

#if defined(KJ_MATH_SIMD)
// SSE2, SSE3, SSE4.1?
#include <xmmintrin.h>
#endif

#if defined(KJ_COMPILER_MSVC)
#include <math.h>
#endif

KJ_FORCE_INLINE bool kj_signbitf(float a) {
    union { float f; uint32_t i; } fi = { a };
    return fi.i >> 0x1F;
}

KJ_FORCE_INLINE float kj_signf(float a) {
    //return kj_signbitf(a) ? -1.0f: 1.0f;
    return (0.0f < a) - (a < 0.0f);
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
    union { float f; uint32_t i; } fi = { a };
    fi.i &= 0x7FFFFFFF;
    return fi.f;
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

KJ_FORCE_INLINE float kj_fmaf(float a, float b, float c) {
#if defined(KJ_COMPILER_MSVC)
    return fmaf(a, b, c);
#elif defined(KJ_COMPILER_CLANG) || defined(KJ_COMPILER_GNU)
    return __builtin_fmaf(a, b, c);
#endif
}

KJ_FORCE_INLINE void kj_sincosf(float* sc, float a) {
    sc[0] = kj_sinf(a);
    sc[1] = kj_cosf(a);
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
    return kj_modf(a, max) + min;
}

KJ_FORCE_INLINE float kj_radian_normalisef(float angle) {
    angle = kj_radian_wrapf(angle);
    return angle > KJ_PI ? angle - KJ_TAU: angle;
}

KJ_FORCE_INLINE float kj_degree_normalisef(float angle) {
    angle = kj_degree_wrapf(angle);
    return angle > 180.0f ? angle - 360.0f: angle;
}

KJ_FORCE_INLINE float kj_radian_clampf(float angle, float min, float max) {
    float max_a = kj_radian_wrapf(max - min) * 0.5f;
    float midpoint = kj_radian_wrapf(min + max_a);
    float a = kj_radian_normalisef(angle - midpoint);
    return kj_absf(a) > max_a ?
        kj_radian_normalisef(midpoint + max_a * kj_signf(a)):
        kj_radian_normalisef(angle);
}

KJ_FORCE_INLINE float kj_degree_clampf(float angle, float min, float max) {
    float max_a = kj_degree_wrapf(max - min) * 0.5f;
    float midpoint = kj_degree_wrapf(min + max_a);
    float a = kj_degree_normalisef(angle - midpoint);
    return kj_absf(a) > max_a ?
        kj_degree_normalisef(midpoint + max_a * kj_signf(a)):
        kj_degree_normalisef(angle);
}

KJ_FORCE_INLINE float kj_clampf(float a, float min, float max) {
    return kj_minf(kj_maxf(a, min), max);
}

KJ_FORCE_INLINE float kj_saturatef(float a) {
    return kj_maxf(0.0f, kj_minf(a, 1.0f));
}

KJ_FORCE_INLINE float kj_lerpf(float min, float max, float t) {
    return (t * (max - min)) + min;
}

KJ_FORCE_INLINE float kj_lerpf_clamped(float min, float max, float t) {
    return (kj_clampf(t, 0.0f, 1.0f) * (max - min)) + min;
}

KJ_FORCE_INLINE float kj_smoothstepf(float min, float max, float t) {
    t = kj_saturatef((t - min) / (max - min));
    return (t * t) * (3.0f - 2.0f * t);
}

KJ_FORCE_INLINE float kj_quickstepf(float min, float max, float t) {
    t = kj_saturatef((t - min) / (max - min));
    t = 1.0f - t * t;
    return 1.0f - t * t;
}

KJ_FORCE_INLINE float kj_stepf(float step, float t) {
    return t < step ? 0.0f: 1.0f;
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
    return kj_vec2f(a.x / b.x, a.y / b.y);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_divf(kjVec2f a, float b) {
    return kj_vec2f(a.x / b, a.y / b);
}

KJ_FORCE_INLINE float kj_vec2f_dot(kjVec2f a, kjVec2f b) {
    return (a.x * b.x) + (a.y * b.y);
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

KJ_FORCE_INLINE float kj_vec2f_distance_sq(kjVec2f a, kjVec2f b) {
    return kj_vec2f_length_sq(kj_vec2f_sub(a, b));
}

KJ_FORCE_INLINE float kj_vec2f_distance(kjVec2f a, kjVec2f b) {
    return kj_sqrtf(kj_vec2f_distance_sq(a, b));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_normalise(kjVec2f a) {
    return kj_vec2f_div(a, kj_vec2f_all(kj_vec2f_length(a)));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_perp(kjVec2f a) {
    return kj_vec2f(-a.y, a.x);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_reflect(kjVec2f a, kjVec2f n) {
    return kj_vec2f_sub(a, kj_vec2f_mulf(n, 2.0f * kj_vec2f_dot(a, n)));
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

KJ_FORCE_INLINE kjVec2f kj_vec2f_saturate(kjVec2f a) {
    return kj_vec2f_clamp(a, kj_vec2f_zero(), kj_vec2f_one());
}

KJ_FORCE_INLINE kjVec3f kj_vec2f_extend(kjVec2f a, float z) {
    return kj_vec3f(a.x, a.y, z);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_from_angle(float radians) {
    return kj_vec2f(kj_cosf(radians), kj_sinf(radians));
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

KJ_FORCE_INLINE float kj_vec2f_angle_between(kjVec2f a, kjVec2f b) {
    return kj_atan2f((a.x * b.y) - (a.y * b.x), kj_vec2f_dot(a, b));
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_x_axis(kjVec2f a) {
    return kj_vec2f(a.y, a.x);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_y_axis(kjVec2f a) {
    return kj_vec2f(-a.x, a.y);
}

KJ_FORCE_INLINE kjVec2f kj_vec2f_rotate(kjVec2f a, float angle) {
    float c = kj_cosf(angle);
    float s = kj_sinf(angle);
    return kj_vec2f(a.x * c - a.y * s, a.x * s + a.y * c);
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
    return kj_vec3f(a.x / b.x, a.y / b.y, a.z / b.z);
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_divf(kjVec3f a, float b) {
    return kj_vec3f(a.x / b, a.y / b, a.z / b);
}

KJ_FORCE_INLINE float kj_vec3f_dot(kjVec3f a, kjVec3f b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
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

KJ_FORCE_INLINE float kj_vec3f_distance_sq(kjVec3f a, kjVec3f b) {
    return kj_vec3f_length_sq(kj_vec3f_sub(a, b));
}

KJ_FORCE_INLINE float kj_vec3f_distance(kjVec3f a, kjVec3f b) {
    return kj_sqrtf(kj_vec3f_distance_sq(a, b));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_normalise(kjVec3f a) {
    return kj_vec3f_div(a, kj_vec3f_all(kj_vec3f_length(a)));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_orthonormalise(kjVec3f normal, kjVec3f ref) {
    return kj_vec3f_normalise(kj_vec3f_sub(normal, kj_vec3f_mulf(ref, kj_vec3f_dot(normal, ref))));
}

KJ_FORCE_INLINE kjVec3f kj_vec3f_reflect(kjVec3f a, kjVec3f n) {
    return kj_vec3f_sub(a, kj_vec3f_mulf(n, 2.0f * kj_vec3f_dot(a, n)));
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

KJ_FORCE_INLINE kjVec3f kj_vec3f_saturate(kjVec3f a) {
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
    return kj_vec4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
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
    return kj_vec4f(a.x / b, a.y / b, a.z / b, a.w / b);
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

KJ_FORCE_INLINE float kj_vec4f_distance_sq(kjVec4f a, kjVec4f b) {
    return kj_vec4f_length_sq(kj_vec4f_sub(a, b));
}

KJ_FORCE_INLINE float kj_vec4f_distance(kjVec4f a, kjVec4f b) {
    return kj_sqrtf(kj_vec4f_distance_sq(a, b));
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_normalise(kjVec4f a) {
    return kj_vec4f_div(a, kj_vec4f_all(kj_vec4f_length(a)));
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
    return kj_vec4f(
            kj_clampf(a.x, min.x, max.x),
            kj_clampf(a.y, min.y, max.y),
            kj_clampf(a.z, min.z, max.z),
            kj_clampf(a.w, min.w, max.w));
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_clampf(kjVec4f a, float min, float max) {
    return kj_vec4f_clamp(a, kj_vec4f_all(min), kj_vec4f_all(max));
}

KJ_FORCE_INLINE kjVec4f kj_vec4f_saturate(kjVec4f a) {
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
    return kj_quatf(q.x / v, q.y / v, q.z / v, q.w / v);
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
            kj_atan2f(2.0f * ((q.y * q.z) + (q.w * q.x)), (q.w * q.w) - (q.x * q.x) - (q.y * q.y) + (q.z * q.z)),
            kj_asinf(-2.0f * ((q.x * q.z) - (q.w * q.y))),
            kj_atan2f(2.0f * ((q.x * q.y) + (q.w * q.z)), (q.w * q.w) - (q.x * q.x) - (q.y * q.y) + (q.z * q.z)));
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
    return kj_quatf_divf(q, kj_quatf_length(q));
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
    if((1.0f - ct) > KJ_F32_EPS) {
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
    return kj_quatf_divf(kj_quatf_conjugate(q), kj_quatf_length_sq(q));
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
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    return kj_mat2f(
            sc.y, sc.x,
            -sc.x, sc.y);
}

KJ_FORCE_INLINE float kj_mat2f_determinant(kjMat2f a) {
    return a.e[0][0] * a.e[1][1] - a.e[1][0] * a.e[0][1];
}

KJ_FORCE_INLINE kjMat2f kj_mat2f_inverse(kjMat2f a) {
    float det = kj_mat2f_determinant(a);
    if(det != 0.0f) {
        return kj_mat2f(
                a.e[1][1] / det, -a.e[0][1] / det,
               -a.e[1][0] / det,  a.e[0][0] / det);
    }
    return kj_mat2f_identity();
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
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    kjVec3f axis = kj_vec3f_normalise(xyz);
    kjVec3f rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - sc.y));
    return kj_mat3f(
            sc.y + rot_axis.x * axis.x, rot_axis.x * axis.y + sc.x * axis.z, rot_axis.x * axis.z - sc.x * axis.y,
            rot_axis.y * axis.x - sc.x * axis.z, sc.y + rot_axis.y * axis.y, rot_axis.y * axis.z + sc.x * axis.x,
            rot_axis.z * axis.x + sc.x * axis.y, rot_axis.z * axis.y - sc.x * axis.x, sc.y + rot_axis.z * axis.z);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate(float radians, float x, float y, float z) {
    return kj_mat3f_rotate_vec3f(radians, kj_vec3f(x, y, z));
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate_x(float radians) {
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    return kj_mat3f(
            1.0f, 0.0f, 0.0f,
            0.0f, sc.y, sc.x,
            0.0f, -sc.x, sc.y);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate_y(float radians) {
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    return kj_mat3f(
            sc.y, 0.0f, -sc.x,
            0.0f, 1.0f, 0.0f,
            sc.x, 0.0f, sc.y);
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_rotate_z(float radians) {
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    return kj_mat3f(
            sc.y, sc.x, 0.0f,
            -sc.x, sc.y, 0.0f,
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
    if(det != 0.0f) {
        kjMat3f res;
        res.c[0] = kj_vec3f_divf(kj_vec3f_cross(a.c[1], a.c[2]), det);
        res.c[1] = kj_vec3f_divf(kj_vec3f_cross(a.c[2], a.c[0]), det);
        res.c[2] = kj_vec3f_divf(kj_vec3f_cross(a.c[0], a.c[1]), det);
        res = kj_mat3f_transpose(res);
    }
    return kj_mat3f_identity();
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
            1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz), 2.0f * (xz - wy),
            2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx),
            2.0f * (xz + wy), 2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy));
}

KJ_FORCE_INLINE kjMat3f kj_mat3f_from_transform(kjVec2f translate, kjVec2f scale, kjQuatf rotate) {
    return kj_mat3f_mul(kj_mat3f_from_quatf(rotate), kj_mat3f_mul(kj_mat3f_scale_vec2f(scale), kj_mat3f_translate_vec2f(translate)));
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
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    return kj_mat4f(
            1.0f,  0.0f, 0.0f, 0.0f,
            0.0f,  sc.y, sc.x, 0.0f,
            0.0f, -sc.x, sc.y, 0.0f,
            0.0f,  0.0f, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate_y(float radians) {
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    return kj_mat4f(
            sc.y, 0.0f, -sc.x, 0.0f,
            0.0f, 1.0f,  0.0f, 0.0f,
            sc.x, 0.0f,  sc.y, 0.0f,
            0.0f, 0.0f,  0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate_z(float radians) {
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    return kj_mat4f(
             sc.y, sc.x, 0.0f, 0.0f,
            -sc.x, sc.y, 0.0f, 0.0f,
             0.0f, 0.0f, 1.0f, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f);
}


KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate_vec3f(float radians, kjVec3f xyz) {
    kjVec2f sc;
    kj_sincosf(&sc.x, radians);
    kjVec3f axis = kj_vec3f_normalise(xyz);
    kjVec3f rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - sc.y));
    return kj_mat4f(
                     sc.y + rot_axis.x * axis.x, rot_axis.x * axis.y + sc.x * axis.z, rot_axis.x * axis.z - sc.x * axis.y, 0.0f,
            rot_axis.y * axis.x - sc.x * axis.z,          sc.y + rot_axis.y * axis.y, rot_axis.y * axis.z + sc.x * axis.x, 0.0f,
            rot_axis.z * axis.x + sc.x * axis.y, rot_axis.z * axis.y - sc.x * axis.x,          sc.y + rot_axis.z * axis.z, 0.0f,
                                           0.0f,                                0.0f,                                0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_rotate(float radians, float x, float y, float z) {
    return kj_mat4f_rotate_vec3f(radians, kj_vec3f(x, y, z));
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scale(float x, float y, float z) {
    return kj_mat4f_diagonal(x, y, z, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scale_uniform(float a) {
    return kj_mat4f_diagonal(a, a, a, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz) {
    return kj_mat4f_scale(xyz.x, xyz.y, xyz.z);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_ortho(float l, float r, float b, float t, float znear, float zfar) {
    float depth = zfar - znear;
    float width = r - l;
    float height = t - b;
    return kj_mat4f(
                2.0f / width,              0.0f,                    0.0f, 0.0f,
                        0.0f,     2.0f / height,                    0.0f, 0.0f,
                        0.0f,              0.0f,           -2.0f / depth, 0.0f,
            -(r + l) / width, -(t + b) / height, -(zfar + znear) / depth, 1.0f);
}


KJ_FORCE_INLINE kjMat4f kj_mat4f_ortho_inf(float l, float r, float b, float t) {
    float width = r - l;
    float height = t - b;
    return kj_mat4f(
                2.0f / width,              0.0f, 0.0f, 0.0f,
                        0.0f,     2.0f / height, 0.0f, 0.0f,
                        0.0f,              0.0f, 0.0f, 0.0f,
            -(r + l) / width, -(t + b) / height, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_perspective(float fovy, float aspect, float znear, float zfar) {
    if(aspect > 0.0f) {
        float tan_fovy = kj_tanf(fovy * 0.5f);
        float depth = zfar - znear;
        return kj_mat4f(
                1.0f / (tan_fovy * aspect),            0.0f,                           0.0f,  0.0f,
                                      0.0f, 1.0f / tan_fovy,                           0.0f,  0.0f,
                                      0.0f,            0.0f,        -(zfar + znear) / depth, -1.0f,
                                      0.0f,            0.0f, -(2.0f * zfar * znear) / depth,  0.0f);
    }
    return kj_mat4f_identity();
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_perspective_inf(float fovy, float aspect, float znear) {
    if(aspect > 0.0f) {
        float tan_fovy = kj_tanf(fovy * 0.5f);
        return kj_mat4f(
                1.0f / (tan_fovy * aspect),            0.0f,          0.0f,  0.0f,
                                      0.0f, 1.0f / tan_fovy,          0.0f,  0.0f,
                                      0.0f,            0.0f,         -1.0f, -1.0f,
                                      0.0f,            0.0f, -2.0f * znear,  0.0f);
    }
    return kj_mat4f_identity();
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_perspective_fov(float fov, float width, float height, float znear, float zfar) {
    fov = fov * 0.5f;
    float h = kj_cosf(fov) / kj_sinf(fov);
    float w = h * height / width;
    float depth = zfar - znear;
    return kj_mat4f(
               w, 0.0f,                           0.0f,  0.0f,
            0.0f,    h,                           0.0f,  0.0f,
            0.0f, 0.0f,        -(zfar + znear) / depth, -1.0f,
            0.0f, 0.0f, -(2.0f * zfar * znear) / depth,  0.0f);
}


KJ_FORCE_INLINE kjMat4f kj_mat4f_look_at(kjVec3f eye, kjVec3f target, kjVec3f up) {
    kjVec3f f = kj_vec3f_normalise(kj_vec3f_sub(target, eye));
    kjVec3f s = kj_vec3f_normalise(kj_vec3f_cross(f, up));
    kjVec3f u = kj_vec3f_cross(s, f);
    return kj_mat4f(
                              s.x,                   u.x,                 -f.x, 0.0f,
                              s.y,                   u.y,                 -f.y, 0.0f,
                              s.z,                   u.z,                 -f.z, 0.0f,
            -kj_vec3f_dot(s, eye), -kj_vec3f_dot(u, eye), kj_vec3f_dot(f, eye), 1.0f);
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
    if(det != 0.0f) {
        det = 1.0 / det;
        kjMat4f res;
        res.e[0][0] = a.e[1][1] * a.e[2][2] * a.e[3][3] + a.e[3][1] * a.e[1][2] * a.e[2][3] + a.e[2][1] * a.e[3][2] * a.e[1][3] - a.e[1][1] * a.e[3][2] * a.e[2][3] - a.e[2][1] * a.e[1][2] * a.e[3][3] - a.e[3][1] * a.e[2][2] * a.e[1][3];
        res.e[0][1] = a.e[0][1] * a.e[3][2] * a.e[2][3] + a.e[2][1] * a.e[0][2] * a.e[3][3] + a.e[3][1] * a.e[2][2] * a.e[0][3] - a.e[3][1] * a.e[0][2] * a.e[2][3] - a.e[2][1] * a.e[3][2] * a.e[0][3] - a.e[0][1] * a.e[2][2] * a.e[3][3];
        res.e[0][2] = a.e[0][1] * a.e[1][2] * a.e[3][3] + a.e[3][1] * a.e[0][2] * a.e[1][3] + a.e[1][1] * a.e[3][2] * a.e[0][3] - a.e[0][1] * a.e[3][2] * a.e[1][3] - a.e[1][1] * a.e[0][2] * a.e[3][3] - a.e[3][1] * a.e[1][2] * a.e[0][3];
        res.e[0][3] = a.e[0][1] * a.e[2][2] * a.e[1][3] + a.e[1][1] * a.e[0][2] * a.e[2][3] + a.e[2][1] * a.e[1][2] * a.e[0][3] - a.e[0][1] * a.e[1][2] * a.e[2][3] - a.e[2][1] * a.e[0][2] * a.e[1][3] - a.e[1][1] * a.e[2][2] * a.e[0][3];
        res.e[1][0] = a.e[1][2] * a.e[3][3] * a.e[2][0] + a.e[2][2] * a.e[1][3] * a.e[3][0] + a.e[3][2] * a.e[2][3] * a.e[1][0] - a.e[1][2] * a.e[2][3] * a.e[3][0] - a.e[3][2] * a.e[1][3] * a.e[2][0] - a.e[2][2] * a.e[3][3] * a.e[1][0];
        res.e[1][1] = a.e[0][2] * a.e[2][3] * a.e[3][0] + a.e[3][2] * a.e[0][3] * a.e[2][0] + a.e[2][2] * a.e[3][3] * a.e[0][0] - a.e[0][2] * a.e[3][3] * a.e[2][0] - a.e[2][2] * a.e[0][3] * a.e[3][0] - a.e[3][2] * a.e[2][3] * a.e[0][0];
        res.e[1][2] = a.e[0][2] * a.e[3][3] * a.e[1][0] + a.e[1][2] * a.e[0][3] * a.e[3][0] + a.e[3][2] * a.e[1][3] * a.e[0][0] - a.e[0][2] * a.e[1][3] * a.e[3][0] - a.e[3][2] * a.e[0][3] * a.e[1][0] - a.e[1][2] * a.e[3][3] * a.e[0][0];
        res.e[1][3] = a.e[0][2] * a.e[1][3] * a.e[2][0] + a.e[2][2] * a.e[0][3] * a.e[1][0] + a.e[1][2] * a.e[2][3] * a.e[0][0] - a.e[0][2] * a.e[2][3] * a.e[1][0] - a.e[1][2] * a.e[0][3] * a.e[2][0] - a.e[2][2] * a.e[1][3] * a.e[0][0];
        res.e[2][0] = a.e[1][3] * a.e[2][0] * a.e[3][1] + a.e[3][3] * a.e[1][0] * a.e[2][1] + a.e[2][3] * a.e[3][0] * a.e[1][1] - a.e[1][3] * a.e[3][0] * a.e[2][1] - a.e[2][3] * a.e[1][0] * a.e[3][1] - a.e[3][3] * a.e[2][0] * a.e[1][1];
        res.e[2][1] = a.e[0][3] * a.e[3][0] * a.e[2][1] + a.e[2][3] * a.e[0][0] * a.e[3][1] + a.e[3][3] * a.e[2][0] * a.e[0][1] - a.e[0][3] * a.e[2][0] * a.e[3][1] - a.e[3][3] * a.e[0][0] * a.e[2][1] - a.e[2][3] * a.e[3][0] * a.e[0][1];
        res.e[2][2] = a.e[0][3] * a.e[1][0] * a.e[3][1] + a.e[3][3] * a.e[0][0] * a.e[1][1] + a.e[1][3] * a.e[3][0] * a.e[0][1] - a.e[0][3] * a.e[3][0] * a.e[1][1] - a.e[1][3] * a.e[0][0] * a.e[3][1] - a.e[3][3] * a.e[1][0] * a.e[0][1];
        res.e[2][3] = a.e[0][3] * a.e[2][0] * a.e[1][1] + a.e[1][3] * a.e[0][0] * a.e[2][1] + a.e[2][3] * a.e[1][0] * a.e[0][1] - a.e[0][3] * a.e[1][0] * a.e[2][1] - a.e[2][3] * a.e[0][0] * a.e[1][1] - a.e[1][3] * a.e[2][0] * a.e[0][1];
        res.e[3][0] = a.e[1][0] * a.e[3][1] * a.e[2][2] + a.e[2][0] * a.e[1][1] * a.e[3][2] + a.e[3][0] * a.e[2][1] * a.e[1][2] - a.e[1][0] * a.e[2][1] * a.e[3][2] - a.e[3][0] * a.e[1][1] * a.e[2][2] - a.e[2][0] * a.e[3][1] * a.e[1][2];
        res.e[3][1] = a.e[0][0] * a.e[2][1] * a.e[3][2] + a.e[3][0] * a.e[0][1] * a.e[2][2] + a.e[2][0] * a.e[3][1] * a.e[0][2] - a.e[0][0] * a.e[3][1] * a.e[2][2] - a.e[2][0] * a.e[0][1] * a.e[3][2] - a.e[3][0] * a.e[2][1] * a.e[0][2];
        res.e[3][2] = a.e[0][0] * a.e[3][1] * a.e[1][2] + a.e[1][0] * a.e[0][1] * a.e[3][2] + a.e[3][0] * a.e[1][1] * a.e[0][2] - a.e[0][0] * a.e[1][1] * a.e[3][2] - a.e[3][0] * a.e[0][1] * a.e[1][2] - a.e[1][0] * a.e[3][1] * a.e[0][2];
        res.e[3][3] = a.e[0][0] * a.e[1][1] * a.e[2][2] + a.e[2][0] * a.e[0][1] * a.e[1][2] + a.e[1][0] * a.e[2][1] * a.e[0][2] - a.e[0][0] * a.e[2][1] * a.e[1][2] - a.e[1][0] * a.e[0][1] * a.e[2][2] - a.e[2][0] * a.e[1][1] * a.e[0][2];
        return kj_mat4f_mulf(res, det);
    }
    return kj_mat4f_identity();
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
            1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz), 2.0f * (xz - wy), 0.0f,
            2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx), 0.0f,
            2.0f * (xz + wy), 2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_from_transform(kjVec3f translate, kjVec3f scale, kjQuatf rotate) {
    return kj_mat4f_mul(kj_mat4f_from_quatf(rotate), kj_mat4f_mul(kj_mat4f_scale_vec3f(scale), kj_mat4f_translate_vec3f(translate)));
}

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
    return kj_mat4f_scale_uniform(a);
}

KJ_FORCE_INLINE kjMat4f kj_mat4f_scale(kjVec3f xyz) {
    return kj_mat4f_scale_vec3f(xyz);
}

KJ_FORCE_INLINE kjMat4f operator*(kjMat4f a, kjMat4f b) {
    return kj_mat4f_mul(a, b);
}
#endif

KJ_FORCE_INLINE bool kj_triangle2d_contains_point(kjVec2f p, kjVec2f a, kjVec2f b, kjVec2f c) {
    bool b1 = ((p.x - b.x) * (a.y - b.y) - (p.y - b.y) * (a.x - b.x)) < 0.0f;
    bool b2 = ((p.x - c.x) * (b.y - c.y) - (p.y - c.y) * (b.x - c.x)) < 0.0f;
    bool b3 = ((p.x - a.x) * (c.y - a.y) - (p.y - a.y) * (c.x - a.x)) < 0.0f;
    return b1 == b2 && b2 == b3;
}

KJ_FORCE_INLINE bool kj_aabb2d_contains_point(kjVec2f min, kjVec2f max, kjVec2f p) {
    return p.x > min.x && p.x < max.x && p.y > min.y && p.y < max.y;
}

KJ_FORCE_INLINE bool kj_circle_contains_point(kjVec2f centre, float radius, kjVec2f p) {
    return kj_vec2f_distance_sq(centre, p) < (radius * radius);
}

KJ_FORCE_INLINE kjVec2f kj_segment2d_midpoint(kjVec2f a, kjVec2f b) {
    return kj_vec2f((a.x + b.x) * 0.5f, (a.y + b.y) * 0.5f);
}

KJ_FORCE_INLINE kjVec2f kj_segment2d_nearest_point(kjVec2f a, kjVec2f b, kjVec2f p) {
    float d = kj_vec2f_distance_sq(a, b) + KJ_F32_EPS;
    float t = kj_saturatef(((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / d);
    return kj_vec2f(a.x + t * (b.x - a.x), a.y + t * b.y - a.y);
}

KJ_FORCE_INLINE float kj_segment2d_distance_sq_to_point(kjVec2f a, kjVec2f b, kjVec2f p) {
    return kj_vec2f_distance_sq(p, kj_segment2d_nearest_point(a, b, p));
}

KJ_FORCE_INLINE float kj_segment2d_distance_to_point(kjVec2f a, kjVec2f b, kjVec2f p) {
    return kj_sqrtf(kj_segment2d_distance_sq_to_point(a, b, p));
}

KJ_FORCE_INLINE kjVec2f kj_arc2d_nearest_point(kjVec2f centre, float angle, float radius, kjVec2f p) {
    if(angle >= KJ_TAU) { return kj_circle_nearest_point(centre, radius, p); }
    kjVec2f cv = kj_vec2f_normalise(kj_vec2f_sub(centre, p));
    float a = kj_radian_clampf(kj_atan2f(cv.y, cv.x) + KJ_PI, 0.0f, angle);
    return kj_vec2f_mulf(kj_vec2f(kj_cosf(a), kj_sinf(a)), radius);
}

KJ_FORCE_INLINE float kj_arc2d_distance_sq_to_point(kjVec2f centre, float angle, float radius, kjVec2f p) {
    return kj_vec2f_distance_sq(p, kj_arc2d_nearest_point(centre, angle, radius, p));
}

KJ_FORCE_INLINE float kj_arc2d_distance_to_point(kjVec2f centre, float angle, float radius, kjVec2f p) {
    return kj_sqrtf(kj_arc2d_distance_sq_to_point(centre, angle, radius, p));
}

KJ_FORCE_INLINE kjVec2f kj_circle_nearest_point(kjVec2f centre, float radius, kjVec2f p) {
    return kj_vec2f_mulf(kj_vec2f_normalise(kj_vec2f_sub(centre, p)), -radius);
}

KJ_FORCE_INLINE float kj_circle_distance_sq_to_point(kjVec2f centre, float radius, kjVec2f p) {
    return kj_vec2f_distance_sq(p, kj_circle_nearest_point(centre, radius, p));
}

KJ_FORCE_INLINE float kj_circle_distance_to_point(kjVec2f centre, float radius, kjVec2f p) {
    return kj_sqrtf(kj_circle_distance_sq_to_point(centre, radius, p));
}

KJ_FORCE_INLINE bool kj_intersect2d_segment_segment(kjVec2f* i, kjVec2f a0, kjVec2f a1, kjVec2f b0, kjVec2f b1) {
    float na = (b1.x - b0.x) * (a0.y - b0.y) - (b1.y - b0.y) * (a0.x - b0.x);
    float nb = (a1.x - a0.x) * (a0.y - b0.y) - (a1.y - a0.y) * (a0.x - b0.x);
    float d = (b1.y - b0.y) * (a1.x - a0.x) - (b1.x - b0.x) * (a1.y - a0.y);
    bool da = kj_absf(d) < KJ_F32_EPS;
    if(kj_absf(na) < KJ_F32_EPS && kj_absf(nb) < KJ_F32_EPS && da) {
        *i = kj_vec2f((a0.x + a1.x) * 0.5f, (a0.y + a1.y) * 0.5f);
        return true;
    }
    if(da) { return false; }
    float ua = na / d;
    float ub = nb / d;
    if(ua < 0.0f || ua > 1.0f || ub < 0.0f || ub > 1.0f) { return false; }
    *i = kj_vec2f(a0.x + ua * (a1.x - a0.x), a0.y + ua * (a1.y - a0.y));
    return true;
}

KJ_FORCE_INLINE bool kj_intersect2d_aabb_aabb(kjVec2f a_min, kjVec2f a_max, kjVec2f b_min, kjVec2f b_max) {
    return !(b_max.x < a_min.x | a_max.x < b_min.x | b_max.y < a_min.y | a_max.y < b_min.y);
}

KJ_FORCE_INLINE bool kj_intersect2d_aabb_circle(kjVec2f a_min, kjVec2f a_max, kjVec2f centre, float radius) {
    return kj_intersect2d_circle_aabb(centre, radius, a_min, a_max);
}

KJ_FORCE_INLINE bool kj_intersect2d_circle_aabb(kjVec2f centre, float radius, kjVec2f b_min, kjVec2f b_max) {
    return kj_vec2f_length_sq(kj_vec2f_sub(centre, kj_vec2f_clamp(centre, b_min, b_max))) < (radius * radius);
}

KJ_FORCE_INLINE bool kj_intersect2d_circle_circle(kjVec2f c0, float r0, kjVec2f c1, float r1) {
    float r2 = r0 + r1;
    return kj_vec2f_length_sq(kj_vec2f_sub(c1, c0)) < (r2 * r2);
}

KJ_FORCE_INLINE bool kj_raycast2d_ray_aabb(kjRaycast2d* raycast, kjRay2d ray, kjVec2f min, kjVec2f max) {
    kjVec2f inv = kj_vec2f(1.0f / ray.dir.x, 1.0f / ray.dir.y);
    kjVec2f d0 = kj_vec2f_mul(kj_vec2f_sub(min, ray.pos), inv);
    kjVec2f d1 = kj_vec2f_mul(kj_vec2f_sub(max, ray.pos), inv);
    kjVec2f v0 = kj_vec2f_min(d0, d1);
    kjVec2f v1 = kj_vec2f_max(d0, d1);
    float vmin = kj_vec2f_hmax(v0);
    float vmax = kj_vec2f_hmin(v1);

    raycast->pos = kj_vec2f_add(ray.pos, kj_vec2f_mulf(ray.dir, vmin));
    kjVec2f c = kj_vec2f_sub(raycast->pos, kj_vec2f_mulf(kj_vec2f_add(min, max), 0.5f));
    kjVec2f abs_c = kj_vec2f_abs(c);
    raycast->normal = abs_c.x > abs_c.y ? kj_vec2f(kj_signf(c.x), 0.0f): kj_vec2f(0.0f, kj_signf(c.y));
    raycast->t = vmin;
    return vmax >= 0 && vmax >= vmin && vmin <= ray.t;
}

KJ_FORCE_INLINE bool kj_raycast2d_ray_circle(kjRaycast2d* raycast, kjRay2d ray, kjVec2f centre, float radius) {
    kjVec2f m = kj_vec2f_sub(ray.pos, centre);
    float c = kj_vec2f_length_sq(m) - (radius * radius);
    float d = kj_vec2f_dot(m, ray.dir);
    float dist = (d * d) - c;
    float t = -d - kj_sqrtf(dist);
    raycast->t = t;
    raycast->pos = kj_vec2f_add(ray.pos, kj_vec2f_mulf(ray.dir, t));
    raycast->normal = kj_vec2f_normalise(kj_vec2f_sub(raycast->pos, centre));
    return dist > 0.0f && t >= 0.0f && t <= ray.t;
}

KJ_FORCE_INLINE bool kj_raycast2d_aabb(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f min, kjVec2f max) {
    kjVec2f dir = kj_vec2f_sub(to, from);
    kjRay2d ray;
    ray.pos = from;
    ray.dir = kj_vec2f_normalise(dir);
    ray.t = kj_vec2f_length(dir);
    return kj_raycast2d_ray_aabb(raycast, ray, min, max);
}

KJ_FORCE_INLINE bool kj_raycast2d_circle(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f centre, float radius) {
    kjVec2f dir = kj_vec2f_sub(to, from);
    kjRay2d ray;
    ray.pos = from;
    ray.dir = kj_vec2f_normalise(dir);
    ray.t = kj_vec2f_length(dir);
    return kj_raycast2d_ray_circle(raycast, ray, centre, radius);
}

#if defined(__cplusplus)
KJ_FORCE_INLINE bool kj_intersect2d(kjVec2f* i, kjVec2f a0, kjVec2f a1, kjVec2f b0, kjVec2f b1) {
    return kj_intersect2d_segment_segment(i, a0, a1, b0, b1);
}

KJ_FORCE_INLINE bool kj_intersect2d(kjVec2f a_min, kjVec2f a_max, kjVec2f b_min, kjVec2f b_max) {
    return kj_intersect2d_aabb_aabb(a_min, a_max, b_min, b_max);
}

KJ_FORCE_INLINE bool kj_intersect2d(kjVec2f a_min, kjVec2f a_max, kjVec2f centre, float radius) {
    return kj_intersect2d_aabb_circle(a_min, a_max, centre, radius);
}

KJ_FORCE_INLINE bool kj_intersect2d(kjVec2f centre, float radius, kjVec2f min, kjVec2f max) {
    return kj_intersect2d_circle_aabb(centre, radius, min, max);
}

KJ_FORCE_INLINE bool kj_intersect2d(kjVec2f c0, float r0, kjVec2f c1, float r1) {
    return kj_intersect2d_circle_circle(c0, r0, c1, r1);
}

KJ_FORCE_INLINE bool kj_raycast2d(kjRaycast2d* raycast, kjRay2d ray, kjVec2f min, kjVec2f max) {
    return kj_raycast2d_ray_aabb(raycast, ray, min, max);
}

KJ_FORCE_INLINE bool kj_raycast2d(kjRaycast2d* raycast, kjRay2d ray, kjVec2f centre, float radius) {
    return kj_raycast2d_ray_circle(raycast, ray, centre, radius);
}

KJ_FORCE_INLINE bool kj_raycast2d(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f min, kjVec2f max) {
    return kj_raycast2d_aabb(raycast, from, to, min, max);
}

KJ_FORCE_INLINE bool kj_raycast2d(kjRaycast2d* raycast, kjVec2f from, kjVec2f to, kjVec2f centre, float radius) {
    return kj_raycast2d_circle(raycast, from, to, centre, radius);
}
#endif

KJ_FORCE_INLINE bool kj_aabb_contains_point(kjVec3f min, kjVec3f max, kjVec3f p) {
    return p.x > min.x && p.x < max.x && p.y > min.y && p.y < max.y && p.z > min.z && p.z < max.z;
}

KJ_FORCE_INLINE bool kj_sphere_contains_point(kjVec3f centre, float radius, kjVec3f p) {
    return kj_vec3f_distance_sq(centre, p) < (radius * radius);
}

KJ_FORCE_INLINE kjVec3f kj_sphere_nearest_point(kjVec3f centre, float radius, kjVec3f p) {
    return kj_vec3f_mulf(kj_vec3f_normalise(kj_vec3f_sub(centre, p)), -radius);
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
    float r2 = r0 + r1;
    return kj_vec3f_length_sq(kj_vec3f_sub(c1, c0)) < (r2 * r2);
}

KJ_FORCE_INLINE bool kj_raycast_ray_aabb(kjRaycast* raycast, kjRay ray, kjVec3f min, kjVec3f max) {
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
    kjRay ray;
    ray.pos = from;
    ray.dir = kj_vec3f_normalise(dir);
    ray.t = kj_vec3f_length(dir);
    return kj_raycast_ray_aabb(raycast, ray, min, max);
}

KJ_FORCE_INLINE bool kj_raycast_sphere(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f centre, float radius) {
    kjVec3f dir = kj_vec3f_sub(to, from);
    kjRay ray;
    ray.pos = from;
    ray.dir = kj_vec3f_normalise(dir);
    ray.t = kj_vec3f_length(dir);
    return kj_raycast_ray_sphere(raycast, ray, centre, radius);
}

#if defined(__cplusplus)
KJ_FORCE_INLINE bool kj_intersect(kjVec3f a_min, kjVec3f a_max, kjVec3f b_min, kjVec3f b_max) {
    return kj_intersect_aabb_aabb(a_min, a_max, b_min, b_max);
}

KJ_FORCE_INLINE bool kj_intersect(kjVec3f min, kjVec3f max, kjVec3f centre, float radius) {
    return kj_intersect_aabb_sphere(min, max, centre, radius);
}

KJ_FORCE_INLINE bool kj_intersect(kjVec3f centre, float radius, kjVec3f min, kjVec3f max) {
    return kj_intersect_sphere_aabb(centre, radius, min, max);
}

KJ_FORCE_INLINE bool kj_intersect(kjVec3f c0, float r0, kjVec3f c1, float r1) {
    return kj_intersect_sphere_sphere(c0, r0, c1, r1);
}

KJ_FORCE_INLINE bool kj_raycast(kjRaycast* raycast, kjRay ray, kjVec3f min, kjVec3f max) {
    return kj_raycast_ray_aabb(raycast, ray, min, max);
}

KJ_FORCE_INLINE bool kj_raycast(kjRaycast* raycast, kjRay ray, kjVec3f centre, float radius) {
    return kj_raycast_ray_sphere(raycast, ray, centre, radius);
}

KJ_FORCE_INLINE bool kj_raycast(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f min, kjVec3f max) {
    return kj_raycast_aabb(raycast, from, to, min, max);
}

KJ_FORCE_INLINE bool kj_raycast(kjRaycast* raycast, kjVec3f from, kjVec3f to, kjVec3f centre, float radius) {
    return kj_raycast_sphere(raycast, from, to, centre, radius);
}
#endif

KJ_FORCE_INLINE void kj_rgba_unpack(uint8_t* unpacked, uint32_t packed) {
    unpacked[0] = ((packed >> 24) & 0xFF);
    unpacked[1] = ((packed >> 16) & 0xFF);
    unpacked[2] = ((packed >> 8) & 0xFF);
    unpacked[3] = ((packed >> 0) & 0xFF);
}

KJ_FORCE_INLINE uint32_t kj_rgba_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (r << 24) | (g << 16) | (b << 8) | (a << 0);
}

KJ_FORCE_INLINE uint32_t kj_rgbav_pack(uint8_t* rgba) {
    return (rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | (rgba[3] << 0);
}

KJ_FORCE_INLINE void kj_rgbaf_unpack(float* unpacked, uint32_t packed) {
    unpacked[0] = kj_saturatef(((packed >> 24) & 0xFF) * (1.0f / 255.0f));
    unpacked[1] = kj_saturatef(((packed >> 16) & 0xFF) * (1.0f / 255.0f));
    unpacked[2] = kj_saturatef(((packed >> 8) & 0xFF) * (1.0f / 255.0f));
    unpacked[3] = kj_saturatef(((packed >> 0) & 0xFF) * (1.0f / 255.0f));
}

KJ_FORCE_INLINE uint32_t kj_rgbaf_pack(float r, float g, float b, float a) {
    return
        ((uint8_t) kj_clampf(r * 255.0f + 0.5f, 0.0f, 255.0f) << 24) |
        ((uint8_t) kj_clampf(g * 255.0f + 0.5f, 0.0f, 255.0f) << 16) |
        ((uint8_t) kj_clampf(b * 255.0f + 0.5f, 0.0f, 255.0f) << 8)  |
        ((uint8_t) kj_clampf(a * 255.0f + 0.5f, 0.0f, 255.0f) << 0);
}

KJ_FORCE_INLINE uint32_t kj_rgbafv_pack(float* rgba) {
    return
        ((uint8_t) kj_clampf(rgba[0] * 255.0f + 0.5f, 0.0f, 255.0f) << 24) |
        ((uint8_t) kj_clampf(rgba[1] * 255.0f + 0.5f, 0.0f, 255.0f) << 16) |
        ((uint8_t) kj_clampf(rgba[2] * 255.0f + 0.5f, 0.0f, 255.0f) << 8)  |
        ((uint8_t) kj_clampf(rgba[3] * 255.0f + 0.5f, 0.0f, 255.0f) << 0);
}

// Source: Andreas Fredriksson
KJ_FORCE_INLINE uint32_t kj_rgba_mix(uint32_t a, uint32_t b, uint32_t t) {
    uint32_t af = 256 - t;
    uint32_t bf = t;
    // uint32_t abgr -> 0a0g0b0r
    uint64_t al = (a & 0x00FF00FF) | (((uint64_t) (a & 0xFF00FF00)) << 24);
    uint64_t bl = (b & 0x00FF00FF) | (((uint64_t) (b & 0xFF00FF00)) << 24);
    // -> a_g_b_r_
    uint64_t mix = (al * af + bl * bf);
    // shift & combine back into 32-bit quantity
    return ((mix >> 32) & 0xFF00FF00) | ((mix & 0xFF00FF00) >> 8);
}

// Convert rgb floats ([0-1],[0-1],[0-1]) to hsv floats ([0-1],[0-1],[0-1]), from Foley & van Dam p592
// Optimized http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
KJ_FORCE_INLINE void kj_hsv_from_rgb(float* hsv, float* rgb) {
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
        K = -2.0f / 6.0f - K;
    }
    float chroma = r - (g < b ? g : b);
    hsv[0] = kj_absf(K + (g - b) / (6.0f * chroma + 1e-20f));
    hsv[1] = chroma / (r + 1e-20f);
    hsv[2] = r;
}

// Convert hsv floats ([0-1],[0-1],[0-1]) to rgb floats ([0-1],[0-1],[0-1]), from Foley & van Dam p593
// also http://en.wikipedia.org/wiki/HSL_and_HSV
KJ_FORCE_INLINE void kj_rgb_from_hsv(float* rgb, float* hsv) {
    float s = hsv[1];
    float v = hsv[2];
    if(s == 0.0f) {
        rgb[0] = v;
        rgb[1] = v;
        rgb[2] = v;
    } else {
        float h = kj_modf(hsv[0], 1.0f) / (60.0f / 360.0f);
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
