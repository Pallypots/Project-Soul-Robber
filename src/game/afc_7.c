/* Area afc, groups 7: type-3 and type-4 singletons 0x000FE270-0x000FFFF0. Names inferred. */
#include "afc.h"

/* 0x000FE270: allocate the type-3 actor singleton. */
void afc_MinionCreate(void)
{
    void *p = sub_00053AB0(sub_000F30E0(3) * 0x208, 0, 0x1B7);
    afc_minion = (AfcSingleton *)p;
    afc_minionState = (AfcActor *)p;
    sub_000F69E0(p);
}

/* 0x000FE2B0: free the type-3 actor singleton. */
void afc_MinionDestroy(void)
{
    afc_minionState = 0;
    sub_00053880(afc_minion);
    afc_minion = 0;
}

/* 0x000FE2E0: change the type-3 actor's state and clear +0xBC. */
void afc_MinionSetState(int state)
{
    AfcPart *p = afc_minion->part8C;
    AfcActor *a;
    if (p == 0) for (;;) ;
    a = afc_minionState;
    if (a == 0) for (;;) ;
    sub_000F3D10(p, a, state);
    afc_minion->wBC = 0;
}

/* 0x000FE330: set the same animation on both type-3 actor parts. */
void afc_MinionSetAnims(int anim)
{
    AfcPart *p;
    if (afc_minion == 0) for (;;) ;
    p = afc_minion->part8C;
    if (p == 0) for (;;) ;
    sub_000832D0(p->node, anim);
    sub_000832D0(afc_minion->part90->node, anim);
}

/* 0x000FE3D0: type-3 actor singleton (must exist). */
AfcSingleton *afc_GetMinion(void)
{
    if (afc_minion == 0) for (;;) ;
    return afc_minion;
}

/* 0x000FE630: copy a message word into the type-3 actor's +0xA8 when the helper is armed. */
void afc_MinionTakeMsg(AfcMsg *m)
{
    if (afc_GetHelper()->vE8 != 0)
        afc_minion->wA8 = m->w0C;
}

/* 0x000FE990: play animation 0x21 on both parts and clear +0x9C. */
void afc_MinionAnim21(void)
{
    AfcSingleton *m = afc_minion;
    AfcPart *p;
    if (m == 0) for (;;) ;
    p = m->part8C;
    if (p == 0) for (;;) ;
    sub_000832D0(p->node, 0x21);
    sub_000832D0(afc_minion->part90->node, 0x21);
    m->v9C = 0;
}

/* 0x000FEA70: play animation 0x22 on both parts and clear +0x1B0. */
void afc_MinionAnim22(void)
{
    AfcSingleton *m = afc_minion;
    AfcPart *p;
    if (m == 0) for (;;) ;
    p = m->part8C;
    if (p == 0) for (;;) ;
    sub_000832D0(p->node, 0x22);
    sub_000832D0(afc_minion->part90->node, 0x22);
    m->v1B0 = 0;
}

/* 0x000FF420: clear the type-3 actor's +0x9C, +0xA0 and +0x1BC. */
void afc_MinionClear(void)
{
    AfcSingleton *m = afc_minion;
    m->v9C = 0;
    m->fA0 = 0.0f;
    m->w1BC = 0;
}

/* 0x000FFE20: when the state has run longer than the minion's +0x1B8, go to state 0x29. */
void afc_MinionTimeout(void *ctx, AfcActor *o)
{
    if (o->stateTime > afc_minion->f1B8)
        sub_000F3D10((AfcPart *)ctx, o, 0x29);
}

/* 0x000FFFB0: allocate the type-4 actor singleton. */
void afc_CtlCreate(void)
{
    void *p = sub_00053AB0(sub_000F30E0(4) * 0x208, 0, 0x13C);
    b10_ctl = (AfcSingleton *)p;
    b10_res3F612C = (AfcActor *)p;
    sub_000F69E0(p);
}

/* 0x000FFFF0: free the type-4 actor singleton. */
void afc_CtlDestroy(void)
{
    b10_res3F612C = 0;
    sub_00053880(b10_ctl);
    b10_ctl = 0;
}
