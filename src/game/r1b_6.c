/* Area r1b, group 6: node pool, pool queries, part lists 0x0001B370..0x0001D0F0. Names inferred. */
#include "r1b.h"

/* 0x0001B370: clear the node list head and all 64 pool nodes. */
void r1b_NodesInit(void)
{
    R1bNode *n;
    sub_0003D860(&r1b_list37C468);
    for (n = r1b_nodes37C068; n < &r1b_nodes37C068[64]; n++) sub_0003D860(n);
}

/* 0x0001B3A0: attach an owner to a free pool node and append it to the list
   (hangs if the owner is not ready or the pool is full). */
void r1b_NodeAttach(R1bNodeOwner *o)
{
    int i;
    if (o == 0) return;
    if ((o->flags & 1) == 0) for (;;) ;
    for (i = 0; r1b_nodes37C068[i].owner != 0; ) {
        if (++i >= 64) for (;;) ;
    }
    r1b_nodes37C068[i].data = o;
    sub_0003D880(&r1b_list37C468, &r1b_nodes37C068[i]);
}

/* 0x0001B3F0: find the node for key, unlink it and clear it. */
void r1b_NodeDetach(void *key)
{
    R1bNode *n;
    if (key == 0) return;
    n = sub_0003DBC0(&r1b_list37C468, 0, key);
    if (n == 0) return;
    sub_0003D8C0(n);
    sub_0003D860(n);
}

/* 0x0001B420: forward a query to the context's object at +0x54. */
void r1b_CtxQuery(const float *from, const float *to, void **list)
{
    sub_00082200(r1_ctx42C8E4->obj54, from, to, *list);
}

/* 0x0001B450: fill a pool from a query and finish it with one key. */
void *r1b_PoolFill1(const float *pos, float r, void **list, void *out)
{
    void *p = r1b_Pool80970();
    sub_000822D0(0, p, pos, r, *list, out);
    return sub_00080CF0(p, pos);
}

/* 0x0001B490: fill a pool from a query and finish it with two keys. */
void *r1b_PoolFill2(const float *from, const float *to, void **list, void *out)
{
    void *p = r1b_Pool80970();
    sub_000824F0(0, p, from, to, *list, out);
    return sub_00080CB0(p, from, to);
}

/* 0x0001C840: query a pool for an object's position and copy the result. */
int r1b_PoolLocate(R1bLocObj *o, const float *from, const float *to, void **list)
{
    uint8_t *r;
    void *p = r1b_Pool80970();
    sub_000824F0(0, p, from, to, *list, o->f11C);
    r = sub_00080CB0(p, from, to);
    if (r == 0) return 0;
    r6_Mat1ADB40(o->f60, r + 0x40);
    return 1;
}

/* 0x0001CFF0: append a node (with its value) at the end of a list. */
void r1b_ListAppend(R1bList *l, R1bLNode *n, int value)
{
    R1bLNode *p;
    if (l == 0) return;
    p = l->head;
    if (p == 0) {
        n->value = value;
        l->head = n;
        return;
    }
    while (p->next) p = p->next;
    n->value = value;
    p->next = n;
}

/* 0x0001D030: unlink a node from a list. */
void r1b_ListRemove(R1bList *l, R1bLNode *n)
{
    R1bLNode *p, *prev;
    if (l == 0) return;
    prev = 0;
    for (p = l->head; p; p = p->next) {
        if (p == n) {
            if (prev) prev->next = n->next;
            else l->head = n->next;
            n->next = 0;
            return;
        }
        prev = p;
    }
}

/* 0x0001D080: find the last active record matching (a, b) across a list of
   record tables (hangs on a null list). */
R1bRec *r1b_RecFind(R1bList *l, int a, int b)
{
    R1bLNode *t;
    R1bRec *found = 0;
    int i;
    if (l == 0) for (;;) ;
    for (t = l->head; t; t = t->next) {
        if (t->recs == 0) continue;
        for (i = 0; i < t->count; i++) {
            if ((t->recs[i].flags & 3) && t->recs[i].a == a && t->recs[i].b == b) {
                found = &t->recs[i];
                break;
            }
        }
    }
    return found;
}

/* 0x0001D0F0: return item idx of an object's part (hangs on a bad index). */
void *r1b_PartItemChecked(R1bPartOwner *o, int idx)
{
    R1bPart *p;
    if (o == 0) return 0;
    p = o->part;
    if (p == 0) return 0;
    switch (p->kind) {
    case 1:
        if (p->items == 0) for (;;) ;
        if (p->count <= idx) for (;;) ;
        return p->items + idx * 0x108;
    case 9:
        if (p->items == 0) for (;;) ;
        if (p->count <= idx) for (;;) ;
        return p->items + idx * 0x180;
    }
    return 0;
}
