/* Area r4j: look-at transform (0x001AE210). Names inferred. */
#include "r4j.h"

/* 0x001AE210: build a camera matrix from a position, a view direction and
   an up vector and pass it to 0x001AE060 (which fills xf): row 0 is the
   normalised up x dir, row 2 the normalised direction, row 1 the negated
   row0 x row2 cross product (computed as row2 x row0 components), row 3
   the identity row moved by pos. Stack args (xf pos dir up). */
void r4j_LookAt(void *xf, const float *pos, const float *dir, const float *up)
{
    R4jVec4 c, side;
    R4jVec4 m[4];

    m[0].v[0] = 1.0f;
    m[1].v[1] = 1.0f;
    m[2].v[2] = 1.0f;
    m[3].v[3] = 1.0f;
    c.v[0] = up[1] * dir[2] - dir[1] * up[2];
    c.v[1] = dir[0] * up[2] - up[0] * dir[2];
    c.v[2] = dir[1] * up[0] - up[1] * dir[0];
    c.v[3] = 0.0f;
    side = c;
    m[0].v[1] = 0.0f;
    m[0].v[2] = 0.0f;
    m[0].v[3] = 0.0f;
    m[1].v[0] = 0.0f;
    m[1].v[2] = 0.0f;
    m[1].v[3] = 0.0f;
    m[2].v[0] = 0.0f;
    m[2].v[1] = 0.0f;
    m[2].v[3] = 0.0f;
    m[3].v[0] = 0.0f;
    m[3].v[1] = 0.0f;
    m[3].v[2] = 0.0f;
    sub_001AD7E0(m[0].v, side.v);
    sub_001AD7E0(m[2].v, dir);
    c.v[0] = m[0].v[2] * m[2].v[1] - m[2].v[2] * m[0].v[1];
    c.v[1] = m[2].v[2] * m[0].v[0] - m[0].v[2] * m[2].v[0];
    c.v[2] = m[0].v[1] * m[2].v[0] - m[2].v[1] * m[0].v[0];
    c.v[3] = 0.0f;
    m[1] = c;
    m[1].v[0] = m[1].v[0] * -1.0f;
    m[1].v[1] = m[1].v[1] * -1.0f;
    m[1].v[2] = m[1].v[2] * -1.0f;
    m[3].v[0] = pos[0] + m[3].v[0];
    m[3].v[1] = pos[1] + m[3].v[1];
    m[3].v[2] = pos[2] + m[3].v[2];
    sub_001AE060(xf, m[0].v);
}
