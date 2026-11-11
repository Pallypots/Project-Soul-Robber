/* Area rbj: object spawning for the 0x00189DA0 actor family (rbj_2). Names inferred. */
#include "rbj.h"

/* 0x0018A060: spawn an object of the given kind (0..0x22): find its template and a free pool
   record, build it from the template, attach it to the scene, reset its push vector, set the
   optional position and rotation, install the component 0xD callbacks, reset the actor
   (component 7) and run the kind's init. If the init fails the record is freed again.
   Returns the object or 0. Hangs when the pool is missing. */
RbjNode *rbj_Spawn18A060(int kind, const RbjVec4 *pos, const RbjVec4 *rot, void *arg)
{
    RbjNode *pool = rbj_pool414444;
    RbjNode *tmpl, *o;
    RbjComp *c;
    RbjActor *a;
    int i, n;

    if (pool == 0)
        for (;;)
        ;
    if (kind < 0 || kind > 0x22)
        return 0;
    n = *rbj_tmplSet3FF57C;
    for (i = 0; i < n; i++)
        if (rbj_tmpl3FF584[i].kind08 == kind)
            break;
    if (i == n)
        return 0;
    tmpl = &rbj_tmpl3FF584[i];
    n = *rbj_poolCount414440;
    for (i = 0; i < n; i++)
        if (!(pool[i].flags0C & 1))
            break;
    if (i == n)
        return 0;
    o = &pool[i];
    sub_00022380(o, tmpl, rbj_scene42C8E4);
    sub_0001E9B0(rbj_scene42C8E4, o, o->p14C, 5, 0x11);
    o->flags10 = 0;
    o->push80.x = 0.0f;
    o->push80.y = 0.0f;
    o->push80.z = 0.0f;
    o->push80.w = 1.0f;
    sub_0001EBF0(o, 1);
    if (pos != 0)
        sub_000F5D40(&o->pos60, pos);
    if (rot != 0)
        sub_000F5D40(&o->rot50, rot);
    c = (RbjComp *)sub_0001D960(o, 0xD);
    if (c == 0)
        for (;;)
        ;
    sub_000EE270(c);
    c->fn24 = (void *)rbj_TryEnd189CF0;
    c->fn28 = (void *)rbj_Update189D30;
    c->fn2C = (void *)rbj_Call189E90;
    a = (RbjActor *)sub_0001D960(o, 7);
    a->f70 = 0.0f;
    a->timer6C = 0.0f;
    a->i5C = 0;
    a->prev64 = 0;
    a->state60 = 0;
    a->i68 = 0;
    a->vel4C.x = 0.0f;
    a->vel4C.y = 0.0f;
    a->vel4C.z = 0.0f;
    a->vel4C.w = 1.0f;
    a->work74 = 0;
    a->fn78 = sub_000AD090;
    a->fn7C = rbj_Move189ED0;
    a->fn80 = sub_000AD090;
    a->states84 = 0;
    a->update88 = 0;
    if (rbj_kindInit32C448[o->kind08](o, a, arg) == 0) {
        o->flags0C &= ~1u;
        sub_0001EB80(o);
        return 0;
    }
    return o;
}
