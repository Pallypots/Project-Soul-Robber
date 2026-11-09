/* Small record helpers (0x0005A6D0-0x0005BBCA), second pass.
 * Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a5b.h"

/* 0x0005A6D0: store the second field of a pair. */
void a5b_PairSet(A5bPair *p, int value)
{
    p->value = value;
}

/* 0x0005A6E0: reset a timer to 60 units per second. */
void a5b_TimerInit(A5bTimer *t)
{
    t->unk00 = 0;
    t->rate = 60.0f;
    t->unk08 = 0;
    t->unk0C = 0;
}

/* 0x0005A700: clear one slot record. */
void a5b_SlotClear(A5bSlot *s)
{
    s->used = 0;
    s->f04 = 0.0f;
    s->id = -1;
    s->unk08 = 0;
    s->unk10 = 0;
}

/* 0x0005A720: count the leading list items whose flag bit 0 is set. */
int a5b_CountLeadingFlagged(void *list)
{
    int n = a12_List_Count(list);
    int i;
    for (i = 0; i < n; i++) {
        uint8_t *item = (uint8_t *)a12_List_At(list, i);
        if (item == 0 || !(item[0xC] & 1))
            break;
    }
    return i;
}

/* 0x0005A850: number of used slots. */
int a5b_SlotCountUsed(A5bSlotList *l)
{
    int n = 0;
    int i;
    A5bSlot *s = l->slots;
    for (i = l->count; i > 0; i--, s++)
        if (s->used != 0)
            n++;
    return n;
}

/* 0x0005A870: index of the next used slot after `i`, or -1. */
int a5b_SlotNextUsed(A5bSlotList *l, int i)
{
    for (i++; i < l->count; i++)
        if (l->slots[i].used != 0)
            break;
    if (i >= l->count)
        return -1;
    return i;
}

/* 0x0005A8B0: attach and clear `count` slot records. */
void a5b_SlotListInit(A5bSlotList *l, int count, A5bSlot *slots)
{
    int i;
    l->count = count;
    l->slots = slots;
    for (i = 0; i < count; i++) {
        slots[i].used = 0;
        slots[i].f04 = 0.0f;
        slots[i].id = -1;
        slots[i].unk08 = 0;
        slots[i].unk10 = 0;
    }
}

/* 0x0005A8F0: index of the first used slot, or -1. */
int a5b_SlotFirstUsed(A5bSlotList *l)
{
    int i;
    for (i = 0; i < l->count; i++)
        if (l->slots[i].used != 0)
            break;
    if (i >= l->count)
        return -1;
    return i;
}

/* 0x0005A990: store two parameters and run 0x0003F9C0 with table 0x002DD450. */
int a5b_Run3F9C0(int a, int b, int c)
{
    a5b_g3E4B54 = b;
    a5b_g3E4B58 = c;
    return sub_0003F9C0(a, a5b_tbl2DD450);
}

/* 0x0005BB70: sort comparator, descending by the float at item->+0xC->+0x24. */
int a5b_CompareDesc24(void *a, void *b)
{
    float fa = *(float *)(*(uint8_t **)((uint8_t *)a + 0xC) + 0x24);
    float fb = *(float *)(*(uint8_t **)((uint8_t *)b + 0xC) + 0x24);
    if (fa > fb)
        return -1;
    if (fb > fa)
        return 1;
    return 0;
}

/* 0x0005BBB0: exchange the value at 0x002DD4D8. */
int a5b_Swap2DD4D8(int v)
{
    int old = a5b_g2DD4D8;
    a5b_g2DD4D8 = v;
    return old;
}

/* 0x0005BBC0: clear 0x003E6040. */
void a5b_Clear3E6040(void)
{
    a5b_g3E6040 = 0;
}
