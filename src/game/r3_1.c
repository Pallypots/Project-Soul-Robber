/* Area r3: character state setters with register arguments (r3_1). Names inferred. */
#include "r3.h"

/* 0x00131310: leave the current state and enter a new one (variant A).
   regargs: obj=EBX act=EDI state=stack. */
void r3_SetStateA(R3Obj *obj, R3Actor *act, int state)
{
    R3Work *w = act->work278;
    uint32_t f;

    sub_001134B0(act);
    obj->flags0C |= 0xE0;
    obj->flags10 &= 0xFFFFFEE8;
    act->flags4C &= 0xFFFFFE8F;
    f = w->flags0C & 0xFFFCFF79;
    w->flags0C = f;
    if ((f & 0x2000) && state != 0x22) {
        sub_00113AA0(obj, act);
        act->flags4C |= 0x200;
        w->flags0C &= ~0x2000u;
    }
    if (w->flags0C & 0x40000) {
        if (w->snd04)
            sub_00194D30(w->snd04, 10);
        sub_0001D720(obj);
    }
    if (act->h6C >= 0) {
        sub_00048250(act->h6C);
        act->h6C = -1;
    }
    sub_0005BE30(obj->i13C);
    if (act->p70) {
        sub_00033A70(act->p70);
        act->p70 = 0;
    }
    if (act->state50 != 0x18 && state == 0x18) {
        sub_0012E5E0(2);
        sub_00113040(obj, act, 0x18);
        return;
    }
    if (act->state50 == 0x18 && state != 0x18)
        sub_0012E5E0(3);
    sub_00113040(obj, act, state);
}

/* 0x00135A70: leave the current state and enter a new one (variant B).
   regargs: obj=ESI act=EDI state=stack. */
void r3_SetStateB(R3Obj *obj, R3Actor *act, int state)
{
    R3Work *w = act->work278;

    sub_001134B0(act);
    obj->flags0C |= 0xE0;
    obj->flags10 &= 0xFFFFFEE8;
    act->flags4C &= 0xFFFFFE8F;
    w->flags08 &= 0xFFFFFFB9;
    sub_0005BE30(obj->i13C);
    sub_00113040(obj, act, state);
}

/* 0x00135730: run every check of condition list `table`; 1 when all pass (or the list is empty).
   regargs: table=EAX obj=EBX act=EDI. Hangs if the list is missing. */
int r3_CheckConds135730(int table, R3Obj *obj, R3Actor *act)
{
    R3Cond *c = r3_condLists135[table];

    if (!c)
        for (;;) ;
    for (; c->active; c++)
        if (!r3_condFns135[c->kind](obj, act, c))
            return 0;
    return 1;
}

/* 0x00135E10: count the live objects of types (2, 5) and (2, 15).
   Stack-argument (no inputs). */
int r3_Count135E10(void)
{
    int n = 0;
    void *o;

    for (o = sub_000EDC20(2, 5); o; o = sub_000EDC20(-1, -1))
        n++;
    for (o = sub_000EDC20(2, 0xF); o; o = sub_000EDC20(-1, -1))
        n++;
    return n;
}

/* 0x0018D9E0: turn b around (yaw + pi, wrapped) and restart a's motion block with spin 2 degrees and speed 80.
   regargs: a=EAX b=EDI. */
void r3_Reset18D9E0(R3Act74 *a, R3Spin *b)
{
    R3Flags74 *s = a->p74;
    float v;

    s->f04 = 0.0349065848f;
    s->f0C = 80.0f;
    s->f08 = 0.0f;
    s->f10 *= 2.0f;
    s->flags |= 2;
    v = b->rot50[1] + 3.14159274f;
    b->rot50[1] = v;
    if (v > 3.14159274f)
        b->rot50[1] = v - 6.28318548f;
    sub_001ADBA0(b->v80, b->v80, -2.0f);
    if (!(s->flags & 8))
        b->v80[1] = 0.0f;
    s->flags &= ~4u;
}
