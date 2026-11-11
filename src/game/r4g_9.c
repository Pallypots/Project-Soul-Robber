/* Area r4g: scene play loop at 0x001A0970 (r4g_9). Names inferred. */
#include "r4g.h"

/* 0x001A0970: play scene s until the movie ends: each frame start the
   shocks of a new cue, update the stage and, when skipping is allowed,
   fade out on a fresh press of button 0x800 (0x840 for the scenes listed
   at 0x0027B380 in mode 2; those read all four pads); afterwards release
   the scene, and while scenes are queued restart the stage job. Stack arg
   (s). */
void r4g_ScenePlayLoop(R4gScene *s)
{
    uint32_t held[4] = { 0, 0, 0, 0 };
    uint32_t mask, b;
    int32_t *p;
    int prev, cur, i;

    a19_g403940 = 0;
    a9c_g403968 = 0;
    r4f_g404338 = 0;
    r4e_g404334 = 0;
    cur = -1;
    mask = 0x800;
    if (sub_001A0CE0() == 2) {
        for (p = r4g_skipIds27B380; p != r4g_skipIds27B380 + 4; p++)
            if (*p == r4g_scene403970) {
                mask = 0x840;
                break;
            }
    }
    while (sub_001A7DC0()) {
        prev = cur;
        cur = sub_001A80C0();
        if (r4e_g404334 <= 0) {
            sub_001A01A0(cur);
            sub_001A0020(cur, prev);
        }
        sub_001A0200();
        if (r4g_g403980 == 1) {
            for (p = r4g_skipIds27B380; p != r4g_skipIds27B380 + 4; p++)
                if (*p == r4g_scene403970)
                    goto all_pads;
            if (mask & sub_0004ECE0(0))
                goto skip;
            goto next;
all_pads:
            for (i = 0; i < 4; i++) {
                b = sub_001A9130(i);
                held[i] = (held[i] ^ b) & b;
                if (mask & held[i])
                    goto skip;
            }
            goto next;
skip:
            sub_0019FEF0(1.0f, 0, 0x80, 0x80, 0x80, 0);
            a19_g403940 = 1;
        }
next:
        sub_000580D0();
    }
    sub_001A1090(s, 0x102);
    if (a19_g403974) {
        sub_0019FE60(s);
        a19_g40396C = 1;
        sub_001A1030(s, 0x100, 0, sub_001A0830, 4, 0x2000);
        sub_001A1060(s, 0x100);
        if (a19_g403974 <= 0)
            goto out;
        a19_g403974--;
        sub_00058190();
        return;
    }
    if (s->kind == 6)
        sub_001A0D70();
out:
    sub_00058190();
}
