/* Area b3b, group 2: enemy predicates and helpers 0x00155xxx-0x00156xxx. Names inferred. */
#include "b3b.h"

/* 0x001550D0: size of this enemy type's component. */
int b3b_Size1550D0(void) { return 0x1E8; }

/* 0x00155550: when work flag 0x20 is set, call 0x00185540 and 0x000ED780. */
void b3b_Cond155550(B3bOwner *o, B3bEnemy *e)
{
    if (e->work->flags40 & 0x20) {
        sub_00185540(o);
        sub_000ED780(o);
    }
}

/* 0x00155AE0: predicate: owner's handle at +0x30 reports nonzero. */
int b3b_PredHandle155AE0(B3bOwner *o) { return sub_000833E0(o->handle30) != 0; }

/* 0x00155BE0: predicate: work flag bit 10. */
int b3b_PredFlag155BE0(B3bOwner *o, B3bEnemy *e) { return (e->work->flags40 >> 10) & 1; }

/* 0x00155C00: predicate: work flag bit 11 clear. */
int b3b_PredNoFlag155C00(B3bOwner *o, B3bEnemy *e) { return ~(e->work->flags40 >> 11) & 1; }

/* 0x00155C70: predicate: work flag bit 12 equals the requested flag. */
int b3b_PredFlag155C70(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    uint32_t v = e->work->flags40 >> 12;
    if (c->a8 == 0) v = ~v;
    return v & 1;
}

/* 0x00155CA0: predicate: (work flags & mask) == value. */
int b3b_PredMask155CA0(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    return (e->work->flags40 & c->a8) == c->aC;
}

/* 0x00155CF0: predicate: work float +0x58 is not positive. */
int b3b_PredF58155CF0(B3bOwner *o, B3bEnemy *e)
{
    if (0.0f >= e->work->f58) return 1;
    return 0;
}

/* 0x001561D0: store two floats at +4/+8. */
void b3b_SetPair1561D0(B3bPair *p, float x, float y)
{
    p->x = x;
    p->y = y;
}

/* 0x00155580: two-step start: wait for the owner's handle, then run 0x00185540 and 0x000ED780. */
void b3b_Start155580(B3bOwner *o, B3bEnemy *e)
{
    switch (e->counter58) {
    case 0:
        if (!sub_000833E0(o->handle30)) return;
        e->counter58++;
        /* fall through */
    case 1:
        sub_00185540(o);
        sub_000ED780(o);
        break;
    }
}

/* 0x001555C0: if 0x00145940 accepts the work pair and range, apply 0x001459D0. */
void b3b_Apply1555C0(B3bOwner *o, B3bEnemy *e, B3bArgs *a)
{
    B3bWork *w = e->work;
    if (sub_00145940(o, w->i64, w->i6C, a->p10, a->p14))
        sub_001459D0(o, w->i64, w->i6C, a->p18);
}

/* 0x001558B0: count the node timer down; when it runs out clear owner flag 4 and advance. */
void b3b_Timer1558B0(B3bOwner *o, B3bEnemy *e, B3bCond *n)
{
    n->lo -= a50_frameSeconds;
    if (n->lo > 0.0f) {
        o->flags10 |= 4;
        return;
    }
    o->flags10 &= ~4u;
    sub_00113370(e, n);
}

/* 0x00155AB0: predicate: work float +0x54 within [lo, hi]. */
int b3b_PredRange155AB0(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    B3bWork *w = e->work;
    if (w->f54 >= c->lo && c->hi >= w->f54) return 1;
    return 0;
}

/* 0x00155B00: predicate: outside modes 2 and 0x1F, value from 0x00185420 within [low, high]. */
int b3b_PredCount155B00(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    unsigned n;
    if (b3b_mode42CAFC == 2 || b3b_mode42CAFC == 0x1F) return 0;
    n = sub_00185420(o);
    if (n < c->a8) return 0;
    if (n > c->aC) return 0;
    return 1;
}

/* 0x00155B40: predicate: work float +0x4C within [lo, hi]. */
int b3b_PredRange155B40(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    B3bWork *w = e->work;
    if (w->f4C >= c->lo && c->hi >= w->f4C) return 1;
    return 0;
}

/* 0x00155CC0: predicate: player state 8 equals the requested flag. */
int b3b_PredPlayerState155CC0(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    int s = PlayerObj_GetState((PlayerObj *)&g_stats);
    if (c->a8 == 0) return s != 8;
    return s == 8;
}
