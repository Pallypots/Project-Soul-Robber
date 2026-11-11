/* Area r3: state handlers that call the variant-A/B state setters (r3_2). Names inferred. */
#include "r3.h"

/* 0x00132110: switch to state 7. Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State132110(R3Obj *obj, R3Actor *act) { r3_SetStateA(obj, act, 7); }

/* 0x00134B60: switch to state 0x27. Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State134B60(R3Obj *obj, R3Actor *act) { r3_SetStateA(obj, act, 0x27); }

/* 0x00132230: once the timer at +0x74 has run out, switch to state 5.
   Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State132230(R3Obj *obj, R3Actor *act)
{
    if (act->f74 <= 0.0f)
        r3_SetStateA(obj, act, 5);
}

/* 0x00133950: once the timer at +0x74 has run out, switch to state 0x19.
   Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State133950(R3Obj *obj, R3Actor *act)
{
    if (act->f74 <= 0.0f)
        r3_SetStateA(obj, act, 0x19);
}

/* 0x00133970: when the animation ends, switch to state 5.
   Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State133970(R3Obj *obj, R3Actor *act)
{
    if (sub_000833E0(obj->anim30))
        r3_SetStateA(obj, act, 5);
}

/* 0x00132BB0: two-step state: wait for the animation, then switch to state 1.
   Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State132BB0(R3Obj *obj, R3Actor *act)
{
    switch (act->step58) {
    case 0:
        if (!sub_000833E0(obj->anim30))
            return;
        act->step58++;
        /* fall through */
    case 1:
        r3_SetStateA(obj, act, 1);
    }
}

/* 0x00132530: when the animation ends go to state 1 (work flag 1 set) or 5.
   Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State132530(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;

    if (!sub_000833E0(obj->anim30))
        return;
    if (w->flags0C & 1)
        r3_SetStateA(obj, act, 1);
    else
        r3_SetStateA(obj, act, 5);
}

/* 0x00132580: as 0x00132530 but first runs 0x0012E5E0 mode 0.
   Stack args; calls 0x0012E5E0 with ESI=0 and 0x00131310 with EBX=obj EDI=act. */
void r3_State132580(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;

    if (!sub_000833E0(obj->anim30))
        return;
    sub_0012E5E0(0);
    if (w->flags0C & 1)
        r3_SetStateA(obj, act, 1);
    else
        r3_SetStateA(obj, act, 5);
}

/* 0x00133F50: when the animation ends pick the follow-up state (0x2B, 0xE or 5).
   Stack args; calls 0x0012E630 with EAX=act (obj on the stack) and 0x00131310 with EBX=obj EDI=act. */
void r3_State133F50(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;

    if (!sub_000833E0(obj->anim30))
        return;
    if (w->flags0C & 0x20) {
        r3_SetStateA(obj, act, 0x2B);
    } else if (sub_0012E630(act, obj)) {
        w->f184 = 0.3f;
        r3_SetStateA(obj, act, 0xE);
    } else {
        r3_SetStateA(obj, act, 5);
    }
}

/* 0x00137460: when the animation ends, switch to state 3.
   Stack args; calls 0x00135A70 with ESI=obj EDI=act. */
void r3_State137460(R3Obj *obj, R3Actor *act)
{
    if (sub_000833E0(obj->anim30))
        r3_SetStateB(obj, act, 3);
}

/* 0x00137490: when the animation ends, reset +0x170/+0x174 and switch to state 5.
   Stack args; calls 0x00135A70 with ESI=obj EDI=act. */
void r3_State137490(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;

    if (sub_000833E0(obj->anim30)) {
        w->u170.i = 0;
        w->i174 = 1;
        r3_SetStateB(obj, act, 5);
    }
}

/* 0x00136C70: at animation time 16 fire event 1; when the animation ends go to state 3 or 1.
   Stack args; calls 0x00135A70 with ESI=obj EDI=act. */
void r3_State136C70(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;

    if (sub_00145780(obj, 16.0f))
        sub_00113480(act, 1);
    if (!sub_000833E0(obj->anim30))
        return;
    if (w->flags08 & 1)
        r3_SetStateB(obj, act, 3);
    else
        r3_SetStateB(obj, act, 1);
}

/* 0x00135EB0: request on the first type-0xC object: mode 0/1 set work flags 0x400/0x800, mode 2 switches it to state 2.
   Stack arg; calls 0x00135A70 with ESI=obj EDI=act. Hangs if the object has no component 4. */
void r3_Request135EB0(int mode)
{
    R3Obj *obj = (R3Obj *)sub_000EDC20(2, 0xC);
    R3Actor *act;
    R3Work *w;

    if (!obj)
        return;
    act = (R3Actor *)sub_0001D960(obj, 4);
    if (!act)
        for (;;) ;
    w = act->work278;
    if (w->flags08 & 0x1000)
        return;
    switch (mode) {
    case 0: w->flags08 |= 0x400; break;
    case 1: w->flags08 |= 0x800; break;
    case 2: r3_SetStateB(obj, act, 2); break;
    }
}

/* 0x00136DC0: at animation time 24 fire event 1; at the end pick a random sound (6, 7 or 8) then go to state 3 or 1.
   Stack args; calls 0x00135A70 with ESI=obj EDI=act. */
void r3_State136DC0(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;
    int v;

    if (sub_00145780(obj, 24.0f))
        sub_00113480(act, 1);
    if (!sub_000833E0(obj->anim30))
        return;
    if (!(sub_001C7EE1() & 3) && w->i180 >= 10)
        v = 6;
    else
        v = 7 + ((sub_001C7EE1() & 1) != 0);
    sub_0012D600(v);
    if (w->flags08 & 1)
        r3_SetStateB(obj, act, 3);
    else
        r3_SetStateB(obj, act, 1);
}

/* 0x00133B00: inside animation window [10, FLT_MAX] maybe chain into state 0x15/0xE; at the end go to 0x2B or 5.
   Stack args; calls 0x0012E630 with EAX=act (obj on the stack) and 0x00131310 with EBX=obj EDI=act. */
void r3_State133B00(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;

    if (!(w->flags0C & 0x20) && sub_001457C0(obj, 10.0f, 3.402823466e+38f) && sub_0012E630(act, obj)) {
        w->f184 = 0.3f;
        r3_SetStateA(obj, act, (sub_001C7EE1() & 3) ? 0xE : 0x15);
    }
    if (!sub_000833E0(obj->anim30))
        return;
    if (w->flags0C & 0x20)
        r3_SetStateA(obj, act, 0x2B);
    else
        r3_SetStateA(obj, act, 5);
}

/* 0x00134D10: once per state post three values (5, 6 from +0x270/+0x274, then 4); at the end go to state 3 or 5.
   Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State134D10(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;
    uint32_t f = w->flags0C;

    if (!(f & 1) && (int16_t)f >= 0) {   /* bit 0x8000 clear */
        w->flags0C = f | 0x8000;
        sub_000253D0(5, (int)act->f270);
        sub_000253D0(6, (int)act->f274);
        sub_000253D0(4, 0);
    }
    if (!sub_000833E0(obj->anim30))
        return;
    if (w->flags0C & 1) {
        w->i174 = 3;
        w->i178 = 0;
        r3_SetStateA(obj, act, 3);
    } else {
        r3_SetStateA(obj, act, 5);
    }
}

/* 0x00134A70: close to the target point and slow: hand over to 0x000C56B0; otherwise reset motion, play effect 0x77 and go to state 0x27.
   Stack args; calls 0x00131310 with EBX=obj EDI=act. */
void r3_State134A70(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;
    R3Work *w2;
    float d = sub_001B2770(obj->pos60, w->vec154);

    if (!(obj->flags128 & 0x1E) && act->f5C < 3.0f && d < 60.0f && !(w->flags0C & 0x80000)) {
        sub_000C56B0(obj);
        return;
    }
    if (sub_001456E0(obj, act, 0x43, 0) == 1)
        sub_0001D4E0(obj);
    w2 = act->work278;
    w2->f16C = 0.0f;
    w2->f168 = 0.0f;
    w2->f164 = 0.0f;
    w2->u170.f = 1.0f;
    sub_000494D0(0x77, obj->pos60, 0);
    sub_000C62A0(obj);
    sub_00025D50(1, 1);
    if (w->flags0C & 0x20)
        obj->flags10 |= 0xD;
    r3_SetStateA(obj, act, 0x27);
}

