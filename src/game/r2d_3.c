/* Area r2d, group 3: camera rig helpers (0x000D45B0..0x000D5C90). Names inferred. */
#include "r2d.h"

/* 0x000D45B0: set the rig's aim point (optional) and clamp the two blend
   values (negative = keep): a to 0..1, b to 0..10. */
void r2d_RigSetAim(R2dRig *r, const void *vec, float a, float b)
{
    if (vec)
        sub_000F5D40(r->v39C, vec);
    if (a >= 0.0f) {
        if (a > 1.0f)
            a = 1.0f;
        r->f398 = a;
    }
    if (b >= 0.0f) {
        if (b > 10.0f)
            b = 10.0f;
        r->f394 = b;
    }
}

/* 0x000D4C10: clear the rig's blend state and its three low mode bits. */
void r2d_RigClear(R2dRig *r)
{
    r->f398 = 0.0f;
    r->f3B8 = 0.0f;
    r->flags3BC &= ~7u;
    r->f3C0 = 0.0f;
    r->f3C4 = 0.0f;
    r->f3C8 = 0.0f;
    r->f3CC = 0.0f;
}

