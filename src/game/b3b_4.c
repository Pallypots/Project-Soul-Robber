/* Area b3b, group 4: enemy helpers 0x00135xxx-0x0013Dxxx. Names inferred. */
#include "b3b.h"

/* 0x001358D0: predicate: (work flags +8 & mask) nonzero equals the requested flag. */
int b3b_PredMask1358D0(B3bOwner *o, B3bEnemy *e, B3bCond *c)
{
    uint32_t v = e->work->flags08;
    if (c->aC == 0) return (v & c->a8) == 0;
    return (v & c->a8) != 0;
}

/* 0x0013BD80: apply table 0x0031CE1C, then call 0x000ED780 once the enemy timer passes 1.0. */
void b3b_Step13BD80(B3bOwner *o, B3bEnemy *e)
{
    sub_0013A380(o, 2, b3b_tbl31CE1C);
    if (e->f5C > 1.0f) sub_000ED780(o);
}

/* 0x0013D910: look up component kind 4; set *out; return its resource +0x34 when allowed. */
void *b3b_Lookup13D910(void *obj, int skip, int *out)
{
    B3bEnemy *c = (B3bEnemy *)sub_0001D960(obj, 4);
    B3bWork *w = c->work;
    if (out) *out = 1;
    if (skip == 0 && w->res34[0] != 0) return w->res34[0];
    return 0;
}

/* 0x0013D950: forward an argument to each of the three work resources. */
void b3b_Each13D950(B3bOwner *o, B3bEnemy *e, int arg)
{
    B3bWork *w = e->work;
    int i;
    for (i = 0; i < 3; i++)
        if (w->res34[i]) sub_0018E700(w->res34[i], arg);
}
