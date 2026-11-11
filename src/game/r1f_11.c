/* Area r1f, group 11: GS packet setup 0x0003DD30. Names inferred. */
#include "r1f.h"

/* 0x0003DD30: build the fixed GS register packet at 0x003DE500. */
void r1f_PktInit(void)
{
    sub_000AD090(0);
    sub_000AD090(&r1f_pkt3DE500[0x18], 0, 0x1500, 4, 0, 8, 8, 0, 0, 0, 0, 1);
    sub_000AD090(&r1f_pkt3DE500[8], 0);
    r1f_pkt3DE500[8] = 0x44;
    r1f_pkt3DE500[9] = 0;
    r1f_pkt3DE500[4] = 0x5008D;
    r1f_pkt3DE500[5] = 0;
    r1f_pkt3DE500[0x28] = 0x47;
    r1f_pkt3DE500[0x29] = 0;
    r1f_pkt3DE500[0] = 0x8009;
    r1f_pkt3DE500[1] = 0x10000000;
    r1f_pkt3DE500[2] = 0xE;
    r1f_pkt3DE500[3] = 0;
    sub_00102FA0(0);
    sub_000AD090(r1f_pkt3DE500);
    sub_000AD090(0, 0);
}

/* 0x0003E0F0: game main loop: one-time setup and 30 warm-up frames, then
   run frames forever. */
void r1f_MainLoop(void)
{
    int i;
    sub_0003DF90();
    sub_001A5480();
    sub_001C7ED4(sub_001C80BE(0));
    b3b_mode42CAFC = 9999;
    g_ad0_42CAE0 = -1;
    for (i = 30; i != 0; i--) {
        sub_0004F0B0();
        r1e_g42CAF0 = (sub_000586E0(0) == 0);
    }
    r4e_g42CB00 = 0;
    sub_0019C4B0();
    r1f_g42CAF4 = 0;
    r1f_g42CAF8 = 0;
    r1e_g42CAF0 = (sub_000586E0(0) == 0);
    for (;;) {
        sub_0004F0B0();
        sub_0005E9B0();
        sub_0004F4C0();
        sub_00049470();
        sub_000ED350();
        sub_00102FA0(r1f_g42CADC);
        sub_00102FA0(r1f_g42CADC, 0, 0);
        sub_0019C4D0();
        sub_001C7EE1();
    }
}
