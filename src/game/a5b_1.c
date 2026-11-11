/* Video timing, cache entries and slot heaps (0x00052900-0x00053BDF),
 * second pass. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a5b.h"

/* 0x000529F0: current video mode. */
int a5b_GetVideoMode(void)
{
    return a50_videoMode;
}

/* 0x00052E10: release every table handle of a cache entry's blob. */
void a5b_CacheRelease(int32_t *entry)
{
    A50Table *t = (A50Table *)((A50Blob *)entry[3])->tableA; /* XBOX32: cache entry word and blob table hold 32-bit addresses */
    uint32_t i;
    for (i = 0; i < t->count; i++)
        sub_001B9FC0(t->entries[i].ptr);
    entry[3] = 0;
}

/* 0x00053880: forward to the heap routine at 0x00047640. */
void a5b_HeapOp47640(int heap)
{
    sub_00047640(heap);
}

/* 0x00053890: shrink a heap to `size` bytes. */
void a5b_HeapShrink(int heap, int size)
{
    sub_00047760(heap, size);
}

/* 0x00053A40: create the main game heap and reset the slot heaps. */
void a5b_InitSlotHeaps(void)
{
    a5b_heapBase = sub_001A8630(0x1E00000);
    a5b_heapSize = 0x1E00000;
    a50_slotHeap[0] = 0;
    a50_slotHeap[1] = 0;
    a50_slotHeap[2] = 0;
    a50_slotHeap[3] = 0;
    a50_slotHeap[4] = 0;
    a50_slotHeap[5] = 0;
    a50_slotHeap[6] = 0;
    a50_slotHeap[7] = 0;
    a50_slotHeap[8] = 0;
    sub_00053760();
    a50_heapDepth = 0;
    a50_heapStack[0] = 8;
}

/* 0x00053AB0: allocate from the slot on top of the heap stack. */
void *a5b_AllocCur(int size, int a, int b)
{
    int slot = a50_heapStack[a50_heapDepth];
    if (slot != 10) {
        if (slot >= 9)
            for (;;) ;
        return sub_00047390(a50_slotHeap[slot], size, a, b);
    }
    return sub_00047450(a50_slotHeap[8], size, a, b);
}

/* 0x00053B10: allocate from the high end of the current slot heap. */
void *a5b_AllocCurHigh(int size, int a, int b)
{
    int slot = a50_heapStack[a50_heapDepth];
    if (slot == 10)
        return sub_00047450(a50_slotHeap[8], size, a, b);
    if (slot >= 9)
        for (;;) ;
    return sub_00047450(a50_slotHeap[slot], size, a, b);
}

/* 0x00053B70: heap routine 0x00047560 on the current slot heap. */
void *a5b_CurHeapOp47560(int a, int b)
{
    int slot = a50_heapStack[a50_heapDepth];
    if (slot == 10)
        return sub_00047560(a50_slotHeap[8], a, b);
    if (slot >= 9)
        for (;;) ;
    return sub_00047560(a50_slotHeap[slot], a, b);
}

/* 0x00053BE0: end the temporary sub-heap of the current slot. */
void a5b_CurSlotEndTemp(void)
{
    int slot = a50_heapStack[a50_heapDepth];
    int used;
    if (a50_slotSaved[slot] == 0)
        return;
    used = sub_000470C0(a50_slotHeap[slot]);
    sub_00047140(a50_slotHeap[slot]);
    sub_00047760(a50_slotHeap[slot], used);
    a50_slotHeap[slot] = a50_slotSaved[slot];
    a50_slotSaved[slot] = 0;
}
