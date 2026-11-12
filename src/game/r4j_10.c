/* Area r4j: rotation about a unit axis (0x001B3700). Names inferred. */
#include "r4j.h"

/* 0x001B3700: set m to the rotation of angle (radians) about the unit
   axis (x y z): identity first, then the upper 3x3 block
   (1-c) * a_i * a_j + c on the diagonal and -/+ s * a_k off it.
   regargs: m=EDI axis=ESI; stack arg (angle). 0x001A3ED0 returns the sine
   and 0x001A3EE0 the cosine. */
void r4j_MatRotUnitAxis(float *m, const float *axis, float angle)
{
    float s = sub_001A3ED0(angle);
    float c = sub_001A3EE0(angle);
    float k;

    sub_001AD940(m);
    k = 1.0f - c;
    m[0] = k * axis[0] * axis[0] + c;
    m[1] = k * axis[0] * axis[1] + axis[2] * s;
    m[2] = axis[2] * k * axis[0] - s * axis[1];
    m[4] = k * axis[0] * axis[1] - axis[2] * s;
    m[5] = k * axis[1] * axis[1] + c;
    m[6] = axis[2] * k * axis[1] + axis[0] * s;
    m[8] = axis[2] * k * axis[0] + s * axis[1];
    m[9] = axis[2] * k * axis[1] - axis[0] * s;
    m[10] = axis[2] * axis[2] * k + c;
}
