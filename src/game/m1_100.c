/* Area m1, file 100: rig setups. Names inferred. */
#include <stdint.h>

typedef struct M1Rig100 { uint8_t unk000[0x50]; uint32_t flags50; uint8_t unk054[0x5C - 0x54]; float f5C; uint8_t unk060[0x68 - 0x60]; float f68; uint8_t unk06C[0x1C0 - 0x6C]; int32_t kind1C0; } M1Rig100;
typedef struct M1Step100 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x58 - 0x50]; int32_t phase58; uint8_t unk05C[0x278 - 0x5C]; M1Rig100 *rig278; } M1Step100;
typedef struct M1Obj100 { uint8_t unk00[0x10]; uint32_t flags10; } M1Obj100;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_00156180(void *rig, int a, int b, int c, float t);
void sub_000414A0(int v);

/* 0x0014FE90: enter state 0x13, rig spin (frameTime * 0.003), o flag 0x20, clear h +0x4C
 * bits 0x70, 0x414A0(1), lower rig +0x68 by 20 clamped to 0..200, rig flag 4, then a wait of
 * 288/432/648 by rig kind +0x1C0 and phase 0x14 (spins on other kinds). */
void m1_RigDrop14FE90(M1Obj100 *o, M1Step100 *h)
{
    M1Rig100 *r = h->rig278;
    M1Rig100 *p;
    sub_001456E0(o, h, 0x13, 0);
    sub_00156180(r, 0, 0, 0, m1_frameTime42C858 * 0.003f);
    o->flags10 |= 0x20;
    h->flags4C &= ~0x70u;
    sub_000414A0(1);
    p = h->rig278;
    p->f68 = p->f68 - 20.0f;
    if (0.0f > p->f68)
        p->f68 = 0.0f;
    else if (p->f68 > 200.0f)
        p->f68 = 200.0f;
    r->flags50 |= 4;
    if (r->kind1C0 == 0) {
        r->f5C = 288.0f;
        h->phase58 = 0x14;
    } else if (r->kind1C0 == 1) {
        r->f5C = 432.0f;
        h->phase58 = 0x14;
    } else if (r->kind1C0 == 2) {
        r->f5C = 648.0f;
        h->phase58 = 0x14;
    } else {
        for (;;) ;
    }
}

typedef struct M1Rec100 { void *owner00; uint8_t unk04[0x24 - 4]; } M1Rec100;
extern M1Rec100 r3c_recs3FF588[12];
extern uint8_t m1_cbTbl32C4D0[], m1_cbTbl32C4F0[];
void sub_0018A2D0(void);
void sub_0018A660(void);
void sub_0018B3A0(void);
int  sub_0001BC40(void *o);
typedef struct M1Obj100R {
    uint8_t unk000[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t unk014[0x64 - 0x14];
    float   f64;               /* +0x64 */
    uint8_t unk068[0x70 - 0x68];
    float   s70[4];            /* +0x70 */
    uint8_t unk080[0xD0 - 0x80];
    int32_t iD0;               /* +0xD0 */
    uint8_t unk0D4[0xEC - 0xD4];
    int32_t iEC;               /* +0xEC */
    uint8_t unk0F0[0xF4 - 0xF0];
    int32_t iF4;               /* +0xF4 */
    uint8_t unk0F8[0x11C - 0xF8];
    int32_t i11C, i120, i124;  /* +0x11C..+0x124 */
} M1Obj100R;
typedef struct M1Step100R {
    uint8_t unk00[0x24];
    int32_t i24;               /* +0x24 */
    uint8_t unk28[0x2C - 0x28];
    float   f2C;               /* +0x2C */
    uint8_t unk30[0x74 - 0x30];
    M1Rec100 *rec74;           /* +0x74 */
    void  (*fn78)(void);       /* +0x78 */
    void  (*fn7C)(void);       /* +0x7C */
    void  (*fn80)(void);       /* +0x80 */
    void   *tbl84;             /* +0x84 */
    void   *tbl88;             /* +0x88 */
} M1Step100R;

/* 0x0018B530: setup: take a free record from table 0x3FF588 (12 entries, 0 when full), hook
 * the step callbacks and tables, unit scale, +0x64 = 1e6, +0x24 = 2, +0x2C = -17, o +0x124 =
 * 3, +0xD0 = 0x1BC40(o), o flags (+0xC clear 0xE0 set 0x100, +0x10 |= 5), modes; returns 1. */
int m1_Setup18B530(M1Obj100R *o, M1Step100R *h)
{
    M1Rec100 *e;
    for (e = r3c_recs3FF588; (int)e < (int)(r3c_recs3FF588 + 12); e++)
        if (e->owner00 == 0)
            goto found;
    return 0;
found:
    e->owner00 = o;
    h->rec74 = e;
    h->tbl84 = m1_cbTbl32C4D0;
    h->tbl88 = m1_cbTbl32C4F0;
    h->fn78 = sub_0018A2D0;
    h->fn7C = sub_0018A660;
    h->fn80 = sub_0018B3A0;
    o->s70[3] = 1.0f;
    o->s70[2] = 1.0f;
    o->s70[1] = 1.0f;
    o->s70[0] = 1.0f;
    o->f64 = 1000000.0f;
    h->i24 = 2;
    h->f2C = -17.0f;
    o->i124 = 3;
    o->iD0 = sub_0001BC40(o);
    o->flags0C = (o->flags0C & ~0xE0u) | 0x100;
    o->iEC = 0;
    o->iF4 = 2;
    o->i11C = 1;
    o->i120 = 2;
    o->flags10 |= 5;
    return 1;
}

typedef struct M1Rig100S { uint8_t unk00[0x20]; float q20[4]; uint8_t unk30[0x8C - 0x30]; float f8C; float f90; } M1Rig100S;
typedef struct M1Step100S { uint8_t unk000[0x278]; M1Rig100S *rig278; } M1Step100S;
typedef struct M1Cmd100 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd100;
extern float m1_frameRate42C85C;
M1Cmd100 *sub_00113400(void *h, int v);

/* 0x001868A0: enter state 1, reset the rig quaternion (+0x20), rig +0x8C = 4, +0x90 =
 * 10 * frameRate, command 1 = +-10 degree sway at 2 degrees/frame, command 2 = (1, 0, 1, 0). */
void m1_RigSway1868A0(void *o, M1Step100S *h)
{
    M1Rig100S *r = h->rig278;
    M1Rig100S *p;
    M1Cmd100 *c;
    float t;
    sub_001456E0(o, h, 1, 0);
    p = h->rig278;
    p->q20[2] = 0.0f;
    p->q20[1] = 0.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    r->f8C = 4.0f;
    r->f90 = m1_frameRate42C85C * 10.0f;
    t = m1_frameTime42C858 * 0.034906585f;
    c = sub_00113400(h, 1);
    c->f10 = 0.17453294f;
    c->f14 = -0.17453294f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
    c = sub_00113400(h, 2);
    c->f10 = 1.0f;
    c->f14 = 0.0f;
    c->f18 = 1.0f;
    c->f1C = 0.0f;
}

typedef struct M1Pl100 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl100;
typedef struct M1Obj100F { uint8_t unk00[0x20]; float *node20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Obj100F;
typedef struct M1Step100F { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; void *rig278; } M1Step100F;
extern M1Pl100 *g_playerObj;
void sub_001561D0(void *rig, float a, float b);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001ADA60(float *out, const float *a, const float *b);

/* 0x00146AA0: enter state 0x41, rig spin (frameTime * 0.003) and tilt (-12, 10 * frameRate),
 * clear h +0x4C bits 0x70, then face away from the player: node forward = -(flat direction
 * from the player), up (0, 1, 0, 0), side rebuilt by 0x1ADA60. */
void m1_FaceAway146AA0(M1Obj100F *o, M1Step100F *h)
{
    void *r = h->rig278;
    float d[4];
    float *n;
    sub_001456E0(o, h, 0x41, 0);
    sub_00156180(r, 0, 0, 0, m1_frameTime42C858 * 0.003f);
    sub_001561D0(r, -12.0f, m1_frameRate42C85C * 10.0f);
    h->flags4C &= ~0x70u;
    sub_001AD9F0(d, o->pos60, g_playerObj->pos60);
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(o->node20 + 8, d, -1.0f);
    o->node20[7] = 0.0f;
    o->node20[6] = 0.0f;
    o->node20[4] = 0.0f;
    o->node20[5] = 1.0f;
    n = o->node20;
    sub_001ADA60(n, n + 4, n + 8);
}

