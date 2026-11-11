/* Area r4c: camera point helper 0x00198DA0 (r4c_8, kept apart so its caller does not inline it). Names inferred. */
#include "r4c.h"

/* 0x00198DA0: transform the negated camera offset (cam +0x28) by the camera matrix at +0x58 into out.
   regargs: p1=ESI (out) p2=EDI (o). */
void r4c_CamPoint(float *out, R4cNode *o)
{
    float a[4], b[4];
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 1.0f;
    a[0] = 0.0f;
    a[1] = 0.0f;
    a[2] = 0.0f;
    a[3] = 1.0f;
    r4c_Vec4Scale(a, o->cam140->v28, -1.0f);
    r4c_Vec4Scale(out, o->cam140->m58[0], a[0]);
    r4c_Vec4Scale(b, o->cam140->m58[1], a[1]);
    r4c_VecAdd(out, b, out);
    r4c_Vec4Scale(b, o->cam140->m58[2], a[2]);
    r4c_VecAdd(out, b, out);
    r4c_VecAdd(out, out, o->cam140->m58[3]);
}
