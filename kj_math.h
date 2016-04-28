// `kj_math.h`
// public domain - no offered or implied warranty, use at your own risk

#ifndef KJ_MATH_H
#define KJ_MATH_H

#define KJ_MATH_VERSION_MAJOR 0
#define KJ_MATH_VERSION_MINOR 1
#define KJ_MATH_VERSION_PATCH 1

#define kj_degrees(a) ((a) * 57.295779513082320f)
#define kj_radians(a) ((a) * 0.017453292519943f)

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
    f32 x, y, w, h;
} kjRect2f;

typedef struct kjRect2i {
    i32 x, y, w, h;
} kjRect2i;

typedef struct kjRect2u {
    u32 x, y, w, h;
} kjRect2u;

typedef struct kjRect3f {
    f32 x, y, z, w, h, d;
} kjRect3f;

typedef struct kjRect3i {
    i32 x, y, z, w, h, d;
} kjRect3i;

typedef struct kjRect3u {
    u32 x, y, z, w, h, d;
} kjRect3u;

#if defined(__cplusplus)
extern "C" {
#endif

KJ_API f32 kj_rsqrtf(f32 a);
KJ_API f32 kj_sqrtf(f32 a);
KJ_API f32 kj_sinf(f32 radians);
KJ_API f32 kj_cosf(f32 radians);
KJ_API f32 kj_tanf(f32 radians);
KJ_API f32 kj_asinf(f32 a);
KJ_API f32 kj_acosf(f32 a);
KJ_API f32 kj_atanf(f32 a);
KJ_API f32 kj_atan2f(f32 y, f32 x);
KJ_API f32 kj_expf(f32 x);
KJ_API f32 kj_logf(f32 x);
KJ_API f32 kj_powf(f32 x, f32 y);

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
KJ_API kjVec2i kj_vec2i_negate(kjVec2i a);
KJ_API kjVec2u kj_vec2u_negate(kjVec2u a);
KJ_API kjVec2f kj_vec2f_add(kjVec2f a, kjVec2f b);
KJ_API kjVec2i kj_vec2i_add(kjVec2i a, kjVec2i b);
KJ_API kjVec2u kj_vec2u_add(kjVec2u a, kjVec2u b);
KJ_API kjVec2f kj_vec2f_sub(kjVec2f a, kjVec2f b);
KJ_API kjVec2i kj_vec2i_sub(kjVec2i a, kjVec2i b);
KJ_API kjVec2u kj_vec2u_sub(kjVec2u a, kjVec2u b);
KJ_API kjVec2f kj_vec2f_mul(kjVec2f a, kjVec2f b);
KJ_API kjVec2i kj_vec2i_mul(kjVec2i a, kjVec2i b);
KJ_API kjVec2u kj_vec2u_mul(kjVec2u a, kjVec2u b);
KJ_API kjVec2f kj_vec2f_mulf(kjVec2f a, f32 b);
KJ_API kjVec2i kj_vec2i_muli(kjVec2i a, i32 b);
KJ_API kjVec2u kj_vec2u_mulu(kjVec2u a, u32 b);
KJ_API kjVec2f kj_vec2f_div(kjVec2f a, kjVec2f b);
KJ_API kjVec2i kj_vec2i_div(kjVec2i a, kjVec2i b);
KJ_API kjVec2u kj_vec2u_div(kjVec2u a, kjVec2u b);
KJ_API f32 kj_vec2f_dot(kjVec2f a, kjVec2f b);
KJ_API i32 kj_vec2i_dot(kjVec2i a, kjVec2i b);
KJ_API u32 kj_vec2u_dot(kjVec2u a, kjVec2u b);
KJ_API f32 kj_vec2f_cross(kjVec2f a, kjVec2f b);
KJ_API i32 kj_vec2i_cross(kjVec2i a, kjVec2i b);
KJ_API u32 kj_vec2u_cross(kjVec2u a, kjVec2u b);
KJ_API f32 kj_vec2f_length_sq(kjVec2f a);
KJ_API i32 kj_vec2i_length_sq(kjVec2i a);
KJ_API u32 kj_vec2u_length_sq(kjVec2u a);
KJ_API f32 kj_vec2f_length(kjVec2f a);
KJ_API i32 kj_vec2i_length(kjVec2i a);
KJ_API u32 kj_vec2u_length(kjVec2u a);
KJ_API kjVec2f kj_vec2f_normalise(kjVec2f a);
KJ_API kjVec2i kj_vec2i_normalise(kjVec2i a);
KJ_API kjVec2u kj_vec2u_normalise(kjVec2u a);

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
KJ_API kjVec3i kj_vec3i_negate(kjVec3i a);
KJ_API kjVec3u kj_vec3u_negate(kjVec3u a);
KJ_API kjVec3f kj_vec3f_add(kjVec3f a, kjVec3f b);
KJ_API kjVec3i kj_vec3i_add(kjVec3i a, kjVec3i b);
KJ_API kjVec3u kj_vec3u_add(kjVec3u a, kjVec3u b);
KJ_API kjVec3f kj_vec3f_sub(kjVec3f a, kjVec3f b);
KJ_API kjVec3i kj_vec3i_sub(kjVec3i a, kjVec3i b);
KJ_API kjVec3u kj_vec3u_sub(kjVec3u a, kjVec3u b);
KJ_API kjVec3f kj_vec3f_mul(kjVec3f a, kjVec3f b);
KJ_API kjVec3i kj_vec3i_mul(kjVec3i a, kjVec3i b);
KJ_API kjVec3u kj_vec3u_mul(kjVec3u a, kjVec3u b);
KJ_API kjVec3f kj_vec3f_mulf(kjVec3f a, f32 b);
KJ_API kjVec3i kj_vec3i_muli(kjVec3i a, i32 b);
KJ_API kjVec3u kj_vec3u_mulu(kjVec3u a, u32 b);
KJ_API kjVec3f kj_vec3f_div(kjVec3f a, kjVec3f b);
KJ_API kjVec3i kj_vec3i_div(kjVec3i a, kjVec3i b);
KJ_API kjVec3u kj_vec3u_div(kjVec3u a, kjVec3u b);
KJ_API f32 kj_vec3f_dot(kjVec3f a, kjVec3f b);
KJ_API i32 kj_vec3i_dot(kjVec3i a, kjVec3i b);
KJ_API u32 kj_vec3u_dot(kjVec3u a, kjVec3u b);
KJ_API kjVec3f kj_vec3f_cross(kjVec3f a, kjVec3f b);
KJ_API kjVec3i kj_vec3i_cross(kjVec3i a, kjVec3i b);
KJ_API kjVec3u kj_vec3u_cross(kjVec3u a, kjVec3u b);
KJ_API f32 kj_vec3f_length_sq(kjVec3f a);
KJ_API i32 kj_vec3i_length_sq(kjVec3i a);
KJ_API u32 kj_vec3u_length_sq(kjVec3u a);
KJ_API f32 kj_vec3f_length(kjVec3f a);
KJ_API i32 kj_vec3i_length(kjVec3i a);
KJ_API u32 kj_vec3u_length(kjVec3u a);
KJ_API kjVec3f kj_vec3f_normalise(kjVec3f a);
KJ_API kjVec3i kj_vec3i_normalise(kjVec3i a);
KJ_API kjVec3u kj_vec3u_normalise(kjVec3u a);

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
KJ_API kjVec4i kj_vec4i_negate(kjVec4i a);
KJ_API kjVec4u kj_vec4u_negate(kjVec4u a);
KJ_API kjVec4f kj_vec4f_add(kjVec4f a, kjVec4f b);
KJ_API kjVec4i kj_vec4i_add(kjVec4i a, kjVec4i b);
KJ_API kjVec4u kj_vec4u_add(kjVec4u a, kjVec4u b);
KJ_API kjVec4f kj_vec4f_sub(kjVec4f a, kjVec4f b);
KJ_API kjVec4i kj_vec4i_sub(kjVec4i a, kjVec4i b);
KJ_API kjVec4u kj_vec4u_sub(kjVec4u a, kjVec4u b);
KJ_API kjVec4f kj_vec4f_mul(kjVec4f a, kjVec4f b);
KJ_API kjVec4i kj_vec4i_mul(kjVec4i a, kjVec4i b);
KJ_API kjVec4u kj_vec4u_mul(kjVec4u a, kjVec4u b);
KJ_API kjVec4f kj_vec4f_mulf(kjVec4f a, f32 b);
KJ_API kjVec4i kj_vec4i_muli(kjVec4i a, i32 b);
KJ_API kjVec4u kj_vec4u_mulu(kjVec4u a, u32 b);
KJ_API kjVec4f kj_vec4f_div(kjVec4f a, kjVec4f b);
KJ_API kjVec4i kj_vec4i_div(kjVec4i a, kjVec4i b);
KJ_API kjVec4u kj_vec4u_div(kjVec4u a, kjVec4u b);
KJ_API f32 kj_vec4f_dot(kjVec4f a, kjVec4f b);
KJ_API i32 kj_vec4i_dot(kjVec4i a, kjVec4i b);
KJ_API u32 kj_vec4u_dot(kjVec4u a, kjVec4u b);
KJ_API f32 kj_vec4f_length_sq(kjVec4f a);
KJ_API i32 kj_vec4i_length_sq(kjVec4i a);
KJ_API u32 kj_vec4u_length_sq(kjVec4u a);
KJ_API f32 kj_vec4f_length(kjVec4f a);
KJ_API i32 kj_vec4i_length(kjVec4i a);
KJ_API u32 kj_vec4u_length(kjVec4u a);
KJ_API kjVec4f kj_vec4f_normalise(kjVec4f a);
KJ_API kjVec4i kj_vec4i_normalise(kjVec4i a);
KJ_API kjVec4u kj_vec4u_normalise(kjVec4u a);

KJ_API kjMat3f kj_mat3f(
        f32 e00, f32 e10, f32 e20,
        f32 e01, f32 e11, f32 e21,
        f32 e02, f32 e12, f32 e22);
KJ_API kjMat3f kj_mat3f_diag(f32 e00, f32 e11, f32 e22);
KJ_API kjMat3f kj_mat3f_ident(void);
KJ_API kjMat3f kj_mat3f_zero(void);
KJ_API kjMat3f kj_mat3f_one(void);
KJ_API kjMat3f kj_mat3f_mul(kjMat3f a, kjMat3f b);
KJ_API kjMat3f kj_mat3f_transpose(kjMat3f a);
KJ_API kjMat3f kj_mat3f_rotate(f32 angle, f32 x, f32 y, f32 z);
KJ_API kjMat3f kj_mat3f_rotate_vec3f(f32 angle, kjVec3f xyz);
KJ_API kjMat3f kj_mat3f_scale(f32 x, f32 y, f32 z);
KJ_API kjMat3f kj_mat3f_scale_vec3f(kjVec3f xyz);

KJ_API kjMat4f kj_mat4f(
        f32 e00, f32 e10, f32 e20, f32 e30,
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
KJ_API kjMat4f kj_mat4f_scale(f32 x, f32 y, f32 z);
KJ_API kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 znear, f32 zfar);
KJ_API kjMat4f kj_mat4f_ortho_inf(f32 left, f32 right, f32 top, f32 bottom);
KJ_API kjMat4f kj_mat4f_perspective(f32 fovy, f32 aspect, f32 znear, f32 zfar);
KJ_API kjMat4f kj_mat4f_perspective_inf(f32 fovy, f32 aspect, f32 znear);
KJ_API kjMat4f kj_mat4f_look_at(kjVec3f eye, kjVec3f target, kjVec3f up);

KJ_API kjRect2f kj_rect2f(f32 x, f32 y, f32 w, f32 h);
KJ_API kjRect2i kj_rect2i(i32 x, i32 y, i32 w, i32 h);
KJ_API kjRect2u kj_rect2u(u32 x, u32 y, u32 w, u32 h);
KJ_API b32 kj_rect2f_contains(kjRect2f r, f32 x, f32 y);
KJ_API b32 kj_rect2i_contains(kjRect2i r, i32 x, i32 y);
KJ_API b32 kj_rect2u_contains(kjRect2u r, u32 x, u32 y);
KJ_API b32 kj_rect2f_contains_vec2f(kjRect2f r, kjVec2f xy);
KJ_API b32 kj_rect2i_contains_vec2i(kjRect2i r, kjVec2i xy);
KJ_API b32 kj_rect2u_contains_vec2u(kjRect2u r, kjVec2u xy);
KJ_API i32 kj_rect2f_extend(kjRect2f r, f32 x, f32 y);
KJ_API i32 kj_rect2i_extend(kjRect2i r, i32 x, i32 y);
KJ_API i32 kj_rect2u_extend(kjRect2u r, u32 x, u32 y);
KJ_API i32 kj_rect2f_extend_vec2f(kjRect2f r, kjVec2f xy);
KJ_API i32 kj_rect2i_extend_vec2i(kjRect2i r, kjVec2i xy);
KJ_API i32 kj_rect2u_extend_vec2u(kjRect2u r, kjVec2u xy);
KJ_API kjVec2f kj_rect2f_centre(kjRect2f r);
KJ_API kjVec2i kj_rect2i_centre(kjRect2i r);
KJ_API kjVec2u kj_rect2u_centre(kjRect2u r);

KJ_API kjRect3f kj_rect3f(f32 x, f32 y, f32 z, f32 w, f32 h, f32 d);
KJ_API kjRect3i kj_rect3i(i32 x, i32 y, i32 z, i32 w, i32 h, i32 d);
KJ_API kjRect3u kj_rect3u(u32 x, u32 y, u32 z, u32 w, u32 h, u32 d);
KJ_API b32 kj_rect3f_contains_xy(kjRect3f r, f32 x, f32 y);
KJ_API b32 kj_rect3i_contains_xy(kjRect3i r, i32 x, i32 y);
KJ_API b32 kj_rect3u_contains_xy(kjRect3u r, u32 x, u32 y);
KJ_API b32 kj_rect3f_contains_vec2f(kjRect3f r, kjVec2f xy);
KJ_API b32 kj_rect3i_contains_vec2i(kjRect3i r, kjVec2i xy);
KJ_API b32 kj_rect3u_contains_vec2u(kjRect3u r, kjVec2u xy);
KJ_API b32 kj_rect3f_contains(kjRect3f r, f32 x, f32 y, f32 z);
KJ_API b32 kj_rect3i_contains(kjRect3i r, i32 x, i32 y, i32 z);
KJ_API b32 kj_rect3u_contains(kjRect3u r, u32 x, u32 y, u32 z);
KJ_API b32 kj_rect3f_contains_vec3f(kjRect3f r, kjVec3f xyz);
KJ_API b32 kj_rect3i_contains_vec3i(kjRect3i r, kjVec3i xyz);
KJ_API b32 kj_rect3u_contains_vec3u(kjRect3u r, kjVec3u xyz);
KJ_API i32 kj_rect3f_extend(kjRect3f r, f32 x, f32 y, f32 z);
KJ_API i32 kj_rect3i_extend(kjRect3i r, i32 x, i32 y, i32 z);
KJ_API i32 kj_rect3u_extend(kjRect3u r, u32 x, u32 y, u32 z);
KJ_API i32 kj_rect3f_extend_vec3f(kjRect3f r, kjVec3f xyz);
KJ_API i32 kj_rect3i_extend_vec3i(kjRect3i r, kjVec3i xyz);
KJ_API i32 kj_rect3u_extend_vec3u(kjRect3u r, kjVec3u xyz);
KJ_API kjVec3f kj_rect3f_centre(kjRect3f r);
KJ_API kjVec3i kj_rect3i_centre(kjRect3i r);
KJ_API kjVec3u kj_rect3u_centre(kjRect3u r);

#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)
KJ_API kjMat3f operator*(kjMat3f a, kjMat3f b);
KJ_API kjMat4f operator*(kjMat4f a, kjMat4f b);
#endif

#endif

#if defined(KJ_MATH_IMPLEMENTATION)

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
f32 kj_rsqrtf(f32 a) { return 1.0f / __builtin_sqrtf(a); }
f32 kj_sqrtf(f32 a) { return __builtin_sqrtf(a); }
f32 kj_sinf(f32 a) { return __builtin_sinf(a); }
f32 kj_cosf(f32 a) { return __builtin_cosf(a); }
f32 kj_tanf(f32 a) { return __builtin_tanf(a); }
f32 kj_asinf(f32 a) { return __builtin_asinf(a); }
f32 kj_acosf(f32 a) { return __builtin_acosf(a); }
f32 kj_atanf(f32 a) { return __builtin_atanf(a); }
f32 kj_atan2f(f32 y, f32 x) { return __builtin_atan2f(y, x); }
f32 kj_expf(f32 x)  { return __builtin_expf(x); }
f32 kj_logf(f32 x)  { return __builtin_logf(x); }
f32 kj_powf(f32 x, f32 y) { return __builtin_powf(x, y); }
#else
#include <math.h>
f32 kj_rsqrtf(f32 a) { return 1.0f / sqrtf(a); }
f32 kj_sqrtf(f32 a) { return sqrtf(a); }
f32 kj_sinf(f32 radians) { return sinf(radians); }
f32 kj_cosf(f32 radians) { return cosf(radians); }
f32 kj_tanf(f32 radians) { return tanf(radians); }
f32 kj_asinf(f32 a) { return asinf(a); }
f32 kj_acosf(f32 a) { return acosf(a); }
f32 kj_atanf(f32 a) { return atanf(a); }
f32 kj_atan2f(f32 y, f32 x) { return atan2f(y, x); }
f32 kj_expf(f32 x)  { return expf(x); }
f32 kj_logf(f32 x)  { return logf(x); }
f32 kj_powf(f32 x, f32 y) { return powf(x, y); }
#endif

kjVec2f kj_vec2f(f32 x, f32 y) { kjVec2f res; res.x = x; res.y = y; return res; }
kjVec2i kj_vec2i(i32 x, i32 y) { kjVec2i res; res.x = x; res.y = y; return res; }
kjVec2u kj_vec2u(u32 x, u32 y) { kjVec2u res; res.x = x; res.y = y; return res; }
kjVec2f kj_vec2f_zero(void) { return kj_vec2f(0.0f, 0.0f); }
kjVec2i kj_vec2i_zero(void) { return kj_vec2i(0, 0); }
kjVec2u kj_vec2u_zero(void) { return kj_vec2u(0, 0); }
kjVec2f kj_vec2f_one(void) { return kj_vec2f(1.0f, 1.0f); }
kjVec2i kj_vec2i_one(void) { return kj_vec2i(1, 1); }
kjVec2u kj_vec2u_one(void) { return kj_vec2u(1, 1); }
kjVec2f kj_vec2f_all(f32 a) { return kj_vec2f(a, a); }
kjVec2i kj_vec2i_all(i32 a) { return kj_vec2i(a, a); }
kjVec2u kj_vec2u_all(u32 a) { return kj_vec2u(a, a); }
kjVec2f kj_vec2f_negate(kjVec2f a) { return kj_vec2f(-a.x, -a.y); }
kjVec2i kj_vec2i_negate(kjVec2i a) { return kj_vec2i(-a.x, -a.y); }
kjVec2u kj_vec2u_negate(kjVec2u a) { return kj_vec2u(-cast_of(i32, a.x), -cast_of(i32, a.y)); }
kjVec2f kj_vec2f_add(kjVec2f a, kjVec2f b) { return kj_vec2f(a.x + b.x, a.y + b.y); }
kjVec2i kj_vec2i_add(kjVec2i a, kjVec2i b) { return kj_vec2i(a.x + b.x, a.y + b.y); }
kjVec2u kj_vec2u_add(kjVec2u a, kjVec2u b) { return kj_vec2u(a.x + b.x, a.y + b.y); }
kjVec2f kj_vec2f_sub(kjVec2f a, kjVec2f b) { return kj_vec2f(a.x - b.x, a.y - b.y); }
kjVec2i kj_vec2i_sub(kjVec2i a, kjVec2i b) { return kj_vec2i(a.x - b.x, a.y - b.y); }
kjVec2u kj_vec2u_sub(kjVec2u a, kjVec2u b) { return kj_vec2u(a.x - b.x, a.y - b.y); }
kjVec2f kj_vec2f_mul(kjVec2f a, kjVec2f b) { return kj_vec2f(a.x * b.x, a.y * b.y); }
kjVec2i kj_vec2i_mul(kjVec2i a, kjVec2i b) { return kj_vec2i(a.x * b.x, a.y * b.y); }
kjVec2u kj_vec2u_mul(kjVec2u a, kjVec2u b) { return kj_vec2u(a.x * b.x, a.y * b.y); }
kjVec2f kj_vec2f_mulf(kjVec2f a, f32 b) { return kj_vec2f(a.x * b, a.y * b); }
kjVec2i kj_vec2i_muli(kjVec2i a, i32 b) { return kj_vec2i(a.x * b, a.y * b); }
kjVec2u kj_vec2u_mulu(kjVec2u a, u32 b) { return kj_vec2u(a.x * b, a.y * b); }
kjVec2f kj_vec2f_div(kjVec2f a, kjVec2f b) { return kj_vec2f(a.x / b.x, a.y / b.y); }
kjVec2i kj_vec2i_div(kjVec2i a, kjVec2i b) { return kj_vec2i(a.x / b.x, a.y / b.y); }
kjVec2u kj_vec2u_div(kjVec2u a, kjVec2u b) { return kj_vec2u(a.x / b.x, a.y / b.y); }
f32 kj_vec2f_dot(kjVec2f a, kjVec2f b) { return (a.x * b.x + a.y * b.y); }
i32 kj_vec2i_dot(kjVec2i a, kjVec2i b) { return (a.x * b.x + a.y * b.y); }
u32 kj_vec2u_dot(kjVec2u a, kjVec2u b) { return (a.x * b.x + a.y * b.y); }
f32 kj_vec2f_cross(kjVec2f a, kjVec2f b) { return (a.x * b.y - b.x * a.y); }
i32 kj_vec2i_cross(kjVec2i a, kjVec2i b) { return (a.x * b.y - b.x * a.y); }
u32 kj_vec2u_cross(kjVec2u a, kjVec2u b) { return (a.x * b.y - b.x * a.y); }
f32 kj_vec2f_length_sq(kjVec2f a) { return kj_vec2f_dot(a, a); }
i32 kj_vec2i_length_sq(kjVec2i a) { return kj_vec2i_dot(a, a); }
u32 kj_vec2u_length_sq(kjVec2u a) { return kj_vec2u_dot(a, a); }
f32 kj_vec2f_length(kjVec2f a) { return kj_sqrtf(kj_vec2f_length_sq(a)); }
i32 kj_vec2i_length(kjVec2i a) { return cast_of(i32, kj_sqrtf(cast_of(f32, kj_vec2i_length_sq(a)))); }
u32 kj_vec2u_length(kjVec2u a) { return cast_of(u32, kj_sqrtf(cast_of(f32, kj_vec2u_length_sq(a)))); }
kjVec2f kj_vec2f_normalise(kjVec2f a) { return kj_vec2f_div(a, kj_vec2f_all(kj_vec2f_length(a))); }
kjVec2i kj_vec2i_normalise(kjVec2i a) { return kj_vec2i_div(a, kj_vec2i_all(kj_vec2i_length(a))); }
kjVec2u kj_vec2u_normalise(kjVec2u a) { return kj_vec2u_div(a, kj_vec2u_all(kj_vec2u_length(a))); }

kjVec3f kj_vec3f(f32 x, f32 y, f32 z) { kjVec3f res; res.x = x; res.y = y; res.z = z; return res; }
kjVec3i kj_vec3i(i32 x, i32 y, i32 z) { kjVec3i res; res.x = x; res.y = y; res.z = z; return res; }
kjVec3u kj_vec3u(u32 x, u32 y, u32 z) { kjVec3u res; res.x = x; res.y = y; res.z = z; return res; }
kjVec3f kj_vec3f_zero(void) { return kj_vec3f(0.0f, 0.0f, 0.0f); }
kjVec3i kj_vec3i_zero(void) { return kj_vec3i(0, 0, 0); }
kjVec3u kj_vec3u_zero(void) { return kj_vec3u(0, 0, 0); }
kjVec3f kj_vec3f_one(void) { return kj_vec3f(1.0f, 1.0f, 1.0f); }
kjVec3i kj_vec3i_one(void) { return kj_vec3i(1, 1, 1); }
kjVec3u kj_vec3u_one(void) { return kj_vec3u(1, 1, 1); }
kjVec3f kj_vec3f_all(f32 a) { return kj_vec3f(a, a, a); }
kjVec3i kj_vec3i_all(i32 a) { return kj_vec3i(a, a, a); }
kjVec3u kj_vec3u_all(u32 a) { return kj_vec3u(a, a, a); }
kjVec3f kj_vec3f_negate(kjVec3f a) { return kj_vec3f(-a.x, -a.y, -a.z); }
kjVec3i kj_vec3i_negate(kjVec3i a) { return kj_vec3i(-a.x, -a.y, -a.z); }
kjVec3u kj_vec3u_negate(kjVec3u a) { return kj_vec3u(-cast_of(i32, a.x), -cast_of(i32, a.y), -cast_of(i32, a.z)); }
kjVec3f kj_vec3f_add(kjVec3f a, kjVec3f b) { return kj_vec3f(a.x + b.x, a.y + b.y, a.z + b.z); }
kjVec3i kj_vec3i_add(kjVec3i a, kjVec3i b) { return kj_vec3i(a.x + b.x, a.y + b.y, a.z + b.z); }
kjVec3u kj_vec3u_add(kjVec3u a, kjVec3u b) { return kj_vec3u(a.x + b.x, a.y + b.y, a.z + b.z); }
kjVec3f kj_vec3f_sub(kjVec3f a, kjVec3f b) { return kj_vec3f(a.x - b.x, a.y - b.y, a.z - b.z); }
kjVec3i kj_vec3i_sub(kjVec3i a, kjVec3i b) { return kj_vec3i(a.x - b.x, a.y - b.y, a.z - b.z); }
kjVec3u kj_vec3u_sub(kjVec3u a, kjVec3u b) { return kj_vec3u(a.x - b.x, a.y - b.y, a.z - b.z); }
kjVec3f kj_vec3f_mul(kjVec3f a, kjVec3f b) { return kj_vec3f(a.x * b.x, a.y * b.y, a.z * b.z); }
kjVec3i kj_vec3i_mul(kjVec3i a, kjVec3i b) { return kj_vec3i(a.x * b.x, a.y * b.y, a.z * b.z); }
kjVec3u kj_vec3u_mul(kjVec3u a, kjVec3u b) { return kj_vec3u(a.x * b.x, a.y * b.y, a.z * b.z); }
kjVec3f kj_vec3f_mulf(kjVec3f a, f32 b) { return kj_vec3f(a.x * b, a.y * b, a.z * b); }
kjVec3i kj_vec3i_muli(kjVec3i a, i32 b) { return kj_vec3i(a.x * b, a.y * b, a.z * b); }
kjVec3u kj_vec3u_mulu(kjVec3u a, u32 b) { return kj_vec3u(a.x * b, a.y * b, a.z * b); }
kjVec3f kj_vec3f_div(kjVec3f a, kjVec3f b) { return kj_vec3f(a.x / b.x, a.y / b.y, a.z / b.z); }
kjVec3i kj_vec3i_div(kjVec3i a, kjVec3i b) { return kj_vec3i(a.x / b.x, a.y / b.y, a.z / b.z); }
kjVec3u kj_vec3u_div(kjVec3u a, kjVec3u b) { return kj_vec3u(a.x / b.x, a.y / b.y, a.z / b.z); }
f32 kj_vec3f_dot(kjVec3f a, kjVec3f b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
i32 kj_vec3i_dot(kjVec3i a, kjVec3i b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
u32 kj_vec3u_dot(kjVec3u a, kjVec3u b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
kjVec3f kj_vec3f_cross(kjVec3f a, kjVec3f b) { return kj_vec3f(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
kjVec3i kj_vec3i_cross(kjVec3i a, kjVec3i b) { return kj_vec3i(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
kjVec3u kj_vec3u_cross(kjVec3u a, kjVec3u b) { return kj_vec3u(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
f32 kj_vec3f_length_sq(kjVec3f a) { return kj_vec3f_dot(a, a); }
i32 kj_vec3i_length_sq(kjVec3i a) { return kj_vec3i_dot(a, a); }
u32 kj_vec3u_length_sq(kjVec3u a) { return kj_vec3u_dot(a, a); }
f32 kj_vec3f_length(kjVec3f a) { return kj_sqrtf(kj_vec3f_length_sq(a)); }
i32 kj_vec3i_length(kjVec3i a) { return cast_of(i32, kj_sqrtf(cast_of(f32, kj_vec3i_length_sq(a)))); }
u32 kj_vec3u_length(kjVec3u a) { return cast_of(u32, kj_sqrtf(cast_of(f32, kj_vec3u_length_sq(a)))); }
kjVec3f kj_vec3f_normalise(kjVec3f a) { return kj_vec3f_div(a, kj_vec3f_all(kj_vec3f_length(a))); }
kjVec3i kj_vec3i_normalise(kjVec3i a) { return kj_vec3i_div(a, kj_vec3i_all(kj_vec3i_length(a))); }
kjVec3u kj_vec3u_normalise(kjVec3u a) { return kj_vec3u_div(a, kj_vec3u_all(kj_vec3u_length(a))); }

kjVec4f kj_vec4f(f32 x, f32 y, f32 z, f32 w) { kjVec4f res; res.x = x; res.y = y; res.z = z; res.w = w; return res; }
kjVec4i kj_vec4i(i32 x, i32 y, i32 z, i32 w) { kjVec4i res; res.x = x; res.y = y; res.z = z; res.w = w; return res; }
kjVec4u kj_vec4u(u32 x, u32 y, u32 z, u32 w) { kjVec4u res; res.x = x; res.y = y; res.z = z; res.w = w; return res; }
kjVec4f kj_vec4f_zero(void) { return kj_vec4f(0.0f, 0.0f, 0.0f, 0.0f); }
kjVec4i kj_vec4i_zero(void) { return kj_vec4i(0, 0, 0, 0); }
kjVec4u kj_vec4u_zero(void) { return kj_vec4u(0, 0, 0, 0); }
kjVec4f kj_vec4f_one(void) { return kj_vec4f(1.0f, 1.0f, 1.0f, 1.0f); }
kjVec4i kj_vec4i_one(void) { return kj_vec4i(1, 1, 1, 1); }
kjVec4u kj_vec4u_one(void) { return kj_vec4u(1, 1, 1, 1); }
kjVec4f kj_vec4f_all(f32 a) { return kj_vec4f(a, a, a, a); }
kjVec4i kj_vec4i_all(i32 a) { return kj_vec4i(a, a, a, a); }
kjVec4u kj_vec4u_all(u32 a) { return kj_vec4u(a, a, a, a); }
kjVec4f kj_vec4f_negate(kjVec4f a) { return kj_vec4f(-a.x, -a.y, -a.z, -a.w); }
kjVec4i kj_vec4i_negate(kjVec4i a) { return kj_vec4i(-a.x, -a.y, -a.z, -a.w); }
kjVec4u kj_vec4u_negate(kjVec4u a) { return kj_vec4u(-cast_of(i32, a.x), -cast_of(i32, a.y), -cast_of(i32, a.z), -cast_of(i32, a.w)); }
kjVec4f kj_vec4f_add(kjVec4f a, kjVec4f b) { return kj_vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
kjVec4i kj_vec4i_add(kjVec4i a, kjVec4i b) { return kj_vec4i(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
kjVec4u kj_vec4u_add(kjVec4u a, kjVec4u b) { return kj_vec4u(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
kjVec4f kj_vec4f_sub(kjVec4f a, kjVec4f b) { return kj_vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
kjVec4i kj_vec4i_sub(kjVec4i a, kjVec4i b) { return kj_vec4i(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
kjVec4u kj_vec4u_sub(kjVec4u a, kjVec4u b) { return kj_vec4u(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
kjVec4f kj_vec4f_mul(kjVec4f a, kjVec4f b) { return kj_vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
kjVec4i kj_vec4i_mul(kjVec4i a, kjVec4i b) { return kj_vec4i(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
kjVec4u kj_vec4u_mul(kjVec4u a, kjVec4u b) { return kj_vec4u(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
kjVec4f kj_vec4f_mulf(kjVec4f a, f32 b) { return kj_vec4f(a.x * b, a.y * b, a.z * b, a.w * b); }
kjVec4i kj_vec4i_muli(kjVec4i a, i32 b) { return kj_vec4i(a.x * b, a.y * b, a.z * b, a.w * b); }
kjVec4u kj_vec4u_mulu(kjVec4u a, u32 b) { return kj_vec4u(a.x * b, a.y * b, a.z * b, a.w * b); }
kjVec4f kj_vec4f_div(kjVec4f a, kjVec4f b) { return kj_vec4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
kjVec4i kj_vec4i_div(kjVec4i a, kjVec4i b) { return kj_vec4i(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
kjVec4u kj_vec4u_div(kjVec4u a, kjVec4u b) { return kj_vec4u(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
f32 kj_vec4f_dot(kjVec4f a, kjVec4f b) { return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w); }
i32 kj_vec4i_dot(kjVec4i a, kjVec4i b) { return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w); }
u32 kj_vec4u_dot(kjVec4u a, kjVec4u b) { return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w); }
f32 kj_vec4f_length_sq(kjVec4f a) { return kj_vec4f_dot(a, a); }
i32 kj_vec4i_length_sq(kjVec4i a) { return kj_vec4i_dot(a, a); }
u32 kj_vec4u_length_sq(kjVec4u a) { return kj_vec4u_dot(a, a); }
f32 kj_vec4f_length(kjVec4f a) { return kj_sqrtf(kj_vec4f_length_sq(a)); }
i32 kj_vec4i_length(kjVec4i a) { return cast_of(i32, kj_sqrtf(cast_of(f32, kj_vec4i_length_sq(a)))); }
u32 kj_vec4u_length(kjVec4u a) { return cast_of(u32, kj_sqrtf(cast_of(f32, kj_vec4u_length_sq(a)))); }
kjVec4f kj_vec4f_normalise(kjVec4f a) { return kj_vec4f_div(a, kj_vec4f_all(kj_vec4f_length(a))); }
kjVec4i kj_vec4i_normalise(kjVec4i a) { return kj_vec4i_div(a, kj_vec4i_all(kj_vec4i_length(a))); }
kjVec4u kj_vec4u_normalise(kjVec4u a) { return kj_vec4u_div(a, kj_vec4u_all(kj_vec4u_length(a))); }

kjMat3f kj_mat3f(
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

kjMat3f kj_mat3f_diag(f32 e00, f32 e11, f32 e22) {
    return kj_mat3f(
            e00, 0.0f, 0.0f,
            0.0f, e11, 0.0f,
            0.0f, 0.0f, e22);
}

kjMat3f kj_mat3f_ident(void) {
    return kj_mat3f_diag(1.0f, 1.0f, 1.0f);
}

kjMat3f kj_mat3f_zero(void) {
    kjMat3f res;
    kj_zero(&res, isize_of(kjMat3f));
    return res;
}

kjMat3f kj_mat3f_one(void) {
    kjMat3f res;
    kj_one(&res, isize_of(kjMat3f));
    return res;
}

kjMat3f kj_mat3f_mul(kjMat3f a, kjMat3f b) {
    kjMat3f res;
    kjVec3f bv0 = kj_vec3f(b.v[0].x, b.v[1].x, b.v[2].x);
    kjVec3f bv1 = kj_vec3f(b.v[0].y, b.v[1].y, b.v[2].y);
    kjVec3f bv2 = kj_vec3f(b.v[0].z, b.v[1].z, b.v[2].z);
    res.v[0] = kj_vec3f_add(kj_vec3f_add(
        kj_vec3f_mul(a.v[0], bv0),
        kj_vec3f_mul(a.v[0], bv1)),
        kj_vec3f_mul(a.v[0], bv2));
    res.v[1] = kj_vec3f_add(kj_vec3f_add(
        kj_vec3f_mul(a.v[1], bv0),
        kj_vec3f_mul(a.v[1], bv1)),
        kj_vec3f_mul(a.v[1], bv2));
    res.v[2] = kj_vec3f_add(kj_vec3f_add(
        kj_vec3f_mul(a.v[2], bv0),
        kj_vec3f_mul(a.v[2], bv1)),
        kj_vec3f_mul(a.v[2], bv2));
    return res;
}

kjMat3f kj_mat3f_transpose(kjMat3f a) {
    return kj_mat3f(
        a.e[0][0], a.e[1][0], a.e[2][0],
        a.e[0][1], a.e[1][1], a.e[2][1],
        a.e[0][2], a.e[1][2], a.e[2][2]);
}

kjMat3f kj_mat3f_rotate(f32 angle, f32 x, f32 y, f32 z) {
    kjMat3f res;
    f32 c = kj_cosf(angle);
    f32 s = kj_sinf(angle);

    kjVec3f axis = kj_vec3f_normalise(kj_vec3f(x, y, z));
    kjVec3f rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - c));
    res.e[0][0] = c + rot_axis.x * axis.x;
    res.e[0][1] = 0.0f + rot_axis.x * axis.y + s * axis.z;
    res.e[0][2] = 0.0f + rot_axis.x * axis.z - s * axis.y;
    res.e[1][0] = 0.0f + rot_axis.y * axis.x - s * axis.z;
    res.e[1][1] = c + rot_axis.y * axis.y;
    res.e[1][2] = 0.0f+ rot_axis.y * axis.z + s * axis.x;
    res.e[2][0] = 0.0f + rot_axis.z * axis.x + s * axis.y;
    res.e[2][1] = 0.0f + rot_axis.z * axis.y - s * axis.x;
    res.e[2][2] = c + rot_axis.z * axis.z;
    return res;
}

kjMat3f kj_mat3f_rotate_vec3f(f32 angle, kjVec3f xyz) {
    return kj_mat3f_rotate(angle, xyz.x, xyz.y, xyz.z);
}

kjMat3f kj_mat3f_scale(f32 x, f32 y, f32 z) {
    return kj_mat3f_diag(x, y, z);
}

kjMat3f kj_mat3f_scale_vec3f(kjVec3f xyz) {
    return kj_mat3f_scale(xyz.x, xyz.y, xyz.z);
}

kjMat4f kj_mat4f(
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

kjMat4f kj_mat4f_diag(f32 e00, f32 e11, f32 e22, f32 e33) {
    return kj_mat4f(
            e00, 0.0f, 0.0f, 0.0f,
            0.0f, e11, 0.0f, 0.0f,
            0.0f, 0.0f, e22, 0.0f,
            0.0f, 0.0f, 0.0f, e33);
}

kjMat4f kj_mat4f_ident(void) {
    return kj_mat4f_diag(1.0f, 1.0f, 1.0f, 1.0f);
}

kjMat4f kj_mat4f_zero(void) {
    kjMat4f res;
    kj_zero(&res, isize_of(kjMat4f));
    return res;
}

kjMat4f kj_mat4f_one(void) {
    kjMat4f res;
    kj_one(&res, isize_of(kjMat4f));
    return res;
}

kjMat4f kj_mat4f_mul(kjMat4f a, kjMat4f b) {
    kjMat4f res;
    for(u32 j = 0; j < 4; j++) {
        for(u32 i = 0; i < 4; i++) {
            res.e[j][i] =
                a.e[0][i] * b.e[j][0] +
                a.e[1][i] * b.e[j][1] +
                a.e[2][i] * b.e[j][2] +
                a.e[3][i] * b.e[j][3];
        }
    }
    return res;
}

kjVec4f kj_mat4f_mul_vec4f(kjMat4f a, kjVec4f b) {
    kjVec4f res;
    res.x = a.e[0][0] * b.x + a.e[1][0] * b.y + a.e[2][0] * b.z + a.e[3][0] * b.w;
    res.y = a.e[0][1] * b.x + a.e[1][1] * b.y + a.e[2][1] * b.z + a.e[3][1] * b.w;
    res.z = a.e[0][2] * b.x + a.e[1][2] * b.y + a.e[2][2] * b.z + a.e[3][2] * b.w;
    res.w = a.e[0][3] * b.x + a.e[1][3] * b.y + a.e[2][3] * b.z + a.e[3][3] * b.w;
    return res;
}

kjMat4f kj_mat4f_transpose(kjMat4f a) {
    return kj_mat4f(
        a.e[0][0], a.e[1][0], a.e[2][0], a.e[3][0],
        a.e[0][1], a.e[1][1], a.e[2][1], a.e[3][1],
        a.e[0][2], a.e[1][2], a.e[2][2], a.e[3][2],
        a.e[0][3], a.e[1][3], a.e[2][3], a.e[3][3]);
}

kjMat4f kj_mat4f_translate(f32 x, f32 y, f32 z) {
    return kj_mat4f(
            1.0f, 0.0f, 0.0f, x,
            0.0f, 1.0f, 0.0f, y,
            0.0f, 0.0f, 1.0f, z,
            0.0f, 0.0f, 0.0f, 1.0f);
}

kjMat4f kj_mat4f_translate_vec3f(kjVec3f xyz) {
    return kj_mat4f_translate(xyz.x, xyz.y, xyz.z);
}

kjMat4f kj_mat4f_rotate(f32 angle, f32 x, f32 y, f32 z) {
    kjMat4f res = kj_mat4f_ident();
    f32 c = kj_cosf(angle);
    f32 s = kj_sinf(angle);

    kjVec3f axis = kj_vec3f_normalise(kj_vec3f(x, y, z));
    kjVec3f rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - c));
    res.e[0][0] = c + rot_axis.x * axis.x;
    res.e[0][1] = 0.0f + rot_axis.x * axis.y + s * axis.z;
    res.e[0][2] = 0.0f + rot_axis.x * axis.z - s * axis.y;
    res.e[0][3] = 0.0f;
    res.e[1][0] = 0.0f + rot_axis.y * axis.x - s * axis.z;
    res.e[1][1] = c + rot_axis.y * axis.y;
    res.e[1][2] = 0.0f+ rot_axis.y * axis.z + s * axis.x;
    res.e[1][3] = 0.0f;
    res.e[2][0] = 0.0f + rot_axis.z * axis.x + s * axis.y;
    res.e[2][1] = 0.0f + rot_axis.z * axis.y - s * axis.x;
    res.e[2][2] = c + rot_axis.z * axis.z;
    res.e[2][3] = 0.0f;
    return res;
}

kjMat4f kj_mat4f_rotate_vec3f(f32 angle, kjVec3f xyz) {
    return kj_mat4f_rotate(angle, xyz.x, xyz.y, xyz.z);
}

kjMat4f kj_mat4f_scale(f32 x, f32 y, f32 z) {
    return kj_mat4f_diag(x, y, z, 1.0f);
}

kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz) {
    return kj_mat4f_scale(xyz.x, xyz.y, xyz.z);
}

kjMat4f kj_mat4f_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 znear, f32 zfar) {
    kjMat4f res = kj_mat4f_ident();
    f32 rl = right - left + F32_EPS;
    f32 tb = top - bottom + F32_EPS;
    f32 fn = zfar - znear + F32_EPS;

    res.e[0][0] = 2.0f / rl;
    res.e[1][1] = 2.0f / tb;
    res.e[2][2] = -1.0f / fn;
    res.e[3][0] = -(right + left) / rl;
    res.e[3][1] = -(top + bottom) / tb;
    res.e[3][2] = -(zfar + znear) / fn;
    return res;
}

kjMat4f kj_mat4f_ortho_inf(f32 left, f32 right, f32 top, f32 bottom) {
    kjMat4f res = kj_mat4f_ident();
    f32 rl = right - left + F32_EPS;
    f32 tb = top - bottom + F32_EPS;

    res.e[0][0] = 2.0f / rl;
    res.e[1][1] = 2.0f / tb;
    res.e[2][2] = -1.0f;
    res.e[3][0] = -(right + left) / rl;
    res.e[3][1] = -(top + bottom) / tb;
    return res;
}

kjMat4f kj_mat4f_perspective(f32 fovy, f32 aspect, f32 znear, f32 zfar) {
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

kjMat4f kj_mat4f_perspective_inf(f32 fovy, f32 aspect, f32 znear) {
    kjMat4f res = kj_mat4f_zero();
    if(aspect > 0.0f) {
        f32 range  = kj_tanf(0.5f * fovy) * znear;
        res.e[0][0] = (2.0f * znear) / ((range * aspect) - (-range * aspect));
        res.e[1][1] = (2.0f * znear) / (range - -range);
        res.e[2][2] = -1.0f;
        res.e[2][3] = -1.0f;
        res.e[3][2] = -2.0f * znear;
    }
    return res;
}

kjMat4f kj_mat4f_look_at(kjVec3f eye, kjVec3f target, kjVec3f up) {
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

kjRect2f kj_rect2f(f32 x, f32 y, f32 w, f32 h) { kjRect2f res; res.x = x; res.y = y; res.w = w; res.h = h; return res; }
kjRect2i kj_rect2i(i32 x, i32 y, i32 w, i32 h) { kjRect2i res; res.x = x; res.y = y; res.w = w; res.h = h; return res; }
kjRect2u kj_rect2u(u32 x, u32 y, u32 w, u32 h) { kjRect2u res; res.x = x; res.y = y; res.w = w; res.h = h; return res; }
b32 kj_rect2f_contains(kjRect2f r, f32 x, f32 y) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y); }
b32 kj_rect2i_contains(kjRect2i r, i32 x, i32 y) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y); }
b32 kj_rect2u_contains(kjRect2u r, u32 x, u32 y) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y); }
b32 kj_rect2f_contains_vec2f(kjRect2f r, kjVec2f xy) { return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y && (r.y + r.h) >= xy.y); }
b32 kj_rect2i_contains_vec2i(kjRect2i r, kjVec2i xy) { return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y && (r.y + r.h) >= xy.y); }
b32 kj_rect2u_contains_vec2u(kjRect2u r, kjVec2u xy) { return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y && (r.y + r.h) >= xy.y); }
i32 kj_rect2f_extend(kjRect2f r, f32 x, f32 y);
i32 kj_rect2i_extend(kjRect2i r, i32 x, i32 y);
i32 kj_rect2u_extend(kjRect2u r, u32 x, u32 y);
i32 kj_rect2f_extend_vec2f(kjRect2f r, kjVec2f xy);
i32 kj_rect2i_extend_vec2i(kjRect2i r, kjVec2i xy);
i32 kj_rect2u_extend_vec2u(kjRect2u r, kjVec2u xy);
kjVec2f kj_rect2f_centre(kjRect2f r) { return kj_vec2f((r.x + (r.x + r.w)) / 2.0f, (r.y + (r.y + r.h)) / 2.0f); }
kjVec2i kj_rect2i_centre(kjRect2i r) { return kj_vec2i((r.x + (r.x + r.w)) / 2, (r.y + (r.y + r.h)) / 2); }
kjVec2u kj_rect2u_centre(kjRect2u r) { return kj_vec2u((r.x + (r.x + r.w)) / 2, (r.y + (r.y + r.h)) / 2); }

kjRect3f kj_rect3f(f32 x, f32 y, f32 z, f32 w, f32 h, f32 d) { kjRect3f res; res.x = x; res.y = y; res.z = z; res.w = w; res.h = h; res.d = d; return res; }
kjRect3i kj_rect3i(i32 x, i32 y, i32 z, i32 w, i32 h, i32 d) { kjRect3i res; res.x = x; res.y = y; res.z = z; res.w = w; res.h = h; res.d = d; return res; }
kjRect3u kj_rect3u(u32 x, u32 y, u32 z, u32 w, u32 h, u32 d) { kjRect3u res; res.x = x; res.y = y; res.z = z; res.w = w; res.h = h; res.d = d; return res; }
b32 kj_rect3f_contains_xy(kjRect3f r, f32 x, f32 y) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y); }
b32 kj_rect3i_contains_xy(kjRect3i r, i32 x, i32 y) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y); }
b32 kj_rect3u_contains_xy(kjRect3u r, u32 x, u32 y) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y); }
b32 kj_rect3f_contains_vec2f(kjRect3f r, kjVec2f xy) { return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y && (r.y + r.h) >= xy.y); }
b32 kj_rect3i_contains_vec2i(kjRect3i r, kjVec2i xy) { return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y && (r.y + r.h) >= xy.y); }
b32 kj_rect3u_contains_vec2u(kjRect3u r, kjVec2u xy) { return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y && (r.y + r.h) >= xy.y); }
b32 kj_rect3f_contains(kjRect3f r, f32 x, f32 y, f32 z) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y && r.z <= z && (r.z + r.d) >= z); }
b32 kj_rect3i_contains(kjRect3i r, i32 x, i32 y, i32 z) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y && r.z <= z && (r.z + r.d) >= z); }
b32 kj_rect3u_contains(kjRect3u r, u32 x, u32 y, u32 z) { return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y && r.z <= z && (r.z + r.d) >= z); }
b32 kj_rect3f_contains_vec3f(kjRect3f r, kjVec3f xyz) { return (r.x <= xyz.x && (r.x + r.w) >= xyz.x && r.y <= xyz.y && (r.y + r.h) >= xyz.y && r.z <= xyz.z && (r.z + r.d) >= xyz.z); }
b32 kj_rect3i_contains_vec3i(kjRect3i r, kjVec3i xyz) { return (r.x <= xyz.x && (r.x + r.w) >= xyz.x && r.y <= xyz.y && (r.y + r.h) >= xyz.y && r.z <= xyz.z && (r.z + r.d) >= xyz.z); }
b32 kj_rect3u_contains_vec3u(kjRect3u r, kjVec3u xyz) { return (r.x <= xyz.x && (r.x + r.w) >= xyz.x && r.y <= xyz.y && (r.y + r.h) >= xyz.y && r.z <= xyz.z && (r.z + r.d) >= xyz.z); }
i32 kj_rect3f_extend(kjRect3f r, f32 x, f32 y, f32 z);
i32 kj_rect3i_extend(kjRect3i r, i32 x, i32 y, i32 z);
i32 kj_rect3u_extend(kjRect3u r, u32 x, u32 y, u32 z);
i32 kj_rect3f_extend_vec3f(kjRect3f r, kjVec3f xyz);
i32 kj_rect3i_extend_vec3i(kjRect3i r, kjVec3i xyz);
i32 kj_rect3u_extend_vec3u(kjRect3u r, kjVec3u xyz);
kjVec3f kj_rect3f_centre(kjRect3f r) { return kj_vec3f((r.x + (r.x + r.w)) / 2.0f, (r.y + (r.y + r.h)) / 2.0f, (r.z + (r.z + r.w)) / 2.0f); }
kjVec3i kj_rect3i_centre(kjRect3i r) { return kj_vec3i((r.x + (r.x + r.w)) / 2, (r.y + (r.y + r.h)) / 2, (r.z + (r.z + r.w)) / 2); }
kjVec3u kj_rect3u_centre(kjRect3u r) { return kj_vec3u((r.x + (r.x + r.w)) / 2, (r.y + (r.y + r.h)) / 2, (r.z + (r.z + r.w)) / 2); }

#if defined(__cplusplus)
kjMat3f operator*(kjMat3f a, kjMat3f b) {
    return kj_mat3f_mul(a, b);
}

kjMat4f operator*(kjMat4f a, kjMat4f b) {
    return kj_mat4f_mul(a, b);
}
#endif

#endif
