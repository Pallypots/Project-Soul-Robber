/* Area m1, file 339: enter-attack state (backstep, two strengths). Names inferred. */
#include <stdint.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78;
    uint8_t _7c[0x90 - 0x7C]; float f90; uint8_t _94[0xB8 - 0x94]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180;
} M1As339;
typedef struct {
    uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c; uint8_t _50[0x74 - 0x50]; float f74;
    uint8_t _78[0x278 - 0x78]; M1As339 *s278;
} M1Aa339;
typedef struct { uint8_t _0[0x10]; uint32_t f10; } M1Ao339;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Kc339;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
int      m1_AiSetState1456E0(void *o, void *a, int st, int f);
void     sub_000F5D40(float *d, const float *s);
void     sub_001ADA40(float *d, const float *m);
void     sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
int      sub_001C7EE1(void);                                    /* rand */
M1Kc339 *m1_Quest113400(void *a, int v);

/* 0x1264E0: enter the backstep: strong (guard bit: pose 2, back at 50/s, blend 4) or weak
   (pose 1, back at 40/s, blend 2); rise at 10/s with gravity -5, spin once in 1/6 s (hangs
   if the frame rate makes that impossible), start the 0.008 s pose blend, a random 1..2.5
   speed scale, a 3.5 timer, flags, and the timed turn effect. */
void m1_EnterBackstep1264E0(M1Ao339 *o, M1Aa339 *a)
{
    M1As339 *s0 = a->s278;
    M1As339 *s;
    M1Kc339 *c;
    float x, b, q, y, z;

    if (a->b20 & 1) {
        m1_AiSetState1456E0(o, a, 2, 0);
        s = a->s278;
        x = m1_frameTime42C858 * (1.0f / 30.0f);
        b = m1_frameRate42C85C * 50.0f;
        sub_000F5D40(s->v40, s->v30);
        s->f58 = 0.0f - b;
        s->f54 = 0.0f; s->f50 = 0.0f;
        s->f5c = 1.0f;
        s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
        s->f64 = x;
        s = a->s278;
        s->f6c = m1_frameRate42C85C * 10.0f;
        s->f68 = -5.0f;
        s->f4 |= 1;
        s = a->s278;
        q = 6.28318548f / (m1_fps42C964 * 6.0f);
        if (!(6.28318548f >= q)) for (;;) ;
        s->f78 = q;
        s->f74 = 5.0f;
        s->f4 |= 2;
        s = a->s278;
        s->f4 |= 4;
        y = m1_frameTime42C858 * 0.008f;
        sub_001ADA40(s->mf8, s->mb8);
        sub_0011F640(4, s->b138);
        s->f178 = 4;
    } else {
        m1_AiSetState1456E0(o, a, 1, 0);
        s = a->s278;
        x = m1_frameTime42C858 * (1.0f / 30.0f);
        b = m1_frameRate42C85C * 40.0f;
        sub_000F5D40(s->v40, s->v30);
        s->f58 = 0.0f - b;
        s->f54 = 0.0f; s->f50 = 0.0f;
        s->f5c = 1.0f;
        s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
        s->f64 = x;
        s = a->s278;
        s->f6c = m1_frameRate42C85C * 10.0f;
        s->f68 = -5.0f;
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
        s->f178 = 2;
    }
    s->f17c = 0.0f;
    s->f180 = y;
    s0->f90 = (float)sub_001C7EE1() * 3.05185094e-05f * 1.5f + 1.0f;
    a->f74 = 3.5f;
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    s0->f4 |= 0x800;
    z = m1_frameTime42C858 * 0.0698131695f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (z != -1.0f) c->f18 = z;
    c->f1c = 0.0f;
}

typedef struct M1Tg339 { uint8_t unk00[4]; int32_t i04; uint8_t unk08[4]; uint8_t b0C; } M1Tg339;
typedef struct M1Ab339 { uint8_t _0[0xF8]; int32_t iF8; uint8_t _fc[0x104 - 0xFC]; M1Tg339 *p104; } M1Ab339;

/* 0x121EF0: enter the hop-back: strong (guard bit: pose 2, back at 30/s, blend 4) or weak
   (pose 1, back at 20/s, blend 2); rise at 10/s with gravity -15, spin once in 1/6 s (hangs
   if the frame rate makes that impossible), start the 0.008 s pose blend, a random 1..2.5
   speed scale only while holding a grabbed kind-0xD target, a 3.5 timer, flags, and the
   timed turn effect. */
void m1_EnterHopBack121EF0(M1Ao339 *o, M1Aa339 *a)
{
    M1As339 *s0 = a->s278;
    M1As339 *s;
    M1Kc339 *c;
    float x, b, q, y, z;

    if (a->b20 & 1) {
        m1_AiSetState1456E0(o, a, 2, 0);
        s = a->s278;
        x = m1_frameTime42C858 * (1.0f / 30.0f);
        b = m1_frameRate42C85C * 30.0f;
        sub_000F5D40(s->v40, s->v30);
        s->f58 = 0.0f - b;
        s->f54 = 0.0f; s->f50 = 0.0f;
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
        s->f4 |= 4;
        y = m1_frameTime42C858 * 0.008f;
        sub_001ADA40(s->mf8, s->mb8);
        sub_0011F640(4, s->b138);
        s->f178 = 4;
    } else {
        m1_AiSetState1456E0(o, a, 1, 0);
        s = a->s278;
        x = m1_frameTime42C858 * (1.0f / 30.0f);
        b = m1_frameRate42C85C * 20.0f;
        sub_000F5D40(s->v40, s->v30);
        s->f58 = 0.0f - b;
        s->f54 = 0.0f; s->f50 = 0.0f;
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
        sub_0011F640(2, s->b138);
        s->f178 = 2;
    }
    s->f17c = 0.0f;
    s->f180 = y;
    if (((M1Ab339 *)a)->iF8 == 1 && (((M1Ab339 *)a)->p104->b0C & 1) && ((M1Ab339 *)a)->p104->i04 == 0xD)
        s0->f90 = (float)sub_001C7EE1() * 3.05185094e-05f * 1.5f + 1.0f;
    a->f74 = 3.5f;
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    s0->f4 |= 0x4000;
    z = m1_frameTime42C858 * 0.0261799395f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (z != -1.0f) c->f18 = z;
    c->f1c = 0.0f;
}
