/* Area b3b, group 3: helpers 0x0015Axxx-0x0016Bxxx. Names inferred. */
#include "b3b.h"

/* 0x0015A650: run the per-frame update and clear work flag 0x10000. */
void b3b_Update15A650(B3bOwner *o, B3bEnemy *e)
{
    B3bWork *w = e->work;
    sub_0015A3D0(o, e, w);
    w->flags40 &= ~0x10000u;
}
