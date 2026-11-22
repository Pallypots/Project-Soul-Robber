/* Area m1, group 307: dash-style enter states. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[0xC]; uint32_t fc; uint8_t _10[0x154 - 0x10]; float v154[4];
    float f164, f168, f16c, f170; void *p174; void *p178; } M1Ds307;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[0xF8 - 0x50]; int32_t ff8; uint8_t _fc[8];
    float v104[4]; uint8_t _114[0x278 - 0x114]; M1Ds307 *s278; } M1Da307;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x60 - 0x14]; uint8_t pos60[0x10]; } M1Do307;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Dc307;

extern float m1_frameTime42C858, m1_frameRate42C85C;
int  m1_AiSetState1456E0(M1Do307 *o, M1Da307 *a, int st, int f);
int  b4c_Enter1456E0d(M1Do307 *o, M1Da307 *a, int st, int f);
void sub_0001D4E0f(M1Do307 *o);
void sub_0001D4E0g(M1Do307 *o);
int  sub_001C7EE1(void);                                    /* rand */
int  sub_000494D0(int id, void *p, int f);
void sub_0012E330(float *out, M1Da307 *a, void *p, void *q);  /* regargs: out=EDI a=ECX p=ESI q=EAX */
void sub_000F5D40(float *d, const float *s);
M1Dc307 *m1_Quest113400(M1Da307 *a, int v);

/* 0x0012EC70: enter the dash (move 2) toward the key point: rise at 30/s,
   sometimes play sound 0x171, start the 5-degree turn command. */
void m1_EnterDash12EC70(M1Do307 *o, M1Da307 *a)
{
    M1Ds307 *t = a->s278;
    M1Ds307 *s;
    M1Dc307 *c;
    float v[4];
    float z, w;

    if (m1_AiSetState1456E0(o, a, 2, 0) == 1)
        sub_0001D4E0f(o);
    s = a->s278;
    z = m1_frameRate42C85C * 30.0f;
    s->f168 = 0.0f;
    s->f164 = 0.0f;
    s->f16c = 0.0f - z;
    s->f170 = 1.0f;
    a->f4c |= 0x70;
    if (sub_001C7EE1() & 1)
        sub_000494D0(0x171, o->pos60, 0);
    sub_0012E330(v, a, t->p174, t->p178);
    sub_000F5D40(t->v154, v);
    a->ff8 = 2;
    sub_000F5D40(a->v104, v);
    t->fc |= 2;
    w = m1_frameTime42C858 * 0.0872664675f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.00174532935f;
    c->f14 = -0.00174532935f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
}

/* 0x0012E940: as 0x12EC70 but also marks o airborne (flags 5). */
void m1_EnterDash12E940(M1Do307 *o, M1Da307 *a)
{
    M1Ds307 *t = a->s278;
    M1Ds307 *s;
    M1Dc307 *c;
    float v[4];
    float z, w;

    if (b4c_Enter1456E0d(o, a, 2, 0) == 1)
        sub_0001D4E0g(o);
    s = a->s278;
    z = m1_frameRate42C85C * 30.0f;
    s->f168 = 0.0f;
    s->f164 = 0.0f;
    s->f170 = 1.0f;
    s->f16c = 0.0f - z;
    o->f10 |= 5;
    a->f4c |= 0x70;
    if (sub_001C7EE1() & 1)
        sub_000494D0(0x171, o->pos60, 0);
    sub_0012E330(v, a, t->p174, t->p178);
    sub_000F5D40(t->v154, v);
    a->ff8 = 2;
    sub_000F5D40(a->v104, v);
    t->fc |= 2;
    w = m1_frameTime42C858 * 0.0872664675f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.00174532935f;
    c->f14 = -0.00174532935f;
    if (w != -1.0f)
        c->f18 = w;
    c->f1c = 0.0f;
}

typedef struct { uint8_t _0[4]; uint32_t f4; uint8_t _8[0x2C - 8]; float f2c, f30, f34, f38;
    uint8_t _3c[0x48 - 0x3C]; float f48; } M1Js307;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0x278 - 0x5C]; M1Js307 *s278; } M1Ja307;
typedef struct { uint8_t _0[0x30]; int32_t h30; uint8_t _34[0x30]; float f64;
    uint8_t _68[0x128 - 0x68]; uint8_t b128; } M1Jo307;

int32_t sub_000833E0(int32_t h);
int  b4c_Enter1456E0f(M1Jo307 *o, M1Ja307 *a, int st, int f);
int  b4c_Enter1456E0i(M1Jo307 *o, M1Ja307 *a, int st, int f);
void sub_0001D4E0h(M1Jo307 *o);
void sub_0001D4E0i(M1Jo307 *o);
void sub_00117580(M1Jo307 *o, int st);
int  sub_001154D0(M1Ja307 *a, M1Jo307 *o);                  /* regargs: a=EAX */
float sub_001A3F30(float x);
extern M1Jo307 *g_playerObj;

/* 0x00117ED0: hop attack: wait for the wind-up, take off (move 0x11: back at
   120/s, up at 80/s), decay the speed by 2% per frame unit until landing,
   land (move 0x12), then go to state 3 when the clip ends. */
void m1_HopAttack117ED0(M1Jo307 *o, M1Ja307 *a)
{
    M1Js307 *t = a->s278;
    M1Js307 *s;
    float z;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) return;
        a->st58++;
    case 1:
        if (b4c_Enter1456E0f(o, a, 0x11, 0) == 1)
            sub_0001D4E0h(o);
        s = a->s278;
        z = m1_frameRate42C85C * 80.0f;
        s->f30 = m1_frameRate42C85C * -120.0f;
        s->f2c = 0.0f;
        s->f34 = 0.0f - z;
        s->f38 = 1.0f;
        t->f4 |= 0x4000;
        a->st58++;
        return;
    case 2:
        t->f2c = (1.0f - m1_frameTime42C858 * 0.02f) * t->f2c;
        t->f34 = (1.0f - m1_frameTime42C858 * 0.02f) * t->f34;
        if (!(o->b128 & 0x18)) return;
        a->st58++;
    case 3:
        if (b4c_Enter1456E0i(o, a, 0x12, 0) == 1)
            sub_0001D4E0i(o);
        s = a->s278;
        s->f34 = 0.0f;
        s->f30 = 0.0f;
        s->f2c = 0.0f;
        s->f38 = 1.0f;
        t->f4 &= ~0x4000u;
        a->st58++;
        return;
    case 4:
        if (sub_000833E0(o->h30))
            sub_00117580(o, 3);
        return;
    }
}

int  b4c_Enter1456E0j(M1Jo307 *o, M1Ja307 *a, int st, int f);
int  b4c_Enter1456E0l(M1Jo307 *o, M1Ja307 *a, int st, int f);
void sub_0001D4E0j(M1Jo307 *o);
void sub_0001D4E0k(M1Jo307 *o);

/* 0x00119500: ledge drop: leave (state 0x25) when 300+ units above or below
   the player; once past step 3 a hit reaction (0x1154D0) jumps to state 9.
   Otherwise: land (move 0x3A), wait, crouch (move 0x3B, or state 0x23 when
   flag 0x10), wait, then state 9 (hit) or 1. */
void m1_LedgeDrop119500(M1Jo307 *o, M1Ja307 *a)
{
    M1Js307 *t = a->s278;
    M1Js307 *s;
    if (sub_001A3F30(o->f64 - g_playerObj->f64) >= 300.0f) {
        sub_00117580(o, 0x25);
        return;
    }
    if (!(t->f4 & 0x10) && a->st58 >= 3 && sub_001154D0(a, o))
        goto hit;
    switch (a->st58) {
    case 0:
        if (!(o->b128 & 0x18)) return;
        a->st58 = 1;
    case 1:
        if (b4c_Enter1456E0j(o, a, 0x3A, 0) == 1)
            sub_0001D4E0j(o);
        s = a->s278;
        s->f34 = 0.0f;
        s->f30 = 0.0f;
        s->f2c = 0.0f;
        s->f38 = 1.0f;
        a->st58++;
        return;
    case 2:
        if (!sub_000833E0(o->h30)) return;
        if (t->f4 & 0x10) {
            sub_00117580(o, 0x23);
            return;
        }
        a->st58++;
    case 3:
        if (b4c_Enter1456E0l(o, a, 0x3B, 0) == 1)
            sub_0001D4E0k(o);
        a->st58++;
        return;
    case 4:
        if (!sub_000833E0(o->h30)) return;
        if (sub_001154D0(a, o)) {
        hit:
            t->f48 = 0.3f;
            sub_00117580(o, 9);
            return;
        }
        sub_00117580(o, 1);
        return;
    }
}

typedef struct { uint8_t _0[0xC]; uint32_t fc; uint8_t _10[0x164 - 0x10]; float f164, f168, f16c, f170;
    uint8_t _174[0x184 - 0x174]; float f184; } M1Ks307;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0x278 - 0x5C]; M1Ks307 *s278; } M1Ka307;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; int32_t h30;
    uint8_t _34[0x128 - 0x34]; uint8_t b128; } M1Ko307;

int  m1_AiSetState1456E0(M1Ko307 *o, M1Ka307 *a, int st, int f);
int  b4c_Enter1456E0d(M1Ko307 *o, M1Ka307 *a, int st, int f);
void sub_0001D4E0f(M1Ko307 *o);
void sub_0001D4E0g(M1Ko307 *o);
int32_t r2_PlayerInFrontB(M1Ka307 *a, M1Ko307 *o);         /* regargs: a=EAX */
void r3_SetStateA(M1Ko307 *o, M1Ka307 *a, int st);          /* regargs: o=EBX a=EDI */

/* 0x001348E0: second boss's ledge drop: once past step 3 a player in front
   triggers the reaction (0x15 one time in 4, else 0xE). Otherwise: land
   (move 0x3A), wait, crouch (move 0x3B, or state 0x2B when flag 0x20),
   wait, then react or go to state 5. */
void m1_BossDrop1348E0(M1Ko307 *o, M1Ka307 *a)
{
    M1Ks307 *t = a->s278;
    M1Ks307 *s;
    if (!(t->fc & 0x20) && a->st58 >= 3 && r2_PlayerInFrontB(a, o))
        goto react;
    switch (a->st58) {
    case 0:
        if (!(o->b128 & 0x18)) return;
        a->st58 = 1;
    case 1:
        if (m1_AiSetState1456E0(o, a, 0x3A, 0) == 1)
            sub_0001D4E0f(o);
        s = a->s278;
        s->f16c = 0.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
        a->st58++;
        return;
    case 2:
        if (!sub_000833E0(o->h30)) return;
        if (t->fc & 0x20) {
            r3_SetStateA(o, a, 0x2B);
            return;
        }
        a->st58++;
    case 3:
        if (b4c_Enter1456E0d(o, a, 0x3B, 0) == 1)
            sub_0001D4E0g(o);
        o->f10 |= 4;
        a->st58++;
        return;
    case 4:
        if (!sub_000833E0(o->h30)) return;
        if (r2_PlayerInFrontB(a, o)) {
        react:
            t->f184 = 0.3f;
            if (!(sub_001C7EE1() & 3)) {
                r3_SetStateA(o, a, 0x15);
                return;
            }
            r3_SetStateA(o, a, 0xE);
            return;
        }
        r3_SetStateA(o, a, 5);
        return;
    }
}

typedef struct { uint32_t f0; float f4, f8, fc, f10; uint8_t _14[0x10]; float f24, f28, f2c, f30;
    uint8_t _34[4]; int32_t h38; uint8_t _3c[4]; uint32_t f40; } M1Ns307;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[0x6C - 0x50]; int32_t h6c, h70;
    uint8_t _74[0x278 - 0x74]; M1Ns307 *s278; } M1Na307;
typedef struct { uint8_t _0[0xC]; uint32_t fc, f10; uint8_t _14[0x13C - 0x14]; int32_t h13c; } M1No307;
typedef struct { uint8_t _0[0x20]; uint8_t b20; } M1Ne307;

M1Ne307 *sub_0001D960(int32_t h, int k);
void sub_00147FD0(int32_t h, int k);
void m1_AiReset1134B0(M1Na307 *a);
void sub_00113AA0(void *o, void *a);
void m1_SndStop048250(int32_t h);
void m1_ObjSnd05BE30(int32_t h);
void sub_00033A70(int32_t h);
void m1_AiGoto113040(M1No307 *o, M1Na307 *a, int st);
int  b4c_Enter1456E0j(M1No307 *o, M1Na307 *a, int st, int f);

/* 0x0015CD80: knocked down: one time in 8, while the stun mark (slot 4) is
   free, take it, reset the AI, clear the motion and sounds and go to state
   0x15; otherwise start the fall (move 0x12, gravity -15). */
void m1_KnockDown15CD80(M1No307 *o, M1Na307 *a)
{
    M1Ns307 *t = a->s278;
    M1Ne307 *e;
    uint32_t f;
    if (!(sub_001C7EE1() & 7) && (e = sub_0001D960(t->h38, 4)) != 0 && !(e->b20 & 1)) {
        sub_00147FD0(t->h38, 4);
        t = a->s278;
        m1_AiReset1134B0(a);
        o->fc |= 0xE0;
        o->f10 &= 0xFFFFFECAu;
        a->f4c &= ~0x100u;
        f = t->f40 & 0xFFFBF579u;
        t->f40 = f;
        t->f0 &= ~0x17u;
        t->f4 = -10.0f;
        t->f8 = m1_frameRate42C85C * 10.0f;
        if (f & 0x4000) {
            sub_00113AA0(o, a);
            a->f4c |= 0x200;
            t->f40 &= ~0x4000u;
        }
        if (a->h6c != -1) {
            m1_SndStop048250(a->h6c);
            a->h6c = -1;
        }
        m1_ObjSnd05BE30(o->h13c);
        if (a->h70) {
            sub_00033A70(a->h70);
            a->h70 = 0;
        }
        m1_AiGoto113040(o, a, 0x15);
        return;
    }
    b4c_Enter1456E0j(o, a, 0x12, 0);
    t->f2c = 0.0f;
    t->f28 = 0.0f;
    t->f24 = 0.0f;
    t->f10 = 0.0f;
    t->fc = m1_frameTime42C858 * 0.005f;
    t->f30 = 1.0f;
    t->f4 = -15.0f;
    t->f8 = m1_frameRate42C85C * 10.0f;
    a->f4c &= ~0x70u;
}
