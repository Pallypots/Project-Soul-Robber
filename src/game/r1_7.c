/* Area r1, group 7: stream, heap, key-table and string helpers 0x00047060..0x0004FA50. Names inferred. */
#include "r1.h"
#include <string.h>

/* 0x00047060: wait until a stream's request is accepted.
   regargs: s=ESI */
void r1_StreamWait(R1Stream *s)
{
    if (s->handle == -1) return;
    while (sub_001AA520(s->handle) == -1) ;
}

/* 0x00047080: best-fitting free block for size bytes (rounded to 64 plus header), or null.
   regargs: h=ECX size=EDX */
R1Blk *r1_HeapFindFit(R1Heap *h, int size)
{
    R1BlkNode *n;
    R1Blk *best = 0, *b;
    uint32_t need;
    n = h->nodes;
    if (n == 0) return 0;
    need = (size + 0x7F) & ~0x3F;
    for (; n; n = n->next) {
        b = n->blk;
        if (b->avail >= need && (best == 0 || (int32_t)b->avail < (int32_t)best->avail)) best = b;
    }
    return best;
}

/* 0x00047160: reset a heap to one free block covering it all.
   regargs: h=ECX */
void r1_HeapReset(R1Heap *h)
{
    R1Blk *b = h->first;
    h->cur = b;
    b->w0C = 0;
    b->w08 = 0;
    b->avail = h->size;
    b->owner = h;
    b->w24 = h->size - 0x44;
    b->w00 = 0;
    b->self = b;
    b->w30 = 0;
    sub_0003D880(h->list0C, h->first->link10);
}

/* 0x00048470: 16-bit value k of the key-table record (a,b), or -1.
   regargs: a=EBX b=EDI; k is the stack argument */
int r1_KeyWord(int a, int b, int k)
{
    R1KeyRec *r = r1_keyTbl;
    int i;
    for (i = 0; r->a != -1; i++, r++)
        if (r->a == a && r->b == b) return r1_keyTbl[i].u.w[k];
    return -1;
}

/* 0x000484B0: 32-bit value of the key-table record (a,b), or -1.
   regargs: a=EBX b=EDI */
int r1_KeyDword(int a, int b)
{
    R1KeyRec *r = r1_keyTbl;
    int i;
    for (i = 0; r->a != -1; i++, r++)
        if (r->a == a && r->b == b) return r1_keyTbl[i].u.d.hi;
    return -1;
}

/* 0x0004F8B0: copy src from offset n into dst, or an empty string when src is not longer than n.
   regargs: src=EBX n=ESI dst=EDX */
void r1_CopyTail(char *dst, const char *src, uint32_t n)
{
    if (strlen(src) > n) strcpy(dst, src + n);
    else *dst = 0;
}

/* 0x0004FA50: query value 1 of p into a local and return the status.
   regargs: p=ECX */
int r1_Query1(void *p)
{
    int v;
    return sub_001A8500(p, 1, &v);
}
