/* Area r6k: gimmick actors (r6k_9). Names inferred. */
#include "r6k.h"

/* 0x00092490: update of a two-record gimmick (the actor and the record
   after it). Step 0: turns its model (0x000C56B0), advances the angle +0x84
   by 10 degrees per frame unit and wraps it (0x000A35B0); it is triggered
   by hit bits 0x18 of the model, by bits 6 when +0x128 is 0, or for types
   0x50 / 0xFB in chapter 2 stage 4 with event flag 0xBA when actor 0x1D
   touches it (0x000A2630 with the point (0, 0, 0, 1)); then clears flags
   0x810, zeroes +0x90, copies its position to the second record and to
   that record's model and moves on. Step 1 sets the second record's
   motion 1 and its own motion -1 (0x000A41D0) and 0x000A4740(a, 0). */
void r6k_GimmickSpin(R6kActor *a)
{
    float v[4];
    R6kModel *m;
    int hit;

    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    m = a->model120;
    switch (a->step40) {
    case 0:
        sub_000C56B0(m);
        a->vec80[1] += a50_frameUnits * 0.17453294f;
        sub_000A35B0(&a->vec80[1]);
        hit = 0;
        if (!(m->flags128 & 0x18)) {
            if (m->flags128 & 6) {
                if (a->i128 != 0)
                    return;
            } else {
                if (a->type04 != 0x50 && a->type04 != 0xFB)
                    return;
                if (a30_g41316C != 2 || a30_g413170 != 4)
                    return;
                if (sub_000D9A70(0xBA) == 0)
                    return;
                sub_000A42A0(0x1D);
                if (sub_000A2630(sub_000A4290(0x1D), m, v) != 0)
                    hit = 1;
                if (!hit)
                    return;
            }
        }
        a->flags &= 0xFFFFF7EF;
        a->vec90[0] = 0.0f;
        a->vec90[1] = 0.0f;
        a->vec90[2] = 0.0f;
        a->vec90[3] = 0.0f;
        sub_000F5D40(a[1].pos70, a->pos70);
        sub_000F5D40(a[1].model120->pos60, a->pos70);
        a->step40++;
        break;
    case 1:
        sub_000A41D0(&a[1], 1);
        sub_000A41D0(a, -1);
        sub_000A4740(a, 0);
        break;
    }
}
