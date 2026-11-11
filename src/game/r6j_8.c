/* Area r6j: lift room script (r6j_8). Names inferred. */
#include "r6j.h"

/* 0x000AEE30: room script for actors 0xF..0x15 run once in mode 2 of
   0x00413170. When event flag 0x2F0 is set actor 0xF's model gets the two
   material values at +0xC4 cleared, the actor is raised by 30 and the
   model placed at its position, and actors 0x10..0x15 are started;
   otherwise actor 0xF gets motion 0x27, actors 0x10..0x14 motion 0x28
   and actor 0x15 is started. Mode 0 resets, mode 1 arms phase 10 with
   count -1, mode 3 forces phase 0x63 which clears the state and
   returns 0. Returns 1. */
int r6j_RoomScriptLift2F0(int mode, R6jStep *st)
{
    R6jModel *m;
    R6jActor *a;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->phase = 10;
        st->count = -1;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x63;
    }
    if (st->phase == 10) {
        if (a30_g413170 == 2) {
            if (sub_000D9A70(0x2F0) != 0) {
                m = sub_000A42A0(0xF);
                m->node30->mat14->fC4 = 0.0f;
                m->part3C->node30->mat14->fC4 = 0.0f;
                a = sub_000A4290(0xF);
                a->pos70[1] += 30.0f;
                sub_000F5D40(m->pos60, a->pos70);
                sub_000A5450(0x10);
                sub_000A5450(0x11);
                sub_000A5450(0x12);
                sub_000A5450(0x13);
                sub_000A5450(0x14);
                sub_000A5450(0x15);
                st->phase++;
                return 1;
            }
            sub_000A43C0(0xF, 0x27);
            sub_000A43C0(0x10, 0x28);
            sub_000A43C0(0x11, 0x28);
            sub_000A43C0(0x12, 0x28);
            sub_000A43C0(0x13, 0x28);
            sub_000A43C0(0x14, 0x28);
            sub_000A5450(0x15);
        }
        st->phase++;
    } else if (st->phase == 0x63) {
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
