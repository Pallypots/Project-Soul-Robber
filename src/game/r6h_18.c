/* Area r6h: spinning object behaviour (r6h_18). Names inferred. */
#include "r6h.h"

/* 0x000A59D0: step a spinning object o. State 0 sets flag bit 1 and, for a
   flag-27 object, its scale (2.0; kind 0x4E: 1.5 with bit 1 cleared and the
   model coloured 255,255,64,128), then picks state 1 or 2 at random. State 1
   turns the heading forward, state 2 backward, by 0.0314 per frame unit,
   wrapping into -pi..pi. */
void r6h_SpinnerStep(R6hSpinner *o)
{
    float rgba[4];
    float t;

    switch (o->state) {
    case 0:
        o->flags |= 2;
        if (o->flags & 0x8000000) {
            if (o->kind != 0x4E) {
                o->scale = 2.0f;
            } else {
                rgba[0] = 255.0f;
                rgba[1] = 255.0f;
                rgba[2] = 64.0f;
                rgba[3] = 128.0f;
                o->flags &= ~2u;
                o->scale = 1.5f;
                sub_000D04E0(o->model, rgba);
            }
        }
        if (sub_001C7EE1() & 1)
            o->state += 2;
        else
            o->state++;
        break;
    case 1:
        t = a50_frameUnits * 0.031415928f + o->heading;
        o->heading = t;
        if (t > 3.1415927f)
            o->heading = t - 6.2831855f;
        break;
    case 2:
        t = o->heading - a50_frameUnits * 0.031415928f;
        o->heading = t;
        if (-3.1415927f > t)
            o->heading = t + 6.2831855f;
        break;
    }
}
