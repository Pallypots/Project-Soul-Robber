/* Area m1, group 305: enter-attack states. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78, f7c, f80;
    uint8_t _84[0xB8 - 0x84]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180; uint8_t _184[0x34C - 0x184]; int32_t f34c;
} M1Fs305;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c; uint8_t _50[8]; int32_t st58;
    uint8_t _5c[0x278 - 0x5C]; M1Fs305 *s278; } M1Fa305;
typedef struct { uint8_t _0[0x10]; uint32_t f10; } M1Fo305;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
int  m1_AiSetState1456E0(M1Fo305 *o, M1Fa305 *a, int st, int f);
int  b4c_Enter1456E0d(M1Fo305 *o, M1Fa305 *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void sub_001ADA40(float *d, const float *m);
void sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
void sub_000414A0(int v);
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Fc305;
M1Fc305 *m1_Quest113400(M1Fa305 *a, int v);
int  sub_00036750(M1Fo305 *o, int k);
int  b4c_Enter1456E0f(M1Fo305 *o, M1Fa305 *a, int st, int f);
int  b4c_Enter1456E0i(M1Fo305 *o, M1Fa305 *a, int st, int f);

/* 0x0012A620: enter the big spin (move 0x40): rise at 5/s with gravity
   -17.5, one turn per frame unit (hangs if impossible), 25-frame pose blend,
   then wait while the body is locked and busy. */
void m1_EnterBigSpin12A620(M1Fo305 *o, M1Fa305 *a)
{
    M1Fs305 *volatile t = a->s278;
    M1Fs305 *s;
    float x, q, y;
    uint32_t f;

    m1_AiSetState1456E0(o, a, 0x40, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f68 = -17.5f;
    s->f6c = m1_frameRate42C85C * 10.0f * 0.5f;
    s->f4 |= 1;
    s = a->s278;
    q = 6.28318548f / m1_fps42C964;
    if (!(6.28318548f >= q)) for (;;) ;
    s->f78 = q;
    s->f74 = 2.5f;
    s->f4 |= 2;
    s = a->s278;
    y = m1_frameTime42C858 * 0.05f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(0x19, s->b138);
    s->f17c = 0.0f;
    s->f178 = 0x19;
    s->f180 = y;
    a->f4c &= ~0x70u;
    f = o->f10 & 8;
    while (f && (t->f4 & 0x20)) ;
}

/* 0x00128090: enter the hurt guard (move 0x15): 1/8 s pose blend, drain the
   guard meter by 20 (0..200), set the knock distance by weight class
   (288/432/648; others hang) and go to phase 20; wait while locked. */
void m1_EnterGuardHit128090(M1Fo305 *o, M1Fa305 *a)
{
    M1Fs305 *t = a->s278;
    M1Fs305 *s;
    float x, y, v, c;
    uint32_t f;
    int32_t k;

    b4c_Enter1456E0d(o, a, 0x15, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    y = m1_frameTime42C858 * 0.125f;
    s = a->s278;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    o->f10 |= 0x20;
    a->f4c &= ~0x70u;
    sub_000414A0(1);
    s = a->s278;
    v = s->f7c - 20.0f;
    s->f7c = v;
    if (0.0f > v)
        s->f7c = 0.0f;
    else if (v > 200.0f)
        s->f7c = 200.0f;
    t->f4 |= 0x80;
    k = t->f34c;
    if (k == 0)      c = 288.0f;
    else if (k == 1) c = 432.0f;
    else if (k == 2) c = 648.0f;
    else for (;;) ;
    t->f80 = c;
    a->st58 = 0x14;
    f = o->f10 & 8;
    while (f && (*(volatile uint32_t *)&t->f4 & 0x20)) ;
}

/* 0x00125C30: enter the tail sweep (move 0x17): rise at 10/s with gravity
   -15, one turn in 1/6 s (hangs if impossible), short pose blend, voice 7
   and the sweep command (rates 0.5, range 10, scale 1). */
void m1_EnterSweep125C30(M1Fo305 *o, M1Fa305 *a)
{
    M1Fs305 *s;
    M1Fc305 *c;
    float x, q, y;

    b4c_Enter1456E0f(o, a, 0x17, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = m1_frameRate42C85C * 10.0f;
    s->f68 = -15.0f;
    s->f4 |= 1;
    s = a->s278;
    q = 6.28318548f / (m1_fps42C964 * 6.0f);
    if (!(6.28318548f >= q)) for (;;) ;
    s->f78 = q;
    s->f74 = 5.0f;
    s->f4 |= 2;
    s = a->s278;
    y = m1_frameTime42C858 * 0.008f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    a->f4c &= ~0x70u;
    sub_00036750(o, 7);
    c = m1_Quest113400(a, 3);
    c->f10 = 0.5f;
    c->f14 = 0.5f;
    c->f18 = 10.0f;
    c->f1c = 1.0f;
}

/* 0x00123D60: enter the charge (move 0x21): rise at 20/s with gravity -20,
   short pose blend, refill the guard meter by 40 (0..200), voice 9 or 8 by
   side, and the charge command (1, 0, 1, 0). */
void m1_EnterCharge123D60(M1Fo305 *o, M1Fa305 *a)
{
    M1Fs305 *t = a->s278;
    M1Fs305 *s;
    M1Fc305 *c;
    float x, y, v;
    volatile int32_t k;

    b4c_Enter1456E0i(o, a, 0x21, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(m1_frameRate42C85C * 10.0f), _mm_set_ss(2.0f)));
    s->f68 = -20.0f;
    s->f4 |= 1;
    y = m1_frameTime42C858 * 0.008f;
    s = a->s278;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f180 = y;
    s->f178 = 1;
    s->f17c = 0.0f;
    s = a->s278;
    v = s->f7c + 40.0f;
    s->f7c = v;
    if (0.0f > v)
        s->f7c = 0.0f;
    else if (v > 200.0f)
        s->f7c = 200.0f;
    o->f10 |= 0x20;
    t->f4 |= 0x800;
    k = 8;
    if (a->b20 & 1) k = 9;
    sub_00036750(o, k);
    c = m1_Quest113400(a, 2);
    c->f10 = 1.0f;
    c->f14 = 0.0f;
    c->f18 = 1.0f;
    c->f1c = 0.0f;
}

typedef struct { uint8_t _0[0xC]; uint32_t fc; uint32_t f10; uint8_t _14[0x60 - 0x14]; uint8_t pos60[0x10];
    uint8_t _70[0xF4 - 0x70]; int32_t ff4; uint8_t _f8[0x120 - 0xF8]; int32_t f120; } M1Go305;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c;
    uint8_t _50[0x74 - 0x50]; float f74; uint8_t _78[0x278 - 0x78]; M1Fs305 *s278; } M1Ga305;
typedef struct { int32_t f0; uint8_t _4[0xC]; float f10, f14, f18, f1c; } M1Gc305;

int  b4c_Enter1456E0j(M1Go305 *o, M1Ga305 *a, int st, int f);
int  b4c_Enter1456E0l(M1Go305 *o, M1Ga305 *a, int st, int f);
M1Gc305 *m1_Quest113400g(M1Ga305 *a, int v);
M1Gc305 *m1_Quest113400h(M1Ga305 *a, int v);
int  sub_000494D0(int id, void *p, int f);
int  sub_00036750g(M1Go305 *o, int k);

/* 0x00128FC0: enter the flinch (move 0x30): 1/8 s pose blend; a pending
   push (flag 0x10) starts the 0.1 s push command, a pending knock (0x20)
   plays sound 0xF7 and voice 0xE/0 and starts the knock command. */
void m1_EnterFlinch128FC0(M1Go305 *o, M1Ga305 *a)
{
    M1Fs305 *t = a->s278;
    M1Fs305 *s;
    M1Gc305 *c;
    float x, y;
    volatile int32_t k;

    b4c_Enter1456E0j(o, a, 0x30, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    y = m1_frameTime42C858 * 0.125f;
    s = a->s278;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    a->f4c &= ~0x70u;
    o->f10 |= 0x24;
    if (t->f4 & 0x10) {
        t->f4 &= ~0x10u;
        c = m1_Quest113400g(a, 5);
        c->f10 = 0.1f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        if (c->f0) c->f0 = 2;
    }
    if (t->f4 & 0x20) {
        sub_000494D0(0xF7, o->pos60, 0);
        k = 0;
        if (a->b20 & 1) k = 0xE;
        sub_00036750g(o, k);
        o->f10 |= 0xD;
        a->f4c &= ~0x1000070u;
        c = m1_Quest113400h(a, 6);
        c->f10 = 1.0f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        if (c->f0) c->f0 = 2;
    }
}

/* 0x00129DB0: enter the stun (move 0x34): 1/8 s pose blend, stop moving and
   reset the timer; a pending knock (0x20) is handled as in 0x128FC0. */
void m1_EnterStun129DB0(M1Go305 *o, M1Ga305 *a)
{
    M1Fs305 *t = a->s278;
    M1Fs305 *s;
    M1Gc305 *c;
    float x, y, z;
    volatile int32_t k;

    b4c_Enter1456E0l(o, a, 0x34, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    z = m1_frameRate42C85C * 100.0f;
    sub_000F5D40(s->v40, s->v30);
    s->f54 = z;
    s->f58 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    y = m1_frameTime42C858 * 0.125f;
    s = a->s278;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f180 = y;
    s->f178 = 1;
    a->f4c &= ~0x70u;
    o->f10 |= 0x24;
    o->ff4 = 2;
    o->f120 = 2;
    o->fc &= ~0x20u;
    a->f74 = 1.0f;
    if (t->f4 & 0x20) {
        sub_000494D0(0xF7, o->pos60, 0);
        k = 0;
        if (a->b20 & 1) k = 0xE;
        sub_00036750g(o, k);
        o->f10 |= 0xD;
        a->f4c &= ~0x1000070u;
        c = m1_Quest113400h(a, 6);
        c->f10 = 1.0f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        if (c->f0) c->f0 = 2;
    }
}
