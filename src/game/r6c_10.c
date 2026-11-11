/* Area r6c: timers and event tables around 0x00084D60-0x00085D20 (r6c_10). Names inferred. */
#include "r6c.h"

/* 0x00084D60: count down every positive timer (paused kinds 4 and 8 skip while flagged); clamp negatives to 0. */
void r6c_TimersTick(void)
{
    R6cCounted *t = r6c_timedTab;
    R6cTimed *e;
    int i;
    if (!t || !r6c_timed)
        return;
    e = r6c_timed;
    for (i = 0; i < t->count; i++, e++) {
        if (e->time > 0.0f) {
            int k = e->obj->kind;
            if ((k == 8 || k == 4) && (e->obj->flags & 1))
                continue;
            e->time -= a50_frameSeconds;
        } else if (0.0f > e->time) {
            e->time = 0.0f;
        }
    }
}

/* 0x000853B0: first entry of the group whose flag is set: its two bytes to *a and *b; 0, or -1.
   regargs: g=EDI */
int r6c_EvFirstA(R6cEvGroup *g, int *a, int *b)
{
    R6cEvEnt *e;
    r6c_evIdxA = 0;
    if (g->count < 1)
        return -1;
    for (e = g->ents; !sub_000D9A70(e->flag); e++)
        if (++r6c_evIdxA >= g->count)
            return -1;
    r6c_evIdxA++;
    *a = e->a;
    *b = e->b;
    return 0;
}

/* 0x00085430: next entry of the group whose flag is set: its two bytes to *a and *b; 0, or -1.
   regargs: g=EDI */
int r6c_EvNextA(R6cEvGroup *g, int *a, int *b)
{
    R6cEvEnt *e;
    if (r6c_evIdxA >= g->count)
        return -1;
    for (e = &g->ents[r6c_evIdxA]; !sub_000D9A70(e->flag); e++)
        if (++r6c_evIdxA >= g->count)
            return -1;
    r6c_evIdxA++;
    *a = e->a;
    *b = e->b;
    return 0;
}

/* 0x000854B0: first entry of the group whose flag is set, or NULL. regargs: g=EDI */
R6cEvEnt *r6c_EvFirstB(R6cEvGroup *g)
{
    R6cEvEnt *e;
    r6c_evIdxB = 0;
    if (g->count < 1)
        return 0;
    for (e = g->ents; !sub_000D9A70(e->flag); e++)
        if (++r6c_evIdxB >= g->count)
            return 0;
    r6c_evIdxB++;
    return e;
}

/* 0x00085520: next entry of the group whose flag is set, or NULL. regargs: g=EDI */
R6cEvEnt *r6c_EvNextB(R6cEvGroup *g)
{
    R6cEvEnt *e;
    if (r6c_evIdxB >= g->count)
        return 0;
    for (e = &g->ents[r6c_evIdxB]; !sub_000D9A70(e->flag); e++)
        if (++r6c_evIdxB >= g->count)
            return 0;
    r6c_evIdxB++;
    return e;
}

/* 0x00085AC0: start the first group for the current entry that has a set flag; 1 when one starts. */
int r6c_EvStartForEntry(void)
{
    int key = a80_CurEntryId();
    R6cEvSet *s = r6c_evSet;
    R6cEvGroup *g = (R6cEvGroup *)s->first;
    int i, j;
    for (i = 0; i < s->count; i++) {
        if (g->key == key) {
            for (j = 0; j < g->count; j++) {
                if (sub_000D9A70(g->ents[j].flag)) {
                    sub_00087A90(g, 0);
                    return 1;
                }
            }
        }
        g = (R6cEvGroup *)&g->ents[g->count];
    }
    return 0;
}

/* 0x00085B60: start the first global (key 0xFF) group with a set flag; 1 when it is not done yet. */
int r6c_EvStartGlobal(void)
{
    R6cEvSet *s = r6c_evSet;
    R6cEvGroup *g = (R6cEvGroup *)s->first;
    int i, j;
    for (i = 0; i < s->count; i++) {
        if (g->key == 0xFF) {
            for (j = 0; j < g->count; j++) {
                if (sub_000D9A70(g->ents[j].flag)) {
                    sub_00085590(g);
                    sub_00087A90(g, 1);
                    return g->done == 0;
                }
            }
        }
        g = (R6cEvGroup *)&g->ents[g->count];
    }
    return 0;
}

/* 0x00085D20: bind the item set and (re)build its slot array. */
void r6c_ItemSlotsInit(R6cItemSet *s)
{
    R6cSlot16 *p;
    int i;
    r6c_items3ED1D4 = s;
    if (!s)
        return;
    p = r6c_slots3ED1D0;
    if (!p) {
        p = a50_Alloc(3, s->count << 4, 0, 0);
        s = r6c_items3ED1D4;
        r6c_slots3ED1D0 = p;
    }
    for (i = 0; i < s->count; i++, p++) {
        p->item = &s->items[i];
        p->i4 = 0;
        p->i8 = -1;
        p->iC = 0;
    }
}
