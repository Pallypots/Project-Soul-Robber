/* Area r6h: node local transform, y_camera.c area (r6h_13). Names inferred. */
#include "r6h.h"

/* 0x0007E350: when the transform of node n is active, build its local matrix
   (identity, rotations by the third, first and second angle in degrees, rows scaled by the
   scale vector, translation from the position) and hand it with arg to the
   transform target. Returns -1 without a node or transform, else 0. */
int r6h_NodeApplyXform(R6hXNode *n, const void *arg)
{
    float m[4][4];
    R6hXform *x;
    void *target;

    if (!n)
        return -1;
    x = n->xf;
    if (!x)
        return -1;
    if (x->flags & 1) {
        target = x->target;
        sub_001AD940(m);
        sub_001AD910(m, m, x->rot[2] * 3.1415927f * 0.0055555557f);
        sub_001AD8B0(m, m, x->rot[0] * 3.1415927f * 0.0055555557f);
        sub_001AD8E0(m, m, x->rot[1] * 3.1415927f * 0.0055555557f);
        sub_001ADBA0(m[0], m[0], x->scale[0]);
        sub_001ADBA0(m[1], m[1], x->scale[1]);
        sub_001ADBA0(m[2], m[2], x->scale[2]);
        m[3][0] = x->pos[0];
        m[3][1] = x->pos[1];
        m[3][2] = x->pos[2];
        sub_001AD7C0(target, m, arg);
    }
    return 0;
}
