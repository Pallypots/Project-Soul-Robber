/* Area r3: small register-argument helpers, 0x0013D000..0x00190000 (r3_3). Names inferred. */
#include "r3.h"

/* 0x0013D4B0: release the two handles at work +0x38/+0x3C.
   regargs: act=EAX. */
void r3_ReleasePair13D4B0(R3Actor *act)
{
    R3Work *w = act->work278;
    void **p = w->p38;
    int n;

    for (n = 2; n != 0; n--, p++) {
        if (*p) {
            sub_0018E7C0(*p);
            *p = 0;
        }
    }
}

/* 0x00155E30: add d to work +0x50 and clamp it to [0, 900].
   regargs: act=EAX d=stack. */
void r3_AddClamped155E30(R3Actor *act, float d)
{
    R3Work *w = act->work278;
    float v = w->f50 + d;

    w->f50 = v;
    if (v < 0.0f)
        w->f50 = 0.0f;
    else if (v > 900.0f)
        w->f50 = 900.0f;
}

/* 0x00169D10: point for index idx: the player position when idx < 0, else entry idx of the table at 0x0031F0E0.
   regargs: idx=EAX. */
float *r3_GetPoint169D10(int idx)
{
    if (idx < 0)
        return ((R3Obj *)g_playerObj)->pos60;
    return r3_points31F0E0[idx];
}

/* 0x00172B50: enter sub-state idx (0..10) of o and run its enter handler.
   regargs: idx=EAX o=ECX arg=stack. Hangs on a bad index. */
int r3_FsmEnter172B50(int idx, R3Fsm *o, void *arg)
{
    if (idx < 0 || idx >= 11)
        for (;;) ;
    o->state4C = idx;
    o->i50 = 0;
    o->f54 = 0.0f;
    return r3_fsmEnter32B1B0[idx](arg, o);
}

/* 0x00172FF0: 1 when point p is closer to obj than the radius of obj's shape.
   regargs: obj=ESI p=EAX. */
int r3_InRange172FF0(R3Obj *obj, const float *p)
{
    float d = sub_001B2770(obj->pos60, p);

    return sub_00082D70(obj->p34 + 0x70) > d;
}

/* 0x00188C80: clear a four-word record (no-op for NULL).
   regargs: r=EAX. */
void r3_Clear188C80(R3Rec4 *r)
{
    if (r) {
        r->a = 0;
        r->f4 = 0.0f;
        r->c = 0;
        r->d = 0;
    }
}

/* 0x0018E230: start (on != 0: handle from 0x00036750(src, 3)) or stop the sound of o's slot.
   regargs: o=EAX src=stack on=stack. Hangs while the slot has no owner at +4. */
void r3_SlotSound18E230(R3SndOwner *o, void *src, int on)
{
    R3SndSlot *s = o->slot74;

    if (!s->p04)
        for (;;) ;
    if (on)
        s->h08 = sub_00036750(src, 3);
    else
        sub_00033A70((void *)s->h08);
}

/* 0x0018E360: combine b and a with 0x001AD9F0 into a temporary vector and measure it against c with 0x001B27C0.
   regargs: a=EAX b=ECX c=stack. */
float r3_Measure18E360(const float *a, const float *b, const float *c)
{
    float t[4];

    sub_001AD9F0(t, b, a);
    return sub_001B27C0(c, t);
}
