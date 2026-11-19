/* Area m1, file 248: effect message handlers and helpers. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1E248 { uint32_t flags0; uint8_t unk04[4]; float f8; } M1E248;
typedef struct M1A248 { uint8_t unk00[0x74]; M1E248 *e74; } M1A248;
typedef struct M1O248 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x70]; float v80[4]; } M1O248;
typedef struct M1M248 { int32_t kind; uint8_t unk04[0x1C]; float v20[4]; } M1M248;
extern float a50_frameUnits, a50_frameSeconds;
void sub_00189DA0(M1O248 *o, M1A248 *a, int32_t st);
void sub_001AD7E0(float *out, const float *in);
void sub_001ADBA0(float *out, const float *in, float k);


typedef struct M1RE248 { uint8_t unk00[0x10]; float v10[4]; } M1RE248;
typedef struct M1RA248 { uint8_t unk00[0x68]; int32_t n68; uint8_t unk6C[8]; M1RE248 *e74; } M1RA248;
typedef struct M1RO248 { uint8_t unk00[0x54]; float r54; uint8_t unk58[8]; uint8_t pos60[0x20]; float v80[4]; } M1RO248;
typedef struct M1RP248 { uint8_t unk00[0x74]; float v74[4]; uint8_t unk84[0x100]; } M1RP248;
extern M1RO248 *g_playerObj;
void m1_RibbonInit18CA90(M1RA248 *a);   /* regargs: a=EAX */
void sub_001AD940(float *m);
void sub_001AD8E0(float *out, const float *in, float ang);
void sub_001AD9B0(float *out, const float *m, const float *v);
void sub_000F5D40(void *dst, const void *src);
void sub_0018D680(M1RO248 *o, M1RP248 *p, float k);
void sub_0018CB60(M1RO248 *o, M1RA248 *a);
float sub_001B2770(const void *a, const void *b);
void sub_00189DA0r(M1RO248 *o, M1RA248 *a, int32_t st);   /* 0x189DA0 */

/* 0x0018CF90: ribbon effect: step 0 initialises it, rotates o's velocity into its frame and seeds the trail from the
   anchor; every tick updates it and moves to step 2 once the player is more than 80 away (calls 0x18CA90 with a=EAX). */
void m1_Ribbon18CF90(M1RO248 *o, M1RA248 *a)
{
    M1RE248 *e = a->e74;
    float m[16];
    float v[4];
    float k;
    M1RP248 p;
    switch (a->n68) {
    case 0:
        m1_RibbonInit18CA90(a);
        sub_001AD940(m);
        sub_001AD8E0(m, m, 0.0f - o->r54);
        sub_001AD9B0(v, m, o->v80);
        k = v[1];
        sub_000F5D40(p.v74, e->v10);
        sub_0018D680(o, &p, 0.0f - k);
        a->n68++;
    case 1:
        sub_0018CB60(o, a);
        if (sub_001B2770(o->pos60, g_playerObj->pos60) > 80.0f)
            sub_00189DA0r(o, a, 2);
        return;
    }
}


typedef struct M1TE248 { uint8_t unk00[4]; int32_t n4; uint8_t unk08[4]; float vC[4]; float v1C[3], w28; } M1TE248;
typedef struct M1TA248 { uint8_t unk00[0x68]; int32_t n68; uint8_t unk6C[4]; float t70; M1TE248 *e74; } M1TA248;
typedef struct M1TO248 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x114]; uint8_t flags128; } M1TO248;
int m1_LockTry18ED40(M1TO248 *o, M1TA248 *s);       /* regargs: o=ESI s=EBX */
int m1_ShapeTest18ECD0(M1TA248 *a, M1TO248 *b);     /* regargs: a=ESI b=EDI */
int32_t m1_HoldDrop13D4E0(int32_t id, M1TO248 *o, int32_t z);
int32_t Stats_HasEFC(void);
float aab_Use82D70(const float *v);
void sub_00189DA0t(M1TO248 *o, M1TA248 *a, int32_t st);   /* 0x189DA0 */
void sub_00189DA0u(M1TO248 *o, M1TA248 *a, int32_t st);   /* same function (aliases stop cl merging calls) */

/* 0x0018F040: thrown-object tick: ground/wall contact or a successful lock-on -> step 7; a shape hit -> step 1 if the
   hold drops it, else 4; otherwise show with the EFC stat, flip its velocity once the timer runs out, and stop it once
   it is more than 70 away (calls 0x18ED40 with o=ESI s=EBX, 0x18ECD0 with a=ESI b=EDI). */
void m1_Thrown18F040(M1TO248 *o, M1TA248 *a)
{
    M1TE248 *e = a->e74;
    if (o->flags128 & 6) {
        sub_00189DA0t(o, a, 7);
        return;
    }
    if (m1_LockTry18ED40(o, a)) {
        sub_00189DA0u(o, a, 7);
        return;
    }
    if (m1_ShapeTest18ECD0(a, o)) {
        if (m1_HoldDrop13D4E0(e->n4, o, 0)) {
            sub_00189DA0t(o, a, 1);
            return;
        }
        sub_00189DA0u(o, a, 4);
        return;
    }
    if (Stats_HasEFC() > 0)
        o->flags10 |= 1;
    else
        o->flags10 &= ~1u;
    switch (a->n68) {
    case 0:
        if (a->t70 <= 0.0f) {
            sub_001ADBA0(e->v1C, e->vC, -1.0f);
            a->n68++;
        }
        return;
    case 1:
        if (aab_Use82D70(e->vC) > 70.0f) {
            e->v1C[0] = 0.0f;
            e->v1C[1] = 0.0f;
            e->v1C[2] = 0.0f;
            e->w28 = 1.0f;
        }
        return;
    }
}
