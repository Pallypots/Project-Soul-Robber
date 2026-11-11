/* Area rbh: game functions in 0x00110000..0x0011FFFF (rbh_3). Names inferred. */
#include "rbh.h"

/* 0x0011AEC0: special move state of an enemy. Sub-state 0 sets emitter 5 to 0.008 and, once
   the animation ends, plays the follow-up animation for the move id (48: 0x1B, 49: 0x1C,
   100..103: 0x68..0x6B; any other id hangs), clears obj flag 4 and moves on; sub-state 1 waits
   for the animation and enters state 0xB (actor flag 0x10000) or 7. */
void rbh_Move11AEC0(RbhEnemy *obj, RbhComp *act)
{
    int anim;

    switch (act->i58) {
    case 0:
        sub_00113400(act, 5)->f10 = 0.008f;
        if (!sub_000833E0(obj->anim30))
            return;
        switch (act->i64) {
        case 48:
            anim = 0x1B;
            break;
        case 49:
            anim = 0x1C;
            break;
        case 100:
            anim = 0x68;
            break;
        case 101:
            anim = 0x69;
            break;
        case 102:
            anim = 0x6A;
            break;
        case 103:
            anim = 0x6B;
            break;
        default:
            for (;;)
                ;
        }
        sub_00113090(obj, act, anim);
        obj->flags10 &= ~4u;
        act->i58++;
        return;
    case 1:
        if (sub_000833E0(obj->anim30))
            sub_00113040(obj, act, (act->bytes20[2] & 1) ? 0xB : 7);
        return;
    }
}

/* 0x001146D0:reaction state for the hit kind of the enemy family at 0x00110000 (states
   0x13..0x22). With work flag 0x4000 set (guarding) most kinds give 0x1C; otherwise each kind
   has its own state and some set work flags. Kind 32 hands p to 0x00113AA0. Flags 0x20/0x10
   (knock-down) override the result and a repeat of the current state falls back to 0x13
   (except 0x16). Hangs on state 0.
   regargs: act=EBX p=EDX */
int rbh_HitState1146D0(void *p, RbhComp *act)
{
    RbhWorkC *w = (RbhWorkC *)act->work278;
    int st;
    uint32_t f;

    w->flags04 &= 0xFFEFFFFFu;
    if (w->flags04 & 0x4000) {
        switch (w->hit5C) {
        case 5:
        case 35:
            st = 0x1A;
            break;
        case 3:
            st = 0x17;
            break;
        case 10:
        case 11:
            w->flags04 |= 0x100000;
            st = 0x1C;
            break;
        case 32:
            st = 0x1C;
            goto hand;
        case 14:
        case 16:
        case 40:
            st = 0x1E;
            break;
        case 12:
        case 33:
        case 43:
            st = 0x13;
            break;
        default:
            st = 0x1C;
            break;
        }
    } else {
        switch (w->hit5C) {
        case 1:
        case 6:
        case 29:
            st = 0x14;
            break;
        case 5:
        case 7:
        case 9:
            st = 0x16;
            break;
        case 2:
            st = 0x15;
            break;
        case 3:
            st = 0x17;
            break;
        case 34:
            w->flags04 |= 8;
            st = 0x19;
            break;
        case 35:
            w->flags04 |= 8;
            st = 0x1A;
            break;
        case 10:
            w->flags04 |= 0x100000;
            st = 0x14;
            break;
        case 11:
            w->flags04 |= 0x100000;
            st = 0x1A;
            break;
        case 8:
            st = 0x1D;
            break;
        case 14:
        case 16:
        case 40:
            st = 0x1E;
            break;
        case 26:
            st = 0x1F;
            break;
        case 42:
            st = 0x20;
            sub_000F5D40(act->v88, w->v7C);
            break;
        case 30:
        case 31:
        case 36:
            st = 0x18;
            break;
        case 32:
            if (!(w->flags04 & 0x10)) {
                st = 0x1B;
                break;
            }
            st = 0x14;
        hand:
            sub_00113AA0(p, act);
            act->flags4C |= 0x200;
            w->flags04 &= ~0x400u;
            break;
        case 12:
            w->flags04 |= 0x8000;
        case 43:
        default:
            st = 0x13;
            break;
        }
    }
    f = w->flags04;
    if (f & 0x20)
        st = (f & 0x10) ? 0x14 : 0x13;
    else if (f & 0x10)
        st = (st == 0x13) ? 0x21 : 0x22;
    else if (st == act->i50 && st != 0x16)
        st = 0x13;
    if (!st)
        for (;;)
            ;
    return st;
}
