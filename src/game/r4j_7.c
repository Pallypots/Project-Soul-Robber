/* Area r4j: small block heap claim/release (0x001BB440). Names inferred. */
#include "r4j.h"

/* first unused block record (inlined twice in the original); 0 if none */
static R4jBlk *r4j_BlkNew(void)
{
    uint32_t i;
    for (i = 0; i < r4j_blkHeap40F75C->count; i++)
        if (r4j_blks40F760[i].used == 0)
            return &r4j_blks40F760[i];
    return 0;
}

/* 0x001BB440: claim (release = 0) or release (release != 0) the address
   range [addr, addr + size) for the owner bits in code. Walks the blocks
   from the one holding addr, splitting off the parts before and after the
   range into new records, then sets or clears the owner bits of each block.
   Returns 0, or -1 when no block holds addr, the bits are already taken
   (claim) or not held / reserved (release), or the range is not contiguous.
   regargs: size=EAX addr=EDX; stack args (code release). */
int sub_001BB440(uint16_t size, uint16_t addr, uint8_t code, int release)
{
    R4jBlk *b = r4_HeapFindBlock(addr);
    R4jBlk *n;
    uint8_t f;
    uint16_t len;

    if (b == 0)
        return -1;
    if (size == 0)
        return 0;
    do {
        if (b->addr < addr) {
            /* split off the part before addr */
            n = r4j_BlkNew();
            *n = *b;
            n->next = b;
            n->size = addr - b->addr;
            b->prev = n;
            b->addr = addr;
            b->size -= n->size;
        }
        if (b->size > size) {
            /* split off the part after the range */
            n = r4j_BlkNew();
            *n = *b;
            n->prev = b;
            n->addr = b->addr + size;
            n->size = b->size - size;
            b->next = n;
            b->size -= n->size;
        }
        f = b->lock0A;
        if (release) {
            if (!(code & f) || (b->lock0B & code))
                return -1;
            b->lock0A = ~code & f;
        } else {
            if (code & (b->lock0B | f))
                return -1;
            b->lock0A = f | code;
        }
        len = b->size;
        size -= len;
        addr += len;
        if (size != 0) {
            if (b->next == 0)
                return -1;
            if (b->addr + len != b->next->addr)
                return -1;
        }
        b = b->next;
    } while (size != 0);
    return 0;
}
