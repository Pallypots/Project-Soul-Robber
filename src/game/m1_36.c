/* Area m1, file 36: actor setup with callbacks. Names inferred. */
#include <stdint.h>

typedef struct M1Obj124 {
    uint8_t  unk000[0xC];
    uint32_t flags0C;          /* +0x00C */
    uint32_t flags10;          /* +0x010 */
    uint8_t  unk014[0x30 - 0x14];
    void    *anim030;          /* +0x030 */
    uint8_t  unk034[0x60 - 0x34];
    float    pos060[4];        /* +0x060 */
    uint8_t  unk070[0x124 - 0x70];
    int32_t  f124;             /* +0x124 */
} M1Obj124;
typedef void (*M1Cb)(void);
typedef struct M1ActCb {
    uint8_t  unk000[0x27C];
    M1Cb     update27C;        /* +0x27C */
    uint8_t  unk280[0x288 - 0x280];
    M1Cb     draw288;          /* +0x288 */
    void    *paramA28C;        /* +0x28C */
    void    *paramB290;        /* +0x290 */
} M1ActCb;
extern uint8_t  m1_paramA32B780[4], m1_paramB32B784[4];  /* 0x0032B780 / 0x0032B784 */
extern const float m1_startPos27A628[4];                 /* 0x0027A628 */
void sub_0017D8E0(void);
void m1_Stub102FA0(void);
void sub_0001EBF0(M1Obj124 *o, int v);
void sub_000F5D40(void *dst, const void *src);
void sub_00113040(void *owner, void *obj, int what);
void sub_000832D0(void *anim, int id);

/* 0x0017E410: sets up o (flags, mode 2) and actor a (callbacks and parameters),
 * places o at the start position and starts animation 0. Returns 1. */
int m1_SetupActor17E410(M1Obj124 *o, M1ActCb *a)
{
    if (o == 0)
        for (;;) ;
    if (a == 0)
        for (;;) ;
    o->flags0C = (o->flags0C & ~0xE0u) | 3;
    o->flags10 |= 0x44D;
    o->f124 = 0;
    sub_0001EBF0(o, 2);
    a->paramA28C = m1_paramA32B780;
    a->paramB290 = m1_paramB32B784;
    a->update27C = sub_0017D8E0;
    a->draw288 = m1_Stub102FA0;
    sub_000F5D40(o->pos060, m1_startPos27A628);
    sub_00113040(o, a, 0);
    sub_000832D0(o->anim030, 0);
    return 1;
}

typedef struct M1Ctl10 {
    uint8_t  unk00[0x10];
    uint32_t flags10;          /* +0x10 */
} M1Ctl10;
typedef struct M1Pl0EC {
    uint8_t  unk000[0x8C];
    M1Ctl10 *ctl08C;           /* +0x08C */
    uint8_t  unk090[0xA4 - 0x90];
    int16_t  wA4, wA6, wA8, wAA, wAC, wAE, wB0, wB2;   /* +0x0A4..+0x0B2 */
    uint8_t  unk0B4[0xBC - 0xB4];
    int16_t  wBC;              /* +0x0BC */
    uint8_t  unk0BE[0xEC - 0xBE];
    int16_t  wEC;              /* +0x0EC */
} M1Pl0EC;
typedef struct M1Mode8 {
    uint8_t unk00[8];
    int32_t mode08;            /* +0x08 */
} M1Mode8;
M1Pl0EC *sub_00100110(void);
M1Pl0EC *sub_000FBAF0(void);
M1Pl0EC *sub_000FE3D0(void);

/* 0x000F6D80: picks the controlled body for mode 4 (0x100110), 5 (0xFBAF0) or
 * otherwise (0xFE3D0); re-enables its controller (flags -0x44 +0x220) and clears its
 * input words, leaving +0xAA = 1. */
void m1_ResetInputF6D80(M1Mode8 *m)
{
    M1Pl0EC *p;
    if (m != 0 && m->mode08 != 3 && m->mode08 == 4)   /* the original tests mode 3 first */
        p = sub_00100110();
    else if (m != 0 && m->mode08 == 5)
        p = sub_000FBAF0();
    else
        p = sub_000FE3D0();
    if (p != 0) {
        p->wA4 = 0;
        p->ctl08C->flags10 &= ~0x44u;
        p->ctl08C->flags10 |= 0x220;
    }
    p->wA6 = 0;
    p->wA8 = 0;
    p->wAC = 0;
    p->wAE = 0;
    p->wB0 = 0;
    p->wB2 = 0;
    p->wBC = 0;
    p->wEC = 0;
    p->wAA = 1;
}

typedef struct M1EWork {
    uint8_t  unk00[4];
    uint32_t flags04;          /* +0x04 */
    uint8_t  unk08[0x14 - 8];
    float    v14[4];           /* +0x14 */
} M1EWork;
typedef struct M1Enemy278 {
    uint8_t  unk000[0x20];
    uint8_t  b020;             /* +0x020 */
    uint8_t  unk021;
    uint8_t  b022;             /* +0x022 */
    uint8_t  unk023[0x58 - 0x23];
    int32_t  state058;         /* +0x058 */
    uint8_t  unk05C[0x278 - 0x5C];
    M1EWork *work278;          /* +0x278 */
} M1Enemy278;
void sub_00113090(void *o, void *e, int anim);
void sub_000414A0(int n);
void sub_00113C60(float *v, float a, float b);
void sub_00113CB0(float *v, float a, int b);

/* 0x00142AF0: enemy hit: animation 0x12 (+1 when bit 0 of +0x22 is set), score 1;
 * flag 0x20000000 flashes (40, 255); otherwise fades (20) and moves to state 2 when
 * flagged 0x40000000, or to state 4 (owner flags |= 6) when bit 0 of +0x20 is set. */
void m1_EnemyHit142AF0(M1Obj124 *o, M1Enemy278 *e)
{
    M1EWork *w = e->work278;
    sub_00113090(o, e, (e->b022 & 1) + 0x12);
    sub_000414A0(1);
    if (w->flags04 & 0x20000000) {
        sub_00113C60(w->v14, 40.0f, 255.0f);
        return;
    }
    sub_00113CB0(w->v14, 20.0f, 0);
    if (w->flags04 & 0x40000000) {
        e->state058 = 2;
        return;
    }
    if (e->b020 & 1) {
        o->flags10 |= 6;
        e->state058 = 4;
    }
}

typedef struct M1Enemy4C {
    uint8_t  unk000[0x20];
    uint8_t  b020;             /* +0x020 */
    uint8_t  unk021;
    uint8_t  b022;             /* +0x022 */
    uint8_t  unk023[0x4C - 0x23];
    uint32_t flags04C;         /* +0x04C */
    uint8_t  unk050[0x58 - 0x50];
    int32_t  state058;         /* +0x058 */
    uint8_t  unk05C[0x278 - 0x5C];
    M1EWork *work278;          /* +0x278 */
} M1Enemy4C;
int aab_Rand(void);

/* 0x00138140: enemy recoil: clears flags, then animation 0x1D/0x1E (work flag
 * 0x800000), or at random 8, or state 1 with animation 0x10/0x11. */
void m1_EnemyRecoil138140(M1Obj124 *o, M1Enemy4C *e)
{
    o->flags0C &= ~0x20u;
    o->flags10 = (o->flags10 & ~0x20u) | 5;
    e->flags04C &= 0xFEFFFF87;
    if (e->work278->flags04 & 0x800000) {
        sub_00113090(o, e, (e->b020 & 1) ? 0x1E : 0x1D);
        return;
    }
    if (aab_Rand() % 2 < 1) {
        sub_00113090(o, e, 8);
        return;
    }
    e->state058 = 1;
    sub_00113090(o, e, (e->b022 & 1) + 0x10);
}
