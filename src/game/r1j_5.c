/* Area r1j, group 5: model texture binding 0x00052B60.
   Names inferred. */
#include "r1j.h"

/* 0x00052B60: bind the textures of loaded model blob m. Only when the
   blob state is 1: rebase the blob (0x00052B00), create a texture handle
   for every texture entry (0x00084C00; the first also goes to
   m->firstTex), then for every part of every mesh group set the two
   texture masks (1 << byte +0x20 / +0x22 of the part's texture) when the
   part is enabled (bit 0), textured (bit 0x20000) and has a texture
   index, else clear them. Returns 0, or -1 when the state is not 1. */
int r1j_ModelBindTextures(R1jModel *m)
{
    R1jTexTable *tt;
    R1jMeshTable *mt;
    R1jMeshGroup *g;
    void *h;
    uint32_t i, k;
    int j;
    if (m->state != 1)
        return -1;
    sub_00052B00(m);
    tt = m->tex;
    for (i = 0; i < tt->count; i++) {
        R1jTexEnt *e = &tt->e[i];
        h = sub_00084C00(e->src, 0);
        if (i == 0)
            m->firstTex = h;
        e->handle = h;
    }
    mt = m->mesh;
    for (k = 0; k < mt->count; k++) {
        g = mt->e[k].grp;
        for (j = 0; j < g->count; j++) {
            if ((g->part[j].flags & 1) && (g->part[j].flags & 0x20000)
                && g->part[j].texIdx >= 0) {
                g->part[j].maskA = 1 << m->tex->e[g->part[j].texIdx].src[0x20];
                g->part[j].maskB = 1 << m->tex->e[g->part[j].texIdx].src[0x22];
            } else {
                g->part[j].maskA = 0;
                g->part[j].maskB = 0;
            }
        }
    }
    return 0;
}
