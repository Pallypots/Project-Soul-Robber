/* Script system helpers 0x000DE8C0-0x000DFF31. Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#include "adc.h"

/* 0x000DE8C0: post the stored command pair. */
void adc_PostStoredCommand(void)
{
    a60_PostCommand(adc_var3EDCF4, adc_30D6B8);
}

/* 0x000DE910: reset channels and post event 10. */
void adc_ResetAndPost(void)
{
    sub_000325A0(1);
    adc_ClearChannels();
    sub_0019D7A0(10, 0);
}

/* 0x000DE970: refill: restore stat 1 from stat 0 and raise stat 0xF to 0xE. */
void adc_RefillStats(void)
{
    int v;
    adc_StatD0030(&g_stats, 0x50);
    sub_00048AF0(0x5D);
    v = Stats_Get(&g_stats, 0);
    Stats_Set(&g_stats, 1, v);
    sub_00026280(v, v);
    v = Stats_Get(&g_stats, 0xE);
    if (v > Stats_Get(&g_stats, 0xF))
        Stats_Set(&g_stats, 0xF, v);
}

/* 0x000DE9E0: set bit n of 0x3EDD00. */
void adc_SetBit(int n)
{
    adc_var3EDD00 |= 1 << n;
}

/* 0x000DEA00: toggle bit n of 0x3EDD00. */
void adc_ToggleBit(int n)
{
    adc_var3EDD00 ^= 1 << n;
}

/* 0x000DEA20: test bit n of 0x3EDD00. */
int adc_TestBit(int n)
{
    return (1 << n) & adc_var3EDD00;
}

/* 0x000DF8E0: map mode 1..5 into 0x3EDD18; 0 when the mode is unknown. */
int adc_MapMode(void)
{
    switch (sub_000E03D0()) {
    case 1: af0_var3EDD18 = 0; return 1;
    case 2: af0_var3EDD18 = 4; return 1;
    case 3: af0_var3EDD18 = 3; return 1;
    case 4: af0_var3EDD18 = 1; return 1;
    case 5: af0_var3EDD18 = 2; return 1;
    }
    af0_var3EDD18 = 0;
    return 0;
}

/* 0x000DF970: pause the sound when test 0xF0 is set and it is playing. */
void adc_SndPauseIf(void)
{
    if (sub_000D9A70(0xF0) && af0_var3EDD1C)
        a5b_SndPause();
}

/* 0x000DF990: resume the sound when test 0xF0 is set and it is playing. */
void adc_SndResumeIf(void)
{
    if (sub_000D9A70(0xF0) && af0_var3EDD1C)
        a5b_SndBegin();
}

/* 0x000DF9C0: release the sound if playing. */
void adc_SndStop(void)
{
    if (af0_var3EDD1C) {
        a5b_SndRelease();
        af0_var3EDD1C = 0;
    }
}

/* 0x000DFC00: advance state 2 -> 3; -1 when not in state 2. */
int adc_State2To3(void)
{
    if (af0_var3F0734 != 2)
        return -1;
    af0_var3F0734 = 3;
    af0_var3F0738 = 1;
    sub_0019D450(1);
    if (g_ad0_41316C == 0 && g_ad0_413170 <= 2)
        sub_000D7590();
    return 0;
}

/* 0x000DFC50: in state 3, reset the queue and set 0x3F073C. */
int adc_State3Reset(void)
{
    if (af0_var3F0734 != 3)
        return -1;
    sub_0003FC10(&af0_var3EE6A8);
    af0_var3F073C = 1;
    return 0;
}

/* 0x000DFC90: resume every script thread. */
void adc_ResumeThreads(void)
{
    int i;
    for (i = 0; i < adc_threadCount; i++)
        *(uint8_t *)&adc_threads[i].flags &= ~1;
}

/* 0x000DFD40: read the (0x41316C, 0x413170) pair. */
void adc_GetMode(int *a, int *b)
{
    *a = g_ad0_41316C;
    *b = g_ad0_413170;
}

/* 0x000DFD60: reset the queue and push one item when b is valid. */
void adc_QueueReset(int a, int b, int c)
{
    sub_0003FC10(&af0_var3EE6A8);
    if (b != -1)
        sub_0003FCB0(&af0_var3EE6A8, sub_0003FA70(a, b, c, 30.0f, -1.0f));
}

/* 0x000DFDB0: push one item when b is valid. */
void adc_QueuePush(int a, int b, int c)
{
    if (b != -1)
        sub_0003FCB0(&af0_var3EE6A8, sub_0003FA70(a, b, c, 30.0f, -1.0f));
}

/* 0x000DFE30: pop n items from the queue. */
void adc_QueuePop(int n)
{
    if (n > 0) {
        do
            sub_0003FC40(&af0_var3EE6A8);
        while (--n);
    }
}

/* 0x000DFE90: set flag bit 8 on object 0x3EE6B0. */
void adc_SetFlag8(int v)
{
    a60_FlagBit8(adc_3EE6B0, v);
}

/* 0x000DFEB0: set flag bit 1 on object 0x3EE6B0. */
void adc_SetFlag1(int v)
{
    a60_FlagBit1(adc_3EE6B0, v);
}
