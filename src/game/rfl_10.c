/* Area rfl, group 10: boss and minion movement steps (0x000FA060..0x001005E6). Names inferred. */
#include "rfl.h"

/* 0x000FA060: start circling the player: random wait of 2.0..5.0 seconds,
   random direction, and an angular rate of speed / radius. */
void rfl_BossCircleInit(RflActor *o)
{
    RflAiState *st = sub_000F5F80(o);
    sub_000F62F0(st, 2);
    st->waitB8 = (float)(sub_001C7EE1() % 31 + 20) * 0.1f;
    st->dir146 = (int16_t)(sub_001C7EE1() & 1);
    st->radius148 = r4_DistanceXZ(o->pos60, rfl_playerObj->pos60);
    st->rate14C = r2c_BossStepSpeed(o) / (st->radius148 * 6.28318548f) * 6.28318548f;
    st->angle150 = rfl_ActorHeading(o);
    st->on144 = 1;
    st->tA0 = 0.0f;
}

/* 0x000FB0C0: move by the velocity at +0x184 and add the step length to
   the travelled distance; after 60 units, or when flags 6 are set at
   +0x128, stop and go to step 0x19. */
void rfl_BossSlide(RflActor *o)
{
    RflAiState *st = sub_000F5F80(o);
    float *vel = st->vel184;
    r4c_VecAdd(o->pos60, o->pos60, vel);
    st->distF0 += afc_VecLengthXZ(vel);
    sub_000C56B0(o);
    if (st->distF0 >= 60.0f || (*(uint8_t *)((uint8_t *)o + 0x128) & 6)) {
        sub_000C62A0(o);
        sub_000F62C0(st, 0x19);
    }
}

/* 0x000FB4D0: keep the actor within 108 units of the arena centre
   0x00318E18 on the ground plane (only when the helper allows it). */
void rfl_ClampToArena(RflActor *o)
{
    float d[4];
    float len;
    if (!o)
        return;
    if (!sub_000FC4D0()->turnE8)
        return;
    sub_001AD9F0(d, o->pos60, rfl_vec318E18);
    len = afc_VecLengthXZ(d);
    if (len > 108.0f) {
        sub_001AD9F0(d, o->pos60, rfl_vec318E18);
        sub_001AD7E0(d, d);
        sub_001ADB60(d, d, len - 108.0f);
        sub_001AD9F0(o->pos60, o->pos60, d);
    }
}

/* 0x000FE8E0: minion chase step: above height 2 mark the minion done;
   within 40 units of the player go to step 0x1D; otherwise turn toward
   the player and walk forward at the boss step speed. */
void rfl_MinionChase(void *owner, RflActor *o)
{
    if (o->pos60[2] > 2.0f) {
        rfl_minion3F6120->doneBC = 1;
        return;
    }
    if (40.0f > r4_DistanceXZ(rfl_minion3F6120->link8C->pos60, rfl_playerObj->pos60)) {
        sub_000F3D10(owner, o, 0x1D);
        return;
    }
    sub_000F7C40(o, rfl_playerObj, a50_frameUnits * 0.0523598790f);
    rfl_ActorStep(o, r2c_BossStepSpeed(o));
}

/* 0x00100540: as rfl_MinionChase for the controller at 0x003F6128: above
   height 2 go to step 0x0C; within 16 units go to step 0x1D. */
void rfl_CtlChase(void *owner, RflActor *o)
{
    if (o->pos60[2] > 2.0f) {
        sub_000F3D10(owner, o, 0xC);
        return;
    }
    if (16.0f > r4_DistanceXZ(rfl_ctl3F6128->link8C->pos60, rfl_playerObj->pos60)) {
        sub_000F3D10(owner, o, 0x1D);
        return;
    }
    sub_000F7C40(o, rfl_playerObj, a50_frameUnits * 0.0523598790f);
    rfl_ActorStep(o, r2c_BossStepSpeed(o));
}
