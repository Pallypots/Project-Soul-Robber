/* Area m2, file 22: sphere mesh. Names inferred. */
#include <stdint.h>

extern float *r1g_batchCur3DCEFC;
void  r1g_BatchBegin(void *b, int kind, int count);
float sub_001A3ED0(float a);
float sub_001A3EE0(float a);
void  sub_0003A2A0(void *b, float rx, float ry, float rz, int nu, int nv);

/* 0x3A6B0: emit a sphere (ellipsoid radii rx, ry, rz) as two strip sets: 2*nu meridian strips over nv+2 rings, then nv latitude strips over 2*nu+1 points; each vertex's fourth word is 0 for a strip start and 0x8000 otherwise. Finishes through 0x3A2A0. */
void m2_SphereMesh3A6B0(void *b, float rx, float ry, float rz, int nu, int nv) {
    float stepU, stepV, sa, ca, sb, cb, t;
    int u, i, j, k;
    float *p;
    if (nu < 1) nu = 1;
    u = nu + nu;
    if (nv < 1) nv = 1;
    stepU = 6.2831860f / (float)u;
    stepV = 3.1415930f / (float)(nv + 1);
    r1g_BatchBegin(b, 2, (nv + 2) * u + (u + 1) * nv);
    for (i = 0; i < u; i++) {
        float a = (float)(i % u) * stepU;
        sa = sub_001A3ED0(a);
        ca = sub_001A3EE0(a);
        for (j = 0; j <= nv + 1; j++) {
            float bb = (float)j * stepV;
            sb = sub_001A3ED0(bb);
            cb = sub_001A3EE0(bb);
            p = r1g_batchCur3DCEFC;
            p[0] = sb * sa * rx;
            ((int32_t *)p)[3] = j ? 0x8000 : 0;
            p[1] = cb * ry;
            p[2] = sb * ca * rz;
            r1g_batchCur3DCEFC = (float *)((uint8_t *)r1g_batchCur3DCEFC + 0x10);
        }
    }
    for (k = 1; k <= nv; k++) {
        float bb = (float)k * stepV;
        sb = sub_001A3ED0(bb);
        cb = sub_001A3EE0(bb);
        t = cb * ry;
        for (j = 0; j <= u; j++) {
            float a = (float)(j % u) * stepU;
            float s1 = sub_001A3ED0(a) * sb;
            float c1 = sub_001A3EE0(a) * sb;
            p = r1g_batchCur3DCEFC;
            p[0] = s1 * rx;
            ((int32_t *)p)[3] = j ? 0x8000 : 0;
            p[1] = t;
            p[2] = c1 * rz;
            r1g_batchCur3DCEFC = (float *)((uint8_t *)r1g_batchCur3DCEFC + 0x10);
        }
    }
    sub_0003A2A0(b, rx, ry, rz, nu, nv);
}

typedef struct M2Crv22 { uint8_t b[0x18]; } M2Crv22;
typedef struct M2Mover22 { uint8_t unk00[0x28]; void *model28; uint8_t unk2C[8]; float t34, t38; int32_t anim3C; float off40; uint8_t unk44[4]; M2Crv22 c48[9]; } M2Mover22;
float m1_CurveAt07F650(M2Crv22 *c, float r);
void  r4e_MatIdentity(float *m);
void  rbj_MatRotX(float *d, const float *s, float a);
void  rbj_MatRotY(float *d, const float *s, float a);
void  rbj_MatRotZ(float *d, const float *s, float a);
void  r4c_Vec4Scale(float *d, const float *a, float s);
int   sub_0007E9B0(void *model, int id);
void  a6b_Model_ScaleParts(void *model, float t);
void  a6b_Model_RateParts(void *model);
void  a6b_Model_SetPartsDC(void *model, float t);
void  sub_0007E350(void *model, float *m);

/* 0x8DE70: pose a moving model at time t: the progress through its [t34, t38] window drives nine curves (position x/y/z, scale x/y/z, rotation x/y/z in degrees); builds the matrix, plays its animation and sets the part time (offset + elapsed; flag set: direct scale, else rate plus a +1000 bias), then applies the matrix. */
void m2_MoverPose8DE70(M2Mover22 *o, float t, char flag) {
    float m[16];
    float c0, c1, c2, c3, c4, c5, c6, c7, c8;
    float rel, span, ratio = 0.0f, x;
    if (t >= o->t34) rel = t - o->t34;
    else rel = 0.0f;
    span = o->t38 - o->t34;
    if (span > 0.0f) ratio = rel / span;
    c0 = m1_CurveAt07F650(&o->c48[0], ratio);
    c1 = m1_CurveAt07F650(&o->c48[1], ratio);
    c2 = m1_CurveAt07F650(&o->c48[2], ratio);
    c3 = m1_CurveAt07F650(&o->c48[3], ratio);
    c4 = m1_CurveAt07F650(&o->c48[4], ratio);
    c5 = m1_CurveAt07F650(&o->c48[5], ratio);
    c6 = m1_CurveAt07F650(&o->c48[6], ratio);
    c7 = m1_CurveAt07F650(&o->c48[7], ratio);
    c8 = m1_CurveAt07F650(&o->c48[8], ratio);
    r4e_MatIdentity(m);
    rbj_MatRotX(m, m, c6 * 3.1415927f * 0.0055555557f);
    rbj_MatRotY(m, m, c7 * 3.1415927f * 0.0055555557f);
    rbj_MatRotZ(m, m, c8 * 3.1415927f * 0.0055555557f);
    r4c_Vec4Scale(m, m, c3);
    r4c_Vec4Scale(m + 4, m + 4, c4);
    r4c_Vec4Scale(m + 8, m + 8, c5);
    m[12] = c0; m[13] = c1; m[14] = c2;
    sub_0007E9B0(o->model28, o->anim3C);
    x = o->off40 + rel;
    if (flag) {
        a6b_Model_ScaleParts(o->model28, x);
    } else {
        a6b_Model_RateParts(o->model28);
        a6b_Model_SetPartsDC(o->model28, x + 1000.0f);
    }
    sub_0007E350(o->model28, m);
}

typedef struct M2Trk22 { uint8_t b[0x10]; } M2Trk22;
typedef struct M2CamSet22 { uint8_t unk00[0x28]; M2Trk22 t28[9]; } M2CamSet22;
typedef struct M2CamObj22 { uint8_t unk00[0x24]; uint8_t flags24; uint8_t unk25[3]; M2CamSet22 *set28; float t2C, t30; M2Crv22 c34[9]; } M2CamObj22;
typedef struct M2Clock22 { uint8_t unk00[0x10]; float t10; } M2Clock22;
extern uint8_t *r2d_ctx;
float sub_0007EF00(M2Trk22 *t, float time);
void  rbi_VecCross(float *d, const float *a, const float *b);
void  r6c_ObjPlaceLight(void *ctx, float *m, float v);

/* 0x8D910: evaluate a camera cut at the clock time: each channel is its track value at the elapsed time plus its curve value at the progress through the cut (eye x/y/z, target x/y/z, an unused pair, and the last value); when enabled (flag bit 0) builds the look-at matrix from eye to target and places it with the last value. -1 without cut or clock, else 0. */
int m2_CamCut8D910(M2CamObj22 *o, M2Clock22 *c) {
    float m[16];
    float rel, span, ratio;
    float s0, s1, s2, s3, s4, s5, s7;
    float k0, k1, k2, k3, k4, k5, k7;
    if (o == 0 || c == 0) return -1;
    span = o->t30 - o->t2C;
    rel = c->t10 - o->t2C;
    if (span != 0.0f) ratio = rel / span;
    else ratio = 0.0f;
    k0 = sub_0007EF00(&o->set28->t28[0], rel);
    k1 = sub_0007EF00(&o->set28->t28[1], rel);
    k2 = sub_0007EF00(&o->set28->t28[2], rel);
    k3 = sub_0007EF00(&o->set28->t28[3], rel);
    k4 = sub_0007EF00(&o->set28->t28[4], rel);
    k5 = sub_0007EF00(&o->set28->t28[5], rel);
    sub_0007EF00(&o->set28->t28[6], rel);
    k7 = sub_0007EF00(&o->set28->t28[7], rel);
    s0 = m1_CurveAt07F650(&o->c34[0], ratio) + k0;
    s1 = m1_CurveAt07F650(&o->c34[1], ratio) + k1;
    s2 = m1_CurveAt07F650(&o->c34[2], ratio) + k2;
    s3 = m1_CurveAt07F650(&o->c34[3], ratio) + k3;
    s4 = m1_CurveAt07F650(&o->c34[4], ratio) + k4;
    s5 = m1_CurveAt07F650(&o->c34[5], ratio) + k5;
    m1_CurveAt07F650(&o->c34[6], ratio);
    s7 = m1_CurveAt07F650(&o->c34[7], ratio) + k7;
    if (o->flags24 & 1) {
        r4e_MatIdentity(m);
        m[8] = s3 - s0; m[9] = s4 - s1; m[10] = s5 - s2; m[11] = 0.0f;
        rbi_VecCross(m, m + 4, m + 8);
        rbi_VecCross(m + 4, m + 8, m);
        m[12] = s0; m[13] = s1; m[14] = s2; m[15] = 0.0f;
        r6c_ObjPlaceLight(r2d_ctx, m, s7);
    }
    return 0;
}
