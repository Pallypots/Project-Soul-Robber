/* Area m1, file 84: movement steps. Names inferred. */
#include <stdint.h>

typedef struct M1Obj84 {
    uint8_t unk00[0x54];
    float   yaw54;             /* +0x54 */
    uint8_t unk58[0x60 - 0x58];
    float   pos60[4];          /* +0x60 */
    uint8_t unk70[0x128 - 0x70];
    uint8_t b128;              /* +0x128 */
} M1Obj84;
typedef struct M1V4 { float x, y, z, w; } M1V4;
typedef struct M1Data84 { uint8_t unk00[0x10]; float fwd10; } M1Data84;
float sub_001A3F30(float x);
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD9B0(float *d, const float *m, const float *v);

/* 0x0017C010: while touching (o +0x128 bits 0x18) and the forward speed is above 0,
 * move the object forward by +0x10 along its yaw. */
void m1_Push17C010(M1Obj84 *o, void *h, M1Data84 *d)
{
    float v[4];
    float m[16];
    M1V4 p;
    if (!(o->b128 & 0x18))
        return;
    if (!(sub_001A3F30(d->fwd10) > 0.0f))
        return;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[3] = 1.0f;
    v[2] = d->fwd10;
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->yaw54);
    sub_001AD9B0(v, m, v);
    p = *(M1V4 *)o->pos60;
    p.x += v[0];
    p.y += v[1];
    p.z += v[2];
    *(M1V4 *)o->pos60 = p;
}

typedef struct M1Rig84D {
    uint8_t unk00[0x10];
    float   f10;               /* +0x10 */
    int32_t i14;               /* +0x14 */
    int32_t fx18;              /* +0x18 */
    int32_t idx1C;             /* +0x1C */
    uint8_t unk20[4];
    int16_t w24;               /* +0x24 */
} M1Rig84D;
typedef struct M1Step84D { uint8_t unk000[0x278]; M1Rig84D *rig278; } M1Step84D;
typedef struct M1Obj84D { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; } M1Obj84D;
extern const float m1_doorYaw27A5F8[4];
extern const float m1_doorPos32B6B8[4][4];
int  sub_000A57C0(int id, const float *pos, const float *rot);
void sub_000A43C0(int slot, int fx);

/* 0x0017C6F0: spawn effect 0xDD at door point +0x1C (table 0x32B6B8) facing the table yaw
 * turned half round (wrapped to pi), keep its slot at +0x18 and give it effect 0x41; o +0x10
 * |= 0x41, clear o +0xC bit 0x20. */
void m1_DoorFx17C6F0(M1Obj84D *o, M1Step84D *h)
{
    M1Rig84D *r = h->rig278;
    float v[4];
    float a;
    int n = r->idx1C;
    v[1] = 0.0f;
    v[0] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    r->f10 = 0.0f;
    r->w24 = 0;
    r->i14 = 0;
    a = m1_doorYaw27A5F8[r->idx1C] + 3.1415927f;
    v[1] = a;
    if (a > 3.1415927f) {
        do
            a -= 6.2831855f;
        while (a > 3.1415927f);
        v[1] = a;
    }
    r->fx18 = sub_000A57C0(0xDD, m1_doorPos32B6B8[n], v);
    if (r->fx18 >= 0)
        sub_000A43C0(r->fx18, 0x41);
    o->flags10 |= 0x41;
    o->flags0C &= ~0x20u;
}


typedef struct M1Hit84 { float v00[4], v10[4], v20[4], v30[4], v40[4]; } M1Hit84;
typedef struct M1Comp84 { uint8_t unk00[0x98]; float v98[4], vA8[4], vB8[4], vC8[4], vD8[4]; } M1Comp84;
typedef struct M1Obj84G { uint8_t unk000[0x64]; float y64; uint8_t unk068[0x11C - 0x68]; uint8_t coll11C[4]; } M1Obj84G;
M1Comp84 *sub_0001D960(void *o, int kind);
M1Hit84 *sub_0001B490(const float *a, const float *b, void *c, void *coll);
void sub_000F5D40(float *d, const float *s);

/* 0x00112C00: ground probe from a to b (0x1B490 with the object's collision +0x11C): on a hit
 * lift the object by the hit height over the higher end and copy the five hit vectors into
 * component 4 (+0x98); returns 1 on a hit. Spins without component 4. */
int m1_GroundProbe112C00(M1Obj84G *o, const float *a, const float *b, void *c)
{
    M1Comp84 *k = sub_0001D960(o, 4);
    M1Hit84 *hit;
    float dy;
    if (k == 0)
        for (;;) ;
    hit = sub_0001B490(a, b, c, o->coll11C);
    if (hit == 0)
        return 0;
    if (a[1] > b[1])
        dy = hit->v40[1] - a[1];
    else
        dy = hit->v40[1] - b[1];
    o->y64 += dy;
    sub_000F5D40(k->v98, hit->v00);
    sub_000F5D40(k->vA8, hit->v10);
    sub_000F5D40(k->vB8, hit->v20);
    sub_000F5D40(k->vC8, hit->v30);
    sub_000F5D40(k->vD8, hit->v40);
    return 1;
}

typedef struct M1Comp84R { uint8_t unk000[0x274]; float f274; } M1Comp84R;
typedef struct M1Step84R {
    uint8_t unk000[0x22];
    uint8_t b22;               /* +0x22 */
    uint8_t unk023[0x50 - 0x23];
    int32_t state50;           /* +0x50 */
    uint8_t unk054[0x270 - 0x54];
    float   f270;              /* +0x270 */
    float   f274;              /* +0x274 */
} M1Step84R;
typedef struct M1Obj84R { uint8_t unk00[8]; int32_t kind08; } M1Obj84R;
uint8_t *sub_000EDBE0(int a, int kind);
float sub_00113200(void *o, const void *pos);
float sub_001A3F30(float x);

/* 0x0011DC20: partner check for kinds 3 and 4: finds the other kind (0xEDBE0) with component 4,
 * and with h +0x22 bit 0 in states 5 or 6 returns 1 when both +0x274 values are within
 * +0x270 * lim[0..1] and the angle to the partner is within lim[2]. */
int m1_PartnerCheck11DC20(M1Obj84R *o, M1Step84R *h, const float *lim)
{
    int k;
    uint8_t *t;
    M1Comp84R *c;
    switch (o->kind08) {
    case 3:
        k = 4;
        break;
    case 4:
        k = 3;
        break;
    default:
        return 0;
    }
    t = sub_000EDBE0(2, k);
    if (t == 0)
        return 0;
    c = (M1Comp84R *)sub_0001D960(t, 4);
    if (c == 0)
        return 0;
    if (!(h->b22 & 1))
        return 0;
    if (h->state50 != 5 && h->state50 != 6)
        return 0;
    if (h->f274 > h->f270 * lim[0])
        return 0;
    if (c->f274 > lim[1] * h->f270)
        return 0;
    if (sub_001A3F30(sub_00113200(o, t + 0x60)) > lim[2])
        return 0;
    return 1;
}
