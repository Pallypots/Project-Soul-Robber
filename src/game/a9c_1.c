/* Area a9c, 0x00190000-0x00196000. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9c.h"

/* 0x001909C0: kinds 0x18/0x19 get the work +8 value applied; destroy when +0x64 exceeds 100. */
void a9c_ApplyAndCull(a9c_Obj *o, a9c_Obj *a)
{
    if (o->f08 == 0x19 || o->f08 == 0x18)
        sub_0001EEC0(o, a->work->f8);
    if (o->f64 > 100.0f)
        sub_000ED780(o);
}

/* 0x00191C70: reset the 26 records at 0x00400120 (state 2). */
void a9c_ResetRecs400120(void)
{
    a9c_Rec18 *r;
    for (r = a9c_g400120; r < a9c_g400120 + 26; r++) {
        r->f0 = 0;
        r->f4 = 2;
    }
}

/* 0x00194A40: when work flag 4 is set advance +0x84; any of flags 0x1E at +0x128 switch to mode 2. */
void a9c_TickAndMode2(a9c_Obj *ctx, a9c_Obj *a)
{
    if (a->work->flags0 & 4)
        ctx->f84 += 0.02f;
    if (ctx->f128 & 0x1E)
        sub_00189DA0(ctx, a, 2);
}

/* 0x00195C10: switch to mode 2 once work +0xC exceeds 11, then advance it by the frame time. */
void a9c_TimerMode2(a9c_Obj *ctx, a9c_Obj *a)
{
    a9c_Work *w = a->work;
    if (w->fC > 11.0f)
        sub_00189DA0(ctx, w->obj8, 2);
    w->fC += a50_frameSeconds;
}

/* 0x00195E80: copy +0x60/+0x68 from the owner, set +0x64 to -500 and refresh. */
void a9c_CopyFromOwner(a9c_Obj *o, a9c_Obj *a)
{
    a9c_Obj *owner = A9C_OWNER(a->work);
    o->f60 = owner->f60;
    o->f68 = owner->f68;
    o->f64 = -500.0f;
    sub_0001D720(o);
}

/* 0x00195EB0: work +0x18 = 1.7 - (85 + owner +0x64) / 85 * 0.8, capped at 1.7. */
void a9c_ScaleFromOwner(a9c_Obj *o, a9c_Obj *a)
{
    a9c_Work *w = a->work;
    float v = 1.7f - (85.0f - (0.0f - A9C_OWNER(w)->f64)) * 0.0117647061f * 0.8f;
    w->f18 = v;
    if (v > 1.7f)
        w->f18 = 1.7f;
}

/* 0x00195F30: copy +0x60/+0x68 from the player object and refresh. */
void a9c_CopyFromPlayer(a9c_Obj *o)
{
    o->f60 = ((a9c_Obj *)g_playerObj)->f60;
    o->f68 = ((a9c_Obj *)g_playerObj)->f68;
    sub_0001D720(o);
}

/* 0x001945D0: first time pick a random delay (180..299 frames scaled by frame time); work +0x14 = delay / 8. */
void a9c_RandomDelay(a9c_Obj *ctx, a9c_Obj *a)
{
    if (!(a->work->flags0 & 0x10)) {
        a->f70 = ((float)(sub_001C7EE1() % 120) + 180.0f) * a50_frameSeconds;
        a->work->flags0 |= 0x10;
    }
    a->work->f14 = a->f70 * 0.125f;
}
