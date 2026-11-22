/* Area m1, file 345: enemy sidestep then counter picker. Names inferred. */
#include <stdint.h>

typedef struct M1St345 { uint8_t unk00[0x14]; float f14; } M1St345;
typedef struct M1Ai345 {
    uint8_t unk000[0x20]; uint8_t b20; uint8_t unk021[0x4C - 0x21]; uint32_t f4C; uint8_t unk050[0x58 - 0x50];
    int32_t n58; uint8_t unk05C[0x68 - 0x5C]; float f68; uint8_t unk06C[0x74 - 0x6C]; float f74;
    uint8_t unk078[0xFC - 0x78]; float fFC; float f100; uint8_t unk104[0x270 - 0x104]; float f270; float f274; M1St345 *s278;
} M1Ai345;
typedef struct M1Ob345 { uint8_t unk00[0x30]; void *anim30; } M1Ob345;
typedef struct M1Tm345 { uint8_t unk00[0x10]; float f10; float f14; } M1Tm345;
typedef int (*M1Fn345)(M1Ob345 *o, M1Ai345 *e, const void *t);
extern M1Fn345 m1_chkFn31DBBC;
extern const uint8_t m1_chkTbl279848[];
extern float m1_frameTime42C858, m1_frameRate42C85C;
extern float m1_g3F7504;
M1Tm345 *sub_001133E0(void *e, int k);
void     sub_00113370(void *e, M1Tm345 *t);
void     sub_00113480(void *e, int k);
int      sub_000833E0(void *a);
float    sub_001A3F30(float x);                        /* fabs */
int      sub_001C7EE1(void);                           /* rand */
int      m1_AiGoto113040(void *o, void *e, int st);

/* 0x144D70: sidestep. Steps 0 and 1 turn one way then the other (the guard bit picks the
   direction and timing) and end the turn; step 2 on the animation end picks 3 (table
   check), 8 (flag 0x100, starting a 360-unit cooldown), 0xA / 9 for a close target in front
   with the cooldown over (0xA half the time when health is at most half), or 5 with a
   90-unit timer (none with the guard bit). */
void m1_AiSidestep144D70(M1Ob345 *o, M1Ai345 *e) {
    M1Tm345 *t;
    float lim, d, a, x;
    int k;
    switch (e->n58) {
    case 0:
        t = sub_001133E0(e, 3);
        if (e->b20 & 1) {
            lim = 34.0f;
            if (e->fFC >= 0.174532935f && 1.04719758f >= e->fFC) {
                t->f10 = m1_frameTime42C858 * 0.0174532924f;
                t->f14 = 0.0f;
            } else {
                t->f10 = 0.0f;
                t->f14 = 0.0f;
            }
        } else {
            lim = 36.0f;
            if (e->fFC >= -0.314159274f && -0.174532935f >= e->fFC)
                t->f14 = 0.0f - m1_frameTime42C858 * 0.0174532924f;
            else
                t->f14 = 0.0f;
            t->f10 = 0.0f;
        }
        if (!(e->f68 >= lim / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        e->n58++;
        return;
    case 1:
        t = sub_001133E0(e, 3);
        if (e->b20 & 1) {
            lim = 60.0f;
            if (e->fFC >= -3.14159274f && -0.174532935f >= e->fFC) {
                t->f14 = m1_frameTime42C858 * -0.0261799395f;
                t->f10 = 0.0f;
            } else {
                t->f14 = 0.0f;
                t->f10 = 0.0f;
            }
        } else {
            lim = 50.0f;
            if (e->fFC >= 0.698131740f && 3.14159274f >= e->fFC)
                t->f10 = m1_frameTime42C858 * 0.0628318563f;
            else
                t->f10 = 0.0f;
            t->f14 = 0.0f;
        }
        if (!(e->f68 >= lim / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        sub_00113370(e, t);
        e->n58++;
        return;
    case 2:
        if (!sub_000833E0(o->anim30))
            return;
        d = e->f100;
        a = sub_001A3F30(e->fFC);
        if (m1_chkFn31DBBC(o, e, m1_chkTbl279848)) {
            k = 3;
        } else if (e->f4C & 0x100) {
            m1_g3F7504 = 360.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            k = 8;
        } else if (e->s278->f14 >= 40.0f && 60.0f >= d && 0.523598790f >= a && 0.0f >= m1_g3F7504) {
            if (e->f270 * 0.5f >= e->f274 && sub_001C7EE1() % 2 < 1)
                k = 0xA;
            else
                k = 9;
        } else {
            k = 5;
            x = 0.0f;
            if (!(e->b20 & 1))
                x = 90.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            e->f74 = x;
        }
        e->f4C = (e->f4C & ~0x100u) | 0x10;
        sub_00113480(e, 2);
        m1_AiGoto113040(o, e, k);
        return;
    }
}
