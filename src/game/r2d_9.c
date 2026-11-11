/* Area r2d, group 9: height sync and switch toggles (0x000EDF90..0x000EFA26). Names inferred. */
#include "r2d.h"

/* 0x000EDF90: copy the height for (kind, id) from the 0x171D50 table into
   the object's matching component (kinds 2 and 4 at +0x270, kind 8 at
   +0x70). */
void r2d_ObjSyncHeight(R2dKObj *o)
{
    R2dKComp *c;
    R2dKDst *d;
    float f;
    c = (R2dKComp *)sub_0001D960(o, 0xD);
    if (!c)
        return;
    d = (R2dKDst *)sub_0001D960(o, sub_000EE5F0(o));
    if (!d)
        return;
    switch (o->kind04) {
    case 2:
    case 4:
        f = sub_00171D50(o->kind04, o->id08, c->v34);
        d->f270 = f;
        d->f274 = f;
        break;
    case 8:
        f = sub_00171D50(o->kind04, o->id08, c->v34);
        d->f74 = f;
        d->f70 = f;
        break;
    }
}

/* 0x000EF930: switch o on (component 5 +0xE4) and post game event 4 with -1.
   regargs: o=EBX */
void r2d_SwitchOn(void *o)
{
    R2dSwComp *c = (R2dSwComp *)sub_0001D960(o, 5);
    R2dGame *g;
    if (c->vE4)
        return;
    g = sub_000E0770();
    c->vE4 = 1;
    c->vDC = 0;
    sub_000F3B30(o, 1);
    sub_000E0A80(g, 4, g->v000, g->v314, -1);
    g->v308 = 0;
    g->v30C = 0;
    sub_000E51F0(g);
    sub_000E0FB0(0);
}

/* 0x000EF9B0: switch o off and post game event 4 with 0 (mode 2, step 9).
   regargs: o=EBX */
void r2d_SwitchOff(void *o)
{
    R2dSwComp *c = (R2dSwComp *)sub_0001D960(o, 5);
    R2dGame *g;
    if (!c->vE4)
        return;
    g = sub_000E0770();
    c->vE4 = 0;
    c->vDC = 1;
    sub_000F3B00(o, 1);
    sub_000E0A80(g, 4, g->v000, g->v314, 0);
    g->v308 = 2;
    g->v30C = 9;
    sub_000E51F0(g);
    sub_000E0FB0(1);
}

/* 0x000ED430: reset the object queues and node pools, then the subsystems
   that use them. */
void r2d_QueuesReset(void)
{
    int i;
    sub_0003D860(&r2d_q3F5DC0);
    sub_0003D860(&r2d_q3F5DB0);
    sub_0003D860(&r2d_q3F60D0);
    for (i = 0; i < 48; i++)
        sub_0003D860(&r2d_qpool3F5DD0[i]);
    for (i = 0; i < 8; i++)
        sub_0003D860(&r2d_qpool3F5D30[i]);
    sub_00112490();
    sub_000F31A0();
    sub_00174B40();
    sub_00189960();
    sub_00171F30();
    sub_0016F6F0();
    sub_001668D0();
    r2d_g3F60E0 = 0;
    r2d_g3F60E4 = 0;
}

/* 0x000EE660: scale the render parts of a node chain by f (kind 1 parts at
   +0xD8 and refreshed, kind 9 parts at +0xDC). */
void r2d_NodesScale(R2dSNode *n, float f)
{
    R2dSPart *p;
    for (; n; n = n->next3C) {
        p = n->part20;
        if (!p)
            continue;
        switch (p->kind8C) {
        case 1:
            p->fD8 = n->f9C * f;
            sub_001B3160(p);
            break;
        case 9:
            p->fDC = n->f9C * f;
            break;
        }
    }
}
