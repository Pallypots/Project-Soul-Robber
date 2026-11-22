/* Area m1, group 315. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78, f7c;
    uint8_t _80[0x90 - 0x80]; float f90; uint8_t _94[0xB8 - 0x94]; float mb8[16]; float mf8[16];
    uint8_t b138[0x40]; int32_t f178; float f17c, f180;
} M1As315;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c; uint8_t _50[8]; int32_t st58; uint8_t _5c[0x74 - 0x5C]; float wait74;
    uint8_t _78[0xF8 - 0x78]; int32_t ff8; uint8_t _fc[8]; struct M1At315 *p104; uint8_t _108[0x278 - 0x108]; M1As315 *s278; } M1Aa315;
typedef struct M1At315 { uint8_t _0[4]; int32_t f4, f8; uint8_t bc; } M1At315;
typedef struct { uint8_t _0[0x10]; uint32_t f10; } M1Ao315;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Ac315;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
int  m1_AiSetState1456E0(M1Ao315 *o, M1Aa315 *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void sub_001ADA40(float *d, const float *m);
void sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
M1Ac315 *m1_Quest113400(M1Aa315 *a, int v);
M1Ac315 *m1_Quest113400g(M1Aa315 *a, int v);
M1Ac315 *m1_Quest113400h(M1Aa315 *a, int v);
int  b4c_Enter1456E0d(M1Ao315 *o, M1Aa315 *a, int st, int f);
int  b4c_Enter1456E0f(M1Ao315 *o, M1Aa315 *a, int st, int f);
int  b4c_Enter1456E0i(M1Ao315 *o, M1Aa315 *a, int st, int f);
M1Ac315 *m1_Quest113400t(M1Aa315 *a, int v);
M1Ac315 *m1_Quest113400w(M1Aa315 *a, int v);
int  sub_00145800(int a, int b);
int  sub_001C7EE1(void);
int  sub_00036750(M1Ao315 *o, int k);

/* 0x001212C0: enter the hover (move 0): rise at 10/s with gravity -15, one
   turn in 1/6 s (hangs if impossible), short pose blend, a 4 s window, the
   5-degree turn command and the drift command (50, 30/s, 15/s). */
void m1_EnterHover1212C0(M1Ao315 *o, M1Aa315 *a)
{
    M1As315 *t = a->s278;
    M1As315 *s;
    M1Ac315 *c;
    float x, q, y, w, p, r;

    m1_AiSetState1456E0(o, a, 0, 0);
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
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    t->f90 = 0.0f;
    t->f4 |= 0x4000;
    a->wait74 = 4.0f;
    w = m1_frameTime42C858 * 0.0349065848f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
    p = m1_frameRate42C85C * 30.0f;
    r = m1_frameRate42C85C * 15.0f;
    c = m1_Quest113400g(a, 9);
    c->f10 = 50.0f;
    if (p != -1.0f)
        c->f14 = p;
    c->f1c = 0.0f;
    if (r != -1.0f)
        c->f18 = r;
}

/* 0x00126110: enter the rush: facing -> move 2 with a random push command
   (strength 2 or 3) and phase 10; otherwise a random move from the 0x10 set,
   one turn in 1/6 s (hangs if impossible), short pose blend, phase 20.
   Then slide at 5/s, rise at 10/s with gravity -5, voice 0x11 and the
   10-degree turn command. */
void m1_EnterRush126110(M1Ao315 *o, M1Aa315 *a)
{
    M1As315 *t = a->s278;
    M1As315 *s;
    M1Ac315 *c;
    float x, q, y, z, w;

    if (a->b20 & 1) {
        b4c_Enter1456E0d(o, a, 2, 0);
        if (sub_001C7EE1() & 1) {
            c = m1_Quest113400(a, 7);
            c->f10 = 2.0f;
        } else {
            c = m1_Quest113400g(a, 7);
            c->f10 = 3.0f;
        }
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        t->f4 |= 8;
        a->st58 = 10;
    } else {
        b4c_Enter1456E0f(o, a, sub_00145800(0, 2) + 0x10, 0);
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
        a->f4c |= 0x70;
        a->st58 = 0x14;
    }
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    z = m1_frameRate42C85C * 5.0f;
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f - z;
    s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f68 = -5.0f;
    s->f6c = m1_frameRate42C85C * 10.0f;
    s->f4 |= 1;
    o->f10 |= 0x20;
    t->f4 |= 0x800;
    sub_00036750(o, 0x11);
    w = m1_frameTime42C858 * 0.0872664675f;
    c = m1_Quest113400h(a, 1);
    c->f10 = 0.174532935f;
    c->f14 = -0.174532935f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
}

/* 0x00123920: enter the spin dash (move 0x20): slide at 5/s, one turn in
   1/4 s (hangs if impossible), short pose blend, refill the guard meter by
   20 (0..200), the 10-degree turn command; then against a weak target
   (type 1, flag 1, rank < 3) rise at 10/s with gravity -10 and scale
   command (0, 0, 1, 0), otherwise rise at 20/s with gravity -4 and scale
   command (0, 0, 1, 1). */
void m1_EnterSpinDash123920(M1Ao315 *o, M1Aa315 *a)
{
    M1As315 *t = a->s278;
    M1As315 *s;
    M1Ac315 *c;
    M1At315 *p;
    float x, z, q, y, v, w;

    b4c_Enter1456E0i(o, a, 0x20, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    z = m1_frameRate42C85C * 5.0f;
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f - z;
    s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    q = 6.28318548f / (m1_fps42C964 * 4.0f);
    if (!(6.28318548f >= q)) for (;;) ;
    s->f78 = q;
    s->f74 = 2.5f;
    s->f4 |= 2;
    s = a->s278;
    y = m1_frameTime42C858 * 0.008f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f180 = y;
    s->f17c = 0.0f;
    s->f178 = 1;
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    t->f4 |= 0x10800;
    s = a->s278;
    v = s->f7c + 20.0f;
    s->f7c = v;
    if (0.0f > v)
        s->f7c = 0.0f;
    else if (v > 200.0f)
        s->f7c = 200.0f;
    w = m1_frameTime42C858 * 0.052359879f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.174532935f;
    c->f14 = -0.174532935f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
    if (a->ff8 == 1 && ((p = a->p104)->bc & 1) && p->f4 == 1 && p->f8 < 3) {
        s = a->s278;
        s->f4 |= 1;
        s->f68 = -10.0f;
        s->f6c = m1_frameRate42C85C * 10.0f;
        c = m1_Quest113400t(a, 2);
        c->f10 = 0.0f;
        c->f14 = 0.0f;
        c->f18 = 1.0f;
        c->f1c = 0.0f;
        return;
    }
    s = a->s278;
    s->f4 |= 1;
    s->f68 = -4.0f;
    s->f6c = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(m1_frameRate42C85C * 10.0f), _mm_set_ss(2.0f)));
    c = m1_Quest113400w(a, 2);
    c->f10 = 0.0f;
    c->f14 = 0.0f;
    c->f18 = 1.0f;
    c->f1c = 1.0f;
}
