/* Area r1i, group 15: release a character unit chain 0x0001E550. Names inferred. */
#include "r1i.h"

/* 0x0001E550: unless head is null or locked (flag 4), release every unit
   of the chain: hide it, free its models, textures (the head also frees
   the texture of its first kind-1 texture entry), buffers and resources,
   reset its transform vectors (128 for the colour) and set state 9.
   Finally the head's resource pair is set to -1. */
void r1i_UnitsRelease(R1iUnit *head)
{
    R1iUnit *u;
    R1iUnitTex *t;
    if (!head || (head->flags & 4))
        return;
    for (t = head->texList; t; t = t->next)
        if (t->kind == 1)
            break;
    u = head;
    do {
        u->flags &= ~1u;
        u->i18 = 0;
        u->i14 = 0;
        if (u->shadow) {
            sub_00074F10(u->shadow);
            sub_000754A0(u->shadow);
            sub_000751C0(u->shadow);
        }
        if (u == head && t && t->tex != -1) {
            t->flags &= ~4u;
            t->i44 = 0;
            sub_001B9FC0(t->tex);
            t->tex = -1;
        }
        u->shadow = 0;
        u->p24 = 0;
        u->model = 0;
        u->p2C = 0;
        u->fx = 0;
        u->p34 = 0;
        if (u->tex[0] != -1) {
            sub_001B9FC0(u->tex[0]);
            u->tex[0] = -1;
        }
        if (u->tex[1] != -1) {
            sub_001B9FC0(u->tex[1]);
            u->tex[1] = -1;
        }
        if (u->tex[2] != -1) {
            sub_001B9FC0(u->tex[2]);
            u->tex[2] = -1;
        }
        if (u->blk12C) {
            sub_00053880(u->blk12C->buf);
            sub_00053880(u->blk12C);
            u->blk12C = 0;
        }
        if (u->blk130) {
            sub_00053880(u->blk130->buf);
            sub_00053880(u->blk130);
            u->blk130 = 0;
        }
        sub_000533B0(u->res4, u->res8);
        if (u->blk138) {
            sub_00053880(u->blk138->buf);
            sub_00053880(u->blk138);
            u->blk138 = 0;
        }
        if (u->p134) {
            sub_00033C20(u->p134);
            u->p134 = 0;
        }
        if (u->p13C) {
            sub_0005BC50(u->p13C);
            u->p13C = 0;
        }
        u->v50[3] = 0.0f;
        u->v50[2] = 0.0f;
        u->v50[1] = 0.0f;
        u->v50[0] = 0.0f;
        u->v60[0] = 0.0f;
        u->v60[1] = 0.0f;
        u->v60[2] = 0.0f;
        u->v60[3] = 1.0f;
        u->v70[3] = 0.0f;
        u->v70[2] = 1.0f;
        u->v70[1] = 1.0f;
        u->v70[0] = 1.0f;
        u->v80[0] = 0.0f;
        u->v80[1] = 0.0f;
        u->v80[2] = 0.0f;
        u->v80[3] = 1.0f;
        u->v90[3] = 128.0f;
        u->v90[2] = 128.0f;
        u->v90[1] = 128.0f;
        u->v90[0] = 128.0f;
        u->i140 = 0;
        u->i144 = 0;
        if (u->buf148) {
            sub_00053880(u->buf148);
            u->buf148 = 0;
        }
        u->state = 9;
        u = u->next;
    } while (u);
    head->res4 = -1;
    head->res8 = -1;
}
