#ifndef KJ_VEC_H
#define KJ_VEC_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_VEC_VERSION_MAJOR 0
#define KJ_VEC_VERSION_MINOR 1
#define KJ_VEC_VERSION_PATCH 0

typedef struct kj_vec2f {
    f32 x, y;
} kj_vec2f_t;

typedef struct kj_vec2i {
    i32 x, y;
} kj_vec2i_t;

typedef struct kj_vec2u {
    u32 x, y;
} kj_vec2u_t;

kj_def kj_vec2f_t kj_vec2f(f32 x, f32 y);
kj_def kj_vec2i_t kj_vec2i(i32 x, i32 y);
kj_def kj_vec2u_t kj_vec2u(u32 x, u32 y);
kj_def kj_vec2f_t kj_vec2f_zero(void);
kj_def kj_vec2i_t kj_vec2i_zero(void);
kj_def kj_vec2u_t kj_vec2u_zero(void);
kj_def kj_vec2f_t kj_vec2f_one(void);
kj_def kj_vec2i_t kj_vec2i_one(void);
kj_def kj_vec2u_t kj_vec2u_one(void);
kj_def kj_vec2f_t kj_vec2f_negate(kj_vec2f_t a);
kj_def kj_vec2i_t kj_vec2i_negate(kj_vec2i_t a);
kj_def kj_vec2u_t kj_vec2u_negate(kj_vec2u_t a);
kj_def kj_vec2f_t kj_vec2f_add(kj_vec2f_t a, kj_vec2f_t b);
kj_def kj_vec2i_t kj_vec2i_add(kj_vec2i_t a, kj_vec2i_t b);
kj_def kj_vec2u_t kj_vec2u_add(kj_vec2u_t a, kj_vec2u_t b);
kj_def kj_vec2f_t kj_vec2f_sub(kj_vec2f_t a, kj_vec2f_t b);
kj_def kj_vec2i_t kj_vec2i_sub(kj_vec2i_t a, kj_vec2i_t b);
kj_def kj_vec2u_t kj_vec2u_sub(kj_vec2u_t a, kj_vec2u_t b);
kj_def kj_vec2f_t kj_vec2f_mul(kj_vec2f_t a, kj_vec2f_t b);
kj_def kj_vec2i_t kj_vec2i_mul(kj_vec2i_t a, kj_vec2i_t b);
kj_def kj_vec2u_t kj_vec2u_mul(kj_vec2u_t a, kj_vec2u_t b);
kj_def kj_vec2f_t kj_vec2f_div(kj_vec2f_t a, kj_vec2f_t b);
kj_def kj_vec2i_t kj_vec2i_div(kj_vec2i_t a, kj_vec2i_t b);
kj_def kj_vec2u_t kj_vec2u_div(kj_vec2u_t a, kj_vec2u_t b);
kj_def f32 kj_vec2f_dot(kj_vec2f_t a, kj_vec2f_t b);
kj_def i32 kj_vec2i_dot(kj_vec2i_t a, kj_vec2i_t b);
kj_def u32 kj_vec2u_dot(kj_vec2u_t a, kj_vec2u_t b);
kj_def f32 kj_vec2f_cross(kj_vec2f_t a, kj_vec2f_t b);
kj_def i32 kj_vec2i_cross(kj_vec2i_t a, kj_vec2i_t b);
kj_def u32 kj_vec2u_cross(kj_vec2u_t a, kj_vec2u_t b);

typedef struct kj_vec3f {
    f32 x, y, z;
} kj_vec3f_t;

typedef struct kj_vec3i {
    i32 x, y, z;
} kj_vec3i_t;

typedef struct kj_vec3u {
    u32 x, y, z;
} kj_vec3u_t;

kj_def kj_vec3f_t kj_vec3f(f32 x, f32 y, f32 z);
kj_def kj_vec3i_t kj_vec3i(i32 x, i32 y, i32 z);
kj_def kj_vec3u_t kj_vec3u(u32 x, u32 y, u32 z);
kj_def kj_vec3f_t kj_vec3f_zero(void);
kj_def kj_vec3i_t kj_vec3i_zero(void);
kj_def kj_vec3u_t kj_vec3u_zero(void);
kj_def kj_vec3f_t kj_vec3f_one(void);
kj_def kj_vec3i_t kj_vec3i_one(void);
kj_def kj_vec3u_t kj_vec3u_one(void);
kj_def kj_vec3f_t kj_vec3f_negate(kj_vec3f_t a);
kj_def kj_vec3i_t kj_vec3i_negate(kj_vec3i_t a);
kj_def kj_vec3u_t kj_vec3u_negate(kj_vec3u_t a);
kj_def kj_vec3f_t kj_vec3f_add(kj_vec3f_t a, kj_vec3f_t b);
kj_def kj_vec3i_t kj_vec3i_add(kj_vec3i_t a, kj_vec3i_t b);
kj_def kj_vec3u_t kj_vec3u_add(kj_vec3u_t a, kj_vec3u_t b);
kj_def kj_vec3f_t kj_vec3f_sub(kj_vec3f_t a, kj_vec3f_t b);
kj_def kj_vec3i_t kj_vec3i_sub(kj_vec3i_t a, kj_vec3i_t b);
kj_def kj_vec3u_t kj_vec3u_sub(kj_vec3u_t a, kj_vec3u_t b);
kj_def kj_vec3f_t kj_vec3f_mul(kj_vec3f_t a, kj_vec3f_t b);
kj_def kj_vec3i_t kj_vec3i_mul(kj_vec3i_t a, kj_vec3i_t b);
kj_def kj_vec3u_t kj_vec3u_mul(kj_vec3u_t a, kj_vec3u_t b);
kj_def kj_vec3f_t kj_vec3f_div(kj_vec3f_t a, kj_vec3f_t b);
kj_def kj_vec3i_t kj_vec3i_div(kj_vec3i_t a, kj_vec3i_t b);
kj_def kj_vec3u_t kj_vec3u_div(kj_vec3u_t a, kj_vec3u_t b);
kj_def f32 kj_vec3f_dot(kj_vec3f_t a, kj_vec3f_t b);
kj_def i32 kj_vec3i_dot(kj_vec3i_t a, kj_vec3i_t b);
kj_def u32 kj_vec3u_dot(kj_vec3u_t a, kj_vec3u_t b);
kj_def kj_vec3f_t kj_vec3f_cross(kj_vec3f_t a, kj_vec3f_t b);
kj_def kj_vec3i_t kj_vec3i_cross(kj_vec3i_t a, kj_vec3i_t b);
kj_def kj_vec3u_t kj_vec3u_cross(kj_vec3u_t a, kj_vec3u_t b);

typedef struct kj_vec4f {
    f32 x, y, z, w;
} kj_vec4f_t;

typedef struct kj_vec4i {
    i32 x, y, z, w;
} kj_vec4i_t;

typedef struct kj_vec4u {
    u32 x, y, z, w;
} kj_vec4u_t;

kj_def kj_vec4f_t kj_vec4f(f32 x, f32 y, f32 z, f32 w);
kj_def kj_vec4i_t kj_vec4i(i32 x, i32 y, i32 z, i32 w);
kj_def kj_vec4u_t kj_vec4u(u32 x, u32 y, u32 z, u32 w);
kj_def kj_vec4f_t kj_vec4f_zero(void);
kj_def kj_vec4i_t kj_vec4i_zero(void);
kj_def kj_vec4u_t kj_vec4u_zero(void);
kj_def kj_vec4f_t kj_vec4f_one(void);
kj_def kj_vec4i_t kj_vec4i_one(void);
kj_def kj_vec4u_t kj_vec4u_one(void);
kj_def kj_vec4f_t kj_vec4f_negate(kj_vec4f_t a);
kj_def kj_vec4i_t kj_vec4i_negate(kj_vec4i_t a);
kj_def kj_vec4u_t kj_vec4u_negate(kj_vec4u_t a);
kj_def kj_vec4f_t kj_vec4f_add(kj_vec4f_t a, kj_vec4f_t b);
kj_def kj_vec4i_t kj_vec4i_add(kj_vec4i_t a, kj_vec4i_t b);
kj_def kj_vec4u_t kj_vec4u_add(kj_vec4u_t a, kj_vec4u_t b);
kj_def kj_vec4f_t kj_vec4f_sub(kj_vec4f_t a, kj_vec4f_t b);
kj_def kj_vec4i_t kj_vec4i_sub(kj_vec4i_t a, kj_vec4i_t b);
kj_def kj_vec4u_t kj_vec4u_sub(kj_vec4u_t a, kj_vec4u_t b);
kj_def kj_vec4f_t kj_vec4f_mul(kj_vec4f_t a, kj_vec4f_t b);
kj_def kj_vec4i_t kj_vec4i_mul(kj_vec4i_t a, kj_vec4i_t b);
kj_def kj_vec4u_t kj_vec4u_mul(kj_vec4u_t a, kj_vec4u_t b);
kj_def kj_vec4f_t kj_vec4f_div(kj_vec4f_t a, kj_vec4f_t b);
kj_def kj_vec4i_t kj_vec4i_div(kj_vec4i_t a, kj_vec4i_t b);
kj_def kj_vec4u_t kj_vec4u_div(kj_vec4u_t a, kj_vec4u_t b);
kj_def f32 kj_vec4f_dot(kj_vec4f_t a, kj_vec4f_t b);
kj_def i32 kj_vec4i_dot(kj_vec4i_t a, kj_vec4i_t b);
kj_def u32 kj_vec4u_dot(kj_vec4u_t a, kj_vec4u_t b);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_VEC_IMPLEMENTATION)
inline kj_vec2f_t kj_vec2f(f32 x, f32 y) { return (kj_vec2f_t) { x, y }; }
inline kj_vec2i_t kj_vec2i(i32 x, i32 y) { return (kj_vec2i_t) { x, y }; }
inline kj_vec2u_t kj_vec2u(u32 x, u32 y) { return (kj_vec2u_t) { x, y }; }
inline kj_vec2f_t kj_vec2f_zero(void) { return kj_vec2f(0.0f, 0.0f); }
inline kj_vec2i_t kj_vec2i_zero(void) { return kj_vec2i(0, 0); }
inline kj_vec2u_t kj_vec2u_zero(void) { return kj_vec2u(0, 0); }
inline kj_vec2f_t kj_vec2f_one(void) { return kj_vec2f(1.0f, 1.0f); }
inline kj_vec2i_t kj_vec2i_one(void) { return kj_vec2i(1, 1); }
inline kj_vec2u_t kj_vec2u_one(void) { return kj_vec2u(1, 1); }
inline kj_vec2f_t kj_vec2f_negate(kj_vec2f_t a) { return kj_vec2f(-a.x, -a.y); }
inline kj_vec2i_t kj_vec2i_negate(kj_vec2i_t a) { return kj_vec2i(-a.x, -a.y); }
inline kj_vec2u_t kj_vec2u_negate(kj_vec2u_t a) { return kj_vec2u(-a.x, -a.y); }
inline kj_vec2f_t kj_vec2f_add(kj_vec2f_t a, kj_vec2f_t b) { return kj_vec2f(a.x + b.x, a.y + b.y); }
inline kj_vec2i_t kj_vec2i_add(kj_vec2i_t a, kj_vec2i_t b) { return kj_vec2i(a.x + b.x, a.y + b.y); }
inline kj_vec2u_t kj_vec2u_add(kj_vec2u_t a, kj_vec2u_t b) { return kj_vec2u(a.x + b.x, a.y + b.y); }
inline kj_vec2f_t kj_vec2f_sub(kj_vec2f_t a, kj_vec2f_t b) { return kj_vec2f(a.x - b.x, a.y - b.y); }
inline kj_vec2i_t kj_vec2i_sub(kj_vec2i_t a, kj_vec2i_t b) { return kj_vec2i(a.x - b.x, a.y - b.y); }
inline kj_vec2u_t kj_vec2u_sub(kj_vec2u_t a, kj_vec2u_t b) { return kj_vec2u(a.x - b.x, a.y - b.y); }
inline kj_vec2f_t kj_vec2f_mul(kj_vec2f_t a, kj_vec2f_t b) { return kj_vec2f(a.x * b.x, a.y * b.y); }
inline kj_vec2i_t kj_vec2i_mul(kj_vec2i_t a, kj_vec2i_t b) { return kj_vec2i(a.x * b.x, a.y * b.y); }
inline kj_vec2u_t kj_vec2u_mul(kj_vec2u_t a, kj_vec2u_t b) { return kj_vec2u(a.x * b.x, a.y * b.y); }
inline kj_vec2f_t kj_vec2f_div(kj_vec2f_t a, kj_vec2f_t b) { return kj_vec2f(a.x / b.x, a.y / b.y); }
inline kj_vec2i_t kj_vec2i_div(kj_vec2i_t a, kj_vec2i_t b) { return kj_vec2i(a.x / b.x, a.y / b.y); }
inline kj_vec2u_t kj_vec2u_div(kj_vec2u_t a, kj_vec2u_t b) { return kj_vec2u(a.x / b.x, a.y / b.y); }
inline f32 kj_vec2f_dot(kj_vec2f_t a, kj_vec2f_t b) { return (a.x * b.y + a.y * b.y); }
inline i32 kj_vec2i_dot(kj_vec2i_t a, kj_vec2i_t b) { return (a.x * b.y + a.y * b.y); }
inline u32 kj_vec2u_dot(kj_vec2u_t a, kj_vec2u_t b) { return (a.x * b.y + a.y * b.y); }
inline f32 kj_vec2f_cross(kj_vec2f_t a, kj_vec2f_t b) { return (a.x * b.y - b.x * a.y); }
inline i32 kj_vec2i_cross(kj_vec2i_t a, kj_vec2i_t b) { return (a.x * b.y - b.x * a.y); }
inline u32 kj_vec2u_cross(kj_vec2u_t a, kj_vec2u_t b) { return (a.x * b.y - b.x * a.y); }

inline kj_vec3f_t kj_vec3f(f32 x, f32 y, f32 z) { return (kj_vec3f_t) { x, y, z }; }
inline kj_vec3i_t kj_vec3i(i32 x, i32 y, i32 z) { return (kj_vec3i_t) { x, y, z }; }
inline kj_vec3u_t kj_vec3u(u32 x, u32 y, u32 z) { return (kj_vec3u_t) { x, y, z }; }
inline kj_vec3f_t kj_vec3f_zero(void) { return kj_vec3f(0.0f, 0.0f, 0.0f); }
inline kj_vec3i_t kj_vec3i_zero(void) { return kj_vec3i(0, 0, 0); }
inline kj_vec3u_t kj_vec3u_zero(void) { return kj_vec3u(0, 0, 0); }
inline kj_vec3f_t kj_vec3f_one(void) { return kj_vec3f(1.0f, 1.0f, 1.0f); }
inline kj_vec3i_t kj_vec3i_one(void) { return kj_vec3i(1, 1, 1); }
inline kj_vec3u_t kj_vec3u_one(void) { return kj_vec3u(1, 1, 1); }
inline kj_vec3f_t kj_vec3f_negate(kj_vec3f_t a) { return kj_vec3f(-a.x, -a.y, -a.z); }
inline kj_vec3i_t kj_vec3i_negate(kj_vec3i_t a) { return kj_vec3i(-a.x, -a.y, -a.z); }
inline kj_vec3u_t kj_vec3u_negate(kj_vec3u_t a) { return kj_vec3u(-a.x, -a.y, -a.z); }
inline kj_vec3f_t kj_vec3f_add(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.x + b.x, a.y + b.y, a.z + b.z); }
inline kj_vec3i_t kj_vec3i_add(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.x + b.x, a.y + b.y, a.z + b.z); }
inline kj_vec3u_t kj_vec3u_add(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.x + b.x, a.y + b.y, a.z + b.z); }
inline kj_vec3f_t kj_vec3f_sub(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.x - b.x, a.y - b.y, a.z - b.z); }
inline kj_vec3i_t kj_vec3i_sub(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.x - b.x, a.y - b.y, a.z - b.z); }
inline kj_vec3u_t kj_vec3u_sub(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.x - b.x, a.y - b.y, a.z - b.z); }
inline kj_vec3f_t kj_vec3f_mul(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.x * b.x, a.y * b.y, a.z * b.z); }
inline kj_vec3i_t kj_vec3i_mul(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.x * b.x, a.y * b.y, a.z * b.z); }
inline kj_vec3u_t kj_vec3u_mul(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.x * b.x, a.y * b.y, a.z * b.z); }
inline kj_vec3f_t kj_vec3f_div(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.x / b.x, a.y / b.y, a.z / b.z); }
inline kj_vec3i_t kj_vec3i_div(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.x / b.x, a.y / b.y, a.z / b.z); }
inline kj_vec3u_t kj_vec3u_div(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.x / b.x, a.y / b.y, a.z / b.z); }
inline f32 kj_vec3f_dot(kj_vec3f_t a, kj_vec3f_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z); }
inline i32 kj_vec3i_dot(kj_vec3i_t a, kj_vec3i_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z); }
inline u32 kj_vec3u_dot(kj_vec3u_t a, kj_vec3u_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z); }
inline kj_vec3f_t kj_vec3f_cross(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
inline kj_vec3i_t kj_vec3i_cross(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
inline kj_vec3u_t kj_vec3u_cross(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }

inline kj_vec4f_t kj_vec4f(f32 x, f32 y, f32 z, f32 w) { return (kj_vec4f_t) { x, y, z, w }; }
inline kj_vec4i_t kj_vec4i(i32 x, i32 y, i32 z, i32 w) { return (kj_vec4i_t) { x, y, z, w }; }
inline kj_vec4u_t kj_vec4u(u32 x, u32 y, u32 z, u32 w) { return (kj_vec4u_t) { x, y, z, w }; }
inline kj_vec4f_t kj_vec4f_zero(void) { return kj_vec4f(0.0f, 0.0f, 0.0f, 0.0f); }
inline kj_vec4i_t kj_vec4i_zero(void) { return kj_vec4i(0, 0, 0, 0); }
inline kj_vec4u_t kj_vec4u_zero(void) { return kj_vec4u(0, 0, 0, 0); }
inline kj_vec4f_t kj_vec4f_one(void) { return kj_vec4f(1.0f, 1.0f, 1.0f, 1.0f); }
inline kj_vec4i_t kj_vec4i_one(void) { return kj_vec4i(1, 1, 1, 1); }
inline kj_vec4u_t kj_vec4u_one(void) { return kj_vec4u(1, 1, 1, 1); }
inline kj_vec4f_t kj_vec4f_negate(kj_vec4f_t a) { return kj_vec4f(-a.x, -a.y, -a.z, -a.w); }
inline kj_vec4i_t kj_vec4i_negate(kj_vec4i_t a) { return kj_vec4i(-a.x, -a.y, -a.z, -a.w); }
inline kj_vec4u_t kj_vec4u_negate(kj_vec4u_t a) { return kj_vec4u(-a.x, -a.y, -a.z, -a.w); }
inline kj_vec4f_t kj_vec4f_add(kj_vec4f_t a, kj_vec4f_t b) { return kj_vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline kj_vec4i_t kj_vec4i_add(kj_vec4i_t a, kj_vec4i_t b) { return kj_vec4i(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline kj_vec4u_t kj_vec4u_add(kj_vec4u_t a, kj_vec4u_t b) { return kj_vec4u(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline kj_vec4f_t kj_vec4f_sub(kj_vec4f_t a, kj_vec4f_t b) { return kj_vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline kj_vec4i_t kj_vec4i_sub(kj_vec4i_t a, kj_vec4i_t b) { return kj_vec4i(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline kj_vec4u_t kj_vec4u_sub(kj_vec4u_t a, kj_vec4u_t b) { return kj_vec4u(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline kj_vec4f_t kj_vec4f_mul(kj_vec4f_t a, kj_vec4f_t b) { return kj_vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
inline kj_vec4i_t kj_vec4i_mul(kj_vec4i_t a, kj_vec4i_t b) { return kj_vec4i(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
inline kj_vec4u_t kj_vec4u_mul(kj_vec4u_t a, kj_vec4u_t b) { return kj_vec4u(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
inline kj_vec4f_t kj_vec4f_div(kj_vec4f_t a, kj_vec4f_t b) { return kj_vec4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
inline kj_vec4i_t kj_vec4i_div(kj_vec4i_t a, kj_vec4i_t b) { return kj_vec4i(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
inline kj_vec4u_t kj_vec4u_div(kj_vec4u_t a, kj_vec4u_t b) { return kj_vec4u(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
inline f32 kj_vec4f_dot(kj_vec4f_t a, kj_vec4f_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z + a.w * b.w); }
inline i32 kj_vec4i_dot(kj_vec4i_t a, kj_vec4i_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z + a.w * b.w); }
inline u32 kj_vec4u_dot(kj_vec4u_t a, kj_vec4u_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z + a.w * b.w); }
#endif
