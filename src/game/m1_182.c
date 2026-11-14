/* Area m1, file 182: overlay quad and curve sampling. Names inferred. */
#include <stdint.h>

typedef struct M1Quad182 { float a[4]; float b[4]; uint32_t col[4]; int32_t tex30; uint32_t mode34; } M1Quad182;
extern int32_t m1_figTex3E057C;
void  r4e_SetRenderState4035C(int on);
void *sub_00072420(void *dl, M1Quad182 *q);

/* 0x4BF00: draw a full-screen (512x448) grey quad with the figure light texture, render state off around it. */
void *m1_FigLightCb04BF00(void *dl) {
    M1Quad182 q; void *r;
    q.tex30 = m1_figTex3E057C;
    q.mode34 = 0xFF000010;
    q.a[0] = 0.0f; q.a[2] = 512.0f; q.a[1] = 0.0f; q.a[3] = 448.0f;
    q.b[0] = 0.0f; q.b[1] = 0.0f; q.b[2] = 512.0f; q.b[3] = 448.0f;
    q.col[3] = 0x80808080; q.col[2] = 0x80808080; q.col[1] = 0x80808080; q.col[0] = 0x80808080;
    r4e_SetRenderState4035C(0);
    r = sub_00072420(dl, &q);
    r4e_SetRenderState4035C(1);
    return r;
}

typedef struct M1Crv182 { int32_t unk0; int32_t kind4; float *v8; } M1Crv182;
extern int32_t m1_curveTbl2E020C[];
float *sub_0007EF30(M1Crv182 *c, float t);

/* 0x7F000: sample a curve at t: find the key before t and interpolate its value toward the next key. */
float m1_CurveSample07F000(M1Crv182 *c, float t) {
    float *k, *nk, d;
    if (c == 0) return 0.0f;
    k = sub_0007EF30(c, t);
    if (k == 0) return 0.0f;
    nk = k + m1_curveTbl2E020C[c->kind4 * 5];
    if (!(0.0f > nk[0])) {
        d = nk[0] - k[0];
        if (d != 0.0f) return (t - k[0]) / d * (nk[1] - k[1]) + k[1];
    }
    return k[1];
}

typedef struct M1Slot182 { float f0, f4, f8, fC; int32_t i10, i14, i18, i1C, i20, i24; float f28; uint8_t unk2C[4]; } M1Slot182;
typedef struct M1Ent182 { uint8_t unk00[0x10]; M1Slot182 *slot10; } M1Ent182;
typedef struct M1Snd182 { uint8_t unk00[0x10]; M1Ent182 ent10[16]; M1Slot182 slots150[16]; } M1Snd182;
void a5b_TimerInit(M1Snd182 *s);
void a5b_SlotClear(M1Ent182 *e);
void a5b_SlotListInit(M1Snd182 *s, int n, M1Ent182 *e);

/* 0x5CAF0: reset a sound bank: 16 slots back to defaults (scale 1, levels 0x80), each linked to its entry, then rebuild the free list. */
void m1_SndBankInit05CAF0(M1Snd182 *s) {
    M1Ent182 *e; M1Slot182 *sl; int n;
    if (s == 0) return;
    a5b_TimerInit(s);
    e = s->ent10; sl = s->slots150;
    for (n = 16; n != 0; n--, e++, sl++) {
        sl->f8 = 0.0f; sl->f4 = 0.0f; sl->f0 = 0.0f; sl->fC = 1.0f;
        sl->i10 = 0; sl->i14 = 0; sl->i18 = 0x80; sl->i1C = 0x80; sl->i20 = 0x80; sl->i24 = 0; sl->f28 = 0.0f;
        a5b_SlotClear(e);
        e->slot10 = sl;
    }
    a5b_SlotListInit(s, 16, s->ent10);
}
