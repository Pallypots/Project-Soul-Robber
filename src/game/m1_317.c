/* Area m1, group 317. Names inferred. */
#include <stdint.h>

typedef struct { uint32_t f0; uint8_t _4[0x3C]; float v40[4]; uint32_t f50; } M1Ss317;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c; uint8_t _50[8];
    int32_t st58; uint8_t _5c[0x6C - 0x5C]; int32_t h6c, h70; uint8_t _74[0x278 - 0x74]; M1Ss317 *s278; } M1Sa317;
typedef struct { uint8_t _0[0xC]; uint32_t fc, f10; uint8_t _14[0x4C]; float pos60[4];
    uint8_t _70[0x13C - 0x70]; int32_t h13c; } M1So317;
typedef struct { int32_t f0; uint8_t _4[0xC]; float f10, f14, f18, f1c; } M1Sc317;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
float sub_001B2730(float *a, float *b);
int  m1_AiSetState1456E0(M1So317 *o, M1Sa317 *a, int st, int f);
int  sub_00036750(M1So317 *o, int k);
int  sub_000494D0(int id, void *p, int f);
M1Sc317 *m1_Quest113400(M1Sa317 *a, int v);
M1Sc317 *m1_Quest113400g(M1Sa317 *a, int v);
void m1_AiReset1134B0(M1Sa317 *a);
void m1_AiSway1561D0(M1Ss317 *s, float a, float b);
void sub_00113AA0(void *o, void *a);
void sub_00113190(M1So317 *o, M1Sa317 *a, int k);
void m1_SndStop048250(int32_t h);
void m1_ObjSnd05BE30(int32_t h);
void sub_00033A70(int32_t h);
void m1_AiGoto113040(M1So317 *o, M1Sa317 *a, int st);
void sub_00156180(M1Ss317 *s, float a, float b, float c, float d);

/* 0x00153650: stun trap: wait until o is 15 units from its anchor, start
   move 0x42, and when the trap fires (flag 0x10): voice 4, sound 0x130,
   the stun command, reset the AI, motion and sounds, go to state 0, start
   the slow drift and, when facing, the push-back command (20, 2). */
void m1_StunTrap153650(M1So317 *o, M1Sa317 *a)
{
    M1Ss317 *t = a->s278;
    M1Ss317 *s;
    M1Sc317 *c;
    float f;
    uint32_t g;
    switch (a->st58) {
    case 0:
        if (sub_001B2730(o->pos60, t->v40) >= 15.0f)
            a->st58++;
        return;
    case 1:
        m1_AiSetState1456E0(o, a, 0x42, 0);
        a->st58++;
        return;
    case 2:
        if (!(t->f50 & 0x10)) return;
        sub_00036750(o, 4);
        sub_000494D0(0x130, o->pos60, 0);
        o->f10 |= 0xD;
        a->f4c &= ~0x1000070u;
        f = m1_fps42C964;
        c = m1_Quest113400(a, 8);
        if (f != -1.0f)
            c->f10 = f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        if (c->f0) c->f0 = 2;
        s = a->s278;
        m1_AiReset1134B0(a);
        o->fc |= 0xE0;
        o->f10 &= 0xFFFFFEC8u;
        a->f4c &= ~0x100u;
        s->f0 &= ~0x17u;
        s->f50 &= 0xFFDBEEBFu;
        m1_AiSway1561D0(s, -10.0f, m1_frameRate42C85C * 10.0f);
        if (s->f50 & 0x10000) {
            sub_00113AA0(o, a);
            a->f4c |= 0x200;
            s->f50 &= ~0x10000u;
        }
        g = s->f50;
        if (g & 0x100000) {
            s->f50 = g & ~0x100000u;
            sub_00113190(o, a, 1);
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
        m1_AiGoto113040(o, a, 0);
        sub_00156180(t, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.003f);
        t->f0 |= 3;
        if (a->b20 & 1) {
            c = m1_Quest113400g(a, 4);
            c->f10 = 20.0f;
            c->f14 = 2.0f;
            c->f18 = 0.0f;
            c->f1c = 0.0f;
            if (c->f0) c->f0 = 2;
        }
        return;
    }
}

typedef struct { uint32_t f0; float f4, f8, fc, f10; uint8_t _14[0x10]; float f24, f28, f2c, f30;
    uint8_t _34[0xC]; uint32_t f40; uint8_t _44[0x30]; float v74[4]; } M1Ts317;
typedef struct { uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4c; uint8_t _50[8];
    int32_t st58; uint8_t _5c[0x6C - 0x5C]; int32_t h6c, h70; uint8_t _74[0x278 - 0x74]; M1Ts317 *s278; } M1Ta317;

float sub_001B2730b(float *a, float *b);
int  b4c_Enter1456E0d(M1So317 *o, M1Ta317 *a, int st, int f);
M1Sc317 *m1_Quest113400h(M1Ta317 *a, int v);
M1Sc317 *m1_Quest113400t(M1Ta317 *a, int v);
void m1_AiReset1134B0b(M1Ta317 *a);
void m1_AiGoto113040b(M1So317 *o, M1Ta317 *a, int st);
int  sub_00036750b(M1So317 *o, int k);
int  sub_000494D0b(int id, void *p, int f);

/* 0x00164C90: stun trap (knock-down layout, as 0x153650): trigger flag 0x10
   at +0x40, stun command 7; on firing reset the motion (height speed -10,
   10/s), go to state 0, stand still with a slow drift and, when facing,
   push back (0.5, 2). */
void m1_StunTrap164C90(M1So317 *o, M1Ta317 *a)
{
    M1Ts317 *t = a->s278;
    M1Ts317 *s;
    M1Sc317 *c;
    float f;
    switch (a->st58) {
    case 0:
        if (sub_001B2730b(o->pos60, t->v74) >= 15.0f)
            a->st58++;
        return;
    case 1:
        b4c_Enter1456E0d(o, a, 0x42, 0);
        a->st58++;
        return;
    case 2:
        if (!(t->f40 & 0x10)) return;
        sub_00036750b(o, 4);
        sub_000494D0b(0x130, o->pos60, 0);
        o->f10 |= 0xD;
        a->f4c &= ~0x1000070u;
        f = m1_fps42C964;
        c = m1_Quest113400h(a, 7);
        if (f != -1.0f)
            c->f10 = f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        if (c->f0) c->f0 = 2;
        s = a->s278;
        m1_AiReset1134B0b(a);
        o->fc |= 0xE0;
        o->f10 &= 0xFFFFFECAu;
        a->f4c &= ~0x100u;
        s->f40 &= 0xFFFBF579u;
        s->f0 &= ~0x17u;
        s->f4 = -10.0f;
        s->f8 = m1_frameRate42C85C * 10.0f;
        if (s->f40 & 0x4000) {
            sub_00113AA0(o, a);
            a->f4c |= 0x200;
            s->f40 &= ~0x4000u;
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
        m1_AiGoto113040b(o, a, 0);
        t->f2c = 0.0f;
        t->f28 = 0.0f;
        t->f24 = 0.0f;
        t->f30 = 1.0f;
        t->f10 = 0.0f;
        t->fc = m1_frameTime42C858 * 0.005f;
        t->f0 |= 3;
        if (a->b20 & 1) {
            c = m1_Quest113400t(a, 5);
            c->f10 = 0.5f;
            c->f14 = 2.0f;
            c->f18 = 0.0f;
            c->f1c = 0.0f;
            if (c->f0) c->f0 = 2;
        }
        return;
    }
}
