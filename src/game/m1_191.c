/* Area m1, file 191: AI state entries (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1AiY191 { uint8_t unk00[0x18]; uint32_t i18; uint8_t unk1C[4]; float f20, f24, f28, f2C; } M1AiY191;
typedef struct M1AiL191 { uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x257]; M1AiY191 *st278; } M1AiL191;
extern float m1_frameRate42C85C;
int m1_AiSetState1456E0(void *a, M1AiL191 *e, int s, int t);
int aab_Rand(void);

/* 0x188390: enter the hop-back state (variant 1 when flagged): jump back 80 and up by 70 scaled by a random 0.8..1.2. */
void m1_AiHopBack188390(void *a, M1AiL191 *e) {
    M1AiY191 *s = e->st278, *t; float r;
    if (e->b20 & 1) { int volatile v1 = 1; m1_AiSetState1456E0(a, e, v1, 0); }
    else { int volatile v2 = 0; m1_AiSetState1456E0(a, e, v2, 0); }
    r = (float)aab_Rand() * 3.05185094e-05f * 0.4f - 0.2f + 1.0f;
    t = e->st278;
    t->f24 = m1_frameRate42C85C * -80.0f;
    t->f20 = 0.0f;
    t->f2C = 1.0f;
    t->f28 = 0.0f - m1_frameRate42C85C * 70.0f * r;
    s->i18 |= 0x800;
}

typedef struct M1Up191 { uint8_t unk00[0x20]; float *mtx20; } M1Up191;
void a3c_VecCopy(float *dst, const float *src);
void r4e_VecNormalize3(float *dst, const float *src);
void r4e_VecCross3(float *dst, const float *a, const float *b);

/* 0x187EA0: enter the stand-up state (variant 1 when flagged) and level the object: flatten its forward axis, set up to +Y and rebuild the side axis. */
void m1_AiStandUp187EA0(M1Up191 *a, M1AiL191 *e) {
    float up[4]; M1AiY191 *t; float *m;
    up[0] = 0.0f; up[1] = 1.0f; up[2] = 0.0f; up[3] = 0.0f;
    if (e->b20 & 1) { int volatile v1 = 1; m1_AiSetState1456E0(a, e, v1, 0); }
    else { int volatile v2 = 0; m1_AiSetState1456E0(a, e, v2, 0); }
    t = e->st278;
    t->f28 = 0.0f; t->f24 = 0.0f; t->f20 = 0.0f; t->f2C = 1.0f;
    a->mtx20[1] = 0.0f;
    r4e_VecNormalize3(a->mtx20, a->mtx20);
    a3c_VecCopy(a->mtx20 + 4, up);
    m = a->mtx20;
    r4e_VecCross3(m + 8, m, m + 4);
}

typedef struct M1GrS191 { uint32_t i0; } M1GrS191;
typedef struct M1Gr191 { uint8_t unk00[0x10]; uint32_t i10; uint8_t unk14[0x5C]; float scale70[4]; } M1Gr191;
typedef struct M1GrE191 { uint8_t unk00[0x54]; int32_t i54; uint8_t unk58[4]; float t5C; uint8_t unk60[0x14]; M1GrS191 *st74; } M1GrE191;
void sub_00035D80(M1Gr191 *o, int a, int b);
void sub_000ED780(M1Gr191 *o);

/* 0x168460: grow-in state: on entry show the object and start a 0.5 timer; each tick set its uniform scale to twice the timer; finish when the timer goes negative. */
void m1_FxGrowIn168460(M1Gr191 *o, M1GrE191 *e) {
    M1GrS191 *s = e->st74;
    float v;
    switch (e->i54) {
    case 0:
        o->i10 |= 1;
        s->i0 = (s->i0 & ~0x18Cu) | 0x40;
        e->t5C = 0.5f;
        sub_00035D80(o, 1, 0);
        e->i54++;
    case 1:
        { float volatile k = 2.0f; v = e->t5C * k; }
        o->scale70[0] = v; o->scale70[1] = v; o->scale70[2] = v; o->scale70[3] = 1.0f;
        if (0.0f > e->t5C) sub_000ED780(o);
        break;
    }
}

typedef struct M1FdS191 { uint8_t unk00[0x4C]; void *p4C; } M1FdS191;
typedef struct M1FdE191 { uint8_t unk00[0x54]; int32_t i54; uint8_t unk58[4]; float t5C; uint8_t unk60[0x14]; M1FdS191 *st74; } M1FdE191;
void m1_AnimScale0EE6D0(void *o, float s);
void m1_FxTint034D30(void *t, float r, float g, float b, float a);

/* 0x16D500: fade-out state: start a 3-unit timer, scale the animation by timer/3 each tick, tint the attached light, and finish when the timer goes negative. */
void m1_FxFadeOut16D500(void *o, M1FdE191 *e) {
    M1FdS191 *s;
    switch (e->i54) {
    case 0:
        e->t5C = 3.0f;
        e->i54 = 1;
    case 1:
        if (0.0f > e->t5C) sub_000ED780((M1Gr191 *)o);
        m1_AnimScale0EE6D0(o, e->t5C * 0.333333343f);
        s = e->st74;
        if (s != 0 && s->p4C != 0) m1_FxTint034D30(s->p4C, 1.0f, 1.0f, 1.0f, 0.99f);
        break;
    }
}
