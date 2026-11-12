/* Area m1, /GS file 7 (kept apart from m1_gs2.c so the path builders are not inlined). Names inferred. */
#include "m1.h"

/* 0x0008E900: load the .clp file for a kind-2 resource once; -1 if the kind is wrong. */
int m1_LoadClpRes8E900(M1Res *r, M1DtObj *o)
{
    char path[0x40];
    if (r->kind != 2)
        return -1;
    if (!(r->flags & 2)) {
        sub_0007F4A0(2, sub_0008BCD0(r->heap));
        m1_PathClp8E8B0(path, r->n, o);
        r->data = sub_0007F510(path, 0);
        r->flags = (uint16_t)((r->flags & ~0xC) | 2);
    }
    return 0;
}

