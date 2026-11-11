/* Area r1j, group 10: HUD sequence save 0x0002B820.
   Names inferred. */
#include "r1j.h"

/* 0x0002B820: snapshot the HUD sequence blocks as the restart templates:
   reset the 15 gauge scales of block A to 1.0, drop a pending command
   4..6 from its queue, refresh the health fields from the player stats,
   copy the live blocks A, B, C and E over their templates, then rebuild
   the HUD (0x00026B50 resume=1) and 0x00026CF0(1). */
void r1j_HudSeqSave(void)
{
    int i, cmd;
    for (i = 0; i < 15; i++) {
        r1j_seqA37C4FC.gauge[i].scaleY = 1.0f;
        r1j_seqA37C4FC.gauge[i].scaleX = 1.0f;
    }
    cmd = r1j_seqA37C4FC.queue[0];
    if (cmd == 4 || cmd == 5 || cmd == 6) {
        r1j_seqA37C4FC.queue[0] = r1j_seqA37C4FC.queue[1];
        r1j_seqA37C4FC.queue[1] = r1j_seqA37C4FC.queue[2];
        r1j_seqA37C4FC.queue[2] = r1j_seqA37C4FC.queue[3];
        r1j_seqA37C4FC.queue[3] = r1j_seqA37C4FC.queue[4];
        r1j_seqA37C4FC.queue[4] = r1j_seqA37C4FC.queue[5];
        r1j_seqA37C4FC.queue[5] = r1j_seqA37C4FC.queue[6];
        r1j_seqA37C4FC.queue[6] = r1j_seqA37C4FC.queue[7];
        r1j_seqA37C4FC.queue[7] = 0;
        r1j_seqA37C4FC.d68 = 0;
    }
    r1j_seqA37C4FC.maxHealth = Stats_Get(&g_stats, 0);
    r1j_seqA37C4FC.health = Stats_Get(&g_stats, 1);
    r1j_seqA37C4FC.d7C = 0;
    r1j_seqA37C4FC.w84 = 0;
    r1j_seqA37C4FC.w86 = 0;
    r1j_seqA37C4FC.d80 = 0;
    r1j_seqA37FB78 = r1j_seqA37C4FC;
    r1j_seqB380C48 = r1j_seqB37D424;
    r1j_seqC380AA0 = r1j_seqC37DA98;
    r1j_seqE3812C0 = r1j_seqE37F480;
    sub_00026B50(1);
    sub_00026CF0(1);
}
