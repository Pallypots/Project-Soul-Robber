/* Area r1h, group 5: graphics memory setup 0x00052360 and the blocking
   wait-for-idle 0x0004E6D0. Names inferred. */
#include "r1h.h"

/* 0x00052360: one-time graphics setup: allocate the command, texture and
   frame buffers, configure the render targets and viewports, allocate the
   two 0x2800-byte work buffers and open the shared resource 0x002CCCC8. */
void r1h_GfxInit(void)
{
    sub_001BBD90();
    sub_00012000();
    r1h_res3E1210 = sub_00053820(8, 0xB020, 0, 0);
    r1h_res3E1214 = sub_00053820(8, 0xFFC, 0, 0);
    r1h_res3E1218 = sub_00053820(8, 0x1FF0, 0, 0);
    sub_001BB2A0(r1h_res3E1214, 0xFFC);
    sub_001BB2E0(0x1800, 0x800, 0);
    sub_001BB2E0(0x1000, 0x800, 0x1B);
    sub_001BB780(r1h_res3E1218, 0x1FF0, 0x2000, 0x2000, 0);
    sub_001BB1D0(0x200, 0xE0, 0);
    sub_001BB1F0(0x200, 0xE0, 0x31);
    sub_001BB210(0x200, 0x1C0, 0);
    sub_001BA650(r1h_res3E1210, 0xB020);
    sub_001B9720();
    sub_001B9730();
    r1h_res3E1204 = sub_00053820(10, 0x2800, 0, 0);
    r1h_res3E1208 = sub_00053820(10, 0x2800, 0, 0);
    r1h_res3E120C = 0;
    r1h_h2DCD48 = sub_00084C00(r1h_name2CCCC8, 0);
}

/* 0x0004E6D0: mark the game busy and block until every pending stage,
   streaming and sound job has finished, servicing the frame (0x001AB850,
   0x000580D0) while waiting; then clear the busy mark. */
void r1h_WaitIdle(void)
{
    r1h_busy3E0540 = 1;
    sub_000325A0(1);
    sub_00038070(r1h_g3E0598);
    sub_00049870();
    if (r1h_g3E05BC == 1 && r1h_g3E00CC == 1) {
        sub_00058540(sub_0004BDA0, 0);
        while (sub_00057E90())
            sub_000580D0();
    }
    sub_000488C0(0x320, 0, 0);
    while (sub_00047A50(0x320, 0, 0)) {
        sub_001AB850();
        sub_000580D0();
    }
    sub_000487F0(r1h_g41316C, r1h_g413170, 0);
    while (sub_00048820(r1h_g41316C, r1h_g413170, 0) != 2) {
        sub_001AB850();
        sub_000580D0();
    }
    sub_00048860(r1h_g41316C, r1h_g413170, 0);
    while (sub_00048890(r1h_g41316C, r1h_g413170, 0)) {
        sub_001AB850();
        sub_000580D0();
    }
    r1h_busy3E0540 = 0;
    sub_000325A0(0);
}
