/* Area r1j, group 18: owner effects 0x0005C580.
   Names inferred. */
#include "r1j.h"

/* 0x0005C580: start or stop the effects of owner o tagged key. With on
   set: for every effect entry of o with this key that is not already
   running (no active effect points at its source) take a pool record
   (0x00036AD0), initialise it (link cleared, 0x0005A400, scale 1.0, key
   -1), add it to the active list, bind it to the entry's source
   (0x0005A6D0), enable it and tag it with the key. Otherwise stop and
   free every active effect with this key, and stop every sound channel
   of the 32 that plays for this key. Returns 0. */
int r1j_OwnerFxSet(R1jFxOwner *o, int key, int on)
{
    R1jFxEnt *e;
    R1jFxNode *a, *next;
    R1jFx *fx;
    R1jFxChan *ch;
    void *rec;
    int i;
    if (o == 0)
        return 0;
    if (on) {
        for (e = o->first; e != 0; e = e->next) {
            if (e->key != key)
                continue;
            for (a = r1j_fxActive3E5AAC.first; a != 0; a = a->next)
                if (a->data->src == &e->src)
                    goto nextEnt;
            rec = sub_00036AD0(r1j_fxPool3E4B70, 0x3C);
            if (rec == 0)
                continue;
            fx = (R1jFx *)((char *)rec + 0x10);
            if (fx != 0) {
                sub_0003D860(&fx->link);
                sub_0005A400(fx);
                fx->scale = 1.0f;
                fx->key = -1;
            }
            fx->link.data = fx;
            sub_0003D880(&r1j_fxActive3E5AAC, &fx->link);
            e->src.cur = e->src.buf;
            sub_0005A6D0(fx, &e->src);
            fx->flags |= 1;
            fx->key = e->key;
nextEnt:    ;
        }
        return 0;
    }
    for (a = r1j_fxActive3E5AAC.first; a != 0; a = next) {
        next = a->next;
        if (a->data->key == key) {
            sub_0005BE30(a->data);
            sub_0005BC50(a->data);
        }
    }
    ch = r1j_fxChan3E5AD4;
    for (i = 32; i != 0; i--, ch++) {
        if (ch->handle != -1 && ch->key == key && sub_00199E70(ch->handle) != 0) {
            sub_00048250(ch->handle);
            ch->handle = -1;
            ch->d04 = 0;
        }
    }
    return 0;
}
