/* Area m1, part k: tail-call thunks into a1a / adc. Names inferred. */
#ifndef M1K_H
#define M1K_H
#include "a1a.h"
void    a1a_GroupFreeAll(A1aGroup *g);       /* 0x001A1130 */
A1aHook a1a_SwapHook8(A1aHook v);            /* 0x001A2120 */
void    adc_ResetAndPost(void);              /* 0x000DE910 */
void    m1_GroupFreeAllThunk19C5D0(A1aGroup *g);   /* 0x0019C5D0 */
A1aHook m1_SwapHook8Thunk1A85C0(A1aHook v);       /* 0x001A85C0 */
void    m1_ResetAndPostThunk19D8B0(void);          /* 0x0019D8B0 */
#endif
