/* Area m1, file 104: state resets. Names inferred. */
#include <stdint.h>

typedef struct M1Slot104 { int32_t i00; int32_t id04; float f08; int32_t z0C[7]; } M1Slot104;
typedef struct M1Step104 { uint8_t unk000[0x60]; int32_t i60; uint8_t unk064[0x2A0 - 0x64]; M1Slot104 slots2A0[4]; } M1Step104;

/* 0x001141F0: clear the four 0x28-byte slots at +0x2A0 (id -1) and +0x60. */
void m1_SlotsClear1141F0(M1Step104 *h)
{
    int i;
    for (i = 0; i < 4; i++) {
        h->slots2A0[i].i00 = 0;
        h->slots2A0[i].id04 = -1;
        h->slots2A0[i].f08 = 0.0f;
        h->slots2A0[i].z0C[0] = 0;
        h->slots2A0[i].z0C[1] = 0;
        h->slots2A0[i].z0C[2] = 0;
        h->slots2A0[i].z0C[3] = 0;
        h->slots2A0[i].z0C[4] = 0;
        h->slots2A0[i].z0C[5] = 0;
        h->slots2A0[i].z0C[6] = 0;
    }
    h->i60 = 0;
}

typedef struct M1Scr104 {
    uint8_t unk000[0x8C];
    int32_t i8C, i90;          /* +0x8C, +0x90 */
    uint8_t unk094[0xD8 - 0x94];
    int32_t iD8, iDC;          /* +0xD8, +0xDC */
    uint8_t unk0E0[0x12C - 0xE0];
    int32_t i12C, i130;        /* +0x12C, +0x130 */
    uint8_t unk134[0x180 - 0x134];
    int32_t i180, i184;        /* +0x180, +0x184 */
    uint8_t unk188[0x198 - 0x188];
    float   v198[4];           /* +0x198 */
    uint8_t unk1A8[0x214 - 0x1A8];
    float   v214[4];           /* +0x214 */
    float   v224[4];           /* +0x224 */
    uint8_t unk234[0x238 - 0x234];
    int32_t i238, i23C;        /* +0x238, +0x23C */
    uint8_t unk240[0x2E4 - 0x240];
    int32_t z2E4[12];          /* +0x2E4 */
    uint8_t unk314[0x314 - 0x314];
} M1Scr104;
extern M1Scr104 *m1_scr3F6130;

/* 0x00101380: scene script reset: clear the whole record, then reset its fields (vectors to 0,
 * +0x238 = -1, the twelve +0x2E4 slots). */
void m1_ScriptReset101380(void)
{
    M1Scr104 *g = m1_scr3F6130;
    int32_t *p = (int32_t *)g;
    int n;
    for (n = 0; n < 0xC5; n++)
        p[n] = 0;
    g->v198[0] = 0.0f;
    g->v198[1] = 0.0f;
    g->v198[2] = 0.0f;
    g->v198[3] = 0.0f;
    g->v224[0] = 0.0f;
    g->v224[1] = 0.0f;
    g->v224[2] = 0.0f;
    g->v224[3] = 0.0f;
    g->v214[0] = 0.0f;
    g->v214[1] = 0.0f;
    g->v214[2] = 0.0f;
    g->v214[3] = 0.0f;
    g->i238 = -1;
    g->i23C = 0;
    for (n = 0; n < 12; n++)
        g->z2E4[n] = 0;
    g->i8C = 0;
    g->i90 = 0;
    g->iD8 = 0;
    g->iDC = 0;
    g->i12C = 0;
    g->i130 = 0;
    g->i180 = 0;
    g->i184 = 0;
}

typedef struct M1Bone104 { uint8_t unk000[0x30]; float pos30[4]; uint8_t unk040[0x180 - 0x40]; } M1Bone104;
typedef struct M1Mdl104 { uint8_t unk000[0xC4]; M1Bone104 *bonesC4; } M1Mdl104;
typedef struct M1Obj104 { uint8_t unk00[0xC]; uint8_t b0C; uint8_t unk0D[0x20 - 0xD]; M1Mdl104 *mdl20; } M1Obj104;
typedef struct M1Rig104 { uint8_t unk00[0x18]; uint8_t b18; } M1Rig104;
typedef struct M1Comp104 { int32_t kind00; uint8_t unk04[0x278 - 4]; M1Rig104 *rig278; } M1Comp104;
typedef struct M1Wob104 { uint8_t unk00[0x10]; M1Obj104 *obj10; int32_t idx14; float amp18; uint8_t unk1C[0x24 - 0x1C]; float amp24; } M1Wob104;
M1Comp104 *sub_0001D960(void *o, int kind);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_0003B300(void *bone);

/* 0x00186500: wobble the bones 3..6 of the object in turn (one per call): push the bone by
 * (0, +0x24, -(+0x18), 0) / 4 when rig flag 2 and the object are active. Spins on a wrong
 * component 6. */
void m1_BoneWobble186500(void *unused, M1Wob104 *s)
{
    M1Obj104 *o = s->obj10;
    float v[4];
    int bones[4];
    M1Comp104 *c;
    M1Bone104 *b;
    v[1] = 1.0f;
    v[0] = 0.0f;
    v[2] = -1.0f;
    v[3] = 0.0f;
    bones[0] = 3;
    bones[1] = 4;
    bones[2] = 5;
    bones[3] = 6;
    c = sub_0001D960(o, 6);
    if (c->kind00 != 6)
        for (;;) ;
    if (!(c->rig278->b18 & 2) || !(o->b0C & 1))
        return;
    b = &o->mdl20->bonesC4[bones[s->idx14]];
    v[2] = s->amp18 * v[2];
    v[1] = s->amp24 * v[1];
    sub_001ADBA0(v, v, 0.25f);
    sub_001ADAF0(b->pos30, b->pos30, v);
    sub_0003B300(b);
    if (++s->idx14 >= 4)
        s->idx14 = 0;
}

typedef struct M1Rig104S {
    uint8_t unk00[0xC];
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
    uint8_t unk44[0x54 - 0x44];
    float   f54;               /* +0x54 */
} M1Rig104S;
typedef struct M1Step104S { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig104S *rig278; } M1Step104S;
typedef struct M1Cmd104 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd104;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_001456E0(void *o, void *h, int a, int b);
M1Cmd104 *sub_00113400(void *h, int v);

/* 0x00157260: as 0x157480 but raising rig +0x54 by 15 and also clearing h +0x4C bit 0x100. */
void m1_Sway157260(void *o, M1Step104S *h)
{
    M1Rig104S *r = h->rig278;
    M1Rig104S *p;
    M1Cmd104 *c;
    float t;
    sub_001456E0(o, h, 0x15, 0);
    r->rate0C = m1_frameTime42C858 * 0.005f;
    r->q24[2] = 0.0f - m1_frameRate42C85C * 3.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    p = h->rig278;
    p->f54 = p->f54 + 15.0f;
    if (0.0f > p->f54)
        p->f54 = 0.0f;
    else if (p->f54 > 200.0f)
        p->f54 = 200.0f;
    h->flags4C &= ~0x170u;
    r->flags40 |= 0x80;
    t = m1_frameTime42C858 * 0.034906585f;
    c = sub_00113400(h, 1);
    c->f10 = 0.17453294f;
    c->f14 = -0.17453294f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}
