/* Area m1, group 304: enter-attack states. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[8]; uint32_t f8; uint8_t _c[0x150 - 0xC]; float v150[4];
    float f160, f164, f168, f16c; void *p170; void *p174; } M1Ks304;
typedef struct { uint8_t _0[0xF8]; int32_t ff8; uint8_t _fc[8]; float v104[4];
    uint8_t _114[0x278 - 0x114]; M1Ks304 *s278; } M1Ka304;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x60 - 0x14]; uint8_t pos60[0x10]; } M1Ko304;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Kc304;

extern float m1_frameTime42C858, m1_frameRate42C85C;
int  b4c_Enter1456E0j(M1Ko304 *o, M1Ka304 *a, int st, int f);
void sub_0001D4E0f(M1Ko304 *o);
int  sub_001C7EE1(void);                                    /* rand */
int  sub_000494D0(int id, void *p, int f);
void r3b_KeyVec135C10(float *out, M1Ka304 *a, void *p, void *q);   /* regargs: a=ECX p=ESI q=EAX */
void sub_000F5D40(float *d, const float *s);
M1Kc304 *m1_Quest113400(M1Ka304 *a, int v);

/* 0x001365C0: enter the dash (move 2): rise at 30/s, sometimes play sound
   0x166, aim at the key point from the two targets, and start the 5-degree
   turn command (rates +/-0.1 degree). */
void m1_EnterDash1365C0(M1Ko304 *o, M1Ka304 *a)
{
    M1Ks304 *t = a->s278;
    M1Ks304 *s;
    M1Kc304 *c;
    float v[4];
    float z, w;

    if (b4c_Enter1456E0j(o, a, 2, 0) == 1)
        sub_0001D4E0f(o);
    s = a->s278;
    z = m1_frameRate42C85C * 30.0f;
    s->f164 = 0.0f;
    s->f160 = 0.0f;
    s->f168 = 0.0f - z;
    s->f16c = 1.0f;
    o->f10 |= 5;
    if (!(sub_001C7EE1() & 3))
        sub_000494D0(0x166, o->pos60, 0);
    r3b_KeyVec135C10(v, a, t->p170, t->p174);
    sub_000F5D40(t->v150, v);
    sub_000F5D40(a->v104, v);
    a->ff8 = 2;
    t->f8 |= 2;
    w = m1_frameTime42C858 * 0.0872664675f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.00174532935f;
    c->f14 = -0.00174532935f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
}

typedef struct { uint8_t _0[0x88]; float f88, f8c, f90; } M1Ls304;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x58 - 0x21]; int32_t st58;
    uint8_t _5c[0x278 - 0x5C]; M1Ls304 *s278; } M1La304;
typedef struct { uint8_t _0[0x30]; int32_t h30; } M1Lo304;

int32_t sub_000833E0(int32_t h);
void sub_00186470(M1Lo304 *o, M1La304 *a, int st);           /* regargs: o=EBX a=EDI */
void sub_00186470b(M1Lo304 *o, M1La304 *a, int st);

/* 0x00187610: landing step: when the clip ends go to state 2 (facing flag)
   or step 3; step 1 sets the target height 8 and climb rate 40/s; step 2
   waits for the height to reach it; step 3 goes to state 1. */
void m1_Land187610(M1Lo304 *o, M1La304 *a)
{
    M1Ls304 *s = a->s278;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) return;
        if (a->b20 & 1) {
            sub_00186470(o, a, 2);
            return;
        }
        a->st58 = 3;
        return;
    case 1:
        s->f8c = 8.0f;
        s->f90 = m1_frameRate42C85C * 40.0f;
        a->st58++;
    case 2:
        if (s->f8c == s->f88)
            a->st58++;
        return;
    case 3:
        sub_00186470b(o, a, 1);
        return;
    }
}

typedef struct { uint8_t _0[0x60]; float pos60[4]; } M1Po304;
typedef struct { float v[4]; float f10; } M1Pl304;
typedef struct { float v[4]; float x, y; } M1Pp304;

extern uint8_t m1_tgt41FEC0[];
void m1_TgtInfo0C4250(void *t, M1Pp304 *p, float *q);
int  sub_000CFFB0(void);
int  sub_000EE2B0(M1Pl304 *l, M1Pp304 *p, float *r);

/* 0x0018BB20: test o (radius 4 around its position) against the current
   target's screen rectangle; 0 when the target has no size or none is set.
   Regargs: o=EAX. */
int m1_TgtHit18BB20(M1Po304 *o)
{
    M1Pl304 l;
    M1Pp304 p;
    float q[4], r[4];

    sub_000F5D40(l.v, o->pos60);
    l.f10 = 4.0f;
    m1_TgtInfo0C4250(m1_tgt41FEC0, &p, q);
    p.x = q[0];
    p.y = q[1];
    if (p.x == 0.0f || p.y == 0.0f) return 0;
    if (sub_000CFFB0() == -1) return 0;
    return sub_000EE2B0(&l, &p, r);
}

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c;
    uint8_t _70[0xB8 - 0x70]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180; uint8_t _184[0x1D8 - 0x184]; float f1d8, f1dc;
} M1Es304;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[0x278 - 0x50]; M1Es304 *s278; } M1Ea304;
typedef struct { uint8_t _0[0x10]; uint32_t f10; } M1Eo304;

int  b4c_Enter1456E0l(M1Eo304 *o, M1Ea304 *a, int st, int f);
int  m1_AiSetState1456E0(M1Eo304 *o, M1Ea304 *a, int st, int f);
void sub_001ADA40(float *d, const float *m);
void sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */

/* 0x0012CC20: enter the idle hop (move 0): rise at 10/s with gravity -20,
   short pose blend. */
void m1_EnterIdleHop12CC20(M1Eo304 *o, M1Ea304 *a)
{
    M1Es304 *s;
    float x, y;

    b4c_Enter1456E0l(o, a, 0, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = m1_frameRate42C85C * 10.0f;
    s->f68 = -20.0f;
    s->f4 |= 1;
    s = a->s278;
    y = m1_frameTime42C858 * 0.008f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    o->f10 |= 5;
    a->f4c &= ~0x70u;
}

/* 0x00126D90: enter the stagger (move 0x23): rise at 10/s with gravity -10,
   short pose blend, mark staggered and start its 1/16 s timer. */
void m1_EnterStagger126D90(M1Eo304 *o, M1Ea304 *a)
{
    M1Es304 *t = a->s278;
    M1Es304 *s;
    float x, y;

    m1_AiSetState1456E0(o, a, 0x23, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = m1_frameRate42C85C * 10.0f;
    s->f68 = -10.0f;
    s->f4 |= 1;
    s = a->s278;
    y = m1_frameTime42C858 * 0.008f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    a->f4c |= 0x70;
    t->f4 |= 0x40000800;
    t->f1d8 = 0.0f;
    t->f1dc = m1_frameTime42C858 * 0.0625f;
}

typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[8]; int32_t st58; uint8_t _5c[8]; int32_t st64;
    uint8_t _68[0x278 - 0x68]; M1Es304 *s278; } M1Ea304b;
typedef struct { uint8_t _0[0xC]; uint32_t fc; uint32_t f10; uint8_t _14[0x1C]; int32_t h30; } M1Eo304b;

int  b4c_Enter1456E0f(M1Eo304b *o, M1Ea304b *a, int st, int f);

/* 0x0012AAC0: enter the recoil: keep the current recoil (moves 0x45/0x49)
   while its clip runs, else start move 0x42 at phase 10; 1/8 s pose blend,
   then wait while the body is locked and busy. */
void m1_EnterRecoil12AAC0(M1Eo304b *o, M1Ea304b *a)
{
    M1Es304 *volatile t = a->s278;
    M1Es304 *s;
    float x, y;
    uint32_t f;
    int32_t k;

    if (!sub_000833E0(o->h30) && ((k = a->st64) == 0x45 || k == 0x49)) {
        a->st58 = 0;
    } else {
        b4c_Enter1456E0f(o, a, 0x42, 0);
        a->st58 = 10;
    }
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    y = m1_frameTime42C858 * 0.125f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    a->f4c &= ~0x70u;
    o->fc &= ~0x20u;
    f = o->f10 & 8;
    while (f && (t->f4 & 0x20)) ;
}
