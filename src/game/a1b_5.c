/* Area a1b, group 5: actor dispatch and list helpers near 0x0001C260..0x0001EBF0. Names inferred. */
#include "a1b.h"

/* 0x0001C260: forward with the two arguments swapped. */
void a1b_Swap_1C260(void *a, void *b) { sub_0001C160(b, (A12Actor *)a); }
/* 0x0001C3E0: forward unless actor kind is 2. */
void a1b_ForwardNot2(void *ctx, A12Actor *a) { if (a->kind != 2) sub_0001C160(ctx, a); }
/* 0x0001C580: clear the word pointed to by *pp. */
void a1b_ClearPtr(void *u, int32_t **pp) { **pp = 0; }
/* 0x0001C9E0: install a callback (default sub_00102FA0). */
void a1b_SetCallback(A1bCbOwner *o, void *u, void *cb)
{
    if (o) o->callback = cb ? cb : (void *)sub_00102FA0;
}
/* 0x0001CFD0: allocate a 16-byte record and clear its first word. */
int32_t *a1b_Alloc16(void)
{
    int32_t *p = (int32_t *)sub_00053AB0(0x10, 0, 0x14A);
    *p = 0;
    return p;
}
/* 0x0001D8B0: set first word, clear the next three. */
void a1b_Init4(int32_t *p, int32_t v) { p[0] = v; p[1] = 0; p[2] = 0; p[3] = 0; }
/* 0x0001D960: find a link by id. */
A1bLink *a1b_FindLink(A1bLinkOwner *o, int32_t id)
{
    A1bLink *n;
    for (n = o->first; n; n = n->next)
        if (n->id == id) break;
    return n;
}
/* 0x0001DA10: apply sub_0001D980 to every node of a chain. */
void a1b_ForEachNode(A12Node *n) { for (; n; n = n->next) sub_0001D980(n); }
/* 0x0001DAF0: look up entry index in the owner's table. */
void *a1b_TableEntry(A1bTblOwner *o, int index)
{
    if (o->table) return sub_0001DAA0(index, o->table);
    return 0;
}
/* 0x0001EBF0: set field 0x14 of the sub-object if present. */
void a1b_SetSub14(A1bSubOwner *o, int32_t v) { if (o->sub) o->sub->v14 = v; }

