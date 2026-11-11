/* Area r1g, group 4: char_unit.c teardown 0x0001F300. Names inferred. */
#include "r1g.h"

/* 0x0001F300: free a character unit and its chain of child units: the
   model, the side buffers, its textures and resource entry (unless it
   shares them, flag bit 2), then the heap-owned links. */
void r1g_CharUnitFree(R1gCharUnit *u)
{
    R1gLink *l;
    if (u == 0)
        return;
    if (u->child) {
        r1g_CharUnitFree(u->child);
        a5b_HeapOp47640(u->child);
    }
    if (u->model) {
        a60_Remove6994(u->model);
        a60_Remove6974(u->model);
        a60_DetachEff6984(u->model);
    }
    if (u->p148) {
        a5b_HeapOp47640(u->p148);
        u->p148 = 0;
    }
    if (!(u->flags & 4)) {
        if (u->tex[0] != -1) r4b_TexFree(u->tex[0]);
        if (u->tex[1] != -1) r4b_TexFree(u->tex[1]);
        if (u->tex[2] != -1) r4b_TexFree(u->tex[2]);
        if (u->obj12C) {
            a5b_HeapOp47640(u->obj12C->buf0C);
            a5b_HeapOp47640(u->obj12C);
            u->obj12C = 0;
        }
        if (u->obj130) {
            a5b_HeapOp47640(u->obj130->buf14);
            a5b_HeapOp47640(u->obj130);
            u->obj130 = 0;
        }
        if (u->obj138) {
            a5b_HeapOp47640(u->obj138->buf0C);
            a5b_HeapOp47640(u->obj138);
            u->obj138 = 0;
        }
        r1_EntAge(u->resA, u->resB);
    }
    r1b_RecFreeRes(u);
    while ((l = u->links) != 0) {
        u->links = l->next;
        if (l->flags & 1)
            a5b_HeapOp47640(l);
    }
}

/* 0x0001F6C0: allocate the per-unit buffers for character `kind`.
   With a template unit `tmpl`, the unit count is one past the last child
   chain entry flagged 1 and r1e_PartValues refines the node counts; the
   template's model parts (+0x20 model, +0x28 node, +0x30 animation)
   decide which buffers each unit gets (all of them without a template).
   Root units use nodesRoot nodes, chained children nodesChild. */
R1gUnitTbl *r1g_CharUnitAlloc(int kind, int count, int nodesRoot, int nodesChild, R1gCharUnit *tmpl)
{
    R1gUnitTbl *tbl;
    int k, off, n;
    if (tmpl) {
        R1gCharUnit *c;
        int i = 0;
        count = 0;
        for (c = tmpl->child; c; c = c->child) {
            i++;
            if (c->flags & 1)
                count = i;
        }
        r1e_PartValues(&nodesRoot, &nodesChild, tmpl);
    }
    tbl = sub_0001F210(kind, count);
    for (k = 0, off = 0; k < tbl->count; k++, off += sizeof(R1gCharUnit)) {
        R1gCharUnit *u = (R1gCharUnit *)((uint8_t *)tbl->units + off);
        R1gCharUnit *cur = tmpl;
        int j = -1;
        for (; u; u = u->child) {
            uint32_t mask;
            u->p148 = a50_AllocTop(r1g_srcCharUnit25FC08, 0x1132);
            n = nodesRoot;
            if (j >= 0)
                n = nodesChild;
            if (cur) {
                mask = 0;
                if (cur->model) mask = 1;
                if (cur->node28) mask |= 2;
                if (cur->anim30) mask |= 4;
            } else {
                mask = 0xFFFFFFFF;
            }
            if (mask & 1) {
                u->model = a5b_AllocCur(0xF0, 0, 0x1154);
                r4b_NodeReset(u->model);
                *(int32_t *)((uint8_t *)u->model + 0x8C) = 0;
                u->nodeBuf = a5b_AllocCur(n * 0x180, 0, 0x1158);
                u->nodes = n;
            }
            if (mask & 2) {
                unsigned int sz;
                u->node28 = a5b_AllocCur(0xF0, 0, 0x1166);
                r4b_NodeReset(u->node28);
                sz = (unsigned int)n * 0x110;
                u->buf2C = a5b_AllocCur(sz > 0x644 ? sz : 0x644, 0, 0x116A);
            }
            if (mask & 4) {
                void *node = a5b_AllocCur(0xE0, 0, 0x1171);
                r4e_NodeInit(node);
                u->anim30 = sub_00083030(node, k, u);
                ((R1gAnimObj *)u->anim30)->buf18 = a5b_AllocCur(n * 0x130, 0, 0x1177);
                u->p34 = sub_0007FC60();
            }
            if (u == (R1gCharUnit *)((uint8_t *)tbl->units + off)) {
                u->task140 = a5b_AllocCur(0x9C, 0, 0x1195);
                a3c_TaskInit(u->task140, u);
            }
            if (u != (R1gCharUnit *)((uint8_t *)tbl->units + off))
                u->p144 = a5b_AllocCur(0x14, 0, 0x119C);
            if (cur)
                cur = cur->child;
            j++;
            a5b_CurSlotEndTemp();
        }
    }
    return tbl;
}

/* 0x0001F930: allocate the per-unit buffers for character `kind` from the
   part counts of the loaded units in `src`: root units use the counts of
   the roots, chained children those of the children (r1_PartsRange). The
   chain length is the longest flagged child chain of src. Animation
   buffers are made when any flagged root of src has one.
   calls 0x0001E850 with EAX=unit EDI=counts */
R1gUnitTbl *r1g_CharUnitAllocFrom(int kind, R1gUnitTbl *src)
{
    int rootCnt[3], childCnt[3];
    int maxChain, hasAnim;
    R1gUnitTbl *tbl;
    int k, off;
    if (kind < 0 || src == 0)
        return 0;
    rootCnt[0] = 0; rootCnt[1] = 0; rootCnt[2] = 0;
    childCnt[0] = 0; childCnt[1] = 0; childCnt[2] = 0;
    maxChain = 0;
    hasAnim = 0;
    if (src->count > 0) {
        R1gCharUnit *u = src->units;
        int i = src->count;
        do {
            if (u->flags & 1) {
                R1gCharUnit *c;
                int chain = 0;
                r1_PartsRange(u, rootCnt);
                for (c = u->child; c; c = c->child) {
                    if (c->flags & 1) {
                        chain++;
                        r1_PartsRange(c, childCnt);
                    }
                }
                if (!(maxChain > chain))
                    maxChain = chain;
                if (u->anim30)
                    hasAnim = 1;
            }
            u++;
        } while (--i);
    }
    tbl = sub_0001F210(kind, maxChain);
    for (k = 0, off = 0; k < tbl->count; k++, off += sizeof(R1gCharUnit)) {
        R1gCharUnit *u = (R1gCharUnit *)((uint8_t *)tbl->units + off);
        int j = 0;
        for (; u; u = u->child, j++) {
            int *cnt;
            int n;
            u->p148 = a50_AllocTop(r1g_srcCharUnit25FC08, 0x1242);
            cnt = rootCnt;
            if (j)
                cnt = childCnt;
            n = cnt[0];
            if (n > 0) {
                u->model = a5b_AllocCur(0xF0, 0, 0x1252);
                r4b_NodeReset(u->model);
                *(int32_t *)((uint8_t *)u->model + 0x8C) = 0;
                u->nodeBuf = a5b_AllocCur(n * 0x180, 0, 0x1257);
                u->nodes = n;
            }
            switch (cnt[1]) {
            case 1:
                u->node28 = a5b_AllocCur(0xF0, 0, 0x126A);
                r4b_NodeReset(u->node28);
                u->buf2C = a5b_AllocCur(0x644, 0, 0x126E);
                break;
            case 2:
                u->node28 = a5b_AllocCur(0xF0, 0, 0x1261);
                r4b_NodeReset(u->node28);
                u->buf2C = a5b_AllocCur(cnt[2] * 0x110, 0, 0x1265);
                break;
            }
            if (hasAnim) {
                void *node = a5b_AllocCur(0xE0, 0, 0x1276);
                r4e_NodeInit(node);
                u->anim30 = sub_00083030(node, k, u);
                ((R1gAnimObj *)u->anim30)->buf18 = a5b_AllocCur(n * 0x130, 0, 0x127E);
                u->p34 = sub_0007FC60();
            }
            if (j == 0) {
                u->task140 = a5b_AllocCur(0x9C, 0, 0x1286);
                a3c_TaskInit(u->task140, u);
            } else if (j > 0) {
                u->p144 = a5b_AllocCur(0x14, 0, 0x128C);
            }
            a5b_CurSlotEndTemp();
        }
    }
    return tbl;
}

/* 0x0001FBD0: attach unit `u` to the unit named by its first kind-1 link,
   starting the name search at `c`: copy the model of `tmpl` into u's
   model, rebuild it for its kind (1 or 9), bind it to the found bone and
   re-hook u's tasks. regargs: c=EDX (u and tmpl on the stack). */
void r1g_CharUnitAttach(R1gCharUnit *u, R1gCharUnit *tmpl, R1gCharUnit *c)
{
    R1gAttach *l;
    void *bone;
    R1gModel *m;
    for (l = (R1gAttach *)tmpl->links; l; l = l->next) {
        if (l->kind == 1)
            break;
    }
    if (l == 0)
        return;
    if (u->model == 0 || tmpl->model == 0)
        return;
    bone = 0;
    if (l->target) {
        if (c->id14 != l->target->id14 || c->id18 != l->target->id18)
            c = r1b_RecFindName(c, &l->target->id14);
        if (c)
            bone = sub_0001DAF0(c, l->bone);
    }
    switch (((R1gModel *)tmpl->model)->kind) {
    case 9:
        m = (R1gModel *)u->model;
        sub_000AD090();
        r4b_NodeInitType9(m);
        sub_000AD090();
        *m = *(R1gModel *)tmpl->model;
        m->dA8 = 0;
        r4_ModelSetCC(m, tmpl->tex[0]);
        r4b_Node5SetE0(m, l->d20, l->d24);
        r4_ModelSetE8(m, l->d28, l->d2C);
        if (((R1gModel *)u->model)->used > (uint32_t)u->nodes)
            for (;;) ;
        sub_000AD090();
        r4b_NodeAttachParts(u->nodeBuf, m);
        sub_000AD090();
        if (bone)
            r4_NodeAttach(bone, m);
        if (l->flags & 4)
            a60_AttachEff6974(m, tmpl->tex[0], l->d40, l->d44);
        break;
    case 1:
        m = (R1gModel *)u->model;
        sub_000AD090();
        r4e_Node1Init(m);
        sub_000AD090();
        *m = *(R1gModel *)tmpl->model;
        m->dA8 = 0;
        if (((R1gModel *)u->model)->used > (uint32_t)u->nodes)
            for (;;) ;
        sub_000AD090();
        r4b_MeshAttachItems(u->nodeBuf, m);
        sub_000AD090();
        r4d_PartsBoneOffset(m, tmpl->tex[0]);
        r4f_EmitASetPair(m, l->d20, l->d24);
        r4_ModelSetE8(m, l->d28, l->d2C);
        if (bone)
            r4_NodeAttach(bone, m);
        if (l->flags & 2)
            r6d_ModelSetUV2(m, tmpl->tex[0], l->uv38);
        if (l->flags & 4)
            a60_AttachEff6984(m, l->d40, l->d44);
        break;
    }
    if (u->task140) {
        r4_HookRemoveAC(u->model, u->task140);
        r4_HookAppendAC(u->model, u->task140);
    }
    if (u->p144) {
        r4_HookRemoveAC(c->model, u->p144);
        if (l->flags & 1)
            r1d_BonesLink(u->p144, c, u);
    }
}
