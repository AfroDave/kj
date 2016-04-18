#ifndef KJ_VEC_H
#define KJ_VEC_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct kj_vec2f {
    f32 x, y;
} kj_vec2f_t;

typedef struct kj_vec2i {
    i32 x, y;
} kj_vec2i_t;

typedef struct kj_vec2u {
    u32 x, y;
} kj_vec2u_t;

kj_vec2f_t kj_vec2f(f32 x, f32 y);
kj_vec2i_t kj_vec2i(i32 x, i32 y);
kj_vec2u_t kj_vec2u(u32 x, u32 y);

kj_vec2f_t kj_vec2f_zero(void);
kj_vec2i_t kj_vec2i_zero(void);
kj_vec2u_t kj_vec2u_zero(void);

kj_vec2f_t kj_vec2f_one(void);
kj_vec2i_t kj_vec2i_one(void);
kj_vec2u_t kj_vec2u_one(void);

kj_vec2f_t kj_vec2f_negate(kj_vec2f_t a);
kj_vec2i_t kj_vec2i_negate(kj_vec2i_t a);
kj_vec2u_t kj_vec2u_negate(kj_vec2u_t a);

kj_vec2f_t kj_vec2f_add(kj_vec2f_t a, kj_vec2f_t b);
kj_vec2i_t kj_vec2i_add(kj_vec2i_t a, kj_vec2i_t b);
kj_vec2u_t kj_vec2u_add(kj_vec2u_t a, kj_vec2u_t b);

kj_vec2f_t kj_vec2f_sub(kj_vec2f_t a, kj_vec2f_t b);
kj_vec2i_t kj_vec2i_sub(kj_vec2i_t a, kj_vec2i_t b);
kj_vec2u_t kj_vec2u_sub(kj_vec2u_t a, kj_vec2u_t b);

kj_vec2f_t kj_vec2f_mul(kj_vec2f_t a, kj_vec2f_t b);
kj_vec2i_t kj_vec2i_mul(kj_vec2i_t a, kj_vec2i_t b);
kj_vec2u_t kj_vec2u_mul(kj_vec2u_t a, kj_vec2u_t b);

kj_vec2f_t kj_vec2f_div(kj_vec2f_t a, kj_vec2f_t b);
kj_vec2i_t kj_vec2i_div(kj_vec2i_t a, kj_vec2i_t b);
kj_vec2u_t kj_vec2u_div(kj_vec2u_t a, kj_vec2u_t b);

f32 kj_vec2f_dot(kj_vec2f_t a, kj_vec2f_t b);
i32 kj_vec2i_dot(kj_vec2i_t a, kj_vec2i_t b);
u32 kj_vec2u_dot(kj_vec2u_t a, kj_vec2u_t b);

f32 kj_vec2f_cross(kj_vec2f_t a, kj_vec2f_t b);
i32 kj_vec2i_cross(kj_vec2i_t a, kj_vec2i_t b);
u32 kj_vec2u_cross(kj_vec2u_t a, kj_vec2u_t b);

typedef struct kj_vec3f {
    f32 x, y, z;
} kj_vec3f_t;

typedef struct kj_vec3i {
    i32 x, y, z;
} kj_vec3i_t;

typedef struct kj_vec3u {
    u32 x, y, z;
} kj_vec3u_t;

kj_vec3f_t kj_vec3f(f32 x, f32 y, f32 z);
kj_vec3i_t kj_vec3i(i32 x, i32 y, i32 z);
kj_vec3u_t kj_vec3u(u32 x, u32 y, u32 z);

kj_vec3f_t kj_vec3f_zero(void);
kj_vec3i_t kj_vec3i_zero(void);
kj_vec3u_t kj_vec3u_zero(void);

kj_vec3f_t kj_vec3f_one(void);
kj_vec3i_t kj_vec3i_one(void);
kj_vec3u_t kj_vec3u_one(void);

kj_vec3f_t kj_vec3f_negate(kj_vec3f_t a);
kj_vec3i_t kj_vec3i_negate(kj_vec3i_t a);
kj_vec3u_t kj_vec3u_negate(kj_vec3u_t a);

kj_vec3f_t kj_vec3f_add(kj_vec3f_t a, kj_vec3f_t b);
kj_vec3i_t kj_vec3i_add(kj_vec3i_t a, kj_vec3i_t b);
kj_vec3u_t kj_vec3u_add(kj_vec3u_t a, kj_vec3u_t b);

kj_vec3f_t kj_vec3f_sub(kj_vec3f_t a, kj_vec3f_t b);
kj_vec3i_t kj_vec3i_sub(kj_vec3i_t a, kj_vec3i_t b);
kj_vec3u_t kj_vec3u_sub(kj_vec3u_t a, kj_vec3u_t b);

kj_vec3f_t kj_vec3f_mul(kj_vec3f_t a, kj_vec3f_t b);
kj_vec3i_t kj_vec3i_mul(kj_vec3i_t a, kj_vec3i_t b);
kj_vec3u_t kj_vec3u_mul(kj_vec3u_t a, kj_vec3u_t b);

kj_vec3f_t kj_vec3f_div(kj_vec3f_t a, kj_vec3f_t b);
kj_vec3i_t kj_vec3i_div(kj_vec3i_t a, kj_vec3i_t b);
kj_vec3u_t kj_vec3u_div(kj_vec3u_t a, kj_vec3u_t b);

f32 kj_vec3f_dot(kj_vec3f_t a, kj_vec3f_t b);
i32 kj_vec3i_dot(kj_vec3i_t a, kj_vec3i_t b);
u32 kj_vec3u_dot(kj_vec3u_t a, kj_vec3u_t b);

kj_vec3f_t kj_vec3f_cross(kj_vec3f_t a, kj_vec3f_t b);
kj_vec3i_t kj_vec3i_cross(kj_vec3i_t a, kj_vec3i_t b);
kj_vec3u_t kj_vec3u_cross(kj_vec3u_t a, kj_vec3u_t b);

typedef struct kj_vec4f {
    f32 x, y, z, w;
} kj_vec4f_t;

typedef struct kj_vec4i {
    i32 x, y, z, w;
} kj_vec4i_t;

typedef struct kj_vec4u {
    u32 x, y, z, w;
} kj_vec4u_t;

kj_vec4f_t kj_vec4f(f32 x, f32 y, f32 z, f32 w);
kj_vec4i_t kj_vec4i(i32 x, i32 y, i32 z, i32 w);
kj_vec4u_t kj_vec4u(u32 x, u32 y, u32 z, u32 w);

kj_vec4f_t kj_vec4f_zero(void);
kj_vec4i_t kj_vec4i_zero(void);
kj_vec4u_t kj_vec4u_zero(void);

kj_vec4f_t kj_vec4f_one(void);
kj_vec4i_t kj_vec4i_one(void);
kj_vec4u_t kj_vec4u_one(void);

kj_vec4f_t kj_vec4f_negate(kj_vec4f_t a);
kj_vec4i_t kj_vec4i_negate(kj_vec4i_t a);
kj_vec4u_t kj_vec4u_negate(kj_vec4u_t a);

kj_vec4f_t kj_vec4f_add(kj_vec4f_t a, kj_vec4f_t b);
kj_vec4i_t kj_vec4i_add(kj_vec4i_t a, kj_vec4i_t b);
kj_vec4u_t kj_vec4u_add(kj_vec4u_t a, kj_vec4u_t b);

kj_vec4f_t kj_vec4f_sub(kj_vec4f_t a, kj_vec4f_t b);
kj_vec4i_t kj_vec4i_sub(kj_vec4i_t a, kj_vec4i_t b);
kj_vec4u_t kj_vec4u_sub(kj_vec4u_t a, kj_vec4u_t b);

kj_vec4f_t kj_vec4f_mul(kj_vec4f_t a, kj_vec4f_t b);
kj_vec4i_t kj_vec4i_mul(kj_vec4i_t a, kj_vec4i_t b);
kj_vec4u_t kj_vec4u_mul(kj_vec4u_t a, kj_vec4u_t b);

kj_vec4f_t kj_vec4f_div(kj_vec4f_t a, kj_vec4f_t b);
kj_vec4i_t kj_vec4i_div(kj_vec4i_t a, kj_vec4i_t b);
kj_vec4u_t kj_vec4u_div(kj_vec4u_t a, kj_vec4u_t b);

f32 kj_vec4f_dot(kj_vec4f_t a, kj_vec4f_t b);
i32 kj_vec4i_dot(kj_vec4i_t a, kj_vec4i_t b);
u32 kj_vec4u_dot(kj_vec4u_t a, kj_vec4u_t b);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_VEC_IMPLEMENTATION)
kj_vec2f_t kj_vec2f(f32 x, f32 y) { return (kj_vec2f_t) { x, y }; }
kj_vec2i_t kj_vec2i(i32 x, i32 y) { return (kj_vec2i_t) { x, y }; }
kj_vec2u_t kj_vec2u(u32 x, u32 y) { return (kj_vec2u_t) { x, y }; }
kj_vec2f_t kj_vec2f_zero(void) { return kj_vec2f(0.0f, 0.0f); }
kj_vec2i_t kj_vec2i_zero(void) { return kj_vec2i(0, 0); }
kj_vec2u_t kj_vec2u_zero(void) { return kj_vec2u(0, 0); }
kj_vec2f_t kj_vec2f_one(void) { return kj_vec2f(1.0f, 1.0f); }
kj_vec2i_t kj_vec2i_one(void) { return kj_vec2i(1, 1); }
kj_vec2u_t kj_vec2u_one(void) { return kj_vec2u(1, 1); }
kj_vec2f_t kj_vec2f_negate(kj_vec2f_t a) { return kj_vec2f(-a.x, -a.y); }
kj_vec2i_t kj_vec2i_negate(kj_vec2i_t a) { return kj_vec2i(-a.x, -a.y); }
kj_vec2u_t kj_vec2u_negate(kj_vec2u_t a) { return kj_vec2u(-a.x, -a.y); }
kj_vec2f_t kj_vec2f_add(kj_vec2f_t a, kj_vec2f_t b) { return kj_vec2f(a.x + b.x, a.y + b.y); }
kj_vec2i_t kj_vec2i_add(kj_vec2i_t a, kj_vec2i_t b) { return kj_vec2i(a.x + b.x, a.y + b.y); }
kj_vec2u_t kj_vec2u_add(kj_vec2u_t a, kj_vec2u_t b) { return kj_vec2u(a.x + b.x, a.y + b.y); }
kj_vec2f_t kj_vec2f_sub(kj_vec2f_t a, kj_vec2f_t b) { return kj_vec2f(a.x - b.x, a.y - b.y); }
kj_vec2i_t kj_vec2i_sub(kj_vec2i_t a, kj_vec2i_t b) { return kj_vec2i(a.x - b.x, a.y - b.y); }
kj_vec2u_t kj_vec2u_sub(kj_vec2u_t a, kj_vec2u_t b) { return kj_vec2u(a.x - b.x, a.y - b.y); }
kj_vec2f_t kj_vec2f_mul(kj_vec2f_t a, kj_vec2f_t b) { return kj_vec2f(a.x * b.x, a.y * b.y); }
kj_vec2i_t kj_vec2i_mul(kj_vec2i_t a, kj_vec2i_t b) { return kj_vec2i(a.x * b.x, a.y * b.y); }
kj_vec2u_t kj_vec2u_mul(kj_vec2u_t a, kj_vec2u_t b) { return kj_vec2u(a.x * b.x, a.y * b.y); }
kj_vec2f_t kj_vec2f_div(kj_vec2f_t a, kj_vec2f_t b) { return kj_vec2f(a.x / b.x, a.y / b.y); }
kj_vec2i_t kj_vec2i_div(kj_vec2i_t a, kj_vec2i_t b) { return kj_vec2i(a.x / b.x, a.y / b.y); }
kj_vec2u_t kj_vec2u_div(kj_vec2u_t a, kj_vec2u_t b) { return kj_vec2u(a.x / b.x, a.y / b.y); }
f32 kj_vec2f_dot(kj_vec2f_t a, kj_vec2f_t b) { return (a.x * b.y + a.y * b.y); }
i32 kj_vec2i_dot(kj_vec2i_t a, kj_vec2i_t b) { return (a.x * b.y + a.y * b.y); }
u32 kj_vec2u_dot(kj_vec2u_t a, kj_vec2u_t b) { return (a.x * b.y + a.y * b.y); }
f32 kj_vec2f_cross(kj_vec2f_t a, kj_vec2f_t b) { return (a.x * b.y - b.x * a.y); }
i32 kj_vec2i_cross(kj_vec2i_t a, kj_vec2i_t b) { return (a.x * b.y - b.x * a.y); }
u32 kj_vec2u_cross(kj_vec2u_t a, kj_vec2u_t b) { return (a.x * b.y - b.x * a.y); }

kj_vec3f_t kj_vec3f(f32 x, f32 y, f32 z) { return (kj_vec3f_t) { x, y, z }; }
kj_vec3i_t kj_vec3i(i32 x, i32 y, i32 z) { return (kj_vec3i_t) { x, y, z }; }
kj_vec3u_t kj_vec3u(u32 x, u32 y, u32 z) { return (kj_vec3u_t) { x, y, z }; }
kj_vec3f_t kj_vec3f_zero(void) { return kj_vec3f(0.0f, 0.0f, 0.0f); }
kj_vec3i_t kj_vec3i_zero(void) { return kj_vec3i(0, 0, 0); }
kj_vec3u_t kj_vec3u_zero(void) { return kj_vec3u(0, 0, 0); }
kj_vec3f_t kj_vec3f_one(void) { return kj_vec3f(1.0f, 1.0f, 1.0f); }
kj_vec3i_t kj_vec3i_one(void) { return kj_vec3i(1, 1, 1); }
kj_vec3u_t kj_vec3u_one(void) { return kj_vec3u(1, 1, 1); }
kj_vec3f_t kj_vec3f_negate(kj_vec3f_t a) { return kj_vec3f(-a.x, -a.y, -a.z); }
kj_vec3i_t kj_vec3i_negate(kj_vec3i_t a) { return kj_vec3i(-a.x, -a.y, -a.z); }
kj_vec3u_t kj_vec3u_negate(kj_vec3u_t a) { return kj_vec3u(-a.x, -a.y, -a.z); }
kj_vec3f_t kj_vec3f_add(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.x + b.x, a.y + b.y, a.z + b.z); }
kj_vec3i_t kj_vec3i_add(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.x + b.x, a.y + b.y, a.z + b.z); }
kj_vec3u_t kj_vec3u_add(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.x + b.x, a.y + b.y, a.z + b.z); }
kj_vec3f_t kj_vec3f_sub(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.x - b.x, a.y - b.y, a.z - b.z); }
kj_vec3i_t kj_vec3i_sub(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.x - b.x, a.y - b.y, a.z - b.z); }
kj_vec3u_t kj_vec3u_sub(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.x - b.x, a.y - b.y, a.z - b.z); }
kj_vec3f_t kj_vec3f_mul(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.x * b.x, a.y * b.y, a.z * b.z); }
kj_vec3i_t kj_vec3i_mul(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.x * b.x, a.y * b.y, a.z * b.z); }
kj_vec3u_t kj_vec3u_mul(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.x * b.x, a.y * b.y, a.z * b.z); }
kj_vec3f_t kj_vec3f_div(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.x / b.x, a.y / b.y, a.z / b.z); }
kj_vec3i_t kj_vec3i_div(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.x / b.x, a.y / b.y, a.z / b.z); }
kj_vec3u_t kj_vec3u_div(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.x / b.x, a.y / b.y, a.z / b.z); }
f32 kj_vec3f_dot(kj_vec3f_t a, kj_vec3f_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z); }
i32 kj_vec3i_dot(kj_vec3i_t a, kj_vec3i_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z); }
u32 kj_vec3u_dot(kj_vec3u_t a, kj_vec3u_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z); }
kj_vec3f_t kj_vec3f_cross(kj_vec3f_t a, kj_vec3f_t b) { return kj_vec3f(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
kj_vec3i_t kj_vec3i_cross(kj_vec3i_t a, kj_vec3i_t b) { return kj_vec3i(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
kj_vec3u_t kj_vec3u_cross(kj_vec3u_t a, kj_vec3u_t b) { return kj_vec3u(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }

kj_vec4f_t kj_vec4f(f32 x, f32 y, f32 z, f32 w) { return (kj_vec4f_t) { x, y, z, w }; }
kj_vec4i_t kj_vec4i(i32 x, i32 y, i32 z, i32 w) { return (kj_vec4i_t) { x, y, z, w }; }
kj_vec4u_t kj_vec4u(u32 x, u32 y, u32 z, u32 w) { return (kj_vec4u_t) { x, y, z, w }; }
kj_vec4f_t kj_vec4f_zero(void) { return kj_vec4f(0.0f, 0.0f, 0.0f, 0.0f); }
kj_vec4i_t kj_vec4i_zero(void) { return kj_vec4i(0, 0, 0, 0); }
kj_vec4u_t kj_vec4u_zero(void) { return kj_vec4u(0, 0, 0, 0); }
kj_vec4f_t kj_vec4f_one(void) { return kj_vec4f(1.0f, 1.0f, 1.0f, 1.0f); }
kj_vec4i_t kj_vec4i_one(void) { return kj_vec4i(1, 1, 1, 1); }
kj_vec4u_t kj_vec4u_one(void) { return kj_vec4u(1, 1, 1, 1); }
kj_vec4f_t kj_vec4f_negate(kj_vec4f_t a) { return kj_vec4f(-a.x, -a.y, -a.z, -a.w); }
kj_vec4i_t kj_vec4i_negate(kj_vec4i_t a) { return kj_vec4i(-a.x, -a.y, -a.z, -a.w); }
kj_vec4u_t kj_vec4u_negate(kj_vec4u_t a) { return kj_vec4u(-a.x, -a.y, -a.z, -a.w); }
kj_vec4f_t kj_vec4f_add(kj_vec4f_t a, kj_vec4f_t b) { return kj_vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
kj_vec4i_t kj_vec4i_add(kj_vec4i_t a, kj_vec4i_t b) { return kj_vec4i(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
kj_vec4u_t kj_vec4u_add(kj_vec4u_t a, kj_vec4u_t b) { return kj_vec4u(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
kj_vec4f_t kj_vec4f_sub(kj_vec4f_t a, kj_vec4f_t b) { return kj_vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
kj_vec4i_t kj_vec4i_sub(kj_vec4i_t a, kj_vec4i_t b) { return kj_vec4i(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
kj_vec4u_t kj_vec4u_sub(kj_vec4u_t a, kj_vec4u_t b) { return kj_vec4u(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
kj_vec4f_t kj_vec4f_mul(kj_vec4f_t a, kj_vec4f_t b) { return kj_vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
kj_vec4i_t kj_vec4i_mul(kj_vec4i_t a, kj_vec4i_t b) { return kj_vec4i(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
kj_vec4u_t kj_vec4u_mul(kj_vec4u_t a, kj_vec4u_t b) { return kj_vec4u(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
kj_vec4f_t kj_vec4f_div(kj_vec4f_t a, kj_vec4f_t b) { return kj_vec4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
kj_vec4i_t kj_vec4i_div(kj_vec4i_t a, kj_vec4i_t b) { return kj_vec4i(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
kj_vec4u_t kj_vec4u_div(kj_vec4u_t a, kj_vec4u_t b) { return kj_vec4u(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
f32 kj_vec4f_dot(kj_vec4f_t a, kj_vec4f_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z + a.w * b.w); }
i32 kj_vec4i_dot(kj_vec4i_t a, kj_vec4i_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z + a.w * b.w); }
u32 kj_vec4u_dot(kj_vec4u_t a, kj_vec4u_t b) { return (a.x * b.y + a.y * b.y + a.z * b.z + a.w * b.w); }
#endif
