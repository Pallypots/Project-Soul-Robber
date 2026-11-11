/* Area r4h: effect spawner of the 0x00400688 family (r4h_3). Names inferred. */
#include "r4g.h"
#include "r4h.h"

/* 0x00192000: spawn callback of the 0x00400688 effect family: take a free
   record (16 x 0x40 bytes), set up collision, callbacks and scale, snap
   the model to the ground when it has one, then enter state 1 (mode 2) or
   state 2 (modes 0 and 1). Returns 0 for no node or no free record.
   Twin of r4g_FxSpawnB (0x00192180). Stack args (o a mode). */
int r4h_FxSpawnA(R4gNode *o, R4gActor *a, int mode)
{
    R4hRec40 *rec;
    int i = 0;
    if (!o)
        return 0;
    for (rec = r4c_recs400688; (intptr_t)rec < (intptr_t)&r4c_recs400688[16]; rec++, i++)
        if (!rec->obj)
            break;
    if ((intptr_t)rec >= (intptr_t)&r4c_recs400688[16])
        return 0;
    if (i >= 16)
        return 0;
    rec = &r4c_recs400688[i];
    rec->obj = o;
    rec->actor = a;
    rec->mode10 = mode;
    a->work = rec;
    o->flagsC = (o->flagsC & ~0x20u) | 3;
    o->flags10 |= 0x41;
    a->i24 = 0;
    o->i124 = 1;
    sub_000F5D60(o, 1.0f, -5.0f, 3.0f, r4h_v27AE94);
    sub_000F5DD0(o, 1.0f, 3.7f, r4h_v27AEA8);
    o->iF0 = 2;
    o->iF4 = (int32_t)0x80000000u;
    sub_000F5E30(o, 1.0f, r4h_v27AEB8, r4h_v27AEC8);
    o->i11C = 1;
    o->i120 = (int32_t)0x80000000u;
    a->f28 = 2.5f;
    a->p84 = r4h_d32C688;
    a->p88 = r4h_d32C698;
    a->fn78 = (void *)sub_00190900;
    a->fn7C = (void *)sub_001909C0;
    a->fn80 = (void *)sub_00191E20;
    if (o->p28) {
        rec->f08 = 1.5f;
        sub_0001EE80(o, sub_00196B40);
    }
    if (mode == 2) {
        sub_00189DA0(o, a, 1);
        return 1;
    }
    if (mode == 0 || mode == 1)
        sub_00189DA0(o, a, 2);
    return 1;
}
