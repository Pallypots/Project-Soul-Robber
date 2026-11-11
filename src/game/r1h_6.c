/* Area r1h, group 6: boot sequence 0x0003DF90 and scene release
   0x00057C70. Names inferred. */
#include "r1h.h"

/* 0x0003DF90: boot the game: system and graphics setup, start the first
   stage task, then wait (presenting frames and counting them in the 64-bit
   frame counter) until loading, the title data and the memory-unit check
   are done; finishes with 0x000524A0. The 0x00102FA0 and 0x000AD090 calls
   are debug stubs that return at once. */
void r1h_Boot(void)
{
    sub_00102FA0(0);
    sub_00053A40();
    sub_000AD090(0);
    sub_000AD090(1);
    r1h_Nop102FA0();
    sub_000AD090(0, 0);
    sub_0003DE20(0);
    r1h_Nop102FA0();
    sub_0004EFE0();
    sub_00077190();
    sub_000582C0();
    r1h_GfxInit();
    sub_00058540(sub_0003DD20, 0);
    while (sub_00057E90()) {
        sub_000583C0();
        sub_00052520();
        r1h_frames42C918++;
    }
    sub_00049490(0);
    while (!sub_00047920()) {
        sub_000583C0();
        sub_00052520();
        r1h_frames42C918++;
    }
    sub_000ED290();
    sub_0004F490();
    sub_0004F540(0);
    while (sub_0004F4D0() == 1) {
        sub_0004F4C0();
        sub_00102FA0(0);
        sub_00052520();
        r1h_frames42C918++;
    }
    r1h_Nop102FA0();
    r1h_g42CADC = sub_000AD090(0x7200, 0x7A00, 0x4B, 0x23);
    sub_00102FA0(r1h_g42CADC);
    sub_000524A0();
}

/* 0x00057C70: release the current scene: stop its systems, free the
   world's three optional resource blocks (+0x1EC, +0x1F0, +0x1F4), clear
   the six effect slots, and stop the world's sound (+0x208 = -1). */
void r1h_SceneRelease(void)
{
    int i;
    sub_00047BF0(0);
    sub_0005FE00();
    sub_000A8B80();
    sub_000C85C0();
    sub_000C5380();
    sub_00019000(r1h_list3E1270, sub_00019020(r1h_list3E1270));
    sub_00034BB0();
    sub_00034B70();
    sub_00053350(0, -1);
    if (r1h_world42C8E4->p1EC) {
        sub_00053880(r1h_world42C8E4->p1EC->p10);
        sub_00053880(r1h_world42C8E4->p1EC);
        r1h_world42C8E4->p1EC = 0;
    }
    sub_0005CA80();
    if (r1h_world42C8E4->p1F0) {
        sub_00053880(r1h_world42C8E4->p1F0->p18);
        sub_00053880(r1h_world42C8E4->p1F0);
        r1h_world42C8E4->p1F0 = 0;
    }
    sub_0003AAB0();
    if (r1h_world42C8E4->p1F4) {
        sub_0003ACC0(r1h_world42C8E4->p1F4);
        sub_00053880(r1h_world42C8E4->p1F4);
        r1h_world42C8E4->p1F4 = 0;
    }
    sub_000DFC80();
    sub_000A9D00();
    sub_00087440();
    for (i = 0; i < 6; i++)
        sub_00087560(i);
    sub_001660C0();
    sub_00037BC0();
    sub_0004F5D0(0xE2);
    sub_00018B10(r1h_list3E1270);
    sub_000A56C0();
    sub_00039820(0);
    sub_0007D090(r1h_world42C8E4);
    sub_0004F5D0(r1h_world42C8E4->snd208);
    r1h_world42C8E4->snd208 = -1;
}
