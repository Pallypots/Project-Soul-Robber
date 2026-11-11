/* Area r6i: results page step (r6i_5). Names inferred. */
#include "r6i.h"

/* 0x0006A970: one frame of the results page (page bytes at 0x00428F80, step
   in byte 2). Step 0 sets bit 3 on sprites 9 and 10 and starts a 30-frame
   timer (skipping to step 3 when 0x00429820 is set); step 1 reveals one row
   every 15 frames (sound 0x38C) until nine rows or a hidden row; steps 1..3
   close on the second button (or button 0x100 in mode 1): fade out, set the
   phase to 3 and queue page 5 (mode 1) or 0, sound 2. */
void r6i_ResultsPageStep(void)
{
    uint32_t pressed;

    sub_0004ECD0(0);
    pressed = sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    pressed |= sub_0004ED20(0);
    sub_0004ED40(0);

    switch (r6g_b428F80[2]) {
    case 0:
        r6i_spr42983C[9].flags |= 8;
        r6i_spr42983C[10].flags |= 8;
        r6i_f4297E8 = 30.0f;
        r6i_b4297EC = 0;
        if (r6i_w429820 != 0) {
            r6i_b4297ED = 0;
            r6i_g429814 = 2;
            r6i_f42981C = 30.0f;
            r6g_b428F80[2] = 3;
        } else {
            r6i_g4297FC = 1;
            r6g_b428F80[2]++;
        }
        break;
    case 1:
        if (r6i_count3E6600 < 9 && (r6i_spr42983C[r6i_count3E6600].flags & 1) == 0) {
            a60_StepByFrame(&r6i_timer3E6604, 1);
            if (r6i_timer3E6604 > (float)r6i_count3E6600 * 15.0f + 10.0f) {
                r6i_count3E6600++;
                sub_00048AF0(0x38C);
            }
        } else {
            r6g_b428F80[2]++;
        }
        /* fall through */
    case 2:
    case 3:
        if ((r1e_padMasks2C4AE8[1] & pressed) != 0) {
            sub_00072F30(a4c_obj428F40, 1, 8.0f, 0, 3);
            r6g_g428F20 = 3;
            r6g_b428F80[7] = 0;
            r6g_b428F80[6] = 0;
            r6g_b428F80[5] = 0;
            r6g_b428F80[4] = 5;
            if (a60_val3E65FC != 1)
                r6g_b428F80[4] = 0;
            sub_00048AF0(2);
        } else if ((pressed & 0x100) != 0 && a60_val3E65FC == 1) {
            sub_00072F30(a4c_obj428F40, 1, 8.0f, 0, 3);
            r6g_g428F20 = 3;
            r6g_b428F80[4] = 5;
            r6g_b428F80[5] = 0;
            r6g_b428F80[6] = 0;
            r6g_b428F80[7] = 0;
            sub_00048AF0(2);
        }
        break;
    }
}
