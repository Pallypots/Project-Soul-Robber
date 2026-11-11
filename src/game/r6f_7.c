/* Area r6f: sound and timing helpers around 0x00088FB0-0x0008A4A8 (r6f_7). Names inferred. */
#include "r6f.h"

/* 0x00088FB0: take the pending entry with the smallest time (below 1000000)
   from the list at 0x003ED27C: copy its position into dst and release it. */
int r6f_PendingPopEarliest(void *dst)
{
    R6fPending *p, *best = 0;
    int lim = 1000000;
    for (p = r6f_pendingList3ED27C; p; p = p->next) {
        if ((float)lim > p->time) {
            lim = (int)p->time;
            best = p;
        }
    }
    if (!best)
        return 0;
    sub_000F5D40(dst, (uint8_t *)r6f_posTable3ED518 + best->index * 16);
    sub_0003D8C0(best);
    return 1;
}

/* 0x00089460: compute once (flag 4) the largest value of the type-1 children of o.
   regargs: o=EBX */
void r6f_BoxCalcMax(R6fBox *o)
{
    float m;
    R6fTask *n;
    float *v;
    if (!(o->flags & 4)) {
        m = 0.0f;
        for (n = o->list; n; n = (R6fTask *)sub_0007F300(n)) {
            v = (float *)sub_0008B0C0(n);
            if (sub_0008B0D0(n) == 1 && *v > m)
                m = *v;
        }
        o->max = m;
        o->flags |= 4;
    }
}

/* 0x000894E0: clamp the values of all children of o to its maximum.
   calls 0x00089460 with EBX=o */
void r6f_BoxClampToMax(R6fBox *o)
{
    float m;
    R6fTask *n;
    float *v;
    if (o->list) {
        sub_00089460(o);
        m = o->max;
        for (n = o->list; n; n = (R6fTask *)sub_0007F300(n)) {
            v = (float *)sub_0008B0C0(n);
            if (*v > m)
                *v = m;
        }
    }
}

/* 0x00089E70: sound task step: while the reference is shown (0x100) and not
   muted (0x200) play sound id+50; otherwise clear the playing flag. */
int r6f_TaskSoundStep(R6fTask *t, void *ref)
{
    R6fWorkI *w = (R6fWorkI *)t->work;
    if (!w)
        return -1;
    if (sub_000896D0(ref, 0x100)) {
        if (!sub_000896D0(ref, 0x200)) {
            if (sub_00048A00(w->i10 + 0x32, (int)w->u14.f) == -1)
                return -1;
        }
        return 0;
    }
    t->f18.u &= ~2;
    return 0;
}

/* 0x0008A440: link the material of the node found for t to the material of the
   type-8 node (keys +0x10..+0x18 of t's work) of x; else clear t's flag 2. */
int r6f_TaskLinkMat(R6fTask *t, R6eArg20 *x)
{
    R6fWorkI *w = (R6fWorkI *)t->work;
    R6fTask *m, *r;
    m = sub_0008AFA0(t);
    if (m) {
        r = sub_0008E5E0(x->i20, w->i10, w->u14.i, w->i18);
        if (r && r->p28 && m->p28) {
            sub_0007E5C0(r->p28, w->i1C, w->i20, m->p28);
            return 0;
        }
    }
    t->f18.u &= ~2;
    return 0;
}
