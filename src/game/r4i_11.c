/* Area r4i: segment against cylinder test (0x00194F00). Names inferred. */
#include "r4i.h"

/* 0x00194F00: intersect the segment seg[0..3] -> seg[4..7] with the
   upright cylinder c (radius +0x10, reaching +0x14 below its position).
   Segments shorter than 0.05 never hit. Solves the XZ circle crossing
   for the entry point t in 0..1; the point must lie between the top
   (height of c) and the bottom. On a hit writes the point (w taken from
   the scaled direction) and returns 1, else 0. Stack args (c seg out). */
int r4i_SegHitCyl(const R4iCyl *c, const float *seg, float *out)
{
    float r = c->r10;
    float dir[4];
    float rel[4];
    float step[4];
    float q[4];
    float a;
    float b;
    float disc;
    float t;

    if (!seg)
        return 0;
    r4i_VecSub(dir, seg + 4, seg);
    if (0.05f > sub_001A3F50(dir[2] * dir[2] + dir[1] * dir[1] + dir[0] * dir[0]))
        return 0;
    r4i_VecSub(rel, seg, c->pos);
    a = dir[2] * dir[2] + dir[0] * dir[0];
    b = (rel[2] * dir[2] + rel[0] * dir[0]) * 2.0f;
    disc = b * b - ((rel[2] * rel[2] + rel[0] * rel[0]) - r * r) * a * 4.0f;
    if (0.0f > disc)
        return 0;
    t = (-b - sub_001A3F50(disc)) / (a + a);
    if (0.0f > t || t > 1.0f)
        return 0;
    sub_001ADB60(step, dir, t);
    sub_001ADAF0(q, rel, step);
    if (!(0.0f >= q[1]) || !(q[1] >= 0.0f - c->h14))
        return 0;
    out[0] = seg[0] + step[0];
    out[1] = seg[1] + step[1];
    out[2] = seg[2] + step[2];
    out[3] = step[3];
    return 1;
}
