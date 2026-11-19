/* Area m1, file 231: actor message handlers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1Ext231 { uint32_t flags0; uint8_t unk04[0x14]; float t18; uint8_t unk1C[4]; float t20; } M1Ext231;
typedef struct M1Obj231 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1Obj231;
typedef struct M1Act231 { uint8_t unk00[0x278]; M1Ext231 *ext278; } M1Act231;
typedef struct M1Msg231 { int32_t kind; int32_t n4; } M1Msg231;
extern float a50_frameSeconds;
void Grade_AddExclamations(int32_t n);
void r3_SetStateD(M1Obj231 *obj, M1Act231 *act, int state);   /* regargs: obj=EBX act=ESI state=stack */


typedef struct M1Ext231b { uint8_t flags0; } M1Ext231b;
typedef struct M1Obj231b { uint8_t unk00[0x30]; void *mdl30; } M1Obj231b;
typedef struct M1Act231b { uint8_t unk00[0x68]; float t68; uint8_t unk6C[0x278 - 0x6C]; M1Ext231b *ext278; } M1Act231b;
extern float a50_frameUnits;
int32_t sub_000833E0(void *m);
void sub_00113040(M1Obj231b *o, M1Act231b *a, int32_t z);
int32_t sub_00036750(M1Obj231b *o, int32_t pose);
void r3_MakeEffect176930(M1Act231b *a);   /* regargs: a=EAX */

/* 0x00176C60: when the clip ends hand over to 0x113040; otherwise after 64 frames switch to pose 0 once (flag 0x80)
   and after 72 frames spawn the effect once (flag 0x40) (calls 0x176930 with a=EAX). */
void m1_Timed176C60(M1Obj231b *o, M1Act231b *a)
{
    M1Ext231b *e = a->ext278;
    if (sub_000833E0(o->mdl30)) {
        sub_00113040(o, a, 0);
        return;
    }
    if (a->t68 > 64.0f / a50_frameUnits * a50_frameSeconds && !(e->flags0 & 0x80)) {
        sub_00036750(o, 0);
        e->flags0 |= 0x80;
    }
    if (a->t68 > 72.0f / a50_frameUnits * a50_frameSeconds && !(e->flags0 & 0x40)) {
        r3_MakeEffect176930(a);
        e->flags0 |= 0x40;
    }
}

typedef struct M1Body231 { uint8_t unk00[0x50]; uint8_t v50[0x10]; float p60, p64, p68, p6C; int32_t n70;
    uint8_t unk74[0x2C]; float dA0, dA4, dA8; } M1Body231;
typedef struct M1BodyS231 { uint8_t unk00[0x74]; float t74; } M1BodyS231;
void r2_BodyReattach(M1BodyS231 *obj, M1Body231 *b);   /* regargs: obj=EAX b=EDI */
void sub_00113040b(M1Body231 *o, M1BodyS231 *s, int32_t mode);
void sub_000C7540(M1Body231 *o, float k, int32_t n, const float *pos, void *v);

/* 0x0011DB30: when t74 runs out reattach the body and hand over to 0x113040 mode 5; otherwise draw at position
   p + d (calls 0x11B1C0 with obj=EAX b=EDI). */
void m1_BodyTick11DB30(M1Body231 *o, M1BodyS231 *s)
{
    float p[4];
    if (s->t74 <= 0.0f) {
        r2_BodyReattach(s, o);
        sub_00113040b(o, s, 5);
        return;
    }
    p[0] = o->p60 + o->dA0;
    p[1] = o->p64 + o->dA4;
    p[2] = o->p68 + o->dA8;
    p[3] = o->p6C;
    sub_000C7540(o, 1.0f, o->n70, p, o->v50);
}

typedef struct M1GE231 { uint8_t unk00[0xC]; uint8_t flagsC; uint8_t unk0D[0x177]; float f184; } M1GE231;
typedef struct M1GS231 { uint8_t unk00[0x278]; M1GE231 *ext278; } M1GS231;
typedef struct M1GO231 { uint8_t unk00[0x30]; void *mdl30; } M1GO231;
int32_t sub_001457C0(M1GO231 *o, float a, float b);
int32_t r2_PlayerInFrontB(M1GS231 *s, M1GO231 *o);         /* regargs: s=EAX */
void r3_SetStateA(M1GO231 *obj, M1GS231 *act, int state);   /* regargs: obj=EBX act=EDI state=stack */
int sub_001C7EE1(void);   /* rand */

/* 0x001339A0: if not flagged 0x20 and the player is within 11 units in front, set f184 = 0.3 and go to state 0x15
   (1 in 8) or 0xE; otherwise when the clip ends go to state 0x2B (flag 0x20) or 5 (calls 0x12E630 with s=EAX,
   0x131310 with obj=EBX act=EDI). */
void m1_Watch1339A0(M1GO231 *o, M1GS231 *s)
{
    M1GE231 *e = s->ext278;
    if (!(e->flagsC & 0x20) && sub_001457C0(o, 11.0f, 3.40282347e+38f) && r2_PlayerInFrontB(s, o)) {
        e->f184 = 0.3f;
        if (!(sub_001C7EE1() & 7)) {
            r3_SetStateA(o, s, 0x15);
            return;
        }
        r3_SetStateA(o, s, 0xE);
        return;
    }
    if (sub_000833E0(o->mdl30)) {
        if (e->flagsC & 0x20) {
            r3_SetStateA(o, s, 0x2B);
            return;
        }
        r3_SetStateA(o, s, 5);
    }
}

/* 0x00133A50: as 0x1339A0 with a 10-unit range and state 0x15 1 time in 4. */
void m1_Watch133A50(M1GO231 *o, M1GS231 *s)
{
    M1GE231 *e = s->ext278;
    if (!(e->flagsC & 0x20) && sub_001457C0(o, 10.0f, 3.40282347e+38f) && r2_PlayerInFrontB(s, o)) {
        e->f184 = 0.3f;
        if (!(sub_001C7EE1() & 3)) {
            r3_SetStateA(o, s, 0x15);
            return;
        }
        r3_SetStateA(o, s, 0xE);
        return;
    }
    if (sub_000833E0(o->mdl30)) {
        if (e->flagsC & 0x20) {
            r3_SetStateA(o, s, 0x2B);
            return;
        }
        r3_SetStateA(o, s, 5);
    }
}

typedef struct M1SpO231 { uint8_t unk00[0x54]; float r54; } M1SpO231;
typedef struct M1SpS231 { uint8_t unk00[0x54]; int32_t st54; uint8_t unk58[4]; float t5C; } M1SpS231;
void r3_SetState16C820(M1SpS231 *a, M1SpO231 *m, int state);   /* regargs: a=EAX m=EDI state=stack */

/* 0x0016E570: spin at 5 degrees per frame unit until t5C runs out, then for 60 frames spin down in proportion to
   the time left and go to state 0xE (calls 0x16C820 with a=EAX m=EDI). */
void m1_SpinDown16E570(M1SpO231 *o, M1SpS231 *s)
{
    switch (s->st54) {
    case 0:
        o->r54 += a50_frameUnits * 0.0872664675f;
        if (0.0f > s->t5C) {
            s->t5C = 60.0f / a50_frameUnits * a50_frameSeconds;
            s->st54++;
        }
        return;
    case 1:
        o->r54 += s->t5C / (60.0f / a50_frameUnits * a50_frameSeconds) * (a50_frameUnits * 0.0872664675f);
        if (0.0f > s->t5C)
            r3_SetState16C820(s, o, 0xE);
        return;
    }
}

struct M1Mgr231;
typedef struct M1Node231 { uint8_t unk00[0x8C]; int32_t kind8C; uint8_t unk90[0x20]; int32_t lB0;
    struct M1Mgr231 *ownerB4; int32_t lB8, lBC, lC0, lC4; uint8_t unkC8[4]; float sCC, sD0; int32_t lD4;
    uint8_t unkD8[0x44]; int32_t l11C; uint8_t unk120[0xC]; } M1Node231;
typedef struct M1Mgr231 { uint8_t unk00[0xB0]; uint32_t nB0; M1Node231 *nodesB4; } M1Mgr231;
void sub_001B25B0(M1Node231 *n);
void sub_001B2020(M1Mgr231 *m, M1Node231 *n);

/* 0x001B61B0: initialise the manager's nodes (0x12C bytes each) in nodes[], link each to m, and store the array. */
void m1_NodesInit1B61B0(M1Mgr231 *m, M1Node231 *nodes)
{
    uint32_t i;
    for (i = 0; i < m->nB0; i++) {
        M1Node231 *n = &nodes[i];
        n->kind8C = 0xF;
        sub_001B25B0(n);
        n->lB0 = 0;
        n->ownerB4 = 0;
        n->lB8 = 0;
        n->lBC = 0;
        n->lC0 = 0;
        n->lC4 = 0;
        n->sCC = 0.0f;
        n->sD0 = 0.0f;
        n->l11C = 0;
        n->lD4 = 0;
        sub_001B2020(m, n);
        n->ownerB4 = m;
    }
    m->nodesB4 = nodes;
}
