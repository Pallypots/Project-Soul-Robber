/* Area a3b, group 3: pool/list walkers near 0x00034270. Names inferred. */
#include "a3b.h"

/* 0x00034270: iterator callback; process enabled records matching an optional owner. */
int a3b_CbProcess(A3bCbRec *r, int32_t *owner)
{
    int32_t *inner = (int32_t *)((char *)r + 0x10);   /* embedded part; owner is its word 6 */
    if (r->flags & 2) {
        if (!owner || *owner == inner[6]) sub_00033C20(inner);
    }
    return 0;
}

/* 0x00034A90: apply to every item in the list at base+0x58450. */
void a3b_ForEachItem(int a)
{
    A3bNode *n;
    for (n = *(A3bNode **)(a3b_base283698 + 0x58450); n; n = n->next)
        sub_00034500(a, n->item);
}

/* 0x00034AC0: iterator callback; release records whose masked bits match. */
int a3b_CbReleaseMatch(A3bCbRec *r, A3bMatch *m)
{
    if ((r->mask & m->mask) == m->value) {
        sub_00033560((char *)r + 0x10);
        return 1;
    }
    return 0;
}

/* 0x00034B50: process the sub-object at +0x10. */
int a3b_ProcessSub(char *p)
{
    if (p) sub_00033C20(p + 0x10);
    return 0;
}

/* 0x00034D70: apply to every idle node of a pool chain. */
void a3b_PoolApplyA(A3bPNode *n, float a)
{
    for (; n; n = n->next)
        if (n->busy == 0) sub_001B6670(n->sub20, a);
}

/* 0x00034DA0: apply to every idle node of a pool chain. */
void a3b_PoolApplyB(A3bPNode *n, float a)
{
    for (; n; n = n->next)
        if (n->busy == 0) sub_001B67F0(n->sub20, a);
}

/* 0x00034E30: apply to the +0xA5C part of every idle node. */
void a3b_PoolApplyC(A3bPNode *n)
{
    for (; n; n = n->next)
        if (n->busy == 0) sub_001B6A90((char *)n + 0xA5C);
}

/* 0x00034E90: apply to the +0xA5C part of every idle node. */
void a3b_PoolApplyD(A3bPNode *n)
{
    for (; n; n = n->next)
        if (n->busy == 0) sub_001B6B10((char *)n + 0xA5C);
}

/* 0x00034F60: apply to every node of a pool chain. */
void a3b_PoolApplyE(A3bPNode *n, void *a)
{
    for (; n; n = n->next)
        sub_000339C0(n, a);
}
