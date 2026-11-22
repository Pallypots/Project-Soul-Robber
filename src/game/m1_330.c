/* Area m1, file 330: angle of a 2D direction by bisection. Names inferred. */
#include <stdint.h>

void sub_001AD7E0(float *d, const float *s);           /* normalise */
void sub_001AD940(void *m);                            /* identity */
void sub_001AD8E0(void *d, const void *s, float a);    /* d = s rotated about Y by a */
void sub_001AD9B0(void *dst, const void *a, const void *b);

/* 0x82A90: angle (radians) of the direction (b, a) in the X/Z plane, found by ten bisection
   steps of a Y rotation in the first quadrant and then mirrored into the right quadrant.
   Axis cases return +-pi/2, 0 or pi directly. Stack args (a b). */
float m1_DirAngle082A90(float a, float b) {
    float v[4];
    float u[4];
    float w[4];
    float m[16];
    float r[16];
    float step, ang, res;
    int q, i;
    if (b == 0.0f)
        return 0.0f > a ? -1.5707964f : 1.5707964f;
    if (a == 0.0f) {
        res = 0.0f;
        if (0.0f > b)
            res = 3.1415927f;
        return res;
    }
    q = 0;
    if (0.0f > b)
        q = 1;
    if (0.0f > a)
        q |= 2;
    if (0.0f > b)
        b = 0.0f - b;
    if (0.0f > a)
        a = 0.0f - a;
    v[0] = b;
    v[1] = 0.0f;
    v[2] = a;
    v[3] = 0.0f;
    sub_001AD7E0(v, v);
    u[0] = 1.0f;
    u[3] = 0.0f;
    u[2] = 0.0f;
    u[1] = 0.0f;
    step = 0.7853982f;
    ang = -0.7853982f;
    sub_001AD940(m);
    for (i = 10; i != 0; i--) {
        sub_001AD8E0(r, m, ang);
        sub_001AD9B0(w, r, u);
        step = step * 0.5f;
        if (v[0] > w[0])
            ang = step + ang;
        else
            ang = ang - step;
    }
    res = 0.0f - ang;
    switch (q) {
    case 1:
        return 3.1415927f - res;
    case 2:
        return 0.0f - res;
    case 3:
        return res - 3.1415927f;
    }
    return res;
}
