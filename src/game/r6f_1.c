/* Area r6f: script task tree helpers around 0x0008B010-0x0008C3BB (r6f_1). Names inferred. */
#include "r6f.h"

/* 0x0008B010: make a new task node with a copy of src's work block (copy handler
   of its kind); frees the node and returns the handler's error on failure. */
int r6f_TaskClone(R6fTask **out, R6fTask *src)
{
    R6fDesc *d;
    int kind, sub;
    int r;
    sub_0007F4A0(4, sub_0008BCD0(sub_0008BD00(4)));
    *out = (R6fTask *)sub_0007F240(0, 0x20, 0x10B, r6e_srcFile26FF8C);
    kind = src->work->kind04;
    sub = src->work->sub05;
    d = &((R6fDesc *)a8b_descGetters[kind]())[sub];
    (*out)->work = (R6eWork *)sub_0008BD80(sub_0008BD00(4), 4, d->size, 0x11F, r6e_srcFile26FF8C);
    (*out)->f18.u |= 1;
    r = d->copy(src, *out);
    if (r) {
        sub_0008BCC0((*out)->work);
        sub_0007F3B0(*out);
        *out = 0;
    }
    return r;
}

/* 0x0008B0E0: allocate and clear the work block of kind/sub for a task and run
   the kind's init handler; -1 when the kind has no block. */
int r6f_TaskInitWork(R6fTask *t, int kind, int sub)
{
    R6fDesc *d = (R6fDesc *)a8b_descGetters[kind]() + sub;
    R6eWork *w;
    int size, r;
    if (!t || !d || !d->p14)
        return -1;
    size = d->size;
    if (!size)
        return -1;
    w = (R6eWork *)sub_0008BD80(sub_0008BD00(4), 4, size, 0x22C, r6e_srcFile26FF8C);
    if (!w)
        return -1;
    sub_0007F1E0(w, 0, size);
    t->f18.u |= 1;
    t->work = w;
    w->kind04 = (int8_t)kind;
    w->sub05 = (int8_t)sub;
    if (d->init) {
        r = d->init(t, 0);
        if (r) {
            sub_0008BCC0(w);
            return r;
        }
    }
    return 0;
}

/* 0x0008B1A0: compare two task nodes with the compare handler of b's kind. */
int r6f_TaskCompare(R6fTask *a, R6fTask *b)
{
    int r = 0;
    R6fDesc *d;
    if (a == b)
        return 0;
    if (!a || !a->work)
        return 1;
    if (!b || !b->work)
        return -1;
    d = sub_0008AF80(b->work->kind04, b->work->sub05);
    if (d->compare)
        r = d->compare(a, b);
    return r;
}

/* 0x0008B290: find the next node of a given kind/sub from t (key search through 0x0008B210). */
R6fTask *r6f_TaskFindKind(R6fTask *t, int8_t kind, int8_t sub)
{
    R6fKey key;
    R6fKeyMsg m;
    if (!t)
        return 0;
    sub_0007F1E0(&m, 0, 0x20);
    sub_0007F1E0(&key, 0, 0x10);
    m.key = &key;
    key.kind04 = kind;
    key.sub05 = sub;
    return (R6fTask *)sub_0008B210(t, &m, 0xC);
}

/* 0x0008B400: free a chain of task nodes with their children, references and work blocks. */
void r6f_TaskFreeChain(R6fTask *n)
{
    R6fTask *next;
    R6eWork *w;
    if (!n)
        return;
    do {
        next = (R6fTask *)sub_0007F300(n);
        r6f_TaskFreeChain((R6fTask *)sub_0007F320(n));
        sub_0007F2B0(n);
        w = n->work;
        if (w->p08) {
            a8b_RefDec(w->p08);
            w->p08 = 0;
        }
        if (n->f18.u & 1) {
            sub_0008BCC0(n->work);
            n->f18.u &= ~1;
        }
        n->work = 0;
        sub_0007F3B0(n);
        n = next;
    } while (n);
}

/* 0x0008B680: for every reference in refs, re-resolve it in the list ctx and
   swap the new object into the work blocks of list that used the old one. */
int r6f_TaskRebindRefs(R6fTask *list, R6fTask *ctx, R6fTask *refs)
{
    R6fTask *nr, *t;
    R6eWork *w;
    if (refs) {
        do {
            nr = sub_0008C350(ctx, refs, 6);
            for (t = list; t; t = (R6fTask *)sub_0007F300(t)) {
                w = t->work;
                if (w && w->p08 == refs) {
                    if (w->p08)
                        a8b_RefDec(w->p08);
                    w->p08 = nr;
                    if (nr)
                        a8b_RefInc(nr);
                }
            }
            refs = (R6fTask *)sub_0007F300(refs);
        } while (refs);
    }
    return 0;
}

/* 0x0008B860: merge the node *src into *list: nodes of the same kind accepted
   by pred are removed (moved to *removed when given, else released). */
int r6f_TaskMerge(R6fTask **list, R6fTask **src, R6fTask **removed, R6fWorkPred pred)
{
    int r = 0;
    R6eWork *w;
    R6fTask *n, *hit, *t, *c;
    if (!list || !src)
        return -1;
    if (!*src)
        return 0;
    w = (*src)->work;
    n = *list;
    if (n) {
        do {
            n = sub_0008B290(n, w->kind04, w->sub05);
            if (!n)
                break;
            if (pred(w, n->work)) {
                hit = n;
                n = (R6fTask *)sub_0007F300(n);
                if (*list == hit)
                    *list = (R6fTask *)sub_0007F300(*list);
                if (removed) {
                    sub_0007F2B0(hit);
                    *removed = (R6fTask *)sub_0007F3F0(*removed, hit);
                } else {
                    sub_0008B760(hit);
                }
            } else {
                n = (R6fTask *)sub_0007F300(n);
            }
        } while (n);
    }
    t = *src;
    *src = 0;
    sub_0007F2B0(t);
    c = sub_0008B780(*list, t);
    if (!c) {
        r = -1;
    } else {
        *list = c;
        t = 0;
    }
    sub_0008B760(t);
    if (removed)
        *removed = (R6fTask *)sub_0007F330(*removed);
    return r;
}

/* 0x0008BD10: clear the two task globals and set the heaps of the seven task slots. */
int r6f_TaskHeapsInit(void)
{
    sub_0007F1E0(&r6f_g3ED524, 0, 4);
    sub_0007F1E0(&r6f_g428EFC, 0, 4);
    sub_0007F4A0(0, 4);
    sub_0007F4A0(1, 4);
    sub_0007F4A0(2, 4);
    sub_0007F4A0(3, 10);
    sub_0007F4A0(4, 4);
    sub_0007F4A0(5, 4);
    sub_0007F4A0(6, 4);
    return 0;
}

/* 0x0008C2C0: swap two nodes of a doubly linked list (adjacent or not). */
void r6f_DListSwap(R6fDNode *a, R6fDNode *b)
{
    R6fDNode *t;
    if (a->prev == b) {
        t = a;
        a = b;
        b = t;
    }
    if (a->next == b) {
        if (a->prev)
            a->prev->next = b;
        if (b->next)
            b->next->prev = a;
        a->next = b->next;
        b->prev = a->prev;
        a->prev = b;
        b->next = a;
        return;
    }
    if (a->next)
        a->next->prev = b;
    if (a->prev)
        a->prev->next = b;
    if (b->next)
        b->next->prev = a;
    if (b->prev)
        b->prev->next = a;
    t = a->prev;
    a->prev = b->prev;
    b->prev = t;
    t = a->next;
    a->next = b->next;
    b->next = t;
}

/* 0x0008C350: from n on, find the first node whose match bits against ref
   (2 = same type, 4 = same target) contain all of mask. */
R6fTask *r6f_TaskFindMatch(R6fTask *n, R6fTask *ref, uint32_t mask)
{
    uint32_t m;
    if (!n)
        return n;
    do {
        m = 0;
        if (ref) {
            if (n->f18.s.type == ref->f18.s.type) {
                m = 2;
                if (n->work == ref->work) {
                    m = 6;
                    if (n->f18.s.type == 5 && n->u24.b[1] != ref->u24.b[1])
                        m = 2;
                }
            } else if (n->work == ref->work) {
                m = 4;
            }
        }
        if ((m & mask) == mask)
            return n;
        n = (R6fTask *)sub_0007F300(n);
    } while (n);
    return n;
}
