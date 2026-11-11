/* Area b13, group 3: enemy state handlers and helpers 0x0013Exxx-0x00145xxx. Names inferred. */
#include "b13.h"

/* 0x0013EFB0: animation 0x24 and set behaviour resource +0x34 to 1.0. */
void b13_State13EFB0(B13Owner *o, B13Enemy *e)
{
    e->flags4C &= ~0x30u;
    o->flags10 &= ~0x20u;
    sub_00113090(o, e, 0x24);
    sub_0018E6C0(e->behav->res34, 1.0f);
}

/* 0x0013F290: once the model is ready, animation 0x29. */
void b13_State13F290(B13Owner *o, B13Enemy *e)
{
    if (sub_000833E0(o->model)) sub_00113040(o, e, 0x29);
}

/* 0x0013F990: if 0x0013A670 allows, animation 0x1E. */
void b13_State13F990(B13Owner *o, B13Enemy *e)
{
    if (sub_0013A670(o, e)) sub_00113040(o, e, 0x1E);
}

/* 0x0013FF00: once the model is ready, clear +0x74 and animation 0xC. */
void b13_State13FF00(B13Owner *o, B13Enemy *e)
{
    if (sub_000833E0(o->model)) {
        e->f74 = 0.0f;
        sub_00113040(o, e, 0xC);
    }
}

/* 0x001401C0: count objects of kind 5 for which 0x0018E680 is true. */
int b13_CountKind5(void)
{
    int n = 0;
    void *p;
    for (p = sub_000EDC20(5, 0); p != 0; p = sub_000EDC20(-1, -1))
        if (sub_0018E680(p)) n++;
    return n;
}

/* 0x001421B0: size of this enemy type's component. */
int b13_Size1421B0(void) { return 0x24; }

/* 0x00142480: pass arg to behaviour resource +0x20 if present. */
void b13_Res142480(B13Owner *o, B13Enemy *e, int arg)
{
    void *r = e->behav->res20;
    if (r) sub_00189DE0(r, arg);
}

/* 0x00142810: mirrored animation 0/1, flag 0x10. */
void b13_State142810(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, e->side22 & 1);
    e->flags4C |= 0x10;
}

/* 0x00142C30: mirrored animation 0x4A/0x4B, clear flag 8. */
void b13_State142C30(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, (e->side22 & 1) + 0x4A);
    e->flags4C &= ~8u;
}

/* 0x00142C60: mirrored animation 0x40/0x41. */
void b13_State142C60(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, (e->side22 & 1) + 0x40);
}

/* 0x00143480: if 0x0013A7B0 allows and counter is 0, set it to 999. */
void b13_State143480(B13Owner *o, B13Enemy *e)
{
    if (sub_0013A7B0(o, e) && e->counter58 == 0) e->counter58 = 999;
}

/* 0x001434B0: if 0x0013A7B0 allows and counter is 2, animation 0x12. */
void b13_State1434B0(B13Owner *o, B13Enemy *e)
{
    if (sub_0013A7B0(o, e) && e->counter58 == 2) sub_00113040(o, e, 0x12);
}

/* 0x00145620: copy v into both the object's +0x60 vector and its child's +0x30. */
void b13_SetPos145620(B13Pair *a, void *v)
{
    b13_VecCopy(a->v60, v);
    b13_VecCopy(a->p20 + 0x30, v);
}

/* 0x00145800: random integer in [lo, hi]. */
int b13_RandRange(int lo, int hi)
{
    return (unsigned)(sub_001C7EE1() >> 16) % (unsigned)(hi - lo + 1) + lo;
}

/* 0x00145F40: look up record (a, b) and pass its +0x40 to 0x001ADA40. */
void b13_Lookup145F40(void *a, int b, int c)
{
    sub_001ADA40(c, sub_0001D0F0(a, b) + 0x40);
}
