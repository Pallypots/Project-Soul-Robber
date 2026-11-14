/* Area m1, file 160: more enemy hop states. Names inferred. */
#include <stdint.h>

typedef struct M1Rg160 { uint8_t unk00[0x50]; uint32_t f50; } M1Rg160;
typedef struct M1Ob160 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; } M1Ob160;
typedef struct M1Ai160 {
    uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x2B]; uint32_t flags4C; uint8_t unk50[0x24]; float t74;
    uint8_t unk78[0x278 - 0x78]; M1Rg160 *rig278;
} M1Ai160;
typedef struct M1St160 { int32_t s0; uint8_t unk04[0xC]; float t10; float t14; float t18; float t1C; } M1St160;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
void m1_AiSetState1456E0(M1Ob160 *o, M1Ai160 *e, int a, int b);
void sub_00156180(M1Rg160 *r, float f, int a, int b, float t);
void m1_AiSway1561D0(void *r, float a, float b);
M1St160 *m1_Quest113400(M1Ai160 *e, int k);

/* 0x148950: hop away with a sway; the strong variant hops higher and turns faster. */
void m1_AiHopAway148950(M1Ob160 *o, M1Ai160 *e) {
    M1Rg160 *r = e->rig278; M1St160 *s; float t; volatile float k = 2.0f;
    if (e->b20 & 1) {
        m1_AiSetState1456E0(o, e, 2, 0);
        sub_00156180(r, m1_frameRate42C85C * 20.0f * 1.39999998f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0279252697f * k;
        s = m1_Quest113400(e, 1);
        s->t10 = 0.279252678f;
        s->t14 = -0.279252678f;
    } else {
        m1_AiSetState1456E0(o, e, 1, 0);
        sub_00156180(r, m1_frameRate42C85C * 20.0f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0279252697f;
        s = m1_Quest113400(e, 1);
        s->t10 = 0.34906587f;
        s->t14 = -0.34906587f;
    }
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
    m1_AiSway1561D0(r, -8.0f, m1_frameRate42C85C * 10.0f);
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    r->f50 |= 0x100;
    e->t74 = 5.0f;
}

/* 0x148DD0: backflip away with a sway (states 3/4); the strong variant flips higher and spins faster. */
void m1_AiFlipAway148DD0(M1Ob160 *o, M1Ai160 *e) {
    M1Rg160 *r = e->rig278; M1St160 *s; float t; volatile float k = 2.0f;
    if (e->b20 & 1) {
        m1_AiSetState1456E0(o, e, 4, 0);
        sub_00156180(r, m1_frameRate42C85C * -28.0f * 1.39999998f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0139626348f * k;
        s = m1_Quest113400(e, 1);
        s->t10 = 0.837758064f;
        s->t14 = -0.837758064f;
    } else {
        m1_AiSetState1456E0(o, e, 3, 0);
        sub_00156180(r, m1_frameRate42C85C * -28.0f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0139626348f;
        s = m1_Quest113400(e, 1);
        s->t10 = 1.04719758f;
        s->t14 = -1.04719758f;
    }
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
    m1_AiSway1561D0(r, -12.0f, m1_frameRate42C85C * 10.0f);
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    r->f50 |= 0x100;
}

typedef struct M1Rg160b { uint8_t unk00[0x50]; uint32_t f50; uint8_t unk54[0x1C]; float f70; } M1Rg160b;

/* 0x14D2E0: knocked-back hop (state 0x41) with a sway; the strong variant hops higher and turns faster. */
void m1_AiKnockHop214D2E0(M1Ob160 *o, M1Ai160 *e) {
    M1Rg160b *r = (M1Rg160b *)e->rig278; M1St160 *s; float t; volatile float k = 2.0f;
    if (e->b20 & 1) {
        m1_AiSetState1456E0(o, e, 0x41, 0);
        sub_00156180((M1Rg160 *)r, m1_frameRate42C85C * 20.0f * 1.39999998f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0279252697f * k;
        s = m1_Quest113400(e, 1);
        s->t10 = 0.279252678f;
        s->t14 = -0.279252678f;
    } else {
        m1_AiSetState1456E0(*(M1Ob160 *volatile *)&o, e, 0x41, 0);
        sub_00156180((M1Rg160 *)r, m1_frameRate42C85C * 20.0f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0279252697f;
        s = m1_Quest113400(e, 1);
        s->t10 = 0.34906587f;
        s->t14 = -0.34906587f;
    }
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
    m1_AiSway1561D0(r, -8.0f, m1_frameRate42C85C * 10.0f);
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    r->f50 |= 0x40;
    e->t74 = 5.0f;
    r->f70 = 1.0f;
    r->f50 |= 0x200000;
}

typedef struct M1Rg160c {
    uint8_t unk00[4]; float f4; float f8; float fC; float f10; uint8_t unk14[0x10]; float f24; float f28; float f2C; float f30;
    uint8_t unk34[4]; void *x38; uint8_t unk3C[4]; uint32_t f40; uint8_t unk44[0xC]; float f50;
} M1Rg160c;
typedef struct M1Ai160c {
    uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x2B]; uint32_t flags4C; uint8_t unk50[0xA8];
    int32_t xF8; uint8_t unkFC[8]; void *x104; uint8_t unk108[0x278 - 0x108]; M1Rg160c *rig278;
} M1Ai160c;
extern void *g_playerObj;
void m1_AiTrail147FD0(void *p, int k);

/* 0x157F80: knocked-back leap toward the player (state 0x41); strong variant leaps higher and spins faster. */
void m1_AiKnockLeap157F80(M1Ob160 *o, M1Ai160c *e) {
    M1Rg160c *r = e->rig278; M1St160 *s; float t, c; uint32_t f; volatile float k = 2.0f;
    m1_AiSetState1456E0(o, (M1Ai160 *)e, 0x41, 0);
    r->f4 = -5.0f;
    r->f8 = m1_frameRate42C85C * 10.0f;
    c = m1_frameTime42C858 * 0.00499999989f;
    if (e->b20 & 1) {
        r->f28 = 0.0f; r->f24 = 0.0f; r->f10 = 0.0f;
        r->f2C = 0.0f - m1_frameRate42C85C * 45.0f * k;
        r->f30 = 1.0f; r->fC = c;
        t = m1_frameTime42C858 * 0.052359879f * k;
    } else {
        r->f28 = 0.0f; r->f24 = 0.0f; r->f10 = 0.0f;
        r->f2C = 0.0f - m1_frameRate42C85C * 45.0f;
        r->f30 = 1.0f; r->fC = c;
        t = m1_frameTime42C858 * 0.052359879f;
    }
    s = m1_Quest113400((M1Ai160 *)e, 1);
    s->t10 = 0.0872664675f;
    s->t14 = -0.0872664675f;
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    r->f40 |= 0x200;
    r->f50 = 300.0f;
    e->x104 = g_playerObj;
    e->xF8 = 1;
    f = r->f40 | 0x80;
    r->f40 = f;
    if (f & 0x1000) { r->f40 = f & ~0x1000u; m1_AiTrail147FD0(r->x38, 3); }
}

/* 0x157880: leap toward the player; strong variant (state 2) leaps higher and spins faster than state 1. */
void m1_AiLeap2157880(M1Ob160 *o, M1Ai160c *e) {
    M1Rg160c *r = e->rig278; M1St160 *s; float t; uint32_t f; volatile float k = 2.0f;
    if (e->b20 & 1) {
        m1_AiSetState1456E0(o, (M1Ai160 *)e, 2, 0);
        r->f28 = 0.0f; r->f24 = 0.0f; r->f10 = 0.0f;
        r->f2C = 0.0f - m1_frameRate42C85C * 35.0f * k;
        r->f30 = 1.0f;
        r->fC = m1_frameTime42C858 * 0.00499999989f;
        t = m1_frameTime42C858 * 0.0349065848f * k;
    } else {
        m1_AiSetState1456E0(o, (M1Ai160 *)e, 1, 0);
        r->f28 = 0.0f; r->f24 = 0.0f; r->f10 = 0.0f;
        r->f2C = 0.0f - m1_frameRate42C85C * 35.0f;
        r->f30 = 1.0f;
        r->fC = m1_frameTime42C858 * 0.00499999989f;
        t = m1_frameTime42C858 * 0.0349065848f;
    }
    s = m1_Quest113400((M1Ai160 *)e, 1);
    s->t10 = 0.0872664675f;
    s->t14 = -0.0872664675f;
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    r->f40 |= 0x200;
    r->f50 = 300.0f;
    e->x104 = g_playerObj;
    e->xF8 = 1;
    f = r->f40 | 0x80;
    r->f40 = f;
    if (f & 0x1000) { r->f40 = f & ~0x1000u; m1_AiTrail147FD0(r->x38, 3); }
}

typedef struct M1Ob160d { uint8_t unk00[0x108]; uint8_t v108[4]; float f10C; } M1Ob160d;
typedef struct M1Ai160d { uint8_t unk00[0x58]; int32_t n58; float t5C; } M1Ai160d;
typedef struct M1Q160d { uint8_t unk00[0x10]; float f10; } M1Q160d;
void *sub_0001D0F0(void *o, int b);
void sub_001AD940(void *m);
void sub_001AD8B0(void *d, void *s, float a);
void sub_0001EF00(M1Ob160d *o, void *v);
M1Q160d *sub_001133E0(M1Ai160d *e, int k);
void sub_0001D700(M1Ob160d *o);
void sub_000ED780(void *o);

/* 0x17B7A0: object pops up: tilt it upright over time while it shrinks back from double size, then remove it. */
void m1_ObjPopUp17B7A0(M1Ob160d *o, M1Ai160d *e) {
    void *m; volatile float k = 2.0f;
    switch (e->n58) {
    case 0:
        m = sub_0001D0F0(o, 0);
        sub_001AD940(m);
        if (e->t5C >= 1.0f) {
            o->f10C = 0.0f;
            sub_0001EF00(o, o->v108);
            sub_001133E0(e, 0)->f10 = 0.0f;
            sub_0001D700(o);
            e->n58++;
            return;
        }
        sub_001AD8B0(m, m, e->t5C * 1.57079637f);
        o->f10C = (1.0f - e->t5C) * k;
        sub_0001EF00(o, o->v108);
        return;
    case 1:
        if (e->t5C >= 1.5f) sub_000ED780(o);
        return;
    }
}
