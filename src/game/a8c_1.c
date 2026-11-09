/* Area a8c, group 1: demo system helpers (0x80CF0-0x83450). Names inferred. */
#include "a8c.h"

/* 0x00080D40: nonzero if both mask words intersect the filter masks. */
int a8c_MaskMatch(uint32_t *mask, A8cFilter *f)
{
    if (!(mask[0] & f->mask30)) return 0;
    return (f->mask34 & mask[1]) != 0;
}

/* 0x00081F60: set +0x24 of the node with the given key. */
void a8c_KeyListSetInt(A8cKeyList *l, int key, int v)
{
    A8cKeyNode *n;
    for (n = l->head04; n; n = n->next04)
        if (n->key10 == key) { n->i24 = v; return; }
}

/* 0x00081F90: set float +0x18 of the node with the given key. */
void a8c_KeyListSetFloat(A8cKeyList *l, int key, float v)
{
    A8cKeyNode *n;
    for (n = l->head04; n; n = n->next04)
        if (n->key10 == key) { n->f18 = v; return; }
}

/* 0x00082270: run 0x81B10 on every chained node. */
void a8c_ChainApply(A8cChainOwner *o)
{
    A8cChainNode *n;
    if (o == 0) return;
    for (n = o->head08; n; n = n->next04)
        sub_00081B10(*o->ctx00, n);
}

/* 0x000822A0: fill the shared buffer at 0x3EC448 and return it. */
uint8_t *a8c_FillShared(int a, int b, int c)
{
    sub_00082200(a, b, c, a8c_buf3EC448);
    return a8c_buf3EC448;
}

/* 0x00082720: attach child c under parent p (push front). */
void a8c_AttachChild(A8cLinkObj *p, A8cLinkObj *c)
{
    c->parent80 = p;
    if (p->child88) c->sib84 = p->child88;
    p->child88 = c;
}

/* 0x00082D70: apply 0x1A3F50 to the 0x1AD9D0 transform of x. */
void a8c_ApplyTransformed(float x)
{
    sub_001A3F50(sub_001AD9D0(x));
}

/* 0x00082F40: append a callback node to the end of the list. */
void a8c_CbAppend(A8cCbOwner *o, A8cCbNode *n)
{
    A8cCbNode *p = o->head24;
    if (p == 0) { o->head24 = n; return; }
    while (p->next00) p = p->next00;
    p->next00 = n;
}

/* 0x00082F70: find the callback node with the given function. */
A8cCbNode *a8c_CbFind(A8cCbOwner *o, void *fn)
{
    A8cCbNode *n;
    for (n = o->head24; n; n = n->next00)
        if ((void *)n->fn04 == fn) break;
    return n;
}

/* 0x00082F90: call every callback of b with a's +0x1C value. */
void a8c_CbRunAll(A8cCbOwner *a, A8cCbOwner *b)
{
    A8cCbNode *n;
    for (n = b->head24; n; n = n->next00)
        n->fn04(n, a->i1C);
}

/* 0x00082FC0: frame count rounded up to whole seconds. */
int a8c_FramesToSeconds(A8cCbOwner *o)
{
    return (o->i14 * 60 + 59) / 60;
}

/* 0x00083120: find entry by key +0. */
A8cEntry *a8c_EntryFind0(A8cEntryOwner *o, int key)
{
    A8cEntry *e;
    for (e = o->head10; e; e = e->next20)
        if (key == e->key00) break;
    return e;
}

/* 0x00083140: find entry by key +4. */
A8cEntry *a8c_EntryFind4(A8cEntryOwner *o, int key)
{
    A8cEntry *e;
    for (e = o->head10; e; e = e->next20)
        if (key == e->key04) break;
    return e;
}

/* 0x00083420: set +0x14 of the entry with key +0. */
void a8c_EntrySet14(A8cEntryOwner *o, int key, int v)
{
    A8cEntry *e;
    for (e = o->head10; e; e = e->next20)
        if (key == e->key00) break;
    if (e) e->val14 = v;
}

/* 0x00083450: +8 of the entry with key +0, or 0. */
int a8c_EntryGet08(A8cEntryOwner *o, int key)
{
    A8cEntry *e;
    for (e = o->head10; e; e = e->next20)
        if (key == e->key00) break;
    if (e) return e->val08;
    return 0;
}

/* 0x00081FC0: reset a key node's payload (+0x18 = 83880000.0). */
void a8c_KeyNodeReset(int32_t *p)
{
    p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
    ((float *)p)[6] = 83880000.0f;
    p[7] = 0; p[8] = 0; p[9] = 0;
}

/* 0x000820C0: unlink a chain node from its owner (owner at +0, next at +4). */
void a8c_ChainUnlink(A8cChainNode *n)
{
    A8cChainNode *owner, *q;
    if (n == 0) return;
    owner = *(A8cChainNode **)n;
    if (owner == 0) return;
    q = owner->next04;
    if (q == n) { owner->next04 = n->next04; return; }
    for (; q; q = q->next04)
        if (q->next04 == n) { q->next04 = n->next04; return; }
}

/* 0x00082FF0: free an entry chain recursively (tail first). */
int a8c_EntryFreeChain(A8cEntry *e)
{
    int r;
    if (e == 0) return 0;
    r = a8c_EntryFreeChain(e->next20);
    if (r) return r;
    if (e->i0C) e->i0C = 0;
    sub_00053880(e);
    return 0;
}

/* 0x00083030: allocate and initialise an entry (key04 = b, +0x14 = a, +0x1C = c). */
A8cEntry *a8c_EntryNew(int a, int b, int c)
{
    A8cEntry *e = (A8cEntry *)a5b_AllocCur(0x24, 0, 0x1D5);
    e->key04 = b;
    e->key00 = 0; e->val08 = 0;
    e->i0C = 0; e->i10 = 0; e->i18 = 0;
    e->val14 = a;
    e->i1C = c;
    return e;
}

/* 0x000830E0: append an entry and bump the count at +0xC. */
void a8c_EntryAppend(A8cEntryOwner *o, A8cEntry *e)
{
    A8cEntry *p = o->head10;
    if (p == 0) { o->head10 = e; o->count0C++; return; }
    while (p->next20) p = p->next20;
    p->next20 = e;
    o->count0C++;
}

/* 0x000833E0: 1 unless the object at +0x14 has state bit 1 without its +0xBC bit 1. */
int a8c_IsIdle(A8cModelRef *x)
{
    uint8_t *m;
    if (x == 0) return 1;
    m = x->model14;
    if (m == 0) return 1;
    if ((sub_001AEE50(m, 0) & 2) && !(m[0xBC] & 2)) return 1;
    return 0;
}

/* 0x00083CA0: end of the packed channel data (count records of n*16 + 16 bytes). */
int32_t *a8c_ChanDataEnd(A8cChanHdr *h)
{
    int n = 1, k;
    int32_t *p;
    if (h->flags04 & 1) n = 2;
    if (h->flags04 & 2) n++;
    if (h->flags04 & 4) n++;
    p = h->data60;
    for (k = h->count00; k > 0; k--)
        p = (int32_t *)((uint8_t *)p + *p * n * 16 + 16);
    return p;
}

/* 0x00083CF0: address past one packed channel record. */
uint8_t *a8c_ChanRecordEnd(A8cChanHdr *h, int32_t *rec)
{
    int n = 1;
    if (h->flags04 & 1) n = 2;
    if (h->flags04 & 2) n++;
    if (h->flags04 & 4) n++;
    return (uint8_t *)rec + (*rec * n + 1) * 16;
}
