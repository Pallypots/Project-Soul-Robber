/* Area m1, file 159: enemy hop states. Names inferred. */
#include <stdint.h>

typedef struct M1Rg159 { uint8_t unk00[0x50]; uint32_t f50; } M1Rg159;
typedef struct M1Ob159 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; } M1Ob159;
typedef struct M1Ai159 {
    uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x2B]; uint32_t flags4C; uint8_t unk50[0xA8];
    int32_t xF8; uint8_t unkFC[8]; void *x104; uint8_t unk108[0x278 - 0x108]; M1Rg159 *rig278;
} M1Ai159;
typedef struct M1St159 { int32_t s0; uint8_t unk04[0xC]; float t10; float t14; float t18; float t1C; } M1St159;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
extern void *g_playerObj;
void m1_AiSetState1456E0(M1Ob159 *o, M1Ai159 *e, int a, int b);
void sub_00156180(M1Rg159 *r, float f, int a, int b, float t);
M1St159 *m1_Quest113400(M1Ai159 *e, int k);

/* 0x14C6C0: start a hop toward the player (bigger and faster for the strong variant). */
void m1_AiHop14C6C0(M1Ob159 *o, M1Ai159 *e) {
    M1Rg159 *r = e->rig278; M1St159 *s; float t; volatile float k = 2.0f;
    if (e->b20 & 1) {
        m1_AiSetState1456E0(o, e, 2, 0);
        sub_00156180(r, m1_frameRate42C85C * 24.0f * 1.39999998f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0558505394f * k;
        s = m1_Quest113400(e, 1);
        s->t10 = 0.139626339f;
        s->t14 = -0.139626339f;
    } else {
        m1_AiSetState1456E0(o, e, 1, 0);
        sub_00156180(r, m1_frameRate42C85C * 24.0f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0558505394f;
        s = m1_Quest113400(e, 1);
        s->t10 = 0.174532935f;
        s->t14 = -0.174532935f;
    }
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
    o->fC &= ~0xE0u;
    o->f10 |= 0x105;
    e->flags4C |= 0x70;
    e->x104 = g_playerObj;
    e->xF8 = 1;
    r->f50 |= 0x40;
}

typedef struct M1Rg159b { uint8_t unk00[0xC]; float fC; float f10; uint8_t unk14[0x10]; float f24; float f28; float f2C; float f30; uint8_t unk34[0xC]; uint32_t f40; } M1Rg159b;
typedef struct M1Ai159b { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x278 - 0x50]; M1Rg159b *rig278; } M1Ai159b;

/* 0x156F90: enemy bounce-back: upward kick, slow spin, state 4. */
void m1_AiBounce156F90(M1Ob159 *o, M1Ai159b *e) {
    M1Rg159b *r = e->rig278; M1St159 *s; float t; volatile float k = 2.0f; float kk;
    m1_AiSetState1456E0(o, (M1Ai159 *)e, 4, 0);
    kk = k;
    r->f28 = 0.0f; r->f24 = 0.0f; r->f10 = 0.0f;
    r->fC = m1_frameTime42C858 * 0.00499999989f;
    r->f2C = 0.0f - m1_frameRate42C85C * -30.0f * kk;
    r->f30 = 1.0f;
    o->f10 |= 0x20;
    e->flags4C &= ~0x70u;
    r->f40 |= 0x200;
    t = m1_frameTime42C858 * 0.0349065848f * kk;
    s = m1_Quest113400((M1Ai159 *)e, 1);
    s->t10 = 0.34906587f;
    s->t14 = -0.34906587f;
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
}

typedef struct M1Rg159c {
    uint8_t unk00[0xC]; float fC; float f10; uint8_t unk14[0x10]; float f24; float f28; float f2C; float f30;
    uint8_t unk34[0xC]; uint32_t f40; uint8_t unk44[0x10]; float f54; uint8_t unk58[0xC]; float v64[4];
} M1Rg159c;
typedef struct M1Ai159c { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x278 - 0x50]; M1Rg159c *rig278; } M1Ai159c;
int m1_AiArc1561F0(M1Ob159 *o, M1Ai159c *e, float *v, int k);

/* 0x156CF0: low leap toward the player; height and turn speed depend on the distance. */
void m1_AiLowLeap156CF0(M1Ob159 *o, M1Ai159c *e) {
    M1Rg159c *r = e->rig278; M1St159 *s; float d, a, t;
    m1_AiSetState1456E0(o, (M1Ai159 *)e, 1, 0);
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    r->f40 |= 0x200;
    d = e->rig278->f54 - 100.0f;
    if (d >= 0.0f) d *= 0.00249999994f; else d *= 0.00499999989f;
    r->f2C = 0.0f - m1_frameRate42C85C * 25.0f * (d + 1.0f);
    r->f28 = 0.0f; r->f24 = 0.0f; r->f30 = 1.0f; r->f10 = 0.0f;
    r->fC = m1_frameTime42C858 * 0.00499999989f;
    if (m1_AiArc1561F0(o, e, r->v64, 0) != 0) r->f40 &= ~1u; else r->f40 |= 1;
    a = r->f54 >= 100.0f ? 50.0f : 40.0f;
    t = m1_frameTime42C858 * 0.052359879f;
    s = m1_Quest113400((M1Ai159 *)e, 2);
    if (a != -1.0f) s->t10 = a;
    if (t != -1.0f) s->t14 = t;
    s->t18 = 0.0f; s->t1C = 0.0f;
}

typedef struct M1Rg159d { uint8_t unk00[0x38]; void *x38; uint8_t unk3C[0x14]; uint32_t f50; } M1Rg159d;
typedef struct M1Ai159d {
    uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x2B]; uint32_t flags4C; uint8_t unk50[0x24]; float t74;
    uint8_t unk78[0x278 - 0x78]; M1Rg159d *rig278;
} M1Ai159d;
void m1_AiSway1561D0(void *r, float a, float b);
void sub_0015A490(void *p, int k);

/* 0x14E0A0: knocked-back hop (state 0x41) with a sway; the strong variant hops higher and turns faster. */
void m1_AiKnockHop14E0A0(M1Ob159 *o, M1Ai159d *e) {
    M1Rg159d *r = e->rig278; M1St159 *s; float f, t; volatile float k = 2.0f;
    m1_AiSetState1456E0(o, (M1Ai159 *)e, 0x41, 0);
    m1_AiSway1561D0(r, -7.0f, m1_frameRate42C85C * 10.0f);
    f = m1_frameRate42C85C * 32.0f;
    if (e->b20 & 1) {
        sub_00156180((M1Rg159 *)r, f * 1.39999998f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0698131695f * k;
    } else {
        sub_00156180((M1Rg159 *)r, f, 0, 0, m1_frameTime42C858 * 0.00300000003f);
        t = m1_frameTime42C858 * 0.0698131695f;
    }
    s = m1_Quest113400((M1Ai159 *)e, 1);
    s->t10 = 0.0872664675f;
    s->t14 = -0.0872664675f;
    if (t != -1.0f) s->t18 = t;
    s->t1C = 0.0f;
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    e->t74 = 5.0f;
    if (r->f50 & 0x400) { r->f50 &= ~0x400u; sub_0015A490(r->x38, 3); }
}

