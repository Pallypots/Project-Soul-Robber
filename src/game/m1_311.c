/* Area m1, group 311. Names inferred. */
#include <stdint.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78, f7c;
    uint8_t _80[4]; float f84; uint8_t _88[4]; float f8c; uint8_t _90[4]; int32_t f94; uint8_t _98[0xB8 - 0x98]; float mb8[16]; float mf8[16];
    uint8_t b138[0x40]; int32_t f178; float f17c, f180;
} M1As311;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c; uint8_t _50[8]; int32_t st58; uint8_t _5c[0x74 - 0x5C]; float wait74; uint8_t _78[0x278 - 0x78]; M1As311 *s278; } M1Aa311;
typedef struct { uint8_t _0[0x10]; uint32_t f10; } M1Ao311;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Ac311;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
int  m1_AiSetState1456E0(M1Ao311 *o, M1Aa311 *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void sub_001ADA40(float *d, const float *m);
void sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
M1Ac311 *m1_Quest113400(M1Aa311 *a, int v);
M1Ac311 *m1_Quest113400g(M1Aa311 *a, int v);
int  b4c_Enter1456E0d(M1Ao311 *o, M1Aa311 *a, int st, int f);
int  b4c_Enter1456E0f(M1Ao311 *o, M1Aa311 *a, int st, int f);
int  b4c_Enter1456E0i(M1Ao311 *o, M1Aa311 *a, int st, int f);
int  b4c_Enter1456E0j(M1Ao311 *o, M1Aa311 *a, int st, int f);
int  r2_AnyFlagMask(int k, M1Ao311 *o, uint32_t mask);      /* regargs: k=EAX o=EDI mask=ESI */
void sub_000414A0(int v);
int  sub_00036750(M1Ao311 *o, int k);
M1Ac311 *m1_Quest113400h(M1Aa311 *a, int v);

/* 0x00120DB0: enter the swoop (move 0): one turn in 1/6 s (hangs if
   impossible), short pose blend, rise at 10/s with gravity -30 (flag
   0x2000) or -15, mark swooping and start the 20-degree sweep command. */
void m1_EnterSwoop120DB0(M1Ao311 *o, M1Aa311 *a)
{
    M1As311 *t = a->s278;
    M1As311 *s;
    M1Ac311 *c;
    float x, q, y, z, w;

    m1_AiSetState1456E0(o, a, 0, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
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
    s->f17c = 0.0f;
    s->f178 = 1;
    a->f4c |= 0x70;
    z = m1_frameRate42C85C * 10.0f;
    s = a->s278;
    s->f6c = z;
    if (t->f4 & 0x2000) {
        s->f4 |= 1;
        s->f68 = -30.0f;
    } else {
        s->f68 = -15.0f;
        s->f4 |= 1;
    }
    o->f10 |= 0x20;
    t->f4 |= 0x4000;
    t->f8c = 0.0f;
    w = m1_frameTime42C858 * 0.0139626348f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.34906587f;
    c->f14 = -0.34906587f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
}

/* 0x00122570: enter the back flip (move 3): slide back at 15/s, rise at
   10/s with gravity -15, one turn in 1/6 s (hangs if impossible), 3-frame
   pose blend, 3.5 s window and the 5-degree turn command. */
void m1_EnterBackFlip122570(M1Ao311 *o, M1Aa311 *a)
{
    M1As311 *t = a->s278;
    M1As311 *s;
    M1Ac311 *c;
    float x, z, q, y, w;

    b4c_Enter1456E0d(o, a, 3, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    z = m1_frameRate42C85C * -15.0f;
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f - z;
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
    sub_0011F640(3, s->b138);
    s->f17c = 0.0f;
    s->f180 = y;
    s->f178 = 3;
    a->wait74 = 3.5f;
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    t->f4 |= 0x4000;
    w = m1_frameTime42C858 * 0.0174532924f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
}

/* 0x001269A0: enter the triple spin (move 0x20): rise at 10/s with gravity
   -5, one turn in 1/4 s (hangs if impossible), short pose blend, three
   spins, the 10-degree turn command and the scale command (0, 0, 1, 1). */
void m1_EnterTripleSpin1269A0(M1Ao311 *o, M1Aa311 *a)
{
    M1As311 *t = a->s278;
    M1As311 *s;
    M1Ac311 *c;
    float x, q, y, w;

    b4c_Enter1456E0f(o, a, 0x20, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f6c = m1_frameRate42C85C * 10.0f;
    s->f68 = -5.0f;
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
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    t->f4 |= 0x800;
    t->f94 = 3;
    w = m1_frameTime42C858 * 0.052359879f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.174532935f;
    c->f14 = -0.174532935f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
    c = m1_Quest113400g(a, 2);
    c->f10 = 0.0f;
    c->f14 = 0.0f;
    c->f18 = 1.0f;
    c->f1c = 1.0f;
}

/* 0x00122E70: enter the high swoop (move 0x13): one turn in 1/6 s (hangs if
   impossible), short pose blend, 20-degree sweep command, rise at 10/s with
   gravity -30 (flag 0x2000) or -17.5; with flag 0x2000 phase 10 when input 5
   or 0xF is held, else phase 0. */
void m1_EnterHighSwoop122E70(M1Ao311 *o, M1Aa311 *a)
{
    M1As311 *t = a->s278;
    M1As311 *s;
    M1Ac311 *c;
    float x, q, y, w, z, g;

    b4c_Enter1456E0i(o, a, 0x13, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
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
    s->f180 = y;
    s->f178 = 1;
    o->f10 |= 0x20;
    a->f4c |= 0x70;
    t->f4 |= 0x800;
    w = m1_frameTime42C858 * 0.0174532924f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.34906587f;
    c->f14 = -0.34906587f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
    g = -30.0f;
    z = m1_frameRate42C85C * 10.0f;
    s = a->s278;
    s->f6c = z;
    if (!(t->f4 & 0x2000))
        g = -17.5f;
    s->f4 |= 1;
    s->f68 = g;
    if ((t->f4 & 0x2000) && (r2_AnyFlagMask(5, o, 0x400000) || r2_AnyFlagMask(0xF, o, 0x400000))) {
        a->st58 = 10;
        return;
    }
    a->st58 = 0;
}

/* 0x00127D70: enter the hurt guard (move 0x15): 1/8 s pose blend, drain the
   guard meter by 20 (0..200), count the hit; facing: voice 7, 2-degree turn
   and the push command, phase 40; otherwise phase 30. Wait while locked. */
void m1_EnterHurtGuard127D70(M1Ao311 *o, M1Aa311 *a)
{
    M1As311 *t = a->s278;
    M1As311 *s;
    M1Ac311 *c;
    float x, y, v, w;
    uint32_t f;

    b4c_Enter1456E0j(o, a, 0x15, 0);
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
    t->f84 = t->f84 + 1.0f;
    if (a->b20 & 1) {
        a->f4c |= 0x70;
        sub_00036750(o, 7);
        w = m1_frameTime42C858 * 0.0349065848f;
        c = m1_Quest113400(a, 1);
        c->f10 = 0.0872664675f;
        c->f14 = -0.0872664675f;
        if (w != -1.0f)
            c->f18 = w;
        c->f1c = 0.0f;
        c = m1_Quest113400h(a, 3);
        c->f10 = 0.3f;
        c->f14 = 0.3f;
        c->f18 = 10.0f;
        c->f1c = 0.0f;
        a->st58 = 0x28;
    } else {
        a->st58 = 0x1E;
    }
    f = o->f10 & 8;
    while (f && (*(volatile uint32_t *)&t->f4 & 0x20)) ;
}
