/* Area r1d, group 7: effect node free/find 0x00033560..0x000336B0. Names inferred. */
#include "r1d.h"

/* 0x00033560: free a node and its child chain: detach an emitter's lists
   or unlink a linked node, then return the bank entry. */
void r1d_NodeFree(R1dNode *n)
{
    if (n == 0) return;
    if (n->child != 0)
        r1d_NodeFree(n->child);
    switch (n->kind) {
    case 0:
        sub_001B6D70(&n->blk);
        r4_NodeDetach(&n->blk);
        r4_NodeDetach(n->list2);
        break;
    case 1:
        a4c_ListRemove(R1D_ENT(n)->link);
        sub_00036B10(R1D_ENT(n));
        return;
    }
    sub_00036B10(R1D_ENT(n));
}

/* 0x000336B0: next node after `after` (or the first in the bank) whose id
   is `id`; 0 when none. */
R1dNode *r1d_NodeFindId(int id, R1dNode *after)
{
    R1dNodeEnt *e = after ? R1D_ENT(after) : (R1dNodeEnt *)r1c_bank283698;
    for (e = r1c_PoolFind(e, 0xB40, 0, 0); e != 0; e = r1c_PoolFind(e, 0xB40, 0, 0)) {
        if (e->node.id == id)
            return &e->node;
    }
    return 0;
}
