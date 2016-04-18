#ifndef KJ_COLOUR_H
#define KJ_COLOUR_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_COLOUR_VERSION_MAJOR 0
#define KJ_COLOUR_VERSION_MINOR 1
#define KJ_COLOUR_VERSION_PATCH 0

typedef struct kj_rgba {
    u8 r, g, b, a;
} kj_rgba_t;

kj_rgba_t kj_rgba(u8 r, u8 g, u8 b, u8 a);
kj_rgba_t kj_rgbaf(f32 r, f32 g, f32 b, f32 a);
u32 kj_rgba_pack(kj_rgba_t rgba);
kj_rgba_t kj_rgba_unpack(u32 packed);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_COLOUR_IMPLEMENTATION)

kj_rgba_t kj_rgba(u8 r, u8 g, u8 b, u8 a)
{
    return (kj_rgba_t) { r, g, b, a };
}

kj_rgba_t kj_rgbaf(f32 r, f32 g, f32 b, f32 a)
{
    return kj_rgba(
        cast_of(u8, kj_range(r, 0.0f, 1.0f, 0.0f, 255.0f)),
        cast_of(u8, kj_range(g, 0.0f, 1.0f, 0.0f, 255.0f)),
        cast_of(u8, kj_range(b, 0.0f, 1.0f, 0.0f, 255.0f)),
        cast_of(u8, kj_range(a, 0.0f, 1.0f, 0.0f, 255.0f)));
}

u32 kj_rgba_pack(kj_rgba_t rgba)
{
    return (rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | (rgba.a << 0);
}

kj_rgba_t kj_rgba_unpack(u32 packed)
{
    return kj_rgba(
        cast_of(u8, (packed & 0xFF000000) >> 24),
        cast_of(u8, (packed & 0x00FF0000) >> 16),
        cast_of(u8, (packed & 0x0000FF00) >> 8),
        cast_of(u8, (packed & 0x000000FF) >> 0));
}


#endif
