/* Area r6i: results banner animation (r6i_11). Names inferred. */
#include "r6i.h"

/* 0x0006AB70: animate the results banner while 0x004297FC is set (state
   0x00429800). State 0 marks sprites 9/10 and starts a 30-frame timer at
   scale 2; state 1 fades the banner in during the first 6 frames; states 1/2
   slide it (offsets timer*8.53 and timer*-17.07); when the timer runs out
   the sprites are unmarked, the rows restart (0x003E6600 = 0), page step 3
   goes back to 1 and sound 0x38B plays with a 90-frame timer; state 3
   shrinks the scale from 1 + timer/24 back to 1. The pad is polled but not
   used. */
void r6i_ResultsBannerStep(void)
{
    sub_0004ECD0(0);
    sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    sub_0004ED20(0);
    sub_0004ED40(0);

    if (r6i_g4297FC == 0)
        return;

    switch (r6i_g429800) {
    case 0:
        r6i_spr42983C[9].flags |= 8;
        r6i_spr42983C[10].flags |= 8;
        r6i_f429810 = 2.0f;
        r6i_f429804 = 30.0f;
        r6i_g429800++;
        /* fall through */
    case 1:
        r6i_b4297EC = (uint8_t)(int)((6.0f - (r6i_f429804 - 24.0f)) * 21.333334f);
        if (r6i_f429804 <= 24.0f) {
            r6i_g429800++;
            r6i_b4297EC = 0x80;
        }
        /* fall through */
    case 2:
        r6i_f429808 = r6i_f429804 * 8.533334f;
        r6i_f42980C = r6i_f429804 * -17.066668f;
        a60_StepByFrame(&r6i_f429804, 0);
        if (r6i_f429804 <= 0.0f) {
            if (r6g_b428F80[2] == 3)
                r6g_b428F80[2] = 1;
            r6i_spr42983C[9].flags &= ~8u;
            r6i_spr42983C[10].flags &= ~8u;
            r6i_f429804 = 90.0f;
            r6i_f429808 = 0.0f;
            r6i_f42980C = 0.0f;
            r6i_count3E6600 = 0;
            r6i_g429800++;
            sub_00048AF0(0x38B);
        }
        break;
    case 3:
        r6i_f429810 = r6i_f429804 * (1.0f / 24.0f) + 1.0f;
        a60_StepByFrame(&r6i_f429804, 0);
        if (r6i_f429804 <= 0.0f) {
            r6i_f429810 = 1.0f;
            r6i_g429800++;
        }
        break;
    }
}
