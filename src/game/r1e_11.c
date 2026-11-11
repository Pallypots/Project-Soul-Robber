/* Area r1e, group 11: slot record lookup and scene effect release, cell page setup 0x0005A7E0..0x0005EDE0. Names inferred. */
#include "r1e.h"

/* 0x0005A7E0: record k of the slot table of child n of a host's object:
   0x108-byte records for kind 1, 0x180-byte records for kind 9. */
void *r1e_ChildSlot(R1eHost *h, int n, int k)
{
    R1eKObj *c;
    R1eSlotOwner *s;
    if (h->obj != 0 && (c = r1e_ObjChild(h->obj, n)) != 0 && (s = c->owner) != 0 && c->d24 != 0) {
        switch (s->kind) {
        case 1:
            return s->slots + k * 0x108;
        case 9:
            return s->slots + k * 0x180;
        }
    }
    return 0;
}

/* 0x0005CA00: free the effect of every flagged item of the scene groups. */
void r1e_SceneFxFree(void)
{
    R1eScene *s = r1e_scene42C8E4;
    R1eItemGroup *g;
    int i;
    if (s != 0 && s->groups != 0) {
        for (g = *s->groups; g != 0; g = g->next) {
            if (g->items != 0) {
                for (i = 0; i < g->count; i++) {
                    if ((g->items[i].flags & 1) && g->items[i].fx != 0) {
                        r1c_SndOwnerFree(g->items[i].fx);
                        g->items[i].fx = 0;
                    }
                }
            }
        }
    }
}

/* 0x0005EDE0: (re)create the two cell page tables. */
void r1e_CellPagesInit(void)
{
    r1e_CellPagesFree();
    a5b_cellTables = sub_00053AB0(0x100, 0, 0x75);
#if defined(_M_IX86)
    __stosd((unsigned long *)a5b_cellTables, 0, 0x40);
#else
    memset(a5b_cellTables, 0, 0x100);
#endif
    r1e_cellOwned3E604C = sub_00053AB0(0x100, 0, 0x78);
#if defined(_M_IX86)
    __stosd((unsigned long *)r1e_cellOwned3E604C, 0, 0x40);
#else
    memset(r1e_cellOwned3E604C, 0, 0x100);
#endif
    a5b_ChansReset();
    a5b_g3E608C = 0;
}
