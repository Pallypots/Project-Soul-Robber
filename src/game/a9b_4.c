/* Area a9b, 0x00198460-0x0019AD10 (slot tables). Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9b.h"

/* 0x00198460: free the work block's +4 handle and detach the work block. */
int a9b_WorkDetach(void *ctx, a9b_Actor *a)
{
    a9b_Work *w = a->work;
    if (w->f4) {
        sub_00033A70((void *)w->f4);
        w->f4 = 0;
    }
    w->flags0 = 0;
    w->f4 = 0;
    a->work = 0;
    return 1;
}

/* 0x00198780: on message 5 update with mode 4 and clear work +8. */
int a9b_OnMsg5(void *ctx, a9b_Actor *a, int *msg)
{
    if (*msg == 5) {
        sub_00189DA0(ctx, a, 4);
        a->work->f8 = 0;
    }
    return 1;
}

/* 0x001987B0: on message 0x2D update with mode 4 and clear work +4. */
int a9b_OnMsg2D(void *ctx, a9b_Actor *a, int *msg)
{
    if (*msg == 0x2D) {
        sub_00189DA0(ctx, a, 4);
        a->work->f4 = 0;
    }
    return 1;
}

/* 0x00199850: +0x10 of active slot i (0..15) at 0x00401B30, or -1. */
int a9b_Slot401B30Get10(int i)
{
    if (i >= 0 && i < 16 && a9b_g401B30[i].f0) {
        if (a9b_g401B30[i].f10 >= 0)
            return a9b_g401B30[i].f10;
    }
    return -1;
}

/* 0x00199880: whether active slot i (0..15) with valid +0x10 has +4 set. */
int a9b_Slot401B30Has4(int i)
{
    if (i >= 0 && i < 16 && a9b_g401B30[i].f0 && a9b_g401B30[i].f10 >= 0)
        return a9b_g401B30[i].f4 != 0;
    return 0;
}

/* 0x00199DE0: +8 of the 0x00401D70 slot linked from entry i (0..10) of 0x003316A0, or -1. */
int a9b_Link3316A0Get8(int i)
{
    if (i <= -1 || i >= 11) for (;;) ;
    if (a9b_g3316A0[i].b0)
        return a9b_g401D70[a9b_g3316A0[i].b10].f8;
    return -1;
}

/* 0x0019A480: word +2 of entry i (-1..995) at 0x0032C930; 0 for -1. */
int a9b_Get32C930W2(int i)
{
    if (i < -1 || i >= 0x3E4) for (;;) ;
    if (i == -1)
        return 0;
    return a19_g32C930[i].w2;
}

/* 0x0019A8B0: clear +8 of active slot i (0..0) at 0x00401AF8. */
void a9b_Slot401AF8Clear8(int i)
{
    if (i >= 0 && i < 1 && a9b_g401AF8[i].f0) {
        if (a9b_g401AF8[i].f0)
            a9b_g401AF8[i].f8 = 0;
    }
}

/* 0x0019A900: +8 of active slot i (0..2) at 0x004019D8 if non-negative, else -1. */
int a9b_Slot4019D8Get8(int i)
{
    if (i >= 0 && i < 3 && a19_g4019D8[i].f0 && a19_g4019D8[i].f8 >= 0)
        return a19_g4019D8[i].f8;
    return -1;
}

/* 0x0019A9D0: free slot i of 0x004019D8 when its +4 is clear; reset 0x00401B28. */
void a9b_Slot4019D8Free(int i)
{
    if (i < 0)
        return;
    if (a19_g4019D8[i].f4 == 0) {
        a19_g4019D8[i].f8 = 0;
        a19_g4019D8[i].f0 = 0;
        a19_g401B28 = 0;
    }
}

/* 0x0019ACE0: sub-entry j (0..3) first field of slot i (0..2) at 0x004019D8, else 0. */
int a9b_Slot4019D8Sub(int i, int j)
{
    if (i < 0 || i >= 3)
        return 0;
    if (j < 0 || j >= 4) for (;;) ;
    return a19_g4019D8[i].sub[j].f0;
}

/* 0x0019AD10: word j (0..3) of table entry i (0..0x263) at 0x003317C0. */
int a9b_EntryWord(int i, int j)
{
    if (i <= -1 || i >= 0x264) for (;;) ;
    if (j < 0 || j >= 4) for (;;) ;
    return (&a9b_g3317C0[i].w6)[j * 4];
}
