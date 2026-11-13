/* Area m1, file 72: rig cleanups. Names inferred. */
#include <stdint.h>

typedef struct M1RigC2 { uint8_t unk00[0x20]; void *fx20; uint8_t unk24[0x34 - 0x24]; void *res34[4]; } M1RigC2;
typedef struct M1StepC2 {
    uint8_t unk000[0x6C];
    int32_t snd6C;             /* +0x6C */
    void   *res70;             /* +0x70 */
    uint8_t unk074[0x278 - 0x74];
    M1RigC2 *rig278;           /* +0x278 */
} M1StepC2;
void sub_0018B260(void *fx, const float *v);
int  sub_000ED780(void *o);
void sub_00033560(void *r);
void sub_00048250(int snd);
void sub_00033A70(void *r);

/* 0x00119F30: cleanup: releases the rig effect (+0x20: zero offset, 0xED780 must return 1
 * or it spins), frees the 4 rig resources at +0x34 (0x33560), stops the +0x6C sound and
 * frees the +0x70 resource; returns 1. */
int m1_RigCleanup119F30(void *o, M1StepC2 *h)
{
    M1RigC2 *r = h->rig278;
    float v[4];
    void **p;
    int n;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    if (r->fx20 != 0) {
        sub_0018B260(r->fx20, v);
        if (sub_000ED780(r->fx20) != 1)
            for (;;) ;
        r->fx20 = 0;
    }
    for (p = r->res34, n = 4; n != 0; n--, p++) {
        if (*p != 0) {
            sub_00033560(*p);
            *p = 0;
        }
    }
    if (h->snd6C >= 0) {
        sub_00048250(h->snd6C);
        h->snd6C = -1;
    }
    if (h->res70 != 0) {
        sub_00033A70(h->res70);
        h->res70 = 0;
    }
    return 1;
}

typedef struct M1Pos60c { uint8_t unk00[0x60]; float pos60[4]; } M1Pos60c;
typedef struct M1Burst {
    uint8_t unk000[0x60];
    float   pos60[4];          /* +0x60 */
    uint8_t unk070[0x128 - 0x70];
    uint8_t b128;              /* +0x128 */
} M1Burst;
typedef struct M1BurstSt { uint8_t unk00[0x6C]; float t6C; } M1BurstSt;
extern M1Pos60c *g_playerObj;
float sub_001B2770(const float *a, const float *b);
void  sub_000C56B0(void *o);
void  sub_00189DA0(void *o, void *h, int next);
void *sub_000C46A0(float a, float rate, float b, const float *pos, float *v0, float *v1);
void  sub_000C4D30(void *o, int n, float k, void *fx);

/* 0x0018EBF0: when o is not busy (+0x128 bits 6), the timer +0x6C is under 4 and the player
 * is within 80, does 0xC56B0; otherwise goes to state 7 (0x189DA0) and starts a burst at
 * o's position (0xC46A0(12.5, 1/60, 2.5)) attached with 0xC4D30(10, 10.0). */
void m1_Burst18EBF0(M1Burst *o, M1BurstSt *h)
{
    float v[4];
    if (!(o->b128 & 6) && !(h->t6C >= 4.0f) &&
        !(sub_001B2770(o->pos60, g_playerObj->pos60) >= 80.0f)) {
        sub_000C56B0(o);
        return;
    }
    sub_00189DA0(o, h, 7);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    sub_000C4D30(o, 10, 10.0f, sub_000C46A0(12.5f, 0.016666668f, 2.5f, o->pos60, v, v));
}

typedef struct M1RigR2 { uint8_t unk00[4]; uint32_t flags04; uint8_t unk08[0xC]; uint8_t wait14[4]; } M1RigR2;
typedef struct M1StepR2 {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[8];
    int32_t state58;           /* +0x58 */
    uint8_t unk05C[0x278 - 0x5C];
    M1RigR2 *rig278;           /* +0x278 */
} M1StepR2;
typedef struct M1CmdR2 { uint8_t unk00[0x10]; int32_t f10, f14, f18; } M1CmdR2;
int      aab_Rand(void);
void     sub_00113090(void *o, void *h, int next);
M1CmdR2 *sub_00113430(void *h, int v);
void     sub_00113CB0(void *wait, float t, int v);

/* 0x001428D0: next state 0x18 with command 2 = (4, 3, 0xC4) when rig flag 2 is clear and h
 * byte +0x20 bit 0 is set, else state 0x15; clears h +0x4C bit 0x10, starts the rig wait
 * (0x113CB0) at a whole number of 70 + (rand % 4001) * 0.01; a pending rig flag 2 is
 * cleared and sets +0x58 = 1. */
void m1_RigPick1428D0(void *o, M1StepR2 *h)
{
    M1RigR2 *r = h->rig278;
    M1CmdR2 *c;
    uint32_t f;
    float t;
    if (!(r->flags04 & 2) && (h->b20 & 1)) {
        sub_00113090(o, h, 0x18);
        c = sub_00113430(h, 2);
        c->f10 = 4;
        c->f14 = 3;
        c->f18 = 0xC4;
    } else {
        sub_00113090(o, h, 0x15);
    }
    h->flags4C &= ~0x10u;
    t = (float)(aab_Rand() % 4001) * 0.01f + 70.0f;
    sub_00113CB0(h->rig278->wait14, (float)(int)t, 0);
    f = r->flags04;
    if (f & 2) {
        r->flags04 = f & ~2u;
        h->state58 = 1;
    }
}

typedef struct M1Glow3 {
    uint8_t unk00[0x50];
    float   v50[4];            /* +0x50 */
    float   pos60[3];          /* +0x60 */
    float   w6C;               /* +0x6C */
    float   size70;            /* +0x70 */
    uint8_t unk74[0xA0 - 0x74];
    float   ofsA0[3];          /* +0xA0 */
} M1Glow3;
typedef struct M1RigFx { uint8_t unk00[0x20]; void *fx20; } M1RigFx;
typedef struct M1GlowSt3 { uint8_t unk000[0x74]; float t74; uint8_t unk078[0x278 - 0x78]; M1RigFx *rig278; } M1GlowSt3;
void sub_00113AA0(void *o, void *h);
void sub_00113040(void *o, void *h, int next);
void sub_000EE660(void *fx, float a);
void sub_000C7540(void *o, float a, float size, const float *pos, const float *v);

/* 0x00143570: once the timer +0x74 is no longer positive ends the step (0x113AA0), sets
 * the rig effect's alpha to 1 (0xEE660) and goes to state 5; else draws the glow at
 * position + offset with size +0x70 (0xC7540). */
void m1_Glow143570(M1Glow3 *o, M1GlowSt3 *h)
{
    float p[4];
    void *fx;
    if (0.0f >= h->t74) {
        sub_00113AA0(o, h);
        fx = h->rig278->fx20;
        if (fx != 0)
            sub_000EE660(fx, 1.0f);
        sub_00113040(o, h, 5);
        return;
    }
    p[0] = o->pos60[0] + o->ofsA0[0];
    p[1] = o->pos60[1] + o->ofsA0[1];
    p[2] = o->pos60[2] + o->ofsA0[2];
    p[3] = o->w6C;
    sub_000C7540(o, 1.0f, o->size70, p, o->v50);
}
