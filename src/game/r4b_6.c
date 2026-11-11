/* Area r4b: mesh setup and matrix upload around 0x001B8E10-0x001B8FAF (r4b_6). Names inferred. */
#include "r4b.h"

/* 0x001B8E10: attach item array base to mesh m and link the root item. Stack args (base m). */
void r4b_MeshAttachItems(R4bMeshItem *base, R4bMesh *m)
{
    int i;
    int root;
    R4bMeshItem *p;
    m->items = base;
    for (i = 0; i < (int)m->count; i++) {
        base[i].type8C = 2;
        sub_001B25B0(&base[i]);
    }
    root = (*m->skelBC)->root0C;
    sub_001B8C80(m, m->items, root);
    p = &base[root];
    m->child88 = p;
    p->parent80 = m;
}

/* 0x001B8EA0: upload matrix m (camera product computed first) to slot 0; returns cmd. Stack args (m cmd). */
uint32_t *r4b_MatUpload(float *m, uint32_t *cmd)
{
    float t[16];
    sub_001AD7C0(t, r4b_g40F334->m1F0, m);
    sub_001A6C90(m);
    sub_001A2350(0, m);
    return cmd;
}

/* 0x001B8EE0: upload the matrix of every item of the referenced mesh; returns cmd. Stack args (r cmd). */
uint32_t *r4b_MeshUploadAll(R4bMeshRef *r, uint32_t *cmd)
{
    uint32_t i;
    float t[16];
    for (i = 0; i < r->mesh->count; i++) {
        sub_001AD7C0(t, r4b_g40F334->m1F0, r->mesh->items[i].m40);
        sub_001AD940(t);
        sub_000F5D40(t + 12, r->mesh->items[i].v30);
        sub_001A6C90(r->mesh->items[i].m40);
        sub_001A2350(i, r->mesh->items[i].m40);
    }
    return cmd;
}
