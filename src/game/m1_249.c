/* Area m1, file 249: effect message handlers. Names inferred. */
#include <stdint.h>

typedef struct M1E249 { uint8_t unk00[0x44]; float v44[3]; float f50; uint8_t unk54[0x1C]; float v70[4]; uint16_t w80, w82; } M1E249;
typedef struct M1A249 { uint8_t unk00[0x60]; int32_t st60; uint8_t unk64[0x10]; M1E249 *e74; } M1A249;
typedef struct M1M249 { int32_t kind; uint8_t unk04[0x1C]; float v20[4]; } M1M249;
extern float a50_frameUnits;
void sub_00189DA0(void *o, M1A249 *a, int32_t st);
void sub_00189DA0b(void *o, M1A249 *a, int32_t st);   /* same function (aliases stop cl merging calls) */
void sub_00189DA0c(void *o, M1A249 *a, int32_t st);
void sub_000F5D40(void *dst, const void *src);
void sub_001ADB60(float *dst, const float *src, float k);

/* 0x00195210: effect message handler (ignored in step 2): hits 1/2/3/7/9/32/34 and 10/41 flag +0x82 and go to step 2;
   5 -> step 6, 12 -> step 2, 14/40 -> step 3 (returns 1), 26-28 copy the message vector -> step 4, 35 -> step 2,
   42 blends toward it -> step 5; most set +0x80. */
int m1_FxMsg195210(void *o, M1A249 *a, M1M249 *m)
{
    M1E249 *e = a->e74;
    int st = a->st60;
    int k;
    if (st == 2)
        return 0;
    switch (m->kind) {
    case 14: case 40:
        e->w80 = 1;
        sub_00189DA0(o, a, 3);
        return 1;
    case 5:
        if (st == 6)
            return 0;
        k = 6;
        goto w80;
    case 26: case 27: case 28:
        e->w80 = 1;
        sub_000F5D40(e->v70, m->v20);
        sub_00189DA0(o, a, 4);
        return 0;
    case 42:
        if (st == 6)
            return 0;
        e->w80 = 1;
        sub_001ADB60(e->v44, m->v20, a50_frameUnits);
        e->f50 = 0.0f;
        sub_00189DA0(o, a, 5);
        return 0;
    case 1: case 2: case 3: case 7: case 9: case 32: case 34:
        e->w82 = 1;
        sub_00189DA0(o, a, 2);
        return 0;
    case 35:
        sub_00189DA0b(o, a, 2);
        return 0;
    case 10: case 41:
        e->w82 = 1;
        sub_00189DA0c(o, a, 2);
        return 0;
    case 12:
        k = 2;
w80:
        e->w80 = 1;
        sub_00189DA0(o, a, *(volatile int *)&k);
        return 0;
    }
    return 0;
}

typedef struct M1SE249 { uint32_t flags0; } M1SE249;
typedef struct M1SA249 { uint8_t unk00[0x60]; int32_t st60; uint8_t unk64[0x10]; M1SE249 *e74; } M1SA249;
typedef struct M1SO249 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0xC]; void *n20; uint8_t unk24[0x2C];
    float r50, r54; uint8_t unk58[8]; float pos60[3]; float w6C; uint8_t unk70[0x10]; float v80[4]; } M1SO249;
int32_t a80_Get3ED238(void);
int32_t Stats_HasEFC(void);
void sub_001ADAF0(float *out, const float *a, const float *b);
void sub_001AD940(float *m);
void sub_001AD8B0(float *out, const float *in, float ang);
void sub_001AD8E0(float *out, const float *in, float ang);
void sub_001ADA40(void *n, const float *m);
void sub_00189DA0s(M1SO249 *o, M1SA249 *a, int32_t st);   /* 0x189DA0 */
void sub_00189DA0t(M1SO249 *o, M1SA249 *a, int32_t st);   /* same function (alias stops cl merging calls) */

/* 0x001942B0: tumbling debris tick: a zone trigger sends it to step 2; show with the EFC stat (unless flag 2), spin
   about x at 0.224 per frame unit (unless flag 0x40), wrap both angles to +-pi, move by its velocity, rebuild the node
   matrix and go to step 2 once it falls below y 200. */
void m1_Debris1942B0(M1SO249 *o, M1SA249 *a)
{
    M1SE249 *e = a->e74;
    float m[16];
    if (a80_Get3ED238() && a->st60 != 2) {
        sub_00189DA0s(o, a, 2);
        return;
    }
    if (!(e->flags0 & 2)) {
        if (Stats_HasEFC() > 0)
            o->flags10 |= 1;
        else
            o->flags10 &= ~1u;
    }
    if (!(e->flags0 & 0x40))
        o->r50 += a50_frameUnits * 0.224274829f;
    if (o->r50 > 3.14159274f)
        o->r50 -= 6.28318548f;
    if (-3.14159274f > o->r50)
        o->r50 += 6.28318548f;
    if (o->r54 > 3.14159274f)
        o->r54 -= 6.28318548f;
    if (-3.14159274f > o->r54)
        o->r54 += 6.28318548f;
    sub_001ADAF0(o->pos60, o->pos60, o->v80);
    o->w6C = 1.0f;
    sub_001AD940(m);
    sub_001AD8B0(m, m, o->r50);
    sub_001AD8E0(m, m, o->r54);
    sub_001ADA40(o->n20, m);
    if (o->pos60[1] > 200.0f)
        sub_00189DA0t(o, a, 2);
}

/* 0x0018C950: as 0x1942B0 without the spin and with the EFC visibility test skipped under flags 6. */
void m1_Debris18C950(M1SO249 *o, M1SA249 *a)
{
    M1SE249 *e = a->e74;
    float m[16];
    if (a80_Get3ED238() && a->st60 != 2) {
        sub_00189DA0s(o, a, 2);
        return;
    }
    if (!(e->flags0 & 6)) {
        if (Stats_HasEFC() > 0)
            o->flags10 |= 1;
        else
            o->flags10 &= ~1u;
    }
    if (o->r50 > 3.14159274f)
        o->r50 -= 6.28318548f;
    if (-3.14159274f > o->r50)
        o->r50 += 6.28318548f;
    if (o->r54 > 3.14159274f)
        o->r54 -= 6.28318548f;
    if (-3.14159274f > o->r54)
        o->r54 += 6.28318548f;
    sub_001ADAF0(o->pos60, o->pos60, o->v80);
    o->w6C = 1.0f;
    sub_001AD940(m);
    sub_001AD8B0(m, m, o->r50);
    sub_001AD8E0(m, m, o->r54);
    sub_001ADA40(o->n20, m);
    if (o->pos60[1] > 200.0f)
        sub_00189DA0t(o, a, 2);
}

typedef struct M1XE249 { uint8_t unk00[0x14]; float v14[4]; } M1XE249;
typedef struct M1XA249 { uint8_t unk00[0x74]; M1XE249 *e74; } M1XA249;
int sub_001C7EE1(void);   /* rand */
void sub_001AD910(float *out, const float *in, float ang);
void sub_000F5D40(void *dst, const void *src);

/* 0x0018B8F0: pick a random spin axis: rotate the identity by random angles about x, y and z (each -pi..pi) and store
   the resulting z axis at +0x14. */
void m1_RandAxis18B8F0(void *o, M1XA249 *a)
{
    M1XE249 *e = a->e74;
    float m[16];
    sub_001AD940(m);
    sub_001AD8B0(m, m, (float)sub_001C7EE1() * (1.0f / 32767.0f) * 6.28318548f - 3.14159274f);
    sub_001AD8E0(m, m, (float)sub_001C7EE1() * (1.0f / 32767.0f) * 6.28318548f - 3.14159274f);
    sub_001AD910(m, m, (float)sub_001C7EE1() * (1.0f / 32767.0f) * 6.28318548f - 3.14159274f);
    sub_000F5D40(e->v14, &m[8]);
}

typedef struct M1GC249 { uint8_t unk00[0xC4]; float fC4; uint8_t unkC8[0x10]; float fD8; } M1GC249;
typedef struct M1GM249 { uint8_t unk00[0x14]; M1GC249 *anim14; } M1GM249;
typedef struct M1GO249 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[0x24]; M1GM249 *mdl30; uint8_t unk34[0x2C];
    uint8_t pos60[0xC8]; uint8_t flags128; } M1GO249;
typedef struct M1GS249 { uint8_t unk00[0x50]; int32_t n50, n54; float f58; } M1GS249;
extern M1GO249 *g_playerObj;
void sub_00170AF0(M1GO249 *o);          /* regargs: o=ESI */
int32_t sub_00170C10(M1GO249 *o);       /* regargs: o=EDI */
void sub_00170470(M1GO249 *o);          /* regargs: o=EAX */
float sub_001B2770(const void *a, const void *b);
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);

/* 0x00171580: ghost tick: kinds below 10 step their drift (0x170AF0), switch to mode 3 when spotted (0x170C10) or 4
   within 23 of the player, and run 0x170470 (tail call) while the clip is within 25 frames of its mark; higher kinds go
   to mode 2 on a zone trigger and play sound 0x70 on ground contact (calls 0x170AF0 with o=ESI, 0x170C10 with o=EDI,
   0x170470 with o=EAX). */
void m1_Ghost171580(M1GO249 *o, M1GS249 *s)
{
    M1GC249 *c;
    if (o->kind8 < 10) {
        sub_00170AF0(o);
        if (sub_00170C10(o)) {
            s->n50 = 3;
            goto reset;
        }
        if (sub_001B2770(o->pos60, g_playerObj->pos60) <= 23.0f) {
            s->n50 = 4;
reset:
            s->n54 = 0;
            s->f58 = 0.0f;
        }
        c = o->mdl30->anim14;
        if (c->fD8 > 25.0f - c->fC4 && c->fC4 + 25.0f > c->fD8)
            sub_00170470(o);
        return;
    }
    if (a80_Get3ED238()) {
        s->n50 = 2;
        s->n54 = 0;
        s->f58 = 0.0f;
    }
    if (o->flags128 & 8)
        aab_Effect494D0(0x70, o->pos60, 0);
}

typedef struct M1JP249 { uint8_t unk00[0x10]; float v10[2]; float f18; uint8_t unk1C[4]; float f20; } M1JP249;
typedef struct M1JM249 { uint8_t unk00[0x30]; float v30[4]; } M1JM249;
void sub_00082A30(float *out, const float *dir, M1JP249 *p);
void sub_001ADB60(float *dst, const float *src, float k);
void sub_001ADBA0(float *out, const float *in, float k);

/* 0x000C7A10: advance a joint: push its position along the reversed direction p+0x10 through 0x82A30, add the vertical
   speed, scale by the frame step and add to the matrix translation, then re-apply the z/x/y rotations (regargs: p=EDI
   m=ESI). */
void m1_JointStep0C7A10(M1JP249 *p, M1JM249 *m)
{
    float a[4], b[4], c[4];
    a[0] = 0.0f;
    a[1] = 0.0f;
    a[2] = 0.0f;
    a[3] = 1.0f;
    b[0] = 0.0f;
    b[1] = 0.0f;
    b[2] = 0.0f;
    b[3] = 1.0f;
    sub_000F5D40(a, p->v10);
    sub_001ADB60(a, a, -1.0f);
    sub_00082A30(c, a, p);
    c[1] = p->f20 * a50_frameUnits + c[1];
    sub_001ADBA0(b, c, a50_frameUnits);
    sub_001ADAF0(b, m->v30, b);
    sub_001AD910((float *)m, (float *)m, p->f18);
    sub_001AD8B0((float *)m, (float *)m, p->v10[0]);
    sub_001AD8E0((float *)m, (float *)m, p->v10[1]);
    sub_000F5D40(m->v30, b);
}
