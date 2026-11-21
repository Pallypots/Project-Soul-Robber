/* Area m1, file 281: bone shake. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Bn281 { uint8_t unk00[0x30]; float v30[4]; } M1Bn281;
typedef struct M1So281 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x5C]; float radius70; } M1So281;
typedef struct M1Ss281 { int32_t f0; uint8_t unk04[4]; float t8; int32_t fC; float dur10; float amp14; } M1Ss281;
float sub_001A3ED0(float a);                                  /* cos */
float sub_001A3EE0(float a);                                  /* sin */
int32_t sub_001C7EE1(void);                                   /* rand */
M1Bn281 *sub_0001D0F0(M1So281 *o, int32_t bone);
void sub_000F5D40(float *d, const float *s);
void sub_00113370(void *a, M1Ss281 *s);

/* 0x00143630: shake step: until the duration runs out, offset bone 1 of o in a random direction (any angle,
   in tenths of a degree) by radius * amplitude, marking o shaking (flag 4) on the first step; when time is up,
   clear the flag, finish the step and zero the offset. */
void m1_BoneShake143630(M1So281 *o, void *a, M1Ss281 *s)
{
    float ang, v[4];
    M1Bn281 *b;
    if (_mm_comige_ss(_mm_load_ss(&s->t8), _mm_load_ss(&s->dur10))) {
        o->flags10 &= ~4u;
        if (s->f0) s->f0 = 1;
        sub_00113370(a, s);
        b = sub_0001D0F0(o, 1);
        b->v30[0] = 0.0f;
        b->v30[1] = 0.0f;
        b->v30[2] = 0.0f;
        b->v30[3] = 1.0f;
        return;
    }
    ang = (float)(sub_001C7EE1() % 3600 - 1800) * 0.0017453294f;
    v[0] = sub_001A3ED0(ang) * o->radius70 * s->amp14;
    v[1] = 0.0f;
    v[2] = sub_001A3EE0(ang) * o->radius70 * s->amp14;
    v[3] = 1.0f;
    sub_000F5D40(sub_0001D0F0(o, 1)->v30, v);
    if (s->fC == 0) {
        o->flags10 |= 4;
        if (s->f0) s->f0 = 2;
        s->fC++;
    }
}

typedef struct M1Tx281 { int32_t f0; int16_t x4, y6; uint8_t unk08[0x8A8]; int32_t f8B0; uint8_t unk8B4[8]; uint32_t col8BC;
    uint8_t unk8C0[0x8C]; int32_t f94C; uint8_t unk950[8]; uint32_t col958; } M1Tx281;
void sub_00038060(uint32_t col);
void sub_00038380(void);
void *sub_000768D0(void *dl, void (*fn)(void), uint32_t col);

/* 0x00076FA0: draw text t with a soft outline: switch to a darker, channel-swapped colour, draw it d pixels
   left and right of its position, then restore t's position and colours and reset the colour. Returns dl.
   regargs: t=EAX, col=ESI; stack args (dl d). */
void *m1_TextOutline76FA0(M1Tx281 *t, uint32_t col, void *dl, int32_t d)
{
    int32_t x = t->x4, y = t->y6;
    int32_t s0 = t->f0, s958 = t->col958, s8bc = t->col8BC, s94c = t->f94C, s8b0 = t->f8B0;
    uint32_t c;
    sub_00038060(col);
    c = ((((col & 0xFE) << 16) | (col & 0xFE00)) << 7) | (((col & 0xFE0000) | (col >> 16)) >> 9);
    t->col958 = c;
    t->col8BC = c;
    t->f94C = 1;
    t->f8B0 = 1;
    t->x4 = (int16_t)(x - d);
    sub_000768D0(dl, sub_00038380, col);
    t->x4 = (int16_t)(d + x);
    sub_000768D0(dl, sub_00038380, col);
    t->y6 = (int16_t)y;
    t->f0 = s0;
    t->col958 = s958;
    t->x4 = (int16_t)x;
    t->col8BC = s8bc;
    t->f94C = s94c;
    t->f8B0 = s8b0;
    sub_00038060((uint32_t)-1);
    return dl;
}
