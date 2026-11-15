/* Area m3, file 23: float-equality tests and revisits. Names inferred. */
#include <stdint.h>

typedef struct M3W8_23 { uint32_t w[8]; } M3W8_23;
typedef struct M3Lt23 {
    uint32_t f0; uint8_t unk04[8]; int32_t iC; float f10; uint8_t unk14[0x10]; M3W8_23 cur24; uint8_t unk44[0x354];
    float f398; uint8_t unk39C[0x1C]; float f3B8; uint32_t f3BC; float f3C0, f3C4, f3C8, f3CC; M3W8_23 prev3D0; M3W8_23 src3F0; float f410; float f414;
} M3Lt23;
typedef struct M3LtCmd23 {
    uint8_t unk00[0x10]; M3W8_23 v10; int32_t i30; float f34, f38; M3Lt23 *lt3C; int32_t i40; uint32_t f44; float f48;
} M3LtCmd23;
void rbk_RigParams0D56C0(M3Lt23 *l, int a, int b, int c, int d, int e, int f, int g, int h);

/* 0xD5B80: apply a light command: with no blend time set the light directly (0xD56C0), else remember the current and target values and the blend time; then apply the change flags (1/2 reset the main fade, 4 the second), the id and the enable bits. */
void m3_LightCmdD5B80(M3LtCmd23 *c) {
    M3Lt23 *p; int32_t fl; float a, b;
    if (c->f48 != 0.0f) {
        c->lt3C->prev3D0 = c->lt3C->cur24;
        c->lt3C->src3F0 = c->v10;
        c->lt3C->f410 = c->f48;
    } else {
        rbk_RigParams0D56C0(c->lt3C, c->v10.w[4], c->v10.w[5], c->v10.w[6], c->v10.w[7], c->v10.w[0], c->v10.w[1], c->v10.w[2], c->v10.w[3]);
        c->lt3C->f410 = 0.0f;
    }
    c->lt3C->f414 = 0.0f;
    fl = c->i30; b = c->f38; a = c->f34; p = c->lt3C;
    if (fl) {
        p->f3BC |= fl;
        if (fl & 3) { p->f3B8 = 0.0f; p->f3C0 = a; p->f3C4 = b; p->f398 = 0.0f; }
        if (fl & 4) { p->f3C8 = 0.0f; p->f3CC = a; }
    }
    c->lt3C->iC = c->i40;
    c->lt3C->f10 = 0.0f;
    c->lt3C->f0 &= ~1u;
    c->lt3C->f0 |= c->f44;
}

typedef struct M3TSt23 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x24]; float v2C, v30, v34, w38; } M3TSt23;
typedef struct M3TEn23 { uint8_t unk00[0x278]; M3TSt23 *st278; } M3TEn23;
typedef struct M3TOb23 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0xC]; float *mtx20; uint8_t unk24[0x3C]; float pos60[4]; } M3TOb23;
typedef struct M3TPl23 { uint8_t unk00[0x60]; float pos60[4]; } M3TPl23;
extern M3TPl23 *g_playerObj;
extern float b10_frameDelta;
void r4c_VecSub(float *dst, const float *a, const float *b);
void rbi_VecNorm(float *d, const float *s);
void rbi_VecScale(float *d, const float *s, float k);
float rbi_VecDot(const float *a, const float *b);
void rbi_VecCross(float *d, const float *a, const float *b);
void a3c_VecCopy(float *dst, const float *src);
int  m1_AiSetState1456E0(void *a, void *e, int s, int t);
void sub_0001D4E0(void *a);
void aab_Effect494D0(int id, void *pos, int a);

/* 0x116380: AI recoil entry: compare its facing with the direction from the player; facing away (dot > 0) enter state 0x38 and turn round, otherwise state 0x34 facing the player; set the slide-back speed, rebuild upright axes, flag the state and play effect 0x16C. */
void m3_AiRecoil116380(M3TOb23 *a, M3TEn23 *o) {
    M3TSt23 *st = o->st278; float d[4], f[4], k; float *m;
    r4c_VecSub(d, a->pos60, g_playerObj->pos60);
    d[1] = 0.0f;
    rbi_VecNorm(d, d);
    rbi_VecScale(f, a->mtx20 + 8, -1.0f);
    f[1] = 0.0f;
    rbi_VecNorm(f, f);
    k = rbi_VecDot(f, d);
    if (k == 0.0f) rbi_VecScale(d, f, -1.0f);
    if (k > 0.0f) {
        if (m1_AiSetState1456E0(a, o, 0x38, 0) == 1) sub_0001D4E0(a);
        o->st278->v30 = 0.0f - b10_frameDelta * 100.0f;
        o->st278->v34 = 0.0f; o->st278->v2C = 0.0f;
        o->st278->w38 = 1.0f;
        rbi_VecScale(a->mtx20 + 8, d, -1.0f);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x34, 0) == 1) sub_0001D4E0(a);
        o->st278->v30 = 0.0f - b10_frameDelta * 100.0f;
        o->st278->v34 = 0.0f; o->st278->v2C = 0.0f;
        o->st278->w38 = 1.0f;
        a3c_VecCopy(a->mtx20 + 8, d);
    }
    a->mtx20[7] = 0.0f; a->mtx20[6] = 0.0f; a->mtx20[4] = 0.0f; a->mtx20[5] = 1.0f;
    m = a->mtx20;
    rbi_VecCross(m, m + 4, m + 8);
    a->f10 |= 0x10;
    st->f4 = (st->f4 & ~0x80000u) | 0x4001;
    aab_Effect494D0(0x16C, a->pos60, 0);
    if (*(uint8_t *)&st->f4 & 0x10) a->f10 |= 0xD;
}

typedef struct M3KSt23 { uint8_t unk00[0x30]; float cur30[4]; float prev40[4]; float v50, v54, v58, w5C, f60, f64; } M3KSt23;
typedef struct M3KEn23 { uint8_t unk00[0x278]; M3KSt23 *st278; } M3KEn23;
typedef struct M3KPar23 { uint8_t unk00[0x10]; float range10; float spd14; float side18; float wait1C; } M3KPar23;
extern float a50_framesPerSecond;
float rbj_Distance(const float *a, const float *b);

/* 0x12CFB0: keep-distance step (every half second): move in when farther than range + 2, back off when nearer than range - 2, keep the side speed, save the previous position and set the blend rate (2.22/fps; flag when it is exactly 1). */
void m3_KeepDist12CFB0(M3TOb23 *a, M3KEn23 *o, M3KPar23 *p) {
    float d, x, y, t; M3KSt23 *st;
    if (p->wait1C > 0.0f) { p->wait1C = p->wait1C - b10_frameDelta; return; }
    p->wait1C = 0.5f;
    d = rbj_Distance(a->pos60, g_playerObj->pos60);
    if (d >= p->range10 + 2.0f) x = p->spd14;
    else if (!(p->range10 - 2.0f >= d)) x = 0.0f;
    else x = 0.0f - p->spd14;
    y = p->side18;
    st = o->st278;
    t = (float)(1.0f / a50_framesPerSecond * 2.2222222222222223);
    a3c_VecCopy(st->prev40, st->cur30);
    st->v58 = 0.0f - x;
    st->v50 = y;
    st->v54 = 0.0f;
    st->w5C = 1.0f;
    if (t == 1.0f) st->f60 = 1.0f;
    else st->f60 = 0.0f;
    st->f64 = t;
}
