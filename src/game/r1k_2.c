/* Area r1k, group 2: title logo sprites 0x000400D0.
   Names inferred. */
#include "r1k.h"

/* 0x000400D0: draw the title logo sprite frames (3, 4 only in video mode
   0, 0, 1, 2 only in video mode 0) with a tint chosen by the current
   stage; returns the advanced command pointer. */
void *r1k_LogoDraw(void *cmd)
{
    R1kSprite *s = &r1k_logoSpr3DF214;
    uint32_t col;
    if (a30_g3DF9BC == 3 || a30_g3DF9BC == 4)
        col = 0x806E807F;
    else if (a30_g3DF9BC == 6 || a30_g3DF9BC == 0x10 ||
             a30_g3DF9BC == 0x15 || a30_g3DF9BC == 0x19)
        col = 0x806E7B80;
    else
        col = 0x80808080;
    s->x = 1.0f;
    s->y = -150.0f;
    s->sy = 1.0f;
    s->sx = 1.0f;
    s->color = col;
    sub_000150B0(s, 3);
    cmd = r1d_TrackApplyD(cmd, s);
    if (sub_000529F0() == 0) {
        s->x = 0.0f;
        s->y = 176.0f;
        sub_000150B0(s, 4);
        cmd = r1d_TrackApplyD(cmd, s);
    }
    s->y = -180.0f;
    s->color = 0x8019416E;
    sub_000150B0(s, 0);
    cmd = r1d_TrackApplyD(cmd, s);
    s->y = -134.0f;
    sub_000150B0(s, 1);
    cmd = r1d_TrackApplyD(cmd, s);
    if (sub_000529F0() == 0) {
        s->y = 173.0f;
        sub_000150B0(s, 2);
        return r1d_TrackApplyD(cmd, s);
    }
    return cmd;
}
