/* Area m1, file 11: tail-call thunks. Names inferred. */
#include "m1k.h"

/* 0x0019C5D0: forwards to 0x1A1130 (a1a_GroupFreeAll). */
void m1_GroupFreeAllThunk19C5D0(A1aGroup *g)
{
    a1a_GroupFreeAll(g);
}

/* 0x001A85C0: forwards to 0x1A2120 (a1a_SwapHook8): swaps hook slot 8, returns the old one. */
A1aHook m1_SwapHook8Thunk1A85C0(A1aHook v)
{
    return a1a_SwapHook8(v);
}

/* 0x0019D8B0: forwards to 0xDE910 (adc_ResetAndPost). */
void m1_ResetAndPostThunk19D8B0(void)
{
    adc_ResetAndPost();
}
