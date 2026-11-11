/* Area r3: callers of the register-argument helpers around 0x00186000..0x0018F000 (r3_6). Names inferred. */
#include "r3.h"

/* 0x00187430: when the animation ends, switch to state 1.
   Stack args; calls 0x00186470 with EBX=obj EDI=act. */
void r3_State187430(R3Obj *obj, R3Actor *act)
{
    if (sub_000833E0(obj->anim30))
        sub_00186470(obj, act, 1);
}

/* 0x00186CF0: when the timer at +0x74 has run out or work flag 0x400 is set, switch to state 10.
   Stack args; calls 0x00186470 with EBX=obj EDI=act. */
void r3_State186CF0(R3Obj *obj, R3Actor *act)
{
    if (act->f74 <= 0.0f || (act->work278->flags18 & 0x400))
        sub_00186470(obj, act, 10);
}

/* 0x00187E70: switch to state 10 when condition list 0 or 13 passes.
   Stack args; calls 0x00186160 with EAX=table EBX=obj EDI=act and 0x00186470 with EBX=obj EDI=act. */
void r3_State187E70(R3Obj *obj, R3Actor *act)
{
    if (r3_CheckConds186160(0, obj, act) || r3_CheckConds186160(0xD, obj, act))
        sub_00186470(obj, act, 10);
}

/* 0x001882B0: when the animation ends switch to state 2 (act flag 0x20.bit0) or 1.
   Stack args; calls 0x00186470 with EBX=obj EDI=act. */
void r3_State1882B0(R3Obj *obj, R3Actor *act)
{
    if (!sub_000833E0(obj->anim30))
        return;
    if (act->flags20 & 1)
        sub_00186470(obj, act, 2);
    else
        sub_00186470(obj, act, 1);
}

/* 0x00186B00: act flag 0x100 forces state 4; otherwise at the end of the animation fire event 2 and go to state 1.
   Stack args; calls 0x00186470 with EBX=obj EDI=act. */
void r3_State186B00(R3Obj *obj, R3Actor *act)
{
    if (act->flags4C & 0x100) {
        sub_00186470(obj, act, 4);
        return;
    }
    if (sub_000833E0(obj->anim30)) {
        sub_00113480(act, 2);
        sub_00186470(obj, act, 1);
    }
}

/* 0x00187330: at the end of the animation (with work flag 0x100 setting +0x1C to 15) switch to state 2.
   Stack args; calls 0x00186470 with EBX=obj EDI=act. */
void r3_State187330(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;

    if (sub_000833E0(obj->anim30)) {
        if (w->flags18 & 0x100)
            w->f1C = 15.0f;
        sub_00186470(obj, act, 2);
    }
}

/* 0x00186BF0: when the timer at +0x74 has run out or work flag 0x400 is set: event 4, clear work flag 0x10, state 10.
   Stack args; calls 0x00186470 with EBX=obj EDI=act. */
void r3_State186BF0(R3Obj *obj, R3Actor *act)
{
    R3Work *w = act->work278;

    if (act->f74 <= 0.0f || (w->flags18 & 0x400)) {
        sub_00113480(act, 4);
        w->flags18 &= ~0x10u;
        sub_00186470(obj, act, 10);
    }
}

/* 0x00187F50: on obj flags 0x18 play effect 0x125, then go to state 1, or to state 2 once +0x5C reaches 1.
   Stack args; calls 0x00186470 with EBX=obj EDI=act. */
void r3_State187F50(R3Obj *obj, R3Actor *act)
{
    if (!(obj->flags128 & 0x18))
        return;
    sub_000494D0(0x125, obj->pos60, 0);
    if (act->flags20 & 1) {
        if (act->f5C >= 1.0f)
            sub_00186470(obj, act, 2);
    } else {
        sub_00186470(obj, act, 1);
    }
}

/* 0x0018DD30: turn b around and, if a has a target at +0x14, steer b to it at twice the block speed.
   Stack args (b a); calls 0x0018D9E0 with EAX=a EDI=b. */
void r3_TurnBack18DD30(R3Spin *b, R3Act74 *a)
{
    R3Flags74 *s;

    r3_Reset18D9E0(a, b);
    s = a->p74;
    if (s->p14)
        sub_0018D680(b, s->p14, s->f10 * 2.0f);
}

/* 0x0018DDC0: reset b's vector to (0,0,0,1), clear b flag 0x40 and a flag 8, then turn b around.
   Stack args (b a); calls 0x0018D9E0 with EAX=a EDI=b. */
void r3_Restart18DDC0(R3Spin *b, R3Act74 *a)
{
    b->v80[0] = 0.0f;
    b->v80[1] = 0.0f;
    b->v80[2] = 0.0f;
    b->v80[3] = 1.0f;
    b->flags0C &= ~0x40u;
    a->p74->flags &= ~8u;
    r3_Reset18D9E0(a, b);
}

/* 0x0018DE60: copy the player's rotation to b, turn b around and scale its vector by -2 once more.
   Stack args (b a); calls 0x0018D9E0 with EAX=a EDI=b. */
void r3_FacePlayer18DE60(R3Spin *b, R3Act74 *a)
{
    sub_000F5D40(b->rot50, ((R3Spin *)g_playerObj)->rot50);
    r3_Reset18D9E0(a, b);
    sub_001ADBA0(b->v80, b->v80, -2.0f);
}

/* 0x0018E700: start or stop the sound of object h (component 7).
   Stack args; calls 0x0018E230 with EAX=component and (h on) on the stack. */
void r3_Sound18E700(void *h, int on)
{
    R3SndOwner *c;

    if (!h)
        return;
    c = (R3SndOwner *)sub_0001D960(h, 7);
    if (!c)
        return;
    sub_00189DE0(h, on);
    r3_SlotSound18E230(c, h, on);
}
