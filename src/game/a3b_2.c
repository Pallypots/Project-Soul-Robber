/* Area a3b, group 2: object/list helpers near 0x00033250. Names inferred. */
#include "a3b.h"

/* 0x00033250: per-frame update in special mode. */
void a3b_UpdateMode100(void)
{
    if (a3b_mode381AB8 == 100) {
        sub_00033130();
        sub_000331D0();
        if (a3b_g381834) sub_00079340();
    }
}

/* 0x000335D0: release the sub-object at +0x10. */
int a3b_ReleaseSub(char *p)
{
    if (p) sub_00033560(p + 0x10);
    return 0;
}

/* 0x000336A0: header word 16 bytes before the pointer is nonzero. */
int a3b_HeaderSet(int32_t *p) { return p[-4] != 0; }

/* 0x00033880: forward +0x20 when the object is idle. */
void a3b_ForwardIfIdle(int32_t *p, int a)
{
    if (p && p[0] == 0) sub_001ADA40(a, (char *)p + 0x20);
}

/* 0x00033AB0: set flag bit 0. */
void a3b_ObjSetFlag(A3bObj *o) { if (o) o->flags |= 1; }

/* 0x00033AC0: clear flag bit 0. */
void a3b_ObjClearFlag(A3bObj *o) { if (o) o->flags &= ~1u; }

/* 0x00033B10: release the sub-object when its owner matches. */
int a3b_ReleaseIfOwner(A3bObj *o, int owner)
{
    if (owner && o->f24 == owner) sub_00033560((char *)o + 0x10);
    return 0;
}

/* 0x00033DA0: clear entry i of a table. */
void a3b_TableClear(A3bTable *t, int i)
{
    if (i >= 0 && i < t->count) t->entries[i].f00 = 0;
}

/* 0x00033DC0: find an item by key in a list. */
A3bItem *a3b_ListFind(A3bList *l, int key)
{
    A3bNode *n;
    for (n = l->head; n; n = n->next)
        if (n->item->key == key) return n->item;
    return 0;
}

/* 0x000341A0: forward fields +4 and +8. */
void a3b_ObjForward(A3bObj *o)
{
    if (o) sub_00053350(o->flags, o->f08);
}

/* 0x000341C0: release object. */
int a3b_Release(void *p)
{
    if (p) sub_0003D860(p);
    return 0;
}

/* 0x000342A0: iterate 0x6C records at base+0x55140. */
void a3b_IterA(void) { sub_00036B30(a3b_base283698 + 0x55140, 0x6C, sub_00034270, 0); }

/* 0x00034370: iterate 0xB40 records at base. */
void a3b_IterB(void) { sub_00036B30(a3b_base283698, 0xB40, sub_000342C0, 0); }
