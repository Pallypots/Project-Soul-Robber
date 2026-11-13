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

/* 0x0010EC80: zeroes the speed vector (frame rate * 0.0), modes 0xF3B00(5),
 * 0xF3BB0(0, 0) and starts mode 0x12. */
void m1_StopSpeed10EC80(void *o, M1Spd15C *h)
{
    h->v15C[0] = m1_frameRate42C85C * 0.0f;
    h->v15C[1] = m1_frameRate42C85C * 0.0f;
    h->v15C[2] = m1_frameRate42C85C * 0.0f;
    h->v15C[3] = m1_frameRate42C85C * 0.0f;
    sub_000F3B00(o, 5);
    sub_000F3BB0(o, 0, 0);
    sub_000F3DA0(o, 0x12, 0, 0);
}

typedef struct M1VecHold3 {
    uint8_t unk000[0x98];
    int32_t snd098;            /* +0x98, <0 = none */
    uint8_t unk09C[0xB4 - 0x9C];
    float   fB4;               /* +0xB4 */
    float   vB8[3];            /* +0xB8 */
    float   vC4[4];            /* +0xC4 */
} M1VecHold3;
void sub_00048250(int h);

/* 0x0010AB90: speed = frame rate * 98, vectors and o +0x50 cleared, modes 0x44 /
 * 0x20, and stops the sound at +0x98. */
void m1_ResetMotion10AB90(M1Ef50 *o, M1VecHold3 *h)
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
    if (h->snd098 >= 0) {
        sub_00048250(h->snd098);
        h->snd098 = -1;
    }
}

typedef struct M1VecHold4 {
    uint8_t unk000[0x94];
    void   *res094;            /* +0x94 */
    uint8_t unk098[0xB4 - 0x98];
    float   fB4;               /* +0xB4 */
    float   vB8[3];            /* +0xB8 */
    float   vC4[4];            /* +0xC4 */
} M1VecHold4;
void sub_00033A70(void *r);

/* 0x0010C030: speed = frame rate * 98, vectors and o +0x50 cleared, frees the
 * resource at +0x94, modes 4 / 0x20. */
void m1_ResetMotion10C030(M1Ef50 *o, M1VecHold4 *h)
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
    if (h->res094 != 0) {
        sub_00033A70(h->res094);
        h->res094 = 0;
    }
    sub_000F3B30(o, 4);
    sub_000F3B00(o, 0x20);
}

typedef struct M1Spd2 {
    uint8_t unk000[0xC8];
    void   *partC8;            /* +0xC8 */
    uint8_t unk0CC[0x15C - 0xCC];
    float   v15C[4];           /* +0x15C */
    uint8_t unk16C[0x188 - 0x16C];
    float   f188, f18C;        /* +0x188 */
} M1Spd2;

/* 0x0010E810: speed vector = frame rate * 0.0, modes 5, 0xF3BB0(0,0), 0x10; then
 * +0x188 / +0x18C cleared. */
void m1_StopSpeed10E810(void *o, M1Spd2 *h)
{
    h->v15C[0] = m1_frameRate42C85C * 0.0f;
    h->v15C[1] = m1_frameRate42C85C * 0.0f;
    h->v15C[2] = m1_frameRate42C85C * 0.0f;
    h->v15C[3] = m1_frameRate42C85C * 0.0f;
    sub_000F3B00(o, 5);
    sub_000F3BB0(o, 0, 0);
    sub_000F3DA0(o, 0x10, 0, 0);
    h->f188 = 0.0f;
    h->f18C = 0.0f;
}

/* 0x0010E470: speed vector = frame rate * 0.0, +0x188 cleared, mode 4 on o and on
 * the part at +0xC8, 0xF3BB0(0,0), start mode 0x24. */
void m1_StopSpeed10E470(void *o, M1Spd2 *h)
{
    h->v15C[0] = m1_frameRate42C85C * 0.0f;
    h->v15C[1] = m1_frameRate42C85C * 0.0f;
    h->v15C[2] = m1_frameRate42C85C * 0.0f;
    h->v15C[3] = m1_frameRate42C85C * 0.0f;
    h->f188 = 0.0f;
    sub_000F3B00(o, 4);
    sub_000F3B00(h->partC8, 4);
    sub_000F3BB0(o, 0, 0);
    sub_000F3DA0(o, 0x24, 0, 0);
}

typedef struct M1VecHold5 {
    uint8_t unk000[0x94];
    void   *res094;            /* +0x94 */
    int32_t snd098;            /* +0x98 */
    uint8_t unk09C[0xA8 - 0x9C];
    int32_t fA8;               /* +0xA8 */
    uint8_t unk0AC[0xB4 - 0xAC];
    float   fB4;               /* +0xB4 */
    float   vB8[3];            /* +0xB8 */
    float   vC4[4];            /* +0xC4 */
    uint8_t unk0D4[0xF8 - 0xD4];
    int32_t fF8;               /* +0xF8 */
} M1VecHold5;
void *sub_00109050(void *o, int k);

#define M1_MOTION_CLEAR(h) \
    (h)->fB4 = m1_frameRate42C85C * 98.0f; \
    (h)->vB8[2] = 0.0f; (h)->vB8[1] = 0.0f; (h)->vB8[0] = 0.0f; \
    (h)->vC4[3] = 0.0f; (h)->vC4[2] = 0.0f; (h)->vC4[1] = 0.0f; (h)->vC4[0] = 0.0f

/* 0x0010BCD0: motion clear; creates the +0x94 resource (0x109050 kind 2) if
 * missing; modes 0xF3B00(4), 0xF3B30(0x20); clears +0xA8 and +0xF8. */
void m1_ResetMotion10BCD0(void *o, M1VecHold5 *h)
{
    M1_MOTION_CLEAR(h);
    if (h->res094 == 0)
        h->res094 = sub_00109050(o, 2);
    sub_000F3B00(o, 4);
    sub_000F3B30(o, 0x20);
    h->fA8 = 0;
    h->fF8 = 0;
}

/* 0x0010C460: motion clear; frees the +0x94 resource and stops the +0x98 sound;
 * modes 0xF3B00(0x20), 0xF3F00(0.5). */
void m1_ResetMotion10C460(void *o, M1VecHold5 *h)
{
    M1_MOTION_CLEAR(h);
    if (h->res094 != 0) {
        sub_00033A70(h->res094);
        h->res094 = 0;
    }
    if (h->snd098 >= 0) {
        sub_00048250(h->snd098);
        h->snd098 = -1;
    }
    sub_000F3B00(o, 0x20);
    sub_000F3F00(o, 0.5f);
}

typedef struct M1Ef10C { uint8_t unk000[0x10C]; float f10C; } M1Ef10C;

/* 0x0010E100: speed vector = frame rate * 0.0, o +0x10C cleared, mode 1, strength
 * 1.5, mode 4 on o and on the part at +0xC8, 0xF3BB0(0,0). */
void m1_StopSpeed10E100(M1Ef10C *o, M1Spd2 *h)
{
    h->v15C[0] = m1_frameRate42C85C * 0.0f;
    h->v15C[1] = m1_frameRate42C85C * 0.0f;
    h->v15C[2] = m1_frameRate42C85C * 0.0f;
    h->v15C[3] = m1_frameRate42C85C * 0.0f;
    o->f10C = 0.0f;
    sub_000F3DA0(o, 1, 0, 0);
    sub_000F3F00(o, 1.5f);
    sub_000F3B30(o, 4);
    sub_000F3B00(h->partC8, 4);
    sub_000F3BB0(o, 0, 0);
}
