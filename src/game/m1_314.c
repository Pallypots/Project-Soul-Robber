/* Area m1, group 314: leap attacks. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[4]; uint32_t f4; uint8_t _8[0x2C - 8]; float f2c, f30, f34, f38;
    uint8_t _3c[0x48 - 0x3C]; float f48; } M1Js314;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[8]; int32_t st64;
    uint8_t _68[0x278 - 0x68]; M1Js314 *s278; } M1Ja314;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; int32_t h30;
    uint8_t _34[0x128 - 0x34]; uint8_t b128; } M1Jo314;

extern float m1_frameTime42C858;
int32_t sub_000833E0(int32_t h);
int32_t sub_000833E0b(int32_t h);
int32_t sub_000833E0c(int32_t h);
int  m1_AiSetState1456E0(M1Jo314 *o, M1Ja314 *a, int st, int f);
int  b4c_Enter1456E0d(M1Jo314 *o, M1Ja314 *a, int st, int f);
int  b4c_Enter1456E0f(M1Jo314 *o, M1Ja314 *a, int st, int f);
void sub_0001D4E0f(M1Jo314 *o);
void sub_0001D4E0g(M1Jo314 *o);
void sub_0001D4E0h(M1Jo314 *o);
int  sub_001154D0(M1Ja314 *a, M1Jo314 *o);                  /* regargs: a=EAX */
int  sub_001154D0b(M1Ja314 *a, M1Jo314 *o);
void sub_00117580(M1Jo314 *o, int st);

/* 0x001192A0: leap attack variant: as 0x118900 but flag 0x10 is checked
   when the landing clip ends (state 0x23), and only the speed decays (5%)
   while airborne. */
void m1_LeapAttack1192A0(M1Jo314 *o, M1Ja314 *a)
{
    M1Js314 *t = a->s278;
    M1Js314 *s;
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
        if (t->f4 & 0x10) {
            sub_00117580(o, 0x23);
            return;
        }
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
    }
}

typedef struct { uint8_t _0[0xC]; uint32_t fc; uint8_t _10[0x164 - 0x10]; float f164, f168, f16c, f170;
    uint8_t _174[0x184 - 0x174]; float f184; } M1Ks314;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[8]; int32_t st64;
    uint8_t _68[0x278 - 0x68]; M1Ks314 *s278; } M1Ka314;

int  m1_AiSetState1456E0k(M1Jo314 *o, M1Ka314 *a, int st, int f);
int  b4c_Enter1456E0dk(M1Jo314 *o, M1Ka314 *a, int st, int f);
int  b4c_Enter1456E0fk(M1Jo314 *o, M1Ka314 *a, int st, int f);
int32_t r2_PlayerInFrontB(M1Ka314 *a, M1Jo314 *o);         /* regargs: a=EAX */
void r3_SetStateA(M1Jo314 *o, M1Ka314 *a, int st);          /* regargs: o=EBX a=EDI */
int  sub_001C7EE1(void);                                    /* rand */

/* 0x00134670: second boss's leap attack (fields at +0x164): wind up, take
   off, wait to land, land, wait (state 0x2B on flag 0x20), recover (flag 4),
   wait, then react to a player in front (0x15 one time in 8, else 0xE) or go
   to state 5. Speed decays by 5% up to step 2. Unknown moves hang. */
void m1_BossLeap134670(M1Jo314 *o, M1Ka314 *a)
{
    M1Ks314 *t = a->s278;
    M1Ks314 *s;
    int32_t k, st;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 1:
        k = a->st64;
        if (k == 0x34)      st = 0x35;
        else if (k == 0x38) st = 0x39;
        else for (;;) ;
        if (m1_AiSetState1456E0k(o, a, st, 0) == 1)
            sub_0001D4E0f(o);
        a->st58++;
    case 2:
        if (o->b128 & 0x18) {
        inc:
            a->st58++;
        }
        break;
    case 3:
        k = a->st64;
        if (k == 0x35)      st = 0x36;
        else if (k == 0x39) st = 0x3A;
        else for (;;) ;
        if (b4c_Enter1456E0dk(o, a, st, 0) == 1)
            sub_0001D4E0g(o);
        s = a->s278;
        s->f16c = 0.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
        a->st58++;
        break;
    case 4:
        if (!sub_000833E0b(o->h30)) break;
        if (t->fc & 0x20) {
            r3_SetStateA(o, a, 0x2B);
            return;
        }
        a->st58++;
    case 5:
        k = a->st64;
        if (k == 0x36)      st = 0x37;
        else if (k == 0x3A) st = 0x3B;
        else for (;;) ;
        if (b4c_Enter1456E0fk(o, a, st, 0) == 1)
            sub_0001D4E0h(o);
        s = a->s278;
        s->f16c = 0.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
        o->f10 |= 4;
        goto inc;
    case 6:
        if (!sub_000833E0c(o->h30)) break;
        a->st58++;
    case 7:
        if (r2_PlayerInFrontB(a, o)) {
            t->f184 = 0.3f;
            if (!(sub_001C7EE1() & 7)) {
                r3_SetStateA(o, a, 0x15);
                return;
            }
            r3_SetStateA(o, a, 0xE);
            return;
        }
        r3_SetStateA(o, a, 5);
        return;
    }
    if (a->st58 <= 2) {
        t->f164 = (1.0f - m1_frameTime42C858 * 0.05f) * t->f164;
        t->f16c = (1.0f - m1_frameTime42C858 * 0.05f) * t->f16c;
    }
}

int32_t r2_PlayerInFrontBk(M1Ka314 *a, M1Jo314 *o);

/* 0x001343D0: second boss's leap attack (as 0x118CD0 with the fields at
   +0x164 and airborne flag 0x10000): from step 5 on a player in front
   triggers the reaction (0x15 one time in 4, else 0xE); at the end state
   0x2B on flag 0x20, react, or state 5. Speed decays by 2% up to step 4. */
void m1_BossLeap1343D0(M1Jo314 *o, M1Ka314 *a)
{
    M1Ks314 *t = a->s278;
    M1Ks314 *s;
    int32_t k, st;
    if (!(t->fc & 0x20) && a->st58 >= 5 && r2_PlayerInFrontB(a, o))
        goto react;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 1:
        k = a->st64;
        if (k == 0x34)      st = 0x35;
        else if (k == 0x38) st = 0x39;
        else for (;;) ;
        if (m1_AiSetState1456E0k(o, a, st, 0) == 1)
            sub_0001D4E0f(o);
        a->st58++;
    case 2:
        if (o->b128 & 0x18) {
            o->f10 &= ~0x10u;
            t->fc &= ~0x10000u;
        inc:
            a->st58++;
        }
        break;
    case 3:
        k = a->st64;
        if (k == 0x35)      st = 0x36;
        else if (k == 0x39) st = 0x3A;
        else for (;;) ;
        if (b4c_Enter1456E0dk(o, a, st, 0) == 1)
            sub_0001D4E0g(o);
        s = a->s278;
        s->f16c = 0.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
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
        if (b4c_Enter1456E0fk(o, a, st, 0) == 1)
            sub_0001D4E0h(o);
        s = a->s278;
        s->f16c = 0.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
        o->f10 |= 4;
        goto inc;
    case 6:
        if (!sub_000833E0c(o->h30)) break;
        a->st58++;
    case 7:
        if (t->fc & 0x20) {
            r3_SetStateA(o, a, 0x2B);
            return;
        }
        if (r2_PlayerInFrontBk(a, o)) {
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
    if (a->st58 <= 4) {
        t->f164 = (1.0f - m1_frameTime42C858 * 0.02f) * t->f164;
        t->f16c = (1.0f - m1_frameTime42C858 * 0.02f) * t->f16c;
    }
}

/* 0x00134110: second boss's leap attack variant: as 0x1343D0, but the early
   reaction picks 0x15 one time in 4 and the final one one time in 8, and
   the speed decays by 5% up to step 2. */
void m1_BossLeap134110(M1Jo314 *o, M1Ka314 *a)
{
    M1Ks314 *t = a->s278;
    M1Ks314 *s;
    int32_t k, st, r;
    if (!(t->fc & 0x20) && a->st58 >= 5 && r2_PlayerInFrontB(a, o)) {
        t->f184 = 0.3f;
        r = sub_001C7EE1() & 3;
        goto pick;
    }
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 1:
        k = a->st64;
        if (k == 0x34)      st = 0x35;
        else if (k == 0x38) st = 0x39;
        else for (;;) ;
        if (m1_AiSetState1456E0k(o, a, st, 0) == 1)
            sub_0001D4E0f(o);
        a->st58++;
    case 2:
        if (o->b128 & 0x18) {
            o->f10 &= ~0x10u;
            t->fc &= ~0x10000u;
        inc:
            a->st58++;
        }
        break;
    case 3:
        k = a->st64;
        if (k == 0x35)      st = 0x36;
        else if (k == 0x39) st = 0x3A;
        else for (;;) ;
        if (b4c_Enter1456E0dk(o, a, st, 0) == 1)
            sub_0001D4E0g(o);
        s = a->s278;
        s->f16c = 0.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
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
        if (b4c_Enter1456E0fk(o, a, st, 0) == 1)
            sub_0001D4E0h(o);
        s = a->s278;
        s->f16c = 0.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
        o->f10 |= 4;
        goto inc;
    case 6:
        if (!sub_000833E0c(o->h30)) break;
        a->st58++;
    case 7:
        if (t->fc & 0x20) {
            r3_SetStateA(o, a, 0x2B);
            return;
        }
        if (r2_PlayerInFrontBk(a, o)) {
            t->f184 = 0.3f;
            r = sub_001C7EE1() & 7;
        pick:
            if (!r) {
                r3_SetStateA(o, a, 0x15);
                return;
            }
            r3_SetStateA(o, a, 0xE);
            return;
        }
        r3_SetStateA(o, a, 5);
        return;
    }
    if (a->st58 <= 2) {
        t->f164 = (1.0f - m1_frameTime42C858 * 0.05f) * t->f164;
        t->f16c = (1.0f - m1_frameTime42C858 * 0.05f) * t->f16c;
    }
}
