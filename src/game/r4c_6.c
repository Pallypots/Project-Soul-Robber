/* Area r4c: pop effect callers 0x00197160-0x001976A8 (r4c_6). Names inferred. */
#include "r4c.h"

/* 0x00197160: message handler of a pop effect: message 5 may switch the actor to state 2, then most
   hit messages pop the effect. Stack args (o a msg). Calls 0x00196DB0 with EAX=kind ECX=o. */
int r4c_FxPopMsg(R4cNode *o, R4cActor *a, R4cMsg *msg)
{
    R4cFxL *w = (R4cFxL *)a->work;
    switch (msg->id) {
    case 5:
        if (a->state60 == 2)
            return 0;
        if (w->s12 == 0) {
            sub_00189DA0(o, a, 2);
            return 0;
        }
        /* fall through */
    case 1: case 2: case 3: case 6: case 7: case 8: case 9: case 32: case 34: case 35:
        if (w->s0E == 0) {
            sub_00196DB0(w->kind08, o);
            sub_000494D0(0x1BC, o->pos, 1);
            sub_000ED780(o);
        }
        return 0;
    }
    return 0;
}

/* 0x001975D0: move and spin a homing effect; pop it after 300 units or on contact. Stack args (o a). */
void r4c_FxHomeFly(R4cNode *o, R4cActor *a)
{
    R4cFxL *w = (R4cFxL *)a->work;
    r4c_VecAdd(o->pos, o->pos, w->v20);
    w->f14 += r4c_VecLenXZ(w->v20);
    r4c_Spin(o, r4c_spin32C838);
    sub_000C61B0(&g_stats, o);
    if (w->f14 > 300.0f || (o->flags128 & 6)) {
        sub_00196DB0(w->kind08, o);
        sub_000494D0(0x1BC, o->pos, 1);
        sub_000ED780(o);
    }
}

/* 0x00197650: hit test of a pop effect: pop it when it touches anything but the player and not a 5/0x11 object. Stack args (o other). */
void r4c_FxPopHit(R4cNode *o, void *other)
{
    R4cFxL *w = (R4cFxL *)((R4cActor *)sub_0001D960(o, 7))->work;
    if (other != (void *)g_playerObj && !sub_000F5CD0(other, 5, 0x11)) {
        sub_00196DB0(w->kind08, o);
        sub_000494D0(0x1BC, o->pos, 1);
        sub_000ED780(o);
    }
}
