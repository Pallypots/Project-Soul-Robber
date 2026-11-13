/* Area m1, file 68: animation clip switches and glows. Names inferred. */
#include <stdint.h>

typedef struct M1Clip10 { uint8_t unk00[0x10]; int32_t len10; } M1Clip10;
typedef struct M1Anim14 { uint8_t unk00[8]; int32_t clip08; uint8_t unk0C[8]; void *track14; } M1Anim14;
typedef struct M1ObjC1 {
    uint8_t unk000[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t unk014[0x30 - 0x14];
    M1Anim14 *anim30;          /* +0x30 */
    uint8_t unk034[0x128 - 0x34];
    uint32_t flags128;         /* +0x128 */
} M1ObjC1;
typedef struct M1StepC1 { uint8_t unk00[0x50]; int32_t next50; int32_t state54; float f58; uint8_t unk5C[4]; float f60; } M1StepC1;
void      sub_000832D0(void *a, int v);
M1Clip10 *sub_00083120(M1Anim14 *a, int clip);
void      sub_001AEDD0(void *track, int len);

/* 0x00170990: state 0 lowers +0x60 by 25, clears o flags 0x18 (+0x128), stops the clip
 * (-1) and its track, sets o flag 4 and moves on; state 1 waits for o flags 0x18, then
 * restores the clip's length on the track, next 2, back to state 0, +0x58 = 0, clear o
 * flag 4. */
void m1_ClipPause170990(M1ObjC1 *o, M1StepC1 *h)
{
    M1Clip10 *c;
    switch (h->state54) {
    case 0:
        h->f60 = h->f60 - 25.0f;
        o->flags128 &= ~0x18u;
        sub_000832D0(o->anim30, -1);
        sub_001AEDD0(o->anim30->track14, 0);
        o->flags10 |= 4;
        h->state54++;
        break;
    case 1:
        if (!(*(uint8_t *)&o->flags128 & 0x18))
            break;
        c = sub_00083120(o->anim30, o->anim30->clip08);
        sub_001AEDD0(o->anim30->track14, c->len10);
        h->next50 = 2;
        h->state54 = 0;
        h->f58 = 0.0f;
        o->flags10 &= ~4u;
        break;
    }
}

typedef struct M1Glow2 {
    uint8_t unk00[0x50];
    float   v50[4];            /* +0x50 */
    float   pos60[3];          /* +0x60 */
    float   w6C;               /* +0x6C */
    float   size70;            /* +0x70 */
    uint8_t unk74[0xA0 - 0x74];
    float   ofsA0[3];          /* +0xA0 */
} M1Glow2;
typedef struct M1GlowSt2 { uint8_t unk00[0x74]; float t74; } M1GlowSt2;
void sub_00113AA0(void *o, void *h);
void sub_00113040(void *o, void *h, int next);
void sub_000C7540(void *o, float a, float size, const float *pos, const float *v);

/* 0x00139030: as 0x1771E0 with next state 0xC: once the timer +0x74 is no longer positive
 * ends the step; else draws the glow at position + offset, size +0x70 * 0.8. */
void m1_Glow139030(M1Glow2 *o, M1GlowSt2 *h)
{
    float p[4];
    if (0.0f >= h->t74) {
        sub_00113AA0(o, h);
        sub_00113040(o, h, 0xC);
        return;
    }
    p[0] = o->pos60[0] + o->ofsA0[0];
    p[1] = o->pos60[1] + o->ofsA0[1];
    p[2] = o->pos60[2] + o->ofsA0[2];
    p[3] = o->w6C;
    sub_000C7540(o, 1.0f, o->size70 * 0.8f, p, o->v50);
}

typedef struct M1StepU { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; void *rig278; } M1StepU;
typedef struct M1ObjU { uint8_t unk00[0x20]; float *frame20; } M1ObjU;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *s, int a, int b);
void sub_00156180(void *rig, float x, float y, float z, float t);
void sub_001AD7E0(float *out, const float *v);
void sub_000F5D40(float *dst, const float *src);
void sub_001ADA60(float *out, const float *a, const float *b);

/* 0x00146DA0: 0x1456E0(0x39), rig blend 0x156180(0, 0, 0, frame time * 0.003), clear h +0x4C
 * bits 0x70, then stands o's frame up: flattens and normalises the first row, sets the
 * second to (0, 1, 0, 0) and the third to their cross product (0x1ADA60). */
void m1_StandUp146DA0(M1ObjU *o, M1StepU *h)
{
    float up[4];
    float *f;
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    sub_001456E0(o, h, 0x39, 0);
    sub_00156180(h->rig278, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.003f);
    h->flags4C &= ~0x70u;
    o->frame20[1] = 0.0f;
    sub_001AD7E0(o->frame20, o->frame20);
    sub_000F5D40(o->frame20 + 4, up);
    f = o->frame20;
    sub_001ADA60(f + 8, f, f + 4);
}

typedef struct M1RigW2 { uint8_t unk00[0x50]; uint32_t flags50; } M1RigW2;
typedef struct M1StepW2 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1RigW2 *rig278; } M1StepW2;
typedef struct M1ObjW2 { uint8_t unk00[0x10]; uint32_t flags10; } M1ObjW2;
typedef struct M1CmdW2 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1CmdW2;
M1CmdW2 *sub_00113400(void *h, int v);

/* 0x001481E0: 0x1456E0(0), rig blend (frame time * 0.003), o flag 0x20, h +0x4C |= 0x70,
 * rig flag 0x100; command 1 = (30 deg, -30 deg, frame time * 2 deg unless that is -1, 0). */
void m1_RigSwing1481E0(M1ObjW2 *o, M1StepW2 *h)
{
    M1RigW2 *r = h->rig278;
    M1CmdW2 *c;
    float t;
    sub_001456E0(o, h, 0, 0);
    sub_00156180(r, 0.0f, 0.0f, 0.0f, m1_frameTime42C858 * 0.003f);
    o->flags10 |= 0x20;
    h->flags4C |= 0x70;
    r->flags50 |= 0x100;
    t = m1_frameTime42C858 * 0.034906585f;
    c = sub_00113400(h, 1);
    c->f10 = 0.52359879f;
    c->f14 = -0.52359879f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

typedef struct M1ObjL2 { uint8_t unk00[0x54]; float yaw54; } M1ObjL2;
typedef struct M1StepL2 { uint8_t unk00[0x68]; float f68; uint8_t unk6C[0x74 - 0x6C]; float t74; float v78[4]; } M1StepL2;
extern float m1_frameRate42C85C;
void sub_001AD940(float *m);
void sub_001AE010(float *out, const float *m, const float *v);
void sub_001AD8E0(float *out, const float *m, float a);

/* 0x00178DF0: launch: a matrix translated by (0, 0, -(frame rate * 45)) (0x1AE010) and
 * turned by o's yaw +0x54 gives the velocity h +0x78 (its last row); timer +0x74 = 50
 * frames and +0x68 = timer * 0.125. */
void m1_Launch178DF0(M1ObjL2 *o, M1StepL2 *h)
{
    float v[4];
    float m[16];
    v[3] = 0.0f;
    v[1] = 0.0f;
    v[0] = 0.0f;
    v[2] = 0.0f - m1_frameRate42C85C * 45.0f;
    sub_001AD940(m);
    sub_001AE010(m, m, v);
    sub_001AD8E0(m, m, o->yaw54);
    sub_000F5D40(h->v78, m + 12);
    h->t74 = 1.0f / m1_frameTime42C858 * 50.0f * m1_frameRate42C85C;
    h->f68 = h->t74 * 0.125f;
}
