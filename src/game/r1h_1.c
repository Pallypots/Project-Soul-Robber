/* Area r1h, group 1: debug instance-tree menu handler 0x0002ECB0. Names inferred. */
#include "r1h.h"

/* 0x0002ECB0: message handler of the debug menu that lists the siblings of
   the current instance-tree node. Message 0 counts the siblings and puts
   the cursor on the current node; message 1 moves the cursor, button 0x20
   acts on the selected node and button 0x10 descends into its children;
   message 2 draws one row per sibling (type name and child count); other
   messages go to the default handler. */
int r1h_TreeMenuProc(int ctx, R1hTreeMenu *m, int msg)
{
    R1hNode *cur, *first, *p;
    int x, y, i, n;
    if (!m)
        return 0;
    cur = m->data->cur;
    if (!cur)
        first = 0;
    else if (cur->parent)
        first = cur->parent->child;
    else
        first = cur;
    switch (msg) {
    case 0:
        n = 0;
        for (p = first; p; p = p->next)
            n++;
        m->count = n;
        m->sel = 0;
        for (p = first; p; p = p->next) {
            if (p == cur)
                return ctx;
            m->sel++;
        }
        m->sel = 0;
        return ctx;
    case 1:
        if (!sub_0003ED50(m, 1)) {
            sub_0003F570(m);
            for (n = m->sel; n > 0; n--)
                first = first->next;
            if (sub_0004ECE0(m->pad) & 0x20)
                sub_0002EAD0(m, first);
            if (sub_0004ECE0(m->pad) & 0x10) {
                sub_0002EB80(m, first->child);
                return ctx;
            }
        }
        return ctx;
    case 2:
        x = m->x;
        y = m->y;
        ctx = sub_0003E460(ctx, x, y, &x, &y, m);
        ctx = sub_0003E550(ctx, x, y, &x, &y, m);
        ctx = sub_0003E610(ctx, x, y, &x, &y, 0, 0, r1h_str2609BC);
        p = first;
        for (i = m->first; i < m->count; i++) {
            if (i >= m->first + m->visible)
                break;
            if (p) {
                R1hNode *c;
                n = 0;
                for (c = p->child; c; c = c->next)
                    n++;
                ctx = sub_0003E610(ctx, x, y, &x, &y, i == m->sel, 1, r1h_fmt2609AC,
                                   i, r1h_nodeTypeNames[p->type], n);
            } else {
                ctx = sub_0003E610(ctx, x, y, &x, &y, i == m->sel, 0, r1h_fmt260990, i);
            }
            p = p->next;
        }
        return sub_0003E5B0(ctx, x, y, &x, &y, m);
    default:
        return sub_0003F780(ctx, m, msg);
    }
}
