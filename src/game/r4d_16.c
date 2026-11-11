/* Area r4d: matrix helper 0x001ADBF0 (r4d_16). Names inferred. */
#include "r4d.h"

/* 0x001ADBF0: out = in * Rz(rot[2]) * Ry(rot[1]) * Rx(rot[0]). Stack args (out in rot);
   the D3DX-style callees are stdcall. */
void r4d_MatRotateZYX(R4dMat *out, const R4dMat *in, const float *rot)
{
    R4dMat r;
    sub_001E4D28(&r, rot[2]);
    sub_001E522D(out, in, &r);
    sub_001E4CAD(&r, rot[1]);
    sub_001E522D(out, out, &r);
    sub_001E4C33(&r, rot[0]);
    sub_001E522D(out, out, &r);
}
