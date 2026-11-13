/* Area m1, file 65: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1RigP { uint8_t unk00[4]; uint32_t flags04; uint8_t unk08[0x2C - 8]; float q2C[4]; } M1RigP;
typedef struct M1StepP { uint8_t unk000[0x278]; M1RigP *rig278; } M1StepP;
typedef struct M1ObjP { uint8_t unk00[0x10]; uint32_t flags10; } M1ObjP;
typedef struct M1CmdP { uint8_t unk00[0x10]; float v10[4]; } M1CmdP;
int     sub_001456E0(void *o, void *s, int a, int b);
void    sub_0001D4E0(void *o);
M1CmdP *sub_00113400(void *h, int v);
void    sub_001199C0(void *o, void *h);

/* 0x00119C80: 0x1456E0(0x18) (0x1D4E0 on 1), rig quaternion +0x2C = (0, 0, 0, 1), o flags
 * |= 5 then 4, rig flag 0x100, command 4 = (1/12, 0, 0, 0), then 0x1199C0 twice. */
void m1_RigStep119C80(M1ObjP *o, M1StepP *h)
{
    M1RigP *r = h->rig278;
    M1RigP *p;
    M1CmdP *c;
    int n;
    if (sub_001456E0(o, h, 0x18, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q2C[2] = 0.0f;
    p->q2C[1] = 0.0f;
    p->q2C[0] = 0.0f;
    p->q2C[3] = 1.0f;
    o->flags10 |= 5;
    r->flags04 |= 0x100;
    o->flags10 |= 4;
    c = sub_00113400(h, 4);
    c->v10[0] = 1.0f / 12.0f;
    c->v10[1] = 0.0f;
    c->v10[2] = 0.0f;
    c->v10[3] = 0.0f;
    for (n = 2; n != 0; n--)
        sub_001199C0(o, h);
}

typedef struct M1Leash { uint8_t flags00; uint8_t unk01[3]; float t04, t08; } M1Leash;
typedef struct M1StepQ2 { uint8_t unk000[0x50]; int32_t state50; uint8_t unk054[0x278 - 0x54]; M1Leash *rig278; } M1StepQ2;
typedef struct M1PosQ { uint8_t unk00[0x60]; float pos60[4]; } M1PosQ;
extern M1PosQ *g_playerObj;
extern float m1_frameRate42C85C;
float sub_001B2770(const float *a, const float *b);
int   sub_00087500(void);
void  sub_00113040(void *o, void *h, int next);

/* 0x00175430: leash timer +0x04 counts down; unless flag 8 or already in state 2, goes to
 * state 2 when the player is over 200 away or o is over 100 above or below them; also
 * state 2 when 0x87500 says so. */
void m1_Leash175430(M1PosQ *o, M1StepQ2 *h)
{
    M1Leash *r = h->rig278;
    float d = sub_001B2770(o->pos60, g_playerObj->pos60);
    float dy = o->pos60[1] - g_playerObj->pos60[1];
    r->t04 -= m1_frameRate42C85C;
    if (!(r->flags00 & 8) && h->state50 != 2 &&
        (d > 200.0f || dy > 100.0f || -100.0f > dy))
        sub_00113040(o, h, 2);
    if (sub_00087500() != 0 && h->state50 != 2)
        sub_00113040(o, h, 2);
}

/* 0x00176510: as 0x175430 with timer +0x08, flag 4 and state 3 (height tests in the
 * other order). */
void m1_Leash176510(M1PosQ *o, M1StepQ2 *h)
{
    M1Leash *r = h->rig278;
    float d = sub_001B2770(o->pos60, g_playerObj->pos60);
    float dy = o->pos60[1] - g_playerObj->pos60[1];
    r->t08 -= m1_frameRate42C85C;
    if (!(r->flags00 & 4) && h->state50 != 3 &&
        (d > 200.0f || -100.0f > dy || dy > 100.0f))
        sub_00113040(o, h, 3);
    if (sub_00087500() != 0 && h->state50 != 3)
        sub_00113040(o, h, 3);
}

typedef struct M1Glow {
    uint8_t unk00[0x50];
    float   v50[4];            /* +0x50 */
    float   pos60[3];          /* +0x60 */
    float   w6C;               /* +0x6C */
    float   size70;            /* +0x70 */
    uint8_t unk74[0xA0 - 0x74];
    float   ofsA0[3];          /* +0xA0 */
} M1Glow;
typedef struct M1GlowSt { uint8_t unk00[0x74]; float t74; } M1GlowSt;
void sub_00113AA0(void *o, void *h);
void sub_000C7540(void *o, float a, float size, const float *pos, const float *v);

/* 0x001771E0: once the timer +0x74 is below 0 ends the step (0x113AA0, state 0); else
 * draws the glow at position + offset (+0xA0) with size +0x70 * 0.8 (0xC7540). */
void m1_Glow1771E0(M1Glow *o, M1GlowSt *h)
{
    float p[4];
    if (0.0f > h->t74) {
        sub_00113AA0(o, h);
        sub_00113040(o, h, 0);
        return;
    }
    p[0] = o->pos60[0] + o->ofsA0[0];
    p[1] = o->pos60[1] + o->ofsA0[1];
    p[2] = o->pos60[2] + o->ofsA0[2];
    p[3] = o->w6C;
    sub_000C7540(o, 1.0f, o->size70 * 0.8f, p, o->v50);
}

typedef struct M1StepK2 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t state58; } M1StepK2;
typedef struct M1ObjK2 { uint8_t unk00[0x30]; int32_t anim30; } M1ObjK2;
int  sub_00194EB0(void);
int  sub_000833E0(int a);
void sub_00113480(void *h, int v);
int  sub_00145780(void *o, float t);
void sub_001151A0(void *h, int v);
void sub_00117580(void *o, int v);

/* 0x00118410: h flag 0x100 when 0x194EB0 says so; state 0 waits for the animation
 * (0x833E0), then 0x113480(1) and on into state 1: 0x1456E0(0x22) (0x1D4E0 on 1), state 2;
 * state 2: 0x1151A0(0) once 0x145780(2.0) fires and 0x117580(1) when the animation ends. */
void m1_Step118410(M1ObjK2 *o, M1StepK2 *h)
{
    if (sub_00194EB0() != 0)
        h->flags4C |= 0x100;
    switch (h->state58) {
    case 0:
        if (sub_000833E0(o->anim30) == 0)
            break;
        sub_00113480(h, 1);
        h->state58++;
        /* fall through */
    case 1:
        if (sub_001456E0(o, h, 0x22, 0) == 1)
            sub_0001D4E0(o);
        h->state58++;
        break;
    case 2:
        if (sub_00145780(o, 2.0f) != 0)
            sub_001151A0(h, 0);
        if (sub_000833E0(o->anim30) != 0)
            sub_00117580(o, 1);
        break;
    }
}

typedef struct M1RigI {
    uint8_t unk000[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint8_t unk010[0x164 - 0x10];
    float   q164[4];           /* +0x164 */
    uint8_t unk174[0x198 - 0x174];
    int32_t kind198;           /* +0x198 */
} M1RigI;
typedef struct M1StepI { uint8_t unk000[0x58]; int32_t state58; uint8_t unk05C[0x278 - 0x5C]; M1RigI *rig278; } M1StepI;
void sub_000414A0(int v);

/* 0x0012FCA0: 0x1456E0(0x33) (0x1D4E0 on 1), rig quaternion +0x164 = (0, 0, 0, 1), clears
 * rig flag 0x1000000, o flag 4, command 6 = (1/12, 0, 0, 0); o flags |= 0xD with rig
 * flag 0x20. */
void m1_RigIdle12FCA0(M1ObjP *o, M1StepI *h)
{
    M1RigI *r = h->rig278;
    M1RigI *p;
    M1CmdP *c;
    if (sub_001456E0(o, h, 0x33, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q164[2] = 0.0f;
    p->q164[1] = 0.0f;
    p->q164[0] = 0.0f;
    p->q164[3] = 1.0f;
    r->flags0C &= ~0x1000000u;
    o->flags10 |= 4;
    c = sub_00113400(h, 6);
    c->v10[0] = 1.0f / 12.0f;
    c->v10[1] = 0.0f;
    c->v10[2] = 0.0f;
    c->v10[3] = 0.0f;
    if (*(uint8_t *)&r->flags0C & 0x20)
        o->flags10 |= 0xD;
}

/* 0x0012FF80: 0x1456E0(0x13) (0x1D4E0 on 1), rig quaternion +0x164 = (0, 0, 0, 1), o flag 4,
 * 0x414A0(1), next state from rig kind +0x198: 0x24 -> 10, 0x1E -> 0x14, 0x1F -> 0x1E. */
void m1_RigIdle12FF80(M1ObjP *o, M1StepI *h)
{
    M1RigI *r = h->rig278;
    M1RigI *p;
    if (sub_001456E0(o, h, 0x13, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q164[2] = 0.0f;
    p->q164[1] = 0.0f;
    p->q164[0] = 0.0f;
    p->q164[3] = 1.0f;
    o->flags10 |= 4;
    sub_000414A0(1);
    if (r->kind198 == 0x24)
        h->state58 = 10;
    else if (r->kind198 == 0x1E)
        h->state58 = 0x14;
    else if (r->kind198 == 0x1F)
        h->state58 = 0x1E;
}
