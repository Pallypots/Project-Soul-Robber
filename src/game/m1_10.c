/* Area m1, file 10: tail-call thunks. Names inferred. */
#include "m1j.h"

/* 0x00194B40: forwards to 0x194410 (r4h_FxThrowMove). */
void m1_FxThrowMoveThunk194B40(R4hFxNodeC *o, R4hFxActC *a)
{
    r4h_FxThrowMove(o, a);
}

/* 0x001A13D0: forwards to 0x1A1B90 (r4d_TempRestore). */
void m1_TempRestoreThunk1A13D0(void)
{
    r4d_TempRestore();
}
