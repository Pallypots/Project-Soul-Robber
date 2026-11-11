/* Area r2d, group 5: stage director helpers (0x000E14C0..0x000E51E6). Names inferred. */
#include "r2d.h"

/* 0x000E14C0: release both handles of link idx and clear them. */
void r2d_StageLinkFree(R2dStage *o, int idx)
{
    void **a = &o->links534[idx].h0;
    void **b;
    if (*a)
        sub_0001EB80(*a);
    b = &o->links534[idx].h4;
    if (*b)
        sub_0001EB80(*b);
    *a = 0;
    *b = 0;
}

/* 0x000E1520: point link idx at the player (k = 0), slot k (1..5) or
   nothing. */
void r2d_StageLinkTarget(R2dStage *o, int idx, int k)
{
    void *t = 0;
    if (k == 0)
        t = g_playerObj;
    else if (k > 0 && k <= 5)
        t = o->slots86C[k - 1].p00;
    o->links534[idx].tgt8 = t;
}

/* 0x000E1570: set track idx's two blend values to f and copy its two
   vectors. */
void r2d_StageTrackSet(R2dStage *o, int idx, float f, const void *a, const void *b)
{
    R2dTrackV *t = &o->trk594[idx];
    t->f0 = f;
    t->f4 = f;
    sub_000F5D40(t->v8, a);
    sub_000F5D40(t->v18, b);
}

/* 0x000E19F0: copy the five saved words at +0x850 to +0x79C, set both
   blend values to f and the weight to 1. */
void r2d_StageRestore(R2dStage *o, float f)
{
    if (!o)
        return;
    o->v79C[0] = o->v850[0];
    o->v79C[1] = o->v850[1];
    o->v79C[2] = o->v850[2];
    o->v79C[3] = o->v850[3];
    o->v79C[4] = o->v850[4];
    o->f794 = f;
    o->f798 = f;
    o->f7B0 = 1.0f;
}

/* 0x000E1C20: set the fade time to f and the colour to (r, g, b, a). */
void r2d_StageFadeColor(R2dStage *o, float f, int r, int g, int b, int a)
{
    if (!o)
        return;
    o->f3F0 = f;
    o->f3F4 = f;
    o->f3F8 = (float)r;
    o->f3FC = (float)g;
    o->f400 = (float)b;
    o->f404 = (float)a;
}

/* 0x000E1C80: set the fade time to f with the default grey (128, 128, 128)
   and alpha 24. */
void r2d_StageFadeGrey(R2dStage *o, float f)
{
    if (!o)
        return;
    o->f3F0 = f;
    o->f3F4 = f;
    o->f3F8 = 128.0f;
    o->f3FC = 128.0f;
    o->f400 = 128.0f;
    o->f404 = 24.0f;
}

/* 0x000E1F60: switch slot idx to state s: run the old state's exit
   handler, reset the slot timer, run the new state's enter handler. */
void r2d_StageSlotSetState(R2dStage *o, int idx, int s)
{
    R2dSlot *sl;
    R2dSlotFn fn;
    if (!o)
        for (;;) ;
    sl = &o->slots86C[idx];
    fn = r2d_slotExit317C30[sl->state1C];
    if (!fn)
        for (;;) ;
    fn(o, idx);
    sl->state1C = s;
    sl->t20 = 0.0f;
    sl->n24 = 0;
    fn = r2d_slotEnter317BF0[s];
    if (!fn)
        for (;;) ;
    fn(o, idx);
}

/* 0x000E3AF0: report whether the stage stream is finished (no streaming,
   or the stream reached state 5). */
int r2d_StageStreamDone(R2dStage *o)
{
    if (!g_acb_3F0A78)
        return 1;
    if (r2d_g3F0A80)
        return 0;
    if (o->h2EC < 0 || o->v2F8)
        return 0;
    return sub_000E07F0(o) == 5;
}

/* 0x000E3B40: open stream id for the stage unless one is open; returns the
   handle. */
int r2d_StageStreamOpen(R2dStage *o, int id)
{
    int h;
    if (!o)
        for (;;) ;
    if (o->h2EC >= 0)
        return o->h2EC;
    h = sub_0019A950(id, 0);
    o->h2EC = h;
    if (h >= 0) {
        o->id2E8 = id;
        o->v2F0 = 0;
        sub_00053F20(0);
        sub_00053F70(0);
    }
    return o->h2EC;
}

/* 0x000E3BA0: stop the stage stream (fade 1000 ms) and its partner. */
void r2d_StageStreamStop(R2dStage *o)
{
    if (!o)
        for (;;) ;
    if (o->h2EC < 0)
        return;
    sub_0019AA00(o->h2EC, 1000);
    sub_0019AA00(o->h2FC, 0);
    sub_00054040();
    sub_00053F70(0);
    o->h2EC = -1;
    o->v2F8 = 1;
    o->v2F0 = 0;
}

/* 0x000E3C40: current stream position of the stage, wrapped into the
   stream's loop range. */
uint32_t r2d_StageStreamPos(R2dStage *o)
{
    uint32_t now, lo, hi;
    if (!o)
        for (;;) ;
    now = sub_00053F60();
    lo = sub_00048530(o->id2E8);
    hi = sub_00048560(o->id2E8);
    if (now >= hi)
        now = (now - lo) % (hi - lo) + lo;
    return now;
}

/* 0x000E4870: in areas 4 and 5 (or for stage 1) mark the stage started and
   play its entry animation on the player. */
void r2d_StageStart(R2dStage *o)
{
    if (g_acb_3F0A7C == 4 || g_acb_3F0A7C == 5 || o->key000 == 1) {
        o->v510 = 1;
        o->v514 = 0;
        sub_000D0200(&r2d_player, 1, r2_anim317758[o->key000].id);
    }
}

/* 0x000E51A0: pause the stage: stop its stream when streaming is idle,
   otherwise pause sound and stop the partner stream. Always returns 1. */
int r2d_StagePause(R2dStage *o)
{
    if (!g_acb_3F0A78)
        return 1;
    if (!r2d_g3F0A80) {
        sub_000E3C00(o);
        return 1;
    }
    sub_00054040();
    if (o->h2FC >= 0)
        sub_0019AB40(o->h2FC);
    return 1;
}
