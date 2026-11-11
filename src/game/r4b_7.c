/* Area r4b: texture entry helpers around 0x001B9650-0x001B9C95 (r4b_7). Names inferred. */
#include "r4b.h"

/* 0x001B9650: texture entry for idx (negative ids select the double-buffered render targets). Stack args. */
R4bTexEnt *r4b_TexEntGet(int idx)
{
    if (idx >= 0)
        return &r4b_g40F750[idx];
    switch (idx) {
    case -1:
        return &r4b_g40F398[(r4b_g40F754 - 1) & 1];
    case -3:
        return &r4b_g40F448[(r4b_g40F754 - 1) & 1];
    case -4:
        return &r4b_g40F448[r4b_g40F754 & 1];
    case -2:
    default:
        return &r4b_g40F398[r4b_g40F754 & 1];
    }
}

/* 0x001B96D0: count down the timer of every used texture entry and publish it to the user. No inputs. */
void r4b_TexTickTimers(void)
{
    R4bTexTable *t = r4_g40F390;
    R4bTexEnt *e;
    uint32_t i;
    for (i = 0, e = r4b_g40F750; i < t->count; i++, e++) {
        if (e->flags & 1) {
            if (--e->timer18 < 0)
                e->timer18 = 0;
            if (e->user50)
                e->user50->timer = e->timer18;
        }
    }
}

/* 0x001B9720: reinitialise heap 2. No inputs. */
void r4b_TexHeapInit(void)
{
    r4_Heap2Init();
}

/* 0x001B9730: pass heap-2 word +0x0C (and 0) to 0x001BB710. No inputs. */
void r4b_TexHeapApply(void)
{
    sub_001BB710(r4_Heap2Word0C(), 0);
}

/* 0x001B9C90: the texture table. No inputs. */
R4bTexTable *r4b_TexTable(void)
{
    return r4_g40F390;
}

/* 0x001B9FC0: free texture entry idx: unlink it, move it to the free list and release its storage;
   returns 1 if another entry still uses the same key. Stack args; calls 0x001B9B90 with ESI=group ECX=key. */
int r4b_TexFree(int idx)
{
    R4bTexEnt *e = &r4b_g40F750[idx];
    R4bTexTable *t;
    int k;
    if (!(e->flags & 1))
        return 0;
    sub_001A64F0(e);
    e->flags &= ~1;
    t = r4_g40F390;
    if (e->next20)
        e->next20->prev24 = e->prev24;
    else
        t->last = e->prev24;
    if (e->prev24)
        e->prev24->next20 = e->next20;
    else
        t->first = e->next20;
    e->next20 = 0;
    if (t->freeLast) {
        t->freeLast->next20 = e;
        e->prev24 = t->freeLast;
    } else {
        t->freeFirst = e;
        e->prev24 = 0;
    }
    t->used--;
    t->freeLast = e;
    k = r4_TexFindByKey(e->group1E, e->key);
    if (k == -1) {
        if (e->flags & 2)
            sub_001B9950(e->v28, e->v30, e->v38, e->v40, (e->flags >> 2) & 1);
        else if (e->user50)
            sub_001BB710(e->user50->w1C, e->user50->w1E);
    }
    return k != -1;
}

/* 0x001BA0B0: set the current texture group; returns the previous one (0xFFFF without a table). Stack args. */
uint16_t r4b_TexSetGroup(uint16_t g)
{
    R4bTexTable *t = r4_g40F390;
    uint16_t old;
    if (t) {
        old = t->group1C;
        t->group1C = g;
        return old;
    }
    return 0xFFFF;
}

/* 0x001BA0D0: the current texture group (0xFFFF without a table). No inputs. */
uint16_t r4b_TexGetGroup(void)
{
    R4bTexTable *t = r4_g40F390;
    if (!t)
        return 0xFFFF;
    return t->group1C;
}

/* 0x001BA640: set the frame parity. Stack args. */
void r4b_TexSetParity(uint32_t v)
{
    r4b_g40F754 = v;
}

/* 0x001BA650: install the texture table in a buffer of size bytes (or none) and reset it. Stack args (t size). */
void r4b_TexInit(R4bTexTable *t, uint32_t size)
{
    if (t) {
        t->size = size;
        t->count = (size - 0x20) / sizeof(R4bTexEnt);
        t->used = 0;
        t->group1C = 0xFFFF;
        r4b_g40F758 = t;
        r4_g40F390 = t;
        r4b_g40F750 = (R4bTexEnt *)(t + 1);
    } else {
        r4b_g40F758 = 0;
    }
    sub_001B93E0();
    sub_001BA170();
    r4b_g40F754 = 0;
}
