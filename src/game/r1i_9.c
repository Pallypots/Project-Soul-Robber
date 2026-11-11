/* Area r1i, group 9: world bounding box 0x0001B4D0. Names inferred. */
#include "r1i.h"

/* 0x0001B4D0: build the world-space box of o in b: the transform is the
   scale times either the matrix at o->mtx (flag 0x100) or the rotation
   matrix scaled by o->rot; radius is half the box diagonal, the centre
   the transformed box middle plus o->pos, and the eight corners of the
   min/max box are transformed and moved by o->pos (w = 1).
   (d[0] is set before the multiply in the else branch; the callee does
   not read d. This keeps modern cl from merging the two calls.) */
void r1i_BoxBuild(const R1iBoxObj *o, R1iBox *b)
{
    R1iMat m, r;
    float d[4];
    float *p;
    int i;
    sub_001AD940(m);
    sub_001ADBF0(m, m, o->scale);
    if (o->flags & 0x100) {
        sub_001AD7C0(m, (const float (*)[4])o->mtx, m);
        d[0] = o->max[0] - o->min[0];
    } else {
        sub_001AD940(r);
        sub_001ADBF0(r, r, o->rot);
        d[0] = o->max[0] - o->min[0];
        sub_001AD7C0(m, r, m);
    }
    d[1] = o->max[1] - o->min[1];
    d[2] = o->max[2] - o->min[2];
    d[3] = o->max[3];
    sub_001ADB60(d, d, 0.5f);
    b->radius = sub_00082D70(d);
    d[0] = o->min[0] + d[0];
    d[1] = o->min[1] + d[1];
    d[2] = o->min[2] + d[2];
    d[3] = o->min[3];
    sub_001AD9B0(d, m, d);
    b->center[0] = o->pos[0] + d[0];
    b->center[1] = o->pos[1] + d[1];
    b->center[2] = o->pos[2] + d[2];
    b->center[3] = o->pos[3];
    b->c[0][0] = o->min[0]; b->c[0][1] = o->min[1]; b->c[0][2] = o->min[2];
    b->c[1][0] = o->max[0]; b->c[1][1] = o->min[1]; b->c[1][2] = o->min[2];
    b->c[2][0] = o->min[0]; b->c[2][1] = o->min[1]; b->c[2][2] = o->max[2];
    b->c[3][0] = o->max[0]; b->c[3][1] = o->min[1]; b->c[3][2] = o->max[2];
    b->c[4][0] = o->min[0]; b->c[4][1] = o->max[1]; b->c[4][2] = o->max[2];
    b->c[5][0] = o->max[0]; b->c[5][1] = o->max[1]; b->c[5][2] = o->max[2];
    b->c[6][0] = o->min[0]; b->c[6][1] = o->max[1]; b->c[6][2] = o->min[2];
    b->c[7][0] = o->max[0]; b->c[7][1] = o->max[1]; b->c[7][2] = o->min[2];
    for (i = 8, p = b->c[0]; i != 0; i--, p += 4) {
        sub_001AD9B0(p, m, p);
        p[0] = o->pos[0] + p[0];
        p[1] = p[1] + o->pos[1];
        p[2] = o->pos[2] + p[2];
        p[3] = 1.0f;
    }
}
