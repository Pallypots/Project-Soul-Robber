/* Area r1f, group 12: menu worker jobs 0x00046E90..0x00046FA0. Names inferred. */
#include "r1f.h"

/* 0x00046E90: run the handler of the current menu state (0..5). */
void r1f_MenuStep(void)
{
    switch (r1f_g3DF1E8) {
    case 0:
        sub_00040240();
        break;
    case 1:
        sub_00046CF0();
        break;
    case 2:
        sub_00046D50();
        break;
    case 3:
        if (a4c_mode3DF1EC == 0)
            sub_000403A0();
        sub_0003FCE0(a4c_buf2B4D84 + a4c_g3DFA5C);
        break;
    case 4:
        sub_00043A90();
        break;
    case 5:
        sub_00043C20();
        break;
    }
}

/* 0x00046F00: menu job: until the menu reaches state 6, poll the movie
   state and the pads each frame; then finish the job. */
void r1f_MenuJob(void)
{
    while (r1f_g3DF1E8 != 6) {
        if (rtc_g3DF9B4 == 10000) {
            if (sub_00079460() == 0) {
                if (a60_b428F45 & 1)
                    a60_b428F45 &= ~1;
                sub_00046E90();
                r1f_g3DFA34 = ((sub_0004ED00(0) | sub_0004ECD0(0)) & 0x5000) == 0;
            } else if (!(a60_b428F45 & 1)) {
                a60_b428F45 |= 1;
            }
        }
        sub_00053CA0(1);
        sub_000580D0();
    }
    sub_001A8A70(2);
    sub_001A0D70();
    sub_00058190();
}

/* 0x00046FA0: register the three menu jobs of group g, release slots 0 and
   -1 and clear the menu state. */
void r1f_MenuJobsInit(void *g)
{
    sub_00038960();
    sub_00079340();
    sub_001A1030(g, 0, 1, sub_00045CC0, 4, 0x2000);
    sub_001A1030(g, 1, 1, r1f_MenuJob, 4, 0x2000);
    sub_001A1030(g, -1, 4, sub_00046D90, 4, 0x2000);
    sub_001A1060(g, 0);
    sub_001A1060(g, -1);
    rtc_g3DF9B4 = 0;
    a30_g3DF1D4 = 0;
    r1f_f3DF1DC = 0.0f;
    r1f_g3DFA34 = 0;
}
