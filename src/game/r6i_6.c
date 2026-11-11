/* Area r6i: results popup step (r6i_6). Names inferred. */
#include "r6i.h"

/* 0x0006AD80: one frame of the results popup shown while 0x00429820 is set
   (state 0x00429814: 1 wait for the first button; 2 fade in over 30 frames;
   3 wait for the first button; 4 fade out, then back to 1 and, on page step
   3, set 0x004297FC). */
void r6i_ResultsPopupStep(void)
{
    uint32_t pressed;

    if (r6i_w429820 == 0)
        return;

    sub_0004ECD0(0);
    pressed = sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    pressed |= sub_0004ED20(0);
    sub_0004ED40(0);

    switch (r6i_g429814) {
    case 1:
        if ((r1e_padMasks2C4AE8[0] & pressed) != 0) {
            r6i_f42981C = 30.0f;
            r6i_b4297ED = 0;
            r6i_g429814++;
        }
        break;
    case 2:
        a60_StepByFrame(&r6i_f42981C, 0);
        r6i_b4297ED = (uint8_t)(int)((30.0f - r6i_f42981C) * (1.0f / 30.0f) * 128.0f);
        if (r6i_f42981C <= 0.0f) {
            r6i_b4297ED = 0x80;
            r6i_g429814++;
        }
        break;
    case 3:
        if ((r1e_padMasks2C4AE8[0] & pressed) != 0) {
            r6i_f42981C = 30.0f;
            r6i_g429814++;
        }
        break;
    case 4:
        a60_StepByFrame(&r6i_f42981C, 0);
        r6i_b4297ED = (uint8_t)(int)(r6i_f42981C * (1.0f / 30.0f) * 128.0f);
        if (r6i_f42981C <= 0.0f) {
            if (r6g_b428F80[2] == 3)
                r6i_g4297FC = 1;
            r6i_b4297ED = 0;
            r6i_g429814 = 1;
        }
        break;
    }
}
