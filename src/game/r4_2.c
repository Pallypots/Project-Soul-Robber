/* Area r4: work-slot attach (r4_2), kept apart from its register-argument callees. Names inferred. */
#include "r4.h"

/* 0x00196900: take a free work slot for actor a / controller c and set it up by type.
   Stack args (a c type). Calls 0x00196790 with ESI=slot; 0x001953B0, 0x00196850, 0x001968A0 with EDI=slot. */
int r4_SlotAttach(R4Actor *a, R4Ctl *c, int type)
{
    R4Slot *s;
    int i = 0;
    for (s = a9b_g400E50; s < a9b_g400E50 + 18; s++, i++)
        if (s->actor == 0)
            goto found;
    return 0;
found:
    s = &a9b_g400E50[i];
    if (i >= 18 || type >= 5)
        return 0;
    s->fC = 0.0f;
    s->type = type;
    s->actor = a;
    s->ctl = c;
    c->slot74 = s;
    a->flagsC |= 3;
    c->p84 = r4_g32C7C8;
    c->p88 = r4_g32C800;
    c->fn78 = (void *)r4_SlotRelease;
    c->fn7C = (void *)a9b_WorkTick;
    c->i24 = 2;
    a->f78 = 1.0f;
    a->f74 = 1.0f;
    a->f70 = 1.0f;
    a->iF0 = 2;
    a->iF4 = 2;
    a->i11C = 1;
    a->i120 = 2;
    if (type == 0 || type == 1)
        r4_SlotInitType0(s);
    else if (type == 2)
        r4_SlotInitType2(s);
    else if (type == 3)
        r4_SlotInitType3(s);
    else if (type == 4)
        r4_SlotInitType4(s);
    return 1;
}
