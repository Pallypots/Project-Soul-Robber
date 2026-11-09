/* Memory reset and record table (0x00053C40-0x00053D6B). Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a50.h"

/* 0x00053C40: reset the heap stack, free slot heaps and clear the cache. */
void a50_MemReset(void)
{
    a50_heapDepth = 0;
    a50_heapStack[0] = 8;
    a50_FreeSlotHeaps();
    sub_00053760();
    a50_ClearCache();
}

/* 0x00053C70: clear the 16 records. */
void a50_RecsClear(void)
{
    int i;
    for (i = 0; i < 16; i++) {
        a50_recs[i].used = 0;
        a50_recs[i].value = 0;
    }
    a50_recCount = 0;
}

/* 0x00053C90: number of records in use. */
int a50_RecsCount(void)
{
    return a50_recCount;
}

/* 0x00053D50: run 0x0004F580 then the two follow-up steps. */
void a50_Sub53D50(int a, int b)
{
    sub_0004F580(a, b);
    sub_0004F4E0();
    sub_0004F6F0();
}
