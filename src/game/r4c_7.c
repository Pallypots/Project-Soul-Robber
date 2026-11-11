/* Area r4c: dynamic record and timed effect callbacks around 0x00197CE0-0x00199500 (r4c_7). Names inferred. */
#include "r4c.h"

/* 0x00197CE0: clear the dynamic record tables at 0x00401830/28/2C (4, 6 and 6 entries). No inputs. */
void r4c_DynRecsReset(void)
{
    int i;
    if (r4c_g401830)
        for (i = 0; i < 4; i++) {
            r4c_g401830[i].obj = 0;
            r4c_g401830[i].i4 = 0;
            r4c_g401830[i].i8 = -1;
        }
    if (r4c_g401828)
        for (i = 0; i < 6; i++) {
            r4c_g401828[i].obj = 0;
            r4c_g401828[i].i4 = -1;
        }
    if (r4c_g40182C)
        for (i = 0; i < 6; i++)
            r4c_g40182C[i].obj = 0;
}

/* 0x00197D90: stop callback of a dynamic-record effect (kinds 0x11, 10, 0x1E); returns 1 when stopped. Stack args (o a). */
int r4c_DynStop(R4cNode *o, R4cActor *a)
{
    if (!(o->flagsC & 1))
        return 0;
    if (o->kind == 0x11) {
        if (!r4c_g401830)
            return 0;
        ((R4cRec40 *)a->work)->i4 = 0;
        ((R4cRec40 *)a->work)->i8 = -1;
    } else if (o->kind == 10) {
        if (!r4c_g401828)
            return 0;
        ((R4cRec44 *)a->work)->i4 = -1;
    } else if (o->kind == 0x1E) {
        if (!r4c_g40182C)
            return 0;
    } else {
        return 0;
    }
    ((R4cRec70 *)a->work)->obj = 0;
    a->work = 0;
    sub_0001EB80(o);
    o->flagsC &= ~1u;
    o->flags10 |= 0x44D;
    return 1;
}

/* 0x00198330: bind node o to a free 0x0040182C record and install its callbacks; returns 1 on success.
   Stack args (o a x). Calls 0x001977A0 with the record on the stack and ECX=x. */
int r4c_DynBind(R4cNode *o, R4cActor *a, int x)
{
    R4cRec70 *r;
    int i;
    for (i = 0; i < 6; i++)
        if (r4c_g40182C[i].obj == 0)
            goto found;
    return 0;
found:
    r = &r4c_g40182C[i];
    if (i >= 6)
        return 0;
    r->obj = o;
    a->work = r;
    o->flagsC = (o->flagsC & ~0xE0u) | 1;
    o->flags10 |= 0x44D;
    sub_001977A0(r, x);
    a->p84 = r4c_g32C870;
    a->p88 = r4c_g32C874;
    a->fn78 = r4c_DynStop;
    a->fn7C = sub_00198020;
    sub_0001D7A0(o);
    sub_00189DA0(o, a, 0);
    return 1;
}

/* 0x001983E0: clear the eight 0x00401838 records and the eight 0x00401918 slots. No inputs. */
void r4c_ClearRecs401838(void)
{
    int i;
    for (i = 0; i < 8; i++) {
        r4c_recs401838[i].f0 = 0;
        r4c_recs401838[i].f4 = 0;
        r4c_recs401918[i].obj = 0;
    }
}

/* 0x00198810: stop a timed effect: velocity (work +0x0C) = 0 * frame time. Stack args (unused a). */
void r4c_TimedStopW(void *unused, R4cActor *a)
{
    R4cTimedW *w = (R4cTimedW *)a->work;
    w->v0C[0] = r4c_frameSeconds * 0.0f;
    w->v0C[1] = r4c_frameSeconds * 0.0f;
    w->v0C[2] = r4c_frameSeconds * 0.0f;
    w->v0C[3] = r4c_frameSeconds * 0.0f;
}

/* 0x00198860: fade part 2 of o over the time at 0x0032C8DC, then free o. Stack args (o a). */
void r4c_TimedFadePart(R4cNode *o, R4cActor *a)
{
    R4cPart *p;
    if (r4c_g32C8DC >= a->f6C) {
        p = (R4cPart *)sub_0001D0F0(o, 2);
        p->v30[2] = (r4c_g32C8DC - a->f6C) / r4c_g32C8DC * p->v30[2];
    } else {
        sub_000ED780(o);
    }
}

/* 0x001988C0: grow o in two phases (0x0032C8F8, 0x0032C900), then hold and switch to state 2. Stack args (o a). */
void r4c_TimedGrow(R4cNode *o, R4cActor *a)
{
    float t1 = r4c_g32C8F8;
    float s;
    if (t1 >= a->f6C) {
        s = r4c_g32C8FC / t1 * r4c_g32C8CC * a->f6C;
        o->scale70[2] = s;
        o->scale70[1] = s;
        o->scale70[0] = s;
        return;
    }
    if (r4c_g32C900 >= a->f6C) {
        s = ((a->f6C - t1) / t1 * (r4c_g32C904 - r4c_g32C8FC) + r4c_g32C8FC) * r4c_g32C8CC;
        o->scale70[2] = s;
        o->scale70[1] = s;
        o->scale70[0] = s;
        return;
    }
    s = r4c_g32C8CC;
    o->scale70[2] = s;
    o->scale70[1] = s;
    o->scale70[0] = s;
    sub_00189DA0(o, a, 2);
    ((R4cTimedW *)a->work)->i04 = 0;
}

/* 0x00198980: stop a timed effect (velocity at work +0x08) and set its X scale from 0x0032C908. Stack args (o a). */
void r4c_TimedStopV6(R4cNode *o, R4cActor *a)
{
    R4cTimedV *w = (R4cTimedV *)a->work;
    w->v08[0] = r4c_frameSeconds * 0.0f;
    w->v08[1] = r4c_frameSeconds * 0.0f;
    w->v08[2] = r4c_frameSeconds * 0.0f;
    w->v08[3] = r4c_frameSeconds * 0.0f;
    o->scale70[0] = r4c_g32C908;
}

/* 0x00198AF0: stop a timed effect (velocity at work +0x08). Stack args (unused a). */
void r4c_TimedStopV(void *unused, R4cActor *a)
{
    R4cTimedV *w = (R4cTimedV *)a->work;
    w->v08[0] = r4c_frameSeconds * 0.0f;
    w->v08[1] = r4c_frameSeconds * 0.0f;
    w->v08[2] = r4c_frameSeconds * 0.0f;
    w->v08[3] = r4c_frameSeconds * 0.0f;
}

/* 0x00198CA0: shrink part 2, the model's +0xDC value and o's scale over their times, then free o. Stack args (o a). */
void r4c_TimedShrink(R4cNode *o, R4cActor *a)
{
    R4cPart *p;
    float k, inv, t2, t3;
    if (r4c_g32C920 >= a->f6C) {
        p = (R4cPart *)sub_0001D0F0(o, 2);
        k = r4c_g32C920;
        inv = 1.0f / k;
        p->v30[0] = (k - a->f6C) * p->v30[0] * inv;
        p->v30[1] = (k - a->f6C) * p->v30[1] * inv;
        p->v30[2] = (k - a->f6C) * p->v30[2] * inv;
    }
    t2 = r4c_g32C918;
    if (t2 > a->f6C) {
        R4cModelX *m = (R4cModelX *)o->p20;
        m->fDC = (t2 - a->f6C) / t2 * m->fDC;
    }
    t3 = r4c_g32C91C;
    if (t3 > a->f6C) {
        float s = (t3 - a->f6C) / t3 * r4c_g32C8CC;
        o->scale70[2] = s;
        o->scale70[1] = s;
        o->scale70[0] = s;
    }
    if (t2 > t3)
        t3 = t2;
    if (a->f6C >= t3)
        sub_000ED780(o);
}

/* 0x00198F90: bind node o to a free 0x00401918 slot, install its callbacks and start it; returns 1 on success. Stack args (o a). */
int r4c_RecB18Bind(R4cNode *o, R4cActor *a)
{
    R4cRecB18 *r;
    int h;
    for (r = r4c_recs401918; r < r4c_recs401918 + 8; r++)
        if (r->obj == 0)
            goto found;
    return 0;
found:
    r->obj = o;
    a->work = r;
    a->p84 = r4c_g32C88C;
    a->p88 = r4c_g32C8B4;
    a->fn78 = sub_001984A0;
    a->fn7C = sub_00198640;
    a->fn80 = sub_001987B0;
    o->scale70[2] = 0.0f;
    o->scale70[1] = 0.0f;
    o->scale70[0] = 0.0f;
    o->scale70[3] = 1.0f;
    a->i24 = 1;
    o->i124 = 1;
    h = sub_0001BC40(o);
    o->fB0 = 0.0f;
    o->fB4 = 0.0f;
    o->fE8 = 0.0f;
    o->iD0 = h;
    o->iEC = 0;
    o->i118 = 0;
    o->v108[1] = -5.0f;
    o->flagsC &= ~0x60u;
    o->flags10 |= 0x45;
    sub_00189DA0(o, a, 1);
    ((R4cRecB18 *)a->work)->i8 = 0;
    return 1;
}

/* 0x00199460: stop a timed effect, play its sound and attach it at the camera point. Stack args (o a).
   Calls 0x00198DA0 with ESI=point EDI=o. */
void r4c_TimedAttachCam(R4cNode *o, R4cActor *a)
{
    R4cTimedW *w = (R4cTimedW *)a->work;
    float v[4];
    void *h;
    w->v0C[0] = r4c_frameSeconds * 0.0f;
    w->v0C[1] = r4c_frameSeconds * 0.0f;
    w->v0C[2] = r4c_frameSeconds * 0.0f;
    w->v0C[3] = r4c_frameSeconds * 0.0f;
    sub_000494D0(0x1DE, o->pos, 0);
    r4c_CamPoint(v, o);
    h = sub_00036750(o, 3);
    w->i04 = h;
    sub_00034CF0(h, v[0], v[1], v[2], v[3]);
}
