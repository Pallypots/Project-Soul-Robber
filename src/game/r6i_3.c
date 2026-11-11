/* Area r6i: status page step (r6i_3). Names inferred. */
#include "r6i.h"

/* 0x00068740: one frame of the status screen page (page bytes at 0x00428F80,
   step in byte 2). Steps 0/1 fade in over 15 frames and show the entry's
   text; step 2 waits for a button (first mask replays the voice in mode 2;
   second mask or mode 5 closes, queueing page 0 or 4 when no icon was
   picked, or going to step 0x10); steps 3/4 fade out, take the queued page
   bytes and tail-call 0x00065AC0; steps 0x10/0x11 find the picked icon's
   slot, fade out, release the resource and show the icon's screen; step 0x12
   waits for the record count and tail-calls 0x00065AA0. */
void r6i_StatusPageStep(void)
{
    uint32_t pressed;
    int i;

    sub_0004ECD0(0);
    pressed = sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    pressed |= sub_0004ED20(0);
    sub_0004ED40(0);

    switch (r6g_b428F80[2]) {
    case 0:
        r6g_b428F80[2]++;
        r6i_f428FAC = 20.0f;
        r6i_timer428F94 = 15.0f;
        r6i_alpha428F98 = 0;
        /* fall through */
    case 1:
        a60_StepByFrame(&r6i_timer428F94, 0);
        r6i_alpha428F98 = (uint8_t)(int)((15.0f - r6i_timer428F94) * 8.533334f);
        if (r6i_timer428F94 <= 0.0f) {
            r6g_b428F80[2]++;
            r6i_alpha428F98 = 0x80;
            r6d_StatusShowText(1, r6d_StatusIcon(r6i_b428FA8));
        }
        break;
    case 2:
        if (r6g_b428F80[3] != 0)
            break;
        if ((r1e_padMasks2C4AE8[0] & pressed) != 0 && a60_work42C5E8->mode == 2)
            sub_0003FC40(a60_work42C5E8->anim);
        if ((r1e_padMasks2C4AE8[1] & pressed) == 0 && a60_work42C5E8->mode != 5)
            break;
        if (r6i_g428FB0 == 0) {
            if (r6i_b428FA8 == 0) {
                r6g_b428F80[5] = 0;
                r6g_b428F80[7] = 1;
            } else if (r6i_b428FA8 == 4) {
                r6g_b428F80[5] = 4;
                r6g_b428F80[7] = 0;
            } else {
                goto close;
            }
            r6g_b428F80[4] = 0;
            r6g_b428F80[6] = 0;
        close:
            r6g_b428F80[2] = 3;
        } else {
            r6g_b428F80[2] = 0x10;
        }
        r6d_StatusShowText(0, 0);
        sub_00048AF0(2);
        break;
    case 3:
        r6g_b428F80[2]++;
        r6i_timer428F94 = 15.0f;
        /* fall through */
    case 4:
        a60_StepByFrame(&r6i_timer428F94, 0);
        r6i_alpha428F98 = (uint8_t)(int)(r6i_timer428F94 * 8.533334f);
        if (r6i_timer428F94 <= 0.0f) {
            r6g_b428F80[0] = r6g_b428F80[4];
            r6i_alpha428F98 = 0;
            r6g_b428F80[1] = r6g_b428F80[5];
            r6g_b428F80[2] = r6g_b428F80[6];
            r6g_b428F80[3] = r6g_b428F80[7];
            r6b_ReleaseRes3E6540();
        }
        break;
    case 0x10:
        for (i = 0; i < 12; i++) {
            if (r6d_icons42970C[i] == r6i_g428FB0) {
                r6d_g428F8C = i;
                break;
            }
        }
        r6g_b428F80[2]++;
        r6i_timer428F94 = 15.0f;
        /* fall through */
    case 0x11:
        a60_StepByFrame(&r6i_timer428F94, 0);
        r6i_alpha428F98 = (uint8_t)(int)(r6i_timer428F94 * 8.533334f);
        if (r6i_timer428F94 <= 0.0f) {
            r6i_alpha428F98 = 0;
            if (a60_res3E6540 != -1) {
                sub_001B9FC0(a60_res3E6540);
                a60_res3E6540 = -1;
            }
            sub_00065A50(r6i_g428FB0);
            r6i_g428FB0 = 0;
            r6g_b428F80[2]++;
        }
        break;
    case 0x12:
        if (sub_00053C90() != 0)
            break;
        r6g_b428F80[2] = 0;
        a60_InitRes65AA0();
        break;
    }
}
