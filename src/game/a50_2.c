/* Slot memory heaps (0x000532B0-0x00053BDF). Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a50.h"


/* 0x000532B0: look up a cache entry and return its data pointer. */
int a50_CacheGetData(int a, int b)
{
    int32_t *e = sub_000531C0(a, b);
    if (e == 0)
        return 0;
    return e[3];
}

/* 0x00053710: push a heap index on the heap stack (hangs on overflow). */
void a50_PushHeap(int heap)
{
    if (a50_heapDepth >= 0x3F)
        for (;;) ;
    a50_heapStack[++a50_heapDepth] = heap;
}

/* 0x00053740: pop the heap stack (hangs on underflow). */
void a50_PopHeap(void)
{
    if (a50_heapDepth <= 0)
        for (;;) ;
    a50_heapDepth--;
}

/* 0x000537F0: release every slot heap. */
void a50_FreeSlotHeaps(void)
{
    int32_t *p;
    for (p = a50_slotHeap; p < &a50_slotHeap[9]; p++) {
        if (*p != 0) {
            sub_00047040(*p);
            *p = 0;
        }
    }
}

/* 0x00053970: end a temporary sub-heap in slot `slot`, shrinking it to its
 * used size and restoring the saved heap. */
void a50_SlotEndTemp(int slot)
{
    int used;
    if (a50_slotSaved[slot] == 0)
        return;
    used = sub_000470C0(a50_slotHeap[slot]);
    sub_00047140(a50_slotHeap[slot]);
    sub_00047760(a50_slotHeap[slot], used);
    a50_slotHeap[slot] = a50_slotSaved[slot];
    a50_slotSaved[slot] = 0;
}

/* 0x000539C0: begin a temporary sub-heap in slot `slot`. */
void a50_SlotBeginTemp(int slot, int heap, int size)
{
    a50_slotSaved[slot] = a50_slotHeap[slot];
    a50_slotHeap[slot] = heap;
    sub_000471B0(heap, size, a50_strHeapName, a50_strHeapFile, 0x2F2);
}

/* 0x00053A00: discard a temporary sub-heap in slot `slot`. */
void a50_SlotDiscardTemp(int slot)
{
    if (a50_slotSaved[slot] == 0)
        return;
    sub_00047040(a50_slotHeap[slot]);
    a50_slotHeap[slot] = a50_slotSaved[slot];
    a50_slotSaved[slot] = 0;
}

/* 0x00053BC0: allocate from the heap on top of the heap stack. */
void *a50_AllocTop(int a, int b)
{
    return sub_000538A0(a50_heapStack[a50_heapDepth], a, b);
}
