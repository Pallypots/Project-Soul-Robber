/* Area r4d: mode switching helpers 0x0019BF80 and 0x0019D2A0 (r4d_10). Names inferred. */
#include "r4d.h"

/* 0x0019BF80: leave mode (from!=0)+3 and enter mode (to!=0)+3, yielding to the job loop while each
   step completes. Stack args (from to). */
void r4d_SwitchMode(int from, int to)
{
    int a, b;
    if (from == to)
        return;
    a = (from != 0) + 3;
    b = (to != 0) + 3;
    sub_00047B70(a);
    while (sub_00047B90(a))
        sub_000580D0();
    sub_00047A80(b);
    while (sub_00047B10(b) != 2)
        sub_000580D0();
    sub_00047B30(b);
    while (sub_00047B50(b))
        sub_000580D0();
}

/* 0x0019D2A0: background job that restores the game state after a menu, then sets job->done04.
   Stack arg (job). */
void r4d_ReturnToGame(R4dDoneFlag *job)
{
    sub_000576F0(r4d_g41316C, r4d_g413170);
    while (sub_00032450(0) && sub_00032470(0))
        sub_000580D0();
    sub_00087A50();
    sub_000D1D00(&g_stats);
    sub_000D1930(&g_stats);
    sub_0019BEB0(0x1810B);
    if (sub_000DFC00()) {
        sub_0005BBC0();
        sub_0005C430(((R4dCtx1F0 *)r4c_ctx42C8E4)->f1F0);
    }
    while (sub_000DFD00() == 1) {
        sub_000E0570();
        sub_000580D0();
    }
    job->done04 = 1;
}
