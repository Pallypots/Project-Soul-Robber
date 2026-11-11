/* Area rfl, group 12: enemy step chooser (0x001238A0). Names inferred. */
#include "rfl.h"

/* 0x001238A0: when the enemy's animation is idle pick its next step:
   0x11 when the player is out of reach, 7 when the body flag 1 is set,
   otherwise 6 (the player distance is computed and dropped).
   calls 0x00120820 with EAX=b ESI=o; calls 0x0011F2B0 with EDI=o EBX=step
   and b on the stack */
void rfl_EnemyPickStep(RflActor *o, RflBody *b)
{
    if (!sub_000833E0(((RflNode *)o)->anim30))
        return;
    if (r2_PlayerOutOfReach(b, o)) {
        sub_0011F2B0(o, 0x11, b);
        return;
    }
    if (b->flags20 & 1) {
        sub_0011F2B0(o, 7, b);
        return;
    }
    r4_DistanceXZ(o->pos60, rfl_playerObj->pos60);
    sub_0011F2B0(o, 6, b);
}
