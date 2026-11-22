/* Area m1, group 308: second-boss attack steps. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[8]; uint32_t f8; uint8_t _c[0x144 - 0xC]; void *p144; uint8_t _148[4]; void *p14c;
    uint8_t _150[0x160 - 0x150]; float f160, f164, f168, f16c, f170; } M1Bs308;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0x74 - 0x5C]; float wait74;
    uint8_t _78[0x278 - 0x78]; M1Bs308 *s278; } M1Ba308;
typedef struct { uint8_t _0[0x30]; int32_t h30; uint8_t _34[0x2C]; float pos60[4];
    uint8_t _70[0x128 - 0x70]; uint8_t b128; } M1Bo308;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Bc308;

extern float m1_frameTime42C858, m1_frameRate42C85C;
extern M1Bo308 *g_playerObj;
int32_t sub_000833E0(int32_t h);
int  m1_AiSetState1456E0(M1Bo308 *o, M1Ba308 *a, int st, int f);
int  b4c_Enter1456E0d(M1Bo308 *o, M1Ba308 *a, int st, int f);
int  b4c_Enter1456E0f(M1Bo308 *o, M1Ba308 *a, int st, int f);
void sub_0001D4E0f(M1Bo308 *o);
void sub_0001D4E0g(M1Bo308 *o);
void sub_0001D4E0h(M1Bo308 *o);
float r4_DistanceXZ(float *a, float *b);
float rfl_FacingAngleXZ(M1Bo308 *o, void *p, void *q);
float sub_001A3F30(float x);
void r3_SetStateA(M1Bo308 *o, M1Ba308 *a, int st);          /* regargs: o=EBX a=EDI */
void r3_SetStateB2(M1Bo308 *o, M1Ba308 *a, int st);         /* regargs */
void r3_SetStateB3(M1Bo308 *o, M1Ba308 *a, int st);
M1Bc308 *m1_Quest113400(M1Ba308 *a, int v);

/* 0x00132BF0: second boss's stalk: wait for the clip, then lunge (move 0x22,
   rise at 48/s, 4-degree turn command, 4 s window); during the window grab
   (state 0x14) when within 30 units and facing within 45 degrees, else
   recover (state 5) once the window ends. */
void m1_Stalk132BF0(M1Bo308 *o, M1Ba308 *a)
{
    M1Bs308 *t = a->s278;
    M1Bs308 *s;
    M1Bc308 *c;
    float z, w, d, y;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) return;
        a->st58++;
        return;
    case 1:
        if (m1_AiSetState1456E0(o, a, 0x22, 0) == 1)
            sub_0001D4E0f(o);
        s = a->s278;
        z = m1_frameRate42C85C * 48.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
        s->f16c = 0.0f - z;
        w = m1_frameTime42C858 * 0.0698131695f;
        c = m1_Quest113400(a, 1);
        c->f10 = 0.0872664675f;
        c->f14 = -0.0872664675f;
        if (w != -1.0f)
            c->f18 = w;
        c->f1c = 0.0f;
        a->wait74 = 4.0f;
        a->st58++;
        return;
    case 2:
        d = r4_DistanceXZ(o->pos60, g_playerObj->pos60);
        y = rfl_FacingAngleXZ(o, t->p144, t->p14c);
        if (30.0f >= d && 0.785398185f >= sub_001A3F30(y)) {
            r3_SetStateA(o, a, 0x14);
            return;
        }
        if (0.0f >= a->wait74)
            r3_SetStateA(o, a, 5);
        return;
    }
}

/* 0x00136ED0: second boss's hop attack (as 0x117ED0 with the fields at
   +0x160): take off back at 120/s and up at 80/s, decay until landing, land,
   then state 5 (flag 1) or 1. */
void m1_BossHop136ED0(M1Bo308 *o, M1Ba308 *a)
{
    M1Bs308 *t = a->s278;
    M1Bs308 *s;
    float z;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) return;
        a->st58++;
    case 1:
        if (b4c_Enter1456E0d(o, a, 0x11, 0) == 1)
            sub_0001D4E0g(o);
        s = a->s278;
        z = m1_frameRate42C85C * 80.0f;
        s->f168 = 0.0f - z;
        s->f164 = m1_frameRate42C85C * -120.0f;
        s->f160 = 0.0f;
        s->f16c = 1.0f;
        a->st58++;
        return;
    case 2:
        t->f160 = (1.0f - m1_frameTime42C858 * 0.02f) * t->f160;
        t->f168 = (1.0f - m1_frameTime42C858 * 0.02f) * t->f168;
        if (!(o->b128 & 0x18)) return;
        a->st58++;
    case 3:
        if (b4c_Enter1456E0f(o, a, 0x12, 0) == 1)
            sub_0001D4E0h(o);
        s = a->s278;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f160 = 0.0f;
        s->f16c = 1.0f;
        a->st58++;
        return;
    case 4:
        if (!sub_000833E0(o->h30)) return;
        if (t->f8 & 1) {
            r3_SetStateB2(o, a, 5);
            return;
        }
        r3_SetStateB3(o, a, 1);
        return;
    }
}

typedef struct { float f0[4]; float f10, f14, f18, f1c; float f20[4]; } M1Mx308;
typedef struct { uint8_t _0[0x18]; uint32_t f18; uint8_t _1c[4]; float f20, f24, f28, f2c;
    uint8_t _30[0x88 - 0x30]; float f88, f8c, f90; } M1Ts308;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x278 - 0x21]; M1Ts308 *s278; } M1Ta308;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0xC]; M1Mx308 *p20; uint8_t _24[0x3C];
    float pos60[4]; } M1To308;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Tc308;

extern M1To308 *g_playerObjT308;
int  m1_AiSetState1456E0t(M1To308 *o, M1Ta308 *a, int st, int f);
int  b4c_Enter1456E0dt(M1To308 *o, M1Ta308 *a, int st, int f);
void sub_001AD9F0(float *out, float *a, float *b);
void sub_001AD7E0(float *out, float *v);
void sub_001ADBA0(void *m, float *v, float s);
void sub_001ADA60(M1Mx308 *m, float *a, float *b);
M1Tc308 *m1_Quest113400t(M1Ta308 *a, int v);
int  sub_00036750(M1To308 *o, int k);

/* 0x00187460: turn to the player (facing flag: move 0x31, aim the body at
   the player on the ground plane, float down to height 25) or stand (move
   0x30); then start any pending shake (1/12 s) or push (0.1 s) command,
   otherwise play voice 1. */
void m1_TurnToPlayer187460(M1To308 *o, M1Ta308 *a)
{
    M1Ts308 *t = a->s278;
    M1Ts308 *s;
    M1Tc308 *c;
    float v[4];
    uint32_t f;

    if (a->b20 & 1) {
        m1_AiSetState1456E0t(o, a, 0x31, 0);
        sub_001AD9F0(v, o->pos60, g_playerObjT308->pos60);
        v[1] = 0.0f;
        sub_001AD7E0(v, v);
        sub_001ADBA0(&o->p20->f20, v, -1.0f);
        o->p20->f1c = 0.0f;
        o->p20->f18 = 0.0f;
        o->p20->f10 = 0.0f;
        o->p20->f14 = 1.0f;
        sub_001ADA60(o->p20, &o->p20->f10, o->p20->f20);
        t->f8c = 25.0f;
        t->f88 = 0.0f;
        t->f90 = m1_frameTime42C858 * 0.5f;
    } else {
        b4c_Enter1456E0dt(o, a, 0x30, 0);
        s = a->s278;
        s->f28 = 0.0f;
        s->f24 = 0.0f;
        s->f20 = 0.0f;
        s->f2c = 1.0f;
    }
    f = t->f18;
    if (f & 0x20000) {
        t->f18 = f & ~0x20000u;
        o->f10 |= 4;
        c = m1_Quest113400t(a, 7);
        c->f10 = 0.0833333358f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
    }
    f = t->f18;
    if (f & 0x40) {
        t->f18 = f & ~0x40u;
        o->f10 |= 4;
        c = m1_Quest113400t(a, 6);
        c->f10 = 0.1f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        return;
    }
    sub_00036750(o, 1);
}

typedef struct { uint8_t _0[0xC]; uint32_t fc; uint8_t _10[0x164 - 0x10]; float f164, f168, f16c, f170; } M1Us308;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0x278 - 0x5C]; M1Us308 *s278; } M1Ua308;
typedef struct { uint8_t _0[0x30]; int32_t h30; uint8_t _34[0x128 - 0x34]; uint8_t b128; } M1Uo308;

int  b4c_Enter1456E0iu(M1Uo308 *o, M1Ua308 *a, int st, int f);
int  b4c_Enter1456E0ju(M1Uo308 *o, M1Ua308 *a, int st, int f);
void sub_0001D4E0iu(M1Uo308 *o);
void sub_0001D4E0ju(M1Uo308 *o);
void r3_SetStateAu(M1Uo308 *o, M1Ua308 *a, int st);        /* regargs: o=EBX a=EDI */
void r3_SetStateA2u(M1Uo308 *o, M1Ua308 *a, int st);

/* 0x001325D0: second boss's hop attack variant (fields at +0x164, airborne
   flag 0x10000): ends in state 3 (flag 1) or 7. */
void m1_BossHop1325D0(M1Uo308 *o, M1Ua308 *a)
{
    M1Us308 *t = a->s278;
    M1Us308 *s;
    float z;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) return;
        a->st58++;
    case 1:
        if (b4c_Enter1456E0iu(o, a, 0x11, 0) == 1)
            sub_0001D4E0iu(o);
        s = a->s278;
        z = m1_frameRate42C85C * 80.0f;
        s->f168 = m1_frameRate42C85C * -120.0f;
        s->f164 = 0.0f;
        s->f16c = 0.0f - z;
        s->f170 = 1.0f;
        t->fc |= 0x10000;
        a->st58++;
        return;
    case 2:
        t->f164 = (1.0f - m1_frameTime42C858 * 0.02f) * t->f164;
        t->f16c = (1.0f - m1_frameTime42C858 * 0.02f) * t->f16c;
        if (!(o->b128 & 0x18)) return;
        a->st58++;
    case 3:
        if (b4c_Enter1456E0ju(o, a, 0x12, 0) == 1)
            sub_0001D4E0ju(o);
        s = a->s278;
        s->f16c = 0.0f;
        s->f168 = 0.0f;
        s->f164 = 0.0f;
        s->f170 = 1.0f;
        t->fc &= ~0x10000u;
        a->st58++;
        return;
    case 4:
        if (!sub_000833E0(o->h30)) return;
        if (t->fc & 1) {
            r3_SetStateAu(o, a, 3);
            return;
        }
        r3_SetStateA2u(o, a, 7);
        return;
    }
}

typedef struct { uint8_t _0[0x2C]; float f2c, f30, f34, f38; } M1Vs308;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0x278 - 0x5C]; M1Vs308 *s278; } M1Va308;

int  m1_AiSetState1456E0v(M1Uo308 *o, M1Va308 *a, int st, int f);
int  b4c_Enter1456E0lv(M1Uo308 *o, M1Va308 *a, int st, int f);
int  b4c_Enter1456E0fv(M1Uo308 *o, M1Va308 *a, int st, int f);
void sub_0001D4E0kv(M1Uo308 *o);
void sub_0001D4E0lv(M1Uo308 *o);
void sub_0001D4E0mv(M1Uo308 *o);
void sub_00117580v(M1Uo308 *o, int st);

/* 0x00118130: climb out: wait, jump (move 0x39, up at 10/s), wait, push off
   (move 0x3A, up at 30/s), wait, stand (move 0x3B), wait, then state 1.
   Through step 4 the speed decays by 2% per frame unit. */
void m1_ClimbOut118130(M1Uo308 *o, M1Va308 *a)
{
    M1Vs308 *t = a->s278;
    M1Vs308 *s;
    float z;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 1:
        if (m1_AiSetState1456E0v(o, a, 0x39, 0) == 1)
            sub_0001D4E0kv(o);
        s = a->s278;
        z = m1_frameRate42C85C * 10.0f;
        s->f30 = 0.0f;
        s->f2c = 0.0f;
        s->f38 = 1.0f;
        s->f34 = 0.0f - z;
        a->st58++;
        break;
    case 2:
        if (sub_000833E0(o->h30))
            a->st58++;
        break;
    case 3:
        if (b4c_Enter1456E0lv(o, a, 0x3A, 0) == 1)
            sub_0001D4E0lv(o);
        s = a->s278;
        s->f34 = 0.0f - m1_frameRate42C85C * 30.0f;
        goto rest;
    case 4:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 5:
        if (b4c_Enter1456E0fv(o, a, 0x3B, 0) == 1)
            sub_0001D4E0mv(o);
        s = a->s278;
        s->f34 = 0.0f;
    rest:
        s->f30 = 0.0f;
        s->f2c = 0.0f;
        s->f38 = 1.0f;
        a->st58++;
        break;
    case 6:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 7:
        sub_00117580v(o, 1);
        return;
    }
    if (a->st58 <= 4) {
        t->f2c = (1.0f - m1_frameTime42C858 * 0.02f) * t->f2c;
        t->f34 = (1.0f - m1_frameTime42C858 * 0.02f) * t->f34;
    }
}
