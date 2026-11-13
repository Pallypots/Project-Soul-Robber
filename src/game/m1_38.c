/* Area m1, file 38: GPU command block builder. Names inferred. */
#include <stdint.h>

extern uint32_t m1_colour2C453C[4];      /* 0x002C453C */
void sub_001ADA40(uint32_t *dst, const void *m);
void sub_001B1F70(uint32_t *dst, const void *m);

/* 0x0003A020: writes a fixed command block (two matrices from m, state words and the
 * colour at 0x2C453C) at p; returns the next free word. regargs: p=EAX m=EBX */
uint32_t *m1_EmitBlock3A020(uint32_t *p, const void *m)
{
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x11000000;
    p[4] = 0x10000008;
    p[5] = 0;
    p[6] = 0x1000101;
    p[7] = 0x6C08001B;
    sub_001ADA40(&p[8], m);
    sub_001B1F70(&p[0x18], m);
    p[0x29] = 0;
    p[0x28] = 0x10000000;
    p[0x2A] = 0x14000000;
    p[0x2B] = 0x11000000;
    p[0x2D] = 0;
    p[0x2C] = 0x10000001;
    p[0x2E] = 0x1000101;
    p[0x2F] = 0x30000000;
    p[0x33] = m1_colour2C453C[3];
    p[0x32] = m1_colour2C453C[2];
    p[0x31] = m1_colour2C453C[1];
    p[0x30] = m1_colour2C453C[0];
    return &p[0x34];
}

typedef struct M1Def34 { uint32_t w[0xD]; } M1Def34;
extern const M1Def34 m1_defaults2E4720[10];   /* 0x002E4720 */
extern M1Def34 m1_live3ED540[10];             /* 0x003ED540 */

/* 0x000A9EF0: restores the ten 0x34-byte records from their defaults. */
void m1_RestoreDefaultsA9EF0(void)
{
    m1_live3ED540[0] = m1_defaults2E4720[0];
    m1_live3ED540[1] = m1_defaults2E4720[1];
    m1_live3ED540[2] = m1_defaults2E4720[2];
    m1_live3ED540[3] = m1_defaults2E4720[3];
    m1_live3ED540[4] = m1_defaults2E4720[4];
    m1_live3ED540[5] = m1_defaults2E4720[5];
    m1_live3ED540[6] = m1_defaults2E4720[6];
    m1_live3ED540[7] = m1_defaults2E4720[7];
    m1_live3ED540[8] = m1_defaults2E4720[8];
    m1_live3ED540[9] = m1_defaults2E4720[9];
}

typedef struct M1Curve19C { uint8_t raw[0x19C]; } M1Curve19C;
typedef struct M1CurveSet {
    uint8_t    unk000[4];
    M1Curve19C c[10];          /* +0x004 */
} M1CurveSet;
typedef struct M1Pose44 {
    uint8_t unk00[0x10];
    float   s10[3];            /* +0x10 */
    uint8_t unk1C[4];
    float   r20[3];            /* +0x20 */
    uint8_t unk2C[4];
    float   t30[3];            /* +0x30 */
    uint8_t unk3C[4];
    float   v40;               /* +0x40 */
} M1Pose44;
float sub_00062080(const M1Curve19C *c, int t);

/* 0x000191F0: samples the ten curves of set at time t into the pose. */
void m1_SamplePose191F0(const M1CurveSet *set, M1Pose44 *out, int t)
{
    out->t30[0] = sub_00062080(&set->c[0], t);
    out->t30[1] = sub_00062080(&set->c[1], t);
    out->t30[2] = sub_00062080(&set->c[2], t);
    out->r20[0] = sub_00062080(&set->c[3], t);
    out->r20[1] = sub_00062080(&set->c[4], t);
    out->r20[2] = sub_00062080(&set->c[5], t);
    out->s10[0] = sub_00062080(&set->c[6], t);
    out->s10[1] = sub_00062080(&set->c[7], t);
    out->s10[2] = sub_00062080(&set->c[8], t);
    out->v40 = sub_00062080(&set->c[9], t);
}

typedef struct M1Rec54 {
    int32_t f00, f04, f08;     /* +0x00 */
    uint8_t unk0C[0x18 - 0xC];
    int32_t h18;               /* +0x18, -1 */
    uint8_t unk1C[0x24 - 0x1C];
    int16_t w24;               /* +0x24 */
    uint8_t unk26[0x50 - 0x26];
    int16_t w50;               /* +0x50, -1 */
    uint8_t unk52[2];
} M1Rec54;
extern M1Rec54 m1_recs3FDC70[6];   /* 0x003FDC70 */
#define M1_REC54_INIT(r) (r).f00 = 0; (r).f04 = 0; (r).f08 = 0; (r).h18 = -1; (r).w24 = 0; (r).w50 = -1
/* 0x0017CDC0: resets the six 0x54 records (unrolled, as the original). */
void m1_ResetRecs17CDC0(void)
{
    M1_REC54_INIT(m1_recs3FDC70[0]);
    M1_REC54_INIT(m1_recs3FDC70[1]);
    M1_REC54_INIT(m1_recs3FDC70[2]);
    M1_REC54_INIT(m1_recs3FDC70[3]);
    M1_REC54_INIT(m1_recs3FDC70[4]);
    M1_REC54_INIT(m1_recs3FDC70[5]);
}
