/* Area r4e: render threads and draw setup around 0x001A1320-0x001A224F (r4e_6). Names inferred. */
#include "r4e.h"

/* 0x001A1320: draw thread body: every frame build the command buffer for the job's
   mode (0: game view with the 0x0003DCE0/0x00036D70 overlay unless state 5 or the
   level reaches 128, 1: 0x0006D310, 2: 0x000324B0), finish it and yield. Never
   returns. Stack arg (job). */
void r4e_DrawThread(R4eDrawJob *job)
{
    uint32_t *cmd;
    for (;;) {
        sub_001A5310();
        cmd = r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd;
        switch (job->mode04) {
        case 0:
            if (sub_0006C260() && (sub_0006C260() == 5 || !(sub_00036FF0() < 128.0f)))
                cmd = sub_000324B0(cmd);
            else
                cmd = sub_00036D70(sub_0003DCE0(cmd));
            break;
        case 1:
            cmd = sub_0006D310(cmd);
            break;
        case 2:
            cmd = sub_000324B0(cmd);
            break;
        }
        r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd = sub_00079480(cmd);
        sub_001A7B90();
        sub_000580D0();
    }
}

/* 0x001A1DA0: reset the 14 render-target slots and create each target from the size
   tables; returns 0 on the first failure, else selects buffer 1 and returns 1. No inputs. */
int r4e_RenderTargetsInit(void)
{
    int i;
    for (i = 0; i < 14; i++) {
        r4c_offsets4046FC[i] = 0;
        r4c_targets404734[i] = (void *)-1;
    }
    r4c_curTarget40476C = -1;
    for (i = 0; i < 14; i++) {
        if (sub_001D2330(r4e_rtSizeB341670[i], r4e_rtSizeA341638[i], &r4c_targets404734[i], 0))
            return 0;
    }
    sub_001D2870(1);
    return 1;
}

/* 0x001A2130: point vertex streams 0..7 at the arrays that follow a vertex block
   header (positions, -, then two more arrays of count*16 bytes), draw count vertices
   (at least 3 for type 4) and advance the caller's pointer past the block.
   Stack arg (pp). */
void r4e_DrawVertexBlock(R4eVtxHdr **pp)
{
    R4eVtxHdr *h = *pp;
    int size = h->count00 * 16;
    uint8_t *p = (uint8_t *)h + 0x10;
    r4e_streams40AFF8[0].addr04 = (uint32_t)(uintptr_t)p & 0x0FFFFFFF;
    sub_001D26C0(0, &r4e_streams40AFF8[0], 0x10);
    p += size;
    r4e_streams40AFF8[1].addr04 = 0;
    sub_001D26C0(1, &r4e_streams40AFF8[1], 0x10);
    r4e_streams40AFF8[2].addr04 = (uint32_t)(uintptr_t)p & 0x0FFFFFFF;
    sub_001D26C0(2, &r4e_streams40AFF8[2], 0x10);
    p += size;
    r4e_streams40AFF8[3].addr04 = (uint32_t)(uintptr_t)p & 0x0FFFFFFF;
    sub_001D26C0(3, &r4e_streams40AFF8[3], 0x10);
    p += size;
    r4e_streams40AFF8[4].addr04 = 0;
    sub_001D26C0(4, &r4e_streams40AFF8[4], 0x10);
    r4e_streams40AFF8[5].addr04 = 0;
    sub_001D26C0(5, &r4e_streams40AFF8[5], 0x10);
    r4e_streams40AFF8[6].addr04 = 0;
    sub_001D26C0(6, &r4e_streams40AFF8[6], 0x10);
    r4e_streams40AFF8[7].addr04 = 0;
    sub_001D26C0(7, &r4e_streams40AFF8[7], 0x10);
    if ((h->flags04 & 7) != 4)
        sub_001D5C30(5, 0, h->count00);
    else if (h->count00 <= 3)
        sub_001D5C30(5, 0, 3);
    else
        sub_001D5C30(6, 0, h->count00);
    *pp = (R4eVtxHdr *)p;
}

/* 0x001A2250: like r4e_DrawVertexBlock, but streams 1..3 are bound only when the
   matching flag bit (1, 2, 4) is set. Stack args (pp flags). */
void r4e_DrawVertexBlockOpt(R4eVtxHdr **pp, int flags)
{
    R4eVtxHdr *h = *pp;
    int size = h->count00 * 16;
    uint8_t *p = (uint8_t *)h + 0x10;
    r4e_streams40AFF8[0].addr04 = (uint32_t)(uintptr_t)p & 0x0FFFFFFF;
    sub_001D26C0(0, &r4e_streams40AFF8[0], 0x10);
    p += size;
    if (flags & 1) {
        r4e_streams40AFF8[1].addr04 = (uint32_t)(uintptr_t)p & 0x0FFFFFFF;
        sub_001D26C0(1, &r4e_streams40AFF8[1], 0x10);
        p += size;
    }
    if (flags & 2) {
        r4e_streams40AFF8[2].addr04 = (uint32_t)(uintptr_t)p & 0x0FFFFFFF;
        sub_001D26C0(2, &r4e_streams40AFF8[2], 0x10);
        p += size;
    }
    if (flags & 4) {
        r4e_streams40AFF8[3].addr04 = (uint32_t)(uintptr_t)p & 0x0FFFFFFF;
        sub_001D26C0(3, &r4e_streams40AFF8[3], 0x10);
        p += size;
    }
    if ((h->flags04 & 7) != 4)
        sub_001D5C30(5, 0, h->count00);
    else if (h->count00 <= 3)
        sub_001D5C30(5, 0, 3);
    else
        sub_001D5C30(6, 0, h->count00);
    *pp = (R4eVtxHdr *)p;
}

