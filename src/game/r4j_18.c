/* Area r4j: scene node update (0x001B2270). Names inferred. */
#include "r4j.h"

/* 0x001B2270: update one scene node and, recursively, its children;
   returns the next sibling. Counts the node per type (0..19). Hidden nodes
   (flag 0x20) are skipped. In pass 0 the done bit is cleared and, unless
   flag 0x10, the node is appended to one of 51 depth buckets (bucket 0 for
   flag 0x100, else 50 - (depth - min) / ((max - min) * 0.02) with the depth
   clamped to [min, max]). Unless render flag bit 0 is set, a node not yet
   done runs its callback for the current pass (marking it done unless the
   next pass has a callback too), the done mask 0x0040F1C0 is ANDed with its
   flags, its world matrix is set (local * parent world, or local) unless
   flag 0x40, and a node that just became done runs its 0xA8 hooks
   (0x001B2240); with render flag bit 0 it is just marked done. After the
   children, a node that just became done runs its 0xAC hooks. Stack arg (n). */
R4jSNode *sub_001B2270(R4jSNode *n)
{
    R4jSNode *parent = n->parent80;
    R4jSNode *c;
    R4jSNodeFn fn;
    R4jHook *h;
    uint32_t flags;
    int bucket;
    int fresh = 0;
    int pass;
    float z;

    if (n->type8C >= 0 && n->type8C < 0x14)
        r4j_typeCount412EE0[n->type8C]++;
    flags = n->flags90;
    if (flags & 0x20)
        return n->next84;
    pass = r4j_pass40F1BC;
    if (pass == 0) {
        flags &= ~1u;
        n->flags90 = flags;
        if (!(flags & 0x10)) {
            bucket = 0;
            if (!(flags & 0x100)) {
                z = n->depth94;
                if (z > r4j_depthMax377F48)
                    z = r4j_depthMax377F48;
                else if (r4j_depthMin40F1C4 > z)
                    z = r4j_depthMin40F1C4;
                bucket = 0x32 - (int)((z - r4j_depthMin40F1C4) /
                                      ((r4j_depthMax377F48 - r4j_depthMin40F1C4) * 0.02f));
            }
            if (r4j_bucketHead413060[bucket] == 0) {
                r4j_bucketHead413060[bucket] = n;
                r4j_bucketTail412F80[bucket] = n;
                n->prevA0 = 0;
            } else {
                r4j_bucketTail412F80[bucket]->nextA4 = n;
                n->prevA0 = r4j_bucketTail412F80[bucket];
                r4j_bucketTail412F80[bucket] = n;
            }
        }
    }
    flags = n->flags90;
    if (!(flags & 1))
        fresh = 1;
    if (r4j_renderFlags412F30 & 1) {
        flags |= 1;
        n->flags90 = flags;
        r4j_doneMask40F1C0 &= flags;
    } else {
        if (!(flags & 1) && (fn = n->passFns98[pass]) != 0) {
            fn(n);
            if (n->passFns98[r4j_pass40F1BC + 1] == 0)
                n->flags90 |= 1;
        } else {
            n->flags90 = flags | 1;
        }
        r4j_doneMask40F1C0 &= n->flags90;
        if (!(n->flags90 & 0x40)) {
            if (parent != 0)
                sub_001AD7C0(n->world40, parent->world40, n);
            else
                sub_001ADA40(n->world40, n);
        }
        if (fresh == 1 && (n->flags90 & 1) && n->hooksA8 != 0)
            r4_HookRunA8(n);
    }
    for (c = n->child88; c != 0; c = sub_001B2270(c))
        ;
    if (fresh == 1 && (n->flags90 & 1)) {
        for (h = n->hooksAC; h != 0; h = h->next)
            if (h->fn != 0)
                h->fn(n, h);
    }
    return n->next84;
}
