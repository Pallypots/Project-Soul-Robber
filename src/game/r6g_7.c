/* Area r6g: effect object teardown (r6g_7). Names inferred. */
#include "r6g.h"

/* 0x0007AEE0: destroy an effect object: detach its part, release its list node,
   buffers, textures (unless not owned) and resources, unlink it from its owner
   list and free it. */
void r6g_EffDestroy(R6gEff *e)
{
    int i;
    R6gEffList *l;

    sub_001B2080(e->part20);
    if (e->part20)
        sub_000751C0(e->part20);
    if (e->part20)
        sub_00074F10(e->part20);
    if (e->node0C) {
        sub_0003D8C0(e->node0C);
        sub_00053880(e->node0C);
        e->node0C = 0;
    }
    if (e->buf18) {
        sub_00053880(e->buf18);
        e->buf18 = 0;
    }
    if (e->buf1C) {
        sub_00053880(e->buf1C);
        e->buf1C = 0;
    }
    if (e->part20) {
        sub_00053880(e->part20);
        e->part20 = 0;
    }
    if (e->buf24) {
        sub_00053880(e->buf24);
        e->buf24 = 0;
    }
    if (!(e->flags30 & 1)) {
        for (i = 0; i < e->nTex; i++) {
            if (e->tex[i] > -1)
                sub_001B9FC0(e->tex[i]);
        }
    }
    sub_00053880(e->tex);
    e->tex = 0;
    sub_00082270(e->res10);
    sub_000820C0(e->res10);
    sub_00053880(e->res10);
    e->res10 = 0;
    if (e->res14) {
        sub_00083070(e->res14);
        e->res14 = 0;
    }
    if (e->buf80) {
        sub_00053880(e->buf80);
        e->buf80 = 0;
    }
    l = e->owner;
    if (l) {
        if (e->prev)
            e->prev->next = e->next;
        else
            l->head = e->next;
        if (e->next)
            e->next->prev = e->prev;
        else
            e->owner->tail = e->prev;
        e->owner->count--;
    }
    sub_00053880(e);
}
