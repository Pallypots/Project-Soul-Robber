/* Area r4h: scene node world matrices (r4h_2). Names inferred. */
#include "r4h.h"

/* 0x001B6DC0: rebuild a node's world matrix from its parent. Flags 0xA in
   +0xCC: billboard-style frame built from the parent's position and the
   up vector 0x00378188 (flag 8 also places the node's position through the
   parent); flag 4: frame from the parent's normalized axes with the node's
   position transformed by the parent; otherwise world = local * parent.
   Then runs the pending callback (bit 7 of +0xB8) and sets bit 3 of +0xB8
   when no child record is waiting. Stack arg (n). */
void r4h_NodeUpdateWorld(R4hXNode *n)
{
    float pos[4];
    float m[4][4];
    R4hNodeRec *r;
    uint32_t f;
    uint32_t i;
    int ready = 1;

    if (n->flagsCC & 0xA) {
        n->flags90 |= 0x40;
        if (n->parent80) {
            sub_000F5D40(m[3], &n->parent80->world[12]);
            sub_000F5D40(m[1], (const float *)g_378188);
            sub_001ADA60(m[0], m[1], &n->parent80->world[8]);
            sub_001ADA60(m[2], m[0], m[1]);
            sub_001AD7E0(m[0], m[0]);
            sub_001AD7E0(m[1], m[1]);
            sub_001AD7E0(m[2], m[2]);
            sub_001AD7C0(n->world, m[0], n->local);
            if (n->flagsCC & 8)
                sub_001AD9B0(&n->world[12], n->parent80->world, &n->local[12]);
        }
    } else if ((n->flagsCC & 4) && n->parent80) {
        n->flags90 |= 0x40;
        sub_001AD7E0(m[0], &n->parent80->world[0]);
        sub_001AD7E0(m[1], &n->parent80->world[4]);
        sub_001AD7E0(m[2], &n->parent80->world[8]);
        sub_001AD9B0(pos, n->parent80->world, &n->local[12]);
        sub_001AD7C0(n->world, m[0], n->local);
        sub_000F5D40(&n->world[12], pos);
    } else {
        n->flags90 |= 0x40;
        if (n->parent80)
            sub_001AD7C0(n->world, n->parent80->world, n->local);
    }
    if ((int8_t)n->flagsB8 < 0)
        sub_001B6B70(n);
    f = (n->flagsB8 & ~0x30u) | 0x40;
    n->flagsB8 = f;
    if (!(f & 4)) {
        for (i = 0; i < n->countB0; i++) {
            r = &n->recsB4[i];
            if ((r->flagsB0 & 1) && !(r->flagsD4 & 1))
                ready = 0;
        }
        if (!ready)
            return;
    }
    n->flagsB8 = f | 8;
}
