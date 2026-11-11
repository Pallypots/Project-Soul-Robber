/* Area r6d: shop prices at 0x00060B20 (r6d_4). Names inferred. */
#include "r6d.h"

/* 0x00060B20: price of a shop item (item 28 half price until stat 0x29 is set;
   60% when the discount flag is clear). */
int r6d_ItemPrice(int id)
{
    int v;
    if (id == 0x1C) {
        v = r6d_prices[0x1C];
        if (!Stats_Get(&g_stats, 0x29))
            v /= 2;
    } else {
        v = r6d_prices[id];
    }
    if (!adc_413178)
        v = v * 60 / 100;
    return v;
}


/* 0x00060300: shop close sequence: fade out, restore the game state, then reset the page. */
void r6d_ShopCloseStep(void)
{
    switch (a60_v3E60D8) {
    case 0:
        sub_00024D30(0, 0);
        r6d_timer3E6100 = 20.0f;
        a60_v3E60D8++;
        break;
    case 1:
        a60_StepByFrame(&r6d_timer3E6100, 0);
        if (r6d_timer3E6100 <= 0.0f) {
            sub_00024D30(5, 0);
            sub_00023D80(0, 0);
            sub_000243B0(0, 0);
            a60_v3E60D8++;
        }
        break;
    case 2:
        a60_StepByFrame(&r6d_timer3E6100, 0);
        if (r6d_timer3E6100 <= 0.0f) {
            a60_state3E60D4 = 0;
            a60_v3E60D8 = 0;
            a60_v3E60DC = 0;
            a60_v3E60E0 = 0;
        }
        break;
    }
}
