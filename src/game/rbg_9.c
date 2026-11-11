/* Area rbg: game functions in 0x00160000..0x0016FFFF (rbg_9). Names inferred. */
#include "rbg.h"

/* 0x001673E0: spawn an effect object of kind (0..4): copy the kind's template into the first
   free pool entry, register it with the scene, show its children, place it at pos facing dir,
   install the movement and behaviour callbacks and run the kind's init with arg. Returns the
   object, or 0 (no template, pool full, or init refused). Hangs without a pool. */
RbgRec150 *rbg_SpawnFx1673E0(int kind, const float *pos, const float *dir, int arg)
{
    RbgRec150 *pool = b4c_objs3F840C;
    RbgRec150 *tmpl, *o, *p;
    RbgComp *c, *d;
    RbgInitFn init;
    int i, n, k;

    if (!pool)
        for (;;)
            ;
    if (kind < 0 || kind > 4)
        return 0;
    n = *b16_task3F8400;
    for (i = 0; i < n; i++)
        if (b16_taskId3F8404[i].i08 == kind)
            break;
    if (i == n)
        return 0;
    tmpl = &b16_taskId3F8404[i];
    n = *r3d_i3F8408;
    for (i = 0; i < n; i++)
        if (!(pool[i].flags0C & 1))
            break;
    if (i == n)
        return 0;
    o = &pool[i];
    sub_00022380(o, tmpl, r3_ctx42C8E4);
    sub_0001E9B0(r3_ctx42C8E4, o, o->i14C, 5, 0x11);
    for (p = o->next3C, k = 0; p; p = p->next3C, k++)
        sub_0001D470(o, k);
    o->flags10 = 0;
    if (pos)
        sub_000F5D40(o->pos60, pos);
    if (dir)
        sub_000F5D40(o->v50, dir);
    c = sub_0001D960(o, 0xD);
    if (!c)
        for (;;)
            ;
    sub_000EE270(c);
    c->fn24 = sub_00166C90;
    c->fn28 = sub_00166CE0;
    c->fn2C = sub_00166D70;
    sub_0001EBF0(o, 1);
    d = sub_0001D960(o, 9);
    if (!d)
        for (;;)
            ;
    d->flags4C = 0;
    d->i50 = 0;
    d->i58 = 0;
    d->f5C = 0.0f;
    d->fnB0 = sub_00166E20;
    d->fnB4 = sub_000AD090;
    d->fnB8 = sub_00102FA0;
    d->fnBC = sub_000AD090;
    d->fnC0 = sub_00102FA0;
    d->fnC4 = sub_00102FA0;
    d->fnD0 = sub_00102FA0;
    d->iCC = 0;
    d->iC8 = 0;
    init = b4c_sndTab279924[o->i08].init08;
    if (init && init(o, d, arg))
        return o;
    o->flags0C &= ~1u;
    sub_0001EB80(o);
    return 0;
}

/* 0x0016FE00: rebuild object o from template tmpl in place, keeping its position, direction,
   scale vector and the three transform blocks at +0xA0, +0xD8 and +0xF8.
   regargs: o=EBX tmpl=stack */
void rbg_Rebuild16FE00(RbgRec150 *o, const void *tmpl)
{
    float v70[4], v50[4], v60[4];
    uint32_t bA0[14], bD8[8], bF8[11];

    sub_000F5D40(v70, o->v70);
    sub_000F5D40(v50, o->v50);
    sub_000F5D40(v60, o->pos60);
    RBG_COPYD(bA0, o->bA0, 14);
    RBG_COPYD(bD8, o->bD8, 8);
    RBG_COPYD(bF8, o->bF8, 11);
    sub_000362B0(o);
    sub_0001EB80(o);
    sub_00022380(o, tmpl, r3_ctx42C8E4);
    sub_0001E9B0(r3_ctx42C8E4, o, o->i14C, 5, 0x11);
    o->flags10 = 0;
    sub_0001EBF0(o, 1);
    RBG_COPYD(o->bA0, bA0, 14);
    RBG_COPYD(o->bD8, bD8, 8);
    RBG_COPYD(o->bF8, bF8, 11);
    sub_000F5D40(o->v70, v70);
    sub_000F5D40(o->v50, v50);
    sub_000F5D40(o->pos60, v60);
}
