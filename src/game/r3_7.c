/* Area r3: callers of register-argument helpers, 0x00140000..0x0018F000 (r3_7). Names inferred. */
#include "r3.h"

/* 0x00140540: while another type-(2,1) object is busy, hold act's timer at 60 frames.
   Stack arg; calls 0x00140170 with ESI=act. */
void r3_Hold140540(R3Actor *act)
{
    if (r3_OtherBusy140170(act))
        act->f74 = 60.0f / r3_frameUnits * r3_frameDelta;
}

/* 0x0018E7F0: set the playback rate of object h (2.0 when on, else 1.0) and, if its sound flag is set, toggle the slot sound.
   Stack args (h on); calls 0x0018E230 with EAX=component and (h, on == 0) on the stack. */
void r3_Rate18E7F0(void *h, int on)
{
    R3SndOwner *c;

    if (!h)
        return;
    c = (R3SndOwner *)sub_0001D960(h, 7);
    if (!c || c->slot74->mode00 != 1)
        return;
    sub_000EE760(h, on ? 2.0f : 1.0f);
    if (c->flags20 & 1)
        r3_SlotSound18E230(c, h, on == 0);
}

/* 0x0017CEA0: tick the pulse driver hung off act's work pointer.
   Stack args (unused, act); calls 0x0017C670 with ESI=driver. */
void r3_Tick17CEA0(void *unused, R3Actor *act)
{
    (void)unused;
    r3_Tick17C670((R3Pulse *)act->work278);
}

/* 0x0017EAC0: clear both records of the table at 0x003FDED8.
   No inputs; calls 0x0017E4D0 with EAX=record. */
void r3_ClearAll17EAC0(void)
{
    R3Rec17E *r;

    for (r = r3_recs3FDED8; r < r3_recs3FDED8 + 2; r++)
        r3_ClearRec17E4D0(r);
}

/* 0x001738F0: reset b's +0xB8 and play animation 3.
   Stack args (a b); calls 0x00172C90 with EAX=b ESI=a EDI=3. */
void r3_Anim1738F0(R3Obj2 *a, R3Ctl *b)
{
    b->iB8 = 0;
    r3_PlayAnim172C90(b, a, 3);
}

/* 0x001736B0: set a flag 4, play animation 0xD (0xE for kind 9 with b flag 0x1000), set b flag 1, clear +0xB8 and take one exclamation point.
   Stack args (a b); calls 0x00172C90 with EAX=b ESI=a EDI=anim. */
void r3_Anim1736B0(R3Obj2 *a, R3Ctl *b)
{
    int anim;

    a->flags10 |= 4;
    if (a->kind08 == 9 && (b->flags5C & 0x1000))
        anim = 0xE;
    else
        anim = 0xD;
    r3_PlayAnim172C90(b, a, anim);
    b->iB8 = 0;
    b->flags5C |= 1;
    Grade_AddExclamations(-1);
}

/* 0x001733E0: clear a flag 4 and b flag 1, then play 0xE for kinds 6/0x17 (resetting +0x50/+0x68), 0xE for kind 7, else 6.
   Stack args (a b); calls 0x00172C90 with EAX=b ESI=a EDI=anim. */
void r3_Anim1733E0(R3Obj2 *a, R3Ctl *b)
{
    int k, anim;

    a->flags10 &= ~4u;
    b->flags5C &= ~1u;
    k = a->kind08;
    if (k == 6 || k == 0x17) {
        anim = 0xE;
        b->i50 = 1;
        b->h68 = 0;
    } else {
        anim = (k == 7) * 8 + 6;
    }
    r3_PlayAnim172C90(b, a, anim);
    b->iB8 = 0;
}

/* 0x00174470: play animation anim on the global object (unless its kind is 0x10..0x14) through its controller component 8.
   Stack arg; calls 0x00172C90 with EAX=controller ESI=global object EDI=anim. Hangs if anything is missing or the animation did not take. */
void r3_GlobalAnim174470(int anim)
{
    R3Obj2 *o = r3_obj3FD7C4;
    R3Ctl *c;

    if (!o)
        for (;;) ;
    if (o->kind08 >= 0x10 && o->kind08 <= 0x14)
        return;
    c = (R3Ctl *)sub_0001D960(o, 8);
    if (!c)
        for (;;) ;
    r3_PlayAnim172C90(c, r3_obj3FD7C4, anim);
    if (r3_obj3FD7C4->anim30->cur08 != anim)
        for (;;) ;
}

/* 0x0017A6C0: step 0 clears work flags 0x18 and +0x18/+0x20; step 1 waits for the animation, then state 1.
   Stack args; calls 0x0017A2B0 with EBX=obj ESI=act. */
void r3_State17A6C0(R3Obj *obj, R3Actor *act)
{
    R3WorkD *w = (R3WorkD *)act->work278;

    switch (act->step58) {
    case 0:
        w->flags00 &= ~0x18u;
        w->f18 = 0.0f;
        w->f20 = 0.0f;
        act->step58++;
        break;
    case 1:
        if (sub_000833E0(obj->anim30))
            r3_SetStateD(obj, act, 1);
        break;
    }
}

/* 0x0017A720: step 0 swaps work flag 8 for 0x10, clears +0x20 and sets act flag 0x200; step 1 waits for the animation, then state 4.
   Stack args; calls 0x0017A2B0 with EBX=obj ESI=act. */
void r3_State17A720(R3Obj *obj, R3Actor *act)
{
    R3WorkD *w = (R3WorkD *)act->work278;

    switch (act->step58) {
    case 0:
        w->flags00 = (w->flags00 & ~8u) | 0x10;
        w->f20 = 0.0f;
        act->flags4C |= 0x200;
        act->step58++;
        break;
    case 1:
        if (sub_000833E0(obj->anim30))
            r3_SetStateD(obj, act, 4);
        break;
    }
}
