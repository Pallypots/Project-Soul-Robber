/* Area r6f: script blob loaders and task handlers around 0x0008D780-0x0008FA61 (r6f_3). Names inferred. */
#include "r6f.h"

/* 0x0008D780: load a script blob: copy the 0x20-byte header, parse the node
   chain and then the task list; returns the bytes used or a negative error. */
int r6f_BlobLoad(R6fBlob *dst, const R6fBlobHdr *src, int size)
{
    const uint8_t *p;
    int r, used;
    sub_0007F210(dst->head, src, 0x1C);
    dst->mode = src->mode;
    p = (const uint8_t *)(src + 1);
    r = sub_0008C770(&dst->nodes, p, size - 0x20);
    if (r < 0)
        return r;
    used = r + 0x20;
    r = sub_0008B9E0(&dst->tasks, p + r, size - used, dst->nodes, dst->mode);
    if (r < 0)
        return r;
    return r + used;
}

/* 0x0008E100: argument parser: three words into +0x24, +0x2C and +0x30; returns 12 or -1. */
int r6f_TaskArgThree(R6eTask *t, const int32_t *args, int n)
{
    if (!args)
        return -1;
    if (n <= 0)
        return -1;
    t->u24.i = *args++;
    t->i2C = *args++;
    t->u30.i = *args;
    return n >= 12 ? 12 : -1;
}

/* 0x0008EA20: task handler: mark the task idle and give it the lowest id not
   used by the type-7 nodes of ref (default: the process reference). */
int r6f_TaskPickFreeId(R6fTask *t, void *ref)
{
    R6fTask *n, *x;
    int i;
    if (!ref)
        ref = sub_0008CD60()->ref;
    t->state = 2;
    n = (R6fTask *)sub_00089570(ref, 7);
    i = 0;
    while (n) {
        for (x = n; x; x = (R6fTask *)sub_0007F300(x))
            if (x->f18.s.type == 7 && (int)(intptr_t)x->work == i)
                break;
        if (!x)
            break;
        i++;
    }
    t->work = (R6eWork *)(intptr_t)i;
    t->p3C = 0;
    sub_000341C0(&t->p28);
    return 0;
}

/* 0x0008ECA0: when flag 2 is set, copy the live slot values into the task's
   saved slots (field +0x24 of each active 0x48-byte slot) and its 0xB0-byte block. */
void r6f_TaskSaveSlots(R6eTask *t)
{
    R6eHolder *h;
    uint32_t n;
    R6fSlot48 *dst, *src;
    if (t->u24.b[0] & 2) {
        h = (R6eHolder *)&t->p28;
        n = sub_0008FFC0(h);
        dst = (R6fSlot48 *)sub_0008FF80(h);
        src = (R6fSlot48 *)sub_00037780();
        sub_000375A0();
        for (; n; n--) {
            dst->i24 = src->i24;
            sub_000376D0(dst);
            src++;
            dst++;
        }
        *(R6fBlockB0 *)sub_000390A0() = *(R6fBlockB0 *)sub_0008FF90(h);
    }
}

/* 0x0008F350: when the task holds a material (flag 2), hand it to every
   type-8 node of x with the same id fields, then release it.
   regargs: t=EDI x=stack */
void r6f_TaskShareMat(R6eArg20 *x, R6fTask *t)
{
    R6fTask *n;
    uint32_t a, b;
    if (t->f18.u & 2) {
        for (n = (R6fTask *)sub_0008C3C0(x->i20, 8); n; n = (R6fTask *)sub_0007F300(n)) {
            a = (uint32_t)(uintptr_t)t->work;
            b = (uint32_t)(uintptr_t)n->work;
            if (!((a ^ b) & 0x0FF00000) && !((a ^ b) & 0x000FFF00) && n->p28)
                sub_0007ED70(n->p28, t->p28);
        }
        sub_0007EAD0(t->p28);
        t->f18.b0 &= ~2;
        t->p28 = 0;
    }
}

/* 0x0008FA20: apply v to every model of a model set (0x0001EBF0). */
void r6f_ModelSetApply(R6fModelSet *s, int v)
{
    void *models = s->models;
    uint32_t i, n;
    void *m;
    if (models) {
        n = s->count;
        for (i = 0; i < n; i++) {
            m = sub_0001D220(models, i);
            if (m)
                sub_0001EBF0(m, v);
        }
    }
}
