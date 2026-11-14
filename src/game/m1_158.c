/* Area m1, file 158: player height helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Md158 { uint8_t unk00[0xC4]; uint8_t *skC4; } M1Md158;
typedef struct M1Fm158 { uint8_t unk00[0x20]; M1Md158 *mdl20; } M1Fm158;
typedef struct M1Pl158 { uint8_t unk00[0x190]; float h190; float f194; float v198[4]; uint8_t unk1A8[0xFD8 - 0x1A8]; M1Fm158 *fmFD8; } M1Pl158;
void sub_000F5D40(float *d, const void *s);
int  m1_ActHp0CF1A0(M1Pl158 *o);

/* 0xC42B0: measure the player's height from three skeleton joints and set the camera offsets. */
void m1_PlHeight0C42B0(M1Pl158 *o) {
    struct { float y[4]; float z[4]; float x[4]; } l; uint8_t *sk; float d;
    l.x[0] = 0.0f; l.x[1] = 0.0f; l.x[2] = 0.0f; l.x[3] = 1.0f;
    l.y[0] = 0.0f; l.y[1] = 0.0f; l.y[2] = 0.0f; l.y[3] = 1.0f;
    l.z[0] = 0.0f; l.z[1] = 0.0f; l.z[2] = 0.0f; l.z[3] = 1.0f;
    sk = o->fmFD8->mdl20->skC4;
    sub_000F5D40(o->v198, sk + 0x370);
    sub_000F5D40(l.x, o->fmFD8->mdl20->skC4 + 0x19F0);
    sub_000F5D40(l.y, o->fmFD8->mdl20->skC4 + 0x3AF0);
    sub_000F5D40(l.z, o->fmFD8->mdl20->skC4 + 0x3F70);
    if (l.z[1] > l.y[1]) l.y[1] = l.z[1];
    if (l.x[1] > l.y[1]) o->v198[1] = l.x[1] + 1.0f; else o->v198[1] = l.y[1];
    d = l.y[1] - l.x[1];
    o->h190 = d;
    if (0.0f > d) o->h190 = d * -1.0f;
    o->h190 = o->h190 + 4.0f;
    o->f194 = m1_ActHp0CF1A0(o) >= 0 ? 5.0f : 3.0f;
}

typedef struct M1Sl158 { uint8_t unk00[0x40]; int32_t x40; } M1Sl158;
typedef struct M1Rg158 { uint8_t unk00[8]; void *p8; int32_t iC; float t10; int32_t n14; int32_t i18; uint8_t unk1C[8]; int16_t w24; uint8_t unk26[2]; float f28; } M1Rg158;
typedef struct M1Ob158 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; uint8_t unk14[0xC]; uint8_t *m20; uint8_t unk24[0x3C]; float pos60[4]; uint8_t unk70[0x14C - 0x70]; int32_t i14C; } M1Ob158;
typedef struct M1Ai158 { uint8_t unk00[0x278]; M1Rg158 *rig278; } M1Ai158;
extern float m1_frameRate42C85C;
extern void *m1_scene42C8E4;
M1Sl158 *m1_SlotGet0A4290(int i);
void *m1_SlotObj0A42A0(int i);
void  m1_SlotHold0A2930(M1Sl158 *s, M1Ob158 *o);
uint8_t *sub_0001D0F0(void *o, int b);
void sub_001B2080(void *m);
void sub_001B2020(void *src, void *dst);
void sub_000ED780(M1Ob158 *o);
void sub_0001EB80(M1Ob158 *o);
void sub_0001E9B0(void *sc, M1Ob158 *o, int k, int a, int b);
void sub_001ADA40(void *d, const void *m);
void m1_AiGoto113040(M1Ob158 *o, M1Ai158 *e, int st);

/* 0x17C7C0: item in a holder: wait, attach to the holder's hand, then drop free when the holder lets go. */
void m1_ItemHeld17C7C0(M1Ob158 *o, M1Ai158 *e) {
    M1Rg158 *r = e->rig278; uint8_t *b;
    switch (r->n14) {
    case 0:
        if (r->t10 > 0.100000001f) { r->n14 = 1; return; }
        r->t10 += m1_frameRate42C85C;
        return;
    case 1:
        if (r->i18 >= 0) r->p8 = m1_SlotObj0A42A0(r->i18);
        if (r->p8 != 0) {
            b = sub_0001D0F0(r->p8, 0xB);
            sub_001B2080(o->m20);
            sub_001B2020(b, o->m20);
            o->pos60[1] -= 0.800000012f;
            m1_SlotHold0A2930(m1_SlotGet0A4290(r->i18), o);
            r->n14++;
            return;
        }
        sub_000ED780(o);
        return;
    case 2:
        if (m1_SlotGet0A4290(r->i18)->x40 != 3) return;
        sub_0001EB80(o);
        sub_0001E9B0(m1_scene42C8E4, o, o->i14C, 5, 0x11);
        b = sub_0001D0F0(r->p8, 0xB);
        sub_001ADA40(o->m20, o->m20 + 0x40);
        sub_000F5D40(o->pos60, b + 0x70);
        o->f10 = (o->f10 & ~0x41u) | 0x200;
        o->fC |= 0x200;
        r->f28 = r->iC != 0 ? 3.0f : 7.0999999f;
        r->w24 = 1;
        m1_AiGoto113040(o, e, 2);
        return;
    }
}
