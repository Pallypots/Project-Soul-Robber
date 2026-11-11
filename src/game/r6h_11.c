/* Area r6h: event triggers (r6h_11). Names inferred. */
#include "r6h.h"

/* 0x00094C10: when event object e has a trigger index, set the story flag
   that belongs to it in the current chapter and stage (kinds 0x11 and 0x19
   only), then clear the pending bit of e. */
void r6h_EventTrigger(R6hEvtObj *e)
{
    int r = sub_000A44C0(e);
    if (r == -1)
        return;
    switch (a30_g41316C) {
    case 1:
        switch (a30_g413170) {
        case 0:
        case 1:
            if (e->kind == 0x11 && r == 8)
                sub_000D9AB0(0x2EE);
            break;
        case 2:
        case 3:
            if (e->kind == 0x11 && r == 0xF)
                sub_000D9AB0(0x2D2);
            break;
        case 4:
            if (e->kind == 0x11 && r == 8)
                sub_000D9AB0(0x2EF);
            break;
        }
        break;
    case 2:
        if (a30_g413170 < 0)
            break;
        if (a30_g413170 <= 1) {
            if (e->kind != 0x19)
                break;
            if (r == 1)
                sub_000D9AB0(0x36);
            else if (r == 3)
                sub_000D9AB0(0xC2);
            else if (r == 5)
                sub_000D9AB0(0xC3);
        } else if (a30_g413170 == 6) {
            if (e->kind == 0x19 && r == 2)
                sub_000D9AB0(0xD6);
        }
        break;
    case 4:
        if (a30_g413170 == 0 && e->kind == 0x19) {
            if (r == 0)
                sub_000D9AB0(0xCE);
            else if (r == 2)
                sub_000D9AB0(0xCF);
            else if (r == 4)
                sub_000D9AB0(0xD0);
        }
        break;
    }
    e->flags &= ~0x10000000u;
}
