/* Area r3: register-argument helpers, 0x00155000..0x00190000 (r3_4). Names inferred. */
#include "r3.h"

/* 0x001558F0: run every check of condition list `table`; 1 when all pass (or the list is empty).
   regargs: table=EAX a=EBX b=EDI. Hangs if the list is missing. */
int r3_CheckConds1558F0(int table, void *a, void *b)
{
    R3Cond2 *c = r3_condLists155[table];

    if (!c)
        for (;;) ;
    for (; c->active; c++)
        if (!r3_condFns155[c->kind](a, b, c))
            return 0;
    return 1;
}

/* 0x0016C820: set the model state, then flag 0x2000 (copying the model's +0x54) unless bits 0xC00 came back.
   regargs: a=EAX m=EDI state=stack; calls 0x001671D0 with all three on the stack (m a state). */
void r3_SetState16C820(R3Act74 *a, R3Model54 *m, int state)
{
    R3Flags74 *s = a->p74;
    uint32_t f;

    s->flags &= ~0xC00u;
    sub_001671D0(m, a, state);
    f = s->flags;
    if (!(f & 0xC00)) {
        s->flags = f | 0x2000;
        s->i3C = m->i54;
    } else {
        s->flags = f & ~0x2000u;
    }
}

/* 0x0016FB60: release the flagged items of a list, unlink it from the context and free it.
   regargs: list=ESI. */
void r3_FreeList16FB60(R3ItemList *list)
{
    int i;

    if (!list)
        return;
    for (i = 0; i < list->count; i++)
        if (list->items[i].flags0C & 1)
            sub_000ED780(&list->items[i]);
    sub_0001D030(r3_ctx42C8E4->p1E8, list);
    sub_00020170(list);
}

/* 0x00176930: create the effect at work +0x2C once (type 5, size 0x10, at e+0x50) and attach it to e.
   regargs: act=EAX e=EDI. */
void r3_MakeEffect176930(R3Actor *act, R3Ent50 *e)
{
    R3Work *w = act->work278;
    void *h;

    if (w->h2C)
        return;
    h = sub_000ED630(5, 0x10, 0, e->pos50, e);
    w->h2C = h;
    if (h)
        sub_0018C450(h, e, 0x1E, w->i30);
}

/* 0x0018E5F0: spawn effect 2 at o's position with zero velocity.
   regargs: o=EAX. */
void r3_Spawn18E5F0(R3Obj *o)
{
    float v[4];

    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    sub_000C4DF0(o, 2, 10.0f, 0, 12.5f, 1.0f, 2.5f, o->pos60, v, v);
}

/* 0x0018E5A0: create a burst at o's position with zero velocity and attach it as effect 10.
   regargs: o=ESI. */
void r3_Spawn18E5A0(R3Obj *o)
{
    float v[4];

    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    sub_000C4D30(o, 10, 10.0f, sub_000C46A0(), 12.5f, 1.0f / 60.0f, 2.5f, o->pos60, v, v);
}
