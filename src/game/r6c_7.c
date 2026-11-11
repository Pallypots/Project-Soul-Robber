/* Area r6c: scene tree callers kept apart from their callees (r6c_7). Names inferred. */
#include "r6c.h"

/* 0x0007E8B0: drop one reference from each sibling, releasing nodes that reach zero (children first). */
int r6c_TreeRelease(R6cTNode *n)
{
    while (n) {
        R6cTNode *next = sub_0007F300(n);
        r6c_TreeRelease(sub_0007F320(n));
        if (--n->refs == 0) {
            r6c_NodeRelease(n->parts);
            sub_0007F2B0(n);
            r6c_TreeFreeAll(n);
        }
        n = next;
    }
    return 0;
}

/* 0x0007ED10: add each node's item (walking down b's first children) to the matching part list.
   calls 0x0007EC40 with ESI=list EDX=item */
int r6c_PartsAddItems(R6cTNode *a, R6cTNode *b)
{
    R6cPart *p;
    for (p = a->parts; p; p = p->next) {
        if (!(p->flags & 1) || !b)
            break;
        if (p->list && b->u1C.item) {
            int r = r6c_ListAddUnique(p->list, b->u1C.item);
            if (r)
                return r;
        }
        b = sub_0007F320(b);
    }
    return 0;
}

/* 0x0007ED70: remove each node's item from the matching part list, clearing the current id.
   calls 0x0007EC90 with EDI=list ESI=item */
int r6c_PartsRemoveItems(R6cTNode *a, R6cTNode *b)
{
    R6cPart *p;
    if (!b)
        return 0;
    for (p = a->parts; p; p = p->next) {
        if (!(p->flags & 1) || !b)
            break;
        if (p->list && b->u1C.item) {
            r6c_ListRemove(p->list, b->u1C.item);
            if (p->list->cur == b->u1C.item->id)
                p->list->cur = -1;
        }
        b = sub_0007F320(b);
    }
    return 0;
}

/* 0x0007EE50: allocate a key block for v and fill its +0x1C from the decoded key info of src. */
int r6c_KeyNewFrom(R6cKeyObj **out, int v, const void *src)
{
    R6cKeyInfo info;
    sub_00053710(a6b_GetHeap(6));
    r6c_KeyNew(out, v);
    sub_0007F1E0(&info, 0, sizeof info);
    sub_0001DA90(&info, src);
    (*out)->i1C = info.i10;
    sub_00053740();
    return 0;
}

/* 0x0007F430: append the sibling chain c to parent's children; returns c. */
R6cTNode *r6c_TreeAddChild(R6cTNode *parent, R6cTNode *c)
{
    R6cTNode *n, *last;
    if (!c)
        return 0;
    if (parent) {
        last = 0;
        for (n = parent->child; n; n = n->next)
            last = n;
        if (last) {
            r6c_TreeInsertAfter(last, c);
        } else {
            parent->child = c;
            for (n = c; n; n = n->next)
                n->parent = parent;
        }
    }
    return c;
}

/* 0x0007EAD0: free a whole subtree with its record chains. */
int r6c_TreeFree(R6cTNode *n)
{
    if (n) {
        r6c_TreeFree(sub_0007F300(n));
        r6c_TreeFree(sub_0007F320(n));
        if (n->u1C.rec) {
            a6b_Rec_FreeList(n->u1C.rec->next);
            if (n->u1C.rec->pC)
                n->u1C.rec->pC = 0;
            sub_00053880(n->u1C.rec);
        }
        n->u1C.rec = 0;
        sub_0007F2B0(n);
        r6c_TreeFreeAll(n);
    }
    return 0;
}
