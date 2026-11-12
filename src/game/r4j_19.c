/* Area r4j: rotation matrix to quaternion (0x001AF0A0). Names inferred. */
#include "r4j.h"

/* 0x001AF0A0: convert the rotation part of the 4x4 matrix m into the
   quaternion q (q[0] = -w, then x y z). With a positive trace the w term
   comes from sqrt(trace + 2); otherwise from the largest diagonal element
   i (next axes j, k from the table {1, 2, 0}), guarding the 0.5 / s factor
   against s == 0. 0x001A3F50 is sqrt. regargs: m=ESI; stack arg (q). */
void r4j_MatToQuat(const float *m, float *q)
{
    float tr, s, t;
    float v[4];
    int i, j, k;

    tr = m[5] + m[0] + m[10];
    if (tr > 0.0f) {
        s = sub_001A3F50(tr + 1.0f + 1.0f);
        q[0] = -(s * 0.5f);
        t = 0.5f / s;
        q[1] = (m[6] - m[9]) * t;
        q[2] = (m[8] - m[2]) * t;
        q[3] = (m[1] - m[4]) * t;
        return;
    }
    i = 0;
    if (m[5] > m[0])
        i = 1;
    if (m[10] > m[i * 5])
        i = 2;
    j = r4j_next367E58[i];
    k = r4j_next367E58[j];
    s = m[i * 5] - (m[k * 5] + m[j * 5]) + 1.0f;
    s = sub_001A3F50(s);
    v[i] = s * 0.5f;
    if (s != 0.0f)
        t = 0.5f / s;
    else
        t = s;
    v[3] = (m[j * 4 + k] - m[k * 4 + j]) * t;
    v[j] = (m[j * 4 + i] + m[i * 4 + j]) * t;
    v[k] = (m[k * 4 + i] + m[i * 4 + k]) * t;
    q[0] = 0.0f - v[3];
    q[1] = v[0];
    q[2] = v[1];
    q[3] = v[2];
}
