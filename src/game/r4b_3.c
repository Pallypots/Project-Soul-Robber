/* Area r4b: callers kept apart from their callees (r4b_3). Names inferred. */
#include "r4b.h"

/* 0x001B3270: refresh +0x94 (unless bit 0 of +0xB0) and load every item's bone matrix. Stack args. */
void r4b_MeshApplyBones(R4bMesh *m)
{
    int i;
    R4bMeshItem *it;
    if (!(m->flagsB0 & 1))
        r4b_MeshCopyI94(m);
    for (i = 0, it = m->items; i < (int)m->count; i++, it++)
        if (it->skelD4)
            sub_001ADA40(it, (const float *)(it->skelD4->mats + it->boneB4 * 0x130));
}

/* 0x001B67F0: rescale the set by factor k relative to its current scale. Stack args. */
void r4b_EmitSetScaleBy(R4bEmitSet *s, float k)
{
    r4b_EmitSetScale(s, s->fD4 * k);
}


/* 0x001B83D0: refresh +0x94 (unless bit 0 of +0xB0) and load both matrices from the matrix pair. Stack args. */
void r4b_NodeCApplyMats(R4bNodeC *n)
{
    if (!(n->iB0 & 1))
        r4b_NodeCCopyI94(n);
    if (n->matsE8) {
        sub_001ADA40(n, n->matsE8);
        sub_001ADA40((uint8_t *)n + 0x40, n->matsE8 + 16);
    }
}

/* 0x001B9CA0: bind texture idx; render targets (idx < 0) first get a 0x10000000 header in cmd. Stack args (cmd idx). */
uint32_t *r4b_TexBindCmd(uint32_t *cmd, int idx)
{
    if (idx < 0) {
        cmd[0] = 0x10000000;
        cmd[1] = 0;
        cmd[2] = 0;
        cmd[3] = 0x11000000;
        sub_001A6820(r4b_TexEntGet(idx));
        return cmd + 4;
    }
    sub_001A6820(r4b_TexEntGet(idx));
    return cmd;
}

/* 0x001BA0F0: bind texture idx, rebuilding non-resident ones in the scratch entry; returns cmd.
   Stack args (cmd idx); calls 0x001B9460 with EAX=dst ECX=hdr and 0x001B9EC0 with ESI=dst. */
uint32_t *r4b_TexBind(uint32_t *cmd, int idx)
{
    R4bTexEnt *e;
    if (idx < 0) {
        sub_001A6820(r4b_TexEntGet(idx));
        return cmd;
    }
    e = &r4b_g40F750[idx];
    if (e->flags & 2) {
        sub_001A6820(e);
        return cmd;
    }
    sub_001B9460(&r4b_g40F4F8, e->hdr14);
    sub_001B9EC0(&r4b_g40F4F8, r4b_g40F750[idx].hdr14, r4_Heap2Word0C());
    sub_001A6820(&r4b_g40F4F8);
    return cmd;
}

/* 0x001BA6B0: free every texture entry. No inputs. */
void r4b_TexFreeAll(void)
{
    uint32_t n = r4_g40F390->count;
    uint32_t i;
    for (i = 0; i < n; i++)
        r4b_TexFree(i);
}
