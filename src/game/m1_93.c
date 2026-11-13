/* Area m1, file 93: sway and attach steps. Names inferred. */
#include <stdint.h>

typedef struct M1Rig93 { uint8_t unk000[8]; int8_t b08; uint8_t unk009[3]; uint8_t unk00C[0x160 - 0xC]; float q160[4]; } M1Rig93;
typedef struct M1Step93 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig93 *rig278; } M1Step93;
typedef struct M1Obj93 { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; } M1Obj93;
typedef struct M1Cmd93 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd93;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_0001D4E0(void *o);
M1Cmd93 *sub_00113400(void *h, int v);

/* 0x00137090: sway (rig quaternion +0x160), state 0x1B, o flags 5, h +0x4C |= 0x70; with rig
 * byte +8 bit 7 clear o bits 0xE0 and set rig bit 4; +-5 degrees at frameTime * pi/48. */
void m1_Sway137090(M1Obj93 *o, M1Step93 *h)
{
    M1Rig93 *r = h->rig278;
    M1Rig93 *p;
    M1Cmd93 *c;
    float t;
    if (sub_001456E0(o, h, 0x1B, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q160[2] = 0.0f;
    p->q160[1] = 0.0f;
    p->q160[0] = 0.0f;
    p->q160[3] = 1.0f;
    o->flags10 |= 5;
    h->flags4C |= 0x70;
    if (r->b08 < 0) {
        o->flags0C &= ~0xE0u;
        *(uint32_t *)&r->b08 |= 4;
    }
    t = m1_frameTime42C858 * 0.065449849f;
    c = sub_00113400(h, 1);
    c->f10 = 0.087266468f;
    c->f14 = -0.087266468f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

typedef struct M1Src93 { uint8_t unk00[0x70]; float off70[4]; } M1Src93;
typedef struct M1Obj93A {
    uint8_t unk00[0x20];
    float  *node20;            /* +0x20 */
    uint8_t unk24[0x34 - 0x24];
    M1Src93 *src34;            /* +0x34 */
    uint8_t unk38[0x60 - 0x38];
    float   pos60[4];          /* +0x60 */
    float   scale70[3];        /* +0x70 */
    uint8_t unk7C[0x80 - 0x7C];
    float   vel80[4];          /* +0x80 */
} M1Obj93A;
void sub_001AD940(float *m);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_000F5D40(float *d, const float *s);

/* 0x00184160: attach step: offset +0x70 of the source, rotated by the node matrix scaled by
 * +0x70..+0x78 (translation cleared), plus position, velocity and the target's +0x78, becomes
 * the new position (w = 1). */
void m1_Attach184160(M1Obj93A *o, uint8_t *t)
{
    float v[4];
    float m[16];
    sub_001AD940(m);
    m[0] = o->scale70[0];
    m[5] = o->scale70[1];
    m[10] = o->scale70[2];
    sub_001AD7C0(m, m, o->node20);
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    sub_001AD9B0(v, m, o->src34->off70);
    sub_001ADAF0(v, o->pos60, v);
    sub_001ADAF0(v, v, o->vel80);
    sub_001ADAF0(v, v, (const float *)(t + 0x78));
    v[3] = 1.0f;
    sub_000F5D40(o->pos60, v);
}

/* 0x0018B750: attach step as 0x184160 but adding the target's +0x4C. */
void m1_Attach18B750(M1Obj93A *o, uint8_t *t)
{
    float v[4];
    float m[16];
    sub_001AD940(m);
    m[0] = o->scale70[0];
    m[5] = o->scale70[1];
    m[10] = o->scale70[2];
    sub_001AD7C0(m, m, o->node20);
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    sub_001AD9B0(v, m, o->src34->off70);
    sub_001ADAF0(v, o->pos60, v);
    sub_001ADAF0(v, v, o->vel80);
    sub_001ADAF0(v, v, (const float *)(t + 0x4C));
    v[3] = 1.0f;
    sub_000F5D40(o->pos60, v);
}

