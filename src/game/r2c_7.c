/* Area r2c, group 7: enemy hit and target helpers (0x0010A750..0x0011F062). Names inferred. */
#include "r2c.h"

/* 0x0010A750: with flag 0, hide obj, end its current state-component action
   (0x0F3D10) and switch it to mode 3 (0x0F3B70). Always returns 0. */
int r2c_DropTarget(void *obj, int flag)
{
    if (!flag) {
        R2cBossObj *c;
        sub_0001D700(obj);
        if (!obj)
            for (;;) ;
        c = (R2cBossObj *)sub_0001D960(obj, 5);
        if (c->v6C)
            sub_000F3D10(obj, c, 0);
        sub_000F3B70(obj, 3);
    }
    return 0;
}

/* 0x00110050: when o's animation part is in state 0x14 and its target has
   flag 2, put o and src's partner into mode 4 and run 0x10FD50 on o.
   Calls 0x0010FD50 with EAX=o. */
void r2c_HitFlash(R2cActor *o, R2cActor *src)
{
    R2cPart *p = o->p30;
    if (p->i08 == 0x14 && (sub_001AEE90(p->t14, 0) & 2)) {
        sub_000F3B30(o, 4);
        sub_000F3B30(src->pC8, 4);
        sub_0010FD50(o);
    }
}

/* 0x00112AA0: run the handler (+0x29C) of obj's kind-specific component;
   a positive result also triggers 0x025D50(1, 1). Returns the result, or 1
   for a negative one. Hangs on a null obj or missing component. */
int r2c_RunHandler(void *obj, int a)
{
    R2cHandler *h;
    int r;
    if (!obj)
        for (;;) ;
    h = (R2cHandler *)sub_0001D960(obj, sub_000EE5F0(obj));
    if (!h)
        for (;;) ;
    r = h->fn29C(obj, h, a);
    if (r > 0) {
        sub_00025D50(1, 1);
        return r;
    }
    if (r < 0)
        return 1;
    return r;
}

/* 0x00114A90: if 0x145940 accepts b's description values with c's range
   (+0x10, +0x14), apply c's value +0x18 through 0x1459D0. */
void r2c_DescTrigger(void *a, R2cActor *b, const R2cCmd *c)
{
    R2cDesc *d = b->p278;
    if (sub_00145940(a, d->vC, d->v14, c->v10, c->v14))
        sub_001459D0(a, d->vC, d->v14, c->v18);
}

/* 0x001154A0: pass every key of kind 2, sub-id 1 to 0x13DF90 together with p.
   regargs: p=ESI (passed on to 0x13DF90 as its second argument). */
void r2c_NotifyKind2(void *p)
{
    void *k;
    for (k = r2c_FindKey(2, 1); k; k = r2c_FindKey(-1, -1))
        sub_0013DF90(k, p);
}

/* 0x001183E0: when o's animation has finished, go to step 1.
   Calls 0x00117580 with stack (o, 1) and EDI=b. */
void r2c_AnimDoneStep(R2cActor *o, void *b)
{
    if (sub_000833E0(o->p30))
        sub_00117580(o, 1, b);
}

/* 0x00119970: when o's animation has finished, go to step 0x23 if b's
   description has flag 0x10, else step 1.
   Calls 0x00117580 with stack (o, step) and EDI=b. */
void r2c_AnimDoneStep23(R2cActor *o, R2cActor *b)
{
    R2cDesc *d = b->p278;
    if (sub_000833E0(o->p30)) {
        if (d->flags4 & 0x10)
            sub_00117580(o, 0x23, b);
        else
            sub_00117580(o, 1, b);
    }
}

/* 0x0011DCF0: 1 when the partner of boss form k (3 <-> 4) exists and
   neither it nor z is disabled or has description flag 0x20. */
int r2c_PartnerFree(const R2cKind *k, R2cActor *z)
{
    int sub;
    void *o;
    R2cActor *c;
    if (k->kind08 == 3)
        sub = 4;
    else if (k->kind08 == 4)
        sub = 3;
    else
        return 0;
    o = sub_000EDBE0(2, sub);
    if (!o)
        return 0;
    c = (R2cActor *)sub_0001D960(o, 4);
    if (!c)
        return 0;
    if ((z->b20 & 1) || (z->p278->flags4 & 0x20) || (c->b20 & 1) || (c->p278->flags4 & 0x20))
        return 0;
    return 1;
}

/* 0x0011EF60: pick a target for condition c and test it against Jack with
   0x145940 (c+0x10, +0x14). Calls 0x0011EE30 with EAX=c ECX=ctx and self on
   the stack. */
int r2c_TargetCheckPlayer(void *self, void *ctx, const R2cCmd *c)
{
    R2cActor *t = (R2cActor *)r2b_PickTargetB(c, ctx, self);
    if (!t)
        return 0;
    return sub_00145940(g_playerObj, t->v60, t->v68, c->v10, c->v14);
}

/* 0x0011EFD0: pick a target for condition c and test it against self with
   0x145940 (c+0x10, +0x14). Calls 0x0011EE30 with EAX=c ECX=ctx and self on
   the stack. */
int r2c_TargetCheck(void *self, void *ctx, const R2cCmd *c)
{
    R2cActor *t = (R2cActor *)r2b_PickTargetB(c, ctx, self);
    if (!t)
        return 0;
    return sub_00145940(self, t->v60, t->v68, c->v10, c->v14);
}

/* 0x0011F010: 1 when w's active key matches mode 1 (w->vF8 1, key kind 1,
   sub-id below 3) or mode 2 (w->vF8 1, key kind 0x0D). */
int r2c_KeyMatches(void *unused, R2cActor *w, const int *mode)
{
    R2cKeyRec *k = w->p104;
    int m;
    (void)unused;
    if (!k || !(k->flags0C & 1))
        return 0;
    m = *mode;
    if (m == 1 && w->vF8 == 1 && k->kind04 == 1 && k->v08 < 3)
        return 1;
    if (m == 2 && w->vF8 == 1 && k->kind04 == 0xD)
        return 1;
    return 0;
}
