#ifndef KJ_MAT_H
#define KJ_MAT_H

#define KJ_MAT_VERSION_MAJOR 0
#define KJ_MAT_VERSION_MINOR 1
#define KJ_MAT_VERSION_PATCH 0

typedef union kj_mat3f {
    f32 e[3][3];
    f32 a[9];
    kj_vec3f_t v[3];
} kj_mat3f_t;

typedef union kj_mat4f {
    f32 e[4][4];
    f32 a[16];
    kj_vec4f_t v[4];
} kj_mat4f_t;

#if defined(__cplusplus)
extern "C" {
#endif

kj_api kj_mat3f_t kj_mat3f(
        f32 e00, f32 e10, f32 e20,
        f32 e01, f32 e11, f32 e21,
        f32 e02, f32 e12, f32 e22);
kj_api kj_mat3f_t kj_mat3f_diag(f32 e00, f32 e11, f32 e22);
kj_api kj_mat3f_t kj_mat3f_ident(void);
kj_api kj_mat3f_t kj_mat3f_zero(void);
kj_api kj_mat3f_t kj_mat3f_one(void);
kj_api kj_mat3f_t kj_mat3f_mul(kj_mat3f_t a, kj_mat3f_t b);

kj_api kj_mat4f_t kj_mat4f(
        f32 e00, f32 e10, f32 e20, f32 e30,
        f32 e01, f32 e11, f32 e21, f32 e31,
        f32 e02, f32 e12, f32 e22, f32 e32,
        f32 e03, f32 e13, f32 e23, f32 e33);
kj_api kj_mat4f_t kj_mat4f_diag(f32 e00, f32 e11, f32 e22, f32 e33);
kj_api kj_mat4f_t kj_mat4f_ident(void);
kj_api kj_mat4f_t kj_mat4f_zero(void);
kj_api kj_mat4f_t kj_mat4f_one(void);
kj_api kj_mat4f_t kj_mat4f_mul(kj_mat4f_t a, kj_mat4f_t b);
kj_api kj_mat4f_t kj_mat4f_translate(f32 x, f32 y, f32 z);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_MAT_IMPLEMENTATION)

kj_mat3f_t kj_mat3f(
        f32 e00, f32 e10, f32 e20,
        f32 e01, f32 e11, f32 e21,
        f32 e02, f32 e12, f32 e22)
{
    kj_mat3f_t res;
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

kj_mat3f_t kj_mat3f_diag(f32 e00, f32 e11, f32 e22)
{
    return kj_mat3f(
            e00, 0.0f, 0.0f,
            0.0f, e11, 0.0f,
            0.0f, 0.0f, e22);
}

kj_mat3f_t kj_mat3f_ident(void)
{
    return kj_mat3f_diag(1.0f, 1.0f, 1.0f);
}

kj_mat3f_t kj_mat3f_zero(void)
{
    kj_mat3f_t res;
    kj_zero(&res, isize_of(kj_mat3f_t));
    return res;
}

kj_mat3f_t kj_mat3f_one(void)
{
    kj_mat3f_t res;
    kj_one(&res, isize_of(kj_mat3f_t));
    return res;
}

kj_mat3f_t kj_mat3f_mul(kj_mat3f_t a, kj_mat3f_t b)
{
    kj_mat3f_t res;
    kj_vec3f_t bv0 = kj_vec3f(b.v[0].x, b.v[1].x, b.v[2].x);
    kj_vec3f_t bv1 = kj_vec3f(b.v[0].y, b.v[1].y, b.v[2].y);
    kj_vec3f_t bv2 = kj_vec3f(b.v[0].z, b.v[1].z, b.v[2].z);
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

kj_mat4f_t kj_mat4f(
        f32 e00, f32 e10, f32 e20, f32 e30,
        f32 e01, f32 e11, f32 e21, f32 e31,
        f32 e02, f32 e12, f32 e22, f32 e32,
        f32 e03, f32 e13, f32 e23, f32 e33)
{
    kj_mat4f_t res;
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

kj_mat4f_t kj_mat4f_diag(f32 e00, f32 e11, f32 e22, f32 e33)
{
    return kj_mat4f(
            e00, 0.0f, 0.0f, 0.0f,
            0.0f, e11, 0.0f, 0.0f,
            0.0f, 0.0f, e22, 0.0f,
            0.0f, 0.0f, 0.0f, e33);
}

kj_mat4f_t kj_mat4f_ident(void)
{
    return kj_mat4f_diag(1.0f, 1.0f, 1.0f, 1.0f);
}

kj_mat4f_t kj_mat4f_zero(void)
{
    kj_mat4f_t res;
    kj_zero(&res, isize_of(kj_mat4f_t));
    return res;
}

kj_mat4f_t kj_mat4f_one(void)
{
    kj_mat4f_t res;
    kj_one(&res, isize_of(kj_mat4f_t));
    return res;
}

kj_mat4f_t kj_mat4f_mul(kj_mat4f_t a, kj_mat4f_t b)
{
    kj_mat4f_t res;
    kj_vec4f_t bv0 = kj_vec4f(b.v[0].x, b.v[1].x, b.v[2].x, b.v[3].x);
    kj_vec4f_t bv1 = kj_vec4f(b.v[0].y, b.v[1].y, b.v[2].y, b.v[3].y);
    kj_vec4f_t bv2 = kj_vec4f(b.v[0].z, b.v[1].z, b.v[2].z, b.v[3].z);
    kj_vec4f_t bv3 = kj_vec4f(b.v[0].w, b.v[1].w, b.v[2].w, b.v[3].w);
    res.v[0] = kj_vec4f_add(kj_vec4f_add(kj_vec4f_add(
        kj_vec4f_mul(a.v[0], bv0),
        kj_vec4f_mul(a.v[0], bv1)),
        kj_vec4f_mul(a.v[0], bv2)),
        kj_vec4f_mul(a.v[0], bv3));
    res.v[1] = kj_vec4f_add(kj_vec4f_add(kj_vec4f_add(
        kj_vec4f_mul(a.v[1], bv0),
        kj_vec4f_mul(a.v[1], bv1)),
        kj_vec4f_mul(a.v[1], bv2)),
        kj_vec4f_mul(a.v[1], bv3));
    res.v[2] = kj_vec4f_add(kj_vec4f_add(kj_vec4f_add(
        kj_vec4f_mul(a.v[2], bv0),
        kj_vec4f_mul(a.v[2], bv1)),
        kj_vec4f_mul(a.v[2], bv2)),
        kj_vec4f_mul(a.v[2], bv3));
    res.v[3] = kj_vec4f_add(kj_vec4f_add(kj_vec4f_add(
        kj_vec4f_mul(a.v[3], bv0),
        kj_vec4f_mul(a.v[3], bv1)),
        kj_vec4f_mul(a.v[3], bv2)),
        kj_vec4f_mul(a.v[3], bv3));
    return res;
}

kj_mat4f_t kj_mat4f_translate(f32 x, f32 y, f32 z)
{
    kj_mat4f_t res = kj_mat4f_ident();
    res.v[3].x = x;
    res.v[3].y = y;
    res.v[3].z = z;
    return res;
}

#endif
