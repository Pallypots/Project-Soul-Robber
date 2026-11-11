/* Area r4: node pool, texture table lookups and small block heaps, 0x001B3380-0x001BB6D6 (r4_4). Names inferred. */
#include "r4.h"

/* 0x001B3380: take an item from the pool's free list. regargs: pool=ECX. */
R4PoolItem *r4_PoolAlloc(R4Pool *pool)
{
    R4PoolItem *it = pool->free, *n;
    if (!it)
        return it;
    n = it->next;
    pool->free = n;
    if (n)
        n->prev = 0;
    it->prev = 0;
    it->next = 0;
    it->owner = pool;
    pool->used++;
    return it;
}

/* 0x001B33C0: give an item back to its pool. regargs: it=ECX. */
void r4_PoolFree(R4PoolItem *it)
{
    R4Pool *pool;
    if (!it)
        return;
    pool = it->owner;
    it->next = pool->free;
    if (pool->free)
        pool->free->prev = it;
    it->prev = 0;
    pool->free = it;
    pool->used--;
}

/* 0x001B33F0: chain all pool items into the free list. regargs: pool=ECX. */
void r4_PoolInit(R4Pool *pool)
{
    R4PoolItem *it = pool->items, *prev = 0;
    uint32_t i;
    pool->free = it;
    pool->used = 0;
    for (i = 0; i < pool->cap; i++) {
        it->prev = prev;
        it->next = it + 1;
        it->owner = pool;
        it->i8C = 0;
        prev = it;
        it++;
    }
    prev->next = 0;
}

/* 0x001B60C0: flag the emitter set and zero every emitter's +0xCC value. Stack arg. */
void r4_EmitSetReset(R4EmitSet *s)
{
    uint32_t i;
    s->flagsB8 |= 1;
    for (i = 0; i < s->count; i++)
        s->items[i].fCC = 0.0f;
}

/* 0x001B6060: set flags 0x180. Stack arg. */
void r4_EmitSetFlags180(R4EmitSet *s)
{
    s->flagsB8 |= 0x180;
}

/* 0x001B6070: clear flag 0x80 and set 0x100. Stack arg. */
void r4_EmitSetFlag100(R4EmitSet *s)
{
    s->flagsB8 = (s->flagsB8 & ~0x80u) | 0x100;
}

/* 0x001B6090: set flag 0x100, and 0x200 too when 0x100 was not set yet. Stack arg. */
void r4_EmitStart(R4EmitSet *s)
{
    uint32_t f = s->flagsB8;
    if (!(f & 0x100))
        s->flagsB8 = f | 0x200;
    s->flagsB8 |= 0x100;
}

/* 0x001B6120: clear flag 1. Stack arg. */
void r4_EmitClearFlag1(R4EmitSet *s)
{
    s->flagsB8 &= ~1u;
}

/* 0x001B6130: set flag 8. Stack arg. */
void r4_EmitSetFlag8(R4EmitSet *s)
{
    s->flagsB8 |= 8;
}

/* 0x001B6140: 1 when flag 8 is set and no active emitter has a non-zero +0xC0 count. Stack arg. */
int r4_EmitIsDone(R4EmitSet *s)
{
    uint32_t i;
    int sum = 0;
    if (!(s->flagsB8 & 8))
        return 0;
    for (i = 0; i < s->count; i++)
        if (s->items[i].flagsB0 & 1)
            sum += s->items[i].iC0;
    return sum == 0;
}

/* 0x001B6190: 1 when the set has no +0x80 owner or has flag 0x20. Stack arg. */
int r4_EmitIsFree(R4EmitSet *s)
{
    return !s->p80 || (s->flagsB8 & 0x20) != 0;
}

/* 0x001B9B90: index of the in-use texture of `group` whose 16-byte key matches; -1 if none.
   regargs: group=ESI key=ECX. */
int r4_TexFindByKey(uint16_t group, const uint32_t *key)
{
    R4TexEnt *first = r4_g40F390->first, *e;
    for (e = first; e; e = e->next) {
        if ((e->flags & 1) && e->group == group &&
            e->id.key[0] == key[0] && e->id.key[1] == key[1] &&
            e->id.key[2] == key[2] && e->id.key[3] == key[3])
            return (int)(e - first);
    }
    return -1;
}

/* Upper-case an ASCII letter. */
static char UpCase(char c)
{
    if (c >= 'a' && c <= 'z')
        c -= 0x20;
    return c;
}

/* 0x001B9BF0: index of the in-use texture of `group` named `name` (8 chars, case-insensitive); -1 if none. Stack args. */
int r4_TexFindByName(uint16_t group, const char *name)
{
    R4TexEnt *first = r4_g40F390->first, *e;
    int i;
    for (e = first; e; e = e->next) {
        if (!(e->flags & 1) || e->group != group)
            continue;
        for (i = 0; i < 8; i++) {
            char a = UpCase(name[i]);
            char b = UpCase(e->id.name[i]);
            if (a != b)
                break;
            if (!a || i == 7)
                return (int)(e - first);
            if (!b)
                break;
        }
    }
    return -1;
}

/* 0x001BB000: mark every block record of heap 1 unused. */
void r4_HeapClearUsed(void)
{
    uint32_t i;
    for (i = 0; i < r4_g40F75C->count; i++)
        r4_g40F760[i].used = 0;
}

/* 0x001BB030: cost of placing `size` units from block b onward with access code `code`; -1 if impossible.
   regargs: b=EDX size=ECX code=EBX (BL). */
int r4_HeapRunCost(R4Blk *b, uint16_t size, uint8_t code)
{
    int cost = 0;
    while (b) {
        uint8_t lock = b->lock0B | b->lock0A;
        uint8_t freeBits;
        int w;
        R4Blk *n;
        if (code & lock)
            break;
        freeBits = (uint8_t)~(lock | code);
        w = 0;
        if (freeBits & 1)
            w = 6;
        if (freeBits & 4)
            w++;
        if (freeBits & 2)
            w++;
        cost += b->size * w;
        if (size <= b->size)
            return cost;
        n = b->next;
        if (!n || b->addr + b->size != n->addr)
            break;
        size -= b->size;
        b = n;
    }
    return -1;
}

/* 0x001BB0B0: access code for an allocation kind. regargs: kind=EAX (low 16 bits); result in AL. */
uint8_t r4_HeapKindCode(int kind)
{
    switch ((uint16_t)kind) {
    case 1:
    case 49:
        return 1;
    case 27:
        return 6;
    case 36:
        return 2;
    case 44:
        return 4;
    default:
        return 7;
    }
}

/* 0x001BB120: heap-1 block that contains addr, or 0. regargs: addr=EDX (low 16 bits). */
R4Blk *r4_HeapFindBlock(uint16_t addr)
{
    R4Blk *b;
    for (b = r4_g40F75C->first; b; b = b->next)
        if (b->addr <= addr && b->addr + b->size > addr)
            break;
    return b;
}

/* 0x001BB160: merge neighbouring heap-1 blocks with equal access flags. */
void r4_HeapMerge(void)
{
    R4Blk *b = r4_g40F75C->first, *n;
    if (!b || !b->next)
        return;
    do {
        n = b->next;
        if (b->addr + b->size == n->addr && b->lock0A == n->lock0A && b->lock0B == n->lock0B) {
            n->used = 0;
            b->size += b->next->size;
            b->next = b->next->next;
        } else {
            b = n;
        }
    } while (b->next);
}

/* 0x001BB1D0: set the three words at 0x00412F4C. */
void r4_Set412F4C(int a, int b, int c)
{
    r4_g412F4C[0] = a;
    r4_g412F4C[1] = b;
    r4_g412F4C[2] = c;
}

/* 0x001BB1F0: set the three words at 0x00412F58. */
void r4_Set412F58(int a, int b, int c)
{
    r4_g412F58[0] = a;
    r4_g412F58[1] = b;
    r4_g412F58[2] = c;
}

/* 0x001BB650: heap-2 header word +0x0C. */
uint16_t r4_Heap2Word0C(void)
{
    return r4_g40F768->wC;
}

/* 0x001BB660: release every heap-2 record and detach its owner. */
void r4_Heap2Reset(void)
{
    uint32_t i;
    for (i = 0; i < r4_g40F768->count; i++) {
        R4Blk2 *r = &r4_g40F76C[i];
        r->used = 0;
        if (r->owner) {
            *(int32_t *)(r->owner + 0x50) = 0;
            r->owner = 0;
        }
    }
}

/* 0x001BB6A0: merge neighbouring free heap-2 records. */
void r4_Heap2Merge(void)
{
    R4Blk2 *b = r4_g40F76C;
    while (b->next) {
        if (!b->b5 && !b->next->b5) {
            b->next->used = 0;
            b->w1E += b->next->w1E;
            b->next = b->next->next;
        } else {
            b = b->next;
        }
    }
}
