/* Area afc, group 1: boss list and boss manager helpers 0x000F31A0-0x000F46E0. Names inferred. */
#include "afc.h"

/* 0x000F31A0: reset boss list globals and run subsystem resets. */
void afc_BossSystemReset(void)
{
    afc_g3F60FC = 0;
    ae0_ptr3F6100 = 0;
    afc_g3F6104 = 0;
    afc_listHead = 0;
    afc_listData = 0;
    afc_g3F6108 = 0;
    sub_00106340();
    sub_0010C830();
    sub_00108B00();
    sub_000F3F40();
    sub_000EED80();
    sub_001011F0();
    sub_00106010();
}

/* 0x000F31F0: allocate the boss list once. */
void afc_BossListAlloc(void)
{
    AfcAlloc *a;
    if (afc_listData != 0)
        return;
    a = sub_0001F210(8, 6);
    afc_listHead = a;
    afc_listData = a->data;
    sub_0001DA40(a);
    afc_g3F6108 = 0;
    afc_g3F6104 = 0;
}

/* 0x000F3230: release kind 3 and clear the boss list globals. */
void afc_BossListClear(void)
{
    sub_000ED560(3);
    afc_listHead = 0;
    afc_listData = 0;
    afc_g3F6108 = 0;
    afc_g3F6104 = 0;
}

/* 0x000F3AA0: reset a boss state block. */
void afc_BossStateReset(AfcBossState *s)
{
    s->v4C = 1;
    s->v50 = 0;
    s->f54 = 0.0f;
    s->f58 = 0.0f;
    s->f5C = 0.0f;
    s->v60 = 0;
    s->v64 = 0;
    s->f68 = 0.0f;
    s->v6C = 0;
    s->v70 = 0;
    s->v74 = 0;
    s->v78 = 0;
    s->v7C = 0;
    s->v80 = 0;
    s->f84 = 0.0f;
    s->f88 = 0.0f;
}

/* 0x000F3F00: apply a setting to every part's model. */
void afc_MultiApply(AfcMulti *m, int v)
{
    int n, i;
    if (m == 0)
        return;
    n = sub_000F3140(m->kind);
    for (i = 0; i < n; i++)
        sub_001AEDD0(m->parts[i].node->model, v);
}

/* 0x000F46A0: shut down boss subsystems and release the manager handle. */
void afc_BossShutdown(void)
{
    AfcBossMgr *m = g_acb_bossMgr;
    sub_00180A60();
    sub_00181DA0();
    sub_001827A0();
    sub_0017D6A0();
    if (m->handle128 != -1) {
        sub_00048250(m->handle128);
        m->handle128 = -1;
    }
}

/* 0x000F46E0: start the boss spin (flag 0x40, rate -4.887/fps). */
void afc_BossStartSpin(void)
{
    AfcBossMgr *m = g_acb_bossMgr;
    m->draw->flags90 |= 0x40;
    m->f118 = 0.0f;
    m->v100 = 0;
    m->f11C = -4.8869219f / aec_fps42C964;
}

/* 0x000F3BF0: add pending boss damage and flags; drop the damage while invulnerable (0x10000). */
void afc_AddPendingDamage(void *boss, float amount, uint32_t flags)
{
    AfcBossComp5 *c;
    if (boss == 0) for (;;) ;
    c = (AfcBossComp5 *)sub_0001D960(boss, 5);
    c->f5C += amount;
    c->v60 |= flags;
    if (sub_0019BE60(0x10000))
        c->f5C = 0.0f;
}

/* 0x000F3D10: change actor state, running the old state's exit and the new state's enter handler. */
void afc_ChangeState(void *ctx, AfcActor *o, int state)
{
    AfcActorStateFn fn;
    o->prevState = o->state;
    o->state = state;
    o->stateTime = 0.0f;
    if (o->exitFns != 0) {
        fn = o->exitFns[o->prevState];
        if (fn == 0) for (;;) ;
        fn(ctx, o);
    }
    fn = o->enterFns[o->state];
    if (fn == 0) for (;;) ;
    fn(ctx, o);
}

/* 0x000F3FD0: rebuild the transform matrix from scale, rotation and position. */
void afc_BuildMatrix(AfcXform *x)
{
    AfcVec4 *m = x->matrix;
    sub_001AD940(m);
    sub_001ADBA0(&m[0], &m[0], x->sclX);
    sub_001ADBA0(&m[1], &m[1], x->sclY);
    sub_001ADBA0(&m[2], &m[2], x->sclZ);
    sub_001AD8B0(m, m, x->rotX);
    sub_001AD8E0(m, m, x->rotY);
    sub_001AD910(m, m, x->rotZ);
    afc_VecCopy(&m[3], &x->pos);
}

/* 0x000F4040: register boss resources of group 4. */
void afc_RegisterBossResources(void)
{
    int i;
    sub_000ED630(4, 0x0C, 0, 0, 0);
    sub_000ED630(4, 0x1B, 0, 0, 0);
    sub_000ED630(4, 0x0B, 0, 0, 0);
    for (i = 0; i < 4; i++) {
        sub_000ED630(4, 8, 0, 0, i);
        sub_000ED630(4, 9, 0, 0, i);
        sub_000ED630(4, 10, 0, 0, i);
    }
}

/* 0x000F40C0: boss in mode 3 facing within +-pi/4 and not shielded. */
int afc_BossCanBeHit(void)
{
    AfcBossMgr *m = g_acb_bossMgr;
    if (m->v100 == 3 && !(m->f114 > 0.785398185f) && !(-0.785398185f > m->f114)
        && (m->v104 != 1 || !sub_0019BE60(0x10000)))
        return 1;
    return 0;
}
