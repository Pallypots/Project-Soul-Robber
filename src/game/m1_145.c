/* Area m1, file 145: enemy idle helpers. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Anm145 { uint8_t unk00[0xC4]; float spdC4; } M1Anm145;
typedef struct M1Mdl145 { uint8_t unk00[0x14]; M1Anm145 *anim14; } M1Mdl145;
typedef struct M1Obj145 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x30 - 0x14]; M1Mdl145 *mdl30; } M1Obj145;
typedef struct M1Rig145 { uint8_t unk00[4]; uint32_t f4; } M1Rig145;
typedef struct M1Ai145 {
    uint8_t unk00[0x20]; uint8_t b20; uint8_t b21; uint8_t b22; uint8_t unk23[0x4C - 0x23]; uint32_t flags4C;
    uint8_t unk50[0x278 - 0x50]; M1Rig145 *rig278;
} M1Ai145;
typedef struct M1Q145 { uint8_t unk00[0x10]; int32_t a10; int32_t a14; } M1Q145;
int  sub_001C7EE1(void);
M1Q145 *m1_Quest113430(M1Ai145 *e, int k);
void sub_00113090(M1Obj145 *o, M1Ai145 *e, int st);
void m1_AnimFrame1AEDF0(M1Anm145 *a, int frame);

/* Start the idle loop on a random frame (0..3, +3 half the time). */
#define M1_RANDFRAME145(o) do { M1Anm145 *a_; float f_ = (float)(sub_001C7EE1() % 4); \
    if (sub_001C7EE1() % 2 < 1) f_ += 3.0f; \
    a_ = (o)->mdl30->anim14; m1_AnimFrame1AEDF0(a_, _mm_cvtt_ss2si(_mm_set_ss(f_ / a_->spdC4))); } while (0)

/* 0x13B6E0: enter the idle state, random start frame. */
void m1_AiIdle13B6E0(M1Obj145 *o, M1Ai145 *e) {
    int st; M1Q145 *q;
    if (e->b20 & 1) { st = 0x17; q = m1_Quest113430(e, 2); q->a10 = 4; q->a14 = 4; }
    else st = 0x16;
    sub_00113090(o, e, st);
    M1_RANDFRAME145(o);
    if ((e->b20 & 1) && (e->rig278->f4 & 1)) { e->flags4C = (e->flags4C & ~0x10u) | 0x40; e->rig278->f4 |= 1; }
    o->f10 |= 0x20;
    e->rig278->f4 |= 0x400000;
}

/* 0x13B890: enter the look-around state, random start frame, sometimes queue a turn. */
void m1_AiLook13B890(M1Obj145 *o, M1Ai145 *e) {
    sub_00113090(o, e, (e->b22 & 1) + 0x35);
    M1_RANDFRAME145(o);
    e->rig278->f4 &= ~0x40000000u;
    if (!(e->b20 & 1) && sub_001C7EE1() % 8 < 1) e->rig278->f4 |= 0x40000000;
    o->f10 |= 0x20;
}


typedef struct M1Lt145 { uint8_t unk00[0x8C]; int32_t type8C; uint8_t unk90[0xC0 - 0x90]; int32_t nC0; uint8_t *arrC4; } M1Lt145;
typedef struct M1Src145 { uint8_t unk00[0x20]; M1Lt145 *lt20; void *f24; } M1Src145;
typedef struct M1Att145 { int32_t f0; uint32_t f4; uint8_t unk08[0xC]; M1Src145 *src14; int32_t idx18; uint8_t unk1C[4]; uint8_t m20[0xA5C - 0x20]; uint8_t mA5C[4]; } M1Att145;
extern uint8_t *m1_gfx283698;
void sub_001B2080(void *m);
void sub_001B2020(void *src, void *dst);

/* 0x338D0: attach a light (or one of its sub-lights) to a shading slot. */
void m1_LightAttach0338D0(M1Att145 *a, M1Src145 *s, int idx) {
    uint8_t *m; M1Lt145 *l;
    if (a == 0 || ((int32_t *)a)[-4] == 0 || s == 0 || s->lt20 == 0 || s->f24 == 0) return;
    m = 0;
    a->src14 = s; a->idx18 = idx;
    if (idx == -1) m = (uint8_t *)s->lt20;
    else {
        l = s->lt20;
        switch (l->type8C) {
        case 1: if (idx < l->nC0) m = l->arrC4 + idx * 0x108; break;
        case 9: if (idx < l->nC0) m = l->arrC4 + idx * 0x180; break;
        }
    }
    if (a->f0 != 0) return;
    sub_001B2080(a->m20);
    sub_001B2080(a->mA5C);
    if (m == 0) return;
    sub_001B2020(m, a->m20);
    sub_001B2020(m1_gfx283698 + ((a->f4 >> 1) & 1) * 0xB0 + 0x5845C, a->mA5C);
}

typedef struct M1Mdl145b { uint8_t unk00[0x20]; void *f20; } M1Mdl145b;
typedef struct M1Pw145 {
    uint8_t unk00[0x618]; void *fx618; uint8_t unk61C[0xD60 - 0x61C]; uint32_t flagsD60;
    uint8_t unkD64[0xD88 - 0xD64]; int32_t lvD88; uint8_t unkD8C[4]; float tD90;
    uint8_t unkD94[0xFD8 - 0xD94]; M1Mdl145b *mdlFD8;
} M1Pw145;
extern float m1_frameTime42C858;
void  sub_00033A40(void *fx);
void *sub_00036750(M1Mdl145b *m, int id);
void  m1_FxTint034D30(void *fx, float r, float g, float b, float a);

/* 0xD2090: run a timed power-up; attaches its effect, fades it near the end, removes it when done. */
void m1_PowerTick0D2090(M1Pw145 *o) {
    int n = o->lvD88; float lim = (float)n * 60.0f + 240.0f; void *p;
    if (!(o->flagsD60 & 1)) return;
    if (o->tD90 >= lim) {
        o->flagsD60 &= ~1u; o->tD90 = 0.0f;
        if (o->fx618 != 0) { sub_00033A40(o->fx618); o->fx618 = 0; }
        return;
    }
    o->tD90 += m1_frameTime42C858;
    p = o->fx618;
    if (p == 0) {
        if (o->mdlFD8 != 0 && o->mdlFD8->f20 != 0) p = sub_00036750(o->mdlFD8, n + 0x47);
        o->fx618 = p;
        return;
    }
    if (o->tD90 >= lim - 10.0f) m1_FxTint034D30(p, 1.0f, 1.0f, 1.0f, 0.800000012f);
}
