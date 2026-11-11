/* Area r1i, group 10: body against box push-out 0x0001C280. Names inferred. */
#include "r1i.h"

/* 0x0001C280: unless a is of kind 6, test a's sphere (position plus
   offset, radius) against box; on contact move a out along the direction
   from the contact point to the sphere centre by the penetration depth,
   mark b touched, call b's hit handler (b, a, 0) and mark a pushed.
   regargs: a=ESI b=EDI; box is the stack argument */
void r1i_BodyPushOut(R1iBody *a, R1iBody *b, const R1iBox *box)
{
    float p[4], q[4];
    float depth;
    if (a->kind == 6)
        return;
    p[0] = a->ofs[0] + a->pos[0];
    p[1] = a->pos[1] + a->ofs[1];
    p[2] = a->pos[2] + a->ofs[2];
    p[3] = a->pos[3];
    if (!sub_0001B9E0(box, p, a->radius, q, 0))
        return;
    depth = a->radius - r4_Distance(q, p);
    q[0] = p[0] - q[0];
    q[1] = p[1] - q[1];
    q[2] = p[2] - q[2];
    q[3] = p[3];
    sub_001AD7E0(q, q);
    sub_001ADB60(q, q, depth);
    a->pos[0] = a->pos[0] + q[0];
    a->pos[1] = a->pos[1] + q[1];
    a->pos[2] = a->pos[2] + q[2];
    b->flags128 |= 1;
    b->onHit(b, a, 0);
    a->flags128 |= 0x80000000;
}
