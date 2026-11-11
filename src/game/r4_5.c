/* Area r4: callers of the register-argument heap and texture helpers (r4_5). Names inferred. */
#include "r4.h"

/* 0x001BB5C0: allocate `size` units of heap 1 for an allocation kind; returns the address or 0xFFFF.
   Stack args. Calls 0x001BB0B0 with EAX=kind; 0x001BB3E0 with EAX=code ECX=first block size=stack;
   0x001BB440 with EAX=size EDX=addr (code 0 on the stack). */
uint16_t r4_HeapAlloc(uint16_t size, int kind)
{
    uint8_t code;
    uint16_t addr;
    if (!r4_g40F75C->first)
        return 0xFFFF;
    code = r4_HeapKindCode(kind);
    addr = r4_HeapFindFit(code, r4_g40F75C->first, size);
    if (addr == 0xFFFF)
        return addr;
    sub_001BB440(size, addr, code, 0);
    r4_HeapMerge();
    return addr;
}

/* 0x001BB620: claim `size` units of heap 1 at a fixed address. Stack args.
   Calls 0x001BB0B0 with EAX=kind and 0x001BB440 with EAX=size EDX=addr (code 1 on the stack). */
int r4_HeapClaim(uint16_t addr, uint16_t size, int kind)
{
    int r = sub_001BB440(size, addr, r4_HeapKindCode(kind), 1);
    r4_HeapMerge();
    return r;
}

/* 0x001BB6E0: reset heap 2 to one free record covering the whole range. */
void r4_Heap2Init(void)
{
    R4Blk2 *r;
    r4_Heap2Reset();
    r = r4_g40F76C;
    r->used = 1;
    r->next = 0;
    r->b5 = 0;
    r->w1C = r4_g40F768->w8;
    r->w1E = r4_g40F768->wA;
}

/* 0x001BA7C0: find a texture by name in the current group (0xFFFF when there is no table). Stack arg. */
int r4_TexFindNamed(const char *name)
{
    R4TexTable *t = r4_g40F390;
    if (!t)
        return r4_TexFindByName(0xFFFF, name);
    return r4_TexFindByName(t->group1C, name);
}
