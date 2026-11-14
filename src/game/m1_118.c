/* Area m1, file 118. Names inferred. */
#include <stdint.h>

typedef struct M1Ent118 { uint32_t flags00; int32_t kind04; uint8_t unk08[4]; uint8_t b0C; uint8_t unk0D[0x60 - 0xD]; float pos60[4]; } M1Ent118;
typedef struct M1Rig118 { uint32_t unk00; uint32_t flags04; } M1Rig118;
typedef struct M1Step118 {
    uint8_t unk000[0xF8];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    M1Ent118 *tgt104;          /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig118 *rig278;          /* +0x278 */
} M1Step118;
typedef struct M1Obj118 { uint8_t unk00[0x60]; float pos60[4]; } M1Obj118;
extern M1Ent118 *g_playerObj;
M1Ent118 *sub_000C7130(void *o);
M1Ent118 *sub_000C7280(M1Ent118 *e);
int  sub_00145940(void *o, float x, float z, float lo, float hi);
float sub_001B2770(const float *a, const float *b);

/* 0x0011E260: target pick: in chase mode (rig flag 0x800) fall back to the player when the
 * target is gone, and while targeting the player (kind 0xD) switch to a nearby decoy in the
 * 90-degree front cone (or back to the player from it); otherwise target whichever of the
 * player and the decoy is nearer, the decoy only within 60. Rig flag 0x1000 marks a change. */
void m1_PickTarget11E260(M1Obj118 *o, M1Step118 *h)
{
    M1Rig118 *r = h->rig278;
    M1Ent118 *e;
    M1Ent118 *x;
    M1Ent118 *p;
    M1Ent118 *t;
    float dp, de;
    uint32_t f = r->flags04 & ~0x1000u;
    r->flags04 = f;
    if (f & 0x800) {
        if (h->mode0F8 == 1 && (h->tgt104 == 0 || !(h->tgt104->b0C & 1))) {
            r->flags04 = f | 0x1000;
            h->tgt104 = g_playerObj;
            h->mode0F8 = 1;
        }
        if (h->mode0F8 != 1)
            return;
        t = h->tgt104;
        if (!(t->b0C & 1) || t->kind04 != 0xD)
            return;
        e = sub_000C7130(o);
        if (e) {
            if (e == h->tgt104) {
                r->flags04 |= 0x1000;
                h->tgt104 = g_playerObj;
                h->mode0F8 = 1;
                return;
            }
            if (sub_00145940(o, e->pos60[0], e->pos60[2], -0.785398185f, 0.785398185f)) {
                r->flags04 |= 0x1000;
                h->tgt104 = e;
                h->mode0F8 = 1;
            }
            return;
        }
        x = sub_000C7280(e);
        if (x && (x->flags00 & 0x20000000)) {
            r->flags04 |= 0x1000;
            h->tgt104 = g_playerObj;
            h->mode0F8 = 1;
        }
        return;
    }
    p = g_playerObj;
    e = sub_000C7130(o);
    if (p)
        dp = sub_001B2770(o->pos60, p->pos60);
    else
        dp = 3.40282347e+38f;
    t = p;
    if (e && sub_00145940(o, e->pos60[0], e->pos60[2], -0.785398185f, 0.785398185f) == 1) {
        de = sub_001B2770(o->pos60, e->pos60);
        if (60.0f >= de && dp >= de)
            t = e;
    }
    if (h->tgt104 == t && h->mode0F8 == 1)
        return;
    h->tgt104 = t;
    h->mode0F8 = 1;
    r->flags04 |= 0x1000;
}

typedef struct M1V4 { float x, y, z, w; } M1V4;
typedef struct M1Part118 { uint8_t unk00[0x70]; float v70[4]; } M1Part118;
typedef struct M1Mdl118 { uint8_t unk00[0x74]; float y74; uint8_t unk78[0xC4 - 0x78]; uint8_t *nodes0C4; } M1Mdl118;
typedef struct M1Rig118F { uint32_t unk00; uint32_t flags04; int32_t node08; int32_t node0C; float dy10; } M1Rig118F;
typedef struct M1Step118F { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x78 - 0x50]; float vel78[4]; uint8_t unk088[0x278 - 0x88]; M1Rig118F *rig278; } M1Step118F;
typedef struct M1Obj118F {
    uint8_t unk000[0x20];
    M1Mdl118 *mdl20;           /* +0x20 */
    uint8_t unk024[0x34 - 0x24];
    M1Part118 *p34;            /* +0x34 */
    uint8_t unk038[0x54 - 0x38];
    float   yaw54;             /* +0x54 */
    uint8_t unk058[0x60 - 0x58];
    M1V4    pos60;             /* +0x60 */
    float   scale70;           /* +0x70 */
    uint8_t unk074[0x80 - 0x74];
    float   push80[4];         /* +0x80 */
    uint8_t unk090[0xA0 - 0x90];
    float   off0A0[4];         /* +0xA0 */
    float   fB0, fB4;          /* +0xB0 */
    uint8_t unk0B8[0xD8 - 0xB8];
    float   fD8, fDC, fE0;     /* +0xD8 */
    uint8_t unk0E4[0xFC - 0xE4];
    float   heightFC;          /* +0xFC */
    uint8_t unk100[0x128 - 0x100];
    uint8_t b128;              /* +0x128 */
} M1Obj118F;
extern float m1_frameRate42C85C;
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001ADB60(float *d, const float *s, float k);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_0001EF00(void *o, const float *v);

/* 0x00137C70: ridden fall step: carry the object by its part offset (yaw-rotated, scaled by
 * +0x70) unless flag 0x200, then the 0x17AA60 fall/friction step (gravity skipped once on rig
 * flag 0x100000, speeds cleared on walls), and re-centre the collider on node +0x08 with the
 * height offset from node +0x0C. */
void m1_RideFall137C70(M1Obj118F *o, M1Step118F *h)
{
    M1Rig118F *r = h->rig278;
    M1Mdl118 *mdl = o->mdl20;
    float m[16];
    float v[4];
    float t[4];
    float c[4];
    float k;
    float *p;
    float x;
    M1V4 q;
    if (!(h->flags4C & 0x200)) {
        sub_001AD940(m);
        sub_001AD8E0(m, m, o->yaw54);
        sub_001AD9B0(v, m, o->p34->v70);
        sub_001ADB60(v, v, o->scale70);
        q = o->pos60;
        q.x += v[0];
        q.y += v[1];
        q.z += v[2];
        o->pos60 = q;
    }
    k = 0.800000012f;
    if (o->b128 & 0x18)
        k = 8.0f;
    if (!(r->flags04 & 0x100000))
        h->vel78[1] += m1_frameRate42C85C * 196.0f;
    r->flags04 &= ~0x100000u;
    p = &h->vel78[0];
    if (*p > 0.0f) {
        x = *p - k * 10.0f * m1_frameRate42C85C;
        *p = x;
        if (0.0f > x)
            *p = 0.0f;
    } else if (0.0f > *p) {
        x = k * 10.0f * m1_frameRate42C85C + *p;
        *p = x;
        if (x > 0.0f)
            *p = 0.0f;
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
    sub_001ADBA0(t, p, m1_frameRate42C85C);
    sub_001ADAF0(&o->pos60.x, &o->pos60.x, t);
    if (o->b128 & 0x18)
        h->vel78[1] = 0.0f;
    if (o->b128 & 6) {
        h->vel78[0] = 0.0f;
        h->vel78[2] = 0.0f;
    }
    sub_001ADAF0(&o->pos60.x, &o->pos60.x, o->push80);
    o->push80[0] = 0.0f;
    o->push80[1] = 0.0f;
    o->push80[2] = 0.0f;
    o->push80[3] = 1.0f;
    o->pos60.w = 1.0f;
    sub_001AD9F0(o->off0A0, (float *)(mdl->nodes0C4 + r->node08 * 0x180 + 0x70), &o->pos60.x);
    o->off0A0[1] = 0.0f;
    x = o->off0A0[0];
    o->fB4 = *(float *)(mdl->nodes0C4 + r->node0C * 0x180 + 0x74) - mdl->y74 + r->dy10;
    o->fD8 = x * 0.5f;
    o->fE0 = o->off0A0[2] * 0.5f;
    o->heightFC = o->fDC - t[1];
    sub_001ADB60(c, o->off0A0, 0.5f);
    sub_0001EF00(o, c);
}
