/* Area m2, file gs1: security-cookie functions (compiled with /GS). Names inferred. */
#include <stdint.h>

extern void *volatile m1_poolAux3E26D0[];
extern void *m1_pools3E26A8[];
extern const char m2_strRegion26BF08[];
extern const char m2_strRegionNone26BEFC[];
int   a6b_Printf3(char *buf, int size, const char *fmt, ...);
void *sub_00047560(void *pool, const char *name, int size);
int   sub_00047740(void *p);
void  r1c_HeapSetup(void *pool, int v);

/* 0x538A0: open a memory region in pool slot (waits until the slot's saved pointer is free): name it "REGION: <name>" (or "-"), carve it from the slot's heap (slot 10 uses the heap in slot 8; other slots past 8 hang), remember the old heap and make the region the slot's heap. Returns the new heap. */
void *m2_RegionOpen538A0(int slot, const char *name, int size) {
    char buf[0x80];
    void *h, *r;
    while (m1_poolAux3E26D0[slot] != 0) ;
    if (name != 0) a6b_Printf3(buf, 0x7F, m2_strRegion26BF08, name);
    else a6b_Printf3(buf, 0x7F, m2_strRegionNone26BEFC);
    if (slot == 10) h = m1_pools3E26A8[8];
    else {
        if (slot >= 9) for (;;) ;
        h = m1_pools3E26A8[slot];
    }
    r = sub_00047560(h, buf, size);
    m1_poolAux3E26D0[slot] = m1_pools3E26A8[slot];
    m1_pools3E26A8[slot] = r;
    r1c_HeapSetup(m1_pools3E26A8[slot], sub_00047740(r));
    return m1_pools3E26A8[slot];
}
