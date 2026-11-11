/* Area rfl, group 13: enemy state choosers 0x00138B40..0x00138F60. Names inferred. */
#include "rfl.h"

/* 0x00138B40: pick state 0x10 when the enemy is close (+0x100 <= 12) and
   nearly facing (|+0xFC| <= pi/5), else 0x0D unless its target is already
   in state 0x0D; release node slot 3 and enter the state. */
void rfl_EnemyLunge(void *owner, RflFoe *e)
{
    int st;
    if (12.0f >= e->dist100 && !(0.628318548f < sub_001A3F30(e->angleFC))) {
        st = 0x10;
    } else {
        st = 0xD;
        if (e->kindF8 == 1 && (e->target104->flagsC & 1) && e->target104->state4 == st)
            return;
    }
    sub_00113480(e, 3);
    e->flags4C |= 0x10;
    e->body278->flags4 &= ~0x400000u;
    sub_00113040(owner, e, st);
}

/* 0x00138EA0: two-step turn: when idle play animation 0x0C/0x0D (by flag 1)
   and arm timer slot 6 with 0x0D; then turn to face the player, take the
   turn off +0xFC and reset the motion vector. */
void rfl_EnemyTurnToPlayer(RflActor *o, RflFoe *e)
{
    float *v;
    switch (e->step58) {
    case 0:
        if (!sub_000833E0(((RflNode *)o)->anim30))
            return;
        sub_00113090(o, e, (e->flags20 & 1) + 0xC);
        sub_00113430(e, 6)->v10 = 0xD;
        e->step58++;
        break;
    case 1:
        o->yaw54 = sub_00113200(o, rfl_playerObj->pos60) + o->yaw54 + 3.14159274f;
        e->angleFC = e->angleFC - (sub_00113200(o, rfl_playerObj->pos60) + 3.14159274f);
        v = (float *)(*(uint8_t **)((uint8_t *)o + 0x34) + 0x70);
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 0.0f;
        v[3] = 1.0f;
        break;
    }
}

/* 0x00139B30: 1 when the enemy should give up on the player: during a
   cut-scene, with body flag 0x400, at ground distance >= lim[0] or height
   difference >= lim[1]. */
int rfl_EnemyLostPlayer(RflActor *o, RflFoe *e, const float *lim)
{
    RflActor *p = rfl_playerObj;
    if (a80_Get3ED238())
        return 1;
    if (e->flags4C & 0x400)
        return 1;
    if (r4_DistanceXZ(o->pos60, p->pos60) >= lim[0])
        return 1;
    if (sub_001A3F30(o->pos60[1] - p->pos60[1]) >= lim[1])
        return 1;
    return 0;
}

/* 0x00139BB0: 1 when the enemy may attack its target: no global hold at
   0x003F7504, a target of kind 1 in state 1 with fewer than 3 attackers,
   within lim[0] and inside the angle window lim[1] (a negative window is
   measured from pi). */
int rfl_EnemyCanAttack(RflFoe *e, const float *lim)
{
    RflFoeTarget *t;
    float fa;
    if (rfl_f3F7504 > 0.0f)
        return 0;
    if (e->kindF8 != 1)
        return 0;
    t = e->target104;
    if (!(t->flagsC & 1) || t->state4 != 1 || t->i8 >= 3)
        return 0;
    if (e->dist100 > lim[0])
        return 0;
    fa = sub_001A3F30(e->angleFC);
    if (lim[1] >= 0.0f) {
        if (!(fa > lim[1]))
            return 1;
    } else {
        if (!(lim[1] + 3.14159274f > fa))
            return 1;
    }
    return 0;
}

/* 0x0013A7B0: jump attack progress: step 0 plays animation 0x42 once the
   enemy is more than 10 x its scale from the jump point; step 1 waits for
   body flags 0x18; step 2 waits for the animation to finish. Returns 1
   when the step completes. */
int rfl_EnemyJumpStep(RflActor *o, RflFoe *e)
{
    switch (e->step58) {
    case 0:
        if (r4_Distance(o->pos60, e->v88) > o->scale70 * 10.0f) {
            sub_00113090(o, e, 0x42);
            return 1;
        }
        break;
    case 1:
        if (o->flags128 & 0x18)
            return 1;
        break;
    case 2:
        if (sub_000833E0(o->anim30)) {
            o->flagsC |= 0x20;
            return 1;
        }
        break;
    }
    return 0;
}

/* 0x0013A840: launch the jump: face the point o - v88, set the velocity
   +0x78 to v88 scaled by 60, arm slot 4 and update the body flags. */
void rfl_EnemyJumpLaunch(RflActor *o, RflFoe *e)
{
    float t[4];
    float a;
    sub_001ADBA0(t, e->v88, -1.0f);
    r4c_VecAdd(t, t, o->pos60);
    a = sub_00113200(o, t);
    o->yaw54 = a + o->yaw54;
    e->angleFC = e->angleFC - a;
    sub_001ADB60(e->v78, e->v88, 60.0f);
    sub_00113400(e, 4);
    e->body278->flags4 |= 0x100000;
    o->flagsC &= ~0xA0u;
    o->flags10 |= 4;
    e->body278->flags4 &= ~0x200000u;
    o->flagsF0 |= 1;
}
