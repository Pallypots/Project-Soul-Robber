/* Area m1, file 98: flicker and shake steps. Names inferred. */
#include <stdint.h>

typedef struct M1Obj98 {
    uint8_t unk00[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t unk14[0x54 - 0x14];
    float   yaw54;             /* +0x54 */
    uint8_t unk58[0x70 - 0x58];
    float   scale70[3];        /* +0x70 */
    float   f7C;               /* +0x7C */
} M1Obj98;
typedef struct M1Step98 { uint8_t unk00[0x54]; int32_t phase54; uint8_t unk58[0x5C - 0x58]; float t5C; uint8_t unk60[0x74 - 0x60]; uint32_t *sub74; } M1Step98;
extern float m1_frameRate42C85C;
void *sub_00035D80(void *o, int a, int b);
int  aab_Rand(void);
void sub_001671D0(void *o, void *h, int v);

/* 0x00167E20: shimmer: phase 0 starts effect 1 and a 1 s timer; phase 1 jitters the yaw by
 * +-5 degrees at random, scales the object by 1 - timer, and when the timer runs out clears
 * o flags 0x41 and sub flag 0x40, rearms it for 3..9 s, runs 0x1671D0(5) and restores scale 1. */
void m1_Shimmer167E20(M1Obj98 *o, M1Step98 *h)
{
    uint32_t *s = h->sub74;
    int r;
    float k;
    switch (h->phase54) {
    case 0:
        sub_00035D80(o, 1, 0);
        h->t5C = 1.0f;
        h->phase54++;
        /* fall through */
    case 1:
        r = aab_Rand();
        if (r & 1) {
            if (r & 2)
                o->yaw54 = o->yaw54 + 0.087266468f;
            else
                o->yaw54 = o->yaw54 - 0.087266468f;
        }
        k = 1.0f - h->t5C;
        o->scale70[0] = k;
        o->scale70[1] = k;
        o->scale70[2] = k;
        o->f7C = 1.0f;
        if (0.0f > h->t5C) {
            o->flags10 &= ~0x41u;
            *s &= ~0x40u;
            h->t5C = (float)(aab_Rand() % 7 + 3) * m1_frameRate42C85C * 60.0f;
            sub_001671D0(o, h, 5);
            o->scale70[0] = 1.0f;
            o->scale70[1] = 1.0f;
            o->scale70[2] = 1.0f;
        }
        break;
    }
}


typedef struct M1Sub98F { uint32_t flags00; float speed04; float boost08; } M1Sub98F;
typedef struct M1Step98F { uint8_t unk00[0x74]; M1Sub98F *sub74; } M1Step98F;
typedef struct M1Obj98F {
    uint8_t unk00[0x20];
    float  *node20;            /* +0x20 */
    uint8_t unk24[0x50 - 0x24];
    float   pitch50;           /* +0x50 */
    float   yaw54;             /* +0x54 */
    uint8_t unk58[0x80 - 0x58];
    float   vel80[4];          /* +0x80 */
} M1Obj98F;
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *s, float a);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);

/* 0x0016B950: fly: wrap the yaw to -pi..pi, build the node from pitch +0x50 and yaw, turn the
 * velocity by it, bump +0x84 by 1 and scale the velocity to the sub speed (x1.5 when boosted).
 * Spins unless the sub record is active. */
void m1_Fly16B950(M1Obj98F *o, M1Step98F *h)
{
    M1Sub98F *s = h->sub74;
    float m[16];
    float k;
    if (!(s->flags00 & 1))
        for (;;) ;
    if (-3.1415927f > o->yaw54)
        o->yaw54 += 6.2831855f;
    if (o->yaw54 > 3.1415927f)
        o->yaw54 -= 6.2831855f;
    sub_001AD940(m);
    sub_001AD8B0(o->node20, m, o->pitch50);
    sub_001AD8E0(o->node20, o->node20, o->yaw54);
    sub_001AD9B0(o->vel80, o->node20, o->vel80);
    k = s->speed04;
    if (s->boost08 > 0.0f)
        k = s->speed04 * 1.5f;
    o->vel80[1] += 1.0f;
    sub_001ADBA0(o->vel80, o->vel80, k);
}
