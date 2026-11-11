/* Area r4d: model part table helpers around 0x001AEE90-0x001BB928 (r4d_14). Names inferred. */
#include "r4d.h"

/* 0x001AEE90: OR of the masks of all parts that are in use. Stack arg (m). */
uint32_t r4d_PartsMask(R4dModel130 *m)
{
    R4dPart130 *p = m->partsB4;
    uint32_t r = 0;
    int n;
    for (n = m->nB0; n > 0; n--, p++)
        if (p->pBC)
            r |= p->maskB8;
    return r;
}

/* 0x001AEED0: set bits in the mask of every part; returns bits. Stack args (m bits). */
uint32_t r4d_PartsSetMask(R4dModel130 *m, uint32_t bits)
{
    R4dPart130 *p = m->partsB4;
    int i;
    for (i = 0; i < m->nB0; i++, p++)
        p->maskB8 |= bits;
    return bits;
}

/* 0x001AEF10: clear bits in the mask of every part; returns bits. Stack args (m bits). */
uint32_t r4d_PartsClearMask(R4dModel130 *m, uint32_t bits)
{
    R4dPart130 *p = m->partsB4;
    int i;
    for (i = 0; i < m->nB0; i++, p++)
        p->maskB8 &= ~bits;
    return bits;
}

/* 0x001B30C0: for parts whose bone has an index, store base + index. Stack args (m base). */
void r4d_PartsBoneOffset(R4dModel108 *m, int base)
{
    R4dPart108 *p = m->partsC4;
    uint32_t i;
    int v;
    for (i = 0; i < m->nC0; i++, p++) {
        v = p->boneBC->idx38;
        if (v > -1)
            p->valD8 = v + base;
    }
}

/* 0x001B3110: for parts whose bone has an index, store tbl[index]. Stack args (m tbl). */
void r4d_PartsBoneLookup(R4dModel108 *m, const int32_t *tbl)
{
    R4dPart108 *p = m->partsC4;
    uint32_t i;
    int v;
    for (i = 0; i < m->nC0; i++, p++) {
        v = p->boneBC->idx38;
        if (v > -1)
            p->valD8 = tbl[v];
    }
}

/* 0x001BB8E0: same as 0x001B3110 for 0x100-byte parts (value at +0xD0). Stack args (m tbl). */
void r4d_Parts100BoneLookup(R4dModel100 *m, const int32_t *tbl)
{
    R4dPart100 *p = m->partsC4;
    uint32_t i;
    int v;
    for (i = 0; i < m->nC0; i++, p++) {
        v = p->boneBC->idx38;
        if (v > -1)
            p->valD0 = tbl[v];
    }
}
