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

typedef struct M1Anim14 { uint8_t unk00[8]; int32_t cur08; uint8_t unk0C[8]; void *h14; } M1Anim14;
typedef struct M1EfAn { uint8_t unk00[0x30]; M1Anim14 *anim30; } M1EfAn;
typedef struct M1Fuel {
    uint8_t unk000[0xC8];
    void   *partC8;            /* +0xC8 */
    uint8_t unk0CC[0xDC - 0xCC];
    float   rateDC;            /* +0xDC */
    uint8_t unk0E0[0x184 - 0xE0];
    float   fuel184;           /* +0x184 */
} M1Fuel;
typedef struct M1Comp6CB { uint8_t unk00[0x6C]; int32_t mode6C; } M1Comp6CB;
extern float aec_fps42C964;    /* 0x0042C964 */
void       sub_0001EEC0(void *o, float v);
int        sub_001AEE90(void *h, int k);
M1Comp6CB *sub_0001D960F(void *o, int kind);   /* 0x0001D960 */
void       sub_000F3D10(void *o, void *c, int mode);

/* 0x0010E760: drains the fuel at +0x184 by rate * 3.5 / (fps * 1.12), floored at
 * 0, feeds it to 0x1EEC0; during animation 0x30 with flag 2, sets modes 4 on o and
 * its part and switches the kind-5 component to mode 4. */
void m1_DrainFuel10E760(M1EfAn *o, M1Fuel *h)
{
    float t = aec_fps42C964 * 1.12f;
    h->fuel184 = h->fuel184 - h->rateDC * 3.5f / t;
    if (0.0f > h->fuel184)
        h->fuel184 = 0.0f;
    sub_0001EEC0(o, h->fuel184);
    if (o->anim30->cur08 != 0x30)
        return;
    if (!(sub_001AEE90(o->anim30->h14, 0) & 2))
        return;
    sub_000F3B30(o, 4);
    sub_000F3B30(h->partC8, 4);
    sub_000F3D10(o, sub_0001D960F(o, 5), 4);
}

typedef struct M1Spd3 {
    uint8_t unk000[0xC8];
    void   *partC8;            /* +0xC8 */
    uint8_t unk0CC[0xDC - 0xCC];
    float   fDC;               /* +0xDC */
    void   *resE0;             /* +0xE0 */
    uint8_t unk0E4[0x15C - 0xE4];
    float   v15C[4];           /* +0x15C */
    float   f16C;              /* +0x16C */
    int32_t f170;              /* +0x170 */
    uint8_t unk174[0x17C - 0x174];
    int32_t f17C, f180;        /* +0x17C */
} M1Spd3;
typedef struct M1Comp5E4B { uint8_t unk00[0xE4]; int32_t sndE4; } M1Comp5E4B;
void        sub_000F3C40(void *o);
M1Comp5E4B *sub_0001D960G(void *o, int kind);   /* 0x0001D960 */

#define M1_SPEED_ZERO(h) \
    (h)->v15C[0] = m1_frameRate42C85C * 0.0f; \
    (h)->v15C[1] = m1_frameRate42C85C * 0.0f; \
    (h)->v15C[2] = m1_frameRate42C85C * 0.0f; \
    (h)->v15C[3] = m1_frameRate42C85C * 0.0f

/* 0x0010E1B0: speed vector = frame rate * 0.0, 0xF3C40, clears +0x16C..+0x180,
 * mode 4 on o and its part, 0xF3BB0(0,0) twice, start mode 0x20. */
void m1_StopSpeed10E1B0(void *o, M1Spd3 *h)
{
    M1_SPEED_ZERO(h);
    sub_000F3C40(o);
    sub_000F3BB0(o, 0, 0);
    h->f16C = 0.0f;
    h->f170 = 0;
    h->f17C = 0;
    h->f180 = 0;
    sub_000F3B00(o, 4);
    sub_000F3B00(h->partC8, 4);
    sub_000F3BB0(o, 0, 0);
    sub_000F3DA0(o, 0x20, 0, 0);
}

/* 0x0010E280: speed vector = frame rate * 0.0, o +0x10C cleared, frees +0xE0,
 * stops the kind-5 sound, mode 4 (0xF3B30) on o and its part. */
void m1_StopSpeed10E280(M1Ef10C *o, M1Spd3 *h)
{
    M1Comp5E4B *c;
    M1_SPEED_ZERO(h);
    o->f10C = 0.0f;
    if (h->resE0 != 0) {
        sub_00033A70(h->resE0);
        h->resE0 = 0;
    }
    c = sub_0001D960G(o, 5);
    if (c->sndE4 >= 0) {
        sub_00048250(c->sndE4);
        c->sndE4 = -1;
    }
    sub_000F3B30(o, 4);
    sub_000F3B30(h->partC8, 4);
}

/* 0x0010E030: as 0x10E280 without clearing o +0x10C. */
void m1_StopSpeed10E030(void *o, M1Spd3 *h)
{
    M1Comp5E4B *c;
    M1_SPEED_ZERO(h);
    if (h->resE0 != 0) {
        sub_00033A70(h->resE0);
        h->resE0 = 0;
    }
    c = sub_0001D960G(o, 5);
    if (c->sndE4 >= 0) {
        sub_00048250(c->sndE4);
        c->sndE4 = -1;
    }
    sub_000F3B30(o, 4);
    sub_000F3B30(h->partC8, 4);
}

typedef struct M1EfC50 { uint8_t unk00[0xC]; uint32_t flags0C; uint8_t unk10[0x50 - 0x10]; float f50; } M1EfC50;
M1Comp6CB *sub_0001D960H(void *o, int kind);   /* 0x0001D960 */
void sub_000F3B70(void *o, int v);

/* 0x0010B250: motion clear, o +0x50 cleared, frees +0x94, modes 0x44 / 0x20,
 * strength 0.5, flag 0x80, puts the kind-5 component back to mode 0, then 0xF3B70(3). */
void m1_ResetMotion10B250(M1EfC50 *o, M1VecHold4 *h)
{
    M1Comp6CB *c;
    M1_MOTION_CLEAR(h);
    o->f50 = 0.0f;
    if (h->res094 != 0) {
        sub_00033A70(h->res094);
        h->res094 = 0;
    }
    sub_000F3B30(o, 0x44);
    sub_000F3B00(o, 0x20);
    sub_000F3F00(o, 0.5f);
    o->flags0C |= 0x80;
    c = sub_0001D960H(o, 5);
    if (c->mode6C != 0)
        sub_000F3D10(o, c, 0);
    sub_000F3B70(o, 3);
}

extern uint8_t m1_snd3E1270[];
void sub_00019000(void *s, int v);
void sub_000BCA50(int v);

/* 0x0010D6B0: as 0x10E030 plus music event 1 (0x19000) and 0xBCA50(3) before the
 * mode-4 calls. */
void m1_StopSpeed10D6B0(void *o, M1Spd3 *h)
{
    M1Comp5E4B *c;
    M1_SPEED_ZERO(h);
    if (h->resE0 != 0) {
        sub_00033A70(h->resE0);
        h->resE0 = 0;
    }
    c = sub_0001D960G(o, 5);
    if (c->sndE4 >= 0) {
        sub_00048250(c->sndE4);
        c->sndE4 = -1;
    }
    sub_00019000(m1_snd3E1270, 1);
    sub_000BCA50(3);
    sub_000F3B30(o, 4);
    sub_000F3B30(h->partC8, 4);
}

#ifndef M1_31_F3BB0
#define M1_31_F3BB0
void sub_000F3BB0(void *o, int a, int b);
void sub_000F3DA0(void *o, int a, int b, int c);
#endif

/* Shared body of 0x10D5D0 / 0x10D790: speed zero, free +0xE0, stop kind-5 sound,
 * 0xF3B00(4) on o and part, 0xF3BB0(0, 0), then 0xF3DA0(anim, b, 0). */
#define M1_SPEED_STOP_ANIM(name, anim, b)                  \
void name(void *o, M1Spd3 *h)                             \
{                                                         \
    M1Comp5E4B *c;                                        \
    M1_SPEED_ZERO(h);                                     \
    if (h->resE0 != 0) {                                  \
        sub_00033A70(h->resE0);                           \
        h->resE0 = 0;                                     \
    }                                                     \
    c = sub_0001D960G(o, 5);                              \
    if (c->sndE4 >= 0) {                                  \
        sub_00048250(c->sndE4);                           \
        c->sndE4 = -1;                                    \
    }                                                     \
    sub_000F3B00(o, 4);                                   \
    sub_000F3B00(h->partC8, 4);                           \
    sub_000F3BB0(o, 0, 0);                                \
    sub_000F3DA0(o, anim, b, 0);                          \
}

/* 0x0010D5D0: speed stop, animation 0x13 with -1. */
M1_SPEED_STOP_ANIM(m1_StopSpeed10D5D0, 0x13, -1)
/* 0x0010D790: speed stop, animation 0x14. */
M1_SPEED_STOP_ANIM(m1_StopSpeed10D790, 0x14, 0)

typedef struct M1Cmp30C4 { uint8_t unk00[0xE8]; float fE8; } M1Cmp30C4;
typedef struct M1Cmp30   { uint8_t unk00[0xC4]; M1Cmp30C4 *pC4; } M1Cmp30;
typedef struct M1Part30  { uint8_t unk00[0x20]; M1Cmp30 *p20; } M1Part30;

/* 0x0010EB90: speed stop with mode 4 on o and part, then the part's
 * +0x20 -> +0xC4 component gets +0xE8 = 128.0. */
void m1_StopSpeed10EB90(void *o, M1Spd3 *h)
{
    M1Comp5E4B *c;
    M1_SPEED_ZERO(h);
    if (h->resE0 != 0) {
        sub_00033A70(h->resE0);
        h->resE0 = 0;
    }
    c = sub_0001D960G(o, 5);
    if (c->sndE4 >= 0) {
        sub_00048250(c->sndE4);
        c->sndE4 = -1;
    }
    sub_000F3B30(o, 4);
    sub_000F3B30(h->partC8, 4);
    ((M1Part30 *)h->partC8)->p20->pC4->fE8 = 128.0f;
}

typedef struct M1ObjD4 { uint8_t unk00[0xD4]; void (*cbD4)(void); uint8_t unkD8[0xE8 - 0xD8]; float fE8; } M1ObjD4;
void sub_00102FA0(void);

/* 0x0010E510: speed stop that sets o +0xE8 = h +0xDC * 27.9 and the o +0xD4
 * callback to 0x102FA0 before mode 4 on o and part. */
void m1_StopSpeed10E510(M1ObjD4 *o, M1Spd3 *h)
{
    M1Comp5E4B *c;
    M1_SPEED_ZERO(h);
    if (h->resE0 != 0) {
        sub_00033A70(h->resE0);
        h->resE0 = 0;
    }
    c = sub_0001D960G(o, 5);
    if (c->sndE4 >= 0) {
        sub_00048250(c->sndE4);
        c->sndE4 = -1;
    }
    o->fE8 = h->fDC * 27.9f;
    o->cbD4 = sub_00102FA0;
    sub_000F3B30(o, 4);
    sub_000F3B30(h->partC8, 4);
}

typedef struct M1Spd4 {
    uint8_t unk000[0xC8];
    M1EfC50 *partC8;           /* +0xC8 */
    uint8_t unk0CC[0xD4 - 0xCC];
    int32_t fD4;               /* +0xD4 */
    uint8_t unk0D8[0xE0 - 0xD8];
    void   *resE0;             /* +0xE0 */
    uint8_t unk0E4[0x15C - 0xE4];
    float   v15C[4];           /* +0x15C */
} M1Spd4;
void sub_000192B0(void *s, void *o);
void sub_0001AB00(void *s, int a, int b, int c, int d);

/* 0x0010DDF0: speed stop with music: 0x192B0(o), then event 1 + 0xBCA50(3) when
 * h +0xD4 is set, else event 2 + 0x1AB00(2, 3); mode 4 and flag 0x20 on o and part. */
void m1_StopSpeed10DDF0(M1EfC50 *o, M1Spd4 *h)
{
    M1Comp5E4B *c;
    M1_SPEED_ZERO(h);
    if (h->resE0 != 0) {
        sub_00033A70(h->resE0);
        h->resE0 = 0;
    }
    c = sub_0001D960G(o, 5);
    if (c->sndE4 >= 0) {
        sub_00048250(c->sndE4);
        c->sndE4 = -1;
    }
    sub_000192B0(m1_snd3E1270, o);
    if (h->fD4 != 0) {
        sub_00019000(m1_snd3E1270, 1);
        sub_000BCA50(3);
    } else {
        sub_00019000(m1_snd3E1270, 2);
        sub_0001AB00(m1_snd3E1270, 2, 3, 0, 0);
    }
    sub_000F3B30(o, 4);
    sub_000F3B30(h->partC8, 4);
    o->flags0C |= 0x20;
    h->partC8->flags0C |= 0x20;
}

typedef struct M1EfP60 { uint8_t unk00[0x60]; float pos60[3]; } M1EfP60;
void *sub_001890F0(int idx, const void *a, const void *b, float range);
void r3d_Hold188C00(void *hold, const float *pos);
extern void *m1_hold3F615C;
extern void *m1_hold3F6158;
extern const uint8_t m1_tbl319EA8[], m1_tbl319F48[], m1_tbl319E68[], m1_tbl319F38[];

/* 0x0010E600: as 0x10E1B0 but also frees +0xE0 and stops the kind-5 sound,
 * plays animation 0x30, then creates the two hold records (range 118) at o's position. */
void m1_StopSpeed10E600(M1EfP60 *o, M1Spd3 *h)
{
    M1Comp5E4B *c;
    M1_SPEED_ZERO(h);
    sub_000F3C40(o);
    sub_000F3BB0(o, 0, 0);
    h->f16C = 0.0f;
    h->f170 = 0;
    if (h->resE0 != 0) {
        sub_00033A70(h->resE0);
        h->resE0 = 0;
    }
    c = sub_0001D960G(o, 5);
    if (c->sndE4 >= 0) {
        sub_00048250(c->sndE4);
        c->sndE4 = -1;
    }
    sub_000F3B00(o, 4);
    sub_000F3B00(h->partC8, 4);
    sub_000F3BB0(o, 0, 0);
    sub_000F3DA0(o, 0x30, 0, 0);
    m1_hold3F615C = sub_001890F0(0, m1_tbl319EA8, m1_tbl319F48, 118.0f);
    m1_hold3F6158 = sub_001890F0(1, m1_tbl319E68, m1_tbl319F38, 118.0f);
    r3d_Hold188C00(m1_hold3F615C, o->pos60);
    r3d_Hold188C00(m1_hold3F6158, o->pos60);
}

/* 0x0010ED00: speed vector = frame rate * 0.0 only. */
void m1_ZeroSpeed10ED00(void *o, M1Spd3 *h)
{
    M1_SPEED_ZERO(h);
}

/* 0x0010DF20: speed vector = frame rate * 0.0, then animation 0 via 0xF3DA0. */
void m1_ZeroSpeed10DF20(void *o, M1Spd3 *h)
{
    M1_SPEED_ZERO(h);
    sub_000F3DA0(o, 0, 0, 0);
}

/* 0x0010EF70: launch vector: x = frame rate * 9.8, y = z = frame rate * 0.0,
 * w = frame rate * -40.0. */
void m1_Launch10EF70(void *o, M1Spd3 *h)
{
    h->v15C[1] = m1_frameRate42C85C * 0.0f;
    h->v15C[2] = m1_frameRate42C85C * 0.0f;
    h->v15C[0] = m1_frameRate42C85C * 9.8f;
    h->v15C[3] = m1_frameRate42C85C * -40.0f;
}

typedef struct M1Spd6 {
    uint8_t unk000[0x15C];
    float   v15C[4];           /* +0x15C */
    uint8_t unk16C[0x188 - 0x16C];
    int32_t f188;              /* +0x188 */
    float   f18C, f190;        /* +0x18C */
} M1Spd6;

/* 0x0010E3D0: speed zero, +0x18C = 0.2, +0x188 = 0, +0x190 = 0.4, animation 0x27. */
void m1_ZeroSpeed10E3D0(void *o, M1Spd6 *h)
{
    M1_SPEED_ZERO(h);
    h->f18C = 0.2f;
    h->f188 = 0;
    h->f190 = 0.4f;
    sub_000F3DA0(o, 0x27, 0, 0);
}
