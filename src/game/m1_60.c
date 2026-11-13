/* Area m1, file 60: helper timers and trail buffers. Names inferred. */
#include <stdint.h>

typedef struct M1HCam { uint8_t unk00[0x10]; uint32_t flags10; } M1HCam;
typedef struct M1HelperT {
    uint8_t unk000[0x8C];
    M1HCam *cam8C;             /* +0x8C */
    void   *fx90;              /* +0x90 */
    uint8_t unk094[0xD4 - 0x94];
    float   tD4, tD8;          /* +0xD4 */
} M1HelperT;
extern M1HelperT *m1_helper3F611C;
extern float m1_frameRate42C85C;
void sub_00033A40(void *r);

/* 0x000FC660: helper timers: while +0xD8 runs the camera gets flag 4 and the timer counts
 * down; when it has run out the flag is cleared and the +0x90 effect freed; +0xD4 counts
 * down while above 0. */
void m1_HelperTimers0FC660(void)
{
    M1HelperT *h = m1_helper3F611C;
    M1HCam *c = h->cam8C;
    if (h->tD8 <= 0.0f) {
        c->flags10 &= ~4u;
        if (h->fx90 != 0) {
            sub_00033A40(h->fx90);
            h->fx90 = 0;
        }
    } else {
        c->flags10 |= 4;
        h->tD8 -= m1_frameRate42C85C;
    }
    if (h->tD4 > 0.0f)
        h->tD4 -= m1_frameRate42C85C;
}

typedef struct M1Trail {
    uint8_t unk000[0x6A8];
    int32_t n6A8;              /* +0x6A8 */
    uint8_t unk6AC[4];
    float   a6AC[32][4];       /* +0x6AC */
    float   b8AC[32][4];       /* +0x8AC */
    float   cAAC[32][4];       /* +0xAAC */
    int32_t dCAC[32];          /* +0xCAC */
} M1Trail;

/* 0x000C4420: clears the trail: count +0x6A8 and the 32 entries of the three vector
 * arrays (+0x6AC, +0x8AC, +0xAAC) and the int array +0xCAC. */
void m1_TrailClear0C4420(M1Trail *t)
{
    int i;
    t->n6A8 = 0;
    for (i = 0; i < 32; i++) {
        t->a6AC[i][3] = 0.0f;
        t->a6AC[i][2] = 0.0f;
        t->a6AC[i][1] = 0.0f;
        t->a6AC[i][0] = 0.0f;
        t->b8AC[i][3] = 0.0f;
        t->b8AC[i][2] = 0.0f;
        t->b8AC[i][1] = 0.0f;
        t->b8AC[i][0] = 0.0f;
        t->cAAC[i][3] = 0.0f;
        t->cAAC[i][2] = 0.0f;
        t->cAAC[i][1] = 0.0f;
        t->cAAC[i][0] = 0.0f;
        t->dCAC[i] = 0;
    }
}

typedef struct M1Fx90b { uint8_t unk00[0x90]; uint32_t flags90; } M1Fx90b;
typedef struct M1HAnim2 { uint8_t unk00[0x30]; void *anim30; } M1HAnim2;
typedef struct M1Boss {
    uint8_t unk000[0x8C];
    M1HAnim2 *cam8C;           /* +0x8C */
    uint8_t unk090[0xA8 - 0x90];
    int16_t wA8;               /* +0xA8 */
    uint8_t unkAA[0xB2 - 0xAA];
    int16_t wB2;               /* +0xB2 */
    uint8_t unkB4[0xBC - 0xB4];
    M1Fx90b *fxBC;             /* +0xBC */
    uint8_t unkC0[0x100 - 0xC0];
    int32_t f100;              /* +0x100 */
    uint8_t unk104[0x118 - 0x104];
    float   f118;              /* +0x118 */
} M1Boss;
typedef struct M1Fl10c { uint8_t unk00[0x10]; uint32_t flags10; } M1Fl10c;
extern M1Boss *m1_cam3F610C;
void sub_000832D0(void *a, int v);
void sub_00192380(int which, int clip);

/* 0x000F5380: with no hit count (+0xA8) sets effect flag 0x40 and clears +0x118; else
 * plays clip 0x1C on the camera (spins when null) and on both arms (0x192380); then
 * +0xB2 = +0xA8, o flag 0x40 and +0x100 = 4. */
void m1_BossPose0F5380(M1Fl10c *o)
{
    M1Boss *b = m1_cam3F610C;
    M1HAnim2 *c;
    if (b->wA8 == 0) {
        b->fxBC->flags90 |= 0x40;
        b->f118 = 0.0f;
    } else {
        c = b->cam8C;
        if (c == 0)
            for (;;) ;
        sub_000832D0(c->anim30, 0x1C);
        sub_00192380(0, 0x1C);
        sub_00192380(1, 0x1C);
    }
    b->wB2 = b->wA8;
    o->flags10 |= 0x40;
    b->f100 = 4;
}

typedef struct M1Tgt { uint8_t unk00[0xC]; uint8_t b0C; uint8_t unk0D[0x60 - 0xD]; float pos60[4]; } M1Tgt;
typedef struct M1Slot68 { uint32_t flags00; uint8_t unk04[0x64 - 4]; M1Tgt *tgt64; } M1Slot68;
typedef struct M1Seeker { uint8_t unk00[0x60]; float pos60[4]; } M1Seeker;
extern M1Slot68 m1_ents41CEC0[3];
float sub_001B2770(const float *a, const float *b);

/* 0x000C7130: nearest live target among the 3 slots at 0x41CEC0 (slot flags 1 and
 * 0x10000000 set, 0x20000000 clear, target flag 1); returns it or 0. */
M1Tgt *m1_Nearest0C7130(M1Seeker *o)
{
    float best = 3.4028235e38f;
    float d;
    M1Tgt *r = 0;
    M1Tgt *t;
    int i;
    for (i = 0; i < 3; i++) {
        M1Slot68 *s = &m1_ents41CEC0[i];
        if (!(s->flags00 & 1))
            continue;
        if (!(s->flags00 & 0x10000000))
            continue;
        if (s->flags00 & 0x20000000)
            continue;
        t = s->tgt64;
        if (t == 0 || !(t->b0C & 1))
            continue;
        d = sub_001B2770(o->pos60, t->pos60);
        if (best > d) {
            best = d;
            r = t;
        }
    }
    return r;
}
