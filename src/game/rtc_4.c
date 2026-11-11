/* Area rtc, group 4: stage resource setup and teardown (0x0003FF60,
   0x00048D70), kept apart from their callers so cl does not inline them.
   Names inferred. */
#include "rtc.h"

/* Free a texture handle and mark it unused (-1). */
#define RTC_TEX_RELEASE(h)        \
    do {                          \
        if ((h) != -1) {          \
            r4b_TexFree(h);       \
            (h) = -1;             \
        }                         \
    } while (0)

/* 0x0003FF60: release the stage's textures for x (by stage mode 0/1/2),
   run commands 0xBA and 0xA0 + video mode, then release the stage heap. */
void rtc_StageTexturesRelease(void *x)
{
    int i;
    r1c_ClearWork42CE80();
    rtc_g3DF9B4 = 0;
    sub_001A1130(x);
    if (a30_g3DF9B8 == 0 || a30_g3DF9B8 == 1) {
        RTC_TEX_RELEASE(rtc_tex3DF9C8[a30_g3DF9BC]);
        RTC_TEX_RELEASE(rtc_tex3DF1D0);
    }
    RTC_TEX_RELEASE(rtc_tex3DF9C0);
    RTC_TEX_RELEASE(rtc_tex3DF9C4);
    switch (a30_g3DF9B8) {
    case 1:
        for (i = 0; i < 9; i++)
            RTC_TEX_RELEASE(rtc_tex3DFA38[i]);
        break;
    case 2:
        for (i = 0; i < 2; i++)
            RTC_TEX_RELEASE(rtc_tex3DF1E0[i]);
        for (i = 0; i < 24; i++)
            RTC_TEX_RELEASE(rtc_tex3DF9C8[i]);
        break;
    default:
        goto cmds;
    }
    RTC_TEX_RELEASE(rtc_tex3DF9A8);
    RTC_TEX_RELEASE(rtc_tex3DF9AC);
cmds:
    b1b_CmdRun(0xBA);
    b1b_CmdRun(a5b_GetVideoMode() + 0xA0);
    a5b_HeapOp47640(a4c_g3DFA5C);
}

/* 0x00048D70: reset the sound state (slot pairs and queues to -1, tables
   cleared, volume 0x3FFF, scale 1.0), start cues 0x76, 2 and 4 and wait
   until all three report state 2 (pumping the system when wait is set),
   then start them. */
void rtc_SoundReset(int wait)
{
    int i, ready;
    sub_001AC680();
    r1c_q3DFEC0[0] = -1;
    r1c_q3DFEC0[1] = -1;
    r1c_q3DFEC0[2] = -1;
    r1c_q3DFEC0[3] = -1;
    for (i = 0; i < 8; i++)
        r1e_pairs3DFEA0[i] = -1;
    for (i = 0; i < 0x10E; i++)
        r1c_tbl3DFA68[i] = 0;
    rtc_g3DFED0 = 0;
    r1e_g3DFED4 = 0x80;
    rtc_level3DFED8 = 0;
    rtc_scale3DFEDC = 1.0f;
    for (i = 0; i < 0x3F; i++)
        rtc_blk3DFEE0[i] = 0;
    r1b_PktOp();
    r4e_SoundInit();
    sub_00048620(0x3FFF);
    sub_000486F0(0x3FFF);
    sub_0019B5C0(0x76);
    sub_0019B5C0(2);
    sub_0019B5C0(4);
    do {
        ready = 1;
        if (r4d_CuePoll(0x76) != 2)
            ready = 0;
        if (r4d_CuePoll(2) != 2)
            ready = 0;
        if (r4d_CuePoll(4) != 2)
            ready = 0;
        if (wait) {
            sub_0019AE90();
            r6b_ReturnZero(0, 0);
        }
    } while (!ready);
    r4d_CueStartAll(0x76);
    r4d_CueStartAll(2);
    r4d_CueStartAll(4);
    sub_00199F70(0x76);
    sub_00199F70(2);
    sub_00199F70(4);
    if (wait) {
        sub_0019AE90();
        r6b_ReturnZero(0, 0);
    }
}
