/* Area m1, group 312: enter-attack states. Names inferred. */
#include <stdint.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78, f7c;
    uint8_t _80[0xB8 - 0x80]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180;
} M1As312;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[0xF8 - 0x50]; int32_t ff8; uint8_t _fc[8];
    void *p104; uint8_t _108[0x278 - 0x108]; M1As312 *s278; } M1Aa312;
typedef struct { uint8_t _0[0x10]; uint32_t f10; } M1Ao312;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Ac312;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
extern void *g_playerObj;
int  m1_AiSetState1456E0(M1Ao312 *o, M1Aa312 *a, int st, int f);
int  b4c_Enter1456E0d(M1Ao312 *o, M1Aa312 *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void sub_001ADA40(float *d, const float *m);
void sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
M1Ac312 *m1_Quest113400(M1Aa312 *a, int v);
M1Ac312 *m1_Quest113400g(M1Aa312 *a, int v);
int  sub_00036750(M1Ao312 *o, int k);

/* 0x0012C7F0: enter the lunge at the player (move 0x28): rise at 10/s with
   gravity -10, one turn in 1/4 s (hangs if impossible), short pose blend,
   target the player, voice 5, the 5-degree turn command and the 5-unit
   chase command. */
void m1_EnterLunge12C7F0(M1Ao312 *o, M1Aa312 *a)
{
    M1As312 *t = a->s278;
    M1As312 *s;
    M1Ac312 *c;
    float x, q, y, w;

    m1_AiSetState1456E0(o, a, 0x28, 0);
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
    s->f17c = 0.0f;
    s->f180 = y;
    s->f178 = 1;
    o->f10 |= 5;
    a->f4c |= 0x1000070;
    t->f4 |= 0x800;
    a->p104 = g_playerObj;
    a->ff8 = 1;
    sub_00036750(o, 5);
    w = m1_frameTime42C858 * 0.104719758f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
    c = m1_Quest113400g(a, 2);
    c->f10 = 5.0f;
    c->f14 = 0.0f;
    c->f18 = 1.0f;
    c->f1c = 0.0f;
}

/* 0x00123660: enter the tail swipe (move 0x17): rise at 10/s with gravity
   -15, one turn in 1/6 s (hangs if impossible), short pose blend, refill
   the guard meter by 60 (0..200) and start the 20-degree sweep command. */
void m1_EnterTailSwipe123660(M1Ao312 *o, M1Aa312 *a)
{
    M1As312 *t = a->s278;
    M1As312 *s;
    M1Ac312 *c;
    float x, q, y, v, w;

    b4c_Enter1456E0d(o, a, 0x17, 0);
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
    s->f180 = y;
    s->f178 = 1;
    s->f17c = 0.0f;
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    t->f4 |= 0x20800;
    s = a->s278;
    v = s->f7c + 60.0f;
    s->f7c = v;
    if (0.0f > v)
        s->f7c = 0.0f;
    else if (v > 200.0f)
        s->f7c = 200.0f;
    w = m1_frameTime42C858 * 0.00872664619f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.34906587f;
    c->f14 = -0.34906587f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
}

#include <xmmintrin.h>
typedef struct { uint8_t _0[0xC]; uint32_t fc, f10; } M1Bo312;
int  b4c_Enter1456E0f(M1Bo312 *o, M1Aa312 *a, int st, int f);

/* 0x00125E50: enter the pounce at the player (move 1): slide at 30/s, rise
   at 20/s with gravity -15, one turn in 1/6 s (hangs if impossible), 2-frame
   pose blend, target the player and start the 3-degree turn command. */
void m1_EnterPounce125E50(M1Bo312 *o, M1Aa312 *a)
{
    M1As312 *t = a->s278;
    M1As312 *s;
    M1Ac312 *c;
    float x, z, q, y, w;

    b4c_Enter1456E0f(o, a, 1, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    z = m1_frameRate42C85C * 30.0f;
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f - z;
    s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(m1_frameRate42C85C * 10.0f), _mm_set_ss(2.0f)));
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
    sub_0011F640(2, s->b138);
    s->f17c = 0.0f;
    s->f180 = y;
    s->f178 = 2;
    o->fc &= ~0x20u;
    o->f10 |= 0x125;
    a->f4c |= 0x70;
    a->p104 = g_playerObj;
    a->ff8 = 1;
    t->f4 |= 0x800;
    w = m1_frameTime42C858 * 0.052359879f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
}
