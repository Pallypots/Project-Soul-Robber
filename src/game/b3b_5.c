/* Area b3b, group 5: enemy state handlers 0x0013Exxx-0x00142xxx. Names inferred. */
#include "b3b.h"

/* 0x0013EB00: enter state 0x11 and set behaviour flag 0x800000. */
void b3b_State13EB00(B3bOwner *o, B3bEnemy *e)
{
    sub_00113090(o, e, 0x11);
    o->flags10 = (o->flags10 & ~0x20u) | 6;
    e->flags4C &= ~0x38u;
    e->work->flags04 |= 0x800000;
}

/* 0x0013EB40: arm the state timer with a random 120..200 frames. */
void b3b_Timer13EB40(B3bOwner *o, B3bEnemy *e)
{
    o->flags10 &= ~0x20u;
    e->u74.f74 = (float)(sub_001C7EE1() % 0x51 + 0x78) / a50_frameUnits * a50_frameSeconds;
}

/* 0x0013ED60: hang if a resource is still attached; else enter state 6. */
void b3b_State13ED60(B3bOwner *o, B3bEnemy *e)
{
    if (e->work->res34[0] != 0) for (;;) ;
    o->flags10 &= ~0x20u;
    e->flags4C &= ~0x30u;
    sub_00113090(o, e, 6);
}

/* 0x0013F210: when the model is ready, reset timer slot 3 and switch to state 0x28. */
void b3b_State13F210(B3bOwner *o, B3bEnemy *e)
{
    if (sub_000833E0(o->handle30)) {
        sub_00113480(e, 3);
        e->flags4C |= 0x38;
        sub_00113040(o, e, 0x28);
    }
}

/* 0x0013F250: when the model is ready, switch to state 0x12. */
void b3b_State13F250(B3bOwner *o, B3bEnemy *e)
{
    if (sub_000833E0(o->handle30)) {
        o->flags10 &= ~6u;
        e->flags4C |= 0x38;
        sub_00113040(o, e, 0x12);
    }
}

/* 0x00141FA0: switch to state 10 when check 0 of table 0x0031D0B8 passes. */
void b3b_State141FA0(B3bOwner *o, B3bEnemy *e)
{
    if (b3b_checkFns31D0B8[0](o, e, b3b_tbl2797C8)) sub_00113040(o, e, 10);
}

/* 0x00142440: look up component kind 4; set *out; return its resource +0x20 when allowed. */
void *b3b_Lookup142440(void *obj, int skip, int *out)
{
    B3bEnemy *c = (B3bEnemy *)sub_0001D960(obj, 4);
    B3bWork *w = c->work;
    if (out) *out = 1;
    if (skip == 0 && w->res20 != 0) return w->res20;
    return 0;
}

/* 0x00142670: enter state 5 and arm the timer with 25 frames. */
void b3b_State142670(B3bOwner *o, B3bEnemy *e)
{
    sub_00139FA0(o, e, 5);
    e->u74.f74 = 25.0f / a50_frameUnits * a50_frameSeconds;
}

/* 0x00142740: enter mirrored state 6/7. */
void b3b_State142740(B3bOwner *o, B3bEnemy *e)
{
    o->flagsC &= ~0x20u;
    o->flags10 |= 5;
    e->flags4C &= 0xFEFFFFF7u;
    sub_00113090(o, e, (e->side22 & 1) + 6);
}

/* 0x00142890: enter state 4 and raise the work value at +0x14 by 50 up to 255. */
void b3b_State142890(B3bOwner *o, B3bEnemy *e)
{
    B3bWork *w = e->work;
    sub_00113090(o, e, 4);
    e->flags4C &= ~0x10u;
    b10_AddClampF(&w->f14, 50.0f, 255.0f);
}

/* 0x00142D20: unless already in state 0x17, enter state 0x44. */
void b3b_State142D20(B3bOwner *o, B3bEnemy *e)
{
    if (e->state54 != 0x17) {
        sub_00113090(o, e, 0x44);
        o->flagsC &= ~0x20u;
        o->flags10 &= ~0x10u;
        e->flags4C &= ~8u;
    }
}

/* 0x00142630: object is type 2 (subtype 2 or 0x10) and its work flag 0x10 is set. */
int b3b_IsFlagged142630(B3bObj *obj)
{
    B3bEnemy *c;
    if (obj && obj->type4 == 2 && (obj->sub8 == 2 || obj->sub8 == 0x10)) {
        c = (B3bEnemy *)sub_0001D960(obj, 4);
        if (c) return (c->work->flags04 >> 4) & 1;
    }
    return 0;
}

/* 0x00142ED0: apply the variant's table, then call 0x000ED780 once the enemy timer passes 1.0. */
void b3b_Step142ED0(B3bOwner *o, B3bEnemy *e)
{
    sub_0013A380(o, 2, o->kind08 == 0x10 ? b3b_tbl31DBFC : b3b_tbl31DBD4);
    if (e->f5C > 1.0f) sub_000ED780(o);
}
