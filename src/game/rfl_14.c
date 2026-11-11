/* Area rfl, group 14: enemy wake-up and attack steps (0x0013BC40..0x00140621). Names inferred. */
#include "rfl.h"

/* 0x0013BC40: guard step: state 9 when check 0 of table 0x0031CE18 says the
   player is lost; otherwise wait 10 frame units, show the actor, then state
   5 once the player is within 40 units. */
void rfl_EnemyGuardStep(RflActor *o, RflFoe *e)
{
    if (rfl_checks31CE18[0](o, e, rfl_lim279798)) {
        sub_00113040(o, e, 9);
        return;
    }
    switch (e->step58) {
    case 0:
        if (e->t5C >= 10.0f / a50_frameUnits * a50_frameSeconds) {
            sub_0001D610(o);
            e->step58++;
        }
        break;
    case 1:
        if (40.0f >= r4_DistanceXZ(o->pos60, rfl_playerObj->pos60))
            sub_00113040(o, e, 5);
        break;
    }
}

/* 0x0013FE60: when the animation is idle choose state 0x13 (target of
   kind 1 in state 1 with fewer than 3 attackers, within 30 units and 40
   degrees) or 0x14. */
void rfl_EnemyAttackOrWait(RflActor *o, RflFoe *e)
{
    RflFoeTarget *t;
    if (!sub_000833E0(o->anim30))
        return;
    e->flags4C |= 0x10;
    if (e->kindF8 == 1) {
        t = e->target104;
        if ((t->flagsC & 1) && t->state4 == 1 && t->i8 < 3 &&
            30.0f >= rfl_TargetDistance(o, (RflTarget *)e) &&
            0.698131740f >= sub_001A3F30(e->angleFC)) {
            sub_00113040(o, e, 0x13);
            return;
        }
    }
    sub_00113040(o, e, 0x14);
}

/* 0x00140580: ambush step: state 0x0A when check 0 of table 0x0031D0B8 says
   the player is lost; otherwise once +0x74 runs out show the actor and
   start its animation, then state 5 once the player is within 20 units. */
void rfl_EnemyAmbushStep(RflActor *o, RflFoe *e)
{
    if (rfl_checks31D0B8[0](o, e, rfl_lim2797C8)) {
        sub_00113040(o, e, 0xA);
        return;
    }
    switch (e->step58) {
    case 0:
        if (!(0.0f < e->f74)) {
            sub_0001D610(o);
            sub_001AEDD0(((RflAnimInst *)o->anim30)->inst14,
                         ((RflAnimKey *)sub_00083120(o->anim30, e->anim64))->v10);
            e->step58++;
        }
        break;
    case 1:
        if (20.0f >= r4_DistanceXZ(o->pos60, rfl_playerObj->pos60))
            sub_00113040(o, e, 5);
        break;
    }
}
