/* Area rfl, group 9: enemy behaviour steps that face the player (0x000F6BC0..0x000F9D8A). Names inferred. */
#include "rfl.h"

/* 0x000F6BC0: 1 when the enemy is in one of the modes 7..10 or 12 and its
   linked actor is at least 42 units from the player on the ground plane. */
int rfl_EnemyFarFromPlayer(RflEnemy *e)
{
    float d[4];
    int mode;
    if (!e)
        return 0;
    mode = e->mode6C;
    if (mode < 7 || (mode > 10 && mode != 12))
        return 0;
    sub_001AD9F0(d, rfl_playerObj->pos60, e->link8C->pos60);
    if (42.0f > sub_001A3F50(d[2] * d[2] + d[0] * d[0]))
        return 0;
    return 1;
}

/* 0x000F91D0: turn toward the player (5 degrees per frame unit) when the
   helper allows it; done when the node is active. */
void rfl_EnemyFacePlayerA(RflActor *o)
{
    RflAiState *st = sub_000F5F80(o);
    if (sub_000FC4D0()->turnE8)
        sub_000F7C40(o, rfl_playerObj, a50_frameUnits * 0.0872664675f);
    if (sub_000F5D00(o))
        st->doneBC = 1;
}

/* 0x000F9360: reset both animations, set a 2 second timer and snap to face
   the player. */
void rfl_EnemyFacePlayerInit(RflActor *o)
{
    RflAiState *st = sub_000F5F80(o);
    sub_000F62F0(st, 0);
    st->timerB4 = 2.0f;
    sub_000F7C40(o, rfl_playerObj, 3.14159274f);
}

/* 0x000F93A0: count the timer down (twice as fast within 40 units of the
   player); done when it runs out. */
void rfl_EnemyWaitNearPlayer(RflActor *o)
{
    RflAiState *st = sub_000F5F80(o);
    if (r4_DistanceXZ(o->pos60, rfl_playerObj->pos60) > 40.0f)
        st->timerB4 -= a50_frameSeconds;
    else
        st->timerB4 -= a50_frameSeconds * 2.0f;
    if (!(0.0f < st->timerB4))
        st->doneBC = 1;
}

/* 0x000F9CB0: turn toward the player (4.5 degrees per frame unit); when the
   node is active clear +0xAE and finish. */
void rfl_EnemyFacePlayerB(RflActor *o)
{
    RflAiState *st = sub_000F5F80(o);
    sub_000F7C40(o, rfl_playerObj, a50_frameUnits * 0.0785398185f);
    if (sub_000F5D00(o)) {
        st->flagAE = 0;
        st->doneBC = 1;
    }
}

/* 0x000F9D40: turn toward the player (4.5 degrees per frame unit); done when
   the node is active. */
void rfl_EnemyFacePlayerC(RflActor *o)
{
    RflAiState *st = sub_000F5F80(o);
    sub_000F7C40(o, rfl_playerObj, a50_frameUnits * 0.0785398185f);
    if (sub_000F5D00(o))
        st->doneBC = 1;
}
