/* Area r1k, group 8: loading screen 0x00059450 (separate file so cl does
   not inline the star field draw). Names inferred. */
#include "r1k.h"

/* 0x00059450: draw the loading screen: the star field, then five rows
   of label sprites at y = 70*i - 140 (x 50 and -90). With language 0 two
   animated sprites use frames i+10/i+15 (i+20/i+25 from page 3 on);
   otherwise one sprite uses frames i and i+5. Returns the advanced
   command pointer. regargs: cmd=EDI (passed on to 0x000592E0) */
void *r1k_LoadingDraw(void *cmd)
{
    int i, f;
    float y;
    cmd = r1k_FieldStarsDraw(cmd);
    for (i = 0; i < 5; i++) {
        if (r1h_lang3E4760 == 0) {
            r1h_anim3E4774[0].x = 50.0f;
            y = (float)i * 70.0f - 140.0f;
            r1h_anim3E4774[0].y = y;
            f = i + 20;
            sub_000150B0(&r1h_anim3E4774[0], r1k_g3E4754 >= 3 ? f : f - 10);
            cmd = sub_00017AE0(cmd, &r1h_anim3E4774[0]);
            r1h_anim3E4774[1].x = -90.0f;
            r1h_anim3E4774[1].y = y;
            sub_000150B0(&r1h_anim3E4774[1], r1k_g3E4754 >= 3 ? f + 5 : f - 5);
            cmd = sub_00017AE0(cmd, &r1h_anim3E4774[1]);
            sub_00014E80(&r1h_anim3E4774[0]);
            sub_00014E80(&r1h_anim3E4774[1]);
        } else {
            r1h_anim3E4774[2].x = 50.0f;
            y = (float)i * 70.0f - 140.0f;
            r1h_anim3E4774[2].y = y;
            sub_000150B0(&r1h_anim3E4774[2], i);
            cmd = sub_00017AE0(cmd, &r1h_anim3E4774[2]);
            r1h_anim3E4774[2].x = -90.0f;
            r1h_anim3E4774[2].y = y;
            sub_000150B0(&r1h_anim3E4774[2], i + 5);
            cmd = sub_00017AE0(cmd, &r1h_anim3E4774[2]);
        }
    }
    return cmd;
}

/* 0x00058D20: step the loading screen sequence (r1k_g3E4754): wait 30,
   start a 4-unit fade in with a 300 minimum, wait for the fade, wait out
   the minimum, fade out, wait, switch the rate mode to 1, wait 30, then
   flag the loading screen finished and reset. The pad reads whose
   results are unused are in the original. */
void r1k_LoadingStep(void)
{
    sub_0004ECD0(0);
    sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    sub_0004ED20(0);
    sub_0004ED40(0);
    switch (r1k_g3E4754) {
    case 0:
        r1k_timer3E4768 = 30.0f;
        r1k_g3E4754 = 1;
        return;
    case 2:
        r1k_timer3E4768 = 300.0f;
        sub_00072EE0(a4c_obj428F40, 0, 4.0f, 0);
        r1k_g3E4754++;
        return;
    case 3:
        if (a60_TimerKind(a4c_obj428F40) == 0)
            r1k_g3E4754++;
        return;
    case 1:
    case 4:
        a60_StepByFrame(&r1k_timer3E4768, 0);
        if (0.0f >= r1k_timer3E4768)
            r1k_g3E4754++;
        return;
    case 5:
        sub_00072F30(a4c_obj428F40, 0, 4.0f, 0, 0);
        r1k_g3E4754++;
        return;
    case 6:
        if (a60_TimerKind(a4c_obj428F40) == 0) {
            rtc_SetRateMode(1);
            r1k_g3E4754++;
        }
        return;
    case 7:
        r1k_timer3E4768 = 30.0f;
        r1k_g3E4754 = 8;
        return;
    case 8:
        a60_StepByFrame(&r1k_timer3E4768, 0);
        if (0.0f >= r1k_timer3E4768) {
            r1k_done3E4750 = 1;
            r1k_g3E4754 = 0;
            r1k_g3E4758 = 0;
            r1k_g3E475C = 0;
        }
        return;
    }
}
