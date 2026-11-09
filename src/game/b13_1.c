/* Area b13, group 1: enemy state handlers 0x00135xxx-0x0013Bxxx. Names inferred. */
#include "b13.h"

/* 0x00135480: size of this enemy type's component. */
int b13_Size135480(void) { return 0x188; }

/* 0x00135490: release sound and effect handles; returns 1. */
int b13_Release135490(B13Owner *o, B13Enemy *e)
{
    if (e->sound6C != -1) { sub_00048250(e->sound6C); e->sound6C = -1; }
    if (e->effect70 != 0) { sub_00033A70(e->effect70); e->effect70 = 0; }
    return 1;
}

/* 0x001354D0: target the player unless behaviour flag 2 is set. */
void b13_TargetPlayer(B13Owner *o, B13Enemy *e)
{
    if (!(e->behav->flags8 & 2)) {
        e->target = g_playerObj;
        e->hasTarget = 1;
    }
}

/* 0x00137C20: size of this enemy type's component. */
int b13_Size137C20(void) { return 0x28; }

/* 0x00137C30: release sound (if valid) and effect handles; returns 1. */
int b13_Release137C30(B13Owner *o, B13Enemy *e)
{
    if (e->sound6C >= 0) { sub_00048250(e->sound6C); e->sound6C = -1; }
    if (e->effect70 != 0) { sub_00033A70(e->effect70); e->effect70 = 0; }
    return 1;
}

/* 0x00138040: enter state with animation 0x63. */
void b13_State138040(B13Owner *o, B13Enemy *e)
{
    o->flags10 |= 6;
    o->flagsC &= ~0x20u;
    e->flags4C = (e->flags4C & ~0x70u) | 8;
    sub_00113090(o, e, 0x63);
}

/* 0x00138080: enter state with animation 0x25 and timer 5/4. */
void b13_State138080(B13Owner *o, B13Enemy *e)
{
    B13Timer *t;
    o->flags10 |= 6;
    o->flagsC &= ~0x20u;
    e->flags4C = (e->flags4C & ~0x70u) | 8;
    sub_00113090(o, e, 0x25);
    t = sub_00113430(e, 2);
    t->a = 5;
    t->b = 4;
}

/* 0x001380D0: enter state with animation 0x1E and stop the model. */
void b13_State1380D0(B13Owner *o, B13Enemy *e)
{
    sub_0001D700(o);
    o->flags10 |= 5;
    e->flags4C &= ~0x78u;
    sub_00113090(o, e, 0x1E);
    sub_001AEDD0(o->model->handle14, 0);
}

/* 0x00138110: mirrored animation 0/1, flags 0x30. */
void b13_State138110(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, e->side22 & 1);
    e->flags4C |= 0x30;
}

/* 0x001381E0: forward to 0x00113190 with 1. */
int b13_State1381E0(B13Owner *o, B13Enemy *e) { return sub_00113190(o, e, 1); }

/* 0x00138200: animation 0x11 and behaviour flag 0x800000. */
void b13_State138200(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, 0x11);
    o->flags10 = (o->flags10 & ~0x20u) | 6;
    e->flags4C &= ~0x18u;
    e->behav->flags4 |= 0x800000;
}

/* 0x00138240: mirrored animation 0/1, owner flag 0x20. */
void b13_State138240(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, e->side22 & 1);
    o->flags10 |= 0x20;
}

/* 0x00138390: animation 0x20, behaviour flag 0x400000, timer 0/3. */
void b13_State138390(B13Owner *o, B13Enemy *e)
{
    B13Timer *t;
    sub_00113090(o, e, 0x20);
    o->flags10 |= 0x20;
    e->flags4C &= ~0x100u;
    e->behav->flags4 |= 0x400000;
    t = sub_00113430(e, 2);
    t->a = 0;
    t->b = 3;
}

/* 0x00138700: mirrored animation 0x12/0x13. */
void b13_State138700(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, (e->side22 & 1) + 0x12);
    o->flags10 = (o->flags10 & ~0x20u) | 6;
    e->flags4C &= ~0x10u;
}

/* 0x001387A0: animation 0x14 and one exclamation point. */
void b13_State1387A0(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, 0x14);
    Grade_AddExclamations(1);
}

/* 0x00138800: mirrored animation 0x33/0x34 and slot 4. */
void b13_State138800(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, (e->side22 & 1) + 0x33);
    o->flagsC |= 0x20;
    sub_00113480(e, 4);
}

/* 0x00138BE0: if the model is ready, switch to animation 0xD. */
void b13_State138BE0(B13Owner *o, B13Enemy *e)
{
    if (sub_000833E0((int)o->model)) {
        o->flags10 &= ~0x20u;
        sub_00113040(o, e, 0xD);
    }
}

/* 0x001399B0: set behaviour flag 0x100000. */
void b13_Flag1399B0(B13Owner *o, B13Enemy *e) { e->behav->flags4 |= 0x100000; }

/* 0x0013AA50: is p one of the four non-null slots? */
int b13_InSlots(void **slots, void *p)
{
    int i;
    for (i = 0; i < 4; i++)
        if (slots[i] != 0 && slots[i] == p) return 1;
    return 0;
}

/* 0x0013BD50: if 0x0013A0A0 allows, flags 0x30 and animation 0x1C. */
void b13_State13BD50(B13Owner *o, B13Enemy *e)
{
    if (sub_0013A0A0(o, e)) {
        e->flags4C |= 0x30;
        sub_00113040(o, e, 0x1C);
    }
}

/* 0x0013D2E0: size of this enemy type's component. */
int b13_Size13D2E0(void) { return 0x40; }
