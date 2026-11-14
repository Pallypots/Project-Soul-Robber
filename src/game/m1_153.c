/* Area m1, file 153: enemy timers. Names inferred. */
#include <stdint.h>

typedef struct M1Ob153 { uint8_t unk00[0x10]; uint32_t f10; } M1Ob153;
typedef struct M1Rig153 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x18]; int32_t c20; } M1Rig153;
typedef struct M1Ai153 { uint8_t unk00[0x74]; float t74; uint8_t unk78[0x278 - 0x78]; M1Rig153 *rig278; } M1Ai153;
typedef struct M1St153 { int32_t s0; uint8_t unk04[0xC]; float t10; } M1St153;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_001C7EE1(void);
M1St153 *m1_Quest113400(M1Ai153 *e, int k);

/* 0x13E800: idle pause of random length; the longer the enemy idles, the likelier a turn is queued. */
void m1_AiPause13E800(M1Ob153 *o, M1Ai153 *e) {
    M1Rig153 *r = e->rig278; M1St153 *s; int n;
    e->t74 = (float)(sub_001C7EE1() % 9) / m1_frameTime42C858 * m1_frameRate42C85C;
    n = r->c20 + 1;
    r->c20 = n;
    r->f4 &= ~0x40000000u;
    if (n >= 8) { if (sub_001C7EE1() % 4 < 1) r->f4 |= 0x40000000; }
    else if (n >= 5) { if (sub_001C7EE1() % 16 < 1) r->f4 |= 0x40000000; }
    o->f10 |= 0x20;
    s = m1_Quest113400(e, 7);
    s->t10 = 5.0f / m1_frameTime42C858 * m1_frameRate42C85C;
    if (s->s0 != 0) s->s0 = 2;
}

typedef struct M1Md153 { uint8_t unk00[0x74]; float f74; } M1Md153;
typedef struct M1Ac153 { uint8_t unk00[0x20]; M1Md153 *mdl20; uint8_t unk24[0x3C]; float pos60[4]; uint8_t unk70[0x68]; float vD8[4]; } M1Ac153;
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_0001B420(float *hi, float *lo, int k);

/* 0x112B30: query the ground under an actor with a 20-unit box around its feet. */
void m1_ActGroundBox112B30(M1Ac153 *o, int k) {
    struct { float lo[4]; float hi[4]; float c[4]; } l;
    sub_001ADAF0(l.c, o->pos60, o->vD8);
    l.hi[0] = l.c[0] + 20.0f;
    l.hi[1] = l.c[1] + 20.0f;
    l.hi[2] = l.c[2] + 20.0f;
    l.lo[0] = l.c[0] - 20.0f;
    l.hi[3] = 1.0f;
    l.lo[1] = (o->mdl20->f74 - o->pos60[1]) + (l.c[1] - 10.0f);
    l.lo[2] = l.c[2] - 20.0f;
    l.lo[3] = 1.0f;
    sub_0001B420(l.hi, l.lo, k);
}
