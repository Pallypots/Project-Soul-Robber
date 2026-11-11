/* Area r2c, group 5: minion and controller body helpers (0x000FE1F0..0x001011E2). Names inferred. */
#include "r2c.h"

/* 0x000FE1F0: attach model m to the helper object (same steps as
   r2c_BodyAttach, finishing with 0x0FE040). Returns m. */
R2cModel *r2c_HelperAttach(R2cModel *m)
{
    R2cBossObj *b;
    if (!m)
        for (;;) ;
    b = (R2cBossObj *)afc_helper;
    b->sub8C = m;
    sub_000F3AA0(b);
    sub_0001D8B0(b, 5);
    sub_0001D8D0(m, b);
    sub_0001D8B0(b->comp10, 0xD);
    sub_0001D8D0(m, b->comp10);
    sub_0001E9B0(aec_ctx42C8E4, m, m->v14C, 5, 0x11);
    sub_0001EBF0(m, 1);
    sub_000EE270(b->comp10);
    sub_000FE040();
    return m;
}

/* 0x000FE370: force-restart animation anim on both minion models. */
void r2c_MinionAnim(int anim)
{
    R2cBossObj *b = afc_minion;
    R2cModel *m;
    if (!b)
        for (;;) ;
    m = b->sub8C;
    if (!m)
        for (;;) ;
    m->part30->i08 = -1;
    b->sub90->part30->i08 = -1;
    m = b->sub8C;
    if (!m)
        for (;;) ;
    sub_000832D0(m->part30, anim);
    sub_000832D0(afc_minion->sub90->part30, anim);
}

/* 0x000FE5A0: minion version of r2c_BodyCheckRecover (blocked states
   0x1C..0x21, 0x22..0x29, 0x12..0x1B, 2, 3, 0x0B; cue 0x22 via 0x0FE2E0). */
void r2c_MinionCheckRecover(void)
{
    R2cBossObj *b = afc_minion;
    int st = afc_minionState->v6C;
    if (sub_000F3B50(b->sub8C) != 2)
        return;
    if (st >= 0x1C && st <= 0x21)
        return;
    if (st >= 0x22 && st <= 0x29)
        return;
    if (st >= 0x12 && st <= 0x1B)
        return;
    if (st == 2 || st == 3)
        return;
    if (!sub_000FC4D0()->vE8)
        return;
    if (b->wEC || st == 0xB)
        return;
    sub_000FE2E0(0x22);
    b->wBC = 0;
}

/* 0x000FE890: start animation 2 on both minion models and raise +0xA6. */
void r2c_MinionAnim2(void)
{
    R2cBossObj *b = afc_minion;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 2);
    sub_000832D0(afc_minion->sub90->part30, 2);
    afc_minion->wA6 = 1;
}

/* 0x000FFE50: start animation 0x2D on both minion models and clear the step. */
void r2c_MinionAnim2D(void)
{
    R2cBossObj *b = afc_minion;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0x2D);
    sub_000832D0(afc_minion->sub90->part30, 0x2D);
    b->v9C = 0;
}

/* 0x000FFF30: attach model m to the minion object (finishing with
   0x0FE660). Returns m. */
R2cModel *r2c_MinionAttach(R2cModel *m)
{
    R2cBossObj *b;
    if (!m)
        for (;;) ;
    b = afc_minion;
    b->sub8C = m;
    sub_000F3AA0(b);
    sub_0001D8B0(b, 5);
    sub_0001D8D0(m, b);
    sub_0001D8B0(b->comp10, 0xD);
    sub_0001D8D0(m, b->comp10);
    sub_0001E9B0(aec_ctx42C8E4, m, m->v14C, 5, 0x11);
    sub_0001EBF0(m, 1);
    sub_000EE270(b->comp10);
    sub_000FE660();
    return m;
}

/* 0x001000B0: force-restart animation anim on both controller models. */
void r2c_CtlAnim(int anim)
{
    R2cBossObj *b = b10_ctl;
    R2cModel *m;
    if (!b)
        for (;;) ;
    m = b->sub8C;
    if (!m)
        for (;;) ;
    m->part30->i08 = -1;
    b->sub90->part30->i08 = -1;
    m = b->sub8C;
    if (!m)
        for (;;) ;
    sub_000832D0(m->part30, anim);
    sub_000832D0(b10_ctl->sub90->part30, anim);
}

/* 0x001002E0: controller version of r2c_BodyCheckRecover (blocked states
   0x1C..0x20, 0x21..0x24, 0x25..0x27, 0x12..0x1B, 2, 3, 0x0B; cue 0x25 via
   0x100020). */
void r2c_CtlCheckRecover(void)
{
    R2cBossObj *b = b10_ctl;
    int st = b10_res3F612C->v6C;
    if (sub_000F3B50(b->sub8C) != 2)
        return;
    if (st >= 0x1C && st <= 0x20)
        return;
    if (st >= 0x21 && st <= 0x24)
        return;
    if (st >= 0x25 && st <= 0x27)
        return;
    if (st >= 0x12 && st <= 0x1B)
        return;
    if (st == 2 || st == 3)
        return;
    if (!sub_000FC4D0()->vE8)
        return;
    if (b->wEC || st == 0xB)
        return;
    sub_00100020(0x25);
    b->wBC = 0;
}

/* 0x001004F0: start animation 2 on both controller models and raise +0xA6. */
void r2c_CtlAnim2(void)
{
    R2cBossObj *b = b10_ctl;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 2);
    sub_000832D0(b10_ctl->sub90->part30, 2);
    b10_ctl->wA6 = 1;
}

/* 0x001005F0: start animation 0x21 on both controller models, clear the step. */
void r2c_CtlAnim21(void)
{
    R2cBossObj *b = b10_ctl;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0x21);
    sub_000832D0(b10_ctl->sub90->part30, 0x21);
    b10_ctl->v9C = 0;
}

/* 0x001008A0: start animation 0x22 on both controller models, clear the step. */
void r2c_CtlAnim22(void)
{
    R2cBossObj *b = b10_ctl;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0x22);
    sub_000832D0(b10_ctl->sub90->part30, 0x22);
    b->v9C = 0;
}

/* 0x00100990: start animation 0x23 on both controller models, clear the step. */
void r2c_CtlAnim23(void)
{
    R2cBossObj *b = b10_ctl;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0x23);
    sub_000832D0(b10_ctl->sub90->part30, 0x23);
    b10_ctl->v9C = 0;
}

/* 0x00100A70: start animation 0x25 on both controller models, raise +0xB0,
   clear +0x1D0 and the step. */
void r2c_CtlAnim25(void)
{
    R2cBossObj *b = b10_ctl;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0x25);
    sub_000832D0(b10_ctl->sub90->part30, 0x25);
    b->wB0 = 1;
    b->w1D0 = 0;
    b->v9C = 0;
}

/* 0x00100F10: start animation 0 on both controller models and stop the
   +0x134 sound. */
void r2c_CtlAnim0(void)
{
    R2cBossObj *b = b10_ctl;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0);
    sub_000832D0(b10_ctl->sub90->part30, 0);
    if (b->h134 != -1) {
        sub_00048250(b->h134);
        b->h134 = -1;
    }
}

/* 0x00101040: start animation 0x29 on both controller models, call
   0x184530 and restart the +0x138 effect 0x154 at +0x1EC. */
void r2c_CtlAnim29(void)
{
    R2cBossObj *b = b10_ctl;
    if (!b)
        for (;;) ;
    if (!b->sub8C)
        for (;;) ;
    sub_000832D0(b->sub8C->part30, 0x29);
    sub_000832D0(b10_ctl->sub90->part30, 0x29);
    sub_00184530();
    if (b->h138 != -1) {
        sub_00048250(b->h138);
        b->h138 = -1;
    }
    b->h138 = sub_000494D0(0x154, b->pos1EC, 1);
}

/* 0x00101170: attach model m to the controller object (finishing with
   0x1003A0). Returns m. */
R2cModel *r2c_CtlAttach(R2cModel *m)
{
    R2cBossObj *b;
    if (!m)
        for (;;) ;
    b = b10_ctl;
    b->sub8C = m;
    sub_000F3AA0(b);
    sub_0001D8B0(b, 5);
    sub_0001D8D0(m, b);
    sub_0001D8B0(b->comp10, 0xD);
    sub_0001D8D0(m, b->comp10);
    sub_0001E9B0(aec_ctx42C8E4, m, m->v14C, 5, 0x11);
    sub_0001EBF0(m, 1);
    sub_000EE270(b->comp10);
    sub_001003A0();
    return m;
}
