/* Area r6i: notice page step (r6i_9). Names inferred. */
#include "r6i.h"

/* 0x00073FC0: one frame of a notice page (page bytes at 0x00428F80, step in
   byte 2). Step 0 waits for the second button and queues page 3 step 0x60
   (sound 2), going to step 0x30; steps 0x10/0x11 fade in over 30 frames;
   steps 0x30/0x31 fade out and then set the page phase 0x00428F20 to 3. */
void r6i_NoticePageStep(void)
{
    uint32_t pressed;

    sub_0004ECD0(0);
    pressed = sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    pressed |= sub_0004ED20(0);
    sub_0004ED40(0);

    switch (r6g_b428F80[2]) {
    case 0:
        if ((r1e_padMasks2C4AE8[1] & pressed) != 0) {
            r6g_b428F80[4] = 3;
            r6g_b428F80[5] = 0;
            r6g_b428F80[6] = 0x60;
            r6g_b428F80[7] = 0;
            r6g_b428F80[2] = 0x30;
            sub_00048AF0(2);
        }
        break;
    case 0x10:
        r6g_b428F80[2]++;
        r6i_timer42A828 = 30.0f;
        r6i_alpha42A82C = 0;
        /* fall through */
    case 0x11:
        a60_StepByFrame(&r6i_timer42A828, 0);
        r6i_alpha42A82C = (uint8_t)(int)((30.0f - r6i_timer42A828) * 4.266667f);
        if (r6i_timer42A828 <= 0.0f) {
            r6g_b428F80[2] = 0;
            r6i_alpha42A82C = 0x80;
        }
        break;
    case 0x30:
        r6g_b428F80[2]++;
        r6i_timer42A828 = 30.0f;
        r6i_alpha42A82C = 0x80;
        /* fall through */
    case 0x31:
        a60_StepByFrame(&r6i_timer42A828, 0);
        r6i_alpha42A82C = (uint8_t)(int)(r6i_timer42A828 * 4.266667f);
        if (r6i_timer42A828 <= 0.0f)
            r6g_g428F20 = 3;
        break;
    }
}
