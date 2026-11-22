/* Area m1, group 322: flyer attack. Names inferred. */
#include <stdint.h>

typedef struct { uint32_t f0; } M1Df322;
typedef struct { uint8_t _0[0x54]; int32_t st54; uint8_t _58[4]; float f5c; uint8_t _60[0x14];
    M1Df322 *flags74; } M1Da322;
typedef struct { uint8_t _0[0x54]; float f54; uint8_t _58[8]; float pos60[4]; } M1Do322;

extern float m1_frameTime42C858, m1_frameRate42C85C;
extern M1Do322 *g_playerObj;
extern float m1_flyAim31F1C0[];
int  sub_001C7EE1(void);                                    /* rand */
float sub_00113290(M1Do322 *o, float *p);
float sub_00113290b(M1Do322 *o, float *p);
float r4_DistanceXZ(float *a, float *b);
void b16_PlayAnim(M1Do322 *o, M1Da322 *a, int k);
void b16_PlayAnimB(M1Do322 *o, M1Da322 *a, int k);
void b16_HoldAll(M1Do322 *o, M1Da322 *a);
void b16_ReleaseAll(M1Do322 *o, M1Da322 *a);
void b16_ReleaseAllB(M1Do322 *o, M1Da322 *a);
void sub_001671D0(M1Do322 *o, M1Da322 *a, int st);
void *sub_00035D80(M1Do322 *o, int a, int b);
void *sub_00035D80b(M1Do322 *o, int a, int b);
void sub_00034E00(void *fx, const float *pos, const float *dir, const float *up);
void sub_00034E00b(void *fx, const float *pos, const float *dir, const float *up);
void sub_000414A0(int v);
void sub_000F5D40(float *d, const float *s);
int  sub_000494D0(int id, void *p, int f);

/* 0x0016A710: flyer dive bomb: turn toward the aim point with a random
   +/-70 degree swing and wait 30-39 units; play the wind-up clip (6) for 19
   units; hold everything for 300 units; then, while within 240 units of the
   window, if the player is under 100 units away and roughly in front, fire
   the two dive effects 15 below o, play sound 0x19A and restart the dive
   (600 units); when the window ends give up (state 0xB). */
void m1_FlyerDive16A710(M1Do322 *o, M1Da322 *a)
{
    M1Df322 *fl = a->flags74;
    M1Do322 *pl;
    float up[4], dir[4], pos[4];
    float ang, d;
    void *h;
    switch (a->st54) {
    case 0:
        fl->f0 |= 0x10000;
        a->f5c = ((float)(sub_001C7EE1() % 10) + 30.0f) / m1_frameTime42C858;
        o->f54 = sub_00113290(o, m1_flyAim31F1C0) + o->f54;
        o->f54 = ((float)(sub_001C7EE1() % 15) * 10.0f - 70.0f) * 0.0174532924f + o->f54;
        a->st54++;
    case 1:
        if (0.0f > a->f5c) {
            a->f5c = 19.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            b16_PlayAnim(o, a, 6);
            a->st54++;
        }
        return;
    case 2:
        if (0.0f > a->f5c) {
            b16_HoldAll(o, a);
            a->f5c = 300.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            a->st54++;
        }
        return;
    case 3:
        pl = g_playerObj;
        d = r4_DistanceXZ(o->pos60, pl->pos60);
        ang = sub_00113290b(o, pl->pos60);
        if (240.0f / m1_frameTime42C858 * m1_frameRate42C85C > a->f5c && 100.0f > d &&
            6.28318548f > ang && ang > -6.28318548f) {
            dir[2] = -1.0f;
            dir[0] = 0.0f;
            dir[1] = 0.0f;
            dir[3] = 1.0f;
            up[0] = 0.0f;
            up[1] = 1.0f;
            up[2] = 0.0f;
            up[3] = 1.0f;
            h = sub_00035D80(o, 1, 3);
            sub_000414A0(-1);
            sub_000F5D40(pos, o->pos60);
            pos[1] = pos[1] - 15.0f;
            sub_00034E00(h, pos, dir, up);
            sub_00034E00b(sub_00035D80b(o, 2, 3), pos, dir, up);
            sub_000494D0(0x19A, o->pos60, 0);
            a->f5c = 600.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            a->st54 = 1;
            b16_ReleaseAll(o, a);
            b16_PlayAnimB(o, a, 0);
            return;
        }
        if (0.0f > a->f5c) {
            fl->f0 &= 0xFFFFFE9Fu;
            b16_ReleaseAllB(o, a);
            sub_001671D0(o, a, 0xB);
        }
        return;
    }
}
