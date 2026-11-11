/* Area r1g, group 8: debug list menu handler 0x0002E960. Names inferred. */
#include "r1g.h"

/* 0x0002E960: message handler of a debug list menu. Message 1 updates
   the cursor and releases the selected item when button 0x20 is pressed;
   message 2 draws the title, the page arrows, a header and the visible
   item names (the selected one highlighted); other messages go to the
   default handler. */
void *r1g_ListMenuProc(void *ctx, R1gMenu *m, int msg)
{
    R1gMenuItem *items = m->data ? m->data->items : 0;
    int x, y, i;
    switch (msg) {
    case 1:
        if (!a3c_CallED50(m)) {
            a4c_ItemProcessEntry(m);
            if (sub_0004ECE0(m->pad) & 0x20)
                a4c_ItemRelease(m, m->sel);
        }
        return ctx;
    case 2:
        x = m->x;
        y = m->y;
        ctx = sub_0003E4B0(ctx, x, y, &x, &y, r1g_str3816DC);
        ctx = r1d_PageArrowUp(ctx, x, y, &x, &y, m);
        if (items) {
            ctx = sub_0003E610(ctx, x, y, &x, &y, 0, 0, r1g_str38171C);
            for (i = m->first; i < m->count; i++) {
                if (i >= m->first + m->visible)
                    break;
                ctx = sub_0003E610(ctx, x, y, &x, &y, i == m->sel, 1, r1g_fmt26058C, items[i].name);
            }
        }
        return r1d_PageArrowDown(ctx, x, y, &x, &y, m);
    default:
        return r1e_SObjOp(ctx, m, msg);
    }
}
