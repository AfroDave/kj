// `kj_math.h`
//
// ---------------------------------- LICENSE ----------------------------------
// This software is in the public domain.  Where that dedication is not
// recognized, you are granted a perpetual, irrevocable license to copy,
// distribute, and modify the source code as you see fit.
//
// The source code is provided "as is", without warranty of any kind, express
// or implied. No attribution is required, but always appreciated.
// =============================================================================
//
// usage:
//      #define KJ_MATH_IMPL
//      #include "kj_math.h"

#ifndef KJ_MATH_H
#define KJ_MATH_H

#define KJ_MATH_VERSION_MAJOR 0
#define KJ_MATH_VERSION_MINOR 4
#define KJ_MATH_VERSION_PATCH 0

#define kj_to_degrees(a) kj_cast(f32, (a) * 57.295779513082320f)
#define kj_to_radians(a) kj_cast(f32, (a) * 0.017453292519943f)
#define kj_from_radians(a) kj_cast(f32, (a) * 57.295779513082320f)
#define kj_from_degrees(a) kj_cast(f32, (a) * 0.017453292519943f)

#define KJ_PI kj_cast(f32, 3.141592653589793f)
#define KJ_TAU kj_cast(f32, 6.283185307179586f)
#define KJ_E kj_cast(f32, 2.718281828459045f)
#define KJ_PHI kj_cast(f32, 1.618033988749894f)

KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_ANONYMOUS_STRUCT)

typedef union kjVec2f {
    struct { f32 x, y; };
    struct { f32 w, h; };
    struct { f32 g, a; };
    f32 e[2];
} kjVec2f;

typedef union kjVec2i {
    struct { i32 x, y; };
    struct { i32 w, h; };
    i32 e[2];
} kjVec2i;

typedef union kjVec2u {
    struct { u32 x, y; };
    struct { u32 w, h; };
    u32 e[2];
} kjVec2u;

typedef union kjVec3f {
    struct { f32 x, y, z; };
    struct { f32 r, g, b; };
    f32 e[3];
} kjVec3f;

typedef union kjVec3i {
    struct { i32 x, y, z; };
    i32 e[3];
} kjVec3i;

typedef union kjVec3u {
    struct { u32 x, y, z; };
    u32 e[3];
} kjVec3u;

typedef union kjVec4f {
    struct { f32 x, y, z, w; };
    struct { f32 r, g, b, a; };
    f32 e[4];
} kjVec4f;

typedef union kjVec4i {
    struct { i32 x, y, z, w; };
    i32 e[4];
} kjVec4i;

typedef union kjVec4u {
    struct { u32 x, y, z, w; };
    u32 e[4];
} kjVec4u;

KJ_COMPILER_WARNING_END

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

typedef struct kjRgba {
    u8 r, g, b, a;
} kjRgba;

KJ_COMPILER_WARNING_BEGIN
KJ_COMPILER_WARNING(KJ_COMPILER_WARNING_MISSING_BRACES)

#define KJ_RGBA_COLOUR_MAP(X)                                                   \
    X(KJ_RGBA_ALICE_BLUE, 0xF0, 0xF8, 0xFF, 0xFF)                               \
    X(KJ_RGBA_ANTIQUE_WHITE, 0xFA, 0xEB, 0xD7, 0xFF)                            \
    X(KJ_RGBA_AQUA, 0x00, 0xFF, 0xFF, 0xFF)                                     \
    X(KJ_RGBA_AQUAMARINE, 0x7F, 0xFF, 0xD4, 0xFF)                               \
    X(KJ_RGBA_AZURE, 0xF0, 0xFF, 0xFF, 0xFF)                                    \
    X(KJ_RGBA_BEIGE, 0xF5, 0xF5, 0xDC, 0xFF)                                    \
    X(KJ_RGBA_BISQUE, 0xFF, 0xE4, 0xC4, 0xFF)                                   \
    X(KJ_RGBA_BLACK, 0x00, 0x00, 0x00, 0xFF)                                    \
    X(KJ_RGBA_BLANCHED_ALMOND, 0xFF, 0xEB, 0xCD, 0xFF)                          \
    X(KJ_RGBA_BLUE, 0x00, 0x00, 0xFF, 0xFF)                                     \
    X(KJ_RGBA_BLUE_VIOLET, 0x8A, 0x2B, 0xE2, 0xFF)                              \
    X(KJ_RGBA_BROWN, 0xA5, 0x2A, 0x2A, 0xFF)                                    \
    X(KJ_RGBA_BURLYWOOD, 0xDE, 0xB8, 0x87, 0xFF)                                \
    X(KJ_RGBA_CADET_BLUE, 0x5F, 0x9E, 0xA0, 0xFF)                               \
    X(KJ_RGBA_CHARTREUSE, 0x7F, 0xFF, 0x00, 0xFF)                               \
    X(KJ_RGBA_CHOCOLATE, 0xD2, 0x69, 0x1E, 0xFF)                                \
    X(KJ_RGBA_CORAL, 0xFF, 0x7F, 0x50, 0xFF)                                    \
    X(KJ_RGBA_CORNFLOWER, 0x64, 0x95, 0xED, 0xFF)                               \
    X(KJ_RGBA_CORNSILK, 0xFF, 0xF8, 0xDC, 0xFF)                                 \
    X(KJ_RGBA_CRIMSON, 0xDC, 0x14, 0x3C, 0xFF)                                  \
    X(KJ_RGBA_CYAN, 0x00, 0xFF, 0xFF, 0xFF)                                     \
    X(KJ_RGBA_DARK_BLUE, 0x00, 0x00, 0x8B, 0xFF)                                \
    X(KJ_RGBA_DARK_CYAN, 0x00, 0x8B, 0x8B, 0xFF)                                \
    X(KJ_RGBA_DARK_GOLDENROD, 0xB8, 0x86, 0x0B, 0xFF)                           \
    X(KJ_RGBA_DARK_GRAY, 0xA9, 0xA9, 0xA9, 0xFF)                                \
    X(KJ_RGBA_DARK_GREEN, 0x00, 0x64, 0x00, 0xFF)                               \
    X(KJ_RGBA_DARK_KHAKI, 0xBD, 0xB7, 0x6B, 0xFF)                               \
    X(KJ_RGBA_DARK_MAGENTA, 0x8B, 0x00, 0x8B, 0xFF)                             \
    X(KJ_RGBA_DARK_OLIVE_GREEN, 0x55, 0x6B, 0x2F, 0xFF)                         \
    X(KJ_RGBA_DARK_ORANGE, 0xFF, 0x8C, 0x00, 0xFF)                              \
    X(KJ_RGBA_DARK_ORCHID, 0x99, 0x32, 0xCC, 0xFF)                              \
    X(KJ_RGBA_DARK_RED, 0x8B, 0x00, 0x00, 0xFF)                                 \
    X(KJ_RGBA_DARK_SALMON, 0xE9, 0x96, 0x7A, 0xFF)                              \
    X(KJ_RGBA_DARK_SEA_GREEN, 0x8F, 0xBC, 0x8F, 0xFF)                           \
    X(KJ_RGBA_DARK_SLATE_BLUE, 0x48, 0x3D, 0x8B, 0xFF)                          \
    X(KJ_RGBA_DARK_SLATE_GRAY, 0x2F, 0x4F, 0x4F, 0xFF)                          \
    X(KJ_RGBA_DARK_TURQUOISE, 0x00, 0xCE, 0xD1, 0xFF)                           \
    X(KJ_RGBA_DARK_VIOLET, 0x94, 0x00, 0xD3, 0xFF)                              \
    X(KJ_RGBA_DEEP_PINK, 0xFF, 0x14, 0x93, 0xFF)                                \
    X(KJ_RGBA_DEEP_SKY_BLUE, 0x00, 0xBF, 0xFF, 0xFF)                            \
    X(KJ_RGBA_DIM_GRAY, 0x69, 0x69, 0x69, 0xFF)                                 \
    X(KJ_RGBA_DODGER_BLUE, 0x1E, 0x90, 0xFF, 0xFF)                              \
    X(KJ_RGBA_FIREBRICK, 0xB2, 0x22, 0x22, 0xFF)                                \
    X(KJ_RGBA_FLORAL_WHITE, 0xFF, 0xFA, 0xF0, 0xFF)                             \
    X(KJ_RGBA_FOREST_GREEN, 0x22, 0x8B, 0x22, 0xFF)                             \
    X(KJ_RGBA_FUCHSIA, 0xFF, 0x00, 0xFF, 0xFF)                                  \
    X(KJ_RGBA_GAINSBORO, 0xDC, 0xDC, 0xDC, 0xFF)                                \
    X(KJ_RGBA_GHOST_WHITE, 0xF8, 0xF8, 0xFF, 0xFF)                              \
    X(KJ_RGBA_GOLD, 0xFF, 0xD7, 0x00, 0xFF)                                     \
    X(KJ_RGBA_GOLDENROD, 0xDA, 0xA5, 0x20, 0xFF)                                \
    X(KJ_RGBA_GRAY, 0xBE, 0xBE, 0xBE, 0xFF)                                     \
    X(KJ_RGBA_GREEN, 0x00, 0xFF, 0x00, 0xFF)                                    \
    X(KJ_RGBA_GREEN_YELLOW, 0xAD, 0xFF, 0x2F, 0xFF)                             \
    X(KJ_RGBA_HONEYDEW, 0xF0, 0xFF, 0xF0, 0xFF)                                 \
    X(KJ_RGBA_HOT_PINK, 0xFF, 0x69, 0xB4, 0xFF)                                 \
    X(KJ_RGBA_INDIAN_RED, 0xCD, 0x5C, 0x5C, 0xFF)                               \
    X(KJ_RGBA_INDIGO, 0x4B, 0x00, 0x82, 0xFF)                                   \
    X(KJ_RGBA_IVORY, 0xFF, 0xFF, 0xF0, 0xFF)                                    \
    X(KJ_RGBA_KHAKI, 0xF0, 0xE6, 0x8C, 0xFF)                                    \
    X(KJ_RGBA_LAVENDER, 0xE6, 0xE6, 0xFA, 0xFF)                                 \
    X(KJ_RGBA_LAVENDER_BLUSH, 0xFF, 0xF0, 0xF5, 0xFF)                           \
    X(KJ_RGBA_LAWN_GREEN, 0x7C, 0xFC, 0x00, 0xFF)                               \
    X(KJ_RGBA_LEMON_CHIFFON, 0xFF, 0xFA, 0xCD, 0xFF)                            \
    X(KJ_RGBA_LIGHT_BLUE, 0xAD, 0xD8, 0xE6, 0xFF)                               \
    X(KJ_RGBA_LIGHT_CORAL, 0xF0, 0x80, 0x80, 0xFF)                              \
    X(KJ_RGBA_LIGHT_CYAN, 0xE0, 0xFF, 0xFF, 0xFF)                               \
    X(KJ_RGBA_LIGHT_GOLDENROD, 0xFA, 0xFA, 0xD2, 0xFF)                          \
    X(KJ_RGBA_LIGHT_GRAY, 0xD3, 0xD3, 0xD3, 0xFF)                               \
    X(KJ_RGBA_LIGHT_GREEN, 0x90, 0xEE, 0x90, 0xFF)                              \
    X(KJ_RGBA_LIGHT_PINK, 0xFF, 0xB6, 0xC1, 0xFF)                               \
    X(KJ_RGBA_LIGHT_SALMON, 0xFF, 0xA0, 0x7A, 0xFF)                             \
    X(KJ_RGBA_LIGHT_SEA_GREEN, 0X20, 0XB2, 0XAA, 0XFF)                          \
    X(KJ_RGBA_LIGHT_SKY_BLUE, 0X87, 0XCE, 0XFA, 0XFF)                           \
    X(KJ_RGBA_LIGHT_SLATE_GRAY, 0X77, 0X88, 0X99, 0XFF)                         \
    X(KJ_RGBA_LIGHT_STEEL_BLUE, 0XB0, 0XC4, 0XDE, 0XFF)                         \
    X(KJ_RGBA_LIGHT_YELLOW, 0xFF, 0xFF, 0xE0, 0xFF)                             \
    X(KJ_RGBA_LIME, 0x00, 0xFF, 0x00, 0xFF)                                     \
    X(KJ_RGBA_LIME_GREEN, 0x32, 0xCD, 0x32, 0xFF)                               \
    X(KJ_RGBA_LINEN, 0xFA, 0xF0, 0xE6, 0xFF)                                    \
    X(KJ_RGBA_MAGENTA, 0xFF, 0x00, 0xFF, 0xFF)                                  \
    X(KJ_RGBA_MAROON, 0xB0, 0x30, 0x60, 0xFF)                                   \
    X(KJ_RGBA_MEDIUM_AQUAMARINE, 0x66, 0xCD, 0xAA, 0xFF)                        \
    X(KJ_RGBA_MEDIUM_BLUE, 0x00, 0x00, 0xCD, 0xFF)                              \
    X(KJ_RGBA_MEDIUM_ORCHID, 0xBA, 0x55, 0xD3, 0xFF)                            \
    X(KJ_RGBA_MEDIUM_PURPLE, 0x93, 0x70, 0xDB, 0xFF)                            \
    X(KJ_RGBA_MEDIUM_SEA_GREEN, 0x3C, 0xB3, 0x71, 0xFF)                         \
    X(KJ_RGBA_MEDIUM_SLATE_BLUE, 0x7B, 0x68, 0xEE, 0xFF)                        \
    X(KJ_RGBA_MEDIUM_SPRING_GREEN, 0x00, 0xFA, 0x9A, 0xFF)                      \
    X(KJ_RGBA_MEDIUM_TURQUOISE, 0x48, 0xD1, 0xCC, 0xFF)                         \
    X(KJ_RGBA_MEDIUM_VIOLET_RED, 0xC7, 0x15, 0x85, 0xFF)                        \
    X(KJ_RGBA_MIDNIGHT_BLUE, 0x19, 0x19, 0x70, 0xFF)                            \
    X(KJ_RGBA_MINT_CREAM, 0xF5, 0xFF, 0xFA, 0xFF)                               \
    X(KJ_RGBA_MISTY_ROSE, 0xFF, 0xE4, 0xE1, 0xFF)                               \
    X(KJ_RGBA_MOCCASIN, 0xFF, 0xE4, 0xB5, 0xFF)                                 \
    X(KJ_RGBA_NAVAJO_WHITE, 0xFF, 0xDE, 0xAD, 0xFF)                             \
    X(KJ_RGBA_NAVY_BLUE, 0x00, 0x00, 0x80, 0xFF)                                \
    X(KJ_RGBA_OLD_LACE, 0xFD, 0xF5, 0xE6, 0xFF)                                 \
    X(KJ_RGBA_OLIVE, 0x80, 0x80, 0x00, 0xFF)                                    \
    X(KJ_RGBA_OLIVE_DRAB, 0x6B, 0x8E, 0x23, 0xFF)                               \
    X(KJ_RGBA_ORANGE, 0xFF, 0xA5, 0x00, 0xFF)                                   \
    X(KJ_RGBA_ORANGE_RED, 0xFF, 0x45, 0x00, 0xFF)                               \
    X(KJ_RGBA_ORCHID, 0xDA, 0x70, 0xD6, 0xFF)                                   \
    X(KJ_RGBA_PALE_GOLDENROD, 0xEE, 0xE8, 0xAA, 0xFF)                           \
    X(KJ_RGBA_PALE_GREEN, 0x98, 0xFB, 0x98, 0xFF)                               \
    X(KJ_RGBA_PALE_TURQUOISE, 0xAF, 0xEE, 0xEE, 0xFF)                           \
    X(KJ_RGBA_PALE_VIOLET_RED, 0xDB, 0x70, 0x93, 0xFF)                          \
    X(KJ_RGBA_PAPAYA_WHIP, 0xFF, 0xEF, 0xD5, 0xFF)                              \
    X(KJ_RGBA_PEACH_PUFF, 0xFF, 0xDA, 0xB9, 0xFF)                               \
    X(KJ_RGBA_PERU, 0xCD, 0x85, 0x3F, 0xFF)                                     \
    X(KJ_RGBA_PINK, 0xFF, 0xC0, 0xCB, 0xFF)                                     \
    X(KJ_RGBA_PLUM, 0xDD, 0xA0, 0xDD, 0xFF)                                     \
    X(KJ_RGBA_POWDER_BLUE, 0xB0, 0xE0, 0xE6, 0xFF)                              \
    X(KJ_RGBA_PURPLE, 0xA0, 0x20, 0xF0, 0xFF)                                   \
    X(KJ_RGBA_REBECCA_PURPLE, 0x66, 0x33, 0x99, 0xFF)                           \
    X(KJ_RGBA_RED, 0xFF, 0x00, 0x00, 0xFF)                                      \
    X(KJ_RGBA_ROSY_BROWN, 0xBC, 0x8F, 0x8F, 0xFF)                               \
    X(KJ_RGBA_ROYAL_BLUE, 0x41, 0x69, 0xE1, 0xFF)                               \
    X(KJ_RGBA_SADDLE_BROWN, 0x8B, 0x45, 0x13, 0xFF)                             \
    X(KJ_RGBA_SALMON, 0xFA, 0x80, 0x72, 0xFF)                                   \
    X(KJ_RGBA_SANDY_BROWN, 0xF4, 0xA4, 0x60, 0xFF)                              \
    X(KJ_RGBA_SEASHELL, 0xFF, 0xF5, 0xEE, 0xFF)                                 \
    X(KJ_RGBA_SEA_GREEN, 0x2E, 0x8B, 0x57, 0xFF)                                \
    X(KJ_RGBA_SIENNA, 0xA0, 0x52, 0x2D, 0xFF)                                   \
    X(KJ_RGBA_SILVER, 0xC0, 0xC0, 0xC0, 0xFF)                                   \
    X(KJ_RGBA_SKY_BLUE, 0x87, 0xCE, 0xEB, 0xFF)                                 \
    X(KJ_RGBA_SLATE_BLUE, 0x6A, 0x5A, 0xCD, 0xFF)                               \
    X(KJ_RGBA_SLATE_GRAY, 0x70, 0x80, 0x90, 0xFF)                               \
    X(KJ_RGBA_SNOW, 0xFF, 0xFA, 0xFA, 0xFF)                                     \
    X(KJ_RGBA_SPRING_GREEN, 0x00, 0xFF, 0x7F, 0xFF)                             \
    X(KJ_RGBA_STEEL_BLUE, 0x46, 0x82, 0xB4, 0xFF)                               \
    X(KJ_RGBA_TAN, 0xD2, 0xB4, 0x8C, 0xFF)                                      \
    X(KJ_RGBA_TEAL, 0x00, 0x80, 0x80, 0xFF)                                     \
    X(KJ_RGBA_THISTLE, 0xD8, 0xBF, 0xD8, 0xFF)                                  \
    X(KJ_RGBA_TOMATO, 0xFF, 0x63, 0x47, 0xFF)                                   \
    X(KJ_RGBA_TURQUOISE, 0x40, 0xE0, 0xD0, 0xFF)                                \
    X(KJ_RGBA_VIOLET, 0xEE, 0x82, 0xEE, 0xFF)                                   \
    X(KJ_RGBA_WEB_GRAY, 0x80, 0x80, 0x80, 0xFF)                                 \
    X(KJ_RGBA_WEB_GREEN, 0x00, 0x80, 0x00, 0xFF)                                \
    X(KJ_RGBA_WEB_MAROON, 0x7F, 0x00, 0x00, 0xFF)                               \
    X(KJ_RGBA_WEB_PURPLE, 0x7F, 0x00, 0x7F, 0xFF)                               \
    X(KJ_RGBA_WHEAT, 0xF5, 0xDE, 0xB3, 0xFF)                                    \
    X(KJ_RGBA_WHITE, 0xFF, 0xFF, 0xFF, 0xFF)                                    \
    X(KJ_RGBA_WHITE_SMOKE, 0xF5, 0xF5, 0xF5, 0xFF)                              \
    X(KJ_RGBA_YELLOW, 0xFF, 0xFF, 0x00, 0xFF)                                   \
    X(KJ_RGBA_YELLOW_GREEN, 0x9A, 0xCD, 0x32, 0xFF)

#define KJ_RGBA_CONST(c, r, g, b, a)                                            \
        KJ_GLOBAL const kjRgba c = {                                            \
            r, g, b, a                                                          \
        };                                                                      \
    KJ_RGBA_COLOUR_MAP(KJ_RGBA_CONST)
#undef KJ_RGBA_CONST

#define KJ_RGBAF_CONST(c, r, g, b, a)                                           \
        KJ_GLOBAL const kjVec4f c = {                                           \
            r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f                      \
        };                                                                      \
    KJ_RGBA_COLOUR_MAP(KJ_RGBAF_CONST)
#undef KJ_RGBAF_CONST

KJ_COMPILER_WARNING_END

KJ_EXTERN_BEGIN

KJ_API f32 kj_rsqrtf(f32 a);
KJ_API f32 kj_sqrtf(f32 a);
KJ_API f32 kj_sinf(f32 radians);
KJ_API f32 kj_cosf(f32 radians);
KJ_API f32 kj_tanf(f32 radians);
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
KJ_API kjMat3f kj_mat3f_rotate(f32 angle, f32 x, f32 y, f32 z);
KJ_API kjMat3f kj_mat3f_rotate_vec3f(f32 angle, kjVec3f xyz);
KJ_API kjMat3f kj_mat3f_scale(f32 x, f32 y, f32 z);
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
KJ_API kjMat4f kj_mat4f_scale(f32 x, f32 y, f32 z);
KJ_API kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_ortho(f32 l, f32 r, f32 b, f32 t, f32 znear, f32 zfar);
KJ_API kjMat4f kj_mat4f_ortho_inf(f32 l, f32 r, f32 t, f32 b);
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

KJ_EXTERN_END

#if defined(__cplusplus)
KJ_API kjMat3f kj_mat3f(f32 e00, f32 e11, f32 e22);
KJ_API kjMat3f kj_mat3f(void);
KJ_API kjMat3f kj_mat3f_rotate(f32 angle, kjVec3f xyz);
KJ_API kjMat3f kj_mat3f_scale(f32 angle, kjVec3f xyz);

KJ_API kjMat4f kj_mat4f(f32 e00, f32 e11, f32 e22, f32 e33);
KJ_API kjMat4f kj_mat4f(void);
KJ_API kjMat4f kj_mat4f_translate(kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_rotate(f32 angle, kjVec3f xyz);
KJ_API kjMat4f kj_mat4f_scale(kjVec3f xyz);
#endif

#endif

#if defined(KJ_MATH_IMPL)

#if defined(KJ_COMPILER_GNU) || defined(KJ_COMPILER_CLANG)
KJ_CONST f32 kj_rsqrtf(f32 a) { return 1.0f / __builtin_sqrtf(a); }
KJ_CONST f32 kj_sqrtf(f32 a) { return __builtin_sqrtf(a); }
KJ_CONST f32 kj_sinf(f32 a) { return __builtin_sinf(a); }
KJ_CONST f32 kj_cosf(f32 a) { return __builtin_cosf(a); }
KJ_CONST f32 kj_tanf(f32 a) { return __builtin_tanf(a); }
KJ_CONST f32 kj_asinf(f32 a) { return __builtin_asinf(a); }
KJ_CONST f32 kj_acosf(f32 a) { return __builtin_acosf(a); }
KJ_CONST f32 kj_atanf(f32 a) { return __builtin_atanf(a); }
KJ_CONST f32 kj_atan2f(f32 y, f32 x) { return __builtin_atan2f(y, x); }
KJ_CONST f32 kj_expf(f32 a) { return __builtin_expf(a); }
KJ_CONST f32 kj_lnf(f32 a) { return __builtin_logf(a); }
KJ_CONST f32 kj_log10f(f32 a) { return __builtin_log10f(a); }
KJ_CONST f32 kj_log2f(f32 a) { return __builtin_log2f(a); }
KJ_CONST f32 kj_powf(f32 x, f32 y) { return __builtin_powf(x, y); }
KJ_CONST f32 kj_floorf(f32 a) { return __builtin_floorf(a); }
KJ_CONST f32 kj_ceilf(f32 a) { return __builtin_ceilf(a); }
KJ_CONST f32 kj_maxf(f32 x, f32 y) { return __builtin_fmaxf(x, y); }
#elif defined(KJ_COMPILER_MSVC)
#include <math.h>
KJ_CONST f32 kj_rsqrtf(f32 a) { return 1.0f / sqrtf(a); }
KJ_CONST f32 kj_sqrtf(f32 a) { return sqrtf(a); }
KJ_CONST f32 kj_sinf(f32 radians) { return sinf(radians); }
KJ_CONST f32 kj_cosf(f32 radians) { return cosf(radians); }
KJ_CONST f32 kj_tanf(f32 radians) { return tanf(radians); }
KJ_CONST f32 kj_asinf(f32 a) { return asinf(a); }
KJ_CONST f32 kj_acosf(f32 a) { return acosf(a); }
KJ_CONST f32 kj_atanf(f32 a) { return atanf(a); }
KJ_CONST f32 kj_atan2f(f32 y, f32 x) { return atan2f(y, x); }
KJ_CONST f32 kj_expf(f32 a) { return expf(a); }
KJ_CONST f32 kj_lnf(f32 a) { return logf(a); }
KJ_CONST f32 kj_log10f(f32 a) { return log10f(a); }
KJ_CONST f32 kj_log2f(f32 a) { return log2f(a); }
KJ_CONST f32 kj_powf(f32 x, f32 y) { return powf(x, y); }
KJ_CONST f32 kj_floorf(f32 a) { return floorf(a); }
KJ_CONST f32 kj_ceilf(f32 a) { return ceilf(a); }
KJ_CONST f32 kj_maxf(f32 x, f32 y) { return fmaxf(x, y); }
#else
#error KJ_MATH_UNSUPPORTED
#endif

KJ_CONST kjVec2f kj_vec2f(f32 x, f32 y) {
    kjVec2f res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_CONST kjVec2i kj_vec2i(i32 x, i32 y) {
    kjVec2i res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_CONST kjVec2u kj_vec2u(u32 x, u32 y) {
    kjVec2u res;
    res.x = x;
    res.y = y;
    return res;
}

KJ_CONST kjVec2f kj_vec2f_zero(void) {
    return kj_vec2f(0.0f, 0.0f);
}

KJ_CONST kjVec2i kj_vec2i_zero(void) {
    return kj_vec2i(0, 0);
}

KJ_CONST kjVec2u kj_vec2u_zero(void) {
    return kj_vec2u(0, 0);
}

KJ_CONST kjVec2f kj_vec2f_one(void) {
    return kj_vec2f(1.0f, 1.0f);
}

KJ_CONST kjVec2i kj_vec2i_one(void) {
    return kj_vec2i(1, 1);
}

KJ_CONST kjVec2u kj_vec2u_one(void) {
    return kj_vec2u(1, 1);
}

KJ_CONST kjVec2f kj_vec2f_all(f32 a) {
    return kj_vec2f(a, a);
}

KJ_CONST kjVec2i kj_vec2i_all(i32 a) {
    return kj_vec2i(a, a);
}

KJ_CONST kjVec2u kj_vec2u_all(u32 a) {
    return kj_vec2u(a, a);
}

KJ_CONST kjVec2f kj_vec2f_negate(kjVec2f a) {
    return kj_vec2f(-a.x, -a.y);
}

KJ_CONST kjVec2i kj_vec2i_negate(kjVec2i a) {
    return kj_vec2i(-a.x, -a.y);
}

KJ_CONST kjVec2u kj_vec2u_negate(kjVec2u a) {
    return kj_vec2u(-kj_cast(i32, a.x), -kj_cast(i32, a.y));
}

KJ_CONST kjVec2f kj_vec2f_add(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x + b.x, a.y + b.y);
}

KJ_CONST kjVec2i kj_vec2i_add(kjVec2i a, kjVec2i b) {
    return kj_vec2i(a.x + b.x, a.y + b.y);
}

KJ_CONST kjVec2u kj_vec2u_add(kjVec2u a, kjVec2u b) {
    return kj_vec2u(a.x + b.x, a.y + b.y);
}

KJ_CONST kjVec2f kj_vec2f_sub(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x - b.x, a.y - b.y);
}

KJ_CONST kjVec2i kj_vec2i_sub(kjVec2i a, kjVec2i b) {
    return kj_vec2i(a.x - b.x, a.y - b.y);
}

KJ_CONST kjVec2u kj_vec2u_sub(kjVec2u a, kjVec2u b) {
    return kj_vec2u(a.x - b.x, a.y - b.y);
}

KJ_CONST kjVec2f kj_vec2f_mul(kjVec2f a, kjVec2f b) {
    return kj_vec2f(a.x * b.x, a.y * b.y);
}

KJ_CONST kjVec2i kj_vec2i_mul(kjVec2i a, kjVec2i b) {
    return kj_vec2i(a.x * b.x, a.y * b.y);
}

KJ_CONST kjVec2u kj_vec2u_mul(kjVec2u a, kjVec2u b) {
    return kj_vec2u(a.x * b.x, a.y * b.y);
}

KJ_CONST kjVec2f kj_vec2f_mulf(kjVec2f a, f32 b) {
    return kj_vec2f(a.x * b, a.y * b);
}

KJ_CONST kjVec2i kj_vec2i_muli(kjVec2i a, i32 b) {
    return kj_vec2i(a.x * b, a.y * b);
}

KJ_CONST kjVec2u kj_vec2u_mulu(kjVec2u a, u32 b) {
    return kj_vec2u(a.x * b, a.y * b);
}

KJ_CONST kjVec2f kj_vec2f_div(kjVec2f a, kjVec2f b) {
    return kj_vec2f(
            a.x / (b.x + KJ_F32_EPS),
            a.y / (b.y + KJ_F32_EPS));
}

KJ_CONST kjVec2i kj_vec2i_div(kjVec2i a, kjVec2i b) {
    return kj_vec2i(a.x / b.x, a.y / b.y);
}

KJ_CONST kjVec2u kj_vec2u_div(kjVec2u a, kjVec2u b) {
    return kj_vec2u(a.x / b.x, a.y / b.y);
}

KJ_CONST f32 kj_vec2f_dot(kjVec2f a, kjVec2f b) {
    return (a.x * b.x + a.y * b.y);
}

KJ_CONST i32 kj_vec2i_dot(kjVec2i a, kjVec2i b) {
    return (a.x * b.x + a.y * b.y);
}

KJ_CONST u32 kj_vec2u_dot(kjVec2u a, kjVec2u b) {
    return (a.x * b.x + a.y * b.y);
}

KJ_CONST f32 kj_vec2f_cross(kjVec2f a, kjVec2f b) {
    return (a.x * b.y - b.x * a.y);
}

KJ_CONST i32 kj_vec2i_cross(kjVec2i a, kjVec2i b) {
    return (a.x * b.y - b.x * a.y);
}

KJ_CONST u32 kj_vec2u_cross(kjVec2u a, kjVec2u b) {
    return (a.x * b.y - b.x * a.y);
}

KJ_CONST f32 kj_vec2f_length_sq(kjVec2f a) {
    return kj_vec2f_dot(a, a);
}

KJ_CONST i32 kj_vec2i_length_sq(kjVec2i a) {
    return kj_vec2i_dot(a, a);
}

KJ_CONST u32 kj_vec2u_length_sq(kjVec2u a) {
    return kj_vec2u_dot(a, a);
}

KJ_CONST f32 kj_vec2f_length(kjVec2f a) {
    return kj_sqrtf(kj_vec2f_length_sq(a));
}

KJ_CONST i32 kj_vec2i_length(kjVec2i a) {
    return kj_cast(i32, kj_sqrtf(kj_cast(f32, kj_vec2i_length_sq(a))));
}

KJ_CONST u32 kj_vec2u_length(kjVec2u a) {
    return kj_cast(u32, kj_sqrtf(kj_cast(f32, kj_vec2u_length_sq(a))));
}

KJ_CONST kjVec2f kj_vec2f_normalise(kjVec2f a) {
    return kj_vec2f_div(a, kj_vec2f_all(kj_vec2f_length(a)));
}

KJ_CONST kjVec2i kj_vec2i_normalise(kjVec2i a) {
    return kj_vec2i_div(a, kj_vec2i_all(kj_vec2i_length(a)));
}

KJ_CONST kjVec2u kj_vec2u_normalise(kjVec2u a) {
    return kj_vec2u_div(a, kj_vec2u_all(kj_vec2u_length(a)));
}

KJ_CONST kjVec2f kj_vec2f_clamp(kjVec2f a, kjVec2f min, kjVec2f max) {
    return kj_vec2f(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y));
}

KJ_CONST kjVec2i kj_vec2i_clamp(kjVec2i a, kjVec2i min, kjVec2i max) {
    return kj_vec2i(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y));
}

KJ_CONST kjVec2u kj_vec2u_clamp(kjVec2u a, kjVec2u min, kjVec2u max) {
    return kj_vec2u(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y));
}

KJ_CONST kjVec2f kj_vec2f_clampf(kjVec2f a, f32 min, f32 max) {
    return kj_vec2f_clamp(a, kj_vec2f_all(min), kj_vec2f_all(max));
}

KJ_CONST kjVec2i kj_vec2i_clampi(kjVec2i a, i32 min, i32 max) {
    return kj_vec2i_clamp(a, kj_vec2i_all(min), kj_vec2i_all(max));
}

KJ_CONST kjVec2u kj_vec2u_clampu(kjVec2u a, u32 min, u32 max) {
    return kj_vec2u_clamp(a, kj_vec2u_all(min), kj_vec2u_all(max));
}

KJ_CONST kjVec3f kj_vec3f(f32 x, f32 y, f32 z) {
    kjVec3f res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_CONST kjVec3i kj_vec3i(i32 x, i32 y, i32 z) {
    kjVec3i res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_CONST kjVec3u kj_vec3u(u32 x, u32 y, u32 z) {
    kjVec3u res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

KJ_CONST kjVec3f kj_vec3f_zero(void) {
    return kj_vec3f(0.0f, 0.0f, 0.0f);
}

KJ_CONST kjVec3i kj_vec3i_zero(void) {
    return kj_vec3i(0, 0, 0);
}

KJ_CONST kjVec3u kj_vec3u_zero(void) {
    return kj_vec3u(0, 0, 0);
}

KJ_CONST kjVec3f kj_vec3f_one(void) {
    return kj_vec3f(1.0f, 1.0f, 1.0f);
}

KJ_CONST kjVec3i kj_vec3i_one(void) {
    return kj_vec3i(1, 1, 1);
}

KJ_CONST kjVec3u kj_vec3u_one(void) {
    return kj_vec3u(1, 1, 1);
}

KJ_CONST kjVec3f kj_vec3f_all(f32 a) {
    return kj_vec3f(a, a, a);
}

KJ_CONST kjVec3i kj_vec3i_all(i32 a) {
    return kj_vec3i(a, a, a);
}

KJ_CONST kjVec3u kj_vec3u_all(u32 a) {
    return kj_vec3u(a, a, a);
}

KJ_CONST kjVec3f kj_vec3f_negate(kjVec3f a) {
    return kj_vec3f(-a.x, -a.y, -a.z);
}

KJ_CONST kjVec3i kj_vec3i_negate(kjVec3i a) {
    return kj_vec3i(-a.x, -a.y, -a.z);
}

KJ_CONST kjVec3u kj_vec3u_negate(kjVec3u a) {
    return kj_vec3u(
            -kj_cast(i32, a.x),
            -kj_cast(i32, a.y),
            -kj_cast(i32, a.z));
}

KJ_CONST kjVec3f kj_vec3f_add(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

KJ_CONST kjVec3i kj_vec3i_add(kjVec3i a, kjVec3i b) {
    return kj_vec3i(a.x + b.x, a.y + b.y, a.z + b.z);
}

KJ_CONST kjVec3u kj_vec3u_add(kjVec3u a, kjVec3u b) {
    return kj_vec3u(a.x + b.x, a.y + b.y, a.z + b.z);
}

KJ_CONST kjVec3f kj_vec3f_sub(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

KJ_CONST kjVec3i kj_vec3i_sub(kjVec3i a, kjVec3i b) {
    return kj_vec3i(a.x - b.x, a.y - b.y, a.z - b.z);
}

KJ_CONST kjVec3u kj_vec3u_sub(kjVec3u a, kjVec3u b) {
    return kj_vec3u(a.x - b.x, a.y - b.y, a.z - b.z);
}

KJ_CONST kjVec3f kj_vec3f_mul(kjVec3f a, kjVec3f b) {
    return kj_vec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

KJ_CONST kjVec3i kj_vec3i_mul(kjVec3i a, kjVec3i b) {
    return kj_vec3i(a.x * b.x, a.y * b.y, a.z * b.z);
}

KJ_CONST kjVec3u kj_vec3u_mul(kjVec3u a, kjVec3u b) {
    return kj_vec3u(a.x * b.x, a.y * b.y, a.z * b.z);
}

KJ_CONST kjVec3f kj_vec3f_mulf(kjVec3f a, f32 b) {
    return kj_vec3f(a.x * b, a.y * b, a.z * b);
}

KJ_CONST kjVec3i kj_vec3i_muli(kjVec3i a, i32 b) {
    return kj_vec3i(a.x * b, a.y * b, a.z * b);
}

KJ_CONST kjVec3u kj_vec3u_mulu(kjVec3u a, u32 b) {
    return kj_vec3u(a.x * b, a.y * b, a.z * b);
}

KJ_CONST kjVec3f kj_vec3f_div(kjVec3f a, kjVec3f b) {
    return kj_vec3f(
            a.x / (b.x + KJ_F32_EPS),
            a.y / (b.y + KJ_F32_EPS),
            a.z / (b.z + KJ_F32_EPS));
}

KJ_CONST kjVec3i kj_vec3i_div(kjVec3i a, kjVec3i b) {
    return kj_vec3i(a.x / b.x, a.y / b.y, a.z / b.z);
}

KJ_CONST kjVec3u kj_vec3u_div(kjVec3u a, kjVec3u b) {
    return kj_vec3u(a.x / b.x, a.y / b.y, a.z / b.z);
}

KJ_CONST f32 kj_vec3f_dot(kjVec3f a, kjVec3f b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

KJ_CONST i32 kj_vec3i_dot(kjVec3i a, kjVec3i b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

KJ_CONST u32 kj_vec3u_dot(kjVec3u a, kjVec3u b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

KJ_CONST kjVec3f kj_vec3f_cross(kjVec3f a, kjVec3f b) {
    return kj_vec3f(
            a.y * b.z - b.y * a.z,
            a.z * b.x - b.z * a.x,
            a.x * b.y - b.x * a.y);
}

KJ_CONST kjVec3i kj_vec3i_cross(kjVec3i a, kjVec3i b) {
    return kj_vec3i(
            a.y * b.z - b.y * a.z,
            a.z * b.x - b.z * a.x,
            a.x * b.y - b.x * a.y);
}

KJ_CONST kjVec3u kj_vec3u_cross(kjVec3u a, kjVec3u b) {
    return kj_vec3u(
            a.y * b.z - b.y * a.z,
            a.z * b.x - b.z * a.x,
            a.x * b.y - b.x * a.y);
}

KJ_CONST f32 kj_vec3f_length_sq(kjVec3f a) {
    return kj_vec3f_dot(a, a);
}

KJ_CONST i32 kj_vec3i_length_sq(kjVec3i a) {
    return kj_vec3i_dot(a, a);
}

KJ_CONST u32 kj_vec3u_length_sq(kjVec3u a) {
    return kj_vec3u_dot(a, a);
}

KJ_CONST f32 kj_vec3f_length(kjVec3f a) {
    return kj_sqrtf(kj_vec3f_length_sq(a));
}

KJ_CONST i32 kj_vec3i_length(kjVec3i a) {
    return kj_cast(i32, kj_sqrtf(kj_cast(f32, kj_vec3i_length_sq(a))));
}

KJ_CONST u32 kj_vec3u_length(kjVec3u a) {
    return kj_cast(u32, kj_sqrtf(kj_cast(f32, kj_vec3u_length_sq(a))));
}

KJ_CONST kjVec3f kj_vec3f_normalise(kjVec3f a) {
    return kj_vec3f_div(a, kj_vec3f_all(kj_vec3f_length(a)));
}

KJ_CONST kjVec3i kj_vec3i_normalise(kjVec3i a) {
    return kj_vec3i_div(a, kj_vec3i_all(kj_vec3i_length(a)));
}

KJ_CONST kjVec3u kj_vec3u_normalise(kjVec3u a) {
    return kj_vec3u_div(a, kj_vec3u_all(kj_vec3u_length(a)));
}

KJ_CONST kjVec3f kj_vec3f_clamp(kjVec3f a, kjVec3f b, kjVec3f c) {
    return kj_vec3f(
            kj_clamp(a.x, b.x, c.x),
            kj_clamp(a.y, b.y, c.y),
            kj_clamp(a.z, b.z, c.z));
}

KJ_CONST kjVec3i kj_vec3i_clamp(kjVec3i a, kjVec3i b, kjVec3i c) {
    return kj_vec3i(
            kj_clamp(a.x, b.x, c.x),
            kj_clamp(a.y, b.y, c.y),
            kj_clamp(a.z, b.z, c.z));
}

KJ_CONST kjVec3u kj_vec3u_clamp(kjVec3u a, kjVec3u b, kjVec3u c) {
    return kj_vec3u(
            kj_clamp(a.x, b.x, c.x),
            kj_clamp(a.y, b.y, c.y),
            kj_clamp(a.z, b.z, c.z));
}

KJ_CONST kjVec3f kj_vec3f_clampf(kjVec3f a, f32 min, f32 max) {
    return kj_vec3f_clamp(a, kj_vec3f_all(min), kj_vec3f_all(max));
}

KJ_CONST kjVec3i kj_vec3i_clampi(kjVec3i a, i32 min, i32 max) {
    return kj_vec3i_clamp(a, kj_vec3i_all(min), kj_vec3i_all(max));
}

KJ_CONST kjVec3u kj_vec3u_clampu(kjVec3u a, u32 min, u32 max) {
    return kj_vec3u_clamp(a, kj_vec3u_all(min), kj_vec3u_all(max));
}

KJ_CONST kjVec4f kj_vec4f(f32 x, f32 y, f32 z, f32 w) {
    kjVec4f res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_CONST kjVec4i kj_vec4i(i32 x, i32 y, i32 z, i32 w) {
    kjVec4i res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_CONST kjVec4u kj_vec4u(u32 x, u32 y, u32 z, u32 w) {
    kjVec4u res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

KJ_CONST kjVec4f kj_vec4f_zero(void) {
    return kj_vec4f(0.0f, 0.0f, 0.0f, 0.0f);
}

KJ_CONST kjVec4i kj_vec4i_zero(void) {
    return kj_vec4i(0, 0, 0, 0);
}

KJ_CONST kjVec4u kj_vec4u_zero(void) {
    return kj_vec4u(0, 0, 0, 0);
}

KJ_CONST kjVec4f kj_vec4f_one(void) {
    return kj_vec4f(1.0f, 1.0f, 1.0f, 1.0f);
}

KJ_CONST kjVec4i kj_vec4i_one(void) {
    return kj_vec4i(1, 1, 1, 1);
}

KJ_CONST kjVec4u kj_vec4u_one(void) {
    return kj_vec4u(1, 1, 1, 1);
}

KJ_CONST kjVec4f kj_vec4f_all(f32 a) {
    return kj_vec4f(a, a, a, a);
}

KJ_CONST kjVec4i kj_vec4i_all(i32 a) {
    return kj_vec4i(a, a, a, a);
}

KJ_CONST kjVec4u kj_vec4u_all(u32 a) {
    return kj_vec4u(a, a, a, a);
}

KJ_CONST kjVec4f kj_vec4f_negate(kjVec4f a) {
    return kj_vec4f(-a.x, -a.y, -a.z, -a.w);
}

KJ_CONST kjVec4i kj_vec4i_negate(kjVec4i a) {
    return kj_vec4i(-a.x, -a.y, -a.z, -a.w);
}

KJ_CONST kjVec4u kj_vec4u_negate(kjVec4u a) {
    return kj_vec4u(
            -kj_cast(i32, a.x), -kj_cast(i32, a.y),
            -kj_cast(i32, a.z), -kj_cast(i32, a.w));
}

KJ_CONST kjVec4f kj_vec4f_add(kjVec4f a, kjVec4f b) {
    return kj_vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

KJ_CONST kjVec4i kj_vec4i_add(kjVec4i a, kjVec4i b) {
    return kj_vec4i(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

KJ_CONST kjVec4u kj_vec4u_add(kjVec4u a, kjVec4u b) {
    return kj_vec4u(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

KJ_CONST kjVec4f kj_vec4f_sub(kjVec4f a, kjVec4f b) {
    return kj_vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

KJ_CONST kjVec4i kj_vec4i_sub(kjVec4i a, kjVec4i b) {
    return kj_vec4i(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

KJ_CONST kjVec4u kj_vec4u_sub(kjVec4u a, kjVec4u b) {
    return kj_vec4u(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

KJ_CONST kjVec4f kj_vec4f_mul(kjVec4f a, kjVec4f b) {
    return kj_vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

KJ_CONST kjVec4i kj_vec4i_mul(kjVec4i a, kjVec4i b) {
    return kj_vec4i(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

KJ_CONST kjVec4u kj_vec4u_mul(kjVec4u a, kjVec4u b) {
    return kj_vec4u(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

KJ_CONST kjVec4f kj_vec4f_mulf(kjVec4f a, f32 b) {
    return kj_vec4f(a.x * b, a.y * b, a.z * b, a.w * b);
}

KJ_CONST kjVec4i kj_vec4i_muli(kjVec4i a, i32 b) {
    return kj_vec4i(a.x * b, a.y * b, a.z * b, a.w * b);
}

KJ_CONST kjVec4u kj_vec4u_mulu(kjVec4u a, u32 b) {
    return kj_vec4u(a.x * b, a.y * b, a.z * b, a.w * b);
}

KJ_CONST kjVec4f kj_vec4f_div(kjVec4f a, kjVec4f b) {
    return kj_vec4f(
            a.x / (b.x + KJ_F32_EPS),
            a.y / (b.y + KJ_F32_EPS),
            a.z / (b.z + KJ_F32_EPS),
            a.w / (b.w + KJ_F32_EPS));
}

KJ_CONST kjVec4i kj_vec4i_div(kjVec4i a, kjVec4i b) {
    return kj_vec4i(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

KJ_CONST kjVec4u kj_vec4u_div(kjVec4u a, kjVec4u b) {
    return kj_vec4u(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

KJ_CONST f32 kj_vec4f_dot(kjVec4f a, kjVec4f b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

KJ_CONST i32 kj_vec4i_dot(kjVec4i a, kjVec4i b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

KJ_CONST u32 kj_vec4u_dot(kjVec4u a, kjVec4u b) {
  return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

KJ_CONST f32 kj_vec4f_length_sq(kjVec4f a) {
    return kj_vec4f_dot(a, a);
}

KJ_CONST i32 kj_vec4i_length_sq(kjVec4i a) {
    return kj_vec4i_dot(a, a);
}

KJ_CONST u32 kj_vec4u_length_sq(kjVec4u a) {
    return kj_vec4u_dot(a, a);
}

KJ_CONST f32 kj_vec4f_length(kjVec4f a) {
    return kj_sqrtf(kj_vec4f_length_sq(a));
}

KJ_CONST i32 kj_vec4i_length(kjVec4i a) {
    return kj_cast(i32, kj_sqrtf(kj_cast(f32, kj_vec4i_length_sq(a))));
}

KJ_CONST u32 kj_vec4u_length(kjVec4u a) {
    return kj_cast(u32, kj_sqrtf(kj_cast(f32, kj_vec4u_length_sq(a))));
}

KJ_CONST kjVec4f kj_vec4f_normalise(kjVec4f a) {
    return kj_vec4f_div(a, kj_vec4f_all(kj_vec4f_length(a)));
}

KJ_CONST kjVec4i kj_vec4i_normalise(kjVec4i a) {
    return kj_vec4i_div(a, kj_vec4i_all(kj_vec4i_length(a)));
}

KJ_CONST kjVec4u kj_vec4u_normalise(kjVec4u a) {
    return kj_vec4u_div(a, kj_vec4u_all(kj_vec4u_length(a)));
}

KJ_CONST kjVec4f kj_vec4f_clamp(kjVec4f a, kjVec4f min, kjVec4f max) {
    return kj_vec4f(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y),
            kj_clamp(a.z, min.z, max.z),
            kj_clamp(a.w, min.w, max.w));
}

KJ_CONST kjVec4i kj_vec4i_clamp(kjVec4i a, kjVec4i min, kjVec4i max) {
    return kj_vec4i(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y),
            kj_clamp(a.z, min.z, max.z),
            kj_clamp(a.w, min.w, max.w));
}

KJ_CONST kjVec4u kj_vec4u_clamp(kjVec4u a, kjVec4u min, kjVec4u max) {
    return kj_vec4u(
            kj_clamp(a.x, min.x, max.x),
            kj_clamp(a.y, min.y, max.y),
            kj_clamp(a.z, min.z, max.z),
            kj_clamp(a.w, min.w, max.w));
}

KJ_CONST kjVec4f kj_vec4f_clampf(kjVec4f a, f32 min, f32 max) {
    return kj_vec4f_clamp(a, kj_vec4f_all(min), kj_vec4f_all(max));
}

KJ_CONST kjVec4i kj_vec4i_clampi(kjVec4i a, i32 min, i32 max) {
    return kj_vec4i_clamp(a, kj_vec4i_all(min), kj_vec4i_all(max));
}

KJ_CONST kjVec4u kj_vec4u_clampu(kjVec4u a, u32 min, u32 max) {
    return kj_vec4u_clamp(a, kj_vec4u_all(min), kj_vec4u_all(max));
}

KJ_CONST kjMat3f kj_mat3f(
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

KJ_CONST kjMat3f kj_mat3f_diag(f32 e00, f32 e11, f32 e22) {
    return kj_mat3f(e00, 0.0f, 0.0f, 0.0f, e11, 0.0f, 0.0f, 0.0f, e22);
}

KJ_CONST kjMat3f kj_mat3f_ident(void) {
    return kj_mat3f_diag(1.0f, 1.0f, 1.0f);
}

KJ_CONST kjMat3f kj_mat3f_zero(void) {
    kjMat3f res;
    kj_zero(&res, kj_isize_of(kjMat3f));
    return res;
}

KJ_CONST kjMat3f kj_mat3f_one(void) {
    kjMat3f res;
    kj_one(&res, kj_isize_of(kjMat3f));
    return res;
}

KJ_CONST kjMat3f kj_mat3f_mul(kjMat3f a, kjMat3f b) {
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

KJ_CONST kjMat3f kj_mat3f_transpose(kjMat3f a) {
    return kj_mat3f(
            a.e[0][0], a.e[1][0], a.e[2][0],
            a.e[0][1], a.e[1][1], a.e[2][1],
            a.e[0][2], a.e[1][2], a.e[2][2]);
}

KJ_CONST kjMat3f kj_mat3f_rotate(f32 angle, f32 x, f32 y, f32 z) {
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
    res.e[1][2] = 0.0f + rot_axis.y * axis.z + s * axis.x;
    res.e[2][0] = 0.0f + rot_axis.z * axis.x + s * axis.y;
    res.e[2][1] = 0.0f + rot_axis.z * axis.y - s * axis.x;
    res.e[2][2] = c + rot_axis.z * axis.z;
    return res;
}

KJ_CONST kjMat3f kj_mat3f_rotate_vec3f(f32 angle, kjVec3f xyz) {
    return kj_mat3f_rotate(angle, xyz.x, xyz.y, xyz.z);
}

KJ_CONST kjMat3f kj_mat3f_scale(f32 x, f32 y, f32 z) {
    return kj_mat3f_diag(x, y, z);
}

KJ_CONST kjMat3f kj_mat3f_scale_vec3f(kjVec3f xyz) {
    return kj_mat3f_scale(xyz.x, xyz.y, xyz.z);
}

KJ_CONST kjMat4f kj_mat4f(
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

KJ_CONST kjMat4f kj_mat4f_diag(f32 e00, f32 e11, f32 e22, f32 e33) {
    return kj_mat4f(
            e00, 0.0f, 0.0f, 0.0f,
            0.0f, e11, 0.0f, 0.0f,
            0.0f, 0.0f, e22, 0.0f,
            0.0f, 0.0f, 0.0f, e33);
}

KJ_CONST kjMat4f kj_mat4f_ident(void) {
    return kj_mat4f_diag(1.0f, 1.0f, 1.0f, 1.0f);
}

KJ_CONST kjMat4f kj_mat4f_zero(void) {
    kjMat4f res;
    kj_zero(&res, kj_isize_of(kjMat4f));
    return res;
}

KJ_CONST kjMat4f kj_mat4f_one(void) {
    kjMat4f res;
    kj_one(&res, kj_isize_of(kjMat4f));
    return res;
}

KJ_CONST kjMat4f kj_mat4f_mul(kjMat4f a, kjMat4f b) {
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

KJ_CONST kjVec4f kj_mat4f_mul_vec4f(kjMat4f a, kjVec4f b) {
    kjVec4f res;
    res.x =
        a.e[0][0] * b.x + a.e[1][0] * b.y +
        a.e[2][0] * b.z + a.e[3][0] * b.w;
    res.y =
        a.e[0][1] * b.x + a.e[1][1] * b.y +
        a.e[2][1] * b.z + a.e[3][1] * b.w;
    res.z =
        a.e[0][2] * b.x + a.e[1][2] * b.y +
        a.e[2][2] * b.z + a.e[3][2] * b.w;
    res.w =
        a.e[0][3] * b.x + a.e[1][3] * b.y +
        a.e[2][3] * b.z + a.e[3][3] * b.w;
    return res;
}

KJ_CONST kjMat4f kj_mat4f_transpose(kjMat4f a) {
    return kj_mat4f(
            a.e[0][0], a.e[1][0], a.e[2][0], a.e[3][0],
            a.e[0][1], a.e[1][1], a.e[2][1], a.e[3][1],
            a.e[0][2], a.e[1][2], a.e[2][2], a.e[3][2],
            a.e[0][3], a.e[1][3], a.e[2][3], a.e[3][3]);
}

KJ_CONST kjMat4f kj_mat4f_translate(f32 x, f32 y, f32 z) {
    return kj_mat4f(
            1.0f, 0.0f, 0.0f, x,
            0.0f, 1.0f, 0.0f, y,
            0.0f, 0.0f, 1.0f, z,
            0.0f, 0.0f, 0.0f, 1.0f);
}

KJ_CONST kjMat4f kj_mat4f_translate_vec3f(kjVec3f xyz) {
    return kj_mat4f_translate(xyz.x, xyz.y, xyz.z);
}

KJ_CONST kjMat4f kj_mat4f_rotate(f32 angle, f32 x, f32 y, f32 z) {
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
    res.e[1][2] = 0.0f + rot_axis.y * axis.z + s * axis.x;
    res.e[1][3] = 0.0f;
    res.e[2][0] = 0.0f + rot_axis.z * axis.x + s * axis.y;
    res.e[2][1] = 0.0f + rot_axis.z * axis.y - s * axis.x;
    res.e[2][2] = c + rot_axis.z * axis.z;
    res.e[2][3] = 0.0f;
    return res;
}

KJ_CONST kjMat4f kj_mat4f_rotate_vec3f(f32 angle, kjVec3f xyz) {
    return kj_mat4f_rotate(angle, xyz.x, xyz.y, xyz.z);
}

KJ_CONST kjMat4f kj_mat4f_scale(f32 x, f32 y, f32 z) {
    return kj_mat4f_diag(x, y, z, 1.0f);
}

KJ_CONST kjMat4f kj_mat4f_scale_vec3f(kjVec3f xyz) {
    return kj_mat4f_scale(xyz.x, xyz.y, xyz.z);
}

KJ_CONST kjMat4f kj_mat4f_ortho(
        f32 l, f32 r, f32 b, f32 t, f32 znear, f32 zfar) {
    kjMat4f res = kj_mat4f_ident();
    f32 rl = r - l + KJ_F32_EPS;
    f32 tb = t - b + KJ_F32_EPS;
    f32 fn = zfar - znear + KJ_F32_EPS;

    res.e[0][0] = 2.0f / rl;
    res.e[1][1] = 2.0f / tb;
    res.e[2][2] = -1.0f / fn;
    res.e[3][0] = -(r + l) / rl;
    res.e[3][1] = -(t + b) / tb;
    res.e[3][2] = -(zfar + znear) / fn;
    return res;
}

KJ_CONST kjMat4f kj_mat4f_ortho_inf(f32 l, f32 r, f32 t, f32 b) {
    kjMat4f res = kj_mat4f_ident();
    f32 rl = r - l + KJ_F32_EPS;
    f32 tb = t - b + KJ_F32_EPS;

    res.e[0][0] = 2.0f / rl;
    res.e[1][1] = 2.0f / tb;
    res.e[2][2] = -1.0f;
    res.e[3][0] = -(r + l) / rl;
    res.e[3][1] = -(t + b) / tb;
    return res;
}

KJ_CONST kjMat4f kj_mat4f_perspective(
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

KJ_CONST kjMat4f kj_mat4f_perspective_inf(f32 fovy, f32 aspect, f32 znear) {
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

KJ_CONST kjMat4f kj_mat4f_look_at(kjVec3f eye, kjVec3f target, kjVec3f up) {
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

KJ_CONST KJ_INLINE kjMat4f kj_mat4f_scale(kjVec3f xyz) {
    return kj_mat4f_scale_vec3f(xyz);
}

KJ_CONST KJ_INLINE kjMat4f operator*(kjMat4f a, kjMat4f b) {
    return kj_mat4f_mul(a, b);
}
#endif

KJ_CONST kjRect2f kj_rect2f(f32 x, f32 y, f32 w, f32 h) {
    kjRect2f res;
    res.x = x;
    res.y = y;
    res.w = w;
    res.h = h;
    return res;
}

KJ_CONST kjRect2i kj_rect2i(i32 x, i32 y, i32 w, i32 h) {
    kjRect2i res;
    res.x = x;
    res.y = y;
    res.w = w;
    res.h = h;
    return res;
}

KJ_CONST kjRect2u kj_rect2u(u32 x, u32 y, u32 w, u32 h) {
    kjRect2u res;
    res.x = x;
    res.y = y;
    res.w = w;
    res.h = h;
    return res;
}

KJ_CONST b32 kj_rect2f_contains(kjRect2f r, f32 x, f32 y) {
    return r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y;
}

KJ_CONST b32 kj_rect2i_contains(kjRect2i r, i32 x, i32 y) {
    return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y);
}

KJ_CONST b32 kj_rect2u_contains(kjRect2u r, u32 x, u32 y) {
    return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y);
}

KJ_CONST b32 kj_rect2f_contains_vec2f(kjRect2f r, kjVec2f xy) {
    return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y &&
            (r.y + r.h) >= xy.y);
}

KJ_CONST b32 kj_rect2i_contains_vec2i(kjRect2i r, kjVec2i xy) {
    return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y &&
            (r.y + r.h) >= xy.y);
}

KJ_CONST b32 kj_rect2u_contains_vec2u(kjRect2u r, kjVec2u xy) {
    return (r.x <= xy.x && (r.x + r.w) >= xy.x && r.y <= xy.y &&
            (r.y + r.h) >= xy.y);
}

KJ_CONST i32 kj_rect2f_extend(kjRect2f r, f32 x, f32 y) {
    kj_unused(r);
    kj_unused(x);
    kj_unused(y);
    kj_unimplemented();
    kj_unreachable();
}

KJ_CONST i32 kj_rect2i_extend(kjRect2i r, i32 x, i32 y) {
    kj_unused(r);
    kj_unused(x);
    kj_unused(y);
    kj_unimplemented();
    kj_unreachable();
}

KJ_CONST i32 kj_rect2u_extend(kjRect2u r, u32 x, u32 y) {
    kj_unused(r);
    kj_unused(x);
    kj_unused(y);
    kj_unimplemented();
    kj_unreachable();
}

KJ_CONST i32 kj_rect2f_extend_vec2f(kjRect2f r, kjVec2f xy) {
    kj_unused(r);
    kj_unused(xy);
    kj_unimplemented();
    kj_unreachable();
}

KJ_CONST i32 kj_rect2i_extend_vec2i(kjRect2i r, kjVec2i xy) {
    kj_unused(r);
    kj_unused(xy);
    kj_unimplemented();
    kj_unreachable();
}

KJ_CONST i32 kj_rect2u_extend_vec2u(kjRect2u r, kjVec2u xy) {
    kj_unused(r);
    kj_unused(xy);
    kj_unimplemented();
    kj_unreachable();
}

KJ_CONST kjVec2f kj_rect2f_centre(kjRect2f r) {
    return kj_vec2f((r.x + (r.x + r.w)) / 2.0f, (r.y + (r.y + r.h)) / 2.0f);
}

KJ_CONST kjVec2i kj_rect2i_centre(kjRect2i r) {
    return kj_vec2i((r.x + (r.x + r.w)) / 2, (r.y + (r.y + r.h)) / 2);
}

KJ_CONST kjVec2u kj_rect2u_centre(kjRect2u r) {
    return kj_vec2u((r.x + (r.x + r.w)) / 2, (r.y + (r.y + r.h)) / 2);
}

KJ_CONST kjRect3f kj_rect3f(f32 x, f32 y, f32 z, f32 w, f32 h, f32 d) {
    kjRect3f res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    res.h = h;
    res.d = d;
    return res;
}

KJ_CONST kjRect3i kj_rect3i(i32 x, i32 y, i32 z, i32 w, i32 h, i32 d) {
    kjRect3i res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    res.h = h;
    res.d = d;
    return res;
}

KJ_CONST kjRect3u kj_rect3u(u32 x, u32 y, u32 z, u32 w, u32 h, u32 d) {
    kjRect3u res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    res.h = h;
    res.d = d;
    return res;
}

KJ_CONST b32 kj_rect3f_contains_xy(kjRect3f r, f32 x, f32 y) {
    return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y);
}

KJ_CONST b32 kj_rect3i_contains_xy(kjRect3i r, i32 x, i32 y) {
    return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y);
}

KJ_CONST b32 kj_rect3u_contains_xy(kjRect3u r, u32 x, u32 y) {
    return (r.x <= x && (r.x + r.w) >= x && r.y <= y && (r.y + r.h) >= y);
}

KJ_CONST b32 kj_rect3f_contains_vec2f(kjRect3f r, kjVec2f xy) {
    return (r.x <= xy.x && (r.x + r.w) >= xy.x &&
            r.y <= xy.y && (r.y + r.h) >= xy.y);
}

KJ_CONST b32 kj_rect3i_contains_vec2i(kjRect3i r, kjVec2i xy) {
    return (r.x <= xy.x && (r.x + r.w) >= xy.x &&
            r.y <= xy.y && (r.y + r.h) >= xy.y);
}

KJ_CONST b32 kj_rect3u_contains_vec2u(kjRect3u r, kjVec2u xy) {
    return (r.x <= xy.x && (r.x + r.w) >= xy.x &&
            r.y <= xy.y && (r.y + r.h) >= xy.y);
}

KJ_CONST b32 kj_rect3f_contains(kjRect3f r, f32 x, f32 y, f32 z) {
    return (r.x <= x && (r.x + r.w) >= x &&
            r.y <= y && (r.y + r.h) >= y &&
            r.z <= z && (r.z + r.d) >= z);
}

KJ_CONST b32 kj_rect3i_contains(kjRect3i r, i32 x, i32 y, i32 z) {
    return (r.x <= x && (r.x + r.w) >= x &&
            r.y <= y && (r.y + r.h) >= y &&
            r.z <= z && (r.z + r.d) >= z);
}

KJ_CONST b32 kj_rect3u_contains(kjRect3u r, u32 x, u32 y, u32 z) {
    return (r.x <= x && (r.x + r.w) >= x &&
            r.y <= y && (r.y + r.h) >= y &&
            r.z <= z && (r.z + r.d) >= z);
}

KJ_CONST b32 kj_rect3f_contains_vec3f(kjRect3f r, kjVec3f xyz) {
    return (r.x <= xyz.x && (r.x + r.w) >= xyz.x &&
            r.y <= xyz.y && (r.y + r.h) >= xyz.y &&
            r.z <= xyz.z && (r.z + r.d) >= xyz.z);
}

KJ_CONST b32 kj_rect3i_contains_vec3i(kjRect3i r, kjVec3i xyz) {
    return (r.x <= xyz.x && (r.x + r.w) >= xyz.x &&
            r.y <= xyz.y && (r.y + r.h) >= xyz.y &&
            r.z <= xyz.z && (r.z + r.d) >= xyz.z);
}

KJ_CONST b32 kj_rect3u_contains_vec3u(kjRect3u r, kjVec3u xyz) {
    return (r.x <= xyz.x && (r.x + r.w) >= xyz.x &&
            r.y <= xyz.y && (r.y + r.h) >= xyz.y &&
            r.z <= xyz.z && (r.z + r.d) >= xyz.z);
}

KJ_CONST i32 kj_rect3f_extend(kjRect3f r, f32 x, f32 y, f32 z);
KJ_CONST i32 kj_rect3i_extend(kjRect3i r, i32 x, i32 y, i32 z);
KJ_CONST i32 kj_rect3u_extend(kjRect3u r, u32 x, u32 y, u32 z);
KJ_CONST i32 kj_rect3f_extend_vec3f(kjRect3f r, kjVec3f xyz);
KJ_CONST i32 kj_rect3i_extend_vec3i(kjRect3i r, kjVec3i xyz);
KJ_CONST i32 kj_rect3u_extend_vec3u(kjRect3u r, kjVec3u xyz);

KJ_CONST kjVec3f kj_rect3f_centre(kjRect3f r) {
    return kj_vec3f(
            (r.x + (r.x + r.w)) / 2.0f,
            (r.y + (r.y + r.h)) / 2.0f,
            (r.z + (r.z + r.w)) / 2.0f);
}

KJ_CONST kjVec3i kj_rect3i_centre(kjRect3i r) {
    return kj_vec3i(
            (r.x + (r.x + r.w)) / 2,
            (r.y + (r.y + r.h)) / 2,
            (r.z + (r.z + r.w)) / 2);
}

KJ_CONST kjVec3u kj_rect3u_centre(kjRect3u r) {
    return kj_vec3u(
            (r.x + (r.x + r.w)) / 2,
            (r.y + (r.y + r.h)) / 2,
            (r.z + (r.z + r.w)) / 2);
}

KJ_CONST kjRgba kj_rgba(u8 r, u8 g, u8 b, u8 a) {
    kjRgba res;
    res.r = r;
    res.b = b;
    res.g = g;
    res.a = a;
    return res;
}

KJ_CONST kjRgba kj_rgba_4f(f32 r, f32 g, f32 b, f32 a) {
    return kj_rgba(
        kj_cast(u8, r * 255.0f + 0.5f),
        kj_cast(u8, g * 255.0f + 0.5f),
        kj_cast(u8, b * 255.0f + 0.5f),
        kj_cast(u8, a * 255.0f + 0.5f));
}

KJ_CONST kjRgba kj_rgba_rgbaf(kjVec4f rgbaf) {
    return kj_rgba_4f(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
}

KJ_CONST u32 kj_rgba_pack(kjRgba rgba) {
    return (rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | (rgba.a << 0);
}

KJ_CONST kjRgba kj_rgba_unpack(u32 packed) {
    return kj_rgba(
        kj_cast(u8, (packed & 0xFF000000) >> 24),
        kj_cast(u8, (packed & 0x00FF0000) >> 16),
        kj_cast(u8, (packed & 0x0000FF00) >> 8),
        kj_cast(u8, (packed & 0x000000FF) >> 0));
}

KJ_CONST kjVec4f kj_rgbaf(f32 r, f32 g, f32 b, f32 a) {
    kjVec4f res;
    res.r = r;
    res.b = b;
    res.g = g;
    res.a = a;
    return res;
}

KJ_CONST kjVec4f kj_rgbaf_4u8(u8 r, u8 g, u8 b, u8 a) {
    return kj_rgbaf(
        kj_cast(f32, r / 255.0f),
        kj_cast(f32, g / 255.0f),
        kj_cast(f32, b / 255.0f),
        kj_cast(f32, a / 255.0f));
}

KJ_CONST kjVec4f kj_rgbaf_rgba(kjRgba rgba) {
    return kj_rgbaf_4u8(rgba.r, rgba.g, rgba.b, rgba.a);
}

KJ_CONST u32 kj_rgbaf_pack(kjVec4f rgba) {
    return
        (kj_cast(u8, rgba.r * 255.0f) << 24) |
        (kj_cast(u8, rgba.g * 255.0f) << 16) |
        (kj_cast(u8, rgba.b * 255.0f) << 8)  |
        (kj_cast(u8, rgba.a * 255.0f) << 0);
}

KJ_CONST kjVec4f kj_rgbaf_unpack(u32 packed) {
    return kj_rgbaf(
        kj_cast(f32, ((packed & 0xFF000000) >> 24) / 255.0f),
        kj_cast(f32, ((packed & 0x00FF0000) >> 16) / 255.0f),
        kj_cast(f32, ((packed & 0x0000FF00) >> 8)  / 255.0f),
        kj_cast(f32, ((packed & 0x000000FF) >> 0)  / 255.0f));
}

#endif
