/* Area rbl: boss set-up (the actor released by 0x00179E40). Names inferred. */
#include "rbl.h"
#include <string.h>

#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define RBL6_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) >> 2)
#else
#define RBL6_ZERO(p, n) memset((p), 0, (n))
#endif

/* 0x0017A820: set up the boss actor: install its callbacks and state tables, clear the
   shared block 0x003FDC3C and link it, place the body (position, scale 1.25), face it
   toward the block's home point (0x00113290) and rotate the model's local matrix to that
   yaw, then size its collision and reach values from the scale and enter state 1
   (0x0017A2B0). Returns 1. Stack args (o a); calls 0x0017A2B0 with EBX=o ESI=a and the
   state on the stack. */
int rbl_BossInit17A820(RblBody *o, RblBossAct *a)
{
    float m[16];
    float k;

    a->tab28C = rbl_states32B4C0;
    a->tab290 = rbl_states32B4D4;
    a->tab294 = rbl_states32B4E8;
    a->fn27C = sub_00179E40;
    a->fn29C = sub_0017A350;
    a->fn280 = sub_00179EC0;
    a->fn284 = sub_00179FE0;
    a->fn288 = sub_00145E10;
    a->fn298 = sub_00102FA0;
    RBL6_ZERO(&r3d_blk3FDC3C, sizeof(r3d_blk3FDC3C));
    a->work278 = &r3d_blk3FDC3C;
    r3d_blk3FDC3C.obj2C = o;
    o->pos60[2] = -177.7f;
    o->pos60[0] = -160.6f;
    o->pos60[3] = 1.0f;
    o->f5C = 1.0f;
    o->pos60[1] = 0.0f;
    o->f50 = 0.0f;
    o->yaw54 = 0.0f;
    o->f58 = 0.0f;
    o->scale70[0] = 1.25f;
    o->scale70[1] = 1.25f;
    o->scale70[2] = 1.25f;
    o->f7C = 0.0f;
    o->yaw54 = sub_00113290(o, r3d_blk3FDC3C.v04);
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->yaw54);
    sub_001AD7C0(o->model20 + 0x40, o->model20 + 0x40, m);
    a->desc30 = rbl_desc32B49C;
    a->i54 = 0;
    a->i50 = 0;
    a->i24 = 3;
    o->iD0 = sub_0001BC40(o);
    o->fB4 = o->scale70[0] * -14.0f;
    k = o->scale70[0] * 5.6f;
    o->fB0 = k;
    o->fDC = o->scale70[0] * -7.5f;
    o->i124 = 1;
    o->iEC = 0;
    o->fE8 = k;
    o->i118 = 0;
    o->fFC = o->fDC;
    o->f10C = 0.0f;
    o->iF0 = 2;
    o->uF4 = 2;
    o->i11C = 1;
    o->u120 = 2;
    o->flags0C |= 0x100;
    a->f28 = o->scale70[0] * -10.0f;
    a->f2C = o->scale70[0] * -17.0f;
    o->flags10 |= 0x480;
    a->snd6C = -1;
    r3d_blk3FDC3C.f20 = 5.0f;
    r3_SetStateD(o, a, 1);
    return 1;
}

/* 0x0017B320: the boss throws: mark the body (flags), aim a velocity of 80 away from Jack
   in the ground plane with a fixed downward slope (-1.5 before normalising), turn the body
   toward Jack (0x00113200), flag joint 0, reset timer node 0 and the animation rate, spawn
   the thrown effect chosen by 0x0017AF00 with that velocity, release node 2 and its effect
   and play sound 0x19B. Stack args (o a); calls 0x0017AF00 with EAX=a and o on the stack. */
void rbl_BossThrow17B320(RblBody *o, RblBossAct *a)
{
    float v[4];
    float len;
    RblJoint *j;
    RblNode *n;
    float *pos = o->pos60;
    const float *jack = ((RblObj *)g_playerObj)->pos60;

    o->flags10 = (o->flags10 & ~0x20u) | 0xD;
    o->flags128 &= ~0x18u;
    o->flags0C &= ~0x80u;
    v[0] = pos[0] - jack[0];
    v[1] = pos[1] - jack[1];
    v[2] = pos[2] - jack[2];
    v[3] = pos[3];
    len = sub_001A3F50(v[2] * v[2] + v[0] * v[0]);
    len = 1.0f / len;
    v[2] = len * v[2];
    v[3] = 0.0f;
    v[0] = len * v[0];
    v[1] = -1.5f;
    sub_001AD7E0(v, v);
    sub_001ADB60(a->v78, v, 80.0f);
    o->yaw54 += sub_00113200(o, ((RblObj *)g_playerObj)->pos60);
    j = sub_0001D0F0(o, 0);
    j->flags90 |= 0x40;
    sub_001133E0(a, 0)->f10 = 0.0f;
    sub_001AEDD0(o->anim30->inst14, 0.0f);
    sub_000A8ED0(sub_0017AF00(a, o), pos, a->v78, 0);
    n = sub_001133E0(a, 2);
    if (n != 0) {
        if (n->i14 >= 0)
            sub_000A7950(n->i14);
        sub_00113370(a, n);
    }
    sub_000494D0(0x19B, pos, 0);
}

/* 0x0017B4D0: as 0x0017B320 with a flat throw: the velocity is the ground-plane direction
   away from Jack scaled by 80 (no slope, no normalising) and is also kept as the initial
   velocity (+0x88); the body's +0x0C and +0x128 flags are left alone.
   Stack args (o a); calls 0x0017AF00 with EAX=a and o on the stack. */
void rbl_BossThrowFlat17B4D0(RblBody *o, RblBossAct *a)
{
    float v[4];
    float len;
    RblJoint *j;
    RblNode *n;
    float *pos = o->pos60;
    const float *jack;

    o->flags10 = (o->flags10 & ~0x20u) | 0xD;
    jack = ((RblObj *)g_playerObj)->pos60;
    v[0] = o->pos60[0] - jack[0];
    v[1] = o->pos60[1] - jack[1];
    v[2] = pos[2] - jack[2];
    v[3] = o->pos60[3];
    len = sub_001A3F50(v[2] * v[2] + v[0] * v[0]);
    len = 1.0f / len;
    v[0] = len * v[0];
    v[1] = 0.0f;
    v[2] = len * v[2];
    v[3] = 0.0f;
    sub_001ADB60(a->v78, v, 80.0f);
    sub_000F5D40(a->v88, a->v78);
    o->yaw54 += sub_00113200(o, ((RblObj *)g_playerObj)->pos60);
    j = sub_0001D0F0(o, 0);
    j->flags90 |= 0x40;
    sub_001133E0(a, 0)->f10 = 0.0f;
    sub_001AEDD0(o->anim30->inst14, 0.0f);
    sub_000A8ED0(sub_0017AF00(a, o), pos, a->v78, 0);
    n = sub_001133E0(a, 2);
    if (n != 0) {
        if (n->i14 >= 0)
            sub_000A7950(n->i14);
        sub_00113370(a, n);
    }
    sub_000494D0(0x19B, pos, 0);
}

/* 0x00179C00: set up minion k (0..8) of the boss in slot k of the pool 0x003FDAF8. Fails
   (returns 0) without a body, for k >= 9 or when the slot is taken. Links body, actor and
   slot, installs the callbacks and state tables, flags the body, takes its health from the
   stat table (0x00171D50), sizes it (0x000F5D60), hides it, places it at its table point
   and yaw, clears the slot's vector and counter, plays animation 5 and enters state 1.
   Returns 1. Stack args (o a k). */
int rbl_MinionInit179C00(RblBody *o, RblBossAct *a, int k)
{
    RblSlot24 *s;
    float hp;

    if (o == 0)
        return 0;
    if (k >= 9)
        return 0;
    s = &b7c_pool3FDAF8[k];
    if (s->obj00 != 0)
        return 0;
    a->work278 = s;
    s->obj00 = o;
    s->act04 = a;
    s->s14 = (int16_t)k;
    a->tab28C = rbl_states32B3B4;
    a->tab290 = rbl_states32B3CC;
    a->fn27C = sub_00179190;
    a->fn288 = sub_00179240;
    a->fn29C = sub_001792D0;
    o->flags10 |= 0x44D;
    o->flags0C = (o->flags0C & ~0xC0u) | 3;
    hp = sub_00171D50(o->i04, o->i08, 0);
    a->maxHp270 = hp;
    a->hp274 = hp;
    a->i24 = 1;
    o->i124 = 0;
    sub_000F5D60(o, 1.0f, -24.0f, 7.5f, rbl_place27A418);
    a->f28 = -10.0f;
    a->f2C = -33.0f;
    o->scale70[2] = 1.0f;
    o->scale70[1] = 1.0f;
    o->scale70[0] = 1.0f;
    sub_0001D700(o);
    sub_000F5D40(o->pos60, rbl_minionPos27A468[k]);
    o->yaw54 = rbl_minionYaw27A4F8[k];
    s->v18[0] = 0.0f;
    s->v18[1] = 0.0f;
    s->v18[2] = 0.0f;
    s->i10 = 0;
    sub_000832D0(o->anim30, 5);
    sub_00113040(o, a, 1);
    return 1;
}

/* 0x00178EB0: set up a boss of the 0x001784D0 family: callbacks and state tables, scale
   1, collision and reach values, home point = current position (+0x88), then enter state
   0, 9 or 10 for mode 0, 1 or 2 and return 1 (0 for any other mode).
   Stack args (o a mode). */
int rbl_BossInit178EB0(RblBody *o, RblBossAct *a, int mode)
{
    a->tab28C = rbl_states32B344;
    a->tab290 = rbl_states32B370;
    a->fn27C = sub_001784D0;
    a->fn29C = sub_001784E0;
    a->fn280 = sub_001786F0;
    a->fn284 = sub_001787A0;
    a->fn288 = sub_00145E10;
    o->scale70[2] = 1.0f;
    o->scale70[1] = 1.0f;
    o->scale70[0] = 1.0f;
    o->f7C = 1.0f;
    o->iD0 = sub_0001BC40(o);
    o->fB0 = 2.8f;
    o->fB4 = -5.5f;
    o->fA4 = 2.75f;
    o->fE8 = 2.7f;
    o->f10C = 2.5f;
    o->uF4 = 0x80000000u;
    o->u120 = 0x80000000u;
    o->fDC = 0.0f;
    o->iEC = 1;
    o->i118 = 0;
    o->fFC = -5.0f;
    o->iF0 = 2;
    o->i11C = 1;
    a->f28 = 0.0f;
    a->f2C = -8.0f;
    o->flags10 |= 0x200;
    o->flags0C |= 0x100;
    sub_000F5D40(a->v88, o->pos60);
    switch (mode) {
    case 0:
        sub_00113040(o, a, 0);
        return 1;
    case 1:
        sub_00113040(o, a, 9);
        return 1;
    case 2:
        sub_00113040(o, a, 10);
        return 1;
    }
    return 0;
}
