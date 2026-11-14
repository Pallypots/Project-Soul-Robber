/* Area m1, file 114. Names inferred. */
#include <stdint.h>

typedef struct M1Part114 { uint8_t unk00[0x70]; float v70[4]; } M1Part114;
typedef struct M1Obj114M {
    uint8_t unk00[0x20];
    float  *m20;               /* +0x20 */
    uint8_t unk24[0x34 - 0x24];
    M1Part114 *p34;            /* +0x34 */
    uint8_t unk38[0x60 - 0x38];
    float   pos60[4];          /* +0x60 */
    float   scale70[4];        /* +0x70 */
    float   vel80[4];          /* +0x80 */
} M1Obj114M;
typedef struct M1Step114M { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x78 - 0x50]; float v78[4]; } M1Step114M;
void sub_001AD940(float *m);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_000F5D40(float *d, const float *s);

/* 0x00145E10: move with offsets (scaled variant of 0x166E20): the part +0x70 offset through
 * the scaled rotation (none while flag 0x200), plus position, pending +0x80 push (cleared)
 * and the step +0x78 velocity, written back as the new position. */
void m1_MoveApply145E10(M1Obj114M *o, M1Step114M *h)
{
    struct { float v[4]; float m[16]; } l;
    sub_001AD940(l.m);
    l.m[0] = o->scale70[0];
    l.m[5] = o->scale70[1];
    l.m[10] = o->scale70[2];
    sub_001AD7C0(l.m, l.m, o->m20);
    l.m[12] = 0.0f;
    l.m[13] = 0.0f;
    l.m[14] = 0.0f;
    l.m[15] = 1.0f;
    if (h->flags4C & 0x200) {
        l.v[0] = 0.0f;
        l.v[1] = 0.0f;
        l.v[2] = 0.0f;
        l.v[3] = 1.0f;
    } else {
        sub_001AD9B0(l.v, l.m, o->p34->v70);
    }
    sub_001ADAF0(l.v, o->pos60, l.v);
    sub_001ADAF0(l.v, l.v, o->vel80);
    o->vel80[0] = 0.0f;
    o->vel80[1] = 0.0f;
    o->vel80[2] = 0.0f;
    o->vel80[3] = 1.0f;
    sub_001ADAF0(l.v, l.v, h->v78);
    l.v[3] = 1.0f;
    sub_000F5D40(o->pos60, l.v);
}

typedef struct M1Pl114 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl114;
typedef struct M1Cmd114 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd114;
typedef struct M1Rig114A { uint8_t unk000[0xC]; uint8_t b0C; uint8_t unk00D[0x164 - 0xD]; float q164[4]; uint8_t unk174[0x184 - 0x174]; float spin184; } M1Rig114A;
typedef struct M1Step114A { uint8_t unk000[0x278]; M1Rig114A *rig278; } M1Step114A;
typedef struct M1Obj114A { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x20 - 0x14]; float *m20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Obj114A;
extern M1Pl114 *g_playerObj;
int  sub_001C7EE1(void);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001ADA60(float *out, const float *a, const float *b);
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_0001D4E0(void *o);
M1Cmd114 *sub_00113400(void *h, int v);

/* 0x0012F170: spin hit: with a spin rate (+0x184) one time in four turn to face along the
 * player direction (matrix rebuilt upright); state 0x10, reset the rig quaternion, o flags
 * 0x105 when rig bit 0 is set, and spin command 6 at +0x184 when positive. */
void m1_SpinHit12F170(M1Obj114A *o, M1Step114A *h)
{
    M1Rig114A *r = h->rig278;
    M1Rig114A *p;
    M1Cmd114 *c;
    float d[4];
    float t;
    if (r->spin184 > 0.0f && !(sub_001C7EE1() & 3)) {
        sub_001AD9F0(d, g_playerObj->pos60, o->pos60);
        d[1] = 0.0f;
        sub_001AD7E0(d, d);
        sub_001ADBA0(o->m20 + 8, d, -1.0f);
        o->m20[7] = 0.0f;
        o->m20[6] = 0.0f;
        o->m20[4] = 0.0f;
        o->m20[5] = 1.0f;
        sub_001ADA60(o->m20, o->m20 + 4, o->m20 + 8);
    }
    if (sub_001456E0(o, h, 0x10, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q164[2] = 0.0f;
    p->q164[1] = 0.0f;
    p->q164[0] = 0.0f;
    p->q164[3] = 1.0f;
    if (r->b0C & 1)
        o->flags10 |= 0x105;
    if (r->spin184 > 0.0f) {
        o->flags10 |= 4;
        t = r->spin184;
        c = sub_00113400(h, 6);
        if (t != -1.0f)
            c->f10 = t;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
    }
}

typedef struct M1Step114V { uint8_t unk00[0x78]; float vel78[4]; } M1Step114V;
typedef struct M1Obj114V {
    uint8_t unk000[0x60];
    float   pos60[4];          /* +0x60 */
    uint8_t unk070[0x80 - 0x70];
    float   push80[4];         /* +0x80 */
    uint8_t unk090[0xDC - 0x90];
    float   floorDC;           /* +0xDC */
    uint8_t unk0E0[0xFC - 0xE0];
    float   heightFC;          /* +0xFC */
    uint8_t unk100[0x128 - 0x100];
    uint8_t b128;              /* +0x128 */
} M1Obj114V;
extern float m1_frameRate42C85C;
void sub_001ADBA0(float *d, const float *s, float k);

/* 0x0017AA60: fall step: gravity 196 * frameRate on +0x7C, horizontal speed +0x78/+0x80 eased
 * toward 0 by friction (8 on the ground, 0.8 in the air, times 10 * frameRate), move by the
 * velocity and the pending +0x80 push (cleared), drop vertical speed on landing, and store the
 * height above the floor in +0xFC. */
void m1_FallStep17AA60(M1Obj114V *o, M1Step114V *h)
{
    float t[4];
    float k = 0.800000012f;
    float *v;
    float x;
    if (o->b128 & 0x18)
        k = 8.0f;
    h->vel78[1] += m1_frameRate42C85C * 196.0f;
    v = &h->vel78[0];
    if (*v > 0.0f) {
        x = *v - k * 10.0f * m1_frameRate42C85C;
        *v = x;
        if (0.0f > x)
            *v = 0.0f;
    } else if (0.0f > *v) {
        x = k * 10.0f * m1_frameRate42C85C + *v;
        *v = x;
        if (x > 0.0f)
            *v = 0.0f;
    }
    if (h->vel78[2] > 0.0f) {
        x = h->vel78[2] - k * 10.0f * m1_frameRate42C85C;
        h->vel78[2] = x;
        if (0.0f > x)
            h->vel78[2] = 0.0f;
    } else if (0.0f > h->vel78[2]) {
        x = k * 10.0f * m1_frameRate42C85C + h->vel78[2];
        h->vel78[2] = x;
        if (x > 0.0f)
            h->vel78[2] = 0.0f;
    }
    sub_001ADBA0(t, v, m1_frameRate42C85C);
    sub_001ADAF0(o->pos60, o->pos60, t);
    if (o->b128 & 0x18)
        h->vel78[1] = 0.0f;
    sub_001ADAF0(o->pos60, o->pos60, o->push80);
    o->push80[0] = 0.0f;
    o->push80[1] = 0.0f;
    o->push80[2] = 0.0f;
    o->push80[3] = 1.0f;
    o->pos60[3] = 1.0f;
    o->heightFC = o->floorDC - t[1];
}

typedef struct M1Node114 { float m00[16]; float pos40[4]; uint8_t unk50[0x70 - 0x50]; float wpos70[4]; uint8_t unk80[0x90 - 0x80]; uint32_t flags90; uint8_t unk94[0x108 - 0x94]; } M1Node114;
typedef struct M1Mdl114 { uint8_t unk00[0xC0]; int32_t n0C0; uint8_t *nodes0C4; } M1Mdl114;
typedef struct M1Obj114N { uint8_t unk00[0x20]; M1Mdl114 *mdl20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Obj114N;
extern float m1_frameTime42C858;
void sub_001B2890(float *m, const float *axis, float a);
int  sub_000494D0(int id, const void *pos, int c);

/* 0x0016FF30: burst apart: every node after the root gets flag 0x40 and flies off along its
 * direction from the root (dropped by 2, 0.6 * frameTime), spinning about the cross axis at
 * 10 degrees * frameTime (matrix rows rebuilt); then sound 0x78. */
void m1_BurstApart16FF30(M1Obj114N *o)
{
    M1Mdl114 *m = o->mdl20;
    float up[4];
    float d[4];
    float ax[4];
    float q[16];
    const float *root;
    M1Node114 *e;
    int i, off;
    up[0] = 0.0f;
    up[1] = -1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    if (m->n0C0 > 1) {
        root = (float *)(m->nodes0C4 + 0x70);
        for (i = 1, off = 0x108; i < m->n0C0; i++, off += 0x108) {
            e = (M1Node114 *)(m->nodes0C4 + off);
            e->flags90 |= 0x40;
            sub_001AD9F0(d, e->wpos70, root);
            sub_001AD7E0(d, d);
            d[1] = -2.0f;
            sub_001ADBA0(d, d, m1_frameTime42C858 * 0.600000024f);
            d[3] = 1.0f;
            sub_001ADA60(ax, d, up);
            sub_001B2890(q, ax, m1_frameTime42C858 * 0.174532935f);
            sub_000F5D40(e->m00, q);
            sub_000F5D40(e->m00 + 4, q + 4);
            sub_000F5D40(e->m00 + 8, q + 8);
            sub_000F5D40(e->m00 + 12, d);
        }
    }
    sub_000494D0(0x78, o->pos60, 0);
}

typedef struct M1Rig114B { uint8_t unk00[0x2C]; float q2C[4]; uint8_t unk3C[0x48 - 0x3C]; float spin48; } M1Rig114B;
typedef struct M1Step114B { uint8_t unk000[0x278]; M1Rig114B *rig278; } M1Step114B;

/* 0x00115A30: spin hit (as 0x12F170 for this rig layout): one time in four face along the
 * player direction while spinning, state 0x10, reset the quaternion at +0x2C, and spin
 * command 4 at +0x48 when positive. */
void m1_SpinHit115A30(M1Obj114A *o, M1Step114B *h)
{
    M1Rig114B *r = h->rig278;
    M1Rig114B *p;
    M1Cmd114 *c;
    float d[4];
    float t;
    if (r->spin48 > 0.0f && !(sub_001C7EE1() & 3)) {
        sub_001AD9F0(d, g_playerObj->pos60, o->pos60);
        d[1] = 0.0f;
        sub_001AD7E0(d, d);
        sub_001ADBA0(o->m20 + 8, d, -1.0f);
        o->m20[7] = 0.0f;
        o->m20[6] = 0.0f;
        o->m20[4] = 0.0f;
        o->m20[5] = 1.0f;
        sub_001ADA60(o->m20, o->m20 + 4, o->m20 + 8);
    }
    if (sub_001456E0(o, h, 0x10, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q2C[2] = 0.0f;
    p->q2C[1] = 0.0f;
    p->q2C[0] = 0.0f;
    p->q2C[3] = 1.0f;
    if (r->spin48 > 0.0f) {
        o->flags10 |= 4;
        t = r->spin48;
        c = sub_00113400(h, 4);
        if (t != -1.0f)
            c->f10 = t;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1C = 0.0f;
    }
}

typedef struct M1Rig114D {
    uint8_t unk00[0xC];
    float   f0C, f10;          /* +0x0C */
    uint8_t unk14[0x24 - 0x14];
    float   f24, f28, f2C, f30;  /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
    uint8_t unk44[0x60 - 0x44];
    float   f60;               /* +0x60 */
} M1Rig114D;
typedef struct M1Step114D {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x104 - 0x50];
    M1Pl114 *tgt104;           /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig114D *rig278;         /* +0x278 */
} M1Step114D;
typedef struct M1Obj114D { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[4]; } M1Obj114D;
float sub_001B2770(const float *a, const float *b);

/* 0x00157CE0: side dodge: by the distance to the target (alt flag: 40, else 30) dodge one way
 * (state 0x41) or the other (0x40) at 50 or 35 times frameRate, rig decay 0.005, flags, rig
 * flag 0x40000, +0x60 = 1, and a 5-degree sway at 5 degrees/frame. */
void m1_Dodge157CE0(M1Obj114D *o, M1Step114D *h)
{
    M1Rig114D *r = h->rig278;
    M1Cmd114 *c;
    float d = sub_001B2770(o->pos60, h->tgt104->pos60);
    float f;
    float t;
    if (h->b20 & 1) {
        if (d >= 40.0f) {
            sub_001456E0(o, h, 0x41, 0);
            f = m1_frameRate42C85C * 50.0f;
        } else {
            sub_001456E0(o, h, 0x40, 0);
            f = 0.0f - m1_frameRate42C85C * 50.0f;
        }
        t = m1_frameTime42C858 * 0.0872664675f;
    } else {
        if (d >= 30.0f) {
            sub_001456E0(o, h, 0x41, 0);
            f = m1_frameRate42C85C * 35.0f;
        } else {
            sub_001456E0(o, h, 0x40, 0);
            f = 0.0f - m1_frameRate42C85C * 35.0f;
        }
        t = m1_frameTime42C858 * 0.0872664675f;
    }
    r->f2C = 0.0f - f;
    r->f28 = 0.0f;
    r->f24 = 0.0f;
    r->f30 = 1.0f;
    r->f10 = 0.0f;
    r->f0C = m1_frameTime42C858 * 0.00499999989f;
    o->flags10 |= 0x20;
    h->flags4C |= 0x70;
    r->flags40 |= 0x40000;
    r->f60 = 1.0f;
    c = sub_00113400(h, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}
