/* Area r4: heap best-fit search (r4_6), kept apart from its callee 0x001BB030 and its caller 0x001BB5C0. Names inferred. */
#include "r4.h"

/* 0x001BB3E0: start address of the cheapest heap-1 run that fits `size`, or 0xFFFF.
   regargs: code=EAX (AL) first=ECX size=stack. Calls 0x001BB030 with EDX=block ECX=size EBX=code. */
uint16_t r4_HeapFindFit(uint8_t code, R4Blk *first, uint16_t size)
{
    R4Blk *b, *best = 0;
    int bestCost = 0x0FFFFFFF;
    for (b = first; b; b = b->next) {
        int c = r4_HeapRunCost(b, size, code);
        if (c == 0) {
            best = b;
            break;
        }
        if (c > 0 && (!best || c < bestCost)) {
            best = b;
            bestCost = c;
        }
    }
    if (!best)
        return 0xFFFF;
    return best->addr;
}
