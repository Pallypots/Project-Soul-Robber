/* Area r1h, group 16: debug menu cursor and keys 0x0003ED50. Names inferred. */
#include "r1h.h"

/* 0x0003ED50: common key handling of the debug menus. Down/up move the
   cursor with wrap-around (a page at a time while the page key is held)
   and scroll the visible window; accept opens the selected item's submenu
   unless flags bit 1 is set or the item has none (returns 1); back closes
   the menu unless flags bit 2 is set (returns -1). Otherwise returns 0.
   Note: when the cursor wraps from the last row to row 0 the first
   visible row becomes sel - count (as in the original). */
int r1h_MenuCursor(R1hMenu *m, int flags)
{
    if (sub_0004ECF0(m->pad) & r1h_keyDown2C4B0C) {
        if (sub_0004ECD0(m->pad) & r1h_keyPage2C4B24) {
            if (m->visible >= m->count) {
                m->sel = m->count - 1;
                return 0;
            }
            m->sel += m->visible;
            if (m->sel >= m->count)
                m->sel = m->count - 1;
            m->first += m->visible;
            if (m->first + m->visible < m->count)
                return 0;
            m->first = m->count - m->visible;
            return 0;
        }
        if (++m->sel >= m->count)
            m->sel = 0;
        if (m->sel < m->first) {
            m->first = m->sel - m->count;
            return 0;
        }
        goto bottom;
    }
    if (sub_0004ECF0(m->pad) & r1h_keyUp2C4B10) {
        if (sub_0004ECD0(m->pad) & r1h_keyPage2C4B24) {
            int v = m->visible;
            m->sel -= v;
            if (m->sel < 0)
                m->sel = 0;
            m->first -= v;
            if (m->first < 0)
                m->first = 0;
            return 0;
        }
        if (--m->sel < 0)
            m->sel = m->count - 1;
        if (m->sel < m->first) {
            m->first = m->sel;
            return 0;
        }
        goto bottom;
    }
    if (sub_0004ECE0(m->pad) & r1h_keyOk2C4B1C) {
        if (!(flags & 1) && m->items && m->items->items) {
            R1hMenuItem *it = &m->items->items[m->sel];
            if ((~(it->flags >> 12) & 1) && it->sub) {
                sub_0003F8B0(m->owner, it->sub, 0);
                return 1;
            }
        }
        return 0;
    }
    if (sub_0004ECE0(m->pad) & r1h_keyBack2C4B20) {
        if (!(flags & 2)) {
            sub_0003E410(m, -1);
            return -1;
        }
    }
    return 0;
bottom:
    if (m->sel >= m->first + m->visible)
        m->first = m->sel - m->visible + 1;
    return 0;
}
