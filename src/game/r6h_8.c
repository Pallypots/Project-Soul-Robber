/* Area r6h: menu item list builder (r6h_8). Names inferred. */
#include <string.h>
#include "r6h.h"

/* 0x000603C0: build the item list of a menu page from the event flags and
   stats and return the number of items (also stored in r6h_menuCount3E6112).
   Page 0: item 1 unless flag 0x37F is set, always item 3, item 0x17 for flag
   0xF4 without 0xF8, item 0x1C while stat 0x29 is below its maximum (stat
   0x1C) and stat 0 below 30. Other pages: one entry per upgradeable stat
   (4, 6, 8, 9, 10 and 11, each while below 2, offset by its base id; 6 needs
   flag 0xF4, 8..11 need flag 0xF5, 11 only on level 0) and item 0x2F for flag
   0xC without 0xD. */
int r6h_MenuBuildList(int page)
{
    int n = 0;
    int v;

    memset(r6h_menuItems3E6104, 0, sizeof(r6h_menuItems3E6104));
    if (page == 0) {
        if (!sub_000D9A70(0x37F)) {
            n = 1;
            r6h_menuItems3E6104[0] = (int16_t)n;
        }
        r6h_menuItems3E6104[n++] = 3;
        if (sub_000D9A70(0xF4) && !sub_000D9A70(0xF8))
            r6h_menuItems3E6104[n++] = 0x17;
        if (Stats_Get(&g_stats, 0x29) < Stats_GetMax(0x1C) && Stats_Get(&g_stats, 0) < 30)
            r6h_menuItems3E6104[n++] = 0x1C;
        r6h_menuCount3E6112 = (int16_t)n;
        return n;
    }
    v = Stats_Get(&g_stats, 4);
    if (v < 2) {
        r6h_menuItems3E6104[0] = (int16_t)(v + 6);
        n = 1;
    }
    v = Stats_Get(&g_stats, 6);
    if (sub_000D9A70(0xF4) && v < 2)
        r6h_menuItems3E6104[n++] = (int16_t)(v + 9);
    if (sub_000D9A70(0xF5)) {
        v = Stats_Get(&g_stats, 8);
        if (v < 2)
            r6h_menuItems3E6104[n++] = (int16_t)(v + 0xC);
        v = Stats_Get(&g_stats, 9);
        if (v < 2)
            r6h_menuItems3E6104[n++] = (int16_t)(v + 0xF);
        v = Stats_Get(&g_stats, 10);
        if (v < 2)
            r6h_menuItems3E6104[n++] = (int16_t)(v + 0x12);
        if (!rfl_level413178) {
            v = Stats_Get(&g_stats, 0xB);
            if (v < 2)
                r6h_menuItems3E6104[n++] = (int16_t)(v + 0x15);
        }
    }
    if (sub_000D9A70(0xC) && !sub_000D9A70(0xD))
        r6h_menuItems3E6104[n++] = 0x2F;
    r6h_menuCount3E6112 = (int16_t)n;
    return n;
}
