/* Script variable helpers and small utilities 0x000DDDE0-0x000DE6C1.
 * Reference build OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#include "adc.h"

/* 0x000DDDE0: reset the script variable block to defaults. */
void adc_ResetScriptVars(void)
{
    af0_var3EDCBC = 0;
    af0_var3EDCC0 = 0;
    af0_var3EDCC4 = 0;
    af0_var3EDCC8 = 0;
    af0_var3EDCE8 = 0;
    af0_var3EDCF0 = 0;
    adc_var3EDCF4 = 0;
    adc_30D6B8 = -1;
    adc_30D6BC = 1;
    af0_var3EDCF8 = 0;
    af0_var3EDCFC = 0;
    adc_var3EDD00 = 0;
    adc_var3EDD04 = 0;
    adc_var3EDD08 = 0;
    adc_var3EDD0C = 0;
    adc_var3EDD10 = 0;
    adc_var3EDD14 = 0.0f;
    af0_var3EDD18 = 0;
    adc_var3EDCCC = -1;
    adc_var3EDCD0 = -1;
}

/* 0x000DDEF0: set the pair unless either half is locked (-2). */
void adc_SetPair(int a, int b)
{
    if (adc_var3EDCCC != -2 && adc_var3EDCD0 != -2) {
        adc_var3EDCCC = a;
        adc_var3EDCD0 = b;
    }
}

/* 0x000DDF20: read the pair. */
void adc_GetPair(int *a, int *b)
{
    *a = adc_var3EDCCC;
    *b = adc_var3EDCD0;
}

/* 0x000DE170: find the list node whose fields match (a, b). */
AdcNode *adc_FindNode(int a, int b)
{
    AdcNode *n;
    for (n = sub_000EDB10(0); n; n = sub_000EDB90()) {
        if (n->a == a && n->b == b)
            break;
    }
    return n;
}

/* 0x000DE1A0: read float field +0xB0. */
float adc_GetB0(uint8_t *o)
{
    return *(float *)(o + 0xB0);
}

/* 0x000DE2F0: random float between lo and hi (order-insensitive). */
float adc_RandRange(float lo, float hi)
{
    if (lo > hi) {
        float t = lo;
        lo = hi;
        hi = t;
    }
    return (float)aab_Rand() * (1.0f / 32767.0f) * (hi - lo) + lo;
}

/* 0x000DE4D0: true when the current (a, b) pair equals the arguments. */
int adc_PairIs(int a, int b)
{
    int x, y;
    sub_000DFD40(&x, &y);
    if (x == a && y == b)
        return 1;
    return 0;
}

/* 0x000DE590: clear every sound/stat channel. */
void adc_ClearChannels(void)
{
    sub_00023D80(0, 0);
    sub_000243B0(0, 0);
    sub_00024D30(0, 0);
    sub_000251B0(0, 0);
    sub_000252A0(0, 0);
    sub_000253D0(0, 0);
    sub_00025C10(0, 0);
    sub_00025D50(0, 0);
    sub_00025F50(0, 0);
    sub_00025F90(0, 0);
    aab_Sound260C0(0, 0, 0);
    aab_Sound260C0(1, 0, 0);
}

/* 0x000DE610: -1 when any level condition flag is set, else 0. */
int adc_AnyLevelFlag(void)
{
    if (a12_Level_37C544() || a12_Level_37D434() || a12_Level_37DAA4() ||
        a12_Level_37DC28() || a12_Level_37DCFC() || a12_Level_37ED04() ||
        a12_Level_37E094() || a12_Level_37EECC() || a12_FlagBit0() ||
        a12_FlagBit1())
        return -1;
    return a12_AnyBit1() ? -1 : 0;
}

/* 0x000DE680: set channels 0x25F50 and 0x25F90 to 1. */
void adc_SetChannels1(void)
{
    sub_00025F50(1, 0);
    sub_00025F90(1, 0);
}

/* 0x000DE6A0: count consecutive set tests 0x20..0x24. */
int adc_CountTests20(void)
{
    int n = 0, i;
    for (i = 0; i < 5; i++) {
        if (!sub_000D9A70(i + 0x20))
            break;
        n++;
    }
    return n;
}
