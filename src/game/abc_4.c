/* Area abc, group 4: player globals, a ring queue and player states (0x000BBF40..0x000BDC20). Names inferred. */
#include "abc.h"

/* 0x000BBF40: load Jack's model list for the given costume (0..4). */
void abc_LoadJackCostume(int costume)
{
    const char *paths[5];
    int id;
    paths[0] = abc_s276D28; paths[1] = abc_s276CFC; paths[2] = abc_s276CD0;
    paths[3] = abc_s276CA4; paths[4] = abc_s276C78;
    id = costume + 0x60;
    sub_00053710(2);
    sub_000512D0(id, sub_00053820(2, sub_0004F680(id), 0, 0));
    sub_0004F700(id);
    sub_00022630(abc_p42C8E0, paths[costume]);
    sub_0004F720();
    sub_00053740();
}

/* 0x000BBFC0: store the negated heading of the rotated +X axis. */
void abc_SetHeading(const float *m)
{
    float v[4];
    v[0] = 1.0f; v[1] = 0.0f; v[2] = 0; v[3] = 0.0f;
    sub_001AD9B0(v, m, v);
    abc_player.headingF4 = -sub_00082A90(v[1], v[0]);
}

/* 0x000BC010: flag whether the vertical velocity is nonzero. */
void abc_UpdateNonzeroFlag(void)
{
    abc_player.nonzero120 = 0;
    if (abc_player.vel110[2] != 0.0f) abc_player.nonzero120 = 1;
}

/* 0x000BC110: copy a point into +0x90 with w = 1. */
void abc_SetPoint90(const float *p)
{
    float v[4];
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    abc_Vec3Copy(v, p);
    v[3] = 1.0f;
    abc_Vec3Copy(abc_player.v90, v);
}

/* 0x000BC170: copy a point into +0x54 with w = 1. */
void abc_SetPoint54(const float *p)
{
    float v[4];
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    abc_Vec3Copy(v, p);
    v[3] = 1.0f;
    abc_Vec3Copy(abc_player.v54, v);
}

/* 0x000BC5D0: clear +0xEC and +0xF0. */
void abc_ClearEC(void) { abc_player.iEC = 0; abc_player.fF0 = 0.0f; }

/* 0x000BC650: last pushed value, -1 when empty. */
int abc_QueueLast(AbcQueue *q)
{
    int i = q->tail;
    if (i == q->head) return -1;
    i--;
    if (i < 0) { i += q->cap; if (i < 0) return -1; }
    return q->buf[i];
}

/* 0x000BC670: pop the oldest value, 0 when empty. */
int abc_QueuePop(AbcQueue *q)
{
    int h = q->head, t = q->tail, n, v;
    if (h == t) return 0;
    n = h + 1;
    if (n >= q->cap) n -= q->cap;
    v = q->buf[h];
    if (n < 0) { q->head = t; q->buf[t] = 0; }
    else q->head = n;
    return v;
}

/* 0x000BC6B0: push a value; 1 when full. */
int abc_QueuePush(AbcQueue *q, int v)
{
    int t = q->tail, n = t + 1;
    if (n >= q->cap) n -= q->cap;
    if (n == q->head || n < 0) return 1;
    q->buf[t] = v;
    q->tail = n;
    return 0;
}

/* 0x000BC6F0: copy the pose of part record idx onto the model's part id. */
void abc_CopyPartPose(int id, int idx)
{
    AbcPartRec *r;
    if (!abc_partSet) return;
    r = sub_0001D2D0(abc_model, id);
    if (!r) return;
    if (sub_0001D960(&abc_partSet->recs[idx], 1)) {
        AbcPart *src = abc_partSet->recs[idx].part20;
        r->part20->poseBC = src->poseBC;
        r->part20->poseC0 = src->poseC0;
    }
}

/* 0x000BC770: allow or block player control depending on game state. */
void abc_UpdateControl(void)
{
    uint32_t *ctl = (uint32_t *)g_42C8EC;
    if (!(*ctl & 1)) {
        int m;
        if ((int32_t)abc_flags420010 >= 0 && abc_player.anim128 < 0x90 && !abc_player.busy1B8 &&
            (m = abc_player.modeD4) != 2 && m != 4 && m != 5) {
            if (abc_flags418B40 & 1) sub_001BA8F0(abc_d418A80);
            abc_flags418B40 &= ~1u;
            if (!abc_player.busy1B8) sub_000D0530(&abc_player, -1, 1);
            return;
        }
        *ctl |= 1;
        sub_001BA8F0(abc_d418A80);
        sub_000D51E0(g_42C8EC);
    }
    abc_flags418B40 |= 1;
    if (!abc_player.busy1B8) sub_000D0530(&abc_player, 1, 1);
}

/* 0x000BCA50: set +0x138. */
void abc_Set138(int v) { abc_player.i138 = v; }

/* 0x000BCB90: start mode 2 if idle, then refresh the model. */
void abc_StatsStartRefresh(void)
{
    if (!abc_player.busy1B8) { abc_player.mode1BC = 2; sub_000D24A0(&abc_player); }
    sub_0001D7A0(abc_model);
}

/* 0x000BCBC0: switch mode, then refresh the model. */
void abc_SwitchRefresh(int a)
{
    sub_000BCA60(a);
    sub_0001D7A0(abc_model);
}

/* 0x000BCC90: update the model. */
void abc_PlayerUpdate(void) { sub_0001D720(abc_model); }

/* 0x000BCF30: per-frame player update: animation change, control, motion. */
void abc_PlayerFrame(void)
{
    sub_000D2F60(&abc_player);
    sub_000D2D90(&abc_player);
    abc_player.timer130 += abc_frameUnits;
    if (abc_player.anim128 != (uint32_t)abc_player.anim12C) {
        sub_000832D0(abc_model->anim30, abc_player.anim12C);
        abc_player.anim128 = abc_player.anim12C;
        abc_player.timer130 = 0.0f;
    }
    sub_000BC770();
    sub_000D9A30(abc_model->sub60, abc_player.f108);
}

/* 0x000BD4A0: reset the sequencer, then start it in mode 1. */
void abc_SeqStart(AbcObjD4 *o, int mode, float t)
{
    sub_000193C0();
    if (o->modeD4 == 1 && mode >= 0) sub_00019370(mode, t);
}

/* 0x000BD870: leave the state: report health, clear flag bit 1. */
void abc_StateLeave(AbcPlayer *p)
{
    abc_SetState(p, 1);
    sub_001BA8F0(abc_d418A80);
    sub_00026280(p->maxHealth, p->health);
    sub_000CA580(p);
    p->flags150 &= ~2u;
}

/* 0x000BDBB0: first step of a state: set animation 5 and timings. */
void abc_StateEnter5(AbcPlayer *p)
{
    if (p->stepE0) return;
    p->flags150 &= 0x83FFF4FE;
    p->f10C = 10.0f;
    p->anim12C = 5;
    p->vel110[2] = 0.5f;
    sub_000CA600(p);
    sub_000D5620(0);
    p->stepE0++;
}

/* 0x000BDC20: state with animation 0x50 that ends after 30 time units. */
void abc_StateWait50(AbcPlayer *p)
{
    switch (p->stepE0) {
    case 0:
        p->flags150 |= 0x2C000000;
        p->anim12C = 0x50;
        p->timeE8 = 0.0f;
        p->stepE0 = 1;
        break;
    case 1:
        if (p->timeE8 > 30.0f) abc_SetState(p, 1);
        break;
    }
}

/* 0x000BD4D0: switch to another state, resetting the step, timers and motion. */
void abc_SetState(AbcPlayer *p, int state)
{
    float v[4];
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    if (p->stateD8 == state) return;
    p->prevStateDC = p->stateD8;
    p->stateD8 = state;
    p->stepE0 = 0;
    p->fE4 = 0.0f;
    p->timeE8 = 0.0f;
    p->f134 = 0.0f;
    abc_Vec3Copy(p->vel110, v);
    abc_Vec3Copy(p->pos10, v);
    sub_000CEE40(0, 0);
}

/* 0x000BDAE0: state with animation 3, then 4 or 12 while active. */
void abc_StateActive(AbcPlayer *p)
{
    if (p->stepE0 != 0) {
        if (p->stepE0 == 8) {
            if (abc_IsActive(p) < 0) p->stepE0 = 0;
            p->anim12C = (p->iEC & 0x43) ? 12 : 4;
        }
        return;
    }
    p->flags150 &= 0x83FFF4FE;
    p->f10C = 10.0f;
    p->anim12C = 3;
    p->vel110[2] = 0.2f;
    sub_000CA600(p);
    sub_000D5620(0);
    if (abc_IsActive(p) > 0) {
        p->stepE0 = 8;
        p->anim12C = (p->iEC & 0x43) ? 12 : 4;
        return;
    }
    p->stepE0++;
}

/* 0x000BDC90: bounce with animation 0x51, then state 3 when the timer ends. */
void abc_StateBounce(AbcPlayer *p)
{
    switch (p->stepE0) {
    case 0:
        p->flags150 |= 0x2C000000;
        p->anim12C = 0x51;
        p->vel110[2] *= -1.0f;
        p->stepE0 = 1;
        break;
    case 1:
        p->vel110[2] *= -1.0f;
        if (abc_TimerDone(p)) abc_SetState(p, 3);
        break;
    }
}

/* 0x000BDD20: stand still with animation 10, then state 1. */
void abc_StateStill10(AbcPlayer *p)
{
    p->vel110[2] = 0.0f; p->vel110[1] = 0.0f; p->vel110[0] = 0.0f;
    switch (p->stepE0) {
    case 0:
        p->flags150 = (p->flags150 & ~1u) | 0x28000000;
        p->anim12C = 10;
        p->stepE0 = 1;
        break;
    case 1:
        if (abc_TimerDone(p)) abc_SetState(p, 1);
        break;
    }
}

/* 0x000BDDA0: stand still with animation 9, then state 1. */
void abc_StateStill9(AbcPlayer *p)
{
    p->vel110[2] = 0.0f; p->vel110[1] = 0.0f; p->vel110[0] = 0.0f;
    switch (p->stepE0) {
    case 0:
        p->flags150 = (p->flags150 & ~1u) | 0x28000000;
        p->anim12C = 9;
        p->stepE0 = 1;
        break;
    case 1:
        if (abc_TimerDone(p)) abc_SetState(p, 1);
        break;
    }
}

/* 0x000BDE20: stand still with animation 10, then state 2. */
void abc_StateStill10To2(AbcPlayer *p)
{
    p->vel110[2] = 0.0f; p->vel110[1] = 0.0f; p->vel110[0] = 0.0f;
    switch (p->stepE0) {
    case 0:
        p->flags150 = (p->flags150 & ~1u) | 0x28000000;
        p->anim12C = 10;
        p->stepE0 = 1;
        break;
    case 1:
        if (abc_TimerDone(p)) abc_SetState(p, 2);
        break;
    }
}
