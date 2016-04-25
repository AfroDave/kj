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
kj_api kj_mat3f_t kj_mat3f_transpose(kj_mat3f_t a);

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
<<<<<<< HEAD
kj_api kj_vec4f_t kj_mat4f_mul_vec4f(kj_mat4f_t a, kj_vec4f_t b);
=======
kj_api kj_mat4f_t kj_mat4f_transpose(kj_mat4f_t a);
>>>>>>> 6a87236... matrix transform
kj_api kj_mat4f_t kj_mat4f_translate(f32 x, f32 y, f32 z);
kj_api kj_mat4f_t kj_mat4f_rotate(f32 angle, f32 x, f32 y, f32 z);
kj_api kj_mat4f_t kj_mat4f_scale(f32 x, f32 y, f32 z);
kj_api kj_mat4f_t kj_mat4f_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 znear, f32 zfar);
kj_api kj_mat4f_t kj_mat4f_ortho_inf(f32 left, f32 right, f32 top, f32 bottom);
kj_api kj_mat4f_t kj_mat4f_perspective(f32 fovy, f32 aspect, f32 znear, f32 zfar);
kj_api kj_mat4f_t kj_mat4f_perspective_inf(f32 fovy, f32 aspect, f32 znear);
kj_api kj_mat4f_t kj_mat4f_look_at(kj_vec3f_t eye, kj_vec3f_t target, kj_vec3f_t up);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_MAT_IMPLEMENTATION)

#include <math.h>

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

kj_vec4f_t kj_mat4f_mul_vec4f(kj_mat4f_t a, kj_vec4f_t b)
{
    kj_vec4f_t v0 = kj_vec4f_mulf(a.v[0], b.x);
    kj_vec4f_t v1 = kj_vec4f_mulf(a.v[1], b.y);
    kj_vec4f_t v2 = kj_vec4f_mulf(a.v[2], b.z);
    kj_vec4f_t v3 = kj_vec4f_mulf(a.v[3], b.w);
    return kj_vec4f_add(kj_vec4f_add(v0, v1), kj_vec4f_add(v2, v3));
}

kj_mat3f_t kj_mat3f_transpose(kj_mat3f_t a)
{
    return kj_mat3f(
        a.e[0][0], a.e[1][0], a.e[2][0],
        a.e[0][1], a.e[1][1], a.e[2][1],
        a.e[0][2], a.e[1][2], a.e[2][2]);
}

kj_mat3f_t kj_mat3f_rotate(f32 angle, f32 x, f32 y, f32 z)
{
    kj_mat3f_t res;
    f32 angle_cos = cosf(angle);
    f32 angle_sin = sinf(angle);

    kj_vec3f_t axis = kj_vec3f_normalise(kj_vec3f(x, y, z));
    kj_vec3f_t rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - angle_cos));
    res.e[0][0] = angle_cos + rot_axis.x * axis.x;
    res.e[0][1] = 0.0f + rot_axis.x * axis.y + angle_sin * axis.z;
    res.e[0][2] = 0.0f + rot_axis.x * axis.z - angle_sin * axis.y;
    res.e[1][0] = 0.0f + rot_axis.y * axis.x - angle_sin * axis.z;
    res.e[1][1] = angle_cos + rot_axis.y * axis.y;
    res.e[1][2] = 0.0f+ rot_axis.y * axis.z + angle_sin * axis.x;
    res.e[2][0] = 0.0f + rot_axis.z * axis.x + angle_sin * axis.y;
    res.e[2][1] = 0.0f + rot_axis.z * axis.y - angle_sin * axis.x;
    res.e[2][2] = angle_cos + rot_axis.z * axis.z;
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

kj_mat4f_t kj_mat4f_transpose(kj_mat4f_t a)
{
    return kj_mat4f(
        a.e[0][0], a.e[1][0], a.e[2][0], a.e[3][0],
        a.e[0][1], a.e[1][1], a.e[2][1], a.e[3][1],
        a.e[0][2], a.e[1][2], a.e[2][2], a.e[3][2],
        a.e[0][3], a.e[1][3], a.e[2][3], a.e[3][3]);
}

kj_mat4f_t kj_mat4f_translate(f32 x, f32 y, f32 z)
{
    kj_mat4f_t res = kj_mat4f_ident();
    res.v[3].x = x;
    res.v[3].y = y;
    res.v[3].z = z;
    return res;
}

kj_mat4f_t kj_mat4f_rotate(f32 angle, f32 x, f32 y, f32 z)
{
    kj_mat4f_t res;
    f32 angle_cos = cosf(angle);
    f32 angle_sin = sinf(angle);

    kj_vec3f_t axis = kj_vec3f_normalise(kj_vec3f(x, y, z));
    kj_vec3f_t rot_axis = kj_vec3f_mul(axis, kj_vec3f_all(1.0f - angle_cos));
    res.e[0][0] = angle_cos + rot_axis.x * axis.x;
    res.e[0][1] = 0.0f + rot_axis.x * axis.y + angle_sin * axis.z;
    res.e[0][2] = 0.0f + rot_axis.x * axis.z - angle_sin * axis.y;
    res.e[0][3] = 0.0f;
    res.e[1][0] = 0.0f + rot_axis.y * axis.x - angle_sin * axis.z;
    res.e[1][1] = angle_cos + rot_axis.y * axis.y;
    res.e[1][2] = 0.0f+ rot_axis.y * axis.z + angle_sin * axis.x;
    res.e[1][3] = 0.0f;
    res.e[2][0] = 0.0f + rot_axis.z * axis.x + angle_sin * axis.y;
    res.e[2][1] = 0.0f + rot_axis.z * axis.y - angle_sin * axis.x;
    res.e[2][2] = angle_cos + rot_axis.z * axis.z;
    res.e[2][3] = 0.0f;
    res.e[3][0] = 0.0f;
    res.e[3][1] = 0.0f;
    res.e[3][2] = 0.0f;
    res.e[3][3] = 1.0f;
    return res;
}

kj_mat4f_t kj_mat4f_scale(f32 x, f32 y, f32 z)
{
    kj_mat4f_t res = kj_mat4f_ident();
    res.e[0][0] = x;
    res.e[1][1] = y;
    res.e[2][2] = z;
    return res;
}

kj_mat4f_t kj_mat4f_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 znear, f32 zfar)
{
    kj_mat4f_t res = kj_mat4f_ident();
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

kj_mat4f_t kj_mat4f_ortho_inf(f32 left, f32 right, f32 top, f32 bottom)
{
    kj_mat4f_t res = kj_mat4f_ident();
    f32 rl = right - left + F32_EPS;
    f32 tb = top - bottom + F32_EPS;

    res.e[0][0] = 2.0f / rl;
    res.e[1][1] = 2.0f / tb;
    res.e[2][2] = -1.0f;
    res.e[3][0] = -(right + left) / rl;
    res.e[3][1] = -(top + bottom) / tb;
    return res;
}

kj_mat4f_t kj_mat4f_perspective(f32 fovy, f32 aspect, f32 znear, f32 zfar)
{
    kj_mat4f_t res = kj_mat4f_zero();
    if(aspect > 0.0f) {
        f32 tanfovy = tanf(0.5f * fovy);
        res.e[0][0] = 1.0f / (aspect * tanfovy);
        res.e[1][1] = 1.0f / tanfovy;
        res.e[2][2] = -(zfar + znear) / (zfar - znear);
        res.e[2][3] = -1.0f;
        res.e[3][2] = -(2.0f * zfar * znear) / (zfar - znear);
    }
    return res;
}

kj_mat4f_t kj_mat4f_perspective_inf(f32 fovy, f32 aspect, f32 znear)
{
    kj_mat4f_t res = kj_mat4f_zero();
    if(aspect > 0.0f) {
        f32 range  = tanf(0.5f * fovy) * znear;
        res.e[0][0] = (2.0f * znear) / ((range * aspect) - (-range * aspect));
        res.e[1][1] = (2.0f * znear) / (range - -range);
        res.e[2][2] = -1.0f;
        res.e[2][3] = -1.0f;
        res.e[3][2] = -2.0f * znear;
    }
    return res;
}

kj_mat4f_t kj_mat4f_look_at(kj_vec3f_t eye, kj_vec3f_t target, kj_vec3f_t up)
{
    kj_mat4f_t res;
    kj_vec3f_t f = kj_vec3f_normalise(kj_vec3f_sub(target, eye));
    kj_vec3f_t s = kj_vec3f_normalise(kj_vec3f_cross(f, up));
    kj_vec3f_t u = kj_vec3f_cross(s, f);

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


#endif
