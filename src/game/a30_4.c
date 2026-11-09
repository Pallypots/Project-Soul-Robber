/* Area a30, group 4: small helpers 0x00047040..0x0004BD80. Names inferred. */
#include "a30.h"

/* 0x00047040: release handle at +0x30 and mark it invalid. */
void a30_Release30(A30Handle30 *o)
{
    if (o) { sub_001AA310(o->handle); o->handle = -1; }
}
/* 0x00047140: release handle at +0x0C and mark it invalid. */
void a30_Release0C(A30Handle0C *o)
{
    if (o) { sub_001AA310(o->handle); o->handle = -1; }
}
/* 0x00047740: read header word 7 dwords before a block unless its flag bit is set. */
int a30_BlockHeaderValue(int32_t *p)
{
    if (p == 0 || (p[-1] & 1)) return 0;
    return p[-7];
}
/* 0x00047B10..0x00047B90: range-checked (3..23) forwarders. */
int a30_Fwd199CA0(int i) { if (i >= 3 && i < 0x18) return sub_00199CA0(i); return 2; }
void a30_Fwd199EB0(int i) { if (i >= 3 && i < 0x18) sub_00199EB0(i); }
int a30_Fwd199F70(int i) { if (i >= 3 && i < 0x18) return sub_00199F70(i); return 0; }
void a30_Fwd19B5F0(int i) { if (i >= 3 && i < 0x18) sub_0019B5F0(i); }
int a30_Fwd19B620(int i) { if (i >= 3 && i < 0x18) return sub_0019B620(i); return 0; }
/* 0x00047F20: read value. */
int a30_Get3DFEC0(void) { return a30_g3DFEC0; }
/* 0x00047F30: read value. */
int a30_Get3DFECC(void) { return a30_g3DFECC; }
/* 0x00047F40: true when the two values differ. */
int a30_Differs(void) { return a30_g3DFEC0 != a30_g3DFEC4; }
/* 0x00048450: clear entry j of record i. */
void a30_ClearRec54(int i, int j) { a30_rec54[i].e[j].w = 0; }
/* 0x000484F0: table size. */
int a30_Pair8Count(void) { return 0x23; }
/* 0x00048500: first field of entry. */
int a30_Pair8A(int i) { return a30_pair8[i].a; }
/* 0x00048510: second field of entry, 0x3E4 when out of range. */
int a30_Pair8B(int i) { if (i >= 0x23) return 0x3E4; return a30_pair8[i].b; }
/* 0x00049860: store value. */
void a30_Set3E05BC(int v) { a30_g3E05BC = v; }
/* 0x0004BD80: call with the two stored values. */
void a30_Call576F0(void) { sub_000576F0(a30_g41316C, a30_g413170); }
