/* Area m1, file 71: frame builders. Names inferred. */
#include <stdint.h>

void sub_001AD7E0(float *out, const float *v);
void sub_000F5D40(float *dst, const float *src);
void sub_001ADA60(float *out, const float *a, const float *b);
void sub_001ADA40(void *node, const float *m);

/* 0x00145F70: gives node an upright frame facing along src's first row: x = unit(src x),
 * y = (0, 1, 0, 0), z = unit(x cross y), x = unit(y cross z), position = src row 3
 * (0x1ADA40). */
void m1_Upright145F70(void *node, const float *src)
{
    float up[4];
    float m[16];
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    sub_001AD7E0(m, src);
    sub_000F5D40(m + 4, up);
    sub_001ADA60(m + 8, m, m + 4);
    sub_001AD7E0(m + 8, m + 8);
    sub_001ADA60(m, m + 4, m + 8);
    sub_001AD7E0(m, m);
    sub_000F5D40(m + 12, src + 12);
    sub_001ADA40(node, m);
}

typedef struct M1Node30 { uint8_t unk00[0x30]; float pos30[4]; } M1Node30;
typedef struct M1Link20 { uint8_t unk00[0x20]; M1Node30 *node20; } M1Link20;
typedef struct M1StepG { uint8_t unk00[0x10]; M1Link20 *link10; } M1StepG;
typedef struct M1Hit40 { uint8_t unk00[0x40]; float pos40[4]; } M1Hit40;
typedef struct M1Scene54 { uint8_t unk00[0x54]; void *coll54; } M1Scene54;
extern M1Scene54 *m1_scene42C8E4;
void    *sub_00080970(void);
void     sub_000824F0(void *coll, void *w, const float *a, const float *b, int c, int d);
M1Hit40 *sub_00080CB0(void *w, const float *a, const float *b);

/* 0x00156440: places o (+0x30) where a ray from the linked node's position to 20 above it
 * hits the world (0x824F0, 0x80CB0), or at that upper point when nothing is hit. */
void m1_DropToNode156440(M1Node30 *o, M1StepG *h)
{
    float b[4];
    float a[4];
    M1Node30 *n = h->link10->node20;
    void *w;
    M1Hit40 *hit;
    if (n == 0)
        return;
    sub_000F5D40(a, n->pos30);
    sub_000F5D40(b, a);
    b[1] = b[1] + 20.0f;
    w = sub_00080970();
    sub_000824F0(m1_scene42C8E4->coll54, w, a, b, 0, 0);
    hit = sub_00080CB0(w, a, b);
    if (hit != 0)
        sub_000F5D40(o->pos30, hit->pos40);
    else
        sub_000F5D40(o->pos30, b);
}

typedef struct M1RigK {
    uint8_t unk000[8];
    uint32_t flags08;          /* +0x08 */
    uint8_t unk00C[0x160 - 0xC];
    float   q160[4];           /* +0x160 */
    uint8_t unk170[0x178 - 0x170];
    float   f178;              /* +0x178 */
    uint8_t unk17C[0x184 - 0x17C];
    int32_t snd184;            /* +0x184 */
} M1RigK;
typedef struct M1StepK3 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1RigK *rig278; } M1StepK3;
typedef struct M1ObjK3 { uint8_t unk00[0xC]; uint32_t flags0C, flags10; } M1ObjK3;
int  sub_001456E0(void *o, void *s, int a, int b);
void sub_0001D4E0(void *o);
int  sub_00048B20(int id, int v);

/* 0x00135F20: 0x1456E0(0x26) (0x1D4E0 on 1), rig quaternion +0x160 = (0, 0, 0, 1), o +0xC
 * clear 0xE0, o +0x10 |= 0x105, h +0x4C |= 0x70, rig flags 0x44; unless rig flag
 * 0x100000: rig +0x178 = 5 and sound 0x212 (0x48B20) into rig +0x184. */
void m1_RigIdle135F20(M1ObjK3 *o, M1StepK3 *h)
{
    M1RigK *r = h->rig278;
    M1RigK *p;
    uint32_t f;
    if (sub_001456E0(o, h, 0x26, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q160[2] = 0.0f;
    p->q160[1] = 0.0f;
    p->q160[0] = 0.0f;
    p->q160[3] = 1.0f;
    o->flags0C &= ~0xE0u;
    o->flags10 |= 0x105;
    h->flags4C |= 0x70;
    f = r->flags08 | 0x44;
    r->flags08 = f;
    if (!(f & 0x100000)) {
        r->f178 = 5.0f;
        r->snd184 = sub_00048B20(0x212, 0);
    }
}
