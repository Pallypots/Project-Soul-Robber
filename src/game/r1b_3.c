/* Area r1b, group 3: packet submit helpers 0x00013AA0..0x00013B20 (kept apart from 0x00013A30). Names inferred. */
#include "r1b.h"

/* 0x00013AA0: submit the current packet buffer, by DMA when enabled. */
void r1b_PktSubmit(void)
{
    R1bPkt *e;
    uint32_t n;
    if (r1b_dma37B390) {
        n = sub_000AD090(&r1b_pkts37B4AC[r1b_pktIdx37B4A0]);
        r1b_DmaKick(r1b_pkts37B4AC[r1b_pktIdx37B4A0].tag & 0x3FF0, n);
        return;
    }
    sub_000AD090(0, 0);
    e = &r1b_pkts37B4AC[r1b_pktIdx37B4A0];
    sub_001A1FF0(r1b_dev37B4A4, (e->tag & 0x0FFFFFFF) | 0x80000000);
}

/* 0x00013B20: submit the fixed packet, by DMA when enabled.
   calls 0x00013A30 with stack=tag&0x3FF0 EDX=1 */
void r1b_PktSubmitFixed(void)
{
    if (r1b_dma37B390) {
        r1b_DmaKick(r1b_fixed37B544 & 0x3FF0, 1);
        return;
    }
    sub_000AD090(0, 0);
    sub_001A1FF0(r1b_dev37B4A4, (r1b_fixed37B544 & 0x0FFFFFFF) | 0x80000000);
}
