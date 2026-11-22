/* Area m1, group 310. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; int32_t h30; uint8_t _34[0x2C];
    uint8_t pos60[0x10]; uint8_t _70[0x18]; float f88; uint8_t _8c[0x128 - 0x8C]; uint32_t f128; } M1So310;
typedef struct { uint32_t f0; float f4; uint32_t _8; float fc; uint32_t _10, _14; float f18; } M1Sf310;
typedef struct { uint8_t _0[0x54]; int32_t st54; uint8_t _58[4]; float f5c; uint8_t _60[0x74 - 0x60];
    M1Sf310 *flags74; } M1Ss310;

extern float m1_frameTime42C858, m1_frameRate42C85C;
int32_t sub_000833E0(int32_t h);
void b16_PlayAnim(M1So310 *o, M1Ss310 *a, int k);
void sub_001671D0(M1So310 *o, M1Ss310 *a, int st);
void sub_001671D0b(M1So310 *o, M1Ss310 *a, int st);
int  sub_00036750(M1So310 *o, int k);
int  sub_00036750b(M1So310 *o, int k);
int  sub_00049700(int id, int r, int g, int b, const void *pos, int a, float size, int c);
void sub_000414A0(int v);

/* 0x0016ADD0: dive: lift off (height speed -3), fall at 60/s (100/s when
   fast, upward when flag 0x100), play the dive clip (8 up / 10 down) and
   wait 45 frame units; then the landing voice and effect, and when the clip
   ends either recover (state 3, flag 0x10000) or spin 360 and go to state 4. */
void m1_Dive16ADD0(M1So310 *o, M1Ss310 *a)
{
    M1Sf310 *fp = a->flags74;
    volatile int32_t k;
    float v;
    uint32_t f;
    switch (a->st54) {
    case 0:
        o->f128 &= ~0x18u;
        fp->f18 = -3.0f;
        a->st54++;
    case 1:
        if (fp->f0 & 0x200)
            v = m1_frameRate42C85C * 100.0f;
        else
            v = m1_frameRate42C85C * 60.0f;
        v = 0.0f - v;
        o->f88 = v;
        if (fp->f0 & 0x100)
            o->f88 = v * -1.0f;
        if (!sub_000833E0(o->h30)) return;
        k = 0xA;
        if (fp->f0 & 0x100) k = 8;
        b16_PlayAnim(o, a, k);
        fp->f0 &= ~0x200u;
        a->f5c = 45.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        a->st54++;
        return;
    case 2:
        if (0.0f > a->f5c) {
            if (fp->f0 & 2) {
                sub_00036750(o, 0);
                if (fp->f0 & 0x10000)
                    sub_00049700(0x19A, 0x80, 0x80, 0x80, o->pos60, 1, 3.40282347e+38f, 0);
            }
            a->st54++;
        }
    case 3:
        if (!sub_000833E0(o->h30)) return;
        f = fp->f0;
        if (f & 0x10000) {
            fp->f0 = f & 0xFFFEFEFBu;
            o->f10 &= 0xFFFFFBFEu;
            fp->fc = 0.0f;
            sub_001671D0(o, a, 3);
            return;
        }
        fp->f4 = 360.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        sub_00036750b(o, 1);
        sub_000414A0(-1);
        sub_001671D0b(o, a, 4);
        return;
    }
}

typedef struct { uint32_t f0; } M1Ws310;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0x74 - 0x5C]; float wait74;
    uint8_t _78[0x278 - 0x78]; M1Ws310 *s278; } M1Wa310;
typedef struct { uint8_t _0[0x30]; int32_t h30; } M1Wo310;

int32_t sub_000833E0w(int32_t h);
int32_t sub_000833E0x(int32_t h);
int  sub_001C7EE1(void);                                    /* rand */
void sub_00113090w(M1Wo310 *o, M1Wa310 *a, int k);
void sub_00113090x(M1Wo310 *o, M1Wa310 *a, int k);
void sub_00113090y(M1Wo310 *o, M1Wa310 *a, int k);
void m1_AiGoto113040w(M1Wo310 *o, M1Wa310 *a, int st);
int  sub_00036750w(M1Wo310 *o, int k);
int  sub_00036750x(M1Wo310 *o, int k);
int  sub_00036750y(M1Wo310 *o, int k);
void m1_SplashFx1757C0(M1Wa310 *a, M1Wo310 *o);             /* regargs: a=EAX o=ECX */
void m1_SplashFx1757C0b(M1Wa310 *a, M1Wo310 *o);
void m1_SplashFx1757C0c(M1Wa310 *a, M1Wo310 *o);
void m1_WaveFx177AC0(M1Wa310 *a, M1Wo310 *o);               /* regargs: a=EAX o=ECX */
void m1_WaveFx177AC0b(M1Wa310 *a, M1Wo310 *o);
void m1_WaveFx177AC0c(M1Wa310 *a, M1Wo310 *o);

/* 0x00175A30: splash attack: after the wind-up start mode 2 with a 120-unit
   window (1 in 16 skips straight to step 3); during the window fire the
   splash at 120, 80 and 40 units left (only the first unless flag 0x10),
   then mode 1; step 2 waits for the clip and goes to state 0 with a
   90-unit cooldown; step 3 waits for the window, then mode 1 and step 2. */
void m1_SplashAttack175A30(M1Wo310 *o, M1Wa310 *a)
{
    M1Ws310 *t = a->s278;
    uint32_t f;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0w(o->h30)) return;
        sub_00113090w(o, a, 2);
        a->wait74 = 120.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        if (!(sub_001C7EE1() & 0xF)) {
            a->st58 = 3;
            return;
        }
        t->f0 &= ~0xE0u;
        a->st58++;
        return;
    case 1:
        if (120.0f / m1_frameTime42C858 * m1_frameRate42C85C >= a->wait74 && !((f = t->f0) & 0x20)) {
            t->f0 = f | 0x20;
            m1_SplashFx1757C0(a, o);
            sub_00036750w(o, 0);
        }
        f = t->f0;
        if (f & 0x10) {
            if (80.0f / m1_frameTime42C858 * m1_frameRate42C85C >= a->wait74 && !(f & 0x40)) {
                t->f0 = f | 0x40;
                m1_SplashFx1757C0b(a, o);
                sub_00036750x(o, 0);
            }
            if (40.0f / m1_frameTime42C858 * m1_frameRate42C85C >= a->wait74 && !((f = t->f0) & 0x80)) {
                t->f0 = f | 0x80;
                m1_SplashFx1757C0c(a, o);
                sub_00036750y(o, 0);
            }
        } else if (80.0f / m1_frameTime42C858 * m1_frameRate42C85C >= a->wait74) {
            a->wait74 = -1.0f;
        }
        if (0.0f > a->wait74) {
            sub_00113090x(o, a, 1);
            a->st58++;
        }
        return;
    case 2:
        if (!sub_000833E0x(o->h30)) return;
        a->wait74 = m1_frameRate42C85C * 90.0f;
        m1_AiGoto113040w(o, a, 0);
        t->f0 &= ~0xE0u;
        return;
    case 3:
        if (0.0f > a->wait74) {
            sub_00113090y(o, a, 1);
            a->st58 = 2;
        }
        return;
    }
}

/* 0x00177CB0: wave attack: as 0x175A30 with the wave effect. */
void m1_WaveAttack177CB0(M1Wo310 *o, M1Wa310 *a)
{
    M1Ws310 *t = a->s278;
    uint32_t f;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0w(o->h30)) return;
        sub_00113090w(o, a, 2);
        a->wait74 = 120.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        if (!(sub_001C7EE1() & 0xF)) {
            a->st58 = 3;
            return;
        }
        t->f0 &= ~0xE0u;
        a->st58++;
        return;
    case 1:
        if (120.0f / m1_frameTime42C858 * m1_frameRate42C85C >= a->wait74 && !((f = t->f0) & 0x20)) {
            t->f0 = f | 0x20;
            m1_WaveFx177AC0(a, o);
            sub_00036750w(o, 0);
        }
        f = t->f0;
        if (f & 0x10) {
            if (80.0f / m1_frameTime42C858 * m1_frameRate42C85C >= a->wait74 && !(f & 0x40)) {
                t->f0 = f | 0x40;
                m1_WaveFx177AC0b(a, o);
                sub_00036750x(o, 0);
            }
            if (40.0f / m1_frameTime42C858 * m1_frameRate42C85C >= a->wait74 && !((f = t->f0) & 0x80)) {
                t->f0 = f | 0x80;
                m1_WaveFx177AC0c(a, o);
                sub_00036750y(o, 0);
            }
        } else if (80.0f / m1_frameTime42C858 * m1_frameRate42C85C >= a->wait74) {
            a->wait74 = -1.0f;
        }
        if (0.0f > a->wait74) {
            sub_00113090x(o, a, 1);
            a->st58++;
        }
        return;
    case 2:
        if (!sub_000833E0x(o->h30)) return;
        a->wait74 = m1_frameRate42C85C * 90.0f;
        m1_AiGoto113040w(o, a, 0);
        t->f0 &= ~0xE0u;
        return;
    case 3:
        if (0.0f > a->wait74) {
            sub_00113090y(o, a, 1);
            a->st58 = 2;
        }
        return;
    }
}
