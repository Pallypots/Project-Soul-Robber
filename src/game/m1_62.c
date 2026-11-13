/* Area m1, file 62: minion controller step. Names inferred. */
#include <stdint.h>

typedef struct M1MinionCtl {
    uint8_t unk000[0x94];
    int32_t f94;               /* +0x94 */
    uint8_t unk098[4];
    int32_t step9C;            /* +0x9C */
    float   tA0;               /* +0xA0 */
    uint8_t unkA4[2];
    int16_t wA6;               /* +0xA6 */
    uint8_t unkA8[0xBC - 0xA8];
    int16_t doneBC;            /* +0xBC */
} M1MinionCtl;
extern M1MinionCtl *m1_minion3F6120;
extern float m1_frameRate42C85C;
int  sub_000F5D00(void *o);
void sub_0001D700(int v);

/* 0x000FFEA0: minion step: at step 0 waits for 0xF5D00(o), then 0x1D700(+0x94), clears
 * +0xA6 and the timer and moves on; later sets +0xBC once the timer passes 0.2, else
 * counts it up by the frame rate. */
void m1_MinionStep0FFEA0(void *o)
{
    M1MinionCtl *g = m1_minion3F6120;
    if (g->step9C == 0) {
        if (sub_000F5D00(o) != 0) {
            sub_0001D700(g->f94);
            g->wA6 = 0;
            g->tA0 = 0.0f;
            g->step9C++;
        }
        return;
    }
    if (g->tA0 > 0.2f)
        g->doneBC = 1;
    else
        g->tA0 += m1_frameRate42C85C;
}

typedef struct M1Spin54 {
    uint8_t unk00[0x10];
    float   rate10;            /* +0x10 */
    uint8_t unk14[0x34 - 0x14];
    float   q34[4];            /* +0x34 */
    uint8_t unk44[0x54 - 0x44];
    float   axis54;            /* +0x54 */
    float   ang58;             /* +0x58 */
} M1Spin54;
extern float m1_frameTime42C858;
void sub_001ADBA0(float *out, const float *axis, float t);
void sub_001ADAF0(float *out, const float *a, const float *b);
int  abs(int);
#pragma intrinsic(abs)

/* 0x000C6E10: spins the +0x34 rotation by the axis at +0x54 for one frame (0x1ADBA0,
 * 0x1ADAF0); +0x58 += rate * frame time, clamped to 2.5 once its whole part reaches it. */
void m1_Spin0C6E10(M1Spin54 *o)
{
    float q[4];
    float t;
    q[0] = 0.0f;
    q[1] = 0.0f;
    q[2] = 0.0f;
    q[3] = 1.0f;
    sub_001ADBA0(q, &o->axis54, m1_frameTime42C858);
    sub_001ADAF0(o->q34, o->q34, q);
    t = o->rate10 * m1_frameTime42C858 + o->ang58;
    o->ang58 = t;
    if ((float)abs((int)t) >= 2.5f)
        o->ang58 = 2.5f;
}

typedef struct M1Sprite {
    uint32_t flags00;          /* +0x00 */
    uint8_t  data04[0x20 - 4]; /* +0x04 */
    float    w20, h24;         /* +0x20 */
    uint8_t  b28;              /* +0x28 */
    uint8_t  unk29[0xA0 - 0x29];
} M1Sprite;
extern M1Sprite m1_sprites3F4D10[16];
void *sub_00017AE0(void *ctx, void *data);
int   sub_0019BE60(int flag);
void  sub_00014E80(void *data);

/* 0x000E7990: draws the 16 sprites at 0x3F4D10 that are on (0x17AE0 chains the context);
 * unless paused (0x19BE60(0x8000)) each is advanced (0x14E80) and scaled by
 * 1 + frame time * 0.05; one-shot sprites (+0x28 bit 0) turn off. Returns the context. */
void *m1_SpritesDraw0E7990(void *ctx)
{
    M1Sprite *s;
    float k;
    int i;
    for (i = 0; i < 16; i++) {
        s = &m1_sprites3F4D10[i];
        if (!(s->flags00 & 1))
            continue;
        ctx = sub_00017AE0(ctx, s->data04);
        if (sub_0019BE60(0x8000) == 0) {
            sub_00014E80(s->data04);
            k = m1_frameTime42C858 * 0.05f + 1.0f;
            s->w20 *= k;
            s->h24 *= k;
        }
        if (s->b28 & 1)
            s->flags00 &= ~1u;
    }
    return ctx;
}
