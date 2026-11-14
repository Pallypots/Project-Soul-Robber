/* Area m1, file 126: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Ent126 { uint8_t unk00[0xC]; uint32_t flags0C; } M1Ent126;
typedef struct M1Slot126 {
    uint32_t flags00;          /* +0x00 */
    float   f04, f08, f0C;     /* +0x04 */
    int32_t a10;               /* +0x10 */
    float   v14[4];            /* +0x14 */
    float   v24[4];            /* +0x24 */
    uint8_t unk34[0xE8 - 0x34];
    M1Ent126 *ent0E8;          /* +0xE8 */
} M1Slot126;
extern M1Slot126 m1_slots41D020[20];
void sub_0001EB80(void *e);

/* 0x000C73B0: get a slot from the 20 at 0x41D020: the first free one (no flags 0x80000001),
 * or the first marked reusable (0x40000000), which is released and reset. Returns its index,
 * -1 when none. */
int m1_SlotGet0C73B0(void)
{
    M1Slot126 *r;
    int i;
    for (r = m1_slots41D020, i = 0; (int)r < (int)(m1_slots41D020 + 20); r++, i++) {
        if (!(r->flags00 & 0x80000001))
            return i;
        if (r->flags00 & 0x40000000)
            goto reuse;
    }
    return -1;
reuse:
    r->ent0E8->flags0C &= ~1u;
    sub_0001EB80(r->ent0E8);
    r->flags00 = 0;
    r->f04 = 0.0f;
    r->f08 = 1.0f;
    r->f0C = 0.0f;
    r->a10 = 0;
    r->v14[2] = 0.0f;
    r->v14[1] = 0.0f;
    r->v14[0] = 0.0f;
    r->v24[2] = 0.0f;
    r->v24[1] = 0.0f;
    r->v24[0] = 0.0f;
    r->v24[3] = 1.0f;
    r->v14[3] = 1.0f;
    r->ent0E8 = 0;
    return i;
}

void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001ADAF0(float *d, const float *a, const float *b);

/* 0x000C48A0: place c at distance k from a toward b, and give d the flat unit direction from b
 * to a (all w set to 1). */
void m1_PlaceToward0C48A0(float *a, float *b, float *c, float *d, float k)
{
    float t[4];
    t[0] = 0.0f;
    t[1] = 0.0f;
    t[2] = 0.0f;
    d[3] = 1.0f;
    c[3] = 1.0f;
    b[3] = 1.0f;
    t[3] = 1.0f;
    a[3] = 1.0f;
    sub_001AD9F0(t, b, a);
    sub_001AD7E0(t, t);
    sub_001ADBA0(t, t, k);
    sub_001ADAF0(c, a, t);
    sub_001AD9F0(d, a, b);
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    d[3] = 1.0f;
}

typedef struct M1Lit126 { uint8_t unk000[0xFAC]; float fFAC; float colFB0[4]; float colFC0[4]; } M1Lit126;
typedef struct M1Sc2_126 { uint8_t unk000[0x3B0]; void *light3B0; } M1Sc2_126;
extern M1Sc2_126 *m1_scene2_42C8EC;
extern float m1_col418B30[3];
void sub_000F5D40(float *d, const float *s);
void sub_000D04E0(void *o, const float *v);
void sub_000C9FB0(void *o, const float *c);
float sub_00171B40(void *o);

/* 0x000CA600: apply the base light colour (128, 128, 128, 70) to both light slots, push it to
 * the scene light, publish it to 0x418B30, apply it (0xC9FB0) and refresh +0xFAC. */
void m1_LightApply0CA600(M1Lit126 *o)
{
    void *g = m1_scene2_42C8EC->light3B0;
    float v[4];
    float *c;
    v[0] = 128.0f;
    v[1] = 128.0f;
    v[2] = 128.0f;
    v[3] = 70.0f;
    sub_000F5D40(o->colFB0, v);
    c = o->colFC0;
    sub_000F5D40(c, v);
    sub_000D04E0(g, o->colFB0);
    sub_000F5D40(c, o->colFB0);
    m1_col418B30[0] = c[0];
    m1_col418B30[1] = c[1];
    m1_col418B30[2] = c[2];
    sub_000C9FB0(o, c);
    o->fFAC = sub_00171B40(o);
}
