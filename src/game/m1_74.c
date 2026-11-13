/* Area m1, file 74: rig fall step, part reset. Names inferred. */
#include <stdint.h>

extern float m1_frameRate42C85C;

typedef struct M1FallR {
    uint8_t unk00[0x18];
    uint32_t flags18;          /* +0x18 */
    float   t1C;               /* +0x1C */
    uint8_t unk20[4];
    float   vel24;             /* +0x24 */
    uint8_t unk28[0x30 - 0x28];
    float   pos30[4];          /* +0x30 */
} M1FallR;
typedef struct M1FallO {
    uint8_t unk000[0x20];
    void   *node20;            /* +0x20 */
    uint8_t unk024[0x128 - 0x24];
    uint8_t b128;              /* +0x128 */
} M1FallO;
typedef struct M1FallH {
    uint8_t unk000[0xF8];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    union { uint8_t *ptr; float v[4]; } src104;   /* +0x104 */
    uint8_t unk114[0x278 - 0x114];
    M1FallR *rig278;           /* +0x278 */
} M1FallH;
void sub_00145F70(void *node, const float *src);
void sub_000F5D40(float *d, const float *s);

/* 0x00185900: rig fall step: upright the node, copy the target position (mode 1: through the
 * +0x104 pointer at +0x60, mode 2: the inline vector), then apply gravity (fr*fr*294,
 * accumulated unless flag 0x18 is set) and count down the +0x1C timer to zero. */
void m1_RigFall185900(M1FallO *o, M1FallH *h)
{
    M1FallR *r = h->rig278;
    uint32_t f;
    sub_00145F70(o->node20, o->node20);
    if (h->mode0F8 == 1)
        sub_000F5D40(r->pos30, (const float *)(h->src104.ptr + 0x60));
    else if (h->mode0F8 == 2)
        sub_000F5D40(r->pos30, h->src104.v);
    f = r->flags18;
    if (!(f & 0x10)) {
        if (f & 0x20) {
            r->flags18 = f & ~0x20u;
        } else {
            float d = m1_frameRate42C85C * m1_frameRate42C85C * 294.0f;
            if (!(o->b128 & 0x18))
                d += r->vel24;
            r->vel24 = d;
        }
    }
    if (r->flags18 & 0x100) {
        r->t1C -= m1_frameRate42C85C;
        if (0.0f > r->t1C)
            r->t1C = 0.0f;
    }
}

typedef struct M1PartE { uint32_t flags; uint8_t pad[0x150 - 4]; } M1PartE;
typedef struct M1PartO {
    uint8_t unk00[8];
    int32_t kind08;            /* +0x08 */
    M1PartE parts0C[1];        /* +0x0C, stride 0x150 */
} M1PartO;
typedef struct M1PartC { uint8_t unk00[0xA0]; int32_t mode0A0; } M1PartC;
typedef struct M1PartD { uint8_t unk00[0x4C]; int32_t v4C; } M1PartD;
extern uint8_t m1_snd3E1270[];
void *sub_0001D960(void *o, int kind);
int  sub_000F3140(int kind);
void sub_0001EB80(void *p);
void sub_000EE270(void *p);
void sub_000F3AA0(void *p);
void sub_0001D910(void *o, void *c);
void sub_000192B0(void *s, int a);

/* 0x0010A230: reset: clears bit 0 of every part (0x1EB80 on each that had it), resets
 * components 13 and 5, re-registers them, and plays the reset sound in mode 1. */
int m1_PartsReset10A230(M1PartO *o)
{
    M1PartC *c = (M1PartC *)sub_0001D960(o, 5);
    void *a;
    M1PartD *b;
    int i;
    char *p;
    if (o == 0)
        for (;;) ;
    for (i = 0, p = (char *)o->parts0C; i < sub_000F3140(o->kind08); i++, p += 0x150) {
        uint32_t f = *(uint32_t *)p;
        if (f & 1) {
            *(uint32_t *)p = f & ~1u;
            sub_0001EB80(p - 0xC);
        }
    }
    a = sub_0001D960(o, 0xD);
    b = (M1PartD *)sub_0001D960(o, 5);
    sub_000EE270(a);
    sub_000F3AA0(b);
    b->v4C = 0;
    sub_0001D910(o, b);
    sub_0001D910(o, a);
    if (c->mode0A0 == 1)
        sub_000192B0(m1_snd3E1270, 0);
    return 1;
}

typedef struct M1TurnD {
    uint8_t unk00[0x10];
    float   max10;             /* +0x10 */
    float   lo14;              /* +0x14 */
    float   hi18;              /* +0x18 */
    uint16_t stA1C;            /* +0x1C */
    uint16_t stB1E;            /* +0x1E */
} M1TurnD;
typedef struct M1TurnO { uint8_t unk00[0x54]; float yaw54; } M1TurnO;
typedef struct M1TurnH {
    uint8_t unk000[0x64];
    int32_t state64;           /* +0x64 */
    uint8_t unk068[0xFC - 0x68];
    float   left0FC;           /* +0xFC */
} M1TurnH;
float sub_001A3F30(float x);
void sub_00113090(void *o, void *h, int state);

/* 0x0013FF80: turn toward a target angle: in state B switch to state A once |left| (0x1A3F30)
 * drops to hi18, otherwise switch to B once it reaches lo14; while in B turn by the remaining
 * angle clamped to +-max10. */
void m1_TurnStep13FF80(M1TurnO *o, M1TurnH *h, M1TurnD *d)
{
    int b = d->stB1E;
    int a = d->stA1C;
    float x = h->left0FC;
    float t = sub_001A3F30(x);
    if (h->state64 == b) {
        if (d->hi18 >= t)
            sub_00113090(o, h, a);
    } else {
        if (t >= d->lo14)
            sub_00113090(o, h, b);
    }
    if (h->state64 == b) {
        float v = x;
        if (v > d->max10)
            v = d->max10;
        if (0.0f - d->max10 > v)
            v = 0.0f - d->max10;
        o->yaw54 += v;
        h->left0FC -= v;
    }
}

typedef struct M1SwayR { uint32_t unk00; uint32_t flags04; uint8_t unk08[0x2C - 8]; float q2C[4]; } M1SwayR;
typedef struct M1SwayH {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1SwayR *rig278;           /* +0x278 */
} M1SwayH;
typedef struct M1SwayC { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1SwayC;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_0001D4E0(void *o);
M1SwayC *sub_00113400(void *h, int v);

/* Sway setup: enter state, reset the rig quaternion, h +0x4C |= 0x70, rig +4 |= 4, command 1
 * = (a, b, frameTime*rate unless -1, 0). */
#define M1_SWAY(name, st, rate, a, b)                       \
void name(void *o, M1SwayH *h)                              \
{                                                           \
    M1SwayR *r = h->rig278;                                 \
    M1SwayR *p;                                             \
    M1SwayC *c;                                             \
    float t;                                                \
    if (sub_001456E0(o, h, st, 0) == 1)                     \
        sub_0001D4E0(o);                                    \
    p = h->rig278;                                          \
    p->q2C[2] = 0.0f;                                       \
    p->q2C[1] = 0.0f;                                       \
    p->q2C[0] = 0.0f;                                       \
    p->q2C[3] = 1.0f;                                       \
    h->flags4C |= 0x70;                                     \
    r->flags04 |= 4;                                        \
    t = m1_frameTime42C858 * (rate);                        \
    c = sub_00113400(h, 1);                                 \
    c->f10 = (a);                                           \
    c->f14 = (b);                                           \
    if (t != -1.0f)                                         \
        c->f18 = t;                                         \
    c->f1C = 0.0f;                                          \
}

/* 0x00115970: sway, state 0x16, +-10 degrees, rate 10. */
M1_SWAY(m1_Sway115970, 0x16, 10.0f, 0.17453294f, -0.17453294f)
/* 0x00115DB0: sway, state 0x21, +-5 degrees, rate 5 degrees. */
M1_SWAY(m1_Sway115DB0, 0x21, 0.087266468f, 0.087266468f, -0.087266468f)
