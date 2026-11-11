/* Area r6c: y_camera.c / y_character.c scene tree helpers around 0x0007E0D0-0x0007F3F0 (r6c_6). Names inferred. */
#include "r6c.h"

/* 0x0007E0D0: copy a camera animation header; returns its track set when the version is 0x65, else NULL. */
A6bTrackSet *r6c_CamAnimCopy(A6bCamAnim *dst, A6bCamAnim *src)
{
    if (!dst)
        return 0;
    if (!src)
        return 0;
    sub_0007F210(dst, src, 0x1C);
    dst->version = src->version;
    if (sub_0007F560(dst, a6b_strYomCamAnim))
        return 0;
    return dst->version == 0x65 ? &src->set : 0;
}

/* 0x0007E1A0: initialise a camera animation: name, version 0x65, ten cleared tracks, one reference. */
int r6c_CamAnimInit(A6bCamAnim *c)
{
    int i;
    sub_0007F1E0(c, 0, 0xCC);
    sub_0007F1E0(c, 0, 0x20);
    a6b_StrCopy(c, a6b_strYomCamAnim);
    c->version = 0x65;
    sub_0007F1E0(&c->set, 0, 0xA8);
    for (i = 0; i < 10; i++)
        a6b_Track_Clear(&c->set.tracks[i]);
    c->set.refs++;
    return 0;
}

/* 0x0007E5C0: attach b's first part to bone c of part n of a. */
int r6c_AttachToPart(R6cTNode *a, int n, int c, R6cTNode *b)
{
    R6cPart *p = a->parts;
    R6cAttach *t = b->parts->att;
    void *m;
    for (; n > 0; n--)
        p = p->next;
    m = sub_0001DAF0(p, c);
    if (t->u80.target)
        sub_001B2080(t);
    sub_001B2020(m, t);
    return 0;
}

/* 0x0007E620: attach b's first part to bone 9 of the current character; -1 for no node. */
int r6c_AttachToHand(R6cTNode *b)
{
    R6cAttach *t;
    uint8_t *m;
    if (!b)
        return -1;
    t = b->parts->att;
    m = sub_000847F0(((R6cObj7 *)a80_ctx42C8E4)->mdl, 9);
    if (t->u80.target)
        sub_001B2080(t);
    sub_001B2020(m, t);
    return 0;
}

/* 0x0007E6C0: release a part chain: free its resource and clear every active flag.
   regargs: p=EAX */
int r6c_NodeRelease(R6cPart *p)
{
    if (p) {
        sub_0001EB80(p);
        sub_00033B30(p);
        if (p->res) {
            if (p->res->handle)
                sub_0008BCC0((void *)p->res->handle);
            sub_0008BCC0(p->res);
            p->res = 0;
        }
        do {
            p->flags &= ~1u;
            p = p->next;
        } while (p);
    }
    return 0;
}

/* 0x0007EC40: add an item to a part list unless it is already a member; -1 for bad arguments.
   regargs: l=ESI it=EDX */
int r6c_ListAddUnique(R6cPList *l, R6cPItem *it)
{
    R6cPItem *p;
    int i = 0;
    if (!l || !it)
        return -1;
    for (p = l->first; p; p = R6C_NEXT(p), i++)
        if (p == it)
            break;
    if (!p || i < 0)
        sub_000830E0(l, it);
    return 0;
}

/* 0x0007EC90: remove an item from a part list; -1 for bad arguments.
   regargs: l=EDI it=ESI */
int r6c_ListRemove(R6cPList *l, R6cPItem *it)
{
    R6cPItem *p, *prev;
    int i = 0;
    if (!l || !it)
        return -1;
    for (p = l->first; p; p = R6C_NEXT(p), i++)
        if (p == it)
            break;
    if (!p)
        return 0;
    if (i < 0)
        return 0;
    if (l->first == it) {
        l->first = it->next;
        l->count--;
        it->next = 0;
        return 0;
    }
    prev = 0;
    for (p = l->first; p; p = R6C_NEXT(p)) {
        if (p == it)
            break;
        prev = p;
    }
    if (!p)
        prev = 0;
    prev->next = it->next;
    l->count--;
    it->next = 0;
    return 0;
}

/* 0x0007EDE0: allocate a 0x20-byte key block holding v; 0, or -2 when out of memory. */
int r6c_KeyNew(R6cKeyObj **out, int v)
{
    R6cBlk20 *b;
    *out = 0;
    a6b_SetHeap(4, a6b_GetHeap(6));
    a6b_SetHeap(5, a6b_GetHeap(6));
    b = (R6cBlk20 *)a6b_Block_Init(0, 0x20, 0x63B, a6b_srcYCharacter);
    *out = (R6cKeyObj *)b;
    if (!b) {
        *out = 0;
        return -2;
    }
    sub_0007F1E0(&b->v18, 0, 8);
    b->v18 = v;
    return 0;
}

/* 0x0007F3B0: free a node, its children and following siblings. */
void r6c_TreeFreeAll(R6cTNode *n)
{
    if (n) {
        r6c_TreeFreeAll(n->child);
        r6c_TreeFreeAll(n->next);
        if (n->flags & 2)
            sub_0008BCC0(n);
        a6b_allocCount3E9308--;
    }
}

/* 0x0007F3F0: insert the sibling chain b after a (b takes a's parent). */
void r6c_TreeInsertAfter(R6cTNode *a, R6cTNode *b)
{
    R6cTNode *parent, *oldNext, *n, *last;
    if (!b)
        return;
    if (!a)
        return;
    parent = a->parent;
    oldNext = a->next;
    a->next = b;
    b->prev = a;
    n = b;
    do {
        last = n;
        n->parent = parent;
        n = n->next;
    } while (n);
    last->next = oldNext;
    if (oldNext)
        oldNext->prev = last;
}
