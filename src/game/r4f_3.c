/* Area r4f: screen fade start at 0x0019FEF0 (r4f_3). Names inferred. */
#include "r4f.h"

/* 0x0019FEF0: start a fade of a seconds (in frames at 50 or 60 Hz) unless one is running:
   store the fade parameters, restart the screen shake and reset the sound channels.
   Stack args (a b c d e f) with a a float. */
void r4f_FadeStart(float a, int b, int c, int d, int e, int f)
{
    if (r4e_g404334 > 0)
        return;
    r4e_g404334 = r4f_g404338 = R4F_FTOI((float)(Video_GetRateMode() ? 50 : 60) * a);
    r4f_g40433C = (uint32_t)((int8_t)r4c_opt413148 * b) >> 3;
    r4f_g404348 = e;
    r4f_g404340 = c;
    r4f_g404344 = d;
    r4f_g40434C = f;
    a19_g403974 = 0;
    if (r4c_g404318) {
        sub_0003FC10(r4d_shake4042F8);
        sub_0003FCB0(r4d_shake4042F8, sub_0003FA70(r4c_g404318, 0), 0, 20.0f, -1.0f);
    }
    sub_0005EB50();
    sub_0005E9B0();
}

