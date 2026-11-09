/* Area acb, group 1: boss component accessors 0x000F3B00-0x000F40B0. Names inferred. */
#include "acb.h"

/* 0x000F3B00: set flag bits; returns new flags. */
uint32_t acb_SetFlags(AcbFlagObj *o, uint32_t bits)
{
    if (o == 0) for (;;) ;
    return o->flags |= bits;
}
/* 0x000F3B20: test flag bits. */
uint32_t acb_TestFlags(AcbFlagObj *o, uint32_t bits)
{
    if (o == 0) for (;;) ;
    return o->flags & bits;
}
/* 0x000F3B30: clear flag bits; returns new flags. */
uint32_t acb_ClearFlags(AcbFlagObj *o, uint32_t bits)
{
    if (o == 0) for (;;) ;
    return o->flags &= ~bits;
}
/* 0x000F3B50: boss component field +0x50. */
int acb_GetBoss50(void *o)
{
    if (o == 0) for (;;) ;
    return ((AcbBossComp *)sub_0001D960(o, 5))->v50;
}
/* 0x000F3B70: set boss component field +0x50. */
void acb_SetBoss50(void *o, int v)
{
    if (o == 0) for (;;) ;
    ((AcbBossComp *)sub_0001D960(o, 5))->v50 = v;
}
/* 0x000F3B90: boss component field +0x80. */
int acb_GetBoss80(void *o)
{
    if (o == 0) for (;;) ;
    return ((AcbBossComp *)sub_0001D960(o, 5))->v80;
}
/* 0x000F3BB0: set boss component +0x80 and both floats +0x84/+0x88. */
void acb_SetBoss80(void *o, int v, float f)
{
    AcbBossComp *c;
    if (o == 0) for (;;) ;
    c = (AcbBossComp *)sub_0001D960(o, 5);
    c->v80 = v;
    c->f88 = f;
    c->f84 = f;
}
/* 0x000F3C40: reset boss component +0x5C and +0x60. */
void acb_ResetBoss5C(void *o)
{
    AcbBossComp *c;
    if (o == 0) for (;;) ;
    c = (AcbBossComp *)sub_0001D960(o, 5);
    c->f5C = 0.0f;
    c->v60 = 0;
}
/* 0x000F3C70: boss float +0x5C, zeroed first when input flag 0x10000 is set. */
float acb_GetBoss5C(void *o)
{
    AcbBossComp *c;
    if (o == 0) for (;;) ;
    c = (AcbBossComp *)sub_0001D960(o, 5);
    if (sub_0019BE60(0x10000)) c->f5C = 0.0f;
    return c->f5C;
}
/* 0x000F3CB0: boss component field +0x60. */
int acb_GetBoss60(void *o)
{
    if (o == 0) for (;;) ;
    return ((AcbBossComp *)sub_0001D960(o, 5))->v60;
}
/* 0x000F3CD0: run the current state handler and advance the state timer. */
void acb_RunState(void *ctx, AcbStateObj *o)
{
    AcbStateFn fn = o->handlers[o->state];
    if (fn == 0) for (;;) ;
    fn(ctx, o);
    o->timer += a50_frameSeconds;
}
/* 0x000F3D70: mark every slot target of the group with -1. */
void acb_ClearGroupTargets(AcbGroup *g)
{
    int n, i;
    if (g == 0) return;
    n = sub_000F3140(g->kind);
    for (i = 0; i < n; i++)
        g->slots[i].target->v08 = -1;
}
/* 0x000F3F40: forget the boss manager. */
void acb_BossMgrClear(void) { g_acb_bossMgr = 0; }
/* 0x000F3F50: free the boss manager. */
void acb_BossMgrFree(void)
{
    AcbBossMgr *m = g_acb_bossMgr;
    g_acb_bossAux = 0;
    sub_00053880(m);
    g_acb_bossMgr = 0;
}
/* 0x000F3F80: boss manager (must exist). */
AcbBossMgr *acb_BossMgrGet(void)
{
    if (g_acb_bossMgr == 0) for (;;) ;
    return g_acb_bossMgr;
}
/* 0x000F3F90: forward a sub-state request to the boss sub-state handler. */
void acb_BossSubState(int arg)
{
    void *s = g_acb_bossMgr->sub8C;
    if (s == 0) for (;;) ;
    if (g_acb_bossAux == 0) for (;;) ;
    sub_000F3D10(s, g_acb_bossAux, arg);
}
/* 0x000F40B0: boss manager field +0x104. */
int acb_BossMgrGet104(void)
{
    if (g_acb_bossMgr == 0) for (;;) ;
    return g_acb_bossMgr->v104;
}
