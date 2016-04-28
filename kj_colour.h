// `kj_colour.h`
// public domain - no offered or implied warranty, use at your own risk

#ifndef KJ_COLOUR_H
#define KJ_COLOUR_H

#define KJ_COLOUR_VERSION_MAJOR 0
#define KJ_COLOUR_VERSION_MINOR 1
#define KJ_COLOUR_VERSION_PATCH 0

typedef struct kjRgba {
    u8 r, g, b, a;
} kjRgba;

typedef struct kjRgbaf {
    f32 r, g, b, a;
} kjRgbaf;

#if defined(__cplusplus)
extern "C" {
#endif

KJ_API kjRgba kj_rgba(u8 r, u8 g, u8 b, u8 a);
KJ_API kjRgba kj_rgba_4f(f32 r, f32 g, f32 b, f32 a);
KJ_API kjRgba kj_rgba_rgbaf(kjRgbaf rgbaf);
KJ_API u32 kj_rgba_pack(kjRgba rgba);
KJ_API kjRgba kj_rgba_unpack(u32 packed);

KJ_API kjRgbaf kjRgbaf(f32 r, f32 g, f32 b, f32 a);
KJ_API kjRgbaf kj_rgbaf_4b(u8 r, u8 g, u8 b, u8 a);
KJ_API kjRgbaf kj_rgbaf_rgba(kjRgba rgba);
KJ_API u32 kj_rgbaf_pack(kjRgbaf rgba);
KJ_API kjRgbaf kj_rgbaf_unpack(u32 packed);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_COLOUR_IMPLEMENTATION)

kjRgba kj_rgba(u8 r, u8 g, u8 b, u8 a) {
    kjRgba res;
    res.r = r;
    res.b = b;
    res.g = g;
    res.a = a;
    return res;
}

kjRgba kj_rgba_4f(f32 r, f32 g, f32 b, f32 a) {
    return kj_rgba(
        cast_of(u8, r * 255.0f + 0.5f),
        cast_of(u8, g * 255.0f + 0.5f),
        cast_of(u8, b * 255.0f + 0.5f),
        cast_of(u8, a * 255.0f + 0.5f));
}

kjRgba kj_rgba_rgbaf(kjRgbaf rgbaf) {
    return kj_rgba_4f(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
}

u32 kj_rgba_pack(kjRgba rgba) {
    return (rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | (rgba.a << 0);
}

kjRgba kj_rgba_unpack(u32 packed) {
    return kj_rgba(
        cast_of(u8, (packed & 0xFF000000) >> 24),
        cast_of(u8, (packed & 0x00FF0000) >> 16),
        cast_of(u8, (packed & 0x0000FF00) >> 8),
        cast_of(u8, (packed & 0x000000FF) >> 0));
}

kjRgbaf kj_rgbaf(f32 r, f32 g, f32 b, f32 a) {
    kjRgbaf res;
    res.r = r;
    res.b = b;
    res.g = g;
    res.a = a;
    return res;
}

kjRgbaf kj_rgbaf_4b(u8 r, u8 g, u8 b, u8 a) {
    return kj_rgbaf(
        cast_of(f32, r / 255.0f),
        cast_of(f32, g / 255.0f),
        cast_of(f32, b / 255.0f),
        cast_of(f32, a / 255.0f));
}

kjRgbaf kj_rgbaf_rgba(kjRgba rgba) {
    return kj_rgbaf_4b(rgba.r, rgba.g, rgba.b, rgba.a);
}

u32 kj_rgbaf_pack(kjRgbaf rgba) {
    return
        (cast_of(u8, rgba.r * 255.0f) << 24) |
        (cast_of(u8, rgba.g * 255.0f) << 16) |
        (cast_of(u8, rgba.b * 255.0f) << 8)  |
        (cast_of(u8, rgba.a * 255.0f) << 0);
}

kjRgbaf kj_rgbaf_unpack(u32 packed) {
    return kj_rgbaf(
        cast_of(f32, ((packed & 0xFF000000) >> 24) / 255.0f),
        cast_of(f32, ((packed & 0x00FF0000) >> 16) / 255.0f),
        cast_of(f32, ((packed & 0x0000FF00) >> 8)  / 255.0f),
        cast_of(f32, ((packed & 0x000000FF) >> 0)  / 255.0f));
}

#endif
