/* Area r6c: collision and bounding helpers around 0x0007FD60-0x00084730 (r6c_9). Names inferred. */
#include "r6c.h"

/* 0x0007FD60: clear record i of the child entity (types 2 and 10) of an entity of type 1 or 9. */
void r6c_ChildClearRec(R6cEnt8C *e, int i)
{
    R6cEnt8C *c;
    switch (e->type) {
    case 1:
    case 9:
        c = e->child;
        if (!c)
            return;
        switch (c->type) {
        case 2:
            ((R6cEnt2 *)c)->recs[i].v = 0;
            break;
        case 10:
            ((R6cEnt10 *)c)->recs[i].v = 0;
            break;
        }
        break;
    }
}

/* 0x00080CB0: pick the nearest hit with one of the two search methods (flag bit 0 of +0x08).
   calls 0x00080A60 with ECX=c; 0x000809C0 with EBX=a ECX=c */
void *r6c_PickNearest(R6cColl *a, const R6cVec4 *b, const R6cVec4 *c)
{
    if (a->flags & 1)
        return sub_00080A60(a, b, c);
    return sub_000809C0(a, b, c);
}

/* 0x00080DA0: allocate an empty bounding box record. */
R6cBox *r6c_BoxNew(void *a, void *b)
{
    R6cBox *x = sub_00053AB0(0x40, 0, 0x96);
    x->max[2] = -8388000.0f;
    x->max[1] = -8388000.0f;
    x->max[0] = -8388000.0f;
    x->i30 = 0;
    x->p08 = a;
    x->p0C = b;
    x->i00 = 0;
    x->i04 = 0;
    x->max[3] = 1.0f;
    x->min[2] = 8388000.0f;
    x->min[1] = 8388000.0f;
    x->min[0] = 8388000.0f;
    x->min[3] = 1.0f;
    return x;
}

/* 0x00080F20: grow a bounding box to include lo..hi. */
void r6c_BoxExtend(R6cBox *x, const float *lo, const float *hi)
{
    if (hi[0] > x->max[0]) x->max[0] = hi[0];
    if (hi[1] > x->max[1]) x->max[1] = hi[1];
    if (hi[2] > x->max[2]) x->max[2] = hi[2];
    if (x->min[0] > lo[0]) x->min[0] = lo[0];
    if (x->min[1] > lo[1]) x->min[1] = lo[1];
    if (x->min[2] > lo[2]) x->min[2] = lo[2];
}

/* 0x00081B10: remove an item from the item chain of any node of a binary tree; 1 when found. */
int r6c_BTreeRemove(R6cBNode *n, R6cBItem *it)
{
    R6cBItem *p = n->items;
    if (p) {
        if (p == it) {
            n->items = it->next;
            return 1;
        }
        do {
            if (p->next == it) {
                p->next = it->next;
                return 1;
            }
            p = p->next;
        } while (p);
    }
    if (n->left && r6c_BTreeRemove(n->left, it) == 1)
        return 1;
    if (n->right && r6c_BTreeRemove(n->right, it) == 1)
        return 1;
    return 0;
}

/* 0x00081FF0: collect the hits of src and give them to owner; 1 when there were any. */
int r6c_CollectHits(R6cHitOwner *owner, R6cHitSrc *src)
{
    R6cHit *h;
    if (!src)
        return 0;
    r6c_src3ECA7C = src;
    r6c_p3ECA38 = src->blk20;
    r6c_v3ECA1C = 0;
    r6c_hits3ECA00 = 0;
    sub_00080E20(src->i0C);
    h = r6c_hits3ECA00;
    if (!h)
        return 0;
    owner->hits = h;
    owner->src = src;
    do {
        h->owner = owner;
        h = h->next;
    } while (h);
    return 1;
}

/* 0x00082060: fill a link record and append it to the owner's chain. */
void r6c_LinkAppend(R6cLinkHead *owner, R6cLink *l, uint8_t *obj, int v)
{
    R6cLink *p;
    l->i10 = v;
    l->owner = owner;
    l->kind = 4;
    l->obj = obj;
    if (obj)
        l->i20 = *(int32_t *)(obj + 0xB4);
    p = owner->first;
    if (p) {
        while (p->next)
            p = p->next;
        p->next = l;
    } else {
        owner->first = l;
    }
}

/* 0x00082200: gather the entries under root between two points into out (0-terminated). */
void r6c_CollectBetween(void **root, const R6cVec4 *a, const R6cVec4 *b, void **out)
{
    if (!out)
        return;
    sub_000F5D40(&r6c_vec3EC9E8, a);
    sub_000F5D40(&r6c_vec3EC864, b);
    r6c_n3ECA20 = 0;
    r6c_out3ECA78 = out;
    if (root && *root)
        sub_00082140(*root);
    r6c_out3ECA78[r6c_n3ECA20] = 0;
}

/* 0x00082950: 1 when the box spanned by (a - d) and (b - c) does not reach outward (or in the free mode). */
int r6c_BoxBehind(const R6cVec4 *a, const R6cVec4 *b, const R6cVec4 *c, const R6cVec4 *d)
{
    R6cVec4 r, v1, v0;
    if (a30_g41316C == 5 && a30_g413170 == 1)
        return 1;
    sub_001AD9F0(&v0, a, d);
    sub_001AD9F0(&v1, b, c);
    sub_001ADE90(&r, &v0, &v1);
    if (r.x <= 0.0f && r.y <= 0.0f && r.z <= 0.0f)
        return 1;
    return 0;
}

/* 0x000829D0: a + b wrapped into -pi..pi. */
float r6c_AngleAdd(float a, float b)
{
    float x = a + b;
    while (x < -3.14159274f)
        x += 6.28318548f;
    while (x > 3.14159274f)
        x -= 6.28318548f;
    return x;
}

/* 0x00082A30: rotate v by the angles in rot (x, y, then z). */
void r6c_RotateVec(R6cVec4 *out, const R6cVec4 *rot, const R6cVec4 *v)
{
    R6cMtx m;
    sub_001AD940(&m);
    sub_001AD8B0(&m, &m, rot->x);
    sub_001AD8E0(&m, &m, rot->y);
    sub_001AD910(&m, &m, rot->z);
    sub_001AD9B0(out, &m, v);
}

/* 0x00083070: free a resource record and its parts; returns the chain error, 0 on success. */
int r6c_Res3Free(R6cRes3 *r)
{
    int e;
    if (!r)
        return 0;
    if (r->p14) {
        sub_001B2080(r->p14);
        sub_00053880(r->p14);
        r->p14 = 0;
    }
    if (r->p18) {
        sub_00053880(r->p18);
        r->p18 = 0;
    }
    e = a8c_EntryFreeChain(r->p10);
    if (e)
        return e;
    r->p10 = 0;
    sub_00053880(r);
    return 0;
}

/* 0x00083480: create a list member for resource a and append it to the list; 1 on success. */
int r6c_E28Add(const void *a, R6cE28List *l)
{
    void *h = sub_00037570(a, 0x40);
    R6cE28 *e, *p;
    if (!h)
        return 0;
    e = sub_00053AB0(0x28, 0, 0x127);
    e->i00 = 0;
    e->i04 = 0;
    e->h0C = h;
    e->i18 = 2;
    e->i1C = 0;
    e->next = 0;
    e->i24 = 0;
    e->i08 = 0;
    e->f10 = 1.0f;
    e->i14 = 10;
    if (!l->first) {
        l->first = e;
        l->count++;
        return 1;
    }
    for (p = l->first; p->next; p = p->next)
        ;
    p->next = e;
    l->count++;
    return 1;
}

/* 0x000846D0: allocate a model part list of n parts with cleared headers. */
R6cMdlList *r6c_MdlListNew(uint32_t n)
{
    R6cMdlList *l = sub_00053AB0(0x10, 0, 0x51);
    uint32_t i;
    l->count = n;
    l->items = sub_00053AB0(n * 0x370, 0, 0x53);
    for (i = 0; i < l->count; i++) {
        R6cMdl370 *m = &l->items[i];
        m->w[0] = 0;
        m->w[1] = 0;
        m->w[2] = 0;
        m->w[3] = 0;
        m->w[4] = 0;
        m->w[5] = 0;
    }
    return l;
}

/* 0x00084730: run every model part through 0x001B7520/0x001B72C0, threading x through. */
void *r6c_MdlListChain(R6cMdlList *l, void *x)
{
    uint32_t i;
    for (i = 0; i < l->count; i++) {
        void *b = l->items[i].blk24;
        sub_001B7520(b, 0);
        x = sub_001B72C0(b, x);
    }
    return x;
}
