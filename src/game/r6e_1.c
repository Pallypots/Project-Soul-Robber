/* Area r6e: script process and task helpers around 0x0008B700-0x0008DE2A (r6e_1). Names inferred. */
#include "r6e.h"

/* 0x0008B700: copy the work block of src into dst (size from the kind table) and
   take a reference on its object. */
int r6e_TaskCopyWork(R6eTask *src, R6eTask *dst)
{
    R6eWork *s = src->work;
    int sub = s->sub05;
    R6eWork *d = dst->work;
    sub_0007F210(d, s, a8b_descGetters[s->kind04]()[sub].size);
    d->p08 = 0;
    d->p08 = s->p08;
    if (s->p08)
        a8b_RefInc(s->p08);
    return 0;
}

/* 0x0008B780: append b after a (or start with b) and finish the chain with 0x0008B560. */
void *r6e_ChainAppendB(void *a, void *b)
{
    if (!b)
        return a;
    if (a) {
        sub_0007F3F0(a, b);
        return sub_0008B560(a);
    }
    return sub_0008B560(b);
}

/* 0x0008B980: create a task node (heap 4, 0x20 bytes) and initialise it; NULL on failure. */
void *r6e_TaskCreate(int a, int b)
{
    void *n;
    sub_0007F4A0(4, sub_0008BCD0(sub_0008BD00(4)));
    n = sub_0007F240(0, 0x20, 0x1B5, r6e_srcFile26FF8C);
    if (sub_0008B0E0(n, a, b)) {
        sub_0007F2B0(n);
        sub_0008B400(n);
        return 0;
    }
    return n;
}

/* 0x0008BC30: task handler: drop camera slot 0 and install the object of x. */
int r6e_TaskCamInstall(R6eTask *t, R6eArg44 *x)
{
    if (!t)
        return -1;
    if (!x || !t->work)
        return -1;
    if (sub_0003D090(0))
        sub_0003D0A0(0);
    if (x->i44)
        sub_0003D020(0, x->i44);
    return 0;
}

/* 0x0008BF70: free a list of task nodes that have no references, children first. */
int r6e_TaskFreeList(R6eTask *n)
{
    R6eTask *next;
    while (n) {
        next = (R6eTask *)sub_0007F300(n);
        if (!n->refs) {
            sub_0008BF70(sub_0007F320(n));
            sub_0007F2B0(n);
            a8b_opsGetters[n->type]()->destroy(n);
            sub_0007F3B0(n);
        }
        n = next;
    }
    return 0;
}

/* 0x0008C1F0: send an event to a list of task nodes until one handles it;
   clears the active bit of each node passed. */
int r6e_TaskSendAll(R6eTask *n, int arg)
{
    int (*fn)(R6eTask *, int);
    int r;
    if (!n)
        return -1;
    do {
        fn = a8b_opsGetters[n->type]()->event;
        if (fn) {
            r = fn(n, arg);
            if (r)
                return r;
        }
        n->f18.b &= ~2;
        n = (R6eTask *)sub_0007F300(n);
    } while (n);
    return 0;
}

/* 0x0008C240: send an event to the nodes of one heap until one handles it. */
int r6e_TaskSendHeap(R6eTask *n, int arg, int heap)
{
    int (*fn)(R6eTask *, int);
    int r;
    if (!n)
        return 0;
    do {
        if (n->heap == heap) {
            fn = a8b_opsGetters[n->type]()->event;
            if (fn) {
                r = fn(n, arg);
                if (r)
                    return r;
            }
        }
        n = (R6eTask *)sub_0007F300(n);
    } while (n);
    return 0;
}

/* 0x0008C290: do two task nodes refer to the same thing (same type and work block,
   and for type 5 the same byte +0x25)?
   regargs: a=ESI b=EDX */
uint8_t r6e_TaskSameTarget(R6eTask *a, R6eTask *b)
{
    uint8_t r = 0;
    if (a->type == b->type) {
        if (a->work == b->work)
            r = 1;
        if (a->type == 5 && a->u24.b[1] != b->u24.b[1])
            r = 0;
    }
    return r;
}

/* 0x0008C900: append b after a (or start with b) and finish the chain with 0x0008C5F0. */
void *r6e_ChainAppendC(void *a, void *b)
{
    if (!b)
        return a;
    if (a) {
        sub_0007F3F0(a, b);
        return sub_0008C5F0(a);
    }
    return sub_0008C5F0(b);
}

/* 0x0008CB90: free a task tree: children and siblings first, then the node. */
int r6e_TaskFreeTree(R6eTask *n)
{
    int r;
    if (n) {
        r = r6e_TaskFreeTree((R6eTask *)sub_0007F300(n));
        if (r)
            return r;
        r = r6e_TaskFreeTree((R6eTask *)sub_0007F320(n));
        if (r)
            return r;
        *(uint32_t *)&n->f18 = 0;
        sub_0007F2B0(n);
        sub_0007F3B0(n);
    }
    return 0;
}

/* 0x0008CBE0: append a node to the end of a root list (or make it the root). */
int r6e_RootAppend(void **root, void *n)
{
    void *last;
    if (!root)
        return -1;
    if (!n)
        return -1;
    if (*root) {
        last = sub_0007F350(*root);
        if (!last)
            return -1;
        if (!sub_0007F3F0(last, n))
            return -1;
    } else {
        *root = n;
    }
    return 0;
}

/* 0x0008CCF0: create the 0x1C-byte root block in heap 3 and store v in it; -2 on failure. */
int r6e_RootCreate(void **root, void *v)
{
    void *b;
    if (!root)
        return -1;
    sub_0007F4A0(4, sub_0008BCD0(sub_0008BD00(3)));
    b = sub_0007F240(0, 0x1C, 0x3E, r6e_srcFile270054);
    *root = b;
    if (!b) {
        *root = b;
        return -2;
    }
    ((void **)b)[6] = v;
    return 0;
}

/* 0x0008CDC0: process step: stop the stream, free the stage object and switch the
   texture group; marks the process stopped. */
int r6e_ProcStopStage(R6eProc *p)
{
    int r;
    if (!(p->flags & 4)) {
        sub_00047BF0(100);
        r = sub_000897B0(p->ref);
        if (r)
            return r;
        p->ref = 0;
        sub_001BA0B0(p->w14);
        p->flags = (p->flags & ~8u) | 4;
    }
    return 0;
}

/* 0x0008D100: process step: when the game mode is 5 clear flag 0x200 of the
   reference, stamp it with the frame units and go to state 6. */
int r6e_ProcWaitMode5(R6eProc *p)
{
    if (sub_00047EE0() == 5) {
        sub_000896A0(p->ref, 0x200);
        p->ref->f14 = a50_frameUnits;
        p->state = 6;
        p->timer = 0;
    }
    return 0;
}

/* 0x0008D170: process step: wait for the reference, then when its flag 2 is set
   stop the stream and go to state 5. */
int r6e_ProcWaitFlag2(R6eProc *p)
{
    int r = sub_00089DD0(p->ref);
    if (r)
        return r;
    if (sub_000896D0(p->ref, 2)) {
        sub_00047BF0(100);
        p->state = 5;
        p->timer = 0;
    }
    return 0;
}

/* 0x0008D1F0: run the enter handler of a process state; on nonzero go to state 1. */
int r6e_ProcEnter(R6eProc *p)
{
    int r;
    if (!p)
        return 0;
    r = r6b_procStates[p->state].enter(p);
    if (r) {
        p->state = 1;
        p->timer = 0;
    }
    return r;
}

/* 0x0008D220: run a process until it stops, restarting it in state 1 whenever a
   step reports completion. */
void r6e_ProcRunToStop(R6eProc *p)
{
    while (!(p->flags & 4)) {
        if (r6b_procStates[p->state].step(p)) {
            p->state = 1;
            p->timer = 0;
        }
    }
}

/* 0x0008D250: run a process until done, then store v and go to state 2. */
void r6e_ProcFinish(R6eProc *p, int v)
{
    while (!(p->flags & 8))
        r6b_procStates[p->state].step(p);
    p->i10 = v;
    p->ref->i04 = v;
    p->state = 2;
    p->timer = 0;
}

/* 0x0008D340: the single process record, created on first use. */
R6eProc *r6e_ProcGet(void)
{
    R6eProc *p;
    if (!a8b_g3ED528) {
        a8b_g3ED528 = (R6eProc *)sub_0008BD80(sub_0008BD00(0), 4, 0x18, 0x8B, r6e_srcFile270114);
        if (!a8b_g3ED528)
            return 0;
        p = a8b_g3ED528;
        sub_0007F1E0(p, 0, 0x18);
        if (p) {
            p->state = 0;
            p->timer = 0;
        }
    }
    return a8b_g3ED528;
}

/* 0x0008D3D0: restart a process, run it until it stops and free it. */
void r6e_ProcRunFree(R6eProc *p)
{
    if (p) {
        p->state = 1;
        p->timer = 0;
        sub_0008D220(p);
        sub_000AD090();
        sub_0008BCC0(p);
        a8b_g3ED528 = 0;
    }
}

/* 0x0008D420: task handler: unless flag 0x200 is set, play the shock of the work block. */
int r6e_TaskShock(R6eTask *t, void *ref)
{
    R6eWork *w;
    if (!ref)
        return -1;
    w = t->work;
    if (!w)
        return -1;
    if (!sub_000896D0(ref, 0x200) && w->i14 >= 0)
        sub_0005EB10(w->u10.i, w->i14);
    return 0;
}

/* 0x0008D4A0: task handler: mark the work block started and bind the source object. */
int r6e_TaskBind(R6eTask *t, R6eArg20 *src)
{
    R6eWork *w = t->work;
    w->i24 = 1;
    w->u10.b = 1;
    if (src) {
        sub_0008B3B0(w, sub_0008C3C0(src->i20, 0x0D));
        return 0;
    }
    w->p08 = 0;
    return 0;
}

/* 0x0008D620: task handler: unless flag 0x200 is set, start the stream of the work
   block; -1 when there is none or it fails. */
int r6e_TaskStream(R6eTask *t, void *ref)
{
    R6eWork *w = t->work;
    if (!w)
        return -1;
    if (!sub_000896D0(ref, 0x200) && sub_00048AF0(w->u10.i) == -1)
        return -1;
    return 0;
}

/* 0x0008D670: release what a task holds (flag 1: object at +0x24, flag 2: list at +0x28). */
int r6e_TaskReleaseHeld(R6eTask *t)
{
    int r;
    if (!t)
        return -1;
    if (t->flags00 & 1)
        sub_0008B400(t->u24.p);
    if (t->flags00 & 2) {
        r = sub_0008BF70(t->p28);
        if (r)
            return r;
    }
    return 0;
}

/* 0x0008D7F0: look up a key and pass the result to 0x0008D780; -2 when not found. */
int r6e_TaskLookup(void *a, R6eKeyArg key)
{
    void *x;
    int r;
    if (!key.name)
        return -1;
    x = sub_0007F510(key.name, &key.size);
    if (!x)
        return -2;
    r = sub_0008D780(a, x, key.size);
    if (r < 0)
        return r;
    return 0;
}

/* 0x0008D8A0: copy the data part (+0x18 onwards) of one task into another. */
int r6e_TaskCopyData(R6eTask *dst, R6eTask *src)
{
    sub_0007F210(&dst->f18, &src->f18, sub_0008BF50(src->type)->size - 0x18);
    return 0;
}

/* 0x0008DB70: task handler: release the camera animation of an idle task. */
int r6e_TaskReleaseCam(R6eTask *t)
{
    if (t->state != 2)
        return -1;
    if (t->f18.b & 2) {
        sub_0007E240(t->p28);
        t->f18.b &= ~2;
        t->p28 = 0;
    }
    return 0;
}

/* 0x0008DBB0: argument parser: one word into +0x24; returns 4 or -1. */
int r6e_TaskArgWord(R6eTask *t, const int32_t *args, int n)
{
    if (!t)
        return -1;
    if (!args || n <= 0)
        return -1;
    t->u24.i = args[0];
    return n >= 4 ? 4 : -1;
}

/* 0x0008DBF0: copy 0xDC bytes of task data from src to dst and add a reference to
   the camera animation of src. */
int r6e_TaskCopyDC(R6eTask *dst, R6eTask *src)
{
    if (!dst)
        return -1;
    if (!src)
        return -1;
    sub_0007F210(&dst->f18, &src->f18, 0xDC);
    if (src->p28)
        sub_0007E190(src->p28);
    return 0;
}

/* 0x0008DD80: grow an array to hold n records (never shrinks below its count). */
void r6e_ArrGrow(R6eArr *a, uint32_t n)
{
    uint8_t *p;
    uint32_t bytes;
    if (a->count >= n)
        return;
    p = (uint8_t *)sub_00053AB0(a->stride * n, 0, 0x51);
    if (!p)
        return;
    bytes = a->count * a->stride;
#if defined(_M_IX86)
    __movsd((unsigned long *)p, (unsigned long *)a->data, bytes >> 2);
    __movsb(p + (bytes - (bytes & 3)), a->data + (bytes - (bytes & 3)), bytes & 3);
#else
    memcpy(p, a->data, bytes);
#endif
    sub_00053880(a->data);
    a->data = p;
    a->cap = n;
}

/* 0x0008DDE0: append one record to an array, doubling its capacity when full. */
void r6e_ArrPush(R6eArr *a, const void *rec)
{
    uint32_t cap = a->cap;
    uint8_t *d;
    uint32_t n;
    if (a->count == cap) {
        sub_0008DD80(a, cap * 2);
        if (cap == a->cap)
            return;
    }
    n = a->stride;
    d = a->data + a->count * n;
#if defined(_M_IX86)
    __movsd((unsigned long *)d, (const unsigned long *)rec, n >> 2);
    __movsb(d + (n - (n & 3)), (const uint8_t *)rec + (n - (n & 3)), n & 3);
#else
    memcpy(d, rec, n);
#endif
    a->count++;
}
