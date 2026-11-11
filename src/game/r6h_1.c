/* Area r6h: page state machine (r6h_1). Names inferred. */
#include "r6h.h"

/* 0x0006D910: run one frame of the page state machine. Phase 0 enters the
   current page and starts fading in; phase 1 waits for the fade; phase 2 runs
   the current page; phase 3 waits for the fade out and the record count, leaves
   the page, takes the queued page bytes and enters the next page (fading in
   unless the page is 5). Every path ends in 0x0006C3F0. */
void r6h_PageStep(void)
{
    switch (r6g_g428F20) {
    case 0:
        r6h_pageEnter2DF108[r6g_b428F80[0]]();
        r6g_g428F20 = 1;
        /* fall through */
    case 1:
        if (sub_00072FA0(a4c_obj428F40) != 0)
            break;
    run:
        r6g_g428F20 = 2;
        break;
    case 2:
        switch (r6g_b428F80[0]) {
        case 0: sub_0006A2E0(); break;
        case 1: sub_0006BF80(); break;
        case 2: sub_00065310(); break;
        case 3: sub_00074DB0(); break;
        case 4: sub_00071F90(); break;
        case 6: sub_0006D780(); break;
        }
        sub_0003FCE0(a60_work42C5E8 + 0xF91E8);
        break;
    case 3:
        if (sub_00072FA0(a4c_obj428F40) != 0)
            break;
        if (sub_00053C90() != 0)
            break;
        r6h_pageLeave2DF124[r6g_b428F80[0]]();
        r6g_b428F80[2] = r6g_b428F80[6];
        r6g_b428F80[1] = r6g_b428F80[5];
        r6g_b428F80[0] = r6g_b428F80[4];
        r6g_b428F80[3] = r6g_b428F80[7];
        r6h_pageEnter2DF108[r6g_b428F80[0]]();
        if (r6g_b428F80[0] == 5)
            break;
        if (r6g_b428F80[2] == 0) {
            sub_00072EE0(a4c_obj428F40, 0, 8.0f, 0);
            r6g_g428F20 = 1;
            break;
        }
        goto run;
    }
    sub_0006C3F0();
}
