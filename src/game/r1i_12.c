/* Area r1i, group 12: body set-up 0x0001C8A0. Names inferred. */
#include "r1i.h"

/* 0x0001C8A0: reset body b (if any): flags 0xE0, empty box, unit scale,
   no offset or radius, the empty stub as hit handler and both contact
   lists cleared. */
void r1i_BodyInit(R1iBodyInit *b)
{
    if (!b)
        return;
    b->i124 = 1;
    b->flagsC |= 0xE0;
    b->max[0] = 0.0f;
    b->max[1] = 0.0f;
    b->max[2] = 0.0f;
    b->max[3] = 1.0f;
    b->min[0] = 0.0f;
    b->min[1] = 0.0f;
    b->min[2] = 0.0f;
    b->min[3] = 0.0f;
    b->fC0 = 0.0f;
    b->scale = 1.0f;
    b->iD0 = 0;
    b->onHit = sub_00102FA0;
    b->ofs[0] = 0.0f;
    b->ofs[1] = 0.0f;
    b->ofs[2] = 0.0f;
    b->ofs[3] = 1.0f;
    b->radius = 0.0f;
    b->iEC = 0;
    sub_00080D20(b->list0F0);
    b->vF8[0] = 0.0f;
    b->vF8[1] = 0.0f;
    b->vF8[2] = 0.0f;
    b->vF8[3] = 1.0f;
    b->v108[0] = 0.0f;
    b->v108[1] = 0.0f;
    b->v108[2] = 0.0f;
    b->v108[3] = 1.0f;
    b->i118 = 0;
    sub_00080D20(b->list11C);
    b->flags128 = 0;
}
