/* Area r2c, group 3: boss manager helpers (0x000F4370..0x000F6B3A). Names inferred. */
#include "r2c.h"

/* 0x000F4370: start animation anim on the boss model; anims 0x20..0x25 also
   go to model children 0 and 1, and both sides of 0x192380 get it.
   regargs: anim=ESI. Hangs without a boss manager or model. */
void r2c_BossSetAnim(int anim)
{
    R2cBossMgr *m = g_acb_bossMgr;
    R2cModel *mdl;
    if (!m)
        for (;;) ;
    mdl = m->sub8C;
    if (!mdl)
        for (;;) ;
    if (anim >= 0x20 && anim <= 0x25) {
        sub_000832D0(sub_0001D2B0(mdl, 0)->part30, anim);
        sub_000832D0(sub_0001D2B0(mdl, 1)->part30, anim);
    }
    sub_000832D0(mdl->part30, anim);
    sub_00192380(0, anim);
    sub_00192380(1, anim);
}

/* 0x000F4610: boss defeated: mark state 2, free its effect and sound, and
   switch the stage game state to mode 2/8 (0x0E0A80, 0x0E51F0). */
void r2c_BossDefeat(void)
{
    R2cBossMgr *m = g_acb_bossMgr;
    R2cGame *g = sub_000E0770();
    m->wA8 = 2;
    if (m->h94) {
        sub_00033A70(m->h94);
        m->h94 = 0;
    }
    sub_000E0A80(g, 4, g->v000, g->v314, 0);
    g->v308 = 2;
    g->v30C = 8;
    sub_000E51F0(g);
    if (m->h124 != -1) {
        sub_00048250(m->h124);
        m->h124 = -1;
    }
}

/* 0x000F4D90: allocate and clear the boss manager and publish it in both
   global pointers. */
void r2c_BossMgrCreate(void)
{
    R2cBossMgr *m = (R2cBossMgr *)sub_00053AB0(sub_000F30E0(6) * 0x130, 0, 0x1F6);
    R2C_ZERO(m, 0x130);
    m->sub8C = 0;
    m->sub90 = 0;
    m->h94 = 0;
    m->vB8 = 0;
    m->vBC = 0;
    g_acb_bossMgr = m;
    g_acb_bossAux = m;
    m->h128 = -1;
    m->h124 = -1;
    m->h12C = -1;
}

/* 0x000F5D40: copy four words. */
void r2c_Vec4Copy(uint32_t *dst, const uint32_t *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

/* 0x000F5FB0: for actor kinds 3..5 count how many of the two matching boss
   objects have the +0xA6 flag set. */
int r2c_CountA6(const R2cKind *k)
{
    int n = 0;
    R2cBossMgr *b;
    if (!k)
        return 0;
    if (k->kind08 == 3) {
        if (sub_00100110()->wA6)
            n = 1;
        b = sub_000FBAF0();
    } else if (k->kind08 == 4) {
        if (sub_000FE3D0()->wA6)
            n = 1;
        b = sub_000FBAF0();
    } else if (k->kind08 == 5) {
        if (sub_000FE3D0()->wA6)
            n = 1;
        b = sub_00100110();
    } else {
        return n;
    }
    if (b->wA6)
        n++;
    return n;
}

/* 0x000F6030: for actor kinds 3..5 count how many of the two matching boss
   objects are in states 0x12..0x1B. */
int r2c_CountState6C(const R2cKind *k)
{
    int n = 0;
    R2cBossMgr *a, *b;
    if (!k)
        return 0;
    if (k->kind08 == 3) {
        a = sub_00100110();
        b = sub_000FBAF0();
    } else if (k->kind08 == 4) {
        a = sub_000FE3D0();
        b = sub_000FBAF0();
    } else if (k->kind08 == 5) {
        a = sub_000FE3D0();
        b = sub_00100110();
    } else {
        a = 0;
        b = 0;
    }
    if (a->v6C >= 0x12 && a->v6C <= 0x1B)
        n = 1;
    if (b->v6C >= 0x12 && b->v6C <= 0x1B)
        n++;
    return n;
}

/* 0x000F69E0: clear a boss object and set its handles to -1. */
void r2c_BossInit(R2cBoss *b)
{
    if (!b)
        return;
    R2C_ZERO(b, 0x208);
    b->sub8C = 0;
    b->sub90 = 0;
    b->v94 = 0;
    b->v98 = 0;
    b->v1A8 = 0;
    b->v1C0 = 0;
    b->v1C4 = 0;
    b->h134 = -1;
    b->h138 = -1;
    b->h13C = -1;
    b->h140 = -1;
    b->vC8 = 0;
    b->vD0 = 0;
    b->vD8 = 0;
    b->vCC = 0;
    b->vD4 = 0;
    b->vDC = 0;
    b->v12C = 0;
    b->w206 = 0;
}

/* 0x000F6AA0: clear flag 2 on every animated part of the boss model, rebuild
   it (0x0C75E0), restart animations 0 and 2 on both models and refresh the
   model handle. */
void r2c_BossModelReset(R2cBoss *b)
{
    R2cModel *m, *n;
    if (!b)
        return;
    m = b->sub8C;
    for (n = m; n; n = n->next3C) {
        if (n->part30 && n->part30->t14)
            n->part30->t14->flagsB8 &= ~2u;
    }
    sub_000C75E0(m);
    sub_000832D0(b->sub8C->part30, 0);
    sub_000832D0(b->sub90->part30, 0);
    sub_000832D0(b->sub8C->part30, 2);
    sub_000832D0(b->sub90->part30, 2);
    m->vD0 = sub_0001BC40(m);
}
