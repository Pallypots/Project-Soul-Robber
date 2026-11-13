/* Area m1, file 49: model show/hide chains and screen shuffles. Names inferred. */
#include <stdint.h>

typedef struct M1Node3C { uint8_t unk00[0x3C]; struct M1Node3C *next3C; } M1Node3C;
typedef struct M1Fade270 {
    uint8_t unk000[0x20];
    uint32_t flags20;          /* +0x20 */
    uint8_t unk024[0x270 - 0x24];
    float   max270;            /* +0x270 */
    float   cur274;            /* +0x274 */
} M1Fade270;
void sub_0001F070(M1Node3C *n, int on);
void sub_0001EBF0(M1Node3C *n, int mode);

/* 0x001130F0: show or hide every node in the chain (+0x3C); when shown sets flag 1,
 * draw mode 3 and grows +0x274 by half of +0x270 (capped at +0x270), else clears
 * flag 1 and draw mode 1. */
void m1_ChainShow1130F0(M1Node3C *n, M1Fade270 *h, int on)
{
    M1Node3C *p = n;
    float t;
    while (p != 0) {
        sub_0001F070(p, on ? 1 : 0);
        p = p->next3C;
    }
    if (on) {
        h->flags20 |= 1;
        sub_0001EBF0(n, 3);
        t = h->max270 * 0.5f + h->cur274;
        h->cur274 = t;
        if (t > h->max270)
            h->cur274 = h->max270;
    } else {
        h->flags20 &= ~1u;
        sub_0001EBF0(n, 1);
    }
}

typedef struct M1Mat108 { uint8_t unk00[0xE8]; float alphaE8; uint8_t unkEC[0x108 - 0xEC]; } M1Mat108;
typedef struct M1Mdl { uint8_t unk00[0xC0]; int32_t nC0; M1Mat108 *matC4; } M1Mdl;
typedef struct M1MdlNode { uint8_t unk00[0x20]; M1Mdl *mdl20; uint8_t unk24[0x3C - 0x24]; struct M1MdlNode *next3C; } M1MdlNode;
typedef struct M1H68b { uint8_t unk00[0x68]; float t68; } M1H68b;
typedef struct M1Comp6C { uint8_t unk00[0x6C]; int32_t mode6C; } M1Comp6C;
M1Comp6C *sub_0001D960(void *o, int kind);
void sub_000F3D10(void *o, void *c, int mode);
void sub_000F3B70(void *o, int v);

/* 0x0010A0A0: fade-out: while h +0x68 is under 0.6, every material of every model in
 * the chain gets alpha (0.6 - t) * 213.33; after that (spins on a null o) puts the
 * kind-5 component back to mode 0 and calls 0xF3B70(3). */
void m1_FadeOut10A0A0(M1MdlNode *o, M1H68b *h)
{
    M1MdlNode *p = o;
    M1Mdl *m;
    M1Comp6C *c;
    float a;
    int i, off;
    if (h->t68 < 0.6f) {
        a = (0.6f - h->t68) * 213.33333f;
        do {
            m = p->mdl20;
            for (i = 0, off = 0; i < m->nC0; i++, off += sizeof(M1Mat108))
                ((M1Mat108 *)((uint8_t *)m->matC4 + off))->alphaE8 = a;
            p = p->next3C;
        } while (p != 0);
        return;
    }
    if (o == 0)
        for (;;) ;
    c = sub_0001D960(o, 5);
    if (c->mode6C != 0)
        sub_000F3D10(o, c, 0);
    sub_000F3B70(o, 3);
}

typedef struct M1Act10 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x30 - 0x14]; int32_t f30; } M1Act10;
typedef struct M1Hit20 { uint8_t unk00[0x20]; uint32_t flags20; uint8_t unk24[0x74 - 0x24]; float f74; } M1Hit20;
int  sub_000833E0(int v);
int  aab_Rand(void);
void sub_00113040(void *o, void *h, int next);

typedef struct M1RigF { uint8_t unk00[4]; uint32_t flags04; } M1RigF;
typedef struct M1StepF {
    uint8_t unk000[0x270];
    float   f270, f274;        /* +0x270 */
    M1RigF *rig278;            /* +0x278 */
} M1StepF;
void sub_000253D0(int slot, int v);
void sub_00117580(void *o, int v);

/* 0x00119900: first time through (rig flag 0x2000) writes +0x270 and +0x274 as ints to
 * slots 5 and 6 and 0 to slot 4 (0x253D0); then 0x117580(1) once 0x833E0(o +0x30) is ready. */
void m1_RigOnce119900(M1Act10 *o, M1StepF *h)
{
    M1RigF *r = h->rig278;
    if (!(r->flags04 & 0x2000)) {
        r->flags04 |= 0x2000;
        sub_000253D0(5, (int)h->f270);
        sub_000253D0(6, (int)h->f274);
        sub_000253D0(4, 0);
    }
    if (sub_000833E0(o->f30) != 0)
        sub_00117580(o, 1);
}

typedef struct M1Fl60b { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[3]; } M1Fl60b;
typedef struct M1Cmd10 { uint8_t unk00[0x10]; int32_t f10, f14, f18; } M1Cmd10;
void     sub_00113090(void *o, void *h, int next);
M1Cmd10 *sub_00113430(void *h, int v);
void     sub_0019E970(float a, float b);
int      sub_000494D0(int id, const void *pos, int c);
int      sub_00036750(void *o, int v);

/* 0x0011A950: o flag 4, clear rig flag 2, next state 0x26 (0x113090), command 2 set to
 * (6, 2, 0xC3), shake 0x19E970(4.0, 2.0), sound 0xC9 at o and 0x36750(0xC). */
void m1_RigStep11A950(M1Fl60b *o, M1StepF *h)
{
    M1Cmd10 *c;
    o->flags10 |= 4;
    h->rig278->flags04 &= ~2u;
    sub_00113090(o, h, 0x26);
    c = sub_00113430(h, 2);
    c->f10 = 6;
    c->f14 = 2;
    c->f18 = 0xC3;
    sub_0019E970(4.0f, 2.0f);
    sub_000494D0(0xC9, o->pos60, 0);
    sub_00036750(o, 0xC);
}

typedef struct M1Rig160 {
    uint8_t unk000[8];
    uint32_t flags08, flags0C; /* +0x08 */
    uint8_t unk010[0x160 - 0x10];
    float   v160[5];           /* +0x160 */
} M1Rig160;
typedef struct M1Step160 {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x74 - 0x50];
    float   f74;               /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig160 *rig278;          /* +0x278 */
} M1Step160;
typedef struct M1Fl0C { uint8_t unk00[0xC]; uint32_t flags0C, flags10; } M1Fl0C;
int  sub_001456E0(void *o, void *s, int a, int b);
void sub_0001D4E0(void *o);

/* Shared body of 0x12E720 / 0x1360B0: 0x1456E0(0) (0x1D4E0 on 1), rig quaternion at
 * +base = (0, 0, 0, 1), o flags: clear 0xE0 in +0xC, set 0x105 in +0x10, h +0x4C |= 0x70,
 * a rig flag word |= mask, h +0x74 = 1.0. */
#define M1_RIG_IDLE(name, base, FLAGS, mask)                \
void name(M1Fl0C *o, M1Step160 *h)                          \
{                                                           \
    M1Rig160 *r = h->rig278;                                \
    M1Rig160 *p;                                            \
    if (sub_001456E0(o, h, 0, 0) == 1)                      \
        sub_0001D4E0(o);                                    \
    p = h->rig278;                                          \
    p->v160[(base) + 2] = 0.0f;                             \
    p->v160[(base) + 1] = 0.0f;                             \
    p->v160[(base) + 0] = 0.0f;                             \
    p->v160[(base) + 3] = 1.0f;                             \
    o->flags0C &= ~0xE0u;                                   \
    o->flags10 |= 0x105;                                    \
    h->flags4C |= 0x70;                                     \
    r->FLAGS |= (mask);                                     \
    h->f74 = 1.0f;                                          \
}

/* 0x0012E720: rig idle, quaternion at +0x164, rig +0xC |= 0x204. */
M1_RIG_IDLE(m1_RigIdle12E720, 1, flags0C, 0x204)
/* 0x001360B0: rig idle, quaternion at +0x160, rig +0x8 |= 0x84. */
M1_RIG_IDLE(m1_RigIdle1360B0, 0, flags08, 0x84)

typedef struct M1RigC { uint8_t unk00[4]; uint32_t flags04; uint8_t unk08[0x18 - 8]; uint8_t fade18[0x34 - 0x18]; void *p34; } M1RigC;
typedef struct M1StepC {
    uint8_t unk000[0x22];
    uint8_t b22;               /* +0x22 */
    uint8_t unk023[0x4C - 0x23];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1RigC *rig278;            /* +0x278 */
} M1StepC;
typedef struct M1CmdF { uint8_t unk00[0x10]; float f10, f14; int32_t i18; void (*cb1C)(void); } M1CmdF;
typedef struct M1CmdF4 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1CmdF4;
extern float m1_frameTime42C858;
void sub_00113C60(void *fade, float a, float b);
void sub_0013D950(void);

/* 0x0013E390: next state 0x16 or 0x17 (h +0x22 bit 0), o flags: clear 0x20 set 2,
 * clear h +0x4C bit 0x10, rig fade 120 -> 255, 0x36750(0), command 1 = (0.3, 0.25, 1,
 * callback 0x13D950). */
void m1_RigStep13E390(M1Act10 *o, M1StepC *h)
{
    M1RigC *r = h->rig278;
    M1CmdF *c;
    sub_00113090(o, h, (h->b22 & 1) + 0x16);
    o->flags10 = (o->flags10 & ~0x20u) | 2;
    h->flags4C &= ~0x10u;
    sub_00113C60(r->fade18, 120.0f, 255.0f);
    sub_00036750(o, 0);
    c = (M1CmdF *)sub_00113430(h, 1);
    c->f10 = 0.3f;
    c->f14 = 0.25f;
    c->i18 = 1;
    c->cb1C = sub_0013D950;
}

/* 0x0013E770: spins on a null rig +0x34; next state 0x22, clear o flag 0x20 and h +0x4C
 * bits 0x30, rig flag 0x400000, rig fade 30 -> 255, command 3 = (frame time * 2 deg, 0,
 * 5 deg, 60 deg). */
void m1_RigStep13E770(M1Act10 *o, M1StepC *h)
{
    M1RigC *r = h->rig278;
    M1CmdF4 *c;
    if (r->p34 == 0)
        for (;;) ;
    sub_00113090(o, h, 0x22);
    o->flags10 &= ~0x20u;
    h->flags4C &= ~0x30u;
    r->flags04 |= 0x400000;
    sub_00113C60(r->fade18, 30.0f, 255.0f);
    c = (M1CmdF4 *)sub_00113430(h, 3);
    c->f10 = m1_frameTime42C858 * 0.034906585f;
    c->f14 = 0.0f;
    c->f18 = 0.087266468f;
    c->f1C = 1.0471976f;
}
