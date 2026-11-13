/* Area m1, file 31: small record and actor helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Act16C {
    uint8_t unk000[0x16C];
    int32_t mode16C;           /* +0x16C */
} M1Act16C;
void sub_000CA850(M1Act16C *a, float v, float lim, int on, int mode, float b);
void sub_000CA9C0(M1Act16C *a, float v, float lim, int mode, float b);

/* 0x000CAB30: scales x and feeds it to the two actor limiters 0xCA850 and 0xCA9C0. */
void m1_FeedLimitsCAB30(M1Act16C *a, float x)
{
    float v = x * 0.096f;
    int mode = a->mode16C;
    sub_000CA850(a, v, 80.0f, 1, mode, 50.0f);
    sub_000CA9C0(a, v, 10000.0f, mode, 30.0f);
}

typedef struct M1ActLvl {
    uint8_t unk000[0x16C];
    int32_t mode16C;           /* +0x16C */
    uint8_t unk170[0xD6C - 0x170];
    int32_t level0D6C;         /* +0xD6C */
} M1ActLvl;
void sub_000CA850L(M1ActLvl *a, float v, float lim, int on, int mode, float b);   /* 0x000CA850 */

/* 0x000CAAD0: feeds the level-scaled values ((level+1)*0.96, (level+5)*10) to
 * limiter 0xCA850 (off, mode, 50). */
void m1_FeedLevelCAAD0(M1ActLvl *a)
{
    int n = a->level0D6C;
    sub_000CA850L(a, (float)(n + 1) * 0.96f, ((float)n + 5.0f) * 10.0f, 0, a->mode16C, 50.0f);
}

typedef struct M1VecHold { uint8_t unk000[0xC4]; float vC4[4]; } M1VecHold;
typedef struct M1Ef50 { uint8_t unk00[0x50]; float f50; } M1Ef50;
void sub_000F3B30(void *o, int v);
void sub_000F3B00(void *o, int v);
void sub_000F3F00(void *o, float v);

/* 0x00109400: zeroes h's vector at +0xC4 and o's +0x50, then sets o's modes
 * (0xF3B30 4, 0xF3B00 0x20, 0xF3F00 0.5). */
void m1_ResetMotion109400(M1Ef50 *o, M1VecHold *h)
{
    h->vC4[3] = 0.0f;
    h->vC4[2] = 0.0f;
    h->vC4[1] = 0.0f;
    h->vC4[0] = 0.0f;
    o->f50 = 0.0f;
    sub_000F3B30(o, 4);
    sub_000F3B00(o, 0x20);
    sub_000F3F00(o, 0.5f);
}
