/* Area r1i, group 16: letterbox wipe 0x000227B0. Names inferred. */
#include "r1i.h"

/* 0x000227B0: draw the two wipe bars into packet p and move them: while
   opening (state 1) each bar shrinks by the speed, while closing (state 2)
   it grows; the lower bar's top edge moves with it. A bar that passes 0
   (opening) or the limit (closing) is clamped and the wipe is done. */
void r1i_WipeDraw(uint32_t *p)
{
    R1iWipeBar *b;
    int i;
    r1c_ReqPush(0x42, 0x88, 0);
    sub_001A69C0(0x88, 0);
    p = r1_PacketBuild(p);
    for (i = 0; i < 2; i++) {
        b = &r1i_wipe37C4CC[i];
        p = sub_00072180(p, b->x, b->y, b->w, b->h, 0, b->col, b->col, b->col, b->col);
        switch (r1i_wipeState37C4C0) {
        case 1:
            b->h -= r1i_wipeSpeed37C4C8;
            if (i == 1)
                r1i_wipe37C4CC[1].y += r1i_wipeSpeed37C4C8;
            if (0.0f > b->h) {
                b->h = 0.0f;
                r1i_wipeState37C4C0 = 3;
            }
            break;
        case 2:
            b->h += r1i_wipeSpeed37C4C8;
            if (i == 1)
                r1i_wipe37C4CC[1].y -= r1i_wipeSpeed37C4C8;
            if (b->h > (float)r1i_wipeMax37C4C4) {
                b->h = (float)r1i_wipeMax37C4C4;
                r1i_wipeState37C4C0 = 3;
            }
            break;
        }
    }
}
