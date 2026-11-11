/* Area r3: register-argument helpers, 0x00135E00..0x00190000 (r3_5). Names inferred. */
#include "r3.h"

/* 0x00135E60: raise the work counter +0x180 to 20 - (+0x17C) - live helper count, posting the increase.
   regargs: act=EAX. */
void r3_Raise135E60(R3Actor *act)
{
    R3Work *w = act->work278;
    int v = 20 - w->i17C - r3_Count135E10();

    if (v > w->i180) {
        sub_00025C10(2, v - w->i180);
        w->i180 = v;
        w->flags08 |= 0x300;
    }
}

/* 0x0013D380: spawn the work +0x34 effect if charges (+0x14) remain; uses one charge unless act flag 0x400.
   regargs: act=EDI obj=EBX. Returns 1 when spawned. Hangs if an effect is already present or creation fails. */
int r3_SpawnCharge13D380(R3Actor *act, R3Obj *obj)
{
    R3Work *w = act->work278;
    void *h;

    if (w->h34)
        for (;;) ;
    if (w->i14 <= 0)
        return 0;
    h = sub_000ED630(5, 0, 0, 0, 0);
    if (!h)
        for (;;) ;
    w->h34 = h;
    sub_00113190(obj, act, 1);
    sub_0018E700(w->h34, act->flags20 & 1);
    if (!(act->flags4C & 0x400))
        w->i14--;
    return 1;
}

/* 0x00140170: 1 when any other type-(2,1) object has work flag 4.bit0 set.
   regargs: self=ESI. */
int r3_OtherBusy140170(void *self)
{
    void *o;

    for (o = sub_000EDC20(2, 1); o; o = sub_000EDC20(-1, -1)) {
        if (o == self)
            continue;
        if (((R3ActorB *)sub_0001D960(o, 4))->work278->flags04 & 1)
            return 1;
    }
    return 0;
}

/* 0x00147270: run every check of condition list `table` (kinds 0..13); 1 when all pass.
   regargs: table=EAX a=EBX b=EDI. Hangs on a missing list, bad kind or missing handler. */
int r3_CheckConds147270(int table, void *a, void *b)
{
    R3Cond3 *c = r3_condLists147[table];
    R3Cond3Fn fn;
    int k;

    if (!c)
        for (;;) ;
    for (; c->active; c++) {
        k = c->kind;
        if (k < 0 || k >= 14)
            for (;;) ;
        fn = r3_condFns147[k];
        if (!fn)
            for (;;) ;
        if (!fn(a, b, c))
            return 0;
    }
    return 1;
}

/* 0x00186160: run every check of condition list `table` (kinds 0..9); 1 when all pass.
   regargs: table=EAX a=EBX b=EDI. Hangs on a missing list, bad kind or missing handler. */
int r3_CheckConds186160(int table, void *a, void *b)
{
    R3Cond3 *c = r3_condLists186[table];
    R3Cond3Fn fn;
    int k;

    if (!c)
        for (;;) ;
    for (; c->active; c++) {
        k = c->kind;
        if (k < 0 || k >= 10)
            for (;;) ;
        fn = r3_condFns186[k];
        if (!fn)
            for (;;) ;
        if (!fn(a, b, c))
            return 0;
    }
    return 1;
}

/* 0x00167D90: when the shared timer has run out, play effect 0x199 at obj and restart the timer at 30 frames.
   regargs: obj=EAX. */
void r3_TimedEffect167D90(R3Obj *obj)
{
    if (r3_timer3F8410 < 0.0f) {
        sub_00049700(0x199, 0x80, 0x80, 0x80, obj->pos60, 1, 80.0f, 0);
        r3_timer3F8410 = 30.0f / r3_frameUnits * r3_frameDelta;
    }
}

/* 0x0018CB10: add angle a to the yaw at +0x54 and rotate the vector at +0x80 by it.
   regargs: o=ESI a=stack. */
void r3_Rotate18CB10(R3Spin *o, float a)
{
    float m[16];

    o->rot50[1] += a;
    sub_001AD940(m);
    sub_001AD8E0(m, m, a);
    sub_001AD9B0(o->v80, m, o->v80);
}
