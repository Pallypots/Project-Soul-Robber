/* Area b1b, group 5: enemy reaction states 0x0011A370-0x0011ACC0. Names inferred. */
#include "b1b.h"

/* 0x0011A370: enter state 5 for 25 frames and stop the attached effect. */
void b1b_FoeStun(void *o, B1bFoe *e)
{
    sub_00139FA0(o, e, 5);
    e->f74 = 25.0f / a50_frameUnits * a50_frameSeconds;
    if (e->info->p34 != 0) {
        sub_00033560(e->info->p34);
        e->info->p34 = 0;
    }
}

/* 0x0011A4A0: guard reaction: play side animation, or drop to state 7 when unguarded. */
void b1b_FoeGuard(void *o, B1bFoe *e)
{
    int side = e->b22 & 1;
    uint8_t f = (uint8_t)e->info->flags04;
    if (side) {
        if (!(f & 8))
            e->i58 = 1;
    } else if (!(f & 8)) {
        e->f74 = 0.0f;
        sub_00113040(o, e, 7);
        return;
    }
    e->flags4C |= 0x10;
    sub_00113090(o, e, side);
}

/* 0x0011A6F0: hit reaction 0x23 (drain 20, codes 0xC3/0xC4, mode 3). */
void b1b_FoeHit23(void *o, B1bFoe *e)
{
    B1bNode *n;
    e->flags4C &= ~0x10u;
    b10_SubClampF(&e->info->f14, 20.0f, 0.0f);
    sub_00113090(o, e, 0x23);
    b1b_NodeRenew((B1bEnemy *)e, 3);
    n = b1b_NodeRenew((B1bEnemy *)e, 2);
    n->i10 = 0;
    n->i14 = 0x30002;
    n->i18 = 0xC400C3;
    n->i1C = 3;
}

/* 0x0011A760: hit reaction 0x24 (drain 20, codes 0xC3/0xC4, mode 2). */
void b1b_FoeHit24(void *o, B1bFoe *e)
{
    B1bNode *n;
    e->flags4C &= ~0x10u;
    b10_SubClampF(&e->info->f14, 20.0f, 0.0f);
    sub_00113090(o, e, 0x24);
    b1b_NodeRenew((B1bEnemy *)e, 3);
    n = b1b_NodeRenew((B1bEnemy *)e, 2);
    n->i10 = 1;
    n->i14 = 0x30002;
    n->i18 = 0xC400C3;
    n->i1C = 2;
}

/* 0x0011A7D0: side-dependent reaction 0x28/0x29 with code 0xC4. */
void b1b_FoeHitSide(void *o, B1bFoe *e)
{
    B1bNode *n;
    e->flags4C &= ~0x10u;
    sub_00113090(o, e, (e->b22 & 1) + 0x28);
    n = b1b_NodeRenew((B1bEnemy *)e, 2);
    n->i10 = (e->b20 & 1) + 3;
    n->i14 = 3;
    n->i18 = 0xC4;
}

/* 0x0011A820: hit reaction 0x27 (drain 20, code 0xC3). */
void b1b_FoeHit27(void *o, B1bFoe *e)
{
    B1bNode *n;
    e->flags4C &= ~0x10u;
    b10_SubClampF(&e->info->f14, 20.0f, 0.0f);
    sub_00113090(o, e, 0x27);
    n = b1b_NodeRenew((B1bEnemy *)e, 2);
    n->i10 = 2;
    n->i14 = 2;
    n->i18 = 0xC3;
}

/* 0x0011A880: heavy hit 0x15 (drain 200, flag owner, code 0xC4). */
void b1b_FoeHeavyHit(B1bOwn *o, B1bFoe *e)
{
    B1bEInfo *i = e->info;
    B1bNode *n;
    o->flags10 |= 6;
    e->flags4C &= ~0x10u;
    b10_SubClampF(&i->f14, 200.0f, 0.0f);
    i->i24 = 0;
    sub_00113090(o, e, 0x15);
    n = b1b_NodeRenew((B1bEnemy *)e, 2);
    n->i10 = 5;
    n->i14 = 3;
    n->i18 = 0xC4;
}

/* 0x0011A8F0: reaction 0x25 draining a random 30..70. */
void b1b_FoeRandDrain(void *o, B1bFoe *e)
{
    int r;
    e->flags4C &= ~0x10u;
    r = sub_001C7EE1() % 4001;
    b10_SubClampF(&e->info->f14, (float)r * 0.01f + 30.0f, 0.0f);
    sub_00113090(o, e, 0x25);
}

/* 0x0011ACC0: death: mark parts, fade the attachment and stop the effect. */
void b1b_FoeDie(void *o, B1bFoe *e)
{
    B1bEInfo *i = e->info;
    b1b_EnemyMarkParts((B1bOwner *)o, (B1bEnemy *)e);
    if (i->p20 != 0)
        sub_000EE660(i->p20, 2.0f);
    if (i->p34 != 0) {
        sub_00033560(i->p34);
        i->p34 = 0;
    }
}
