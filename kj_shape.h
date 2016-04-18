#ifndef KJ_SHAPE_H
#define KJ_SHAPE_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_SHAPE_VERSION_MAJOR 0
#define KJ_SHAPE_VERSION_MINOR 1
#define KJ_SHAPE_VERSION_PATCH 0

typedef struct kj_rect2f {
    f32 x, y, w, h;
} kj_rect2f_t;

typedef struct kj_rect2i {
    i32 x, y, w, h;
} kj_rect2i_t;

typedef struct kj_rect2u {
    u32 x, y, w, h;
} kj_rect2u_t;

kj_rect2f_t kj_rect2f(f32 x, f32 y, f32 w, f32 h);
kj_rect2i_t kj_rect2i(i32 x, i32 y, i32 w, i32 h);
kj_rect2u_t kj_rect2u(u32 x, u32 y, u32 w, u32 h);

typedef struct kj_rect3f {
    f32 x, y, z, w, h, d;
} kj_rect3f_t;

typedef struct kj_rect3i {
    i32 x, y, z, w, h, d;
} kj_rect3i_t;

typedef struct kj_rect3u {
    u32 x, y, z, w, h, d;
} kj_rect3u_t;

kj_rect3f_t kj_rect3f(f32 x, f32 y, f32 z, f32 w, f32 h, f32 d);
kj_rect3i_t kj_rect3i(i32 x, i32 y, i32 z, i32 w, i32 h, i32 d);
kj_rect3u_t kj_rect3u(u32 x, u32 y, u32 z, u32 w, u32 h, u32 d);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_SHAPE_IMPLEMENTATION)

kj_rect2f_t kj_rect2f(f32 x, f32 y, f32 w, f32 h) { return (kj_rect2f_t) { x, y, w, h }; }
kj_rect2i_t kj_rect2i(i32 x, i32 y, i32 w, i32 h) { return (kj_rect2i_t) { x, y, w, h }; }
kj_rect2u_t kj_rect2u(u32 x, u32 y, u32 w, u32 h) { return (kj_rect2u_t) { x, y, w, h }; }

kj_rect3f_t kj_rect3f(f32 x, f32 y, f32 z, f32 w, f32 h, f32 d) { return (kj_rect3f_t) { x, y, z, w, h, d }; }
kj_rect3i_t kj_rect3i(i32 x, i32 y, i32 z, i32 w, i32 h, i32 d) { return (kj_rect3i_t) { x, y, z, w, h, d }; }
kj_rect3u_t kj_rect3u(u32 x, u32 y, u32 z, u32 w, u32 h, u32 d) { return (kj_rect3u_t) { x, y, z, w, h, d }; }

#endif
