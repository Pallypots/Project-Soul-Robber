/* Area a3c, group 4: pool and list walkers near 0x00033770..0x00036A90. Names inferred. */
#include "a3c.h"

/* 0x00033770: copy two vectors into an active node. */
void a3c_NodeSetVecs(A3cPNode *n, const void *a, const void *b)
{
    if (n && n->busy == 1) {
        a3c_VecCopy(n->sub20, a);
        a3c_VecCopy(n->sub30, b);
    }
}

/* 0x000338A0: run 0x001B60C0 on every idle node. */
void a3c_ListIdleA(A3cPNode *n)
{
    for (; n; n = n->next)
        if (n->busy == 0) sub_001B60C0(n->sub20);
}

/* 0x00033A40: run 0x001B6130 on every idle node. */
void a3c_ListIdleB(A3cPNode *n)
{
    for (; n; n = n->next)
        if (n->busy == 0) sub_001B6130(n->sub20);
}

/* 0x00033B30: release records owned by each chained object. */
void a3c_ReleaseOwnedChain(A3cChain3C *c)
{
    for (; c; c = c->next)
        sub_00036B30(a3b_base283698, 0xB40, sub_00033B10, c);
}

/* 0x00033BF0: visit the records with a pair of values. */
void a3c_VisitPair(int a, int b)
{
    A3cPair pr;
    pr.a = a;
    pr.b = b;
    sub_00036B30(a3b_base283698, 0xB40, sub_00033B70, &pr);
}

/* 0x00034B70: release both record pools. */
void a3c_ReleasePools(void)
{
    sub_00036B30(a3b_base283698, 0xB40, sub_000335D0, 0);
    sub_00036B30(a3b_base283698 + 0x55140, 0x6C, sub_00034B50, 0);
}

/* 0x00034DD0: apply 0x000337A0 to every node. */
void a3c_ListApplyA(A3cPNode *n, void *a, void *b, void *c)
{
    for (; n; n = n->next) sub_000337A0(n, a, b, c);
}

/* 0x00034E00: apply 0x00033800 to every node. */
void a3c_ListApplyB(A3cPNode *n, void *a, void *b, void *c)
{
    for (; n; n = n->next) sub_00033800(n, a, b, c);
}

/* 0x00034E60: forward to the +0xA5C block of every idle node. */
void a3c_ListIdleForward(A3cPNode *n, float a)
{
    for (; n; n = n->next)
        if (n->busy == 0) sub_001B6A60((char *)n + 0xA5C, a);
}

/* 0x00034F00: apply 0x000338D0 to every node. */
void a3c_ListApplyC(A3cPNode *n, int a, int b)
{
    for (; n; n = n->next) sub_000338D0(n, a, b);
}

/* 0x00034F30: apply 0x000338D0 with each node's own +0x18 value. */
void a3c_ListApplyOwn(A3cPNode *n, int a)
{
    for (; n; n = n->next) sub_000338D0(n, a, n->f18);
}

/* 0x000362B0: run 0x00036290 over the records for each chained object. */
void a3c_VisitChain(A3cChain3C *c)
{
    for (; c; c = c->next)
        sub_00036B30(a3b_base283698, 0xB40, sub_00036290, c);
}

/* 0x000367B0: walk the sub-object at +0x10 and free it unless flagged. */
int a3c_WalkAndFree(char *p)
{
    uint8_t *s = (uint8_t *)p + 0x10;
    sub_0005A510(s, sub_000362F0);
    if (!(*s & 1)) sub_00033C20(s);
    return 0;
}

/* 0x00036A90: build a free pool of count-1 entries of `stride` bytes after the header. */
void a3c_PoolInit(A3cPoolHdr *h, int stride, int count)
{
    A3cPoolEnt *e;
    int i;
    h->count = count - 1;
    h->head = 0;
    e = (A3cPoolEnt *)((char *)h + stride);
    for (i = 0; i < h->count; i++) {
        e->f00 = 0;
        e->owner = h;
        e = (A3cPoolEnt *)((char *)e + stride);
    }
}
