/* Area r4j: bone tree build (0x001BBA20). Names inferred. */
#include "r4j.h"

/* 0x001BBA20: initialise bone node idx and, recursively, its children and
   following siblings from the owner's bone file: child/sibling links, the
   definition and its data, the bind matrix, the owner's colour and
   parameters, and the parent link of the first child (this node) and of the
   next sibling (this node's parent). The sibling chain is walked as a loop
   (tail call). Stack args (m nodes idx). */
void sub_001BBA20(R4jBoneOwner *m, R4jBone *nodes, int idx)
{
    R4jBoneDef *d;
    R4jBone *n;

    for (;;) {
        d = &m->fileBC->hdrs04->defs04[idx];
        n = &nodes[idx];
        n->child88 = d->child02 == 0xFFFF ? 0 : &nodes[d->child02];
        n->sib84 = d->sib04 == 0xFFFF ? 0 : &nodes[d->sib04];
        n->idxB4 = idx;
        n->iB0 = 0;
        n->defB8 = d;
        n->dataBC = m->fileBC->base00 + d->off08;
        n->ownerC0 = m;
        n->iC4 = m->fileBC->hdrs04[idx].f00;
        n->iC8 = m->iB4;
        n->iCC = m->iB8;
        sub_001ADA40(n, d->mat10);
        n->iD0 = 0;
        sub_000F5D40(n->colD4, m->colC8);
        n->vE4[0] = 0.0f;
        n->vE4[1] = 0.0f;
        n->vE4[2] = 0.0f;
        n->vE4[3] = 0.0f;
        n->iF8 = m->iD8;
        n->iFC = m->iDC;
        if (d->child02 != 0xFFFF) {
            nodes[d->child02].parent80 = n;
            sub_001BBA20(m, nodes, d->child02);
        }
        if (d->sib04 == 0xFFFF)
            return;
        nodes[d->sib04].parent80 = n->parent80;
        idx = d->sib04;
    }
}
