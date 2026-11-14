/* Area m1, file 155: enemy part setup. Names inferred. */
#include <stdint.h>

typedef struct M1Part155 { int32_t id; float f[4]; int32_t z; } M1Part155;
typedef struct M1Ob155 { uint8_t unk00[0x20]; void *x20; } M1Ob155;
typedef struct M1Ai155 { uint8_t unk00[0x278]; uint8_t *rig278; } M1Ai155;
void m1_PartAttach03C2D0(void *slot, void *mdl, M1Part155 *p);

/* 0x120720: attach the four body-part trackers (ids 9..12) to an enemy. */
void m1_AiParts120720(M1Ob155 *o, M1Ai155 *e) {
    M1Part155 p[4]; M1Part155 *q; uint8_t *s; int n;
    p[0].z = 0; p[1].z = 0; p[2].z = 0; p[3].z = 0;
    p[0].id = 9;  p[0].f[0] = 0.0f; p[0].f[1] = 0.100000001f; p[0].f[2] = 0.949999988f; p[0].f[3] = 0.100000001f;
    p[1].id = 10; p[1].f[0] = 0.0f; p[1].f[1] = 0.100000001f; p[1].f[2] = 0.949999988f; p[1].f[3] = 0.100000001f;
    p[2].id = 11; p[2].f[0] = 0.0f; p[2].f[1] = 0.100000001f; p[2].f[2] = 0.949999988f; p[2].f[3] = 0.100000001f;
    p[3].id = 12; p[3].f[0] = 0.0f; p[3].f[1] = 0.100000001f; p[3].f[2] = 0.949999988f; p[3].f[3] = 0.100000001f;
    for (q = p, s = e->rig278 + 0x378, n = 4; n != 0; n--, q++, s += 0xC0)
        m1_PartAttach03C2D0(s, o->x20, q);
}

typedef struct M1Rg155 {
    uint8_t unk00[0xC]; float fC; float f10; uint8_t unk14[0x10]; float f24; float f28; float f2C; float f30;
    uint8_t unk34[0xC]; uint32_t f40; uint8_t unk44[0x10]; float f54; uint8_t unk58[0xC]; float v64[4];
} M1Rg155;
typedef struct M1Ob155b { uint8_t unk00[0x10]; uint32_t f10; } M1Ob155b;
typedef struct M1Ai155b { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x278 - 0x50]; M1Rg155 *rig278; } M1Ai155b;
typedef struct M1St155 { int32_t s0; uint8_t unk04[0xC]; float t10; float t14; float t18; float t1C; } M1St155;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
void m1_AiSetState1456E0(M1Ob155b *o, M1Ai155b *e, int a, int b);
int  m1_AiArc1561F0(M1Ob155b *o, M1Ai155b *e, float *v, int k);
M1St155 *m1_Quest113400(M1Ai155b *e, int k);

/* 0x156E50: leap toward the player; jump height grows with distance past 100 units. */
void m1_AiLeap156E50(M1Ob155b *o, M1Ai155b *e) {
    M1Rg155 *r = e->rig278; M1St155 *s; float d, f, t; volatile float k = 2.0f; float kk;
    m1_AiSetState1456E0(o, e, 2, 0);
    o->f10 |= 0x20;
    e->flags4C |= 0x70;
    r->f40 |= 0x200;
    d = e->rig278->f54 - 100.0f;
    if (d >= 0.0f) d *= 0.00249999994f; else d *= 0.00499999989f;
    kk = k;
    f = m1_frameRate42C85C * 25.0f * kk;
    r->f2C = 0.0f - f * (d + 1.0f);
    r->f28 = 0.0f; r->f24 = 0.0f; r->f30 = 1.0f; r->f10 = 0.0f;
    r->fC = m1_frameTime42C858 * 0.00499999989f;
    if (m1_AiArc1561F0(o, e, r->v64, 0) != 0) r->f40 &= ~1u; else r->f40 |= 1;
    t = m1_frameTime42C858 * 0.052359879f * kk;
    s = m1_Quest113400(e, 2);
    s->t10 = 50.0f;
    if (t != -1.0f) s->t14 = t;
    s->t18 = 0.0f; s->t1C = 0.0f;
}

typedef struct M1St155c { uint32_t f0; } M1St155c;
typedef struct M1Ai155c { uint8_t unk00[0x60]; int32_t n60; uint8_t unk64[0x10]; M1St155c *st74; } M1Ai155c;
typedef struct M1Fl155 {
    uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0xC]; void *mdl20; uint8_t unk24[0x2C];
    float a50; float a54; uint8_t unk58[8]; float pos60[4]; uint8_t unk70[0x10]; float v80[4];
} M1Fl155;
int  sub_00087500(void);
int  sub_000CF6C0(void);
void sub_00189DA0(M1Fl155 *o, M1Ai155c *e, int k);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_001AD940(float (*m)[4]);
void sub_001AD8B0(float (*d)[4], float (*s)[4], float a);
void sub_001AD8E0(float (*d)[4], float (*s)[4], float a);
void sub_001ADA40(void *d, float (*m)[4]);

/* 0x18D8A0: move a flying projectile: wrap its angles, advance, rebuild its matrix, drop it when it flies off. */
void m1_ShotFly18D8A0(M1Fl155 *o, M1Ai155c *e) {
    M1St155c *s = e->st74; float m[4][4];
    if (sub_00087500() != 0 && e->n60 != 1) { sub_00189DA0((M1Fl155 *)*(void *volatile *)&o, e, 1); return; }
    if (!(s->f0 & 2)) {
        if (sub_000CF6C0() > 0) o->f10 |= 1; else o->f10 &= ~1u;
    }
    if (o->a50 > 3.14159274f) o->a50 -= 6.28318548f;
    if (-3.14159274f > o->a50) o->a50 += 6.28318548f;
    if (o->a54 > 3.14159274f) o->a54 -= 6.28318548f;
    if (-3.14159274f > o->a54) o->a54 += 6.28318548f;
    sub_001ADAF0(o->pos60, o->pos60, o->v80);
    o->pos60[3] = 1.0f;
    sub_001AD940(m);
    sub_001AD8B0(m, m, o->a50);
    sub_001AD8E0(m, m, o->a54);
    sub_001ADA40(o->mdl20, m);
    if (!(o->pos60[1] > 200.0f)) return;
    sub_00189DA0(o, e, 1);
}

typedef struct M1Anm155d { uint8_t unk00[4]; } M1Anm155d;
typedef struct M1Obj155d { uint8_t unk00[0x30]; M1Anm155d *anim30; uint8_t unk34[0x3C]; float pos70[4]; } M1Obj155d;
typedef struct M1Fly155d { uint8_t unk00[0x58]; int32_t n58; uint8_t unk5C[0x18]; float t74; uint8_t unk78[0x10]; float v88[4]; } M1Fly155d;
int  sub_000833E0(void *a);
void sub_000ED780(void *o);
void sub_000F5D40(float *d, const void *s);
void sub_001ADB60(float *d, const float *s, float t);

/* 0x138A10: two-step pop-out then glide toward the saved spot; removes the object when time runs out. */
void m1_PopGlide138A10(M1Obj155d *o, M1Fly155d *s) {
    if (s->n58 < 2) {
        if (sub_000833E0(o->anim30) == 0) return;
        switch (s->n58) {
        case 0: sub_000ED780(o); return;
        case 1:
            s->t74 = 0.200000003f;
            sub_000F5D40(s->v88, o->pos70);
            s->n58++;
            return;
        }
        return;
    }
    if (0.0f >= s->t74) { sub_000ED780(*(M1Obj155d *volatile *)&o); return; }
    sub_001ADB60(o->pos70, s->v88, s->t74 * 5.0f);
}

typedef struct M1Fx155e { uint8_t unk00[0xC]; int32_t kind0C; } M1Fx155e;
typedef struct M1Act155e {
    uint8_t unk00[0xD8]; int32_t state0D8; uint8_t unkDC[0xEC - 0xDC]; uint32_t ec;
    uint8_t unkF0[0x150 - 0xF0]; uint32_t flags150; uint8_t unk154[0x1B8 - 0x154]; int32_t mode1B8;
    uint8_t unk1BC[0x620 - 0x1BC]; M1Fx155e *fx620;
} M1Act155e;
M1Fx155e *m1_FxDrop0D00A0(M1Act155e *o, M1Fx155e *fx);
M1Fx155e *m1_FxMake0D0030(M1Act155e *o, int kind);

/* 0xCA010: keep the actor's aura effect in step with its charge state. */
void m1_ActAura0CA010(M1Act155e *o) {
    int k;
    if (o->mode1B8 != 0 || !(o->flags150 & 0x400)) {
        if (o->fx620 != 0) o->fx620 = m1_FxDrop0D00A0(o, o->fx620);
        return;
    }
    switch (o->state0D8) {
    case 0x25: k = 0x1C; break;
    case 0x26: k = 0x1D; break;
    case 0x27: k = 0x1E; break;
    default:
        if (o->fx620 != 0) o->fx620 = m1_FxDrop0D00A0(*(M1Act155e *volatile *)&o, o->fx620);
        return;
    }
    if (o->ec & 0x40) k += 3;
    if (o->fx620 != 0) {
        if (o->fx620->kind0C == k) return;
        o->fx620 = m1_FxDrop0D00A0(o, o->fx620);
        o->fx620 = m1_FxMake0D0030(*(M1Act155e *volatile *)&o, k);
        return;
    }
    o->fx620 = m1_FxMake0D0030(o, k);
}

typedef struct M1Ctx155f { uint8_t unk00[8]; int32_t kind08; } M1Ctx155f;
typedef struct M1Pl155f { uint8_t unk00[0x8C]; void *o8C; void *o90; uint8_t unk94[0xBC - 0x94]; int16_t w0BC; } M1Pl155f;
typedef struct M1Sys155f { uint8_t unk00[0x324]; int32_t on324; } M1Sys155f;
typedef struct M1Hit155f { int32_t x0; int32_t x4; int32_t x8; int16_t idC; int16_t idE; } M1Hit155f;
M1Ctx155f *sub_000E23F0(int a, int b);
M1Pl155f  *sub_00100110(void);
M1Pl155f  *sub_000FBAF0(void);
M1Pl155f  *sub_000FE3D0(void);
M1Sys155f *sub_000E0770(void);
int  m1_HitCheck0F6BC0(M1Pl155f *p, M1Hit155f *h);
void sub_000F3D10(void *a, M1Pl155f *p, int k);
void sub_000E1060(void *o, int x, int y, int z);

static M1Pl155f *m1_Pick155(M1Ctx155f *c) {
    if (c != 0 && c->kind08 != 3) {
        if (c->kind08 == 4) return sub_00100110();
        if (c->kind08 == 5) return sub_000FBAF0();
    }
    return sub_000FE3D0();
}

/* 0xF6E20: move the hit context and the player to the hit position. */
void m1_HitWarp0F6E20(M1Hit155f *h) {
    M1Ctx155f *c = sub_000E23F0(h->idC, h->idE);
    M1Pl155f *p = m1_Pick155(c);
    if (sub_000E0770()->on324 != 0) {
        if (m1_HitCheck0F6BC0(p, h) == 0) return;
        if (p != 0) { sub_000F3D10(p->o8C, p, 1); p->w0BC = 0; }
        sub_000E1060(c, h->x0, h->x4, h->x8);
        sub_000E1060(p->o90, h->x0, h->x4, h->x8);
        return;
    }
    sub_000E1060(*(M1Ctx155f *volatile *)&c, h->x0, h->x4, h->x8);
    sub_000E1060((*(M1Pl155f *volatile *)&p)->o90, h->x0, h->x4, h->x8);
}
