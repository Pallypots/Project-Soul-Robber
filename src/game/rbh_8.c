/* Area rbh: game functions in 0x00180000..0x0018FFFF (rbh_8). Names inferred. */
#include "rbh.h"

/* 0x00185680: reaction state for the hit kind of the enemy family at 0x00180000 (states
   0x0A..0x13). Without health left the state is 0x13. With work flag 0x800 (guarding) most
   kinds give 0x0F; otherwise each kind has its own state (0x0D/0x0E chosen by the actor's
   flag bit 0) and flag 0x2000 turns every state but 0x0B into 0x13. Flag 4 (knock-down)
   overrides the result and a repeat of the current state falls back to 0x0B unless flag 0x80
   is set. Hangs on state 0.
   regargs: act=EBX */
int rbh_HitState185680(RbhComp *act)
{
    RbhWorkF *w = (RbhWorkF *)act->work278;
    int st;
    uint32_t f;

    w->flags18 &= 0xFFFDFFFFu;
    if (act->f274 > 0.0f) {
        if (w->flags18 & 0x800) {
            switch (w->hit40) {
            case 14:
            case 16:
            case 40:
                st = 0x10;
                break;
            case 12:
            case 36:
            case 43:
                st = 0xB;
                break;
            case 10:
            case 11:
                w->flags18 |= 0x20000;
                st = 0xF;
                break;
            default:
                st = 0xF;
                break;
            }
            goto done;
        }
        switch (w->hit40) {
        case 1:
        case 2:
        case 5:
        case 6:
        case 7:
        case 9:
        case 30:
        case 31:
        case 32:
        case 33:
        case 36:
            st = 0xC;
            break;
        case 3:
            st = (act->flags20 & 1) ? 0xE : 0xD;
            break;
        case 34:
            w->flags18 |= 0x40;
            st = 0xC;
            break;
        case 35:
            w->flags18 |= 0x40;
            st = (act->flags20 & 1) ? 0xE : 0xD;
            break;
        case 8:
            st = (act->flags20 & 1) ? 0xE : 0xD;
            break;
        case 10:
        case 11:
            w->flags18 |= 0x20000;
            st = 0xC;
            break;
        case 14:
        case 16:
        case 40:
            st = 0x10;
            break;
        case 26:
            st = 0x11;
            break;
        case 42:
            st = 0x12;
            sub_000F5D40(act->v88, w->v60);
            break;
        case 45:
            st = 0xA;
            break;
        case 12:
            w->flags18 |= 0x200;
        default:
            st = 0xB;
            break;
        }
        if (!(w->flags18 & 0x2000) || st == 0xB)
            goto done;
    }
    st = 0x13;
done:
    f = w->flags18;
    if (f & 4)
        st = (f & 0x80) ? 0x13 : 0xB;
    else if (st == act->i50 && !(f & 0x80))
        st = 0xB;
    if (!st)
        for (;;)
            ;
    return st;
}
