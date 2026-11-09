/* Area a80, group 1: pool init and small object field helpers. Names inferred. */
#include "a80.h"

/* 0x00080970: reset the static pool (capacity 0x80) and return it. */
A80Pool *a80_PoolReset(void)
{
    a80_pool.used = 0;
    a80_pool.head = 0;
    a80_pool.capacity = 0x80;
    a80_pool.storage = a80_poolStorage;
    return &a80_pool;
}
/* 0x000809A0: OR bits into flags08. */
void a80_OrFlags08(A80Obj *o, uint32_t bits) { o->flags08 |= bits; }
/* 0x00080D20: set a pair to -1/-1 (invalid). */
void a80_PairInvalidate(A80Pair *p) { p->a = -1; p->b = -1; }
/* 0x00080D80: test bits in sub50's mask. */
uint32_t a80_TestSubMask(A80Obj *o, uint32_t bits) { return o->sub50->mask30 & bits; }
/* 0x00080D90: get sub50's mask. */
uint32_t a80_GetSubMask(A80Obj *o) { return o->sub50->mask30; }
/* 0x00082100: set field 0x24. */
void a80_SetX24(A80Obj *o, int32_t v) { o->x24 = v; }
/* 0x00082110: set float field 0x18. */
void a80_SetF18(A80Obj *o, float v) { o->f18 = v; }
/* 0x00082120: OR bits into flags30. */
void a80_OrFlags30(A80Obj *o, uint32_t bits) { o->flags30 |= bits; }
/* 0x00082700: allocate n 0x108-byte records (tag 0x37). */
void a80_AllocRecords(int n) { sub_00053AB0(n * 0x108, 0, 0x37); }
/* 0x00082F00: forward to 0x82C80 with the default table. */
void a80_ForwardDefault(int a, int b) { sub_00082C80(a, b, a80_tbl2E0380); }
/* 0x00082F20: clear a pair and set its second word. */
void a80_PairSetB(A80Pair *p, int32_t b) { p->a = 0; p->b = b; }
