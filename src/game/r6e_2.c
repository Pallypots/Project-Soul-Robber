/* Area r6e: script task handlers and small containers around 0x0008E0B0-0x00090577 (r6e_2). Names inferred. */
#include "r6e.h"

/* 0x0008E0B0: task handler: drop the resource and, for a running task, its tree. */
int r6e_TaskStopTree(R6eTask *t)
{
    sub_000904C0(t->p120);
    t->p120 = 0;
    switch (t->state) {
    case 1:
    case 3:
        break;
    default:
        return -1;
    }
    if (t->f18.b & 2) {
        sub_0007EB40(t->p28);
        t->f18.b &= ~2;
        t->p28 = 0;
    }
    return 0;
}

/* 0x0008E150: copy 0x110 bytes of task data and add references to what src holds. */
int r6e_TaskCopy110(R6eTask *dst, R6eTask *src)
{
    if (!dst)
        return -1;
    if (!src)
        return -1;
    sub_0007F210(&dst->f18, &src->f18, 0x110);
    if (src->p28)
        sub_0007E340(src->p28);
    if (src->p120)
        sub_00090410(src->p120);
    return 0;
}

/* 0x0008E200: drop the resource of a task and reset its animation speed to 1. */
void r6e_TaskDropRes(R6eTask *t)
{
    sub_000904C0(t->p120);
    t->p120 = 0;
    sub_000EE6D0(((R6eAnimRef *)t->p28)->p5C, 1.0f);
}

/* 0x0008E340: run 0x0008E240 for n items between two resource locks of channel ch.
   regargs: ch=EDI n=EBX; calls 0x0008E240 with ECX=i EDX=b */
int r6e_TaskRunItems(int a, void *b, void *ch, int n)
{
    int i;
    sub_0007E2D0(ch, 4);
    for (i = 0; i < n; i++)
        sub_0008E240(ch, a, i, b);
    sub_0007E310(ch, 4);
    return 0;
}

/* 0x0008E380: task handler: drop the resource and, for a running task, its tree; returns 0. */
int r6e_TaskStopTree2(R6eTask *t)
{
    sub_000904C0(t->p120);
    t->p120 = 0;
    switch (t->state) {
    case 1:
    case 3:
        if (t->f18.b & 2) {
            sub_0007EB40(t->p28);
            t->f18.b &= ~2;
            t->p28 = 0;
        }
        break;
    }
    return 0;
}

/* 0x0008E6A0: when the current reference value changed, store it and refresh the task. */
void r6e_TaskSyncRef(R6eTask *t)
{
    int v;
    if (((R6eAnimRef *)t->p28)->p5C) {
        v = sub_00089660(sub_00089390());
        if (t->i124 != v) {
            t->i124 = v;
            sub_0008E3D0(t, sub_000896D0(sub_00089390(), 0x200));
        }
    }
}

/* 0x0008E7E0: task handler for event bit 0x1000: detach the current reference. */
int r6e_TaskEvDetach(R6eTask *t, const uint32_t *ev)
{
    if (*ev & 0x1000) {
        if (t->u24.i & 1) {
            if (t->p28)
                sub_00089740(sub_00089390(), t);
            t->u24.i &= ~1;
        }
    }
    return 0;
}

/* 0x0008E820: task handler: release the material of an idle task when it is
   still the one installed on ref. */
int r6e_TaskReleaseMat(R6eTask *t, void *ref)
{
    if (!ref)
        return -1;
    if (t->state != 2)
        return -1;
    if (t->f18.b & 2) {
        if (sub_000897A0(ref) == t)
            sub_00089740(ref, 0);
        t->f18.b &= ~2;
        t->p28 = 0;
    }
    return 0;
}

/* 0x0008E880: argument parser: one word with bit 0 cleared into +0x24; returns 4 or -3. */
int r6e_TaskArgWordEven(R6eTask *t, const int32_t *args, int n)
{
    if (!args || n <= 0)
        return -1;
    t->u24.i = args[0] & ~1;
    return n >= 4 ? 4 : -3;
}

/* 0x0008EA90: free the block at +0x3C and the effect list at +0x28. */
int r6e_TaskFreeFx(R6eTask *t)
{
    if (!t)
        return -1;
    sub_00053880(t->p3C);
    t->p3C = 0;
    sub_000341C0(&t->p28);
    return 0;
}

/* 0x0008EAC0: start (flag 1) or stop the effect list of a task, tracking it in flag 2. */
int r6e_TaskFxToggle(R6eTask *t, int arg)
{
    uint32_t f;
    if (!t || !arg)
        return -1;
    f = t->u24.u;
    if (f & 1) {
        if (f & 2)
            return 0;
        if (sub_000341E0(&t->p28))
            return -1;
        t->u24.u |= 2;
        return 0;
    }
    if (f & 2) {
        sub_000342A0();
        t->u24.u &= ~2u;
    }
    return 0;
}

/* 0x0008EC10: argument parser: one word into +0x24; returns 4 or -1. */
int r6e_TaskArgWord2(R6eTask *t, const int32_t *args, int n)
{
    if (!args || n <= 0)
        return -1;
    t->u24.i = args[0];
    return n >= 4 ? 4 : -1;
}

/* 0x0008EC40: copy 0x28 bytes of task data, then clear and release the effect list of src. */
int r6e_TaskMoveFx(R6eTask *dst, R6eTask *src)
{
    if (!dst)
        return -1;
    if (!src)
        return -1;
    sub_0007F210(&dst->f18, &src->f18, 0x28);
    sub_0007F1E0(&src->p28, 0, 0x14);
    sub_000341C0(&src->p28);
    return 0;
}

/* 0x0008EC90: task descriptor getter. */
uint8_t *r6e_GetDesc270340(void) { return r6b_desc270340; }

/* 0x0008ED10: reset a task to idle and clear +0x24; returns 0. */
int r6e_TaskIdleClear24(R6eTask *t)
{
    t->state = 2;
    t->u24.i = 0;
    return 0;
}

/* 0x0008ED30: task handler: release the held block of an idle task. */
int r6e_TaskReleaseHold(R6eTask *t)
{
    if (t->state != 2)
        return -1;
    if (t->f18.b & 2) {
        sub_0008FFB0(&t->p28);
        t->u24.i &= ~2;
        t->f18.w &= ~2;
    }
    return 0;
}

/* 0x0008EEA0: task descriptor getter. */
uint8_t *r6e_GetDesc270380(void) { return r6b_desc270380; }
/* 0x0008EEB0: task descriptor getter. */
uint8_t *r6e_GetDesc2703A4(void) { return r6b_desc2703A4; }

/* 0x0008EEC0: task handler for event bit 0x800: install the object as camera 1. */
int r6e_TaskEvCam1(R6eTask *t, const uint32_t *ev)
{
    if (!(*ev & 0x800))
        return 0;
    if (t->u24.i & 1) {
        if (sub_0003D090(1))
            sub_0003D0A0(1);
        if (t->p28) {
            sub_0003D020(1, t->p28);
            sub_0003D100(1);
        }
        t->u24.i &= ~1;
    }
    return 0;
}

/* 0x0008EF20: task handler: remove an idle task's object from camera 1 and free it
   when owned. */
int r6e_TaskCam1Release(R6eTask *t)
{
    if (t->state != 2)
        return -1;
    if (t->f18.b & 2) {
        if (sub_0003D090(1) == t->p28)
            sub_0003D0A0(1);
        if (t->u24.i & 2) {
            sub_0008BCC0(t->p28);
            t->u24.i &= ~2;
        }
        t->f18.b &= ~2;
        t->p28 = 0;
    }
    return 0;
}

/* 0x0008EF80: argument parser: one word with bits 0-1 cleared into +0x24; returns 4 or -1. */
int r6e_TaskArgWordAlign4(R6eTask *t, const int32_t *args, int n)
{
    if (!t)
        return -1;
    if (!args || n <= 0)
        return -1;
    t->u24.i = args[0] & ~3;
    return (uint32_t)n < 4 ? -1 : 4;
}

/* 0x0008F110: reset a task to idle with no target and both scales at -1. */
int r6e_TaskResetTarget(R6eTask *t)
{
    t->state = 2;
    t->u24.i = 0;
    t->p28 = 0;
    t->i2C = -1;
    t->u30.f = -1.0f;
    t->f34 = -1.0f;
    return 0;
}

/* 0x0008F140: show the menu line of a task (or close it when it has none). */
void r6e_TaskMenuLine(R6eTask *t)
{
    if (t->p28 && (t->u24.i & 1)) {
        if (t->i2C >= 0) {
            sub_000186A0(3, t->p28);
            sub_00018580(3, t->i2C, 0x10, 20.0f, -1.0f);
            t->u24.i &= ~1;
        } else {
            sub_00018610();
            t->u24.i &= ~1;
        }
    }
}

/* 0x0008F1D0: copy 0x20 bytes of task data from src to dst and clear src +0x28. */
int r6e_TaskCopy20(R6eTask *dst, R6eTask *src)
{
    if (!dst)
        return -1;
    if (!src)
        return -1;
    sub_0007F210(&dst->f18, &src->f18, 0x20);
    src->p28 = 0;
    return 0;
}

/* 0x0008F5E0: task handler: for an idle or waiting task pass a to 0x0008F350. */
int r6e_TaskPass(R6eTask *t, void *a)
{
    if (t) {
        switch (t->state) {
        case 2:
        case 4:
            break;
        default:
            return -1;
        }
        sub_0008F350(a, t);
    }
    return 0;
}

/* 0x0008F620: task handler: replace the node at +0x28 by its root and release the
   node made from a (idle or waiting tasks only). */
int r6e_TaskReroot(R6eTask *t, int a)
{
    void *v = 0;
    switch (t->state) {
    case 2:
    case 4:
        v = sub_0008F430(a);
        break;
    }
    t->p28 = sub_0007F370(t->p28);
    sub_0007EC20(v);
    return 0;
}

/* 0x0008F6B0: activate an idle task in its heap (task checked). */
int r6e_TaskActivateChecked(R6eTask *t, int a)
{
    if (!t || !a)
        return -1;
    if (t->state != 2)
        return -1;
    if (!(t->f18.b & 2)) {
        sub_0007F4A0(2, sub_0008BCD0(t->heap));
        t->f18.w = (t->f18.w & ~0xC) | 2;
    }
    return 0;
}

/* 0x0008F750: activate an idle task in its heap. */
int r6e_TaskActivate(R6eTask *t, int a)
{
    if (!a)
        return -1;
    if (t->state != 2)
        return -1;
    if (!(t->f18.b & 2)) {
        sub_0007F4A0(2, sub_0008BCD0(t->heap));
        t->f18.w = (t->f18.w & ~0xC) | 2;
    }
    return 0;
}

/* 0x0008F970: advance *it until the predicate accepts a node or it reaches *end;
   returns the node. */
R6eLink *r6e_ListFindIf(R6eLink **it, R6eLink **end, R6ePred *p)
{
    while (*it != *end) {
        if (p->fn(p, *it))
            break;
        *it = (*it)->next;
    }
    return *it;
}

/* 0x0008FC50: predicate: does the node's table entry carry keys a and b? */
uint8_t r6e_PredMatch(R6ePred *p, R6eLinkNode *n)
{
    void *e = 0;
    uint8_t r = 0;
    if (n->p08)
        e = sub_0001D220(n->p08, 0);
    if (p->a == sub_000894D0(e)) {
        e = 0;
        if (n->p08)
            e = sub_0001D220(n->p08, 0);
        if (p->b == sub_001BBDD0(e))
            r = 1;
    }
    return r;
}

/* 0x0008FDC0: find the first node of a list whose table entry carries keys a and b. */
R6eLink *r6e_ListFindKeys(void *l, int a, int b)
{
    R6ePred p;
    R6eLink *it, *end;
    p.fn = (uint8_t (*)(R6ePred *, void *))r6e_PredMatch;
    p.a = a;
    p.b = b;
    it = (R6eLink *)sub_000894D0(l);
    end = sub_0008F8F0(l);
    return sub_0008F970(&it, &end, &p);
}

/* 0x0008FF30: copy the ten 0x48-byte slots of src into the holder's block. */
void r6e_HolderCopySlots(R6eHolder *h, const R6eSlot48 *src)
{
    R6eSlot48 *d = h->data;
    const R6eSlot48 *p;
    for (p = src; p != src + 10; p++, d++)
        *d = *p;
}

/* 0x00090420: set a ramp from (x0, y0) to (x1, y1), both y clamped to 0..1. */
void r6e_RampSet(R6eRamp *r, float x0, float y0, float x1, float y1)
{
    if (y0 > 1.0f)
        y0 = 1.0f;
    else if (y0 < 0.0f)
        y0 = 0.0f;
    if (y1 > 1.0f)
        y1 = 1.0f;
    else if (y1 < 0.0f)
        y1 = 0.0f;
    r->y0 = y0;
    r->x0 = x0;
    r->x1 = x1;
    r->y1 = y1;
}

/* 0x00090480: evaluate a ramp at x (held flat outside x0..x1). */
float r6e_RampEval(const R6eRamp *r, float x)
{
    if (r->x0 >= x)
        return r->y0;
    if (x > r->x1)
        return r->y1;
    return (r->y1 - r->y0) / (r->x1 - r->x0) * (x - r->x0) + r->y0;
}

/* 0x000904C0: drop a reference to a resource and free it at zero. */
void r6e_ResRelease(R6eRes *r)
{
    if (r) {
        if (r->refs)
            r->refs--;
        if (!r->refs)
            sub_00053880(r);
    }
}

/* 0x00090560: run the handler selected by +0x3C (none for -1). */
void r6e_Dispatch(R6eDisp *o)
{
    if (o->index != -1)
        r6e_dispFns2E1398[o->index](o);
}
