/* Area a9b, 0x00199B00-0x0019D710. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9b.h"

/* 0x00199B00: word at 0x003316B4 (index 0..1 asserted, unused). */
int a9b_Get3316B4(int i)
{
    if (i <= -1 || i >= 2) for (;;) ;
    return a9b_g3316B4;
}

/* 0x0019A810: first field of record i (0..0) at 0x00401AF8, else 0. */
int a9b_GetRec401AF8(int i)
{
    if (i < 0 || i >= 1)
        return 0;
    return a9b_g401AF8[i].f0;
}

/* 0x0019A8E0: word +0 of 24-byte record i (0..0) at 0x003317B8. */
int a9b_GetRec3317B8(int i)
{
    if (i <= -1 || i >= 1) for (;;) ;
    return a9b_g3317B8[i].f0;
}

/* 0x0019ADC0: signed byte +2 of table entry i (0..0x263) at 0x003317C0. */
int a9b_GetEntryByte2(int i)
{
    if (i <= -1 || i >= 0x264) for (;;) ;
    return ((int8_t *)&a9b_g3317C0[i].f0)[2];
}

/* 0x0019ADE0: top 4 bits (signed) of table entry i (0..0x263). */
int a9b_GetEntryTop4(int i)
{
    if (i <= -1 || i >= 0x264) for (;;) ;
    return a9b_g3317C0[i].f0 >> 28;
}

/* 0x0019B9F0: decrement counter 0x00402FA8 (asserts it is positive). */
void a9b_Dec402FA8(void)
{
    int n = g_402FA8;
    if (n <= 0) for (;;) ;
    g_402FA8 = n - 1;
}
