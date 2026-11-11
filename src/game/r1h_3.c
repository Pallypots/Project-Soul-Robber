/* Area r1h, group 3: fixed rows of the debug node menu 0x0002EF30. Names inferred. */
#include "r1h.h"

/* 0x0002EF30: the 12 fixed rows of the debug node menu (handler
   0x0002F2A0). Mode 0 counts the rows and loads the six flag toggles
   (rows 2..7) from the current node's flags; mode 1 lets the selected row
   edit itself and moves to the next sibling, first child or parent (rows
   9, 10, 11) on button 0x20; mode 2 draws the visible fixed rows; other
   modes go to the default handler. regargs: px=ECX py=EAX mode=EDX. */
void *r1h_NodeRows(void *ctx, R1hMenu *m, int *px, int *py, int mode)
{
    R1hMenuItem *rows = m->items ? r1h_nodeMenuData.items : 0;
    R1hNodeEx *cur = (R1hNodeEx *)m->data->cur;
    const char *name;
    int i, on, hilite;
    switch (mode) {
    case 0:
        m->count = 0;
        m->count += sub_0003E9E0(&r1h_nodeMenuData);
        m->count += sub_0003E9E0(m->items);
        for (i = 0; i < 12; i++, rows++) {
            switch (i) {
            case 2: sub_0003EAF0(rows, cur->flags & 1); break;
            case 3: sub_0003EAF0(rows, cur->flags & 0x10); break;
            case 4: sub_0003EAF0(rows, cur->flags & 0x20); break;
            case 5: sub_0003EAF0(rows, cur->flags & 0x40); break;
            case 6: sub_0003EAF0(rows, cur->flags & 0x80); break;
            case 7: sub_0003EAF0(rows, cur->flags & 0x100); break;
            }
        }
        return ctx;
    case 1:
        if (m->sel < 12)
            sub_0003EF00(&rows[m->sel], m->pad);
        switch (m->sel) {
        case 9:
            if (sub_0004ECE0(m->pad) & 0x20) {
                sub_0002EB80(m, cur->n.next);
                return ctx;
            }
            break;
        case 10:
            if (sub_0004ECE0(m->pad) & 0x20) {
                sub_0002EB80(m, cur->n.child);
                return ctx;
            }
            break;
        case 11:
            if (sub_0004ECE0(m->pad) & 0x20) {
                sub_0002EB80(m, cur->n.parent);
                return ctx;
            }
            break;
        }
        return ctx;
    case 2:
        if (!rows)
            return ctx;
        for (i = m->first; i < 12; i++) {
            if (i >= m->first + m->visible)
                break;
            switch (i) {
            case 0:
                ctx = sub_0003E610(ctx, *px, *py, px, py, m->sel == 0, 0, r1h_fmt260954,
                                   *(const char **)&rows[0], r1h_nodeTypeNames[cur->n.type]);
                break;
            case 9:
                name = *(const char **)&rows[9];
                on = cur->n.next != 0;
                hilite = m->sel == 9;
                goto link_row;
            case 10:
                name = *(const char **)&rows[10];
                on = cur->n.child != 0;
                hilite = m->sel == 10;
                goto link_row;
            case 11:
                name = *(const char **)&rows[11];
                on = cur->n.parent != 0;
                hilite = m->sel == 11;
            link_row:
                ctx = sub_0003E610(ctx, *px, *py, px, py, hilite, on, r1h_fmt26094C, name);
                break;
            default:
                ctx = sub_0002EBC0(ctx, *px, *py, px, py, i == m->sel, &rows[i]);
                break;
            }
        }
        return ctx;
    default:
        return sub_0003F780(ctx, m, mode);
    }
}
