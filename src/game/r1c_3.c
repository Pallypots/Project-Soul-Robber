/* Area r1c, group 3: small helpers 0x0001EE80..0x0005BE80. Names inferred. */
#include "r1c.h"

/* 0x0001EE80: set the parameter word of an object's effect controller.
   Hangs (assert) when the controller's handler is not 0x0001ED90. */
void r1c_FxCtlSetParam(R1cFxObj *o, void *v)
{
    R1cFxCtl *c;
    if (o == 0 || !(o->flags & 0x10) || o->owner == 0) return;
    c = o->owner->ctl;
    if (c == 0) return;
    if (c->handler != (void *)sub_0001ED90) for (;;) ;
    c->param = v;
}

/* 0x0001EEC0: set the rate of an object's effect controller.
   Hangs (assert) when the controller's handler is not 0x0001ED90. */
void r1c_FxCtlSetRate(R1cFxObj *o, float rate)
{
    R1cFxCtl *c;
    if (o == 0 || !(o->flags & 0x10) || o->owner == 0) return;
    c = o->owner->ctl;
    if (c == 0) return;
    if (c->handler != (void *)sub_0001ED90) for (;;) ;
    c->rate = rate;
}

/* 0x0002CF50: main loop: run the frame step; when it reports nothing to do,
   post event 1 to the given target and service jobs; then yield. Never
   returns. */
void r1c_MainLoop(void *target)
{
    for (;;) {
        if (sub_0002CC20() == 0) {
            sub_001A1060(target, 1);
            sub_00058190();
        }
        sub_000580D0();
    }
}

/* 0x000340D0: format the effect pack path for a world id into buf (255
   bytes); retries until the id resolves.
   regargs: id=ESI */
void r1c_FxPackPath(char *buf, int id)
{
    int area, sub;
    while (sub_00057690(id, &area, &sub) != 0)
        ;
    a6b_Printf3(buf, 0xFF, r1c_fmtFxPath, area, sub, area, sub);
}

/* 0x00036AD0: take the first free entry of a pool (entries of `stride`
   bytes after a one-stride header); marks it used and bumps the owner's
   use count. Returns 0 when the pool is full. */
R1cPoolEnt *r1c_PoolTake(R1cPool *pool, int stride)
{
    int i;
    int n = pool->count;
    R1cPoolEnt *e = (R1cPoolEnt *)((char *)pool + stride);
    for (i = 0; i < n; i++) {
        if (!(e->flags & 1)) break;
        e = (R1cPoolEnt *)((char *)e + stride);
    }
    if (i >= n) return 0;
    e->flags = 1;
    e->owner->used++;
    return e;
}

/* 0x0003B150: the current camera's field value, or -1.0 when there is no
   active camera. */
float r1c_CamValue(void)
{
    R1cCamSet *s;
    if (r1c_camCount3DDC60 > 0 && r1c_cam3DDC64 != 0) {
        s = r1c_cam3DDC64->set;
        if (s != 0 && (s->flags & 1))
            return s->value;
    }
    return -1.0f;
}

/* 0x0003CFE0: reset the group header block at 0x003DDCC0. */
void r1c_GroupHdrReset(void)
{
    r1c_grp3DDCC0.d00 = 0;
    r1c_grp3DDCC0.recs = 0;
    r1c_grp3DDCC0.data = 0;
    r1c_grp3DDCC0.d04 = 0;
    r1c_grp3DDCC0.d24 = 0;
    r1c_grp3DDCC0.d1C = 0;
    r1c_grp3DDCC0.d28 = 0;
    sub_0003D860(&r1c_grp3DDCC0.list);
}

/* 0x0003F880: dispatch an event to an object's handler table entry +4, or to
   the default handler 0x0003F780 when it has none. */
void r1c_ObjDispatch(void *ev, R1cHObj *o, int mode)
{
    R1cHFunc fn;
    if (o->vt != 0 && (fn = o->vt->handle) != 0) {
        fn(ev, o, mode);
        return;
    }
    sub_0003F780(ev, o, mode);
}

/* 0x00048250: stop sound slot i and clear its word in the table at
   0x003DFA68. */
void r1c_SlotStop(int i)
{
    sub_0019A4B0(i);
    r1c_tbl3DFA68[i].w00 = 0;
}

/* 0x00048530: field +4 of the lookup table entry with this key, or 0. */
int r1c_LookupA(int key)
{
    int i;
    for (i = 0; i < 9; i++)
        if (r1c_tbl2C7A84[i].key == key)
            return r1c_tbl2C7A84[i].a;
    return 0;
}

/* 0x00048560: field +8 of the lookup table entry with this key, or 0. */
int r1c_LookupB(int key)
{
    int i;
    for (i = 0; i < 9; i++)
        if (r1c_tbl2C7A84[i].key == key)
            return r1c_tbl2C7A84[i].b;
    return 0;
}

/* 0x00048EE0: start the queued request when the queue is idle, otherwise
   mark the request pending (-1).
   calls 0x00048AA0 with ESI=arg */
void r1c_QueueKick(int arg)
{
    if (r1c_q3DFEC0 == r1c_q3DFEC4)
        sub_00048AA0(arg);
    else
        r1c_q3DFEC8 = -1;
}

/* 0x00053100: format the particle pack path for a world id into buf (255
   bytes); retries until the id resolves.
   regargs: id=ESI */
void r1c_PtPackPath(char *buf, int id)
{
    int area, sub;
    while (sub_00057690(id, &area, &sub) != 0)
        ;
    a6b_Printf3(buf, 0xFF, r1c_fmtPtPath, area, sub, area, sub);
}

/* 0x0005BE80: index of the first unused slot of a slot list, or -1. */
int r1c_SlotFindFree(R1cSlotList *l)
{
    int i;
    int n = l->count;
    for (i = 0; i < n; i++)
        if (l->slot[i].used == 0) break;
    return i < n ? i : -1;
}
