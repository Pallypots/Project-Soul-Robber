/* Area r6i: message page step (r6i_2). Names inferred. */
#include "r6i.h"

/* 0x00061290: one frame of a message page. Steps 0..2 fade in (20 frames,
   showing the selected item's text half way); step 0x10 waits for a button
   (first mask: replay the voice while it is in mode 2; second mask or mode 5:
   clear the text, queue page 2 and play sound 0x397); steps 0x20/0x21 fade
   out, release the loaded texture and switch to the queued page through the
   page table at 0x002DDAE0. */
void r6i_MessagePageStep(void)
{
    uint32_t pressed;

    sub_0004ECD0(0);
    pressed = sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    pressed |= sub_0004ED20(0);
    sub_0004ED40(0);

    switch (a60_v3E60D8) {
    case 0:
        r6d_timer3E6100 = 20.0f;
        r6i_alpha3E60FC = 0;
        a60_v3E60D8 = 1;
        break;
    case 1:
        if (r6d_timer3E6100 <= 10.0f) {
            r6d_MenuShowText(r6h_menuItems3E6104[a60_w3E60FA + a60_w3E60F8]);
            a60_v3E60D8++;
        }
        /* fall through */
    case 2:
        a60_StepByFrame(&r6d_timer3E6100, 0);
        r6i_alpha3E60FC = (uint8_t)(int)((20.0f - r6d_timer3E6100) * 6.4f);
        if (r6d_timer3E6100 <= 0.0f) {
            r6i_alpha3E60FC = 0x80;
            a60_v3E60D8 = 0x10;
        }
        break;
    case 0x10:
        if ((r1e_padMasks2C4AE8[0] & pressed) != 0 && a60_menu3E60CC->mode96C == 2)
            sub_0003FC40(a60_menu3E60CC->snd968);
        if ((r1e_padMasks2C4AE8[1] & pressed) != 0 || a60_menu3E60CC->mode96C == 5) {
            a60_TextClear(a60_menu3E60CC->text970);
            r6i_next3E60E4[0] = 2;
            r6i_next3E60E4[1] = 0;
            r6i_next3E60E4[2] = 0;
            r6i_next3E60E4[3] = 0;
            a60_v3E60D8 = 0x20;
            sub_00048AF0(0x397);
        }
        break;
    case 0x20:
        r6d_timer3E6100 = 20.0f;
        r6i_alpha3E60FC = 0x80;
        a60_v3E60D8 = 0x21;
        break;
    case 0x21:
        a60_StepByFrame(&r6d_timer3E6100, 0);
        r6i_alpha3E60FC = (uint8_t)(int)(r6d_timer3E6100 * 6.4f);
        if (r6d_timer3E6100 <= 0.0f) {
            r6i_alpha3E60FC = 0;
            if (a60_res3E64BC != -1) {
                sub_001B9FC0(a60_res3E64BC);
                a60_res3E64BC = -1;
            }
            a60_state3E60D4 = r6i_next3E60E4[0];
            a60_v3E60D8 = r6i_next3E60E4[1];
            a60_v3E60DC = r6i_next3E60E4[2];
            a60_v3E60E0 = r6i_next3E60E4[3];
            r6i_pageFns2DDAE0[a60_state3E60D4]();
        }
        break;
    }
}
