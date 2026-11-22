/* Area m1, group 325: flyer patrol. Names inferred. */
#include <stdint.h>

typedef struct { uint32_t f0; float f4, f8, fc; float *p10; } M1Pf325;
typedef struct { uint8_t _0[0x54]; int32_t st54; uint8_t _58[4]; float f5c; uint8_t _60[0x14];
    M1Pf325 *flags74; } M1Pa325;
typedef struct { uint8_t _0[0x54]; float f54; uint8_t _58[8]; float pos60[4];
    uint8_t _70[0x128 - 0x70]; uint8_t b128; } M1Po325;

extern float m1_frameRate42C85C;
extern M1Po325 *g_playerObj;
float r4_DistanceXZ(float *a, float *b);
float r4_DistanceXZb(float *a, float *b);
float sub_00113290(M1Po325 *o, float *p);
float sub_00113290b(M1Po325 *o, float *p);
int  sub_001C7EE1(void);                                    /* rand */
int  sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c);
void sub_001671D0(M1Po325 *o, M1Pa325 *a, int st);
void sub_001671D0b(M1Po325 *o, M1Pa325 *a, int st);
void sub_001671D0c(M1Po325 *o, M1Pa325 *a, int st);
void sub_001671D0d(M1Po325 *o, M1Pa325 *a, int st);

/* 0x0016BA40: flyer patrol: a swooping flyer more than 100 above or below
   the player gives up (state 2). While touched, a calm flyer counts up to
   1.5 and then flees (state 3), a fleeing one turns around (180 degrees,
   +/-25 jitter). Step 0 picks a mode: circling (90-179 units, buzz sound)
   or chasing (60-119 units). Circling: drift around the point at 1.5 turns
   per frame unit, keep 20 units off it, then attack (state 1) when time is
   up. Chasing: home in on the point (within 3 units ends early) turning 1.5
   degrees per frame unit. */
void m1_FlyerPatrol16BA40(M1Po325 *o, M1Pa325 *a)
{
    M1Pf325 *t = a->flags74;
    uint32_t f = t->f0;
    float dy, ang;
    volatile uint32_t vf = f;
    if ((vf & 2) && !(vf & 0x20)) {
        dy = o->pos60[1] - g_playerObj->pos60[1];
        if (dy > 100.0f || -100.0f > dy) {
            sub_001671D0(o, a, 2);
            return;
        }
    }
    if ((o->b128 & 6) && (f & 0x102)) {
        if (!(f & 0x20)) {
            t->fc = t->fc + m1_frameRate42C85C;
            if (t->fc > 1.5f) {
                sub_001671D0b(o, a, 3);
                return;
            }
        } else if (f & 0x40) {
            o->f54 = o->f54 + 3.14159274f;
            o->f54 = (float)(sub_001C7EE1() % 10 - 5) * 0.174532935f + o->f54;
        }
    } else {
        t->fc = 0.0f;
    }
    switch (a->st54) {
    case 0:
        if (t->f0 & 0x102) {
            a->f5c = (float)(sub_001C7EE1() % 0x5A + 0x5A) * m1_frameRate42C85C;
            t->f4 = 1.0f;
            a->st54 = 1;
            sub_00049700(0x198, 0x80, 0x80, 0x80, o->pos60, 1, 40.0f, 0);
            return;
        }
        a->f5c = (float)(sub_001C7EE1() % 0x3C + 0x3C) * m1_frameRate42C85C;
        a->st54 = 2;
        return;
    case 1:
        if (0.0f > a->f5c) {
        attack:
            sub_001671D0c(o, a, 1);
            return;
        }
        if (t->f8 > 0.0f) {
            t->f8 = t->f8 - m1_frameRate42C85C;
        } else if (20.0f > r4_DistanceXZ(o->pos60, t->p10)) {
            t->f8 = m1_frameRate42C85C * 60.0f;
            a->f5c = m1_frameRate42C85C * 60.0f + a->f5c;
        }
        ang = sub_00113290(o, t->p10);
        if (ang > 0.0f && 0.69813174f > ang) {
            o->f54 = o->f54 - 0.00523598818f;
            return;
        }
        if (0.0f > ang && ang > -0.69813174f)
            o->f54 = o->f54 + 0.00523598818f;
        return;
    case 2:
        if (0.0f > a->f5c)
            goto attack;
        if (3.0f > r4_DistanceXZb(o->pos60, t->p10)) {
            a->f5c = 0.0f;
            sub_001671D0d(o, a, 1);
        }
        ang = sub_00113290b(o, t->p10);
        if (ang > 0.174532935f) {
            o->f54 = o->f54 + 0.0261799395f;
            return;
        }
        if (-0.174532935f > ang)
            o->f54 = o->f54 - 0.0261799395f;
        return;
    }
}
