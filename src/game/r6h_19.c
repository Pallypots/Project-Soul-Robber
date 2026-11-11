/* Area r6h: motion record reset (r6h_19). Names inferred. */
#include "r6h.h"

/* 0x000A7700: reset motion record m to its defaults: scalars 0 except +0x10
   (1.0), +0x14 (10.0), +0x28 (4.0) and the target (-1); five vectors
   (0,0,0,1); sixteen words at +0x90 and the three words at +0xD0 cleared. */
void r6h_MotionReset(R6hMotion *m)
{
    int i;

    m->f14 = 10.0f;
    m->f08 = 0.0f;
    m->f0C = 0.0f;
    m->f10 = 1.0f;
    m->target = -1;
    m->f24 = 0.0f;
    m->f28 = 4.0f;
    m->f2C = 0.0f;
    for (i = 0; i < 5; i++) {
        m->v[i].z = 0.0f;
        m->v[i].y = 0.0f;
        m->v[i].x = 0.0f;
    }
    m->v[4].w = 1.0f;
    m->v[3].w = 1.0f;
    m->v[2].w = 1.0f;
    m->v[1].w = 1.0f;
    m->v[0].w = 1.0f;
    m->flags = 0;
    m->v04 = 0;
    m->v1C = 0;
    m->v20 = 0;
    m->vD4 = 0;
    m->vD8 = 0;
    for (i = 0; i < 16; i++)
        m->w[i] = 0;
    m->vD0 = 0;
}
