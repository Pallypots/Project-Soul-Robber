/* Area r4c: bounce effect callbacks around 0x00194780-0x00194EF6 (r4c_4). Names inferred. */
#include "r4c.h"

/* 0x00194780: burst effect: play its sound and light, spawn debris (two styles by work flag 2), free it. Stack args (o a). */
void r4c_FxBurst(R4cNode *o, R4cActor *a)
{
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    sub_00035DD0(o, o->i130, 4, 1);
    sub_00049700(0x20E, 0x80, 0x80, 0x80, o->pos, 1, 100.0f, 0);
    if (((R4cFxE *)a->work)->flags & 2) {
        /* The original pushes only four arguments here; 0x000C4D30 reads its
           arguments 5..10 from the six still on the stack from 0x000C46A0
           (one merged add esp, 0x28). Called through a 4-argument type. */
        ((int (*)(void *, int, float, int))sub_000C4D30)(o, 10, 10.0f,
            sub_000C46A0(12.5f, 0.016666668f, 2.5f, o->pos, v, v));
        sub_000ED780(o);
    } else {
        sub_000C4DF0(o, 0, 10.0f, 0, 12.5f, 1.0f, 2.5f, o->pos, v, v);
        sub_000ED780(o);
    }
}

/* 0x001948A0: bounce: turn half a circle, reverse and double the motion, spin towards the target. Stack args (o a). */
void r4c_FxBounce(R4cNode *o, R4cActor *a)
{
    R4cFxE *w = (R4cFxE *)a->work;
    float r;
    w->flags = (w->flags & ~0xCu) | 2;
    r = o->rot50[1] + 3.1415927f;
    o->rot50[1] = r;
    if (r > 3.1415927f)
        o->rot50[1] = r - 6.2831855f;
    r4c_Vec4Scale(o->v80, o->v80, -2.0f);
    o->v80[1] = 0.0f;
    w->f04 = 0.0f;
    w->f0C = w->f0C * 2.0f;
    w->f08 = 80.0f;
    if (((R4cFxE *)a->work)->p18)
        sub_0018D680(o, ((R4cFxE *)a->work)->p18, r4c_frameSeconds * 90.0f * 2.0f);
    sub_00189DA0(o, a, 0);
}

/* 0x00194970: bounce and stop: as 0x001948A0 but clears rotation and motion afterwards. Stack args (o a). */
void r4c_FxBounceStop(R4cNode *o, R4cActor *a)
{
    R4cFxE *w;
    float r;
    float *v;
    sub_000EE6D0(o, 1.0f);
    w = (R4cFxE *)a->work;
    w->flags = (w->flags & ~0xCu) | 2;
    r = o->rot50[1] + 3.1415927f;
    o->rot50[1] = r;
    if (r > 3.1415927f)
        o->rot50[1] = r - 6.2831855f;
    v = o->v80;
    r4c_Vec4Scale(v, v, -2.0f);
    o->v80[1] = 0.0f;
    w->f0C = w->f0C * 2.0f;
    w->f04 = 0.0f;
    w->f08 = 80.0f;
    ((R4cFxE *)a->work)->flags |= 0x40;
    o->rot50[0] = 0.0f;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    o->flagsC &= ~0xC0u;
}

/* 0x00194A80: bounce facing the player: copy the player's rotation, then bounce and reverse. Stack args (o a). */
void r4c_FxBounceFace(R4cNode *o, R4cActor *a)
{
    R4cFxE *w;
    float r;
    sub_000F5D40(o->rot50, (char *)g_playerObj + 0x50);
    w = (R4cFxE *)a->work;
    w->flags = (w->flags & ~0xCu) | 2;
    r = o->rot50[1] + 3.1415927f;
    o->rot50[1] = r;
    if (r > 3.1415927f)
        o->rot50[1] = r - 6.2831855f;
    r4c_Vec4Scale(o->v80, o->v80, -2.0f);
    o->v80[1] = 0.0f;
    w->f04 = 0.0f;
    w->f0C = w->f0C * 2.0f;
    w->f08 = 80.0f;
    r4c_Vec4Scale(o->v80, o->v80, -1.0f);
    ((R4cFxE *)a->work)->flags &= ~0x40u;
}

/* 0x00194D90: spawn a shot (kind 0x14 for owner 3/5, 0x21 for owner 2/13) from p0 to p1; returns 1 if spawned.
   Stack args (owner p0 p1 k). */
int r4c_SpawnShot(R4cOwner *owner, float *p0, float *p1, float k)
{
    void *fx;
    R4cActor *act;
    R4cFxF *w;
    if (!owner)
        return 0;
    if (owner->i04 == 3 && owner->i08 == 5)
        fx = sub_000ED630(5, 0x14, 0, 0, 3);
    else if (owner->i04 == 2 && owner->i08 == 0xD)
        fx = sub_000ED630(5, 0x21, 0, 0, 3);
    else
        return 0;
    if (!fx)
        return 0;
    act = (R4cActor *)sub_0001D960(fx, 7);
    w = (R4cFxF *)act->work;
    w->f54 = k;
    w->owner = owner;
    sub_000F5D40(w->v24, p0);
    sub_000F5D40(w->v34, p1);
    sub_00189DA0(fx, act, 0xC);
    return 1;
}

/* 0x00194E30: spawn a kind-0x1F shot from p0 to p1; returns 1 if spawned. Stack args (owner p0 p1 k). */
int r4c_SpawnShot1F(void *owner, float *p0, float *p1, float k)
{
    void *fx;
    R4cActor *act;
    R4cFxF *w;
    if (!owner)
        return 0;
    fx = sub_000ED630(5, 0x1F, 0, 0, 3);
    if (!fx)
        return 0;
    act = (R4cActor *)sub_0001D960(fx, 7);
    w = (R4cFxF *)act->work;
    w->owner = owner;
    w->f54 = k;
    sub_000F5D40(w->v24, p0);
    sub_000F5D40(w->v34, p1);
    sub_00189DA0(fx, act, 0xD);
    return 1;
}
