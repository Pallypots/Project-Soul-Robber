/* Area m1, file 111: more knock-state setups. Names inferred. */
#include <stdint.h>

typedef struct M1Cmd111 { int32_t kind00; uint8_t unk04[0x10 - 4]; float f10, f14, f18, f1C; } M1Cmd111;
typedef struct M1Step111 {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    void   *rig278;            /* +0x278 */
} M1Step111;
typedef struct M1Obj111 {
    uint8_t unk000[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t unk014[0x60 - 0x14];
    float   pos60[4];          /* +0x60 */
    uint8_t unk070[0x128 - 0x70];
    uint32_t flags128;         /* +0x128 */
} M1Obj111;
extern float m1_frameTime42C858;
extern float m1_fps42C964;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_00156180(void *r, float a, float b, float c, float d);
M1Cmd111 *sub_00113400(void *h, int v);
int  sub_000494D0(int id, const void *pos, int c);
int  sub_00036750(void *o, int v);

typedef struct M1Rig111R {
    uint32_t flags00;
    uint8_t unk04[0xC - 4];
    float   f0C, f10;          /* +0x0C */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint8_t b40;               /* +0x40 */
} M1Rig111R;

/* 0x001599D0: knocked down (rig variant of 0x1538B0): state 0x49 or 0x45, rig decay 0.005,
 * flags, pose 6 with sound 0x10E; with rig flag 0x10 the 0x159500 tail. */
void m1_KnockDown1599D0(M1Obj111 *o, M1Step111 *h)
{
    M1Rig111R *r = (M1Rig111R *)h->rig278;
    M1Cmd111 *c;
    uint32_t f = o->flags128;
    float t;
    if (!(f & 0x18) && (f & 6))
        sub_001456E0(o, h, 0x49, 0);
    else
        sub_001456E0(o, h, 0x45, 0);
    r->f2C = 0.0f;
    r->f28 = 0.0f;
    r->f24 = 0.0f;
    r->f30 = 1.0f;
    r->f10 = 0.0f;
    r->f0C = m1_frameTime42C858 * 0.00499999989f;
    o->flags0C &= ~0x20u;
    h->flags4C &= ~0x70u;
    r->flags00 |= 2;
    sub_00036750(o, 6);
    sub_000494D0(0x10E, o->pos60, 0);
    if (!(r->b40 & 0x10))
        return;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 0xD;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = sub_00113400(h, 7);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = sub_00113400(h, 5);
        c->f10 = 0.5f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

typedef struct M1Rig111N { uint8_t unk00[0x50]; uint8_t b50; uint8_t unk51[0x68 - 0x51]; float f68; } M1Rig111N;

/* 0x0014EDB0: spin hit: state 0x33, decay 0.003, o flag 0x20, +0x68 += 20 clamped to 0..200,
 * o flag 4 with spin command 0xA at 1/12, and with rig flag 0x10 the launch-up tail. */
void m1_SpinHit14EDB0(M1Obj111 *o, M1Step111 *h)
{
    M1Rig111N *r = (M1Rig111N *)h->rig278;
    M1Rig111N *p;
    M1Cmd111 *c;
    float v;
    float t;
    sub_001456E0(o, h, 0x33, 0);
    sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    o->flags10 |= 0x20;
    h->flags4C &= ~0x70u;
    p = (M1Rig111N *)h->rig278;
    v = p->f68 + 20.0f;
    p->f68 = v;
    if (0.0f > v)
        p->f68 = 0.0f;
    else if (v > 200.0f)
        p->f68 = 200.0f;
    o->flags10 |= 4;
    c = sub_00113400(h, 0xA);
    c->f10 = 0.0833333358f;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (!(r->b50 & 0x10))
        return;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 5;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = sub_00113400(h, 8);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = sub_00113400(h, 4);
        c->f10 = 20.0f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

void sub_001561D0(void *r, float a, float b);
extern float m1_frameRate42C85C;
typedef struct M1Rig111T { uint8_t unk00[0x50]; uint32_t flags50; } M1Rig111T;

/* 0x00151310: blown back: state 0x30, decay 0.003, rise (-12, 10 * frameRate), o flags 0x24,
 * the launch-up tail with rig flag 0x10, and a 0.1 spin command 7 for a pending rig flag 8. */
void m1_BlownBack151310(M1Obj111 *o, M1Step111 *h)
{
    M1Rig111T *r = (M1Rig111T *)h->rig278;
    M1Cmd111 *c;
    float t;
    sub_001456E0(o, h, 0x30, 0);
    sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.00300000003f);
    sub_001561D0(r, -12.0f, m1_frameRate42C85C * 10.0f);
    h->flags4C &= ~0x70u;
    o->flags10 |= 0x24;
    if (*(uint8_t *)&r->flags50 & 0x10) {
        sub_00036750(o, 4);
        sub_000494D0(0x130, o->pos60, 0);
        o->flags10 |= 5;
        h->flags4C &= ~0x1000070u;
        t = m1_fps42C964;
        c = sub_00113400(h, 8);
        if (t != -1.0f)
            c->f10 = t;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
        if (h->b20 & 1) {
            c = sub_00113400(h, 4);
            c->f10 = 20.0f;
            c->f14 = 2.0f;
            c->f18 = 0.0f;
            c->f1C = 0.0f;
            if (c->kind00 != 0)
                c->kind00 = 2;
        }
    }
    if (r->flags50 & 8) {
        r->flags50 &= ~8u;
        c = sub_00113400(h, 7);
        c->f10 = 0.100000001f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

typedef struct M1Rig111U {
    uint32_t unk00;
    float   f04, f08, f0C, f10;  /* +0x04 */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
} M1Rig111U;

/* 0x00158DA0: blown back (rig variant of 0x151310): state 0x30, rig motion (-12, 10 *
 * frameRate, decay 0.005), o flags 0x24, the 0x159500 tail with rig flag 0x10, and a 0.1 spin
 * command 6 for a pending rig flag 8. */
void m1_BlownBack158DA0(M1Obj111 *o, M1Step111 *h)
{
    M1Rig111U *r = (M1Rig111U *)h->rig278;
    M1Cmd111 *c;
    float t;
    sub_001456E0(o, h, 0x30, 0);
    r->f2C = 0.0f;
    r->f28 = 0.0f;
    r->f24 = 0.0f;
    r->f10 = 0.0f;
    r->f0C = m1_frameTime42C858 * 0.00499999989f;
    r->f30 = 1.0f;
    r->f04 = -12.0f;
    r->f08 = m1_frameRate42C85C * 10.0f;
    o->flags10 |= 0x24;
    h->flags4C &= ~0x70u;
    if (*(uint8_t *)&r->flags40 & 0x10) {
        sub_00036750(o, 4);
        sub_000494D0(0x130, o->pos60, 0);
        o->flags10 |= 0xD;
        h->flags4C &= ~0x1000070u;
        t = m1_fps42C964;
        c = sub_00113400(h, 7);
        if (t != -1.0f)
            c->f10 = t;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
        if (h->b20 & 1) {
            c = sub_00113400(h, 5);
            c->f10 = 0.5f;
            c->f14 = 2.0f;
            c->f18 = 0.0f;
            c->f1C = 0.0f;
            if (c->kind00 != 0)
                c->kind00 = 2;
        }
    }
    if (r->flags40 & 8) {
        r->flags40 &= ~8u;
        c = sub_00113400(h, 6);
        c->f10 = 0.100000001f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

typedef struct M1Rig111S {
    uint32_t unk00;
    uint8_t unk04[0xC - 4];
    float   f0C, f10;          /* +0x0C */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint8_t b40;               /* +0x40 */
    uint8_t unk41[0x54 - 0x41];
    float   f54;               /* +0x54 */
} M1Rig111S;

/* 0x001582A0: spin hit (rig variant of 0x14EDB0): state 0x33, rig decay 0.005, o flag 0x20,
 * +0x54 += 20 clamped to 0..200, o flag 4 with spin command 9 at 1/12, and with rig flag 0x10
 * the 0x159500 tail. */
void m1_SpinHit1582A0(M1Obj111 *o, M1Step111 *h)
{
    M1Rig111S *r = (M1Rig111S *)h->rig278;
    M1Rig111S *p;
    M1Cmd111 *c;
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
    p = (M1Rig111S *)h->rig278;
    v = p->f54 + 20.0f;
    p->f54 = v;
    if (0.0f > v)
        p->f54 = 0.0f;
    else if (v > 200.0f)
        p->f54 = 200.0f;
    o->flags10 |= 4;
    c = sub_00113400(h, 9);
    c->f10 = 0.0833333358f;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (!(r->b40 & 0x10))
        return;
    sub_00036750(o, 4);
    sub_000494D0(0x130, o->pos60, 0);
    o->flags10 |= 0xD;
    h->flags4C &= ~0x1000070u;
    t = m1_fps42C964;
    c = sub_00113400(h, 7);
    if (t != -1.0f)
        c->f10 = t;
    c->f14 = 0.0f;
    c->f18 = 0.0f;
    c->f1C = 0.0f;
    if (c->kind00 != 0)
        c->kind00 = 2;
    if (h->b20 & 1) {
        c = sub_00113400(h, 5);
        c->f10 = 0.5f;
        c->f14 = 2.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
    }
}

typedef struct M1Rig111G {
    uint32_t flags00;
    uint8_t unk04[0xC - 4];
    float   f0C, f10;          /* +0x0C */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
    uint8_t unk44[0x1BC - 0x44];
    int32_t kind1BC;           /* +0x1BC */
} M1Rig111G;
typedef struct M1Step111G {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t state58;           /* +0x58 */
    uint8_t unk05C[0x74 - 0x5C];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig111G *rig278;         /* +0x278 */
} M1Step111G;
void sub_00113AA0(void *o, void *h);
void sub_00113A40(void *o, void *h);

/* 0x00159320: grab hit (rig variant of 0x1521E0): with rig flag 0x10 enter state 7, rig decay
 * 0.005, 0x113AA0 and the 0x159500 tail with step 10; otherwise rig decay, 0x113A40, rig flags
 * and a wait of 2, 3 or 4 by rig kind +0x1BC (hangs on any other kind). */
void m1_GrabHit159320(M1Obj111 *o, M1Step111G *h)
{
    M1Rig111G *r = h->rig278;
    M1Cmd111 *c;
    float t;
    int k;
    if (*(uint8_t *)&r->flags40 & 0x10) {
        sub_001456E0(o, h, 7, 0);
        r->f2C = 0.0f;
        r->f28 = 0.0f;
        r->f24 = 0.0f;
        r->f30 = 1.0f;
        r->f10 = 0.0f;
        r->f0C = m1_frameTime42C858 * 0.00499999989f;
        sub_00113AA0(o, h);
        sub_00036750(o, 4);
        sub_000494D0(0x130, o->pos60, 0);
        o->flags10 |= 0xD;
        h->flags4C &= ~0x1000070u;
        t = m1_fps42C964;
        c = sub_00113400(h, 7);
        if (t != -1.0f)
            c->f10 = t;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
        if (c->kind00 != 0)
            c->kind00 = 2;
        h->state58 = 10;
        if (h->b20 & 1) {
            c = sub_00113400(h, 5);
            c->f10 = 0.5f;
            c->f14 = 2.0f;
            c->f18 = 0.0f;
            c->f1C = 0.0f;
            if (c->kind00 != 0)
                c->kind00 = 2;
        }
        return;
    }
    r->f2C = 0.0f;
    r->f28 = 0.0f;
    r->f24 = 0.0f;
    r->f30 = 1.0f;
    r->f10 = 0.0f;
    r->f0C = m1_frameTime42C858 * 0.00499999989f;
    sub_00113A40(o, h);
    r->flags40 |= 0x4000;
    r->flags00 |= 7;
    k = r->kind1BC;
    if (k == 0)
        h->wait74 = 2.0f;
    else if (k == 1)
        h->wait74 = 3.0f;
    else if (k == 2)
        h->wait74 = 4.0f;
    else
        for (;;) ;
}
