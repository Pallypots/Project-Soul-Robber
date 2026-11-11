/* Area r1d, group 17: camera flags and title loops 0x0003AEB0..0x0003CA50. Names inferred. */
#include "r1d.h"

/* 0x0003AEB0: set (on) or clear flag bit 0 of every camera matching key. */
void r1d_CamSetFlag(int key, int on)
{
    R1dCamRef *e = sub_0003DBC0(&r1c_camList3DDC60, sub_0003ABC0, key);
    uint32_t *f = e ? e->flags : 0;
    while (f != 0) {
        if (on)
            *f |= 1;
        else
            *f &= ~1u;
        e = sub_0003DC10((char *)f - 0x10, sub_0003ABC0, key);
        if (e == 0) break;
        f = e->flags;
    }
}

/* 0x0003C3C0: free the title screen's textures and heap and restore the
   video slot. */
void r1d_TitleRelease(void)
{
    int i;
    r1d_g3DDC74 = 0;
    for (i = 0; i < 7; i++) {
        if (r1d_tex3DDC98[i] != -1) {
            sub_001B9FC0(r1d_tex3DDC98[i]);
            r1d_tex3DDC98[i] = -1;
        }
    }
    sub_00053880(r1d_heap3DDC70);
    sub_0004F5D0(a5b_GetVideoMode() + 0xCA);
    sub_001A1B90();
}

/* 0x0003C9D0: run the title loop until its state becomes 0xFFFF, pausing
   input while a movie plays. */
void r1d_TitleLoop(void)
{
    while (r1d_g3DDC80 != 0xFFFF) {
        if (a60_MovieState() == 0) {
            if (a4c_obj428F40[5] & 1) {
                a4c_obj428F40[5] &= ~1;
                sub_0019BEB0(0x8000);
            }
            sub_0003C7E0();
        } else if (!(a4c_obj428F40[5] & 1)) {
            a4c_obj428F40[5] |= 1;
            sub_0019BE90(0x8000);
        }
        sub_000580D0();
    }
    sub_001A0D70();
    r1c_JobFinish();
}

/* 0x0003CA50: endless frame loop drawing the title into the current
   command buffer. */
void r1d_FrameLoop(void)
{
    void *cmd;
    for (;;) {
        cmd = r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd;
        sub_001A5310();
        if (r1d_g3DDC74 == 10000)
            cmd = sub_000727E0(sub_0003C740(cmd), a4c_obj428F40);
        r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd = sub_00079480(cmd);
        sub_000580D0();
    }
}
