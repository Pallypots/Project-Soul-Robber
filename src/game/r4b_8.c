/* Area r4b: texture group, type-17 nodes and heap setup around 0x001BA7F0-0x001BB2DF (r4b_8). Names inferred. */
#include "r4b.h"

/* 0x001BA7F0: call 0x001BA6E0 with the current texture group (0xFFFF without a table). Stack args. */
int r4b_TexWithGroup(int x)
{
    R4bTexTable *t = r4_g40F390;
    if (!t)
        return sub_001BA6E0(0xFFFF, x);
    return sub_001BA6E0(t->group1C, x);
}

/* 0x001BA820: initialise a type-17 node; returns n. Stack args. */
R4bNodeP *r4b_NodeInitType17(R4bNodeP *n)
{
    n->type8C = 0x11;
    sub_001B25B0(n);
    n->colB0[0] = 128.0f;
    n->colB0[1] = 128.0f;
    n->colB0[2] = 128.0f;
    n->colB0[3] = 128.0f;
    n->iC0 = 0;
    n->iE4 = 0;
    n->countD0 = 0;
    n->recsD4 = 0;
    n->iE8 = 0;
    n->iF0 = 0;
    n->iC4 = 0;
    n->iC8 = 0;
    n->iE0 = 0x48;
    n->fEC = 0.2f;
    return n;
}

/* 0x001BA8B0: restart with k steps. Stack args (n k). */
void r4b_NodePStart(R4bNodeP *n, int k)
{
    n->iC0 = 0;
    n->iF0 = k;
    n->iF4 = 0;
    n->iC4 = 0;
    n->fEC = 1.0f / (float)k;
}

/* 0x001BA8F0: rewind. Stack args. */
void r4b_NodePRewind(R4bNodeP *n)
{
    n->iC0 = 0;
    n->iF4 = 0;
    n->iC4 = 0;
}

/* 0x001BA910: bind records recs to the parts listed in ids (terminated by a negative id). Stack args (n unused ids recs). */
void r4b_NodePBindParts(R4bNodeParts *n, int unused, const int *ids, R4bPartRec *recs)
{
    int count = 0;
    const int *p;
    R4bNodeP *np = (R4bNodeP *)n;
    for (p = ids; *p >= 0; p++)
        count++;
    np->countD0 = count;
    np->recsD4 = recs;
    np->iD8 = 0;
    for (p = ids; *p >= 0; p++, recs++)
        recs->part = &n->parts[*p];
}

/* 0x001BB210: store three values at 0x00412F40. Stack args. */
void r4b_Set412F40(int a, int b, int c)
{
    r4b_g412F40[0] = a;
    r4b_g412F40[1] = b;
    r4b_g412F40[2] = c;
}

/* 0x001BB230: address of the three values at 0x00412F40. No inputs. */
int32_t *r4b_Get412F40(void)
{
    return r4b_g412F40;
}

/* 0x001BB2A0: install heap 1 in a buffer of size bytes (or none) and clear it. Stack args (h size). */
void r4b_HeapInit(R4bHeap *h, uint32_t size)
{
    if (!h) {
        r4b_g40F764 = 0;
        return;
    }
    h->size = size;
    h->count = (size - 0xC) >> 4;
    h->first = 0;
    r4b_g40F764 = h;
    r4_g40F75C = h;
    r4_g40F760 = (R4bBlk *)((uint8_t *)h + 0xC);
    r4_HeapClearUsed();
}
