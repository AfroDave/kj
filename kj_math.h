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

#ifndef KJ_MATH_H
#define KJ_MATH_H

#define KJ_MATH_VERSION_MAJOR 0
#define KJ_MATH_VERSION_MINOR 5
#define KJ_MATH_VERSION_PATCH 0

#if defined(__cplusplus)
extern "C" {
#endif

#define kj_to_degrees(a) ((a) * 57.295779513082320f)
#define kj_to_radians(a) ((a) * 0.017453292519943f)
#define kj_from_radians(a) ((a) * 57.295779513082320f)
#define kj_from_degrees(a) ((a) * 0.017453292519943f)

#define KJ_PI (3.141592653589793f)
#define KJ_TAU (6.283185307179586f)
#define KJ_E (2.718281828459045f)
#define KJ_PHI (1.618033988749894f)

typedef struct kjVec2f {
    f32 x, y;
} kjVec2f;

typedef struct kjVec2i {
    i32 x, y;
} kjVec2i;

typedef struct kjVec2u {
    u32 x, y;
} kjVec2u;

typedef struct kjVec3f {
    f32 x, y, z;
} kjVec3f;

typedef struct kjVec3i {
    i32 x, y, z;
} kjVec3i;

typedef struct kjVec3u {
    u32 x, y, z;
} kjVec3u;

typedef struct kjVec4f {
    f32 x, y, z, w;
} kjVec4f;

typedef struct kjVec4i {
    i32 x, y, z, w;
} kjVec4i;

typedef struct kjVec4u {
    u32 x, y, z, w;
} kjVec4u;

typedef union kjMat3f {
    f32 e[3][3];
    f32 a[9];
    kjVec3f v[3];
} kjMat3f;

typedef union kjMat4f {
    f32 e[4][4];
    f32 a[16];
    kjVec4f v[4];
} kjMat4f;

typedef struct kjRect2f {
    kjVec2f min, max;
} kjRect2f;

typedef struct kjRect2i {
    kjVec2i min, max;
} kjRect2i;

typedef struct kjRect2u {
    kjVec2u min, max;
} kjRect2u;

typedef struct kjRect3f {
    kjVec3f min, max;
} kjRect3f;

typedef struct kjRect3i {
    kjVec3i min, max;
} kjRect3i;

typedef struct kjRect3u {
    kjVec3u min, max;
} kjRect3u;

typedef struct kjRgba {
    u8 r, g, b, a;
} kjRgba;

KJ_API f32 kj_rad_wrapf(f32 a);
KJ_API f32 kj_deg_wrapf(f32 a);

KJ_API b32 kj_signbitf(f32 a);
KJ_API f32 kj_rsqrtf(f32 a);
KJ_API f32 kj_sqrtf(f32 a);
KJ_API f32 kj_sinf(f32 a);
KJ_API f32 kj_cosf(f32 a);
KJ_API f32 kj_tanf(f32 a);
KJ_API f32 kj_asinf(f32 a);
KJ_API f32 kj_acosf(f32 a);
KJ_API f32 kj_atanf(f32 a);
KJ_API f32 kj_atan2f(f32 y, f32 x);
KJ_API f32 kj_expf(f32 a);
KJ_API f32 kj_lnf(f32 a);
KJ_API f32 kj_log10f(f32 a);
KJ_API f32 kj_log2f(f32 a);
KJ_API f32 kj_powf(f32 x, f32 y);
KJ_API f32 kj_floorf(f32 a);
KJ_API f32 kj_ceilf(f32 a);
KJ_API f32 kj_minf(f32 x, f32 y);
KJ_API f32 kj_maxf(f32 x, f32 y);

KJ_API kjVec2f kj_vec2f(f32 x, f32 y);
KJ_API kjVec2i kj_vec2i(i32 x, i32 y);
KJ_API kjVec2u kj_vec2u(u32 x, u32 y);
KJ_API kjVec2f kj_vec2f_zero(void);
KJ_API kjVec2i kj_vec2i_zero(void);
KJ_API kjVec2u kj_vec2u_zero(void);
KJ_API kjVec2f kj_vec2f_one(void);
KJ_API kjVec2i kj_vec2i_one(void);
KJ_API kjVec2u kj_vec2u_one(void);
KJ_API kjVec2f kj_vec2f_all(f32 a);
KJ_API kjVec2i kj_vec2i_all(i32 a);
KJ_API kjVec2u kj_vec2u_all(u32 a);
KJ_API kjVec2f kj_vec2f_negate(kjVec2f a);
KJ_API kjVec2f kj_vec2f_add(kjVec2f a, kjVec2f b);
KJ_API kjVec2f kj_vec2f_sub(kjVec2f a, kjVec2f b);
KJ_API kjVec2f kj_vec2f_mul(kjVec2f a, kjVec2f b);
KJ_API kjVec2f kj_vec2f_mulf(kjVec2f a, f32 b);
KJ_API kjVec2f kj_vec2f_div(kjVec2f a, kjVec2f b);
KJ_API f32 kj_vec2f_dot(kjVec2f a, kjVec2f b);
KJ_API f32 kj_vec2f_cross(kjVec2f a, kjVec2f b);
KJ_API f32 kj_vec2f_length_sq(kjVec2f a);
KJ_API f32 kj_vec2f_length(kjVec2f a);
KJ_API kjVec2f kj_vec2f_normalise(kjVec2f a);
KJ_API kjVec2f kj_vec2f_clamp(kjVec2f a, kjVec2f min, kjVec2f max);
KJ_API kjVec2i kj_vec2i_clamp(kjVec2i a, kjVec2i min, kjVec2i max);
KJ_API kjVec2u kj_vec2u_clamp(kjVec2u a, kjVec2u min, kjVec2u max);
KJ_API kjVec2f kj_vec2f_clampf(kjVec2f a, f32 min, f32 max);
KJ_API kjVec2i kj_vec2i_clampi(kjVec2i a, i32 min, i32 max);
KJ_API kjVec2u kj_vec2u_clampu(kjVec2u a, u32 min, u32 max);

KJ_API kjVec3f kj_vec3f(f32 x, f32 y, f32 z);
KJ_API kjVec3i kj_vec3i(i32 x, i32 y, i32 z);
KJ_API kjVec3u kj_vec3u(u32 x, u32 y, u32 z);
KJ_API kjVec3f kj_vec3f_zero(void);
KJ_API kjVec3i kj_vec3i_zero(void);
KJ_API kjVec3u kj_vec3u_zero(void);
KJ_API kjVec3f kj_vec3f_one(void);
KJ_API kjVec3i kj_vec3i_one(void);
KJ_API kjVec3u kj_vec3u_one(void);
KJ_API kjVec3f kj_vec3f_all(f32 a);
KJ_API kjVec3i kj_vec3i_all(i32 a);
KJ_API kjVec3u kj_vec3u_all(u32 a);
KJ_API kjVec3f kj_vec3f_negate(kjVec3f a);
KJ_API kjVec3f kj_vec3f_add(kjVec3f a, kjVec3f b);
KJ_API kjVec3f kj_vec3f_sub(kjVec3f a, kjVec3f b);
KJ_API kjVec3f kj_vec3f_mul(kjVec3f a, kjVec3f b);
KJ_API kjVec3f kj_vec3f_mulf(kjVec3f a, f32 b);
KJ_API kjVec3f kj_vec3f_div(kjVec3f a, kjVec3f b);
KJ_API f32 kj_vec3f_dot(kjVec3f a, kjVec3f b);
KJ_API i32 kj_vec3i_dot(kjVec3i a, kjVec3i b);
KJ_API u32 kj_vec3u_dot(kjVec3u a, kjVec3u b);
KJ_API kjVec3f kj_vec3f_cross(kjVec3f a, kjVec3f b);
KJ_API f32 kj_vec3f_length_sq(kjVec3f a);
KJ_API f32 kj_vec3f_length(kjVec3f a);
KJ_API kjVec3f kj_vec3f_normalise(kjVec3f a);
KJ_API kjVec3f kj_vec3f_clamp(kjVec3f a, kjVec3f min, kjVec3f max);
KJ_API kjVec3i kj_vec3i_clamp(kjVec3i a, kjVec3i min, kjVec3i max);
KJ_API kjVec3u kj_vec3u_clamp(kjVec3u a, kjVec3u min, kjVec3u max);
KJ_API kjVec3f kj_vec3f_clampf(kjVec3f a, f32 min, f32 max);
KJ_API kjVec3i kj_vec3i_clampi(kjVec3i a, i32 min, i32 max);
KJ_API kjVec3u kj_vec3u_clampu(kjVec3u a, u32 min, u32 max);

KJ_API kjVec4f kj_vec4f(f32 x, f32 y, f32 z, f32 w);
KJ_API kjVec4i kj_vec4i(i32 x, i32 y, i32 z, i32 w);
KJ_API kjVec4u kj_vec4u(u32 x, u32 y, u32 z, u32 w);
KJ_API kjVec4f kj_vec4f_zero(void);
KJ_API kjVec4i kj_vec4i_zero(void);
KJ_API kjVec4u kj_vec4u_zero(void);
KJ_API kjVec4f kj_vec4f_one(void);
KJ_API kjVec4i kj_vec4i_one(void);
KJ_API kjVec4u kj_vec4u_one(void);
KJ_API kjVec4f kj_vec4f_all(f32 a);
KJ_API kjVec4i kj_vec4i_all(i32 a);
KJ_API kjVec4u kj_vec4u_all(u32 a);
KJ_API kjVec4f kj_vec4f_negate(kjVec4f a);
KJ_API kjVec4f kj_vec4f_add(kjVec4f a, kjVec4f b);
KJ_API kjVec4f kj_vec4f_sub(kjVec4f a, kjVec4f b);
KJ_API kjVec4f kj_vec4f_mul(kjVec4f a, kjVec4f b);
KJ_API kjVec4f kj_vec4f_mulf(kjVec4f a, f32 b);
KJ_API kjVec4f kj_vec4f_div(kjVec4f a, kjVec4f b);
KJ_API f32 kj_vec4f_dot(kjVec4f a, kjVec4f b);
KJ_API f32 kj_vec4f_length_sq(kjVec4f a);
KJ_API f32 kj_vec4f_length(kjVec4f a);
KJ_API kjVec4f kj_vec4f_normalise(kjVec4f a);
KJ_API kjVec4f kj_vec4f_clamp(kjVec4f a, kjVec4f min, kjVec4f max);
KJ_API kjVec4i kj_vec4i_clamp(kjVec4i a, kjVec4i min, kjVec4i max);
KJ_API kjVec4u kj_vec4u_clamp(kjVec4u a, kjVec4u min, kjVec4u max);
KJ_API kjVec4f kj_vec4f_clampf(kjVec4f a, f32 min, f32 max);
KJ_API kjVec4i kj_vec4i_clampi(kjVec4i a, i32 min, i32 max);
KJ_API kjVec4u kj_vec4u_clampu(kjVec4u a, u32 min, u32 max);

KJ_API kjMat3f kj_mat3f(f32 e00, f32 e10, f32 e20,
                        f32 e01, f32 e11, f32 e21,
                        f32 e02, f32 e12, f32 e22);
KJ_API kjMat3f kj_mat3f_diag(f32 e00, f32 e11, f32 e22);
KJ_API kjMat3f kj_mat3f_ident(void);
KJ_API kjMat3f kj_mat3f_zero(void);
KJ_API kjMat3f kj_mat3f_one(void);
KJ_API kjMat3f kj_mat3f_mul(kjMat3f a, kjMat3f b);
KJ_API kjMat3f kj_mat3f_transpose(kjMat3f a);
KJ_API kjMat3f kj_mat3f_translate(f32 x, f32 y);
KJ_API kjMat3f kj_mat3f_translate_vec2f(kjVec2f xy);
KJ_API kjMat3f kj_mat3f_rotate(f32 angle, f32 x, f32 y, f32 z);
KJ_API kjMat3f kj_mat3f_rotate_vec3f(f32 angle, kjVec3f xyz);
KJ_API kjMat3f kj_mat3f_scale(f32 x, f32 y, f32 z);
KJ_API kjMat3f kj_mat3f_scale_uniform(f32 a);
KJ_API kjMat3f kj_mat3f_scale_vec3f(kjVec3f xyz);

KJ_API kjMat4f kj_mat4f(f32 e00, f32 e10, f32 e20, f32 e30,
                        f32 e01, f32 e11, f32 e21, f32 e31,
                        f32 e02, f32 e12, f32 e22, f32 e32,
                        f32 e03, f32 e13, f32 e23, f32 e33);
KJ_API kjMat4f kj_mat4f_diag(f32 e00, f32 e11, f32 e22, f32 e33);
KJ_API kjMat4f kj_mat4f_ident(void);
KJ_API kjMat4f kj_mat4f_zero(void);
KJ_API kjMat4f kj_mat4f_one(void);
KJ_API kjMat4f kj_mat4f_mul(kjMat4f a, kjMat4f b);
KJ_API kjVec4f kj_mat4f_mul_vec4f(kjMat4f a, kjVec4f b);
KJ_API kjMat4f kj_mat4f_transpose(kjMat4f a);
KJ_API kjMat4f kj_mat4f_translate(f32 x, f32 y, f32 z);
KJ_API kjMat4f kj_mat4f_translate_vec3f(kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_rotate(f32 angle, f32 x, f32 y, f32 z);
KJ_API kjMat4f kj_mat4f_rotate_vec3f(f32 angle, kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_rotate_x(f32 angle);
KJ_API kjMat4f kj_mat4f_rotate_y(f32 angle);
KJ_API kjMat4f kj_mat4f_rotate_z(f32 angle);
KJ_API kjMat4f kj_mat4f_scale(f32 x, f32 y, f32 z);
KJ_API kjMat4f kj_mat4f_scale_uniform(f32 a);
KJ_API kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_ortho(f32 l, f32 r, f32 b, f32 t, f32 znear, f32 zfar);
KJ_API kjMat4f kj_mat4f_ortho_inf(f32 l, f32 r, f32 t, f32 b);
KJ_API kjMat4f kj_mat4f_perspective(f32 fovy, f32 aspect, f32 znear, f32 zfar);
KJ_API kjMat4f kj_mat4f_perspective_inf(f32 fovy, f32 aspect, f32 znear);
KJ_API kjMat4f kj_mat4f_look_at(kjVec3f eye, kjVec3f target, kjVec3f up);

#define kj_contains2(x1, y1, x2, y2, x, y)                                      \
    (x1) <= (x) && (x2) >= (x) && (y1) <= (y) && (y2) >= (y)
#define kj_contains3(x1, y1, z1, x2, y2, z2, x, y, z)                           \
    (x1) <= (x) && (x2) >= (x) &&                                               \
    (y1) <= (y) && (y2) >= (y) &&                                               \
    (z1) <= (z) && (z2) >= (z)

KJ_API kjRect2f kj_rect2f(f32 x1, f32 y1, f32 x2, f32 y2);
KJ_API kjRect2i kj_rect2i(i32 x1, i32 y1, i32 x2, i32 y2);
KJ_API kjRect2u kj_rect2u(u32 x1, u32 y1, u32 x2, u32 y2);
#define kj_rect2_contains(r, x, y)                                              \
    kj_contains2((r).min.x, (r).min.y, (r).max.x, (r).max.y, (x), (y))
#define kj_rect2_contains_vec2(r, v)                                            \
    kj_contains2((r).min.x, (r).min.y, (r).max.x, (r).max.y, (v).x, (v).y)

KJ_API kjRect3f kj_rect3f(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2);
KJ_API kjRect3i kj_rect3i(i32 x1, i32 y1, i32 z1, i32 x2, i32 y2, i32 z2);
KJ_API kjRect3u kj_rect3u(u32 x1, u32 y1, u32 z1, u32 x2, u32 y2, u32 z2);
#define kj_rect3_contains(r, x, y, z)                                           \
    kj_contains3(                                                               \
            (r).min.x, (r).min.y, (r).min.z,                                    \
            (r).max.x, (r).max.y, (r).max.z, (x), (y), (z))
#define kj_rect3_contains_vec3(r, v)                                            \
    kj_contains3(                                                               \
            (r).min.x, (r).min.y, (r).min.z,                                    \
            (r).max.x, (r).max.y, (r).max.z, (v).x, (v).y, (v).z)

KJ_API kjRgba kj_rgba(u8 r, u8 g, u8 b, u8 a);
KJ_API kjRgba kj_rgba_4f(f32 r, f32 g, f32 b, f32 a);
KJ_API kjRgba kj_rgba_rgbaf(kjVec4f rgbaf);
KJ_API u32 kj_rgba_pack(kjRgba rgba);
KJ_API kjRgba kj_rgba_unpack(u32 packed);

KJ_API kjVec4f kj_rgbaf(f32 r, f32 g, f32 b, f32 a);
KJ_API kjVec4f kj_rgbaf_4u8(u8 r, u8 g, u8 b, u8 a);
KJ_API kjVec4f kj_rgbaf_rgba(kjRgba rgba);
KJ_API u32 kj_rgbaf_pack(kjVec4f rgba);
KJ_API kjVec4f kj_rgbaf_unpack(u32 packed);

#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)
KJ_API kjMat3f kj_mat3f(f32 e00, f32 e11, f32 e22);
KJ_API kjMat3f kj_mat3f(void);
KJ_API kjMat3f kj_mat3f_translate(kjVec2f xy);
KJ_API kjMat3f kj_mat3f_rotate(f32 angle, kjVec3f xyz);
KJ_API kjMat3f kj_mat3f_scale(f32 a);
KJ_API kjMat3f kj_mat3f_scale(kjVec3f xyz);
KJ_API kjMat3f operator*(kjMat3f a, kjMat3f b);

KJ_API kjMat4f kj_mat4f(f32 e00, f32 e11, f32 e22, f32 e33);
KJ_API kjMat4f kj_mat4f(void);
KJ_API kjMat4f kj_mat4f_translate(kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_rotate(f32 angle, kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_scale(f32 a);
KJ_API kjMat4f kj_mat4f_scale(kjVec3f xyz);
KJ_API kjMat4f operator*(kjMat4f a, kjMat4f b);
#endif

#endif

#if defined(KJ_MATH_IMPL)

KJ_INLINE f32 kj_rad_wrapf(f32 a) {
    if(a < -KJ_PI) return a + KJ_TAU;
    if(a > KJ_PI) return a - KJ_TAU;
    return a;
}

KJ_INLINE f32 kj_deg_wrapf(f32 a) {
    if(a < -180.0) return a + 360.0f;
    if(a > 180.0) return a - 360.0f;
    return a;
}

#if defined(KJ_COMPILER_MSVC)
#include <math.h>
KJ_INLINE b32 kj_signbitf(f32 a) { return ((*(u32*) &a) & (1 << 31)) != 0; }
KJ_INLINE f32 kj_rsqrtf(f32 a) { return 1.0f / sqrtf(a); }
KJ_INLINE f32 kj_sqrtf(f32 a) { return sqrtf(a); }
KJ_INLINE f32 kj_sinf(f32 a) { return sinf(a); }
KJ_INLINE f32 kj_cosf(f32 a) { return cosf(a); }
KJ_INLINE f32 kj_tanf(f32 a) { return tanf(a); }
KJ_INLINE f32 kj_asinf(f32 a) { return asinf(a); }
KJ_INLINE f32 kj_acosf(f32 a) { return acosf(a); }
KJ_INLINE f32 kj_atanf(f32 a) { return atanf(a); }
KJ_INLINE f32 kj_atan2f(f32 y, f32 x) { return atan2f(y, x); }
KJ_INLINE f32 kj_expf(f32 a) { return expf(a); }
KJ_INLINE f32 kj_lnf(f32 a) { return logf(a); }
KJ_INLINE f32 kj_log10f(f32 a) { return log10f(a); }
KJ_INLINE f32 kj_log2f(f32 a) { return log2f(a); }
KJ_INLINE f32 kj_powf(f32 x, f32 y) { return powf(x, y); }
KJ_INLINE f32 kj_floorf(f32 a) { return floorf(a); }
KJ_INLINE f32 kj_ceilf(f32 a) { return ceilf(a); }
KJ_INLINE f32 kj_minf(f32 x, f32 y) { return fminf(x, y); }
KJ_INLINE f32 kj_maxf(f32 x, f32 y) { return fmaxf(x, y); }
#elif defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
KJ_INLINE b32 kj_signbitf(f32 a) { return __builtin_signbitf(a); }
KJ_INLINE f32 kj_rsqrtf(f32 a) { return 1.0f / __builtin_sqrtf(a); }
KJ_INLINE f32 kj_sqrtf(f32 a) { return __builtin_sqrtf(a); }
KJ_INLINE f32 kj_sinf(f32 a) { return __builtin_sinf(a); }
KJ_INLINE f32 kj_cosf(f32 a) { return __builtin_cosf(a); }
KJ_INLINE f32 kj_tanf(f32 a) { return __builtin_tanf(a); }
KJ_INLINE f32 kj_asinf(f32 a) { return __builtin_asinf(a); }
KJ_INLINE f32 kj_acosf(f32 a) { return __builtin_acosf(a); }
KJ_INLINE f32 kj_atanf(f32 a) { return __builtin_atanf(a); }
KJ_INLINE f32 kj_atan2f(f32 y, f32 x) { return __builtin_atan2f(y, x); }
KJ_INLINE f32 kj_expf(f32 a) { return __builtin_expf(a); }
KJ_INLINE f32 kj_lnf(f32 a) { return __builtin_logf(a); }
KJ_INLINE f32 kj_log10f(f32 a) { return __builtin_log10f(a); }
KJ_INLINE f32 kj_log2f(f32 a) { return __builtin_log2f(a); }
KJ_INLINE f32 kj_powf(f32 x, f32 y) { return __builtin_powf(x, y); }
KJ_INLINE f32 kj_floorf(f32 a) { return __builtin_floorf(a); }
KJ_INLINE f32 kj_ceilf(f32 a) { return __builtin_ceilf(a); }
KJ_INLINE f32 kj_minf(f32 x, f32 y) { return __builtin_fminf(x, y); }
KJ_INLINE f32 kj_maxf(f32 x, f32 y) { return __builtin_fmaxf(x, y); }
#endif

KJ_CONST KJ_INLINE kjVec2f kj_vec2f(f32 x, f32 y) {
    kjVec2f res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_CONST KJ_INLINE kjVec2i kj_vec2i(i32 x, i32 y) {
    kjVec2i res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_CONST KJ_INLINE kjVec2u kj_vec2u(u32 x, u32 y) {
    kjVec2u res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_zero(void) {
    return kj_vec2f(0.0f, 0.0f);
}

KJ_CONST KJ_INLINE kjVec2i kj_vec2i_zero(void) {
    return kj_vec2i(0, 0);
}

KJ_CONST KJ_INLINE kjVec2u kj_vec2u_zero(void) {
    return kj_vec2u(0, 0);
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_one(void) {
    return kj_vec2f(1.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjVec2i kj_vec2i_one(void) {
    return kj_vec2i(1, 1);
}

KJ_CONST KJ_INLINE kjVec2u kj_vec2u_one(void) {
    return kj_vec2u(1, 1);
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_all(f32 a) {
    return kj_vec2f(a, a);
}

KJ_CONST KJ_INLINE kjVec2i kj_vec2i_all(i32 a) {
    return kj_vec2i(a, a);
}

KJ_CONST KJ_INLINE kjVec2u kj_vec2u_all(u32 a) {
    return kj_vec2u(a, a);
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_negate(kjVec2f a) {
    return kj_vec2f(-a.x, -a.y);
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_add(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x + b.x, a.y + b.y);
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_sub(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x - b.x, a.y - b.y);
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_mul(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x * b.x, a.y * b.y);
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_mulf(kjVec2f a, f32 b) {
    return kj_vec2f(a.x * b, a.y * b);
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_div(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x * (1.0f / b.x), a.y * (1.0f / b.y));
}

KJ_CONST KJ_INLINE f32 kj_vec2f_dot(kjVec2f a, kjVec2f b) {
    return (a.x * b.x + a.y * b.y);
}

KJ_CONST KJ_INLINE f32 kj_vec2f_cross(kjVec2f a, kjVec2f b) {
    return (a.x * b.y - b.x * a.y);
}

KJ_CONST KJ_INLINE f32 kj_vec2f_length_sq(kjVec2f a) {
    return kj_vec2f_dot(a, a);
}

KJ_CONST KJ_INLINE f32 kj_vec2f_length(kjVec2f a) {
    return kj_sqrtf(kj_vec2f_length_sq(a));
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_normalise(kjVec2f a) {
    return kj_vec2f_div(a, kj_vec2f_all(kj_vec2f_length(a)));
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_clamp(kjVec2f a, kjVec2f min, kjVec2f max) {
    return kj_vec2f(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y));
}

KJ_CONST KJ_INLINE kjVec2i kj_vec2i_clamp(kjVec2i a, kjVec2i min, kjVec2i max) {
    return kj_vec2i(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y));
}

KJ_CONST KJ_INLINE kjVec2u kj_vec2u_clamp(kjVec2u a, kjVec2u min, kjVec2u max) {
    return kj_vec2u(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y));
}

KJ_CONST KJ_INLINE kjVec2f kj_vec2f_clampf(kjVec2f a, f32 min, f32 max) {
    return kj_vec2f_clamp(a, kj_vec2f_all(min), kj_vec2f_all(max));
}

KJ_CONST KJ_INLINE kjVec2i kj_vec2i_clampi(kjVec2i a, i32 min, i32 max) {
    return kj_vec2i_clamp(a, kj_vec2i_all(min), kj_vec2i_all(max));
}

KJ_CONST KJ_INLINE kjVec2u kj_vec2u_clampu(kjVec2u a, u32 min, u32 max) {
    return kj_vec2u_clamp(a, kj_vec2u_all(min), kj_vec2u_all(max));
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f(f32 x, f32 y, f32 z) {
    kjVec3f res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_CONST KJ_INLINE kjVec3i kj_vec3i(i32 x, i32 y, i32 z) {
    kjVec3i res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_CONST KJ_INLINE kjVec3u kj_vec3u(u32 x, u32 y, u32 z) {
    kjVec3u res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_zero(void) {
    return kj_vec3f(0.0f, 0.0f, 0.0f);
}

KJ_CONST KJ_INLINE kjVec3i kj_vec3i_zero(void) {
    return kj_vec3i(0, 0, 0);
}

KJ_CONST KJ_INLINE kjVec3u kj_vec3u_zero(void) {
    return kj_vec3u(0, 0, 0);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_one(void) {
    return kj_vec3f(1.0f, 1.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjVec3i kj_vec3i_one(void) {
    return kj_vec3i(1, 1, 1);
}

KJ_CONST KJ_INLINE kjVec3u kj_vec3u_one(void) {
    return kj_vec3u(1, 1, 1);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_all(f32 a) {
    return kj_vec3f(a, a, a);
}

KJ_CONST KJ_INLINE kjVec3i kj_vec3i_all(i32 a) {
    return kj_vec3i(a, a, a);
}

KJ_CONST KJ_INLINE kjVec3u kj_vec3u_all(u32 a) {
    return kj_vec3u(a, a, a);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_negate(kjVec3f a) {
    return kj_vec3f(-a.x, -a.y, -a.z);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_add(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_sub(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_mul(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_mulf(kjVec3f a, f32 b) {
    return kj_vec3f(a.x * b, a.y * b, a.z * b);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_div(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x * (1.0f / b.x), a.y * (1.0f / b.y), a.z * (1.0f / b.z));
}

KJ_CONST KJ_INLINE f32 kj_vec3f_dot(kjVec3f a, kjVec3f b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_cross(kjVec3f a, kjVec3f b) {
    return kj_vec3f(
            a.y * b.z - b.y * a.z,
            a.z * b.x - b.z * a.x,
            a.x * b.y - b.x * a.y);
}

KJ_CONST KJ_INLINE f32 kj_vec3f_length_sq(kjVec3f a) {
    return kj_vec3f_dot(a, a);
}

KJ_CONST KJ_INLINE f32 kj_vec3f_length(kjVec3f a) {
    return kj_sqrtf(kj_vec3f_length_sq(a));
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_normalise(kjVec3f a) {
    return kj_vec3f_div(a, kj_vec3f_all(kj_vec3f_length(a)));
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_clamp(kjVec3f a, kjVec3f b, kjVec3f c) {
    return kj_vec3f(
            kj_clamp(a.x, b.x, c.x),
            kj_clamp(a.y, b.y, c.y),
            kj_clamp(a.z, b.z, c.z));
}

KJ_CONST KJ_INLINE kjVec3i kj_vec3i_clamp(kjVec3i a, kjVec3i b, kjVec3i c) {
    return kj_vec3i(
            kj_clamp(a.x, b.x, c.x),
            kj_clamp(a.y, b.y, c.y),
            kj_clamp(a.z, b.z, c.z));
}

KJ_CONST KJ_INLINE kjVec3u kj_vec3u_clamp(kjVec3u a, kjVec3u b, kjVec3u c) {
    return kj_vec3u(
            kj_clamp(a.x, b.x, c.x),
            kj_clamp(a.y, b.y, c.y),
            kj_clamp(a.z, b.z, c.z));
}

KJ_CONST KJ_INLINE kjVec3f kj_vec3f_clampf(kjVec3f a, f32 min, f32 max) {
    return kj_vec3f_clamp(a, kj_vec3f_all(min), kj_vec3f_all(max));
}

KJ_CONST KJ_INLINE kjVec3i kj_vec3i_clampi(kjVec3i a, i32 min, i32 max) {
    return kj_vec3i_clamp(a, kj_vec3i_all(min), kj_vec3i_all(max));
}

KJ_CONST KJ_INLINE kjVec3u kj_vec3u_clampu(kjVec3u a, u32 min, u32 max) {
    return kj_vec3u_clamp(a, kj_vec3u_all(min), kj_vec3u_all(max));
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f(f32 x, f32 y, f32 z, f32 w) {
    kjVec4f res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_CONST KJ_INLINE kjVec4i kj_vec4i(i32 x, i32 y, i32 z, i32 w) {
    kjVec4i res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_CONST KJ_INLINE kjVec4u kj_vec4u(u32 x, u32 y, u32 z, u32 w) {
    kjVec4u res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_zero(void) {
    return kj_vec4f(0.0f, 0.0f, 0.0f, 0.0f);
}

KJ_CONST KJ_INLINE kjVec4i kj_vec4i_zero(void) {
    return kj_vec4i(0, 0, 0, 0);
}

KJ_CONST KJ_INLINE kjVec4u kj_vec4u_zero(void) {
    return kj_vec4u(0, 0, 0, 0);
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_one(void) {
    return kj_vec4f(1.0f, 1.0f, 1.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjVec4i kj_vec4i_one(void) {
    return kj_vec4i(1, 1, 1, 1);
}

KJ_CONST KJ_INLINE kjVec4u kj_vec4u_one(void) {
    return kj_vec4u(1, 1, 1, 1);
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_all(f32 a) {
    return kj_vec4f(a, a, a, a);
}

KJ_CONST KJ_INLINE kjVec4i kj_vec4i_all(i32 a) {
    return kj_vec4i(a, a, a, a);
}

KJ_CONST KJ_INLINE kjVec4u kj_vec4u_all(u32 a) {
    return kj_vec4u(a, a, a, a);
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_negate(kjVec4f a) {
    return kj_vec4f(-a.x, -a.y, -a.z, -a.w);
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_add(kjVec4f a, kjVec4f b) {
    return kj_vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_sub(kjVec4f a, kjVec4f b) {
    return kj_vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_mul(kjVec4f a, kjVec4f b) {
    return kj_vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_mulf(kjVec4f a, f32 b) {
    return kj_vec4f(a.x * b, a.y * b, a.z * b, a.w * b);
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_div(kjVec4f a, kjVec4f b) {
    return kj_vec4f(
            a.x * (1.0f / b.x), a.y * (1.0f / b.y),
            a.z * (1.0f / b.z), a.w * (1.0f / b.w));
}

KJ_CONST KJ_INLINE f32 kj_vec4f_dot(kjVec4f a, kjVec4f b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

KJ_CONST KJ_INLINE f32 kj_vec4f_length_sq(kjVec4f a) {
    return kj_vec4f_dot(a, a);
}

KJ_CONST KJ_INLINE f32 kj_vec4f_length(kjVec4f a) {
    return kj_sqrtf(kj_vec4f_length_sq(a));
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_normalise(kjVec4f a) {
    return kj_vec4f_div(a, kj_vec4f_all(kj_vec4f_length(a)));
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_clamp(kjVec4f a, kjVec4f min, kjVec4f max) {
    return kj_vec4f(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y),
            kj_clamp(a.z, min.z, max.z),
            kj_clamp(a.w, min.w, max.w));
}

KJ_CONST KJ_INLINE kjVec4i kj_vec4i_clamp(kjVec4i a, kjVec4i min, kjVec4i max) {
    return kj_vec4i(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y),
            kj_clamp(a.z, min.z, max.z),
            kj_clamp(a.w, min.w, max.w));
}

KJ_CONST KJ_INLINE kjVec4u kj_vec4u_clamp(kjVec4u a, kjVec4u min, kjVec4u max) {
    return kj_vec4u(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y),
            kj_clamp(a.z, min.z, max.z),
            kj_clamp(a.w, min.w, max.w));
}

KJ_CONST KJ_INLINE kjVec4f kj_vec4f_clampf(kjVec4f a, f32 min, f32 max) {
    return kj_vec4f_clamp(a, kj_vec4f_all(min), kj_vec4f_all(max));
}

KJ_CONST KJ_INLINE kjVec4i kj_vec4i_clampi(kjVec4i a, i32 min, i32 max) {
    return kj_vec4i_clamp(a, kj_vec4i_all(min), kj_vec4i_all(max));
}

KJ_CONST KJ_INLINE kjVec4u kj_vec4u_clampu(kjVec4u a, u32 min, u32 max) {
    return kj_vec4u_clamp(a, kj_vec4u_all(min), kj_vec4u_all(max));
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f(
        f32 e00, f32 e10, f32 e20,
        f32 e01, f32 e11, f32 e21,
        f32 e02, f32 e12, f32 e22) {
    kjMat3f res;
    res.e[0][0] = e00;
    res.e[1][0] = e10;
    res.e[2][0] = e20;
    res.e[0][1] = e01;
    res.e[1][1] = e11;
    res.e[2][1] = e21;
    res.e[0][2] = e02;
    res.e[1][2] = e12;
    res.e[2][2] = e22;
    return res;
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_diag(f32 e00, f32 e11, f32 e22) {
    return kj_mat3f(e00, 0.0f, 0.0f, 0.0f, e11, 0.0f, 0.0f, 0.0f, e22);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_ident(void) {
    return kj_mat3f_diag(1.0f, 1.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_zero(void) {
    kjMat3f res;
    kj_mem_zero(&res, kj_isize_of(kjMat3f));
    return res;
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_one(void) {
    return kj_mat3f(
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_mul(kjMat3f a, kjMat3f b) {
    kjMat3f res;
    kjVec3f bv0 = kj_vec3f(b.v[0].x, b.v[1].x, b.v[2].x);
    kjVec3f bv1 = kj_vec3f(b.v[0].y, b.v[1].y, b.v[2].y);
    kjVec3f bv2 = kj_vec3f(b.v[0].z, b.v[1].z, b.v[2].z);
    res.v[0] = kj_vec3f_add(
            kj_vec3f_add(kj_vec3f_mul(a.v[0], bv0), kj_vec3f_mul(a.v[0], bv1)),
            kj_vec3f_mul(a.v[0], bv2));
    res.v[1] = kj_vec3f_add(
            kj_vec3f_add(kj_vec3f_mul(a.v[1], bv0), kj_vec3f_mul(a.v[1], bv1)),
            kj_vec3f_mul(a.v[1], bv2));
    res.v[2] = kj_vec3f_add(
            kj_vec3f_add(kj_vec3f_mul(a.v[2], bv0), kj_vec3f_mul(a.v[2], bv1)),
            kj_vec3f_mul(a.v[2], bv2));
    return res;
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_transpose(kjMat3f a) {
    return kj_mat3f(
            a.e[0][0], a.e[1][0], a.e[2][0],
            a.e[0][1], a.e[1][1], a.e[2][1],
            a.e[0][2], a.e[1][2], a.e[2][2]);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_translate(f32 x, f32 y) {
    return kj_mat3f(
            1.0f, 0.0f, x,
            0.0f, 1.0f, y,
            0.0f, 0.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_translate_vec2f(kjVec2f xy) {
    return kj_mat3f_translate(xy.x, xy.y);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_rotate(f32 angle, f32 x, f32 y, f32 z) {
    return kj_mat3f_rotate_vec3f(angle, kj_vec3f(x, y, z));
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_rotate_x(f32 angle) {
    return kj_mat3f_rotate(angle, 1.0f, 0.0f, 0.0f);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_rotate_y(f32 angle) {
    return kj_mat3f_rotate(angle, 0.0f, 1.0f, 0.0f);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_rotate_z(f32 angle) {
    return kj_mat3f_rotate(angle, 0.0f, 0.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_rotate_vec3f(f32 angle, kjVec3f xyz) {
    kjMat3f res;
    f32 c = kj_cosf(angle);
    f32 s = kj_sinf(angle);

    kjVec3f axis = kj_vec3f_normalise(xyz);
    kjVec3f rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - c));
    res.e[0][0] = c + rot_axis.x * axis.x;
    res.e[0][1] = 0.0f + rot_axis.x * axis.y + s * axis.z;
    res.e[0][2] = 0.0f + rot_axis.x * axis.z - s * axis.y;
    res.e[1][0] = 0.0f + rot_axis.y * axis.x - s * axis.z;
    res.e[1][1] = c + rot_axis.y * axis.y;
    res.e[1][2] = 0.0f + rot_axis.y * axis.z + s * axis.x;
    res.e[2][0] = 0.0f + rot_axis.z * axis.x + s * axis.y;
    res.e[2][1] = 0.0f + rot_axis.z * axis.y - s * axis.x;
    res.e[2][2] = c + rot_axis.z * axis.z;
    return res;
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_scale(f32 x, f32 y, f32 z) {
    return kj_mat3f_diag(x, y, z);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_scale_uniform(f32 a) {
    return kj_mat3f_diag(a, a, a);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_scale_vec3f(kjVec3f xyz) {
    return kj_mat3f_diag(xyz.x, xyz.y, xyz.z);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f(
        f32 e00, f32 e10, f32 e20, f32 e30,
        f32 e01, f32 e11, f32 e21, f32 e31,
        f32 e02, f32 e12, f32 e22, f32 e32,
        f32 e03, f32 e13, f32 e23, f32 e33) {
    kjMat4f res;
    res.e[0][0] = e00;
    res.e[1][0] = e10;
    res.e[2][0] = e20;
    res.e[3][0] = e30;
    res.e[0][1] = e01;
    res.e[1][1] = e11;
    res.e[2][1] = e21;
    res.e[3][1] = e31;
    res.e[0][2] = e02;
    res.e[1][2] = e12;
    res.e[2][2] = e22;
    res.e[3][2] = e32;
    res.e[0][3] = e03;
    res.e[1][3] = e13;
    res.e[2][3] = e23;
    res.e[3][3] = e33;
    return res;
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_diag(f32 e00, f32 e11, f32 e22, f32 e33) {
    return kj_mat4f(
            e00, 0.0f, 0.0f, 0.0f,
            0.0f, e11, 0.0f, 0.0f,
            0.0f, 0.0f, e22, 0.0f,
            0.0f, 0.0f, 0.0f, e33);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_ident(void) {
    return kj_mat4f_diag(1.0f, 1.0f, 1.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_zero(void) {
    kjMat4f res;
    kj_mem_zero(&res, kj_isize_of(kjMat4f));
    return res;
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_one(void) {
    return kj_mat4f(
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_mul(kjMat4f a, kjMat4f b) {
    kjMat4f res;
    res.e[0][0] =
        a.e[0][0] * b.e[0][0] + a.e[1][0] * b.e[0][1] +
        a.e[2][0] * b.e[0][2] + a.e[3][0] * b.e[0][3];
    res.e[0][1] =
        a.e[0][1] * b.e[0][0] + a.e[1][1] * b.e[0][1] +
        a.e[2][1] * b.e[0][2] + a.e[3][1] * b.e[0][3];
    res.e[0][2] =
        a.e[0][2] * b.e[0][0] + a.e[1][2] * b.e[0][1] +
        a.e[2][2] * b.e[0][2] + a.e[3][2] * b.e[0][3];
    res.e[0][3] =
        a.e[0][3] * b.e[0][0] + a.e[1][3] * b.e[0][1] +
        a.e[2][3] * b.e[0][2] + a.e[3][3] * b.e[0][3];

    res.e[1][0] =
        a.e[0][0] * b.e[1][0] + a.e[1][0] * b.e[1][1] +
        a.e[2][0] * b.e[1][2] + a.e[3][0] * b.e[1][3];
    res.e[1][1] =
        a.e[0][1] * b.e[1][0] + a.e[1][1] * b.e[1][1] +
        a.e[2][1] * b.e[1][2] + a.e[3][1] * b.e[1][3];
    res.e[1][2] =
        a.e[0][2] * b.e[1][0] + a.e[1][2] * b.e[1][1] +
        a.e[2][2] * b.e[1][2] + a.e[3][2] * b.e[1][3];
    res.e[1][3] =
        a.e[0][3] * b.e[1][0] + a.e[1][3] * b.e[1][1] +
        a.e[2][3] * b.e[1][2] + a.e[3][3] * b.e[1][3];

    res.e[2][0] =
        a.e[0][0] * b.e[2][0] + a.e[1][0] * b.e[2][1] +
        a.e[2][0] * b.e[2][2] + a.e[3][0] * b.e[2][3];
    res.e[2][1] =
        a.e[0][1] * b.e[2][0] + a.e[1][1] * b.e[2][1] +
        a.e[2][1] * b.e[2][2] + a.e[3][1] * b.e[2][3];
    res.e[2][2] =
        a.e[0][2] * b.e[2][0] + a.e[1][2] * b.e[2][1] +
        a.e[2][2] * b.e[2][2] + a.e[3][2] * b.e[2][3];
    res.e[2][3] =
        a.e[0][3] * b.e[2][0] + a.e[1][3] * b.e[2][1] +
        a.e[2][3] * b.e[2][2] + a.e[3][3] * b.e[2][3];

    res.e[3][0] =
        a.e[0][0] * b.e[3][0] + a.e[1][0] * b.e[3][1] +
        a.e[2][0] * b.e[3][2] + a.e[3][0] * b.e[3][3];
    res.e[3][1] =
        a.e[0][1] * b.e[3][0] + a.e[1][1] * b.e[3][1] +
        a.e[2][1] * b.e[3][2] + a.e[3][1] * b.e[3][3];
    res.e[3][2] =
        a.e[0][2] * b.e[3][0] + a.e[1][2] * b.e[3][1] +
        a.e[2][2] * b.e[3][2] + a.e[3][2] * b.e[3][3];
    res.e[3][3] =
        a.e[0][3] * b.e[3][0] + a.e[1][3] * b.e[3][1] +
        a.e[2][3] * b.e[3][2] + a.e[3][3] * b.e[3][3];
    return res;
}

KJ_CONST KJ_INLINE kjVec4f kj_mat4f_mul_vec4f(kjMat4f a, kjVec4f b) {
    return kj_vec4f(
        a.e[0][0] * b.x + a.e[1][0] * b.y + a.e[2][0] * b.z + a.e[3][0] * b.w,
        a.e[0][1] * b.x + a.e[1][1] * b.y + a.e[2][1] * b.z + a.e[3][1] * b.w,
        a.e[0][2] * b.x + a.e[1][2] * b.y + a.e[2][2] * b.z + a.e[3][2] * b.w,
        a.e[0][3] * b.x + a.e[1][3] * b.y + a.e[2][3] * b.z + a.e[3][3] * b.w);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_transpose(kjMat4f a) {
    return kj_mat4f(
            a.e[0][0], a.e[1][0], a.e[2][0], a.e[3][0],
            a.e[0][1], a.e[1][1], a.e[2][1], a.e[3][1],
            a.e[0][2], a.e[1][2], a.e[2][2], a.e[3][2],
            a.e[0][3], a.e[1][3], a.e[2][3], a.e[3][3]);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_translate(f32 x, f32 y, f32 z) {
    return kj_mat4f(
            1.0f, 0.0f, 0.0f, x,
            0.0f, 1.0f, 0.0f, y,
            0.0f, 0.0f, 1.0f, z,
            0.0f, 0.0f, 0.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_translate_vec3f(kjVec3f xyz) {
    return kj_mat4f_translate(xyz.x, xyz.y, xyz.z);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_rotate(f32 angle, f32 x, f32 y, f32 z) {
    return kj_mat4f_rotate_vec3f(angle, kj_vec3f(x, y, z));
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_rotate_x(f32 angle) {
    return kj_mat4f_rotate(angle, 1.0f, 0.0f, 0.0f);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_rotate_y(f32 angle) {
    return kj_mat4f_rotate(angle, 0.0f, 1.0f, 0.0f);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_rotate_z(f32 angle) {
    return kj_mat4f_rotate(angle, 0.0f, 0.0f, 1.0f);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_rotate_vec3f(f32 angle, kjVec3f xyz) {
    kjMat4f res = kj_mat4f_ident();
    f32 c = kj_cosf(angle);
    f32 s = kj_sinf(angle);

    kjVec3f axis = kj_vec3f_normalise(xyz);
    kjVec3f rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - c));
    res.e[0][0] = c + rot_axis.x * axis.x;
    res.e[0][1] = 0.0f + rot_axis.x * axis.y + s * axis.z;
    res.e[0][2] = 0.0f + rot_axis.x * axis.z - s * axis.y;
    res.e[0][3] = 0.0f;
    res.e[1][0] = 0.0f + rot_axis.y * axis.x - s * axis.z;
    res.e[1][1] = c + rot_axis.y * axis.y;
    res.e[1][2] = 0.0f + rot_axis.y * axis.z + s * axis.x;
    res.e[1][3] = 0.0f;
    res.e[2][0] = 0.0f + rot_axis.z * axis.x + s * axis.y;
    res.e[2][1] = 0.0f + rot_axis.z * axis.y - s * axis.x;
    res.e[2][2] = c + rot_axis.z * axis.z;
    res.e[2][3] = 0.0f;
    return res;
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_scale(f32 x, f32 y, f32 z) {
    return kj_mat4f_diag(x, y, z, 1.0f);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_scale_uniform(f32 a) {
    return kj_mat4f_diag(a, a, a, 1.0f);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz) {
    return kj_mat4f_scale(xyz.x, xyz.y, xyz.z);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_ortho(
        f32 l, f32 r, f32 b, f32 t, f32 znear, f32 zfar) {
    kjMat4f res = kj_mat4f_ident();
    f32 rl = r - l + F32_EPS;
    f32 tb = t - b + F32_EPS;
    f32 fn = zfar - znear + F32_EPS;

    res.e[0][0] = 2.0f / rl;
    res.e[1][1] = 2.0f / tb;
    res.e[2][2] = -1.0f / fn;
    res.e[3][0] = -(r + l) / rl;
    res.e[3][1] = -(t + b) / tb;
    res.e[3][2] = -(zfar + znear) / fn;
    return res;
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_ortho_inf(f32 l, f32 r, f32 t, f32 b) {
    kjMat4f res = kj_mat4f_ident();
    f32 rl = r - l + F32_EPS;
    f32 tb = t - b + F32_EPS;

    res.e[0][0] = 2.0f / rl;
    res.e[1][1] = 2.0f / tb;
    res.e[2][2] = -1.0f;
    res.e[3][0] = -(r + l) / rl;
    res.e[3][1] = -(t + b) / tb;
    return res;
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_perspective(
        f32 fovy, f32 aspect, f32 znear, f32 zfar) {
    kjMat4f res = kj_mat4f_zero();
    if(aspect > 0.0f) {
        f32 tanfovy = kj_tanf(0.5f * fovy);
        res.e[0][0] = 1.0f / (aspect * tanfovy);
        res.e[1][1] = 1.0f / tanfovy;
        res.e[2][2] = -(zfar + znear) / (zfar - znear);
        res.e[2][3] = -1.0f;
        res.e[3][2] = -(2.0f * zfar * znear) / (zfar - znear);
    }
    return res;
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_perspective_inf(
        f32 fovy, f32 aspect, f32 znear) {
    kjMat4f res = kj_mat4f_zero();
    if(aspect > 0.0f) {
        f32 range = kj_tanf(0.5f * fovy) * znear;
        res.e[0][0] = (2.0f * znear) / ((range * aspect) - (-range * aspect));
        res.e[1][1] = (2.0f * znear) / (range - -range);
        res.e[2][2] = -1.0f;
        res.e[2][3] = -1.0f;
        res.e[3][2] = -2.0f * znear;
    }
    return res;
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_look_at(
        kjVec3f eye, kjVec3f target, kjVec3f up) {
    kjMat4f res;
    kjVec3f f = kj_vec3f_normalise(kj_vec3f_sub(target, eye));
    kjVec3f s = kj_vec3f_normalise(kj_vec3f_cross(f, up));
    kjVec3f u = kj_vec3f_cross(s, f);

    res.e[0][0] = s.x;
    res.e[1][0] = s.y;
    res.e[2][0] = s.z;
    res.e[3][0] = -kj_vec3f_dot(s, eye);
    res.e[0][1] = u.x;
    res.e[1][1] = u.y;
    res.e[2][1] = u.z;
    res.e[3][1] = -kj_vec3f_dot(u, eye);
    res.e[0][2] = -f.x;
    res.e[1][2] = -f.y;
    res.e[2][2] = -f.z;
    res.e[3][2] = kj_vec3f_dot(f, eye);
    res.e[0][3] = 0.0f;
    res.e[1][3] = 0.0f;
    res.e[2][3] = 0.0f;
    res.e[3][3] = 1.0f;
    return res;
}

#if defined(__cplusplus)
KJ_CONST KJ_INLINE kjMat3f kj_mat3f(f32 e00, f32 e11, f32 e22) {
    return kj_mat3f_diag(e00, e11, e22);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f(void) {
    return kj_mat3f_ident();
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_rotate(f32 angle, kjVec3f xyz) {
    return kj_mat3f_rotate_vec3f(angle, xyz);
}

KJ_CONST KJ_INLINE kjMat3f kj_mat3f_scale(kjVec3f xyz) {
    return kj_mat3f_scale_vec3f(xyz);
}

KJ_CONST KJ_INLINE kjMat3f operator*(kjMat3f a, kjMat3f b) {
    return kj_mat3f_mul(a, b);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f(f32 e00, f32 e11, f32 e22, f32 e33) {
    return kj_mat4f_diag(e00, e11, e22, e33);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f(void) {
    return kj_mat4f_ident();
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_translate(kjVec3f xyz) {
    return kj_mat4f_translate_vec3f(xyz);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_rotate(f32 angle, kjVec3f xyz) {
    return kj_mat4f_rotate_vec3f(angle, xyz);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_scale(f32 a) {
    return kj_mat4f_scale_uniform(a);
}

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_scale(kjVec3f xyz) {
    return kj_mat4f_scale_vec3f(xyz);
}

KJ_CONST KJ_INLINE kjMat4f operator*(kjMat4f a, kjMat4f b) {
    return kj_mat4f_mul(a, b);
}
#endif

KJ_CONST KJ_INLINE kjRect2f kj_rect2f(f32 x1, f32 y1, f32 x2, f32 y2) {
    kjRect2f res;
    res.min = kj_vec2f(x1, y1);
    res.max = kj_vec2f(x2, y2);
    return res;
}

KJ_CONST KJ_INLINE kjRect2i kj_rect2i(i32 x1, i32 y1, i32 x2, i32 y2) {
    kjRect2i res;
    res.min = kj_vec2i(x1, y1);
    res.max = kj_vec2i(x2, y2);
    return res;
}

KJ_CONST KJ_INLINE kjRect2u kj_rect2u(u32 x1, u32 y1, u32 x2, u32 y2) {
    kjRect2u res;
    res.min = kj_vec2u(x1, y1);
    res.max = kj_vec2u(x2, y2);
    return res;
}

KJ_CONST KJ_INLINE kjRect3f kj_rect3f(
        f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2) {
    kjRect3f res;
    res.min = kj_vec3f(x1, y1, z1);
    res.max = kj_vec3f(x2, y2, z2);
    return res;
}

KJ_CONST KJ_INLINE kjRect3i kj_rect3i(
        i32 x1, i32 y1, i32 z1, i32 x2, i32 y2, i32 z2) {
    kjRect3i res;
    res.min = kj_vec3i(x1, y1, z1);
    res.max = kj_vec3i(x2, y2, z2);
    return res;
}

KJ_CONST KJ_INLINE kjRect3u kj_rect3u(
        u32 x1, u32 y1, u32 z1, u32 x2, u32 y2, u32 z2) {
    kjRect3u res;
    res.min = kj_vec3u(x1, y1, z1);
    res.max = kj_vec3u(x2, y2, z2);
    return res;
}

KJ_CONST KJ_INLINE kjRgba kj_rgba(u8 r, u8 g, u8 b, u8 a) {
    kjRgba res;
    res.r = r;
    res.b = b;
    res.g = g;
    res.a = a;
    return res;
}

KJ_CONST KJ_INLINE kjRgba kj_rgba_4f(f32 r, f32 g, f32 b, f32 a) {
    return kj_rgba(
        kj_cast(u8, r * 255.0f + 0.5f),
        kj_cast(u8, g * 255.0f + 0.5f),
        kj_cast(u8, b * 255.0f + 0.5f),
        kj_cast(u8, a * 255.0f + 0.5f));
}

KJ_CONST KJ_INLINE kjRgba kj_rgba_rgbaf(kjVec4f rgbaf) {
    return kj_rgba_4f(rgbaf.x, rgbaf.y, rgbaf.z, rgbaf.w);
}

KJ_CONST KJ_INLINE u32 kj_rgba_pack(kjRgba rgba) {
    return (rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | (rgba.a << 0);
}

KJ_CONST KJ_INLINE kjRgba kj_rgba_unpack(u32 packed) {
    return kj_rgba(
        kj_cast(u8, (packed & 0xFF000000) >> 24),
        kj_cast(u8, (packed & 0x00FF0000) >> 16),
        kj_cast(u8, (packed & 0x0000FF00) >> 8),
        kj_cast(u8, (packed & 0x000000FF) >> 0));
}

KJ_CONST KJ_INLINE kjVec4f kj_rgbaf(f32 r, f32 g, f32 b, f32 a) {
    kjVec4f res;
    res.x = r;
    res.y = g;
    res.z = b;
    res.w = a;
    return res;
}

KJ_CONST KJ_INLINE kjVec4f kj_rgbaf_4u8(u8 r, u8 g, u8 b, u8 a) {
    return kj_rgbaf(
        kj_cast(f32, r * (1.0f / 255.0f)),
        kj_cast(f32, g * (1.0f / 255.0f)),
        kj_cast(f32, b * (1.0f / 255.0f)),
        kj_cast(f32, a * (1.0f / 255.0f)));
}

KJ_CONST KJ_INLINE kjVec4f kj_rgbaf_rgba(kjRgba rgba) {
    return kj_rgbaf_4u8(rgba.r, rgba.g, rgba.b, rgba.a);
}

KJ_CONST KJ_INLINE u32 kj_rgbaf_pack(kjVec4f rgba) {
    return
        (kj_cast(u8, rgba.x * 255.0f) << 24) |
        (kj_cast(u8, rgba.y * 255.0f) << 16) |
        (kj_cast(u8, rgba.z * 255.0f) << 8)  |
        (kj_cast(u8, rgba.w * 255.0f) << 0);
}

KJ_CONST KJ_INLINE kjVec4f kj_rgbaf_unpack(u32 packed) {
    return kj_rgbaf(
        kj_cast(f32, ((packed & 0xFF000000) >> 24) * (1.0f / 255.0f)),
        kj_cast(f32, ((packed & 0x00FF0000) >> 16) * (1.0f / 255.0f)),
        kj_cast(f32, ((packed & 0x0000FF00) >> 8)  * (1.0f / 255.0f)),
        kj_cast(f32, ((packed & 0x000000FF) >> 0)  * (1.0f / 255.0f)));
}

#endif
