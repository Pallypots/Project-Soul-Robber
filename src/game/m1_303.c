/* Area m1, group 303: enter-attack states. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78;
    float f7c; uint8_t _80[4]; float f84; uint8_t _88[0xB8 - 0x88]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180; uint8_t _184[0x348 - 0x184]; int32_t f348;
} M1As303;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c; uint8_t _50[8]; int32_t st58; uint8_t _5c[0x278 - 0x5C]; M1As303 *s278; } M1Aa303;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x60 - 0x14]; uint8_t pos60[0x10]; } M1Ao303;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
int  m1_AiSetState1456E0(M1Ao303 *o, M1Aa303 *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void sub_001ADA40(float *d, const float *m);
void sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
void sub_000414A0(int v);
int  sub_000494D0(int id, void *p, int f);
int  sub_00036750(M1Ao303 *o, int k);
int  sub_00036750w(M1Ao303 *o, int k);
int  sub_00036750b(M1Ao303 *o, int k);
int  b4c_Enter1456E0d(M1Ao303 *o, M1Aa303 *a, int st, int f);
int  b4c_Enter1456E0f(M1Ao303 *o, M1Aa303 *a, int st, int f);
int  b4c_Enter1456E0i(M1Ao303 *o, M1Aa303 *a, int st, int f);

/* 0x001233D0: enter the spin attack (move 0x14): reset the move blend,
   rise at 10/s with gravity -17.5, spin once around in 1/6 s (hangs if the
   frame rate makes that impossible), and start the 0.1 s pose blend. */
void m1_EnterSpin1233D0(M1Ao303 *o, M1Aa303 *a)
{
    M1As303 *s;
    float x, q, y;

    m1_AiSetState1456E0(o, a, 0x14, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = m1_frameRate42C85C * 10.0f;
    s->f68 = -17.5f;
    s->f4 |= 1;
    s = a->s278;
    q = 6.28318548f / (m1_fps42C964 * 6.0f);
    if (!(6.28318548f >= q)) for (;;) ;
    s->f78 = q;
    s->f74 = 5.0f;
    s->f4 |= 2;
    s = a->s278;
    y = m1_frameTime42C858 * 0.1f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    sub_000414A0(1);
}

/* 0x00127AF0: enter the guard (move 0x15): reset the move blend and start the
   1/8 s pose blend; a pending counter flag (0x1000000) jumps to phase 30,
   otherwise in stance 0x24 the guard meter is refilled by 40 (0..200) and
   phase 10 starts. Waits while the body is locked (flag 8) and busy (0x20). */
void m1_EnterGuard127AF0(M1Ao303 *o, M1Aa303 *a)
{
    M1As303 *t = a->s278;
    M1As303 *s;
    float x, y, v;
    uint32_t f;

    m1_AiSetState1456E0(o, a, 0x15, 0);
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
    if (t->f4 & 0x1000000) {
        t->f4 &= ~0x1000000u;
        a->st58 = 0x1E;
    } else if (t->f348 == 0x24) {
        t->f84 = 0.0f;
        s = a->s278;
        v = s->f7c + 40.0f;
        s->f7c = v;
        if (0.0f > v)
            s->f7c = 0.0f;
        else if (v > 200.0f)
            s->f7c = 200.0f;
        a->st58 = 10;
    }
    f = o->f10 & 8;
    while (f && (*(volatile uint32_t *)&t->f4 & 0x20)) ;
}

/* 0x00127300: enter the hop-back (move 0x15): slide back at 5/s, rise at
   20/s with gravity -12.5, 1/8 s pose blend. */
void m1_EnterHopBack127300(M1Ao303 *o, M1Aa303 *a)
{
    M1As303 *s;
    float x, z, y;

    b4c_Enter1456E0d(o, a, 0x15, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    z = m1_frameRate42C85C * -5.0f;
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f - z;
    s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(m1_frameRate42C85C * 10.0f), _mm_set_ss(2.0f)));
    s->f68 = -12.5f;
    s->f4 |= 1;
    s = a->s278;
    y = m1_frameTime42C858 * 0.125f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    o->f10 |= 0x20;
    a->f4c &= ~0x70u;
    sub_000414A0(1);
}

/* 0x0012BA30: enter the pounce (move 5): rise at 10/s with gravity -20,
   short pose blend, play sound 0xF6 and the attack voice (2 or 1 by side). */
void m1_EnterPounce12BA30(M1Ao303 *o, M1Aa303 *a)
{
    M1As303 *s;
    float x, y;

    b4c_Enter1456E0f(o, a, 5, 0);
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
    y = m1_frameTime42C858 * 0.008f;
    s = a->s278;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    o->f10 |= 5;
    a->f4c = (a->f4c & ~0x70u) | 0x1000000;
    sub_000494D0(0xF6, o->pos60, 0);
    sub_00036750(o, 5);
    if (a->b20 & 1)
        sub_00036750w(o, 2);
    else
        sub_00036750b(o, 1);
}

/* 0x00125AC0: enter the leap (move 6): as 0x12BA30 with sound 0xF7 and voice
   0xF or 6, clearing the pounce flag. */
void m1_EnterLeap125AC0(M1Ao303 *o, M1Aa303 *a)
{
    M1As303 *s;
    float x, y;

    b4c_Enter1456E0i(o, a, 6, 0);
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
    y = m1_frameTime42C858 * 0.008f;
    s = a->s278;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f17c = 0.0f;
    s->f178 = 1;
    s->f180 = y;
    o->f10 |= 5;
    a->f4c &= ~0x1000070u;
    sub_000494D0(0xF7, o->pos60, 0);
    if (a->b20 & 1)
        sub_00036750w(o, 0xF);
    else
        sub_00036750b(o, 6);
}

/* 0x0012A7C0: enter the knock-back (move 0x37): slide back at 70/s, rise at
   -40/s, 24-frame pose blend, bump the hit counter and wait while locked. */
void m1_EnterKnock12A7C0(M1Ao303 *o, M1Aa303 *a)
{
    M1As303 *t = a->s278;
    M1As303 *s;
    float x, z1, z2, w;
    uint32_t f, g;

    m1_AiSetState1456E0(o, a, 0x37, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    z1 = m1_frameRate42C85C * -40.0f;
    z2 = m1_frameRate42C85C * 70.0f;
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f - z2;
    s->f54 = z1;
    s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    w = m1_frameTime42C858 * 0.125f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(0x18, s->b138);
    s->f17c = 0.0f;
    s->f180 = w;
    s->f178 = 0x18;
    o->f10 |= 0x20;
    a->f4c &= ~0x70u;
    g = t->f4 | 8;
    t->f4 = g;
    t->f84 = t->f84 + 1.0f;
    f = o->f10 & 8;
    if (f && (g & 0x20)) for (;;) ;
}
