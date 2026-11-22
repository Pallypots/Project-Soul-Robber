/* Area m1, group 309. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[0xC]; uint32_t fc; } M1Bs309;
typedef struct {
    uint8_t _0[0x58]; int32_t st58; uint8_t _5c[8]; int32_t st64; uint8_t _68[4];
    int32_t h6c; int32_t h70; uint8_t _74[0x278 - 0x74]; M1Bs309 *s278;
} M1Ba309;
typedef struct { uint8_t _0[0x60]; uint8_t f60[4]; } M1Bo309;

int  m1_AiSetState1456E0(M1Bo309 *o, M1Ba309 *a, int st, int f);
int  b4c_Enter1456E0f(M1Bo309 *o, M1Ba309 *a, int st, int f);
int  b4c_Enter1456E0d(M1Bo309 *o, M1Ba309 *a, int st, int f);
void sub_0001D4E0f(M1Bo309 *o);
void sub_0001D4E0g(M1Bo309 *o);
void sub_0001D4E0h(M1Bo309 *o);
int  sub_000494D0(int id, void *p, int f);
int  sub_00036750(M1Bo309 *o, int k);
void a80_ModeSetFlag4(void);

/* 0x00130FF0: second boss's follow-up picker (as 0x1172F0, clearing flag
   0x1000 at +0x0C). */
void m1_NextAction130FF0(M1Bo309 *o, M1Ba309 *a)
{
    M1Bs309 *s;
    int st;
    switch (a->st64) {
    case 0x30: case 0x31: case 0x32: case 0x33: case 0x37: case 0x3B:
        if (m1_AiSetState1456E0(o, a, 0x14, 0) == 1)
            sub_0001D4E0f(o);
        goto spawn;
    case 0x36:
        st = 0x37;
        goto enter;
    case 0x3A:
        st = 0x3B;
    enter:
        if (b4c_Enter1456E0f(o, a, st, 0) == 1)
            sub_0001D4E0g(o);
        a->st58 = 0;
        break;
    default:
        if (b4c_Enter1456E0d(o, a, 0x14, 0) == 1)
            sub_0001D4E0h(o);
    spawn:
        a->h6c = sub_000494D0(0x174, o->f60, 0);
        a->h70 = sub_00036750(o, 2);
        a->st58 = 0x63;
        break;
    }
    s = a->s278;
    if (s->fc & 0x1000) {
        s->fc &= ~0x1000u;
        a80_ModeSetFlag4();
    }
}

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78;
} M1Rs309;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[8]; int32_t st58; uint8_t _5c[8]; int32_t st64;
    uint8_t _68[0x278 - 0x68]; M1Rs309 *s278; } M1Ra309;
typedef struct { float f0, f4, f8, fc; float f10[4]; float f20[4]; } M1Rm309;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0xC]; M1Rm309 *p20; } M1Ro309;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
int  b4c_Enter1456E0i(M1Ro309 *o, M1Ra309 *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void r2_BodyResetMat(M1Ra309 *a, float t);                  /* regargs: a=EAX */
void sub_001AD7E0(float *out, float *v);
void sub_001ADA60(float *a, M1Rm309 *m, float *b);

/* 0x0012B0D0: enter the big recoil: keep the running recoil (move 0x45 at
   phase 0, 0x49 at phase 10), else start move 0x4A (rise at 10/s, gravity
   -15, one turn in 1/6 s; hangs if impossible) at phase 20; then stand the
   body upright and wait while it is locked and busy. */
void m1_EnterBigRecoil12B0D0(M1Ro309 *o, M1Ra309 *a)
{
    M1Rs309 *t = a->s278;
    M1Rs309 *s;
    M1Rm309 *m;
    float up[4];
    float x, q;
    uint32_t f;
    int32_t k;

    o->f10 |= 0x20;
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    k = a->st64;
    if (k == 0x45) {
        a->st58 = 0;
    } else if (k == 0x49) {
        a->st58 = 10;
    } else {
        b4c_Enter1456E0i(o, a, 0x4A, 0);
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
        s->f4 |= 2;
        s->f74 = 5.0f;
        r2_BodyResetMat(a, m1_frameTime42C858 * 0.125f);
        a->f4c &= ~0x70u;
        a->st58 = 0x14;
    }
    o->p20->f4 = 0.0f;
    sub_001AD7E0(&o->p20->f0, &o->p20->f0);
    sub_000F5D40(o->p20->f10, up);
    m = o->p20;
    sub_001ADA60(m->f20, m, m->f10);
    f = o->f10 & 8;
    while (f && (*(volatile uint32_t *)&t->f4 & 0x20)) ;
}

typedef struct { uint8_t _0[4]; uint32_t f4; uint8_t _8[0x48 - 8]; float f48; } M1Es309;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[0x74 - 0x50]; float wait74;
    uint8_t _78[0x278 - 0x78]; M1Es309 *s278; } M1Ea309;
typedef struct { uint8_t _0[0x20]; uint8_t *p20; uint8_t _24[0x60 - 0x24]; float x60, y64, z68;
    uint8_t _6c[0xA0 - 0x6C]; float xa0, _a4, za8; } M1Eo309;
typedef struct { float x, y, z, w; } M1V4309;

float m1_Height145B60(void *p);
void  m1_XfAlloc0C7540(M1Eo309 *o, float a, float b, M1V4309 *p, M1V4309 *d);
void  sub_00113AA0(void *o, void *h);
int   sub_001154D0(M1Ea309 *a, M1Eo309 *o);                 /* regargs: a=EAX */
void  sub_00117580(M1Eo309 *o, int st);

/* 0x00118F20: enemy phase step (as 0x133FC0): while the wait runs, spawn the
   effect at o's offset position; when it ends, leave on flag 0x10 (state
   0x23), react to a hit (state 9) or go to state 1. */
void m1_Phase118F20(M1Eo309 *o, M1Ea309 *a)
{
    M1Es309 *s = a->s278;
    M1V4309 d, p;
    if (a->wait74 > 0.0f) {
        p.x = o->xa0 + o->x60;
        p.z = o->za8 + o->z68;
        p.y = o->y64;
        p.w = 1.0f;
        d.x = 0.0f; d.y = 0.0f; d.z = 0.0f; d.w = 1.0f;
        d.y = m1_Height145B60(o->p20 + 0x20);
        m1_XfAlloc0C7540(o, 1.0f, 0.6f, &p, &d);
        return;
    }
    sub_00113AA0(o, a);
    a->f4c |= 0x200;
    s->f4 &= ~0x80400u;
    if (s->f4 & 0x10) {
        sub_00117580(o, 0x23);
        return;
    }
    if (sub_001154D0(a, o)) {
        s->f48 = 0.3f;
        sub_00117580(o, 9);
        return;
    }
    sub_00117580(o, 1);
}

typedef struct { float v[12]; } M1Fm309;
typedef struct { uint8_t _0[0x70]; union { M1Fm309 m70; struct { float _70[6]; float f88, f8c, f90, f94, _98, f9c; } p; } u; } M1Fs309;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0x278 - 0x5C]; M1Fs309 *s278; } M1Fa309;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; int32_t h30; } M1Fo309;

int32_t sub_000833E0(int32_t h);
void sub_00186470(M1Fo309 *o, M1Fa309 *a, int st);           /* regargs: o=EBX a=EDI */

/* 0x00187A50: fall: apply gravity (294 per frame unit squared) to the fall
   speed until it lands, and once the clip ends step on; step 1 sets the
   target height 10 and climb rate 50/s; step 2 waits to reach it; step 3
   goes to state 2. */
void m1_Fall187A50(M1Fo309 *o, M1Fa309 *a)
{
    M1Fs309 *t = a->s278;
    M1Fm309 m;
    int32_t landed;
    float fr;
    switch (a->st58) {
    case 0:
        m = t->u.m70;
        m.v[9] = m.v[9] + m.v[11];
        if (m.v[9] > 0.0f) {
            m.v[9] = 0.0f;
            landed = 1;
        } else {
            landed = 0;
        }
        fr = m1_frameRate42C85C;
        m.v[11] = fr * fr * 294.0f + m.v[11];
        t->u.m70 = m;
        if (sub_000833E0(o->h30) && landed)
            a->st58++;
        return;
    case 1:
        t->u.p.f8c = 10.0f;
        t->u.p.f90 = m1_frameRate42C85C * 50.0f;
        t->u.p.f94 = 0.0f;
        t->u.p.f9c = 0.0f;
        o->f10 &= ~4u;
        a->st58++;
    case 2:
        if (t->u.p.f8c == t->u.p.f88)
            a->st58++;
        return;
    case 3:
        sub_00186470(o, a, 2);
        return;
    }
}
