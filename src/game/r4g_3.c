/* Area r4g: static model draw node at 0x001B8FB0 (r4g_3). Names inferred. */
#include "r4g.h"

/* 0x001B8FB0: draw a static model node: select its state block and
   textures unless the previously drawn node already set them, upload the
   world matrix (per mesh item for skinned meshes), draw it and close the
   command; count the sub-model's size in 0x0041312C. Returns the new
   command pointer. Stack args (cmd n). */
uint32_t *r4g_DrawStaticNode(uint32_t *cmd, R4gDrawNode *n)
{
    R4gDrawNode *p;
    int selected;
    float t[16];

    if (n->itemsC4) {
        selected = 0;
        if (n->selCC && r4_g40F324 != n->selCC) {
            cmd = sub_001B2A10(cmd, n->selCC);
            selected = 1;
        }
        if (n->texD0 && r4_g40F208 != n->texD0)
            cmd = sub_001B26A0(cmd, n->texD0);
        p = n->prevA0;
        if (!p || p->type8C != 2 || !p->itemsC4 || p->texD8 != n->texD8)
            cmd = sub_001B9CA0(cmd, n->texD8);
        sub_001A69C0(n->fmt100, n->fmt104);
        if ((n->meshBC->flags4 & 7) == 1) {
            p = n->prevA0;
            if (selected || !p || p->type8C != 2 || !p->itemsC4 || p->modelC0 != n->modelC0)
                cmd = sub_001B8EE0(n, cmd);
        } else {
            sub_001AD7C0(t, r4b_g40F334->m1F0, n->m40);
            sub_001A6C90(n->m40);
            sub_001A2350(0, n->m40);
        }
        sub_001A3080(n);
        cmd = sub_001B3340(cmd, n->itemsC4);
    }
    r4b_g41312C += n->modelC0->infoBC->subs[n->subB4].size0C;
    return cmd;
}

/* 0x001B8C80: set up draw node idx of model m from its bone description:
   child and sibling links, mesh data, bind matrix and draw state, then
   link the children recursively and continue with the next sibling (which
   inherits the parent). Stack args (m base idx). */
void r4g_MeshLinkNode(R4gModel *m, R4gDrawNode *base, int idx)
{
    R4gBoneDesc *b;
    R4gDrawNode *n;
    for (;;) {
        b = &m->infoBC->subs->bones04[idx];
        n = &base[idx];
        n->child88 = b->child02 == 0xFFFF ? 0 : &base[b->child02];
        n->sib84 = b->sib04 == 0xFFFF ? 0 : &base[b->sib04];
        n->subB4 = idx;
        n->iB0 = 0;
        n->descB8 = b;
        n->meshBC = (R4gMeshDesc *)(m->infoBC->base + b->off08);
        n->modelC0 = m;
        n->itemsC4 = m->infoBC->subs[idx].f00;
        n->texC8 = 0;
        n->selCC = m->iB4;
        n->iD4 = 0;
        n->texD0 = m->iB8;
        sub_001ADA40(n->m00, b->m10);
        n->texD8 = 0;
        sub_000F5D40(n->vDC, m->vCC);
        n->vEC[0] = 0.0f;
        n->vEC[1] = 0.0f;
        n->vEC[2] = 0.0f;
        n->vEC[3] = 0.0f;
        n->fmt100 = m->iE0;
        n->fmt104 = m->iE4;
        if (b->child02 != 0xFFFF) {
            base[b->child02].parent80 = n;
            r4g_MeshLinkNode(m, base, b->child02);
        }
        if (b->sib04 == 0xFFFF)
            return;
        base[b->sib04].parent80 = n->parent80;
        idx = b->sib04;
    }
}

/* 0x001B8410: skinned variant of 0x001B8C80 for 0x110-byte nodes: same
   links and draw state, white colour, and the skin bone index. Stack args
   (m base idx). */
void r4g_SkinLinkNode(R4gModel *m, R4gSkinNode *base, int idx)
{
    R4gBoneDesc *b;
    R4gSkinNode *n;
    for (;;) {
        b = &m->infoBC->subs->bones04[idx];
        n = &base[idx];
        n->child88 = b->child02 == 0xFFFF ? 0 : &base[b->child02];
        n->sib84 = b->sib04 == 0xFFFF ? 0 : &base[b->sib04];
        n->subB4 = idx;
        n->iB0 = 0;
        n->descB8 = b;
        n->meshBC = (R4gMeshDesc *)(m->infoBC->base + b->off08);
        n->modelC0 = m;
        n->itemsC4 = m->infoBC->subs[idx].f00;
        n->texC8 = 0;
        n->selCC = m->iB4;
        n->iD4 = 0;
        n->texD0 = m->iB8;
        n->v100[3] = 1.0f;
        n->v100[2] = 1.0f;
        n->v100[1] = 1.0f;
        n->v100[0] = 1.0f;
        sub_001ADA40(n->m00, b->m10);
        sub_000F5D40(n->vD8, m->vCC);
        n->fmtE8 = m->iE0;
        n->fmtEC = m->iE4;
        n->boneFC = b->bone06;
        if (b->child02 != 0xFFFF) {
            base[b->child02].parent80 = n;
            r4g_SkinLinkNode(m, base, b->child02);
        }
        if (b->sib04 == 0xFFFF)
            return;
        base[b->sib04].parent80 = n->parent80;
        idx = b->sib04;
    }
}

/* 0x001B1200: set up 0x180-byte bone node idx of m from its image
   description (0x001AE8E0): links, then the world matrix (relative bones
   combine with the parent's, absolute ones copy the bind matrix, flagged
   ones start from identity) and the decomposed transform; then link the
   children and continue with the next sibling. Stack args (m base idx). */
void r4g_BoneLinkNode(R4gBoneOwner *m, R4gBone180 *base, int idx)
{
    R4gBoneDesc2 *b;
    R4gBone180 *n, *p;
    for (;;) {
        b = sub_001AE8E0(*m->imgBC, idx);
        n = &base[idx];
        n->child88 = b->child02 == 0xFFFF ? 0 : &base[b->child02];
        n->sib84 = b->sib04 == 0xFFFF ? 0 : &base[b->sib04];
        n->iB0 = 0;
        n->idxB4 = idx;
        n->ownerB8 = m;
        n->i17C = 0;
        if (b->rel08 == 0) {
            p = n->parent80;
            if (p) {
                sub_001ADA40(n->m00, b->m10);
                sub_001AD7C0(n->m40, p->m40, n->m00);
                sub_001AE060(n->xfBC, n->m40);
            } else {
                sub_001AE060(n->xfBC, b->m10);
                sub_001ADA40(n->m00, b->m10);
                sub_001ADA40(n->m40, n->m00);
            }
        } else {
            sub_001AD940(n->m00);
            sub_001ADA40(n->m40, n->m00);
        }
        if (b->child02 != 0xFFFF) {
            base[b->child02].parent80 = n;
            r4g_BoneLinkNode(m, base, b->child02);
        }
        if (b->sib04 == 0xFFFF)
            return;
        base[b->sib04].parent80 = n->parent80;
        idx = b->sib04;
    }
}
