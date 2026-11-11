/* Area r1d, group 8: effect node create/attach/kill 0x000335F0..0x00033B70 (kept apart from 0x00033560). Names inferred. */
#include "r1d.h"

/* 0x000335F0: create an emitter node for effect `key` of fx: look the
   effect up, set up the emitter and bind each element's texture. */
R1dNode *r1d_NodeCreate(R1dFx *fx, uint32_t key)
{
    R1dNode *n;
    int32_t *def;
    R1dEmitElem *el;
    uint32_t i;
    if (fx == 0) return 0;
    n = sub_00033410(0);
    if (n == 0) return 0;
    n->key = key;
    def = a50_TableFind(fx->index, key & 0xFFFF);
    if (def != 0) {
        sub_001B6C80(&n->blk, *def);
        el = n->blk.e.elems;
        for (i = 0; i < n->blk.e.count; i++, el++)
            r4b_EmitSetSet11C(el, fx->tab[el->id].v20);
        r4_EmitClearFlag1(&n->blk);
        return n;
    }
    r1d_NodeFree(n);
    return 0;
}

/* 0x000339C0: move an idle emitter node onto actor o's effect list and
   the bank's list for its layer (flag bit 1). */
void r1d_NodeAttach(R1dNode *n, R1dActor *o)
{
    void *list;
    if (n == 0 || R1D_ENT(n)->flags == 0 || o == 0) return;
    list = sub_000847F0(o->d44, 3);
    if (n->kind != 0) return;
    r4_NodeDetach(&n->blk);
    r4_NodeDetach(n->list2);
    if (list != 0) {
        sub_001B2020(list, &n->blk);
        sub_001B2020(r1c_bank283698 + 0x5845C + ((n->flags >> 1) & 1) * 0xB0, n->list2);
    }
}

/* 0x00033B70: unless the entry's node is locked (bit 0), free it when any
   node of its chain decodes to want (b of -1 matches anything). Returns 0. */
int r1d_NodeKillMatch(R1dNodeEnt *e, R1dAB *want)
{
    R1dNode *top = &e->node;
    R1dNode *n;
    int a, b;
    if (top != 0 && (top->flags & 1)) return 0;
    for (n = top; n != 0; n = n->child) {
        r1d_KeyDecode(n->key, n->pair, &a, &b);
        if (a == want->a && (b == -1 || want->b == -1 || b == want->b)) {
            r1d_NodeFree(top);
            return 0;
        }
    }
    return 0;
}
