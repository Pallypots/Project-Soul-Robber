/* Area r4b: camera matrices and render setup around 0x001B7320-0x001B74D3 (r4b_5). Names inferred. */
#include "r4b.h"

/* 0x001B7320: build the combined camera matrices (+0x1F0 and +0x230). Stack args. */
void r4b_CamCombine(R4bCam *c)
{
    sub_001AD7C0(c->m1F0, c->mF0, c->mB0);
    sub_001AD7C0(c->m230, c->m170, c->mB0);
}

/* 0x001B7520: initialise a type-4 camera node under parent; returns c. Stack args (c parent). */
R4bCam *r4b_CamInit(R4bCam *c, void *parent)
{
    float m[16];
    c->type8C = 4;
    sub_001B25B0(c);
    sub_001AD940(m);
    sub_001ADA40(c->mB0, m);
    c->parent80 = parent;
    r4_FogInit(c->fog290);
    c->i2C8 = 0;
    return c;
}

/* 0x001B7B50: emit matrix m twice as a register block plus a trailing constant vector; returns the new end. Stack args (m cmd). */
uint32_t *r4b_CmdEmitMatrix(const float *m, uint32_t *cmd)
{
    sub_001A6C90(m);
    cmd[0] = 0x10000000;
    cmd[1] = 0;
    cmd[2] = 0;
    cmd[3] = 0x11000000;
    cmd[4] = 0x10000008;
    cmd[5] = 0;
    cmd[6] = 0x1000101;
    cmd[7] = 0x6C08001B;
    sub_001ADA40(cmd + 8, m);
    sub_001ADA40(cmd + 0x18, m);
    cmd[0x29] = 0;
    cmd[0x2D] = 0;
    cmd[0x28] = 0x10000000;
    cmd[0x2A] = 0x14000000;
    cmd[0x2B] = 0x11000000;
    cmd[0x2C] = 0x10000001;
    cmd[0x2E] = 0x1000101;
    cmd[0x2F] = 0x30000000;
    cmd[0x33] = r4b_g3780E8[3];
    cmd[0x32] = r4b_g3780E8[2];
    cmd[0x31] = r4b_g3780E8[1];
    cmd[0x30] = r4b_g3780E8[0];
    return cmd + 0x34;
}

/* 0x001B7E50: emit the three passes of 0x001B7C30 (a b a); stack args; calls 0x001B7C30 with EAX=x ESI=cmd. */
uint32_t *r4b_CmdEmit3(uint32_t *cmd, int a, int b, void *p)
{
    cmd = sub_001B7C30(a, cmd, p, 0);
    cmd = sub_001B7C30(b, cmd, p, 1);
    return sub_001B7C30(a, cmd, p, 2);
}

/* 0x001B8240: initialise a type-12 node; returns n. Stack args. */
R4bNodeC *r4b_NodeInitType12(R4bNodeC *n)
{
    n->type8C = 0xC;
    sub_001B25B0(n);
    n->vCC[0] = 0.0f;
    n->vCC[1] = 0.0f;
    n->vCC[2] = 32.0f;
    n->iB0 = 0;
    n->iB4 = 0;
    n->iB8 = 0;
    n->iBC = 0;
    n->count = 0;
    n->items = 0;
    n->iC8 = 0;
    n->iE4 = 0;
    n->matsE8 = 0;
    n->iEC = 0;
    n->vCC[3] = 64.0f;
    n->iE0 = 0x44;
    return n;
}

/* 0x001B82E0: set +0xB8 and copy it into every item. Stack args (n v);
   v is a light (float[4]) pointer (r1i_14 passes s->light). */
void r4b_NodeCSetB8(R4bNodeC *n, const float *v)
{
    int i;
    R4bNodeCItem *it;
    n->iB8 = v;
    for (i = 0, it = n->items; it; i++, it++) {
        if (i >= n->count)
            break;
        it->iD0 = n->iB8;
    }
}

/* 0x001B8390: copy +0x94 into the first item (the original never advances the item pointer). Stack args. */
void r4b_NodeCCopyI94(R4bNodeC *n)
{
    int i;
    R4bNodeCItem *it = n->items;
    if (it)
        for (i = 0; i < n->count; i++)
            it->i94 = n->i94;
}

/* 0x001B87F0: set the matrix pair pointer. Stack args. */
void r4b_NodeCSetMats(R4bNodeC *n, const float *m)
{
    n->matsE8 = m;
}

