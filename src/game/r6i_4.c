/* Area r6i: picture-book page step (r6i_4). Names inferred. */
#include "r6i.h"

/* Queue the page to return to after the book closes (entry 0 or 4). */
#define R6I_QUEUE_RETURN()                    \
    if (r6i_b428FA8 == 0) {                   \
        r6g_b428F80[5] = 0;                   \
        r6g_b428F80[6] = 0;                   \
        r6g_b428F80[7] = 1;                   \
        r6g_b428F80[4] = 0;                   \
    } else if (r6i_b428FA8 == 4) {            \
        r6g_b428F80[5] = r6i_b428FA8;         \
        r6g_b428F80[6] = 1;                   \
        r6g_b428F80[7] = 0;                   \
        r6g_b428F80[4] = 0;                   \
    }

/* 0x00068A60: one frame of the picture-book page (page bytes at 0x00428F80,
   step in byte 2). Steps 0/1 fade in over 30 frames; step 2 turns pages with
   the held directions (0x8000 back, 0x2000 forward, sound 0x384), the first
   button turns forward or closes on the last page (sound 1), the second
   button closes (sound 2); closing queues the return page; steps 3/4 fade out
   over 15 frames, take the queued page bytes and release the four page
   textures at 0x003E6528. */
void r6i_BookPageStep(void)
{
    uint32_t pressed, held;
    int i;

    sub_0004ECD0(0);
    pressed = sub_0004ECE0(0);
    held = sub_0004ECF0(0);
    sub_0004ED00(0);
    pressed |= sub_0004ED20(0);
    held |= sub_0004ED40(0);

    switch (r6g_b428F80[2]) {
    case 0:
        sub_00015070(r6i_obj4292C0);
        r6i_timer428F94 = 30.0f;
        r6i_alpha428F9B = 0;
        r6g_b428F80[2]++;
        sub_00048AF0(0x384);
        /* fall through */
    case 1:
        a60_StepByFrame(&r6i_timer428F94, 0);
        r6i_alpha428F9B = (uint8_t)(int)((30.0f - r6i_timer428F94) * 4.266667f);
        if (r6i_timer428F94 <= 0.0f) {
            r6i_alpha428F9B = 0x80;
            r6g_b428F80[2]++;
        }
        break;
    case 2:
        if ((held & 0x8000) != 0) {
            if (r6i_page429704 == 0)
                break;
            r6i_page429704--;
            goto turned;
        }
        if ((held & 0x2000) != 0) {
            if (r6i_page429704 >= r6d_texSets[r6d_texSet3E6538].pages - 1)
                break;
            goto forward;
        }
        if ((r1e_padMasks2C4AE8[0] & pressed) != 0) {
            if (r6i_page429704 < r6d_texSets[r6d_texSet3E6538].pages - 1) {
            forward:
                r6i_page429704++;
            turned:
                sub_00048AF0(0x384);
                break;
            }
            R6I_QUEUE_RETURN()
            r6g_b428F80[2] = 3;
            sub_00048AF0(1);
        } else if ((r1e_padMasks2C4AE8[1] & pressed) != 0) {
            if (r6i_b428FA8 == 0) {
                r6g_b428F80[5] = 0;
                r6g_b428F80[6] = 0;
                r6g_b428F80[7] = 1;
                r6g_b428F80[4] = 0;
                r6g_b428F80[2] = 3;
                sub_00048AF0(2);
                break;
            }
            if (r6i_b428FA8 == 4) {
                r6g_b428F80[5] = r6i_b428FA8;
                r6g_b428F80[6] = 1;
                r6g_b428F80[7] = 0;
                r6g_b428F80[4] = 0;
            }
            r6g_b428F80[2] = 3;
            sub_00048AF0(2);
        }
        break;
    case 3:
        r6g_b428F80[2]++;
        r6i_timer428F94 = 15.0f;
        /* fall through */
    case 4:
        a60_StepByFrame(&r6i_timer428F94, 0);
        r6i_alpha428F9A = r6i_alpha428F9B = (uint8_t)(int)(r6i_timer428F94 * 8.533334f);
        if (r6i_timer428F94 <= 0.0f) {
            r6g_b428F80[0] = r6g_b428F80[4];
            r6i_alpha428F9B = 0;
            r6i_alpha428F9A = 0;
            r6g_b428F80[1] = r6g_b428F80[5];
            r6g_b428F80[2] = r6g_b428F80[6];
            r6g_b428F80[3] = r6g_b428F80[7];
            for (i = 0; i < 4; i++) {
                if (r6g_tex3E6528[i] != -1) {
                    sub_001B9FC0(r6g_tex3E6528[i]);
                    r6g_tex3E6528[i] = -1;
                }
            }
        }
        break;
    }
}
