/* Area r6d: stage link helpers around 0x0008A9C0-0x0008AF51 (r6d_21). Names inferred. */
#include "r6d.h"

/* 0x0008A9C0: detach the link's sound from its target's effect list and clear the link. */
int r6d_LinkDetachSound(R6dLinkObj *o)
{
    R6dLink *l = o->link;
    R6dLinkTarget *t;
    if (l->slot >= 0) {
        t = (R6dLinkTarget *)sub_0008E5E0(a80_CurRefX0C(l->a, l->b, l->c)->id);
        if (t && t->owner && t->owner->chr) {
            if (t->owner->chr->effects)
                sub_00033DA0((uint8_t *)sub_00033DC0(t->owner->chr->effects, l->key) + 0x14, l->slot);
            l->a = -1;
            l->b = -1;
            l->c = -1;
            l->key = -1;
            l->slot = -1;
        }
    }
    return 0;
}

/* 0x0008AAA0: stop the sound playing on the link's target. */
int r6d_LinkStopSound(R6dLinkObj *o)
{
    R6dLink *l = o->link;
    R6dLinkTarget *t = (R6dLinkTarget *)sub_0008E5E0(a80_CurRefX0C(l->a, l->b, l->c)->id);
    void *s;
    if (t) {
        s = sub_0008E1B0(t);
        if (s) {
            sub_00033B30(s);
            t->sound = -1;
        }
    }
    return 0;
}

/* 0x0008ADA0: order two links: by 0x0008B320 first, then by a, then by b. */
int r6d_LinkCompare(R6dLinkObj *x, R6dLinkObj *y)
{
    R6dLink *p = x->link;
    R6dLink *q = y->link;
    int r = sub_0008B320(x, y);
    if (r)
        return r;
    if (p->a > q->a)
        return 1;
    if (p->a < q->a)
        return -1;
    if (p->b > q->b)
        return 1;
    return (p->b >= q->b) - 1;
}

/* 0x0008ADF0: attach a type-7 node for p to the link, creating it when missing;
   returns 0, -2 when no node is free, or the attach error. */
int r6d_LinkAttachA(R6dLinkObj *o, R6dLinkSrc *p)
{
    R6dLink *l = o->link;
    int r = 0;
    R6dLinkNode *tmp = 0;
    R6dLinkNode *n;
    if (p) {
        n = (R6dLinkNode *)sub_0008C3C0(p->id, 7);
        if (!n) {
            tmp = (R6dLinkNode *)sub_0008C6E0(7, 0);
            if (!tmp) {
                r = -2;
                r6b_NodeUnlinkRelease2(tmp);
                return r;
            }
            tmp->flags |= 3;
            r = sub_00089540(p, tmp);
            if (r) {
                r6b_NodeUnlinkRelease2(tmp);
                return r;
            }
            n = tmp;
            tmp = 0;
        }
        sub_0008B3B0(l, n);
        l->head = p->value;
    }
    r6b_NodeUnlinkRelease2(tmp);
    return r;
}

/* 0x0008AED0: attach a type-7 node for p to the link (variant without the shared release). */
int r6d_LinkAttachB(R6dLinkObj *o, R6dLinkSrc *p)
{
    R6dLink *l;
    R6dLinkNode *n;
    int r;
    if (!p)
        return 0;
    l = o->link;
    n = (R6dLinkNode *)sub_0008C3C0(p->id, 7);
    if (!n) {
        n = (R6dLinkNode *)sub_0008C6E0(7, 0);
        if (!n)
            return -2;
        n->flags |= 3;
        r = sub_00089540(p, n);
        if (r) {
            r6b_NodeUnlinkRelease2(n);
            return r;
        }
    }
    sub_0008B3B0(l, n);
    l->head = p->value;
    return 0;
}
