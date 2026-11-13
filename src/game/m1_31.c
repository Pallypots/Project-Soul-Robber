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

typedef struct M1VecHold2 {
    uint8_t unk000[0xB4];
    float   fB4;               /* +0xB4 */
    float   vB8[3];            /* +0xB8 */
    float   vC4[4];            /* +0xC4 */
} M1VecHold2;
extern float m1_frameRate42C85C;   /* 0x0042C85C */

/* 0x0010C510: as 0x109400 but also sets h's speed (+0xB4 = frame rate * 98) and
 * clears +0xB8..+0xC0; modes 0xF3B30(0x44), 0xF3B00(0x20). */
void m1_ResetMotion10C510(M1Ef50 *o, M1VecHold2 *h)
{
    h->fB4 = m1_frameRate42C85C * 98.0f;
    h->vB8[2] = 0.0f;
    h->vB8[1] = 0.0f;
    h->vB8[0] = 0.0f;
    h->vC4[3] = 0.0f;
    h->vC4[2] = 0.0f;
    h->vC4[1] = 0.0f;
    h->vC4[0] = 0.0f;
    o->f50 = 0.0f;
    sub_000F3B30(o, 0x44);
    sub_000F3B00(o, 0x20);
}

typedef struct M1Spd15C {
    uint8_t unk000[0x15C];
    float   v15C[4];           /* +0x15C */
    uint8_t unk16C[0x188 - 0x16C];
    float   f188;              /* +0x188 */
} M1Spd15C;
void sub_000F3DA0(void *o, int a, int b, int c);

/* 0x0010E350: zeroes h's speed vector (each frame rate * 0.0, as the original), sets
 * +0x188 = 0.2 and starts mode 0x27 on o. */
void m1_StopSpeed10E350(void *o, M1Spd15C *h)
{
    h->v15C[0] = m1_frameRate42C85C * 0.0f;
    h->v15C[1] = m1_frameRate42C85C * 0.0f;
    h->v15C[2] = m1_frameRate42C85C * 0.0f;
    h->v15C[3] = m1_frameRate42C85C * 0.0f;
    h->f188 = 0.2f;
    sub_000F3DA0(o, 0x27, 0, 0);
}

typedef struct M1Ef60 { uint8_t unk00[0x60]; float pos60[4]; } M1Ef60;
int sub_000494D0(int id, const void *pos, int c);

/* 0x0010C590: like 0x10C510 with modes 0xF3B30(0x20), 0xF3B00(0x44), 0xF3B30(0x20),
 * 0xF3F00(0) and sound 0x19B at o. */
void m1_ResetMotion10C590(M1Ef60 *o, M1VecHold2 *h)
{
    sub_000F3B30(o, 0x20);
    h->fB4 = m1_frameRate42C85C * 98.0f;
    h->vB8[2] = 0.0f;
    h->vB8[1] = 0.0f;
    h->vB8[0] = 0.0f;
    h->vC4[3] = 0.0f;
    h->vC4[2] = 0.0f;
    h->vC4[1] = 0.0f;
    h->vC4[0] = 0.0f;
    sub_000F3B00(o, 0x44);
    sub_000F3B30(o, 0x20);
    sub_000F3F00(o, 0.0f);
    sub_000494D0(0x19B, o->pos60, 1);
}

void sub_000F3BB0(void *o, int a, int b);

/* 0x0010ED90: zeroes the first two speed components (frame rate * 0.0), clears
 * +0x188 and sets modes 0xF3B00(5), 0xF3BB0(0, 0). */
void m1_StopSpeed10ED90(void *o, M1Spd15C *h)
{
    h->v15C[0] = m1_frameRate42C85C * 0.0f;
    h->v15C[1] = m1_frameRate42C85C * 0.0f;
    h->f188 = 0.0f;
    sub_000F3B00(o, 5);
    sub_000F3BB0(o, 0, 0);
}

/* 0x0010B910: speed = frame rate * 98, vectors cleared, modes 0xF3B00(4), 0xF3B30(0x20). */
void m1_ResetMotion10B910(void *o, M1VecHold2 *h)
{
    h->fB4 = m1_frameRate42C85C * 98.0f;
    h->vB8[2] = 0.0f;
    h->vB8[1] = 0.0f;
    h->vB8[0] = 0.0f;
    h->vC4[3] = 0.0f;
    h->vC4[2] = 0.0f;
    h->vC4[1] = 0.0f;
    h->vC4[0] = 0.0f;
    sub_000F3B00(o, 4);
    sub_000F3B30(o, 0x20);
}

/* 0x0010C630: modes 0xF3B00(0x20), speed = frame rate * 98, vectors and o +0x50
 * cleared, 0xF3B30(0x44), 0xF3B00(0x20). */
void m1_ResetMotion10C630(M1Ef50 *o, M1VecHold2 *h)
{
    sub_000F3B00(o, 0x20);
    h->fB4 = m1_frameRate42C85C * 98.0f;
    h->vB8[2] = 0.0f;
    h->vB8[1] = 0.0f;
    h->vB8[0] = 0.0f;
    h->vC4[3] = 0.0f;
    h->vC4[2] = 0.0f;
    h->vC4[1] = 0.0f;
    h->vC4[0] = 0.0f;
    o->f50 = 0.0f;
    sub_000F3B30(o, 0x44);
    sub_000F3B00(o, 0x20);
}
