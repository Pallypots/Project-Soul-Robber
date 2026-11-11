/* Area r3b: condition callbacks built on the target resolver 0x00155940 (r3b_7). Names inferred.
   Every call to 0x00155940 passes EAX=cond ECX=b and a on the stack. */
#include "r3b.h"

/* 0x001472D0: 1 when the distance from a to the condition's target lies in [c->a10, c->a14]. */
int r3b_CondDist1472D0(R3bObj *a, void *b, R3bCond *c)
{
    R3bTgt *t = sub_00155940(c, b, a);
    float d;

    if (t) {
        d = sub_001B2770(a->pos60, t->u60.pos60);
        if (d >= c->a10.f && c->a14.f >= d)
            return 1;
    }
    return 0;
}

/* 0x00147330: 1 when the height difference between a and the condition's target lies in [c->a10, c->a14]. */
int r3b_CondHeight147330(R3bObj *a, void *b, R3bCond *c)
{
    R3bTgt *t = sub_00155940(c, b, a);
    float d;

    if (t) {
        d = sub_001A3F30(a->pos60[1] - t->u60.pos60[1]);
        if (d >= c->a10.f && c->a14.f >= d)
            return 1;
    }
    return 0;
}

/* 0x001473A0: animation-window test (0x00145940) of a against the condition's target handles. */
int r3b_CondAnim1473A0(R3bObj *a, void *b, R3bCond *c)
{
    R3bTgt *t = sub_00155940(c, b, a);

    if (!t)
        return 0;
    return sub_00145940(a, t->u60.h.i60, t->u60.h.i68, c->a10.i, c->a14.i);
}

/* 0x001559A0: 1 when the distance from a to the condition's target lies in [c->a10, c->a14]. */
int r3b_CondDist1559A0(R3bObj *a, void *b, R3bCond *c)
{
    R3bTgt *t = sub_00155940(c, b, a);
    float d;

    if (t) {
        d = sub_001B2770(a->pos60, t->u60.pos60);
        if (d >= c->a10.f && c->a14.f >= d)
            return 1;
    }
    return 0;
}

/* 0x00155A00: 1 when the height difference between a and the condition's target lies in [c->a10, c->a14]. */
int r3b_CondHeight155A00(R3bObj *a, void *b, R3bCond *c)
{
    R3bTgt *t = sub_00155940(c, b, a);
    float d;

    if (t) {
        d = sub_001A3F30(a->pos60[1] - t->u60.pos60[1]);
        if (d >= c->a10.f && c->a14.f >= d)
            return 1;
    }
    return 0;
}

/* 0x00155A70: animation-window test (0x00145940) of a against the condition's target handles. */
int r3b_CondAnim155A70(R3bObj *a, void *b, R3bCond *c)
{
    R3bTgt *t = sub_00155940(c, b, a);

    if (!t)
        return 0;
    return sub_00145940(a, t->u60.h.i60, t->u60.h.i68, c->a10.i, c->a14.i);
}

/* 0x00155C20: test the condition's target with 0x001460A0: c->i08 == 0 wants 0, otherwise wants 1. */
int r3b_CondState155C20(R3bObj *a, void *b, R3bCond *c)
{
    R3bTgt *t = sub_00155940(c, b, a);
    int r;

    if (!t)
        return 0;
    r = sub_001460A0(t);
    if (c->i08 == 0)
        return r == 0;
    return r == 1;
}
