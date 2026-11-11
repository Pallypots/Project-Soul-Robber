/* Area r2e, group 1: stage director and track helpers (0x000DD880..0x000ED9D7). Names inferred. */
#include "r2e.h"

/* 0x000E45F0: reload slot idx's resource handle and switch its model to
   mode (0, 1). */
void r2e_SlotReload01(R2eStage *o, int idx)
{
    void *m;
    o->slots86C[idx].h04 = sub_0001D080(r2e_ctx->res1E8, 3, sub_000E2420(o));
    m = o->slots86C[idx].p00;
    if (m)
        sub_0001D7F0(m, 0, 1);
}

/* 0x000E4640: same with mode (1, 1). */
void r2e_SlotReload11(R2eStage *o, int idx)
{
    void *m;
    o->slots86C[idx].h04 = sub_0001D080(r2e_ctx->res1E8, 3, sub_000E2420(o));
    m = o->slots86C[idx].p00;
    if (m)
        sub_0001D7F0(m, 1, 1);
}

/* 0x000E4770: if slot idx has a model, reload its handle and switch the
   model to mode (0, 1). */
void r2e_SlotReloadIf(R2eStage *o, int idx)
{
    R2eSlot *s = &o->slots86C[idx];
    if (s->p00) {
        o->slots86C[idx].h04 = sub_0001D080(r2e_ctx->res1E8, 3, sub_000E2420(o));
        if (s->p00)
            sub_0001D7F0(s->p00, 0, 1);
    }
}

/* 0x000E47D0: same as 0x000E45F0 with mode (2, 0). */
void r2e_SlotReload20(R2eStage *o, int idx)
{
    void *m;
    o->slots86C[idx].h04 = sub_0001D080(r2e_ctx->res1E8, 3, sub_000E2420(o));
    m = o->slots86C[idx].p00;
    if (m)
        sub_0001D7F0(m, 2, 0);
}

/* 0x000E4820: same with mode (3, 0). */
void r2e_SlotReload30(R2eStage *o, int idx)
{
    void *m;
    o->slots86C[idx].h04 = sub_0001D080(r2e_ctx->res1E8, 3, sub_000E2420(o));
    m = o->slots86C[idx].p00;
    if (m)
        sub_0001D7F0(m, 3, 0);
}

/* 0x000EB820: when on, send event (3, 0) and apply key 3. */
void r2e_Key3On(int on)
{
    if (on) {
        sub_000E23F0(3, 0);
        sub_0012D600(3);
    }
}

/* 0x000EBBD0: when on, send event (3, 0) and apply key 4. */
void r2e_Key4On(int on)
{
    if (on) {
        sub_000E23F0(3, 0);
        sub_0012D600(4);
    }
}

/* 0x000EB180: start a stage colour fade from a colour record (time in
   milliseconds, RGBA bytes). */
void r2e_StageFadeRec(void *o, R2eColRec *c)
{
    if (c && o)
        r2d_StageFadeColor(o, (float)c->timeC * 0.001f, c->rgba10[0], c->rgba10[1], c->rgba10[2], c->rgba10[3]);
}

/* 0x000EB200: post cue event 4 for the director, using the cue's +0x0C
   value when flag bit 0 is set and +0x10 otherwise. */
void r2e_DirCue(R2eDir *o, R2eCue *c)
{
    if (c && o) {
        if (o->flags2F4 & 1)
            sub_000E0A80(o, 4, o->key000, o->v314, c->vC);
        else
            sub_000E0A80(o, 4, o->key000, o->v314, c->v10);
    }
}

/* 0x000E2240: copy slot idx's +0x18 value to its model, replay the slot's
   own cue and drop the pending 0x003F1B20 object. */
void r2e_SlotReplay(R2eStage *o, int idx)
{
    R2eSlot *s = &o->slots86C[idx];
    if (s->p00) {
        s->p00->f64 = s->f18;
        sub_000E1FD0(o, idx, s->v08);
        if (r2e_g3F1B20)
            sub_00189510(r2e_g3F1B20);
        r2e_g3F1B20 = 0;
    }
}

/* 0x000E2350: set slot idx's model value to +0x18 plus the lift at 0x00317D7C (24.0), play the cue at
   0x00317D80 and switch the model to mode (0, 1). */
void r2e_SlotCue(R2eStage *o, int idx)
{
    R2eSlot *s = &o->slots86C[idx];
    if (s->p00) {
        s->p00->f64 = s->f18 + r2e_cueLift317D7C;
        sub_000E1FD0(o, idx, r2e_cue317D80);
        if (s->p00)
            sub_0001D7F0(s->p00, 0, 1);
    }
}

/* 0x000E5CF0: let the background job finish, start job 0x000E5300 and
   wait for it as well; returns 1. */
int r2e_RunJobE5300(void)
{
    while (Job_IsRunning()) {
        sub_00033250();
        sub_000580D0();
    }
    sub_00058540(sub_000E5300, 0);
    while (Job_IsRunning()) {
        sub_00033250();
        sub_000580D0();
    }
    return 1;
}

/* 0x000DE530: save the player position (flag clear) or put the player
   back at the saved position and reset it to (0, 0, 0, 1). */
void r2e_PlayerSavePos(int restore)
{
    if (!restore) {
        sub_000F5D40(r2e_vec30D6A8, (uint8_t *)g_playerObj + 0x60);
        return;
    }
    r2d_PlayerPlace(r2e_player41FEC0, r2e_vec30D6A8);
    r2e_vec30D6A8[0] = 0.0f;
    r2e_vec30D6A8[1] = 0.0f;
    r2e_vec30D6A8[2] = 0.0f;
    r2e_vec30D6A8[3] = 1.0f;
}

/* 0x000EA660: clear the manager +0x40C, post event (4, 0) and, when the
   cue's hit is of kind 3, trigger it and mark the cue done. */
void r2e_MgrCueHit(R2eMgr *o, R2eCue *c)
{
    R2eHit *h;
    if (o && c) {
        o->v40C = 0;
        sub_000E8690(4, 0);
        h = sub_000E2540(o, c->vC);
        if (h && h->kind4 == 3) {
            sub_000F3BF0(h, o->v420, 2);
            sub_000E2670(o, c->vC, 1);
        }
    }
}

/* 0x000E9CB0: start a camera span: bump the sequence, centre it on
   s->center0 with half-width s->widthC / 2 and mode 0xF040. */
void r2e_CamSpan(R2eCam *c, R2eSpan *s)
{
    if (c) {
        c->seq418++;
        c->on430 = 1;
        c->center434 = s->center0;
        c->lo438 = s->center0 - s->widthC / 2;
        c->hi43C = s->widthC / 2 + s->center0;
        c->mode440 = 0xF040;
        c->v444 = -1;
        c->v448 = s->v10;
    }
}

/* 0x000E22A0: lift slot idx's model by the ramp (time / 0.8 of the lift)
   while ramping, else by the full lift and enter state 5. */
void r2e_SlotRamp(R2eStage *o, int idx)
{
    R2eSlot *s = &o->slots86C[idx];
    if (s->p00) {
        if (r2e_slotRamp317DEC > s->t20) {
            s->p00->f64 = s->t20 / r2e_slotRamp317DEC * r2e_cueLift317D7C + s->f18;
            return;
        }
        s->p00->f64 = s->f18 + r2e_cueLift317D7C;
        r2d_StageSlotSetState(o, idx, 5);
    }
}

/* 0x000E3F20: attach resource a of the stage model to target (type,
   id), or the player for type 1; 0 when either is missing. */
int r2e_StageAttach(int a, int type, int id)
{
    R2eRes130 *m = sub_0001D080(r2e_ctx->res1E8, 3, sub_000E2420(&r2e_stage3F0758));
    void *t;
    if (type == 1)
        t = g_playerObj;
    else
        t = sub_0001D080(r2e_ctx->res1E8, type, id);
    if (m && t)
        return sub_00036770(t, m->v130, a);
    return 0;
}

/* 0x000E9300: fade queue step: arm a 220 timer in state 0; in state 1 run
   the timer down and, when it expires, shift the queue by one. */
void r2e_FadeQStep(void)
{
    switch (r2e_fadeQ3F47B8.state) {
    case 0:
        r2e_fadeQ3F47B8.t = 220.0f;
        r2e_fadeQ3F47B8.state = 1;
        break;
    case 1:
        sub_000720A0(&r2e_fadeQ3F47B8.t, 0);
        if (0.0f >= r2e_fadeQ3F47B8.t) {
            r2e_fadeQ3F47B8.q[0] = r2e_fadeQ3F47B8.q[1];
            r2e_fadeQ3F47B8.q[1] = r2e_fadeQ3F47B8.q[2];
            r2e_fadeQ3F47B8.q[2] = r2e_fadeQ3F47B8.q[3];
            r2e_fadeQ3F47B8.q[3] = 0;
            r2e_fadeQ3F47B8.state = 0;
        }
        break;
    }
}

/* 0x000E9D70: close a camera span: when the span reached its count, add
   the cue amount (capped at +0x410) and post event 2; then reset it. */
void r2e_CamSpanEnd(R2eCam *c, R2eCue *cue)
{
    sub_000E8920(0, 0);
    if (c && cue) {
        if (c->v41C >= c->seq418) {
            c->v40C += cue->vC;
            sub_000E8690(2, cue->vC);
            if (c->v40C >= c->max410)
                c->v40C = c->max410;
        }
        c->v518 = 0;
        c->seq418 = 0;
        c->v41C = 0;
    }
}
