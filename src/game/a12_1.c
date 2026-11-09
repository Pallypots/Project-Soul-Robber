/* Area a12, group 1. Names inferred. */
#include "a12.h"

/* 0x0001C4D0: forward actor to handler 0x1C160 if its kind is 9. */
void a12_ForwardKind9A(void *ctx, A12Actor *a) { if (a->kind == 9) sub_0001C160(ctx, a); }
/* 0x0001C520: forward actor to handler 0x1BEE0 if its kind is 9. */
void a12_ForwardKind9B(void *ctx, A12Actor *a) { if (a->kind == 9) sub_0001BEE0(ctx, a); }
/* 0x0001C540: forward actor to handler 0x1BEE0 if its kind is 13. */
void a12_ForwardKind13(void *ctx, A12Actor *a) { if (a->kind == 13) sub_0001BEE0(ctx, a); }
/* 0x0001C560: forward actor to handler 0x1BEE0 if its kind is 14. */
void a12_ForwardKind14(void *ctx, A12Actor *a) { if (a->kind == 14) sub_0001BEE0(ctx, a); }

/* 0x0001D220: entry i of a 0x150-byte table. The original guard is
 * (i < 0 && i >= count), which only rejects nothing useful: kept as is. */
void *a12_Table_Get(A12Table *t, int i)
{
    if (i < 0 && i >= t->count)
        return 0;
    return t->entries + i * 0x150;
}

/* 0x0001D270: length of the linked list hanging off +0x3C. */
int a12_List_Count(A12Node *n)
{
    int c = 0;
    for (n = n->next; n; n = n->next) c++;
    return c;
}

/* 0x0001D290: find the list node whose id matches. */
A12Node *a12_List_FindId(A12Node *n, int id)
{
    for (n = n->next; n; n = n->next)
        if (n->id == id) break;
    return n;
}

/* 0x0001D2B0: n-th node of the list (NULL if too short). */
A12Node *a12_List_At(A12Node *n, int idx)
{
    int i = 0;
    for (n = n->next; n; n = n->next) {
        if (i == idx) break;
        i++;
    }
    return n;
}
