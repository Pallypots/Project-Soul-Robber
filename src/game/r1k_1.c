/* Area r1k, group 1: title "press start" step 0x00040240.
   Names inferred. */
#include "r1k.h"

/* 0x00040240: menu state 0 (press start). Step 0 starts the fade-in,
   step 1 waits for it, step 16 counts the idle time and on any of the
   start buttons (or after 600 s) stops the stream and starts the fade
   out, step 17 waits for it and switches the menu to state 4. The pad
   reads whose results are unused are in the original. */
void r1k_PressStartStep(void)
{
    uint32_t pressed;
    sub_0004ECD0(0);
    pressed = sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    pressed |= sub_0004ED20(0);
    sub_0004ED40(0);
    switch (a4c_mode3DF1EC) {
    case 0:
        a60_TimerSetCount(a4c_obj428F40, 0);
        sub_00072EE0(a4c_obj428F40, 1, 8.0f, 2);
        a4c_mode3DF1EC++;
        return;
    case 1:
        if (a60_TimerKind(a4c_obj428F40) == 0)
            a4c_mode3DF1EC = 16;
        return;
    case 16:
        a60_StepByFrame(&r1f_f3DF1DC, 1);
        if ((pressed & 0x8F0) == 0 && !(r1f_f3DF1DC >= 600.0f))
            return;
        sub_00047BF0(500);
        sub_00072F30(a4c_obj428F40, 1, 8.0f, 0, 2);
        a4c_mode3DF1EC++;
        return;
    case 17:
        if (a60_TimerKind(a4c_obj428F40) == 0) {
            r1f_g3DF1E8 = 4;
            a4c_mode3DF1EC = 0;
            r1k_g3DF1F0 = 0;
            r1k_g3DF1F4 = 0;
        }
        return;
    }
}
