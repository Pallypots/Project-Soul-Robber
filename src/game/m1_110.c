/* Area m1, file 110. Names inferred. */
#include <stdint.h>

typedef struct M1Cmd110 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd110;
typedef struct M1Pl110 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl110;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
extern M1Pl110 *g_playerObj;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_00156180(void *r, float a, float b, float c, float d);
void sub_001561D0(void *r, float a, float b);
M1Cmd110 *sub_00113400(void *h, int v);
int  sub_000494D0(int id, const void *pos, int c);
void sub_000F5D40(float *d, const float *s);

typedef struct M1Rig110K { uint8_t unk00[0x50]; uint32_t flags50; uint8_t unk54[0x68 - 0x54]; float f68; float f6C; uint8_t unk70[0x78 - 0x70]; float v78[4]; } M1Rig110K;
typedef struct M1Step110K {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0xF8 - 0x50];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    void   *tgt104;            /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig110K *rig278;         /* +0x278 */
} M1Step110K;
typedef struct M1Obj110K { uint8_t unk00[0x60]; float pos60[4]; } M1Obj110K;

/* 0x0014A220: stagger setup: state 0x21, decay 0.003, rise (-12, 10 * frameRate), +0x6C = 0,
 * +0x68 -= 25 clamped to 0..200, sound 0x12B, flag 0x40, aimed at the player (+0x104, mode 1,
 * position to rig +0x78), and a +-10 degree sway at 5 degrees/frame. */
void m1_Stagger14A220(M1Obj110K *o, M1Step110K *h)
{
    M1Rig110K *r = h->rig278;
    M1Rig110K *p;
    M1Cmd110 *c;
    M1Pl110 *g;
    float v;
    float t;
    sub_001456E0(o, h, 0x21, 0);
    sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    sub_001561D0(r, -12.0f, m1_frameRate42C85C * 10.0f);
    h->flags4C &= ~0x70u;
    r->f6C = 0.0f;
    p = h->rig278;
    v = p->f68 - 25.0f;
    p->f68 = v;
    if (0.0f > v)
        p->f68 = 0.0f;
    else if (v > 200.0f)
        p->f68 = 200.0f;
    sub_000494D0(0x12B, o->pos60, 0);
    r->flags50 |= 0x40;
    g = g_playerObj;
    h->tgt104 = g;
    h->mode0F8 = 1;
    sub_000F5D40(r->v78, g->pos60);
    t = m1_frameTime42C858 * 0.0872664675f;
    c = sub_00113400(h, 1);
    c->f10 = 0.174532935f;
    c->f14 = -0.174532935f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

typedef struct M1Rig110F { uint8_t unk00[0x18]; uint32_t flags18; uint8_t unk1C[4]; float q20[4]; } M1Rig110F;
typedef struct M1Step110F { uint8_t unk000[0x278]; M1Rig110F *rig278; } M1Step110F;
typedef struct M1Obj110F { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x20 - 0x14]; float *m20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Obj110F;
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001ADA60(float *out, const float *a, const float *b);
int  sub_00036750(void *o, int v);

/* 0x001876D0: flip away: state 0x30, rig spin (0, -140, -20 times frameRate), rig flag 0x20,
 * face the object away from the player on the flat plane (matrix rebuilt upright), and either
 * a 0.3 spin command 6 (pending rig flag 0x40, o flag 4) or pose 1. */
void m1_FlipAway1876D0(M1Obj110F *o, M1Step110F *h)
{
    M1Rig110F *r = h->rig278;
    M1Rig110F *p;
    M1Cmd110 *c;
    float d[4];
    sub_001456E0(o, h, 0x30, 0);
    p = h->rig278;
    p->q20[2] = 0.0f - m1_frameRate42C85C * 20.0f;
    p->q20[1] = m1_frameRate42C85C * -140.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    r->flags18 |= 0x20;
    sub_001AD9F0(d, o->pos60, g_playerObj->pos60);
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(o->m20 + 8, d, -1.0f);
    o->m20[7] = 0.0f;
    o->m20[6] = 0.0f;
    o->m20[4] = 0.0f;
    o->m20[5] = 1.0f;
    sub_001ADA60(o->m20, o->m20 + 4, o->m20 + 8);
    if (r->flags18 & 0x40) {
        r->flags18 &= ~0x40u;
        o->flags10 |= 4;
        c = sub_00113400(h, 6);
        c->f10 = 0.300000012f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        return;
    }
    sub_00036750(o, 1);
}

typedef struct M1Cmd110F { int32_t kind00; uint8_t unk04[0x10 - 4]; float f10, f14, f18, f1C; } M1Cmd110F;
typedef struct M1Step110L {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    void   *rig278;            /* +0x278 */
} M1Step110L;
typedef struct M1Obj110L {
    uint8_t unk000[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t unk014[0x60 - 0x14];
    float   pos60[4];          /* +0x60 */
    uint8_t unk070[0x128 - 0x70];
    uint32_t flags128;         /* +0x128 */
} M1Obj110L;
typedef struct M1Rig110L {
    uint32_t flags00;
    uint8_t unk04[0xC - 4];
    float   f0C, f10;          /* +0x0C */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint8_t b40;               /* +0x40 */
} M1Rig110L;
typedef struct M1Rig110M { uint32_t flags00; uint8_t unk04[0x50 - 4]; uint8_t b50; } M1Rig110M;
extern float m1_fps42C964;

/* 0x00159500: launch up (rig variant of 0x152740): state 0x37, rig motion (rise 100 *
 * frameRate, decay 0.005), flags; with rig flag 0x10 also pose 4, sound 0x130, o flags 0xD,
 * a one-second hold (command 7) and, with the alt flag, command 5 = (0.5, 2). */
void m1_LaunchUp159500(M1Obj110L *o, M1Step110L *h)
{
    M1Rig110L *r = (M1Rig110L *)h->rig278;
    M1Cmd110F *c;
    float t;
    sub_001456E0(o, h, 0x37, 0);
    r->f28 = m1_frameRate42C85C * 100.0f;
    r->f2C = 0.0f;
    r->f24 = 0.0f;
    r->f30 = 1.0f;
    r->f10 = 0.0f;
    r->f0C = m1_frameTime42C858 * 0.00499999989f;
    o->flags0C &= ~0x20u;
    h->flags4C &= ~0x70u;
    o->flags10 |= 4;
    r->flags00 |= 0xF;
    if (!(r->b40 & 0x10))
        return;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 0xD;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = (M1Cmd110F *)sub_00113400(h, 7);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = (M1Cmd110F *)sub_00113400(h, 5);
        c->f10 = 0.5f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

/* 0x001538B0: knocked down: state 0x49 when airborne-hit (o +0x128 bits 6 without 0x18) else
 * 0x45, decay 0.003, flags, pose 6 with sound 0x10E; with rig flag 0x10 the launch-up tail of
 * 0x152740 (pose 4, sound 0x130, hold command 8, alt command 4 = (20, 2)). */
void m1_KnockDown1538B0(M1Obj110L *o, M1Step110L *h)
{
    M1Rig110M *r = (M1Rig110M *)h->rig278;
    M1Cmd110F *c;
    uint32_t f = o->flags128;
    float t;
    if (!(f & 0x18) && (f & 6))
        sub_001456E0(o, h, 0x49, 0);
    else
        sub_001456E0(o, h, 0x45, 0);
    sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    h->flags4C &= ~0x70u;
    o->flags0C &= ~0x20u;
    r->flags00 |= 2;
    sub_00036750(o, 6);
    sub_000494D0(0x10E, o->pos60, 0);
    if (!(r->b50 & 0x10))
        return;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 5;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = (M1Cmd110F *)sub_00113400(h, 8);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = (M1Cmd110F *)sub_00113400(h, 4);
        c->f10 = 20.0f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

/* 0x00154080: launch-up tail shared by the knock states: pose 4, sound 0x130, o flags 5,
 * clear h flags, a one-second hold (command 8) and, with the alt flag, command 4 = (20, 2). */
void m1_LaunchTail154080(M1Obj110L *o, M1Step110L *h)
{
    M1Cmd110F *c;
    float t;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 5;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = (M1Cmd110F *)sub_00113400(h, 8);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = (M1Cmd110F *)sub_00113400(h, 4);
        c->f10 = 20.0f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

typedef struct M1Rig110N { uint8_t unk00[0x50]; uint8_t b50; uint8_t unk51[0x58 - 0x51]; int32_t n58; uint8_t unk5C[0x68 - 0x5C]; float f68; } M1Rig110N;

/* 0x0014E800: heavy hit: state 0x33, decay 0.003, o flag 0x20, hit count +0x58 += 2, +0x68 +=
 * 20 clamped to 0..200, and with rig flag 0x10 the launch-up tail (as 0x154080). */
void m1_HeavyHit14E800(M1Obj110L *o, M1Step110L *h)
{
    M1Rig110N *r = (M1Rig110N *)h->rig278;
    M1Rig110N *p;
    M1Cmd110F *c;
    float v;
    float t;
    sub_001456E0(o, h, 0x33, 0);
    sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    o->flags10 |= 0x20;
    h->flags4C &= ~0x70u;
    r->n58 += 2;
    p = (M1Rig110N *)h->rig278;
    v = p->f68 + 20.0f;
    p->f68 = v;
    if (0.0f > v)
        p->f68 = 0.0f;
    else if (v > 200.0f)
        p->f68 = 200.0f;
    if (!(r->b50 & 0x10))
        return;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 5;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = (M1Cmd110F *)sub_00113400(h, 8);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = (M1Cmd110F *)sub_00113400(h, 4);
        c->f10 = 20.0f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

typedef struct M1Rig110P { uint32_t flags00; uint8_t unk04[0x50 - 4]; uint32_t flags50; uint8_t unk54[0x1C0 - 0x54]; int32_t kind1C0; } M1Rig110P;
typedef struct M1Step110P {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t state58;           /* +0x58 */
    uint8_t unk05C[0x74 - 0x5C];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig110P *rig278;         /* +0x278 */
} M1Step110P;
void sub_00113AA0(void *o, void *h);
void sub_00113A40(void *o, void *h);

/* 0x001521E0: grab hit: with rig flag 0x10 enter state 7 and the launch-up tail (o flags 0xD,
 * hold command 8, then step 10); otherwise decay 0.003, 0x113A40, rig flags, and a wait of
 * 2, 3 or 4 by rig kind +0x1C0 (hangs on any other kind). */
void m1_GrabHit1521E0(M1Obj110L *o, M1Step110P *h)
{
    M1Rig110P *r = h->rig278;
    M1Cmd110F *c;
    float t;
    int k;
    if (r->flags50 & 0x10) {
        sub_001456E0(o, h, 7, 0);
        sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
        sub_00113AA0(o, h);
        sub_00036750(o, 4);
        sub_000494D0(0x130, o->pos60, 0);
        o->flags10 |= 0xD;
        h->flags4C &= ~0x1000070u;
        t = m1_fps42C964;
        c = (M1Cmd110F *)sub_00113400(h, 8);
        if (t != -1.0f)
            c->f10 = t;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
        h->state58 = 10;
        return;
    }
    sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    sub_00113A40(o, h);
    r->flags50 |= 0x10000;
    r->flags00 |= 7;
    k = r->kind1C0;
    if (k == 0)
        h->wait74 = 2.0f;
    else if (k == 1)
        h->wait74 = 3.0f;
    else if (k == 2)
        h->wait74 = 4.0f;
    else
        for (;;) ;
}

typedef struct M1Rig110Q {
    uint32_t unk00;
    uint8_t unk04[0xC - 4];
    float   f0C, f10;          /* +0x0C */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint8_t b40;               /* +0x40 */
    uint8_t unk41[3];
    int32_t n44;               /* +0x44 */
    uint8_t unk48[0x54 - 0x48];
    float   f54;               /* +0x54 */
} M1Rig110Q;

/* 0x00158140: heavy hit (rig variant of 0x14E800): state 0x33, rig decay 0.005, o flag 0x20,
 * hit count +0x44 += 2, +0x54 += 20 clamped to 0..200, and with rig flag 0x10 the tail of
 * 0x159500 (o flags 0xD, hold command 7, alt command 5 = (0.5, 2)). */
void m1_HeavyHit158140(M1Obj110L *o, M1Step110L *h)
{
    M1Rig110Q *r = (M1Rig110Q *)h->rig278;
    M1Rig110Q *p;
    M1Cmd110F *c;
    float v;
    float t;
    sub_001456E0(o, h, 0x33, 0);
    r->f0C = m1_frameTime42C858 * 0.00499999989f;
    r->f2C = 0.0f;
    r->f28 = 0.0f;
    r->f24 = 0.0f;
    r->f30 = 1.0f;
    r->f10 = 0.0f;
    o->flags10 |= 0x20;
    h->flags4C &= ~0x70u;
    r->n44 += 2;
    p = (M1Rig110Q *)h->rig278;
    v = p->f54 + 20.0f;
    p->f54 = v;
    if (0.0f > v)
        p->f54 = 0.0f;
    else if (v > 200.0f)
        p->f54 = 200.0f;
    if (!(r->b40 & 0x10))
        return;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 0xD;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = (M1Cmd110F *)sub_00113400(h, 7);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = (M1Cmd110F *)sub_00113400(h, 5);
        c->f10 = 0.5f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}
