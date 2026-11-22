/* Area m1, group 316. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[0xC]; uint32_t fc; uint8_t _10[0x164 - 0x10]; float f164, f168, f16c, f170;
    uint8_t _174[0x184 - 0x174]; float f184; } M1Ks316;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[8]; int32_t st64;
    uint8_t _68[0x278 - 0x68]; M1Ks316 *s278; } M1Ka316;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; int32_t h30;
    uint8_t _34[0x128 - 0x34]; uint8_t b128; } M1Ko316;

extern float m1_frameTime42C858, m1_frameRate42C85C;
int32_t sub_000833E0(int32_t h);
int32_t sub_000833E0b(int32_t h);
int32_t sub_000833E0c(int32_t h);
int  m1_AiSetState1456E0k(M1Ko316 *o, M1Ka316 *a, int st, int f);
int  b4c_Enter1456E0dk(M1Ko316 *o, M1Ka316 *a, int st, int f);
int  b4c_Enter1456E0fk(M1Ko316 *o, M1Ka316 *a, int st, int f);
void sub_0001D4E0f(M1Ko316 *o);
void sub_0001D4E0g(M1Ko316 *o);
void sub_0001D4E0h(M1Ko316 *o);
int32_t r2_PlayerInFrontB(M1Ka316 *a, M1Ko316 *o);         /* regargs: a=EAX */
int32_t r2_PlayerInFrontBk(M1Ka316 *a, M1Ko316 *o);
void r3_SetStateA(M1Ko316 *o, M1Ka316 *a, int st);          /* regargs: o=EBX a=EDI */
int  sub_001C7EE1(void);                                    /* rand */

/* 0x00133BA0: second boss's leap attack (as 0x118900): landing clears the
   airborne flags 0x10004; up to step 2 the speed decays by 5% and gravity
   adds 147 per frame unit squared; a player in front from step 5 on
   triggers the reaction (0x15 one time in 4, else 0xE). */
void m1_BossLeap133BA0(M1Ko316 *o, M1Ka316 *a)
{
    M1Ks316 *t = a->s278;
    M1Ks316 *s;
    int32_t k, st;
    float fr;
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
            t->fc &= ~0x10004u;
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
    if (a->st58 <= 2) {
        t->f164 = (1.0f - m1_frameTime42C858 * 0.05f) * t->f164;
        t->f16c = (1.0f - m1_frameTime42C858 * 0.05f) * t->f16c;
        fr = m1_frameRate42C85C;
        t->f168 = fr * fr * 147.0f + t->f168;
    }
}

typedef struct { uint8_t _0[0x14]; void *p14; } M1Mm316;
typedef struct { uint8_t _0[0x14]; uint32_t f14; uint8_t _18[0xC0 - 0x18]; } M1Hl316;
typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64; uint8_t _68[0x34C - 0x68]; int32_t f34c;
    uint8_t _350[0x41C - 0x350]; M1Hl316 l41c[4];
} M1Hs316;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c; uint8_t _50[8];
    int32_t st58; uint8_t _5c[8]; int32_t st64; uint8_t _68[0x74 - 0x68]; float wait74;
    uint8_t _78[0x278 - 0x78]; M1Hs316 *s278; } M1Ha316;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; M1Mm316 *m30; uint8_t _34[0x2C];
    uint8_t pos60[0x10]; } M1Ho316;
typedef struct { int32_t f0; uint8_t _4[0xC]; float f10, f14, f18, f1c; } M1Hc316;

int  b4c_Enter1456E0d(M1Ho316 *o, M1Ha316 *a, int st, int f);
int  b4c_Enter1456E0f(M1Ho316 *o, M1Ha316 *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void sub_000F5D40b(float *d, const float *s);
void sub_00113AA0(void *o, void *a);
int  sub_000494D0(int id, void *p, int f);
int  sub_00036750(M1Ho316 *o, int k);
M1Hc316 *m1_Quest113400(M1Ha316 *a, int v);
M1Hc316 *m1_Quest113400g(M1Ha316 *a, int v);
void sub_00083120(M1Mm316 *m, int k);
void m1_AnimSpeed1B1190(void *p, float s);
void sub_001AEDD0(void *p, float s);

/* 0x00129920: enter the slam: a pending knock (flag 0x20) starts move 6,
   plays sound 0xF7 and voice 0xE/0, starts the knock command and goes to
   phase 10. Otherwise (moves 0x23/0x24 restart move 0x10 at a random speed
   of 1, 8, 10 or 16) reset the blend, flag the four sway channels, set the
   window by weight class (2.5 / 4 / 5.5 s; others hang) and start the
   1/60 s shake command. */
void m1_EnterSlam129920(M1Ho316 *o, M1Ha316 *a)
{
    M1Hs316 *t = a->s278;
    M1Hs316 *s;
    M1Hc316 *c;
    M1Hl316 *p;
    M1Mm316 *m;
    float spd[4];
    float x, w;
    int32_t i, k;
    volatile int32_t v;

    spd[0] = 1.0f;
    spd[1] = 8.0f;
    spd[2] = 10.0f;
    spd[3] = 16.0f;
    if (t->f4 & 0x20) {
        b4c_Enter1456E0d(o, a, 6, 0);
        s = a->s278;
        x = m1_frameTime42C858 * (1.0f / 30.0f);
        sub_000F5D40(s->v40, s->v30);
        s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
        s->f5c = 1.0f;
        s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
        s->f64 = x;
        sub_00113AA0(o, a);
        sub_000494D0(0xF7, o->pos60, 0);
        v = 0;
        if (a->b20 & 1) v = 0xE;
        sub_00036750(o, v);
        o->f10 |= 0xD;
        a->f4c &= ~0x1000070u;
        c = m1_Quest113400(a, 6);
        c->f10 = 1.0f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        if (c->f0) c->f0 = 2;
        a->st58 = 10;
        return;
    }
    k = a->st64;
    if (k == 0x23 || k == 0x24) {
        b4c_Enter1456E0f(o, a, 0x10, 0);
        m = o->m30;
        sub_00083120(m, 0x10);
        m1_AnimSpeed1B1190(m->p14, spd[sub_001C7EE1() & 3]);
        sub_001AEDD0(m->p14, 0.5f);
    }
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40b(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    p = t->l41c;
    for (i = 4; i != 0; i--, p++)
        p->f14 |= 4;
    t->f4 |= 0x4000000;
    k = t->f34c;
    if (k == 0)      w = 2.5f;
    else if (k == 1) w = 4.0f;
    else if (k == 2) w = 5.5f;
    else for (;;) ;
    a->wait74 = w;
    o->f10 |= 4;
    c = m1_Quest113400g(a, 8);
    c->f10 = 1.0f / 60.0f;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1c = 0.0f;
}
