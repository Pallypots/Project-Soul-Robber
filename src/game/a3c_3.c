/* Area a3c, group 3: list and state helpers near 0x0003C9B0..0x0003FA70. Names inferred. */
#include "a3c.h"

/* 0x0003C9B0: notify, then run the follow-up step. */
int a3c_NotifyThenStep(int a)
{
    sub_001A1130(a);
    return sub_0003C3C0();
}

/* 0x0003CFC0: select entry i and cache its table value. */
void a3c_SelectEntry(int i)
{
    a3c_g3DDCB8 = i;
    a3c_g2C4AE8 = a3c_tbl2C4AD0[i];
}

/* 0x0003D090: slot i of the table at 0x003DDCC0. */
int a3c_SlotGet(int i) { return a3c_tbl3DDCC0[i]; }

/* 0x0003D100: make slot i current when it is in use. */
void a3c_SlotSelect(int i)
{
    if (a3c_tbl3DDCC0[i]) a3c_g3DDCE8 = i;
}

/* 0x0003D860: zero a four-word list header. */
void a3c_Clear16(A3cQuad *q)
{
    q->f00 = 0;
    q->f04 = 0;
    q->f08 = 0;
    q->f0C = 0;
}

/* 0x0003DB40: forward a range record's fields. */
void a3c_RangeForward(A3cTriple *r, int a)
{
    sub_0003D990(r, r->f04, r->f08, a);
}

/* 0x0003DBA0: id at +0x0C equals k. */
int a3c_IdIs(A3cId0C *p, int k) { return p->id == k; }

/* 0x0003DC50: unlink and return the second node. */
void *a3c_TakeSecond(A3cHolder *h)
{
    void *n = h->second;
    if (!n) return 0;
    sub_0003D8C0(n);
    return n;
}

/* 0x0003DC70: unlink and return the first node. */
void *a3c_TakeFirst(A3cHolder *h)
{
    void *n = h->first;
    if (!n) return 0;
    sub_0003D8C0(n);
    return n;
}

/* 0x0003DC90: reset the flags and the two default sizes. */
void a3c_HeapDefaults(void)
{
    a3c_flags3DE4F8 = 0;
    a3c_g3DE4F0 = 0x3000;
    a3c_g3DE4F4 = 0x3800;
}

/* 0x0003DCE0: run the hook when flag 2 is set; pass the argument through. */
int a3c_HookPass(int v)
{
    if (a3c_flags3DE4F8 & 2) sub_001A7490();
    return v;
}

/* 0x0003DD00: set flag 1. */
void a3c_FlagSet1(void) { a3c_flags3DE4F8 |= 1; }

/* 0x0003DD10: clear the flags and shut down. */
void a3c_FlagsClearShutdown(void)
{
    a3c_flags3DE4F8 = 0;
    sub_001B9720();
}

/* 0x0003DDE0: first word of session slot 1 or 0. */
int a3c_SessionWord(int second)
{
    return second ? *(int32_t *)g_sessionSlots[1].b : *(int32_t *)g_sessionSlots[0].b;
}

/* 0x0003DE00: screen width. */
int a3c_ScreenW(void) { return 0x200; }

/* 0x0003DE10: screen height. */
int a3c_ScreenH(void) { return 0xE0; }

/* 0x0003F770: call 0x0003ED50 with a zero second argument. */
int a3c_CallED50(int a) { return sub_0003ED50(a, 0); }

/* 0x0003F9C0: call 0x0003F8B0 with a zero third argument. */
int a3c_CallF8B0(int a, int b) { return sub_0003F8B0(a, b, 0); }

/* 0x0003FA70: pointer to entry i of an offset table (hang when out of range). */
void *a3c_OffTabGet(A3cOffTab *t, uint32_t i)
{
    if (!t) return 0;
    if (t->count <= i) for (;;) ;
    return (char *)t + t->off[i];
}

/* 0x0003D1A0: copy record j of slot i out to dst. */
void a3c_SlotRecGet(int i, int j, void *dst)
{
    if (a3c_tbl3DDCC0[i]) a3c_VecCopy(dst, &a3c_ptr3DDCE0[i][j]);
}

/* 0x0003D1E0: copy src into record j of slot i. */
void a3c_SlotRecSet(int i, int j, const void *src)
{
    if (a3c_tbl3DDCC0[i]) a3c_VecCopy(&a3c_ptr3DDCE0[i][j], src);
}

/* 0x0003D220: copy the +0x20 part of record j of slot i out to dst. */
void a3c_SlotRecGet20(int i, int j, void *dst)
{
    if (a3c_tbl3DDCC0[i]) a3c_VecCopy(dst, a3c_ptr3DDCE0[i][j].sub20);
}

/* 0x0003D260: copy src into the +0x20 part of record j of slot i. */
void a3c_SlotRecSet20(int i, int j, const void *src)
{
    if (a3c_tbl3DDCC0[i]) a3c_VecCopy(a3c_ptr3DDCE0[i][j].sub20, src);
}

/* 0x0003D6C0: initialise a task with its callback and argument. */
void a3c_TaskInit(A3cTask *t, int arg)
{
    sub_001B2150(t);
    t->fn = (void *)sub_0003D540;
    t->arg = arg;
    t->f14 = 0;
    sub_001B26C0(t->sub18);
}
