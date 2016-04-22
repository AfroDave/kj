#ifndef KJ_COLOUR_H
#define KJ_COLOUR_H

#define KJ_COLOUR_VERSION_MAJOR 0
#define KJ_COLOUR_VERSION_MINOR 1
#define KJ_COLOUR_VERSION_PATCH 0

typedef struct kj_rgba {
    u8 r, g, b, a;
} kj_rgba_t;

typedef struct kj_rgbaf {
    f32 r, g, b, a;
} kj_rgbaf_t;

#if defined(__cplusplus)
extern "C" {
#endif

kj_api kj_rgba_t kj_rgba(u8 r, u8 g, u8 b, u8 a);
kj_api kj_rgba_t kj_rgba_4f(f32 r, f32 g, f32 b, f32 a);
kj_api kj_rgba_t kj_rgba_rgbaf(kj_rgbaf_t rgbaf);
kj_api u32 kj_rgba_pack(kj_rgba_t rgba);
kj_api kj_rgba_t kj_rgba_unpack(u32 packed);

kj_api kj_rgbaf_t kj_rgbaf(f32 r, f32 g, f32 b, f32 a);
kj_api kj_rgbaf_t kj_rgbaf_4b(u8 r, u8 g, u8 b, u8 a);
kj_api kj_rgbaf_t kj_rgbaf_rgba(kj_rgba_t rgba);
kj_api u32 kj_rgbaf_pack(kj_rgbaf_t rgba);
kj_api kj_rgbaf_t kj_rgbaf_unpack(u32 packed);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_COLOUR_IMPLEMENTATION)

kj_rgba_t kj_rgba(u8 r, u8 g, u8 b, u8 a)
{
    return (kj_rgba_t) { r, g, b, a };
}

kj_rgba_t kj_rgba_4f(f32 r, f32 g, f32 b, f32 a)
{
    return kj_rgba(
        cast_of(u8, r * 255.0f + 0.5f),
        cast_of(u8, g * 255.0f + 0.5f),
        cast_of(u8, b * 255.0f + 0.5f),
        cast_of(u8, a * 255.0f + 0.5f));
}

kj_rgba_t kj_rgba_rgbaf(kj_rgbaf_t rgbaf)
{
    return kj_rgba_4f(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
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

kj_rgbaf_t kj_rgbaf(f32 r, f32 g, f32 b, f32 a)
{
    return (kj_rgbaf_t) { r, g, b, a };
}

kj_rgbaf_t kj_rgbaf_4b(u8 r, u8 g, u8 b, u8 a)
{
    return kj_rgbaf(
        cast_of(f32, r / 255.0f),
        cast_of(f32, g / 255.0f),
        cast_of(f32, b / 255.0f),
        cast_of(f32, a / 255.0f));
}

kj_rgbaf_t kj_rgbaf_rgba(kj_rgba_t rgba)
{
    return kj_rgbaf_4b(rgba.r, rgba.g, rgba.b, rgba.a);
}

u32 kj_rgbaf_pack(kj_rgbaf_t rgba)
{
    return
        (cast_of(u8, rgba.r * 255.0f) << 24) |
        (cast_of(u8, rgba.g * 255.0f) << 16) |
        (cast_of(u8, rgba.b * 255.0f) << 8)  |
        (cast_of(u8, rgba.a * 255.0f) << 0);
}

kj_rgbaf_t kj_rgbaf_unpack(u32 packed)
{
    return kj_rgbaf(
        cast_of(f32, ((packed & 0xFF000000) >> 24) / 255.0f),
        cast_of(f32, ((packed & 0x00FF0000) >> 16) / 255.0f),
        cast_of(f32, ((packed & 0x0000FF00) >> 8)  / 255.0f),
        cast_of(f32, ((packed & 0x000000FF) >> 0)  / 255.0f));
}
#endif
