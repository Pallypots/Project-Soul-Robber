/* Area rbg: game functions in 0x00150000..0x0015FFFF (rbg_7). Names inferred. */
#include "rbg.h"

/* 0x0015B6B0: pick the hit reaction of an enemy from the first condition table that holds
   (tables 0..2 give reaction 0x18) and start it.
   calls 0x001558F0 with EAX=table EBX=obj EDI=act; 0x0015A270 with ESI=act */
void rbg_PickReact15B6B0(void *obj, void *act)
{
    if (r3_CheckConds1558F0(0, obj, act) || r3_CheckConds1558F0(1, obj, act) ||
        r3_CheckConds1558F0(2, obj, act))
        sub_0015A270(obj, 0x18, act);
    else if (r3_CheckConds1558F0(0x1D, obj, act))
        sub_0015A270(obj, 0x24, act);
    else if (r3_CheckConds1558F0(6, obj, act))
        sub_0015A270(obj, 0x15, act);
    else if (r3_CheckConds1558F0(0x1C, obj, act))
        sub_0015A270(obj, 0x21, act);
    else if (r3_CheckConds1558F0(0xC, obj, act))
        sub_0015A270(obj, 0xF, act);
    else if (r3_CheckConds1558F0(8, obj, act))
        sub_0015A270(obj, 0x12, act);
    else if (r3_CheckConds1558F0(0x10, obj, act))
        sub_0015A270(obj, 0xC, act);
    else if (r3_CheckConds1558F0(0xE, obj, act))
        sub_0015A270(obj, 0xA, act);
    else if (r3_CheckConds1558F0(0x14, obj, act))
        sub_0015A270(obj, 0x10, act);
    else if (r3_CheckConds1558F0(0x12, obj, act))
        sub_0015A270(obj, 0x14, act);
}


/* 0x001550E0: reaction state for the hit kind of the second enemy family (same scheme as
   0x00146140 with states 0x25..0x3A and the work flags at +0x40). Hangs on state 0.
   regargs: act=EBX */
int rbg_HitState1550E0(RbgComp *act)
{
    RbgWorkB *w = (RbgWorkB *)act->work278;
    int st;

    w->flags40 &= 0xFFF5FFFFu;
    switch (w->hit1B8) {
    case 1:
    case 6:
    case 29:
        st = 0x2C;
        break;
    case 2:
        st = 0x26;
        break;
    case 3:
        st = 0x2B;
        break;
    case 5:
        st = w->i1C0 ? 0x2C : 0x27;
        break;
    case 7:
    case 9:
        st = 0x27;
        break;
    case 34:
        w->flags40 |= 8;
        st = 0x2D;
        break;
    case 35:
        w->flags40 |= 8;
        st = 0x2E;
        break;
    case 10:
        w->flags40 |= 0xA0000;
        st = 0x2C;
        break;
    case 11:
        w->flags40 |= 0xA0000;
        st = 0x2E;
        break;
    case 8:
        st = 0x30;
        break;
    case 14:
        st = 0x32;
        break;
    case 15:
        st = 0x33;
        break;
    case 26:
        st = 0x34;
        break;
    case 17:
        st = 0x36;
        break;
    case 28:
        st = 0x38;
        break;
    case 16:
    case 18:
    case 19:
    case 20:
    case 21:
        st = 0x35;
        break;
    case 42:
        st = 0x39;
        sub_000F5D40(act->v88, w->v1D8);
        break;
    case 13:
        st = 0x37;
        break;
    case 36:
        st = 0x28;
        break;
    case 30:
        st = 0x29;
        break;
    case 31:
        st = 0x2A;
        break;
    case 32:
        st = 0x2F;
        break;
    case 43:
        if ((act->flags20 & 1) || (act->i50 >= 0x25 && act->i50 <= 0x3A))
            st = 0x25;
        else
            st = 0x31;
        w->fD8 = 0.05f;
        break;
    case 12:
        w->flags40 |= 0x10000;
    default:
        st = 0x25;
        break;
    }
    if (w->flags40 & 2)
        st = (w->flags40 & 0x10) ? 0x2C : 0x25;
    else if (w->flags40 & 0x10) {
        if (st == 0x25)
            st = 0x3A;
    } else if (st == act->i50 && st != 0x27)
        st = 0x25;
    if (!st)
        for (;;)
            ;
    return st;
}
