/* Area r4e: sound driver slot wait at 0x001AB210 (r4e_12). Names inferred. */
#include "r4e.h"

/* 0x001AB210: sleep 1 ms on a waitable timer (alertable), then run the slot's two
   member updates 0x001ACF30 and 0x001ACF00 (this in ECX). Stack args (unused i). */
void r4e_DrvSlotSettle(int unused, int i)
{
    R4eDrvSlot *d = &aac_g40E604[i];
    int64_t due;
    void *h = sub_001BD128(0, 1, 0);
    due = -10000;
    sub_001BD186(h, &due, 0, 0, 0, 0);
    WaitForSingleObjectEx(h, 0, 1);
    sub_001BC6FD(h);
    sub_001ACF30(d);
    sub_001ACF00(d);
}
