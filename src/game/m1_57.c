/* Area m1, file 57: player vector checks. Names inferred. */
#include <stdint.h>

typedef struct M1Pos64 { uint8_t unk00[0x64]; float y64; } M1Pos64;
typedef struct M1PlV {
    uint8_t unk000[0x5B4];
    float   y5B4;              /* +0x5B4 */
    uint8_t unk5B8[0x5D0 - 0x5B8];
    float   v5D0[4];           /* +0x5D0 */
    float   v5E0[4];           /* +0x5E0 */
    uint8_t unk5F0[0xFD8 - 0x5F0];
    M1Pos64 *refFD8;           /* +0xFD8 */
} M1PlV;
float sub_00082D70(const float *v);
void  sub_001ADAF0(float *dst, const float *a, const float *b);

/* 0x000CBEB0: when the length of +0x5D0 (0x82D70) is over 0.5, combines it with +0x5E0
 * (0x1ADAF0); then 1 when +0x5B4 - 5 is above the reference object's height, else -1. */
int m1_AboveRef0CBEB0(M1PlV *p)
{
    float *v = p->v5D0;
    if (sub_00082D70(v) > 0.5f)
        sub_001ADAF0(v, v, p->v5E0);
    if (p->y5B4 - 5.0f > p->refFD8->y64)
        return 1;
    return -1;
}

typedef struct M1Reward { uint8_t unk00[4]; int32_t kind04; int32_t lvl08; } M1Reward;
float sub_00171E20(int kind, int lvl);
int   sub_00026740(void);
short sub_00026650(void);
int   sub_000EDF10(M1Reward *r);

/* 0x000A82C0: reward amount: base value of (kind, level) (0x171E20, truncated) times
 * (0x26650 + 1 when 0x26740 says so, else 1) times 2 when 0x0EDF10 returns 1 (not for
 * kind 12), else 1. */
int m1_RewardAmount0A82C0(M1Reward *r)
{
    int base = (int)sub_00171E20(r->kind04, r->lvl08);
    int mul;
    int dbl;
    if (sub_00026740() == 0)
        mul = 1;
    else
        mul = sub_00026650() + 1;
    if (r->kind04 == 12)
        dbl = 1;
    else
        dbl = (sub_000EDF10(r) == 1) ? 2 : 1;
    return dbl * mul * base;
}

typedef struct M1Grow40 { uint32_t flags00; uint8_t unk04[0xC]; float size10; uint8_t unk14[0x40 - 0x14]; int32_t state40; } M1Grow40;
extern float m1_frameTime42C858;
void sub_000A41D0(M1Grow40 *o, int v);
void sub_000A4870(M1Grow40 *o, float size);

/* Shared body of 0x94360 / 0x943D0: state 0 grows +0x10 by frame time * 0.05 up to
 * the limit (then state 1) and applies the size (0xA4870); state 1 clears flag
 * 0x2000000 and calls 0xA41D0(-1). */
#define M1_GROW(name, lim)                                  \
void name(M1Grow40 *o)                                      \
{                                                           \
    float s;                                                \
    switch (o->state40) {                                   \
    case 0:                                                 \
        s = (float)(m1_frameTime42C858 * 0.05 + o->size10); \
        if (s >= (lim)) {                                   \
            s = (lim);                                      \
            o->state40 = 1;                                 \
        }                                                   \
        sub_000A4870(o, s);                                 \
        break;                                              \
    case 1:                                                 \
        o->flags00 &= ~0x2000000u;                          \
        sub_000A41D0(o, -1);                                \
        break;                                              \
    }                                                       \
}

/* 0x00094360: grow up to 1.8. */
M1_GROW(m1_Grow094360, 1.8f)
/* 0x000943D0: grow up to 1.0. */
M1_GROW(m1_Grow0943D0, 1.0f)
