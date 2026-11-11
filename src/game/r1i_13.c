/* Area r1i, group 13: body against world 0x0001C630. Names inferred. */
#include "r1i.h"

/* 0x0001C630: collide sphere centre pos (radius b->radius) with the
   world up to twice: query the pool around pos into b's contact list and,
   when the nearest hit lies against the body's motion (pos - node row),
   move pos out along the flattened (never upwards) direction from the hit
   by the distance from the radius. Finally the body position becomes pos
   minus its offset. Returns 1 when pos was moved. */
int r1i_BodyHitWorld(R1iBody *b, float *pos, void **list)
{
    float v[4], d[4];
    float r, len;
    uint8_t *h;
    void *pool;
    int hit, i;
    if (0.0f >= b->radius)
        return 0;
    sub_001AD9F0(v, b->pos, b->node->v70);
    hit = 0;
    for (i = 0; i < 2; i++) {
        r = b->radius;
        pool = sub_00080970();
        sub_000822D0(0, pool, pos, r, *list, b->list0F0);
        h = sub_00080CF0(pool, pos);
        if (!h)
            break;
        sub_001AD9F0(d, pos, (const float *)(h + 0x40));
        if (0.0f > sub_001AD9D0(v, d)) {
            len = sub_00082D70(d);
            if (d[1] > 0.0f)
                d[1] = 0.0f;
            sub_001AD7E0(d, d);
            if (b->radius > len)
                sub_001ADBA0(d, d, b->radius - len);
            else
                sub_001ADBA0(d, d, len - b->radius);
            sub_001ADAF0(pos, pos, d);
            hit = 1;
        }
    }
    sub_001AD9F0(b->pos, pos, b->ofs);
    return hit;
}
