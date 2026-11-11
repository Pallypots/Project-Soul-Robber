/* Area r1j, group 17: graphics reset 0x0003DE20.
   Names inferred. */
#include "r1j.h"

/* 0x0003DE20: reset the graphics state: the (empty in this build) setup
   hooks 0x000AD090 / 0x00102FA0 with their original arguments, clear the
   screen (0x00014940), reset both session slots (bytes cleared, scale
   1.0), set the default TEST register value 0x5000D in the three
   packets, and rebuild the fixed register packet (0x0003DD30, tail
   call). interlaced selects field mode 3 instead of 2. */
void r1j_GfxReset(int interlaced)
{
    int i;
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_000AD090(0);
    sub_00102FA0(0, 1, interlaced == 0 ? 2 : 3, 1);
    sub_00014940(0, 0, 0, 0);
    sub_00102FA0(r1j_pkt3DE5B0, 0, 0x200, 0xE0, 2, 0x31, 1);
    g_sessionSlots[0].b[0] = 0;
    g_sessionSlots[0].b[1] = 0;
    g_sessionSlots[0].b[2] = 0;
    g_sessionSlots[0].b[3] = 0;
    g_sessionSlots[0].scale = 1.0f;
    g_sessionSlots[1].b[0] = 0;
    g_sessionSlots[1].b[1] = 0;
    g_sessionSlots[1].b[2] = 0;
    g_sessionSlots[1].b[3] = 0;
    g_sessionSlots[1].scale = 1.0f;
    for (i = 20; i != 0; i--)
        sub_000AD090(0);
    r1j_test42CAE8[0] = 0x5000D;
    r1j_test42CAE8[1] = 0;
    r1j_test3DE680 = 0x5000D;
    r1j_test3DE770 = 0x5000D;
    sub_00102FA0(0);
    sub_0003DD30();
}
