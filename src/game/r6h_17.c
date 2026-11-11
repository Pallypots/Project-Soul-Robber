/* Area r6h: wandering object behaviour (r6h_17). Names inferred. */
#include "r6h.h"

/* 0x000A6B50: step a wandering object o. State 0 starts a wander: flags
   0x12, timer 0, a random duration value (0.2 + 0..15 * 0.01) and a random
   turn rate (0.0314 + 0..127 * 0.00314, random sign). State 1 runs the timer
   for 120 frame units, then sets flag bit 30 and state -1; it copies the
   duration value to +0x64 every step. Every step the speed is cleared and the
   heading turned by the turn rate, wrapped into -pi..pi. */
void r6h_WanderStep(R6hWander *o)
{
    float t;

    switch (o->state) {
    case 0:
        o->flags |= 0x12;
        o->timer = 0.0f;
        o->dur = (float)(sub_001C7EE1() & 0xF) * 0.01f + 0.2f;
        o->turn = (float)(sub_001C7EE1() & 0x7F) * 0.003141593f + 0.031415928f;
        if (!(sub_001C7EE1() & 1))
            o->turn = o->turn * -1.0f;
        o->state++;
        break;
    case 1:
        t = o->timer + a50_frameUnits;
        o->timer = t;
        if (t >= 120.0f) {
            o->flags |= 0x40000000;
            o->state = -1;
        }
        o->v64 = o->dur;
        break;
    }
    o->speed = 0.0f;
    t = o->turn * a50_frameUnits + o->heading;
    o->heading = t;
    if (t > 3.1415927f)
        o->heading = t - 6.2831855f;
    if (-3.1415927f > o->heading)
        o->heading = o->heading + 6.2831855f;
}
