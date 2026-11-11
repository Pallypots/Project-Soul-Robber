/* Area rbg: game functions in 0x00180000..0x0018FFFF (rbg_8). Names inferred. */
#include "rbg.h"

/* 0x00182E50: four-step group routine for the four partner actors whose component 6 is in
   mode 1: 0 resets them, 1 (after wait 1) starts animation 6/7 and flags them, 2 and 3 (after
   wait 2) play the next animations; step 3 ends by returning the owner to state 0. */
void rbg_GroupSteps182E50(void *obj, void *act)
{
    int i;
    RbgRec150 *o;
    RbgComp *c;

    switch (b7c_count3FE374) {
    case 0:
        for (i = 0; i < 4; i++)
            if (((RbgComp *)sub_0001D960(sub_00181C20(i), 6))->i50 == 1)
                sub_00181CE0(i, 6);
        b7c_count3FE374++;
        break;
    case 1:
        if (!sub_00181D40(1))
            return;
        for (i = 0; i < 4; i++) {
            if (((RbgComp *)sub_0001D960(sub_00181C20(i), 6))->i50 == 1) {
                rtc_PairAnimA(i, (i & 1) ? 6 : 7);
                sub_00181CE0(i, 2);
                o = sub_00181BE0(i);
                o->flags10 |= 0xC;
                c = sub_0001D960(o, 6);
                if (c)
                    c->flags4C &= ~0x01000000u;
            }
        }
        b7c_count3FE374++;
        break;
    case 2:
        if (!sub_00181D40(2))
            return;
        for (i = 0; i < 4; i++)
            if (((RbgComp *)sub_0001D960(sub_00181C20(i), 6))->i50 == 1)
                rtc_PairAnimA(i, 2);
        b7c_count3FE374++;
        break;
    case 3:
        if (!sub_00181D40(2))
            return;
        for (i = 0; i < 4; i++) {
            if (((RbgComp *)sub_0001D960(sub_00181C20(i), 6))->i50 == 1) {
                rtc_PairAnimA(i, 3);
                sub_00181CE0(i, 3);
            }
        }
        sub_00113040(obj, act, 0);
        break;
    }
}
