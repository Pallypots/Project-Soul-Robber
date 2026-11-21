/* Area m1, file 278: entity setup. Names inferred. */
#include <stdint.h>

typedef struct M1Kd278 { uint32_t ent0, mdl4, mdl8; uint16_t hookC, flagsE; } M1Kd278;   /* 0x10 */
typedef struct M1Hd278 { uint8_t unk00[8]; int32_t f8; } M1Hd278;
typedef struct M1Md278 { uint8_t unk00[0xC]; uint32_t flagsC, flags10; uint8_t unk14[0x1C]; M1Hd278 *h30; uint8_t unk34[8];
    int32_t h3C; uint8_t unk40[0xB4]; uint32_t fF4; uint8_t unkF8[0x2C]; int32_t f124; } M1Md278;
typedef struct M1En278 { uint32_t flags0; int32_t kind4; uint8_t unk08[0x3C]; int32_t f44, f48; uint8_t unk4C[0xD4];
    M1Md278 *m120; } M1En278;
extern const M1Kd278 m1_kinds2E30E0[0xFD];
void sub_0001B3A0(M1Md278 *m);
void sub_000832D0(M1Hd278 *h, int32_t mode);
void sub_0001D7F0(int32_t h, int32_t a, int32_t b);
void sub_000A4870(M1En278 *e, float scale);

/* 0x000A4E50: apply e's kind table entry (kinds 0..0xFC, asserted, model asserted): OR in the entity and model
   flags, run the kind's hook, set the kind's extra flags; kind 0x22 gets a fixed sort key, others pick it from
   the model's draw bits. Kind 0x71 also freezes its animation. Kinds 0x22 and 0x5D-0x5F are scaled to 1.8x.
   regargs: e=ESI. */
void m1_ApplyKindA4E50(M1En278 *e)
{
    M1Md278 *m;
    int32_t k;
    volatile int32_t vk;   /* keeps the separate signed range compares */
    vk = e->kind4;
    if (vk < 0) for (;;) ;
    if (vk >= 0xFD) for (;;) ;
    if (!e->m120) for (;;) ;
    e->flags0 |= m1_kinds2E30E0[e->kind4].ent0;
    e->m120->flagsC |= m1_kinds2E30E0[e->kind4].mdl4;
    e->m120->flags10 |= m1_kinds2E30E0[e->kind4].mdl8;
    if (m1_kinds2E30E0[e->kind4].hookC)
        sub_0001B3A0(e->m120);
    k = e->kind4;
    e->f44 = m1_kinds2E30E0[k].flagsE;
    m = e->m120;
    if (k == 0x22)
        m->fF4 = 0x80000000u;
    else
        m->f124 = (m->flagsC & 0xC0) ? 2 : 0;
    if (e->kind4 == 0x71 && (m = e->m120) != 0) {
        sub_000832D0(m->h30, 1);
        sub_0001D7F0(m->h3C, 1, 0);
        m->h30->f8 = -1;
        e->f48 = 1;
    }
    vk = e->kind4;
    if (vk == 0x22 || (vk > 0x5C && vk <= 0x5F))
        sub_000A4870(e, 1.8f);
}

typedef struct M1Pa278 { uint8_t unk00[0x80]; float *m80; } M1Pa278;
typedef struct M1Ch278 { uint8_t unk00[0x10]; float pos10[4]; float t20[4]; uint8_t unk30[0x30]; float m60[16];
    uint8_t unkA0[8]; float spinA8; uint8_t unkAC[0xC]; uint32_t flagsB8; } M1Ch278;
extern float m1_frameTime42C858;
extern float m1_followRate2C4618;                            /* 1.0 in the shipped data */
void sub_001AD940(float *m);
void sub_001ADA40(float *d, const float *s);
void sub_001ADB40(float *d, const float *s);                  /* copy a 3-vector */
void sub_001AD7C0(float *d, const float *a, const float *b);   /* d = a * b */
void sub_001ADCD0(float *d, const float *a, const float *b, float t);   /* d = lerp(a, b, t) */
void sub_000F5D40(float *d, const float *s);

/* 0x0003BA20: follow step for child c of parent p. When snapping (flags 0x08/0x10) c's matrix is reset, the
   parent's world matrix is taken (lifted by 4x the spin value) and c snaps to it; flag 0x08 becomes 0x10, any
   other snap clears both. Otherwise c's matrix follows parent * local, c spins, and its position eases toward
   the parent. Either way c's position is stored. regargs: c=EAX, p=EDI. */
void m1_Follow3BA20(M1Ch278 *c, M1Pa278 *p)
{
    float v[4], m[16];
    uint32_t fl;
    if (c->flagsB8 & 0x18) {
        sub_001AD940(c->m60);
        sub_001ADA40(m, p->m80 + 16);
        m[13] = c->spinA8 * 4.0f + m[13];
        sub_001ADB40(c->t20, &m[12]);
        sub_001ADB40(v, &m[12]);
        fl = c->flagsB8;
        if (fl & 8)
            c->flagsB8 = (fl & ~8u) | 0x10;
        else
            c->flagsB8 = fl & ~0x18u;
    } else {
        sub_001AD7C0(m, p->m80 + 16, c->m60);
        c->t20[1] += c->spinA8;
        sub_001ADCD0(v, c->t20, &m[12], m1_frameTime42C858 * m1_followRate2C4618);
    }
    sub_000F5D40(c->pos10, v);
}

typedef struct M1Vx278 { float v[4]; } M1Vx278;

/* 0x0001B8D0: corners of triangle n of an 8-vertex band mesh at base. Triangles 0-7 walk the band (odd ones
   flip winding by swapping the first two corners, using *c as scratch), 8-11 are the two cap quads from a
   fixed table, anything else gives vertices 0, 1, 2. regargs: n=EAX, base=ECX, b=EDX, c=EDI; stack arg (a). */
void m1_BandTri1B8D0(int32_t n, M1Vx278 *base, M1Vx278 **b, M1Vx278 **c, M1Vx278 **a)
{
    int32_t cap[12];
    int32_t i;
    cap[1] = 2;
    cap[2] = 6;
    cap[3] = 6;
    cap[4] = 2;
    cap[0] = 0;
    cap[5] = 4;
    cap[6] = 3;
    cap[7] = 1;
    cap[8] = 5;
    cap[9] = 1;
    cap[10] = 7;
    cap[11] = 5;
    if (n < 8) {
        *a = &base[n];
        if (n + 1 < 8)
            *b = *a + 1;
        else
            *b = (M1Vx278 *)((uint8_t *)base + ((*(volatile int32_t *)&n - 7) << 4));
        if (n & 1) {
            *c = *a;
            *a = *b;
            *b = *c;
        }
        if (n + 2 < 8)
            *c = &base[n + 2];
        else
            *c = (M1Vx278 *)((uint8_t *)base + ((*(volatile int32_t *)&n - 6) << 4));
        return;
    }
    if (n < 12) {
        i = (*(volatile int32_t *)&n * 3 - 24) * 4;
        *a = &base[*(int32_t *)((uint8_t *)cap + i)];
        *b = &base[*(int32_t *)((uint8_t *)cap + i + 4)];
        *c = &base[*(int32_t *)((uint8_t *)cap + i + 8)];
        return;
    }
    *a = base;
    *b = base + 1;
    *c = base + 2;
}
