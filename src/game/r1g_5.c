/* Area r1g, group 5: effman.c slot pool allocation 0x00035700. Names inferred. */
#include "r1g.h"

/* 0x00035700: return the index of a free slot of pool `p`; when every
   slot is used, grow the tables by 16 and move the old entries over. */
int r1g_PoolAlloc(R1gPool *p)
{
    for (;;) {
        R1gPoolE14 *old14;
        R1gPoolE60 *old60;
        int i, n;
        for (i = 0; i < p->hdr.cap; i++) {
            if (p->tbl14[i].used == 0)
                break;
        }
        if (i < p->hdr.cap)
            return i;
        n = p->hdr.cap;
        old14 = p->tbl14;
        old60 = p->tbl60;
        sub_00035320(p, n + 0x10);
        for (i = 0; i < n; i++) {
            p->tbl14[i] = old14[i];
            p->tbl60[i] = old60[i];
            p->tbl14[i].data = &p->tbl60[i];
        }
        a5b_HeapOp47640(old14);
        a5b_HeapOp47640(old60);
    }
}
