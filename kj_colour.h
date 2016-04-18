#ifndef KJ_COLOUR_H
#define KJ_COLOUR_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct kj_rgba {
    u8 r, g, b, a;
} kj_rgba_t;

kj_rgba_t kj_rgba(u8 r, u8 g, u8 b, u8 a);
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

u32 kj_rgba_pack(kj_rgba_t rgba)
{
    return (rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | (rgba.a << 0);
}

kj_rgba_t kj_rgba_unpack(u32 packed)
{
    kj_rgba_t res;
    res.r = cast_of(u8, (packed & 0xFF000000) >> 24);
    res.g = cast_of(u8, (packed & 0x00FF0000) >> 16);
    res.b = cast_of(u8, (packed & 0x0000FF00) >> 8);
    res.a = cast_of(u8, (packed & 0x000000FF) >> 0);
    return res;
}


#endif
