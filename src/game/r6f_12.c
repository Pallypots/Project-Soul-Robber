/* Area r6f: task key search, ordering and target helpers around 0x0008B210-0x0008E777 (r6f_12). Names inferred. */
#include "r6f.h"

/* 0x0008B210: from n on, find the first node whose work matches the key of m
   in all mask bits (2 time, 4 kind, 8 sub, 0x10 object). */
R6fTask *r6f_TaskFindKey(R6fTask *n, R6fKeyMsg *m, uint32_t mask)
{
    R6fKey *key = m ? m->key : 0;
    R6fKey *w;
    uint32_t r;
    if (!n)
        return n;
    do {
        r = 0;
        w = (R6fKey *)n->work;
        if (w && key) {
            if (w->f00 == key->f00)
                r = 2;
            if (w->kind04 == key->kind04)
                r |= 4;
            if (w->sub05 == key->sub05)
                r |= 8;
            if (w->p08 == key->p08)
                r |= 0x10;
        }
        if ((r & mask) == mask)
            break;
        n = (R6fTask *)sub_0007F300(n);
    } while (n);
    return n;
}

/* 0x0008B320: order two task nodes by time, kind, object id, sub and the
   word at +0x0C (-1, 0 or 1; nodes without work sort last). */
int r6f_TaskOrder(R6fTask *a, R6fTask *b)
{
    R6fKey *wa, *wb;
    if (a == b)
        return 0;
    if (!a || !(wa = (R6fKey *)a->work))
        return 1;
    if (!b || !(wb = (R6fKey *)b->work))
        return -1;
    if (wa->f00 > wb->f00)
        return 1;
    if (wb->f00 > wa->f00)
        return -1;
    if (wa->kind04 > wb->kind04)
        return 1;
    if (wa->kind04 < wb->kind04)
        return -1;
    if (wa->p08 && wb->p08) {
        if (((R6fIdObj *)wa->p08)->id > ((R6fIdObj *)wb->p08)->id)
            return 1;
        if (((R6fIdObj *)wa->p08)->id < ((R6fIdObj *)wb->p08)->id)
            return -1;
    }
    if (wa->sub05 > wb->sub05)
        return 1;
    if (wa->sub05 < wb->sub05)
        return -1;
    if (wa->u0C > wb->u0C)
        return 1;
    return wa->u0C < wb->u0C ? -1 : 0;
}

/* 0x0008BDC0: once the target's start time is reached, set the target of the
   object from this node's time and the next matching node's time. */
int r6f_TaskTimedTarget(R6fTask *t)
{
    R6fKey *w = (R6fKey *)t->work;
    R6fTimedObj *o = (R6fTimedObj *)w->p08;
    R6fKey *w2;
    R6fKey key;
    R6fKeyMsg msg;
    R6fTask *n;
    if (!o)
        return -1;
    sub_0007F1E0(&msg, 0, 0x20);
    sub_0007F1E0(&key, 0, 0x10);
    msg.key = &key;
    key.kind04 = ((R6fKey *)t->work)->kind04;
    key.sub05 = ((R6fKey *)t->work)->sub05;
    key.p08 = ((R6fKey *)t->work)->p08;
    n = (R6fTask *)sub_0008B210((R6fTask *)sub_0007F300(t), &msg, 0x1C);
    if (!n || !(w2 = (R6fKey *)n->work))
        w2 = w;
    if (w->f00 >= o->start) {
        sub_0008F0E0(o, w->i10, w->f00, w2->f00);
        sub_0008F140(o);
    }
    return 0;
}

/* 0x0008BE80: copy the material of t's active target into the type-8 node
   with the same id fields under x and restart it; else clear t's flag 2. */
int r6f_TaskCopyMat(R6fTask *t, R6fRangeArg *x)
{
    R6fTask *m, *r;
    int id, v;
    m = sub_0008AFA0(t);
    if (!m || !(m->f18.b0 & 2)) {
        t->f18.u &= ~2;
        return 0;
    }
    id = (int)(intptr_t)m->work;
    r = sub_0008E5E0(sub_000893B0(x), (id >> 20) & 0xFF, (id >> 8) & 0xFFF, id & 0xFF);
    if (r && r->p28 && m->p28) {
        sub_0007ED10(r->p28, m->p28);
        v = *((R6fMat *)m->p28)->p1C;
        r->p3C = (void *)(intptr_t)v;
        sub_0007E9B0(r->p28, v);
        if (x->f10 > x->f0C)
            sub_0008E3D0((R6eTask *)r, 0);
        return 0;
    }
    t->f18.u &= ~2;
    return 0;
}

/* 0x0008E6F0: task handler: while the reference shows (0x400), sync the task
   to it, refresh and set the animation speed from the task's ramp (1.0 without one). */
int r6f_TaskSyncSpeed(R6eTask *t, R6fRefObj *ref)
{
    float v;
    if (t->p28 && ((R6eAnimRef *)t->p28)->i5C && sub_000896D0(ref, 0x400)) {
        sub_0008E6A0(t);
        sub_0008DE70(t, ref->i10, sub_00089450(ref));
        if (t->p120)
            v = sub_00090480(t->p120, ref->i10);
        else
            v = 1.0f;
        sub_000EE6D0(((R6eAnimRef *)t->p28)->i5C, v);
    }
    return 0;
}
