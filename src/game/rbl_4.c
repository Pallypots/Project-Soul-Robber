/* Area rbl: enemy state handlers of the 0x00113040 state machine (0x00142xxx family).
   Names inferred. */
#include "rbl.h"

/* 0x00142DA0: recovery state. Runs only while 0x00139FE0 allows it. Step 0 plays sound
   0xCB at the owner and waits 70 frames; step 1 moves to step 2; step 2 marks the enemy
   (+0x4C bits 3 and 4) and picks the next state: a side-0 enemy raises its work value
   +0x14 by 50 (capped at 255) and enters state 9 one time in four, else 8; a side-1 enemy
   enters state 8 one time in four, else waits 60 frames and enters state 5.
   Stack args (o e). */
void rbl_Recover142DA0(RblOwner *o, RblEnemy *e)
{
    if (!sub_00139FE0(o, e))
        return;
    switch (e->i58) {
    case 0:
        sub_000494D0(0xCB, o->model20 + 0x30, 0);
        e->f74 = 70.0f / a50_frameUnits * a50_frameSeconds;
        e->i58++;
        break;
    case 1:
        e->i58 = 2;
        break;
    case 2:
        e->flags4C |= 0x18;
        if (e->u20.b[0] & 1) {
            sub_00113C60(&e->work->f14, 50.0f, 255.0f);
            sub_00113040(o, e, sub_001C7EE1() % 4 < 1 ? 9 : 8);
        } else if (sub_001C7EE1() % 4 < 1) {
            sub_00113040(o, e, 8);
        } else {
            e->f74 = 60.0f / a50_frameUnits * a50_frameSeconds;
            sub_00113040(o, e, 5);
        }
        break;
    }
}

/* 0x00142F10: get-up state. Step 0 waits for the timer, lowers the work value +0x14 (by
   30 when work bit 31 is set, else by 10, floor 0) and sets state 0x32 + side (+2 with
   bit 31); step 1 waits until +0x68 reaches 34 frames and clears the owner's +0x10 bit 2;
   step 2 waits for the animation (0x000833E0) and picks the next state: 4 when work bit 2
   is set on a side-0 enemy, else 8 for a side-1 enemy facing within 60 degrees one time
   in four (setting work bit 1), else 5. Stack args (o e). */
void rbl_Rise142F10(RblOwner *o, RblEnemy *e)
{
    RblEWork *w = e->work;
    int k, st;

    switch (e->i58) {
    case 0:
        if (!(0.0f >= e->f74))
            return;
        k = (e->u20.b[2] & 1) + 0x32;
        if ((int32_t)w->flags04 < 0) {
            k += 2;
            sub_00113CB0(&w->f14, 30.0f, 0.0f);
        } else {
            sub_00113CB0(&w->f14, 10.0f, 0.0f);
        }
        sub_00113090(o, e, k);
        e->i58++;
        break;
    case 1:
        if (e->f68 >= 34.0f / a50_frameUnits * a50_frameSeconds) {
            o->flags10 &= ~4u;
            e->i58++;
        }
        break;
    case 2:
        if (!sub_000833E0(o->anim30))
            return;
        st = 4;
        if (!(e->work->flags04 & 4) || (e->u20.b[0] & 1)) {
            st = 5;
            if ((e->u20.b[2] & 1) && 1.0471976f > e->angFC && sub_001C7EE1() % 4 < 1) {
                w->flags04 |= 2;
                st = 8;
            }
        }
        o->flags10 &= ~4u;
        sub_00113040(o, e, st);
        break;
    }
}

/* 0x001440B0: stagger state. Step 0 waits 14 frames of state time (+0x5C), applies the
   hit (0x00142270) and advances; step 1 waits for the animation and picks the next state:
   after hit kind 4, 8 when the target is nearer than 45; after hit kind 0x15, 3 when
   check 0 of table 0x0031DBBC holds (0x00143740), else 8 one time in four when health is
   at most half and the facing angle is within 40 degrees (setting work bit 1); otherwise 5.
   Clears the owner's +0x10 bits 1-2. Stack args (o e);
   calls 0x00143740 with EAX=0 EDX=e and o on the stack. */
void rbl_Stagger1440B0(RblOwner *o, RblEnemy *e)
{
    int st;

    switch (e->i58) {
    case 0:
        if (e->f5C >= 14.0f / a50_frameUnits * a50_frameSeconds) {
            sub_00142270(o, e);
            e->i58++;
        }
        break;
    case 1:
        if (!sub_000833E0(o->anim30))
            return;
        st = 5;
        if (e->i64 == 4) {
            if (45.0f > e->f100)
                st = 8;
        } else if (e->i64 == 0x15) {
            if (r3b_Dispatch143740(0, e, o)) {
                st = 3;
            } else if (e->maxHp270 * 0.5f >= e->hp274 &&
                       0.6981317f >= sub_001A3F30(e->angFC) && sub_001C7EE1() % 4 < 1) {
                e->work->flags04 |= 2;
                st = 8;
            }
        }
        o->flags10 &= ~6u;
        e->flags4C |= 0x10;
        sub_00113040(o, e, st);
        break;
    }
}

