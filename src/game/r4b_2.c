/* Area r4b: part and mesh-item helpers around 0x001B13F0-0x001B3383 (r4b_2). Names inferred. */
#include "r4b.h"

/* 0x001B13F0: if enabled, load the part's bone matrix from its owner's skeleton. Stack args. */
void r4b_PartApplyBone(R4bBonePart *p)
{
    if (p->i17C)
        sub_001ADA40(p, (const float *)(p->ownerB8->skel->mats + p->boneB4 * 0x130));
}

/* 0x001B3070: set +0xC8 of the mesh and +0xD4 of every item. Stack args (m v). */
void r4b_MeshSetC8(R4bMesh *m, void *v)
{
    uint32_t i;
    R4bMeshItem *it = m->items;
    m->iC8 = v;
    for (i = 0; i < m->count; i++, it++)
        it->skelD4 = v;
}

/* 0x001B31D0: copy +0x94 of the mesh into every item. Stack args. */
void r4b_MeshCopyI94(R4bMesh *m)
{
    int i;
    R4bMeshItem *it = m->items;
    if (it)
        for (i = 0; i < (int)m->count; i++, it++)
            it->i94 = m->i94;
}

/* Buffer header filled by 0x001B32E0: base, cursor, size. */
typedef struct R4bBufHdr {
    void *base;     /* +0x00 */
    void *cur;      /* +0x04 */
    int   size;     /* +0x08 */
} R4bBufHdr;

/* 0x001B32E0: store a, a, b (buffer base and cursor, then size). Stack args;
   callers pass buffers (r1e_buf3E05DC, a 0x00053AB0 block) as a. */
void r4b_Set3(void *p, void *a, int b)
{
    R4bBufHdr *h = (R4bBufHdr *)p;
    h->base = a;
    h->cur = a;
    h->size = b;
}

/* 0x001B3300: reset the render state cache and start a command list with a 0x70000000 header. Stack args. */
void r4b_CmdReset(R4bCmdCtx *c)
{
    uint32_t *p;
    r4_g40F324 = 0;
    r4_g40F208 = 0;
    r4b_g40F330 = 0;
    r4b_g40F388 = 0;
    p = c->cur;
    c->start = p;
    p[0] = 0x70000000;
    p[1] = 0;
    c->cur[2] = 0;
    c->cur[3] = 0;
}

/* 0x001B3340: close a command block of n entries and append the end marker; returns the marker. Stack args. */
uint32_t *r4b_CmdEnd(uint32_t *p, uint32_t n)
{
    p[1] = n & 0x7FFFFFFF;
    p[2] = 0;
    p[3] = 0;
    p[0] = 0x50000000;
    p += 4;
    p[0] = 0x70000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    return p;
}
