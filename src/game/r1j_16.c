/* Area r1j, group 16: title menu steps 0x0004E1C0.
   Names inferred. */
#include "r1j.h"

/* 0x0004E1C0: one step of the title menu flow (skipped while a movie
   plays). Reads the pads, then by step: 0 starts stream 0x22; 1 waits for
   the fade; 2 waits for a confirm button; 3 stops the stream and fades out
   over 8 frames; 4 when faded gives the rank reward check (0x0004BE80:
   none goes to mode 5) and starts stream 0x20 before chapter 25;
   0x100 opens the loading screen and releases the menu textures; 0x101
   waits for the load (0x0004BFA0) and switches to mode 4. */
void r1j_TitleMenuStep(void)
{
    uint32_t pad;
    if (sub_00079460() != 0)
        return;
    sub_0004ECD0(0);
    pad = sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    pad |= sub_0004ED20(0);
    sub_0004ED40(0);
    switch ((uint32_t)r1j_menuFlow.step) {
    case 0:
        sub_00048A00(0x22, 1000);
        r1j_menuFlow.step++;
        return;
    case 1:
        if (sub_00072FA0(r1j_fade428F40) != 0)
            return;
        r1j_menuFlow.step++;
        return;
    case 2:
        if ((pad & (r1j_padMasks2C4AE8[0] + r1j_padMasks2C4AE8[1])) == 0)
            return;
        r1j_menuFlow.step = 3;
        return;
    case 3:
        sub_00047BF0(1000);
        sub_00072F30(r1j_fade428F40, 1, 8.0f, 0, 2);
        r1j_menuFlow.step++;
        return;
    case 4:
        if (sub_00072FA0(r1j_fade428F40) != 0)
            return;
        if (sub_0004BE80() != -1) {
            r1j_menuFlow.step = 0x100;
        } else {
            r1j_menuFlow.mode = 5;
            r1j_menuFlow.step = 0;
            r1j_menuFlow.a = 0;
            r1j_menuFlow.b = 0;
        }
        if (r1j_chapter413164 < 25)
            sub_00048A00(0x20, 1000);
        return;
    case 0x100:
        r1j_loading3E0540 = 1;
        sub_000325A0(1);
        r1j_MenuTexRelease();
        r1j_menuKind = 4;
        r1j_menuFlow.step++;
        return;
    case 0x101:
        if (sub_0004BFA0() != 0)
            return;
        r1j_loading3E0540 = 0;
        sub_000325A0(0);
        r1j_menuFlow.mode = 4;
        r1j_menuFlow.step = 0;
        r1j_menuFlow.a = 0;
        r1j_menuFlow.b = 0;
        return;
    }
}
