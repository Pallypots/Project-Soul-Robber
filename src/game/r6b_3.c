/* Area r6b: thin wrappers over helpers kept in other files (r6b_3). Names inferred. */
#include "r6b.h"

R6bHolderData *r6b_HolderData(R6bHolder *h);
void r6b_IterNext(R6bLink **it);
uint8_t r6b_IterEqual(R6bLink **a, R6bLink **b);
R6bLink **r6b_ListHeadRef(R6bList *l);
void r6b_ListInit(R6bList *l);
void r6b_Free81B80(void *p);

/* 0x00089010: switch to mode `mode` unless its record refuses; returns 1 when refused.
   calls 0x000881B0 with ESI=&a80_modeTable[mode]. */
int r6b_ModeSelect(int mode)
{
    if (sub_000881B0(&a80_modeTable[mode]))
        return 1;
    a80_curMode = mode;
    return 0;
}

/* 0x0008B760: unlink a node, then release it with 0x0008B400. */
void r6b_NodeUnlinkRelease(void *n)
{
    a6b_Node_Unlink(n);
    sub_0008B400(n);
}

/* 0x0008BCC0: forwards to 0x00081B80 (free). */
void r6b_Free8BCC0(void *p)
{
    r6b_Free81B80(p);
}

/* 0x0008C4B0: unlink a node, then release it with 0x0008BF70. */
void r6b_NodeUnlinkRelease2(void *n)
{
    a6b_Node_Unlink(n);
    sub_0008BF70(n);
}

/* 0x0008FA70: forwards to 0x0008FF80 (holder data). */
R6bHolderData *r6b_FwdHolderData(R6bHolder *h)
{
    return r6b_HolderData(h);
}

/* 0x0008FA80: forwards to 0x0008F940 (iterator advance). */
void r6b_FwdIterNext(R6bLink **it)
{
    r6b_IterNext(it);
}

/* 0x0008FA90: forwards to 0x0008F960 (iterator compare). */
uint8_t r6b_FwdIterEqual(R6bLink **a, R6bLink **b)
{
    return r6b_IterEqual(a, b);
}

/* 0x0008FAA0: forwards to 0x000894D0. */
void *r6b_FwdGetX04(void *p)
{
    return a80_GetX04(p);
}

/* 0x0008FAB0: forwards to 0x0008F8F0 (list head reference). */
R6bLink **r6b_FwdListHeadRef(R6bList *l)
{
    return r6b_ListHeadRef(l);
}

/* 0x0008FB60: allocate and initialise an empty list. */
R6bList *r6b_ListNew(void)
{
    R6bList *l = (R6bList *)a5b_AllocCur(8, 0, 0x227);
    r6b_ListInit(l);
    return l;
}
