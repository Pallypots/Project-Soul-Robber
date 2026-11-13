/* Area m1, file 73: rotation helpers and rig aim setups. Names inferred. */
#include <stdint.h>

typedef struct M1Turn2 { uint8_t unk00[0x20]; void *node20; uint8_t unk24[0x50 - 0x24]; float rx50, ry54; } M1Turn2;
void sub_001AD940(float *m);
void sub_001AD8B0(float *out, const float *m, float a);
void sub_001AD8E0(float *out, const float *m, float a);
void sub_001ADA40(void *node, const float *m);

/* 0x001787A0: wraps the two angles +0x50 / +0x54 into -pi..pi and applies the rotation
 * (x by +0x50 via 0x1AD8B0, then y by +0x54 via 0x1AD8E0) to the node +0x20. */
void m1_TurnNode1787A0(M1Turn2 *o)
{
    float m[16];
    if (o->rx50 > 3.1415927f)
        o->rx50 = o->rx50 - 6.2831855f;
    if (-3.1415927f > o->rx50)
        o->rx50 = o->rx50 + 6.2831855f;
    if (o->ry54 > 3.1415927f)
        o->ry54 = o->ry54 - 6.2831855f;
    if (-3.1415927f > o->ry54)
        o->ry54 = o->ry54 + 6.2831855f;
    sub_001AD940(m);
    sub_001AD8B0(m, m, o->rx50);
    sub_001AD8E0(m, m, o->ry54);
    sub_001ADA40(o->node20, m);
}

typedef struct M1Fx90c { uint8_t unk00[0x90]; uint32_t flags90; } M1Fx90c;
typedef struct M1RigA {
    uint8_t unk00[8];
    int32_t dir08;             /* +0x08 */
    int16_t w0C;               /* +0x0C */
    uint8_t unk0E[0x18 - 0xE];
    float   f18, f1C;          /* +0x18 */
    uint8_t unk20[4];
    float   f24;               /* +0x24 */
    uint8_t unk28[4];
    float   f2C;               /* +0x2C */
    uint8_t unk30[4];
    M1Fx90c *fx34;             /* +0x34 */
} M1RigA;
typedef struct M1StepA2 { uint8_t unk000[0x278]; M1RigA *rig278; } M1StepA2;
typedef struct M1ObjA2 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x30 - 0x14]; void *anim30; } M1ObjA2;
void  sub_000832D0(void *a, int v);
float sub_001A3EE0(float a);
float sub_001A3ED0(float a);

/* 0x00181400: clip 3, then the rig's direction +0x08 (0..3) picks an angle (45, -45,
 * -135, 135 degrees; left unset otherwise); +0x24 = 23 * 0x1A3EE0(angle), +0x2C = 23 *
 * 0x1A3ED0(angle), +0x1C = 0, +0x0C = 0, +0x18 = 0.1, effect flag 0x40, clear o flags 0xC. */
void m1_RigAim181400(M1ObjA2 *o, M1StepA2 *h)
{
    M1RigA *r = h->rig278;
    float a;
    sub_000832D0(o->anim30, 3);
    if (r->dir08 == 0)
        a = 0.78539819f;
    else if (r->dir08 == 1)
        a = -0.78539801f;
    else if (r->dir08 == 2)
        a = -2.3561945f;
    else if (r->dir08 == 3)
        a = 2.3561945f;
    r->f24 = sub_001A3EE0(a) * 23.0f;
    r->f2C = sub_001A3ED0(a) * 23.0f;
    r->f1C = 0.0f;
    r->w0C = 0;
    r->f18 = 0.1f;
    r->fx34->flags90 |= 0x40;
    o->flags10 &= ~0xCu;
}
