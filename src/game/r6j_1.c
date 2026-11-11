/* Area r6j: menu item availability (r6j_1). Names inferred. */
#include "r6j.h"

/* 0x000605B0: returns 1 when menu item `item` (1..48) is available, from
   event flags (0x000D9A70) and player stats (Stats_Get on g_stats).
   The three shared tests at the end of the cases (stat == 1, stat == -1,
   value == 0) are written as labels reached with goto, as in the original. */
int r6j_MenuItemAvailable(int item)
{
    int ok = 0;
    int stat;
    int id;
    int r;

    switch (item) {
    case 1:
        id = 0x37F;
        goto flag_clear;
    case 28:
        if (Stats_Get(&g_stats, 0x29) >= Stats_GetMax(0x1C))
            break;
        if (Stats_Get(&g_stats, 0) >= 0x1E)
            break;
        return 1;
    case 47:
        if (sub_000D9A70(0xC) == 0)
            break;
        id = 0xD;
        goto flag_clear;
    case 23:
        if (sub_000D9A70(0xF4) == 0)
            break;
        return 1;
    case 6:
        r = Stats_Get(&g_stats, 4);
        goto is_zero;
    case 7:
        stat = 4;
        goto is_one;
    case 9:
        if (sub_000D9A70(0xF4) == 0)
            break;
        r = Stats_Get(&g_stats, 6);
        goto is_zero;
    case 10:
        if (sub_000D9A70(0xF4) == 0)
            break;
        stat = 6;
        goto is_one;
    case 12:
        if (sub_000D9A70(0xF5) == 0)
            break;
        r = Stats_Get(&g_stats, 8);
        goto is_zero;
    case 13:
        if (sub_000D9A70(0xF5) == 0)
            break;
        stat = 8;
        goto is_one;
    case 14:
        if (sub_000D9A70(0xF5) == 0)
            break;
        stat = 9;
        goto is_minus_one;
    case 15:
        if (sub_000D9A70(0xF5) == 0)
            break;
        r = Stats_Get(&g_stats, 9);
        goto is_zero;
    case 16:
        if (sub_000D9A70(0xF5) == 0)
            break;
        stat = 9;
        goto is_one;
    case 17:
        if (sub_000D9A70(0xF5) == 0)
            break;
        stat = 10;
        goto is_minus_one;
    case 18:
        if (sub_000D9A70(0xF5) == 0)
            break;
        r = Stats_Get(&g_stats, 10);
        goto is_zero;
    case 19:
        if (sub_000D9A70(0xF5) == 0)
            break;
        stat = 10;
        goto is_one;
    case 20:
        if (r6i_g413178 != 0 || sub_000D9A70(0xF5) == 0)
            break;
        stat = 11;
    is_minus_one:
        if (Stats_Get(&g_stats, stat) != -1)
            break;
        ok = 1;
        break;
    case 21:
        if (r6i_g413178 != 0 || sub_000D9A70(0xF5) == 0)
            break;
        r = Stats_Get(&g_stats, 11);
        goto is_zero;
    case 22:
        if (r6i_g413178 != 0 || sub_000D9A70(0xF5) == 0)
            break;
        stat = 11;
    is_one:
        if (Stats_Get(&g_stats, stat) != 1)
            break;
        ok = 1;
        break;
    case 48:
        if (sub_000D9A70(0x10C) == 0)
            break;
        id = 0x52;
    flag_clear:
        r = sub_000D9A70(id);
    is_zero:
        if (r != 0)
            break;
        /* fall through */
    case 3:
        ok = 1;
        break;
    }
    return ok;
}
