/* Area r1g, group 10: heap block split 0x00047240. Names inferred. */
#include "r1g.h"

/* 0x00047240: take `size` bytes from free block `b`, splitting off the
   rest as a new free block when it is large enough (64-byte granules,
   0x40-byte header). With `low` set the allocation stays at the start of
   b, otherwise it is carved from the end. Returns the used block.
   regargs: low=EAX b=ECX size=EBX */
R1gBlk *r1g_BlkTake(int low, R1gBlk *b, uint32_t size)
{
    R1gBlk *n;
    if (low) {
        if (b->size > ((size + 0xBF) & ~0x3Fu)) {
            n = (R1gBlk *)(((uintptr_t)b + size + 0x7F) & ~(uintptr_t)0x3F);
            n->next = b->next;
            if (b->next)
                b->next->prev = n;
            n->prev = b;
            n->size = b->size - ((size + 0x7F) & ~0x3Fu);
            n->avail = n->size - 0x44;
            n->used = 0;
            n->d3C = 0;
            n->heap = b->heap;
            n->self = n;
            b->next = n;
            b->size = (uint32_t)((uint8_t *)n - (uint8_t *)b);
            a4c_ListAppend(b->heap->freeList, n->node);
            if (n->next == 0)
                n->heap->last = n;
        }
        a4c_ListRemove(b->node);
        a4c_ListAppend(b->heap->usedList, b->node);
        b->avail = size;
        b->used = 1;
        b->d3C = 0;
        return b;
    }
    a4c_ListRemove(b->node);
    if (b->size > ((size + 0xBF) & ~0x3Fu)) {
        uint32_t sz = (size + 0x7F) & ~0x3Fu;
        R1gBlk *a = b;
        b = (R1gBlk *)((uint8_t *)a + (a->size - sz));
        b->next = a->next;
        if (a->next)
            a->next->prev = b;
        b->prev = a;
        b->self = b;
        a->size = (uint32_t)((uint8_t *)b - (uint8_t *)a);
        a->next = b;
        a->avail = a->size - 0x44;
        a->used = 0;
        a->d3C = 0;
        b->size = sz;
        b->heap = a->heap;
        a4c_ListAppend(a->heap->freeList, a->node);
        if (b->next == 0)
            b->heap->last = b;
    }
    b->avail = size;
    b->used = 1;
    b->d3C = 0;
    a4c_ListAppend(b->heap->usedList, b->node);
    return b;
}
