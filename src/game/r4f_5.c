/* Area r4f: idle draw loop at 0x0019D390 (r4f_5). Names inferred. */
#include "r4f.h"

/* 0x0019D390: reset both session slots, then draw frames forever: clear, build the
   frame's command buffer (with the extra pass in mode 10 / substate 0) and flip.
   No inputs; never returns. */
void r4f_IdleDrawLoop(void)
{
    uint32_t *cmd;
    int i;
    for (i = 0; i < 2; i++) {
        g_sessionSlots[i].b[0] = 0;
        g_sessionSlots[i].b[1] = 0;
        g_sessionSlots[i].b[2] = 0;
        g_sessionSlots[i].b[3] = 0;
        g_sessionSlots[i].scale = 1.0f;
    }
    for (;;) {
        sub_001A5310();
        cmd = sub_000325E0(sub_000AA500(sub_0003DCE0(r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd)));
        if (r4e_g41316C == 10 && r4e_g413170 == 0)
            cmd = sub_000324B0(cmd);
        r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd = cmd;
        sub_001A7B90();
        sub_000580D0();
    }
}
