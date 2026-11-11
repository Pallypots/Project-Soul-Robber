/* Area r1h, group 2: debug node-property menu handler 0x0002F2A0. Names inferred. */
#include "r1h.h"

/* 0x0002F2A0: message handler of the debug menu whose first 12 rows are
   the fixed node rows drawn by 0x0002EF30 and whose further rows are the
   menu's own items. Message 1 lets an item row edit itself; message 2
   draws the visible rows; other messages go to the default handler.
   Calls 0x0002EF30 with ECX=px EAX=py EDX=mode (null pointers for modes
   0 and 1) and 0x0002EBC0 with EBX=&x EDI=&y ESI=hilite ECX=item. */
int r1h_NodeMenuProc(int ctx, R1hMenu *m, int msg)
{
    R1hMenuItem *items = m->items ? m->items->items : 0;
    int x, y, i;
    switch (msg) {
    case 0:
        return sub_0002EF30(ctx, m, 0, 0, 0);
    case 1:
        if (sub_0003ED50(m, 1))
            return ctx;
        if (m->sel >= 12)
            sub_0003EF00(&items[m->sel - 12], m->pad);
        return sub_0002EF30(ctx, m, 0, 0, 1);
    case 2:
        x = m->x;
        y = m->y;
        ctx = sub_0003E460(ctx, x, y, &x, &y, m);
        ctx = sub_0003E550(ctx, x, y, &x, &y, m);
        ctx = sub_0002EF30(ctx, m, &x, &y, 2);
        if (items) {
            for (i = m->first; i < m->count; i++) {
                if (i >= m->first + m->visible)
                    break;
                if (i >= 12)
                    ctx = sub_0002EBC0(ctx, x, y, &x, &y, i == m->sel, &items[i - 12]);
            }
        }
        return sub_0003E5B0(ctx, x, y, &x, &y, m);
    default:
        return sub_0003F780(ctx, m, msg);
    }
}
