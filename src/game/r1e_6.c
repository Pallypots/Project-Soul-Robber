/* Area r1e, group 6: buffers, frame setup, movie state 0x0004EAE0..0x0004FAE0. Names inferred. */
#include "r1e.h"

/* 0x0004EAE0: allocate the two 64 KB buffers once and set up their queues. */
void r1e_QueuesInit(void)
{
    if (r1e_buf3E05DC == 0 && r1e_buf3E05E0 == 0) {
        r1e_buf3E05DC = sub_001A8630(0x10000);
        r1e_buf3E05E0 = sub_001A8630(0x10000);
    }
    r1e_g42CAC0 = 0;
    sub_001B32E0(r1e_q42CAC4, r1e_buf3E05DC, 0x100000);
    sub_001B32E0(r1e_q42CAD0, r1e_buf3E05E0, 0x100000);
}

/* 0x0004EC60: note whether the frame is ready, then set up the screen of
   the current field parity and send the frame packet. */
void r1e_FrameSetup(void)
{
    r1e_g42CAF0 = sub_000586E0(0) == 0;
    r1b_PktOp((r1e_frame42C918 & 1) ? r1e_scr3DE700 : r1e_scr3DE610, 0x800, 0x800, r1e_g42CAF0);
    sub_000AD090(r1e_pkt3DE5B0, (int)r1e_frame42C918);
}

/* 0x0004F4E0: run the movie state machine until it stops. */
int r1e_MovieRun(void)
{
    while (r1e_mstate3E0DB4 != 0) {
        if (sub_00057EC0() != 0) {
            sub_000AD090(0, 0);
            r1e_g42CAF0 = sub_000586E0(0);
            r1e_mfuncs2C8890[r1e_mstate3E0DB4]();
        } else if (sub_00057EA0() == 0) {
            sub_000580D0();
        }
    }
    r1b_PktOp(0);
    return 0;
}

/* 0x0004FA70: start movie id in mode 2 unless one is running (-1) or the
   movie is marked unplayable. */
int r1e_MovieStartA(int id, int arg)
{
    if (r1e_mstate3E0DB4 != 0)
        return -1;
    if (id < 0 || id >= 0x21E || r1e_movies2C8900[id].d1C != 1) {
        r1e_mId3E0DBC = id;
        r1e_m3E0DC0 = 0;
        r1e_mArg3E0DC4 = arg;
        r1e_m3E0DC8 = 0;
        r1e_m3E0DB8 = 0;
        r1e_m3E0DCC = 0;
        r1e_mb3E0DD0 = 0;
        r1e_mstate3E0DB4 = 2;
    }
    return 0;
}

/* 0x0004FAE0: as 0x0004FA70 in mode 4. */
int r1e_MovieStartB(int id, int arg)
{
    if (r1e_mstate3E0DB4 != 0)
        return -1;
    if (id < 0 || id >= 0x21E || r1e_movies2C8900[id].d1C != 1) {
        r1e_mId3E0DBC = id;
        r1e_m3E0DC0 = 0;
        r1e_mArg3E0DC4 = arg;
        r1e_m3E0DC8 = 0;
        r1e_m3E0DB8 = 0;
        r1e_m3E0DCC = 0;
        r1e_mb3E0DD0 = 0;
        r1e_mstate3E0DB4 = 4;
    }
    return 0;
}
