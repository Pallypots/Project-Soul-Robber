/* Area r2b, group 5: script support helpers (0x000DE000..0x000DFFFF). Names inferred. */
#include "r2b.h"

/* 0x000DF830: apply entry (8, 0x72) and, for each of flag bits 0xF9..0xFC that is set,
   entry (0xC..9, 0xF2) to object 0x417868. */
void r2b_ApplyUnlocks(void)
{
    sub_000E0380(r2b_g417868, 8, 0x72);
    if (r2b_TestBit(0xF9))
        sub_000E0380(r2b_g417868, 0xC, 0xF2);
    if (r2b_TestBit(0xFA))
        sub_000E0380(r2b_g417868, 0xB, 0xF2);
    if (r2b_TestBit(0xFB))
        sub_000E0380(r2b_g417868, 0xA, 0xF2);
    if (r2b_TestBit(0xFC))
        sub_000E0380(r2b_g417868, 9, 0xF2);
}

/* 0x000DFCC0: suspend every script thread except the first, the last and thread keep. */
void r2b_SuspendThreads(int keep)
{
    int i;
    for (i = 0; i < adc_threadCount; i++) {
        uint16_t *f = &adc_threads[i].flags54;
        if (f != &adc_threads[0].flags54 && i != adc_threadCount - 1 && i != keep)
            *f |= 1;
    }
}

/* 0x000E0510: step every runnable script thread (not flagged 1 or 2): only thread 0
   when 0x3F0738 is set, only the last one when 0x3F073C is set, else all but the
   first and the last.  calls 0x000DFF40 with ESI=thread */
void r2b_RunThreads(void)
{
    int i = 0, end = adc_threadCount;
    if (end) {
        if (af0_var3F0738)
            end = 1;
        else if (af0_var3F073C)
            i = end - 1;
        else {
            i = 1;
            end--;
        }
    }
    for (; i < end; i++)
        if (!(adc_threads[i].flags54 & 3))
            sub_000DFF40(&adc_threads[i]);
}
