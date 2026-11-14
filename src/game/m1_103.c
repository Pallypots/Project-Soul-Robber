/* Area m1, file 103: spawn bursts. Names inferred. */
#include <stdint.h>

typedef struct M1Obj103 { uint8_t unk00[0x84]; float f84; } M1Obj103;
typedef struct M1Step103 { uint8_t unk00[0x58]; int32_t phase58; float t5C; } M1Step103;
extern float m1_frameRate42C85C;
void sub_0013A380(void *o, int a, const int *ids);
void *sub_00036750(void *o, int b);
int  sub_000ED780(void *o);

/* 0x00177400: phase 0 spawns the parts 0x12..0x1E (0x13A380, list ends with -1) and after 1 s
 * starts effect 2 and goes to phase 1; phase 1 raises +0x84 by 10 * frameRate and releases the
 * object after 3 s. */
void m1_Burst177400(M1Obj103 *o, M1Step103 *h)
{
    int ids[14];
    ids[0] = 0x12;
    ids[1] = 0x13;
    ids[2] = 0x14;
    ids[3] = 0x15;
    ids[4] = 0x16;
    ids[5] = 0x17;
    ids[6] = 0x18;
    ids[7] = 0x19;
    ids[8] = 0x1A;
    ids[9] = 0x1B;
    ids[10] = 0x1C;
    ids[11] = 0x1D;
    ids[12] = 0x1E;
    ids[13] = -1;
    switch (h->phase58) {
    case 0:
        sub_0013A380(o, 1, ids);
        if (h->t5C > 1.0f) {
            sub_00036750(o, 2);
            h->phase58++;
        }
        break;
    case 1:
        o->f84 = m1_frameRate42C85C * 10.0f + o->f84;
        if (h->t5C > 3.0f)
            sub_000ED780(o);
        break;
    }
}

typedef struct M1Mov103 {
    uint8_t unk00[0xB4];
    float   fB4, fB8, fBC, fC0, fC4, fC8, fCC, fD0;   /* +0xB4..+0xD0 */
} M1Mov103;
typedef struct M1Obj103J { uint8_t unk00[0xC]; uint32_t flags0C; uint8_t unk10[0x64 - 0x10]; float f64; } M1Obj103J;
void sub_000F3B00(void *o, int v);
void sub_000F3B30(void *o, int v);
void sub_000F3F00(void *o, float v);

/* Movement reset shared with the jump starts: +0xB4 = 98 * frameRate, clear +0xB8..+0xD0. */
static void m1_MoveReset103(M1Mov103 *s)
{
    s->fB4 = m1_frameRate42C85C * 98.0f;
    s->fC0 = 0.0f;
    s->fB8 = 0.0f;
    s->fC4 = 0.0f;
    s->fBC = 0.0f;
    s->fD0 = 0.0f;
    s->fCC = 0.0f;
    s->fC8 = 0.0f;
}

/* 0x0010B150: knock-up: reset the movement, height +0x64 = -2.5, clear o flag 0x80, launch
 * (+0xB4 0.02, +0xB8 0.07, +0xC0 -9, +0xC4 0.0044, all per frameRate), 0xF3B00(0xC4),
 * 0xF3B30(0x20), 0xF3F00(0.75). */
void m1_KnockUp10B150(M1Obj103J *o, M1Mov103 *s)
{
    m1_MoveReset103(s);
    o->f64 = -2.5f;
    o->flags0C &= ~0x80u;
    s->fB4 = m1_frameRate42C85C * 0.02f;
    s->fB8 = m1_frameRate42C85C * 0.07f;
    s->fC0 = m1_frameRate42C85C * -9.0f;
    s->fC4 = m1_frameRate42C85C * 0.0043633231f;
    sub_000F3B00(o, 0xC4);
    sub_000F3B30(o, 0x20);
    sub_000F3F00(o, 0.75f);
}

typedef struct M1Rig103 {
    uint8_t unk00[0xC];
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
    uint8_t unk44[0x54 - 0x44];
    float   f54;               /* +0x54 */
} M1Rig103;
typedef struct M1Step103S { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig103 *rig278; } M1Step103S;
typedef struct M1Cmd103 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd103;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
M1Cmd103 *sub_00113400(void *h, int v);

/* 0x00157370: as 0x157480 but raising rig +0x54 by 30. */
void m1_Sway157370(void *o, M1Step103S *h)
{
    M1Rig103 *r = h->rig278;
    M1Rig103 *p;
    M1Cmd103 *c;
    float t;
    sub_001456E0(o, h, 0x15, 0);
    r->rate0C = m1_frameTime42C858 * 0.005f;
    r->q24[2] = 0.0f - m1_frameRate42C85C * 3.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    p = h->rig278;
    p->f54 = p->f54 + 30.0f;
    if (0.0f > p->f54)
        p->f54 = 0.0f;
    else if (p->f54 > 200.0f)
        p->f54 = 200.0f;
    h->flags4C &= ~0x70u;
    r->flags40 |= 0x80;
    t = m1_frameTime42C858 * 0.034906585f;
    c = sub_00113400(h, 1);
    c->f10 = 0.17453294f;
    c->f14 = -0.17453294f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

typedef struct M1Rig103T { uint8_t unk000[0x50]; uint32_t flags50; uint8_t unk054[0x68 - 0x54]; float f68; uint8_t unk06C[0x78 - 0x6C]; float pos78[4]; } M1Rig103T;
typedef struct M1Step103T {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0xF8 - 0x50];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    void   *tgt104;            /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig103T *rig278;         /* +0x278 */
} M1Step103T;
typedef struct M1Pl103 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl103;
extern M1Pl103 *g_playerObj;
void sub_00156180(void *rig, float a, float b, float c, float t);
void sub_001561D0(void *rig, float a, float b);
int  sub_000494D0(int id, const void *pos, int c);
void sub_000F5D40(float *d, const float *s);

/* 0x0014A9F0: enter state 0x22, rig spin (-2 * frameRate, frameTime * 0.003) and tilt (-15,
 * 10 * frameRate), clear h +0x4C bits 0x70, lower rig +0x68 by 30 clamped to 0..200, sound
 * 0x12B, rig flag 0x40, target the player (mode 1) and copy its position to rig +0x78. */
void m1_RigLunge14A9F0(uint8_t *o, M1Step103T *h)
{
    M1Rig103T *r = h->rig278;
    M1Rig103T *p;
    sub_001456E0(o, h, 0x22, 0);
    sub_00156180(r, m1_frameRate42C85C * -2.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.003f);
    sub_001561D0(r, -15.0f, m1_frameRate42C85C * 10.0f);
    h->flags4C &= ~0x70u;
    p = h->rig278;
    p->f68 = p->f68 - 30.0f;
    if (0.0f > p->f68)
        p->f68 = 0.0f;
    else if (p->f68 > 200.0f)
        p->f68 = 200.0f;
    sub_000494D0(0x12B, o + 0x60, 0);
    r->flags50 |= 0x40;
    h->tgt104 = g_playerObj;
    h->mode0F8 = 1;
    sub_000F5D40(r->pos78, g_playerObj->pos60);
}

typedef struct M1Rig103D {
    uint8_t unk00[0xC];
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
    uint8_t unk44[0x48 - 0x44];
    float   f48;               /* +0x48 */
    uint8_t unk4C[0x54 - 0x4C];
    float   f54;               /* +0x54 */
    uint8_t unk58[0x1BC - 0x58];
    int32_t kind1BC;           /* +0x1BC */
} M1Rig103D;
typedef struct M1Step103D { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x58 - 0x50]; int32_t phase58; uint8_t unk05C[0x278 - 0x5C]; M1Rig103D *rig278; } M1Step103D;
void sub_000414A0(int v);

/* 0x00158660: enter state 0x13, reset the rig quaternion, rig +0xC = frameTime * 0.005, clear
 * h +0x4C bits 0x70, 0x414A0(1), lower rig +0x54 by 20 clamped to 0..200, rig flag 4, then a
 * wait of 288/432/648 by rig kind +0x1BC and phase 0x14 (spins on other kinds). */
void m1_RigDrop158660(void *o, M1Step103D *h)
{
    M1Rig103D *r = h->rig278;
    M1Rig103D *p;
    sub_001456E0(o, h, 0x13, 0);
    r->q24[2] = 0.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    r->rate0C = m1_frameTime42C858 * 0.005f;
    h->flags4C &= ~0x70u;
    sub_000414A0(1);
    p = h->rig278;
    p->f54 = p->f54 - 20.0f;
    if (0.0f > p->f54)
        p->f54 = 0.0f;
    else if (p->f54 > 200.0f)
        p->f54 = 200.0f;
    r->flags40 |= 4;
    if (r->kind1BC == 0) {
        r->f48 = 288.0f;
        h->phase58 = 0x14;
    } else if (r->kind1BC == 1) {
        r->f48 = 432.0f;
        h->phase58 = 0x14;
    } else if (r->kind1BC == 2) {
        r->f48 = 648.0f;
        h->phase58 = 0x14;
    } else {
        for (;;) ;
    }
}
