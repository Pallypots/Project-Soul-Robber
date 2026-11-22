/* Area m1, group 320. Names inferred. */
#include <stdint.h>

typedef struct { uint32_t f0; float f4; uint8_t _8[0xC]; float f14; } M1Hf320;
typedef struct { uint8_t _0[0x50]; int32_t f50; uint8_t _54[0x20]; M1Hf320 *flags74; } M1Ha320;
typedef struct { uint8_t _0[4]; } M1Ho320;
typedef struct { int32_t id; uint8_t _4[0xC]; float v10[4]; } M1He320;

extern float m1_frameTime42C858, m1_frameRate42C85C;
float sub_00113290(M1Ho320 *o, float *p);
void sub_001671D0(M1Ho320 *o, M1Ha320 *a, int st);
void sub_001671D0b(M1Ho320 *o, M1Ha320 *a, int st);
void sub_001671D0c(M1Ho320 *o, M1Ha320 *a, int st);
void sub_001671D0d(M1Ho320 *o, M1Ha320 *a, int st);
void sub_001671D0e(M1Ho320 *o, M1Ha320 *a, int st);
void sub_001671D0f(M1Ho320 *o, M1Ha320 *a, int st);

/* 0x00169800: flyer's hit handler: ignored while recovering (flag 4 clear
   and the recovery timer running). Hits 1-3/5/10/11 (and 35, which also
   marks a heavy hit) knock it back toward the side the hit came from
   (state 0xB, 10-unit recovery); 42 knocks it straight back; 14, 16 and 26
   pick states 8, 0xA and 9; 34 first starts a 60-unit guard, then like
   30-32 staggers it (state 6) unless it is already in state 5, 8 or 0xA;
   36 staggers it without consuming the hit. Returns -1 when consumed. */
int32_t m1_FlyerHit169800(M1Ho320 *o, M1Ha320 *a, M1He320 *e)
{
    M1Hf320 *t = a->flags74;
    uint32_t f = t->f0;
    float ang;
    int32_t k;
    int32_t r = 0;
    if (!(f & 4) && t->f14 > 0.0f)
        return 0;
    switch (e->id) {
    case 35:
        t->f0 = f | 0x200;
    case 1: case 2: case 3: case 5: case 10: case 11:
        ang = sub_00113290(o, e->v10);
        if (1.57079637f > ang && ang > -1.57079637f)
            t->f0 |= 0x100;
        else
            t->f0 &= ~0x100u;
        t->f14 = 10.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        sub_001671D0(o, a, 0xB);
        return -1;
    case 42:
        t->f0 = f & ~0x100u;
        sub_001671D0b(o, a, 0xB);
        return -1;
    case 14:
        sub_001671D0c(o, a, 8);
        return -1;
    case 26:
        sub_001671D0d(o, a, 9);
        return 0;
    case 16:
        sub_001671D0e(o, a, 0xA);
        return -1;
    case 34:
        if (0.0f > t->f4) {
            t->f4 = 60.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            t->f14 = 10.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            return -1;
        }
    case 30: case 31: case 32:
        k = a->f50;
        if (k == 8 || k == 5 || k == 0xA)
            return r;
        r = -1;
    case 36:
        sub_001671D0f(o, a, 6);
        return r;
    }
    return r;
}

typedef struct { uint8_t _0[0x374]; float f374; } M1Pk320;
typedef struct { uint8_t _0[0xC4]; M1Pk320 *pc4; } M1Pb320;
typedef struct { uint8_t _0[0x20]; M1Pb320 *p20; uint8_t _24[0x3C]; float pos60[4]; } M1Pp320;
typedef struct { uint32_t f0; float f4; uint8_t _8[0x18]; float f20; uint8_t _24[0xC]; float f30; } M1If320;
typedef struct { uint8_t _0[0x54]; int32_t st54; uint8_t _58[4]; float f5c; uint8_t _60[0x14];
    M1If320 *flags74; } M1Ia320;
typedef struct { uint8_t _0[0x128]; uint8_t b128; } M1Io320;

extern M1Pp320 *g_playerObj;
void sub_00167D90(M1Io320 *o);                              /* regargs: o=EAX */
float sub_00113290b(M1Io320 *o, float *p);
int  sub_001C7EE1(void);                                    /* rand */
void sub_001671D0h(M1Io320 *o, M1Ia320 *a, int st);
void sub_001671D0i(M1Io320 *o, M1Ia320 *a, int st);

/* 0x00167F10: flyer idle: step 0 picks a hover height (the player's head
   height - 15 when flag 2, else around its base +10 minus 0..10), a random
   drift speed (10 + 0..30), which side the player is on and, when flag
   0x20, a 3-5 s wait; step 1 fires its timed effect once under 4 units
   left, flips side when touching, and when the wait ends restarts (flag
   0x20, or a new 3-5 s wait without flag 2) or attacks (state 3, left or
   right at random). */
void m1_FlyerIdle167F10(M1Io320 *o, M1Ia320 *a)
{
    M1If320 *t = a->flags74;
    uint32_t f;
    switch (a->st54) {
    case 0:
        f = t->f0;
        if (!(f & 0x40000))
            t->f0 = f | 0x58C;
        t->f0 &= 0xFCFFBFFFu;
        t->f4 = (float)(sub_001C7EE1() % 7) * 5.0f + 10.0f;
        if (0.0f > sub_00113290b(o, g_playerObj->pos60))
            f = t->f0 & ~0x200u;
        else
            f = t->f0 | 0x200;
        t->f0 = f;
        if (f & 2)
            t->f20 = g_playerObj->p20->pc4->f374 - 15.0f;
        else
            t->f20 = (t->f30 + 10.0f) - (float)(sub_001C7EE1() % 11);
        if (t->f0 & 0x20)
            a->f5c = (float)(sub_001C7EE1() % 3 + 3) * m1_frameRate42C85C * 60.0f;
        a->st54++;
        return;
    case 1:
        if (!(t->f0 & 0x1000000) && 4.0f > a->f5c) {
            sub_00167D90(o);
            t->f0 |= 0x1000000;
        }
        if (o->b128 & 6)
            t->f0 ^= 0x200;
        if (!(0.0f > a->f5c)) return;
        f = t->f0;
        if (!(f & 2)) {
            a->f5c = (float)(sub_001C7EE1() % 3 + 3) * m1_frameRate42C85C * 60.0f;
        } else if (!(f & 0x20)) {
            if (sub_001C7EE1() & 1) {
                t->f0 |= 0x4000;
                sub_001671D0h(o, a, 3);
                return;
            }
            t->f0 |= 0x20000;
            sub_001671D0i(o, a, 3);
            return;
        }
        a->st54 = 0;
        return;
    }
}
