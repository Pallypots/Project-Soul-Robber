/* Area m1, file 335: enemy stagger / counter state. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Anim335 { uint8_t unk00[0xC4]; float rateC4; } M1Anim335;
typedef struct M1Mdl335 { uint8_t unk00[0x14]; M1Anim335 *a14; } M1Mdl335;
typedef struct M1Ob335 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; M1Mdl335 *anim30; } M1Ob335;
typedef struct M1St335 { uint8_t unk00[4]; uint32_t f04; } M1St335;
typedef struct M1Ai335 {
    uint8_t unk000[0x20]; uint32_t f20; uint8_t unk024[0x4C - 0x24]; uint32_t f4C; uint8_t unk050[0x58 - 0x50];
    int32_t n58; uint8_t unk05C[0x68 - 0x5C]; float f68; uint8_t unk06C[0x74 - 0x6C]; float f74;
    uint8_t unk078[0x278 - 0x78]; M1St335 *s278;
} M1Ai335;
typedef struct M1Tm335 { uint8_t unk00[0x10]; float f10; float f14; int32_t i18; void *fn1C; } M1Tm335;
extern float m1_frameTime42C858, m1_frameRate42C85C;
int      sub_000833E0(void *a);
void     sub_00113090(void *o, void *e, int st);
void     m1_AnimFrame1AEDF0(void *a, int f);
M1Tm335 *m1_Quest113430(void *e, int k);
void     b13_Res142480(void);
/* aliases of 0x113040 (AI state change): separate names keep the separate original calls */
int m1_AiGoto113040(void *o, void *e, int st);
int m1_AiGoto113040b(void *o, void *e, int st);
int m1_AiGoto113040c(void *o, void *e, int st);
int m1_AiGoto113040d(void *o, void *e, int st);
int m1_AiGoto113040e(void *o, void *e, int st);
int m1_AiGoto113040w(void *o, void *e, int st);
int sub_00113040b(void *o, void *e, int st);

#define B22(e) (((uint8_t *)(e))[0x22])

/* 0x143150: stagger. Steps 0/1 wait 35 units, enter the stagger animation (0x16 or 0x17)
   at frame 60/rate and skip ahead two steps; step 2 picks the follow-up when it ends
   (counter flags on the state block give 8, 7, 4 or 0xF, else 8 or 7 by the guard bit);
   step 3 ends in state 5 with a 60-unit timer; step 4 waits 10 units, starts a 0.25 flash
   and returns to step 1. */
void m1_AiStagger143150(M1Ob335 *o, M1Ai335 *e) {
    M1St335 *s;
    M1Anim335 *a;
    M1Tm335 *t;
    uint32_t f;
    switch (e->n58) {
    case 0:
    case 1:
        if (!(e->f68 >= 35.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        sub_00113090(o, e, (B22(e) & 1) + 0x16);
        a = o->anim30->a14;
        m1_AnimFrame1AEDF0(a, _mm_cvttss_si32(_mm_set_ss(60.0f / a->rateC4)));
        e->n58 += 2;
        return;
    case 2:
        if (!sub_000833E0(o->anim30))
            return;
        s = e->s278;
        f = s->f04;
        if (f & 0x20000000) {
            if (e->f20 & 1) {
                if (e->f20 & 0x10000) {
                    s->f04 = f | 2;
                    s->f04 = (f | 2) & ~0x20000000u;
                    m1_AiGoto113040(o, e, 8);
                    return;
                }
                s->f04 &= ~0x20000000u;
                m1_AiGoto113040b(o, e, 7);
                return;
            }
            s->f04 &= ~0x20000000u;
            m1_AiGoto113040c(o, e, 4);
            return;
        }
        if (f & 0x40000000) {
            m1_AiGoto113040d(o, e, 0xF);
            return;
        }
        if (B22(e) & 1) {
            s->f04 = f | 2;
            m1_AiGoto113040e(o, e, 8);
            return;
        }
        m1_AiGoto113040w(o, e, 7);
        return;
    case 3:
        if (!sub_000833E0(o->anim30))
            return;
        e->f74 = 60.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        o->f10 &= ~6u;
        e->f4C |= 0x10;
        sub_00113040b(o, e, 5);
        return;
    case 4:
        if (!(e->f68 >= 10.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        t = m1_Quest113430(e, 1);
        if (t) {
            t->f10 = 0.25f;
            t->f14 = 0.25f;
            t->i18 = 0;
            t->fn1C = (void *)b13_Res142480;
        }
        e->n58 = 1;
        return;
    }
}
