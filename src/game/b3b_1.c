/* Area b3b, group 1: enemy predicates and helpers 0x00146xxx-0x00147xxx. Names inferred. */
#include "b3b.h"

/* 0x00146090: size of this enemy type's component. */
int b3b_Size146090(void) { return 0x1EC; }

/* 0x00146750: run the per-frame update and clear work flag 0x80000. */
void b3b_Update146750(B3bOwner *o, B3bEnemy *e)
{
    B3bWork *w = e->work;
    sub_0015A3D0(o, e, w);
    w->flags50 &= ~0x80000u;
}

/* 0x00146780: set owner flags 0xD. */
void b3b_SetFlags146780(B3bOwner *o) { o->flags10 |= 0xD; }

/* 0x00146790: call 0x000ED780 when work flag 0x20 is set. */
void b3b_Cond146790(B3bOwner *o, B3bEnemy *e)
{
    if (e->work->flags50 & 0x20) sub_000ED780(o);
}

/* 0x001473E0: predicate: side bit equals the requested flag. */
int b3b_PredSide1473E0(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    if (c->a8 == 0) return (uint8_t)~e->b20 & 1;
    return e->b20 & 1;
}

/* 0x00147410: predicate: work float +0x68 within [lo, hi]. */
int b3b_PredRange147410(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    B3bWork *w = e->work;
    if (w->f68 >= c->lo && c->hi >= w->f68) return 1;
    return 0;
}

/* 0x00147440: predicate: random chance (rand % modulus < threshold). */
int b3b_PredChance147440(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    if ((unsigned)sub_001C7EE1() % c->aC < c->a8) return 1;
    return 0;
}

/* 0x00147460: predicate: active slot count within [low, high]. */
int b3b_PredCount147460(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    unsigned n = sub_0018B6B0();
    if (n < c->a8) return 0;
    if (n > c->aC) return 0;
    return 1;
}

/* 0x00147480: predicate: work float +0x60 within [lo, hi]. */
int b3b_PredRange147480(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    B3bWork *w = e->work;
    if (w->f60 >= c->lo && c->hi >= w->f60) return 1;
    return 0;
}

/* 0x001474B0: predicate: global float 0x003F7504 is not positive. */
int b3b_PredGlobal1474B0(void)
{
    if (0.0f >= b10_f3F7504) return 1;
    return 0;
}

/* 0x00147540: predicate: work flag bit 9. */
int b3b_PredFlag147540(B3bOwner *o, B3bEnemy *e) { return (e->work->flags50 >> 9) & 1; }

/* 0x00147560: predicate: (work flags & mask) == value. */
int b3b_PredMask147560(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    return (e->work->flags50 & c->a8) == c->aC;
}
