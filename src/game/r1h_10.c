/* Area r1h, group 10: sound sequencer object handler 0x0005D030
   (seseq.c). Names inferred. */
#include "r1h.h"

/* 0x0005D030: message handler of a sound sequencer object. 0 and 1
   forward to the owner's start/stop, 2 updates the sequence data, 3 binds
   the object to its owner's sequence node (creating the owner's node list
   on first use), 4 takes a free slot and records its position among the
   used slots, 5 releases the slot at the recorded position. Returns 0. */
int r1h_SeqObjProc(int msg, R1hSeqObj *o)
{
    R1hSeqOwner *ow;
    R1hSeqData *d;
    R1hSeqNode *nd;
    int slot, k, n, i;
    if (!o)
        return 0;
    d = (R1hSeqData *)o->data;
    ow = o->owner;
    switch (msg) {
    case 0:
        sub_0005CEB0(ow);
        return 0;
    case 1:
        sub_0005C1E0(ow);
        return 0;
    case 3:
        if (!ow->p138) {
            ow->p138 = sub_00053AB0(0x10, 0, 0x87);
            sub_0003D860(ow->p138);
        }
        if (ow->p13C) {
            o->data = ow->p13C->p04;
            return 0;
        }
        nd = sub_0005CC70(ow->p138, ow->p30->id);
        nd->flags |= 2;
        sub_0005CB90(ow, &nd->flags);
        o->data = &nd->flags;
        return 0;
    case 4:
        slot = sub_0005BE80(d);
        if (slot < 0)
            break;
        sub_0005BEB0(&d->work[slot]);
        sub_0005A700(&d->slot[slot]);
        d->slot[slot].used = 1;
        d->slot[slot].v04 = o->v0C;
        d->slot[slot].work = &d->work[slot];
        d->slot[slot].v0C = 0;
        n = 0;
        for (k = sub_0005A8F0(d); k != slot; k = sub_0005A870(d, k))
            n++;
        o->index = n;
        return 0;
    case 5:
        if (d->count < 0)
            break;
        n = o->index;
        k = sub_0005A8F0(d);
        for (i = 0; k >= 0 && i < n; i++)
            k = sub_0005A870(d, k);
        if (k >= 0)
            d->slot[k].used = 0;
        break;
    case 2:
        sub_0005C0E0(d, ow->v04, ow->v08, ow->p30->id);
        break;
    }
    return 0;
}
