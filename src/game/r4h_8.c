/* Area r4h: thrown effect movement of the 0x00400CA8 family (r4h_8). Names inferred. */
#include "r4h.h"

/* 0x00194410: common movement step of the thrown effect: advance the
   record timer (bit 3 when it passes its end), apply gravity (bit 2),
   end on landing or timeout when held (bit 1), else keep it solid while
   Jack can act, bounce on the floor (state 1, motion 5) and end (state 2)
   when it reaches Jack or hits a wall. Stack args (o a). */
void r4h_FxThrowMove(R4hFxNodeC *o, R4hFxActC *a)
{
    R4hRec1C *w = a->work;
    float pos[4];
    float hit[4];
    float out[4];
    float dir[4];
    float h;

    w->t04 = w->step0C + w->t04;
    if (w->t04 > w->end08)
        w->flags |= 8;
    if (w->flags & 4)
        o->vel80[1] = r4c_frameUnits * 0.02f * r4c_frameUnits + o->vel80[1];
    if (w->flags & 2) {
        sub_000C56B0(o);
        if (!(o->flags128 & 0x1E)) {
            if (!(w->flags & 8))
                return;
            if (a->state60 == 5)
                return;
        }
        goto end;
    }
    if (a->state60 == 0 && sub_000CFFB0() == -1)
        o->flagsC &= ~0x20u;
    else
        o->flagsC |= 0x20;
    if ((o->flags128 & 0x18) && a->state60 != 1) {
        a->work->flags |= 0x40;
        sub_00189DA0(o, a, 1);
        sub_00035DD0(o, o->list130, 5, 1);
    }
    if (a->state60 == 0 && sub_000CFFB0() != -1) {
        sub_000F5D40(pos, o->pos60);
        h = o->scale70[1] * 3.5f;
        pos[1] = pos[1] - h;
        sub_000C4250(&g_stats, dir, out);
        if (out[0] != 0.0f && out[1] != 0.0f && sub_000EE2B0(pos, dir, hit))
            sub_00189DA0(o, a, 2);
    }
    if (!(o->flags128 & 6) || a->state60 == 2)
        return;
end:
    sub_00189DA0(o, a, 2);
}
