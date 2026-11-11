/* Area r4b: emitter set helpers around 0x001B6260-0x001B6B6B (r4b_4). Names inferred. */
#include "r4b.h"

/* 0x001B6260: set +0x11C. Stack args. */
void r4b_EmitSetSet11C(R4bEmitSet *s, int v)
{
    s->i11C = v;
}

/* 0x001B6270: give every item's chain of pool items back to its pool. Stack args. */
void r4b_EmitSetReleaseAll(R4bEmitSet *s)
{
    uint32_t i;
    R4bEmitItem *it;
    R4bPoolItem *first, *last;
    R4bPool *pool;
    for (i = 0; i < s->count; i++) {
        it = &s->items[i];
        first = it->firstC4;
        if (first) {
            pool = first->owner;
            last = it->lastC8;
            if (pool->free) {
                pool->free->prev = last;
                last->next = pool->free;
            }
            pool->free = first;
            pool->used -= it->usedC0;
            it->lastC8 = 0;
            it->firstC4 = 0;
            it->usedC0 = 0;
        }
    }
}

/* 0x001B6610: scale the four base factors at +0xBC and pass them to 0x001B6310. Stack args. */
void r4b_EmitSetScale4(R4bEmitSet *s, float a, float b, float c, float d)
{
    sub_001B6310(s, s->fBC * a, s->fC0 * b, s->fC4 * c, s->fC8 * d);
}

/* 0x001B6670: set the scale and rescale every item from its definition. Stack args (s scale). */
void r4b_EmitSetScale(R4bEmitSet *s, float scale)
{
    uint32_t i;
    R4bEmitItem *it;
    R4bEmitDef *d;
    s->fD4 = scale;
    for (i = 0; i < s->count; i++) {
        it = &s->items[i];
        d = it->def118;
        if (d) {
            it->fD8 = d->f28 * s->fD4;
            it->fDC = d->f2C * s->fD4;
            it->fE0 = d->f30 * s->fD4;
            it->fE4 = d->f34 * s->fD4;
            it->fE8 = d->f38 * s->fD4;
            it->fEC = d->f44 * s->fD4;
            it->fF0 = d->f48 * s->fD4;
            it->fF4 = d->f4C * s->fD4;
            it->fF8 = d->f64 * s->fD4;
            it->fFC = d->f68 * s->fD4;
            it->f100 = d->fC4 * s->fD4;
            it->f104 = d->f70 * s->fD4;
            it->f108 = d->f74 * s->fD4;
            it->i10C = d->i78;
        }
    }
}

/* 0x001B6820: set +0xD0. Stack args. */
void r4b_EmitSetSetD0(R4bEmitSet *s, float v)
{
    s->fD0 = v;
}

/* 0x001B6840: set +0xD8. Stack args. */
void r4b_EmitSetSetD8(R4bEmitSet *s, float v)
{
    s->fD8 = v;
}

/* 0x001B6860: initialise a type-0x10 node. Stack args. */
void r4b_NodeInitType16(R4bNode *n)
{
    n->type8C = 0x10;
    sub_001B25B0(n);
    n->i90 |= 0x40;
    n->iB0 = 0;
}

/* 0x001B69D0: run 0x001B5C70 over every item of an active set, threading arg through; returns arg. Stack args (arg h). */
int r4b_EmitHolderEmit(int arg, R4bEmitHolder *h)
{
    R4bEmitSet *s = h->set;
    uint32_t i;
    if (s && s->p80 && !(s->flagsB8 & 0x20)) {
        for (i = 0; i < s->count; i++)
            arg = sub_001B5C70(arg, &s->items[i]);
        return arg;
    }
    return arg;
}

/* 0x001B6A40: attach set s (if the holder exists). Stack args. */
void r4b_EmitHolderSetSet(R4bEmitHolder *h, R4bEmitSet *s)
{
    if (h)
        h->set = s;
}

/* 0x001B6A60: set the holder time and mark the set dirty. Stack args. */
void r4b_EmitHolderSetTime(R4bEmitHolder *h, float t)
{
    h->fB4 = t;
    if (h->set)
        h->set->flagsB8 |= 0x200;
}

/* 0x001B6B10: clear the holder time and the set's dirty flag. Stack args. */
void r4b_EmitHolderClearTime(R4bEmitHolder *h)
{
    h->fB4 = 0.0f;
    if (h->set)
        h->set->flagsB8 &= ~0x200u;
}

/* 0x001B6B40: install pool and size it to the buffer (calls 0x001B33F0 with ECX=pool). Stack args (pool size). */
void r4b_PoolSetup(R4bPool *pool, uint32_t size)
{
    r4b_g40F32C = pool;
    if (size >= 0x144) {
        pool->cap = (size - 0x10) / sizeof(R4bPoolItem) - 1;
        r4_PoolInit(pool);
    }
}
