/* Area m1, group 313: jump attacks. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[4]; uint32_t f4; uint8_t _8[0x2C - 8]; float f2c, f30, f34, f38;
    uint8_t _3c[0x48 - 0x3C]; float f48; } M1Js313;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[8]; int32_t st64;
    uint8_t _68[0x278 - 0x68]; M1Js313 *s278; } M1Ja313;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; int32_t h30;
    uint8_t _34[0x128 - 0x34]; uint8_t b128; } M1Jo313;

extern float m1_frameTime42C858, m1_frameRate42C85C;
int32_t sub_000833E0(int32_t h);
int32_t sub_000833E0b(int32_t h);
int32_t sub_000833E0c(int32_t h);
int32_t sub_000833E0w(int32_t h);
int  m1_AiSetState1456E0(M1Jo313 *o, M1Ja313 *a, int st, int f);
int  b4c_Enter1456E0d(M1Jo313 *o, M1Ja313 *a, int st, int f);
int  b4c_Enter1456E0f(M1Jo313 *o, M1Ja313 *a, int st, int f);
void sub_0001D4E0f(M1Jo313 *o);
void sub_0001D4E0g(M1Jo313 *o);
void sub_0001D4E0h(M1Jo313 *o);
int  sub_001154D0(M1Ja313 *a, M1Jo313 *o);                  /* regargs: a=EAX */
int  sub_001154D0b(M1Ja313 *a, M1Jo313 *o);
void sub_00117580(M1Jo313 *o, int st);

/* 0x00118CD0: leap attack: wind up, take off (move 0x34->0x35 / 0x38->0x39),
   wait to land, land (+1), wait, recover (+1, flag 4), wait, then leave on
   flag 0x10 (state 0x23), react to a hit (state 9, also checked from step 5
   on) or go to state 1. Speed decays by 2% per frame unit up to step 4.
   Unknown moves hang. */
void m1_LeapAttack118CD0(M1Jo313 *o, M1Ja313 *a)
{
    M1Js313 *t = a->s278;
    M1Js313 *s;
    int32_t k, st;
    if (!(t->f4 & 0x10) && a->st58 >= 5 && sub_001154D0(a, o))
        goto hit;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 1:
        k = a->st64;
        if (k == 0x34)      st = 0x35;
        else if (k == 0x38) st = 0x39;
        else for (;;) ;
        if (m1_AiSetState1456E0(o, a, st, 0) == 1)
            sub_0001D4E0f(o);
        a->st58++;
    case 2:
        if (o->b128 & 0x18) {
            o->f10 &= ~0x10u;
            t->f4 &= ~0x4000u;
        inc:
            a->st58++;
        }
        break;
    case 3:
        k = a->st64;
        if (k == 0x35)      st = 0x36;
        else if (k == 0x39) st = 0x3A;
        else for (;;) ;
        if (b4c_Enter1456E0d(o, a, st, 0) == 1)
            sub_0001D4E0g(o);
        s = a->s278;
        s->f34 = 0.0f;
        s->f30 = 0.0f;
        s->f2c = 0.0f;
        s->f38 = 1.0f;
        a->st58++;
        break;
    case 4:
        if (!sub_000833E0b(o->h30)) break;
        a->st58++;
    case 5:
        k = a->st64;
        if (k == 0x36)      st = 0x37;
        else if (k == 0x3A) st = 0x3B;
        else for (;;) ;
        if (b4c_Enter1456E0f(o, a, st, 0) == 1)
            sub_0001D4E0h(o);
        s = a->s278;
        s->f34 = 0.0f;
        s->f30 = 0.0f;
        s->f2c = 0.0f;
        s->f38 = 1.0f;
        o->f10 |= 4;
        goto inc;
    case 6:
        if (!sub_000833E0c(o->h30)) break;
        a->st58++;
    case 7:
        if (t->f4 & 0x10) {
            sub_00117580(o, 0x23);
            return;
        }
        if (sub_001154D0b(a, o)) {
        hit:
            t->f48 = 0.3f;
            sub_00117580(o, 9);
            return;
        }
        sub_00117580(o, 1);
        return;
    }
    if (a->st58 <= 4) {
        t->f2c = (1.0f - m1_frameTime42C858 * 0.02f) * t->f2c;
        t->f34 = (1.0f - m1_frameTime42C858 * 0.02f) * t->f34;
    }
}

/* 0x00118900: as 0x118CD0 but landing also clears flag 1, and while
   airborne (up to step 2) the speed decays by 5% and gravity adds 147 per
   frame unit squared. */
void m1_LeapAttack118900(M1Jo313 *o, M1Ja313 *a)
{
    M1Js313 *t = a->s278;
    M1Js313 *s;
    int32_t k, st;
    float fr;
    if (!(t->f4 & 0x10) && a->st58 >= 5 && sub_001154D0(a, o))
        goto hit;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 1:
        k = a->st64;
        if (k == 0x34)      st = 0x35;
        else if (k == 0x38) st = 0x39;
        else for (;;) ;
        if (m1_AiSetState1456E0(o, a, st, 0) == 1)
            sub_0001D4E0f(o);
        a->st58++;
    case 2:
        if (o->b128 & 0x18) {
            o->f10 &= ~0x10u;
            t->f4 &= ~0x4001u;
        inc:
            a->st58++;
        }
        break;
    case 3:
        k = a->st64;
        if (k == 0x35)      st = 0x36;
        else if (k == 0x39) st = 0x3A;
        else for (;;) ;
        if (b4c_Enter1456E0d(o, a, st, 0) == 1)
            sub_0001D4E0g(o);
        s = a->s278;
        s->f34 = 0.0f;
        s->f30 = 0.0f;
        s->f2c = 0.0f;
        s->f38 = 1.0f;
        a->st58++;
        break;
    case 4:
        if (!sub_000833E0b(o->h30)) break;
        a->st58++;
    case 5:
        k = a->st64;
        if (k == 0x36)      st = 0x37;
        else if (k == 0x3A) st = 0x3B;
        else for (;;) ;
        if (b4c_Enter1456E0f(o, a, st, 0) == 1)
            sub_0001D4E0h(o);
        s = a->s278;
        s->f34 = 0.0f;
        s->f30 = 0.0f;
        s->f2c = 0.0f;
        s->f38 = 1.0f;
        o->f10 |= 4;
        goto inc;
    case 6:
        if (!sub_000833E0c(o->h30)) break;
        a->st58++;
    case 7:
        if (t->f4 & 0x10) {
            sub_00117580(o, 0x23);
            return;
        }
        if (sub_001154D0b(a, o)) {
        hit:
            t->f48 = 0.3f;
            sub_00117580(o, 9);
            return;
        }
        sub_00117580(o, 1);
        return;
    }
    if (a->st58 <= 2) {
        t->f2c = (1.0f - m1_frameTime42C858 * 0.05f) * t->f2c;
        t->f34 = (1.0f - m1_frameTime42C858 * 0.05f) * t->f34;
        fr = m1_frameRate42C85C;
        t->f30 = fr * fr * 147.0f + t->f30;
    }
}
