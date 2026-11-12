/* Area r4j: camera matrices (0x001B7100). Names inferred. */
#include "r4j.h"

/* 0x001B7100: build the view's matrices from a lens block: m0F0 by
   0x001B6FE0, the projection by 0x001A6D70, then the frustum matrix
   (2n/(r-l), 2n/(t-b), (f+n)/(f-n), -2fn/(f-n), w = 1) and the screen
   matrix (scale sx, sy by the half extents, depth (zmax-zmin)/2 and
   (zmin+zmax)/2, offset ox, oy) from identities. Half extents are
   halfW/w * near and halfH/w * near. Stack args (p lens). */
void sub_001B7100(void *p, void *a)
{
    R4jView *v = (R4jView *)p;
    const R4jLens *l = (const R4jLens *)a;
    float *m;
    float inv, hw, hh;

    sub_001B6FE0(v->m0F0, l);
    r4f_SetProjection(v->proj130, (const R4fLens *)l);
    inv = 1.0f / l->w00;
    hw = l->halfW24 * inv * l->near1C;
    hh = l->halfH28 * inv * l->near1C;
    m = v->frus170;
    sub_001AD940(m);
    m[0] = l->near1C * 2.0f / (hw - (0.0f - hw));
    m[5] = l->near1C * 2.0f / (hh - (0.0f - hh));
    m[10] = (l->far20 + l->near1C) / (l->far20 - l->near1C);
    m[15] = 0.0f;
    m[14] = l->far20 * l->near1C * -2.0f / (l->far20 - l->near1C);
    m[11] = 1.0f;
    inv = 1.0f / l->w00;
    hw = l->halfW24 * inv * l->near1C;
    hh = l->halfH28 * inv * l->near1C;
    m = v->scr1B0;
    sub_001AD940(m);
    m[0] = l->sx04 / l->near1C * l->w00 * hw;
    m[5] = l->sy08 / l->near1C * l->w00 * hh;
    m[10] = (l->zmax14 - l->zmin18) * 0.5f;
    m[14] = (l->zmin18 + l->zmax14) * 0.5f;
    m[12] = l->ox0C;
    m[13] = l->oy10;
    m[15] = 1.0f;
}
