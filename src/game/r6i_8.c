/* Area r6i: title press-start page step (r6i_8). Names inferred. */
#include "r6i.h"

/* 0x00071230: one frame of the press-start page (page bytes at 0x00428F80,
   step in byte 2). Step 0 waits for either button and queues page 4 step
   0x10 (sound 2) then fades out; steps 0x10/0x11 fade in over 30 frames;
   steps 0x20/0x21 fade out, wait for the record count, release the title
   textures (0x0006E490), take the queued page bytes and tail-call
   0x0006DD40. */
void r6i_PressStartStep(void)
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
        if ((pressed & (r1e_padMasks2C4AE8[1] + r1e_padMasks2C4AE8[0])) != 0) {
            r6g_b428F80[4] = 4;
            r6g_b428F80[5] = 0;
            r6g_b428F80[6] = 0x10;
            r6g_b428F80[7] = 0;
            r6g_b428F80[2] = 0x20;
            sub_00048AF0(2);
        }
        break;
    case 0x10:
        r6g_b428F80[2]++;
        r6i_timer42AC80 = 30.0f;
        r6i_alpha42AC84 = 0;
        /* fall through */
    case 0x11:
        a60_StepByFrame(&r6i_timer42AC80, 0);
        r6i_alpha42AC84 = (uint8_t)(int)((30.0f - r6i_timer42AC80) * 4.266667f);
        if (r6i_timer42AC80 <= 0.0f) {
            r6g_b428F80[2] = 0;
            r6i_alpha42AC85 = 0x80;
        }
        break;
    case 0x20:
        r6g_b428F80[2]++;
        r6i_timer42AC80 = 30.0f;
        r6i_alpha42AC84 = 0x80;
        /* fall through */
    case 0x21:
        a60_StepByFrame(&r6i_timer42AC80, 0);
        r6i_alpha42AC84 = (uint8_t)(int)(r6i_timer42AC80 * 4.266667f);
        if (r6i_timer42AC80 <= 0.0f) {
            r6i_alpha42AC84 = 0;
            if (sub_00053C90() != 0)
                break;
            r6i_TitleReleaseTextures();
            r6g_b428F80[0] = r6g_b428F80[4];
            r6g_b428F80[1] = r6g_b428F80[5];
            r6g_b428F80[2] = r6g_b428F80[6];
            r6g_b428F80[3] = r6g_b428F80[7];
            sub_0006DD40();
        }
        break;
    }
}
