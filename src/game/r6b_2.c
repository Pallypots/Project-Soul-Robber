/* Area r6b: task handlers, list and handle helpers around 0x0008F0D0-0x00090410 (r6b_2). Names inferred. */
#include "r6b.h"

/* 0x0008F0D0: task descriptor getter. */
R6bDesc *r6b_GetDesc2703E4(void) { return &r6b_desc2703E4; }

/* 0x0008F0E0: set a task's target (+0x2C) and two parameters, mark it pending. */
void r6b_TaskSetTarget(R6bTask *t, int target, float a, float b)
{
    t->u24.i24 |= 1;
    t->i2C = target;
    t->f30 = a;
    t->f34 = b;
}

/* 0x0008F1A0: deactivate an idle task; -1 when it is not idle. */
int r6b_TaskDeactivate(R6bTask *t)
{
    if (t->state != 2)
        return -1;
    if (t->flags18 & 2) {
        t->flags18 &= ~2;
        t->u28.i28 = 0;
    }
    return 0;
}

/* 0x0008F320: task descriptor getter. */
R6bDesc *r6b_GetDesc270420(void) { return &r6b_desc270420; }

/* 0x0008F330: reset a task to idle and clear byte +0x25; -1 for no task. */
int r6b_TaskIdleClear25(R6bTask *t)
{
    if (!t)
        return -1;
    t->state = 2;
    t->u24.bb.b25 = 0;
    return 0;
}

/* 0x0008F3D0: argument parser: two halfwords into bytes +0x24/+0x25; returns 4 or -1. */
int r6b_TaskArgBytes(R6bTask *t, const uint16_t *args, int n)
{
    t->u24.bb.b25 = (uint8_t)args[1];
    t->u24.bb.b24 = (uint8_t)args[0];
    return n >= 4 ? 4 : -1;
}

/* 0x0008F400: copy 0x14 bytes at +0x18 from src to dst, clear src +0x28; returns 0. */
int r6b_TaskCopy18(R6bTask *dst, R6bTask *src)
{
    sub_0007F210(&dst->flags18, &src->flags18, 0x14);
    src->u28.i28 = 0;
    return 0;
}

/* 0x0008F660: task descriptor getter. */
R6bDesc *r6b_GetDesc270474(void) { return &r6b_desc270474; }

/* 0x0008F670: reset a task to idle; -1 for no task. */
int r6b_TaskIdleChecked(R6bTask *t)
{
    if (!t)
        return -1;
    t->state = 2;
    return 0;
}

/* 0x0008F690: handler that only checks its arguments: 0 when both are given, else -1. */
int r6b_TaskCheckArgs(R6bTask *t, const void *args)
{
    if (!t)
        return -1;
    return args ? 0 : -1;
}

/* 0x0008F710: argument parser: one word into +0x24 (task checked); returns 4 or -1. */
int r6b_TaskArgWordChecked(R6bTask *t, const int32_t *args, int n)
{
    if (!t || !args || n <= 0)
        return -1;
    t->u24.i24 = args[0];
    if (n >= 4)
        return 4;
    return -1;
}

/* 0x0008F740: task descriptor getter. */
R6bDesc *r6b_GetDesc270498(void) { return &r6b_desc270498; }

/* 0x0008F7B0: argument parser: one word with bit 0 cleared into +0x24; returns 4 or -1. */
int r6b_TaskArgWordEven(R6bTask *t, const int32_t *args, int n)
{
    if (!args || n <= 0)
        return -1;
    t->u24.i24 = args[0] & ~1;
    if (n >= 4)
        return 4;
    return -1;
}

/* 0x0008F8B0: task descriptor getter. */
R6bDesc *r6b_GetDesc2704BC(void) { return &r6b_desc2704BC; }
/* 0x0008F8C0: task descriptor getter. */
R6bDesc *r6b_GetDesc2704E0(void) { return &r6b_desc2704E0; }
/* 0x0008F8D0: task descriptor getter. */
R6bDesc *r6b_GetDesc270504(void) { return &r6b_desc270504; }

/* 0x0008F8E0: initialise an empty list (head points at itself). */
void r6b_ListInit(R6bList *l)
{
    l->head = (R6bLink *)&l->head;
    l->count = 0;
}

/* 0x0008F8F0: address of the list head link. */
R6bLink **r6b_ListHeadRef(R6bList *l)
{
    return &l->head;
}

/* 0x0008F900: push a node at the front of a list. */
void r6b_ListPush(R6bList *l, R6bLink *n)
{
    n->next = l->head;
    l->head = n;
    l->count++;
}

/* 0x0008F920: drop the front node of a non-empty list. */
void r6b_ListPop(R6bList *l)
{
    if (l->count) {
        l->head = l->head->next;
        l->count--;
    }
}

/* 0x0008F940: advance a list iterator. */
void r6b_IterNext(R6bLink **it)
{
    *it = (*it)->next;
}

/* 0x0008F950: node after the iterator position. */
R6bLink *r6b_IterPeek(R6bLink **it)
{
    return (*it)->next;
}

/* 0x0008F960: true when two iterators are at the same node. */
uint8_t r6b_IterEqual(R6bLink **a, R6bLink **b)
{
    return *a == *b;
}

/* 0x0008F9B0: increment the counter at +0x04. */
void r6b_ResIncSize(R6bRes *r)
{
    r->size++;
}

/* 0x0008F9C0: load a handle's data once (key and size known, nothing loaded yet). */
void r6b_ResLoad(R6bRes *r)
{
    if (r->key && !r->loaded && r->size)
        r->loaded = sub_0001F930(r->size, r->key);
}

/* 0x0008F9F0: loaded data of a handle. */
void *r6b_ResLoaded(R6bRes *r)
{
    return r->loaded;
}

/* 0x0008FA00: table entry of a handle's key, 0 when it has no key. */
void *r6b_ResTableEntry(R6bRes *r)
{
    if (r->key)
        return a12_Table_Get(r->key, 0);
    return 0;
}

/* 0x0008FDA0: destroy an object: shut it down, release it and free it. */
void r6b_ObjDestroy(void *p)
{
    if (p) {
        sub_0008FB80(p);
        a8c_Release102FA0(p);
        sub_00053880(p);
    }
}

/* 0x0008FEE0: allocate a holder's zeroed data block (0x380 bytes). */
void r6b_HolderAlloc(R6bHolder *h)
{
    R6bHolderData *d = (R6bHolderData *)a5b_AllocCur(0x380, 0, 0x45);
    uint32_t *w = (uint32_t *)d;
    int i;
    h->data = d;
    for (i = 0; i < 0xE0; i++)
        w[i] = 0;
}

/* 0x0008FF10: free a holder's data block. */
void r6b_HolderFree(R6bHolder *h)
{
    sub_00053880(h->data);
    h->data = 0;
}

/* 0x0008FF60: copy a 0xB0-byte block into the holder data at +0x2D0. */
void r6b_HolderSetBlk(R6bHolder *h, const R6bBlkB0 *src)
{
    h->data->blk2D0 = *src;
}

/* 0x0008FF80: holder data pointer. */
R6bHolderData *r6b_HolderData(R6bHolder *h)
{
    return h->data;
}

/* 0x0008FF90: address of the block at +0x2D0 of the holder data. */
R6bBlkB0 *r6b_HolderBlk(R6bHolder *h)
{
    return &h->data->blk2D0;
}

/* 0x0008FFA0: set the holder data pointer. */
void r6b_HolderSet(R6bHolder *h, R6bHolderData *d)
{
    h->data = d;
}

/* 0x0008FFB0: take the holder data pointer (holder is cleared). */
R6bHolderData *r6b_HolderTake(R6bHolder *h)
{
    R6bHolderData *d = h->data;
    h->data = 0;
    return d;
}

/* 0x0008FFC0: number of leading used slots (of 10) in the holder data. */
uint32_t r6b_HolderCountSlots(R6bHolder *h)
{
    R6bSlot48 *s = h->data->slots;
    uint32_t i;
    for (i = 0; i < 10; i++, s++)
        if (!s->p20)
            break;
    return i;
}

/* 0x00090070: free the buffers of four 0x14-byte records. */
void r6b_FreeRecs4(R6bRec14 *r)
{
    int i;
    for (i = 4; i != 0; i--, r++)
        sub_00053880(r->p);
}

/* 0x00090410: add a reference to a handle. */
void r6b_ResAddRef(R6bRes *r)
{
    r->refs++;
}
