/* Area r1c, group 4: pools, bit reader and lists 0x0002E3D0..0x0005BEB0.
   Names inferred. */
#include "r1c.h"

/* 0x0002E3D0: run the handler of the current top-level mode (0..3). */
void r1c_ModeRun(void)
{
    switch (r1c_mode381400) {
    case 0: sub_0002D230(); break;
    case 1: sub_0002D790(); break;
    case 2: sub_0002DBC0(); break;
    case 3: sub_0002C870(); break;
    }
}

/* 0x000310B0: read n bits (LSB first) from a bit stream; when a word is
   used up the refill callback runs once the byte position reaches the limit.
   regargs: b=ESI */
uint32_t r1c_BitRead(R1cBits *b, uint32_t n)
{
    uint32_t v = 0;
    uint32_t i;
    for (i = 0; i < n; i++) {
        uint32_t *p = b->ptr;
        uint32_t bit = (*p >> b->bit) & 1;
        b->bit = (b->bit + 1) & 31;
        if (b->bit == 0) {
            R1cBitsRefill refill = b->refill;
            b->ptr = p + 1;
            b->pos += 4;
            if (refill != 0 && b->limit >= 0 && b->pos >= b->limit)
                refill(b);
        }
        v |= bit << i;
    }
    return v;
}

/* 0x00036B30: call fn(entry, ctx) for each used pool entry until one
   returns nonzero; returns that value, or 0. */
int r1c_PoolForEach(R1cPool *pool, int stride, R1cPoolFn fn, void *ctx)
{
    int i;
    char *e = (char *)pool + stride;
    int r;
    for (i = 0; i < pool->count; i++, e += stride) {
        if (((R1cPoolEnt *)e)->flags & 1) {
            r = fn(e, ctx);
            if (r != 0) return r;
        }
    }
    return 0;
}

/* 0x00036B70: first used pool entry accepted by fn(entry, ctx) (any used
   entry when fn is null), or 0. */
void *r1c_PoolFind(R1cPool *pool, int stride, R1cPoolFn fn, void *ctx)
{
    int i;
    char *e = (char *)pool + stride;
    for (i = 0; i < pool->count; i++, e += stride) {
        if (((R1cPoolEnt *)e)->flags & 1) {
            if (fn == 0 || fn(e, ctx) != 0)
                return e;
        }
    }
    return 0;
}

/* 0x00036F40: set the shake offset and its fourth component unless the
   block is locked (bit 0). */
void r1c_ShakeSet4(float x, float y, float z, float w)
{
    if (!(r1c_shake3DA098.flags & 1)) {
        r1c_shake3DA098.x = x;
        r1c_shake3DA098.y = y;
        r1c_shake3DA098.z = z;
        r1c_shake3DA098.f18 = w;
    }
}

/* 0x000389C0: append a request to the 16-entry queue at 0x003DA398; a full
   queue hangs (assert). */
void r1c_ReqPush(int value, int a, int b)
{
    if (r1c_reqCount3DA390 >= 16) for (;;) ;
    r1c_req3DA398[r1c_reqCount3DA390].a = a;
    r1c_req3DA398[r1c_reqCount3DA390].b = b;
    r1c_req3DA398[r1c_reqCount3DA390].value = value;
    r1c_reqCount3DA390++;
}

/* 0x0003AAB0: move every camera node off the active list onto the free
   list at 0x003DCFF0. */
void r1c_CamFlush(void)
{
    R1cCamSet *s;
    char *node;
    while (r1c_camCount3DDC60 > 0) {
        s = r1c_cam3DDC64->set;
        if (s != 0) {
            node = (char *)s - 0x10;
            sub_0003D8C0(node);
            sub_0003D880(r1c_free3DCFF0, node);
        }
    }
}

/* 0x0003B300: update a node's world transform from its parent, then
   recurse into its visible children. */
void r1c_NodeUpdate(R1cXNode *n)
{
    R1cXNode *c;
    sub_001AD7C0(n->m40, n->parent->m40, n);
    for (c = n->child; c != 0; c = c->sibling)
        if (!(c->flags & 0x40))
            r1c_NodeUpdate(c);
}

/* 0x00036450: load a resource by name and attach it to the matching entry
   of the object's table. */
void r1c_ObjAttach(R1cAttObj *o, int key, const char *name)
{
    void *res = sub_00053630(name, 0, 0);
    char *e;
    if (res == 0) return;
    e = sub_000363F0(o->table, key);
    if (e != 0)
        sub_000358C0(e + 0x14, res);
}

/* 0x0005BC50: release a sound owner: clear every channel record it owns,
   unlink it and return its pool entry. */
void r1c_SndOwnerFree(char *owner)
{
    R1cChan *c;
    int n;
    if (owner == 0) return;
    for (c = r1c_chan3E5AD4, n = 32; n != 0; n--, c++) {
        if (c->owner == owner) {
            c->handle = -1;
            c->owner = 0;
        }
    }
    sub_0003D8C0(owner + 0x14);
    sub_00036B10(owner - 0x10);
}

/* 0x0005BEB0: default emitter parameters. */
void r1c_EmitDefaults(R1cEmit *e)
{
    e->x = 0.0f;
    e->y = 0.0f;
    e->z = 0.0f;
    e->w = 1.0f;
    e->d10 = 0;
    e->d14 = 0;
    e->r = 0x80;
    e->g = 0x80;
    e->b = 0x80;
    e->d24 = 0;
    e->f28 = 0.0f;
}
