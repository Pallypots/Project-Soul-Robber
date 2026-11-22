/* Area m1, group 306: enter-attack states. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78, f7c, f80, f84;
    uint8_t _88[0xB8 - 0x88]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180;
} M1Hs306;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c;
    uint8_t _50[0x6C - 0x50]; int32_t h6c, h70; uint8_t _74[0x278 - 0x74]; M1Hs306 *s278; } M1Ha306;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x60 - 0x14]; uint8_t pos60[0x10]; } M1Ho306;
typedef struct { int32_t f0; uint8_t _4[0xC]; float f10, f14, f18, f1c; } M1Hc306;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
int  m1_AiSetState1456E0(M1Ho306 *o, M1Ha306 *a, int st, int f);
int  b4c_Enter1456E0d(M1Ho306 *o, M1Ha306 *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void sub_001ADA40(float *d, const float *m);
void sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
M1Hc306 *m1_Quest113400(M1Ha306 *a, int v);
int  sub_000494D0(int id, void *p, int f);
int  sub_00036750(M1Ho306 *o, int k);
int  sub_00036750g(M1Ho306 *o, int k);
int  sub_001C7EE1(void);                                    /* rand */

/* 0x00127530: enter the heavy flinch (move 0x33): 1/8 s pose blend, add 2
   to the hit counter and 20 to the guard meter (0..200), voice 0xB/0xA by
   side; a pending knock (0x20) plays 0xF7 and starts the knock command. */
void m1_EnterHeavyFlinch127530(M1Ho306 *o, M1Ha306 *a)
{
    M1Hs306 *t = a->s278;
    M1Hs306 *s;
    M1Hc306 *c;
    float x, y, v;
    volatile int32_t k;

    m1_AiSetState1456E0(o, a, 0x33, 0);
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
    s->f180 = y;
    s->f178 = 1;
    s->f17c = 0.0f;
    o->f10 |= 0x20;
    a->f4c &= ~0x70u;
    t->f84 = t->f84 + 2.0f;
    s = a->s278;
    v = s->f7c + 20.0f;
    s->f7c = v;
    if (0.0f > v)
        s->f7c = 0.0f;
    else if (v > 200.0f)
        s->f7c = 200.0f;
    k = 0xA;
    if (a->b20 & 1) k = 0xB;
    sub_00036750(o, k);
    if (t->f4 & 0x20) {
        sub_000494D0(0xF7, o->pos60, 0);
        k = 0;
        if (a->b20 & 1) k = 0xE;
        sub_00036750g(o, k);
        o->f10 |= 0xD;
        a->f4c &= ~0x1000070u;
        c = m1_Quest113400(a, 6);
        c->f10 = 1.0f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        if (c->f0) c->f0 = 2;
    }
}

/* 0x00125350: enter the roll (move 0x16): rise at 10/s with gravity -12.5,
   one turn in 1/6 s (hangs if impossible), short pose blend; reset the hit
   counter, pick a random 2..4 s roll time if none is pending, then play
   sound 0xF5 and voice 0x10. */
void m1_EnterRoll125350(M1Ho306 *o, M1Ha306 *a)
{
    M1Hs306 *t = a->s278;
    M1Hs306 *s;
    float x, q, y;

    b4c_Enter1456E0d(o, a, 0x16, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = m1_frameRate42C85C * 10.0f;
    s->f68 = -12.5f;
    s->f4 |= 1;
    s = a->s278;
    q = 6.28318548f / (m1_fps42C964 * 6.0f);
    if (!(6.28318548f >= q)) for (;;) ;
    s->f78 = q;
    s->f74 = 2.5f;
    s->f4 |= 2;
    s = a->s278;
    y = m1_frameTime42C858 * 0.008f;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(1, s->b138);
    s->f178 = 1;
    s->f17c = 0.0f;
    s->f180 = y;
    o->f10 |= 0x30;
    t->f4 &= ~0x80u;
    t->f84 = 0.0f;
    if (0.0f >= t->f80)
        t->f80 = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss((float)sub_001C7EE1() * (1.0f / 32767.0f) + 1.0f),
                                          _mm_set_ss(2.0f)));
    a->h6c = sub_000494D0(0xF5, o->pos60, 0);
    a->h70 = sub_00036750(o, 0x10);
}

M1Hc306 *m1_Quest113400g(M1Ha306 *a, int v);
int  b4c_Enter1456E0f(M1Ho306 *o, M1Ha306 *a, int st, int f);

/* 0x00127830: enter the heavy flinch variant (move 0x33): as 0x127530 without
   the hit counter, plus the 1/12 s shake command. */
void m1_EnterHeavyFlinch127830(M1Ho306 *o, M1Ha306 *a)
{
    M1Hs306 *t = a->s278;
    M1Hs306 *s;
    M1Hc306 *c;
    float x, y, v;
    volatile int32_t k;

    b4c_Enter1456E0f(o, a, 0x33, 0);
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
    s->f180 = y;
    s->f178 = 1;
    s->f17c = 0.0f;
    o->f10 |= 0x20;
    a->f4c &= ~0x70u;
    s = a->s278;
    v = s->f7c + 20.0f;
    s->f7c = v;
    if (0.0f > v)
        s->f7c = 0.0f;
    else if (v > 200.0f)
        s->f7c = 200.0f;
    k = 0xA;
    if (a->b20 & 1) k = 0xB;
    sub_00036750(o, k);
    o->f10 |= 4;
    c = m1_Quest113400g(a, 8);
    c->f10 = 0.0833333358f;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1c = 0.0f;
    if (t->f4 & 0x20) {
        sub_000494D0(0xF7, o->pos60, 0);
        k = 0;
        if (a->b20 & 1) k = 0xE;
        sub_00036750g(o, k);
        o->f10 |= 0xD;
        a->f4c &= ~0x1000070u;
        c = m1_Quest113400(a, 6);
        c->f10 = 1.0f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        if (c->f0) c->f0 = 2;
    }
}

typedef struct { float f0, f4, f8; uint8_t _c[8]; uint32_t f14; uint8_t _18[0xC0 - 0x18]; } M1Hl306;
typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64; uint8_t _68[0xB8 - 0x68]; float mb8[16]; float mf8[16];
    uint8_t b138[0x40]; int32_t f178; float f17c, f180; uint8_t _184[0x41C - 0x184]; M1Hl306 l41c[4];
} M1Hs306b;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c;
    uint8_t _50[0x278 - 0x50]; M1Hs306b *s278; } M1Ha306b;
typedef struct { uint8_t _0[0xC]; uint32_t fc; uint32_t f10; uint8_t _14[0x60 - 0x14]; uint8_t pos60[0x10];
    uint8_t _70[0xF4 - 0x70]; int32_t ff4; uint8_t _f8[0x120 - 0xF8]; int32_t f120; } M1Ho306b;

int  b4c_Enter1456E0i(M1Ho306b *o, M1Ha306b *a, int st, int f);
int  sub_000494D0b(int id, void *p, int f);
int  sub_00036750b(M1Ho306b *o, int k);
M1Hc306 *m1_Quest113400h(M1Ha306b *a, int v);

/* 0x0012AE80: enter the dizzy state (move 0x45): 1/8 s pose blend, stop
   moving, play sound 0xE5, reset the four sway channels (0.1 s, offset 0)
   and start channel 0 at full weight; a pending knock (0x20) is handled as
   in 0x127530. */
void m1_EnterDizzy12AE80(M1Ho306b *o, M1Ha306b *a)
{
    M1Hs306b *t = a->s278;
    M1Hs306b *s;
    M1Hl306 *volatile p;
    M1Hc306 *c;
    float x, y;
    int32_t i;
    volatile int32_t k;

    (void)*(volatile uint8_t *)&((uint8_t *)o)[0x128];
    b4c_Enter1456E0i(o, a, 0x45, 0);
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
    s->f180 = y;
    s->f178 = 1;
    a->f4c &= ~0x70u;
    o->ff4 = 2;
    o->f120 = 2;
    o->fc &= ~0x20u;
    sub_000494D0b(0xE5, o->pos60, 0);
    p = t->l41c;
    i = 4;
    do {
        p->f4 = 0.0f;
        p->f0 = 0.1f;
        p++;
    } while (--i);
    t->l41c[0].f14 |= 1;
    t->l41c[0].f8 = 1.0f;
    if (t->f4 & 0x20) {
        sub_000494D0b(0xF7, o->pos60, 0);
        k = 0;
        if (a->b20 & 1) k = 0xE;
        sub_00036750b(o, k);
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
