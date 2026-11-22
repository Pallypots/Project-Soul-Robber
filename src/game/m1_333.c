/* Area m1, file 333: enemy recover / counter state. Names inferred. */
#include <stdint.h>

typedef struct M1Ob333 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; void *anim30; } M1Ob333;
typedef struct M1St333 { uint8_t unk00[4]; uint32_t f04; uint8_t unk08[0x34 - 8]; void *p34[3]; } M1St333;
typedef struct M1Ai333 {
    uint8_t unk000[0x20]; uint32_t f20; uint8_t unk024[0x58 - 0x24];
    int32_t n58; uint8_t unk05C[0x68 - 0x5C]; float f68; uint8_t unk06C[0x74 - 0x6C]; float f74;
    uint8_t unk078[0x278 - 0x78]; M1St333 *s278;
} M1Ai333;
typedef struct M1Tm333 { uint8_t unk00[8]; float f08; uint8_t unk0C[4]; float f10; float f14; int32_t i18; } M1Tm333;
extern float m1_frameTime42C858, m1_frameRate42C85C;
int      sub_000833E0(void *a);
M1Tm333 *m1_Quest113430(void *e, int k);
M1Tm333 *sub_001133E0(void *e, int k);
void     sub_0018E700(void *p, int k);
/* aliases of 0x113040 (AI state change): separate names keep the separate original calls */
int m1_AiGoto113040(void *o, void *e, int st);
int m1_AiGoto113040b(void *o, void *e, int st);
int m1_AiGoto113040c(void *o, void *e, int st);
int m1_AiGoto113040d(void *o, void *e, int st);
int m1_AiGoto113040e(void *o, void *e, int st);
int m1_AiGoto113040w(void *o, void *e, int st);
int sub_00113040b(void *o, void *e, int st);

#define B22(e) (((uint8_t *)(e))[0x22])

/* 0x13FA50: recover state. Step 0: when the animation ends pick the follow-up (counter
   flags on the state block choose 0xC/0x13, 0x28, 0xB or 0x1A, else 0x28 | guard bit);
   step 1 waits 10 units and starts a 0.25 flash; step 2 waits for the timer and releases
   the three held effects; step 3 ends in state 0xC (with a 90-unit timer) or 0x28. */
void m1_AiRecover13FA50(M1Ob333 *o, M1Ai333 *e) {
    M1St333 *s;
    M1Tm333 *t;
    void **p;
    int n;
    volatile int32_t m;
    switch (e->n58) {
    case 0:
        if (!sub_000833E0(o->anim30))
            return;
        s = e->s278;
        if (s->f04 & 0x20000000) {
            s->f04 &= ~0x20000000u;
            if (e->f20 & 1) {
                if (e->f20 & 0x10000) {
                    m = -(int32_t)((s->f04 & 0x10) != 0);
                    o->f10 &= ~0x26u;
                    m1_AiGoto113040(o, e, (m & -7) + 0x13);
                    return;
                }
                o->f10 &= ~0x26u;
                m1_AiGoto113040b(o, e, 0x28);
                return;
            }
            o->f10 &= ~0x26u;
            m1_AiGoto113040c(o, e, 0xB);
            return;
        }
        if (s->f04 & 0x40000000) {
            s->f04 &= ~0x40000000u;
            o->f10 &= ~0x26u;
            m1_AiGoto113040d(o, e, 0x1A);
            return;
        }
        o->f10 &= ~0x26u;
        m1_AiGoto113040e(o, e, (B22(e) & 1) | 0x28);
        return;
    case 1:
        if (!(e->f68 >= 10.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        t = m1_Quest113430(e, 1);
        if (t) {
            t->f10 = 0.25f;
            t->f14 = 0.25f;
            t->i18 = 0;
        }
        e->n58++;
        return;
    case 2:
        t = sub_001133E0(e, 1);
        if (!(t->f08 > t->f10))
            return;
        p = e->s278->p34;
        for (n = 3; n != 0; n--, p++)
            if (*p)
                sub_0018E700(*p, 0);
        e->n58++;
        return;
    case 3:
        if (!sub_000833E0(o->anim30))
            return;
        o->f10 &= ~0x26u;
        if (B22(e) & 1) {
            e->f74 = 90.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            m1_AiGoto113040w(o, e, 0xC);
            return;
        }
        sub_00113040b(o, e, 0x28);
        return;
    }
}
