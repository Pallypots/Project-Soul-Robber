/* Area b1b, group 3: enemy reaction handlers 0x0011A500-0x0011DBD0. Names inferred. */
#include "b1b.h"

/* 0x0011A500: enter state 3, set flag 0x10 and arm node 3 with +/-10 degrees. */
void b1b_FoeEnter3(void *o, B1bFoe *e)
{
    B1bNode *n;
    sub_00113090(o, e, 3);
    e->flags4C |= 0x10;
    n = b1b_NodeRenew((B1bEnemy *)e, 3);
    n->f18 = 0.17453294f;
    n->f1C = -0.17453294f;
}

/* 0x0011A550: enter state 4, clear flag 0x10 and add 50 (max 255) to the info value. */
void b1b_FoeEnter4(void *o, B1bFoe *e)
{
    sub_00113090(o, e, 4);
    e->flags4C &= ~0x10u;
    b10_AddClampF(&e->info->f14, 50.0f, 255.0f);
}

/* 0x0011A9D0: pick a random delay of 0..8 frames and flag the owner. */
void b1b_FoeRandDelay(B1bOwn *o, B1bFoe *e)
{
    int r = sub_001C7EE1() % 9;
    e->f74 = (float)r / a50_frameUnits * a50_frameSeconds;
    o->flags10 |= 4;
}

/* 0x0011ABB0: enter state 0x10 and set info flag 1. */
void b1b_FoeEnter10(void *o, B1bFoe *e)
{
    sub_00113090(o, e, 0x10);
    e->info->flags04 |= 1;
}

/* 0x0011ABE0: random delay; consume the info top-bit request into +0x58. */
void b1b_FoeRandDelay2(void *o, B1bFoe *e)
{
    B1bEInfo *i = e->info;
    int r = sub_001C7EE1() % 9;
    e->f74 = (float)r / a50_frameUnits * a50_frameSeconds;
    if ((int32_t)i->flags04 < 0) {
        e->i58 = 1;
        i->flags04 &= 0x7FFFFFFF;
    }
}

/* 0x0011AFE0: in states 5/6 with flag 0x10000, switch to state 4 and release a node. */
void b1b_FoeRecover(void *o, B1bFoe *e, void *node)
{
    if ((e->b22 & 1) && (e->state == 5 || e->state == 6)) {
        sub_00113040(o, e, 4);
        sub_00113370((B1bEnemy *)e, (B1bNode *)node);
    }
}

/* 0x0011DBD0: refuse sides 3/4 when the opposite side is present, else run 0x00143760. */
int b1b_SideRequest(B1bReq *r, void *b, void *c)
{
    int other;
    switch (r->side) {
    case 3: other = 4; break;
    case 4: other = 3; break;
    default: goto run;
    }
    if (sub_000EDBE0(2, other) != 0)
        return 0;
run:
    return sub_00143760(r, b, c);
}
