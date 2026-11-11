/* Area r1i, group 18: HUD set-up 0x00026B50. Names inferred. */
#include "r1i.h"

/* 0x00026B50: show the HUD and read the life, soul and item values from
   Jack's stats (life at least 10). A fresh start (resume 0) slides the
   life gauge in from x 0x130 and shows the soul gauge at full alpha; a
   resume restarts the gauge, soul, item and key animations instead (state
   3, timers 0, -1 marker). regargs: resume=EDI */
void r1i_HudSetup(int resume)
{
    int v;
    r1i_hudOn37C4F8 |= 1;
    r1i_life37C570 = Stats_Get(&g_stats, 0);
    r1i_lifeMax37C574 = Stats_Get(&g_stats, 1);
    if (r1i_life37C570 < 10)
        r1i_life37C570 = 10;
    if (!resume) {
        r1i_lifeX37C56E = 0x130;
    } else {
        r1i_lifeF37C584 = -1.0f;
        r1i_lifeX37C56E = 0;
        r1i_lifeSt37C544 = 3;
        r1i_lifeT37C548 = 0;
        r1i_lifeT37C564 = 0;
    }
    r1i_soulA37D45C = 0x80;
    r1i_soulW37D47C = 50;
    r1i_soulW37D478 = 50;
    r1i_soulV37D47A = (int16_t)Stats_Get(&g_stats, 6);
    r1i_soulK37D474 = 4;
    r1i_soulK37D476 = 0;
    if (!resume) {
        r1i_soulX37D46C = 0x80;
        r1i_itemCol37DAE0 = 0x153F4A;
    } else {
        r1i_soulX37D46C = 0;
        r1i_soulSt37D434 = 3;
        r1i_soulT37D438 = 0;
        r1i_soulM37D460 = 2;
        r1i_soulT37D454 = 0;
        r1i_itemF37DACC = -1.0f;
        r1i_itemCol37DAE0 = 0x193B55;
        r1i_itemA37DAD0 = 0x80;
        r1i_itemSt37DAA4 = 3;
        r1i_itemT37DAA8 = 0;
        r1i_itemT37DAC4 = 0;
    }
    v = Stats_Get(&g_stats, 0xC);
    r1i_itemV37DAD8 = v;
    r1i_itemV37DAD4 = v;
    r1i_itemV37DADC = v;
    r1i_hudFl37F0C8 |= 3;
    r1i_hud37FB70 = 0;
    if (resume) {
        r1i_keyF37F4AC = -1.0f;
        r1i_keyA37F4B0 = 0x80;
        r1i_keySt37F484 = 3;
        r1i_keyT37F488 = 0;
        r1i_keyT37F4A4 = 0;
    }
}
