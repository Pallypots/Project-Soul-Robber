/* Area m1, file 167: enemy approach state (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1An167 { uint8_t unk00[0xC4]; float fC4; uint8_t unkC8[0x14]; float fDC; } M1An167;
typedef struct M1Md167 { uint8_t unk00[0x14]; M1An167 *a14; } M1Md167;
typedef struct M1Ob167 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; M1Md167 *anim30; } M1Ob167;
typedef struct M1Ai167 { uint8_t unk00[0x20]; uint32_t f20; uint8_t unk24[0x40]; int32_t n64; uint8_t unk68[0xC]; float t74; } M1Ai167;
typedef struct M1Q167 { uint8_t unk00[0x10]; int32_t a10; int32_t a14; } M1Q167;
typedef struct M1S167 { int32_t s0; uint8_t unk04[0xC]; float t10; } M1S167;
extern float m1_frameRate42C85C;
int  sub_00139DB0(M1Ai167 *e);
void sub_00139D50(M1Ob167 *o);
M1Q167 *m1_Quest113430(M1Ai167 *e, int k);
M1S167 *m1_Quest113400(M1Ai167 *e, int k);
void sub_00113090(M1Ob167 *o, M1Ai167 *e, int st);
void m1_AiGoto113040(M1Ob167 *o, M1Ai167 *e, int st);

/* 0x13B620: approach step: if the target is close queue an attack, otherwise walk with the matching gait. */
void m1_AiApproach13B620(M1Ob167 *o, M1Ai167 *e) {
    M1Q167 *q; M1S167 *s; int st; volatile int k;
    if (sub_00139DB0(e) != 0) {
        q = m1_Quest113430(e, 8);
        q->a14 = 0xD;
        q->a10 = (((uint8_t *)e)[0x22] & 1) + 0x50;
        m1_AiGoto113040(o, e, 0);
        return;
    }
    k = -((uint8_t)(e->f20 & 1) != 0) & 2;
    st = k + 2 + ((e->f20 >> 16) & 1);
    if (e->n64 != st) { sub_00113090(o, e, st); sub_00139D50(o); }
    o->f10 |= 0x20;
    e->t74 = o->anim30->a14->fDC / o->anim30->a14->fC4 * m1_frameRate42C85C;
    s = m1_Quest113400(e, 3);
    s->t10 = 0.0f;
}

#include <xmmintrin.h>
typedef struct M1Rg167 { uint8_t unk00[4]; uint32_t f4; } M1Rg167;
typedef struct M1Ob167b { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; M1Md167 *anim30; } M1Ob167b;
typedef struct M1Ai167b { uint8_t unk00[0x22]; uint8_t b22; uint8_t unk23[0x278 - 0x23]; M1Rg167 *rig278; } M1Ai167b;
extern float m1_frameTime42C858;
int  sub_001C7EE1(void);
void m1_AnimFrame1AEDF0(void *a, int frame);

/* 0x13B7C0: enter the walk state (variant picked by flags), random start frame, start a 5 s timer. */
void m1_AiWalk13B7C0(M1Ob167b *o, M1Ai167b *e) {
    M1S167 *s; volatile int st; M1An167 *a; float f;
    st = (e->b22 & 1) + 0x31;
    if ((int32_t)e->rig278->f4 < 0) st += 2;
    sub_00113090((M1Ob167 *)o, (M1Ai167 *)e, st);
    f = (float)(sub_001C7EE1() % 4);
    if (sub_001C7EE1() % 2 < 1) f += 3.0f;
    a = o->anim30->a14;
    m1_AnimFrame1AEDF0(a, _mm_cvtt_ss2si(_mm_set_ss(f / a->fC4)));
    o->f10 |= 0x20;
    s = m1_Quest113400((M1Ai167 *)e, 7);
    s->t10 = 5.0f / m1_frameTime42C858 * m1_frameRate42C85C;
    if (s->s0 != 0) s->s0 = 2;
}
