/* Area r6d: 3D sprite object helpers around 0x0007AE30-0x0007D1AD (r6d_12). Names inferred. */
#include "r6d.h"

/* 0x0007AE30: allocate a named node and append it to the owner's list at +0x1F8. */
R6dNamedNode *r6d_NodeAdd(R6dNodeOwner *owner, int a, int b, const char *name)
{
    R6dNamedNode *n = (R6dNamedNode *)sub_00053AB0(0x84, 0, 0x567);
    R6dNodeList *l;
    n->b = b;
    n->name[0] = 0;
    n->next = 0;
    n->prev = 0;
    n->list = 0;
    n->f0C = 0;
    n->a = a;
    n->f30 = 0;
    n->f20 = 0;
    n->f24 = 0;
    n->f18 = 0;
    n->f1C = 0;
    n->f34 = 0;
    n->f38 = 0;
    n->f10 = 0;
    n->f14 = 0;
    strcpy(n->name, name);
    n->f80 = 0;
    l = &owner->nodes;
    n->list = l;
    if (l->head == 0) {
        l->head = n;
        l->tail = n;
        n->prev = 0;
        n->next = 0;
    } else {
        l->tail->next = n;
        n->prev = l->tail;
        n->next = 0;
        l->tail = n;
    }
    l->count++;
    return n;
}

/* Free one resource slot of a scene object. */
static void r6d_ResFree(R6dRes **slot)
{
    if (*slot) {
        r6b_Free81B80((*slot)->data);
        (*slot)->size = 0;
        (*slot)->data = 0;
        sub_00053880(*slot);
        *slot = 0;
    }
}

/* 0x0007D090: free every child of a scene object and its six resource slots. */
void r6d_SceneFree(R6dScene *s)
{
    while (s->child)
        sub_0007AEE0(s->child);
    r6d_ResFree(&s->res[0]);
    r6d_ResFree(&s->res[1]);
    r6d_ResFree(&s->res[2]);
    r6d_ResFree(&s->res[3]);
    r6d_ResFree(&s->res[4]);
    r6d_ResFree(&s->res[5]);
}
