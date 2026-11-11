/* Area r6h: actor body sync (r6h_14). Names inferred. */
#include "r6h.h"

/* 0x000A3B80: copy the position and rotation of actor a into its body (w = 1)
   and update the body's node: when the body is node-driven (flag bit 8) only
   the node position is set, otherwise the node gets the matrix built from the
   rotation angles (third, second, first), uniform scale and position. */
void r6h_ActorSyncBody(R6hActor2 *a)
{
    float m[4][4];
    uint8_t *node = a->body->node;

    sub_000F5D40(&a->body->pos, &a->pos);
    a->pos.w = 1.0f;
    a->body->pos.w = 1.0f;
    sub_000F5D40(&a->body->rot, &a->rot);
    a->rot.w = 1.0f;
    a->body->rot.w = 1.0f;
    if (!(a->body->flags & 0x100)) {
        sub_001AD940(m);
        sub_001AD910(m, m, a->rot.z);
        sub_001AD8E0(m, m, a->rot.y);
        sub_001AD8B0(m, m, a->rot.x);
        sub_001ADBA0(m[0], m[0], a->scale);
        sub_001ADBA0(m[1], m[1], a->scale);
        sub_001ADBA0(m[2], m[2], a->scale);
        sub_000F5D40(m[3], &a->body->pos);
        sub_001ADA40(node, m);
    } else {
        sub_000F5D40(node + 0x30, &a->body->pos);
    }
}
