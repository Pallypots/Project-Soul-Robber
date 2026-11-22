/* Area m1, file 357: enemy rise-from-ground state. Names inferred. */
#include <stdint.h>

typedef struct M1St357 {
    uint8_t _0[4]; uint32_t f04; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5C, f60, f64;
} M1St357;
typedef struct M1Ai357 {
    uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x4C - 0x21]; uint32_t f4C; uint8_t _50[8]; int32_t n58;
    uint8_t _5C[0x278 - 0x5C]; M1St357 *s278;
} M1Ai357;
typedef struct M1Ob357 { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; void *anim30; uint8_t _34[0x2C]; float p60[4]; } M1Ob357;
typedef struct M1Kc357 { int32_t i00; uint8_t _4[0xC]; float f10, f14, f18, f1C; } M1Kc357;
int      sub_000833E0(void *a);
int      m1_AiSetState1456E0(void *o, void *e, int st, int f);
void     sub_000494D0(int id, void *pos, int k);
void     sub_00036750(void *o, int k);
M1Kc357 *m1_Quest113400(void *e, int v);
void     sub_0011F2B0(void *obj, int k, void *e);      /* regargs: obj=EDI k=EBX */
void     sub_000F5D40(float *d, const float *s);

/* 0x12AC20: rise from the ground: wait for the animation, enter pose 0x42 and wait at step
   0xA for the state block's 0x20 cue; then play the rise effect and cry (0xE with the
   guard bit), clear the move flags, start the 1-unit effect timer (re-armed when running),
   enter state 0x2F and reset the move blend. */
void m1_AiRise12AC20(M1Ob357 *o, M1Ai357 *e) {
    M1St357 *s;
    M1Kc357 *c;
    volatile int k;
    switch (e->n58) {
    case 0:
        if (!sub_000833E0(o->anim30))
            return;
        e->n58++;
    case 1:
        m1_AiSetState1456E0(o, e, 0x42, 0);
        e->n58 = 0xA;
        return;
    case 0xA:
        if (!(e->s278->f04 & 0x20))
            return;
        sub_000494D0(0xF7, o->p60, 0);
        k = 0;
        if (e->b20 & 1)
            k = 0xE;
        sub_00036750(o, k);
        o->f10 |= 0xD;
        e->f4C &= 0xFEFFFF8Fu;
        c = m1_Quest113400(e, 6);
        c->f10 = 1.0f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->i00)
            c->i00 = 2;
        sub_0011F2B0(o, 0x2F, e);
        s = e->s278;
        sub_000F5D40(s->v40, s->v30);
        s->f58 = 0.0f;
        s->f54 = 0.0f;
        s->f50 = 0.0f;
        s->f5C = 1.0f;
        s->f60 = 1.0f;
        s->f64 = 1.0f;
        return;
    }
}
