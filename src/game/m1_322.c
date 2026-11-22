/* Area m1, group 322: flyer handlers. Names inferred. */
#include <stdint.h>

typedef struct { uint32_t f0, f4, f8, fc, f10, f14, f18, f1c; } M1Fp322;
typedef struct { uint8_t _0[0x74]; M1Fp322 *flags74; } M1Fa322;

/* 0x00169A00: flyer despawn handler: clear its pool slot and free it. */
int32_t m1_FlyerFree169A00(void *o, M1Fa322 *a)
{
    M1Fp322 *p = a->flags74;
    p->f0 = 0; p->f4 = 0; p->f8 = 0; p->fc = 0;
    p->f10 = 0; p->f14 = 0; p->f18 = 0; p->f1c = 0;
    *(volatile uint32_t *)&p->f0 &= ~1u;
    return 1;
}

typedef struct { uint32_t f0; uint8_t _4[0xC]; float f10; uint8_t _14[4]; float f18; } M1Mp322;
typedef struct { uint8_t _0[0x50]; int32_t f50; uint8_t _54[0x20]; M1Mp322 *flags74; } M1Ma322;
typedef struct { uint8_t _0[0x54]; float f54; uint8_t _58[0x28]; float v80[4];
    uint8_t _90[0x128 - 0x90]; uint8_t b128; } M1Mo322;

extern float m1_frameTime42C858, m1_frameRate42C85C;
void sub_000EE6D0(M1Mo322 *o, float a);
void sub_000EE6D0b(M1Mo322 *o, float a);
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, float *m, float ang);
void m1_VecXform1AD9B0(float *d, float *m, float *v);

/* 0x00169A50: flyer motion handler: fade in over 90 units after appearing
   (flag 0x20000), wrap its heading into -pi..pi, turn its velocity to the
   heading (except in state 8), fall at 0.2 per frame unit while airborne
   (state 7 and touching ground stop the fall) and apply the vertical
   speed. */
void m1_FlyerMove169A50(M1Mo322 *o, M1Ma322 *a)
{
    M1Mp322 *t = a->flags74;
    float m[16];
    float v, lim;
    if (t->f0 & 0x20000) {
        v = t->f10 - m1_frameRate42C85C;
        t->f10 = v;
        if (0.0f > v) {
            sub_000EE6D0(o, 1.0f);
            t->f0 &= ~0x20000u;
        } else {
            lim = 90.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            sub_000EE6D0b(o, (lim - v) / lim);
        }
    }
    if (o->f54 > 3.14159274f)
        o->f54 = o->f54 - 6.28318548f;
    if (-3.14159274f > o->f54)
        o->f54 = o->f54 + 6.28318548f;
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->f54);
    if (a->f50 != 8)
        m1_VecXform1AD9B0(o->v80, m, o->v80);
    if (!(o->b128 & 0x18) && a->f50 != 7)
        t->f18 = m1_frameRate42C85C * 0.199999988f + t->f18;
    else if (t->f18 > 0.0f)
        t->f18 = 0.0f;
    o->v80[1] = o->v80[1] + t->f18;
}
