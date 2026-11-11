/* Area a9b, 0x00190870-0x001960E0. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9b.h"

/* 0x00190870: 1 unless at least six of the ten slots at 0x004003A0 are free. */
int a9b_HasFewFreeSlots(void)
{
    int n = 0, i;
    for (i = 0; i < 10; i++) {
        if (a9b_g4003A0[i].f0 == 0 && ++n >= 6)
            return 0;
    }
    return 1;
}

/* 0x001940D0: clear work flag bit 0 and notify the +0x18 handle. */
int a9b_WorkRelease(void *ctx, a9b_Actor *a)
{
    a9b_Work *w = a->work;
    w->flags0 &= ~1u;
    if (w->f18)
        sub_001777A0(w->f18, ctx, w->f10);
    return 1;
}

/* 0x00194860: optionally sink +0x70 by frame time * 60, then update. */
void a9b_SinkAndUpdate(void *ctx, a9b_Actor *a)
{
    if (a->work->flags0 & 0x10)
        a->f70 -= a50_frameSeconds * 60.0f;
    sub_00189DA0(ctx, a, 1);
}

/* 0x00195110: release the handles of slots in state 3 or 4 at 0x00400E50. */
void a9b_ReleaseSlots(void)
{
    int i;
    for (i = 0; i < 18; i++) {
        if ((a9b_g400E50[i].f10 == 3 || a9b_g400E50[i].f10 == 4) && a9b_g400E50[i].f4)
            sub_000ED780(a9b_g400E50[i].f4);
    }
}

/* 0x001951E0: call 0x1EEC0 with work +0x18, advance work timer +0x0C. */
void a9b_WorkTick(void *ctx, a9b_Actor *a)
{
    a9b_Work *w = a->work;
    sub_0001EEC0(ctx, A9B_WF18(w));
    w->fC += a50_frameSeconds;
}

/* 0x00195DB0: scale work vector +0x44 by -2, clear +0x50/+0x48/+0x20. */
void a9b_WorkReflect44(void *ctx, a9b_Actor *a)
{
    a9b_Work *w = a->work;
    sub_001ADB60(w->v44, w->v44, -2.0f);
    w->f50 = 0.0f;
    w->v44[1] = 0.0f;
    w->f20 = 0.0f;
}

/* 0x00195F00: count work timer +0x18 down by 0.34, clamped at 0. */
void a9b_WorkCountdown34(void *ctx, a9b_Actor *a)
{
    a9b_Work *w = a->work;
    A9B_WF18(w) -= 0.34f;
    if (A9B_WF18(w) < 0.0f)
        A9B_WF18(w) = 0.0f;
}

/* 0x001960A0: count work +0x18 down by 0.5667; on expiry release ctx. */
void a9b_CountdownRelease(a9b_Actor *ctx, a9b_Actor *a)
{
    a9b_Work *w = a->work;
    A9B_WF18(w) -= 0.56666666f;
    if (A9B_WF18(w) < 0.0f) {
        A9B_WF18(w) = 0.0f;
        sub_000ED780(ctx);
    }
}

/* 0x001960E0: count work +0x18 down by 0.5667; on expiry call 0x1D7A0. */
void a9b_CountdownRefresh(a9b_Actor *ctx, a9b_Actor *a)
{
    a9b_Work *w = a->work;
    A9B_WF18(w) -= 0.56666666f;
    if (A9B_WF18(w) < 0.0f) {
        A9B_WF18(w) = 0.0f;
        sub_0001D7A0(ctx);
    }
}
