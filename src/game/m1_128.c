/* Area m1, file 128: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Pl128 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl128;
typedef struct M1Obj128 {
    uint32_t flags00;          /* +0x00 */
    uint8_t unk004[0x40 - 4];
    int32_t state40;           /* +0x40 */
    uint8_t unk044[0x90 - 0x44];
    float   dir90[4];          /* +0x90 */
    uint8_t unk0A0[0x120 - 0xA0];
    M1Pl128 *src120;           /* +0x120 */
    uint8_t unk124[0x14C - 0x124];
    int32_t fx14C;             /* +0x14C */
} M1Obj128;
extern M1Pl128 *g_playerObj;
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
void sub_000F5D40(float *d, const float *s);
void sub_00033A40(int fx);
void sub_000A41D0(void *o, int a);

/* Two-step fling: step 0 sets the flat unit direction (player minus source, or the reverse),
 * step 1 clears it, flags 0x80, drops the effect and finishes (0xA41D0, -1). */
#define M1_FLING128(name, A, B)                                     \
void name(M1Obj128 *o)                                              \
{                                                                   \
    M1Pl128 *c = o->src120;                                         \
    float v[4];                                                     \
    v[0] = 0.0f;                                                    \
    v[1] = 0.0f;                                                    \
    v[2] = 0.0f;                                                    \
    v[3] = 1.0f;                                                    \
    switch (o->state40) {                                           \
    case 0:                                                         \
        sub_001AD9F0(v, A, B);                                      \
        sub_001AD7E0(v, v);                                         \
        v[1] = 0.0f;                                                \
        sub_000F5D40(o->dir90, v);                                  \
        o->state40++;                                               \
        return;                                                     \
    case 1:                                                         \
        sub_000F5D40(o->dir90, v);                                  \
        o->flags00 |= 0x80;                                         \
        sub_00033A40(o->fx14C);                                     \
        sub_000A41D0(o, -1);                                        \
        return;                                                     \
    }                                                               \
}

/* 0x00091550: fling away from the source toward the player side. */
M1_FLING128(m1_FlingTo091550, g_playerObj->pos60, c->pos60)
/* 0x00091490: fling the other way. */
M1_FLING128(m1_FlingFrom091490, c->pos60, g_playerObj->pos60)

typedef struct M1Trk128 {
    uint8_t unk00[4];
    void   *fn04;              /* +0x04 */
    uint8_t unk08[0x10 - 8];
    int32_t a10;               /* +0x10 */
    float   f14;               /* +0x14 */
    int32_t a18;               /* +0x18 */
    uint8_t unk1C[4];
    float   v20[4], v30[4];    /* +0x20 */
    int32_t a40;               /* +0x40 */
    float   f44;               /* +0x44 */
    int32_t a48, a4C;          /* +0x48 */
    float   v50[4], v60[4], v70[4]; /* +0x50 */
} M1Trk128;
void *sub_00053AB0(int size, int a, int tag);
void sub_001B2150(void *t);
void sub_0007F710(void);

/* 0x0007FC60: allocate and initialise an animation track (0x80 bytes, tag 0x14F): update
 * callback 0x7F710, identity vectors, counters cleared. */
M1Trk128 *m1_TrackNew07FC60(void)
{
    M1Trk128 *t = (M1Trk128 *)sub_00053AB0(0x80, 0, 0x14F);
    sub_001B2150(t);
    t->fn04 = sub_0007F710;
    t->a10 = 0;
    t->f14 = 0.0f;
    t->a18 = 1;
    t->v20[0] = 0.0f;
    t->v20[1] = 0.0f;
    t->v20[2] = 0.0f;
    t->v20[3] = 1.0f;
    t->v30[0] = 0.0f;
    t->v30[1] = 0.0f;
    t->v30[2] = 0.0f;
    t->v30[3] = 1.0f;
    t->a48 = 1;
    t->a40 = 0;
    t->f44 = 0.0f;
    t->a4C = 0;
    t->v50[0] = 0.0f;
    t->v50[1] = 0.0f;
    t->v50[2] = 0.0f;
    t->v50[3] = 1.0f;
    t->v60[0] = 0.0f;
    t->v60[1] = 0.0f;
    t->v60[2] = 0.0f;
    t->v60[3] = 1.0f;
    t->v70[0] = 0.0f;
    t->v70[1] = 0.0f;
    t->v70[2] = 0.0f;
    t->v70[3] = 1.0f;
    return t;
}

extern int32_t m1_ms3F47B8, m1_ms3F47BC, m1_ms3F47C0, m1_ms3F47C4, m1_ms3F47C8;
extern float m1_ms3F47CC;

/* 0x000E8920: menu slide request: mode 1 opens it (from states 0 and 2: state 1, step 3,
 * target 2), mode 0 closes it (from state 1 mirroring the slide position 20 - x, or from
 * state 3). */
void m1_MenuSlide0E8920(int mode)
{
    switch (mode) {
    case 0:
        switch (m1_ms3F47B8) {
        case 1:
            m1_ms3F47B8 = 2;
            m1_ms3F47BC = 0;
            m1_ms3F47CC = 20.0f - m1_ms3F47CC;
            return;
        case 3:
            m1_ms3F47B8 = 2;
            m1_ms3F47BC = 0;
            m1_ms3F47C8 = 0;
            return;
        }
        return;
    case 1:
        switch (m1_ms3F47B8) {
        case 0:
        case 2:
            m1_ms3F47B8 = 1;
            m1_ms3F47BC = 3;
            m1_ms3F47C0 = 2;
            m1_ms3F47C4 = 0;
            m1_ms3F47C8 = 0;
            return;
        }
        return;
    }
}
