/* Area r1j, group 13: slot heap resize 0x00047760.
   Names inferred. */
#include "r1j.h"

/* block header of user pointer p (0x40 bytes before it) */
#define R1J_BLK(p) ((R1jBlk *)((char *)(p) - 0x40))
/* a block size rounded to 64 bytes with its header (0x40) */
#define R1J_BLK_SIZE(n) (((n) + 0x7F) & ~0x3Fu)

/* 0x00047760: resize the heap block at p to size bytes. A block of a
   stack-style heap (flag bit 0 at +0x3C) only moves the heap top. Under
   the heap lock: an unchanged rounded size just records the new size; a
   shrink by at least one 64-byte unit splits off the tail as a free
   block (merged with the free blocks after it); a size that still fits
   keeps the block; otherwise a new block is allocated (0x00047390), the
   data copied and the old block freed (0x00047640). Returns the block,
   or 0 (null p or allocation failure). */
void *r1j_HeapResize(void *p, uint32_t size)
{
    R1jBlk *b, *nb, *q;
    R1jHeap *h;
    void *np;
    if (p == 0)
        return 0;
    if (R1J_BLK(p)->flags3C & 1) {
        R1J_BLK(p)->heap->top = (char *)(((uintptr_t)p + size + 0x3F) & ~(uintptr_t)0x3F);
        return p;
    }
    h = R1J_BLK(p)->heap;
    b = R1J_BLK(p);
    if (h->sem != -1)
        sub_001AA460(h->sem);
    if (b->size == R1J_BLK_SIZE(size)) {
        b->used = size;
        np = p;
    } else if ((size + 0xBF & ~0x3Fu) < b->size) {
        nb = (R1jBlk *)(((uintptr_t)b + size + 0x7F) & ~(uintptr_t)0x3F);
        nb->next = b->next;
        if (b->next != 0)
            b->next->prev = nb;
        nb->prev = b;
        nb->size = b->size - R1J_BLK_SIZE(size);
        nb->used = nb->size - 0x44;
        nb->flags = 0;
        nb->flags3C = 0;
        nb->heap = h;
        nb->self = nb;
        sub_0003D880(&h->list, &nb->link);
        b->next = nb;
        b->size = (uint32_t)((char *)nb - (char *)b);
        b->used = size;
        for (q = nb->next; q != 0 && !(q->flags & 1); q = nb->next) {
            nb->next = q->next;
            nb->size += q->size;
            sub_0003D8C0(&q->link);
        }
        if (nb->next != 0)
            nb->next->prev = nb;
        nb->used = nb->size - 0x44;
        if (nb->next == 0)
            h->tail = nb;
        np = (char *)b + 0x40;
    } else if (size > b->used) {
        sub_00047060(h);
        np = sub_00047390(h, size, 0, 0);
        if (h->sem != -1)
            sub_001AA460(h->sem);
        if (np == 0) {
            sub_00047060(h);
            return 0;
        }
        r1j_CopyFwd(np, p, b->used);
        sub_00047060(h);
        sub_00047640(p);
        if (h->sem != -1)
            sub_001AA460(h->sem);
    } else {
        np = p;
    }
    if (h->sem != -1)
        while (sub_001AA520(h->sem) == -1)
            ;
    return np;
}
