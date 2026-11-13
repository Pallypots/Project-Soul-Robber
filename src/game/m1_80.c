/* Area m1, file 80: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1Cmd80I { uint8_t unk00[0x10]; int32_t i10, i14; } M1Cmd80I;
typedef struct M1Cmd80 { uint8_t unk00[0x10]; float f10; } M1Cmd80;
typedef struct M1Step80 { uint8_t unk00[0x74]; float wait74; } M1Step80;
void *sub_00113400(void *h, int v);
void *sub_001133E0(void *h, int v);
int  sub_0017AE00(void);
void *sub_00036750(void *o, int b);
int  sub_000494D0(int id, const void *pos, int c);
void sub_0005EB10(int a, int b);
void sub_00113040(void *o, void *h, int state);

/* 0x0017B9A0: command 2 holds a count; when empty refill it from 0x17AE00 (with effect, sound
 * 0x59 and 0x5EB10(0, 3)); when the wait ran out go to state 6 (count left, command 3 = 0)
 * or state 3 with a 2 s wait. */
void m1_Refill17B9A0(uint8_t *o, M1Step80 *h)
{
    M1Cmd80I *c = (M1Cmd80I *)sub_00113400(h, 2);
    int n;
    if (c->i10 <= 0) {
        c->i14 = -1;
        n = sub_0017AE00();
        if (n > 0) {
            c->i10 = n;
            c->i14 = -1;
            sub_00036750(o, 0);
            sub_000494D0(0x59, o + 0x60, 0);
            sub_0005EB10(0, 3);
        }
    }
    if (0.0f >= h->wait74) {
        if (c->i10 > 0) {
            sub_00113040(o, h, 6);
            ((M1Cmd80 *)sub_001133E0(h, 3))->f10 = 0.0f;
        } else {
            sub_00113040(o, h, 3);
            h->wait74 = 2.0f;
        }
    }
}

typedef struct M1Rig80 { uint8_t unk00[0x20]; float v20[4]; } M1Rig80;
typedef struct M1StepA80 { uint8_t unk000[0x278]; M1Rig80 *rig278; } M1StepA80;
typedef struct M1Obj80 { uint8_t unk00[0x20]; void *node20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Obj80;
extern void *g_playerObj;
void sub_00145F40(void *o, int bone, float *m);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AE060(float *m, const void *node);
void sub_001AD9B0(float *d, const float *m, const float *v);

/* 0x00188690: aim at the player's bone 0x27: rig +0x20 = (bone position - object position)
 * in the object's local frame, w = 1. */
void m1_AimBone188690(M1Obj80 *o, M1StepA80 *h)
{
    float out[4];
    float d[4];
    float m[16];
    float inv[16];
    M1Rig80 *r;
    sub_00145F40(g_playerObj, 0x27, m);
    sub_001AD9F0(d, &m[12], o->pos60);
    sub_001AE060(inv, o->node20);
    sub_001AD9B0(out, inv, d);
    r = h->rig278;
    r->v20[2] = 0.0f - (0.0f - out[2]);
    r->v20[1] = out[1];
    r->v20[0] = out[0];
    r->v20[3] = 1.0f;
}

typedef struct M1Ctx80 { uint8_t unk00[0x54]; void *coll54; } M1Ctx80;
extern M1Ctx80 *a80_ctx42C8E4;
typedef struct M1Node80 { uint8_t unk00[0x30]; float pos30[4]; } M1Node80;
typedef struct M1Mdl80 { uint8_t unk00[0x20]; M1Node80 *node20; } M1Mdl80;
typedef struct M1Src80 { uint8_t unk00[0x10]; M1Mdl80 *mdl10; } M1Src80;
typedef struct M1Hit80 { uint8_t unk00[0x40]; float pos40[4]; } M1Hit80;
void sub_000F5D40(float *d, const float *s);
void *sub_00080970(void);
void sub_000824F0(void *coll, void *w, const float *a, const float *b, int c, int d);
M1Hit80 *sub_00080CB0(void *w, const float *a, const float *b);

/* 0x00188DD0: snap to the ground under the source's node: cast from the node position to
 * the same point at height 1000; on a hit copy the hit position to +0x30 and +0x70. */
void m1_SnapGround188DD0(uint8_t *a, M1Src80 *b)
{
    float from[4];
    float to[4];
    M1Node80 *n;
    void *w;
    M1Hit80 *hit;
    if (a == 0 || b == 0 || (n = b->mdl10->node20) == 0)
        return;
    sub_000F5D40(from, n->pos30);
    sub_000F5D40(to, from);
    to[1] = 1000.0f;
    w = sub_00080970();
    sub_000824F0(a80_ctx42C8E4->coll54, w, from, to, 0, 0);
    hit = sub_00080CB0(w, from, to);
    if (hit != 0) {
        sub_000F5D40((float *)(a + 0x30), hit->pos40);
        sub_000F5D40((float *)(a + 0x70), hit->pos40);
    }
}

typedef struct M1RigOr { uint8_t unk00[0x40]; uint8_t b40; uint8_t unk41[0x64 - 0x41]; float c64[4]; } M1RigOr;
typedef struct M1StepOr { uint8_t unk000[0x278]; M1RigOr *rig278; } M1StepOr;
typedef struct M1DataOr { uint8_t unk00[0x10]; float radius10; int32_t i14; } M1DataOr;
void sub_001AD7E0(float *out, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_00145C50(float *d, const float *s, float a);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_001459D0(void *o, float x, float z, int k);

/* 0x00155610: orbit: flat direction from the rig centre +0x64 to the object, scaled to the
 * radius, turned 5 degrees (direction by rig +0x40 bit 0), placed back around the centre and
 * passed to 0x1459D0 as the new x/z target. */
void m1_Orbit155610(uint8_t *o, M1StepOr *h, M1DataOr *d)
{
    M1RigOr *r = h->rig278;
    float *c = r->c64;
    float v[4];
    float t[4];
    sub_001AD9F0(v, (const float *)(o + 0x60), c);
    v[1] = 0.0f;
    sub_001AD7E0(v, v);
    sub_001ADBA0(v, v, d->radius10);
    sub_00145C50(t, v, (r->b40 & 1) ? 0.087266468f : -0.087266468f);
    sub_001ADAF0(v, t, c);
    sub_001459D0(o, v[0], v[2], d->i14);
}
