/* Area m1, file 113. Names inferred. */
#include <stdint.h>

extern float m1_frameRate42C85C;

typedef struct M1Rig113F { uint8_t unk00[0x10]; float t10; int32_t armed14; uint8_t unk18[0x44 - 0x18]; float v44[4]; } M1Rig113F;
typedef struct M1Step113F { uint8_t unk000[0x278]; M1Rig113F *rig278; } M1Step113F;
typedef struct M1Obj113F { uint8_t unk000[0x130]; int32_t i130; } M1Obj113F;
void *sub_0001D0F0(void *o, int part);
void sub_000F5D40(float *d, const float *s);
void *sub_00035DD0(void *o, int a, int b, int c);
void sub_00033880(void *fx, float *m);
void sub_00034E00(void *fx, const float *pos, const float *dir, const float *up);
int  m1_AimPoint17D5C0(void *a, void *b, void *c, float *out);

/* 0x0017FBE0: gun step: arm after 0.04 s, then every 29 frames fire: muzzle effect 3 at the
 * rig +0x44 point, aim along the segment from part 9 to that point (0x17D5C0) and, when it
 * finds a point, the impact effect 4 there. */
void m1_GunStep17FBE0(M1Obj113F *o, M1Step113F *h)
{
    struct { float up[4]; float hit[4]; float muzzle[4]; float seg[2][4]; float m[16]; } l;
    M1Rig113F *r = h->rig278;
    void *fx;
    sub_000F5D40(l.muzzle, (float *)((uint8_t *)sub_0001D0F0(o, 9) + 0x70));
    if (r->armed14 == 0) {
        if (r->t10 > 0.0399999991f) {
            r->armed14 = 1;
        } else {
            r->t10 += m1_frameRate42C85C;
            return;
        }
    } else if (!(r->t10 > m1_frameRate42C85C * 29.0f)) {
        r->t10 += m1_frameRate42C85C;
        return;
    }
    r->t10 = 0.0f;
    l.up[0] = 0.0f;
    l.up[1] = 1.0f;
    l.up[2] = 0.0f;
    l.up[3] = 1.0f;
    fx = sub_00035DD0(o, o->i130, 3, 3);
    sub_00033880(fx, l.m);
    sub_00034E00(fx, r->v44, &l.m[8], l.up);
    sub_000F5D40(l.seg[0], l.muzzle);
    sub_000F5D40(l.seg[1], r->v44);
    if (m1_AimPoint17D5C0(o, l.seg, 0, l.hit) == -1)
        return;
    fx = sub_00035DD0(o, o->i130, 4, 3);
    sub_00033880(fx, l.m);
    sub_00034E00(fx, l.hit, &l.m[8], l.up);
}

typedef struct M1Pl113 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl113;
typedef struct M1Cmd113 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd113;
typedef struct M1Rig113A {
    uint8_t unk00[0x18];
    uint32_t flags18;          /* +0x18 */
    uint8_t unk1C[4];
    float   q20[4];            /* +0x20 */
    uint8_t unk30[0x88 - 0x30];
    float   cur88, goal8C, step90; /* +0x88 */
    uint8_t unk94[0x9C - 0x94];
    float   f9C;               /* +0x9C */
} M1Rig113A;
typedef struct M1Step113A { uint8_t unk000[0x278]; M1Rig113A *rig278; } M1Step113A;
typedef struct M1Obj113A { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x20 - 0x14]; float *m20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Obj113A;
extern M1Pl113 *g_playerObj;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001ADA60(float *out, const float *a, const float *b);
M1Cmd113 *sub_00113400(void *h, int v);
int  sub_00036750(void *o, int v);

/* 0x001878E0: turn away: state 0x31, face away from the player on the flat plane (matrix
 * rebuilt upright), rig turn to 25 from 0 at 0.5 * frameTime, +0x9C = -150 * frameRate, reset the
 * quaternion, then a 0.1 spin command 6 (pending rig flag 0x40, o flag 4) or pose 1. */
void m1_TurnAway1878E0(M1Obj113A *o, M1Step113A *h)
{
    M1Rig113A *r = h->rig278;
    M1Rig113A *p;
    M1Cmd113 *c;
    float d[4];
    sub_001456E0(o, h, 0x31, 0);
    sub_001AD9F0(d, o->pos60, g_playerObj->pos60);
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(o->m20 + 8, d, -1.0f);
    o->m20[7] = 0.0f;
    o->m20[6] = 0.0f;
    o->m20[4] = 0.0f;
    o->m20[5] = 1.0f;
    sub_001ADA60(o->m20, o->m20 + 4, o->m20 + 8);
    r->goal8C = 25.0f;
    r->cur88 = 0.0f;
    r->step90 = m1_frameTime42C858 * 0.5f;
    r->f9C = m1_frameRate42C85C * -150.0f;
    p = h->rig278;
    p->q20[2] = 0.0f;
    p->q20[1] = 0.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    if (r->flags18 & 0x40) {
        r->flags18 &= ~0x40u;
        o->flags10 |= 4;
        c = sub_00113400(h, 6);
        c->f10 = 0.100000001f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        return;
    }
    sub_00036750(o, 1);
}
