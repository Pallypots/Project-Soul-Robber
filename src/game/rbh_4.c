/* Area rbh: game functions in 0x00120000..0x0012FFFF (rbh_4). Names inferred. */
#include "rbh.h"

/* 0x0012D6F0: reaction state for the hit kind of the enemy family at 0x00120000 (states
   0x1A..0x2A; same scheme as 0x001146D0 with every state 7 higher). Work flag 0x20000 forces
   0x24 (hit kind must be 0x23, else hang); with flag 0x10000 (guarding) most kinds give 0x23.
   Kind 32 hands p to 0x00113AA0. Flags 0x40/0x20 (knock-down) override the result and a repeat
   of the current state falls back to 0x1A (except 0x1C). Hangs on state 0.
   regargs: act=EBX p=EDX */
int rbh_HitState12D6F0(void *p, RbhComp *act)
{
    RbhWorkD *w = (RbhWorkD *)act->work278;
    int st;
    uint32_t f;

    w->flags0C &= 0xFFF7FFFFu;
    if (w->flags0C & 0x20000) {
        if (w->hit198 != 0x23)
            for (;;)
                ;
        st = 0x24;
    } else if (w->flags0C & 0x10000) {
        switch (w->hit198) {
        case 5:
        case 35:
            st = 0x24;
            break;
        case 3:
            st = 0x1E;
            break;
        case 10:
        case 11:
            w->flags0C |= 0x80000;
            st = 0x23;
            break;
        case 32:
            st = 0x23;
            goto hand;
        case 14:
        case 16:
        case 40:
            st = 0x26;
            break;
        case 12:
        case 33:
        case 43:
            st = 0x1A;
            break;
        default:
            st = 0x23;
            break;
        }
    } else {
        switch (w->hit198) {
        case 1:
        case 6:
        case 29:
            st = 0x1F;
            break;
        case 5:
        case 7:
        case 9:
            st = 0x1C;
            break;
        case 2:
            st = 0x1B;
            break;
        case 3:
            st = 0x1E;
            break;
        case 34:
            w->flags0C |= 0x10;
            st = 0x20;
            break;
        case 35:
            w->flags0C |= 0x10;
            st = 0x21;
            break;
        case 10:
            w->flags0C |= 0x80000;
            st = 0x1F;
            break;
        case 11:
            w->flags0C |= 0x80000;
            st = 0x21;
            break;
        case 8:
            st = 0x25;
            break;
        case 14:
        case 16:
        case 40:
            st = 0x26;
            break;
        case 26:
            st = 0x27;
            break;
        case 42:
            st = 0x28;
            sub_000F5D40(act->v88, w->v1B8);
            break;
        case 30:
        case 31:
        case 36:
            st = 0x1D;
            break;
        case 32:
            if (!(w->flags0C & 0x20)) {
                st = 0x22;
                break;
            }
            st = 0x1F;
        hand:
            sub_00113AA0(p, act);
            act->flags4C |= 0x200;
            w->flags0C &= ~0x2000u;
            break;
        case 12:
            w->flags0C |= 0x80000;
        case 43:
        default:
            st = 0x1A;
            break;
        }
    }
    f = w->flags0C;
    if (f & 0x40)
        st = (f & 0x20) ? 0x1F : 0x1A;
    else if (f & 0x20)
        st = (st == 0x1A) ? 0x29 : 0x2A;
    else if (st == act->i50 && st != 0x1C)
        st = 0x1A;
    if (!st)
        for (;;)
            ;
    return st;
}
