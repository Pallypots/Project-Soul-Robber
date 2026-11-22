/* Area m1, group 318. Names inferred. */
#include <stdint.h>

typedef struct { uint32_t f0; float f4, f8, fc, f10; uint8_t _14[0x10]; float f24, f28, f2c, f30;
    uint8_t _34[0xC]; uint32_t f40; uint8_t _44[0x30]; float v74[4]; } M1Ns318;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[8]; int32_t st58; float f5c;
    uint8_t _60[0x6C - 0x60]; int32_t h6c, h70; uint8_t _74[0x278 - 0x74]; M1Ns318 *s278; } M1Na318;
typedef struct { uint8_t _0[0xC]; uint32_t fc, f10; uint8_t _14[0x1C]; int32_t h30; uint8_t _34[0x2C];
    float pos60[4]; uint8_t _70[0x128 - 0x70]; uint8_t b128; uint8_t _129[0x13C - 0x129]; int32_t h13c; } M1No318;

extern float m1_frameTime42C858, m1_frameRate42C85C;
int  sub_00156040(M1No318 *o);                              /* regargs: o=ESI */
void m1_AiReset1134B0(M1Na318 *a);
void m1_AiReset1134B0b(M1Na318 *a);
void sub_00113AA0(void *o, void *a);
void sub_00113AA0b(void *o, void *a);
void m1_SndStop048250(int32_t h);
void m1_SndStop048250b(int32_t h);
void m1_ObjSnd05BE30(int32_t h);
void m1_ObjSnd05BE30b(int32_t h);
void sub_00033A70(int32_t h);
void sub_00033A70b(int32_t h);
void m1_AiGoto113040(M1No318 *o, M1Na318 *a, int st);
void m1_AiGoto113040b(M1No318 *o, M1Na318 *a, int st);
int32_t sub_000833E0(int32_t h);
float r4_DistanceXZ(float *a, float *b);
void m1_LockMark0C56B0(M1No318 *o);
int  m1_AiSetState1456E0(M1No318 *o, M1Na318 *a, int st, int f);
int  sub_000494D0(int id, void *p, int f);
int  sub_000494D0b(int id, void *p, int f);
void m1_PlShot0C62A0(M1No318 *o);
void sub_00025D50(int a, int b);

/* 0x001651B0: ground pound: lock on when close (under 60 units, under 3 s
   of cooldown, standing, not shielded); otherwise start move 0x49, stand
   still, play sounds 0x10E and 0x77 and fire, shake the camera, and step on
   unless flag 0x10; wait for the clip; then reset the AI, motion and sounds
   and go to state 0x18 (when 0x156040 agrees) or 0x38. */
void m1_GroundPound1651B0(M1No318 *o, M1Na318 *a)
{
    M1Ns318 *t = a->s278;
    M1Ns318 *s;
    float d;
    switch (a->st58) {
    case 0:
        d = r4_DistanceXZ(o->pos60, t->v74);
        if (!(o->b128 & 0x1E) && !(a->f5c >= 3.0f) && !(d >= 60.0f) && !(t->f40 & 0x10000)) {
            m1_LockMark0C56B0(o);
            return;
        }
        m1_AiSetState1456E0(o, a, 0x49, 0);
        t->f2c = 0.0f;
        t->f28 = 0.0f;
        t->f24 = 0.0f;
        t->f30 = 1.0f;
        t->f10 = 0.0f;
        t->fc = m1_frameTime42C858 * 0.005f;
        a->f4c &= ~0x70u;
        t->f0 |= 3;
        sub_000494D0(0x10E, o->pos60, 0);
        sub_000494D0b(0x77, o->pos60, 0);
        m1_PlShot0C62A0(o);
        sub_00025D50(1, 1);
        if (!(t->f40 & 0x10))
            a->st58++;
        return;
    case 1:
        if (sub_000833E0(o->h30))
            a->st58++;
        return;
    case 2:
        if (sub_00156040(o)) {
            s = a->s278;
            m1_AiReset1134B0(a);
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
            m1_AiGoto113040(o, a, 0x18);
            return;
        }
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
            sub_00113AA0b(o, a);
            a->f4c |= 0x200;
            s->f40 &= ~0x4000u;
        }
        if (a->h6c != -1) {
            m1_SndStop048250b(a->h6c);
            a->h6c = -1;
        }
        m1_ObjSnd05BE30b(o->h13c);
        if (a->h70) {
            sub_00033A70b(a->h70);
            a->h70 = 0;
        }
        m1_AiGoto113040b(o, a, 0x38);
        return;
    }
}

typedef struct { uint32_t f0; uint8_t _4[0x3C]; float v40[4]; uint32_t f50; } M1Ps318;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[8]; int32_t st58; float f5c;
    uint8_t _60[0x6C - 0x60]; int32_t h6c, h70; uint8_t _74[0x278 - 0x74]; M1Ps318 *s278; } M1Pa318;

int  sub_00156040b(M1No318 *o);
void m1_AiReset1134B0c(M1Pa318 *a);
void m1_AiReset1134B0d(M1Pa318 *a);
void m1_AiSway1561D0(M1Ps318 *s, float a, float b);
void m1_AiSway1561D0b(M1Ps318 *s, float a, float b);
void sub_00113190(M1No318 *o, M1Pa318 *a, int k);
void sub_00113190b(M1No318 *o, M1Pa318 *a, int k);
void sub_00113AA0c(void *o, void *a);
void sub_00113AA0d(void *o, void *a);
void m1_SndStop048250c(int32_t h);
void m1_SndStop048250d(int32_t h);
void m1_ObjSnd05BE30c(int32_t h);
void m1_ObjSnd05BE30d(int32_t h);
void sub_00033A70c(int32_t h);
void sub_00033A70d(int32_t h);
void m1_AiGoto113040c(M1No318 *o, M1Pa318 *a, int st);
void m1_AiGoto113040d(M1No318 *o, M1Pa318 *a, int st);
int32_t sub_000833E0b(int32_t h);
float r4_DistanceXZb(float *a, float *b);
void m1_LockMark0C56B0b(M1No318 *o);
int  b4c_Enter1456E0d(M1No318 *o, M1Pa318 *a, int st, int f);
void sub_00156180(M1Ps318 *s, float a, float b, float c, float d);
int  sub_000494D0c(int id, void *p, int f);
int  sub_000494D0d(int id, void *p, int f);
void m1_PlShot0C62A0b(M1No318 *o);
void sub_00025D50b(int a, int b);

/* 0x00153D80: ground pound (stun-trap layout, as 0x1651B0): shield flag
   0x80000 at +0x50, slow drift while pounding; the reset also clears the
   sway and pending hold; ends in state 0xC or 0x2A. */
void m1_GroundPound153D80(M1No318 *o, M1Pa318 *a)
{
    M1Ps318 *t = a->s278;
    M1Ps318 *s;
    float d;
    uint32_t g;
    switch (a->st58) {
    case 0:
        d = r4_DistanceXZb(o->pos60, t->v40);
        if (!(o->b128 & 0x1E) && !(a->f5c >= 3.0f) && !(d >= 60.0f) && !(t->f50 & 0x80000)) {
            m1_LockMark0C56B0b(o);
            return;
        }
        b4c_Enter1456E0d(o, a, 0x49, 0);
        sub_00156180(t, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.003f);
        a->f4c &= ~0x70u;
        t->f0 |= 3;
        sub_000494D0c(0x10E, o->pos60, 0);
        sub_000494D0d(0x77, o->pos60, 0);
        m1_PlShot0C62A0b(o);
        sub_00025D50b(1, 1);
        if (!(t->f50 & 0x10))
            a->st58++;
        return;
    case 1:
        if (sub_000833E0b(o->h30))
            a->st58++;
        return;
    case 2:
        if (sub_00156040b(o)) {
            s = a->s278;
            m1_AiReset1134B0c(a);
            o->fc |= 0xE0;
            o->f10 &= 0xFFFFFEC8u;
            a->f4c &= ~0x100u;
            s->f0 &= ~0x17u;
            s->f50 &= 0xFFDBEEBFu;
            m1_AiSway1561D0(s, -10.0f, m1_frameRate42C85C * 10.0f);
            if (s->f50 & 0x10000) {
                sub_00113AA0c(o, a);
                a->f4c |= 0x200;
                s->f50 &= ~0x10000u;
            }
            g = s->f50;
            if (g & 0x100000) {
                s->f50 = g & ~0x100000u;
                sub_00113190(o, a, 1);
            }
            if (a->h6c != -1) {
                m1_SndStop048250c(a->h6c);
                a->h6c = -1;
            }
            m1_ObjSnd05BE30c(o->h13c);
            if (a->h70) {
                sub_00033A70c(a->h70);
                a->h70 = 0;
            }
            m1_AiGoto113040c(o, a, 0xC);
            return;
        }
        s = a->s278;
        m1_AiReset1134B0d(a);
        o->fc |= 0xE0;
        o->f10 &= 0xFFFFFEC8u;
        a->f4c &= ~0x100u;
        s->f0 &= ~0x17u;
        s->f50 &= 0xFFDBEEBFu;
        m1_AiSway1561D0b(s, -10.0f, m1_frameRate42C85C * 10.0f);
        if (s->f50 & 0x10000) {
            sub_00113AA0d(o, a);
            a->f4c |= 0x200;
            s->f50 &= ~0x10000u;
        }
        g = s->f50;
        if (g & 0x100000) {
            s->f50 = g & ~0x100000u;
            sub_00113190b(o, a, 1);
        }
        if (a->h6c != -1) {
            m1_SndStop048250d(a->h6c);
            a->h6c = -1;
        }
        m1_ObjSnd05BE30d(o->h13c);
        if (a->h70) {
            sub_00033A70d(a->h70);
            a->h70 = 0;
        }
        m1_AiGoto113040d(o, a, 0x2A);
        return;
    }
}
