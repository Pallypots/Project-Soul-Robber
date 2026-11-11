/* Area r3b: character state callbacks in 0x0013C000..0x0013FFFF (r3b_6). Names inferred. */
#include "r3b.h"

/* 0x0013CCB0: when the animation has finished, enter state 9 if condition 7 of table 0x0031CDFC holds, else state 0x1C. */
void r3b_State13CCB0(R3bObj *obj, R3bAct *act)
{
    if (sub_000833E0(obj->anim30)) {
        if (r3b_disp31CDFC[7](obj, act, &r3b_recs279728[7]))
            sub_00113040(obj, act, 9);
        else
            sub_00113040(obj, act, 0x1C);
    }
}

/* 0x0013CF40: when 0x0013A7B0 allows it in sub-step 2, raise work flag bit 31 and enter state 0x1E. */
void r3b_State13CF40(R3bObj *obj, R3bAct *act)
{
    if (sub_0013A7B0(obj, act) && act->step58 == 2) {
        act->work278->u04.flags |= 0x80000000;
        sub_00113040(obj, act, 0x1E);
    }
}

/* 0x0013D8B0: after 30 frames-worth in the state, try a charge (0x0013D380) or, half the time, enter state 0x1B.
   Returns 1 when the charge started or the coin said stay. regargs: act=EAX obj=ECX;
   calls 0x0013D380 with EDI=act EBX=obj. */
int r3b_TryCharge13D8B0(R3bAct *act, R3bObj *obj)
{
    if (act->f68 >= 30.0f / r3_frameUnits * r3_frameDelta) {
        if (r3_SpawnCharge13D380(act, obj))
            return 1;
        if (sub_001C7EE1() % 2 >= 1)
            return 1;
        sub_00113040(obj, act, 0x1B);
    }
    return 0;
}

/* 0x0013E0E0: enter state 0x26 and arm timer slot 2 with (3, 6). */
void r3b_State13E0E0(R3bObj *obj, R3bAct *act)
{
    R3bTimer *t;

    obj->flags0C &= ~0x20u;
    obj->flags10 |= 6;
    act->flags4C |= 8;
    sub_00113090(obj, act, 0x26);
    t = sub_00113430(act, 2);
    t->a10.i = 3;
    t->a14.i = 6;
}

/* 0x0013E560: reset act, enter state 6 (or sub-step 2 when the side bit is set) and attach part 10. */
void r3b_State13E560(R3bObj *obj, R3bAct *act)
{
    sub_001134B0(act);
    if (!(act->b22 & 1))
        sub_00113090(obj, act, 6);
    else
        act->step58 = 2;
    act->flags4C = (act->flags4C & ~0x10u) | 0x20;
    act->work278->u04.flags |= 0x400000;
    sub_00036750(obj, 0xA);
}

/* 0x0013E970: clear the work counter and restart the work timer at 30 or 15 depending on 0x0013A4A0. */
void r3b_Timer13E970(R3bObj *obj, R3bAct *act)
{
    R3bWork *w = act->work278;

    w->i20 = 0;
    sub_00113CB0(&w->flags18, sub_0013A4A0(obj, act) ? 30.0f : 15.0f, 0);
}

/* 0x0013EAA0: enter state 0x15, start effect 0xA4 at the model position and attach part 9 (counter cleared). */
void r3b_State13EAA0(R3bObj *obj, R3bAct *act)
{
    sub_00113090(obj, act, 0x15);
    act->h6C = sub_000494D0(0xA4, (const float *)(obj->p20 + 0x30), 0);
    act->work278->i20 = 0;
    obj->flags10 |= 0x30;
    act->flags4C &= ~0x10u;
    act->h70 = sub_00036750(obj, 9);
}

/* 0x0013EBA0: set a random speed of 0..8 units per second and drop act flag 8. */
void r3b_RandSpeed13EBA0(void *obj, R3bAct *act)
{
    act->f74 = (float)(sub_001C7EE1() % 9) / r3_frameUnits * r3_frameDelta;
    act->flags4C &= ~8u;
}

/* 0x0013EC50: enter state 0x33/0x34 (by side bit), start the work counter and raise event 4. */
void r3b_State13EC50(R3bObj *obj, R3bAct *act)
{
    sub_00113090(obj, act, (act->b22 & 1) + 0x33);
    sub_00113C90(&act->work278->i20, 1, 0);
    sub_00113480(act, 4);
    obj->flags0C |= 0x20;
}

/* 0x0013ECA0: run 0x0013B960, start the work counter, effect 0x84, part 7, and enter state 0x45 at sub-step 2. */
void r3b_State13ECA0(R3bObj *obj, R3bAct *act)
{
    sub_0013B960(obj, act);
    sub_00113C90(&act->work278->i20, 1, 0);
    sub_000494D0(0x84, (const float *)(obj->p20 + 0x30), 0);
    sub_00036750(obj, 7);
    sub_00113090(obj, act, 0x45);
    obj->flags10 |= 4;
    act->step58 = 2;
}

/* 0x0013EDA0: enter state 0x2C (hangs without the work +0x34 handle) and zero the work +0x1C value. */
void r3b_State13EDA0(R3bObj *obj, R3bAct *act)
{
    if (!act->work278->p34)
        for (;;) ;
    sub_00113090(obj, act, 0x2C);
    obj->flags10 |= 0x20;
    act->flags4C |= 0x10;
    act->work278->f1C = 0.0f;
}

/* 0x0013EE20: enter state 0x27 and arm timer slot 10 with spin values (2 degrees * units, 25 degrees, 5 degrees, 0x280027). */
void r3b_State13EE20(R3bObj *obj, R3bAct *act)
{
    R3bTimer *t;

    sub_00113090(obj, act, 0x27);
    obj->flags10 |= 0x20;
    act->flags4C |= 0x10;
    t = sub_00113430(act, 0xA);
    t->a10.f = r3_frameUnits * 0.0349065848f;
    t->a14.f = 0.436332315f;
    t->a18.f = 0.0872664675f;
    t->i1C = 0x280027;
}

/* 0x0013EFF0: restart the work timer at 20, enter state 0x14 and award one exclamation. */
void r3b_State13EFF0(R3bObj *obj, R3bAct *act)
{
    R3bWork *w = act->work278;

    act->flags4C &= ~0x30u;
    obj->flags10 &= ~0x20u;
    sub_00113CB0(&w->flags18, 20.0f, 0);
    sub_00113090(obj, act, 0x14);
    Grade_AddExclamations(1);
}

/* 0x0013F1C0: when the animation has finished, raise event 2 and enter state 0xC. */
void r3b_State13F1C0(R3bObj *obj, R3bAct *act)
{
    if (sub_000833E0(obj->anim30)) {
        obj->flags0C |= 0x20;
        obj->flags10 &= ~6u;
        sub_00113480(act, 2);
        sub_00113040(obj, act, 0xC);
    }
}

/* 0x0013FC70: when the animation has finished, enter state 0xA (raising work flag 0x800000) once the work count is spent, else state 0x1C. */
void r3b_State13FC70(R3bObj *obj, R3bAct *act)
{
    R3bWork *w;

    if (sub_000833E0(obj->anim30)) {
        w = act->work278;
        if (w->i14 <= 0) {
            w->u04.flags |= 0x800000;
            sub_00113040(obj, act, 0xA);
        } else {
            sub_00113040(obj, act, 0x1C);
        }
    }
}

/* 0x0013FF30: when the animation has finished, enter state 0xB if the work +0x18 value reached 180 (and act bit 0 is clear), else state 0x28. */
void r3b_State13FF30(R3bObj *obj, R3bAct *act)
{
    int st;

    if (sub_000833E0(obj->anim30)) {
        if (!(act->b20[0] & 1) && act->work278->f18 >= 180.0f)
            st = 0xB;
        else
            st = 0x28;
        sub_00113040(obj, act, st);
    }
}
