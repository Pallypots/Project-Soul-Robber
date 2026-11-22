/* Area m1, group 319. Names inferred. */
#include <stdint.h>

typedef struct { uint32_t f0; uint8_t _4[0x4C]; uint32_t f50; uint8_t _54[0x18]; float f6c; } M1Ps319;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[8]; int32_t st58; float f5c;
    uint8_t _60[0x6C - 0x60]; int32_t h6c, h70; uint8_t _74[0x278 - 0x74]; M1Ps319 *s278; } M1Pa319;
typedef struct { uint8_t _0[0xC]; uint32_t fc, f10; uint8_t _14[0x1C]; int32_t h30; uint8_t _34[0x2C];
    float pos60[4]; uint8_t _70[0x13C - 0x70]; int32_t h13c; } M1Po319;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Pc319;

extern float m1_frameTime42C858, m1_frameRate42C85C;
extern M1Po319 *g_playerObj;
int32_t sub_000833E0(int32_t h);
int32_t sub_000833E0b(int32_t h);
int  m1_AiSetState1456E0(M1Po319 *o, M1Pa319 *a, int st, int f);
void sub_00156180(M1Ps319 *s, float a, float b, float c, float d);
int  sub_00036750(M1Po319 *o, int k);
M1Pc319 *m1_Quest113400(M1Pa319 *a, int v);
M1Pc319 *m1_Quest113400g(M1Pa319 *a, int v);
int  sub_00156040(M1Po319 *o);                              /* regargs: o=ESI */
void m1_AiReset1134B0(M1Pa319 *a);
void m1_AiSway1561D0(M1Ps319 *s, float a, float b);
void sub_00113AA0(void *o, void *a);
void sub_00113190(M1Po319 *o, M1Pa319 *a, int k);
void m1_SndStop048250(int32_t h);
void m1_ObjSnd05BE30(int32_t h);
void sub_00033A70(int32_t h);
void m1_AiGoto113040(M1Po319 *o, M1Pa319 *a, int st);
float r4_DistanceXZ(float *a, float *b);
void sub_00147580(M1Po319 *o, int st, M1Pa319 *a);         /* regargs: st=EBX a=ESI */
void sub_00147580b(M1Po319 *o, int st, M1Pa319 *a);

/* 0x0014B5B0: dash and recover: wait for the clip, start move 0x22 (back at
   2/s with the slow drift), lock the body, voice 1, the chase command
   (17, 2, 1) and the scale pulse (0.1, 0.1, 1/30, 1); when it ends either
   reset the AI and go to state 0xC (0x156040 agrees) or pick the follow-up
   by distance to the player (4 under 50 units, else 2). */
void m1_DashRecover14B5B0(M1Po319 *o, M1Pa319 *a)
{
    M1Ps319 *t = a->s278;
    M1Ps319 *s;
    M1Pc319 *c;
    uint32_t g;
    switch (a->st58) {
    case 0:
        if (sub_000833E0b(o->h30))
            a->st58++;
        return;
    case 1:
        m1_AiSetState1456E0(o, a, 0x22, 0);
        sub_00156180(t, m1_frameRate42C85C * -2.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.003f);
        a->f4c &= ~0x70u;
        o->f10 |= 6;
        t->f6c = 0.0f;
        sub_00036750(o, 1);
        c = m1_Quest113400(a, 4);
        c->f10 = 17.0f;
        c->f14 = 2.0f;
        c->f18 = 1.0f;
        c->f1c = 0.0f;
        c = m1_Quest113400g(a, 5);
        c->f10 = 0.1f;
        c->f14 = 0.1f;
        c->f18 = 1.0f / 30.0f;
        c->f1c = 1.0f;
        a->f5c = 0.0f;
        a->st58++;
        return;
    case 2:
        if (!sub_000833E0(o->h30)) return;
        if (sub_00156040(o)) {
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
            m1_AiGoto113040(o, a, 0xC);
            return;
        }
        if (!(r4_DistanceXZ(g_playerObj->pos60, o->pos60) >= 50.0f)) {
            sub_00147580(o, 4, a);
            return;
        }
        sub_00147580b(o, 2, a);
        return;
    }
}
