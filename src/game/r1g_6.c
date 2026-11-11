/* Area r1g, group 6: effman.c pool image loader 0x000357E0 (kept apart from 0x00035700). Names inferred. */
#include "r1g.h"


/* 0x000357E0: load pool `p` from the file image `b`; returns the first
   byte after the image. regargs: p=EBX (b on the stack). */
uint8_t *r1g_PoolLoad(const R1gPoolBlob *b, R1gPool *p)
{
    const R1gPoolE14 *src14 = (const R1gPoolE14 *)((const uint8_t *)b + b->off14);
    const R1gPoolE60 *src60 = (const R1gPoolE60 *)((const uint8_t *)b + b->off60);
    int i;
    sub_00035320(p, b->hdr.cap);
    for (i = 0; i < b->hdr.cap; i++) {
        int k = r1g_PoolAlloc(p);
        p->tbl14[k] = src14[i];
        p->tbl60[k] = src60[i];
        p->tbl14[k].data = &p->tbl60[k];
    }
    p->hdr = b->hdr;
    p->hdr.slots = p->tbl14;
    return (uint8_t *)(src60 + i);
}
